/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXParticle.h"

// properties

// constructor
TXParticle::TXParticle () {
    trigGroupIndex = 0;
    trigGroupSize = 1;
    lifetimeSecs = 0;
    posX = 0;
    posY = 0;
    scaleX = 0;
    scaleY = 0;
    anchorX = 0;
    anchorY = 0;
    spreadRandX = ofRandom(1.0f) - 0.5;
    spreadRandY = ofRandom(1.0f) - 0.5;
    spreadOffsetX = 0;
    spreadOffsetY = 0;
    width = 0;
    height = 0;
    alpha = 0;
    alive = false;
    awake = false;
    
    resetInitialVariables();
    
    dancePattern.setup();
    dancePattern.lfoType = 1;
    dancePattern.cycleTimeBeats = 4;
    dancePattern.advanceBy(0, 60);
};

// methods

void TXParticle::resetInitialVariables() {
    initialVariablesUpdated = false;
    initialSpreadCenterX = 0;
    initialSpreadCenterY = 0;
    initialAlphaScale = 0; 
    initialWidth = 0; 
    initialHeight = 0; 
    initialScaleX = 0; 
    initialScaleY = 0; 
    initialAnchorX = 0;
    initialAnchorY = 0;
    initialRotationOffset = 0;
    initialSpreadWidth = 0; 
    initialSpreadHeight = 0; 
    initialSpreadRotation = 0; 
    initialSamplePositionX = 0; 
    initialSamplePositionY = 0; 
    initialDanceWidth = 0; 
    initialDanceHeight = 0; 
    initialAttractionPointX = 0; 
    initialAttractionPointY = 0; 
    initialPosX = 0; 
    initialPosY = 0; 
    initialTintMix = 0;
    initialTintR = 0;
    initialTintG = 0;
    initialTintB = 0;
}

void TXParticle::trigger (int trigGroupIndexArg, int trigGroupSizeArg, float lifetimeSecsArg, float startDelayArg, float widthArg, float heightArg, float scaleXArg, float scaleYArg, float velocityXArg, float  velocityYArg, float rotationArg, float anchorXArg, float anchorYArg, float samplePosXArg, float samplePosYArg) {

    alive = true;
    awake = false;
    alpha = 0;
    age = 0;
    randSeed = ofRandom(10000);
    posXPerlinPhase = ofRandom(1000.0f);
    posYPerlinPhase = ofRandom(1000.0f);
    widthPerlinPhase = ofRandom(1000.0f);
    heightPerlinPhase = ofRandom(1000.0f);
    alphaPerlinPhase = ofRandom(1000.0f);
    rotationPerlinPhase = ofRandom(1000.0f);

    trigGroupIndex = trigGroupIndexArg;
    trigGroupSize = trigGroupSizeArg;
    lifetimeSecs = lifetimeSecsArg + startDelayArg; 
    startDelay = startDelayArg;
    width = widthArg;
    height = heightArg;
    scaleX = scaleXArg;
    scaleY = scaleYArg; 
    velocityX = velocityXArg;
    velocityY = velocityYArg;
    rotation = rotationArg;
    anchorX = anchorXArg;
    anchorY = anchorYArg;
    samplePosX = samplePosXArg;
    samplePosY = samplePosYArg;
};

void TXParticle::advanceBy(float timeDeltaArg, float masterBpm) {
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

void TXParticle::kill() {
    alive = false;
    awake = false;
}

