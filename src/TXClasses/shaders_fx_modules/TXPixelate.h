/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXShaderFXBase.h"

class TXPixelate  :  public TXShaderFXBase
{
public:
	// constructor
	TXPixelate();
    
    // destructor
    ~TXPixelate();
    
    // overide these methods in FX modules:
    bool setExtraUniforms(int sourceImageWidth, int sourceImageHeight);
	void addExtraParameters();
	void addExtraListeners();
	void loadRenderShader();
    
public:
    // Extra parameters:
     
    ofPtr<TXModParamFloat> pixelWidth;
    ofPtr<TXModParamFloat> pixelHeight;
    ofParameter<bool> usePixelWidthForHeight;
    ofPtr<TXModParamFloat> mix;
};
