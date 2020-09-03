/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXShaderFX2TexBase.h"

enum TXSLIDERXFADETYPE {
    // for ref: in ofxTweenLite: enum ofEaseFunction
    // NB xFadeTypeOffset = 9 because 1st 9 aren't used here:
    //    TXSLIDERXFADETYPE_BACK_IN,
    //    TXSLIDERXFADETYPE_BACK_OUT,
    //    TXSLIDERXFADETYPE_BACK_INOUT,
    //    TXSLIDERXFADETYPE_BOUNCE_IN,
    //    TXSLIDERXFADETYPE_BOUNCE_OUT,
    //    TXSLIDERXFADETYPE_BOUNCE_INOUT,
    //    TXSLIDERXFADETYPE_CIRC_IN,
    //    TXSLIDERXFADETYPE_CIRC_OUT,
    //    TXSLIDERXFADETYPE_CIRC_INOUT,
    TXSLIDERXFADETYPE_CUBIC_IN,
    TXSLIDERXFADETYPE_CUBIC_OUT,
    TXSLIDERXFADETYPE_CUBIC_INOUT,
    TXSLIDERXFADETYPE_ELASTIC_IN,
    TXSLIDERXFADETYPE_ELASTIC_OUT,
    TXSLIDERXFADETYPE_ELASTIC_INOUT,
    TXSLIDERXFADETYPE_EXPO_IN,
    TXSLIDERXFADETYPE_EXPO_OUT,
    TXSLIDERXFADETYPE_EXPO_INOUT,
    TXSLIDERXFADETYPE_LINEAR_IN,
    TXSLIDERXFADETYPE_LINEAR_OUT,
    TXSLIDERXFADETYPE_LINEAR_INOUT,
    TXSLIDERXFADETYPE_QUAD_IN,
    TXSLIDERXFADETYPE_QUAD_OUT,
    TXSLIDERXFADETYPE_QUAD_INOUT,
    TXSLIDERXFADETYPE_QUART_IN,
    TXSLIDERXFADETYPE_QUART_OUT,
    TXSLIDERXFADETYPE_QUART_INOUT,
    TXSLIDERXFADETYPE_QUINT_IN,
    TXSLIDERXFADETYPE_QUINT_OUT,
    TXSLIDERXFADETYPE_QUINT_INOUT,
    TXSLIDERXFADETYPE_SINE_IN,
    TXSLIDERXFADETYPE_SINE_OUT,
    TXSLIDERXFADETYPE_SINE_INOUT
};

class TXSlideShow  :  public TXShaderFX2TexBase
{
public:
    
    static const int numXFadeTypes = 24;
    static const int xFadeTypeOffset = 9;

    // constructor
	TXSlideShow();
    
    // destructor
    ~TXSlideShow();
    
    void extraSetupAction();
    void addExtraParameters();
	void loadRenderShader();
    bool setExtraUniforms(int sourceImageWidth, int sourceImageHeight, int sourceImage2Width, int sourceImage2Height);
    void renderTexture(bool clearFirstArg);
    void advanceBy(float timeDeltaArg);
    
    // listener methods
    void  xFadeTypeChanged(ofAbstractParameter & dummyParameterArg );
    void  folderNameChanged(string & stringArg);

public:
    // Extra methods & parameters:
    
    ofParameter<string> folderName;
    ofPtr<TXModParamBool> randomiseOrder;
    ofPtr<TXModParamFloat> holdTimeFixed;
    ofPtr<TXModParamFloat> holdTimeRandom;
    ofPtr<TXModParamInt> xFadeType;
    ofPtr<TXModParamFloat> xFadeTimeFixed;
    ofPtr<TXModParamFloat> xFadeTimeRandom;
    ofPtr<TXModParamBool> runSlideShow;
    ofPtr<TXModParamBool> pauseSlideShow;
    ofPtr<TXModParamBool> jumpToFirstImage;
    ofPtr<TXModParamBool> jumpToNextImage;
    ofPtr<TXModParamBool> jumpToPreviousImage;
    ofPtr<TXModParamBool> jumpToRandomImage;
    ofPtr<TXModParamBool> triggerXFadeForwards;
    ofPtr<TXModParamBool> triggerXFadeBackwards;
    ofPtr<TXModParamBool> triggerXFadeToRandom;

protected:

    // Methods

    void  setBlendMix(float blendMixArg);
    void  startXFade(bool reverseArg = false);
    void  startHoldPeriod();
//    void  clearImages();
    void  openFolder();
    void  incrementImageIndices();
    void  decrementImageIndices();
    void  randomiseNextImageIndex();
    int   getRandomIndex();
    void  loadFirstImage(bool randomiseArg = false);
    void  loadBlendImage1(int indexArg);
    void  loadBlendImage2(int indexArg);
    void  loadNextImage(int indexArg);
    void  loadPreviousImage(int indexArg);
    void  loadRandomImage();
    void  rotateToNextImage(int nextIndexOptionalArg = -1);
    void  rotateToPreviousImage();
    
    // parameters:
    bool canUseLoader;
    bool holdModeIsActive;
    bool xFadeModeIsActive;
    bool reverseXFade;
    float holdPeriod;
    float xFadePeriod;
    float holdTimer;
    float xFadeTimer;
    float blendMix;
    float blendMixEased;
    int  currentImageIndex;
    bool validDir;
    bool oldRunSlideShow;
    bool oldTriggerXFadeForwards;
    bool oldTriggerXFadeBackwards;
    bool oldTriggerXFadeToRandom;
    bool oldJumpToFirstImage;
    bool oldJumpToNextImage;
    bool oldJumpToPreviousImage;
    bool oldJumpToRandomImage;
    
    ofDirectory dir;
    
    ofImage sourceImage3;
    ofImage sourceImage4;
    ofImage * blendImage1;
    ofImage * blendImage2;
    ofImage * nextImage;
    ofImage * previousImage;
    int  nextImageIndex;
    int  previousImageIndex;
    
};
