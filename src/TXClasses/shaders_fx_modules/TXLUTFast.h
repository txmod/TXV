/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

// TXLUTFast- NOTE this LUT module uses a fragment shader

#pragma once

#include "ofMain.h"
#include "TXShaderFXBase.h"

class TXLUTFast  :  public TXShaderFXBase
{
public:
    static const int numBlendModes = 27;
    
	// constructor
	TXLUTFast();
    
    // destructor
    ~TXLUTFast();
    
    // overide these methods in FX modules:
	void addExtraParameters();
	void addExtraListeners();
    void extraSetupAction();
	void loadRenderShader();
    bool setExtraUniforms(int sourceImageWidth, int sourceImageHeight);
//	void updatePixels();
    
public:
    // Extra methods & parameters:
    void cubeAssetSlotChanged(string slotNameArg);
    void loadLUT();
    bool loadLUT(string lutFile);
    bool loadLUT(ofBuffer &buffer);
    
    ofPtr<TXModParamInt> blendMode;
    ofPtr<TXModParamFloat> blendMix;
    ofPtr<TXModParamBool> blendReverse;

    ofFbo LUTImage;
    bool LUTloaded;
    
};
