/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXDrawBase.h"
#include "ofxAssimpModelLoader.h"

class TXDraw3DModel  :  public TXDrawBase
{
public:
	// constructor
	TXDraw3DModel();
    
    // destructor
    ~TXDraw3DModel();

	void setup();
    void update();
    void draw();

    bool loadModel();
    bool getModelHasLoaded();

    void a3DModelAssetSlotChanged(string slotNameArg);
    void loopTypeHasChanged(ofAbstractParameter & parameterArg);

    // parameters

    ofPtr<TXModParamBool> createLightsFromModel;
    
    /*    
     enum ofLoopType{
     OF_LOOP_NONE=0x01,
     OF_LOOP_PALINDROME=0x02,
     OF_LOOP_NORMAL=0x03
     };
    */
    
// animation
    ofPtr<TXModParamInt> loopType;
    ofPtr<TXModParamBool> play;
    ofPtr<TXModParamBool> pause;
    ofPtr<TXModParamBool> goToStart;
    ofPtr<TXModParamFloat> animationPosition; // float

    // draw
    ofPtr<TXModParamFloat> drawPosX;
    ofPtr<TXModParamFloat> drawPosY;
    ofPtr<TXModParamFloat> drawPosZ;
    ofParameter<bool>     adjustPosToSceneCentre;
    ofPtr<TXModParamFloat> rotateX;
    ofPtr<TXModParamFloat> rotateY;
    ofPtr<TXModParamFloat> rotateZ;
    ofPtr<TXModParamFloat> rotateMultiply;
    ofPtr<TXModParamFloat> scaleX;
    ofPtr<TXModParamFloat> scaleY;
    ofPtr<TXModParamFloat> scaleZ;
    ofParameter<bool>     useScaleXForScaleY;
    ofParameter<bool>     useScaleXForScaleZ;

    ofxAssimpModelLoader model;
    
private:
    bool modelHasLoaded;    
    bool loopTypeChanged;

    float oldPosition;
    bool  oldPause;
    bool  oldPlay;
    bool  oldGoToStart;
};

