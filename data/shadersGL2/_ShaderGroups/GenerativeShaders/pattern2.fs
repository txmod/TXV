uniform float time;
uniform vec2 resolution;
//uniform vec4 mouse;
uniform float zoom;
uniform vec4 color1;
//uniform vec4 color2;
//uniform vec4 color3;
//uniform vec4 color4;

const float tot = 2.0*3.1415926;

void main(void){
    vec2 p = -1.0 + zoom * gl_FragCoord.xy / resolution.xy;
    p.y *= resolution.y/resolution.x;
    p *= 100.0;
    const float n = 9.0;
    const float df = tot/n; 
    float c = 1.;
    float t = time*1.0;

    for (float phi =0.0; phi < tot; phi+=df){
        c+=cos(cos(phi)*p.x+sin(phi)*p.y+t*phi/tot);
    }

    //gl_FragColor = vec4(c,c,c,1.0);
    gl_FragColor = vec4(c * color1.r,c * color1.g,c * color1.b,c * color1.a);
}