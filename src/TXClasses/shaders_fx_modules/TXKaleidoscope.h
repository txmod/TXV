/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXShaderFXBase.h"

class TXKaleidoscope  :  public TXShaderFXBase
{
public:
	// constructor
	TXKaleidoscope();
    
    // destructor
    ~TXKaleidoscope();
    
    // overide these methods in FX modules:
    bool setExtraUniforms(int sourceImageWidth, int sourceImageHeight);
	void addExtraParameters();
	void addExtraListeners();
	void loadRenderShader();
    
public:
    // Extra parameters:
        
    ofPtr<TXModParamFloat> numSections;
    ofPtr<TXModParamBool> quantizeSections;
    ofPtr<TXModParamFloat> rotationOffset;
};
