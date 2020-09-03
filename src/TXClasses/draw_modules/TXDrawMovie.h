/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXDrawBase.h"

class TXDrawMovie  :  public TXDrawBase
{
public:
	// constructor
	TXDrawMovie();
    
    // destructor
    ~TXDrawMovie();

	void setup();
    void update();
    void draw();

    bool loadMovie();
    bool getMovieHasLoaded();
    int getTextureWidth(); // overide base class
    int getTextureHeight(); // overide base class
    ofTexture *  getTexture(); // overide base class
    ofPixelsRef getPixels(); // overide base class

    void movieAssetSlotChanged(string slotNameArg);
    void readMovieAlphaChanged(bool & readMovieAlphaArg);
    void speedHasChanged(ofAbstractParameter & parameterArg);
    void loopTypeHasChanged(ofAbstractParameter & parameterArg);

    // parameters
    
    ofPtr<TXModParamInt> movieScaleMode;
    ofPtr<TXModParamFloat> speed;
    ofParameter<bool> readMovieAlpha;
    ofPtr<TXModParamInt> loopType;
    ofPtr<TXModParamBool> play;
    ofPtr<TXModParamBool> pause;
    ofPtr<TXModParamBool> goToNextFrame;
    ofPtr<TXModParamBool> goToPreviousFrame;
    ofPtr<TXModParamBool> goToFirstFrame;
    ofPtr<TXModParamFloat> position; // float

    ofParameter<bool> useSamplePosForDrawPos;
    ofParameter<bool> useSampleSizeForDrawSize;
    ofParameter<bool> constrainToEdges;
    ofParameter<float> alphaThreshold;
    ofPtr<TXModParamFloat> alpha;
    ofPtr<TXModParamFloat> samplePosX;
    ofPtr<TXModParamFloat> samplePosY;
    ofPtr<TXModParamFloat> sampleWidth;
    ofPtr<TXModParamFloat> sampleHeight;
    ofPtr<TXModParamFloat> drawPosX;
    ofPtr<TXModParamFloat> drawPosY;
    ofPtr<TXModParamFloat> drawWidth;
    ofPtr<TXModParamFloat> drawHeight;
    ofPtr<TXModParamFloat> anchorX;
    ofPtr<TXModParamFloat> anchorY;
    ofPtr<TXModParamFloat> rotate;
    ofPtr<TXModParamFloat> rotateMultiply;
    ofPtr<TXModParamFloat> scaleX;
    ofPtr<TXModParamFloat> scaleY;
    ofParameter<bool> useScaleXForScaleY;

    //instead of using ofVideoPlayer use the ofQTKitPlayer directly
    //ofQTKitPlayer outMovie;
    ofVideoPlayer outMovie;
    
private:
    bool movieHasLoaded;
    ofMesh drawMesh;
	ofShader drawShader;
    
    bool speedChanged;
    bool loopTypeChanged;
    bool forceStop;
    
    bool oldPause;
    bool oldPlay;
    float oldPosition;
    bool oldGoToNextFrame;
    bool oldGoToPreviousFrame;
    bool oldGoToFirstFrame;
};

