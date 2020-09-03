/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"
#include "TXDrawBase.h"
#include "TXParticle.h"
#include "TXLFO2D.h"

enum PARTICLESPREADTYPE {
    PARTICLESPREADTYPE_CIRCLE,
    PARTICLESPREADTYPE_HORIZONTAL,
    PARTICLESPREADTYPE_VERTICAL,
    PARTICLESPREADTYPE_DIAGONAL,
};

enum TXPARTICLEDISTRIBUTIONTYPE {
    // for ref: in ofxTweenLite: enum ofEaseFunction
    // NB smoothTypeOffset = 9 because 1st 9 aren't used here:
    //    TXPARTICLEDISTRIBUTIONTYPE_BACK_IN,
    //    TXPARTICLEDISTRIBUTIONTYPE_BACK_OUT,
    //    TXPARTICLEDISTRIBUTIONTYPE_BACK_INOUT,
    //    TXPARTICLEDISTRIBUTIONTYPE_BOUNCE_IN,
    //    TXPARTICLEDISTRIBUTIONTYPE_BOUNCE_OUT,
    //    TXPARTICLEDISTRIBUTIONTYPE_BOUNCE_INOUT,
    //    TXPARTICLEDISTRIBUTIONTYPE_CIRC_IN,
    //    TXPARTICLEDISTRIBUTIONTYPE_CIRC_OUT,
    //    TXPARTICLEDISTRIBUTIONTYPE_CIRC_INOUT,
    TXPARTICLEDISTRIBUTIONTYPE_CUBIC_IN,
    TXPARTICLEDISTRIBUTIONTYPE_CUBIC_OUT,
    TXPARTICLEDISTRIBUTIONTYPE_CUBIC_INOUT,
    TXPARTICLEDISTRIBUTIONTYPE_ELASTIC_IN,
    TXPARTICLEDISTRIBUTIONTYPE_ELASTIC_OUT,
    TXPARTICLEDISTRIBUTIONTYPE_ELASTIC_INOUT,
    TXPARTICLEDISTRIBUTIONTYPE_EXPO_IN,
    TXPARTICLEDISTRIBUTIONTYPE_EXPO_OUT,
    TXPARTICLEDISTRIBUTIONTYPE_EXPO_INOUT,
    TXPARTICLEDISTRIBUTIONTYPE_LINEAR_IN,
    TXPARTICLEDISTRIBUTIONTYPE_LINEAR_OUT,
    TXPARTICLEDISTRIBUTIONTYPE_LINEAR_INOUT,
    TXPARTICLEDISTRIBUTIONTYPE_QUAD_IN,
    TXPARTICLEDISTRIBUTIONTYPE_QUAD_OUT,
    TXPARTICLEDISTRIBUTIONTYPE_QUAD_INOUT,
    TXPARTICLEDISTRIBUTIONTYPE_QUART_IN,
    TXPARTICLEDISTRIBUTIONTYPE_QUART_OUT,
    TXPARTICLEDISTRIBUTIONTYPE_QUART_INOUT,
    TXPARTICLEDISTRIBUTIONTYPE_QUINT_IN,
    TXPARTICLEDISTRIBUTIONTYPE_QUINT_OUT,
    TXPARTICLEDISTRIBUTIONTYPE_QUINT_INOUT,
    TXPARTICLEDISTRIBUTIONTYPE_SINE_IN,
    TXPARTICLEDISTRIBUTIONTYPE_SINE_OUT,
    TXPARTICLEDISTRIBUTIONTYPE_SINE_INOUT
};

class TXDrawParticles : public  TXDrawBase
{
public:
    
	// constructor
	TXDrawParticles ();
    
    // destructor
    ~TXDrawParticles();
    
//    static const int totalNoParticles = 200;
//    static const int numDistributionTypes = 24;
//    static const int distributionTypeOffset = 9;
    enum {totalNoParticles = 200, numDistributionTypes = 24, distributionTypeOffset = 9};

	// methods
	void setup();
	void update();
    void  draw();
    void drawParticle(float &posX, float &posY, float &texturePosX, float &texturePosY, float &width, float &height, float &alpha, float &anchorPointX, float &anchorPointY, float &rotation, float &widthScale, float &heightScale, float &tintMix, float &tintR, float &tintG, float &tintB, float &sourceImageWidth, float &sourceImageHeight, float &maskImageWidth, float &maskImageHeight, int &maskType, int &sourceImageScaleMode);

    void  triggerParticles();
    float  adjustPerlin(float input, float scaleArg = 4.2);
	// speed/bpm methods:
    void  advanceBy(float timeDeltaArg);
    //    void  setTime(float timeArg = 0);
    void  resetTime();
    void  killAllParticles(int startIndex = 0);
    
    void imageAssetSlotChanged(string slotNameArg);
    bool loadSourceImage();
    bool loadMaskImage();
    bool getSourceImageHasLoaded();
    bool getMaskImageHasLoaded();
    int getTextureWidth(); // overide base class
    int getTextureHeight(); // overide base class
    ofTexture *  getTexture(); // overide base class
    ofPixelsRef getPixels(); // overide base class
    
    // listeners
    void  triggerLevelChanged(ofAbstractParameter & parameterArg);
    void  triggerNowChanged(ofAbstractParameter & parameterArg);
    void  killAllNowChanged(ofAbstractParameter & parameterArg);
    void  maximumActiveParticlesChanged(int & intArg);
    void  tintHueChanged(ofAbstractParameter & parameterArg);
    void  tintHueRotateChanged(ofAbstractParameter & parameterArg);
    void  tintSaturationChanged(ofAbstractParameter & parameterArg);
    void  tintBrightnessChanged(ofAbstractParameter & parameterArg);
    void  tintHSBAsRGBChanged(ofAbstractParameter & parameterArg);
    
    // function
    float interpolate(float point1, float point2, float inbetween, bool smooth);
    
    // array of particles
    TXParticle arrParticles[totalNoParticles];
    
    // Parameters
        
    // images
    ofPtr<TXModParamInt> sourceImageScaleMode;
    ofParameter<bool> useExternalSourceImage;
    ofParameter<bool> useExternalMaskImage;
    ofPtr<TXModParamInt> maskType;
    ofParameter<bool> invertMask;
    ofPtr<TXModParamFloat> feathering;
    
    ofPtr<TXModParamBool> useCentralColourOnly;
    
    // locks
    ofPtr<TXModParamBool> lockColourAtStart;
    ofPtr<TXModParamBool> lockAlphaScaleAtStart;
    ofPtr<TXModParamBool> lockWidthAtStart;
    ofPtr<TXModParamBool> lockHeightAtStart;
    ofPtr<TXModParamBool> lockSpreadAtStart;
    ofPtr<TXModParamBool> lockScaleAtStart;
    ofPtr<TXModParamBool> lockAnchorAtStart;
    ofPtr<TXModParamBool> lockRotationOffsetAtStart;
    ofPtr<TXModParamBool> lockSamplePositionAtStart;
    ofPtr<TXModParamBool> lockDanceWidthHeightAtStart;
    ofPtr<TXModParamBool> lockAttractionPointAtStart;
    ofPtr<TXModParamBool> lockTintAtStart;
    
    // triggering
    ofPtr<TXModParamBool> useTriggerTimeForLifetime;
    ofPtr<TXModParamBool> triggerContinuosly;
    ofPtr<TXModParamBool> triggerNow;
    ofPtr<TXModParamBool> killAllNow;
    ofPtr<TXModParamInt>  numParticlesPerTrigger;
    ofParameter<int> maximumActiveParticles;
    ofPtr<TXModParamFloat> bpm;
    ofPtr<TXModParamBool>  useMasterBpm;
    ofPtr<TXModParamFloat> stepTimeBeats;
    ofPtr<TXModParamFloat> stepTimeDivisor;
    ofPtr<TXModParamFloat> triggerLevel;
    ofPtr<TXModParamFloat> triggerThreshold;
    ofPtr<TXModParamFloat> triggerProbability;
    ofPtr<TXModParamFloat> triggerDelaySpread;
    ofPtr<TXModParamInt>   triggerDelayDistribution;
    ofPtr<TXModParamFloat> triggerDelayRandom;
    ofPtr<TXModParamFloat> lifetimeBeats;
    ofPtr<TXModParamFloat> lifetimeRandomVariation;
    
    // spread
    // spreadType: ["Circle", "Horizontal Line", "Vertical Line", "Diagonal Line"]
    ofPtr<TXModParamInt>   spreadType;
    ofPtr<TXModParamInt>   spreadDistribution;
    ofPtr<TXModParamFloat> spreadCenterX;
    ofPtr<TXModParamFloat> spreadCenterY;
    ofPtr<TXModParamFloat> spreadWidth;
    ofPtr<TXModParamFloat> spreadHeight;
    ofPtr<TXModParamFloat> spreadRotation;
    ofPtr<TXModParamFloat> spreadRandom;

    // movement
    ofPtr<TXModParamFloat> posXPerlinMix;
    ofPtr<TXModParamFloat> posYPerlinMix;
    ofPtr<TXModParamFloat> posXPerlinSpeed;
    ofPtr<TXModParamFloat> posYPerlinSpeed;
    ofPtr<TXModParamFloat> gravityX;
    ofPtr<TXModParamFloat> gravityY;
    ofPtr<TXModParamFloat> velocityX;
    ofPtr<TXModParamFloat> velocityY;
    ofPtr<TXModParamFloat> attraction;
    TXParameterFloat256    attractionCurve;
    ofPtr<TXModParamFloat> attractionPointX;
    ofPtr<TXModParamFloat> attractionPointY;
    
    // size
    ofPtr<TXModParamBool>  useWidthForHeight;
	ofPtr<TXModParamFloat> width;
    TXParameterFloat256    widthCurve;
    ofPtr<TXModParamFloat> widthPerlinMix;
    ofPtr<TXModParamFloat> widthPerlinSpeed;
    ofPtr<TXModParamFloat> height;
    TXParameterFloat256    heightCurve;
    ofPtr<TXModParamFloat> heightPerlinMix;
    ofPtr<TXModParamFloat> heightPerlinSpeed;
    
    // scale
    ofPtr<TXModParamBool>  useScaleXForScaleY;
    ofPtr<TXModParamFloat> scaleX;
    TXParameterFloat256    scaleXCurve;
    ofPtr<TXModParamFloat> scaleY;
    TXParameterFloat256    scaleYCurve;

    // transparency
    ofPtr<TXModParamFloat> alphaScale;
    TXParameterFloat256    alphaCurve;
    ofPtr<TXModParamFloat> alphaPerlinMix;
    ofPtr<TXModParamFloat> alphaPerlinSpeed;
    
    // anchor
    ofPtr<TXModParamFloat> anchorX;
    TXParameterFloat256    anchorXCurve;
    ofPtr<TXModParamFloat> anchorY;
    TXParameterFloat256    anchorYCurve;
    
    // rotation
    ofPtr<TXModParamFloat> rotationOffset;
    TXParameterFloat256    rotationCurve;
    ofPtr<TXModParamFloat> rotationPerlinMix;
    ofPtr<TXModParamFloat> rotationPerlinSpeed;
    
    // dance
    ofPtr<TXModParamFloat> dance_width;
    ofPtr<TXModParamFloat> dance_height;
    ofPtr<TXModParamBool>  dance_randomStartPhase;
    ofPtr<TXModParamBool>  useParticlePosForSamplePos;
    ofPtr<TXModParamFloat> samplePosX;
    ofPtr<TXModParamFloat> samplePosY;
    
    // wave mask
    ofPtr<TXModParamFloat> numWavesX;
    ofPtr<TXModParamFloat> numWavesY;
    ofPtr<TXModParamBool>  wavesHorizontalOn;
    ofPtr<TXModParamBool>  wavesVerticalOn;
    ofPtr<TXModParamBool>  wavesQuantised;
    
    // image bend
    ofPtr<TXModParamBool>  bendOn;
    ofPtr<TXModParamFloat> bendRandomPhaseX;
    ofPtr<TXModParamFloat> bendRandomPhaseY;
    ofPtr<TXModParamFloat> bendPhaseX;
    ofPtr<TXModParamFloat> bendPhaseY;
    ofPtr<TXModParamFloat> bendDepthX;
    ofPtr<TXModParamFloat> bendDepthY;
    ofPtr<TXModParamFloat> bendZoom;
    
    // tint
    ofPtr<TXModParamFloat> tintMix;
    ofPtr<TXModParamFloat> tintHue;
    ofPtr<TXModParamFloat> tintHueRotate;
    ofPtr<TXModParamFloat> tintSaturation;
    ofPtr<TXModParamFloat> tintBrightness;
    ofPtr<TXModParamBool>  tintHSBAsRGB;
    
    ofImage sourceImage;
    ofImage maskImage;
    
protected:
    void  updateTintFromHSB();

    bool sourceImageHasLoaded;
    bool maskImageHasLoaded;

    float currentTime;
    float lastRecordedTriggerTime;
	float phase;
    int   nextParticleIndex;
    // note: triggerConfirmed is a bool. trigger level is float which is checked against threshold to set triggerConfirmed.
    bool  triggerConfirmed;
    float triggerPrevious;
    bool  triggerNowPrevious;
    bool  killAllNowPrevious;
    
    TXLFO2D dancePattern;
    TXLFO2DValues lfoValues;
	ofShader particleShader;
	ofShader particleShaderWithMask;
	ofShader particleShaderWithMaskTex;
    ofShader * holdShader;
    ofColor tint;
    ofMesh drawMesh;
    ofImage greyImage;

};

