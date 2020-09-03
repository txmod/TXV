
precision highp float;
//precision mediump float;

// Varyings
varying vec4 v_texCoord0;

// Uniforms
uniform sampler2D u_texture0Sampler;
uniform mediump float u_brightness;
uniform mediump float u_contrast;
uniform mediump float u_saturation;
uniform lowp int u_invert;

/*
 ** Contrast, saturation, brightness
 ** Code of this function is from TGM's shader pack
 ** http://irrlicht.sourceforge.net/phpBB2/viewtopic.php?t=21057
 */

// For all settings: 1.0 = 100% 0.5=50% 1.5 = 150%

vec3 BrightnessContrastSaturation(vec3 color, float brt, float con, float sat)
{
	// Increase or decrease these values to adjust r, g and b color channels seperately
	const float AvgLumR = 0.5;
	const float AvgLumG = 0.5;
	const float AvgLumB = 0.5;
	
	const vec3 LumCoeff = vec3(0.2125, 0.7154, 0.0721);
	
	vec3 AvgLumin = vec3(AvgLumR, AvgLumG, AvgLumB);
	vec3 brtColor = color * brt;
	vec3 intensity = vec3(dot(brtColor, LumCoeff));
	vec3 satColor = mix(intensity, brtColor, sat);
	vec3 conColor = mix(AvgLumin, satColor, con);
	return conColor;
}

void main() 
{
	vec4 t0;
    vec3 inv;
    vec3 bcs;
    vec4 outColor;
    
    t0 = texture2D(u_texture0Sampler, v_texCoord0.st);
    if (u_invert == 1) {
        inv = vec3(1.0, 1.0, 1.0) - t0.rgb;
    } else {
        inv = t0.rgb;
    };
    bcs = BrightnessContrastSaturation(inv, u_brightness, u_contrast, u_saturation);
    outColor = vec4(bcs, t0.a);
	gl_FragColor = outColor;
}
