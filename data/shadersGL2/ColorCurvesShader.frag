
#version 120

// changes for #version 120: OpenGL 2.1
// change sampler2D to sampler2DRect and texture2D to texture2DRect

// Varyings
varying vec2 v_texCoord0;

// Uniforms
uniform sampler2DRect u_texture0Sampler;
uniform sampler2DRect u_curveSampler;

uniform int u_curvesMode;
uniform float u_redCurveMorph;
uniform float u_greenCurveMorph;
uniform float u_blueCurveMorph;
uniform float u_curvesMix;
//uniform float u_gamma;
uniform float u_inputMin;
uniform float u_inputMax;
uniform float u_outputMin;
uniform float u_outputMax;
uniform int u_useRedCurveForGreen;
uniform int u_useRedCurveForBlue;

uniform int u_posterize;
uniform int u_posterizeSteps;
uniform float u_posterizeBias;
uniform int u_channelReorder;
uniform float u_redMultiply;
uniform float u_greenMultiply;
uniform float u_blueMultiply;
uniform int u_blendMode;
uniform float u_blendMix;
uniform int u_blendReverse;

/*
 ** Gamma correction
 ** Details: http://mouaif.wordpress.com/2009/01/22/photoshop-gamma-correction-shader/
 */

//OLD: #define GammaCorrection(color, gamma)								pow(color, vec3(1.0 / gamma))
// NEW changed by paul to remove divide - done in c++ instead
#define GammaCorrection(color, gamma)								pow(color, vec3(1.0 / gamma))

/*
 ** Levels control (input (+gamma), output)
 ** Details: http://blog.mouaif.org/2009/01/28/levels-control-shader/
 */

//OLD: #define LevelsControlInputRange(color, minInput, maxInput)				min(max(color - vec3(minInput), vec3(0.0)) / (vec3(maxInput) - vec3(minInput)), vec3(1.0))
// NEW changed by paul - quicker:
#define LevelsControlInputRange(color, minInput, maxInput)				min(max(color - vec3(minInput), vec3(0.0)) / vec3(maxInput- minInput), vec3(1.0))
#define LevelsControlInput(color, minInput, gamma, maxInput)			GammaCorrection(LevelsControlInputRange(color, minInput, maxInput), gamma)
#define LevelsControlOutputRange(color, minOutput, maxOutput) 			mix(vec3(minOutput), vec3(maxOutput), color)
#define LevelsControl(color, minInput, gamma, maxInput, minOutput, maxOutput) 	LevelsControlOutputRange(LevelsControlInput(color, minInput, gamma, maxInput), minOutput, maxOutput)

/*
 ** Photoshop & misc math
 ** Romain Dura | Romz
 ** Blog: http://blog.mouaif.org
 ** Post: http://blog.mouaif.org/?p=94
 */

// ** Hue, saturation, luminance

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
		rgb.b= HueToRGB(f1, f2, hsl.x - (1.0/3.0));
	}

	return rgb;
}

/*
 ** Float blending modes
 ** Adapted from here: http://www.nathanm.com/photoshop-blending-math/
 ** But I modified the HardMix (wrong condition), Overlay, SoftLight, ColorDodge, ColorBurn, VividLight, PinLight (inverted layers) ones to have correct results
 */

#define BlendLinearDodgef 			BlendAddf
#define BlendLinearBurnf 			BlendSubstractf
#define BlendAddf(base, blend) 		min(base + blend, 1.0)
#define BlendSubstractf(base, blend) 	max(base + blend - 1.0, 0.0)
#define BlendLightenf(base, blend) 		max(blend, base)
#define BlendDarkenf(base, blend) 		min(blend, base)
#define BlendLinearLightf(base, blend) 	(blend < 0.5 ? BlendLinearBurnf(base, (2.0 * blend)) : BlendLinearDodgef(base, (2.0 * (blend - 0.5))))
#define BlendScreenf(base, blend) 		(1.0 - ((1.0 - base) * (1.0 - blend)))
#define BlendOverlayf(base, blend) 	(base < 0.5 ? (2.0 * base * blend) : (1.0 - 2.0 * (1.0 - base) * (1.0 - blend)))
#define BlendSoftLightf(base, blend) 	((blend < 0.5) ? (2.0 * base * blend + base * base * (1.0 - 2.0 * blend)) : (sqrt(base) * (2.0 * blend - 1.0) + 2.0 * base * (1.0 - blend)))
#define BlendColorDodgef(base, blend) 	((blend == 1.0) ? blend : min(base / (1.0 - blend), 1.0))
#define BlendColorBurnf(base, blend) 	((blend == 0.0) ? blend : max((1.0 - ((1.0 - base) / blend)), 0.0))
#define BlendVividLightf(base, blend) 	((blend < 0.5) ? BlendColorBurnf(base, (2.0 * blend)) : BlendColorDodgef(base, (2.0 * (blend - 0.5))))
#define BlendPinLightf(base, blend) 	((blend < 0.5) ? BlendDarkenf(base, (2.0 * blend)) : BlendLightenf(base, (2.0 *(blend - 0.5))))
#define BlendHardMixf(base, blend) 	((BlendVividLightf(base, blend) < 0.5) ? 0.0 : 1.0)
#define BlendReflectf(base, blend) 		((blend == 1.0) ? blend : min(base * base / (1.0 - blend), 1.0))

/*
 ** Vector3 blending modes
 */
// Component wise blending
#define Blend(base, blend, funcf) 		vec3(funcf(base.r, blend.r), funcf(base.g, blend.g), funcf(base.b, blend.b))

#define BlendNormal(base, blend) 		(blend)
#define BlendLighten				BlendLightenf
#define BlendDarken				BlendDarkenf
#define BlendMultiply(base, blend) 		(base * blend)
#define BlendAverage(base, blend) 		((base + blend) / 2.0)
#define BlendAdd(base, blend) 		min(base + blend, vec3(1.0))
#define BlendSubstract(base, blend) 	max(base + blend - vec3(1.0), vec3(0.0))
#define BlendDifference(base, blend) 	abs(base - blend)
#define BlendNegation(base, blend) 	(vec3(1.0) - abs(vec3(1.0) - base - blend))
#define BlendExclusion(base, blend) 	(base + blend - 2.0 * base * blend)
#define BlendScreen(base, blend) 		Blend(base, blend, BlendScreenf)
#define BlendOverlay(base, blend) 		Blend(base, blend, BlendOverlayf)
#define BlendSoftLight(base, blend) 	Blend(base, blend, BlendSoftLightf)
#define BlendHardLight(base, blend) 	BlendOverlay(blend, base)
#define BlendColorDodge(base, blend) 	Blend(base, blend, BlendColorDodgef)
#define BlendColorBurn(base, blend) 	Blend(base, blend, BlendColorBurnf)
#define BlendLinearDodge			BlendAdd
#define BlendLinearBurn			BlendSubstract
// Linear Light is another contrast-increasing mode
// If the blend color is darker than midgray, Linear Light darkens the image by decreasing the brightness. If the blend color is lighter than midgray, the result is a brighter image due to increased brightness.
#define BlendLinearLight(base, blend) 	Blend(base, blend, BlendLinearLightf)
#define BlendVividLight(base, blend) 	Blend(base, blend, BlendVividLightf)
#define BlendPinLight(base, blend) 		Blend(base, blend, BlendPinLightf)
#define BlendHardMix(base, blend) 		Blend(base, blend, BlendHardMixf)
#define BlendReflect(base, blend) 		Blend(base, blend, BlendReflectf)
#define BlendGlow(base, blend) 		BlendReflect(blend, base)
#define BlendPhoenix(base, blend) 		(min(base, blend) - max(base, blend) + vec3(1.0))
#define BlendOpacity(base, blend, F, O) 	(F(base, blend) * O + blend * (1.0 - O))

// Hue Blend mode creates the result color by combining the luminance and saturation of the base color with the hue of the blend color.
vec3 BlendHue(vec3 base, vec3 blend)
{
	vec3 baseHSL = RGBToHSL(base);
	return HSLToRGB(vec3(RGBToHSL(blend).r, baseHSL.g, baseHSL.b));
}

// Saturation Blend mode creates the result color by combining the luminance and hue of the base color with the saturation of the blend color.
vec3 BlendSaturation(vec3 base, vec3 blend)
{
	vec3 baseHSL = RGBToHSL(base);
	return HSLToRGB(vec3(baseHSL.r, RGBToHSL(blend).g, baseHSL.b));
}

// Color Mode keeps the brightness of the base color and applies both the hue and saturation of the blend color.
vec3 BlendColor(vec3 base, vec3 blend)
{
	vec3 blendHSL = RGBToHSL(blend);
	return HSLToRGB(vec3(blendHSL.r, blendHSL.g, RGBToHSL(base).b));
}

// Luminosity Blend mode creates the result color by combining the hue and saturation of the base color with the luminance of the blend color.
vec3 BlendLuminosity(vec3 base, vec3 blend)
{
	vec3 baseHSL = RGBToHSL(base);
	return HSLToRGB(vec3(baseHSL.r, baseHSL.g, RGBToHSL(blend).b));
}

vec3 getModColor (vec3 inColor, float sampleOffset) {
    float modColorRed;
    float modColorGreen;
    float modColorBlue;
    float modColorRed1;
    float modColorGreen1;
    float modColorBlue1;
    float modColorRed2;
    float modColorGreen2;
    float modColorBlue2;
    float redLookup = inColor.r * 255.0;
    float greenLookup = inColor.g * 255.0;
    float blueLookup = inColor.b * 255.0;
    
//    if (redLookup >= 255.0) {
//        modColorRed = texture2DRect(u_curveSampler, vec2(sampleOffset + redLookup, 0.0)).r;
//    } else {
//        modColorRed1 = texture2DRect(u_curveSampler, vec2(floor(sampleOffset + redLookup), 0.0)).r;
//        modColorRed2 = texture2DRect(u_curveSampler, vec2(floor(sampleOffset + redLookup)+1, 0.0)).r;
//        modColorRed = mix(modColorRed1, modColorRed2, fract(redLookup));
//    };
//    
//    if (u_useRedCurveForGreen == 1 && (u_curvesMode < 7)){
//        if (greenLookup >= 255.0) {
//            modColorGreen = texture2DRect(u_curveSampler, vec2(sampleOffset + greenLookup, 0.0)).r;
//        } else {
//            modColorGreen1 = texture2DRect(u_curveSampler, vec2(floor(sampleOffset + greenLookup), 0.0)).r;
//            modColorGreen2 = texture2DRect(u_curveSampler, vec2(floor(sampleOffset + greenLookup)+1, 0.0)).r;
//            modColorGreen = mix(modColorGreen1, modColorGreen2, fract(greenLookup));
//        };
//    } else {
//        if (greenLookup >= 255.0) {
//            modColorGreen = texture2DRect(u_curveSampler, vec2(sampleOffset + greenLookup, 0.0)).g;
//        } else {
//            modColorGreen1 = texture2DRect(u_curveSampler, vec2(floor(sampleOffset + greenLookup), 0.0)).g;
//            modColorGreen2 = texture2DRect(u_curveSampler, vec2(floor(sampleOffset + greenLookup)+1, 0.0)).g;
//            modColorGreen = mix(modColorGreen1, modColorGreen2, fract(greenLookup));
//        };
//    };
//    
//    if (u_useRedCurveForBlue == 1 && (u_curvesMode < 7)) {
//        if (blueLookup >= 255.0) {
//            modColorBlue = texture2DRect(u_curveSampler, vec2(sampleOffset + blueLookup, 0.0)).r;
//        } else {
//            modColorBlue1 = texture2DRect(u_curveSampler, vec2(floor(sampleOffset + blueLookup), 0.0)).r;
//            modColorBlue2 = texture2DRect(u_curveSampler, vec2(floor(sampleOffset + blueLookup)+1, 0.0)).r;
//            modColorBlue = mix(modColorBlue1, modColorBlue2, fract(blueLookup));
//        };
//    } else {
//        if (blueLookup >= 255.0) {
//            modColorBlue = texture2DRect(u_curveSampler, vec2(sampleOffset + blueLookup, 0.0)).b;
//        } else {
//            modColorBlue1 = texture2DRect(u_curveSampler, vec2(floor(sampleOffset + blueLookup), 0.0)).b;
//            modColorBlue2 = texture2DRect(u_curveSampler, vec2(floor(sampleOffset + blueLookup)+1, 0.0)).b;
//            modColorBlue = mix(modColorBlue1, modColorBlue2, fract(blueLookup));
//        };
//    };

    modColorRed = texture2DRect(u_curveSampler, vec2((1.0 + sampleOffset + redLookup), 0.0)).r;
    
    if (u_useRedCurveForGreen == 1 && (u_curvesMode < 7)){
            modColorGreen = texture2DRect(u_curveSampler, vec2((1.0 + sampleOffset + greenLookup), 0.0)).r;
    } else {
            modColorGreen = texture2DRect(u_curveSampler, vec2((1.0 + sampleOffset + greenLookup), 0.0)).g;
    };
    
    if (u_useRedCurveForBlue == 1 && (u_curvesMode < 7)) {
            modColorBlue = texture2DRect(u_curveSampler, vec2((1.0 + sampleOffset + blueLookup), 0.0)).r;
    } else {
            modColorBlue = texture2DRect(u_curveSampler, vec2((1.0 + sampleOffset + blueLookup), 0.0)).b;
    };
    return vec3(modColorRed, modColorGreen, modColorBlue);
}

void main()
{
    vec3 curvesColor;
    vec3 mixColor;
    vec3 postColor;
    vec3 swapColor;
    vec3 multiplyColor;
    vec3 blendColor;
    vec3 color0;
    vec3 color1;
    vec3 sampleColor1;
    vec3 sampleColor2;
    vec3 modColor;
    vec3 outColor;
	vec4 tex0 = texture2DRect(u_texture0Sampler, v_texCoord0.st);
    vec3 startColor = tex0.rgb;
    vec3 limitColor = LevelsControlInputRange(startColor, u_inputMin, u_inputMax);
    
    // convert if HSL
    if (u_curvesMode >= 7) {
        limitColor = RGBToHSL(limitColor);
    };
    
    sampleColor1 = getModColor(limitColor, 0.0);
    sampleColor2 = getModColor(limitColor, 256.0);
    float holdGreenMorph;
    float holdBlueMorph;
    if (u_useRedCurveForGreen == 1 && (u_curvesMode < 7)){
        holdGreenMorph = u_redCurveMorph;
    } else {
        holdGreenMorph = u_greenCurveMorph;
    };
    if (u_useRedCurveForBlue == 1 && (u_curvesMode < 7)){
        holdBlueMorph = u_redCurveMorph;
    } else {
        holdBlueMorph = u_blueCurveMorph;
    };
    modColor = vec3 (mix(sampleColor1.r, sampleColor2.r, u_redCurveMorph),
                     mix(sampleColor1.g, sampleColor2.g, holdGreenMorph),
                     mix(sampleColor1.b, sampleColor2.b, holdBlueMorph));

    // if not HSL, apply output range first
    if (u_curvesMode < 7) {
        modColor =  LevelsControlOutputRange(modColor, u_outputMin, u_outputMax);
    };
    
    if (u_curvesMode == 0) {
        // TXCOLORCURVESMODE_RGB
        curvesColor = vec3(modColor.r, modColor.g, modColor.b);
    } else if (u_curvesMode == 1) {
        // TXCOLORCURVESMODE_RED
        curvesColor = vec3(modColor.r, tex0.g, tex0.b);
    } else if (u_curvesMode == 2) {
        // TXCOLORCURVESMODE_GREEN
        curvesColor = vec3(tex0.r, modColor.g, tex0.b);
    } else if (u_curvesMode == 3) {
        // TXCOLORCURVESMODE_BLUE
        curvesColor = vec3(tex0.r, tex0.g, modColor.b);
    } else if (u_curvesMode == 4) {
        // TXCOLORCURVESMODE_REDGREEN
        curvesColor = vec3(modColor.r, modColor.g, tex0.b);
    } else if (u_curvesMode == 5) {
        // TXCOLORCURVESMODE_REDBLUE
        curvesColor = vec3(modColor.r, tex0.g, modColor.b);
    } else if (u_curvesMode == 6) {
        // TXCOLORCURVESMODE_GREENBLUE
        curvesColor = vec3(tex0.r, modColor.g, modColor.b);
    } else if (u_curvesMode == 7) {
        // TXCOLORCURVESMODE_HSL
        curvesColor = vec3(modColor.r, modColor.g, modColor.b);
    } else if (u_curvesMode == 8) {
        // TXCOLORCURVESMODE_HUE
        curvesColor = vec3(modColor.r, limitColor.g, limitColor.b);
    } else if (u_curvesMode == 9) {
        // TXCOLORCURVESMODE_SATURATION
        curvesColor = vec3(limitColor.r, modColor.g, limitColor.b);
    } else if (u_curvesMode == 10) {
        // TXCOLORCURVESMODE_LUMINOSITY
        curvesColor = vec3(limitColor.r, limitColor.g, modColor.b);
    } else if (u_curvesMode == 11) {
        // TXCOLORCURVESMODE_HUESATURATION
        curvesColor = vec3(modColor.r, modColor.g, limitColor.b);
    } else if (u_curvesMode == 12) {
        // TXCOLORCURVESMODE_HUELUMINOSITY
        curvesColor = vec3(modColor.r, limitColor.g, modColor.b);
    } else if (u_curvesMode == 13) {
        // TXCOLORCURVESMODE_SATURATIONLUMINOSITY
        curvesColor = vec3(limitColor.r, modColor.g, modColor.b);
    };
    
    // convert & apply output range if HSL
    if (u_curvesMode >= 7) {
        curvesColor = HSLToRGB(curvesColor);
        curvesColor =  LevelsControlOutputRange(curvesColor, u_outputMin, u_outputMax);
    };
    
    mixColor = mix(startColor, curvesColor, u_curvesMix);

    if (u_posterize == 0) {
        postColor = mixColor;
    } else {
        postColor = pow(mixColor, vec3(1.0 / u_posterizeBias));
        postColor = floor((postColor * vec3(u_posterizeSteps)) + vec3(0.5)) / vec3(u_posterizeSteps);
        postColor = LevelsControlOutputRange(postColor, u_outputMin, u_outputMax);
        postColor = pow(postColor, vec3(u_posterizeBias));
    };
    
    if (u_channelReorder == 0) {
        // TXCURVESCHANNELORDER_RGB
        swapColor = postColor;
    } else if (u_channelReorder == 1) {
        // TXCURVESCHANNELORDER_RBG
        swapColor = vec3(postColor.r, postColor.b, postColor.g);
    } else if (u_channelReorder == 2) {
        // TXCURVESCHANNELORDER_GBR
        swapColor = vec3(postColor.g, postColor.b, postColor.r);
    } else if (u_channelReorder == 3) {
        // TXCURVESCHANNELORDER_GRB
        swapColor = vec3(postColor.g, postColor.r, postColor.b);
    } else if (u_channelReorder == 4) {
        // TXCURVESCHANNELORDER_BRG
        swapColor = vec3(postColor.b, postColor.r, postColor.g);
    } else if (u_channelReorder == 5) {
        // TXCURVESCHANNELORDER_BGR
        swapColor = vec3(postColor.b, postColor.g, postColor.r);
    };
    
	multiplyColor = vec3(swapColor.r * u_redMultiply, swapColor.g * u_greenMultiply, swapColor.b * u_blueMultiply);
    
	if (u_blendReverse == 0) {color0 = startColor; color1 = multiplyColor;}
    else {color0 = multiplyColor; color1 = startColor;}
    
	if (u_blendMode == 0) {blendColor = BlendNormal(color0, color1);}
	else if (u_blendMode == 1) {blendColor = BlendLighten(color0, color1);}
	else if (u_blendMode == 2) {blendColor = BlendDarken(color0, color1);}
	else if (u_blendMode == 3) {blendColor = BlendMultiply(color0, color1);}
	else if (u_blendMode == 4) {blendColor = BlendAverage(color0, color1);}
	else if (u_blendMode == 5) {blendColor = BlendAdd(color0, color1);}
	else if (u_blendMode == 6) {blendColor = BlendSubstract(color0, color1);}
	else if (u_blendMode == 7) {blendColor = BlendDifference(color0, color1);}
	else if (u_blendMode == 8) {blendColor = BlendNegation(color0, color1);}
	else if (u_blendMode == 9) {blendColor = BlendExclusion(color0, color1);}
	else if (u_blendMode == 10) {blendColor = BlendScreen(color0, color1);}
	else if (u_blendMode == 11) {blendColor = BlendOverlay(color0, color1);}
	else if (u_blendMode == 12) {blendColor = BlendSoftLight(color0, color1);}
	else if (u_blendMode == 13) {blendColor = BlendHardLight(color0, color1);}
	else if (u_blendMode == 14) {blendColor = BlendColorDodge(color0, color1);}
	else if (u_blendMode == 15) {blendColor = BlendColorBurn(color0, color1);}
	else if (u_blendMode == 16) {blendColor = BlendLinearLight(color0, color1);}
	else if (u_blendMode == 17) {blendColor = BlendVividLight(color0, color1);}
	else if (u_blendMode == 18) {blendColor = BlendPinLight(color0, color1);}
	else if (u_blendMode == 19) {blendColor = BlendHardMix(color0, color1);}
	else if (u_blendMode == 20) {blendColor = BlendReflect(color0, color1);}
	else if (u_blendMode == 21) {blendColor = BlendGlow(color0, color1);}
	else if (u_blendMode == 22) {blendColor = BlendPhoenix(color0, color1);}
	else if (u_blendMode == 23) {blendColor = BlendHue(color0, color1);}
	else if (u_blendMode == 24) {blendColor = BlendSaturation(color0, color1);}
	else if (u_blendMode == 25) {blendColor = BlendColor(color0, color1);}
	else if (u_blendMode == 26) {blendColor = BlendLuminosity(color0, color1);}
    
    outColor = mix(color0, blendColor, u_blendMix);
    gl_FragColor = vec4(outColor.rgb, tex0.a);
}



