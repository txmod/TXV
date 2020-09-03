#version 120

// texcoords
varying vec2 texcoord0;
varying vec2 texcoord1;

// samplers
uniform sampler2DRect u_texture0Sampler;
uniform sampler2DRect u_texture1Sampler;

uniform vec2 u_texdim0;
uniform vec2 u_texdim1;

uniform float luma;
uniform float tolerance;
uniform float fade;

uniform int invert;
uniform int maskMode;
uniform int showSourceImage2;

//uniform vec4 lumcoeff; // use constant instead

void main()
{
    const vec4 lumcoeff = vec4(0.2125, 0.7154, 0.0721, 0.0);
	//const vec4 one = vec4(1.0);
    const vec4 black = vec4(0,0,0,0);
    vec4 a;
    vec4 b;
    
    if ((texcoord0.x < 1) || (texcoord0.x > (u_texdim0.x - 1)) || (texcoord0.y < 1) || (texcoord0.y > (u_texdim0.y - 1)) ) {
        a = black;
    } else {
        a = texture2DRect(u_texture0Sampler, texcoord0);
    };
    if ((texcoord1.x < 1) || (texcoord1.x > (u_texdim1.x - 1)) || (texcoord1.y < 1) || (texcoord1.y > (u_texdim1.y - 1)) ) {
        b = black;
    } else {
        b = texture2DRect(u_texture1Sampler, texcoord1);
    };
    
	// calculate our luminance
	float luminance = dot(a,lumcoeff);
    
	// measure distance from target
	float delta = abs(luminance-luma);
    
	// determine scaling coefficient witin our fade range
	float scale = smoothstep(abs(tolerance),abs(tolerance)+abs(fade),delta);
    
	// invert if necessary
    float mixamount;
    if (invert == 1) {
        mixamount = 1.0 - scale;
    } else {
        mixamount = scale;
    };
    
    vec4 mColor;
    // output either mixColor or mask based on maskMode
    if (maskMode == 1) {
        mColor = vec4(mixamount);
    } else {
        vec4 mixColor;
        if (showSourceImage2 == 1) {
            // blend between sources based on mixamount
            mixColor = mix(b,a,vec4(mixamount));
        } else {
            // if not showSourceImage2 just set alpha value
            a.a = mixamount;
            mixColor = a;
        };
        mColor = mixColor;
    };
    
    gl_FragColor = mColor;
	
	// setting the fragment color is a useful means of debugging
	//gl_FragColor = vec4(luminance);
}
