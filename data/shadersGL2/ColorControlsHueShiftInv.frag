
#version 120

// change sampler2D to sampler2DRect and texture2D to texture2DRect
// Varyings
varying vec2 v_texCoord0;

// Uniforms
uniform sampler2DRect u_texture0Sampler;
uniform float u_brightness;
uniform float u_contrast;
uniform float u_contrastMidPoint;
uniform float u_saturation;
uniform int u_useHueshift;
uniform float u_hueshift;
uniform int u_invert;
uniform float u_fxMix;

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
	
//	vec3 AvgLumin = vec3(AvgLumR, AvgLumG, AvgLumB);
	vec3 AvgLumin = vec3(u_contrastMidPoint, u_contrastMidPoint, u_contrastMidPoint);
	vec3 brtColor = color * brt;
	vec3 intensity = vec3(dot(brtColor, LumCoeff));
	vec3 satColor = mix(intensity, brtColor, sat);
	vec3 conColor = mix(AvgLumin, satColor, con);
	return conColor;
}

/*
 ** Hue, saturation, luminance
 */

vec3 RGBToHSL(vec3 color)
{
	vec3 hsl; // init to 0 to avoid warnings ? (and reverse if + remove first part)
	
	float fmin = min(min(color.r, color.g), color.b);    //Min. value of RGB
	float fmax = max(max(color.r, color.g), color.b);    //Max. value of RGB
	float delta = fmax - fmin;             //Delta RGB value
    
	hsl.z = (fmax + fmin) / 2.0; // Luminance
    
	if (delta == 0.0)		//This is a gray, no chroma...
	{
		hsl.x = 0.0;	// Hue
		hsl.y = 0.0;	// Saturation
	}
	else                                    //Chromatic data...
	{
		if (hsl.z < 0.5)
        hsl.y = delta / (fmax + fmin); // Saturation
		else
        hsl.y = delta / (2.0 - fmax - fmin); // Saturation
		
		float deltaR = (((fmax - color.r) / 6.0) + (delta / 2.0)) / delta;
		float deltaG = (((fmax - color.g) / 6.0) + (delta / 2.0)) / delta;
		float deltaB = (((fmax - color.b) / 6.0) + (delta / 2.0)) / delta;
        
		if (color.r == fmax )
        hsl.x = deltaB - deltaG; // Hue
		else if (color.g == fmax)
        hsl.x = (1.0 / 3.0) + deltaR - deltaB; // Hue
		else if (color.b == fmax)
        hsl.x = (2.0 / 3.0) + deltaG - deltaR; // Hue
        
		if (hsl.x < 0.0)
        hsl.x += 1.0; // Hue
		else if (hsl.x > 1.0)
        hsl.x -= 1.0; // Hue
	}
    
	return hsl;
}

float HueToRGB(float f1, float f2, float hue)
{
	if (hue < 0.0)
    hue += 1.0;
	else if (hue > 1.0)
    hue -= 1.0;
	float res;
	if ((6.0 * hue) < 1.0)
    res = f1 + (f2 - f1) * 6.0 * hue;
	else if ((2.0 * hue) < 1.0)
    res = f2;
	else if ((3.0 * hue) < 2.0)
    res = f1 + (f2 - f1) * ((2.0 / 3.0) - hue) * 6.0;
	else
    res = f1;
	return res;
}

vec3 HSLToRGB(vec3 hsl)
{
	vec3 rgb;
	
	if (hsl.y == 0.0)
    rgb = vec3(hsl.z); // Luminance
	else
	{
		float f2;
		
		if (hsl.z < 0.5)
        f2 = hsl.z * (1.0 + hsl.y);
		else
        f2 = (hsl.z + hsl.y) - (hsl.y * hsl.z);
        
		float f1 = 2.0 * hsl.z - f2;
		
		rgb.r = HueToRGB(f1, f2, hsl.x + (1.0/3.0));
		rgb.g = HueToRGB(f1, f2, hsl.x);
		rgb.b = HueToRGB(f1, f2, hsl.x - (1.0/3.0));
	}
	
	return rgb;
}

void main() 
{
	vec4 t0;
    vec3 bcs;
    vec3 convertHSL;
    vec3 hueShifted;
    vec3 inverted;
    vec4 outColor;

    
    t0 = texture2DRect(u_texture0Sampler, v_texCoord0.st);
    bcs = BrightnessContrastSaturation(t0.rgb, u_brightness, u_contrast, u_saturation);
    if (u_useHueshift == 1) {
        convertHSL = RGBToHSL(bcs);
        hueShifted = HSLToRGB(vec3(convertHSL.x + u_hueshift , convertHSL.y, convertHSL.z));
    } else {
        hueShifted = bcs;
    };
    if (u_invert == 1) {
        inverted = vec3(1.0, 1.0, 1.0) - hueShifted;
    } else {
        inverted = hueShifted;
    };
    outColor = vec4(inverted, t0.a);
	gl_FragColor = mix(t0, outColor, u_fxMix);
}
