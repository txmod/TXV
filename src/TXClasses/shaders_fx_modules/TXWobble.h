/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXShaderFXBase.h"

class TXWobble  :  public TXShaderFXBase
{
public:
	// constructor
	TXWobble();
    
    // destructor
    ~TXWobble();
    
    // overide these methods in FX modules:
    bool setExtraUniforms(int sourceImageWidth, int sourceImageHeight);
	void addExtraParameters();
	void addExtraListeners();
	void loadRenderShader();
    
public:
    // Extra parameters:
    
    ofPtr<TXModParamFloat> phase;
    ofPtr<TXModParamFloat> freqX;
    ofPtr<TXModParamFloat> freqY;
    ofPtr<TXModParamFloat> ampX;
    ofPtr<TXModParamFloat> ampY;
};
