#version 120

varying vec2 v_texCoord0;

uniform sampler2DRect tex0;
uniform float softEdge;// 0.001;
uniform float threshold;// 0.3;
uniform int invert;
uniform int maskMode;

void main(void)
{
	float f = softEdge/2.0;
	float a = threshold - f;
	float b = threshold + f;
	
	vec4 tx = texture2DRect(tex0, v_texCoord0);
	float l = (tx.x + tx.y + tx.z) / 3.0;
	
	float v = smoothstep(a, b, l);
	
    // invert if necessary
    float outV;
    if (invert == 1) {
        outV = 1.0 - v;
    } else {
        outV = v;
    };
    
    if (maskMode == 1) {
        gl_FragColor= vec4(outV);
    } else {
        gl_FragColor= outV * tx;
    };

}