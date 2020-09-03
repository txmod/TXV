/*
 *  Copyright 2018 Paul Miller. All rights reserved.
 */

#include "TXSystem.h"
#include "TXWaveTerrain.h"
#include "TXFunctions.h"

// constructor
TXWaveTerrain::TXWaveTerrain() {
    setup();
}

// destructor
TXWaveTerrain::~TXWaveTerrain() {
    // remove listeners to relevent parameters:
    ofRemoveListener(colorMixCurveA.parameters.parameterChangedE(),this,&TXWaveTerrain::colorMixImageChanged);
    ofRemoveListener(colorMixCurveB.parameters.parameterChangedE(),this,&TXWaveTerrain::colorMixImageChanged);
    
    ofRemoveListener(lookupCurve1A.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesImageChanged);
    ofRemoveListener(lookupCurve1B.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesImageChanged);
    ofRemoveListener(lookupCurve2A.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesImageChanged);
    ofRemoveListener(lookupCurve2B.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesImageChanged);
    ofRemoveListener(lookupCurve3A.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesImageChanged);
    ofRemoveListener(lookupCurve3B.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesImageChanged);
    ofRemoveListener(lookupCurve4A.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesImageChanged);
    ofRemoveListener(lookupCurve4B.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesImageChanged);
    
    ofRemoveListener(colorHueCurveA.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesHSLImageChanged);
    ofRemoveListener(colorHueCurveB.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesHSLImageChanged);
    ofRemoveListener(colorSaturationCurveA.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesHSLImageChanged);
    ofRemoveListener(colorSaturationCurveB.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesHSLImageChanged);
    ofRemoveListener(colorBrightnessCurveA.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesHSLImageChanged);
    ofRemoveListener(colorBrightnessCurveB.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesHSLImageChanged);
    ofRemoveListener(colorAlphaCurveA.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesHSLImageChanged);
    ofRemoveListener(colorAlphaCurveB.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesHSLImageChanged);
}

void TXWaveTerrain::setup(){
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    float hardMinVal = -100.0;
    float hardMaxVal = 100.0;
    float softMinVal = -2.0;
    float softMaxVal = 2.0;
    
    // create input paramaters
    initialiseParameters();
 
    // terrainStructure;  // using 1/2/3/4 layers
    parameters.add(terrainStructure.set("terrainStructure", 0, 0, totalTerrainStructureTypes - 1));
    
    parameters.add(layerABJoinProcess.set("layerABJoinProcess", 0, 0, totalBinaryOpProcesses - 1));
    parameters.add(layerBCJoinProcess.set("layerBCJoinProcess", 0, 0, totalBinaryOpProcesses - 1));
    parameters.add(layerCDJoinProcess.set("layerCDJoinProcess", 0, 0, totalBinaryOpProcesses - 1));
    
    holdModParamFloatArgs.name = "squeezeX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -1.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
    squeezeX = createModParameter(holdModParamFloatArgs);
    parameters.add(squeezeX->parameters);
    
    holdModParamFloatArgs.name = "squeezeY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -1.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
    squeezeY = createModParameter(holdModParamFloatArgs);
    parameters.add(squeezeY->parameters);
    
    holdModParamFloatArgs.name = "skewX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -1.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
    skewX = createModParameter(holdModParamFloatArgs);
    parameters.add(skewX->parameters);
    
    holdModParamFloatArgs.name = "skewY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -1.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
    skewY = createModParameter(holdModParamFloatArgs);
    parameters.add(skewY->parameters);
    
    parameters.add(outputRangeProcess.set("outputRangeProcess", 0, 0, 2));
    
    holdModParamFloatArgs.name = "outputRangeMin";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    outputRangeMin = createModParameter(holdModParamFloatArgs);
    parameters.add(outputRangeMin->parameters);
    
    holdModParamFloatArgs.name = "outputRangeMax";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    outputRangeMax = createModParameter(holdModParamFloatArgs);
    parameters.add(outputRangeMax->parameters);
    
    // Curves

    colorMixCurveA.setValueArrayToRamp(0, 1);
    colorMixCurveA.setName("colorMixCurveA");
    parameters.add(colorMixCurveA.parameters);
    
    colorMixCurveB.setValueArrayToRamp(0, 1);
    colorMixCurveB.setName("colorMixCurveB");
    parameters.add(colorMixCurveB.parameters);
    
    holdModParamFloatArgs.name = "colorMixCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    colorMixCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(colorMixCurveMorph->parameters);
    
    holdModParamFloatArgs.name = "colorMixCurvePhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    colorMixCurvePhase = createModParameter(holdModParamFloatArgs);
    parameters.add(colorMixCurvePhase->parameters);
    
    lookupCurve1A.setValueArrayToRamp(0, 1);
    lookupCurve1A.setName("lookupCurve1A");
    parameters.add(lookupCurve1A.parameters);
    
    lookupCurve1B.setValueArrayToRamp(0, 1);
    lookupCurve1B.setName("lookupCurve1B");
    parameters.add(lookupCurve1B.parameters);
    
    holdModParamFloatArgs.name = "lookupCurve1Morph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    lookupCurve1Morph = createModParameter(holdModParamFloatArgs);
    parameters.add(lookupCurve1Morph->parameters);
    
    holdModParamFloatArgs.name = "lookupCurve1Phase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    lookupCurve1Phase = createModParameter(holdModParamFloatArgs);
    parameters.add(lookupCurve1Phase->parameters);
    
    lookupCurve2A.setValueArrayToRamp(0, 1);
    lookupCurve2A.setName("lookupCurve2A");
    parameters.add(lookupCurve2A.parameters);
    
    lookupCurve2B.setValueArrayToRamp(0, 1);
    lookupCurve2B.setName("lookupCurve2B");
    parameters.add(lookupCurve2B.parameters);
    
    holdModParamFloatArgs.name = "lookupCurve2Morph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    lookupCurve2Morph = createModParameter(holdModParamFloatArgs);
    parameters.add(lookupCurve2Morph->parameters);
    
    holdModParamFloatArgs.name = "lookupCurve2Phase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    lookupCurve2Phase = createModParameter(holdModParamFloatArgs);
    parameters.add(lookupCurve2Phase->parameters);
    
    lookupCurve3A.setValueArrayToRamp(0, 1);
    lookupCurve3A.setName("lookupCurve3A");
    parameters.add(lookupCurve3A.parameters);
    
    lookupCurve3B.setValueArrayToRamp(0, 1);
    lookupCurve3B.setName("lookupCurve3B");
    parameters.add(lookupCurve3B.parameters);
    
    holdModParamFloatArgs.name = "lookupCurve3Morph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    lookupCurve3Morph = createModParameter(holdModParamFloatArgs);
    parameters.add(lookupCurve3Morph->parameters);
    
    holdModParamFloatArgs.name = "lookupCurve3Phase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    lookupCurve3Phase = createModParameter(holdModParamFloatArgs);
    parameters.add(lookupCurve3Phase->parameters);
    
    lookupCurve4A.setValueArrayToRamp(0, 1);
    lookupCurve4A.setName("lookupCurve4A");
    parameters.add(lookupCurve4A.parameters);
    
    lookupCurve4B.setValueArrayToRamp(0, 1);
    lookupCurve4B.setName("lookupCurve4B");
    parameters.add(lookupCurve4B.parameters);
    
    holdModParamFloatArgs.name = "lookupCurve4Morph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    lookupCurve4Morph = createModParameter(holdModParamFloatArgs);
    parameters.add(lookupCurve4Morph->parameters);
    
    holdModParamFloatArgs.name = "lookupCurve4Phase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    lookupCurve4Phase = createModParameter(holdModParamFloatArgs);
    parameters.add(lookupCurve4Phase->parameters);
    
    holdModParamFloatArgs.name = "perlinLayer1Mix";  // perlinLayer defaults: 0.533, 0.267, 0.133, 0.067
    holdModParamFloatArgs.fixedValue = 0.533;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    perlinLayer1Mix = createModParameter(holdModParamFloatArgs);
    parameters.add(perlinLayer1Mix->parameters);
    
    holdModParamFloatArgs.name = "perlinLayer2Mix";
    holdModParamFloatArgs.fixedValue = 0.267;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    perlinLayer2Mix = createModParameter(holdModParamFloatArgs);
    parameters.add(perlinLayer2Mix->parameters);
    
    holdModParamFloatArgs.name = "perlinLayer3Mix";
    holdModParamFloatArgs.fixedValue = 0.133;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    perlinLayer3Mix = createModParameter(holdModParamFloatArgs);
    parameters.add(perlinLayer3Mix->parameters);
    
    holdModParamFloatArgs.name = "perlinLayer4Mix";
    holdModParamFloatArgs.fixedValue = 0.067;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    perlinLayer4Mix = createModParameter(holdModParamFloatArgs);
    parameters.add(perlinLayer4Mix->parameters);
    
    parameters.add(coloringMethod.set("coloringMethod", 0, 0, totalColoringMethods - 1));
    
    holdModParamFloatArgs.name = "color1Hue";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    color1Hue = createModParameter(holdModParamFloatArgs);
    parameters.add(color1Hue->parameters);
    
    holdModParamFloatArgs.name = "color1HueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    color1HueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(color1HueRotate->parameters);
    
    holdModParamFloatArgs.name = "color1Saturation";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    color1Saturation = createModParameter(holdModParamFloatArgs);
    parameters.add(color1Saturation->parameters);
    
    holdModParamFloatArgs.name = "color1Brightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    color1Brightness = createModParameter(holdModParamFloatArgs);
    parameters.add(color1Brightness->parameters);
    
    holdModParamFloatArgs.name = "color1Alpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    color1Alpha = createModParameter(holdModParamFloatArgs);
    parameters.add(color1Alpha->parameters);
    
    holdModParamBoolArgs.name = "color1HSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    color1HSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(color1HSBAsRGB->parameters);
    
    holdModParamFloatArgs.name = "color2Hue";
    holdModParamFloatArgs.fixedValue = 0.25;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    color2Hue = createModParameter(holdModParamFloatArgs);
    parameters.add(color2Hue->parameters);
    
    holdModParamFloatArgs.name = "color2HueRotate";
    holdModParamFloatArgs.fixedValue = 0.25;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    color2HueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(color2HueRotate->parameters);
    
    holdModParamFloatArgs.name = "color2Saturation";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    color2Saturation = createModParameter(holdModParamFloatArgs);
    parameters.add(color2Saturation->parameters);
    
    holdModParamFloatArgs.name = "color2Brightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    color2Brightness = createModParameter(holdModParamFloatArgs);
    parameters.add(color2Brightness->parameters);
    
    holdModParamFloatArgs.name = "color2Alpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    color2Alpha = createModParameter(holdModParamFloatArgs);
    parameters.add(color2Alpha->parameters);
    
    holdModParamBoolArgs.name = "color2HSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    color2HSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(color2HSBAsRGB->parameters);
    
    holdModParamFloatArgs.name = "color3Hue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    color3Hue = createModParameter(holdModParamFloatArgs);
    parameters.add(color3Hue->parameters);
    
    holdModParamFloatArgs.name = "color3HueRotate";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    color3HueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(color3HueRotate->parameters);
    
    holdModParamFloatArgs.name = "color3Saturation";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    color3Saturation = createModParameter(holdModParamFloatArgs);
    parameters.add(color3Saturation->parameters);
    
    holdModParamFloatArgs.name = "color3Brightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    color3Brightness = createModParameter(holdModParamFloatArgs);
    parameters.add(color3Brightness->parameters);
    
    holdModParamFloatArgs.name = "color3Alpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    color3Alpha = createModParameter(holdModParamFloatArgs);
    parameters.add(color3Alpha->parameters);
    
    holdModParamBoolArgs.name = "color3HSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    color3HSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(color3HSBAsRGB->parameters);
    
    colorHueCurveA.setValueArrayToRamp(0, 1);
    colorHueCurveA.setName("colorHueCurveA");
    parameters.add(colorHueCurveA.parameters);
    
    colorHueCurveB.setValueArrayToRamp(0, 1);
    colorHueCurveB.setName("colorHueCurveB");
    parameters.add(colorHueCurveB.parameters);
    
    holdModParamFloatArgs.name = "colorHueCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    colorHueCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(colorHueCurveMorph->parameters);
    
    holdModParamFloatArgs.name = "colorHueCurveRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    colorHueCurveRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(colorHueCurveRotate->parameters);
    
    colorSaturationCurveA.setValueArrayToRamp(0, 1);
    colorSaturationCurveA.setName("colorSaturationCurveA");
    parameters.add(colorSaturationCurveA.parameters);
    
    colorSaturationCurveB.setValueArrayToRamp(0, 1);
    colorSaturationCurveB.setName("colorSaturationCurveB");
    parameters.add(colorSaturationCurveB.parameters);
    
    holdModParamFloatArgs.name = "colorSaturationCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    colorSaturationCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(colorSaturationCurveMorph->parameters);
    
    colorBrightnessCurveA.setValueArrayToRamp(0, 1);
    colorBrightnessCurveA.setName("colorBrightnessCurveA");
    parameters.add(colorBrightnessCurveA.parameters);
    
    colorBrightnessCurveB.setValueArrayToRamp(0, 1);
    colorBrightnessCurveB.setName("colorBrightnessCurveB");
    parameters.add(colorBrightnessCurveB.parameters);
    
    holdModParamFloatArgs.name = "colorBrightnessCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    colorBrightnessCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(colorBrightnessCurveMorph->parameters);
    
    colorAlphaCurveA.setValueArrayTo(1.0);
    colorAlphaCurveA.setName("colorAlphaCurveA");
    parameters.add(colorAlphaCurveA.parameters);
    
    colorAlphaCurveB.setValueArrayTo(1.0);
    colorAlphaCurveB.setName("colorAlphaCurveB");
    parameters.add(colorAlphaCurveB.parameters);
    
    holdModParamFloatArgs.name = "colorAlphaCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    colorAlphaCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(colorAlphaCurveMorph->parameters);
    
    // Layers:
    
    parameters.add(layerA_usePolarCoords.set("layerA_usePolarCoords", false));
    
    holdModParamFloatArgs.name = "layerA_rotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
    layerA_rotate = createModParameter(holdModParamFloatArgs);
    parameters.add(layerA_rotate->parameters);
    
    holdModParamFloatArgs.name = "layerA_inputXMin";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerA_inputXMin = createModParameter(holdModParamFloatArgs);
    parameters.add(layerA_inputXMin->parameters);
    
    holdModParamFloatArgs.name = "layerA_inputXMax";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerA_inputXMax = createModParameter(holdModParamFloatArgs);
    parameters.add(layerA_inputXMax->parameters);
    
    holdModParamFloatArgs.name = "layerA_inputYMin";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerA_inputYMin = createModParameter(holdModParamFloatArgs);
    parameters.add(layerA_inputYMin->parameters);
    
    holdModParamFloatArgs.name = "layerA_inputYMax";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerA_inputYMax = createModParameter(holdModParamFloatArgs);
    parameters.add(layerA_inputYMax->parameters);
    
    parameters.add(layerA_offsetProcs12InSeries.set("layerA_offsetProcs12InSeries", false));
    parameters.add(layerA_offsetProcess1Active.set("layerA_offsetProcess1Active", false));

    parameters.add(layerA_offsetProcess1Type.set("layerA_offsetProcess1Type", 0, 0, totalUnaryOpProcesses - 1));
    
    holdModParamFloatArgs.name = "layerA_offsetProcess1MultInputX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerA_offsetProcess1MultInputX = createModParameter(holdModParamFloatArgs);
    parameters.add(layerA_offsetProcess1MultInputX->parameters);
    
    holdModParamFloatArgs.name = "layerA_offsetProcess1AddInputX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerA_offsetProcess1AddInputX = createModParameter(holdModParamFloatArgs);
    parameters.add(layerA_offsetProcess1AddInputX->parameters);
    
    holdModParamFloatArgs.name = "layerA_offsetProcess1MultOutputX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerA_offsetProcess1MultOutputX = createModParameter(holdModParamFloatArgs);
    parameters.add(layerA_offsetProcess1MultOutputX->parameters);
    
    holdModParamFloatArgs.name = "layerA_offsetProcess1MultInputY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerA_offsetProcess1MultInputY = createModParameter(holdModParamFloatArgs);
    parameters.add(layerA_offsetProcess1MultInputY->parameters);
    
    holdModParamFloatArgs.name = "layerA_offsetProcess1AddInputY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerA_offsetProcess1AddInputY = createModParameter(holdModParamFloatArgs);
    parameters.add(layerA_offsetProcess1AddInputY->parameters);
    
    holdModParamFloatArgs.name = "layerA_offsetProcess1MultOutputY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerA_offsetProcess1MultOutputY = createModParameter(holdModParamFloatArgs);
    parameters.add(layerA_offsetProcess1MultOutputY->parameters);
    
    parameters.add(layerA_offsetProcess2Active.set("layerA_offsetProcess2Active", false));
    
    parameters.add(layerA_offsetProcess2Type.set("layerA_offsetProcess2Type", 0, 0, totalUnaryOpProcesses - 1));
    
    holdModParamFloatArgs.name = "layerA_offsetProcess2MultInputX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerA_offsetProcess2MultInputX = createModParameter(holdModParamFloatArgs);
    parameters.add(layerA_offsetProcess2MultInputX->parameters);
    
    holdModParamFloatArgs.name = "layerA_offsetProcess2AddInputX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerA_offsetProcess2AddInputX = createModParameter(holdModParamFloatArgs);
    parameters.add(layerA_offsetProcess2AddInputX->parameters);
    
    holdModParamFloatArgs.name = "layerA_offsetProcess2MultOutputX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerA_offsetProcess2MultOutputX = createModParameter(holdModParamFloatArgs);
    parameters.add(layerA_offsetProcess2MultOutputX->parameters);
    
    holdModParamFloatArgs.name = "layerA_offsetProcess2MultInputY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerA_offsetProcess2MultInputY = createModParameter(holdModParamFloatArgs);
    parameters.add(layerA_offsetProcess2MultInputY->parameters);
    
    holdModParamFloatArgs.name = "layerA_offsetProcess2AddInputY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerA_offsetProcess2AddInputY = createModParameter(holdModParamFloatArgs);
    parameters.add(layerA_offsetProcess2AddInputY->parameters);
    
    holdModParamFloatArgs.name = "layerA_offsetProcess2MultOutputY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerA_offsetProcess2MultOutputY = createModParameter(holdModParamFloatArgs);
    parameters.add(layerA_offsetProcess2MultOutputY->parameters);

    parameters.add(layerA_generatorProcessType.set("layerA_generatorProcessType", 0, 0, totalUnaryOpProcesses - 1));
    
    parameters.add(layerA_genInputXYProcess.set("layerA_genInputXYProcess", 0, 0, totalBinaryOpProcesses - 1));
    
    holdModParamFloatArgs.name = "layerA_genInputXMult";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerA_genInputXMult = createModParameter(holdModParamFloatArgs);
    parameters.add(layerA_genInputXMult->parameters);
    
    holdModParamIntArgs.name = "layerA_genInputXPower";
    holdModParamIntArgs.fixedValue = 1;
    holdModParamIntArgs.fixedModMix = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 100;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 10;
    layerA_genInputXPower = createModParameter(holdModParamIntArgs);
    parameters.add(layerA_genInputXPower->parameters);
    
    holdModParamFloatArgs.name = "layerA_genInputYMult";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerA_genInputYMult = createModParameter(holdModParamFloatArgs);
    parameters.add(layerA_genInputYMult->parameters);
    
    holdModParamIntArgs.name = "layerA_genInputYPower";
    holdModParamIntArgs.fixedValue = 1;
    holdModParamIntArgs.fixedModMix = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 100;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 10;
    layerA_genInputYPower = createModParameter(holdModParamIntArgs);
    parameters.add(layerA_genInputYPower->parameters);
    
    holdModParamFloatArgs.name = "layerA_genInputMult";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerA_genInputMult = createModParameter(holdModParamFloatArgs);
    parameters.add(layerA_genInputMult->parameters);
    
    holdModParamFloatArgs.name = "layerA_genInputOffset";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerA_genInputOffset = createModParameter(holdModParamFloatArgs);
    parameters.add(layerA_genInputOffset->parameters);
    
    parameters.add(layerA_postProcess1Active.set("layerA_postProcess1Active", false));
    
    parameters.add(layerA_postProcess1Type.set("layerA_postProcess1Type", 0, 0, (totalUnaryOpProcesses + totalBinaryOpProcesses) - 1));
    
    holdModParamFloatArgs.name = "layerA_postProcess1YVal";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerA_postProcess1YVal = createModParameter(holdModParamFloatArgs);
    parameters.add(layerA_postProcess1YVal->parameters);
    
    parameters.add(layerA_postProcess2Active.set("layerA_postProcess2Active", false));
    
    parameters.add(layerA_postProcess2Type.set("layerA_postProcess2Type", 0, 0, (totalUnaryOpProcesses + totalBinaryOpProcesses) - 1));
    
    holdModParamFloatArgs.name = "layerA_postProcess2YVal";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerA_postProcess2YVal = createModParameter(holdModParamFloatArgs);
    parameters.add(layerA_postProcess2YVal->parameters);
    
    parameters.add(layerA_postProcess3Active.set("layerA_postProcess3Active", false));
    
    parameters.add(layerA_postProcess3Type.set("layerA_postProcess3Type", 0, 0, (totalUnaryOpProcesses + totalBinaryOpProcesses) - 1));
    
    holdModParamFloatArgs.name = "layerA_postProcess3YVal";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerA_postProcess3YVal = createModParameter(holdModParamFloatArgs);
    parameters.add(layerA_postProcess3YVal->parameters);
    
    parameters.add(layerB_usePolarCoords.set("layerB_usePolarCoords", false));
    
    holdModParamFloatArgs.name = "layerB_rotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
    layerB_rotate = createModParameter(holdModParamFloatArgs);
    parameters.add(layerB_rotate->parameters);
    
    holdModParamFloatArgs.name = "layerB_inputXMin";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerB_inputXMin = createModParameter(holdModParamFloatArgs);
    parameters.add(layerB_inputXMin->parameters);
    
    holdModParamFloatArgs.name = "layerB_inputXMax";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerB_inputXMax = createModParameter(holdModParamFloatArgs);
    parameters.add(layerB_inputXMax->parameters);
    
    holdModParamFloatArgs.name = "layerB_inputYMin";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerB_inputYMin = createModParameter(holdModParamFloatArgs);
    parameters.add(layerB_inputYMin->parameters);
    
    holdModParamFloatArgs.name = "layerB_inputYMax";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerB_inputYMax = createModParameter(holdModParamFloatArgs);
    parameters.add(layerB_inputYMax->parameters);
    
    parameters.add(layerB_offsetProcs12InSeries.set("layerB_offsetProcs12InSeries", false));
    parameters.add(layerB_offsetProcess1Active.set("layerB_offsetProcess1Active", false));
    
    parameters.add(layerB_offsetProcess1Type.set("layerB_offsetProcess1Type", 0, 0, totalUnaryOpProcesses - 1));
    
    holdModParamFloatArgs.name = "layerB_offsetProcess1MultInputX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerB_offsetProcess1MultInputX = createModParameter(holdModParamFloatArgs);
    parameters.add(layerB_offsetProcess1MultInputX->parameters);
    
    holdModParamFloatArgs.name = "layerB_offsetProcess1AddInputX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerB_offsetProcess1AddInputX = createModParameter(holdModParamFloatArgs);
    parameters.add(layerB_offsetProcess1AddInputX->parameters);
    
    holdModParamFloatArgs.name = "layerB_offsetProcess1MultOutputX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerB_offsetProcess1MultOutputX = createModParameter(holdModParamFloatArgs);
    parameters.add(layerB_offsetProcess1MultOutputX->parameters);
    
    holdModParamFloatArgs.name = "layerB_offsetProcess1MultInputY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerB_offsetProcess1MultInputY = createModParameter(holdModParamFloatArgs);
    parameters.add(layerB_offsetProcess1MultInputY->parameters);
    
    holdModParamFloatArgs.name = "layerB_offsetProcess1AddInputY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerB_offsetProcess1AddInputY = createModParameter(holdModParamFloatArgs);
    parameters.add(layerB_offsetProcess1AddInputY->parameters);
    
    holdModParamFloatArgs.name = "layerB_offsetProcess1MultOutputY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerB_offsetProcess1MultOutputY = createModParameter(holdModParamFloatArgs);
    parameters.add(layerB_offsetProcess1MultOutputY->parameters);
    
    parameters.add(layerB_offsetProcess2Active.set("layerB_offsetProcess2Active", false));
    
    parameters.add(layerB_offsetProcess2Type.set("layerB_offsetProcess2Type", 0, 0, totalUnaryOpProcesses - 1));
    
    holdModParamFloatArgs.name = "layerB_offsetProcess2MultInputX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerB_offsetProcess2MultInputX = createModParameter(holdModParamFloatArgs);
    parameters.add(layerB_offsetProcess2MultInputX->parameters);
    
    holdModParamFloatArgs.name = "layerB_offsetProcess2AddInputX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerB_offsetProcess2AddInputX = createModParameter(holdModParamFloatArgs);
    parameters.add(layerB_offsetProcess2AddInputX->parameters);
    
    holdModParamFloatArgs.name = "layerB_offsetProcess2MultOutputX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerB_offsetProcess2MultOutputX = createModParameter(holdModParamFloatArgs);
    parameters.add(layerB_offsetProcess2MultOutputX->parameters);
    
    holdModParamFloatArgs.name = "layerB_offsetProcess2MultInputY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerB_offsetProcess2MultInputY = createModParameter(holdModParamFloatArgs);
    parameters.add(layerB_offsetProcess2MultInputY->parameters);
    
    holdModParamFloatArgs.name = "layerB_offsetProcess2AddInputY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerB_offsetProcess2AddInputY = createModParameter(holdModParamFloatArgs);
    parameters.add(layerB_offsetProcess2AddInputY->parameters);
    
    holdModParamFloatArgs.name = "layerB_offsetProcess2MultOutputY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerB_offsetProcess2MultOutputY = createModParameter(holdModParamFloatArgs);
    parameters.add(layerB_offsetProcess2MultOutputY->parameters);
    
    parameters.add(layerB_generatorProcessType.set("layerB_generatorProcessType", 0, 0, totalUnaryOpProcesses - 1));
    
    parameters.add(layerB_genInputXYProcess.set("layerB_genInputXYProcess", 0, 0, totalBinaryOpProcesses - 1));
    
    holdModParamFloatArgs.name = "layerB_genInputXMult";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerB_genInputXMult = createModParameter(holdModParamFloatArgs);
    parameters.add(layerB_genInputXMult->parameters);
    
    holdModParamIntArgs.name = "layerB_genInputXPower";
    holdModParamIntArgs.fixedValue = 1;
    holdModParamIntArgs.fixedModMix = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 100;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 10;
    layerB_genInputXPower = createModParameter(holdModParamIntArgs);
    parameters.add(layerB_genInputXPower->parameters);
    
    holdModParamFloatArgs.name = "layerB_genInputYMult";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerB_genInputYMult = createModParameter(holdModParamFloatArgs);
    parameters.add(layerB_genInputYMult->parameters);
    
    holdModParamIntArgs.name = "layerB_genInputYPower";
    holdModParamIntArgs.fixedValue = 1;
    holdModParamIntArgs.fixedModMix = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 100;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 10;
    layerB_genInputYPower = createModParameter(holdModParamIntArgs);
    parameters.add(layerB_genInputYPower->parameters);
    
    holdModParamFloatArgs.name = "layerB_genInputMult";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerB_genInputMult = createModParameter(holdModParamFloatArgs);
    parameters.add(layerB_genInputMult->parameters);
    
    holdModParamFloatArgs.name = "layerB_genInputOffset";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerB_genInputOffset = createModParameter(holdModParamFloatArgs);
    parameters.add(layerB_genInputOffset->parameters);
    
    parameters.add(layerB_postProcess1Active.set("layerB_postProcess1Active", false));
    
    parameters.add(layerB_postProcess1Type.set("layerB_postProcess1Type", 0, 0, (totalUnaryOpProcesses + totalBinaryOpProcesses) - 1));
    
    holdModParamFloatArgs.name = "layerB_postProcess1YVal";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerB_postProcess1YVal = createModParameter(holdModParamFloatArgs);
    parameters.add(layerB_postProcess1YVal->parameters);
    
    parameters.add(layerB_postProcess2Active.set("layerB_postProcess2Active", false));
    
    parameters.add(layerB_postProcess2Type.set("layerB_postProcess2Type", 0, 0, (totalUnaryOpProcesses + totalBinaryOpProcesses) - 1));
    
    holdModParamFloatArgs.name = "layerB_postProcess2YVal";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerB_postProcess2YVal = createModParameter(holdModParamFloatArgs);
    parameters.add(layerB_postProcess2YVal->parameters);
    
    parameters.add(layerB_postProcess3Active.set("layerB_postProcess3Active", false));
    
    parameters.add(layerB_postProcess3Type.set("layerB_postProcess3Type", 0, 0, (totalUnaryOpProcesses + totalBinaryOpProcesses) - 1));
    
    holdModParamFloatArgs.name = "layerB_postProcess3YVal";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerB_postProcess3YVal = createModParameter(holdModParamFloatArgs);
    parameters.add(layerB_postProcess3YVal->parameters);
    
    parameters.add(layerC_usePolarCoords.set("layerC_usePolarCoords", false));
    
    holdModParamFloatArgs.name = "layerC_rotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
    layerC_rotate = createModParameter(holdModParamFloatArgs);
    parameters.add(layerC_rotate->parameters);
    
    holdModParamFloatArgs.name = "layerC_inputXMin";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerC_inputXMin = createModParameter(holdModParamFloatArgs);
    parameters.add(layerC_inputXMin->parameters);
    
    holdModParamFloatArgs.name = "layerC_inputXMax";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerC_inputXMax = createModParameter(holdModParamFloatArgs);
    parameters.add(layerC_inputXMax->parameters);
    
    holdModParamFloatArgs.name = "layerC_inputYMin";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerC_inputYMin = createModParameter(holdModParamFloatArgs);
    parameters.add(layerC_inputYMin->parameters);
    
    holdModParamFloatArgs.name = "layerC_inputYMax";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerC_inputYMax = createModParameter(holdModParamFloatArgs);
    parameters.add(layerC_inputYMax->parameters);
    
    parameters.add(layerC_offsetProcs12InSeries.set("layerC_offsetProcs12InSeries", false));
    parameters.add(layerC_offsetProcess1Active.set("layerC_offsetProcess1Active", false));
    
    parameters.add(layerC_offsetProcess1Type.set("layerC_offsetProcess1Type", 0, 0, totalUnaryOpProcesses - 1));
    
    holdModParamFloatArgs.name = "layerC_offsetProcess1MultInputX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerC_offsetProcess1MultInputX = createModParameter(holdModParamFloatArgs);
    parameters.add(layerC_offsetProcess1MultInputX->parameters);
    
    holdModParamFloatArgs.name = "layerC_offsetProcess1AddInputX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerC_offsetProcess1AddInputX = createModParameter(holdModParamFloatArgs);
    parameters.add(layerC_offsetProcess1AddInputX->parameters);
    
    holdModParamFloatArgs.name = "layerC_offsetProcess1MultOutputX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerC_offsetProcess1MultOutputX = createModParameter(holdModParamFloatArgs);
    parameters.add(layerC_offsetProcess1MultOutputX->parameters);
    
    holdModParamFloatArgs.name = "layerC_offsetProcess1MultInputY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerC_offsetProcess1MultInputY = createModParameter(holdModParamFloatArgs);
    parameters.add(layerC_offsetProcess1MultInputY->parameters);
    
    holdModParamFloatArgs.name = "layerC_offsetProcess1AddInputY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerC_offsetProcess1AddInputY = createModParameter(holdModParamFloatArgs);
    parameters.add(layerC_offsetProcess1AddInputY->parameters);
    
    holdModParamFloatArgs.name = "layerC_offsetProcess1MultOutputY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerC_offsetProcess1MultOutputY = createModParameter(holdModParamFloatArgs);
    parameters.add(layerC_offsetProcess1MultOutputY->parameters);
    
    parameters.add(layerC_offsetProcess2Active.set("layerC_offsetProcess2Active", false));
    
    parameters.add(layerC_offsetProcess2Type.set("layerC_offsetProcess2Type", 0, 0, totalUnaryOpProcesses - 1));
    
    holdModParamFloatArgs.name = "layerC_offsetProcess2MultInputX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerC_offsetProcess2MultInputX = createModParameter(holdModParamFloatArgs);
    parameters.add(layerC_offsetProcess2MultInputX->parameters);
    
    holdModParamFloatArgs.name = "layerC_offsetProcess2AddInputX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerC_offsetProcess2AddInputX = createModParameter(holdModParamFloatArgs);
    parameters.add(layerC_offsetProcess2AddInputX->parameters);
    
    holdModParamFloatArgs.name = "layerC_offsetProcess2MultOutputX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerC_offsetProcess2MultOutputX = createModParameter(holdModParamFloatArgs);
    parameters.add(layerC_offsetProcess2MultOutputX->parameters);
    
    holdModParamFloatArgs.name = "layerC_offsetProcess2MultInputY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerC_offsetProcess2MultInputY = createModParameter(holdModParamFloatArgs);
    parameters.add(layerC_offsetProcess2MultInputY->parameters);
    
    holdModParamFloatArgs.name = "layerC_offsetProcess2AddInputY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerC_offsetProcess2AddInputY = createModParameter(holdModParamFloatArgs);
    parameters.add(layerC_offsetProcess2AddInputY->parameters);
    
    holdModParamFloatArgs.name = "layerC_offsetProcess2MultOutputY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerC_offsetProcess2MultOutputY = createModParameter(holdModParamFloatArgs);
    parameters.add(layerC_offsetProcess2MultOutputY->parameters);
    
    parameters.add(layerC_generatorProcessType.set("layerC_generatorProcessType", 0, 0, totalUnaryOpProcesses - 1));
    
    parameters.add(layerC_genInputXYProcess.set("layerC_genInputXYProcess", 0, 0, totalBinaryOpProcesses - 1));
    
    holdModParamFloatArgs.name = "layerC_genInputXMult";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerC_genInputXMult = createModParameter(holdModParamFloatArgs);
    parameters.add(layerC_genInputXMult->parameters);
    
    holdModParamIntArgs.name = "layerC_genInputXPower";
    holdModParamIntArgs.fixedValue = 1;
    holdModParamIntArgs.fixedModMix = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 100;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 10;
    layerC_genInputXPower = createModParameter(holdModParamIntArgs);
    parameters.add(layerC_genInputXPower->parameters);
    
    holdModParamFloatArgs.name = "layerC_genInputYMult";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerC_genInputYMult = createModParameter(holdModParamFloatArgs);
    parameters.add(layerC_genInputYMult->parameters);
    
    holdModParamIntArgs.name = "layerC_genInputYPower";
    holdModParamIntArgs.fixedValue = 1;
    holdModParamIntArgs.fixedModMix = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 100;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 10;
    layerC_genInputYPower = createModParameter(holdModParamIntArgs);
    parameters.add(layerC_genInputYPower->parameters);
    
    holdModParamFloatArgs.name = "layerC_genInputMult";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerC_genInputMult = createModParameter(holdModParamFloatArgs);
    parameters.add(layerC_genInputMult->parameters);
    
    holdModParamFloatArgs.name = "layerC_genInputOffset";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerC_genInputOffset = createModParameter(holdModParamFloatArgs);
    parameters.add(layerC_genInputOffset->parameters);
    
    parameters.add(layerC_postProcess1Active.set("layerC_postProcess1Active", false));
    
    parameters.add(layerC_postProcess1Type.set("layerC_postProcess1Type", 0, 0, (totalUnaryOpProcesses + totalBinaryOpProcesses) - 1));
    
    holdModParamFloatArgs.name = "layerC_postProcess1YVal";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerC_postProcess1YVal = createModParameter(holdModParamFloatArgs);
    parameters.add(layerC_postProcess1YVal->parameters);
    
    parameters.add(layerC_postProcess2Active.set("layerC_postProcess2Active", false));
    
    parameters.add(layerC_postProcess2Type.set("layerC_postProcess2Type", 0, 0, (totalUnaryOpProcesses + totalBinaryOpProcesses) - 1));
    
    holdModParamFloatArgs.name = "layerC_postProcess2YVal";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerC_postProcess2YVal = createModParameter(holdModParamFloatArgs);
    parameters.add(layerC_postProcess2YVal->parameters);
    
    parameters.add(layerC_postProcess3Active.set("layerC_postProcess3Active", false));
    
    parameters.add(layerC_postProcess3Type.set("layerC_postProcess3Type", 0, 0, (totalUnaryOpProcesses + totalBinaryOpProcesses) - 1));
    
    holdModParamFloatArgs.name = "layerC_postProcess3YVal";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerC_postProcess3YVal = createModParameter(holdModParamFloatArgs);
    parameters.add(layerC_postProcess3YVal->parameters);
    
    parameters.add(layerD_usePolarCoords.set("layerD_usePolarCoords", false));
    
    holdModParamFloatArgs.name = "layerD_rotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
    layerD_rotate = createModParameter(holdModParamFloatArgs);
    parameters.add(layerD_rotate->parameters);
    
    holdModParamFloatArgs.name = "layerD_inputXMin";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerD_inputXMin = createModParameter(holdModParamFloatArgs);
    parameters.add(layerD_inputXMin->parameters);
    
    holdModParamFloatArgs.name = "layerD_inputXMax";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerD_inputXMax = createModParameter(holdModParamFloatArgs);
    parameters.add(layerD_inputXMax->parameters);
    
    holdModParamFloatArgs.name = "layerD_inputYMin";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerD_inputYMin = createModParameter(holdModParamFloatArgs);
    parameters.add(layerD_inputYMin->parameters);
    
    holdModParamFloatArgs.name = "layerD_inputYMax";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerD_inputYMax = createModParameter(holdModParamFloatArgs);
    parameters.add(layerD_inputYMax->parameters);
    
    parameters.add(layerD_offsetProcs12InSeries.set("layerD_offsetProcs12InSeries", false));
    parameters.add(layerD_offsetProcess1Active.set("layerD_offsetProcess1Active", false));
    
    parameters.add(layerD_offsetProcess1Type.set("layerD_offsetProcess1Type", 0, 0, totalUnaryOpProcesses - 1));
    
    holdModParamFloatArgs.name = "layerD_offsetProcess1MultInputX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerD_offsetProcess1MultInputX = createModParameter(holdModParamFloatArgs);
    parameters.add(layerD_offsetProcess1MultInputX->parameters);
    
    holdModParamFloatArgs.name = "layerD_offsetProcess1AddInputX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerD_offsetProcess1AddInputX = createModParameter(holdModParamFloatArgs);
    parameters.add(layerD_offsetProcess1AddInputX->parameters);
    
    holdModParamFloatArgs.name = "layerD_offsetProcess1MultOutputX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerD_offsetProcess1MultOutputX = createModParameter(holdModParamFloatArgs);
    parameters.add(layerD_offsetProcess1MultOutputX->parameters);
    
    holdModParamFloatArgs.name = "layerD_offsetProcess1MultInputY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerD_offsetProcess1MultInputY = createModParameter(holdModParamFloatArgs);
    parameters.add(layerD_offsetProcess1MultInputY->parameters);
    
    holdModParamFloatArgs.name = "layerD_offsetProcess1AddInputY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerD_offsetProcess1AddInputY = createModParameter(holdModParamFloatArgs);
    parameters.add(layerD_offsetProcess1AddInputY->parameters);
    
    holdModParamFloatArgs.name = "layerD_offsetProcess1MultOutputY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerD_offsetProcess1MultOutputY = createModParameter(holdModParamFloatArgs);
    parameters.add(layerD_offsetProcess1MultOutputY->parameters);
    
    parameters.add(layerD_offsetProcess2Active.set("layerD_offsetProcess2Active", false));
    
    parameters.add(layerD_offsetProcess2Type.set("layerD_offsetProcess2Type", 0, 0, totalUnaryOpProcesses - 1));
    
    holdModParamFloatArgs.name = "layerD_offsetProcess2MultInputX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerD_offsetProcess2MultInputX = createModParameter(holdModParamFloatArgs);
    parameters.add(layerD_offsetProcess2MultInputX->parameters);
    
    holdModParamFloatArgs.name = "layerD_offsetProcess2AddInputX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerD_offsetProcess2AddInputX = createModParameter(holdModParamFloatArgs);
    parameters.add(layerD_offsetProcess2AddInputX->parameters);
    
    holdModParamFloatArgs.name = "layerD_offsetProcess2MultOutputX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerD_offsetProcess2MultOutputX = createModParameter(holdModParamFloatArgs);
    parameters.add(layerD_offsetProcess2MultOutputX->parameters);
    
    holdModParamFloatArgs.name = "layerD_offsetProcess2MultInputY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerD_offsetProcess2MultInputY = createModParameter(holdModParamFloatArgs);
    parameters.add(layerD_offsetProcess2MultInputY->parameters);
    
    holdModParamFloatArgs.name = "layerD_offsetProcess2AddInputY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerD_offsetProcess2AddInputY = createModParameter(holdModParamFloatArgs);
    parameters.add(layerD_offsetProcess2AddInputY->parameters);
    
    holdModParamFloatArgs.name = "layerD_offsetProcess2MultOutputY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerD_offsetProcess2MultOutputY = createModParameter(holdModParamFloatArgs);
    parameters.add(layerD_offsetProcess2MultOutputY->parameters);
    
    parameters.add(layerD_generatorProcessType.set("layerD_generatorProcessType", 0, 0, totalUnaryOpProcesses - 1));
    
    parameters.add(layerD_genInputXYProcess.set("layerD_genInputXYProcess", 0, 0, totalBinaryOpProcesses - 1));
    
    holdModParamFloatArgs.name = "layerD_genInputXMult";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerD_genInputXMult = createModParameter(holdModParamFloatArgs);
    parameters.add(layerD_genInputXMult->parameters);
    
    holdModParamIntArgs.name = "layerD_genInputXPower";
    holdModParamIntArgs.fixedValue = 1;
    holdModParamIntArgs.fixedModMix = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 100;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 10;
    layerD_genInputXPower = createModParameter(holdModParamIntArgs);
    parameters.add(layerD_genInputXPower->parameters);
    
    holdModParamFloatArgs.name = "layerD_genInputYMult";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerD_genInputYMult = createModParameter(holdModParamFloatArgs);
    parameters.add(layerD_genInputYMult->parameters);
    
    holdModParamIntArgs.name = "layerD_genInputYPower";
    holdModParamIntArgs.fixedValue = 1;
    holdModParamIntArgs.fixedModMix = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 100;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 10;
    layerD_genInputYPower = createModParameter(holdModParamIntArgs);
    parameters.add(layerD_genInputYPower->parameters);
    
    holdModParamFloatArgs.name = "layerD_genInputMult";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerD_genInputMult = createModParameter(holdModParamFloatArgs);
    parameters.add(layerD_genInputMult->parameters);
    
    holdModParamFloatArgs.name = "layerD_genInputOffset";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerD_genInputOffset = createModParameter(holdModParamFloatArgs);
    parameters.add(layerD_genInputOffset->parameters);
    
    parameters.add(layerD_postProcess1Active.set("layerD_postProcess1Active", false));
    
    parameters.add(layerD_postProcess1Type.set("layerD_postProcess1Type", 0, 0, (totalUnaryOpProcesses + totalBinaryOpProcesses) - 1));
    
    holdModParamFloatArgs.name = "layerD_postProcess1YVal";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerD_postProcess1YVal = createModParameter(holdModParamFloatArgs);
    parameters.add(layerD_postProcess1YVal->parameters);
    
    parameters.add(layerD_postProcess2Active.set("layerD_postProcess2Active", false));
    
    parameters.add(layerD_postProcess2Type.set("layerD_postProcess2Type", 0, 0, (totalUnaryOpProcesses + totalBinaryOpProcesses) - 1));
    
    holdModParamFloatArgs.name = "layerD_postProcess2YVal";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerD_postProcess2YVal = createModParameter(holdModParamFloatArgs);
    parameters.add(layerD_postProcess2YVal->parameters);
    
    parameters.add(layerD_postProcess3Active.set("layerD_postProcess3Active", false));
    
    parameters.add(layerD_postProcess3Type.set("layerD_postProcess3Type", 0, 0, (totalUnaryOpProcesses + totalBinaryOpProcesses) - 1));
    
    holdModParamFloatArgs.name = "layerD_postProcess3YVal";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = hardMinVal;
    holdModParamFloatArgs.hardMax = hardMaxVal;
    holdModParamFloatArgs.softMin = softMinVal;
    holdModParamFloatArgs.softMax = softMaxVal;
    layerD_postProcess3YVal = createModParameter(holdModParamFloatArgs);
    parameters.add(layerD_postProcess3YVal->parameters);
    
    //  =============
    
    holdModParamBoolArgs.name = "renderContinuosly";
    holdModParamBoolArgs.fixedValue = false;
    renderContinuosly = createModParameter(holdModParamBoolArgs);
    parameters.add(renderContinuosly->parameters);
    
    holdModParamBoolArgs.name = "renderNow";
    holdModParamBoolArgs.fixedValue = false;
    renderNow = createModParameter(holdModParamBoolArgs);
    parameters.add(renderNow->parameters);
    
    renderWidthHeightRule.set("renderWidthHeightRule",0,0,11);
    parameters.add(renderWidthHeightRule);
    
    renderCustomWidth.set("renderCustomWidth",1024,1,4096);
    parameters.add(renderCustomWidth);
    
    renderCustomHeight.set("renderCustomHeight",768,1,4096);
    parameters.add(renderCustomHeight);
    
    holdModParamBoolArgs.name = "clearBeforeRender";
    holdModParamBoolArgs.fixedValue = true;
    clearBeforeRender = createModParameter(holdModParamBoolArgs);
    parameters.add(clearBeforeRender->parameters);
    
    holdModParamBoolArgs.name = "clearNow";
    holdModParamBoolArgs.fixedValue = false;
    clearNow = createModParameter(holdModParamBoolArgs);
    parameters.add(clearNow->parameters);
    
    holdModParamFloatArgs.name = "clearColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    holdModParamFloatArgs.autoScaleModSumming = true;
    clearColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(clearColorHue->parameters);
    
    holdModParamFloatArgs.name = "clearColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    holdModParamFloatArgs.autoScaleModSumming = true;
    clearColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(clearColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "clearColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    holdModParamFloatArgs.autoScaleModSumming = true;
    clearColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(clearColorBrightness->parameters);
    
    holdModParamFloatArgs.name = "clearColorAlpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    holdModParamFloatArgs.autoScaleModSumming = true;
    clearColorAlpha = createModParameter(holdModParamFloatArgs);
    parameters.add(clearColorAlpha->parameters);
    
    holdModParamBoolArgs.name = "clearColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    clearColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(clearColorHSBAsRGB->parameters);
    
    holdModParamFloatArgs.name = "drawAlpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	drawAlpha = createModParameter(holdModParamFloatArgs);
    parameters.add(drawAlpha->parameters);
    
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
    
    holdModParamFloatArgs.name = "drawWidth";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	drawWidth = createModParameter(holdModParamFloatArgs);
    parameters.add(drawWidth->parameters);
    
    holdModParamFloatArgs.name = "drawHeight";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	drawHeight = createModParameter(holdModParamFloatArgs);
    parameters.add(drawHeight->parameters);
    
    holdModParamFloatArgs.name = "anchorX";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	anchorX = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorX->parameters);
    
    holdModParamFloatArgs.name = "anchorY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	anchorY = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorY->parameters);
    
    holdModParamFloatArgs.name = "rotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	rotate = createModParameter(holdModParamFloatArgs);
    parameters.add(rotate->parameters);
    
    holdModParamFloatArgs.name = "rotateMultiply";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = softMaxVal;
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
    
    parameters.add(useScaleXForScaleY.set("useScaleXForScaleY", false));
    
    // add listener to relevent parameters:
    renderWidthHeightRule.addListener(this, &TXWaveTerrain::renderSizeChanged);
    renderCustomWidth.addListener(this, &TXWaveTerrain::renderSizeChanged);
    renderCustomHeight.addListener(this, &TXWaveTerrain::renderSizeChanged);

    // add listener to relevent parameters:
    ofAddListener(colorMixCurveA.parameters.parameterChangedE(),this,&TXWaveTerrain::colorMixImageChanged);
    ofAddListener(colorMixCurveB.parameters.parameterChangedE(),this,&TXWaveTerrain::colorMixImageChanged);

    ofAddListener(lookupCurve1A.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesImageChanged);
    ofAddListener(lookupCurve1B.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesImageChanged);
    ofAddListener(lookupCurve2A.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesImageChanged);
    ofAddListener(lookupCurve2B.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesImageChanged);
    ofAddListener(lookupCurve3A.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesImageChanged);
    ofAddListener(lookupCurve3B.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesImageChanged);
    ofAddListener(lookupCurve4A.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesImageChanged);
    ofAddListener(lookupCurve4B.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesImageChanged);
    
    ofAddListener(colorHueCurveA.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesHSLImageChanged);
    ofAddListener(colorHueCurveB.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesHSLImageChanged);
    ofAddListener(colorSaturationCurveA.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesHSLImageChanged);
    ofAddListener(colorSaturationCurveB.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesHSLImageChanged);
    ofAddListener(colorBrightnessCurveA.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesHSLImageChanged);
    ofAddListener(colorBrightnessCurveB.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesHSLImageChanged);
    ofAddListener(colorAlphaCurveA.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesHSLImageChanged);
    ofAddListener(colorAlphaCurveB.parameters.parameterChangedE(),this,&TXWaveTerrain::curvesHSLImageChanged);

    terrainStructure.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerABJoinProcess.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerBCJoinProcess.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerCDJoinProcess.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    outputRangeProcess.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    coloringMethod.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    
    // Layers:
    layerA_usePolarCoords.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerA_offsetProcs12InSeries.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerA_offsetProcess1Active.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerA_offsetProcess1Type.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerA_offsetProcess2Active.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerA_offsetProcess2Type.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerA_generatorProcessType.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerA_genInputXYProcess.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerA_postProcess1Active.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerA_postProcess1Type.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerA_postProcess2Active.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerA_postProcess2Type.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerA_postProcess3Active.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerA_postProcess3Type.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    
    layerB_usePolarCoords.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerB_offsetProcs12InSeries.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerB_offsetProcess1Active.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerB_offsetProcess1Type.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerB_offsetProcess2Active.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerB_offsetProcess2Type.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerB_generatorProcessType.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerB_genInputXYProcess.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerB_postProcess1Active.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerB_postProcess1Type.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerB_postProcess2Active.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerB_postProcess2Type.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerB_postProcess3Active.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerB_postProcess3Type.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    
    layerC_usePolarCoords.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerC_offsetProcs12InSeries.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerC_offsetProcess1Active.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerC_offsetProcess1Type.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerC_offsetProcess2Active.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerC_offsetProcess2Type.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerC_generatorProcessType.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerC_genInputXYProcess.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerC_postProcess1Active.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerC_postProcess1Type.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerC_postProcess2Active.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerC_postProcess2Type.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerC_postProcess3Active.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerC_postProcess3Type.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    
    layerD_usePolarCoords.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerD_offsetProcs12InSeries.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerD_offsetProcess1Active.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerD_offsetProcess1Type.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerD_offsetProcess2Active.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerD_offsetProcess2Type.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerD_generatorProcessType.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerD_genInputXYProcess.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerD_postProcess1Active.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerD_postProcess1Type.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerD_postProcess2Active.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerD_postProcess2Type.addListener(this, &TXWaveTerrain::shaderCodeChangedI);
    layerD_postProcess3Active.addListener(this, &TXWaveTerrain::shaderCodeChangedB);
    layerD_postProcess3Type.addListener(this, &TXWaveTerrain::shaderCodeChangedI);

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
    
    // init vars
    oldRenderNow = false;
    oldClearNow = false;
    shaderCodeHasChanged = false;
    colorMixImageHasChanged = true;
    curvesImageHasChanged = true;
    curvesHSLImageHasChanged = true;

    // load draw shader
#ifdef TARGET_OPENGLES
	drawShader.load("shadersES2/AlphaTextureShader.vert","shadersES2/AlphaTextureShader.frag");
#else
	if(ofIsGLProgrammableRenderer()){
		drawShader.load("shadersGL3/AlphaTextureShader.vert", "shadersGL3/AlphaTextureShader.frag");
	}else{
		drawShader.load("shadersGL2/AlphaTextureShader.vert", "shadersGL2/AlphaTextureShader.frag");
	}
#endif
    // load render shader
    loadRenderShader();

    // set up texture
    allocateTexture();
    registerTexture();
    curvesImageSetup();
}

void TXWaveTerrain::update(){
    bool newRenderContinuosly = renderContinuosly->getBool();
    bool newRenderNow = renderNow->getBool();
    bool newClearBeforeRender = clearBeforeRender->getBool();
    bool newClearNow = clearNow->getBool();
    bool clearNowNewTrigger = (newClearNow && (newClearNow != oldClearNow));
    bool clearFirst = false;
    // check whether to clear
    if (newClearBeforeRender || clearNowNewTrigger) {
        clearFirst = true;
    };

    if (shaderCodeHasChanged) {
        loadRenderShader();
        shaderCodeHasChanged = false;
    };
    if (colorMixImageHasChanged) {
        updateColorMixImagePixels();
        colorMixImageHasChanged = false;
    };
    if (curvesImageHasChanged) {
        updateCurvesImagePixels();
        curvesImageHasChanged = false;
    };
    if (curvesHSLImageHasChanged) {
        updateCurvesHSLImagePixels();
        curvesHSLImageHasChanged = false;
    };

    // check whether to render
    if (newRenderContinuosly || (newRenderNow && (newRenderNow != oldRenderNow)) || clearNowNewTrigger) {
        renderTexture(clearFirst);
    };
    // reset vars
    oldClearNow = newClearNow;
    oldRenderNow = newRenderNow;
}

void TXWaveTerrain::draw(){
    bool setUniforms = true;
    float drawXAdjusted, drawYAdjusted;
    float holdDrawPosX, holdDrawPosY;
	int   drawWidthPixels, drawHeightPixels;
    float anchorXPixels, anchorYPixels;
    float holdScaleX, holdScaleY;
    // check before drawing
    if (!drawActive->getBool()) {
        return;
    };
    int   holdMaxWidth = getMaxWidth();
    int   holdMaxHeight = getMaxHeight();
    float holdImageWidth = outImage.getWidth();
    float holdImageHeight = outImage.getHeight();
    float fboEdgeOffsetX = 1.0f / holdImageWidth;
    float fboEdgeOffsetY = 1.0f / holdImageHeight;
    //    was set to higher for ipad retina
    //    float fboEdgeOffsetX = 2.0f / holdImageWidth;
    //    float fboEdgeOffsetY = 2.0f / holdImageHeight;
    
    holdDrawPosX = drawPosX->getFloat();
    holdDrawPosY = drawPosY->getFloat();
    drawWidthPixels = (int) (fmax(drawWidth->getFloat() * holdMaxWidth, 1));
    drawHeightPixels = (int) (fmax(drawHeight->getFloat() * holdMaxHeight, 1));
    anchorXPixels = anchorX->getFloat() * drawWidthPixels;
    anchorYPixels = anchorY->getFloat() * drawHeightPixels;
    holdScaleX = scaleX->getFloat();
    if (useScaleXForScaleY) {
        holdScaleY = holdScaleX;
    } else {
        holdScaleY = scaleY->getFloat();
    };
    //
    // translate, rotate, scale
    drawXAdjusted = holdDrawPosX * holdMaxWidth;
    drawYAdjusted = holdDrawPosY * holdMaxHeight;
    ofPushMatrix();
    ofTranslate(drawXAdjusted, drawYAdjusted, 0.0);
    ofRotateZ(rotateMultiply->getFloat() * rotate->getFloat());
    ofScale(holdScaleX, holdScaleY, 1.0);
    
    //    // testing xxx
    //    ofLogNotice() << "testing xxx  TXWaveTerrain::draw -  widthNextPow2Ratio, heightNextPow2Ratio, outImage.getWidth(), outImage.getHeight()";
    //    ofLogNotice() << widthNextPow2Ratio <<  ", " << heightNextPow2Ratio <<  ", " << outImage.getWidth() <<  ", " << outImage.getHeight();
    
    float tex0X, tex0Y, tex1X, tex1Y, tex2X, tex2Y, tex3X, tex3Y;
#ifdef TARGET_OPENGLES
    // Use widthNextPow2Ratio, heightNextPow2Ratio to adjust texture coords
    float widthNextPow2Ratio = (float) holdImageWidth /ofNextPow2(holdImageWidth);
    float heightNextPow2Ratio = (float) holdImageHeight /ofNextPow2(holdImageHeight);
    tex0X = (fboEdgeOffsetX) * widthNextPow2Ratio;
    tex0Y = fboEdgeOffsetY * heightNextPow2Ratio;
    tex1X = (holdSampleWidth - fboEdgeOffsetX) * widthNextPow2Ratio;
    tex1Y = fboEdgeOffsetY * heightNextPow2Ratio;
    tex2X = (holdSampleWidth - fboEdgeOffsetX) * widthNextPow2Ratio;
    tex2Y = (holdSampleHeight - fboEdgeOffsetY) * heightNextPow2Ratio;
    tex3X = (fboEdgeOffsetX) * widthNextPow2Ratio;
    tex3Y = (holdSampleHeight - fboEdgeOffsetY) * heightNextPow2Ratio;
#else
    tex0X = fboEdgeOffsetX;
    tex0Y = fboEdgeOffsetY;
    tex1X = (holdImageWidth - fboEdgeOffsetX);
    tex1Y = fboEdgeOffsetY;
    tex2X = (holdImageWidth - fboEdgeOffsetX);
    tex2Y = (holdImageHeight - fboEdgeOffsetY);
    tex3X = fboEdgeOffsetX;
    tex3Y = (holdImageHeight - fboEdgeOffsetY);
#endif
    //  draw
    drawShader.begin();
    // save time if already set before
    if (setUniforms) {
        drawShader.setUniform1f("u_alpha", drawAlpha->getFloat());
        drawShader.setUniform1f("u_alphaThreshold", parentSystem->alphaThreshold);
        drawShader.setUniformTexture("u_texture0Sampler", outImage.getTexture(0), 0);
    };
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
    
    // draw
    ofEnableAlphaBlending();
    drawMesh.draw();
    ofDisableAlphaBlending();
    
    ofPopMatrix();
    drawShader.end();
}


void TXWaveTerrain::allocateTexture() {
    
#ifdef TARGET_OPENGLES
    outImage.allocate(getRenderWidth(), getRenderHeight(), GL_RGBA);
    //ofLogWarning("ofApp") << "TXWaveTerrain::allocateTexture() - GL_RGBA32F_ARB is not available for OPENGLES.  Using RGBA.";
#else
    // TESTING XXX - CHANGE TO GL_RGBA
    //outImage.allocate(getRenderWidth(), getRenderHeight(), GL_RGBA32F_ARB);
    outImage.allocate(getRenderWidth(), getRenderHeight(), GL_RGBA);
    //ofLogNotice() << "TXWaveTerrain::allocateTexture() - GL_RGBA32F_ARB: ";
#endif
    
    outImage.begin();
    ofClear(0,255);
    outImage.end();
}

void TXWaveTerrain::renderTexture(bool clearFirstArg) {
    float holdWidth = outImage.getWidth();
    float holdHeight = outImage.getHeight();
    ofColor color1;
    ofColor color2;
    ofColor color3;

    outImage.begin();
    
    if (clearFirstArg) {
        if (clearColorHSBAsRGB->getBool()) {
            ofColor newColor = ofColor(clearColorHue->getFloat() * 255, clearColorSaturation->getFloat() * 255, clearColorBrightness->getFloat() * 255, clearColorAlpha->getFloat() * 255);
            ofEnableAlphaBlending();
            ofClear(newColor);
            ofDisableAlphaBlending();
        } else {
            ofColor newColor = ofColor::fromHsb(clearColorHue->getFloat() * 255, clearColorSaturation->getFloat() * 255, clearColorBrightness->getFloat() * 255, clearColorAlpha->getFloat() * 255);
            ofEnableAlphaBlending();
            ofClear(newColor);
            ofDisableAlphaBlending();
        };
    };

    renderShader.begin();
    
    // set uniforms
    renderShader.setUniform2f("resolution", holdWidth, holdHeight);
    renderShader.setUniform1f("squeezeX", squeezeX->getFloat());
    renderShader.setUniform1f("squeezeY", squeezeY->getFloat());
    renderShader.setUniform1f("skewX", skewX->getFloat());
    renderShader.setUniform1f("skewY", skewY->getFloat());
    renderShader.setUniform1i("outputRangeProcess", outputRangeProcess);
    renderShader.setUniform1f("outputRangeMin", outputRangeMin->getFloat());
    renderShader.setUniform1f("outputRangeMax", outputRangeMax->getFloat());
    
    renderShader.setUniformTexture("curveSampler", curvesImage.getTexture(), 0);
    renderShader.setUniformTexture("curveHSLSampler", curvesHSLImage.getTexture(), 1);
    renderShader.setUniformTexture("colorMixSampler", colorMixImage.getTexture(), 2);

    renderShader.setUniform1f("colorMixCurveMorph", colorMixCurveMorph->getFloat());
    renderShader.setUniform1f("colorMixCurvePhase", colorMixCurvePhase->getFloat());
    renderShader.setUniform1f("lookupCurve1Morph", lookupCurve1Morph->getFloat());
    renderShader.setUniform1f("lookupCurve1Phase", lookupCurve1Phase->getFloat());
    renderShader.setUniform1f("lookupCurve2Morph", lookupCurve2Morph->getFloat());
    renderShader.setUniform1f("lookupCurve2Phase", lookupCurve2Phase->getFloat());
    renderShader.setUniform1f("lookupCurve3Morph", lookupCurve3Morph->getFloat());
    renderShader.setUniform1f("lookupCurve3Phase", lookupCurve3Phase->getFloat());
    renderShader.setUniform1f("lookupCurve4Morph", lookupCurve4Morph->getFloat());
    renderShader.setUniform1f("lookupCurve4Phase", lookupCurve4Phase->getFloat());
    renderShader.setUniform1f("perlinLayer1Mix", perlinLayer1Mix->getFloat());
    renderShader.setUniform1f("perlinLayer2Mix", perlinLayer2Mix->getFloat());
    renderShader.setUniform1f("perlinLayer3Mix", perlinLayer3Mix->getFloat());
    renderShader.setUniform1f("perlinLayer4Mix", perlinLayer4Mix->getFloat());
    
    switch (coloringMethod) {
        case 0:
            // "Use color1/2/3 with colorMixCurve to blend"
            color1 =  TXFunctions::txGetColor(color1Hue->getFloat(),  color1Saturation->getFloat(),  color1Brightness->getFloat(),  1.0, color1HueRotate->getFloat(), color1HSBAsRGB->getBool());
            color2 =  TXFunctions::txGetColor(color2Hue->getFloat(),  color2Saturation->getFloat(),  color2Brightness->getFloat(),  1.0, color2HueRotate->getFloat(), color2HSBAsRGB->getBool());
            color3 =  TXFunctions::txGetColor(color3Hue->getFloat(),  color3Saturation->getFloat(),  color3Brightness->getFloat(),  1.0, color3HueRotate->getFloat(), color3HSBAsRGB->getBool());
            renderShader.setUniform4f("color1", color1.r/255.0f, color1.g/255.0f, color1.b/255.0f, color1.a/255.0f);
            renderShader.setUniform4f("color2", color2.r/255.0f, color2.g/255.0f, color2.b/255.0f, color2.a/255.0f);
            renderShader.setUniform4f("color3", color3.r/255.0f, color3.g/255.0f, color3.b/255.0f, color3.a/255.0f);
            break;
        case 1:
            // "Use color1/2/3 with linear blend"
            color1 =  TXFunctions::txGetColor(color1Hue->getFloat(),  color1Saturation->getFloat(),  color1Brightness->getFloat(),  1.0, color1HueRotate->getFloat(), color1HSBAsRGB->getBool());
            color2 =  TXFunctions::txGetColor(color2Hue->getFloat(),  color2Saturation->getFloat(),  color2Brightness->getFloat(),  1.0, color2HueRotate->getFloat(), color2HSBAsRGB->getBool());
            color3 =  TXFunctions::txGetColor(color3Hue->getFloat(),  color3Saturation->getFloat(),  color3Brightness->getFloat(),  1.0, color3HueRotate->getFloat(), color3HSBAsRGB->getBool());
            renderShader.setUniform4f("color1", color1.r/255.0f, color1.g/255.0f, color1.b/255.0f, color1.a/255.0f);
            renderShader.setUniform4f("color2", color2.r/255.0f, color2.g/255.0f, color2.b/255.0f, color2.a/255.0f);
            renderShader.setUniform4f("color3", color3.r/255.0f, color3.g/255.0f, color3.b/255.0f, color3.a/255.0f);
            break;
        case 2:
            color1 =  TXFunctions::txGetColor(color1Hue->getFloat(),  color1Saturation->getFloat(),  color1Brightness->getFloat(),  1.0, color1HueRotate->getFloat(), color1HSBAsRGB->getBool());
            color2 =  TXFunctions::txGetColor(color2Hue->getFloat(),  color2Saturation->getFloat(),  color2Brightness->getFloat(),  1.0, color2HueRotate->getFloat(), color2HSBAsRGB->getBool());
            renderShader.setUniform4f("color1", color1.r/255.0f, color1.g/255.0f, color1.b/255.0f, color1.a/255.0f);
            renderShader.setUniform4f("color2", color2.r/255.0f, color2.g/255.0f, color2.b/255.0f, color2.a/255.0f);
            break;
        case 3:
            // "Use color1/2 with linear blend"
            color1 =  TXFunctions::txGetColor(color1Hue->getFloat(),  color1Saturation->getFloat(),  color1Brightness->getFloat(),  1.0, color1HueRotate->getFloat(), color1HSBAsRGB->getBool());
            color2 =  TXFunctions::txGetColor(color2Hue->getFloat(),  color2Saturation->getFloat(),  color2Brightness->getFloat(),  1.0, color2HueRotate->getFloat(), color2HSBAsRGB->getBool());
            renderShader.setUniform4f("color1", color1.r/255.0f, color1.g/255.0f, color1.b/255.0f, color1.a/255.0f);
            renderShader.setUniform4f("color2", color2.r/255.0f, color2.g/255.0f, color2.b/255.0f, color2.a/255.0f);
            break;
        case 4:
            // "Use color2/3 with colorMixCurve to blend"
            color2 =  TXFunctions::txGetColor(color2Hue->getFloat(),  color2Saturation->getFloat(),  color2Brightness->getFloat(),  1.0, color2HueRotate->getFloat(), color2HSBAsRGB->getBool());
            color3 =  TXFunctions::txGetColor(color3Hue->getFloat(),  color3Saturation->getFloat(),  color3Brightness->getFloat(),  1.0, color3HueRotate->getFloat(), color3HSBAsRGB->getBool());
            renderShader.setUniform4f("color2", color2.r/255.0f, color2.g/255.0f, color2.b/255.0f, color2.a/255.0f);
            renderShader.setUniform4f("color3", color3.r/255.0f, color3.g/255.0f, color3.b/255.0f, color3.a/255.0f);
            break;
        case 5:
            // "Use color2/3 with linear blend"
            color2 =  TXFunctions::txGetColor(color2Hue->getFloat(),  color2Saturation->getFloat(),  color2Brightness->getFloat(),  1.0, color2HueRotate->getFloat(), color2HSBAsRGB->getBool());
            color3 =  TXFunctions::txGetColor(color3Hue->getFloat(),  color3Saturation->getFloat(),  color3Brightness->getFloat(),  1.0, color3HueRotate->getFloat(), color3HSBAsRGB->getBool());
            renderShader.setUniform4f("color2", color2.r/255.0f, color2.g/255.0f, color2.b/255.0f, color2.a/255.0f);
            renderShader.setUniform4f("color3", color3.r/255.0f, color3.g/255.0f, color3.b/255.0f, color3.a/255.0f);
            break;
        case 6:
            // "Use Black/Grey/White with colorMixCurve to blend"
            break;
        case 7:
            // "Use Black/Grey/White with linear blend"
            break;
        case 8:
            // "Use White/Black/White with colorMixCurve to blend"
            break;
        case 9:
            // "Use White/Black/White with linear blend"
            break;
        case 10:
            // "Use Black/White/Black with colorMixCurve to blend"
            break;
        case 11:
            // "Use Black/White/Black with linear blend"
            break;
        case 12:
            // "Use Blue/Black/Red with colorMixCurve to blend"
            break;
        case 13:
            // "Use Blue/Black/Red with linear blend"
            break;
        case 14:
            // ""Use Color Curves as HSBA with linear blend"
            renderShader.setUniform1f("colorHueCurveMorph", colorHueCurveMorph->getFloat());
            renderShader.setUniform1f("colorHueCurveRotate", colorHueCurveRotate->getFloat());
            renderShader.setUniform1f("colorSaturationCurveMorph", colorSaturationCurveMorph->getFloat());
            renderShader.setUniform1f("colorBrightnessCurveMorph", colorBrightnessCurveMorph->getFloat());
            renderShader.setUniform1f("colorAlphaCurveMorph", colorAlphaCurveMorph->getFloat());
            break;
        case 15:
            // "Use Color Curves as HSBA with colorMixCurve to blend"
            renderShader.setUniform1f("colorHueCurveMorph", colorHueCurveMorph->getFloat());
            renderShader.setUniform1f("colorHueCurveRotate", colorHueCurveRotate->getFloat());
            renderShader.setUniform1f("colorSaturationCurveMorph", colorSaturationCurveMorph->getFloat());
            renderShader.setUniform1f("colorBrightnessCurveMorph", colorBrightnessCurveMorph->getFloat());
            renderShader.setUniform1f("colorAlphaCurveMorph", colorAlphaCurveMorph->getFloat());
            break;
        case 16:
            // ""Use Color Curves as RGBA with linear blend"
            renderShader.setUniform1f("colorHueCurveMorph", colorHueCurveMorph->getFloat());
            renderShader.setUniform1f("colorHueCurveRotate", colorHueCurveRotate->getFloat());
            renderShader.setUniform1f("colorSaturationCurveMorph", colorSaturationCurveMorph->getFloat());
            renderShader.setUniform1f("colorBrightnessCurveMorph", colorBrightnessCurveMorph->getFloat());
            renderShader.setUniform1f("colorAlphaCurveMorph", colorAlphaCurveMorph->getFloat());
            break;
        case 17:
            // "Use Color Curves as RGBA with colorMixCurve to blend"
            renderShader.setUniform1f("colorHueCurveMorph", colorHueCurveMorph->getFloat());
            renderShader.setUniform1f("colorHueCurveRotate", colorHueCurveRotate->getFloat());
            renderShader.setUniform1f("colorSaturationCurveMorph", colorSaturationCurveMorph->getFloat());
            renderShader.setUniform1f("colorBrightnessCurveMorph", colorBrightnessCurveMorph->getFloat());
            renderShader.setUniform1f("colorAlphaCurveMorph", colorAlphaCurveMorph->getFloat());
            break;
        case 18:
            // ""Use Color Curves as RGBA with linear blend"
            renderShader.setUniform1f("colorHueCurveMorph", colorHueCurveMorph->getFloat());
            renderShader.setUniform1f("colorHueCurveRotate", colorHueCurveRotate->getFloat());
            renderShader.setUniform1f("colorSaturationCurveMorph", colorSaturationCurveMorph->getFloat());
            renderShader.setUniform1f("colorBrightnessCurveMorph", colorBrightnessCurveMorph->getFloat());
            renderShader.setUniform1f("colorAlphaCurveMorph", colorAlphaCurveMorph->getFloat());
            break;
        case 19:
            // "Use Color Curves as RGBA with colorMixCurve to blend"
            renderShader.setUniform1f("colorHueCurveMorph", colorHueCurveMorph->getFloat());
            renderShader.setUniform1f("colorHueCurveRotate", colorHueCurveRotate->getFloat());
            renderShader.setUniform1f("colorSaturationCurveMorph", colorSaturationCurveMorph->getFloat());
            renderShader.setUniform1f("colorBrightnessCurveMorph", colorBrightnessCurveMorph->getFloat());
            renderShader.setUniform1f("colorAlphaCurveMorph", colorAlphaCurveMorph->getFloat());
            break;
        default:
            break;
    };

    setLayerAUniforms();
    setLayerBUniforms();
    setLayerCUniforms();
    setLayerDUniforms();
    
    ofEnableAlphaBlending();
    
    // draw rect
    ofDrawRectangle(0,0,holdWidth, holdHeight);
    
    ofDisableAlphaBlending();
    
    renderShader.end();
    ofClearAlpha();
    outImage.end();
    
}

void TXWaveTerrain::windowResized(int w, int h) {
    if (maxWidthHeightRule != MAXWIDTHHEIGHTRULE_CUSTOMSIZE) {
        allocateTexture();
        //        outImage.begin();
        //        ofEnableAlphaBlending();
        //        ofClear(ofColor(0));
        //        ofDisableAlphaBlending();
        //        outImage.end();
    };
}

int TXWaveTerrain::getTextureWidth() {
    return outImage.getWidth();
}

int TXWaveTerrain::getTextureHeight() {
    return outImage.getHeight();
}

ofTexture *  TXWaveTerrain::getTexture() {
    return & outImage.getTexture();
}

void TXWaveTerrain::curvesImageSetup() {
    colorMixImage.allocate(512, 1, OF_IMAGE_COLOR_ALPHA);
    curvesImage.allocate(512, 1, OF_IMAGE_COLOR_ALPHA);
    curvesHSLImage.allocate(512, 1, OF_IMAGE_COLOR_ALPHA);
}

void TXWaveTerrain::updateColorMixImagePixels() {
    ofColor holdColor;
    for(int x = 0; x < 256; ++x){
        holdColor.set(colorMixCurveA.parameters.getFloat(x) * 255.0f, 0.0f, 0.0f, 0.0f);
        colorMixImage.setColor(x, 0, holdColor);
        holdColor.set(colorMixCurveB.parameters.getFloat(x) * 255.0f, 0.0f, 0.0f, 0.0f);
        colorMixImage.setColor(x + 256, 0, holdColor);
    }
    colorMixImage.update();
}

void TXWaveTerrain::updateCurvesImagePixels() {
    ofColor holdColor;
    for(int x = 0; x < 256; ++x){
        holdColor.set(lookupCurve1A.parameters.getFloat(x) * 255.0f, lookupCurve2A.parameters.getFloat(x) * 255.0f, lookupCurve3A.parameters.getFloat(x) * 255.0f, lookupCurve4A.parameters.getFloat(x) * 255.0f);
        curvesImage.setColor(x, 0, holdColor);
        holdColor.set(lookupCurve1B.parameters.getFloat(x) * 255.0f, lookupCurve2B.parameters.getFloat(x) * 255.0f, lookupCurve3B.parameters.getFloat(x) * 255.0f, lookupCurve4B.parameters.getFloat(x) * 255.0f);
        curvesImage.setColor(x + 256, 0, holdColor);
    }
    curvesImage.update();
}

void TXWaveTerrain::updateCurvesHSLImagePixels() {
    ofColor holdColor;
    for(int x = 0; x < 256; ++x){
        holdColor.set(colorHueCurveA.parameters.getFloat(x) * 255.0f, colorSaturationCurveA.parameters.getFloat(x) * 255.0f, colorBrightnessCurveA.parameters.getFloat(x) * 255.0f, colorAlphaCurveA.parameters.getFloat(x) * 255.0f);
        curvesHSLImage.setColor(x, 0, holdColor);
        holdColor.set(colorHueCurveB.parameters.getFloat(x) * 255.0f, colorSaturationCurveB.parameters.getFloat(x) * 255.0f, colorBrightnessCurveB.parameters.getFloat(x) * 255.0f, colorAlphaCurveB.parameters.getFloat(x) * 255.0f);
        curvesHSLImage.setColor(x + 256, 0, holdColor);
    }
    curvesHSLImage.update();
}

void  TXWaveTerrain::colorMixImageChanged(ofAbstractParameter & dummyParameterArg ) {
    colorMixImageHasChanged = true;
}

void  TXWaveTerrain::curvesImageChanged(ofAbstractParameter & dummyParameterArg ) {
    curvesImageHasChanged = true;
}

void  TXWaveTerrain::curvesHSLImageChanged(ofAbstractParameter & dummyParameterArg ) {
    curvesHSLImageHasChanged = true;
}

void  TXWaveTerrain::shaderCodeChangedI(int & intArg) {
    shaderCodeHasChanged = true;
}

void  TXWaveTerrain::shaderCodeChangedB(bool & boolArg) {
    shaderCodeHasChanged = true;
}

void TXWaveTerrain::loadRenderShader(){
    renderShader.setupShaderFromSource(GL_VERTEX_SHADER, getVertexShader());
    renderShader.setupShaderFromSource(GL_FRAGMENT_SHADER, getFragmentShader());
    renderShader.linkProgram();
}

string TXWaveTerrain::getVertexShader(){
    string outString = string("#version 120\n") +
    STRINGIFY(
              void main() {
                  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
                  //gl_Position = ftransform();
              }
              );
    return outString;
}

string TXWaveTerrain::getFragmentShader(){
   
    switch (terrainStructure) {
        case 0:  // "1L (A)"
            layerAUsed = true;
            layerBUsed = false;
            layerCUsed = false;
            layerDUsed = false;
            break;
         case 1:  // "1L (B)"
            layerAUsed = false;
            layerBUsed = true;
            layerCUsed = false;
            layerDUsed = false;
            break;
        case 2:   // "1L (C)"
            layerAUsed = false;
            layerBUsed = false;
            layerCUsed = true;
            layerDUsed = false;
            break;
        case 3:  // "1L (D)"
            layerAUsed = false;
            layerBUsed = false;
            layerCUsed = false;
            layerDUsed = true;
            break;
        case 4:  // "2L (A:B)"
            layerAUsed = true;
            layerBUsed = true;
            layerCUsed = false;
            layerDUsed = false;
            break;
        case 5:  // "3L ((A:B) : C)"
            layerAUsed = true;
            layerBUsed = true;
            layerCUsed = true;
            layerDUsed = false;
            break;
        case 6:  // "3L (A : (B:C))"
            layerAUsed = true;
            layerBUsed = true;
            layerCUsed = true;
            layerDUsed = false;
            break;
        case 7:  // "4L (((A:B) : C) : D)"
            layerAUsed = true;
            layerBUsed = true;
            layerCUsed = true;
            layerDUsed = true;
            break;
        case 8:  // "4L ((A:B) : (C:D))"
            layerAUsed = true;
            layerBUsed = true;
            layerCUsed = true;
            layerDUsed = true;
            break;
        case 9:  // "4L ((A : (B:C)) : D)"
            layerAUsed = true;
            layerBUsed = true;
            layerCUsed = true;
            layerDUsed = true;
            break;
        case 10:  // "4L (A : (B : (C:D)))"
            layerAUsed = true;
            layerBUsed = true;
            layerCUsed = true;
            layerDUsed = true;
            break;
        default:
            layerAUsed = true;
            layerBUsed = false;
            layerCUsed = false;
            layerDUsed = false;
            break;
    };
    
    string outString = string("#version 120\n#define PI 3.141592653589793\n") +
    string("#define TWOPI 6.2831853071796\n#define TWOOVERPI 0.63661977236758\n#define SQRTTWO 1.4142135623731\n") +
    string("#define INVTWOPI 0.1591549430919\n#define INVSQRTTWO 0.70710678118655\n") +
    
    STRINGIFY(
              
              // Uniforms
              uniform vec2 resolution;
              uniform sampler2DRect curveSampler;
              uniform sampler2DRect curveHSLSampler;
              uniform sampler2DRect colorMixSampler;
              
              uniform float squeezeX;
              uniform float squeezeY;
              uniform float skewX;
              uniform float skewY;
              uniform float outputRangeMin;
              uniform float outputRangeMax;
              uniform int outputRangeProcess;
              
              uniform float colorMixCurveMorph;
              uniform float colorMixCurvePhase;
              uniform float lookupCurve1Morph;
              uniform float lookupCurve1Phase;
              uniform float lookupCurve2Morph;
              uniform float lookupCurve2Phase;
              uniform float lookupCurve3Morph;
              uniform float lookupCurve3Phase;
              uniform float lookupCurve4Morph;
              uniform float lookupCurve4Phase;
              uniform float perlinLayer1Mix;
              uniform float perlinLayer2Mix;
              uniform float perlinLayer3Mix;
              uniform float perlinLayer4Mix;
              uniform float colorHueCurveMorph;
              uniform float colorHueCurveRotate;
              uniform float colorSaturationCurveMorph;
              uniform float colorBrightnessCurveMorph;
              uniform float colorAlphaCurveMorph;
              uniform vec4 color1;
              uniform vec4 color2;
              uniform vec4 color3;
              );
    
    outString = outString +
    getLayerAUniforms() +
    getLayerBUniforms() +
    getLayerCUniforms() +
    getLayerDUniforms() +
    
    getGLSLFunctions() +
    
    // main loop
    string("\nvoid main() {\n") +
    STRINGIFY(
              float x, y, lookupVal, blend;   //  reusable variables
              vec4 colorA, colorB, outColor;
              float layerAOut, layerBOut, layerCOut, layerDOut;
              float outTerrain, chainAB, chainCD;
              float layerStartX, layerStartY, layerX, layerY, inputX, inputY;
              float offsetProcess1X, offsetProcess1Y, offsetProcess2X, offsetProcess2Y, processOut;
              //float tempX, tempY; // for testing
              
              // prepare xy
              vec2 xyPosNorm = (gl_FragCoord.xy / resolution.xy);
              
              inputX = xyPosNorm.x - 0.5;
              inputY = xyPosNorm.y - 0.5;
              
              // squeeze
              if (squeezeX != 0.0) {
                  inputX = inputX - (inputX * squeezeX * inputY * 2);
                  //inputX = inputX - (inputX * squeezeX * sqrt(abs(inputY) * 2.0) * sign(inputY));     // testing sqrt
                  //inputX = inputX - (inputX * squeezeX * pow(abs(inputY) * 2.0, 2.0) * sign(inputY)); // testing squared
              };
              if (squeezeY != 0.0) {
                  inputY = inputY - (inputY * squeezeY * inputX * 2);
                  //inputY = inputY - (inputY * squeezeY * sqrt(abs(inputX) * 2.0) * sign(inputX));     // testing sqrt
                  //inputY = inputY - (inputY * squeezeY * pow(abs(inputX) * 2.0, 2.0) * sign(inputX)); // testing squared
              };
              // skew
              if (skewX != 0.0) {
                  inputX = inputX + (skewX * inputY * 2.0);
              };
              if (skewY != 0.0) {
                  inputY = inputY + (skewY * inputX * 2.0);
              };
              layerStartX = inputX;
              layerStartY = inputY;
              ) +
    
    getLayerAValue() +
    getLayerBValue() +
    getLayerCValue() +
    getLayerDValue();
    
    switch (terrainStructure) {
        case 0:
            // "1L (A)"
            outString = outString +
            STRINGIFY(
                      outTerrain = layerAOut;
                      );
            break;
        case 1:
            // "1L (B)"
            outString = outString +
            STRINGIFY(
                      outTerrain = layerBOut;
                      );
            break;
        case 2:
            // "1L (C)"
            outString = outString +
            STRINGIFY(
                      outTerrain = layerCOut;
                      );
            break;
        case 3:
            // "1L (D)"
            outString = outString +
            STRINGIFY(
                      outTerrain = layerDOut;
                      );
            break;
        case 4:
            // "2L (A:B)"
            outString = outString +
            STRINGIFY(
                      x = layerAOut;
                      y = layerBOut;
                      outTerrain =
                      );
            outString = outString + getBinaryOpProcess(layerABJoinProcess);
            break;
        case 5:
            // "3L ((A:B) : C)"
            outString = outString +
            STRINGIFY(
                      x = layerAOut;
                      y = layerBOut;
                      outTerrain =
                      );
            outString = outString + getBinaryOpProcess(layerABJoinProcess);
            outString = outString +
            STRINGIFY(
                      x = outTerrain;
                      y = layerCOut;
                      outTerrain =
                      );
            outString = outString + getBinaryOpProcess(layerBCJoinProcess);
            break;
        case 6:
            // "3L (A : (B:C))"
            outString = outString +
            STRINGIFY(
                      x = layerBOut;
                      y = layerCOut;
                      outTerrain =
                      );
            outString = outString + getBinaryOpProcess(layerBCJoinProcess);
            outString = outString +
            STRINGIFY(
                      x = layerAOut;
                      y = outTerrain;
                      outTerrain =
                      );
            outString = outString + getBinaryOpProcess(layerABJoinProcess);
            break;
        case 7:
            // "4L (((A:B) : C) : D)"
            outString = outString +
            STRINGIFY(
                      x = layerAOut;
                      y = layerBOut;
                      outTerrain =
                      );
            outString = outString + getBinaryOpProcess(layerABJoinProcess);
            outString = outString +
            STRINGIFY(
                      x = outTerrain;
                      y = layerCOut;
                      outTerrain =
                      );
            outString = outString + getBinaryOpProcess(layerBCJoinProcess);
            outString = outString +
            STRINGIFY(
                      x = outTerrain;
                      y = layerDOut;
                      outTerrain =
                      );
            outString = outString + getBinaryOpProcess(layerCDJoinProcess);
            break;
        case 8:
            // "4L ((A:B) : (C:D))"
            outString = outString +
            STRINGIFY(
                      x = layerAOut;
                      y = layerBOut;
                      chainAB =
                      );
            outString = outString + getBinaryOpProcess(layerABJoinProcess);
            outString = outString +
            STRINGIFY(
                      x = layerCOut;
                      y = layerDOut;
                      chainCD =
                      );
            outString = outString + getBinaryOpProcess(layerCDJoinProcess);
            outString = outString +
            STRINGIFY(
                      x = chainAB;
                      y = chainCD;
                      outTerrain =
                      );
            outString = outString + getBinaryOpProcess(layerBCJoinProcess);
            break;
        case 9:
            // "4L ((A : (B:C)) : D)"
            outString = outString +
            STRINGIFY(
                      x = layerBOut;
                      y = layerCOut;
                      outTerrain =
                      );
            outString = outString + getBinaryOpProcess(layerBCJoinProcess);
            outString = outString +
            STRINGIFY(
                      x = layerAOut;
                      y = outTerrain;
                      outTerrain =
                      );
            outString = outString + getBinaryOpProcess(layerABJoinProcess);
            outString = outString +
            STRINGIFY(
                      x = outTerrain;
                      y = layerDOut;
                      outTerrain =
                      );
            outString = outString + getBinaryOpProcess(layerCDJoinProcess);
            break;
        case 10:
            // "4L (A : (B : (C:D)))"
            outString = outString +
            STRINGIFY(
                      x = layerCOut;
                      y = layerDOut;
                      outTerrain =
                      );
            outString = outString + getBinaryOpProcess(layerCDJoinProcess);
            outString = outString +
            STRINGIFY(
                      x = layerBOut;
                      y = outTerrain;
                      outTerrain =
                      );
            outString = outString + getBinaryOpProcess(layerBCJoinProcess);
            outString = outString +
            STRINGIFY(
                      x = layerAOut;
                      y = outTerrain;
                      outTerrain =
                      );
            outString = outString + getBinaryOpProcess(layerABJoinProcess);
            break;
        default:
            outString = outString +
            STRINGIFY(
                      outTerrain = 0;
                      );
            break;
    };

    outString = outString +
    STRINGIFY(
              // limit to range :  fold/ wrap/ clamp
              if (outputRangeProcess == 0) {
                  outTerrain = fold(outTerrain, min(outputRangeMin, outputRangeMax), max(outputRangeMin, outputRangeMax)) ;
              } else if (outputRangeProcess == 1) {
                  outTerrain = wrap(outTerrain, min(outputRangeMin, outputRangeMax), max(outputRangeMin, outputRangeMax)) ;
              } else  {
                  outTerrain = clamp(outTerrain, min(outputRangeMin, outputRangeMax), max(outputRangeMin, outputRangeMax)) ;
              };
              // normalise
              outTerrain = map(outTerrain, outputRangeMin, outputRangeMax, 0.0, 1.0);
              );

    switch (coloringMethod) {
        case 0:
            // "Use color1/2/3 with colorMixCurve to blend"
            outString = outString +
            STRINGIFY(
                      lookupVal = lookupColorMix(outTerrain, colorMixCurveMorph, colorMixCurvePhase);
                      if (lookupVal < 0.5) {
                          blend = lookupVal * 2;
                          colorA = color1;
                          colorB = color2;
                      } else {
                          blend = (lookupVal - 0.5) * 2;
                          colorA = color2;
                          colorB = color3;
                      };
                      outColor = mix(colorA, colorB, blend);
                      );
            break;
        case 1:
            // "Use color1/2/3 with linear blend"
            outString = outString +
            STRINGIFY(
                      if (outTerrain < 0.5) {
                          blend = outTerrain * 2;
                          colorA = color1;
                          colorB = color2;
                      } else {
                          blend = (outTerrain - 0.5) * 2;
                          colorA = color2;
                          colorB = color3;
                      };
                      outColor = mix(colorA, colorB, blend);
                      );
            break;
        case 2:
            // "Use color1/2 with colorMixCurve to blend"
            outString = outString +
            STRINGIFY(
                      lookupVal = lookupColorMix(outTerrain, colorMixCurveMorph, colorMixCurvePhase);
                      outColor = mix(color1, color2, lookupVal);
                      );
            break;
        case 3:
            // "Use color1/2 with linear blend"
            outString = outString +
            STRINGIFY(
                      outColor = mix(color1, color2, outTerrain);
                      );
            break;
        case 4:
            // "Use color2/3 with colorMixCurve to blend"
            outString = outString +
            STRINGIFY(
                      lookupVal = lookupColorMix(outTerrain, colorMixCurveMorph, colorMixCurvePhase);
                      outColor = mix(color2, color3, lookupVal);
                      );
            break;
        case 5:
            // "Use color2/3 with linear blend"
            outString = outString +
            STRINGIFY(
                      outColor = mix(color2, color3, outTerrain);
                      );
            break;
        case 6:
            // "Use Black/Grey/White with colorMixCurve to blend"
            outString = outString +
            STRINGIFY(
                      lookupVal = lookupColorMix(outTerrain, colorMixCurveMorph, colorMixCurvePhase);
                      outColor = mix(vec4(0, 0, 0, 1), vec4(1, 1, 1, 1), lookupVal);
                      );
            break;
        case 7:
            // "Use Black/Grey/White with linear blend"
            outString = outString +
            STRINGIFY(
                      outColor = mix(vec4(0, 0, 0, 1), vec4(1, 1, 1, 1), outTerrain);
                      );
            break;
        case 8:
            // "Use White/Black/White with colorMixCurve to blend"
            outString = outString +
            STRINGIFY(
                      lookupVal = lookupColorMix(outTerrain, colorMixCurveMorph, colorMixCurvePhase);
                      if (lookupVal < 0.5) {
                          blend = lookupVal * 2;
                          colorA = vec4(1, 1, 1, 1);
                          colorB = vec4(0, 0, 0, 1);
                      } else {
                          blend = (lookupVal - 0.5) * 2;
                          colorA = vec4(0, 0, 0, 1);
                          colorB = vec4(1, 1, 1, 1);
                      };
                      outColor = mix(colorA, colorB, blend);
                      );
            break;
        case 9:
            // "Use White/Black/White with linear blend"
            outString = outString +
            STRINGIFY(
                      if (outTerrain < 0.5) {
                          blend = outTerrain * 2;
                          colorA = vec4(1, 1, 1, 1);
                          colorB = vec4(0, 0, 0, 1);
                      } else {
                          blend = (outTerrain - 0.5) * 2;
                          colorA = vec4(0, 0, 0, 1);
                          colorB = vec4(1, 1, 1, 1);
                      };
                      outColor = mix(colorA, colorB, blend);
                      );
            break;
        case 10:
            // "Use Black/White/Black with colorMixCurve to blend"
            outString = outString +
            STRINGIFY(
                      lookupVal = lookupColorMix(outTerrain, colorMixCurveMorph, colorMixCurvePhase);
                      if (lookupVal < 0.5) {
                          blend = lookupVal * 2;
                          colorA = vec4(0, 0, 0, 1);
                          colorB = vec4(1, 1, 1, 1);
                      } else {
                          blend = (lookupVal - 0.5) * 2;
                          colorA = vec4(1, 1, 1, 1);
                          colorB = vec4(0, 0, 0, 1);
                      };
                      outColor = mix(colorA, colorB, blend);
                      );
            break;
        case 11:
            // "Use Black/White/Black with linear blend"
            outString = outString +
            STRINGIFY(
                      if (outTerrain < 0.5) {
                          blend = outTerrain * 2;
                          colorA = vec4(0, 0, 0, 1);
                          colorB = vec4(1, 1, 1, 1);
                      } else {
                          blend = (outTerrain - 0.5) * 2;
                          colorA = vec4(1, 1, 1, 1);
                          colorB = vec4(0, 0, 0, 1);
                      };
                      outColor = mix(colorA, colorB, blend);
                      );
            break;
        case 12:
            // "Use Blue/Black/Red with colorMixCurve to blend"
            outString = outString +
            STRINGIFY(
                      lookupVal = lookupColorMix(outTerrain, colorMixCurveMorph, colorMixCurvePhase);
                      if (lookupVal < 0.5) {
                          blend = lookupVal * 2;
                          colorA = vec4(0, 0, 1, 1);
                          colorB = vec4(0, 0, 0, 1);
                      } else {
                          blend = (lookupVal - 0.5) * 2;
                          colorA = vec4(0, 0, 0, 1);
                          colorB = vec4(1, 0, 0, 1);
                      };
                      outColor = mix(colorA, colorB, blend);
                      );
            break;
        case 13:
            // "Use Blue/Black/Red with linear blend"
            outString = outString +
            STRINGIFY(
                      if (outTerrain < 0.5) {
                          blend = outTerrain * 2;
                          colorA = vec4(0, 0, 1, 1);
                          colorB = vec4(0, 0, 0, 1);
                      } else {
                          blend = (outTerrain - 0.5) * 2;
                          colorA = vec4(0, 0, 0, 1);
                          colorB = vec4(1, 0, 0, 1);
                      };
                      outColor = mix(colorA, colorB, blend);
                      );
            break;
        case 14:
            // "Use Color Curves as HSBA with colorMixCurve to blend"
            outString = outString +
            STRINGIFY(
                      lookupVal = lookupColorMix(outTerrain, colorMixCurveMorph, colorMixCurvePhase);
                      outColor = lookupHSL(lookupVal);
                      vec3 convert = HSVToRGB(outColor.rgb);
                      outColor = vec4(convert, outColor.a);
                      );
            break;
        case 15:
            // "Use Color Curves as HSBA with linear blend"
            outString = outString +
            STRINGIFY(
                      outColor = lookupHSL(outTerrain);
                      vec3 convert = HSVToRGB(outColor.rgb);
                      outColor = vec4(convert, outColor.a);
                      );
            break;
        case 16:
            // "Use Color Curves as RGBA with colorMixCurve to blend"
            outString = outString +
            STRINGIFY(
                      lookupVal = lookupColorMix(outTerrain, colorMixCurveMorph, colorMixCurvePhase);
                      outColor = lookupHSL(lookupVal);
                      );
            break;
        case 17:
            // "Use Color Curves as RGBA with linear blend"
            outString = outString +
            STRINGIFY(
                      outColor = lookupHSL(outTerrain);
                      );
            break;
        case 18:
            // "Use Color Curves as HSLA with colorMixCurve to blend"
            outString = outString +
            STRINGIFY(
                      lookupVal = lookupColorMix(outTerrain, colorMixCurveMorph, colorMixCurvePhase);
                      outColor = lookupHSL(lookupVal);
                      vec3 convert = HSLToRGB(outColor.rgb);
                      outColor = vec4(convert, outColor.a);
                      );
            break;
        case 19:
            // "Use Color Curves as HSLA with linear blend"
            outString = outString +
            STRINGIFY(
                      outColor = lookupHSL(outTerrain);
                      vec3 convert = HSLToRGB(outColor.rgb);
                      outColor = vec4(convert, outColor.a);
                      );
            break;
        default:
            break;
    };

    outString = outString +
    STRINGIFY(
              // TESTING XXX
              //gl_FragColor =  vec4(1.0, 0.0, 0.5, 1.0);
              //gl_FragColor =  vec4(xyPosNorm, 0.5, 1.0);     // = NB  LOOKS NICE!
              //gl_FragColor =  vec4(layerX, layerY, 0.5, 1.0);
              //gl_FragColor =  vec4(outTerrain, layerAOut, 0.5, 1.0);
              //gl_FragColor =  vec4(tempX, tempY, 0.5, 1.0);

              // terrain color out
              gl_FragColor =  outColor;
              );

    // end of main loop
    outString = outString + string("\n}");
    
    return outString;
}

string TXWaveTerrain::getLayerAUniforms(){
    string outString = string(" ");
    if (layerAUsed) {
        outString = outString +
        STRINGIFY(
                  uniform float layerA_rotate;
                  uniform float layerA_inputXMin;
                  uniform float layerA_inputXMax;
                  uniform float layerA_inputYMin;
                  uniform float layerA_inputYMax;
                  );
        if (layerA_offsetProcess1Active) {
            outString = outString +
            STRINGIFY(
                      uniform float layerA_offsetProcess1MultInputX;
                      uniform float layerA_offsetProcess1AddInputX;
                      uniform float layerA_offsetProcess1MultOutputX;
                      uniform float layerA_offsetProcess1MultInputY;
                      uniform float layerA_offsetProcess1AddInputY;
                      uniform float layerA_offsetProcess1MultOutputY;
                      );
        };
        if (layerA_offsetProcess2Active) {
            outString = outString +
            STRINGIFY(
                      uniform float layerA_offsetProcess2MultInputX;
                      uniform float layerA_offsetProcess2AddInputX;
                      uniform float layerA_offsetProcess2MultOutputX;
                      uniform float layerA_offsetProcess2MultInputY;
                      uniform float layerA_offsetProcess2AddInputY;
                      uniform float layerA_offsetProcess2MultOutputY;
                      );
        };
        outString = outString +
        STRINGIFY(
                  uniform float layerA_genInputXMult;
                  uniform int   layerA_genInputXPower;
                  uniform float layerA_genInputYMult;
                  uniform int   layerA_genInputYPower;
                  uniform float layerA_genInputMult;
                  uniform float layerA_genInputOffset;
                  );
        if (layerA_postProcess1Active) {
            outString = outString +
            STRINGIFY(
                      uniform float layerA_postProcess1YVal;
                      );
        };
        if (layerA_postProcess2Active) {
            outString = outString +
            STRINGIFY(
                      uniform float layerA_postProcess2YVal;
                      );
        };
        if (layerA_postProcess3Active) {
            outString = outString +
            STRINGIFY(
                      uniform float layerA_postProcess3YVal;
                      );
        };
    };
    
    return outString;
}

void TXWaveTerrain::setLayerAUniforms(){
    if (layerAUsed) {
        renderShader.setUniform1f("layerA_rotate", ofDegToRad(layerA_rotate->getFloat()));
        renderShader.setUniform1f("layerA_inputXMin", layerA_inputXMin->getFloat());
        renderShader.setUniform1f("layerA_inputXMax", layerA_inputXMax->getFloat());
        renderShader.setUniform1f("layerA_inputYMin", layerA_inputYMin->getFloat());
        renderShader.setUniform1f("layerA_inputYMax", layerA_inputYMax->getFloat());
        if (layerA_offsetProcess1Active) {
            renderShader.setUniform1f("layerA_offsetProcess1MultInputX", layerA_offsetProcess1MultInputX->getFloat());
            renderShader.setUniform1f("layerA_offsetProcess1AddInputX", layerA_offsetProcess1AddInputX->getFloat());
            renderShader.setUniform1f("layerA_offsetProcess1MultOutputX", layerA_offsetProcess1MultOutputX->getFloat());
            renderShader.setUniform1f("layerA_offsetProcess1MultInputY", layerA_offsetProcess1MultInputY->getFloat());
            renderShader.setUniform1f("layerA_offsetProcess1AddInputY", layerA_offsetProcess1AddInputY->getFloat());
            renderShader.setUniform1f("layerA_offsetProcess1MultOutputY", layerA_offsetProcess1MultOutputY->getFloat());
        };
        if (layerA_offsetProcess2Active) {
            renderShader.setUniform1f("layerA_offsetProcess2MultInputX", layerA_offsetProcess2MultInputX->getFloat());
            renderShader.setUniform1f("layerA_offsetProcess2AddInputX", layerA_offsetProcess2AddInputX->getFloat());
            renderShader.setUniform1f("layerA_offsetProcess2MultOutputX", layerA_offsetProcess2MultOutputX->getFloat());
            renderShader.setUniform1f("layerA_offsetProcess2MultInputY", layerA_offsetProcess2MultInputY->getFloat());
            renderShader.setUniform1f("layerA_offsetProcess2AddInputY", layerA_offsetProcess2AddInputY->getFloat());
            renderShader.setUniform1f("layerA_offsetProcess2MultOutputY", layerA_offsetProcess2MultOutputY->getFloat());
        };
        renderShader.setUniform1f("layerA_genInputXMult", layerA_genInputXMult->getFloat());
        renderShader.setUniform1i("layerA_genInputXPower", layerA_genInputXPower->getInt());
        renderShader.setUniform1f("layerA_genInputYMult", layerA_genInputYMult->getFloat());
        renderShader.setUniform1i("layerA_genInputYPower", layerA_genInputYPower->getInt());
        renderShader.setUniform1f("layerA_genInputMult", layerA_genInputMult->getFloat());
        renderShader.setUniform1f("layerA_genInputOffset", layerA_genInputOffset->getFloat());
        if (layerA_postProcess1Active) {
            renderShader.setUniform1f("layerA_postProcess1YVal", layerA_postProcess1YVal->getFloat());
        };
        if (layerA_postProcess2Active) {
            renderShader.setUniform1f("layerA_postProcess2YVal", layerA_postProcess2YVal->getFloat());
        };
        if (layerA_postProcess3Active) {
            renderShader.setUniform1f("layerA_postProcess3YVal", layerA_postProcess3YVal->getFloat());
        };
    };
}

string TXWaveTerrain::getLayerAValue(){
    string outString =
    STRINGIFY(
              // Init layer
              layerX = layerStartX;
              layerY = layerStartY;
              );
if (layerAUsed) {
        // convert to polar if needed
        if(layerA_usePolarCoords) {
            outString = outString +
            STRINGIFY(
                      // CONVERT POLAR TO RECT
                      inputX = layerX * SQRTTWO;
                      inputY = layerY * TWOPI;
                      layerX = inputX * cos(inputY);
                      layerY = inputX * sin(inputY);
                      
                      // TESTING XXX - CONVERT RECT TO POLAR
                      // layerX = sqrt((layerX * layerX) + (layerY * layerY)) * SQRTTWO;
                      // layerY = atan(layerY / layerX) * INVTWOPI;
                      );
        };
        outString = outString +
        STRINGIFY(
                  // rotation
                  if (layerA_rotate != 0.0) {
                      inputX = layerX;
                      inputY = layerY;
                      layerX = (inputX * cos(layerA_rotate)) - (inputY * sin(layerA_rotate));
                      layerY = (inputX * sin(layerA_rotate)) + (inputY * cos(layerA_rotate));
                  };
                  );
        // map inputs
        outString = outString +
        STRINGIFY(
                  layerX = map(layerX, -0.5, 0.5, layerA_inputXMin, layerA_inputXMax);
                  layerY = map(layerY, -0.5, 0.5, layerA_inputYMin, layerA_inputYMax);
                    );
        // apply offsets
        if (layerA_offsetProcess1Active) {
            outString = outString +
            STRINGIFY(
                      x = (layerX * layerA_offsetProcess1MultInputX) + layerA_offsetProcess1AddInputX;
                      processOut =
                      );
            outString = outString + getUnaryOpProcess(layerA_offsetProcess1Type);
            outString = outString +
            STRINGIFY(
                      offsetProcess1X = processOut * layerA_offsetProcess1MultOutputX;
                      );
            outString = outString +
            STRINGIFY(
                      x = (layerY * layerA_offsetProcess1MultInputY) + layerA_offsetProcess1AddInputY;
                      processOut =
                      );
            outString = outString + getUnaryOpProcess(layerA_offsetProcess1Type);
            outString = outString +
            STRINGIFY(
                      offsetProcess1Y = processOut * layerA_offsetProcess1MultOutputY;
                      );
        } else {
            outString = outString +
            STRINGIFY(
                      offsetProcess1X = 0;
                      offsetProcess1Y = 0;
                      );
        };
        if (layerA_offsetProcess2Active) {
            // prepare inputs
            if (layerA_offsetProcs12InSeries) {
                outString = outString +
                STRINGIFY(
                          inputX = layerX + offsetProcess1X;
                          inputY = layerY + offsetProcess1Y;
                          );
            } else {
                outString = outString +
                STRINGIFY(
                          inputX = layerX;
                          inputY = layerY;
                          );
            };
            outString = outString +
            STRINGIFY(
                      x = (inputX * layerA_offsetProcess2MultInputX) + layerA_offsetProcess2AddInputX;
                      processOut =
                      );
            outString = outString + getUnaryOpProcess(layerA_offsetProcess2Type);
            outString = outString +
            STRINGIFY(
                      offsetProcess2X = processOut * layerA_offsetProcess2MultOutputX;
                      );
            outString = outString +
            STRINGIFY(
                      x = (inputY * layerA_offsetProcess2MultInputY) + layerA_offsetProcess2AddInputY;
                      processOut =
                      );
            outString = outString + getUnaryOpProcess(layerA_offsetProcess2Type);
            outString = outString +
            STRINGIFY(
                      offsetProcess2Y = processOut * layerA_offsetProcess2MultOutputY;
                      );
        } else {
            outString = outString +
            STRINGIFY(
                      offsetProcess2X = 0;
                      offsetProcess2Y = 0;
                      );
        };
        // add offsets to layer
        if (!(layerA_offsetProcess2Active && layerA_offsetProcs12InSeries)) {
            outString = outString +
            STRINGIFY(
                      layerX = layerX + offsetProcess1X;
                      layerY = layerY + offsetProcess1Y;
                      );
        };
        outString = outString +
        STRINGIFY(
                  layerX = layerX + offsetProcess2X;
                  layerY = layerY + offsetProcess2Y;
                  );
        // generate terrain
        outString = outString +
        STRINGIFY(
                  x = layerA_genInputXMult * pow(layerX, layerA_genInputXPower);
                  y = layerA_genInputYMult * pow(layerY, layerA_genInputYPower);
                  processOut =
                  );
        outString = outString + getBinaryOpProcess(layerA_genInputXYProcess);
        outString = outString +
        STRINGIFY(
                  x = (processOut * layerA_genInputMult) + layerA_genInputOffset;
                  processOut =
                  );
        outString = outString + getUnaryOpProcess(layerA_generatorProcessType);
        if (layerA_postProcess1Active) {
            outString = outString +
            STRINGIFY(
                      x = processOut;
                      y = layerA_postProcess1YVal;
                      processOut =
                      );
        };
        outString = outString + getUnaryOrBinaryOpProcess(layerA_postProcess1Type);
        if (layerA_postProcess2Active) {
            outString = outString +
            STRINGIFY(
                      x = processOut;
                      y = layerA_postProcess2YVal;
                      processOut =
                      );
        };
        outString = outString + getUnaryOrBinaryOpProcess(layerA_postProcess2Type);
        if (layerA_postProcess3Active) {
            outString = outString +
            STRINGIFY(
                      x = processOut;
                      y = layerA_postProcess3YVal;
                      processOut =
                      );
        };
        outString = outString + getUnaryOrBinaryOpProcess(layerA_postProcess3Type);
        outString = outString + string(" \nlayerAOut = processOut; \n");
    } else {
        outString = string(" \nlayerAOut = 0; \n");
    };

    return outString;
}

string TXWaveTerrain::getLayerBUniforms(){
    string outString = string(" ");
    if (layerBUsed) {
        outString = outString +
        STRINGIFY(
                  uniform float layerB_rotate;
                  uniform float layerB_inputXMin;
                  uniform float layerB_inputXMax;
                  uniform float layerB_inputYMin;
                  uniform float layerB_inputYMax;
                  );
        if (layerB_offsetProcess1Active) {
            outString = outString +
            STRINGIFY(
                      uniform float layerB_offsetProcess1MultInputX;
                      uniform float layerB_offsetProcess1AddInputX;
                      uniform float layerB_offsetProcess1MultOutputX;
                      uniform float layerB_offsetProcess1MultInputY;
                      uniform float layerB_offsetProcess1AddInputY;
                      uniform float layerB_offsetProcess1MultOutputY;
                      );
        };
        if (layerB_offsetProcess2Active) {
            outString = outString +
            STRINGIFY(
                      uniform float layerB_offsetProcess2MultInputX;
                      uniform float layerB_offsetProcess2AddInputX;
                      uniform float layerB_offsetProcess2MultOutputX;
                      uniform float layerB_offsetProcess2MultInputY;
                      uniform float layerB_offsetProcess2AddInputY;
                      uniform float layerB_offsetProcess2MultOutputY;
                      );
        };
        outString = outString +
        STRINGIFY(
                  uniform float layerB_genInputXMult;
                  uniform int   layerB_genInputXPower;
                  uniform float layerB_genInputYMult;
                  uniform int   layerB_genInputYPower;
                  uniform float layerB_genInputMult;
                  uniform float layerB_genInputOffset;
                  );
        if (layerB_postProcess1Active) {
            outString = outString +
            STRINGIFY(
                      uniform float layerB_postProcess1YVal;
                      );
        };
        if (layerB_postProcess2Active) {
            outString = outString +
            STRINGIFY(
                      uniform float layerB_postProcess2YVal;
                      );
        };
        if (layerB_postProcess3Active) {
            outString = outString +
            STRINGIFY(
                      uniform float layerB_postProcess3YVal;
                      );
        };
    };
    
    return outString;
}

void TXWaveTerrain::setLayerBUniforms(){
    if (layerBUsed) {
        renderShader.setUniform1f("layerB_rotate", ofDegToRad(layerB_rotate->getFloat()));
        renderShader.setUniform1f("layerB_inputXMin", layerB_inputXMin->getFloat());
        renderShader.setUniform1f("layerB_inputXMax", layerB_inputXMax->getFloat());
        renderShader.setUniform1f("layerB_inputYMin", layerB_inputYMin->getFloat());
        renderShader.setUniform1f("layerB_inputYMax", layerB_inputYMax->getFloat());
        if (layerB_offsetProcess1Active) {
            renderShader.setUniform1f("layerB_offsetProcess1MultInputX", layerB_offsetProcess1MultInputX->getFloat());
            renderShader.setUniform1f("layerB_offsetProcess1AddInputX", layerB_offsetProcess1AddInputX->getFloat());
            renderShader.setUniform1f("layerB_offsetProcess1MultOutputX", layerB_offsetProcess1MultOutputX->getFloat());
            renderShader.setUniform1f("layerB_offsetProcess1MultInputY", layerB_offsetProcess1MultInputY->getFloat());
            renderShader.setUniform1f("layerB_offsetProcess1AddInputY", layerB_offsetProcess1AddInputY->getFloat());
            renderShader.setUniform1f("layerB_offsetProcess1MultOutputY", layerB_offsetProcess1MultOutputY->getFloat());
        };
        if (layerB_offsetProcess2Active) {
            renderShader.setUniform1f("layerB_offsetProcess2MultInputX", layerB_offsetProcess2MultInputX->getFloat());
            renderShader.setUniform1f("layerB_offsetProcess2AddInputX", layerB_offsetProcess2AddInputX->getFloat());
            renderShader.setUniform1f("layerB_offsetProcess2MultOutputX", layerB_offsetProcess2MultOutputX->getFloat());
            renderShader.setUniform1f("layerB_offsetProcess2MultInputY", layerB_offsetProcess2MultInputY->getFloat());
            renderShader.setUniform1f("layerB_offsetProcess2AddInputY", layerB_offsetProcess2AddInputY->getFloat());
            renderShader.setUniform1f("layerB_offsetProcess2MultOutputY", layerB_offsetProcess2MultOutputY->getFloat());
        };
        renderShader.setUniform1f("layerB_genInputXMult", layerB_genInputXMult->getFloat());
        renderShader.setUniform1i("layerB_genInputXPower", layerB_genInputXPower->getInt());
        renderShader.setUniform1f("layerB_genInputYMult", layerB_genInputYMult->getFloat());
        renderShader.setUniform1i("layerB_genInputYPower", layerB_genInputYPower->getInt());
        renderShader.setUniform1f("layerB_genInputMult", layerB_genInputMult->getFloat());
        renderShader.setUniform1f("layerB_genInputOffset", layerB_genInputOffset->getFloat());
        if (layerB_postProcess1Active) {
            renderShader.setUniform1f("layerB_postProcess1YVal", layerB_postProcess1YVal->getFloat());
        };
        if (layerB_postProcess2Active) {
            renderShader.setUniform1f("layerB_postProcess2YVal", layerB_postProcess2YVal->getFloat());
        };
        if (layerB_postProcess3Active) {
            renderShader.setUniform1f("layerB_postProcess3YVal", layerB_postProcess3YVal->getFloat());
        };
    };
}

string TXWaveTerrain::getLayerBValue(){
    string outString =
    STRINGIFY(
              // Init layer
              layerX = layerStartX;
              layerY = layerStartY;
              );
    if (layerBUsed) {
        // convert to polar if needed
        if(layerB_usePolarCoords) {
            outString = outString +
            STRINGIFY(
                      inputX = layerX * SQRTTWO;
                      inputY = layerY * TWOPI;
                      layerX = inputX * cos(inputY);
                      layerY = inputX * sin(inputY);
                      );
        };
        outString = outString +
        STRINGIFY(
                  // rotation
                  if (layerB_rotate != 0.0) {
                      inputX = layerX;
                      inputY = layerY ;
                      layerX = (inputX * cos(layerB_rotate)) - (inputY * sin(layerB_rotate));
                      layerY = (inputX * sin(layerB_rotate)) + (inputY * cos(layerB_rotate));
                  };
                  );
        // map inputs
        outString = outString +
        STRINGIFY(
                  layerX = map(layerX, -0.5, 0.5, layerB_inputXMin, layerB_inputXMax);
                  layerY = map(layerY, -0.5, 0.5, layerB_inputYMin, layerB_inputYMax);
                  );
        // apply offsets
        if (layerB_offsetProcess1Active) {
            outString = outString +
            STRINGIFY(
                      x = (layerX * layerB_offsetProcess1MultInputX) + layerB_offsetProcess1AddInputX;
                      processOut =
                      );
            outString = outString + getUnaryOpProcess(layerB_offsetProcess1Type);
            outString = outString +
            STRINGIFY(
                      offsetProcess1X = processOut * layerB_offsetProcess1MultOutputX;
                      );
            outString = outString +
            STRINGIFY(
                      x = (layerY * layerB_offsetProcess1MultInputY) + layerB_offsetProcess1AddInputY;
                      processOut =
                      );
            outString = outString + getUnaryOpProcess(layerB_offsetProcess1Type);
            outString = outString +
            STRINGIFY(
                      offsetProcess1Y = processOut * layerB_offsetProcess1MultOutputY;
                      );
        } else {
            outString = outString +
            STRINGIFY(
                      offsetProcess1X = 0;
                      offsetProcess1Y = 0;
                      );
        };
        if (layerB_offsetProcess2Active) {
            // prepare inputs
            if (layerB_offsetProcs12InSeries) {
                outString = outString +
                STRINGIFY(
                          inputX = layerX + offsetProcess1X;
                          inputY = layerY + offsetProcess1Y;
                          );
            } else {
                outString = outString +
                STRINGIFY(
                          inputX = layerX;
                          inputY = layerY;
                          );
            };
            outString = outString +
            STRINGIFY(
                      x = (inputX * layerB_offsetProcess2MultInputX) + layerB_offsetProcess2AddInputX;
                      processOut =
                      );
            outString = outString + getUnaryOpProcess(layerB_offsetProcess2Type);
            outString = outString +
            STRINGIFY(
                      offsetProcess2X = processOut * layerB_offsetProcess2MultOutputX;
                      );
            outString = outString +
            STRINGIFY(
                      x = (inputY * layerB_offsetProcess2MultInputY) + layerB_offsetProcess2AddInputY;
                      processOut =
                      );
            outString = outString + getUnaryOpProcess(layerB_offsetProcess2Type);
            outString = outString +
            STRINGIFY(
                      offsetProcess2Y = processOut * layerB_offsetProcess2MultOutputY;
                      );
        } else {
            outString = outString +
            STRINGIFY(
                      offsetProcess2X = 0;
                      offsetProcess2Y = 0;
                      );
        };
        // add offsets to layer
        if (!(layerB_offsetProcess2Active && layerB_offsetProcs12InSeries)) {
            outString = outString +
            STRINGIFY(
                      layerX = layerX + offsetProcess1X;
                      layerY = layerY + offsetProcess1Y;
                      );
        };
        outString = outString +
        STRINGIFY(
                  layerX = layerX + offsetProcess2X;
                  layerY = layerY + offsetProcess2Y;
                  );
        // generate terrain
        outString = outString +
        STRINGIFY(
                  x = layerB_genInputXMult * pow(layerX, layerB_genInputXPower);
                  y = layerB_genInputYMult * pow(layerY, layerB_genInputYPower);
                  processOut =
                  );
        outString = outString + getBinaryOpProcess(layerB_genInputXYProcess);
        outString = outString +
        STRINGIFY(
                  x = (processOut * layerB_genInputMult) + layerB_genInputOffset;
                  processOut =
                  );
        outString = outString + getUnaryOpProcess(layerB_generatorProcessType);
        if (layerB_postProcess1Active) {
            outString = outString +
            STRINGIFY(
                      x = processOut;
                      y = layerB_postProcess1YVal;
                      processOut =
                      );
        };
        outString = outString + getUnaryOrBinaryOpProcess(layerB_postProcess1Type);
        if (layerB_postProcess2Active) {
            outString = outString +
            STRINGIFY(
                      x = processOut;
                      y = layerB_postProcess2YVal;
                      processOut =
                      );
        };
        outString = outString + getUnaryOrBinaryOpProcess(layerB_postProcess2Type);
        if (layerB_postProcess3Active) {
            outString = outString +
            STRINGIFY(
                      x = processOut;
                      y = layerB_postProcess3YVal;
                      processOut =
                      );
        };
        outString = outString + getUnaryOrBinaryOpProcess(layerB_postProcess3Type);
        outString = outString + string(" \nlayerBOut = processOut; \n");
    } else {
        outString = string(" \nlayerBOut = 0; \n");
    };
    
    return outString;
}


string TXWaveTerrain::getLayerCUniforms(){
    string outString = string(" ");
    if (layerCUsed) {
        outString = outString +
        STRINGIFY(
                  uniform float layerC_rotate;
                  uniform float layerC_inputXMin;
                  uniform float layerC_inputXMax;
                  uniform float layerC_inputYMin;
                  uniform float layerC_inputYMax;
                  );
        if (layerC_offsetProcess1Active) {
            outString = outString +
            STRINGIFY(
                      uniform float layerC_offsetProcess1MultInputX;
                      uniform float layerC_offsetProcess1AddInputX;
                      uniform float layerC_offsetProcess1MultOutputX;
                      uniform float layerC_offsetProcess1MultInputY;
                      uniform float layerC_offsetProcess1AddInputY;
                      uniform float layerC_offsetProcess1MultOutputY;
                      );
        };
        if (layerC_offsetProcess2Active) {
            outString = outString +
            STRINGIFY(
                      uniform float layerC_offsetProcess2MultInputX;
                      uniform float layerC_offsetProcess2AddInputX;
                      uniform float layerC_offsetProcess2MultOutputX;
                      uniform float layerC_offsetProcess2MultInputY;
                      uniform float layerC_offsetProcess2AddInputY;
                      uniform float layerC_offsetProcess2MultOutputY;
                      );
        };
        outString = outString +
        STRINGIFY(
                  uniform float layerC_genInputXMult;
                  uniform int   layerC_genInputXPower;
                  uniform float layerC_genInputYMult;
                  uniform int   layerC_genInputYPower;
                  uniform float layerC_genInputMult;
                  uniform float layerC_genInputOffset;
                  );
        if (layerC_postProcess1Active) {
            outString = outString +
            STRINGIFY(
                      uniform float layerC_postProcess1YVal;
                      );
        };
        if (layerC_postProcess2Active) {
            outString = outString +
            STRINGIFY(
                      uniform float layerC_postProcess2YVal;
                      );
        };
        if (layerC_postProcess3Active) {
            outString = outString +
            STRINGIFY(
                      uniform float layerC_postProcess3YVal;
                      );
        };
    };
    
    return outString;
}

void TXWaveTerrain::setLayerCUniforms(){
    if (layerCUsed) {
        renderShader.setUniform1f("layerC_rotate", ofDegToRad(layerC_rotate->getFloat()));
        renderShader.setUniform1f("layerC_inputXMin", layerC_inputXMin->getFloat());
        renderShader.setUniform1f("layerC_inputXMax", layerC_inputXMax->getFloat());
        renderShader.setUniform1f("layerC_inputYMin", layerC_inputYMin->getFloat());
        renderShader.setUniform1f("layerC_inputYMax", layerC_inputYMax->getFloat());
        if (layerC_offsetProcess1Active) {
            renderShader.setUniform1f("layerC_offsetProcess1MultInputX", layerC_offsetProcess1MultInputX->getFloat());
            renderShader.setUniform1f("layerC_offsetProcess1AddInputX", layerC_offsetProcess1AddInputX->getFloat());
            renderShader.setUniform1f("layerC_offsetProcess1MultOutputX", layerC_offsetProcess1MultOutputX->getFloat());
            renderShader.setUniform1f("layerC_offsetProcess1MultInputY", layerC_offsetProcess1MultInputY->getFloat());
            renderShader.setUniform1f("layerC_offsetProcess1AddInputY", layerC_offsetProcess1AddInputY->getFloat());
            renderShader.setUniform1f("layerC_offsetProcess1MultOutputY", layerC_offsetProcess1MultOutputY->getFloat());
        };
        if (layerC_offsetProcess2Active) {
            renderShader.setUniform1f("layerC_offsetProcess2MultInputX", layerC_offsetProcess2MultInputX->getFloat());
            renderShader.setUniform1f("layerC_offsetProcess2AddInputX", layerC_offsetProcess2AddInputX->getFloat());
            renderShader.setUniform1f("layerC_offsetProcess2MultOutputX", layerC_offsetProcess2MultOutputX->getFloat());
            renderShader.setUniform1f("layerC_offsetProcess2MultInputY", layerC_offsetProcess2MultInputY->getFloat());
            renderShader.setUniform1f("layerC_offsetProcess2AddInputY", layerC_offsetProcess2AddInputY->getFloat());
            renderShader.setUniform1f("layerC_offsetProcess2MultOutputY", layerC_offsetProcess2MultOutputY->getFloat());
        };
        renderShader.setUniform1f("layerC_genInputXMult", layerC_genInputXMult->getFloat());
        renderShader.setUniform1i("layerC_genInputXPower", layerC_genInputXPower->getInt());
        renderShader.setUniform1f("layerC_genInputYMult", layerC_genInputYMult->getFloat());
        renderShader.setUniform1i("layerC_genInputYPower", layerC_genInputYPower->getInt());
        renderShader.setUniform1f("layerC_genInputMult", layerC_genInputMult->getFloat());
        renderShader.setUniform1f("layerC_genInputOffset", layerC_genInputOffset->getFloat());
        if (layerC_postProcess1Active) {
            renderShader.setUniform1f("layerC_postProcess1YVal", layerC_postProcess1YVal->getFloat());
        };
        if (layerC_postProcess2Active) {
            renderShader.setUniform1f("layerC_postProcess2YVal", layerC_postProcess2YVal->getFloat());
        };
        if (layerC_postProcess3Active) {
            renderShader.setUniform1f("layerC_postProcess3YVal", layerC_postProcess3YVal->getFloat());
        };
    };
}

string TXWaveTerrain::getLayerCValue(){
    string outString =
    STRINGIFY(
              // Init layer
              layerX = layerStartX;
              layerY = layerStartY;
              );
    if (layerCUsed) {
        // convert to polar if needed
        if(layerC_usePolarCoords) {
            outString = outString +
            STRINGIFY(
                      inputX = layerX * SQRTTWO;
                      inputY = layerY * TWOPI;
                      layerX = inputX * cos(inputY);
                      layerY = inputX * sin(inputY);
                      );
        };
        outString = outString +
        STRINGIFY(
                  // rotation
                  if (layerC_rotate != 0.0) {
                      inputX = layerX;
                      inputY = layerY;
                      layerX = (inputX * cos(layerC_rotate)) - (inputY * sin(layerC_rotate));
                      layerY = (inputX * sin(layerC_rotate)) + (inputY * cos(layerC_rotate));
                  };
                  );
        // map inputs
        outString = outString +
        STRINGIFY(
                  layerX = map(layerX, -0.5, 0.5, layerC_inputXMin, layerC_inputXMax);
                  layerY = map(layerY, -0.5, 0.5, layerC_inputYMin, layerC_inputYMax);
                  );
        // apply offsets
        if (layerC_offsetProcess1Active) {
            outString = outString +
            STRINGIFY(
                      x = (layerX * layerC_offsetProcess1MultInputX) + layerC_offsetProcess1AddInputX;
                      processOut =
                      );
            outString = outString + getUnaryOpProcess(layerC_offsetProcess1Type);
            outString = outString +
            STRINGIFY(
                      offsetProcess1X = processOut * layerC_offsetProcess1MultOutputX;
                      );
            outString = outString +
            STRINGIFY(
                      x = (layerY * layerC_offsetProcess1MultInputY) + layerC_offsetProcess1AddInputY;
                      processOut =
                      );
            outString = outString + getUnaryOpProcess(layerC_offsetProcess1Type);
            outString = outString +
            STRINGIFY(
                      offsetProcess1Y = processOut * layerC_offsetProcess1MultOutputY;
                      );
        } else {
            outString = outString +
            STRINGIFY(
                      offsetProcess1X = 0;
                      offsetProcess1Y = 0;
                      );
        };
        if (layerC_offsetProcess2Active) {
            // prepare inputs
            if (layerC_offsetProcs12InSeries) {
                outString = outString +
                STRINGIFY(
                          inputX = layerX + offsetProcess1X;
                          inputY = layerY + offsetProcess1Y;
                          );
            } else {
                outString = outString +
                STRINGIFY(
                          inputX = layerX;
                          inputY = layerY;
                          );
            };
            outString = outString +
            STRINGIFY(
                      x = (inputX * layerC_offsetProcess2MultInputX) + layerC_offsetProcess2AddInputX;
                      processOut =
                      );
            outString = outString + getUnaryOpProcess(layerC_offsetProcess2Type);
            outString = outString +
            STRINGIFY(
                      offsetProcess2X = processOut * layerC_offsetProcess2MultOutputX;
                      );
            outString = outString +
            STRINGIFY(
                      x = (inputY * layerC_offsetProcess2MultInputY) + layerC_offsetProcess2AddInputY;
                      processOut =
                      );
            outString = outString + getUnaryOpProcess(layerC_offsetProcess2Type);
            outString = outString +
            STRINGIFY(
                      offsetProcess2Y = processOut * layerC_offsetProcess2MultOutputY;
                      );
        } else {
            outString = outString +
            STRINGIFY(
                      offsetProcess2X = 0;
                      offsetProcess2Y = 0;
                      );
        };
        // add offsets to layer
        if (!(layerC_offsetProcess2Active && layerC_offsetProcs12InSeries)) {
            outString = outString +
            STRINGIFY(
                      layerX = layerX + offsetProcess1X;
                      layerY = layerY + offsetProcess1Y;
                      );
        };
        outString = outString +
        STRINGIFY(
                  layerX = layerX + offsetProcess2X;
                  layerY = layerY + offsetProcess2Y;
                  );
        // generate terrain
        outString = outString +
        STRINGIFY(
                  x = layerC_genInputXMult * pow(layerX, layerC_genInputXPower);
                  y = layerC_genInputYMult * pow(layerY, layerC_genInputYPower);
                  processOut =
                  );
        outString = outString + getBinaryOpProcess(layerC_genInputXYProcess);
        outString = outString +
        STRINGIFY(
                  x = (processOut * layerC_genInputMult) + layerC_genInputOffset;
                  processOut =
                  );
        outString = outString + getUnaryOpProcess(layerC_generatorProcessType);
        if (layerC_postProcess1Active) {
            outString = outString +
            STRINGIFY(
                      x = processOut;
                      y = layerC_postProcess1YVal;
                      processOut =
                      );
        };
        outString = outString + getUnaryOrBinaryOpProcess(layerC_postProcess1Type);
        if (layerC_postProcess2Active) {
            outString = outString +
            STRINGIFY(
                      x = processOut;
                      y = layerC_postProcess2YVal;
                      processOut =
                      );
        };
        outString = outString + getUnaryOrBinaryOpProcess(layerC_postProcess2Type);
        if (layerC_postProcess3Active) {
            outString = outString +
            STRINGIFY(
                      x = processOut;
                      y = layerC_postProcess3YVal;
                      processOut =
                      );
        };
        outString = outString + getUnaryOrBinaryOpProcess(layerC_postProcess3Type);
        outString = outString + string(" \nlayerCOut = processOut; \n");
    } else {
        outString = string(" \nlayerCOut = 0; \n");
    };
    
    return outString;
}


string TXWaveTerrain::getLayerDUniforms(){
    string outString = string(" ");
    if (layerDUsed) {
        outString = outString +
        STRINGIFY(
                  uniform float layerD_rotate;
                  uniform float layerD_inputXMin;
                  uniform float layerD_inputXMax;
                  uniform float layerD_inputYMin;
                  uniform float layerD_inputYMax;
                  );
        if (layerD_offsetProcess1Active) {
            outString = outString +
            STRINGIFY(
                      uniform float layerD_offsetProcess1MultInputX;
                      uniform float layerD_offsetProcess1AddInputX;
                      uniform float layerD_offsetProcess1MultOutputX;
                      uniform float layerD_offsetProcess1MultInputY;
                      uniform float layerD_offsetProcess1AddInputY;
                      uniform float layerD_offsetProcess1MultOutputY;
                      );
        };
        if (layerD_offsetProcess2Active) {
            outString = outString +
            STRINGIFY(
                      uniform float layerD_offsetProcess2MultInputX;
                      uniform float layerD_offsetProcess2AddInputX;
                      uniform float layerD_offsetProcess2MultOutputX;
                      uniform float layerD_offsetProcess2MultInputY;
                      uniform float layerD_offsetProcess2AddInputY;
                      uniform float layerD_offsetProcess2MultOutputY;
                      );
        };
        outString = outString +
        STRINGIFY(
                  uniform float layerD_genInputXMult;
                  uniform int   layerD_genInputXPower;
                  uniform float layerD_genInputYMult;
                  uniform int   layerD_genInputYPower;
                  uniform float layerD_genInputMult;
                  uniform float layerD_genInputOffset;
                  );
        if (layerD_postProcess1Active) {
            outString = outString +
            STRINGIFY(
                      uniform float layerD_postProcess1YVal;
                      );
        };
        if (layerD_postProcess2Active) {
            outString = outString +
            STRINGIFY(
                      uniform float layerD_postProcess2YVal;
                      );
        };
        if (layerD_postProcess3Active) {
            outString = outString +
            STRINGIFY(
                      uniform float layerD_postProcess3YVal;
                      );
        };
    };
    
    return outString;
}

void TXWaveTerrain::setLayerDUniforms(){
    if (layerDUsed) {
        renderShader.setUniform1f("layerD_rotate", ofDegToRad(layerD_rotate->getFloat()));
        renderShader.setUniform1f("layerD_inputXMin", layerD_inputXMin->getFloat());
        renderShader.setUniform1f("layerD_inputXMax", layerD_inputXMax->getFloat());
        renderShader.setUniform1f("layerD_inputYMin", layerD_inputYMin->getFloat());
        renderShader.setUniform1f("layerD_inputYMax", layerD_inputYMax->getFloat());
        if (layerD_offsetProcess1Active) {
            renderShader.setUniform1f("layerD_offsetProcess1MultInputX", layerD_offsetProcess1MultInputX->getFloat());
            renderShader.setUniform1f("layerD_offsetProcess1AddInputX", layerD_offsetProcess1AddInputX->getFloat());
            renderShader.setUniform1f("layerD_offsetProcess1MultOutputX", layerD_offsetProcess1MultOutputX->getFloat());
            renderShader.setUniform1f("layerD_offsetProcess1MultInputY", layerD_offsetProcess1MultInputY->getFloat());
            renderShader.setUniform1f("layerD_offsetProcess1AddInputY", layerD_offsetProcess1AddInputY->getFloat());
            renderShader.setUniform1f("layerD_offsetProcess1MultOutputY", layerD_offsetProcess1MultOutputY->getFloat());
        };
        if (layerD_offsetProcess2Active) {
            renderShader.setUniform1f("layerD_offsetProcess2MultInputX", layerD_offsetProcess2MultInputX->getFloat());
            renderShader.setUniform1f("layerD_offsetProcess2AddInputX", layerD_offsetProcess2AddInputX->getFloat());
            renderShader.setUniform1f("layerD_offsetProcess2MultOutputX", layerD_offsetProcess2MultOutputX->getFloat());
            renderShader.setUniform1f("layerD_offsetProcess2MultInputY", layerD_offsetProcess2MultInputY->getFloat());
            renderShader.setUniform1f("layerD_offsetProcess2AddInputY", layerD_offsetProcess2AddInputY->getFloat());
            renderShader.setUniform1f("layerD_offsetProcess2MultOutputY", layerD_offsetProcess2MultOutputY->getFloat());
        };
        renderShader.setUniform1f("layerD_genInputXMult", layerD_genInputXMult->getFloat());
        renderShader.setUniform1i("layerD_genInputXPower", layerD_genInputXPower->getInt());
        renderShader.setUniform1f("layerD_genInputYMult", layerD_genInputYMult->getFloat());
        renderShader.setUniform1i("layerD_genInputYPower", layerD_genInputYPower->getInt());
        renderShader.setUniform1f("layerD_genInputMult", layerD_genInputMult->getFloat());
        renderShader.setUniform1f("layerD_genInputOffset", layerD_genInputOffset->getFloat());
        if (layerD_postProcess1Active) {
            renderShader.setUniform1f("layerD_postProcess1YVal", layerD_postProcess1YVal->getFloat());
        };
        if (layerD_postProcess2Active) {
            renderShader.setUniform1f("layerD_postProcess2YVal", layerD_postProcess2YVal->getFloat());
        };
        if (layerD_postProcess3Active) {
            renderShader.setUniform1f("layerD_postProcess3YVal", layerD_postProcess3YVal->getFloat());
        };
    };
}

string TXWaveTerrain::getLayerDValue(){
    string outString =
    STRINGIFY(
              // Init layer
              layerX = layerStartX;
              layerY = layerStartY;
              );
    if (layerDUsed) {
        // convert to polar if needed
        if(layerD_usePolarCoords) {
            outString = outString +
            STRINGIFY(
                      inputX = layerX * SQRTTWO;
                      inputY = layerY * TWOPI;
                      layerX = inputX * cos(inputY);
                      layerY = inputX * sin(inputY);
                      );
        };
        outString = outString +
        STRINGIFY(
                  // rotation
                  if (layerD_rotate != 0.0) {
                      inputX = layerX;
                      inputY = layerY;
                      layerX = (inputX * cos(layerD_rotate)) - (inputY * sin(layerD_rotate));
                      layerY = (inputX * sin(layerD_rotate)) + (inputY * cos(layerD_rotate));
                  };
                  );
        // map inputs
        outString = outString +
        STRINGIFY(
                  layerX = map(layerX, -0.5, 0.5, layerD_inputXMin, layerD_inputXMax);
                  layerY = map(layerY, -0.5, 0.5, layerD_inputYMin, layerD_inputYMax);
                  );
        // apply offsets
        if (layerD_offsetProcess1Active) {
            outString = outString +
            STRINGIFY(
                      x = (layerX * layerD_offsetProcess1MultInputX) + layerD_offsetProcess1AddInputX;
                      processOut =
                      );
            outString = outString + getUnaryOpProcess(layerD_offsetProcess1Type);
            outString = outString +
            STRINGIFY(
                      offsetProcess1X = processOut * layerD_offsetProcess1MultOutputX;
                      );
            outString = outString +
            STRINGIFY(
                      x = (layerY * layerD_offsetProcess1MultInputY) + layerD_offsetProcess1AddInputY;
                      processOut =
                      );
            outString = outString + getUnaryOpProcess(layerD_offsetProcess1Type);
            outString = outString +
            STRINGIFY(
                      offsetProcess1Y = processOut * layerD_offsetProcess1MultOutputY;
                      );
        } else {
            outString = outString +
            STRINGIFY(
                      offsetProcess1X = 0;
                      offsetProcess1Y = 0;
                      );
        };
        if (layerD_offsetProcess2Active) {
            // prepare inputs
            if (layerD_offsetProcs12InSeries) {
                outString = outString +
                STRINGIFY(
                          inputX = layerX + offsetProcess1X;
                          inputY = layerY + offsetProcess1Y;
                          );
            } else {
                outString = outString +
                STRINGIFY(
                          inputX = layerX;
                          inputY = layerY;
                          );
            };
            outString = outString +
            STRINGIFY(
                      x = (inputX * layerD_offsetProcess2MultInputX) + layerD_offsetProcess2AddInputX;
                      processOut =
                      );
            outString = outString + getUnaryOpProcess(layerD_offsetProcess2Type);
            outString = outString +
            STRINGIFY(
                      offsetProcess2X = processOut * layerD_offsetProcess2MultOutputX;
                      );
            outString = outString +
            STRINGIFY(
                      x = (inputY * layerD_offsetProcess2MultInputY) + layerD_offsetProcess2AddInputY;
                      processOut =
                      );
            outString = outString + getUnaryOpProcess(layerD_offsetProcess2Type);
            outString = outString +
            STRINGIFY(
                      offsetProcess2Y = processOut * layerD_offsetProcess2MultOutputY;
                      );
        } else {
            outString = outString +
            STRINGIFY(
                      offsetProcess2X = 0;
                      offsetProcess2Y = 0;
                      );
        };
        // add offsets to layer
        if (!(layerD_offsetProcess2Active && layerD_offsetProcs12InSeries)) {
            outString = outString +
            STRINGIFY(
                      layerX = layerX + offsetProcess1X;
                      layerY = layerY + offsetProcess1Y;
                      );
        };
        outString = outString +
        STRINGIFY(
                  layerX = layerX + offsetProcess2X;
                  layerY = layerY + offsetProcess2Y;
                  );
        // generate terrain
        outString = outString +
        STRINGIFY(
                  x = layerD_genInputXMult * pow(layerX, layerD_genInputXPower);
                  y = layerD_genInputYMult * pow(layerY, layerD_genInputYPower);
                  processOut =
                  );
        outString = outString + getBinaryOpProcess(layerD_genInputXYProcess);
        outString = outString +
        STRINGIFY(
                  x = (processOut * layerD_genInputMult) + layerD_genInputOffset;
                  processOut =
                  );
        outString = outString + getUnaryOpProcess(layerD_generatorProcessType);
        if (layerD_postProcess1Active) {
            outString = outString +
            STRINGIFY(
                      x = processOut;
                      y = layerD_postProcess1YVal;
                      processOut =
                      );
        };
        outString = outString + getUnaryOrBinaryOpProcess(layerD_postProcess1Type);
        if (layerD_postProcess2Active) {
            outString = outString +
            STRINGIFY(
                      x = processOut;
                      y = layerD_postProcess2YVal;
                      processOut =
                      );
        };
        outString = outString + getUnaryOrBinaryOpProcess(layerD_postProcess2Type);
        if (layerD_postProcess3Active) {
            outString = outString +
            STRINGIFY(
                      x = processOut;
                      y = layerD_postProcess3YVal;
                      processOut =
                      );
        };
        outString = outString + getUnaryOrBinaryOpProcess(layerD_postProcess3Type);
        outString = outString + string(" \nlayerDOut = processOut; \n");
    } else {
        outString = string(" \nlayerDOut = 0; \n");
    };
    
    return outString;
}

////////


string TXWaveTerrain::getGLSLFunctions(){
    string outString =
    STRINGIFY(
              float lookup(int curveIndex, float x, float morph, float phase){
                  float outVal, lookupOffset1, lookupOffset2;
                  vec4 colorA, colorB;
                  
                  //lookupOffset1 = fract(x + phase) * 255;
                  lookupOffset1 = 0.5 + (fract(x + phase) * 254);
                  lookupOffset2 = lookupOffset1 + 256;
                  colorA = texture2DRect(curveSampler, vec2(lookupOffset1, 0.0));
                  colorB = texture2DRect(curveSampler, vec2(lookupOffset2, 0.0));
                  if (curveIndex == 0) {
                      outVal = mix(colorA.r, colorB.r, morph);
                  } else if (curveIndex == 1) {
                      outVal = mix(colorA.g, colorB.g, morph);
                  } else if (curveIndex == 2) {
                      outVal = mix(colorA.b, colorB.b, morph);
                  } else if (curveIndex == 3) {
                      outVal = mix(colorA.a, colorB.a, morph);
                  };
                  return outVal;
              }
              
              float lookupColorMix(float x, float morph, float phase){
                  float outVal, lookupOffset1, lookupOffset2;
                  vec4 colorA, colorB;
                  
                  //lookupOffset1 = fract(x + phase) * 255;
                  lookupOffset1 = 0.5 + (fract(x + phase) * 254);
                  lookupOffset2 = lookupOffset1 + 256;
                  colorA = texture2DRect(colorMixSampler, vec2(lookupOffset1, 0.0));
                  colorB = texture2DRect(colorMixSampler, vec2(lookupOffset2, 0.0));
                  outVal = mix(colorA.r, colorB.r, morph);
                  return outVal;
              }
              
              vec4 lookupHSL(float x){
                  float lookupOffset1, lookupOffset2, hVal, sVal, bVal, aVal;
                  vec4 colorA, colorB;
                  
                  lookupOffset1 = x * 255;
                  lookupOffset2 = lookupOffset1 + 256;
                  colorA = texture2DRect(curveHSLSampler, vec2(lookupOffset1, 0.0));
                  colorB = texture2DRect(curveHSLSampler, vec2(lookupOffset2, 0.0));
                  hVal = mix(colorA.r, colorB.r, colorHueCurveMorph);
                  sVal = mix(colorA.g, colorB.g, colorSaturationCurveMorph);
                  bVal = mix(colorA.b, colorB.b, colorBrightnessCurveMorph);
                  aVal = mix(colorA.a, colorB.a, colorAlphaCurveMorph);
                  return vec4(fract(hVal + colorHueCurveRotate), sVal, bVal, aVal);
              }
              
              /*
               ** Photoshop & misc math
               ** Romain Dura | Romz
               ** Blog: http://blog.mouaif.org
               ** Post: http://blog.mouaif.org/?p=94
               */
              
              // ** Hue, saturation, luminance
              
              vec3 RGBToHSL(vec3 color)
              {
                  vec3 hsl; // init to 0 to avoid warnings ? (and reverse if + remove first part)
                  float fmin, fmax, delta, deltaR, deltaG, deltaB;
                  
                  fmin = min(min(color.r, color.g), color.b);    //Min. value of RGB
                  fmax = max(max(color.r, color.g), color.b);    //Max. value of RGB
                  delta = fmax - fmin;             //Delta RGB value
                  
                  hsl.z = (fmax + fmin) / 2.0; // Luminance
                  
                  if (delta == 0.0)		//This is a gray, no chroma...
                  {
                      hsl.x = 0.0;	// Hue
                      hsl.y = 0.0;	// Saturation
                  }
                  else                                    //Chromatic data...
                  {
                      if (hsl.z < 0.5)
                          hsl.y = delta / (fmax + fmin); // Saturation
                      else
                          hsl.y = delta / (2.0 - fmax - fmin); // Saturation
                      
                      deltaR = (((fmax - color.r) / 6.0) + (delta / 2.0)) / delta;
                      deltaG = (((fmax - color.g) / 6.0) + (delta / 2.0)) / delta;
                      deltaB = (((fmax - color.b) / 6.0) + (delta / 2.0)) / delta;
                      
                      if (color.r == fmax )
                          hsl.x = deltaB - deltaG; // Hue
                      else if (color.g == fmax)
                          hsl.x = (1.0 / 3.0) + deltaR - deltaB; // Hue
                      else if (color.b == fmax)
                          hsl.x = (2.0 / 3.0) + deltaG - deltaR; // Hue
                      
                      if (hsl.x < 0.0)
                          hsl.x += 1.0; // Hue
                      else if (hsl.x > 1.0)
                          hsl.x -= 1.0; // Hue
                  }
                  
                  return hsl;
              }
              
              float HueToRGB(float f1, float f2, float hue)
              {
                  float res;
                  if (hue < 0.0)
                      hue += 1.0;
                  else if (hue > 1.0)
                      hue -= 1.0;
                  if ((6.0 * hue) < 1.0)
                      res = f1 + (f2 - f1) * 6.0 * hue;
                  else if ((2.0 * hue) < 1.0)
                      res = f2;
                  else if ((3.0 * hue) < 2.0)
                      res = f1 + (f2 - f1) * ((2.0 / 3.0) - hue) * 6.0;
                  else
                      res = f1;
                  return res;
              }
              
              vec3 HSLToRGB(vec3 hsl)
              {
                  vec3 rgb;
                  
                  if (hsl.y == 0.0)
                      rgb = vec3(hsl.z); // Luminance
                  else
                  {
                      float f1, f2;
                      
                      if (hsl.z < 0.5)
                          f2 = hsl.z * (1.0 + hsl.y);
                      else
                          f2 = (hsl.z + hsl.y) - (hsl.y * hsl.z);
                      
                      f1 = 2.0 * hsl.z - f2;
                      
                      rgb.r = HueToRGB(f1, f2, hsl.x + (1.0/3.0));
                      rgb.g = HueToRGB(f1, f2, hsl.x);
                      rgb.b = HueToRGB(f1, f2, hsl.x - (1.0/3.0));
                  }
                  
                  return rgb;
              }
              
              //
              // Follow 2 functions taken from http://lolengine.net/blog/2013/07/27/rgb-to-hsv-in-glsl.
              //
              // All components are in the range [0…1], including hue.
              vec3 RGBToHSV(vec3 c)
              {
                  vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
                  vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
                  vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));
                  
                  float d = q.x - min(q.w, q.y);
                  float e = 1.0e-10;
                  return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
              }
              // All components are in the range [0…1], including hue.
              vec3 HSVToRGB(vec3 c)
              {
                  vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
                  vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
                  return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
              }
             
              // -------- glsl functions: --------------///////
              
              float map(float val,float inMin,float inMax,float outMin,float outMax){
                  if (inMin == inMax) {
                      return outMin;
                  };
                  return outMin + (((outMax - outMin) / (inMax - inMin)) * (val - inMin));
              }
              
              float fmod(float val, float modulo){
                  int i;
                  i = int(val/modulo);
                  return val - (i*modulo);
              }
              
              float mod(float inVal, float hi)
              {
                  // avoid the divide if possible
                  const float lo = 0.0;
                  if (inVal >= hi) {
                      inVal -= hi;
                      if (inVal < hi) return inVal;
                  } else if (inVal < lo) {
                      inVal += hi;
                      if (inVal >= lo) return inVal;
                  } else return inVal;
                  
                  if (hi == lo) return lo;
                  return inVal - hi*floor(inVal/hi);
              }
              
              float wrap(float inVal, float lo, float hi)
              {
                  float range;
                  // avoid the divide if possible
                  if (inVal >= hi) {
                      range = hi - lo;
                      inVal -= range;
                      if (inVal < hi) return inVal;
                  } else if (inVal < lo) {
                      range = hi - lo;
                      inVal += range;
                      if (inVal >= lo) return inVal;
                  } else return inVal;
                  
                  if (hi == lo) return lo;
                  return inVal - range * floor((inVal - lo)/range);
              }
              
              float fold(float inVal, float lo, float hi)
              {
                  float x, c, range, range2;
                  x = inVal - lo;
                  
                  // avoid the divide if possible
                  if (inVal >= hi) {
                      inVal = hi + hi - inVal;
                      if (inVal >= lo) return inVal;
                  } else if (inVal < lo) {
                      inVal = lo + lo - inVal;
                      if (inVal < hi) return inVal;
                  } else return inVal;
                  
                  if (hi == lo) return lo;
                  // ok do the divide
                  range = hi - lo;
                  range2 = range + range;
                  c = x - range2 * floor(x / range2);
                  if (c>=range) c = range2 - c;
                  return c + lo;
              }
              
              float round(float x, float quant)
              {
                  return quant==0.0 ? x : floor(x/quant + 0.5) * quant;
              }
              
              float roundUp(float x, float quant)
              {
                  return quant==0.0 ? x : ceil(x/quant) * quant;
              }
              float trunc(float x, float quant)
              {
                  return quant==0.0 ? x : floor(x/quant) * quant;
              }
              
              float thresh(float a, float b)
              {
                  return a < b ? 0.0 : a;
              }
              
              // perlin noise functions
              
              vec3 mod289(vec3 x) {
                  return x - floor(x * (1.0 / 289.0)) * 289.0;
              }
              
              vec4 mod289(vec4 x) {
                  return x - floor(x * (1.0 / 289.0)) * 289.0;
              }
              
              vec4 permute(vec4 x) {
                  return mod289(((x*34.0)+1.0)*x);
              }
              
              vec4 taylorInvSqrt(vec4 r)
              {
                  return 1.79284291400159 - 0.85373472095314 * r;
              }
              
              float snoise(vec3 v)
              {
                  const vec2  C = vec2(1.0/6.0, 1.0/3.0) ;
                  const vec4  D = vec4(0.0, 0.5, 1.0, 2.0);
                  
                  // First corner
                  vec3 i  = floor(v + dot(v, C.yyy) );
                  vec3 x0 =   v - i + dot(i, C.xxx) ;
                  
                  // Other corners
                  vec3 g = step(x0.yzx, x0.xyz);
                  vec3 l = 1.0 - g;
                  vec3 i1 = min( g.xyz, l.zxy );
                  vec3 i2 = max( g.xyz, l.zxy );
                  
                  //   x0 = x0 - 0.0 + 0.0 * C.xxx;
                  //   x1 = x0 - i1  + 1.0 * C.xxx;
                  //   x2 = x0 - i2  + 2.0 * C.xxx;
                  //   x3 = x0 - 1.0 + 3.0 * C.xxx;
                  vec3 x1 = x0 - i1 + C.xxx;
                  vec3 x2 = x0 - i2 + C.yyy; // 2.0*C.x = 1/3 = C.y
                  vec3 x3 = x0 - D.yyy;      // -1.0+3.0*C.x = -0.5 = -D.y
                  
                  // Permutations
                  i = mod289(i);
                  vec4 p = permute( permute( permute(
                                                     i.z + vec4(0.0, i1.z, i2.z, 1.0 ))
                                            + i.y + vec4(0.0, i1.y, i2.y, 1.0 ))
                                   + i.x + vec4(0.0, i1.x, i2.x, 1.0 ));
                  
                  // Gradients: 7x7 points over a square, mapped onto an octahedron.
                  // The ring size 17*17 = 289 is close to a multiple of 49 (49*6 = 294)
                  float n_ = 0.142857142857; // 1.0/7.0
                  vec3  ns = n_ * D.wyz - D.xzx;
                  
                  vec4 j = p - 49.0 * floor(p * ns.z * ns.z);  //  mod(p,7*7)
                  
                  vec4 x_ = floor(j * ns.z);
                  vec4 y_ = floor(j - 7.0 * x_ );    // mod(j,N)
                  
                  vec4 x = x_ *ns.x + ns.yyyy;
                  vec4 y = y_ *ns.x + ns.yyyy;
                  vec4 h = 1.0 - abs(x) - abs(y);
                  
                  vec4 b0 = vec4( x.xy, y.xy );
                  vec4 b1 = vec4( x.zw, y.zw );
                  
                  //vec4 s0 = vec4(lessThan(b0,0.0))*2.0 - 1.0;
                  //vec4 s1 = vec4(lessThan(b1,0.0))*2.0 - 1.0;
                  vec4 s0 = floor(b0)*2.0 + 1.0;
                  vec4 s1 = floor(b1)*2.0 + 1.0;
                  vec4 sh = -step(h, vec4(0.0));
                  
                  vec4 a0 = b0.xzyw + s0.xzyw*sh.xxyy ;
                  vec4 a1 = b1.xzyw + s1.xzyw*sh.zzww ;
                  
                  vec3 p0 = vec3(a0.xy,h.x);
                  vec3 p1 = vec3(a0.zw,h.y);
                  vec3 p2 = vec3(a1.xy,h.z);
                  vec3 p3 = vec3(a1.zw,h.w);
                  
                  //Normalise gradients
                  vec4 norm = taylorInvSqrt(vec4(dot(p0,p0), dot(p1,p1), dot(p2, p2), dot(p3,p3)));
                  p0 *= norm.x;
                  p1 *= norm.y;
                  p2 *= norm.z;
                  p3 *= norm.w;
                  
                  // Mix final noise value
                  vec4 m = max(0.6 - vec4(dot(x0,x0), dot(x1,x1), dot(x2,x2), dot(x3,x3)), 0.0);
                  m = m * m;
                  return 42.0 * dot( m*m, vec4( dot(p0,x0), dot(p1,x1),
                                               dot(p2,x2), dot(p3,x3) ) );
              }
              
              // amp mult 0.5 (unnormalised)   [0.5, 0.25, 0.125, 0.0625];
              // amp mult 0.5     [ 0.533, 0.267, 0.133, 0.067 ]
              // amp mult 0.6666   [ 0.415, 0.277, 0.185, 0.123 ];
              // amp mult 0.75   [ 0.366, 0.274, 0.206, 0.154 ];
              // amp mult 0.85   [ 0.314, 0.267, 0.227, 0.193 ];
              // amp mult 1   [ 0.25, 0.25, 0.25, 0.25 ];
              // amp mult 1.25 = [ 0.173, 0.217, 0.271, 0.339 ];
              // amp mult 1.333 = [ 0.154, 0.206, 0.274, 0.366 ];
              // amp mult 1.5 = [ 0.123, 0.185, 0.277, 0.415 ];
              // amp mult 2 = [ 0.067, 0.133, 0.267, 0.533 ];
              
              /* // OLD VERSION
              float pnoise(vec3 v) // amp mult 0.5, normalised
              {
                  float result = (snoise(v) * 0.533)
                  + (snoise(vec3(v.x * 2.0, v.y * 2.0, v.z * 2.0)) * 0.267)
                  + (snoise(vec3(v.x * 4.0, v.y * 4.0, v.z * 4.0)) * 0.133)
                  + (snoise(vec3(v.x * 8.0, v.y * 8.0, v.z * 8.0)) * 0.067);
                  return result;
              }
               */
              float pnoise(vec3 v) // using octave inputs
              {
                  float result = (snoise(v) * perlinLayer1Mix)
                  + (snoise(vec3(v.x * 2.0, v.y * 2.0, v.z * 2.0)) * perlinLayer2Mix)
                  + (snoise(vec3(v.x * 4.0, v.y * 4.0, v.z * 4.0)) * perlinLayer3Mix)
                  + (snoise(vec3(v.x * 8.0, v.y * 8.0, v.z * 8.0)) * perlinLayer4Mix);
                  return result;
              }
              float pnoise1(float x)
              {
                  float result =  pnoise(vec3(x, 0.0, 0.0));
                  result =  map(result, 0, 1, -1, 1);  // map to range +-1
                  return result;
              }
              
              float pnoise2(float x, float y)
              {
                  float result =  pnoise(vec3(x, y, 0.0));
                  result =  map(result, 0, 1, -1, 1);  // map to range +-1
                  return result;
              }
              
              );

    return outString;
}

string TXWaveTerrain::getUnaryOpProcess(int index){
    string unaryOpProcesses[] = {
        "x;",
        "x * -1;",
        "abs(x);",
        "sign(x);",
        "(1/x);",
        "sin(TWOPI * x);",
        "cos(TWOPI * x);",
        "tan(TWOPI * x);",
        "asin(wrap(x, -1, 1)) * TWOOVERPI;",
        "acos(wrap(x, -1, 1)) * TWOOVERPI;",
        "atan(x) * TWOOVERPI;",
        "pnoise1(x);",
        "abs(pnoise1(x));",
        "fract(x);",
        "ceil(x);",
        "floor(x);",
        "x * x;",
        "x * x * x;",
        "sqrt(abs(x));",
        "inversesqrt(abs(x));",
        "exp(abs(x));",
        "exp2(x);",
        "log(x);",
        "log2(x);",
        "step(0.5, x);",
        "step(0, x);",
        "clamp(x, 0, 1);",
        "clamp(x, 0, 1);",
        "fold(x, 0, 1);",
        "fold(x, -1, 1);",
        "wrap(x, 0, 1);",
        "wrap(x, -1, 1);",
        "lookup(0, clamp(x, 0, 1), lookupCurve1Morph, lookupCurve1Phase);",
        "lookup(0, clamp(x, -1, 1) * 0.5 + 0.5, lookupCurve1Morph, lookupCurve1Phase);",
        "lookup(0, fold(x, 0, 1), lookupCurve1Morph, lookupCurve1Phase);",
        "lookup(0, fold(x, -1, 1) * 0.5 + 0.5, lookupCurve1Morph, lookupCurve1Phase);",
        "lookup(0, wrap(x, 0, 1), lookupCurve1Morph, lookupCurve1Phase);",
        "lookup(0, wrap(x, -1, 1) * 0.5 + 0.5, lookupCurve1Morph, lookupCurve1Phase);",
        "lookup(1, clamp(x, 0, 1), lookupCurve2Morph, lookupCurve2Phase);",
        "lookup(1, clamp(x, -1, 1) * 0.5 + 0.5, lookupCurve2Morph, lookupCurve2Phase);",
        "lookup(1, fold(x, 0, 1), lookupCurve2Morph, lookupCurve2Phase);",
        "lookup(1, fold(x, -1, 1) * 0.5 + 0.5, lookupCurve2Morph, lookupCurve2Phase);",
        "lookup(1, wrap(x, 0, 1), lookupCurve2Morph, lookupCurve2Phase);",
        "lookup(1, wrap(x, -1, 1) * 0.5 + 0.5, lookupCurve2Morph, lookupCurve2Phase);",
        "lookup(2, clamp(x, 0, 1), lookupCurve3Morph, lookupCurve3Phase);",
        "lookup(2, clamp(x, -1, 1) * 0.5 + 0.5, lookupCurve3Morph, lookupCurve3Phase);",
        "lookup(2, fold(x, 0, 1), lookupCurve3Morph, lookupCurve3Phase);",
        "lookup(2, fold(x, -1, 1) * 0.5 + 0.5, lookupCurve3Morph, lookupCurve3Phase);",
        "lookup(2, wrap(x, 0, 1), lookupCurve3Morph, lookupCurve3Phase);",
        "lookup(2, wrap(x, -1, 1) * 0.5 + 0.5, lookupCurve3Morph, lookupCurve3Phase);",
        "lookup(3, clamp(x, 0, 1), lookupCurve4Morph, lookupCurve4Phase);",
        "lookup(3, clamp(x, -1, 1) * 0.5 + 0.5, lookupCurve4Morph, lookupCurve4Phase);",
        "lookup(3, fold(x, 0, 1), lookupCurve4Morph, lookupCurve4Phase);",
        "lookup(3, fold(x, -1, 1) * 0.5 + 0.5, lookupCurve4Morph, lookupCurve4Phase);",
        "lookup(3, wrap(x, 0, 1), lookupCurve4Morph, lookupCurve4Phase);",
        "lookup(3, wrap(x, -1, 1) * 0.5 + 0.5, lookupCurve4Morph, lookupCurve4Phase);",
    };
    int holdInd = ofClamp(index, 0, totalUnaryOpProcesses - 1);  // clamp to valid range
    return unaryOpProcesses[holdInd];
}


string TXWaveTerrain::getBinaryOpProcess(int index){
    string binaryOpProcesses[] = {
        "(x + y);",
        "(x - y);",
        "(y - x);",
        "(x * y);",
        "(x / y);",
        "(y / x);",
        "fmod(x, y);",
        "fmod(y, x);",
        "min(x, y);",
        "max(x, y);",
        "pow(abs(x), y);",
        "pow(abs(y), x);",
        "int(x == y);",
        "int(x != y);",
        "int(x > y);",
        "int(x < y);",
        "int(x >= y);",
        "int(x <= y);",
        "step(x, y);",
        "step(y, x);",
        "smoothstep(-x, x, y);",
        "smoothstep(-y, y, x);",
        "length(vec2(x, y));",
        "pnoise2(x, y);",
        "pnoise2(y, x);",
        "atan(x, y);",
        "atan(y, x);",
        "clamp(x, 0, y);",
        "clamp(y, 0, x);",
        "clamp(x, -y, y);",
        "clamp(y, -x, x);",
        "fold(x, 0, y);",
        "fold(y, 0, x);",
        "fold(x, -y, y);",
        "fold(y, -x, x);",
        "wrap(x, 0, y);",
        "wrap(y, 0, x);",
        "wrap(x, -y, y);",
        "wrap(y, -x, x);",
        "round(x, y);",
        "round(y, x);",
        "roundUp(x, y);",
        "roundUp(y, x);",
        "trunc(x, y);",
        "trunc(y, x);",
        "thresh(x, y);",
        "thresh(y, x);",
        "x;",
        "y;"
    };
    int holdInd = ofClamp(index, 0, totalBinaryOpProcesses - 1);  // clamp to valid range
    return binaryOpProcesses[holdInd];
}

string TXWaveTerrain::getUnaryOrBinaryOpProcess(int index){
    int holdInd = ofClamp(index, 0, totalUnaryOpProcesses + totalBinaryOpProcesses - 1);  // clamp to valid range
    string outString;
    if (holdInd < totalUnaryOpProcesses) {
        outString = getUnaryOpProcess(holdInd);
    } else {
        outString = getBinaryOpProcess(holdInd - totalUnaryOpProcesses);
    };
    return outString;
}

void  TXWaveTerrain::renderSizeChanged(int & intArg) {
    if ((getRenderWidth() != outImage.getWidth()) || (getRenderHeight() != outImage.getHeight())) {
        // if size changed, reallocate
        allocateTexture();
    };
}

int TXWaveTerrain::getRenderWidth() {
    switch (renderWidthHeightRule) {
        case MAXWIDTHHEIGHTRULE_SCREENWIDTHHEIGHT:
            return getWindowWidth();
            break;
        case MAXWIDTHHEIGHTRULE_MAXSCREENWIDTHHEIGHT:
            return max(getWindowWidth(), getWindowHeight());
            break;
        case MAXWIDTHHEIGHTRULE_MINSCREENWIDTHHEIGHT:
            return min(getWindowWidth(), getWindowHeight());
            break;
        case MAXWIDTHHEIGHTRULE_SQUARESCREENWIDTH:
            return getWindowWidth();
            break;
        case MAXWIDTHHEIGHTRULE_SQUARESCREENHEIGHT:
            return getWindowHeight();
            break;
        case MAXWIDTHHEIGHTRULE_CUSTOMSIZE:
            return renderCustomWidth;
            break;
        case MAXWIDTHHEIGHTRULE_480_360:
            return 480;
            break;
        case MAXWIDTHHEIGHTRULE_858_480:
            return 858;
            break;
        case MAXWIDTHHEIGHTRULE_1280_720:
            return 1280;
            break;
        case MAXWIDTHHEIGHTRULE_1920_1080:
            return 1920;
            break;
        case MAXWIDTHHEIGHTRULE_2560_1440:
            return 2560;
            break;
        case MAXWIDTHHEIGHTRULE_3840_2160:
            return 3840;
            break;
        default:
            return getWindowWidth();
            break;
    }
}

int TXWaveTerrain::getRenderHeight() {
    switch (renderWidthHeightRule) {
        case MAXWIDTHHEIGHTRULE_SCREENWIDTHHEIGHT:
            return getWindowHeight();
            break;
        case MAXWIDTHHEIGHTRULE_MAXSCREENWIDTHHEIGHT:
            return max(getWindowWidth(), getWindowHeight());
            break;
        case MAXWIDTHHEIGHTRULE_MINSCREENWIDTHHEIGHT:
            return min(getWindowWidth(), getWindowHeight());
            break;
        case MAXWIDTHHEIGHTRULE_SQUARESCREENWIDTH:
            return getWindowWidth();
            break;
        case MAXWIDTHHEIGHTRULE_SQUARESCREENHEIGHT:
            return getWindowHeight();
            break;
        case MAXWIDTHHEIGHTRULE_CUSTOMSIZE:
            return renderCustomHeight;
            break;
        case MAXWIDTHHEIGHTRULE_480_360:
            return 360;
            break;
        case MAXWIDTHHEIGHTRULE_858_480:
            return 480;
            break;
        case MAXWIDTHHEIGHTRULE_1280_720:
            return 720;
            break;
        case MAXWIDTHHEIGHTRULE_1920_1080:
            return 1080;
            break;
        case MAXWIDTHHEIGHTRULE_2560_1440:
            return 1440;
            break;
        case MAXWIDTHHEIGHTRULE_3840_2160:
            return 2160;
            break;
        default:
            return getWindowHeight();
            break;
    }
}

