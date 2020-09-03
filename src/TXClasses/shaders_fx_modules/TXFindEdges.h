/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXShaderFXBase.h"

class TXFindEdges  :  public TXShaderFXBase
{
public:
    static const int numBlendModes = 27;
    
	// constructor
	TXFindEdges();
    
    // destructor
    ~TXFindEdges();

    // overide these methods in FX modules:
    bool setExtraUniforms(int sourceImageWidth, int sourceImageHeight);
	void addExtraParameters();
	void addExtraListeners();
	void loadRenderShader();

public:
    // Extra methods & parameters:

    void  showEdgeColorChanged(ofAbstractParameter & parameterArg );
    
    ofPtr<TXModParamBool> showEdgeColor; 
    ofPtr<TXModParamInt> blendMode;
    ofPtr<TXModParamFloat> blendMix;
    ofPtr<TXModParamBool> blendReverse;
    
};

 