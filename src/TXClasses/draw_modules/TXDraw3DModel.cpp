/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXDraw3DModel.h"
#include "TXSystem.h"
#include "TXAsset.h"

// constructor
TXDraw3DModel::TXDraw3DModel() {
    setup();
}

// destructor
TXDraw3DModel::~TXDraw3DModel() {
    // remove listeners to relevent parameters:
    ofRemoveListener(loopType->parameters.parameterChangedE(),this,&TXDraw3DModel::loopTypeHasChanged);
}

void TXDraw3DModel::setup(){
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
    
    holdModParamBoolArgs.name = "createLightsFromModel";
    holdModParamBoolArgs.fixedValue = false;
    createLightsFromModel = createModParameter(holdModParamBoolArgs);
    parameters.add(createLightsFromModel->parameters);
    
    holdModParamIntArgs.name = "loopType";
    holdModParamIntArgs.fixedValue = OF_LOOP_NORMAL;
    holdModParamIntArgs.hardMin = OF_LOOP_NONE;
    holdModParamIntArgs.hardMax = OF_LOOP_NORMAL;
    holdModParamIntArgs.softMin = OF_LOOP_NONE;
    holdModParamIntArgs.softMax = OF_LOOP_NORMAL;
	loopType = createModParameter(holdModParamIntArgs);
    parameters.add(loopType->parameters);
    
    holdModParamBoolArgs.name = "play";
    holdModParamBoolArgs.fixedValue = false;
    play = createModParameter(holdModParamBoolArgs);
    parameters.add(play->parameters);
    
    holdModParamBoolArgs.name = "pause";
    holdModParamBoolArgs.fixedValue = false;
    pause = createModParameter(holdModParamBoolArgs);
    parameters.add(pause->parameters);
    
    holdModParamBoolArgs.name = "goToStart";
    holdModParamBoolArgs.fixedValue = false;
    goToStart = createModParameter(holdModParamBoolArgs);
    parameters.add(goToStart->parameters);
    
    holdModParamFloatArgs.name = "animationPosition";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	animationPosition = createModParameter(holdModParamFloatArgs);
    parameters.add(animationPosition->parameters);
    
    holdModParamFloatArgs.name = "drawPosX";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	drawPosX = createModParameter(holdModParamFloatArgs);
    parameters.add(drawPosX->parameters);
    
    holdModParamFloatArgs.name = "drawPosY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	drawPosY = createModParameter(holdModParamFloatArgs);
    parameters.add(drawPosY->parameters);
    
    holdModParamFloatArgs.name = "drawPosZ";
    holdModParamFloatArgs.fixedValue = 0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -1.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
	drawPosZ = createModParameter(holdModParamFloatArgs);
    parameters.add(drawPosZ->parameters);
    
    parameters.add(adjustPosToSceneCentre.set("adjustPosToSceneCentre", false));

    holdModParamFloatArgs.name = "rotateX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	rotateX = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateX->parameters);
    
    holdModParamFloatArgs.name = "rotateY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	rotateY = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateY->parameters);
    
    holdModParamFloatArgs.name = "rotateZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	rotateZ = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateZ->parameters);
    
    holdModParamFloatArgs.name = "rotateMultiply";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
	rotateMultiply = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateMultiply->parameters);
    
    holdModParamFloatArgs.name = "scaleX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 3.0;
	scaleX = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleX->parameters);
    
    holdModParamFloatArgs.name = "scaleY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 3.0;
	scaleY = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleY->parameters);
    
    holdModParamFloatArgs.name = "scaleZ";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 3.0;
	scaleZ = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleZ->parameters);
    
    parameters.add(useScaleXForScaleY.set("useScaleXForScaleY", false));
    parameters.add(useScaleXForScaleZ.set("useScaleXForScaleZ", false));

    // add listener to relevent mod parameters:
    ofAddListener(loopType->parameters.parameterChangedE(),this,&TXDraw3DModel::loopTypeHasChanged);

    // asset slots
    create3DModelAssetSlot("modelAsset");
    
    // init
    model.createEmptyModel();
    modelHasLoaded = false;
    loopTypeChanged = false;
    oldPause = false;
    oldPlay = false;
    oldPosition = 0.0;
    oldGoToStart = false;
}

void TXDraw3DModel::update(){
    float newPosition = animationPosition->getFloat();
    float newGoToStart = goToStart->getBool();
    bool newPause = pause->getBool();
    bool newPlay = play->getBool();
    
    if (loopTypeChanged) {
        model.setLoopStateForAllAnimations((ofLoopType) loopType->getInt());
    };
    // prioritise updates to avoid conflicts - lower priority ignored
    if (newPosition != oldPosition) {
        model.setPositionForAllAnimations(newPosition);
    } else if (newGoToStart && !oldGoToStart) {
        model.resetAllAnimations();
    };
    if (newPlay != oldPlay) {
        if (newPlay) {
            model.resetAllAnimations();
            model.playAllAnimations();
            if (newPause) {
                model.setPausedForAllAnimations(true);
            }
        } else {
            //model.setPaused(true);
            model.stopAllAnimations();
        };
    } else {
        if ((newPause != oldPause) && newPlay) {
            model.setPausedForAllAnimations(newPause);
        };
    };
    
    // reset vars
    oldPause = newPause;
    oldPlay = newPlay;
    oldPosition = newPosition;
    oldGoToStart = newGoToStart;
    loopTypeChanged = false;
    
    // now ready to update
    model.update();
}

void TXDraw3DModel::draw(){
    float holdScaleX,  holdScaleY,  holdScaleZ, holdRotateMultiply;
    float holdDrawPosX, holdDrawPosY, holdDrawPosZ;

    // check before drawing
    if (!drawActive->getBool()) {
        return;
    };
    if (!modelHasLoaded) {
        return;
    };

    holdScaleX = scaleX->getFloat();
    if (useScaleXForScaleY) {
        holdScaleY = holdScaleX;
    } else {
        holdScaleY = scaleY->getFloat();
    };
    if (useScaleXForScaleZ) {
        holdScaleZ = holdScaleX;
    } else {
        holdScaleZ = scaleZ->getFloat();
    };
//    int   holdMaxWidth = getMaxWidth();
//    int   holdMaxHeight = getMaxHeight();
    holdDrawPosX = drawPosX->getFloat() * getMaxWidth();
    holdDrawPosY = drawPosY->getFloat() * getMaxHeight();
    holdDrawPosZ = drawPosZ->getFloat() * getMaxDepth();
    
    holdRotateMultiply = rotateMultiply->getFloat();

    ofPushMatrix();
    
    if (adjustPosToSceneCentre) {
        holdDrawPosX += model.getSceneCenter().x;
        holdDrawPosY += model.getSceneCenter().y;
        holdDrawPosZ += model.getSceneCenter().z;
    };

    // NB USE THIS TO ADJUST POSITION
    model.getSceneCenter();  // WHIC IS A ofPoint
    
    model.setPosition(holdDrawPosX, holdDrawPosY, holdDrawPosZ);
    model.setScale(holdScaleX,  holdScaleY,  holdScaleZ);
    model.setRotation(0, holdRotateMultiply * rotateX->getFloat(), 1, 0, 0);
    model.setRotation(1, holdRotateMultiply * rotateY->getFloat(), 0, 1, 0);
    model.setRotation(2, holdRotateMultiply * rotateZ->getFloat(), 0, 0, 1);
    
    if (createLightsFromModel->getBool()) {
        model.createLightsFromAiModel();
    }
    model.drawFaces();
    
    ofPopMatrix();
}

bool TXDraw3DModel::loadModel() {
    ofPtr <TXAsset> asset;
    string fileName;
    int modelAssetID = get3DModelAssetIDSlot("modelAsset").first;
    if (modelHasLoaded) {
        model.stopAllAnimations();
        modelHasLoaded = false;
    };
    if (modelAssetID != 0) {
        asset = parentSystem->getAsset(TXASSETTYPE_3DMODEL, modelAssetID);
        fileName = asset->getFileName();
        
        if (model.loadModel(fileName)) {
            modelHasLoaded = true;
            model.setLoopStateForAllAnimations((ofLoopType) loopType->getInt());
            model.setScaleNormalization(true);
            model.setNormalizationFactor(1);
            if (play->getBool()) {
                model.playAllAnimations();
                if(pause->getBool()) {
                    model.setPausedForAllAnimations(true);
                };
            };
            
            ofLogNotice() << "TXDraw3DModel::loadModel - model HasLoaded:" << fileName;
        } else {
            model.createEmptyModel();
            ofLogNotice() << "TXDraw3DModel::loadModel - model failed to Load: " << fileName;
        };
    };
    return modelHasLoaded;
}

bool TXDraw3DModel::getModelHasLoaded() {
    return modelHasLoaded;
}

void  TXDraw3DModel::a3DModelAssetSlotChanged(string slotNameArg) {
    loadModel();
}

void TXDraw3DModel::loopTypeHasChanged(ofAbstractParameter & parameterArg ) {
    loopTypeChanged = true;
}

