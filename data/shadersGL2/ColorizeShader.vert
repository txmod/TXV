
#version 120

// Uniforms

// Varyings
varying vec2 v_texCoord0;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	v_texCoord0 = gl_MultiTexCoord0.xy; // pass the attribute along
}


/*
 Rules for Each Band:
 Selection rules - divide into bands using min-max selection range based on r/g/b/a or h/s/b/a Channel
 tint pixel
 FX1/2/3 - applied in sequence,
 - modify color using curve a/b/c/d
 - phase based on position in band min-max or x/y pixel position
 - min-max selection range for all relevant Channel - if max<min, then select only outside the range
 
 band1SelectionMin;
 band1SelectionMax;
 band1SelectionChannel;  // def: TXCOLORRGBHSLCHANNELMODE_RGB
 band1TintMix;
 band1TintColorHue;
 band1TintColorHueRotate;
 band1TintColorSaturation;
 band1TintColorBrightness;
 band1TintColorHSBAsRGB;
 band1Mod1Type;  // off/ invert/replace with curveval/ add curveval/ subtr curveval/ mult by curveval/ divide by  curveval
 band1Mod1Channel;  // def: TXCOLORRGBHSLCHANNELMODE_RGB
 band1Mod1Curve;  // curve A/B/C/D/ Ramp Up/Down/Up-Down/  [not working: Ramp DownUp/ Flat 0/0.5/1]
 band1Mod1Freq;
 band1Mod1PhaseBase;  // lookup bandcurve MinMaxRangePos/ImagePosX/ImagePos/ImagePosX+Y/PerlinNoise/Phase0
 band1Mod1PhaseOffset;
 band1Mod2Type;
 band1Mod2Channel;
 band1Mod2Curve;
 band1Mod2Freq;
 band1Mod2PhaseBase;
 band1Mod2PhaseOffset;
 */


/*
 //enum TXCOLORRGBHSLCHANNEL {
 //    TXCOLORRGBHSLCHANNEL_RED,
 //    TXCOLORRGBHSLCHANNEL_GREEN,
 //    TXCOLORRGBHSLCHANNEL_BLUE,
 //    TXCOLORRGBHSLCHANNEL_HUE,
 //    TXCOLORRGBHSLCHANNEL_SATURATION,
 //    TXCOLORRGBHSLCHANNEL_LUMINOSITY,
 //    TXCOLORRGBHSLCHANNEL_TOTAL
 //};
 
 enum TXCOLORIZEMODTYPE {
 TXCOLORIZEMODTYPE_NONE,
 TXCOLORIZEMODTYPE_INVERT,
 TXCOLORIZEMODTYPE_REPLACE,
 TXCOLORIZEMODTYPE_ADD,
 TXCOLORIZEMODTYPE_SUBTRACT,
 TXCOLORIZEMODTYPE_MULTIPLY,
 TXCOLORIZEMODTYPE_DIVIDE,
 TXCOLORIZEMODTYPE_TOTAL
 };
 
 enum TXCOLORIZEMODCURVE {
 TXCOLORIZEMODCURVE_CURVEA,
 TXCOLORIZEMODCURVE_CURVEB,
 TXCOLORIZEMODCURVE_CURVEC,
 TXCOLORIZEMODCURVE_CURVED,
 TXCOLORIZEMODCURVE_RAMPUP,
 TXCOLORIZEMODCURVE_RAMPDOWN,
 TXCOLORIZEMODCURVE_RAMPUPDOWN,
 TXCOLORIZEMODCURVE_RAMPDOWNUP,
 TXCOLORIZEMODCURVE_FLAT_0,
 TXCOLORIZEMODCURVE_FLAT_0_5,
 TXCOLORIZEMODCURVE_FLAT_1,
 TXCOLORIZEMODCURVE_TOTAL
 };
 
 // Uniforms
 uniform sampler2DRect u_texture0Sampler;
 uniform sampler2DRect u_curveSampler;
 
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
 
 uniform int u_blendMode;
 uniform float u_blendMix;
 uniform int u_blendReverse;
*/

