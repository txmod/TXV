/*
 *  Copyright 2014 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXShaderFXBase.h"


class TXColorControls  :  public TXShaderFXBase
{
public:

	// constructor
	TXColorControls();
    
    // destructor
    ~TXColorControls();
    
    // overide these methods in FX modules:
    bool setExtraUniforms(int sourceImageWidth, int sourceImageHeight);
	void addExtraParameters();
	void addExtraListeners();
	void loadRenderShader();
    
public:
    // Extra parameters:
    
    ofPtr<TXModParamFloat> brightness;
    ofPtr<TXModParamFloat> contrast;
    ofPtr<TXModParamFloat> contrastMidPoint;
    ofPtr<TXModParamFloat> saturation;
    ofPtr<TXModParamBool> useHueshift; // bool
    ofPtr<TXModParamFloat> hueshift;
    ofPtr<TXModParamBool> invert; // bool
    ofPtr<TXModParamFloat> fxMix;
};

