uniform vec2 resolution;
//uniform vec2 mouse;
uniform float time;
uniform float zoom;
uniform vec4 color1;
//uniform vec4 color2;
//uniform vec4 color3;
//uniform vec4 color4;

const float pi = 3.1415926;

void main(void){
    vec2 p = -1.0 + 2.0 * gl_FragCoord.xy / resolution.xy;
	p.y *= resolution.y/resolution.x;
	p *= zoom*10.0;
	const float tot = pi*2.0;
	const float n = 9.0;
	const float df = tot/n;
    float c = 0.0;
	float t = time*2.0;

	for (float phi =0.0; phi < tot; phi+=df){
		c+=cos(cos(phi)*p.x+sin(phi)*p.y +t);
	}
	
    //gl_FragColor = vec4(c,c,c,1.0);
    gl_FragColor = vec4(c * color1.r,c * color1.g,c * color1.b,c * color1.a);
}