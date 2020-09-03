uniform float time;
uniform vec2 resolution;
uniform vec2 mouse;
uniform float zoom;
uniform vec4 color1;
//uniform vec4 color2;
//uniform vec4 color3;
//uniform vec4 color4;

vec3 mod289(vec3 x) {
	return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec2 mod289(vec2 x) {
	return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec3 permute(vec3 x) {
	return mod289(((x*34.0)+1.0)*x);
}

float snoise(vec2 v){
	const vec4 C = vec4(0.211324865405187, 0.366025403784439, -0.577350269189626, 0.024390243902439);
	
	vec2 i  = floor(v + dot(v, C.yy) );
	vec2 x0 = v -   i + dot(i, C.xx);
	
	vec2 i1;
	
	i1 = (x0.x > x0.y) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);
	
	vec4 x12 = x0.xyxy + C.xxzz;
	x12.xy -= i1;
	
	i = mod289(i);
	vec3 p = permute( permute( i.y + vec3(0.0, i1.y, 1.0 )) + i.x + vec3(0.0, i1.x, 1.0 ));
	
	vec3 m = max(0.5 - vec3(dot(x0,x0), dot(x12.xy,x12.xy), dot(x12.zw,x12.zw)), 0.0);
	m = m*m ;
	m = m*m ;
	
	vec3 x = 2.0 * fract(p * C.www) - 1.0;
	vec3 h = abs(x) - 0.5;
	vec3 ox = floor(x + 0.5);
	vec3 a0 = x - ox;
	
	m *= 1.79284291400159 - 0.85373472095314 * ( a0*a0 + h*h );
	
	vec3 g;
	g.x  = a0.x  * x0.x  + h.x  * x0.y;
	g.yz = a0.yz * x12.xz + h.yz * x12.yw;
	return 130.0 * dot(m, g);
}

void main( void ) {
	vec2 p = zoom * ( gl_FragCoord.xy / resolution.xy );
	p = (p * 2.0 - 1.0) * vec2(800, 600);
	p += mouse * 8196.0;
	float z = 84.0;
	
	float v = snoise(p * 0.002 + z + 0.05 * time);  p += 1017.0;
	v += 0.5 * snoise(p * 0.004 - 0.2 * time);
	v += 0.125 * snoise(p * 0.008 + 0.0001 * v * time);
	v = 0.15 * v + 0.7;
	
	//gl_FragColor = vec4(v);
    gl_FragColor = vec4(v*color1.r,v*color1.g,v*color1.b,v*color1.a);
}