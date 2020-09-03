/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXDrawParticles3D.h"
#include "TXSystem.h"
#include "TXFunctions.h"
#include "ofxTweenLite.h"

// constructor
TXDrawParticles3D::TXDrawParticles3D(){
    setup();
};

// destructor
TXDrawParticles3D::~TXDrawParticles3D() {
    // remove listeners to relevent parameters:
    ofRemoveListener(triggerLevel->parameters.parameterChangedE(),this,&TXDrawParticles3D::triggerLevelChanged);
    ofRemoveListener(triggerNow->parameters.parameterChangedE(),this,&TXDrawParticles3D::triggerNowChanged);
    ofRemoveListener(killAllNow->parameters.parameterChangedE(),this,&TXDrawParticles3D::killAllNowChanged);
}

void TXDrawParticles3D::setup () {
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
        
    holdModParamBoolArgs.name = "lockDiffuseColorAtStart";
    holdModParamBoolArgs.fixedValue = false;
    lockDiffuseColorAtStart = createModParameter(holdModParamBoolArgs);
    parameters.add(lockDiffuseColorAtStart->parameters);
    
    holdModParamBoolArgs.name = "lockAmbientColorAtStart";
    holdModParamBoolArgs.fixedValue = false;
    lockAmbientColorAtStart = createModParameter(holdModParamBoolArgs);
    parameters.add(lockAmbientColorAtStart->parameters);
    
    holdModParamBoolArgs.name = "lockSpecularColorAtStart";
    holdModParamBoolArgs.fixedValue = false;
    lockSpecularColorAtStart = createModParameter(holdModParamBoolArgs);
    parameters.add(lockSpecularColorAtStart->parameters);
    
    holdModParamBoolArgs.name = "lockEmissiveColorAtStart";
    holdModParamBoolArgs.fixedValue = false;
    lockEmissiveColorAtStart = createModParameter(holdModParamBoolArgs);
    parameters.add(lockEmissiveColorAtStart->parameters);
    
    holdModParamBoolArgs.name = "lockWidthAtStart";
    holdModParamBoolArgs.fixedValue = false;
    lockWidthAtStart = createModParameter(holdModParamBoolArgs);
    parameters.add(lockWidthAtStart->parameters);
    
    holdModParamBoolArgs.name = "lockHeightAtStart";
    holdModParamBoolArgs.fixedValue = false;
    lockHeightAtStart = createModParameter(holdModParamBoolArgs);
    parameters.add(lockHeightAtStart->parameters);
    
    holdModParamBoolArgs.name = "lockDepthAtStart";
    holdModParamBoolArgs.fixedValue = false;
    lockDepthAtStart = createModParameter(holdModParamBoolArgs);
    parameters.add(lockDepthAtStart->parameters);
    
    holdModParamBoolArgs.name = "lockRadiusAtStart";
    holdModParamBoolArgs.fixedValue = false;
    lockRadiusAtStart = createModParameter(holdModParamBoolArgs);
    parameters.add(lockRadiusAtStart->parameters);
    
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
    
    holdModParamBoolArgs.name = "lockDanceWidthHeightDepthAtStart";
    holdModParamBoolArgs.fixedValue = false;
    lockDanceWidthHeightDepthAtStart = createModParameter(holdModParamBoolArgs);
    parameters.add(lockDanceWidthHeightDepthAtStart->parameters);
    
    holdModParamBoolArgs.name = "lockAttractionPointAtStart";
    holdModParamBoolArgs.fixedValue = false;
    lockAttractionPointAtStart = createModParameter(holdModParamBoolArgs);
    parameters.add(lockAttractionPointAtStart->parameters);
    
    holdModParamBoolArgs.name = "triggerContinuosly";
    holdModParamBoolArgs.fixedValue = false;
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
    
    parameters.add(maximumActiveParticles.set("maximumActiveParticles", totalNoParticles, 2, totalNoParticles));
    
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
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    spreadCenterX = createModParameter(holdModParamFloatArgs);
    parameters.add(spreadCenterX->parameters);
    
    holdModParamFloatArgs.name = "spreadCenterY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    spreadCenterY = createModParameter(holdModParamFloatArgs);
    parameters.add(spreadCenterY->parameters);
    
    holdModParamFloatArgs.name = "spreadCenterZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 0.0;
    spreadCenterZ = createModParameter(holdModParamFloatArgs);
    parameters.add(spreadCenterZ->parameters);
    
    holdModParamFloatArgs.name = "spreadWidth";
    holdModParamFloatArgs.fixedValue = 0.3;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    spreadWidth = createModParameter(holdModParamFloatArgs);
    parameters.add(spreadWidth->parameters);
    
    holdModParamFloatArgs.name = "spreadHeight";
    holdModParamFloatArgs.fixedValue = 0.3;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    spreadHeight = createModParameter(holdModParamFloatArgs);
    parameters.add(spreadHeight->parameters);
    
    holdModParamFloatArgs.name = "spreadDepth";
    holdModParamFloatArgs.fixedValue = 0.3;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    spreadDepth = createModParameter(holdModParamFloatArgs);
    parameters.add(spreadDepth->parameters);
    
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
    
    holdModParamFloatArgs.name = "posZPerlinMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    posZPerlinMix = createModParameter(holdModParamFloatArgs);
    parameters.add(posZPerlinMix->parameters);
    
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
    
    holdModParamFloatArgs.name = "posZPerlinSpeed";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
    posZPerlinSpeed = createModParameter(holdModParamFloatArgs);
    parameters.add(posZPerlinSpeed->parameters);
    
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
    
    holdModParamFloatArgs.name = "gravityZ";
    holdModParamFloatArgs.fixedValue = -0.05;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
    gravityZ = createModParameter(holdModParamFloatArgs);
    parameters.add(gravityZ->parameters);
    
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
    
    holdModParamFloatArgs.name = "velocityZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
    velocityZ = createModParameter(holdModParamFloatArgs);
    parameters.add(velocityZ->parameters);
    
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
    
    holdModParamFloatArgs.name = "attractionPointZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -1.0;
    holdModParamFloatArgs.hardMax = 2.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    attractionPointZ = createModParameter(holdModParamFloatArgs);
    parameters.add(attractionPointZ->parameters);
    
    holdModParamBoolArgs.name = "useWidthForHeight";
    holdModParamBoolArgs.fixedValue = false;
    useWidthForHeight = createModParameter(holdModParamBoolArgs);
    parameters.add(useWidthForHeight->parameters);
    
    holdModParamBoolArgs.name = "useWidthForDepth";
    holdModParamBoolArgs.fixedValue = false;
    useWidthForDepth = createModParameter(holdModParamBoolArgs);
    parameters.add(useWidthForDepth->parameters);
    
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
    
    holdModParamFloatArgs.name = "depth";
    holdModParamFloatArgs.fixedValue = 0.2;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    depth = createModParameter(holdModParamFloatArgs);
    parameters.add(depth->parameters);
    
    depthCurve.setValueArrayTo(1.0f);
    depthCurve.setName("depthCurve");
    parameters.add(depthCurve.parameters);
    
    holdModParamFloatArgs.name = "depthPerlinMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    depthPerlinMix = createModParameter(holdModParamFloatArgs);
    parameters.add(depthPerlinMix->parameters);
    
    holdModParamFloatArgs.name = "depthPerlinSpeed";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
    depthPerlinSpeed = createModParameter(holdModParamFloatArgs);
    parameters.add(depthPerlinSpeed->parameters);
    
    holdModParamFloatArgs.name = "radius";
    holdModParamFloatArgs.fixedValue = 0.2;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    radius = createModParameter(holdModParamFloatArgs);
    parameters.add(radius->parameters);
    
    radiusCurve.setValueArrayTo(1.0f);
    radiusCurve.setName("radiusCurve");
    parameters.add(radiusCurve.parameters);
    
    holdModParamFloatArgs.name = "radiusPerlinMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    radiusPerlinMix = createModParameter(holdModParamFloatArgs);
    parameters.add(radiusPerlinMix->parameters);
    
    holdModParamFloatArgs.name = "radiusPerlinSpeed";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
    radiusPerlinSpeed = createModParameter(holdModParamFloatArgs);
    parameters.add(radiusPerlinSpeed->parameters);
    
    holdModParamBoolArgs.name = "useScaleXForScaleY";
    holdModParamBoolArgs.fixedValue = false;
    useScaleXForScaleY = createModParameter(holdModParamBoolArgs);
    parameters.add(useScaleXForScaleY->parameters);
    
    holdModParamBoolArgs.name = "useScaleXForScaleZ";
    holdModParamBoolArgs.fixedValue = false;
    useScaleXForScaleZ = createModParameter(holdModParamBoolArgs);
    parameters.add(useScaleXForScaleZ->parameters);
    
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
    
    holdModParamFloatArgs.name = "scaleZ";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 2.0;
    scaleZ = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleZ->parameters);
    
    scaleZCurve.setValueArrayTo(1.0f);
    scaleZCurve.setName("scaleZCurve");
    parameters.add(scaleZCurve.parameters);
    
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
    
    holdModParamFloatArgs.name = "anchorZ";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    anchorZ = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorZ->parameters);
    
    anchorZCurve.setValueArrayTo(1.0f);
    anchorZCurve.setName("anchorZCurve");
    parameters.add(anchorZCurve.parameters);
    
    holdModParamFloatArgs.name = "rotationXOffset";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
    rotationXOffset = createModParameter(holdModParamFloatArgs);
    parameters.add(rotationXOffset->parameters);
    
    rotationXCurve.setValueArrayTo(1.0f);
    rotationXCurve.setName("rotationXCurve");
    parameters.add(rotationXCurve.parameters);
    
    holdModParamFloatArgs.name = "rotationXPerlinMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    rotationXPerlinMix = createModParameter(holdModParamFloatArgs);
    parameters.add(rotationXPerlinMix->parameters);
    
    holdModParamFloatArgs.name = "rotationXPerlinSpeed";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
    rotationXPerlinSpeed = createModParameter(holdModParamFloatArgs);
    parameters.add(rotationXPerlinSpeed->parameters);
    
    holdModParamFloatArgs.name = "rotationYOffset";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
    rotationYOffset = createModParameter(holdModParamFloatArgs);
    parameters.add(rotationYOffset->parameters);
    
    rotationYCurve.setValueArrayTo(1.0f);
    rotationYCurve.setName("rotationYCurve");
    parameters.add(rotationYCurve.parameters);
    
    holdModParamFloatArgs.name = "rotationYPerlinMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    rotationYPerlinMix = createModParameter(holdModParamFloatArgs);
    parameters.add(rotationYPerlinMix->parameters);
    
    holdModParamFloatArgs.name = "rotationYPerlinSpeed";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
    rotationYPerlinSpeed = createModParameter(holdModParamFloatArgs);
    parameters.add(rotationYPerlinSpeed->parameters);
    
    holdModParamFloatArgs.name = "rotationZOffset";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
    rotationZOffset = createModParameter(holdModParamFloatArgs);
    parameters.add(rotationZOffset->parameters);
    
    rotationZCurve.setValueArrayTo(1.0f);
    rotationZCurve.setName("rotationZCurve");
    parameters.add(rotationZCurve.parameters);
    
    holdModParamFloatArgs.name = "rotationZPerlinMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    rotationZPerlinMix = createModParameter(holdModParamFloatArgs);
    parameters.add(rotationZPerlinMix->parameters);
    
    holdModParamFloatArgs.name = "rotationZPerlinSpeed";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
    rotationZPerlinSpeed = createModParameter(holdModParamFloatArgs);
    parameters.add(rotationZPerlinSpeed->parameters);
    
    holdModParamFloatArgs.name = "dance_width";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    dance_width = createModParameter(holdModParamFloatArgs);
    parameters.add(dance_width->parameters);
    
    holdModParamFloatArgs.name = "dance_height";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    dance_height = createModParameter(holdModParamFloatArgs);
    parameters.add(dance_height->parameters);
    
    holdModParamFloatArgs.name = "dance_depth";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    dance_depth = createModParameter(holdModParamFloatArgs);
    parameters.add(dance_depth->parameters);
    
    // create dance pattern LFO & merge parameters
    dancePattern.setup("dance_");
    mergeParameters(dancePattern.parameters, dancePattern.modParameters);
    
    holdModParamBoolArgs.name = "dance_randomStartPhase";
    holdModParamBoolArgs.fixedValue = false;
    dance_randomStartPhase = createModParameter(holdModParamBoolArgs);
    parameters.add(dance_randomStartPhase->parameters);
    
    // create shape & merge parameters
   shape.setup("shape_");
    shape.positionX->setSoftMin(-20.0f);
    shape.positionX->setSoftMax(20.0f);
    shape.positionY->setSoftMin(-20.0f);
    shape.positionY->setSoftMax(20.0f);
    shape.positionZ->setSoftMin(-20.0f);
    shape.positionZ->setSoftMax(20.0f);
    mergeParameters(shape.parameters, shape.modParameters);
    
    // add listeners to relevent parameters:
    ofAddListener(triggerLevel->parameters.parameterChangedE(),this,&TXDrawParticles3D::triggerLevelChanged);
    ofAddListener(triggerNow->parameters.parameterChangedE(),this,&TXDrawParticles3D::triggerNowChanged);
    ofAddListener(killAllNow->parameters.parameterChangedE(),this,&TXDrawParticles3D::killAllNowChanged);

    // add listener to relevent parameters:
    maximumActiveParticles.addListener(this, &TXDrawParticles3D::maximumActiveParticlesChanged);

    // asset slots
    createImageAssetSlot("sourceImageAsset");
    
    // external image slots
    createExtImageModuleSlot("extSourceImageModule");
        
    // register Texture
    registerTexture();
    
    // initialise
    nextParticleIndex = 0;
    for (int i = 0; i < totalNoParticles; i++) {
        arrParticles[i].particleID = i;
    };
    // OLD
//    posXPerlin.setup(4, 2, 0.3, 100);
//    posYPerlin.setup(4, 2, 0.3, 200);
//    posZPerlin.setup(4, 2, 0.3, 200);
//    widthPerlin.setup(4, 2, 0.3, 300);
//    heightPerlin.setup(4, 2, 0.3, 400);
//    depthPerlin.setup(4, 2, 0.3, 400);
//    radiusPerlin.setup(4, 2, 0.3, 400);
//    rotationXPerlin.setup(4, 2, 0.3, 600);
//    rotationYPerlin.setup(4, 2, 0.3, 600);
//    rotationZPerlin.setup(4, 2, 0.3, 600);
    // TXSimplePerlin setup (int perlinTypeArg = PERLINTYPE_NORMAL, float speedArg = 1.0, float speedDivisorArg = 1.0,
    //            float phaseOffsetArg = 0.0, bool useMasterBpmArg = false, bool frozenArg = false, int randSeedArg = 0);

    dancePattern.lfoType->setFixedValue(1);
    dancePattern.cycleTimeBeats->setFixedValue(4);
    
    lastRecordedTriggerTime = 0;
    triggerConfirmed = false;
    triggerNowPrevious = false;
    killAllNowPrevious = false;
    resetTime();
    advanceBy(0);
};

void TXDrawParticles3D::update(){
    dancePattern.update();
//    for (int i = 0; i < totalNoParticles; i++) {
//        arrParticles[i].dancePattern.update();
//    };
    if (triggerConfirmed || triggerContinuosly->getBool()) {
        triggerParticles();
    };
}

void TXDrawParticles3D::draw() {
    // check before drawing
    if (!drawActive->getBool()) {
        return;
    };
    float holdHeight, holdDepth, holdScaleY, holdScaleZ;
    bool holdUseWidthForHeight = useWidthForHeight->getBool();
    bool holdUseWidthForDepth = useWidthForDepth->getBool();
    bool holdUseScaleXForScaleY = useScaleXForScaleY->getBool();
    bool holdUseScaleXForScaleZ = useScaleXForScaleZ->getBool();
    int   holdMaxWidth = shape.getMaxWidth();
    int   holdMaxHeight = shape.getMaxHeight();
    int   holdMaxDepth = shape.getMaxDepth();
    float holdSpreadCenterX = spreadCenterX->getFloat();
    float holdSpreadCenterY = spreadCenterY->getFloat();
    float holdSpreadCenterZ = spreadCenterZ->getFloat();
    bool  holdLockDiffuseColorAtStart = lockDiffuseColorAtStart->getBool();
    bool  holdLockAmbientColorAtStart = lockAmbientColorAtStart->getBool();
    bool  holdLockSpecularColorAtStart = lockSpecularColorAtStart->getBool();
    bool  holdLockEmissiveColorAtStart = lockEmissiveColorAtStart->getBool();
    
    // colors initially reset - can be overridden below
    shape.setMaterialDiffuseColor(shape.getCurrentDiffuseColor());
    shape.setMaterialAmbientColor(shape.getCurrentAmbientColor());
    shape.setMaterialSpecularColor(shape.getCurrentSpecularColor());
    shape.setMaterialEmissiveColor(shape.getCurrentEmissiveColor());
    
    // draw particles
    for (int i = 0; i < maximumActiveParticles; i++) {
        if (arrParticles[i].awake) {
            if (holdUseWidthForHeight) {
                holdHeight = arrParticles[i].width;
            } else {
                holdHeight = arrParticles[i].height;
            };
            if (holdUseWidthForDepth) {
                holdDepth = arrParticles[i].width;
            } else {
                holdDepth = arrParticles[i].depth;
            };
            if (holdUseScaleXForScaleY) {
                holdScaleY = arrParticles[i].scaleX;
            } else {
                holdScaleY = arrParticles[i].scaleY;
            };
            if (holdUseScaleXForScaleZ) {
                holdScaleZ = arrParticles[i].scaleX;
            } else {
                holdScaleZ = arrParticles[i].scaleZ;
            };
            if (holdLockDiffuseColorAtStart) {
                shape.setMaterialDiffuseColor(arrParticles[i].initialDiffuseColor);
            };
            if (holdLockAmbientColorAtStart) {
                shape.setMaterialAmbientColor(arrParticles[i].initialAmbientColor);
            };
            if (holdLockSpecularColorAtStart) {
                shape.setMaterialSpecularColor(arrParticles[i].initialSpecularColor);
            };
            if (holdLockEmissiveColorAtStart) {
                shape.setMaterialEmissiveColor(arrParticles[i].initialEmissiveColor);
            };
            drawParticle(arrParticles[i].posX, arrParticles[i].posY, arrParticles[i].posZ, arrParticles[i].width, holdHeight, holdDepth, arrParticles[i].radius, arrParticles[i].rotationX, arrParticles[i].rotationY, arrParticles[i].rotationZ, arrParticles[i].scaleX, holdScaleY, holdScaleZ, arrParticles[i].anchorX, arrParticles[i].anchorY, arrParticles[i].anchorZ);

        };
    };
}

void TXDrawParticles3D::drawParticle(float &posX, float &posY, float &posZ, float &width, float &height, float &depth, float &radius, float &rotationX, float &rotationY, float &rotationZ, float &widthScale, float &heightScale, float &depthScale, float &anchorX, float &anchorY, float &anchorZ){
    
    ofPushMatrix();
    shape.positionX->setFixedValue(posX);
    shape.positionY->setFixedValue(posY);
    shape.positionZ->setFixedValue(posZ);
    shape.width->setFixedValue(width);
    shape.height->setFixedValue(height);
    shape.depth->setFixedValue(depth);
    shape.radius->setFixedValue(radius);
    shape.rotateX->setFixedValue(rotationX);
    shape.rotateY->setFixedValue(rotationY);
    shape.rotateZ->setFixedValue(rotationZ);
    shape.scaleX->setFixedValue(widthScale);
    shape.scaleY->setFixedValue(heightScale);
    shape.scaleZ->setFixedValue(depthScale);
    shape.anchorX->setFixedValue(anchorX);
    shape.anchorY->setFixedValue(anchorY);
    shape.anchorZ->setFixedValue(anchorZ);
    shape.update();
    shape.draw();
    ofPopMatrix();
}

void TXDrawParticles3D::setParentSystem(TXSystem * parentSystemArg) {
    parentSystem = parentSystemArg;
    shape.setParentSystem(parentSystem);
}

void TXDrawParticles3D::triggerParticles() {
    bool trigger;
    float holdSpeed, holdLifetimeSecs, holdSpreadOffsetX, holdSpreadOffsetY, holdSpreadOffsetZ, spreadProportion;
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
        float holdScaleZStart = scaleZCurve.parameters.getFloat(0);
        float holdScaleZ = scaleZ->getFloat();
        float holdAnchorXStart = anchorXCurve.parameters.getFloat(0);
        float holdAnchorX = anchorX->getFloat();
        float holdAnchorYStart = anchorYCurve.parameters.getFloat(0);
        float holdAnchorY = anchorY->getFloat();
        float holdAnchorZStart = anchorZCurve.parameters.getFloat(0);
        float holdAnchorZ = anchorZ->getFloat();
        float holdVelocityX = velocityX->getFloat();
        float holdVelocityY = velocityY->getFloat();
        float holdVelocityZ = velocityZ->getFloat();
        float holdRotationXStart = rotationXCurve.parameters.getFloat(0);
        float holdRotationYStart = rotationYCurve.parameters.getFloat(0);
        float holdRotationZStart = rotationZCurve.parameters.getFloat(0);
        float holdWidth = width->getFloat();
        float holdHeight = height->getFloat();
        float holdDepth = depth->getFloat();
        float holdRadius = radius->getFloat();
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
                
                arrParticles[nextParticleIndex].trigger(i, holdNumParticlesPerTrigger, holdLifetimeSecs, startDelay, holdWidth, holdHeight, holdDepth,  holdRadius, holdScaleXStart * holdScaleX, holdScaleYStart * holdScaleY, holdScaleZStart * holdScaleZ, holdVelocityX, holdVelocityY, holdVelocityZ, holdRotationXStart, holdRotationYStart, holdRotationZStart, holdAnchorXStart, holdAnchorYStart, holdAnchorZStart);
                
                arrParticles[nextParticleIndex].resetInitialVariables();
                
                // only draw spread if more than 1 particle
                if (holdNumParticlesPerTrigger == 1) {
                    holdSpreadOffsetX = 0;
                    holdSpreadOffsetY = 0;
                    holdSpreadOffsetZ = 0;
                } else {
                    spreadProportion =  ofxTweenLite::tween ( 0.0, 1.0, indexProportion, (ofEaseFunction) (holdSpreadDistribution + distributionTypeOffset));
                    switch (holdSpreadType) {
                        case 0:
                            // "Spread 1: Circle",
                            holdSpreadOffsetX = 0.5 * sin(spreadProportion * TWO_PI);
                            holdSpreadOffsetY = 0.5 * cos(spreadProportion * TWO_PI);
                            holdSpreadOffsetZ = 0;
                            break;
                        case 1:
                            // "Spread 2: Horizontal Line",
                            holdSpreadOffsetX = -0.5 + spreadProportion;
                            holdSpreadOffsetY = 0;
                            holdSpreadOffsetZ = 0;
                            break;
                        case 2:
                            // "Spread 3: Vertical Line",
                            holdSpreadOffsetX = 0;
                            holdSpreadOffsetY =  -0.5 + spreadProportion;
                            holdSpreadOffsetZ = 0;
                            break;
                        case 3:
                            // "Spread 4: Diagonal Line",
                            holdSpreadOffsetX =  -0.5 + spreadProportion;
                            holdSpreadOffsetY =  -0.5 + spreadProportion;
                            holdSpreadOffsetZ = - spreadProportion;
                            break;
                        default:
                            holdSpreadOffsetX = 0;
                            holdSpreadOffsetY = 0;
                            holdSpreadOffsetZ = 0;
                            break;
                    };
                };
                arrParticles[nextParticleIndex].spreadOffsetX = ((1 - holdSpreadRandom) * holdSpreadOffsetX) + (holdSpreadRandom * arrParticles[nextParticleIndex].spreadRandX);
                arrParticles[nextParticleIndex].spreadOffsetY = ((1 - holdSpreadRandom) * holdSpreadOffsetY) + (holdSpreadRandom * arrParticles[nextParticleIndex].spreadRandY);
                arrParticles[nextParticleIndex].spreadOffsetZ = ((1 - holdSpreadRandom) * holdSpreadOffsetZ) + (holdSpreadRandom * arrParticles[nextParticleIndex].spreadRandZ);
                
                // initialise dancePattern lfo with current vals
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
//void TXDrawParticles3D::setTime(float timeArg){
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

void TXDrawParticles3D::resetTime() {
    currentTime = 0.0;
    phase = 0;
    lastRecordedTriggerTime = 0.0;
    killAllParticles();
}

void TXDrawParticles3D::killAllParticles(int startIndex) {
    for (int i = startIndex; i < totalNoParticles; i++){
        arrParticles[i].kill();
    };
}

float  TXDrawParticles3D::adjustPerlin(float input, float scaleArg) {
    float   holdVal = ((scaleArg * input) + 1) * 0.5;
    return  holdVal;
}

void TXDrawParticles3D::advanceBy(float timeDeltaArg) {
	float holdPhase;
    float holdSpeed;
    float holdAttractionCurve;
    float holdWidthCurve;
    float holdHeightCurve;
    float holdDepthCurve;
    float holdRadiusCurve;
    float holdAlphaCurve;
    float holdWidth;
    float holdHeight;
    float holdDepth;
    float holdRadius;
    float holdAge;
    float holdAgeProportion;
    float holdLifetimeSecs;
    float holdRotationXCurve;
    float holdRotationYCurve;
    float holdRotationZCurve;
    float holdPerlinX, holdPerlinY, holdPerlinZ, holdPerlinW, holdPerlinH, holdPerlinD, holdPerlinA, holdPerlinRotX, holdPerlinRotY, holdPerlinRotZ, holdPerlinRadius;
    float holdVelocityX, holdVelocityY, holdVelocityZ;
    float holdAlphaScaleFinal;
    float holdScaleXCurve;
    float holdScaleYCurve;
    float holdScaleZCurve;
    float holdAnchorXCurve;
    float holdAnchorYCurve;
    float holdAnchorZCurve;
    float holdRotationXSum;
    float holdRotationYSum;
    float holdRotationZSum;
    float holdSpreadWidth, holdSpreadHeight, holdSpreadDepth;
    float holdSpreadOffsetX, holdSpreadOffsetY, holdSpreadOffsetZ;
    float holdSamplePositionX, holdSamplePositionY;
    float holdDanceX, holdDanceY, holdDanceZ;
    float holdDanceScaleX, holdDanceScaleY, holdDanceScaleZ;
    float holdAttractionPointX, holdAttractionPointY, holdAttractionPointZ, holdAttractionMoveX, holdAttractionMoveY, holdAttractionMoveZ;
    float holdSin, holdCos;
    float holdSumX, holdSumY, holdSumZ, holdOffset;
    
    if (useMasterBpm->getBool()) {
        holdSpeed = masterBpm / 60.0;
    } else {
        holdSpeed = bpm->getFloat() / 60.0;
    };
    currentTime += timeDeltaArg;
    holdPhase = (phase + (timeDeltaArg * holdSpeed  * stepTimeDivisor->getFloat() / stepTimeBeats->getFloat()));
    phase = fmod(holdPhase, 1.0f);
    
    float holdScaleX = scaleX->getFloat();
    float holdScaleY = scaleY->getFloat();
    float holdScaleZ = scaleZ->getFloat();
    float holdAnchorX = anchorX->getFloat();
    float holdAnchorY = anchorY->getFloat();
    float holdAnchorZ = anchorZ->getFloat();
    
    float holdRotationXOffset = rotationXOffset->getFloat();
    float holdRotationYOffset = rotationYOffset->getFloat();
    float holdRotationZOffset = rotationZOffset->getFloat();
    
    float holdGravityX = gravityX->getFloat();
    float holdGravityY = gravityY->getFloat();
    float holdGravityZ = gravityZ->getFloat();
    
    bool  holdLockWidthAtStart = lockWidthAtStart->getBool();
    bool  holdLockHeightAtStart = lockHeightAtStart->getBool();
    bool  holdLockDepthAtStart = lockDepthAtStart->getBool();
    bool  holdLockRadiusAtStart = lockRadiusAtStart->getBool();
    bool  holdLockRotationOffsetAtStart = lockRotationOffsetAtStart->getBool();
    bool  holdLockSpreadAtStart = lockSpreadAtStart->getBool();
    bool  holdLockScaleAtStart = lockScaleAtStart->getBool();
    bool  holdLockAnchorAtStart = lockAnchorAtStart->getBool();
    bool  holdLockDanceWidthHeightDepthAtStart = lockDanceWidthHeightDepthAtStart->getBool();
    bool  holdLockAttractionPointAtStart = lockAttractionPointAtStart->getBool();
    
    float holdPosXPerlinMix = posXPerlinMix->getFloat();
    float holdPosYPerlinMix = posYPerlinMix->getFloat();
    float holdPosZPerlinMix = posZPerlinMix->getFloat();
    float holdAttraction = attraction->getFloat();
    
    float holdUseScaleXForScaleY = useScaleXForScaleY->getBool();
    float holdUseScaleXForScaleZ = useScaleXForScaleZ->getBool();
    float holdUseWidthForHeight = useWidthForHeight->getBool();
    float holdUseWidthForDepth = useWidthForDepth->getBool();

    float v_posXPerlinSpeed = posXPerlinSpeed->getFloat();
    float v_posYPerlinSpeed = posYPerlinSpeed->getFloat();
    float v_posZPerlinSpeed = posZPerlinSpeed->getFloat();
    float v_widthPerlinSpeed = widthPerlinSpeed->getFloat();
    float v_heightPerlinSpeed = heightPerlinSpeed->getFloat();
    float v_depthPerlinSpeed = depthPerlinSpeed->getFloat();
    float v_radiusPerlinSpeed = radiusPerlinSpeed->getFloat();
    float v_rotationXPerlinSpeed = rotationXPerlinSpeed->getFloat();
    float v_rotationYPerlinSpeed = rotationYPerlinSpeed->getFloat();
    float v_rotationZPerlinSpeed = rotationZPerlinSpeed->getFloat();
    
    float v_posXPerlinMix = posXPerlinMix->getFloat();
    float v_posYPerlinMix = posYPerlinMix->getFloat();
    float v_posZPerlinMix = posZPerlinMix->getFloat();
    float v_widthPerlinMix = widthPerlinMix->getFloat();
    float v_heightPerlinMix = heightPerlinMix->getFloat();
    float v_depthPerlinMix = depthPerlinMix->getFloat();
    float v_radiusPerlinMix = radiusPerlinMix->getFloat();
    float v_rotationXPerlinMix = rotationXPerlinMix->getFloat();
    float v_rotationYPerlinMix = rotationYPerlinMix->getFloat();
    float v_rotationZPerlinMix = rotationZPerlinMix->getFloat();
    
    float v_width = width->getFloat();
    float v_height = height->getFloat();
    float v_depth = depth->getFloat();
    float v_radius = radius->getFloat();
    float v_rotationXOffset = rotationXOffset->getFloat();
    float v_rotationYOffset = rotationYOffset->getFloat();
    float v_rotationZOffset = rotationZOffset->getFloat();
    float v_spreadCenterX = spreadCenterX->getFloat();
    float v_spreadCenterY = spreadCenterY->getFloat();
    float v_spreadCenterZ = spreadCenterZ->getFloat();
    float v_spreadWidth = spreadWidth->getFloat();
    float v_spreadHeight = spreadHeight->getFloat();
    float v_spreadDepth = spreadDepth->getFloat();
    float v_dance_width = dance_width->getFloat();
    float v_dance_height = dance_height->getFloat();
    float v_dance_depth = dance_depth->getFloat();
    float v_attractionPointX = attractionPointX->getFloat();
    float v_attractionPointY = attractionPointY->getFloat();
    float v_attractionPointZ = attractionPointZ->getFloat();

    for (int i = 0; i < maximumActiveParticles; i++){
        if (arrParticles[i].alive) {
            arrParticles[i].advanceBy(timeDeltaArg, masterBpm);
            if (arrParticles[i].awake) {
                // adjust age & lifetime subtracting startdelay
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
                holdDepthCurve = depthCurve.interpolatedLookup(holdAgeProportion);
                holdRadiusCurve = radiusCurve.interpolatedLookup(holdAgeProportion);
                holdScaleXCurve = scaleXCurve.interpolatedLookup(holdAgeProportion);
                holdScaleYCurve = scaleYCurve.interpolatedLookup(holdAgeProportion);
                holdScaleZCurve = scaleZCurve.interpolatedLookup(holdAgeProportion);
                holdAnchorXCurve = anchorXCurve.interpolatedLookup(holdAgeProportion);
                holdAnchorYCurve = anchorYCurve.interpolatedLookup(holdAgeProportion);
                holdAnchorZCurve = anchorZCurve.interpolatedLookup(holdAgeProportion);
                holdRotationXCurve = rotationXCurve.interpolatedLookup(holdAgeProportion) * 360;
                holdRotationYCurve = rotationYCurve.interpolatedLookup(holdAgeProportion) * 360;
                holdRotationZCurve = rotationZCurve.interpolatedLookup(holdAgeProportion) * 360;
                
                arrParticles[i].posXPerlinPhase += timeDeltaArg * v_posXPerlinSpeed;
                arrParticles[i].posYPerlinPhase += timeDeltaArg * v_posYPerlinSpeed;;
                arrParticles[i].posZPerlinPhase += timeDeltaArg * v_posZPerlinSpeed;;
                arrParticles[i].widthPerlinPhase += timeDeltaArg * v_widthPerlinSpeed;;
                arrParticles[i].heightPerlinPhase += timeDeltaArg * v_heightPerlinSpeed;;
                arrParticles[i].depthPerlinPhase += timeDeltaArg * v_depthPerlinSpeed;;
                arrParticles[i].radiusPerlinPhase += timeDeltaArg * v_radiusPerlinSpeed;;
                arrParticles[i].rotationXPerlinPhase += timeDeltaArg * v_rotationXPerlinSpeed;;
                arrParticles[i].rotationYPerlinPhase += timeDeltaArg * v_rotationYPerlinSpeed;;
                arrParticles[i].rotationZPerlinPhase += timeDeltaArg * v_rotationZPerlinSpeed;;
                
                holdPerlinX = adjustPerlin(ofSignedNoise(arrParticles[i].posXPerlinPhase));
                holdPerlinY = adjustPerlin(ofSignedNoise(arrParticles[i].posYPerlinPhase));
                holdPerlinZ = adjustPerlin(ofSignedNoise(arrParticles[i].posZPerlinPhase));
                holdPerlinW = adjustPerlin(ofSignedNoise(arrParticles[i].widthPerlinPhase));
                holdPerlinH = adjustPerlin(ofSignedNoise(arrParticles[i].heightPerlinPhase));
                holdPerlinD = adjustPerlin(ofSignedNoise(arrParticles[i].depthPerlinPhase));
                holdPerlinRadius = adjustPerlin(ofSignedNoise(arrParticles[i].radiusPerlinPhase));
                holdPerlinRotX = adjustPerlin(ofSignedNoise(arrParticles[i].rotationXPerlinPhase));
                holdPerlinRotY = adjustPerlin(ofSignedNoise(arrParticles[i].rotationYPerlinPhase));
                holdPerlinRotZ = adjustPerlin(ofSignedNoise(arrParticles[i].rotationZPerlinPhase));
                
                // set initial variables
                if (!arrParticles[i].initialVariablesUpdated) {
                    arrParticles[i].initialWidth = v_width;
                    arrParticles[i].initialHeight = v_height;
                    arrParticles[i].initialDepth = v_depth;
                    arrParticles[i].initialRadius = v_radius;
                    arrParticles[i].initialScaleX = holdScaleX;
                    arrParticles[i].initialScaleY = holdScaleY;
                    arrParticles[i].initialScaleZ = holdScaleZ;
                    arrParticles[i].initialAnchorX = holdAnchorX;
                    arrParticles[i].initialAnchorY = holdAnchorY;
                    arrParticles[i].initialAnchorZ = holdAnchorZ;
                    arrParticles[i].initialRotationXOffset = v_rotationXOffset;
                    arrParticles[i].initialRotationYOffset = v_rotationYOffset;
                    arrParticles[i].initialRotationZOffset = v_rotationZOffset;
                    arrParticles[i].initialSpreadCenterX = v_spreadCenterX;
                    arrParticles[i].initialSpreadCenterY = v_spreadCenterY;
                    arrParticles[i].initialSpreadCenterZ = v_spreadCenterZ;
                    arrParticles[i].initialSpreadWidth = v_spreadWidth;
                    arrParticles[i].initialSpreadHeight = v_spreadHeight;
                    arrParticles[i].initialSpreadDepth = v_spreadDepth;
                    arrParticles[i].initialDanceWidth = v_dance_width;
                    arrParticles[i].initialDanceHeight = v_dance_height;
                    arrParticles[i].initialDanceDepth = v_dance_depth;
                    arrParticles[i].initialAttractionPointX = v_attractionPointX;
                    arrParticles[i].initialAttractionPointY = v_attractionPointY;
                    arrParticles[i].initialAttractionPointZ = v_attractionPointZ;
                    arrParticles[i].initialPosX = arrParticles[i].posX;
                    arrParticles[i].initialPosY = arrParticles[i].posY;
                    arrParticles[i].initialPosZ = arrParticles[i].posZ;
                    arrParticles[i].initialDiffuseColor = shape.getCurrentDiffuseColor();
                    arrParticles[i].initialAmbientColor = shape.getCurrentAmbientColor();
                    arrParticles[i].initialSpecularColor = shape.getCurrentSpecularColor();
                    arrParticles[i].initialEmissiveColor = shape.getCurrentEmissiveColor();
                    arrParticles[i].initialVariablesUpdated = true;
                };
                
                holdVelocityX = arrParticles[i].velocityX + (holdGravityX * timeDeltaArg);
                holdVelocityY = arrParticles[i].velocityY + (holdGravityY * timeDeltaArg);
                holdVelocityZ = arrParticles[i].velocityZ + (holdGravityZ * timeDeltaArg);
                
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
                if (holdLockDepthAtStart) {
                    holdDepth = arrParticles[i].initialDepth * holdDepthCurve;
                } else {
                    holdDepth = v_depth * holdDepthCurve;
                };
                if (holdLockRadiusAtStart) {
                    holdRadius = arrParticles[i].initialRadius * holdRadiusCurve;
                } else {
                    holdRadius = v_radius * holdRadiusCurve;
                };
                if (holdLockRotationOffsetAtStart) {
                    holdRotationXSum = holdRotationXCurve + arrParticles[i].initialRotationXOffset;
                    holdRotationYSum = holdRotationYCurve + arrParticles[i].initialRotationYOffset;
                    holdRotationZSum = holdRotationZCurve + arrParticles[i].initialRotationZOffset;
                } else {
                    holdRotationXSum = holdRotationXCurve + v_rotationXOffset;
                    holdRotationYSum = holdRotationYCurve + v_rotationYOffset;
                    holdRotationZSum = holdRotationZCurve + v_rotationZOffset;
                };
                if (holdLockSpreadAtStart) {
                    holdSpreadWidth = arrParticles[i].initialSpreadWidth;
                    holdSpreadHeight = arrParticles[i].initialSpreadHeight;
                    holdSpreadDepth = arrParticles[i].initialSpreadDepth;
                } else {
                    holdSpreadWidth = v_spreadWidth;
                    holdSpreadHeight = v_spreadHeight;
                    holdSpreadDepth = v_spreadDepth;
                };
                if (holdLockDanceWidthHeightDepthAtStart) {
                    holdDanceScaleX = arrParticles[i].initialDanceWidth;
                    holdDanceScaleY = arrParticles[i].initialDanceHeight;
                    holdDanceScaleZ = arrParticles[i].initialDanceDepth;
                } else {
                    holdDanceScaleX = v_dance_width;
                    holdDanceScaleY = v_dance_height;
                    holdDanceScaleZ = v_dance_depth;
                };
                if (holdLockAttractionPointAtStart) {
                    holdAttractionPointX = arrParticles[i].initialAttractionPointX;
                    holdAttractionPointY = arrParticles[i].initialAttractionPointY;
                    holdAttractionPointZ = arrParticles[i].initialAttractionPointZ;
                } else {
                    holdAttractionPointX = v_attractionPointX;
                    holdAttractionPointY = v_attractionPointY;
                    holdAttractionPointZ = v_attractionPointZ;
                };
                
                holdSpreadOffsetX = arrParticles[i].spreadOffsetX * holdSpreadWidth;
                holdSpreadOffsetY = arrParticles[i].spreadOffsetY * holdSpreadHeight;
                holdSpreadOffsetZ = arrParticles[i].spreadOffsetZ * holdSpreadDepth;

                arrParticles[i].velocityX = holdVelocityX;
                arrParticles[i].velocityY = holdVelocityY;
                arrParticles[i].velocityZ = holdVelocityZ;
                
                holdDanceX = (arrParticles[i].dancePattern.positionX - 0.5) *  holdDanceScaleX;
                holdDanceY = (arrParticles[i].dancePattern.positionY - 0.5) *  holdDanceScaleY;
                holdDanceZ = (arrParticles[i].dancePattern.positionZ - 0.5) *  holdDanceScaleZ;

                holdSumX = ((1-holdPosXPerlinMix) * (holdSpreadOffsetX + v_spreadCenterX)) + (holdPosXPerlinMix * holdPerlinX) + (holdVelocityX * holdAge) + holdDanceX;
                holdSumY = ((1-holdPosYPerlinMix) * (holdSpreadOffsetY + v_spreadCenterY)) + (holdPosYPerlinMix * holdPerlinY) + (holdVelocityY * holdAge) + holdDanceY;
                holdSumZ = ((1-holdPosZPerlinMix) * (holdSpreadOffsetZ + v_spreadCenterZ)) + (holdPosZPerlinMix * holdPerlinZ) + (holdVelocityZ * holdAge) + holdDanceZ;
                
                if (holdAttraction != 0) {
                    float distX, distY, distZ, holdAttractionProp;
                    distX = abs(holdAttractionPointX - holdSumX);
                    distY = abs(holdAttractionPointY - holdSumY);
                    distZ = abs(holdAttractionPointZ - holdSumZ);
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
                    if (holdSumZ < holdAttractionPointZ) {
                        holdAttractionMoveZ = holdAttractionProp * distZ;
                    } else {
                        holdAttractionMoveZ = holdAttractionProp * -distZ;
                    };
                } else {
                    holdAttractionMoveX = 0;
                    holdAttractionMoveY = 0;
                    holdAttractionMoveZ = 0;
                };
                
                arrParticles[i].posX = holdSumX + holdAttractionMoveX;
                arrParticles[i].posY = holdSumY + holdAttractionMoveY;
                arrParticles[i].posZ = holdSumZ + holdAttractionMoveZ;
                
                arrParticles[i].width = ((1-v_widthPerlinMix) * holdWidth) + (v_widthPerlinMix * holdPerlinW);
                if (holdUseWidthForHeight) {
                    arrParticles[i].height = arrParticles[i].width;
                } else {
                    arrParticles[i].height = ((1-v_heightPerlinMix) * holdHeight) + (v_heightPerlinMix * holdPerlinH);
                };
                if (holdUseWidthForDepth) {
                    arrParticles[i].depth = arrParticles[i].width;
                } else {
                    arrParticles[i].depth = ((1-v_depthPerlinMix) * holdDepth) + (v_depthPerlinMix * holdPerlinD);
                };
                arrParticles[i].radius = ((1-v_radiusPerlinMix) * holdRadius) + (v_radiusPerlinMix * holdPerlinRadius);
                
                arrParticles[i].rotationX = ((1-v_rotationXPerlinMix) * holdRotationXSum) + (v_rotationXPerlinMix * ((holdPerlinRotX * 360) -180));
                arrParticles[i].rotationY = ((1-v_rotationYPerlinMix) * holdRotationYSum) + (v_rotationYPerlinMix * ((holdPerlinRotY * 360) -180));
                arrParticles[i].rotationZ = ((1-v_rotationZPerlinMix) * holdRotationZSum) + (v_rotationZPerlinMix * ((holdPerlinRotZ * 360) -180));
                
                if (holdLockScaleAtStart) {
                    arrParticles[i].scaleX = holdScaleXCurve * arrParticles[i].initialScaleX;
                    if (holdUseScaleXForScaleY) {
                        arrParticles[i].scaleY = arrParticles[i].scaleX;
                    } else {
                        arrParticles[i].scaleY = holdScaleYCurve * arrParticles[i].initialScaleY;
                    };
                    if (holdUseScaleXForScaleZ) {
                        arrParticles[i].scaleZ = arrParticles[i].scaleX;
                    } else {
                        arrParticles[i].scaleZ = holdScaleZCurve * arrParticles[i].initialScaleZ;
                    };
                } else {
                    arrParticles[i].scaleX = holdScaleXCurve * holdScaleX;
                    if (holdUseScaleXForScaleY) {
                        arrParticles[i].scaleY = arrParticles[i].scaleX;
                    } else {
                        arrParticles[i].scaleY = holdScaleYCurve * holdScaleY;
                    };
                    if (holdUseScaleXForScaleZ) {
                        arrParticles[i].scaleZ = arrParticles[i].scaleX;
                    } else {
                        arrParticles[i].scaleZ = holdScaleZCurve * holdScaleZ;
                    };
                };
                if (holdLockAnchorAtStart) {
                    arrParticles[i].anchorX = holdAnchorXCurve * arrParticles[i].initialAnchorX;
                    arrParticles[i].anchorY = holdAnchorYCurve * arrParticles[i].initialAnchorY;
                    arrParticles[i].anchorZ = holdAnchorZCurve * arrParticles[i].initialAnchorZ;
                } else {
                    arrParticles[i].anchorX = holdAnchorXCurve * holdAnchorX;
                    arrParticles[i].anchorY = holdAnchorYCurve * holdAnchorY;
                    arrParticles[i].anchorZ = holdAnchorZCurve * holdAnchorZ;
                };
            };
        };
    };
}

///////////////////////////////////////////////////////

void  TXDrawParticles3D::imageAssetSlotChanged(string slotNameArg) {
    int sourceImageAssetID, assetBankNo;
    if (slotNameArg == "sourceImageAsset") {
        sourceImageAssetID = getImageAssetIDSlot("sourceImageAsset").first;
        assetBankNo = getImageAssetIDSlot("sourceImageAsset").second;
        shape.setImageAssetSlot(slotNameArg, sourceImageAssetID, assetBankNo);
    };
}

int TXDrawParticles3D::getTextureWidth() {
    return shape.getTextureWidth();
}

int TXDrawParticles3D::getTextureHeight() {
    return shape.getTextureHeight();
}

ofTexture *  TXDrawParticles3D::getTexture() {
    return shape.getTexture();
}

ofPixelsRef TXDrawParticles3D::getPixels() {
    return shape.getPixels() ;
}

/////////////////////////////////////////

void  TXDrawParticles3D::triggerLevelChanged(ofAbstractParameter & parameterArg){
    float holdTriggerThreshold = triggerThreshold->getFloat();
    float holdTriggerLevel = triggerLevel->getFloat();
    // if rising above threshold
    if ((triggerPrevious < holdTriggerThreshold) && (holdTriggerLevel >= holdTriggerThreshold)) {
        triggerConfirmed = true;
    };
    triggerPrevious = holdTriggerLevel;
}

void  TXDrawParticles3D::triggerNowChanged(ofAbstractParameter & parameterArg){
    float holdTriggerNow = triggerNow->getBool();
    // if changed to on, confirm
    if ((triggerNowPrevious == 0) && (holdTriggerNow == 1)) {
        triggerConfirmed = true;
    };
    triggerNowPrevious = holdTriggerNow;
}

void  TXDrawParticles3D::killAllNowChanged(ofAbstractParameter & parameterArg){
    float holdKillAllNow = killAllNow->getBool();
    // if changed to on
    if ((killAllNowPrevious == 0) && (holdKillAllNow == 1)) {
        killAllParticles();
    };
    killAllNowPrevious = holdKillAllNow;
}

void  TXDrawParticles3D::maximumActiveParticlesChanged(int & intArg){
    int total = totalNoParticles;
    int holdNo = maximumActiveParticles;
    maximumActiveParticles = min(holdNo, total);
    killAllParticles(maximumActiveParticles);
}

//////////////////////////////////////////////////////////////


float TXDrawParticles3D::interpolate(float point1, float point2, float inbetween, bool smooth) {
    float holdVal;
    
    if (smooth) {
        holdVal = TXFunctions::cosineInterpolate(point1, point2, inbetween);
    } else {
        holdVal = point1  + (inbetween * (point2 - point1));
    };
    
    return holdVal;
}

