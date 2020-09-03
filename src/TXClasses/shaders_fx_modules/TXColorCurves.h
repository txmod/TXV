/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXShaderFXBase.h"

//enum TXCOLORRGBCHANNELORDER {
//    TXCOLORRGBCHANNELORDER_RGB,
//    TXCOLORRGBCHANNELORDER_RBG,
//    TXCOLORRGBCHANNELORDER_GBR,
//    TXCOLORRGBCHANNELORDER_GRB,
//    TXCOLORRGBCHANNELORDER_BRG,
//    TXCOLORRGBCHANNELORDER_BGR,
//    TXCOLORRGBCHANNELORDER_TOTAL,
//};

//enum TXCOLORRGBHSLCHANNELMODE {
//    TXCOLORRGBHSLCHANNELMODE_RGB,
//    TXCOLORRGBHSLCHANNELMODE_RED,
//    TXCOLORRGBHSLCHANNELMODE_GREEN,
//    TXCOLORRGBHSLCHANNELMODE_BLUE,
//    TXCOLORRGBHSLCHANNELMODE_REDGREEN,
//    TXCOLORRGBHSLCHANNELMODE_REDBLUE,
//    TXCOLORRGBHSLCHANNELMODE_GREENBLUE,
//    TXCOLORRGBHSLCHANNELMODE_HSL,
//    TXCOLORRGBHSLCHANNELMODE_HUE,
//    TXCOLORRGBHSLCHANNELMODE_SATURATION,
//    TXCOLORRGBHSLCHANNELMODE_LUMINOSITY,
//    TXCOLORRGBHSLCHANNELMODE_HUESATURATION,
//    TXCOLORRGBHSLCHANNELMODE_HUELUMINOSITY,
//    TXCOLORRGBHSLCHANNELMODE_SATURATIONLUMINOSITY,
//    TXCOLORRGBHSLCHANNELMODE_TOTAL
//};

class TXColorCurves  :  public TXShaderFXBase
{
public:
    static const int numBlendModes = 27;

	// constructor
	TXColorCurves();
    
    // destructor
    ~TXColorCurves();
    
    // overide these methods in FX modules:
    bool setExtraUniforms(int sourceImageWidth, int sourceImageHeight);
	void addExtraParameters();
	void addExtraListeners();
	void loadRenderShader();
    
    void curvesImageSetup();
    void updateCurvesImagePixels();
    void updateCurvesHSLImagePixels();
    
    // listener methods
    void  redCurveChanged(ofAbstractParameter & parameterArg );
    void  greenCurveChanged(ofAbstractParameter & parameterArg );
    void  blueCurveChanged(ofAbstractParameter & parameterArg );
    void  hueCurveChanged(ofAbstractParameter & parameterArg );
    void  saturationCurveChanged(ofAbstractParameter & parameterArg );
    void  luminosityCurveChanged(ofAbstractParameter & parameterArg );

public:
    // Extra parameters:
    
    ofPtr<TXModParamInt> curvesMode;
    ofPtr<TXModParamFloat> curvesMix;
    ofPtr<TXModParamFloat> inputMin;
    ofPtr<TXModParamFloat> inputMax;
    ofPtr<TXModParamFloat> outputMin;
    ofPtr<TXModParamFloat> outputMax;
    TXParameterFloat256 redCurve1;
    TXParameterFloat256 redCurve2;
    ofPtr<TXModParamFloat> redCurveMorph;
    TXParameterFloat256 greenCurve1;
    TXParameterFloat256 greenCurve2;
    ofPtr<TXModParamFloat> greenCurveMorph;
    TXParameterFloat256 blueCurve1;
    TXParameterFloat256 blueCurve2;
    ofPtr<TXModParamFloat> blueCurveMorph;
    ofPtr<TXModParamBool> useRedCurveForBlue;
    ofPtr<TXModParamBool> useRedCurveForGreen;
    TXParameterFloat256 hueCurve1;
    TXParameterFloat256 hueCurve2;
    ofPtr<TXModParamFloat> hueCurveMorph;
    TXParameterFloat256 saturationCurve1;
    TXParameterFloat256 saturationCurve2;
    ofPtr<TXModParamFloat> saturationCurveMorph;
    TXParameterFloat256 luminosityCurve1;
    TXParameterFloat256 luminosityCurve2;
    ofPtr<TXModParamFloat> luminosityCurveMorph;
    
    ofPtr<TXModParamBool> posterize;
    ofPtr<TXModParamInt> posterizeSteps;
    ofPtr<TXModParamFloat> posterizeBias;
    ofPtr<TXModParamInt> channelReorder;
    ofPtr<TXModParamFloat> redMultiply;
    ofPtr<TXModParamFloat> greenMultiply;
    ofPtr<TXModParamFloat> blueMultiply;
    ofPtr<TXModParamInt> blendMode;
    ofPtr<TXModParamFloat> blendMix;
    ofPtr<TXModParamBool> blendReverse;
    
protected:
    ofImage curvesImage;
    bool curvesImageHasChanged;
    ofImage curvesHSLImage;
    bool curvesHSLImageHasChanged;
};

