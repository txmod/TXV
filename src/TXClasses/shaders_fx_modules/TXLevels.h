/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXShaderFXBase.h"

enum TXLEVELSMODE {
    TXLEVELSMODE_RGB,
    TXLEVELSMODE_RED,
    TXLEVELSMODE_GREEN,
    TXLEVELSMODE_BLUE,
    TXLEVELSMODE_REDGREEN,
    TXLEVELSMODE_REDBLUE,
    TXLEVELSMODE_GREENBLUE,
};

enum TXLEVELSCHANNELORDER {
    TXLEVELSCHANNELORDER_RGB,
    TXLEVELSCHANNELORDER_RBG,
    TXLEVELSCHANNELORDER_GBR,
    TXLEVELSCHANNELORDER_GRB,
    TXLEVELSCHANNELORDER_BRG,
    TXLEVELSCHANNELORDER_BGR,
};

class TXLevels  :  public TXShaderFXBase
{
public:
    // NOTE - change numLevelsModes when adding new LFO types:
    static const int numLevelsModes = 6;
    static const int numBlendModes = 27;
    static const int numChannelOrders = 6;

	// constructor
	TXLevels();
    
    // destructor
    ~TXLevels();
    
    // overide these methods in FX modules:
    bool setExtraUniforms(int sourceImageWidth, int sourceImageHeight);
	void addExtraParameters();
	void addExtraListeners();
	void loadRenderShader();
    
public:
    // Extra parameters:
     
    ofPtr<TXModParamInt> levelsMode;
    ofPtr<TXModParamFloat> levelsMix;
    ofPtr<TXModParamFloat> inputMin;
    ofPtr<TXModParamFloat> gamma;
    ofPtr<TXModParamFloat> inputMax;
    ofPtr<TXModParamFloat> outputMin;
    ofPtr<TXModParamFloat> outputMax;
    
    ofPtr<TXModParamBool> posterize;
    ofPtr<TXModParamInt> posterizeSteps;
    ofPtr<TXModParamFloat> posterizeBias;
    ofPtr<TXModParamInt> channelReorder;
    ofPtr<TXModParamFloat> redMultiply;
    ofPtr<TXModParamFloat> greenMultiply;
    ofPtr<TXModParamFloat> blueMultiply;
    ofPtr<TXModParamInt> blendMode;
    ofPtr<TXModParamFloat> blendMix;
    ofPtr<TXModParamBool> blendReverse;
};

