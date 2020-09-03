/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXParticle3D.h"

// properties

// constructor
TXParticle3D::TXParticle3D () {
    trigGroupIndex = 0;
    trigGroupSize = 1;
    lifetimeSecs = 0;
    posX = 0;
    posY = 0;
    posZ = 0;
    scaleX = 0;
    scaleY = 0;
    scaleZ = 0;
    anchorX = 0;
    anchorY = 0;
    anchorZ = 0;
    spreadRandX = ofRandom(1.0f) - 0.5;
    spreadRandY = ofRandom(1.0f) - 0.5;
    spreadRandZ = ofRandom(1.0f) - 0.5;
    spreadOffsetX = 0;
    spreadOffsetY = 0;
    spreadOffsetZ = 0;
    width = 0;
    height = 0;
    depth = 0;
    radius = 0;
    alive = false;
    awake = false;
    
    resetInitialVariables();
    
    dancePattern.setup();
    dancePattern.lfoType = 1;
    dancePattern.cycleTimeBeats = 4;
    dancePattern.advanceBy(0, 60);
};

// methods

void TXParticle3D::resetInitialVariables() {
    initialVariablesUpdated = false;
    initialSpreadCenterX = 0;
    initialSpreadCenterY = 0;
    initialSpreadCenterZ = 0;
    initialWidth = 0;
    initialHeight = 0;
    initialDepth = 0;
    initialRadius = 0;
    initialScaleX = 0;
    initialScaleY = 0;
    initialScaleZ = 0;
    initialAnchorX = 0;
    initialAnchorY = 0;
    initialAnchorZ = 0;
    initialRotationXOffset = 0;
    initialRotationYOffset = 0;
    initialRotationZOffset = 0;
    initialSpreadWidth = 0;
    initialSpreadHeight = 0;
    initialSpreadDepth = 0;
    initialDanceWidth = 0;
    initialDanceHeight = 0;
    initialDanceDepth = 0;
    initialAttractionPointX = 0;
    initialAttractionPointY = 0;
    initialAttractionPointZ = 0;
    initialPosX = 0;
    initialPosY = 0;
    initialPosZ = 0;
    initialDiffuseColor = ofColor::white;
    initialAmbientColor = ofColor::white;
    initialSpecularColor = ofColor::white;
    initialEmissiveColor = ofColor::white;
}

void TXParticle3D::trigger(int trigGroupIndexArg, int trigGroupSizeArg, float lifetimeSecsArg, float startDelayArg, float widthArg, float heightArg, float depthArg, float radiusArg, float scaleXArg, float scaleYArg, float scaleZArg, float velocityXArg, float  velocityYArg, float velocityZArg, float rotationXArg, float rotationYArg, float rotationZArg, float anchorXArg, float anchorYArg, float anchorZArg) {

    alive = true;
    awake = false;
    age = 0;
    randSeed = ofRandom(10000);
    posXPerlinPhase = ofRandom(1000.0f);
    posYPerlinPhase = ofRandom(1000.0f);
    posZPerlinPhase = ofRandom(1000.0f);
    widthPerlinPhase = ofRandom(1000.0f);
    heightPerlinPhase = ofRandom(1000.0f);
    depthPerlinPhase = ofRandom(1000.0f);
    radiusPerlinPhase = ofRandom(1000.0f);
    rotationXPerlinPhase = ofRandom(1000.0f);
    rotationYPerlinPhase = ofRandom(1000.0f);
    rotationZPerlinPhase = ofRandom(1000.0f);

    trigGroupIndex = trigGroupIndexArg;
    trigGroupSize = trigGroupSizeArg;
    lifetimeSecs = lifetimeSecsArg + startDelayArg; 
    startDelay = startDelayArg;
    width = widthArg;
    height = heightArg;
    depth = depthArg;
    radius = radiusArg;
    scaleX = scaleXArg;
    scaleY = scaleYArg;
    scaleZ = scaleZArg;
    velocityX = velocityXArg;
    velocityY = velocityYArg;
    velocityZ = velocityZArg;
    rotationX = rotationXArg;
    rotationY = rotationYArg;
    rotationZ = rotationZArg;
    anchorX = anchorXArg;
    anchorY = anchorYArg;
    anchorZ = anchorZArg;
};

void TXParticle3D::advanceBy(float timeDeltaArg, float masterBpm) {
    if (alive) {
        age = age + timeDeltaArg;
        if (age > lifetimeSecs) {
            alive = false;
            awake = false;
        } else {
            if (age > startDelay) {
                awake = true;
                dancePattern.advanceBy(timeDeltaArg, masterBpm);
            };
        };
    };
}

void TXParticle3D::kill() {
    alive = false;
    awake = false;
}

