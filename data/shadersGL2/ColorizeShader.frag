
#version 120

// changes for #version 120: OpenGL 2.1
// change sampler2D to sampler2DRect and texture2D to texture2DRect

// Varyings
varying vec2 v_texCoord0;

// Uniforms
uniform sampler2DRect u_texture0Sampler;
uniform sampler2DRect u_curveSampler;
uniform vec2 u_texdim0;

uniform float u_curveAMorph;
uniform float u_curveBMorph;
uniform float u_curveCMorph;
uniform float u_curveDMorph;

uniform float u_band1Level;
uniform float u_band1SelectionMin;
uniform float u_band1SelectionMax;
uniform int u_band1SelectionChannel;
uniform float u_band1TintMix;
uniform int u_band1TintVaryBrightness;
uniform vec3 u_band1TintColor;
uniform int u_band1Mod1Type;
uniform int u_band1Mod1Channel;
uniform int u_band1Mod1Curve;
uniform float u_band1Mod1Freq;
uniform int u_band1Mod1PhaseBase;
uniform float u_band1Mod1PhaseOffset;
uniform int u_band1Mod2Type;
uniform int u_band1Mod2Channel;
uniform int u_band1Mod2Curve;
uniform float u_band1Mod2Freq;
uniform int u_band1Mod2PhaseBase;
uniform float u_band1Mod2PhaseOffset;

uniform float u_band2Level;
uniform float u_band2SelectionMin;
uniform float u_band2SelectionMax;
uniform int u_band2SelectionChannel;
uniform float u_band2TintMix;
uniform int u_band2TintVaryBrightness;
uniform vec3 u_band2TintColor;
uniform int u_band2Mod1Type;
uniform int u_band2Mod1Channel;
uniform int u_band2Mod1Curve;
uniform float u_band2Mod1Freq;
uniform int u_band2Mod1PhaseBase;
uniform float u_band2Mod1PhaseOffset;
uniform int u_band2Mod2Type;
uniform int u_band2Mod2Channel;
uniform int u_band2Mod2Curve;
uniform float u_band2Mod2Freq;
uniform int u_band2Mod2PhaseBase;
uniform float u_band2Mod2PhaseOffset;

uniform float u_band3Level;
uniform float u_band3SelectionMin;
uniform float u_band3SelectionMax;
uniform int u_band3SelectionChannel;
uniform float u_band3TintMix;
uniform int u_band3TintVaryBrightness;
uniform vec3 u_band3TintColor;
uniform int u_band3Mod1Type;
uniform int u_band3Mod1Channel;
uniform int u_band3Mod1Curve;
uniform float u_band3Mod1Freq;
uniform int u_band3Mod1PhaseBase;
uniform float u_band3Mod1PhaseOffset;
uniform int u_band3Mod2Type;
uniform int u_band3Mod2Channel;
uniform int u_band3Mod2Curve;
uniform float u_band3Mod2Freq;
uniform int u_band3Mod2PhaseBase;
uniform float u_band3Mod2PhaseOffset;

uniform float u_band4Level;
uniform float u_band4SelectionMin;
uniform float u_band4SelectionMax;
uniform int u_band4SelectionChannel;
uniform float u_band4TintMix;
uniform int u_band4TintVaryBrightness;
uniform vec3 u_band4TintColor;
uniform int u_band4Mod1Type;
uniform int u_band4Mod1Channel;
uniform int u_band4Mod1Curve;
uniform float u_band4Mod1Freq;
uniform int u_band4Mod1PhaseBase;
uniform float u_band4Mod1PhaseOffset;
uniform int u_band4Mod2Type;
uniform int u_band4Mod2Channel;
uniform int u_band4Mod2Curve;
uniform float u_band4Mod2Freq;
uniform int u_band4Mod2PhaseBase;
uniform float u_band4Mod2PhaseOffset;

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

vec3 mod289(vec3 x) {
    return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec4 mod289(vec4 x) {
    return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec4 permute(vec4 x) {
    return mod289(((x*34.0)+1.0)*x);
}

vec4 taylorInvSqrt(vec4 r)
{
    return 1.79284291400159 - 0.85373472095314 * r;
}

float snoise(vec3 v)
{
    const vec2  C = vec2(1.0/6.0, 1.0/3.0) ;
    const vec4  D = vec4(0.0, 0.5, 1.0, 2.0);
    
    // First corner
    vec3 i  = floor(v + dot(v, C.yyy) );
    vec3 x0 =   v - i + dot(i, C.xxx) ;
    
    // Other corners
    vec3 g = step(x0.yzx, x0.xyz);
    vec3 l = 1.0 - g;
    vec3 i1 = min( g.xyz, l.zxy );
    vec3 i2 = max( g.xyz, l.zxy );
    
    //   x0 = x0 - 0.0 + 0.0 * C.xxx;
    //   x1 = x0 - i1  + 1.0 * C.xxx;
    //   x2 = x0 - i2  + 2.0 * C.xxx;
    //   x3 = x0 - 1.0 + 3.0 * C.xxx;
    vec3 x1 = x0 - i1 + C.xxx;
    vec3 x2 = x0 - i2 + C.yyy; // 2.0*C.x = 1/3 = C.y
    vec3 x3 = x0 - D.yyy;      // -1.0+3.0*C.x = -0.5 = -D.y
    
    // Permutations
    i = mod289(i);
    vec4 p = permute( permute( permute(
                                       i.z + vec4(0.0, i1.z, i2.z, 1.0 ))
                              + i.y + vec4(0.0, i1.y, i2.y, 1.0 ))
                     + i.x + vec4(0.0, i1.x, i2.x, 1.0 ));
    
    // Gradients: 7x7 points over a square, mapped onto an octahedron.
    // The ring size 17*17 = 289 is close to a multiple of 49 (49*6 = 294)
    float n_ = 0.142857142857; // 1.0/7.0
    vec3  ns = n_ * D.wyz - D.xzx;
    
    vec4 j = p - 49.0 * floor(p * ns.z * ns.z);  //  mod(p,7*7)
    
    vec4 x_ = floor(j * ns.z);
    vec4 y_ = floor(j - 7.0 * x_ );    // mod(j,N)
    
    vec4 x = x_ *ns.x + ns.yyyy;
    vec4 y = y_ *ns.x + ns.yyyy;
    vec4 h = 1.0 - abs(x) - abs(y);
    
    vec4 b0 = vec4( x.xy, y.xy );
    vec4 b1 = vec4( x.zw, y.zw );
    
    //vec4 s0 = vec4(lessThan(b0,0.0))*2.0 - 1.0;
    //vec4 s1 = vec4(lessThan(b1,0.0))*2.0 - 1.0;
    vec4 s0 = floor(b0)*2.0 + 1.0;
    vec4 s1 = floor(b1)*2.0 + 1.0;
    vec4 sh = -step(h, vec4(0.0));
    
    vec4 a0 = b0.xzyw + s0.xzyw*sh.xxyy ;
    vec4 a1 = b1.xzyw + s1.xzyw*sh.zzww ;
    
    vec3 p0 = vec3(a0.xy,h.x);
    vec3 p1 = vec3(a0.zw,h.y);
    vec3 p2 = vec3(a1.xy,h.z);
    vec3 p3 = vec3(a1.zw,h.w);
    
    //Normalise gradients
    vec4 norm = taylorInvSqrt(vec4(dot(p0,p0), dot(p1,p1), dot(p2, p2), dot(p3,p3)));
    p0 *= norm.x;
    p1 *= norm.y;
    p2 *= norm.z;
    p3 *= norm.w;
    
    // Mix final noise value
    vec4 m = max(0.6 - vec4(dot(x0,x0), dot(x1,x1), dot(x2,x2), dot(x3,x3)), 0.0);
    m = m * m;
    return 42.0 * dot( m*m, vec4( dot(p0,x0), dot(p1,x1), 
                                 dot(p2,x2), dot(p3,x3) ) );
}

// amp mult 0.5 (unnormalised)   [0.5, 0.25, 0.125, 0.0625];
// amp mult 0.5     [ 0.533, 0.267, 0.133, 0.067 ]
// amp mult 0.6666   [ 0.415, 0.277, 0.185, 0.123 ];
// amp mult 0.75   [ 0.366, 0.274, 0.206, 0.154 ];
// amp mult 0.85   [ 0.314, 0.267, 0.227, 0.193 ];
// amp mult 1   [ 0.25, 0.25, 0.25, 0.25 ];
// amp mult 1.25 = [ 0.173, 0.217, 0.271, 0.339 ];
// amp mult 1.333 = [ 0.154, 0.206, 0.274, 0.366 ];
// amp mult 1.5 = [ 0.123, 0.185, 0.277, 0.415 ];
// amp mult 2 = [ 0.067, 0.133, 0.267, 0.533 ];

float pnoise(vec3 v) // amp mult 0.5, normalised
{
    float result = (snoise(v) * 0.533)
    + (snoise(vec3(v.x * 2.0, v.y * 2.0, v.z * 2.0)) * 0.267)
    + (snoise(vec3(v.x * 4.0, v.y * 4.0, v.z * 4.0)) * 0.133)
    + (snoise(vec3(v.x * 8.0, v.y * 8.0, v.z * 8.0)) * 0.067);
    return result;
}

float FadeCurveLookup (float phase, int band) {
    float outVal, lookup;
    lookup = phase * 255.0;
    if (band == 0) {
        // Band 1
        outVal = texture2DRect(u_curveSampler, vec2(lookup + 512.0, 0.0)).r;
    } else if (band == 1) {
        // Band 2
        outVal = texture2DRect(u_curveSampler, vec2(lookup + 512.0, 0.0)).g;
    } else if (band == 2) {
        // Band 3
        outVal = texture2DRect(u_curveSampler, vec2(lookup + 512.0, 0.0)).b;
    } else if (band == 3) {
        // Band 4
        outVal = texture2DRect(u_curveSampler, vec2(lookup + 512.0, 0.0)).a;
    } else {
        outVal = 0;
    };
    return outVal;
}

float CurveLookup (float phase, int modCurve) {
    float outVal, lookup, outVal1, outVal2;
    //float hold1, hold2, floorLookup, fractLookup;
    // apply mod
    if (modCurve == 0) {
        // TXCOLORIZEMODCURVE_CURVEA,
        lookup = phase * 255.0;
        outVal1 = texture2DRect(u_curveSampler, vec2(lookup, 0.0)).r;
        outVal2 = texture2DRect(u_curveSampler, vec2(lookup + 256.0, 0.0)).r;
        outVal = mix(outVal1, outVal2, u_curveAMorph);
    } else if (modCurve == 1) {
        // TXCOLORIZEMODCURVE_CURVEB,
        lookup = phase * 255.0;
        outVal1 = texture2DRect(u_curveSampler, vec2(lookup, 0.0)).g;
        outVal2 = texture2DRect(u_curveSampler, vec2(lookup + 256.0, 0.0)).g;
        outVal = mix(outVal1, outVal2, u_curveBMorph);
    } else if (modCurve == 2) {
        // TXCOLORIZEMODCURVE_CURVEC,
        lookup = phase * 255.0;
        outVal1 = texture2DRect(u_curveSampler, vec2(lookup, 0.0)).b;
        outVal2 = texture2DRect(u_curveSampler, vec2(lookup + 256.0, 0.0)).b;
        outVal = mix(outVal1, outVal2, u_curveCMorph);
    } else if (modCurve == 3) {
        // TXCOLORIZEMODCURVE_CURVED,
        lookup = phase * 255.0;
        outVal1 = texture2DRect(u_curveSampler, vec2(lookup, 0.0)).a;
        outVal2 = texture2DRect(u_curveSampler, vec2(lookup + 256.0, 0.0)).a;
        outVal = mix(outVal1, outVal2, u_curveDMorph);
    } else if (modCurve == 4) {
        // TXCOLORIZEMODCURVE_RAMPUP,
        outVal = phase;
    } else if (modCurve == 5) {
        // TXCOLORIZEMODCURVE_RAMPDOWN,
        outVal = 1 - phase;
    } else if (modCurve == 6) {
        // TXCOLORIZEMODCURVE_RAMPUPDOWN,
        if (phase > 0.5) {
            outVal = 1 - (2 * (phase - 0.5));
        } else {
            outVal = 2 * phase;
        };
        // NB SHADER SLOWS DOWN MASSIVELY IF NEXT OPTIONS ARE ADDED
        
//    } else if (modCurve == 7) {
//        // TXCOLORIZEMODCURVE_RAMPDOWNUP,
//        if (phase > 0.5) {
//            outVal = 2 * (phase - 0.5);
//        } else {
//            outVal = 1 - (2 * phase);
//        };
//    } else if (modCurve == 8) {
//        // TXCOLORIZEMODCURVE_FLAT_0,
//        outVal = 0;
//    } else if (modCurve == 9) {
//        // TXCOLORIZEMODCURVE_FLAT_0_5,
//        outVal = 0.5;
//    } else if (modCurve == 10) {
//        // TXCOLORIZEMODCURVE_FLAT_1,
//        outVal = 1;
    };
    return outVal;
}

vec3 ApplyMod(vec3 inColor,  int modType, int modChannel, int modCurve, float modFreq, float modPhaseBaseVal, float modPhaseOffset)
{
    vec3 holdColor;
    vec3 outColor;
    float channelVal;
    float modVal;
    float phase;
    //  convert HSLToRGB if needed & select channel
    if (modChannel == 0) {
        // TXCOLORRGBHSLCHANNEL_RED,
        holdColor = inColor;
        channelVal = holdColor.r;
    } else if (modChannel == 1) {
        // TXCOLORRGBHSLCHANNEL_GREEN,
        holdColor = inColor;
        channelVal = holdColor.g;
    } else if (modChannel == 2) {
        // TXCOLORRGBHSLCHANNEL_BLUE,
        holdColor = inColor;
        channelVal = holdColor.b;
    } else if (modChannel == 3) {
        // TXCOLORRGBHSLCHANNEL_HUE,
        holdColor = RGBToHSL(inColor);
        channelVal = holdColor.r;
    } else if (modChannel == 4) {
        // TXCOLORRGBHSLCHANNEL_SATURATION,
        holdColor = RGBToHSL(inColor);
        channelVal = holdColor.g;
    } else if (modChannel == 5) {
        // TXCOLORRGBHSLCHANNEL_LUMINOSITY,
        holdColor = RGBToHSL(inColor);
        channelVal = holdColor.b;
    };
    // get phase if needed
    if (modType > 1) {
        phase = fract((modPhaseBaseVal * modFreq) + modPhaseOffset);
    };
    // apply mod
    if (modType == 1) {
        // TXCOLORIZEMODTYPE_INVERT,
        modVal = 1 - channelVal;
    } else if (modType == 2) {
        // TXCOLORIZEMODTYPE_REPLACE,
        modVal = CurveLookup (phase, modCurve);
    } else if (modType == 3) {
        // TXCOLORIZEMODTYPE_ADD,
        modVal = channelVal + CurveLookup (phase, modCurve);
    } else if (modType == 4) {
        // TXCOLORIZEMODTYPE_SUBTRACT,
        modVal = channelVal - CurveLookup (phase, modCurve);
    } else if (modType == 5) {
        // TXCOLORIZEMODTYPE_MULTIPLY,
        modVal = channelVal * CurveLookup (phase, modCurve);
    } else if (modType == 6) {
        // TXCOLORIZEMODTYPE_DIVIDE,
        modVal = channelVal / max(0.001, CurveLookup (phase, modCurve)); // prevent blowup
    };
    // merge channel & convert HSLToRGB if needed
    if (modChannel == 0) {
        // TXCOLORRGBHSLCHANNEL_RED,
        outColor = vec3(modVal, holdColor.g, holdColor.b);
    } else if (modChannel == 1) {
        // TXCOLORRGBHSLCHANNEL_GREEN,
        outColor = vec3(holdColor.r, modVal, holdColor.b);
    } else if (modChannel == 2) {
        // TXCOLORRGBHSLCHANNEL_BLUE,
        outColor = vec3(holdColor.r, holdColor.g, modVal);
    } else if (modChannel == 3) {
        // TXCOLORRGBHSLCHANNEL_HUE,
        //holdColor.r = modVal;
        holdColor.r = fract(modVal + 1.0);  // wrap hue rotatation
        outColor = HSLToRGB(holdColor);
    } else if (modChannel == 4) {
        // TXCOLORRGBHSLCHANNEL_SATURATION,
        holdColor.g = modVal;
        outColor = HSLToRGB(holdColor);
    } else if (modChannel == 5) {
        // TXCOLORRGBHSLCHANNEL_LUMINOSITY,
        holdColor.b = modVal;
        outColor = HSLToRGB(holdColor);
    };
    return outColor;
}

vec3 applyBand(int bandIndex, vec3 inColor, float selectionMin, float selectionMax, int selectionChannel, float tintMix, int tintVaryBrightness, vec3 tintColor, int mod1Type, int mod1Channel, int mod1Curve, float mod1Freq, int mod1PhaseBase, float mod1PhaseOffset, int mod2Type, int mod2Channel, int mod2Curve, float mod2Freq, int mod2PhaseBase, float mod2PhaseOffset)
{
    vec3 outColor;
    vec3 tintColorVary;
    vec3 withTintColor;
    vec3 mod1Color;
    vec3 mod2Color;
    float channelVal;
    float phaseBaseVal, fadeVal;
    
    if (selectionChannel == 0) {
        //    TXCOLORRGBHSLCHANNEL_RED,
        channelVal = inColor.r;
    } else if (selectionChannel == 1) {
        //    TXCOLORRGBHSLCHANNEL_GREEN,
        channelVal = inColor.g;
    } else if (selectionChannel == 2) {
        //    TXCOLORRGBHSLCHANNEL_BLUE,
        channelVal = inColor.b;
    } else if (selectionChannel == 3) {
        //    TXCOLORRGBHSLCHANNEL_HUE,
        channelVal = RGBToHSL(inColor).r;
    } else if (selectionChannel == 4) {
        //    TXCOLORRGBHSLCHANNEL_SATURATION,
        channelVal = RGBToHSL(inColor).g;
    } else if (selectionChannel == 5) {
        //    TXCOLORRGBHSLCHANNEL_LUMINOSITY,
        channelVal = RGBToHSL(inColor).b;
        //channelVal = 0.3333 * (inColor.r + inColor.g + inColor.b); // testing with average
    };
    // if selected
    if ((channelVal >= selectionMin) && (channelVal <= selectionMax)) {
        // apply tint
        if (tintMix > 0.0) {
            if (tintVaryBrightness == 1) {
                tintColorVary = tintColor * (inColor.r + inColor.g + inColor.b) * 0.33333;
            } else {
                tintColorVary = tintColor;
            }
            withTintColor = mix(inColor, tintColorVary, tintMix);
        } else {
            withTintColor = inColor;
        };
        // apply mod1
        if (mod1Type > 0) {
            if (mod1PhaseBase == 0) {
                // Position within band normalised
                phaseBaseVal = abs(channelVal - selectionMin) / max(0.001, abs(selectionMax - selectionMin));
            } else if (mod1PhaseBase == 1) {
                // Position within band
                phaseBaseVal = channelVal;
            } else if (mod1PhaseBase == 2) {
                // perlin noise
                phaseBaseVal = pnoise(vec3((v_texCoord0.x / u_texdim0.x) * mod1Freq, (v_texCoord0.y / u_texdim0.y) * mod1Freq, mod1PhaseOffset * 10));
//            } else if (mod1PhaseBase == 3) {
            } else {
                // 0 phase
                phaseBaseVal = 0;
//            } else if (mod1PhaseBase == 4) {
//                // ImagePosX
//                phaseBaseVal = v_texCoord0.x / u_texdim0.x;
//            } else if (mod1PhaseBase == 5) {
//                // ImagePosY
//                phaseBaseVal = v_texCoord0.y / u_texdim0.y;
//            } else if (mod1PhaseBase == 6) {
//                // ImagePosX+Y
//                phaseBaseVal = 0.5 * ((v_texCoord0.x / u_texdim0.x) + (v_texCoord0.y / u_texdim0.y));
//            } else if (mod1PhaseBase == 7) {
//                // ImagePosX-Y
//                phaseBaseVal = 0.5 * ((v_texCoord0.x / u_texdim0.x) + (1 - (v_texCoord0.y / u_texdim0.y)));
            };
            mod1Color = ApplyMod(withTintColor, mod1Type, mod1Channel, mod1Curve, mod1Freq, phaseBaseVal, mod1PhaseOffset);
        } else {
            mod1Color = withTintColor;
        };
        // apply mod2
        if (mod2Type > 0) {
            if (mod2PhaseBase == 0) {
                // Position within band normalised
                phaseBaseVal = abs(channelVal - selectionMin) / max(0.001, abs(selectionMax - selectionMin));
            } else if (mod2PhaseBase == 1) {
                // Position within band
                phaseBaseVal = channelVal;
            } else if (mod2PhaseBase == 2) {
                // perlin noise
                phaseBaseVal = pnoise(vec3((v_texCoord0.x / u_texdim0.x) * mod2Freq, (v_texCoord0.y / u_texdim0.y) * mod2Freq, mod2PhaseOffset * 10));
//            } else if (mod2PhaseBase == 3) {
            } else {
                // phase 0
                phaseBaseVal = 0;
//            } else if (mod2PhaseBase == 4) {
//                // ImagePosX
//                phaseBaseVal = v_texCoord0.x / u_texdim0.x;
//            } else if (mod2PhaseBase == 5) {
//                // ImagePosY
//                phaseBaseVal = v_texCoord0.y / u_texdim0.y;
//            } else if (mod2PhaseBase == 6) {
//                // ImagePosX+Y
//                phaseBaseVal = 0.5 * ((v_texCoord0.x / u_texdim0.x) + (v_texCoord0.y / u_texdim0.y));
//            } else if (mod2PhaseBase == 7) {
//                // ImagePosX-Y
//                phaseBaseVal = 0.5 * ((v_texCoord0.x / u_texdim0.x) + (1 - (v_texCoord0.y / u_texdim0.y)));
            };
            outColor = ApplyMod(mod1Color, mod2Type, mod2Channel, mod2Curve, mod2Freq, phaseBaseVal, mod2PhaseOffset);
        } else {
            outColor = mod1Color;
        };
        // apply fade
        // Position within band normalised
        phaseBaseVal = abs(channelVal - selectionMin) / max(0.001, abs(selectionMax - selectionMin));
        fadeVal = FadeCurveLookup(phaseBaseVal, bandIndex);
        outColor = outColor * fadeVal;
    } else {
        outColor = vec3(0.0, 0.0, 0.0);
    };
    return outColor;
}

void main()
{
    vec4 tex0;
    vec3 startColor;
    vec3 band1Color;
    vec3 band2Color;
    vec3 band3Color;
    vec3 band4Color;
    vec3 mixColor;
    vec3 color0;
    vec3 color1;
    vec3 blendColor;
    vec3 outColor;
    
    tex0 = texture2DRect(u_texture0Sampler, v_texCoord0.st);
    startColor = tex0.rgb;
    
    mixColor = vec3(0.0, 0.0, 0.0);
    if (u_band1Level > 0.0) {
        band1Color = u_band1Level * applyBand(0, startColor, u_band1SelectionMin, u_band1SelectionMax, u_band1SelectionChannel, u_band1TintMix, u_band1TintVaryBrightness, u_band1TintColor, u_band1Mod1Type, u_band1Mod1Channel, u_band1Mod1Curve, u_band1Mod1Freq, u_band1Mod1PhaseBase, u_band1Mod1PhaseOffset, u_band1Mod2Type, u_band1Mod2Channel, u_band1Mod2Curve, u_band1Mod2Freq, u_band1Mod2PhaseBase, u_band1Mod2PhaseOffset);
        mixColor = mixColor + band1Color;
    };
    if (u_band2Level > 0.0) {
        band2Color = u_band2Level * applyBand(1, startColor, u_band2SelectionMin, u_band2SelectionMax, u_band2SelectionChannel, u_band2TintMix, u_band2TintVaryBrightness, u_band2TintColor, u_band2Mod1Type, u_band2Mod1Channel, u_band2Mod1Curve, u_band2Mod1Freq, u_band2Mod1PhaseBase, u_band2Mod1PhaseOffset, u_band2Mod2Type, u_band2Mod2Channel, u_band2Mod2Curve, u_band2Mod2Freq, u_band2Mod2PhaseBase, u_band2Mod2PhaseOffset);
        mixColor = mixColor + band2Color;
    };
    if (u_band3Level > 0.0) {
        band3Color = u_band3Level * applyBand(2, startColor, u_band3SelectionMin, u_band3SelectionMax, u_band3SelectionChannel, u_band3TintMix, u_band3TintVaryBrightness, u_band3TintColor, u_band3Mod1Type, u_band3Mod1Channel, u_band3Mod1Curve, u_band3Mod1Freq, u_band3Mod1PhaseBase, u_band3Mod1PhaseOffset, u_band3Mod2Type, u_band3Mod2Channel, u_band3Mod2Curve, u_band3Mod2Freq, u_band3Mod2PhaseBase, u_band3Mod2PhaseOffset);
        mixColor = mixColor + band3Color;
    };
    if (u_band4Level > 0.0) {
        band4Color = u_band4Level * applyBand(3, startColor, u_band4SelectionMin, u_band4SelectionMax, u_band4SelectionChannel, u_band4TintMix, u_band4TintVaryBrightness, u_band4TintColor, u_band4Mod1Type, u_band4Mod1Channel, u_band4Mod1Curve, u_band4Mod1Freq, u_band4Mod1PhaseBase, u_band4Mod1PhaseOffset, u_band4Mod2Type, u_band4Mod2Channel, u_band4Mod2Curve, u_band4Mod2Freq, u_band4Mod2PhaseBase, u_band4Mod2PhaseOffset);
        mixColor = mixColor + band4Color;
    };
    
	if (u_blendReverse == 0) {color0 = startColor; color1 = mixColor;}
    else {color0 = mixColor; color1 = startColor;}
    
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



