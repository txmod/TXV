/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXShaderFXBase.h"

class TXSoftThreshold  :  public TXShaderFXBase
{
public:
	// constructor
	TXSoftThreshold();
    
    // destructor
    ~TXSoftThreshold();
    
    // overide these methods in FX modules:
    bool setExtraUniforms(int sourceImageWidth, int sourceImageHeight);
	void addExtraParameters();
	void addExtraListeners();
	void loadRenderShader();
    
public:
    // Extra parameters:
    
    ofPtr<TXModParamFloat> softEdge;
    ofPtr<TXModParamFloat> threshold;
    ofPtr<TXModParamBool> invert;
    ofPtr<TXModParamBool> maskMode;
};
