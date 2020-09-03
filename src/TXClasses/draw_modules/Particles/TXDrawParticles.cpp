/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXDrawParticles.h"
#include "TXSystem.h"
#include "TXFunctions.h"
#include "ofxTweenLite.h"

// constructor
TXDrawParticles::TXDrawParticles(){
    setup();
};

// destructor
TXDrawParticles::~TXDrawParticles() {
    // remove listeners to relevent parameters:
    ofRemoveListener(triggerLevel->parameters.parameterChangedE(),this,&TXDrawParticles::triggerLevelChanged);
    ofRemoveListener(triggerNow->parameters.parameterChangedE(),this,&TXDrawParticles::triggerNowChanged);
    ofRemoveListener(killAllNow->parameters.parameterChangedE(),this,&TXDrawParticles::killAllNowChanged);
    ofRemoveListener(tintHue->parameters.parameterChangedE(),this,&TXDrawParticles::tintHueChanged);
    ofRemoveListener(tintHueRotate->parameters.parameterChangedE(),this,&TXDrawParticles::tintHueRotateChanged);
    ofRemoveListener(tintSaturation->parameters.parameterChangedE(),this,&TXDrawParticles::tintSaturationChanged);
    ofRemoveListener(tintBrightness->parameters.parameterChangedE(),this,&TXDrawParticles::tintBrightnessChanged);
    ofRemoveListener(tintHSBAsRGB->parameters.parameterChangedE(),this,&TXDrawParticles::tintHSBAsRGBChanged);
}

void TXDrawParticles::setup () {
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
    
    // images
    holdModParamIntArgs.name = "sourceImageScaleMode";
    holdModParamIntArgs.fixedValue = TXIMAGESCALEMODE_SCALETOFIT;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 2;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 2;
	sourceImageScaleMode = createModParameter(holdModParamIntArgs);
    parameters.add(sourceImageScaleMode->parameters);
    
    parameters.add(useExternalSourceImage.set("useExternalSourceImage", false));
    parameters.add(useExternalMaskImage.set("useExternalMaskImage", false));
    
    holdModParamIntArgs.name = "maskType";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXMASKTYPE_FEATHEREDDIAMOND;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXMASKTYPE_FEATHEREDDIAMOND;
	maskType = createModParameter(holdModParamIntArgs);
    parameters.add(maskType->parameters);
    
    parameters.add(invertMask.set("invertMask", false));

    holdModParamFloatArgs.name = "feathering";
    holdModParamFloatArgs.fixedValue = 0.2;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    feathering = createModParameter(holdModParamFloatArgs);
    parameters.add(feathering->parameters);
    
    holdModParamBoolArgs.name = "useCentralColourOnly";
    holdModParamBoolArgs.fixedValue = true;
    useCentralColourOnly = createModParameter(holdModParamBoolArgs);
    parameters.add(useCentralColourOnly->parameters);
    
    holdModParamBoolArgs.name = "lockColourAtStart";
    holdModParamBoolArgs.fixedValue = false;
    lockColourAtStart = createModParameter(holdModParamBoolArgs);
    parameters.add(lockColourAtStart->parameters);
    
    holdModParamBoolArgs.name = "lockAlphaScaleAtStart";
    holdModParamBoolArgs.fixedValue = false;
    lockAlphaScaleAtStart = createModParameter(holdModParamBoolArgs);
    parameters.add(lockAlphaScaleAtStart->parameters);
    
    holdModParamBoolArgs.name = "lockWidthAtStart";
    holdModParamBoolArgs.fixedValue = false;
    lockWidthAtStart = createModParameter(holdModParamBoolArgs);
    parameters.add(lockWidthAtStart->parameters);
    
    holdModParamBoolArgs.name = "lockHeightAtStart";
    holdModParamBoolArgs.fixedValue = false;
    lockHeightAtStart = createModParameter(holdModParamBoolArgs);
    parameters.add(lockHeightAtStart->parameters);
    
    holdModParamBoolArgs.name = "lockSpreadAtStart";
    holdModParamBoolArgs.fixedValue = false;
    lockSpreadAtStart = createModParameter(holdModParamBoolArgs);
    parameters.add(lockSpreadAtStart->parameters);
    
    holdModParamBoolArgs.name = "lockScaleAtStart";
    holdModParamBoolArgs.fixedValue = false;
    lockScaleAtStart = createModParameter(holdModParamBoolArgs);
    parameters.add(lockScaleAtStart->parameters);
    
    holdModParamBoolArgs.name = "lockAnchorAtStart";
    holdModParamBoolArgs.fixedValue = false;
    lockAnchorAtStart = createModParameter(holdModParamBoolArgs);
    parameters.add(lockAnchorAtStart->parameters);
    
    holdModParamBoolArgs.name = "lockRotationOffsetAtStart";
    holdModParamBoolArgs.fixedValue = false;
    lockRotationOffsetAtStart = createModParameter(holdModParamBoolArgs);
    parameters.add(lockRotationOffsetAtStart->parameters);
    
    holdModParamBoolArgs.name = "lockSamplePositionAtStart";
    holdModParamBoolArgs.fixedValue = false;
    lockSamplePositionAtStart = createModParameter(holdModParamBoolArgs);
    parameters.add(lockSamplePositionAtStart->parameters);
    
    holdModParamBoolArgs.name = "lockDanceWidthHeightAtStart";
    holdModParamBoolArgs.fixedValue = false;
    lockDanceWidthHeightAtStart = createModParameter(holdModParamBoolArgs);
    parameters.add(lockDanceWidthHeightAtStart->parameters);
    
    holdModParamBoolArgs.name = "lockAttractionPointAtStart";
    holdModParamBoolArgs.fixedValue = false;
    lockAttractionPointAtStart = createModParameter(holdModParamBoolArgs);
    parameters.add(lockAttractionPointAtStart->parameters);
    
    holdModParamBoolArgs.name = "lockTintAtStart";
    holdModParamBoolArgs.fixedValue = false;
    lockTintAtStart = createModParameter(holdModParamBoolArgs);
    parameters.add(lockTintAtStart->parameters);
    
    holdModParamBoolArgs.name = "triggerContinuosly";
    holdModParamBoolArgs.fixedValue = true;
    triggerContinuosly = createModParameter(holdModParamBoolArgs);
    parameters.add(triggerContinuosly->parameters);
    
    holdModParamBoolArgs.name = "triggerNow";
    holdModParamBoolArgs.fixedValue = false;
    triggerNow = createModParameter(holdModParamBoolArgs);
    parameters.add(triggerNow->parameters);
    
    holdModParamBoolArgs.name = "killAllNow";
    holdModParamBoolArgs.fixedValue = false;
    killAllNow = createModParameter(holdModParamBoolArgs);
    parameters.add(killAllNow->parameters);
    
    holdModParamIntArgs.name = "numParticlesPerTrigger";
    holdModParamIntArgs.fixedValue = 8;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 100;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 10;
	numParticlesPerTrigger = createModParameter(holdModParamIntArgs);
    parameters.add(numParticlesPerTrigger->parameters);
   
    parameters.add(maximumActiveParticles.set("maximumActiveParticles", 200, 2, totalNoParticles));
    
    holdModParamFloatArgs.name = "bpm";
    holdModParamFloatArgs.fixedValue = 120.0;
    holdModParamFloatArgs.hardMin = 0.001;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 0.1;
    holdModParamFloatArgs.softMax = 200.0;
    bpm = createModParameter(holdModParamFloatArgs);
    parameters.add(bpm->parameters);
    
    holdModParamBoolArgs.name = "useMasterBpm";
    holdModParamBoolArgs.fixedValue = true;
    useMasterBpm = createModParameter(holdModParamBoolArgs);
    parameters.add(useMasterBpm->parameters);
    
    holdModParamFloatArgs.name = "stepTimeBeats";
    holdModParamFloatArgs.fixedValue = 4.0;
    holdModParamFloatArgs.hardMin = 1.0;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 1.0;
    holdModParamFloatArgs.softMax = 64.0;
    stepTimeBeats = createModParameter(holdModParamFloatArgs);
    parameters.add(stepTimeBeats->parameters);
    
    holdModParamFloatArgs.name = "stepTimeDivisor";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 1.0;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 1.0;
    holdModParamFloatArgs.softMax = 64.0;
    stepTimeDivisor = createModParameter(holdModParamFloatArgs);
    parameters.add(stepTimeDivisor->parameters);
    
    holdModParamFloatArgs.name = "triggerLevel";
    holdModParamFloatArgs.fixedModMix = 1.0;  // set to 1 by default
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    triggerLevel = createModParameter(holdModParamFloatArgs);
    parameters.add(triggerLevel->parameters);

    // set back to default val
    holdModParamFloatArgs.fixedModMix = 0.0;

    holdModParamFloatArgs.name = "triggerThreshold";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    triggerThreshold = createModParameter(holdModParamFloatArgs);
    parameters.add(triggerThreshold->parameters);
    
    holdModParamFloatArgs.name = "triggerProbability";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    triggerProbability = createModParameter(holdModParamFloatArgs);
    parameters.add(triggerProbability->parameters);
    
    holdModParamFloatArgs.name = "triggerDelaySpread";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    triggerDelaySpread = createModParameter(holdModParamFloatArgs);
    parameters.add(triggerDelaySpread->parameters);
    
    holdModParamIntArgs.name = "triggerDelayDistribution";
    holdModParamIntArgs.fixedValue = 11;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = numDistributionTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = numDistributionTypes - 1;
	triggerDelayDistribution = createModParameter(holdModParamIntArgs);
    parameters.add(triggerDelayDistribution->parameters);
    
    holdModParamFloatArgs.name = "triggerDelayRandom";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    triggerDelayRandom = createModParameter(holdModParamFloatArgs);
    parameters.add(triggerDelayRandom->parameters);
    
    holdModParamFloatArgs.name = "lifetimeBeats";
    holdModParamFloatArgs.fixedValue = 8.0;
    holdModParamFloatArgs.hardMin = 0.01;
    holdModParamFloatArgs.hardMax = 128.0;
    holdModParamFloatArgs.softMin = 0.01;
    holdModParamFloatArgs.softMax = 32.0;
    lifetimeBeats = createModParameter(holdModParamFloatArgs);
    parameters.add(lifetimeBeats->parameters);
    
    holdModParamFloatArgs.name = "lifetimeRandomVariation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    lifetimeRandomVariation = createModParameter(holdModParamFloatArgs);
    parameters.add(lifetimeRandomVariation->parameters);
    
    holdModParamBoolArgs.name = "useTriggerTimeForLifetime";
    holdModParamBoolArgs.fixedValue = false;
    useTriggerTimeForLifetime = createModParameter(holdModParamBoolArgs);
    parameters.add(useTriggerTimeForLifetime->parameters);
    
    // spreadType: ["Circle", "Horizontal Line", "Vertical Line", "Diagonal Line"]
    holdModParamIntArgs.name = "spreadType";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 3;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 3;
	spreadType = createModParameter(holdModParamIntArgs);
    parameters.add(spreadType->parameters);
    
    holdModParamIntArgs.name = "spreadDistribution";
    holdModParamIntArgs.fixedValue = 9;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = numDistributionTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = numDistributionTypes - 1;
	spreadDistribution = createModParameter(holdModParamIntArgs);
    parameters.add(spreadDistribution->parameters);
    
    holdModParamFloatArgs.name = "spreadCenterX";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    spreadCenterX = createModParameter(holdModParamFloatArgs);
    parameters.add(spreadCenterX->parameters);
    
    holdModParamFloatArgs.name = "spreadCenterY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    spreadCenterY = createModParameter(holdModParamFloatArgs);
    parameters.add(spreadCenterY->parameters);
    
    holdModParamFloatArgs.name = "spreadWidth";
    holdModParamFloatArgs.fixedValue = 0.3;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    spreadWidth = createModParameter(holdModParamFloatArgs);
    parameters.add(spreadWidth->parameters);
    
    holdModParamFloatArgs.name = "spreadHeight";
    holdModParamFloatArgs.fixedValue = 0.3;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    spreadHeight = createModParameter(holdModParamFloatArgs);
    parameters.add(spreadHeight->parameters);
    
    holdModParamFloatArgs.name = "spreadRotation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
    spreadRotation = createModParameter(holdModParamFloatArgs);
    parameters.add(spreadRotation->parameters);
    
    holdModParamFloatArgs.name = "spreadRandom";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    spreadRandom = createModParameter(holdModParamFloatArgs);
    parameters.add(spreadRandom->parameters);
    
    holdModParamFloatArgs.name = "posXPerlinMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    posXPerlinMix = createModParameter(holdModParamFloatArgs);
    parameters.add(posXPerlinMix->parameters);
    
    holdModParamFloatArgs.name = "posYPerlinMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    posYPerlinMix = createModParameter(holdModParamFloatArgs);
    parameters.add(posYPerlinMix->parameters);
    
    holdModParamFloatArgs.name = "posXPerlinSpeed";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
    posXPerlinSpeed = createModParameter(holdModParamFloatArgs);
    parameters.add(posXPerlinSpeed->parameters);
    
    holdModParamFloatArgs.name = "posYPerlinSpeed";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
    posYPerlinSpeed = createModParameter(holdModParamFloatArgs);
    parameters.add(posYPerlinSpeed->parameters);
    
    holdModParamFloatArgs.name = "gravityX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
    gravityX = createModParameter(holdModParamFloatArgs);
    parameters.add(gravityX->parameters);
    
    holdModParamFloatArgs.name = "gravityY";
    holdModParamFloatArgs.fixedValue = 0.05;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
    gravityY = createModParameter(holdModParamFloatArgs);
    parameters.add(gravityY->parameters);
    
    holdModParamFloatArgs.name = "velocityX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
    velocityX = createModParameter(holdModParamFloatArgs);
    parameters.add(velocityX->parameters);
    
    holdModParamFloatArgs.name = "velocityY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
    velocityY = createModParameter(holdModParamFloatArgs);
    parameters.add(velocityY->parameters);
    
    holdModParamFloatArgs.name = "attraction";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
    attraction = createModParameter(holdModParamFloatArgs);
    parameters.add(attraction->parameters);
    
    attractionCurve.setValueArrayToRamp(0, 1);
    attractionCurve.setName("attractionCurve");
    parameters.add(attractionCurve.parameters);
    
    holdModParamFloatArgs.name = "attractionPointX";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -1.0;
    holdModParamFloatArgs.hardMax = 2.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    attractionPointX = createModParameter(holdModParamFloatArgs);
    parameters.add(attractionPointX->parameters);
    
    holdModParamFloatArgs.name = "attractionPointY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -1.0;
    holdModParamFloatArgs.hardMax = 2.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    attractionPointY = createModParameter(holdModParamFloatArgs);
    parameters.add(attractionPointY->parameters);
    
    holdModParamBoolArgs.name = "useWidthForHeight";
    holdModParamBoolArgs.fixedValue = false;
    useWidthForHeight = createModParameter(holdModParamBoolArgs);
    parameters.add(useWidthForHeight->parameters);
    
    holdModParamFloatArgs.name = "width";
    holdModParamFloatArgs.fixedValue = 0.2;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    width = createModParameter(holdModParamFloatArgs);
    parameters.add(width->parameters);
    
    widthCurve.setValueArrayTo(1.0f);
    widthCurve.setName("widthCurve");
    parameters.add(widthCurve.parameters);
    
    holdModParamFloatArgs.name = "widthPerlinMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    widthPerlinMix = createModParameter(holdModParamFloatArgs);
    parameters.add(widthPerlinMix->parameters);
    
    holdModParamFloatArgs.name = "widthPerlinSpeed";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
    widthPerlinSpeed = createModParameter(holdModParamFloatArgs);
    parameters.add(widthPerlinSpeed->parameters);
    
    holdModParamFloatArgs.name = "height";
    holdModParamFloatArgs.fixedValue = 0.2;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    height = createModParameter(holdModParamFloatArgs);
    parameters.add(height->parameters);
    
    heightCurve.setValueArrayTo(1.0f);
    heightCurve.setName("heightCurve");
    parameters.add(heightCurve.parameters);
    
    holdModParamFloatArgs.name = "heightPerlinMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    heightPerlinMix = createModParameter(holdModParamFloatArgs);
    parameters.add(heightPerlinMix->parameters);
    
    holdModParamFloatArgs.name = "heightPerlinSpeed";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
    heightPerlinSpeed = createModParameter(holdModParamFloatArgs);
    parameters.add(heightPerlinSpeed->parameters);
    
    holdModParamBoolArgs.name = "useScaleXForScaleY";
    holdModParamBoolArgs.fixedValue = false;
    useScaleXForScaleY = createModParameter(holdModParamBoolArgs);
    parameters.add(useScaleXForScaleY->parameters);
    
    holdModParamFloatArgs.name = "scaleX";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 2.0;
    scaleX = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleX->parameters);
    
    scaleXCurve.setValueArrayTo(1.0f);
    scaleXCurve.setName("scaleXCurve");
    parameters.add(scaleXCurve.parameters);
    
    holdModParamFloatArgs.name = "scaleY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 2.0;
    scaleY = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleY->parameters);
    
    scaleYCurve.setValueArrayTo(1.0f);
    scaleYCurve.setName("scaleYCurve");
    parameters.add(scaleYCurve.parameters);
    
    holdModParamFloatArgs.name = "alphaScale";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    alphaScale = createModParameter(holdModParamFloatArgs);
    parameters.add(alphaScale->parameters);
    
    alphaCurve.setValueArrayTo(1.0f);
    alphaCurve.setName("alphaCurve");
    parameters.add(alphaCurve.parameters);
    
    holdModParamFloatArgs.name = "alphaPerlinMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    alphaPerlinMix = createModParameter(holdModParamFloatArgs);
    parameters.add(alphaPerlinMix->parameters);
    
    holdModParamFloatArgs.name = "alphaPerlinSpeed";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
    alphaPerlinSpeed = createModParameter(holdModParamFloatArgs);
    parameters.add(alphaPerlinSpeed->parameters);
    
    holdModParamFloatArgs.name = "tintMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    tintMix = createModParameter(holdModParamFloatArgs);
    parameters.add(tintMix->parameters);
    
    holdModParamFloatArgs.name = "tintHue";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    tintHue = createModParameter(holdModParamFloatArgs);
    parameters.add(tintHue->parameters);
    
    holdModParamFloatArgs.name = "tintHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    tintHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(tintHueRotate->parameters);
    
    holdModParamBoolArgs.name = "tintHSBAsRGB";
    holdModParamBoolArgs.fixedValue = true;
    tintHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(tintHSBAsRGB->parameters);

    holdModParamFloatArgs.name = "tintSaturation";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    tintSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(tintSaturation->parameters);
    
    holdModParamFloatArgs.name = "tintBrightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    tintBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(tintBrightness->parameters);
    
    holdModParamFloatArgs.name = "anchorX";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    anchorX = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorX->parameters);
    
    anchorXCurve.setValueArrayTo(1.0f);
    anchorXCurve.setName("anchorXCurve");
    parameters.add(anchorXCurve.parameters);
    
    holdModParamFloatArgs.name = "anchorY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    anchorY = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorY->parameters);
    
    anchorYCurve.setValueArrayTo(1.0f);
    anchorYCurve.setName("anchorYCurve");
    parameters.add(anchorYCurve.parameters);
    
    
    holdModParamFloatArgs.name = "rotationOffset";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
    rotationOffset = createModParameter(holdModParamFloatArgs);
    parameters.add(rotationOffset->parameters);
    
    rotationCurve.setValueArrayTo(1.0f);
    rotationCurve.setName("rotationCurve");
    parameters.add(rotationCurve.parameters);
    
    holdModParamFloatArgs.name = "rotationPerlinMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    rotationPerlinMix = createModParameter(holdModParamFloatArgs);
    parameters.add(rotationPerlinMix->parameters);
    
    holdModParamFloatArgs.name = "rotationPerlinSpeed";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
    rotationPerlinSpeed = createModParameter(holdModParamFloatArgs);
    parameters.add(rotationPerlinSpeed->parameters);
    
    holdModParamBoolArgs.name = "useParticlePosForSamplePos";
    holdModParamBoolArgs.fixedValue = true;
    useParticlePosForSamplePos = createModParameter(holdModParamBoolArgs);
    parameters.add(useParticlePosForSamplePos->parameters);
    
    holdModParamFloatArgs.name = "samplePosX";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    samplePosX = createModParameter(holdModParamFloatArgs);
    parameters.add(samplePosX->parameters);
    
    holdModParamFloatArgs.name = "samplePosY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    samplePosY = createModParameter(holdModParamFloatArgs);
    parameters.add(samplePosY->parameters);
    
    holdModParamBoolArgs.name = "wavesHorizontalOn";
    holdModParamBoolArgs.fixedValue = false;
    wavesHorizontalOn = createModParameter(holdModParamBoolArgs);
    parameters.add(wavesHorizontalOn->parameters);
    
    holdModParamBoolArgs.name = "wavesVerticalOn";
    holdModParamBoolArgs.fixedValue = false;
    wavesVerticalOn = createModParameter(holdModParamBoolArgs);
    parameters.add(wavesVerticalOn->parameters);
    
    holdModParamBoolArgs.name = "wavesQuantised";
    holdModParamBoolArgs.fixedValue = false;
    wavesQuantised = createModParameter(holdModParamBoolArgs);
    parameters.add(wavesQuantised->parameters);
    
    holdModParamFloatArgs.name = "numWavesX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 5.0;
    numWavesX = createModParameter(holdModParamFloatArgs);
    parameters.add(numWavesX->parameters);
    
    holdModParamFloatArgs.name = "numWavesY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 5.0;
    numWavesY = createModParameter(holdModParamFloatArgs);
    parameters.add(numWavesY->parameters);
    
    holdModParamBoolArgs.name = "bendOn";
    holdModParamBoolArgs.fixedValue = false;
    bendOn = createModParameter(holdModParamBoolArgs);
    parameters.add(bendOn->parameters);
    
    holdModParamFloatArgs.name = "bendRandomPhaseX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    bendRandomPhaseX = createModParameter(holdModParamFloatArgs);
    parameters.add(bendRandomPhaseX->parameters);
    
    holdModParamFloatArgs.name = "bendRandomPhaseY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    bendRandomPhaseY = createModParameter(holdModParamFloatArgs);
    parameters.add(bendRandomPhaseY->parameters);
    
    holdModParamFloatArgs.name = "bendPhaseX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    bendPhaseX = createModParameter(holdModParamFloatArgs);
    parameters.add(bendPhaseX->parameters);
    
    holdModParamFloatArgs.name = "bendPhaseY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    bendPhaseY = createModParameter(holdModParamFloatArgs);
    parameters.add(bendPhaseY->parameters);
    
    holdModParamFloatArgs.name = "bendDepthX";
    holdModParamFloatArgs.fixedValue = 0.2;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 4.0;
    bendDepthX = createModParameter(holdModParamFloatArgs);
    parameters.add(bendDepthX->parameters);
    
    holdModParamFloatArgs.name = "bendDepthY";
    holdModParamFloatArgs.fixedValue = 0.2;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 4.0;
    bendDepthY = createModParameter(holdModParamFloatArgs);
    parameters.add(bendDepthY->parameters);
    
    holdModParamFloatArgs.name = "bendZoom";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
    bendZoom = createModParameter(holdModParamFloatArgs);
    parameters.add(bendZoom->parameters);
   
    holdModParamFloatArgs.name = "dance_width";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    dance_width = createModParameter(holdModParamFloatArgs);
    parameters.add(dance_width->parameters);
    
    holdModParamFloatArgs.name = "dance_height";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    dance_height = createModParameter(holdModParamFloatArgs);
    parameters.add(dance_height->parameters);
    
    // create dance pattern LFO & merge parameters
    dancePattern.setup("dance_");
    mergeParameters(dancePattern.parameters, dancePattern.modParameters);
    
    holdModParamBoolArgs.name = "dance_randomStartPhase";
    holdModParamBoolArgs.fixedValue = false;
    dance_randomStartPhase = createModParameter(holdModParamBoolArgs);
    parameters.add(dance_randomStartPhase->parameters);
    
    // add listeners to relevent parameters:
    ofAddListener(triggerLevel->parameters.parameterChangedE(),this,&TXDrawParticles::triggerLevelChanged);
    ofAddListener(triggerNow->parameters.parameterChangedE(),this,&TXDrawParticles::triggerNowChanged);
    ofAddListener(killAllNow->parameters.parameterChangedE(),this,&TXDrawParticles::killAllNowChanged);
    ofAddListener(tintHue->parameters.parameterChangedE(),this,&TXDrawParticles::tintHueChanged);
    ofAddListener(tintHueRotate->parameters.parameterChangedE(),this,&TXDrawParticles::tintHueRotateChanged);
    ofAddListener(tintSaturation->parameters.parameterChangedE(),this,&TXDrawParticles::tintSaturationChanged);
    ofAddListener(tintBrightness->parameters.parameterChangedE(),this,&TXDrawParticles::tintBrightnessChanged);
    ofAddListener(tintHSBAsRGB->parameters.parameterChangedE(),this,&TXDrawParticles::tintHSBAsRGBChanged);

    // asset slots
    createImageAssetSlot("sourceImageAsset");
    createImageAssetSlot("maskImageAsset");
    
    // external image slots
    createExtImageModuleSlot("extSourceImageModule");
    createExtImageModuleSlot("extMaskImageModule");
    
    sourceImageHasLoaded = false;
    maskImageHasLoaded = false;
    
    // set up drawMesh
    drawMesh.clear();
    drawMesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    // top left
    drawMesh.addTexCoord(ofVec2f(0, 0));
    drawMesh.addVertex(ofVec3f(0, 0, 0));
    drawMesh.addColor(ofFloatColor(1, 1, 1, 1));
    drawMesh.addNormal(ofVec3f(0, 0, 0));
    // top right
    drawMesh.addTexCoord(ofVec2f(0, 0));
    drawMesh.addVertex(ofVec3f(0, 0, 0));
    drawMesh.addColor(ofFloatColor(1, 1, 1, 1));
    drawMesh.addNormal(ofVec3f(0, 0, 0));
    // bottom right
    drawMesh.addTexCoord(ofVec2f(0, 1));
    drawMesh.addVertex(ofVec3f(0, 1, 0));
    drawMesh.addColor(ofFloatColor(1, 1, 1, 1));
    drawMesh.addNormal(ofVec3f(0, 0, 0));
    // bottom left
    drawMesh.addTexCoord(ofVec2f(0, 1));
    drawMesh.addVertex(ofVec3f(0, 1, 0));
    drawMesh.addColor(ofFloatColor(1, 1, 1, 1));
    drawMesh.addNormal(ofVec3f(0, 0, 0));
    
    // load shaders
#ifdef TARGET_OPENGLES
	particleShader.load("shadersES2/ParticleShader.vert","shadersES2/ParticleShader.frag");
    particleShaderWithMask.load("shadersES2/ParticleMaskShader.vert","shadersES2/ParticleMaskShader.frag");
    particleShaderWithMaskTex.load("shadersES2/ParticleMaskShader.vert","shadersES2/ParticleMaskTexShader.frag");
#else
	if(ofIsGLProgrammableRenderer()){
		particleShader.load("shadersGL3/ParticleShader.vert", "shadersGL3/ParticleShader.frag");
        particleShaderWithMask.load("shadersGL3/ParticleShader.vert","shadersGL3/ParticleMaskShader.frag");
        particleShaderWithMaskTex.load("shadersGL3/ParticleShader.vert","shadersGL3/ParticleMaskTexShader.frag");
    }else{
		particleShader.load("shadersGL2/ParticleShader.vert", "shadersGL2/ParticleShader.frag");
        particleShaderWithMask.load("shadersGL2/ParticleShader.vert","shadersGL2/ParticleMaskShader.frag");
        particleShaderWithMaskTex.load("shadersGL2/ParticleShader.vert","shadersGL2/ParticleMaskTexShader.frag");
	}
#endif
    
    // register Texture
    registerTexture();

    // initialise
    greyImage.allocate(20, 20, OF_IMAGE_COLOR);
    greyImage.setColor(ofColor(128));
    nextParticleIndex = 0;
    for (int i = 0; i < totalNoParticles; i++) {
        arrParticles[i].particleID = i;
    };    
    
    dancePattern.lfoType->setFixedValue(1);
    dancePattern.cycleTimeBeats->setFixedValue(4);
    
    lastRecordedTriggerTime = 0;
    triggerConfirmed = false;
    triggerNowPrevious = false;
    killAllNowPrevious = false;
    resetTime();
    advanceBy(0);
    loadSourceImage();
    
};  // end of setup ()

void TXDrawParticles::update(){
    dancePattern.update();
//    for (int i = 0; i < totalNoParticles; i++) {
//        arrParticles[i].dancePattern.update();
//    };
    if (triggerConfirmed || triggerContinuosly->getBool()) {
        triggerParticles();
    };
}

void TXDrawParticles::draw() {
    float holdHeight, holdScaleY, textureX, textureY;
    float holdPhaseX, holdPhaseY;
    float holdTintMix, holdTintR, holdTintG, holdTintB;
    float sourceImageWidth;
    float sourceImageHeight;
    float maskImageWidth;
    float maskImageHeight;
    int holdSourceID;
    int holdMaskID;
    int holdMaskType;
    float colourDiv = (float) 1/255;
    
    // check before drawing
    if (!drawActive->getBool()) {
        return;
    };
    holdMaskType = maskType->getInt();
    if (holdMaskType == 1) {
        if (!useExternalMaskImage) {
            if (!maskImageHasLoaded) {
                return;
            };
        };
    };
    //  choose shader
    if (holdMaskType == 0) {
        holdShader = & particleShader;
    } else if (holdMaskType == 1) {
        holdShader = & particleShaderWithMaskTex;
    } else {
        holdShader = & particleShaderWithMask;
    };
    holdShader->begin();
    
     if (!useExternalSourceImage) {
        if (!sourceImageHasLoaded) {
            return;
        };
    };
    if (useExternalSourceImage) {
        holdSourceID = getExtImageModuleIDSlot("extSourceImageModule");
        if (!parentSystem->isValidModuleID(holdSourceID)) {
            return;
        };
        if (parentSystem->allModules[holdSourceID]->getTexture() == NULL) {
            return;
        };
        sourceImageWidth = parentSystem->allModules[holdSourceID]->getTextureWidth();
        sourceImageHeight = parentSystem->allModules[holdSourceID]->getTextureHeight();
    } else {
        sourceImageWidth = sourceImage.getWidth();
        sourceImageHeight = sourceImage.getHeight();
    };
    if ((holdMaskType == 1) && useExternalMaskImage) {
        holdMaskID = getExtImageModuleIDSlot("extMaskImageModule");
        // check for valid module & texture
        if (parentSystem->allModules[holdMaskID] == NULL) {
            return;
        };
        if (parentSystem->allModules[holdMaskID]->getTexture() == NULL) {
            return;
        };
        maskImageWidth = parentSystem->allModules[holdMaskID]->getTextureWidth();
        maskImageHeight = parentSystem->allModules[holdMaskID]->getTextureHeight();
    } else {
        maskImageWidth = maskImage.getWidth();
        maskImageHeight = maskImage.getHeight();
    };

    // set textures
    //ofSetTextureWrap(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
    
    if (useExternalSourceImage) {
        ofTexture * sourceTex = parentSystem->allModules[holdSourceID]->getTexture();
        holdShader->setUniformTexture("u_texture0Sampler", * sourceTex, 0);
    } else {
        holdShader->setUniformTexture("u_texture0Sampler", sourceImage.getTexture(), 0);
    };
    if (holdMaskType > 0) {
        if (holdMaskType == 1) {
            if (useExternalMaskImage) {
                ofTexture * maskTex = parentSystem->allModules[holdMaskID]->getTexture();
                holdShader->setUniformTexture("u_texture1Sampler", * maskTex, 1);
            } else {
                holdShader->setUniformTexture("u_texture1Sampler", maskImage.getTexture(), 1);
            };
        } else {
            holdShader->setUniform1f("u_feathering", feathering->getFloat());
        };
    };
    holdShader->setUniform1i("u_maskType", holdMaskType);
    holdShader->setUniform1i("u_invertMask", (int) invertMask);
    holdShader->setUniform1f("u_alphaThreshold", parentSystem->alphaThreshold);
    holdShader->setUniform1i("u_useCenterPixel", (int) useCentralColourOnly->getBool());

    // adjust variables for shader maths:
    holdShader->setUniform1i("u_bendOn", (int) bendOn->getBool());
    //    holdShader->setUniform1f("u_numBendsX", pow(numBendsX, 3));
    //    holdShader->setUniform1f("u_numBendsY", pow(numBendsY, 3));
    holdShader->setUniform1f("u_bendDepthX", pow(1 + bendDepthX->getFloat(), 2));
    holdShader->setUniform1f("u_bendDepthY", pow(1 + bendDepthY->getFloat(), 2) );
    holdShader->setUniform1f("u_bendZoom", bendZoom->getFloat());
    holdShader->setUniform1f("u_numWavesX", numWavesX->getFloat());
    holdShader->setUniform1f("u_numWavesY", numWavesY->getFloat());
    holdShader->setUniform1i("u_wavesHorizontalOn", (int) wavesHorizontalOn->getBool());
    holdShader->setUniform1i("u_wavesVerticalOn", (int) wavesVerticalOn->getBool());
    holdShader->setUniform1i("u_wavesQuantised", (int) wavesQuantised->getBool());
    
    bool holdLockColourAtStart = lockColourAtStart->getBool();
    bool holdUseParticlePosForSamplePos = useParticlePosForSamplePos->getBool();
    bool holdUseWidthForHeight = useWidthForHeight->getBool();
    bool holdUseScaleXForScaleY = useScaleXForScaleY->getBool();
    bool holdLockTintAtStart = lockTintAtStart->getBool();
    
    ofEnableAlphaBlending();
    // draw particles
    for (int i = 0; i < maximumActiveParticles; i++) {
        if (arrParticles[i].awake) {
            holdPhaseX = bendPhaseX->getFloat() + (bendRandomPhaseX->getFloat() * arrParticles[i].spreadRandX);
            holdPhaseY = bendPhaseY->getFloat() + (bendRandomPhaseY->getFloat() * arrParticles[i].spreadRandX); // n.b. use spreadRandX for both to retain relative x/y phase
            holdShader->setUniform1f("u_phaseX", holdPhaseX * 2 * PI);
            holdShader->setUniform1f("u_phaseY", holdPhaseY * 2 * PI);
            if (holdLockColourAtStart) {
                if (holdUseParticlePosForSamplePos) {
                    textureX = arrParticles[i].initialSpreadCenterX + (arrParticles[i].initialSpreadWidth * arrParticles[i].spreadOffsetX);
                    textureY = arrParticles[i].initialSpreadCenterY + (arrParticles[i].initialSpreadHeight * arrParticles[i].spreadOffsetY);
                    // textureX = arrParticles[i].initialPosX;
                    //  textureY = arrParticles[i].initialPosY;
                } else {
                    textureX = arrParticles[i].initialSamplePositionX + (arrParticles[i].initialSpreadWidth * arrParticles[i].spreadOffsetX);
                    textureY = arrParticles[i].initialSamplePositionY + (arrParticles[i].initialSpreadHeight * arrParticles[i].spreadOffsetY);
                };
            } else {
                if (holdUseParticlePosForSamplePos) {
                    textureX = arrParticles[i].posX;
                    textureY = arrParticles[i].posY;
                } else {
                    textureX = arrParticles[i].samplePosX + (spreadWidth->getFloat() * arrParticles[i].spreadOffsetX);
                    textureY = arrParticles[i].samplePosY + (spreadHeight->getFloat() * arrParticles[i].spreadOffsetY);
                };
            };
            if (holdUseWidthForHeight) {
                holdHeight = arrParticles[i].width;
            } else {
                holdHeight = arrParticles[i].height;
            };
            if (holdUseScaleXForScaleY) {
                holdScaleY = arrParticles[i].scaleX;
            } else {
                holdScaleY = arrParticles[i].scaleY;
            };
            if (holdLockTintAtStart) {
                holdTintMix = arrParticles[i].initialTintMix;
                holdTintR = arrParticles[i].initialTintR;
                holdTintG = arrParticles[i].initialTintG;
                holdTintB = arrParticles[i].initialTintB;
            } else {
                holdTintMix = tintMix->getFloat();
                holdTintR = tint.r;
                holdTintG = tint.g;
                holdTintB = tint.b;
            };
            int holdSourceImageScaleMode = sourceImageScaleMode->getInt();
            float holdAlpha = arrParticles[i].alpha * alphaScale->getFloat();
            
            float holdAnchorX = anchorX->getFloat();
            float holdAnchorY = anchorY->getFloat();
            float holdR = holdTintR * colourDiv;
            float holdG = holdTintG * colourDiv;
            float holdB = holdTintB * colourDiv;
            drawParticle(arrParticles[i].posX, arrParticles[i].posY, textureX, textureY, arrParticles[i].width, holdHeight, holdAlpha, arrParticles[i].anchorX, arrParticles[i].anchorY, arrParticles[i].rotation, arrParticles[i].scaleX, holdScaleY, holdTintMix, holdR, holdG, holdB, sourceImageWidth, sourceImageHeight, maskImageWidth, maskImageHeight, holdMaskType, holdSourceImageScaleMode);
        };
    };
    ofDisableAlphaBlending();
//    ofRestoreTextureWrap();
    holdShader->end();
}

void TXDrawParticles::drawParticle(float &posX, float &posY, float &texturePosX, float &texturePosY, float &width, float &height, float &alpha, float &anchorX, float &anchorY, float &rotation, float &widthScale, float &heightScale, float &tintMix, float &tintR, float &tintG, float &tintB, float &sourceImageWidth, float &sourceImageHeight, float &maskImageWidth, float &maskImageHeight, int &maskType, int &sourceImageScaleMode) {
    
    float texPosX, texPosY, holdWidthPixels, holdHeightPixels;
    float normLeft, normRight, normTop, normBottom;
    
    holdShader->setUniform1f("u_alpha", alpha);
    holdShader->setUniform1f("u_centerX", texturePosX * sourceImageWidth);
    holdShader->setUniform1f("u_centerY", texturePosY * sourceImageHeight);
    holdShader->setUniform1f("u_tintMix", tintMix);
    holdShader->setUniform1f("u_tintR", tintR);
    holdShader->setUniform1f("u_tintG", tintG);
    holdShader->setUniform1f("u_tintB", tintB);

// OLD CODE IN PIXI:
//
//    float anchorPixelsX, anchorPixelsY;
//    holdWidthPixels = (int) (fmax(width * getWindowWidth(), 1));
//    holdHeightPixels = (int) (fmax(height * getWindowHeight(), 1));
//    texPosX = texturePosX - (width * anchorX);
//    texPosY = texturePosY - (height * anchorY);
//    
//    anchorPixelsX = anchorX * holdWidthPixels;
//    anchorPixelsY = anchorY * holdHeightPixels;
//    if (maskType == 0) {
//        normLeft = fboEdgeOffsetX;
//        normRight = widthNextPow2Ratio - fboEdgeOffsetX;
//        normTop =  fboEdgeOffsetY;
//        normBottom = heightNextPow2Ratio - fboEdgeOffsetY;
//    } else {
//        normLeft = 0.0;
//        normRight = 1.0;
//        normTop = 0.0;
//        normBottom = 1.0;
//    };
//    
//    ofPushMatrix();
//    
//    ofTranslate(posX * getWindowWidth(), posY * getWindowHeight());
//    ofRotateZ(rotation);
//    ofScale(widthScale, heightScale, 1.0);
//    
//    // NOTES - 2ND TEXTURE COORDS HELD IN NORMAL(X/Y) FOR CONVENIENCE
//    // - Use widthNextPow2Ratio, heightNextPow2Ratio to adjust texture coords
//    
//    // top left
//    brushMesh.setTexCoord(0, ofVec2f(texPosX, texPosY));
//    brushMesh.setNormal(0, ofVec3f(normLeft, normTop, 0));
//    brushMesh.setVertex(0, ofVec3f(-anchorPixelsX, -anchorPixelsY, 0));
//    // top right
//    brushMesh.setTexCoord(1, ofVec2f((texPosX + width), texPosY));
//    brushMesh.setNormal(1, ofVec3f(normRight, normTop, 0));
//    brushMesh.setVertex(1, ofVec3f(holdWidthPixels-anchorPixelsX, -anchorPixelsY, 0));
//    // bottom right
//    brushMesh.setTexCoord(2, ofVec2f((texPosX + width), (texPosY + height)));
//    brushMesh.setNormal(2, ofVec3f(normRight, normBottom, 0));
//    brushMesh.setVertex(2, ofVec3f(holdWidthPixels-anchorPixelsX, holdHeightPixels-anchorPixelsY, 0));
//    // bottom left
//    brushMesh.setTexCoord(3, ofVec2f(texPosX, (texPosY + height)));
//    brushMesh.setNormal(3, ofVec3f(normLeft, normBottom, 0));
//    brushMesh.setVertex(3, ofVec3f(-anchorPixelsX, holdHeightPixels-anchorPixelsY, 0));
//    // draw
//    brushMesh.draw();
//    
//    ofPopMatrix();

    float drawXAdjusted, drawYAdjusted;
    float drawWScaled, drawHScaled;
//    float holdDrawPosX, holdDrawPosY;
	int   drawWidthPixels, drawHeightPixels;
    float holdScaleX, holdScaleY;
    int   holdMaxWidth = getMaxWidth();
    int   holdMaxHeight = getMaxHeight();
    float anchorXPixels, anchorYPixels;
    float fboEdgeOffsetX = 1.0f / sourceImageWidth;
    float fboEdgeOffsetY = 1.0f / sourceImageHeight;
    //    was set to higher for ipad retina
    //    float fboEdgeOffsetX = 2.0f / sourceImageWidth;
    //    float fboEdgeOffsetY = 2.0f / sourceImageHeight;
    
    float sourceImageRatioW, sourceImageRatioH;
    float sourceImageScaleX, sourceImageScaleY;
    float drawBorderX, drawBorderY;
    float scaledImageWidth, scaledImageHeight;
    float ratioOrig, ratioTarget;
    float tex0X, tex0Y, tex1X, tex1Y, tex2X, tex2Y, tex3X, tex3Y;
    float texBorderX, texBorderY;
    float texImageWidth, texImageHeight;
    float sampleWidthPixels, sampleHeightPixels;
    float sampleOffsetX, sampleOffsetY;
    
    switch (sourceImageScaleMode) {
        case TXIMAGESCALEMODE_SCALETOFIT:
            sourceImageRatioW = (float) holdMaxWidth / sourceImageWidth;
            sourceImageRatioH = (float) holdMaxHeight / sourceImageHeight;
            sourceImageScaleX = min(sourceImageRatioW, sourceImageRatioH);
            sourceImageScaleY = sourceImageScaleX;
            scaledImageWidth = sourceImageWidth * sourceImageScaleX;
            scaledImageHeight = sourceImageHeight * sourceImageScaleY;
            drawBorderX = (holdMaxWidth - scaledImageWidth) * 0.5;
            drawBorderY = (holdMaxHeight - scaledImageHeight) * 0.5;
            texImageWidth = sourceImageWidth;
            texImageHeight = sourceImageHeight;
            texBorderX = 0;
            texBorderY = 0;
            break;
        case TXIMAGESCALEMODE_SCALETOFILL:
            scaledImageWidth = holdMaxWidth;
            scaledImageHeight = holdMaxHeight;
            drawBorderX = 0;
            drawBorderY = 0;
            ratioOrig = (float) sourceImageWidth / sourceImageHeight;
            ratioTarget = (float) holdMaxWidth / holdMaxHeight;
            if (ratioOrig > ratioTarget) {
                texImageWidth = sourceImageHeight * ratioTarget;
                texImageHeight = sourceImageHeight;
                texBorderX =  (sourceImageWidth - texImageWidth ) * 0.5;
                texBorderY = 0;
            } else {
                texImageWidth = sourceImageWidth;
                texImageHeight = sourceImageWidth / ratioTarget;
                texBorderX = 0;
                texBorderY = (sourceImageHeight - texImageHeight ) * 0.5;
            };
            break;
        case TXIMAGESCALEMODE_STRETCHTOFILL:
            scaledImageWidth = holdMaxWidth;
            scaledImageHeight = holdMaxHeight;
            drawBorderX = 0;
            drawBorderY = 0;
            texImageWidth = sourceImageWidth;
            texImageHeight = sourceImageHeight;
            texBorderX = 0;
            texBorderY = 0;
            break;
        default:
            scaledImageWidth = holdMaxWidth;
            scaledImageHeight = holdMaxHeight;
            drawBorderX = 0;
            drawBorderY = 0;
            texImageWidth = sourceImageWidth;
            texImageHeight = sourceImageHeight;
            texBorderX = 0;
            texBorderY = 0;
            break;
    };
    
    drawWidthPixels = (int) (fmax(width * scaledImageWidth, 1));
    drawHeightPixels = (int) (fmax(height * scaledImageHeight, 1));
    anchorXPixels = anchorX * drawWidthPixels;
    anchorYPixels = anchorY * drawHeightPixels;
    
    // translate, rotate, scale
    drawWScaled = drawWidthPixels * widthScale;
    drawHScaled = drawHeightPixels * heightScale;
    drawXAdjusted = (0.5* drawWScaled) + ((scaledImageWidth - drawWScaled) * posX);
    drawYAdjusted = (0.5* drawHScaled) + ((scaledImageHeight - drawHScaled) * posY);

    ofPushMatrix();
    ofTranslate(drawBorderX + drawXAdjusted, drawBorderY + drawYAdjusted, 0.0);
    ofRotateZ(rotation);
    ofScale(widthScale, heightScale, 1.0);
    
    sampleWidthPixels = width * texImageWidth;
    sampleHeightPixels = height * texImageHeight;
    sampleOffsetX = texturePosX * (1 - width) * texImageWidth;
    sampleOffsetY = texturePosY * (1 - height) * texImageHeight;
    
#ifdef TARGET_OPENGLES
    //
    // WARNING - THIS OLD TARGET_OPENGLES CODE IS UNTESTED AND PROBABLY WRONG!!
    /*
     // Use widthNextPow2Ratio, heightNextPow2Ratio to adjust texture coords
     float widthNextPow2Ratio = (float) sourceImageWidth /ofNextPow2(sourceImageWidth);
     float heightNextPow2Ratio = (float) sourceImageHeight /ofNextPow2(sourceImageHeight);
     tex0X = (texBorderX + fboEdgeOffsetX + sampleOffsetX) * widthNextPow2Ratio;
     tex0Y = (texBorderY + fboEdgeOffsetY + sampleOffsetY) * heightNextPow2Ratio;
     tex1X = (texBorderX + width + sampleOffsetX - fboEdgeOffsetX) * widthNextPow2Ratio;
     tex1Y = (texBorderY + fboEdgeOffsetY + sampleOffsetY) * heightNextPow2Ratio;
     tex2X = (texBorderX + width + sampleOffsetX - fboEdgeOffsetX) * widthNextPow2Ratio;
     tex2Y = (texBorderY + height + sampleOffsetY - fboEdgeOffsetY) * heightNextPow2Ratio;
     tex3X = (texBorderX + fboEdgeOffsetX + sampleOffsetX) * widthNextPow2Ratio;
     tex3Y = (texBorderY + height + sampleOffsetY - fboEdgeOffsetY) * heightNextPow2Ratio;
     if (holdMaskType > 0) {
     if (holdMaskType == 1) {
     float maskWidthNextPow2Ratio = (float) maskImageWidth /ofNextPow2(maskImageWidth);
     float maskHeightNextPow2Ratio = (float) maskImageHeight /ofNextPow2(maskImageHeight);
     float maskFboEdgeOffsetX = 1.0f / maskImageWidth;
     float maskFboEdgeOffsetY = 1.0f / maskImageHeight;
     normLeft = maskFboEdgeOffsetX * maskWidthNextPow2Ratio;
     normRight = (1.0 - maskFboEdgeOffsetX) * maskWidthNextPow2Ratio;
     normTop = maskFboEdgeOffsetY * maskHeightNextPow2Ratio;
     normBottom = (1.0 - maskFboEdgeOffsetY) * maskHeightNextPow2Ratio;
     } else {
     normLeft = 0.0;
     normRight = 1.0;
     normTop = 0.0;
     normBottom = 1.0;
     };
     };
     */
#else
    tex0X = texBorderX + fboEdgeOffsetX + sampleOffsetX;
    tex0Y = texBorderY + fboEdgeOffsetY + sampleOffsetY;
    tex1X = texBorderX + sampleWidthPixels + sampleOffsetX - fboEdgeOffsetX;
    tex1Y = texBorderY + fboEdgeOffsetY + sampleOffsetY;
    tex2X = texBorderX + sampleWidthPixels + sampleOffsetX - fboEdgeOffsetX;
    tex2Y = texBorderY + sampleHeightPixels + sampleOffsetY - fboEdgeOffsetY;
    tex3X = texBorderX + fboEdgeOffsetX + sampleOffsetX;
    tex3Y = texBorderY + sampleHeightPixels + sampleOffsetY - fboEdgeOffsetY;
    if (maskType > 0) {
        if (maskType == 1) {
            float maskFboEdgeOffsetX = 1.0f / maskImageWidth;
            float maskFboEdgeOffsetY = 1.0f / maskImageHeight;
            normLeft = maskImageWidth * maskFboEdgeOffsetX;
            normRight = maskImageWidth * (1.0 - maskFboEdgeOffsetX);
            normTop = maskImageHeight * maskFboEdgeOffsetY;
            normBottom = maskImageHeight * (1.0 - maskFboEdgeOffsetY);
        } else {
            normLeft = 0.0;
            normRight = 1.0;
            normTop = 0.0;
            normBottom = 1.0;
        };
    };
#endif

    //holdShader->bindDefaults();
    

    // top left
    drawMesh.setTexCoord(0, ofVec2f(tex0X, tex0Y));
    drawMesh.setVertex(0, ofVec3f(-anchorXPixels, -anchorYPixels, 0));
    // top right
    drawMesh.setTexCoord(1, ofVec2f(tex1X, tex1Y));
    drawMesh.setVertex(1, ofVec3f(drawWidthPixels - anchorXPixels, -anchorYPixels, 0));
    // bottom right
    drawMesh.setTexCoord(2, ofVec2f(tex2X, tex2Y));
    drawMesh.setVertex(2, ofVec3f(drawWidthPixels - anchorXPixels, drawHeightPixels - anchorYPixels, 0));
    // bottom left
    drawMesh.setTexCoord(3, ofVec2f(tex3X, tex3Y));
    drawMesh.setVertex(3, ofVec3f(-anchorXPixels, drawHeightPixels - anchorYPixels, 0));
    if (maskType > 0) {
        // NOTE - MASK TEXTURE COORDS HELD IN NORMAL(X/Y) FOR CONVENIENCE
        drawMesh.setNormal(0, ofVec3f(normLeft, normTop, 0));
        drawMesh.setNormal(1, ofVec3f(normRight, normTop, 0));
        drawMesh.setNormal(2, ofVec3f(normRight, normBottom, 0));
        drawMesh.setNormal(3, ofVec3f(normLeft, normBottom, 0));
    };
    
    // draw
    ofEnableAlphaBlending();
    drawMesh.draw();
    ofDisableAlphaBlending();
    
    ofPopMatrix();
}

void TXDrawParticles::triggerParticles() {
    bool trigger;
    float holdSpeed, holdLifetimeSecs, holdSpreadOffsetX, holdSpreadOffsetY, spreadProportion;
    float lastExpectedTriggerTime, stepTimeSecs, startDelay, randomLifetimeOffset;
    
    if (useMasterBpm->getBool()) {
        holdSpeed = masterBpm / 60;
    } else {
        holdSpeed = bpm->getFloat() / 60;
    };
    stepTimeSecs = stepTimeBeats->getFloat() / (stepTimeDivisor->getFloat() * holdSpeed);
    lastExpectedTriggerTime = currentTime - fmod(currentTime, stepTimeSecs);
    
    if (triggerConfirmed || (currentTime == 0) || (lastExpectedTriggerTime > lastRecordedTriggerTime)) {
        lastRecordedTriggerTime = currentTime;
        triggerConfirmed = false;
        
        dancePattern.getAllOutputValues(lfoValues);
        
        bool holdDance_randomStartPhase = dance_randomStartPhase->getBool();
        float holdTriggerProbability = triggerProbability->getFloat();
        float holdtriggerDelaySpread = triggerDelaySpread->getFloat();
        int holdtriggerDelayDistribution = triggerDelayDistribution->getInt();
        float holdtriggerDelayRandom = triggerDelayRandom->getFloat();
        float holdScaleXStart = scaleXCurve.parameters.getFloat(0);
        float holdScaleX = scaleX->getFloat();
        float holdScaleYStart = scaleYCurve.parameters.getFloat(0);
        float holdScaleY = scaleY->getFloat();
        float holdAnchorXStart = anchorXCurve.parameters.getFloat(0);
        float holdAnchorX = anchorX->getFloat();
        float holdAnchorYStart = anchorYCurve.parameters.getFloat(0);
        float holdAnchorY = anchorY->getFloat();
        float holdVelocityX = velocityX->getFloat();
        float holdVelocityY = velocityY->getFloat();
        float holdRotationStart = rotationCurve.parameters.getFloat(0);
        float holdSamplePosX = samplePosX->getFloat();
        float holdSamplePosY = samplePosY->getFloat();
        float holdWidth = width->getFloat();
        float holdHeight = height->getFloat();
        int holdSpreadType = spreadType->getInt();
        int holdSpreadDistribution = spreadDistribution->getInt();
        float holdSpreadRandom = spreadRandom->getFloat();
        float holdLifetimeRandomVariation = lifetimeRandomVariation->getFloat();
        int holdmaximumActiveParticles = maximumActiveParticles;
        int holdNumParticlesPerTrigger = min(numParticlesPerTrigger->getInt(), holdmaximumActiveParticles);

        if (useTriggerTimeForLifetime->getBool()) {
            holdLifetimeSecs = stepTimeSecs;
        } else {
            holdLifetimeSecs = lifetimeBeats->getFloat() / holdSpeed;
        };
        
        for (int i = 0; i < holdNumParticlesPerTrigger; i++) {
            trigger = ((ofRandom(1.0) - 1 + holdTriggerProbability) >= 0);
            if (trigger) {
                randomLifetimeOffset = holdLifetimeSecs * ofRandom(-1.0, 1.0) * holdLifetimeRandomVariation;
                holdLifetimeSecs = holdLifetimeSecs + randomLifetimeOffset;
                
                float indexProportion = (float) i / holdNumParticlesPerTrigger;
                float partDelay =  ofxTweenLite::tween ( 0.0, holdtriggerDelaySpread, indexProportion, (ofEaseFunction) (holdtriggerDelayDistribution + distributionTypeOffset));
                float randDelay = ofRandom(1.0);
                
                startDelay = ofLerp(partDelay, randDelay, holdtriggerDelayRandom) * stepTimeSecs;
                
                arrParticles[nextParticleIndex].trigger(i, holdNumParticlesPerTrigger, holdLifetimeSecs, startDelay, holdWidth, holdHeight, holdScaleXStart * holdScaleX, holdScaleYStart * holdScaleY, holdVelocityX, holdVelocityY, holdRotationStart, holdAnchorXStart, holdAnchorYStart,holdSamplePosX, holdSamplePosY);
               
                arrParticles[nextParticleIndex].resetInitialVariables();
                
                // only draw spread if more than 1 particle
                if (holdNumParticlesPerTrigger == 1) {
                    holdSpreadOffsetX = 0;
                    holdSpreadOffsetY = 0;
                } else {
                    spreadProportion =  ofxTweenLite::tween ( 0.0, 1.0, indexProportion, (ofEaseFunction) (holdSpreadDistribution + distributionTypeOffset));

                    switch (holdSpreadType) {
                        case 0:
                            // "Spread 1: Circle",
                            holdSpreadOffsetX = 0.5 * sin(spreadProportion * TWO_PI);
                            holdSpreadOffsetY = 0.5 * cos(spreadProportion * TWO_PI);
                            break;
                        case 1:
                            // "Spread 2: Horizontal Line",
                            holdSpreadOffsetX = -0.5 + spreadProportion;
                            holdSpreadOffsetY = 0;
                            break;
                        case 2:
                            // "Spread 3: Vertical Line",
                            holdSpreadOffsetX = 0;
                            holdSpreadOffsetY =  -0.5 + spreadProportion;
                            break;
                        case 3:
                            // "Spread 4: Diagonal Line",
                            holdSpreadOffsetX =  -0.5 + spreadProportion;
                            holdSpreadOffsetY =  -0.5 + spreadProportion;
                            break;
                        default:
                            holdSpreadOffsetX = 0;
                            holdSpreadOffsetY = 0;
                            break;
                    };
                };
                
                arrParticles[nextParticleIndex].spreadOffsetX = ((1 - holdSpreadRandom) * holdSpreadOffsetX) + (holdSpreadRandom * arrParticles[nextParticleIndex].spreadRandX);
                arrParticles[nextParticleIndex].spreadOffsetY = ((1 - holdSpreadRandom) * holdSpreadOffsetY) + (holdSpreadRandom * arrParticles[nextParticleIndex].spreadRandY);
  
                // initialise lfo with current vals
                arrParticles[nextParticleIndex].dancePattern.setAllValues(lfoValues);
                arrParticles[nextParticleIndex].dancePattern.resetTime();

                if (holdDance_randomStartPhase) {
                    arrParticles[nextParticleIndex].dancePattern.advanceBy(ofRandom(1000.0), masterBpm);
                } else {
                    arrParticles[nextParticleIndex].dancePattern.advanceBy(0, masterBpm);
                };
                // new index
                nextParticleIndex++;
                if (nextParticleIndex >= maximumActiveParticles) {
                    nextParticleIndex = 0;
                };
            };
        };
    };
}

// OLD CODE
//void TXDrawParticles::setTime(float timeArg){
//	float holdPhase;
//    float holdSpeed;
//    if (useMasterBpm) {
//        holdSpeed = masterBpm / 60;
//    } else {
//        holdSpeed = bpm;
//    };
//    currentTime = timeArg;
//    holdPhase = timeArg * holdSpeed  * stepTimeDivisor / stepTimeBeats;
//    phase = fmod(holdPhase, 1.0f);
//}

void TXDrawParticles::resetTime() {
    currentTime = 0.0;
    phase = 0;
    lastRecordedTriggerTime = 0.0;
    killAllParticles();
}

void TXDrawParticles::killAllParticles(int startIndex) {
    for (int i = startIndex; i < totalNoParticles; i++){
        arrParticles[i].kill();
    };
}

float  TXDrawParticles::adjustPerlin(float input, float scaleArg) {
    float   holdVal = ((scaleArg * input) + 1) * 0.5;
    return  holdVal;
}

void TXDrawParticles::advanceBy(float timeDeltaArg) {
	float holdPhase;
    float holdSpeed;
    float holdAttractionCurve;
    float holdWidthCurve;
    float holdHeightCurve;
    float holdAlphaCurve;
    float holdWidth;
    float holdHeight;
    float holdRotationCurve;
    float holdAgeProportion;
    float holdAge;
    float holdLifetimeSecs;
    float holdPerlinX, holdPerlinY, holdPerlinW, holdPerlinH, holdPerlinA, holdPerlinR;
    float holdVelocityX, holdVelocityY;
    float holdAlphaScaleFinal;
    float holdScaleXCurve;
    float holdScaleYCurve;
    float holdAnchorXCurve;
    float holdAnchorYCurve;
    float holdRotationSum;
    float holdSpreadCenterX, holdSpreadCenterY;
    float holdSpreadWidth, holdSpreadHeight;
    float holdSpreadOffsetX, holdSpreadOffsetY;
    float holdSamplePositionX, holdSamplePositionY;
    float holdDanceX, holdDanceY;
    float holdDanceScaleX, holdDanceScaleY;
    float holdAttractionPointX, holdAttractionPointY, holdAttractionMoveX, holdAttractionMoveY;
    float holdSpreadRotation;
    float holdSin, holdCos;
    float holdSumX, holdSumY, holdOffset, holdHalfAttDec;
    
    if (useMasterBpm->getBool()) {
        holdSpeed = masterBpm / 60.0;
    } else {
        holdSpeed = bpm->getFloat() / 60.0;
    };
    currentTime += timeDeltaArg;
    holdPhase = (phase + (timeDeltaArg * holdSpeed  * stepTimeDivisor->getFloat() / stepTimeBeats->getFloat()));
    phase = fmod(holdPhase, 1.0f);
    
    bool holdUseScaleXForScaleY = useScaleXForScaleY->getBool();
    bool holdUseWidthForHeight = useWidthForHeight->getBool();

    float holdAlphaScale = alphaScale->getFloat();
    float holdScaleX = scaleX->getFloat();
    float holdScaleY = scaleY->getFloat();
    float holdAnchorX = anchorX->getFloat();
    float holdAnchorY = anchorY->getFloat();
    float holdRotationOffset = rotationOffset->getFloat();
    float holdGravityX = gravityX->getFloat();
    float holdGravityY = gravityY->getFloat();

    bool  holdLockAlphaScaleAtStart = lockAlphaScaleAtStart->getBool();
    bool  holdLockWidthAtStart = lockWidthAtStart->getBool();
    bool  holdLockHeightAtStart = lockHeightAtStart->getBool();
    bool  holdLockSpreadAtStart = lockSpreadAtStart->getBool();
    bool  holdLockScaleAtStart = lockScaleAtStart->getBool();
    bool  holdLockAnchorAtStart = lockAnchorAtStart->getBool();
    bool  holdLockRotationOffsetAtStart = lockRotationOffsetAtStart->getBool();
    bool  holdLockSamplePositionAtStart = lockSamplePositionAtStart->getBool();
    bool  holdLockDanceWidthHeightAtStart = lockDanceWidthHeightAtStart->getBool();
    bool  holdLockAttractionPointAtStart = lockAttractionPointAtStart->getBool();

    float holdPosXPerlinMix = posXPerlinMix->getFloat();
    float holdPosYPerlinMix = posYPerlinMix->getFloat();
    float holdAttraction = attraction->getFloat();
    float holdTintMix = tintMix->getFloat();

    float v_posXPerlinSpeed = posXPerlinSpeed->getFloat();
    float v_posYPerlinSpeed = posYPerlinSpeed->getFloat();
    float v_widthPerlinSpeed = widthPerlinSpeed->getFloat();
    float v_heightPerlinSpeed = heightPerlinSpeed->getFloat();
    float v_alphaPerlinSpeed = alphaPerlinSpeed->getFloat();
    float v_rotationPerlinSpeed = rotationPerlinSpeed->getFloat();
    
    float v_posXPerlinMix = posXPerlinMix->getFloat();
    float v_posYPerlinMix = posYPerlinMix->getFloat();
    float v_widthPerlinMix = widthPerlinMix->getFloat();
    float v_heightPerlinMix = heightPerlinMix->getFloat();
    float v_alphaPerlinMix = alphaPerlinMix->getFloat();
    float v_rotationPerlinMix = rotationPerlinMix->getFloat();
    
    float v_width = width->getFloat();
    float v_height = height->getFloat();
    float v_rotationOffset = rotationOffset->getFloat();
    float v_spreadCenterX = spreadCenterX->getFloat();
    float v_spreadCenterY = spreadCenterY->getFloat();
    float v_spreadWidth = spreadWidth->getFloat();
    float v_spreadHeight = spreadHeight->getFloat();
    float v_spreadRotation = spreadRotation->getFloat();
    float v_samplePosX = samplePosX->getFloat();
    float v_samplePosY = samplePosY->getFloat();
    float v_dance_width = dance_width->getFloat();
    float v_dance_height = dance_height->getFloat();
    float v_attractionPointX = attractionPointX->getFloat();
    float v_attractionPointY = attractionPointY->getFloat();


    for (int i = 0; i < maximumActiveParticles; i++){
        if (arrParticles[i].alive) {
            arrParticles[i].advanceBy(timeDeltaArg, masterBpm);
            if (arrParticles[i].awake) {
                // adjust age & lifetime re: startdelay
                holdAge = arrParticles[i].age - arrParticles[i].startDelay;
                // calculate curves using particle age
                if (holdAge == 0) {
                    holdAgeProportion = 0;
                } else {
                    holdLifetimeSecs = arrParticles[i].lifetimeSecs - arrParticles[i].startDelay;
                    holdAgeProportion = fmin(holdAge / holdLifetimeSecs, 1.0f);
                };
                holdAttractionCurve = attractionCurve.interpolatedLookup(holdAgeProportion);
                holdWidthCurve = widthCurve.interpolatedLookup(holdAgeProportion);
                holdHeightCurve = heightCurve.interpolatedLookup(holdAgeProportion);
                holdAlphaCurve = alphaCurve.interpolatedLookup(holdAgeProportion);
                holdScaleXCurve = scaleXCurve.interpolatedLookup(holdAgeProportion);
                holdScaleYCurve = scaleYCurve.interpolatedLookup(holdAgeProportion);
                holdAnchorXCurve = anchorXCurve.interpolatedLookup(holdAgeProportion);
                holdAnchorYCurve = anchorYCurve.interpolatedLookup(holdAgeProportion);
                holdRotationCurve = rotationCurve.interpolatedLookup(holdAgeProportion) * 360;
                
//                holdPerlinLookup = (arrParticles[i].age + arrParticles[i].randSeed);
//                holdGetPerlX = holdPerlinLookup * v_posXPerlinSpeed;
//                holdGetPerlY = holdPerlinLookup * v_posYPerlinSpeed;
//                holdGetPerlW = holdPerlinLookup * v_widthPerlinSpeed;
//                holdGetPerlH = holdPerlinLookup * v_heightPerlinSpeed;
//                holdGetPerlA = holdPerlinLookup * v_alphaPerlinSpeed;
//                holdGetPerlR = holdPerlinLookup * v_rotationPerlinSpeed;
//                
//                holdPerlinX = adjustPerlin(posXPerlin.get(holdGetPerlX, holdGetPerlX), 6.0);
//                holdPerlinY = adjustPerlin( posYPerlin.get(holdGetPerlY, holdGetPerlY), 6.0);
//                holdPerlinW = adjustPerlin( widthPerlin.get(holdGetPerlW, holdGetPerlW));
//                holdPerlinH = adjustPerlin( heightPerlin.get(holdGetPerlH, holdGetPerlH));
//                holdPerlinA = adjustPerlin( alphaPerlin.get(holdGetPerlA, holdGetPerlA));
//                holdPerlinR = adjustPerlin( rotationPerlin.get(holdGetPerlR, holdGetPerlR));
                
                float posXPerlinPhase;
                float posYPerlinPhase;
                float widthPerlinPhase;
                float heightPerlinPhase;
                float alphaPerlinPhase;
                float rotationPerlinPhase;

                arrParticles[i].posXPerlinPhase += timeDeltaArg * v_posXPerlinSpeed;
                arrParticles[i].posYPerlinPhase += timeDeltaArg * v_posYPerlinSpeed;;
                arrParticles[i].widthPerlinPhase += timeDeltaArg * v_widthPerlinSpeed;;
                arrParticles[i].heightPerlinPhase += timeDeltaArg * v_heightPerlinSpeed;;
                arrParticles[i].alphaPerlinPhase += timeDeltaArg * v_alphaPerlinSpeed;;
                arrParticles[i].rotationPerlinPhase += timeDeltaArg * v_rotationPerlinSpeed;;
                
                holdPerlinX = adjustPerlin(ofSignedNoise(arrParticles[i].posXPerlinPhase));
                holdPerlinY = adjustPerlin(ofSignedNoise(arrParticles[i].posYPerlinPhase));
                holdPerlinW = adjustPerlin(ofSignedNoise(arrParticles[i].widthPerlinPhase));
                holdPerlinH = adjustPerlin(ofSignedNoise(arrParticles[i].heightPerlinPhase));
                holdPerlinA = adjustPerlin(ofSignedNoise(arrParticles[i].alphaPerlinPhase));
                holdPerlinR = adjustPerlin(ofSignedNoise(arrParticles[i].rotationPerlinPhase));

                if (!arrParticles[i].initialVariablesUpdated) {
                    // store init values
                    arrParticles[i].initialAlphaScale = holdAlphaScale;
                    arrParticles[i].initialWidth = v_width;
                    arrParticles[i].initialHeight = v_height;
                    arrParticles[i].initialScaleX = holdScaleX;
                    arrParticles[i].initialScaleY = holdScaleY;
                    arrParticles[i].initialAnchorX = holdAnchorX;
                    arrParticles[i].initialAnchorY = holdAnchorY;
                    arrParticles[i].initialRotationOffset = v_rotationOffset;
                    arrParticles[i].initialSpreadCenterX = v_spreadCenterX;
                    arrParticles[i].initialSpreadCenterY = v_spreadCenterY;
                    arrParticles[i].initialSpreadWidth = v_spreadWidth;
                    arrParticles[i].initialSpreadHeight = v_spreadHeight;
                    arrParticles[i].initialSpreadRotation = v_spreadRotation;
                    arrParticles[i].initialSamplePositionX = v_samplePosX;
                    arrParticles[i].initialSamplePositionY = v_samplePosY;
                    arrParticles[i].initialDanceWidth = v_dance_width;
                    arrParticles[i].initialDanceHeight = v_dance_height;
                    arrParticles[i].initialAttractionPointX = v_attractionPointX;
                    arrParticles[i].initialAttractionPointY = v_attractionPointY;
                    arrParticles[i].initialTintMix = holdTintMix;
                    arrParticles[i].initialTintR = tint.r;
                    arrParticles[i].initialTintG = tint.g;
                    arrParticles[i].initialTintB = tint.b;
                    arrParticles[i].initialPosX = arrParticles[i].posX;
                    arrParticles[i].initialPosY = arrParticles[i].posY;
                    arrParticles[i].initialVariablesUpdated = true;
                };
                
                holdVelocityX = arrParticles[i].velocityX + (holdGravityX * timeDeltaArg);
                holdVelocityY = arrParticles[i].velocityY + (holdGravityY * timeDeltaArg);

                if (holdLockAlphaScaleAtStart) {
                    holdAlphaScaleFinal = arrParticles[i].initialAlphaScale;
                } else {
                    holdAlphaScaleFinal = holdAlphaScale;
                };
                if (holdLockWidthAtStart) {
                    holdWidth = arrParticles[i].initialWidth * holdWidthCurve;
                } else {
                    holdWidth = v_width * holdWidthCurve;
                };
                if (holdLockHeightAtStart) {
                    holdHeight = arrParticles[i].initialHeight * holdHeightCurve;
                } else {
                    holdHeight = v_height * holdHeightCurve;
                };
                if (holdLockSpreadAtStart) {
                    holdSpreadCenterX = arrParticles[i].initialSpreadCenterX;
                    holdSpreadCenterY = arrParticles[i].initialSpreadCenterY;
                    holdSpreadWidth = arrParticles[i].initialSpreadWidth;
                    holdSpreadHeight = arrParticles[i].initialSpreadHeight;
                    holdSpreadRotation = ofDegToRad(arrParticles[i].initialSpreadRotation);
                } else {
                    holdSpreadCenterX = v_spreadCenterX;
                    holdSpreadCenterY = v_spreadCenterY;
                    holdSpreadWidth = v_spreadWidth;
                    holdSpreadHeight = v_spreadHeight;
                    holdSpreadRotation = ofDegToRad(v_spreadRotation);
                };
                if (holdLockRotationOffsetAtStart) {
                    holdRotationSum = holdRotationCurve + arrParticles[i].initialRotationOffset;
                } else {
                    holdRotationSum = holdRotationCurve + v_rotationOffset;
                };
                if (holdLockSamplePositionAtStart) {
                    holdSamplePositionX = arrParticles[i].initialSamplePositionX;
                    holdSamplePositionY = arrParticles[i].initialSamplePositionY;
                } else {
                    holdSamplePositionX = v_samplePosX;
                    holdSamplePositionY = v_samplePosY;
                };
                if (holdLockDanceWidthHeightAtStart) {
                    holdDanceScaleX = arrParticles[i].initialDanceWidth;
                    holdDanceScaleY = arrParticles[i].initialDanceHeight;
                } else {
                    holdDanceScaleX = v_dance_width;
                    holdDanceScaleY = v_dance_height;
                };
                if (holdLockAttractionPointAtStart) {
                    holdAttractionPointX = arrParticles[i].initialAttractionPointX;
                    holdAttractionPointY = arrParticles[i].initialAttractionPointY;
                } else {
                    holdAttractionPointX = v_attractionPointX;
                    holdAttractionPointY = v_attractionPointY;
                };

                // rotate spread
                holdSin = sin(holdSpreadRotation);
                holdCos = cos(holdSpreadRotation);
                holdSpreadOffsetX = (arrParticles[i].spreadOffsetX * holdCos - arrParticles[i].spreadOffsetY * holdSin) * holdSpreadWidth;
                holdSpreadOffsetY = (arrParticles[i].spreadOffsetX * holdSin + arrParticles[i].spreadOffsetY * holdCos) * holdSpreadHeight;
                
                arrParticles[i].velocityX = holdVelocityX;
                arrParticles[i].velocityY = holdVelocityY;
                
                holdDanceX = (arrParticles[i].dancePattern.positionX - 0.5) *  holdDanceScaleX;
                holdDanceY = (arrParticles[i].dancePattern.positionY - 0.5) *  holdDanceScaleY;
                
                holdSumX = ((1-holdPosXPerlinMix) * (holdSpreadOffsetX + holdSpreadCenterX)) + (holdPosXPerlinMix * holdPerlinX) + (holdVelocityX * arrParticles[i].age) + holdDanceX;
                holdSumY = ((1-holdPosYPerlinMix) * (holdSpreadOffsetY + holdSpreadCenterY)) + (holdPosYPerlinMix * holdPerlinY) + (holdVelocityY * arrParticles[i].age) + holdDanceY;
                
                if (holdAttraction != 0) {
                    float distX, distY, holdAttractionProp;
                    
                    distX = abs(holdAttractionPointX - holdSumX);
                    distY = abs(holdAttractionPointY - holdSumY);
                    
                    if (holdAttraction > 0) {
                        holdAttractionProp = min(1.0f, holdAttraction * holdAttractionCurve);
                    } else {
                        holdAttractionProp = holdAttraction * holdAttractionCurve;
                    };
                    
                    if (holdSumX < holdAttractionPointX) {
                        holdAttractionMoveX = holdAttractionProp * distX;
                    } else {
                        holdAttractionMoveX = holdAttractionProp * -distX;
                    };
                    if (holdSumY < holdAttractionPointY) {
                        holdAttractionMoveY = holdAttractionProp * distY;
                    } else {
                        holdAttractionMoveY = holdAttractionProp * -distY;
                    };
                } else {
                    holdAttractionMoveX = 0;
                    holdAttractionMoveY = 0;
                };
                
                arrParticles[i].posX = holdSumX + holdAttractionMoveX;
                arrParticles[i].posY = holdSumY + holdAttractionMoveY;

                arrParticles[i].width = ((1-v_widthPerlinMix) * holdWidth) + (v_widthPerlinMix * holdPerlinW);
                if (holdUseWidthForHeight) {
                    arrParticles[i].height = arrParticles[i].width;
                } else {
                    arrParticles[i].height = ((1-v_heightPerlinMix) * holdHeight) + (v_heightPerlinMix * holdPerlinH);
                };
                arrParticles[i].alpha = ((1-v_alphaPerlinMix) * holdAlphaCurve) + (v_alphaPerlinMix * holdPerlinA);
                arrParticles[i].rotation = ((1-v_rotationPerlinMix) * holdRotationSum) + (v_rotationPerlinMix * ((holdPerlinR * 360) -180));
               
                if (holdLockScaleAtStart) {
                    arrParticles[i].scaleX = holdScaleXCurve * arrParticles[i].initialScaleX;
                    if (holdUseScaleXForScaleY) {
                        arrParticles[i].scaleY = arrParticles[i].scaleX;
                    } else {
                        arrParticles[i].scaleY = holdScaleYCurve * arrParticles[i].initialScaleY;
                    };
                } else {
                    arrParticles[i].scaleX = holdScaleXCurve * holdScaleX;
                    if (holdUseScaleXForScaleY) {
                        arrParticles[i].scaleY = arrParticles[i].scaleX;
                    } else {
                        arrParticles[i].scaleY = holdScaleYCurve * holdScaleY;
                    };
                };
                if (holdLockAnchorAtStart) {
                    arrParticles[i].anchorX = holdAnchorXCurve * arrParticles[i].initialAnchorX;
                    arrParticles[i].anchorY = holdAnchorYCurve * arrParticles[i].initialAnchorY;
                } else {
                    arrParticles[i].anchorX = holdAnchorXCurve * holdAnchorX;
                    arrParticles[i].anchorY = holdAnchorYCurve * holdAnchorY;
                };
            };
        };
    };
}

/////////////////////////////////////////////////////// 

void  TXDrawParticles::imageAssetSlotChanged(string slotNameArg) {
    if (slotNameArg == "sourceImageAsset") {
        loadSourceImage();
    } else {
        loadMaskImage();
    };
}

bool TXDrawParticles::loadSourceImage() {
    ofPtr <TXAsset> asset;
    string fileName;
    int sourceImageAssetID = getImageAssetIDSlot("sourceImageAsset").first;
    sourceImageHasLoaded = false;
    if (sourceImageAssetID != 0) {
        asset = parentSystem->getAsset(TXASSETTYPE_IMAGE, sourceImageAssetID);
        fileName = asset->getFileName();
        if (sourceImage.load(fileName)) {
            sourceImageHasLoaded = true;
        };
    } else {
        sourceImage = greyImage;
        sourceImageHasLoaded = true;
    };
    return sourceImageHasLoaded;
}

bool TXDrawParticles::loadMaskImage() {
    ofPtr <TXAsset> asset;
    string fileName;
    int maskImageAssetID = getImageAssetIDSlot("maskImageAsset").first;
    maskImageHasLoaded = false;
    if (maskImageAssetID != 0) {
        asset = parentSystem->getAsset(TXASSETTYPE_IMAGE, maskImageAssetID);
        fileName = asset->getFileName();
        if (maskImage.load(fileName)) {
            maskImageHasLoaded = true;
        };
    };
    return maskImageHasLoaded;
}

bool TXDrawParticles::getSourceImageHasLoaded() {
    return sourceImageHasLoaded;
}

bool TXDrawParticles::getMaskImageHasLoaded() {
    return maskImageHasLoaded;
}

int TXDrawParticles::getTextureWidth() {
    if (sourceImageHasLoaded) {
        return sourceImage.getWidth();
    } else {
        return 0;
    }
}

int TXDrawParticles::getTextureHeight() {
    if (sourceImageHasLoaded) {
        return sourceImage.getHeight();
    } else {
        return 0;
    }
}

ofTexture *  TXDrawParticles::getTexture() {
    if (sourceImageHasLoaded) {
        return & sourceImage.getTexture();
    } else {
        return NULL;
    };
}

ofPixelsRef TXDrawParticles::getPixels() {
    return sourceImage.getPixels() ;
}

/////////////////////////////////////////

void  TXDrawParticles::triggerLevelChanged(ofAbstractParameter & parameterArg){
    float holdTriggerThreshold = triggerThreshold->getFloat();
    float holdTriggerLevel = triggerLevel->getFloat();
    // if rising above threshold
    if ((triggerPrevious < holdTriggerThreshold) && (holdTriggerLevel >= holdTriggerThreshold)) {
        triggerConfirmed = true;
    };
    triggerPrevious = holdTriggerLevel;
}

void  TXDrawParticles::triggerNowChanged(ofAbstractParameter & parameterArg){
    float holdTriggerNow = triggerNow->getBool();
    // if changed to on, confirm
    if ((triggerNowPrevious == 0) && (holdTriggerNow == 1)) {
        triggerConfirmed = true;
    };
    triggerNowPrevious = holdTriggerNow;
}

void  TXDrawParticles::killAllNowChanged(ofAbstractParameter & parameterArg){
    float holdKillAllNow = killAllNow->getBool();
    // if changed to on, confirm
    if ((killAllNowPrevious == 0) && (holdKillAllNow == 1)) {
        killAllParticles();
    };
    killAllNowPrevious = holdKillAllNow;
}

void  TXDrawParticles::maximumActiveParticlesChanged(int & intArg){
    killAllParticles(intArg);
}

void  TXDrawParticles::tintHueChanged(ofAbstractParameter & parameterArg){
    updateTintFromHSB();
}


void  TXDrawParticles::tintHueRotateChanged(ofAbstractParameter & parameterArg){
    updateTintFromHSB();
}

void  TXDrawParticles::tintSaturationChanged(ofAbstractParameter & parameterArg){
    updateTintFromHSB();
}

void  TXDrawParticles::tintBrightnessChanged(ofAbstractParameter & parameterArg){
    updateTintFromHSB();
}

void  TXDrawParticles::tintHSBAsRGBChanged(ofAbstractParameter & parameterArg){
    updateTintFromHSB();
}


//////////////////////////////////////////////////////////////

void TXDrawParticles::updateTintFromHSB() {
    tint = TXFunctions::txGetColor(tintHue->getFloat(), tintSaturation->getFloat(), tintBrightness->getFloat(), 1.0,
                                   tintHueRotate->getFloat(), tintHSBAsRGB->getBool());
}

float TXDrawParticles::interpolate(float point1, float point2, float inbetween, bool smooth) {
    float holdVal;
    
    if (smooth) {
        holdVal = TXFunctions::cosineInterpolate(point1, point2, inbetween);
    } else {
        holdVal = point1  + (inbetween * (point2 - point1));
    };
    
    return holdVal;
}

