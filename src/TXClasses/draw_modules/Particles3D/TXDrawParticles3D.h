/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"
#include "TXDrawBase.h"
#include "TXParticle3D.h"
#include "TXLFO3D.h"
#include "TXDrawShape3D.h"

enum PARTICLES3DPREADTYPE {
    PARTICLES3DPREADTYPE_CIRCLE,
    PARTICLES3DPREADTYPE_HORIZONTAL,
    PARTICLES3DPREADTYPE_VERTICAL,
    PARTICLES3DPREADTYPE_DIAGONAL,
};

//enum TXPARTICLEDISTRIBUTIONTYPE {
//    // for ref: in ofxTweenLite: enum ofEaseFunction
//    // NB smoothTypeOffset = 9 because 1st 9 aren't used here:
//    //    TXPARTICLEDISTRIBUTIONTYPE_BACK_IN,
//    //    TXPARTICLEDISTRIBUTIONTYPE_BACK_OUT,
//    //    TXPARTICLEDISTRIBUTIONTYPE_BACK_INOUT,
//    //    TXPARTICLEDISTRIBUTIONTYPE_BOUNCE_IN,
//    //    TXPARTICLEDISTRIBUTIONTYPE_BOUNCE_OUT,
//    //    TXPARTICLEDISTRIBUTIONTYPE_BOUNCE_INOUT,
//    //    TXPARTICLEDISTRIBUTIONTYPE_CIRC_IN,
//    //    TXPARTICLEDISTRIBUTIONTYPE_CIRC_OUT,
//    //    TXPARTICLEDISTRIBUTIONTYPE_CIRC_INOUT,
//    TXPARTICLEDISTRIBUTIONTYPE_CUBIC_IN,
//    TXPARTICLEDISTRIBUTIONTYPE_CUBIC_OUT,
//    TXPARTICLEDISTRIBUTIONTYPE_CUBIC_INOUT,
//    TXPARTICLEDISTRIBUTIONTYPE_ELASTIC_IN,
//    TXPARTICLEDISTRIBUTIONTYPE_ELASTIC_OUT,
//    TXPARTICLEDISTRIBUTIONTYPE_ELASTIC_INOUT,
//    TXPARTICLEDISTRIBUTIONTYPE_EXPO_IN,
//    TXPARTICLEDISTRIBUTIONTYPE_EXPO_OUT,
//    TXPARTICLEDISTRIBUTIONTYPE_EXPO_INOUT,
//    TXPARTICLEDISTRIBUTIONTYPE_LINEAR_IN,
//    TXPARTICLEDISTRIBUTIONTYPE_LINEAR_OUT,
//    TXPARTICLEDISTRIBUTIONTYPE_LINEAR_INOUT,
//    TXPARTICLEDISTRIBUTIONTYPE_QUAD_IN,
//    TXPARTICLEDISTRIBUTIONTYPE_QUAD_OUT,
//    TXPARTICLEDISTRIBUTIONTYPE_QUAD_INOUT,
//    TXPARTICLEDISTRIBUTIONTYPE_QUART_IN,
//    TXPARTICLEDISTRIBUTIONTYPE_QUART_OUT,
//    TXPARTICLEDISTRIBUTIONTYPE_QUART_INOUT,
//    TXPARTICLEDISTRIBUTIONTYPE_QUINT_IN,
//    TXPARTICLEDISTRIBUTIONTYPE_QUINT_OUT,
//    TXPARTICLEDISTRIBUTIONTYPE_QUINT_INOUT,
//    TXPARTICLEDISTRIBUTIONTYPE_SINE_IN,
//    TXPARTICLEDISTRIBUTIONTYPE_SINE_OUT,
//    TXPARTICLEDISTRIBUTIONTYPE_SINE_INOUT
//};

class TXDrawParticles3D : public  TXDrawBase
{
public:
    
	// constructor
	TXDrawParticles3D ();
    
    // destructor
    ~TXDrawParticles3D();
    
//    static const int totalNoParticles = 100;
//    static const int numDistributionTypes = 24;
//    static const int distributionTypeOffset = 9;
    enum {totalNoParticles = 100, numDistributionTypes = 24, distributionTypeOffset = 9};

 	// methods
	void setup();
	void update();
    void  draw();
    void drawParticle(float &posX, float &posY, float &posZ, float &width, float &height, float &depth, float &radius, float &rotationX, float &rotationY, float &rotationZ, float &widthScale, float &heightScale, float &depthScale, float &anchorX, float &anchorY, float &anchorZ);

    void setParentSystem(TXSystem * parentSystemArg);
    void  triggerParticles();
    float  adjustPerlin(float input, float scaleArg = 4.2);
	// speed/bpm methods:
    void  advanceBy(float timeDeltaArg);
    //    void  setTime(float timeArg = 0);
    void  resetTime();
    void  killAllParticles(int startIndex = 0);
    
    void imageAssetSlotChanged(string slotNameArg);
    int getTextureWidth(); // overide base class
    int getTextureHeight(); // overide base class
    ofTexture *  getTexture(); // overide base class
    ofPixelsRef getPixels(); // overide base class
    
    // listeners
    void  triggerLevelChanged(ofAbstractParameter & parameterArg);
    void  triggerNowChanged(ofAbstractParameter & parameterArg);
    void  killAllNowChanged(ofAbstractParameter & parameterArg);
    void  maximumActiveParticlesChanged(int & intArg);

    // function
    float interpolate(float point1, float point2, float inbetween, bool smooth);
    
    // array of particles
    TXParticle3D arrParticles[totalNoParticles];
    
    // locks
    //- add locks for Diffuse, Ambient, Specular and Emissive Colours
    ofPtr<TXModParamBool> lockDiffuseColorAtStart;
    ofPtr<TXModParamBool> lockAmbientColorAtStart;
    ofPtr<TXModParamBool> lockSpecularColorAtStart;
    ofPtr<TXModParamBool> lockEmissiveColorAtStart;
    ofPtr<TXModParamBool> lockWidthAtStart;
    ofPtr<TXModParamBool> lockHeightAtStart;
    ofPtr<TXModParamBool> lockDepthAtStart;
    ofPtr<TXModParamBool> lockRadiusAtStart;
    ofPtr<TXModParamBool> lockSpreadAtStart;
    ofPtr<TXModParamBool> lockScaleAtStart;
    ofPtr<TXModParamBool> lockAnchorAtStart;
    ofPtr<TXModParamBool> lockRotationOffsetAtStart;
    ofPtr<TXModParamBool> lockDanceWidthHeightDepthAtStart;
    ofPtr<TXModParamBool> lockAttractionPointAtStart;
    
    // triggering
    ofPtr<TXModParamBool> useTriggerTimeForLifetime;
    ofPtr<TXModParamBool> triggerContinuosly;
    ofPtr<TXModParamBool> triggerNow;
    ofPtr<TXModParamBool> killAllNow;
    ofPtr<TXModParamInt> numParticlesPerTrigger;
    ofParameter<int> maximumActiveParticles;
    ofPtr<TXModParamFloat> bpm;
    ofPtr<TXModParamBool> useMasterBpm;
    ofPtr<TXModParamFloat> stepTimeBeats;
    ofPtr<TXModParamFloat> stepTimeDivisor;
    ofPtr<TXModParamFloat> triggerLevel;
    ofPtr<TXModParamFloat> triggerThreshold;
    ofPtr<TXModParamFloat> triggerProbability;
    ofPtr<TXModParamFloat> triggerDelaySpread;
    ofPtr<TXModParamInt> triggerDelayDistribution;
    ofPtr<TXModParamFloat> triggerDelayRandom;
    ofPtr<TXModParamFloat> lifetimeBeats;
    ofPtr<TXModParamFloat> lifetimeRandomVariation;
    
    // spread
    // spreadType: ["Circle", "Horizontal Line", "Vertical Line", "Diagonal Line"]
    ofPtr<TXModParamInt> spreadType;
    ofPtr<TXModParamInt> spreadDistribution;
    ofPtr<TXModParamFloat> spreadCenterX;
    ofPtr<TXModParamFloat> spreadCenterY;
    ofPtr<TXModParamFloat> spreadCenterZ;
    ofPtr<TXModParamFloat> spreadWidth;
    ofPtr<TXModParamFloat> spreadHeight;
    ofPtr<TXModParamFloat> spreadDepth;
    ofPtr<TXModParamFloat> spreadRandom;

    // movement
    ofPtr<TXModParamFloat> posXPerlinMix;
    ofPtr<TXModParamFloat> posYPerlinMix;
    ofPtr<TXModParamFloat> posZPerlinMix;
    ofPtr<TXModParamFloat> posXPerlinSpeed;
    ofPtr<TXModParamFloat> posYPerlinSpeed;
    ofPtr<TXModParamFloat> posZPerlinSpeed;
    ofPtr<TXModParamFloat> gravityX;
    ofPtr<TXModParamFloat> gravityY;
    ofPtr<TXModParamFloat> gravityZ;
    ofPtr<TXModParamFloat> velocityX;
    ofPtr<TXModParamFloat> velocityY;
    ofPtr<TXModParamFloat> velocityZ;
    ofPtr<TXModParamFloat> attraction;
    TXParameterFloat256   attractionCurve;
    ofPtr<TXModParamFloat> attractionPointX;
    ofPtr<TXModParamFloat> attractionPointY;
    ofPtr<TXModParamFloat> attractionPointZ;
    
    // size
    ofPtr<TXModParamBool> useWidthForHeight;
    ofPtr<TXModParamBool> useWidthForDepth;
	ofPtr<TXModParamFloat> width;
    TXParameterFloat256   widthCurve;
    ofPtr<TXModParamFloat> widthPerlinMix;
    ofPtr<TXModParamFloat> widthPerlinSpeed;
    ofPtr<TXModParamFloat> height;
    TXParameterFloat256   heightCurve;
    ofPtr<TXModParamFloat> heightPerlinMix;
    ofPtr<TXModParamFloat> heightPerlinSpeed;
    ofPtr<TXModParamFloat> depth;
    TXParameterFloat256   depthCurve;
    ofPtr<TXModParamFloat> depthPerlinMix;
    ofPtr<TXModParamFloat> depthPerlinSpeed;
    ofPtr<TXModParamFloat> radius;
    TXParameterFloat256   radiusCurve;
    ofPtr<TXModParamFloat> radiusPerlinMix;
    ofPtr<TXModParamFloat> radiusPerlinSpeed;

    // scale
    ofPtr<TXModParamBool> useScaleXForScaleY;
    ofPtr<TXModParamBool> useScaleXForScaleZ;
    ofPtr<TXModParamFloat> scaleX;
    TXParameterFloat256   scaleXCurve;
    ofPtr<TXModParamFloat> scaleY;
    TXParameterFloat256   scaleYCurve;
    ofPtr<TXModParamFloat> scaleZ;
    TXParameterFloat256   scaleZCurve;
    
    // anchor
    ofPtr<TXModParamFloat> anchorX;
    TXParameterFloat256   anchorXCurve;
    ofPtr<TXModParamFloat> anchorY;
    TXParameterFloat256   anchorYCurve;
    ofPtr<TXModParamFloat> anchorZ;
    TXParameterFloat256   anchorZCurve;

    ofPtr<TXModParamFloat> rotationXOffset;
    TXParameterFloat256   rotationXCurve;
    ofPtr<TXModParamFloat> rotationXPerlinMix;
    ofPtr<TXModParamFloat> rotationXPerlinSpeed;
    ofPtr<TXModParamFloat> rotationYOffset;
    TXParameterFloat256   rotationYCurve;
    ofPtr<TXModParamFloat> rotationYPerlinMix;
    ofPtr<TXModParamFloat> rotationYPerlinSpeed;
    ofPtr<TXModParamFloat> rotationZOffset;
    TXParameterFloat256   rotationZCurve;
    ofPtr<TXModParamFloat> rotationZPerlinMix;
    ofPtr<TXModParamFloat> rotationZPerlinSpeed;
    
    // dance
    ofPtr<TXModParamFloat> dance_width;
    ofPtr<TXModParamFloat> dance_height;
    ofPtr<TXModParamFloat> dance_depth;
    ofPtr<TXModParamBool> dance_randomStartPhase;
    
protected:
    float currentTime;
    float lastRecordedTriggerTime;
	float phase;
    int   nextParticleIndex;
    // note: triggerConfirmed is a bool. trigger level is float which is checked against threshold to set triggerConfirmed.
    bool  triggerConfirmed;
    float triggerPrevious;
    bool  triggerNowPrevious;
    bool  killAllNowPrevious;
    
    TXDrawShape3D shape;
    TXLFO3D dancePattern;
    TXLFO3DValues lfoValues;

    int oldFrameNo = -1;
    
};

