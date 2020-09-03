/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXShaderFXBase.h"

enum TXKERNELTYPE {TXKERNELTYPE_BLUR1, //
    TXKERNELTYPE_BLUR2, //
    TXKERNELTYPE_FINDEDGE1, //
    TXKERNELTYPE_FINDEDGE2, //
    TXKERNELTYPE_FINDVERTICALEDGE1, //
    TXKERNELTYPE_FINDVERTICALEDGE2, //
    TXKERNELTYPE_FINDHORIZONTALEDGE1, //
    TXKERNELTYPE_FINDHORIZONTALEDGE2, //
    TXKERNELTYPE_SHARPEN1, //
    TXKERNELTYPE_SHARPEN2, // - USES 5 IN BETWEEN OTHERS
    TXKERNELTYPE_SHARPEN3, //
    TXKERNELTYPE_EMBOSS1, // {-2, -2, 0, -2, 6, 0, 0, 0, 0}
    TXKERNELTYPE_EMBOSS2, // {-2, -1, 0, -1, 1, 1, 0, 1, 2}
    TXKERNELTYPE_CUSTOMISE, // USE K0-K8
    TXKERNELTYPE_TOTAL,
};
class TXConvolution  :  public TXShaderFXBase
{
public:
	// constructor
	TXConvolution();
    
    // destructor
    ~TXConvolution();
    
    // overide these methods in FX modules:
    bool setExtraUniforms(int sourceImageWidth, int sourceImageHeight);
	void addExtraParameters();
	void addExtraListeners();
	void loadRenderShader();
    
public:
    // Extra parameters:
    
    ofPtr<TXModParamFloat> mix;
    ofPtr<TXModParamInt> kernelType;
    ofPtr<TXModParamFloat> bias;
    ofPtr<TXModParamFloat> kernel1;
    ofPtr<TXModParamFloat> kernel2;
    ofPtr<TXModParamFloat> kernel3;
    ofPtr<TXModParamFloat> kernel4;
    ofPtr<TXModParamFloat> kernel5;
    ofPtr<TXModParamFloat> kernel6;
    ofPtr<TXModParamFloat> kernel7;
    ofPtr<TXModParamFloat> kernel8;
    ofPtr<TXModParamFloat> kernel9;
};
