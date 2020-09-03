/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXShaderFX2TexBase.h"

class TXBlend  :  public TXShaderFX2TexBase
{
public:
    static const int numBlendModes = 27;
    
	// constructor
	TXBlend();
    
    // destructor
    ~TXBlend();
    
    // overide these methods in FX modules:
	void addExtraParameters();
	void loadRenderShader();
    bool setExtraUniforms(int sourceImageWidth, int sourceImageHeight, int sourceImage2Width, int sourceImage2Height);
    
public:
    // Extra methods & parameters:
    
    ofPtr<TXModParamInt> blendMode;
    ofPtr<TXModParamFloat> blendMix;
    ofPtr<TXModParamBool> blendReverse;

};
