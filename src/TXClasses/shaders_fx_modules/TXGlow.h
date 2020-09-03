/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXShaderFXBase.h"

class TXGlow  :  public TXShaderFXBase
{
public:
	// constructor
	TXGlow();
    
    // destructor
    ~TXGlow();
    
    // overide these methods in FX modules:
    bool setExtraUniforms(int sourceImageWidth, int sourceImageHeight);
	void addExtraParameters();
	void addExtraListeners();
	void loadRenderShader();
    
public:
    // Extra parameters:
    
    ofPtr<TXModParamFloat> glow;
};
