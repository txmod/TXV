/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXShaderFX2TexBase.h"

class TXLumaKey  :  public TXShaderFX2TexBase
{
public:    
	// constructor
	TXLumaKey();
    
    // destructor
    ~TXLumaKey();
    
    // overide these methods in FX modules:
	void addExtraParameters();
	void loadRenderShader();
    bool setExtraUniforms(int sourceImageWidth, int sourceImageHeight, int sourceImage2Width, int sourceImage2Height);
    
public:
    // Extra methods & parameters:
    
    ofPtr<TXModParamFloat> luma;
    ofPtr<TXModParamFloat> tolerance;
    ofPtr<TXModParamFloat> fade;
    ofPtr<TXModParamBool> showSourceImage2;
    ofPtr<TXModParamBool> invert;
    ofPtr<TXModParamBool> maskMode;

};

