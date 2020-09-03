/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"

#include "TXSimpleLFO2D.h"

class TXParticle
{
public:
	// constructor
	TXParticle ();
    
	// methods
    
    void trigger (int trigGroupIndexArg, int trigGroupSizeArg, float lifetimeSecsArg, float startDelayArg, float widthArg, float heightArg, float scaleXArg, float scaleYArg, float velocityXArg, float  velocityYArg, float rotationArg, float anchorXArg, float anchorYArg, float samplePosXArg, float samplePosYArg);
    
	void advanceBy(float timeDeltaArg, float masterBpmArg); 
    
    void resetInitialVariables();
    
    void kill();
    
	// properties

    TXSimpleLFO2D dancePattern;

    int   particleID;  // set only when initialised
    int   randSeed;  
    int   trigGroupIndex;
    int   trigGroupSize;
    float lifetimeSecs; // lifetime in seconds 
    float startDelay; 
    // others:
    float spreadOffsetX;
    float spreadOffsetY;
    float spreadRandX;
    float spreadRandY;
    float width;
    float height;
    float scaleX;
    float scaleY;
    float anchorX;
    float anchorY;
    float rotation;
    float alpha;
    bool  alive;
    bool  awake;
    float age;
    float posX;
    float posY;
    float velocityX;
    float velocityY;
    float samplePosX;
    float samplePosY;
    
    float initialAlphaScale; 
    float initialWidth; 
    float initialHeight; 
    float initialScaleX; 
    float initialScaleY; 
    float initialAnchorX;
    float initialAnchorY;
    float initialRotationOffset;
    float initialSpreadCenterX;
    float initialSpreadCenterY; 
    float initialSpreadWidth; 
    float initialSpreadHeight; 
    float initialSpreadRotation; 
    float initialSamplePositionX; 
    float initialSamplePositionY;
    float initialDanceWidth; 
    float initialDanceHeight; 
    float initialAttractionPointX; 
    float initialAttractionPointY; 
    float initialPosX; 
    float initialPosY; 
    float initialTintMix;
    float initialTintR;
    float initialTintG;
    float initialTintB;
    
    bool  initialVariablesUpdated;
    float posXPerlinPhase;
    float posYPerlinPhase;
    float widthPerlinPhase;
    float heightPerlinPhase;
    float alphaPerlinPhase;
    float rotationPerlinPhase;
};




