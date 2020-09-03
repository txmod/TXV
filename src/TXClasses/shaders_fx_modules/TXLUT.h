/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

// NOTE: this module is VERY slow - too slow for real-time video

#pragma once

#include "ofMain.h"
#include "TXPixelFXBase.h"

class TXLUT  :  public TXPixelFXBase
{
public:
	// constructor
	TXLUT();
    
    // destructor
    ~TXLUT();
    
    // overide these methods in FX modules:
	void addExtraParameters();
	void addExtraListeners();
    void extraSetupAction();
	void updatePixels();
    
public:
    // Extra methods & parameters:
    void cubeAssetSlotChanged(string slotNameArg);
    void loadLUT();
    void applyLUT(ofPixelsRef pix);

    bool LUTloaded;
	ofVec3f lut[32][32][32];
	
};
