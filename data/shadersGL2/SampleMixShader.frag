
//precision highp float;
precision mediump float;

// Varyings
varying vec2 v_normal;
varying vec2 v_texCoord0;

// Uniforms
uniform sampler2D u_texture0Sampler;
uniform sampler2D u_texture1Sampler;

uniform mediump float u_mixTex1Tex2;
uniform mediump float u_brightnessTex1;
uniform mediump float u_contrastTex1;
uniform mediump float u_saturationTex1;
uniform mediump float u_brightnessTex2;
uniform mediump float u_contrastTex2;
uniform mediump float u_saturationTex2;

/*
 ** Photoshop & misc math
 ** Romain Dura | Romz
 ** Blog: http://blog.mouaif.org
 ** Post: http://blog.mouaif.org/?p=94
 */

/*
** Contrast, saturation, brightness
** Code of this function is from TGM's shader pack
** http://irrlicht.sourceforge.net/phpBB2/viewtopic.php?t=21057
*/

// BrightnessContrastSaturation - For all settings: 1.0 = 100% 0.5=50% 1.5 = 150%
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

/*
 ********************************************
 */
void main() 
{
	vec3 tex0 = vec3(texture2D(u_texture0Sampler, v_texCoord0.st));
	vec3 tex1 = vec3(texture2D(u_texture1Sampler, v_normal.st));
	vec3 color0 = BrightnessContrastSaturation(tex0, u_brightnessTex1, u_contrastTex1, u_saturationTex1);
	vec3 color1 = BrightnessContrastSaturation(tex1, u_brightnessTex2, u_contrastTex2, u_saturationTex2);

	vec4 color = vec4(mix(color0, color1, u_mixTex1Tex2), 1);

	gl_FragColor = color;
}

