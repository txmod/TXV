#version 120

varying vec2 v_texCoord0;

uniform sampler2DRect tex0;
uniform float mix;
uniform float kernel0;
uniform float kernel1;
uniform float kernel2;
uniform float kernel3;
uniform float kernel4;
uniform float kernel5;
uniform float kernel6;
uniform float kernel7;
uniform float kernel8;

float kernel[9];
vec2 offset[9];

void main(void){
    vec2  st = v_texCoord0;
    vec4 sum = vec4(0.0);
    
    offset[0] = vec2(-1.0, -1.0);
    offset[1] = vec2(0.0, -1.0);
    offset[2] = vec2(1.0, -1.0);
    offset[3] = vec2(-1.0, 0.0);
    offset[4] = vec2(0.0, 0.0);
    offset[5] = vec2(1.0, 0.0);
    offset[6] = vec2(-1.0, 1.0);
    offset[7] = vec2(0.0, 1.0);
    offset[8] = vec2(1.0, 1.0);
    
//    kernel[0] = 1.0/16.0;   kernel[1] = 2.0/16.0;   kernel[2] = 1.0/16.0;
//    kernel[3] = 2.0/16.0;   kernel[4] = 4.0/16.0;   kernel[5] = 2.0/16.0;
//    kernel[6] = 1.0/16.0;   kernel[7] = 2.0/16.0;   kernel[8] = 1.0/16.0;
    kernel[0] = kernel0;
    kernel[1] = kernel1;
    kernel[2] = kernel2;
    kernel[3] = kernel3;
    kernel[4] = kernel4;
    kernel[5] = kernel5;
    kernel[6] = kernel6;
    kernel[7] = kernel7;
    kernel[8] = kernel8;
    
    int i = 0;
    for (i = 0; i < 4; i++){
        vec4 tmp = texture2DRect(tex0, st + offset[i]);
        sum += tmp * kernel[i];
    }
    
    for (i = 5; i < 9; i++){
        vec4 tmp = texture2DRect(tex0, st + offset[i]);
        sum += tmp * kernel[i];
    }
    
    vec4 color0 = texture2DRect(tex0, st + offset[4]);
    sum += color0 * kernel[4];
    
    gl_FragColor = (1.0 - mix) * color0 +  mix * vec4(sum.rgb, color0.a);
}