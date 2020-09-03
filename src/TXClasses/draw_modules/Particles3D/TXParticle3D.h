/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"

#include "TXSimpleLFO3D.h"

class TXParticle3D
{
public:
	// constructor
	TXParticle3D ();
    
	// methods
    
    void trigger (int trigGroupIndexArg, int trigGroupSizeArg, float lifetimeSecsArg, float startDelayArg, float widthArg, float heightArg, float depthArg, float radius, float scaleXArg, float scaleYArg, float scaleZArg, float velocityXArg, float  velocityYArg, float  velocityZArg, float rotationXArg, float rotationYArg, float rotationZArg, float anchorXArg, float anchorYArg, float anchorZArg);
    
	void advanceBy(float timeDeltaArg, float masterBpmArg); 
    
    void resetInitialVariables();
    
    void kill();
    
	// properties

    TXSimpleLFO3D dancePattern;

    int   particleID;  // set only when initialised
    int   randSeed;  
    int   trigGroupIndex;
    int   trigGroupSize;
    float lifetimeSecs; // lifetime in seconds 
    float startDelay; 
    // others:
    float spreadOffsetX;
    float spreadOffsetY;
    float spreadOffsetZ;
    float spreadRandX;
    float spreadRandY;
    float spreadRandZ;
    float width;
    float height;
    float depth;
    float radius;
    float scaleX;
    float scaleY;
    float scaleZ;
    float anchorX;
    float anchorY;
    float anchorZ;
    float rotationX;
    float rotationY;
    float rotationZ;
    bool  alive;
    bool  awake;
    float age;
    float posX;
    float posY;
    float posZ;
    float velocityX;
    float velocityY;
    float velocityZ;
    
    float initialWidth;
    float initialHeight;
    float initialDepth;
    float initialRadius;
    float initialScaleX;
    float initialScaleY;
    float initialScaleZ;
    float initialAnchorX;
    float initialAnchorY;
    float initialAnchorZ;
    float initialRotationXOffset;
    float initialRotationYOffset;
    float initialRotationZOffset;
    float initialSpreadCenterX;
    float initialSpreadCenterY;
    float initialSpreadCenterZ;
    float initialSpreadWidth;
    float initialSpreadHeight;
    float initialSpreadDepth;
    float initialDanceWidth;
    float initialDanceHeight;
    float initialDanceDepth;
    float initialAttractionPointX;
    float initialAttractionPointY;
    float initialAttractionPointZ;
    float initialPosX;
    float initialPosY;
    float initialPosZ;
    ofFloatColor initialDiffuseColor;
    ofFloatColor initialAmbientColor;
    ofFloatColor initialSpecularColor;
    ofFloatColor initialEmissiveColor;
    
    bool  initialVariablesUpdated;
    float posXPerlinPhase;
    float posYPerlinPhase;
    float posZPerlinPhase;
    float widthPerlinPhase;
    float heightPerlinPhase;
    float depthPerlinPhase;
    float radiusPerlinPhase;
    float rotationXPerlinPhase;
    float rotationYPerlinPhase;
    float rotationZPerlinPhase;
};




