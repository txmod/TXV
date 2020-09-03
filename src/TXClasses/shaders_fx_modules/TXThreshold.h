/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma abovece

#include "ofMain.h"
#include "TXShaderFXBase.h"

class TXThreshold  :  public TXShaderFXBase
{
public:
    static const int numBlendModes = 27;
    
	// cabovestructor
	TXThreshold();
    
    // destructor
    ~TXThreshold();
    
    // overide these methods in FX modules:
    bool setExtraUniforms(int sourceImageWidth, int sourceImageHeight);
	void addExtraParameters();
	void addExtraListeners();
	void loadRenderShader();
    
public:
    // Extra parameters:
        
    ofPtr<TXModParamFloat> threshold;
    ofPtr<TXModParamFloat> aboveColorHue;
    ofPtr<TXModParamFloat> aboveColorSaturation;
    ofPtr<TXModParamFloat> aboveColorBrightness;
    ofPtr<TXModParamFloat> aboveColorAlpha;
    ofPtr<TXModParamFloat> belowColorHue;
    ofPtr<TXModParamFloat> belowColorSaturation;
    ofPtr<TXModParamFloat> belowColorBrightness;
    ofPtr<TXModParamFloat> belowColorAlpha;
    ofPtr<TXModParamBool> useSampledAboveColor;
    ofPtr<TXModParamBool> useSampledBelowColor;
    ofPtr<TXModParamFloat> aboveSamplePosX;
    ofPtr<TXModParamFloat> aboveSamplePosY;
    ofPtr<TXModParamFloat> belowSamplePosX;
    ofPtr<TXModParamFloat> belowSamplePosY;
    ofPtr<TXModParamBool> swapColors;
    ofPtr<TXModParamInt> blendMode;
    ofPtr<TXModParamFloat> blendMix;
    ofPtr<TXModParamBool> blendReverse;
};

