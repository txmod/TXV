/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXShaderFXBase.h"

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

class TXColorize  :  public TXShaderFXBase
{
public:
    static const int numBlendModes = 27;
    static const int numPhaseBaseTypes = 4;

	// constructor
	TXColorize();
    
    // destructor
    ~TXColorize();
    
    // overide these methods in FX modules:
    bool setExtraUniforms(int sourceImageWidth, int sourceImageHeight);
	void addExtraParameters();
	void addExtraListeners();
	void loadRenderShader();
    
    void curvesImageSetup();
    void updateCurvesImagePixels();
    
    // listener methods
    void  curvesChanged(ofAbstractParameter & parameterArg);

public:
    /*
     Rules for Each Band:
     Selection rules - divide into bands using min-max selection range based on r/g/b/a/h/s/l Channel
     - min-max selection range for relevant Channel - if max<min, then select only outside the range
     - tint pixel
     - mod 1 & 2 applied     
     band1Mod1Type;  // off/ invert/replace with curveval/ add curveval/ subtr curveval/ mult by curveval/ divide by  curveval
     band1Mod1Curve;  // curve A/B/C/D/ Ramp Up/Down/Up-Down/  [not working: Ramp DownUp/ Flat 0/0.5/1]
     band1Mod1PhaseBase;  // lookup bandcurve MinMaxRangePos/ImagePosX/ImagePos/ImagePosX+Y/PerlinNoise/Phase0
     */
    
    // Extra parameters:
    
    ofPtr<TXModParamFloat> band1Level;
    ofPtr<TXModParamFloat> band1SelectionMin;
    ofPtr<TXModParamFloat> band1SelectionMax;
    ofPtr<TXModParamInt> band1SelectionChannel;
    ofPtr<TXModParamFloat> band1TintMix;
    ofPtr<TXModParamBool> band1TintVaryBrightness;
    ofPtr<TXModParamFloat> band1TintColorHue;
    ofPtr<TXModParamFloat> band1TintColorHueRotate;
    ofPtr<TXModParamFloat> band1TintColorSaturation;
    ofPtr<TXModParamFloat> band1TintColorBrightness;
    ofPtr<TXModParamBool> band1TintColorHSBAsRGB;
    ofPtr<TXModParamInt> band1Mod1Type;
    ofPtr<TXModParamInt> band1Mod1Channel;
    ofPtr<TXModParamInt> band1Mod1Curve;
    ofPtr<TXModParamFloat> band1Mod1Freq;
    ofPtr<TXModParamInt> band1Mod1PhaseBase;
    ofPtr<TXModParamFloat> band1Mod1PhaseOffset;
    ofPtr<TXModParamInt> band1Mod2Type;
    ofPtr<TXModParamInt> band1Mod2Channel;
    ofPtr<TXModParamInt> band1Mod2Curve;
    ofPtr<TXModParamFloat> band1Mod2Freq;
    ofPtr<TXModParamInt> band1Mod2PhaseBase;
    ofPtr<TXModParamFloat> band1Mod2PhaseOffset;
    
    ofPtr<TXModParamFloat> band2Level;
    ofPtr<TXModParamFloat> band2SelectionMin;
    ofPtr<TXModParamFloat> band2SelectionMax;
    ofPtr<TXModParamInt> band2SelectionChannel;
    ofPtr<TXModParamFloat> band2TintMix;
    ofPtr<TXModParamBool> band2TintVaryBrightness;
    ofPtr<TXModParamFloat> band2TintColorHue;
    ofPtr<TXModParamFloat> band2TintColorHueRotate;
    ofPtr<TXModParamFloat> band2TintColorSaturation;
    ofPtr<TXModParamFloat> band2TintColorBrightness;
    ofPtr<TXModParamBool> band2TintColorHSBAsRGB;
    ofPtr<TXModParamInt> band2Mod1Type;
    ofPtr<TXModParamInt> band2Mod1Channel;
    ofPtr<TXModParamInt> band2Mod1Curve;
    ofPtr<TXModParamFloat> band2Mod1Freq;
    ofPtr<TXModParamInt> band2Mod1PhaseBase;
    ofPtr<TXModParamFloat> band2Mod1PhaseOffset;
    ofPtr<TXModParamInt> band2Mod2Type;
    ofPtr<TXModParamInt> band2Mod2Channel;
    ofPtr<TXModParamInt> band2Mod2Curve;
    ofPtr<TXModParamFloat> band2Mod2Freq;
    ofPtr<TXModParamInt> band2Mod2PhaseBase;
    ofPtr<TXModParamFloat> band2Mod2PhaseOffset;
    
    ofPtr<TXModParamFloat> band3Level;
    ofPtr<TXModParamFloat> band3SelectionMin;
    ofPtr<TXModParamFloat> band3SelectionMax;
    ofPtr<TXModParamInt> band3SelectionChannel;
    ofPtr<TXModParamFloat> band3TintMix;
    ofPtr<TXModParamBool> band3TintVaryBrightness;
    ofPtr<TXModParamFloat> band3TintColorHue;
    ofPtr<TXModParamFloat> band3TintColorHueRotate;
    ofPtr<TXModParamFloat> band3TintColorSaturation;
    ofPtr<TXModParamFloat> band3TintColorBrightness;
    ofPtr<TXModParamBool> band3TintColorHSBAsRGB;
    ofPtr<TXModParamInt> band3Mod1Type;
    ofPtr<TXModParamInt> band3Mod1Channel;
    ofPtr<TXModParamInt> band3Mod1Curve;
    ofPtr<TXModParamFloat> band3Mod1Freq;
    ofPtr<TXModParamInt> band3Mod1PhaseBase;
    ofPtr<TXModParamFloat> band3Mod1PhaseOffset;
    ofPtr<TXModParamInt> band3Mod2Type;
    ofPtr<TXModParamInt> band3Mod2Channel;
    ofPtr<TXModParamInt> band3Mod2Curve;
    ofPtr<TXModParamFloat> band3Mod2Freq;
    ofPtr<TXModParamInt> band3Mod2PhaseBase;
    ofPtr<TXModParamFloat> band3Mod2PhaseOffset;
    
    ofPtr<TXModParamFloat> band4Level;
    ofPtr<TXModParamFloat> band4SelectionMin;
    ofPtr<TXModParamFloat> band4SelectionMax;
    ofPtr<TXModParamInt> band4SelectionChannel;
    ofPtr<TXModParamFloat> band4TintMix;
    ofPtr<TXModParamBool> band4TintVaryBrightness;
    ofPtr<TXModParamFloat> band4TintColorHue;
    ofPtr<TXModParamFloat> band4TintColorHueRotate;
    ofPtr<TXModParamFloat> band4TintColorSaturation;
    ofPtr<TXModParamFloat> band4TintColorBrightness;
    ofPtr<TXModParamBool> band4TintColorHSBAsRGB;
    ofPtr<TXModParamInt> band4Mod1Type;
    ofPtr<TXModParamInt> band4Mod1Channel;
    ofPtr<TXModParamInt> band4Mod1Curve;
    ofPtr<TXModParamFloat> band4Mod1Freq;
    ofPtr<TXModParamInt> band4Mod1PhaseBase;
    ofPtr<TXModParamFloat> band4Mod1PhaseOffset;
    ofPtr<TXModParamInt> band4Mod2Type;
    ofPtr<TXModParamInt> band4Mod2Channel;
    ofPtr<TXModParamInt> band4Mod2Curve;
    ofPtr<TXModParamFloat> band4Mod2Freq;
    ofPtr<TXModParamInt> band4Mod2PhaseBase;
    ofPtr<TXModParamFloat> band4Mod2PhaseOffset;
    
    TXParameterFloat256 curveA1;
    TXParameterFloat256 curveA2;
    ofPtr<TXModParamFloat> curveAMorph;
    TXParameterFloat256 curveB1;
    TXParameterFloat256 curveB2;
    ofPtr<TXModParamFloat> curveBMorph;
    TXParameterFloat256 curveC1;
    TXParameterFloat256 curveC2;
    ofPtr<TXModParamFloat> curveCMorph;
    TXParameterFloat256 curveD1;
    TXParameterFloat256 curveD2;
    ofPtr<TXModParamFloat> curveDMorph;
    TXParameterFloat256 band1FadeCurve;
    TXParameterFloat256 band2FadeCurve;
    TXParameterFloat256 band3FadeCurve;
    TXParameterFloat256 band4FadeCurve;
    
    ofPtr<TXModParamInt> blendMode;
    ofPtr<TXModParamFloat> blendMix;
    ofPtr<TXModParamBool> blendReverse;
    
protected:
    ofImage curvesImage;
    bool curvesImageHasChanged;
};

