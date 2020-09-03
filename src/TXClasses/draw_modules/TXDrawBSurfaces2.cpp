/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXSystem.h"
#include "TXDrawBSurfaces2.h"
#include "TXFunctions.h"

TXDrawBSurfaces2::TXDrawBSurfaces2() {
    setup();
}

// destructor
TXDrawBSurfaces2::~TXDrawBSurfaces2() {
    // remove listeners to relevent parameters:
    ofRemoveListener(surfaceResolution->parameters.parameterChangedE(),this,&TXDrawBSurfaces2::surfaceResolutionChanged);
    ofRemoveListener(useLooping->parameters.parameterChangedE(),this,&TXDrawBSurfaces2::useLoopingChanged);
}

void TXDrawBSurfaces2::setup(){
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
    
    parameters.add(useImageAsTexture.set("useImageAsTexture", true));
    parameters.add(useExternalSourceImage.set("useExternalSourceImage", false));
    
    holdModParamIntArgs.name = "numSurfaces";
    holdModParamIntArgs.fixedValue = 4;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = maxSurfaces;
    holdModParamIntArgs.softMin = 1;
    holdModParamIntArgs.softMax = maxSurfaces;
	numSurfaces = createModParameter(holdModParamIntArgs);
    parameters.add(numSurfaces->parameters);
    
    holdModParamIntArgs.name = "surfaceResolution";
    holdModParamIntArgs.fixedValue = 32;
    holdModParamIntArgs.hardMin = 2;
    holdModParamIntArgs.hardMax = 1024;
    holdModParamIntArgs.softMin = 2;
    holdModParamIntArgs.softMax = 128;
	surfaceResolution = createModParameter(holdModParamIntArgs);
    parameters.add(surfaceResolution->parameters);
    
    holdModParamBoolArgs.name = "drawWireframe";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	drawWireframe = createModParameter(holdModParamBoolArgs);
    parameters.add(drawWireframe->parameters);
    
    holdModParamBoolArgs.name = "useLooping";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	useLooping = createModParameter(holdModParamBoolArgs);
    parameters.add(useLooping->parameters);
    
    holdModParamIntArgs.name = "pointsMorphType";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXPOINTSMORPHTYPE_TOTAL-1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXPOINTSMORPHTYPE_TOTAL-1;
	pointsMorphType = createModParameter(holdModParamIntArgs);
    parameters.add(pointsMorphType->parameters);
    
    holdModParamBoolArgs.name = "usePointsToOffsetMorph";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	usePointsToOffsetMorph = createModParameter(holdModParamBoolArgs);
    parameters.add(usePointsToOffsetMorph->parameters);
    
    holdModParamFloatArgs.name = "pointsMorphX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	pointsMorphX = createModParameter(holdModParamFloatArgs);
    parameters.add(pointsMorphX->parameters);
    
    holdModParamFloatArgs.name = "pointsMorphXEnd";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	pointsMorphXEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(pointsMorphXEnd->parameters);
    
    parameters.add(pointsMorphXEndIgnore.set("pointsMorphXEndIgnore", true));
    
    holdModParamFloatArgs.name = "pointsMorphY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	pointsMorphY = createModParameter(holdModParamFloatArgs);
    parameters.add(pointsMorphY->parameters);
    
    holdModParamFloatArgs.name = "pointsMorphYEnd";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	pointsMorphYEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(pointsMorphYEnd->parameters);
    
    parameters.add(pointsMorphYEndIgnore.set("pointsMorphYEndIgnore", true));
    
    holdModParamIntArgs.name = "pointsMorphPresetA";
    holdModParamIntArgs.fixedValue = 1;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalNumPointsPresets-1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalNumPointsPresets-1;
	pointsMorphPresetA = createModParameter(holdModParamIntArgs);
    parameters.add(pointsMorphPresetA->parameters);
    
    holdModParamIntArgs.name = "pointsMorphPresetB";
    holdModParamIntArgs.fixedValue = 2;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalNumPointsPresets-1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalNumPointsPresets-1;
	pointsMorphPresetB = createModParameter(holdModParamIntArgs);
    parameters.add(pointsMorphPresetB->parameters);
    
    holdModParamIntArgs.name = "pointsMorphPresetC";
    holdModParamIntArgs.fixedValue = 3;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalNumPointsPresets-1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalNumPointsPresets-1;
	pointsMorphPresetC = createModParameter(holdModParamIntArgs);
    parameters.add(pointsMorphPresetC->parameters);
    
    holdModParamIntArgs.name = "pointsMorphPresetD";
    holdModParamIntArgs.fixedValue = 4;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalNumPointsPresets-1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalNumPointsPresets-1;
	pointsMorphPresetD = createModParameter(holdModParamIntArgs);
    parameters.add(pointsMorphPresetD->parameters);
    
    holdModParamIntArgs.name = "pointsMorphPresetE";
    holdModParamIntArgs.fixedValue = 5;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalNumPointsPresets-1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalNumPointsPresets-1;
	pointsMorphPresetE = createModParameter(holdModParamIntArgs);
    parameters.add(pointsMorphPresetE->parameters);
    
    parameters.add(initPresetsAsFlatPlane.set("initPresetsAsFlatPlane", true));
    parameters.add(offsetDistortPointX.set("offsetDistortPointX", 0.0, -3.0, 3.0));
    parameters.add(offsetDistortPointY.set("offsetDistortPointY", 0.0, -3.0, 3.0));
    parameters.add(offsetDistortPointZ.set("offsetDistortPointZ", 0.0, -3.0, 3.0));
    parameters.add(offsetRandomSeed.set("offsetRandomSeed", 0, 0, 1000000));
    
    // setup point offsets and merge parameters
    arrPointOffsets[0].setup(this, "offset1");
    arrPointOffsets[1].setup(this, "offset2");
    arrPointOffsets[2].setup(this, "offset3");
    arrPointOffsets[3].setup(this, "offset4");
    arrPointOffsets[4].setup(this, "offset5");
    arrPointOffsets[5].setup(this, "offset6");
    arrPointOffsets[6].setup(this, "offset7");
    arrPointOffsets[7].setup(this, "offset8");
    arrPointOffsets[8].setup(this, "offset9");
    arrPointOffsets[9].setup(this, "offset10");
    arrPointOffsets[10].setup(this, "offset11");
    arrPointOffsets[11].setup(this, "offset12");
    arrPointOffsets[12].setup(this, "offset13");
    arrPointOffsets[13].setup(this, "offset14");
    arrPointOffsets[14].setup(this, "offset15");
    arrPointOffsets[15].setup(this, "offset16");
    arrPointOffsets[16].setup(this, "offset17");
    arrPointOffsets[17].setup(this, "offset18");
    arrPointOffsets[18].setup(this, "offset19");
    arrPointOffsets[19].setup(this, "offset20");
    
    mergeParameters(arrPointOffsets[0].parameters);
    mergeParameters(arrPointOffsets[1].parameters);
    mergeParameters(arrPointOffsets[2].parameters);
    mergeParameters(arrPointOffsets[3].parameters);
    mergeParameters(arrPointOffsets[4].parameters);
    mergeParameters(arrPointOffsets[5].parameters);
    mergeParameters(arrPointOffsets[6].parameters);
    mergeParameters(arrPointOffsets[7].parameters);
    mergeParameters(arrPointOffsets[8].parameters);
    mergeParameters(arrPointOffsets[9].parameters);
    mergeParameters(arrPointOffsets[10].parameters);
    mergeParameters(arrPointOffsets[11].parameters);
    mergeParameters(arrPointOffsets[12].parameters);
    mergeParameters(arrPointOffsets[13].parameters);
    mergeParameters(arrPointOffsets[14].parameters);
    mergeParameters(arrPointOffsets[15].parameters);
    mergeParameters(arrPointOffsets[16].parameters);
    mergeParameters(arrPointOffsets[17].parameters);
    mergeParameters(arrPointOffsets[18].parameters);
    mergeParameters(arrPointOffsets[19].parameters);
    
    pointsSpreadCurve.setValueArrayToRamp(0, 1);
    pointsSpreadCurve.setName("pointsSpreadCurve");
    parameters.add(pointsSpreadCurve.parameters);
    
    pointsSpreadCurve2.setValueArrayToRamp(0, 1);
    pointsSpreadCurve2.setName("pointsSpreadCurve2");
    parameters.add(pointsSpreadCurve2.parameters);
    
    holdModParamFloatArgs.name = "pointsSpreadCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	pointsSpreadCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(pointsSpreadCurveMorph->parameters);
    
	// material:
    holdModParamFloatArgs.name = "materialShininess";
    holdModParamFloatArgs.fixedValue = 25.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 128.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 128.0;
	materialShininess = createModParameter(holdModParamFloatArgs);
    parameters.add(materialShininess->parameters);
    
    holdModParamFloatArgs.name = "materialShininessEnd";
    holdModParamFloatArgs.fixedValue = 25.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 128.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 128.0;
	materialShininessEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(materialShininessEnd->parameters);
    
    parameters.add(materialShininessEndIgnore.set("materialShininessEndIgnore", true));
    
    holdModParamFloatArgs.name = "materialDiffuseColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialDiffuseColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(materialDiffuseColorHue->parameters);
    
    holdModParamFloatArgs.name = "materialDiffuseColorHueEnd";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialDiffuseColorHueEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(materialDiffuseColorHueEnd->parameters);
    
    parameters.add(materialDiffuseColorHueEndIgnore.set("materialDiffuseColorHueEndIgnore", true));
    
    holdModParamFloatArgs.name = "materialDiffuseColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialDiffuseColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(materialDiffuseColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "materialDiffuseColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialDiffuseColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(materialDiffuseColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "materialDiffuseColorSaturationEnd";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialDiffuseColorSaturationEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(materialDiffuseColorSaturationEnd->parameters);
    
    parameters.add(materialDiffuseColorSaturationEndIgnore.set("materialDiffuseColorSaturationEndIgnore", true));
    
    holdModParamFloatArgs.name = "materialDiffuseColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialDiffuseColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(materialDiffuseColorBrightness->parameters);
    
    holdModParamFloatArgs.name = "materialDiffuseColorBrightnessEnd";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialDiffuseColorBrightnessEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(materialDiffuseColorBrightnessEnd->parameters);
    
    parameters.add(materialDiffuseColorBrightnessEndIgnore.set("materialDiffuseColorBrightnessEndIgnore", true));
    
    holdModParamBoolArgs.name = "materialDiffuseColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	materialDiffuseColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(materialDiffuseColorHSBAsRGB->parameters);
    
    parameters.add(useDiffuseColorForAmbient.set("useDiffuseColorForAmbient", false));
    
    holdModParamFloatArgs.name = "materialAmbientColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialAmbientColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(materialAmbientColorHue->parameters);
    
    holdModParamFloatArgs.name = "materialAmbientColorHueEnd";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialAmbientColorHueEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(materialAmbientColorHueEnd->parameters);
    
    parameters.add(materialAmbientColorHueEndIgnore.set("materialAmbientColorHueEndIgnore", true));
    
    holdModParamFloatArgs.name = "materialAmbientColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialAmbientColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(materialAmbientColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "materialAmbientColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialAmbientColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(materialAmbientColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "materialAmbientColorSaturationEnd";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialAmbientColorSaturationEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(materialAmbientColorSaturationEnd->parameters);
    
    parameters.add(materialAmbientColorSaturationEndIgnore.set("materialAmbientColorSaturationEndIgnore", true));
    
    holdModParamFloatArgs.name = "materialAmbientColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialAmbientColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(materialAmbientColorBrightness->parameters);
    
    holdModParamFloatArgs.name = "materialAmbientColorBrightnessEnd";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialAmbientColorBrightnessEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(materialAmbientColorBrightnessEnd->parameters);
    
    parameters.add(materialAmbientColorBrightnessEndIgnore.set("materialAmbientColorBrightnessEndIgnore", true));
    
    holdModParamBoolArgs.name = "materialAmbientColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	materialAmbientColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(materialAmbientColorHSBAsRGB->parameters);
    
    parameters.add(useDiffuseColorForSpecular.set("useDiffuseColorForSpecular", false));
    
    holdModParamFloatArgs.name = "materialSpecularColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialSpecularColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(materialSpecularColorHue->parameters);
    
    holdModParamFloatArgs.name = "materialSpecularColorHueEnd";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialSpecularColorHueEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(materialSpecularColorHueEnd->parameters);
    
    parameters.add(materialSpecularColorHueEndIgnore.set("materialSpecularColorHueEndIgnore", true));
    
    holdModParamFloatArgs.name = "materialSpecularColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialSpecularColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(materialSpecularColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "materialSpecularColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialSpecularColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(materialSpecularColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "materialSpecularColorSaturationEnd";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialSpecularColorSaturationEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(materialSpecularColorSaturationEnd->parameters);
    
    parameters.add(materialSpecularColorSaturationEndIgnore.set("materialSpecularColorSaturationEndIgnore", true));
    
    holdModParamFloatArgs.name = "materialSpecularColorBrightness";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialSpecularColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(materialSpecularColorBrightness->parameters);
    
    holdModParamFloatArgs.name = "materialSpecularColorBrightnessEnd";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialSpecularColorBrightnessEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(materialSpecularColorBrightnessEnd->parameters);
    
    parameters.add(materialSpecularColorBrightnessEndIgnore.set("materialSpecularColorBrightnessEndIgnore", true));
    
    holdModParamBoolArgs.name = "materialSpecularColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	materialSpecularColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(materialSpecularColorHSBAsRGB->parameters);
    
    parameters.add(useDiffuseColorForEmissive.set("useDiffuseColorForEmissive", false));
    
    holdModParamFloatArgs.name = "materialEmissiveColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialEmissiveColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(materialEmissiveColorHue->parameters);
    
    holdModParamFloatArgs.name = "materialEmissiveColorHueEnd";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialEmissiveColorHueEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(materialEmissiveColorHueEnd->parameters);
    
    parameters.add(materialEmissiveColorHueEndIgnore.set("materialEmissiveColorHueEndIgnore", true));
    
    holdModParamFloatArgs.name = "materialEmissiveColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialEmissiveColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(materialEmissiveColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "materialEmissiveColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialEmissiveColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(materialEmissiveColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "materialEmissiveColorSaturationEnd";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialEmissiveColorSaturationEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(materialEmissiveColorSaturationEnd->parameters);
    
    parameters.add(materialEmissiveColorSaturationEndIgnore.set("materialEmissiveColorSaturationEndIgnore", true));
    
    holdModParamFloatArgs.name = "materialEmissiveColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialEmissiveColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(materialEmissiveColorBrightness->parameters);
    
    holdModParamFloatArgs.name = "materialEmissiveColorBrightnessEnd";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialEmissiveColorBrightnessEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(materialEmissiveColorBrightnessEnd->parameters);
    
    parameters.add(materialEmissiveColorBrightnessEndIgnore.set("materialEmissiveColorBrightnessEndIgnore", true));
    
    holdModParamBoolArgs.name = "materialEmissiveColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	materialEmissiveColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(materialEmissiveColorHSBAsRGB->parameters);
    
    colorSpreadCurve.setValueArrayToRamp(0, 1);
    colorSpreadCurve.setName("colorSpreadCurve");
    parameters.add(colorSpreadCurve.parameters);
    
    colorSpreadCurve2.setValueArrayToRamp(0, 1);
    colorSpreadCurve2.setName("colorSpreadCurve2");
    parameters.add(colorSpreadCurve2.parameters);
    
    holdModParamFloatArgs.name = "colorSpreadCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	colorSpreadCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(colorSpreadCurveMorph->parameters);
    
    holdModParamFloatArgs.name = "positionX";
    holdModParamFloatArgs.fixedValue = 0.25;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	positionX = createModParameter(holdModParamFloatArgs);
    parameters.add(positionX->parameters);
    
    holdModParamFloatArgs.name = "positionXEnd";
    holdModParamFloatArgs.fixedValue = 0.75;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	positionXEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(positionXEnd->parameters);
    
    parameters.add(positionXEndIgnore.set("positionXEndIgnore", false));
    
    holdModParamFloatArgs.name = "positionY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	positionY = createModParameter(holdModParamFloatArgs);
    parameters.add(positionY->parameters);
    
    holdModParamFloatArgs.name = "positionYEnd";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	positionYEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(positionYEnd->parameters);
    
    parameters.add(positionYEndIgnore.set("positionYEndIgnore", true));
    
    holdModParamFloatArgs.name = "positionZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 0.0;
	positionZ = createModParameter(holdModParamFloatArgs);
    parameters.add(positionZ->parameters);
    
    holdModParamFloatArgs.name = "positionZEnd";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 0.0;
	positionZEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(positionZEnd->parameters);
    
    parameters.add(positionZEndIgnore.set("positionZEndIgnore", true));
    
    positionSpreadCurve.setValueArrayToRamp(0, 1);
    positionSpreadCurve.setName("positionSpreadCurve");
    parameters.add(positionSpreadCurve.parameters);
    
    positionSpreadCurve2.setValueArrayToRamp(0, 1);
    positionSpreadCurve2.setName("positionSpreadCurve2");
    parameters.add(positionSpreadCurve2.parameters);
    
    holdModParamFloatArgs.name = "positionSpreadCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	positionSpreadCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(positionSpreadCurveMorph->parameters);
    
    holdModParamFloatArgs.name = "rotateX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	rotateX = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateX->parameters);
    
    holdModParamFloatArgs.name = "rotateXEnd";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	rotateXEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateXEnd->parameters);
    
    parameters.add(rotateXEndIgnore.set("rotateXEndIgnore", true));
    
    holdModParamFloatArgs.name = "rotateY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	rotateY = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateY->parameters);
    
    holdModParamFloatArgs.name = "rotateYEnd";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	rotateYEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateYEnd->parameters);
    
    parameters.add(rotateYEndIgnore.set("rotateYEndIgnore", true));
    
    holdModParamFloatArgs.name = "rotateZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	rotateZ = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateZ->parameters);
    
    holdModParamFloatArgs.name = "rotateZEnd";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	rotateZEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateZEnd->parameters);
    
    parameters.add(rotateZEndIgnore.set("rotateZEndIgnore", true));
    
    holdModParamFloatArgs.name = "rotateMultiply";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
	rotateMultiply = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateMultiply->parameters);
    
    holdModParamFloatArgs.name = "rotateMultiplyEnd";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
	rotateMultiplyEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateMultiplyEnd->parameters);
    
    parameters.add(rotateMultiplyEndIgnore.set("rotateMultiplyEndIgnore", true));
    
    rotateSpreadCurve.setValueArrayToRamp(0, 1);
    rotateSpreadCurve.setName("rotateSpreadCurve");
    parameters.add(rotateSpreadCurve.parameters);
    
    rotateSpreadCurve2.setValueArrayToRamp(0, 1);
    rotateSpreadCurve2.setName("rotateSpreadCurve2");
    parameters.add(rotateSpreadCurve2.parameters);
    
    holdModParamFloatArgs.name = "rotateSpreadCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	rotateSpreadCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateSpreadCurveMorph->parameters);
    
    holdModParamFloatArgs.name = "anchorX";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	anchorX = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorX->parameters);
    
    holdModParamFloatArgs.name = "anchorXEnd";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	anchorXEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorXEnd->parameters);
    
    parameters.add(anchorXEndIgnore.set("anchorXEndIgnore", true));
    
    holdModParamFloatArgs.name = "anchorY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	anchorY = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorY->parameters);
    
    holdModParamFloatArgs.name = "anchorYEnd";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	anchorYEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorYEnd->parameters);
    
    parameters.add(anchorYEndIgnore.set("anchorYEndIgnore", true));
    
    holdModParamFloatArgs.name = "anchorZ";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	anchorZ = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorZ->parameters);
    
    holdModParamFloatArgs.name = "anchorZEnd";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	anchorZEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorZEnd->parameters);
    
    parameters.add(anchorZEndIgnore.set("anchorZEndIgnore", true));
    
    anchorSpreadCurve.setValueArrayToRamp(0, 1);
    anchorSpreadCurve.setName("anchorSpreadCurve");
    parameters.add(anchorSpreadCurve.parameters);
    
    anchorSpreadCurve2.setValueArrayToRamp(0, 1);
    anchorSpreadCurve2.setName("anchorSpreadCurve2");
    parameters.add(anchorSpreadCurve2.parameters);
    
    holdModParamFloatArgs.name = "anchorSpreadCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	anchorSpreadCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorSpreadCurveMorph->parameters);
    
    holdModParamFloatArgs.name = "scaleX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 3.0;
	scaleX = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleX->parameters);
    
    holdModParamFloatArgs.name = "scaleXEnd";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 3.0;
	scaleXEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleXEnd->parameters);
    
    parameters.add(scaleXEndIgnore.set("scaleXEndIgnore", true));
    
    holdModParamFloatArgs.name = "scaleY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 3.0;
	scaleY = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleY->parameters);
    
    holdModParamFloatArgs.name = "scaleYEnd";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 3.0;
	scaleYEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleYEnd->parameters);
    
    parameters.add(scaleYEndIgnore.set("scaleYEndIgnore", true));
    
    holdModParamFloatArgs.name = "scaleZ";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 3.0;
	scaleZ = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleZ->parameters);
    
    holdModParamFloatArgs.name = "scaleZEnd";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 3.0;
	scaleZEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleZEnd->parameters);
    
    parameters.add(scaleZEndIgnore.set("scaleZEndIgnore", true));
    
    parameters.add(useScaleXForScaleY.set("useScaleXForScaleY", false));
    parameters.add(useScaleXForScaleZ.set("useScaleXForScaleZ", false));
    
    scaleSpreadCurve.setValueArrayToRamp(0, 1);
    scaleSpreadCurve.setName("scaleSpreadCurve");
    parameters.add(scaleSpreadCurve.parameters);
    
    scaleSpreadCurve2.setValueArrayToRamp(0, 1);
    scaleSpreadCurve2.setName("scaleSpreadCurve2");
    parameters.add(scaleSpreadCurve2.parameters);
    
    holdModParamFloatArgs.name = "scaleSpreadCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	scaleSpreadCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleSpreadCurveMorph->parameters);
    
    // setup points and merge parameters
    arrCurvePoints[0].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "corner11");
    arrCurvePoints[1].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point12");
    arrCurvePoints[2].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point13");
    arrCurvePoints[3].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point14");
    arrCurvePoints[4].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point15");
    arrCurvePoints[5].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "corner16");
    arrCurvePoints[6].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point21");
    arrCurvePoints[7].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point22");
    arrCurvePoints[8].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point23");
    arrCurvePoints[9].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point24");
    arrCurvePoints[10].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point25");
    arrCurvePoints[11].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point26");
    arrCurvePoints[12].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point31");
    arrCurvePoints[13].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point32");
    arrCurvePoints[14].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point33");
    arrCurvePoints[15].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point34");
    arrCurvePoints[16].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point35");
    arrCurvePoints[17].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point36");
    arrCurvePoints[18].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point41");
    arrCurvePoints[19].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point42");
    arrCurvePoints[20].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point43");
    arrCurvePoints[21].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point44");
    arrCurvePoints[22].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point45");
    arrCurvePoints[23].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point46");
    arrCurvePoints[24].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point51");
    arrCurvePoints[25].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point52");
    arrCurvePoints[26].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point53");
    arrCurvePoints[27].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point54");
    arrCurvePoints[28].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point55");
    arrCurvePoints[29].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point56");
    arrCurvePoints[30].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "corner61");
    arrCurvePoints[31].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point62");
    arrCurvePoints[32].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point63");
    arrCurvePoints[33].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point64");
    arrCurvePoints[34].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "point65");
    arrCurvePoints[35].setup(TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION, "corner66");

    mergeParameters(arrCurvePoints[0].parameters, arrCurvePoints[0].modParameters);
    mergeParameters(arrCurvePoints[1].parameters, arrCurvePoints[1].modParameters);
    mergeParameters(arrCurvePoints[2].parameters, arrCurvePoints[2].modParameters);
    mergeParameters(arrCurvePoints[3].parameters, arrCurvePoints[3].modParameters);
    mergeParameters(arrCurvePoints[4].parameters, arrCurvePoints[4].modParameters);
    mergeParameters(arrCurvePoints[5].parameters, arrCurvePoints[5].modParameters);
    mergeParameters(arrCurvePoints[6].parameters, arrCurvePoints[6].modParameters);
    mergeParameters(arrCurvePoints[7].parameters, arrCurvePoints[7].modParameters);
    mergeParameters(arrCurvePoints[8].parameters, arrCurvePoints[8].modParameters);
    mergeParameters(arrCurvePoints[9].parameters, arrCurvePoints[9].modParameters);
    mergeParameters(arrCurvePoints[10].parameters, arrCurvePoints[10].modParameters);
    mergeParameters(arrCurvePoints[11].parameters, arrCurvePoints[11].modParameters);
    mergeParameters(arrCurvePoints[12].parameters, arrCurvePoints[12].modParameters);
    mergeParameters(arrCurvePoints[13].parameters, arrCurvePoints[13].modParameters);
    mergeParameters(arrCurvePoints[14].parameters, arrCurvePoints[14].modParameters);
    mergeParameters(arrCurvePoints[15].parameters, arrCurvePoints[15].modParameters);
    mergeParameters(arrCurvePoints[16].parameters, arrCurvePoints[16].modParameters);
    mergeParameters(arrCurvePoints[17].parameters, arrCurvePoints[17].modParameters);
    mergeParameters(arrCurvePoints[18].parameters, arrCurvePoints[18].modParameters);
    mergeParameters(arrCurvePoints[19].parameters, arrCurvePoints[19].modParameters);
    mergeParameters(arrCurvePoints[20].parameters, arrCurvePoints[20].modParameters);
    mergeParameters(arrCurvePoints[21].parameters, arrCurvePoints[21].modParameters);
    mergeParameters(arrCurvePoints[22].parameters, arrCurvePoints[22].modParameters);
    mergeParameters(arrCurvePoints[23].parameters, arrCurvePoints[23].modParameters);
    mergeParameters(arrCurvePoints[24].parameters, arrCurvePoints[24].modParameters);
    mergeParameters(arrCurvePoints[25].parameters, arrCurvePoints[25].modParameters);
    mergeParameters(arrCurvePoints[26].parameters, arrCurvePoints[26].modParameters);
    mergeParameters(arrCurvePoints[27].parameters, arrCurvePoints[27].modParameters);
    mergeParameters(arrCurvePoints[28].parameters, arrCurvePoints[28].modParameters);
    mergeParameters(arrCurvePoints[29].parameters, arrCurvePoints[29].modParameters);
    mergeParameters(arrCurvePoints[30].parameters, arrCurvePoints[30].modParameters);
    mergeParameters(arrCurvePoints[31].parameters, arrCurvePoints[31].modParameters);
    mergeParameters(arrCurvePoints[32].parameters, arrCurvePoints[32].modParameters);
    mergeParameters(arrCurvePoints[33].parameters, arrCurvePoints[33].modParameters);
    mergeParameters(arrCurvePoints[34].parameters, arrCurvePoints[34].modParameters);
    mergeParameters(arrCurvePoints[35].parameters, arrCurvePoints[35].modParameters);


    // add listeners to relevent parameters:
    ofAddListener(surfaceResolution->parameters.parameterChangedE(),this,&TXDrawBSurfaces2::surfaceResolutionChanged);
    ofAddListener(useLooping->parameters.parameterChangedE(),this,&TXDrawBSurfaces2::useLoopingChanged);
 
    // add listener to relevent parameters:
    useImageAsTexture.addListener(this, &TXDrawBSurfaces2::useImageAsTextureChanged);
    useExternalSourceImage.addListener(this, &TXDrawBSurfaces2::useExternalSourceImageChanged);

    initPresetsAsFlatPlane.addListener(this, &TXDrawBSurfaces2::presetsChangedBool);
    offsetDistortPointX.addListener(this, &TXDrawBSurfaces2::presetsChangedFloat);
    offsetDistortPointY.addListener(this, &TXDrawBSurfaces2::presetsChangedFloat);
    offsetDistortPointZ.addListener(this, &TXDrawBSurfaces2::presetsChangedFloat);
    offsetRandomSeed.addListener(this, &TXDrawBSurfaces2::presetsChangedInt);
    
    // asset slots
    createImageAssetSlot("sourceImageAsset");
    
    // external image slots
    createExtImageModuleSlot("extSourceImageModule");
        
    // register Texture
    registerTexture();
    
    // initialise material
    material.setShininess(25.0);
    
    // init image ptrs
    sourceImage = &holdImage1;
    newImage = &holdImage2;
    
    // init
    rebuildPresets();
    setupSurface();
    meshCentroid.zero();
    sourceImageHasChanged = false;
    retryMapTexture = false;
}

void TXDrawBSurfaces2::update(){
    ofImage * tempImage;
    if (rebuildPresetsRequested) {
        rebuildPresets();
    };
    if (sourceImageHasChanged) {
        loadSourceImage();
        sourceImageHasChanged = false;
    };
    // if new image loaded then swap images & remap
    if (newImage->getTexture().isAllocated()) {
        tempImage = sourceImage;
        sourceImage = newImage;
        newImage = tempImage;
        newImage->clear();
        retryMapTexture = true;
        surfaceHasChanged = true;
    };
    if (retryMapTexture) {
        mapTextureToSurface();
    };
    if (surfaceHasChanged) {
        setupSurface();
    };
}

void TXDrawBSurfaces2::draw(){
    if (!drawActive->getBool()) {
        return;
    };

    int num, totalSurfaces, holdLineWidth;
    float holdAnchorX, holdAnchorY, holdAnchorZ;
    bool holdDrawWireframe = drawWireframe->getBool();
    bool holdUseLooping = useLooping->getBool();

    float holdPosSpreadCurveMorph = positionSpreadCurveMorph->getFloat();
    float holdRotateSpreadCurveMorph = rotateSpreadCurveMorph->getFloat();
    float holdAnchorSpreadCurveMorph = anchorSpreadCurveMorph->getFloat();
    float holdScaleSpreadCurveMorph = scaleSpreadCurveMorph->getFloat();
    float holdColorSpreadCurveMorph = colorSpreadCurveMorph->getFloat();
    float holdPointsSpreadCurveMorph = pointsSpreadCurveMorph->getFloat();

    float hold_pointsMorphX = pointsMorphX->getFloat();
    float hold_pointsMorphY = pointsMorphY->getFloat();
    float hold_positionX = positionX->getFloat();
    float hold_positionY = positionY->getFloat();
    float hold_positionZ = positionZ->getFloat();
    float hold_rotateX = rotateX->getFloat();
    float hold_rotateY = rotateY->getFloat();
    float hold_rotateZ = rotateZ->getFloat();
    float hold_rotateMultiply = rotateMultiply->getFloat();
    float hold_anchorX = anchorX->getFloat();
    float hold_anchorY = anchorY->getFloat();
    float hold_anchorZ = anchorZ->getFloat();
    float hold_scaleX = scaleX->getFloat();
    float hold_scaleY = scaleY->getFloat();
    float hold_scaleZ = scaleZ->getFloat();

    float hold_materialShininess = materialShininess->getFloat();
    float hold_materialDiffuseColorHue = materialDiffuseColorHue->getFloat();
    float hold_materialDiffuseColorHueRotate = materialDiffuseColorHueRotate->getFloat();
    float hold_materialDiffuseColorSaturation = materialDiffuseColorSaturation->getFloat();
    float hold_materialDiffuseColorBrightness = materialDiffuseColorBrightness->getFloat();
    float hold_materialDiffuseColorHSBAsRGB = materialDiffuseColorHSBAsRGB->getBool();
    float hold_materialAmbientColorHue = materialAmbientColorHue->getFloat();
    float hold_materialAmbientColorHueRotate = materialAmbientColorHueRotate->getFloat();
    float hold_materialAmbientColorSaturation = materialAmbientColorSaturation->getFloat();
    float hold_materialAmbientColorBrightness = materialAmbientColorBrightness->getFloat();
    float hold_materialAmbientColorHSBAsRGB = materialAmbientColorHSBAsRGB->getBool();
    float hold_materialSpecularColorHue = materialSpecularColorHue->getFloat();
    float hold_materialSpecularColorHueRotate = materialSpecularColorHueRotate->getFloat();
    float hold_materialSpecularColorSaturation = materialSpecularColorSaturation->getFloat();
    float hold_materialSpecularColorBrightness = materialSpecularColorBrightness->getFloat();
    float hold_materialSpecularColorHSBAsRGB = materialSpecularColorHSBAsRGB->getBool();
    float hold_materialEmissiveColorHue = materialEmissiveColorHue->getFloat();
    float hold_materialEmissiveColorHueRotate = materialEmissiveColorHueRotate->getFloat();
    float hold_materialEmissiveColorSaturation = materialEmissiveColorSaturation->getFloat();
    float hold_materialEmissiveColorBrightness = materialEmissiveColorBrightness->getFloat();
    float hold_materialEmissiveColorHSBAsRGB = materialEmissiveColorHSBAsRGB->getBool();

    float hold_pointsMorphXEnd;
    float hold_pointsMorphYEnd;
    float hold_positionXEnd;
    float hold_positionYEnd;
    float hold_positionZEnd;
    float hold_rotateXEnd;
    float hold_rotateYEnd;
    float hold_rotateZEnd;
    float hold_rotateMultiplyEnd;
    float hold_anchorXEnd;
    float hold_anchorYEnd;
    float hold_anchorZEnd;
    float hold_scaleXEnd;
    float hold_scaleYEnd;
    float hold_scaleZEnd;
    float hold_materialShininessEnd;
    float hold_materialDiffuseColorHueEnd;
    float hold_materialDiffuseColorSaturationEnd;
    float hold_materialDiffuseColorBrightnessEnd;
    float hold_materialAmbientColorHueEnd;
    float hold_materialAmbientColorSaturationEnd;
    float hold_materialAmbientColorBrightnessEnd;
    float hold_materialSpecularColorHueEnd;
    float hold_materialSpecularColorSaturationEnd;
    float hold_materialSpecularColorBrightnessEnd;
    float hold_materialEmissiveColorHueEnd;
    float hold_materialEmissiveColorSaturationEnd;
    float hold_materialEmissiveColorBrightnessEnd;

    float copy_pointsMorphX;
    float copy_pointsMorphY;
    float copy_positionX;
    float copy_positionY;
    float copy_positionZ;
    float copy_rotateX;
    float copy_rotateY;
    float copy_rotateZ;
    float copy_rotateMultiply;
    float copy_anchorX;
    float copy_anchorY;
    float copy_anchorZ;
    float copy_scaleX;
    float copy_scaleY;
    float copy_scaleZ;
    float copy_materialShininess; // 0 - 128
    float copy_materialDiffuseColorHue;
    float copy_materialDiffuseColorHueRotate;
    float copy_materialDiffuseColorSaturation;
    float copy_materialDiffuseColorBrightness;
    float copy_materialAmbientColorHue;
    float copy_materialAmbientColorHueRotate;
    float copy_materialAmbientColorSaturation;
    float copy_materialAmbientColorBrightness;
    float copy_materialSpecularColorHue;
    float copy_materialSpecularColorHueRotate;
    float copy_materialSpecularColorSaturation;
    float copy_materialSpecularColorBrightness;
    float copy_materialEmissiveColorHue;
    float copy_materialEmissiveColorHueRotate;
    float copy_materialEmissiveColorSaturation;
    float copy_materialEmissiveColorBrightness;
    
    if (!pointsMorphXEndIgnore) {
        hold_pointsMorphXEnd = pointsMorphXEnd->getFloat();
    } else {
        hold_pointsMorphXEnd = hold_pointsMorphX;
    };
    if (!pointsMorphYEndIgnore) {
        hold_pointsMorphYEnd = pointsMorphYEnd->getFloat();
    } else {
        hold_pointsMorphYEnd = hold_pointsMorphY;
    };
    if (!positionXEndIgnore) {
        hold_positionXEnd = positionXEnd->getFloat();
    } else {
        hold_positionXEnd = hold_positionX;
    };
    if (!positionYEndIgnore) {
        hold_positionYEnd = positionYEnd->getFloat();
    } else {
        hold_positionYEnd = hold_positionY;
    };
    if (!positionZEndIgnore) {
        hold_positionZEnd = positionZEnd->getFloat();
    } else {
        hold_positionZEnd = hold_positionZ;
    };
    if (!rotateXEndIgnore) {
        hold_rotateXEnd = rotateXEnd->getFloat();
    } else {
        hold_rotateXEnd = hold_rotateX;
    };
    if (!rotateYEndIgnore) {
        hold_rotateYEnd = rotateYEnd->getFloat();
    } else {
        hold_rotateYEnd = hold_rotateY;
    };
    if (!rotateZEndIgnore) {
        hold_rotateZEnd = rotateZEnd->getFloat();
    } else {
        hold_rotateZEnd = hold_rotateZ;
    };
    if (!rotateMultiplyEndIgnore) {
        hold_rotateMultiplyEnd = rotateMultiplyEnd->getFloat();
    } else {
        hold_rotateMultiplyEnd = hold_rotateMultiply;
    };
    if (!anchorXEndIgnore) {
        hold_anchorXEnd = anchorXEnd->getFloat();
    } else {
        hold_anchorXEnd = hold_anchorX;
    };
    if (!anchorYEndIgnore) {
        hold_anchorYEnd = anchorYEnd->getFloat();
    } else {
        hold_anchorYEnd = hold_anchorY;
    };
    if (!anchorZEndIgnore) {
        hold_anchorZEnd = anchorZEnd->getFloat();
    } else {
        hold_anchorZEnd = hold_anchorZ;
    };
    if (!scaleXEndIgnore) {
        hold_scaleXEnd = scaleXEnd->getFloat();
    } else {
        hold_scaleXEnd = hold_scaleX;
    };
    if (!scaleYEndIgnore) {
        hold_scaleYEnd = scaleYEnd->getFloat();
    } else {
        hold_scaleYEnd = hold_scaleY;
    };
    if (!scaleZEndIgnore) {
        hold_scaleZEnd = scaleZEnd->getFloat();
    } else {
        hold_scaleZEnd = hold_scaleZ;
    };

    if (!materialShininessEndIgnore) {
        hold_materialShininessEnd = materialShininessEnd->getFloat();
    } else {
        hold_materialShininessEnd = hold_materialShininess;
    };
    if (!materialDiffuseColorHueEndIgnore) {
        hold_materialDiffuseColorHueEnd = materialDiffuseColorHueEnd->getFloat();
    } else {
        hold_materialDiffuseColorHueEnd = hold_materialDiffuseColorHue;
    };
    if (!materialDiffuseColorSaturationEndIgnore) {
        hold_materialDiffuseColorSaturationEnd = materialDiffuseColorSaturationEnd->getFloat();
    } else {
        hold_materialDiffuseColorSaturationEnd = hold_materialDiffuseColorSaturation;
    };
    if (!materialDiffuseColorBrightnessEndIgnore) {
        hold_materialDiffuseColorBrightnessEnd = materialDiffuseColorBrightnessEnd->getFloat();
    } else {
        hold_materialDiffuseColorBrightnessEnd = hold_materialDiffuseColorBrightness;
    };
    if (!materialAmbientColorHueEndIgnore) {
        hold_materialAmbientColorHueEnd = materialAmbientColorHueEnd->getFloat();
    } else {
        hold_materialAmbientColorHueEnd = hold_materialAmbientColorHue;
    };
    if (!materialAmbientColorSaturationEndIgnore) {
        hold_materialAmbientColorSaturationEnd = materialAmbientColorSaturationEnd->getFloat();
    } else {
        hold_materialAmbientColorSaturationEnd = hold_materialAmbientColorSaturation;
    };
    if (!materialAmbientColorBrightnessEndIgnore) {
        hold_materialAmbientColorBrightnessEnd = materialAmbientColorBrightnessEnd->getFloat();
    } else {
        hold_materialAmbientColorBrightnessEnd = hold_materialAmbientColorBrightness;
    };
    if (!materialSpecularColorHueEndIgnore) {
        hold_materialSpecularColorHueEnd = materialSpecularColorHueEnd->getFloat();
    } else {
        hold_materialSpecularColorHueEnd = hold_materialSpecularColorHue;
    };
    if (!materialSpecularColorSaturationEndIgnore) {
        hold_materialSpecularColorSaturationEnd = materialSpecularColorSaturationEnd->getFloat();
    } else {
        hold_materialSpecularColorSaturationEnd = hold_materialSpecularColorSaturation;
    };
    if (!materialSpecularColorBrightnessEndIgnore) {
        hold_materialSpecularColorBrightnessEnd = materialSpecularColorBrightnessEnd->getFloat();
    } else {
        hold_materialSpecularColorBrightnessEnd = hold_materialSpecularColorBrightness;
    };
    if (!materialEmissiveColorHueEndIgnore) {
        hold_materialEmissiveColorHueEnd = materialEmissiveColorHueEnd->getFloat();
    } else {
        hold_materialEmissiveColorHueEnd = hold_materialEmissiveColorHue;
    };
    if (!materialEmissiveColorSaturationEndIgnore) {
        hold_materialEmissiveColorSaturationEnd = materialEmissiveColorSaturationEnd->getFloat();
    } else {
        hold_materialEmissiveColorSaturationEnd = hold_materialEmissiveColorSaturation;
    };
    if (!materialEmissiveColorBrightnessEndIgnore) {
        hold_materialEmissiveColorBrightnessEnd = materialEmissiveColorBrightnessEnd->getFloat();
    } else {
        hold_materialEmissiveColorBrightnessEnd = hold_materialEmissiveColorBrightness;
    };

    totalSurfaces = numSurfaces->getInt();

    // bind texture if valid
    bool validTexture = false;
    int holdExtSourceID;
    if(useImageAsTexture) {
        if (useExternalSourceImage) {
            holdExtSourceID = getExtImageModuleIDSlot("extSourceImageModule");
            if (holdExtSourceID != 0) {
                if (parentSystem->getModuleTexture(holdExtSourceID) != NULL) {
                    (* parentSystem->getModuleTexture(holdExtSourceID)).bind();
                    validTexture = true;
                };
            };
        } else {
            if (!sourceImage->getTexture().isAllocated()) {
                //validTexture = false;
            } else {
                sourceImage->getTexture().bind();
                validTexture = true;
            };
        };
    };
    
    // for all surfaces
    for (int surfaceNo = 0; surfaceNo < totalSurfaces; surfaceNo++){
        float proportion;
        if ((surfaceNo == 0) || (totalSurfaces < 2)) {
            proportion = 0;
        } else {
            proportion = (float) surfaceNo / (totalSurfaces - 1);
        };
        float positionSpreadProportion =  TXFunctions::getInterpCurves(positionSpreadCurve, positionSpreadCurve2, proportion, holdPosSpreadCurveMorph);
        float rotateSpreadProportion =  TXFunctions::getInterpCurves(rotateSpreadCurve, rotateSpreadCurve2, proportion, holdRotateSpreadCurveMorph);
        float anchorSpreadProportion =  TXFunctions::getInterpCurves(anchorSpreadCurve, anchorSpreadCurve2, proportion, holdAnchorSpreadCurveMorph);
        float scaleSpreadProportion =  TXFunctions::getInterpCurves(scaleSpreadCurve, scaleSpreadCurve2, proportion, holdScaleSpreadCurveMorph);
        float colorSpreadProportion =  TXFunctions::getInterpCurves(colorSpreadCurve, colorSpreadCurve2, proportion, holdColorSpreadCurveMorph);
        float pointsSpreadProportion =  TXFunctions::getInterpCurves(pointsSpreadCurve, pointsSpreadCurve2, proportion, holdPointsSpreadCurveMorph);

        if (pointsMorphXEndIgnore) {
            copy_pointsMorphX = hold_pointsMorphX;
        } else {
            copy_pointsMorphX = TXFunctions::getInterp(hold_pointsMorphX, hold_pointsMorphXEnd, pointsSpreadProportion);
        };
        if (pointsMorphYEndIgnore) {
            copy_pointsMorphY = hold_pointsMorphY;
        } else {
            copy_pointsMorphY = TXFunctions::getInterp(hold_pointsMorphY, hold_pointsMorphYEnd, pointsSpreadProportion);
        };       
        if (positionXEndIgnore) {
            copy_positionX = hold_positionX;
        } else {
            copy_positionX = TXFunctions::getInterp(hold_positionX, hold_positionXEnd, positionSpreadProportion);
        };
        if (positionYEndIgnore) {
            copy_positionY = hold_positionY;
        } else {
            copy_positionY = TXFunctions::getInterp(hold_positionY, hold_positionYEnd, positionSpreadProportion);
        };
        if (positionZEndIgnore) {
            copy_positionZ = hold_positionZ;
        } else {
            copy_positionZ = TXFunctions::getInterp(hold_positionZ, hold_positionZEnd, positionSpreadProportion);
        };
        if (rotateXEndIgnore) {
            copy_rotateX = hold_rotateX;
        } else {
            copy_rotateX = TXFunctions::getInterp(hold_rotateX, hold_rotateXEnd, rotateSpreadProportion);
        };
        if (rotateYEndIgnore) {
            copy_rotateY = hold_rotateY;
        } else {
            copy_rotateY = TXFunctions::getInterp(hold_rotateY, hold_rotateYEnd, rotateSpreadProportion);
        };
        if (rotateZEndIgnore) {
            copy_rotateZ = hold_rotateZ;
        } else {
            copy_rotateZ = TXFunctions::getInterp(hold_rotateZ, hold_rotateZEnd, rotateSpreadProportion);
        };
        if (rotateMultiplyEndIgnore) {
            copy_rotateMultiply = hold_rotateMultiply;
        } else {
            copy_rotateMultiply = TXFunctions::getInterp(hold_rotateMultiply, hold_rotateMultiplyEnd, rotateSpreadProportion);
        };
        if (anchorXEndIgnore) {
            copy_anchorX = hold_anchorX;
        } else {
            copy_anchorX = TXFunctions::getInterp(hold_anchorX, hold_anchorXEnd, anchorSpreadProportion);
        };
        if (anchorYEndIgnore) {
            copy_anchorY = hold_anchorY;
        } else {
            copy_anchorY = TXFunctions::getInterp(hold_anchorY, hold_anchorYEnd, anchorSpreadProportion);
        };
        if (anchorZEndIgnore) {
            copy_anchorZ = hold_anchorZ;
        } else {
            copy_anchorZ = TXFunctions::getInterp(hold_anchorZ, hold_anchorZEnd, anchorSpreadProportion);
        };
        if (scaleXEndIgnore) {
            copy_scaleX = hold_scaleX;
        } else {
            copy_scaleX = TXFunctions::getInterp(hold_scaleX, hold_scaleXEnd, scaleSpreadProportion);
        };
        if (useScaleXForScaleY) {
            copy_scaleY = copy_scaleX;
        } else {
            if (scaleYEndIgnore) {
                copy_scaleY = hold_scaleY;
            } else {
                copy_scaleY = TXFunctions::getInterp(hold_scaleY, hold_scaleYEnd, scaleSpreadProportion);
            };
        };
        if (useScaleXForScaleZ) {
            copy_scaleZ = copy_scaleX;
        } else {
            if (scaleZEndIgnore) {
                copy_scaleZ = hold_scaleZ;
            } else {
                copy_scaleZ = TXFunctions::getInterp(hold_scaleZ, hold_scaleZEnd, scaleSpreadProportion);
            };
        };

        ofColor holdColor;
        
        if (materialShininessEndIgnore) {
            copy_materialShininess = hold_materialShininess;
        } else {
            copy_materialShininess = TXFunctions::getInterp(hold_materialShininess, hold_materialShininessEnd, colorSpreadProportion);
        };
        material.setShininess(copy_materialShininess);
        
        if (materialDiffuseColorHueEndIgnore) {
            copy_materialDiffuseColorHue = hold_materialDiffuseColorHue;
        } else {
            copy_materialDiffuseColorHue = TXFunctions::getInterp(hold_materialDiffuseColorHue, hold_materialDiffuseColorHueEnd, colorSpreadProportion);
        };
        if (materialDiffuseColorSaturationEndIgnore) {
            copy_materialDiffuseColorSaturation = hold_materialDiffuseColorSaturation;
        } else {
            copy_materialDiffuseColorSaturation = TXFunctions::getInterp(hold_materialDiffuseColorSaturation, hold_materialDiffuseColorSaturationEnd, colorSpreadProportion);
        };
        if (materialDiffuseColorBrightnessEndIgnore) {
            copy_materialDiffuseColorBrightness = hold_materialDiffuseColorBrightness;
        } else {
            copy_materialDiffuseColorBrightness = TXFunctions::getInterp(hold_materialDiffuseColorBrightness, hold_materialDiffuseColorBrightnessEnd, colorSpreadProportion);
        };
        holdColor = TXFunctions::txGetColor(copy_materialDiffuseColorHue, copy_materialDiffuseColorSaturation, copy_materialDiffuseColorBrightness, 1.0, hold_materialDiffuseColorHueRotate, hold_materialDiffuseColorHSBAsRGB);
        material.setDiffuseColor(holdColor);
        
        if (useDiffuseColorForAmbient) {
            material.setAmbientColor(material.getDiffuseColor());
        } else {
            if (materialAmbientColorHueEndIgnore) {
                copy_materialAmbientColorHue = hold_materialAmbientColorHue;
            } else {
                copy_materialAmbientColorHue = TXFunctions::getInterp(hold_materialAmbientColorHue, hold_materialAmbientColorHueEnd, colorSpreadProportion);
            };
            if (materialAmbientColorSaturationEndIgnore) {
                copy_materialAmbientColorSaturation = hold_materialAmbientColorSaturation;
            } else {
                copy_materialAmbientColorSaturation = TXFunctions::getInterp(hold_materialAmbientColorSaturation, hold_materialAmbientColorSaturationEnd, colorSpreadProportion);
            };
            if (materialAmbientColorBrightnessEndIgnore) {
                copy_materialAmbientColorBrightness = hold_materialAmbientColorBrightness;
            } else {
                copy_materialAmbientColorBrightness = TXFunctions::getInterp(hold_materialAmbientColorBrightness, hold_materialAmbientColorBrightnessEnd, colorSpreadProportion);
            };
            holdColor = TXFunctions::txGetColor(copy_materialAmbientColorHue, copy_materialAmbientColorSaturation, copy_materialAmbientColorBrightness, 1.0, hold_materialAmbientColorHueRotate, hold_materialAmbientColorHSBAsRGB);
            material.setAmbientColor(holdColor);
        };
        
        if (useDiffuseColorForSpecular) {
            material.setSpecularColor(material.getDiffuseColor());
        } else {
            if (materialSpecularColorHueEndIgnore) {
                copy_materialSpecularColorHue = hold_materialSpecularColorHue;
            } else {
                copy_materialSpecularColorHue = TXFunctions::getInterp(hold_materialSpecularColorHue, hold_materialSpecularColorHueEnd, colorSpreadProportion);
            };
            if (materialSpecularColorSaturationEndIgnore) {
                copy_materialSpecularColorSaturation = hold_materialSpecularColorSaturation;
            } else {
                copy_materialSpecularColorSaturation = TXFunctions::getInterp(hold_materialSpecularColorSaturation, hold_materialSpecularColorSaturationEnd, colorSpreadProportion);
            };
            if (materialSpecularColorBrightnessEndIgnore) {
                copy_materialSpecularColorBrightness = hold_materialSpecularColorBrightness;
            } else {
                copy_materialSpecularColorBrightness = TXFunctions::getInterp(hold_materialSpecularColorBrightness, hold_materialSpecularColorBrightnessEnd, colorSpreadProportion);
            };
            holdColor = TXFunctions::txGetColor(copy_materialSpecularColorHue, copy_materialSpecularColorSaturation, copy_materialSpecularColorBrightness, 1.0, hold_materialSpecularColorHueRotate, hold_materialSpecularColorHSBAsRGB);
            material.setSpecularColor(holdColor);
        };
        
        if (useDiffuseColorForEmissive) {
            material.setEmissiveColor(material.getDiffuseColor());
        } else {
            if (materialEmissiveColorHueEndIgnore) {
                copy_materialEmissiveColorHue = hold_materialEmissiveColorHue;
            } else {
                copy_materialEmissiveColorHue = TXFunctions::getInterp(hold_materialEmissiveColorHue, hold_materialEmissiveColorHueEnd, colorSpreadProportion);
            };
            if (materialEmissiveColorSaturationEndIgnore) {
                copy_materialEmissiveColorSaturation = hold_materialEmissiveColorSaturation;
            } else {
                copy_materialEmissiveColorSaturation = TXFunctions::getInterp(hold_materialEmissiveColorSaturation, hold_materialEmissiveColorSaturationEnd, colorSpreadProportion);
            };
            if (materialEmissiveColorBrightnessEndIgnore) {
                copy_materialEmissiveColorBrightness = hold_materialEmissiveColorBrightness;
            } else {
                copy_materialEmissiveColorBrightness = TXFunctions::getInterp(hold_materialEmissiveColorBrightness, hold_materialEmissiveColorBrightnessEnd, colorSpreadProportion);
            };
            holdColor = TXFunctions::txGetColor(copy_materialEmissiveColorHue, copy_materialEmissiveColorSaturation, copy_materialEmissiveColorBrightness, 1.0, hold_materialEmissiveColorHueRotate, hold_materialEmissiveColorHSBAsRGB);
            material.setEmissiveColor(holdColor);
        };

        int holdPointsMorphType = pointsMorphType->getInt();
        bool holdUsePointsToOffsetMorph = usePointsToOffsetMorph->getBool();
        
        int hold_pointsMorphPresetA = pointsMorphPresetA->getInt();
        int hold_pointsMorphPresetB = pointsMorphPresetB->getInt();
        int hold_pointsMorphPresetC = pointsMorphPresetC->getInt();
        int hold_pointsMorphPresetD = pointsMorphPresetD->getInt();
        int hold_pointsMorphPresetE = pointsMorphPresetE->getInt();
        
        // if control points needed then build contolPointsData
        if ((holdPointsMorphType == TXPOINTSMORPHTYPE_NOMORPH) || holdUsePointsToOffsetMorph) {
            for (int pointNo = 0; pointNo < totalCurvePoints; pointNo++){
                contolPointsData[(pointNo * 3)] = arrCurvePoints[pointNo].getInterpControl1X(pointsSpreadProportion, 2, OF_EASE_LINEAR_IN);
                contolPointsData[(pointNo * 3)+1] = arrCurvePoints[pointNo].getInterpControl1Y(pointsSpreadProportion, 2, OF_EASE_LINEAR_IN);
                contolPointsData[(pointNo * 3)+2] = arrCurvePoints[pointNo].getInterpControl1Z(pointsSpreadProportion, 2, OF_EASE_LINEAR_IN);
            };
        };

        // build point vector
        ofVec3f holdPoint, scaledPoint, mirrorPoint, inputA, inputB, inputC, inputD, inputE, holdMix1, holdMix2;
        ofVec3f midPoint, morphPoint;
        float holdPropX, holdPropY, holdDistance;
        float minX = 10000, minY = 10000, minZ = 10000;
        float maxX = -10000, maxY = -10000, maxZ = -10000;
        vector<ofVec3f> arrPoints;
        vector<ofVec3f> arrLoopPoints;
        vector<ofVec3f> arrMirrorPoints;
        
        arrPoints.resize(totalCurvePoints);
        
        for (int pointNo = 0; pointNo < totalCurvePoints; pointNo++){
            switch (holdPointsMorphType ) {
                case TXPOINTSMORPHTYPE_NOMORPH:
                    holdPoint.x += contolPointsData[(pointNo*3)];
                    holdPoint.y += contolPointsData[(pointNo*3)+1];
                    holdPoint.z += contolPointsData[(pointNo*3)+2];
                    break;
                case TXPOINTSMORPHTYPE_SOLOMORPHPRESETA:
                    holdPoint = getSetData(hold_pointsMorphPresetA, pointNo);
                    break;
                case TXPOINTSMORPHTYPE_SOLOMORPHPRESETB:
                    holdPoint = getSetData(hold_pointsMorphPresetB, pointNo);
                    break;
                case TXPOINTSMORPHTYPE_SOLOMORPHPRESETC:
                    holdPoint = getSetData(hold_pointsMorphPresetC, pointNo);
                    break;
                case TXPOINTSMORPHTYPE_SOLOMORPHPRESETD:
                    holdPoint = getSetData(hold_pointsMorphPresetD, pointNo);
                    break;
                case TXPOINTSMORPHTYPE_SOLOMORPHPRESETE:
                    holdPoint = getSetData(hold_pointsMorphPresetE, pointNo);
                    break;
                case TXPOINTSMORPHTYPE_LINEAR2SETS:
                    inputA  = getSetData(hold_pointsMorphPresetA, pointNo);
                    inputB = getSetData(hold_pointsMorphPresetB, pointNo);
                    holdPoint = inputA.getInterpolated(inputB, copy_pointsMorphX);
                    break;
                case TXPOINTSMORPHTYPE_LINEAR3SETS:
                    if (copy_pointsMorphX <= 0.5) {
                        inputA  = getSetData(hold_pointsMorphPresetA, pointNo);
                        inputB = getSetData(hold_pointsMorphPresetB, pointNo);
                        holdPropX = copy_pointsMorphX * 2;
                        holdPoint = inputA.getInterpolated(inputB, holdPropX);
                    } else {
                        inputB = getSetData(hold_pointsMorphPresetB, pointNo);
                        inputC  = getSetData(hold_pointsMorphPresetC, pointNo);
                        holdPropX = (copy_pointsMorphX - 0.5) * 2;
                        holdPoint = inputB.getInterpolated(inputC, holdPropX);
                    }
                    break;
                case TXPOINTSMORPHTYPE_LINEAR4SETS:
                    if (copy_pointsMorphX <= 0.33333333) {
                        inputA  = getSetData(hold_pointsMorphPresetA, pointNo);
                        inputB = getSetData(hold_pointsMorphPresetB, pointNo);
                        holdPropX = copy_pointsMorphX * 3;
                        holdPoint = inputA.getInterpolated(inputB, holdPropX);
                    } else if (copy_pointsMorphX <= 0.6666666) {
                        inputB = getSetData(hold_pointsMorphPresetB, pointNo);
                        inputC  = getSetData(hold_pointsMorphPresetC, pointNo);
                        holdPropX = (copy_pointsMorphX - 0.33333333) * 3;
                        holdPoint = inputB.getInterpolated(inputC, holdPropX);
                    } else {
                        inputC  = getSetData(hold_pointsMorphPresetC, pointNo);
                        inputD = getSetData(hold_pointsMorphPresetD, pointNo);
                        holdPropX = (copy_pointsMorphX - 0.6666666) * 3;
                        holdPoint = inputC.getInterpolated(inputD, holdPropX);
                    }
                    break;
                case TXPOINTSMORPHTYPE_LINEAR5SETS:
                    if (copy_pointsMorphX <= 0.25) {
                        inputA  = getSetData(hold_pointsMorphPresetA, pointNo);
                        inputB = getSetData(hold_pointsMorphPresetB, pointNo);
                        holdPropX = copy_pointsMorphX * 4;
                        holdPoint = inputA.getInterpolated(inputB, holdPropX);
                    } else if (copy_pointsMorphX <= 0.5) {
                        inputB = getSetData(hold_pointsMorphPresetB, pointNo);
                        inputC  = getSetData(hold_pointsMorphPresetC, pointNo);
                        holdPropX = (copy_pointsMorphX - 0.25) * 4;
                        holdPoint = inputB.getInterpolated(inputC, holdPropX);
                    } else if (copy_pointsMorphX <= 0.75) {
                        inputC  = getSetData(hold_pointsMorphPresetC, pointNo);
                        inputD = getSetData(hold_pointsMorphPresetD, pointNo);
                        holdPropX = (copy_pointsMorphX - 0.5) * 4;
                        holdPoint = inputC.getInterpolated(inputD, holdPropX);
                    } else {
                        inputD = getSetData(hold_pointsMorphPresetD, pointNo);
                        inputE  = getSetData(hold_pointsMorphPresetE, pointNo);
                        holdPropX = (copy_pointsMorphX - 0.75) * 4;
                        holdPoint = inputD.getInterpolated(inputE, holdPropX);
                    }
                    break;
                case TXPOINTSMORPHTYPE_2D4SETS:
                    inputA  = getSetData(hold_pointsMorphPresetA, pointNo);
                    inputB = getSetData(hold_pointsMorphPresetB, pointNo);
                    inputC  = getSetData(hold_pointsMorphPresetC, pointNo);
                    inputD = getSetData(hold_pointsMorphPresetD, pointNo);
                    holdMix1 = inputA.getInterpolated(inputB, copy_pointsMorphX);
                    holdMix2 = inputC.getInterpolated(inputD, copy_pointsMorphX);
                    holdPoint = holdMix1.getInterpolated(holdMix2, copy_pointsMorphY);
                    break;
                case TXPOINTSMORPHTYPE_2D5SETS:
                    inputA  = getSetData(hold_pointsMorphPresetA, pointNo);
                    inputB = getSetData(hold_pointsMorphPresetB, pointNo);
                    inputC  = getSetData(hold_pointsMorphPresetC, pointNo);
                    inputD = getSetData(hold_pointsMorphPresetD, pointNo);
                    inputE  = getSetData(hold_pointsMorphPresetE, pointNo);
                    holdMix1 = inputA.getInterpolated(inputB, copy_pointsMorphX);
                    holdMix2 = inputC.getInterpolated(inputD, copy_pointsMorphX);
                    holdPoint = holdMix1.getInterpolated(holdMix2, copy_pointsMorphY);
                    // mix in E using distance to centre
                    midPoint = ofVec3f(0.5,0.5,0);
                    morphPoint = ofVec3f(copy_pointsMorphX,copy_pointsMorphY,0);
                    holdDistance = midPoint.distance(morphPoint);
                    // scale distance so corners are full mix
                    holdPoint = inputE.getInterpolated(holdPoint, holdDistance * 1.4142135623731);
                    break;
                default:
                    // same as TXPOINTSMORPHTYPE_NOMORPH
                    holdPoint.x += contolPointsData[(pointNo*3)];
                    holdPoint.y += contolPointsData[(pointNo*3)+1];
                    holdPoint.z += contolPointsData[(pointNo*3)+2];
                    break;
            }; // end of switch
            
            if ((holdPointsMorphType > 0) && holdUsePointsToOffsetMorph) {
                holdPoint.x += contolPointsData[(pointNo*3)];
                holdPoint.y += contolPointsData[(pointNo*3)+1];
                holdPoint.z += contolPointsData[(pointNo*3)+2];
            };
            // scale before adding to array
            scaledPoint.x = getMaxWidth() * holdPoint.x;
            scaledPoint.y = getMaxHeight() * holdPoint.y;
            scaledPoint.z = getMaxDepth() * holdPoint.z;
            arrPoints[pointNo] = scaledPoint;
            minX = min(minX, scaledPoint.x);
            minY = min(minY, scaledPoint.y);
            minZ = min(minZ, scaledPoint.z);
            maxX = max(maxX, scaledPoint.x);
            maxY = max(maxY, scaledPoint.y);
            maxZ = max(maxZ, scaledPoint.z);
        };  // end of for (int pointNo = 0; pointNo < totalCurvePoints; pointNo++)
 
        // if looping
        if (holdUseLooping) {
            arrLoopPoints.resize(totalCurvePlusLoopPoints);
            // add loop points
            int loopPointsIndex, holdIndex;
            for (int rowNo = 0; rowNo < 8; rowNo++){
                for (int colNo = 0; colNo < 8; colNo++){
                    loopPointsIndex = (rowNo * 8) + colNo;
                    if (rowNo < 6) {
                        if (colNo < 6) {
                            holdIndex = (rowNo * 6) + colNo;
                            arrLoopPoints[loopPointsIndex] = arrPoints[holdIndex];
                        } else {
                            if (colNo == 6) {
                                // mirror at opposite edge
                                holdIndex = (rowNo * 6);
                                arrLoopPoints[loopPointsIndex]  = (2 * arrPoints[holdIndex]) - arrPoints[holdIndex + 1];
                            } else {
                                // colNo == 7, copy 1st point in row
                                holdIndex = (rowNo * 6);
                                arrLoopPoints[loopPointsIndex] = arrPoints[holdIndex];
                            };
                        };
                    } else {
                        if (colNo < 6) {
                            if (rowNo == 6) {
                                // mirror at opposite edge
                                holdIndex = colNo;
                                arrLoopPoints[loopPointsIndex]  = (2 * arrPoints[holdIndex]) - arrPoints[holdIndex + 6];
                            } else {
                                // rowNo == 7, copy 1st point in col
                                holdIndex = colNo;
                                arrLoopPoints[loopPointsIndex] = arrPoints[holdIndex];
                            };
                        } else {
                            switch (loopPointsIndex) {
                                case 54:
                                    // mirror at diag opposite corner
                                    arrLoopPoints[loopPointsIndex]  = (2 * arrPoints[0]) - arrPoints[7];
                                    break;
                                case 55:
                                    // copy 1st point in row
                                    arrLoopPoints[loopPointsIndex] = arrLoopPoints[48];
                                    break;
                                case 62:
                                    // copy 1st point in col
                                    arrLoopPoints[loopPointsIndex] = arrLoopPoints[6];
                                    break;
                                case 63:
                                    // copy diag opposite corner
                                    arrLoopPoints[loopPointsIndex]  = arrPoints[0];
                                    break;
                                default:
                                    break;
                            };
                        }
                    };
                }; // end of: for (int colNo = 0; colNo < 8; colNo++)
            }; // end of: for (int rowNo = 0; rowNo < 8; rowNo++)

            // build surface with loop points
            surface.setControlPnts(arrLoopPoints);
            
        } else {
            // build surface with points
            surface.setControlPnts(arrPoints);
        };
        // end of if looping

        meshCentroid = surface.plane.getMesh().getCentroid();
        surface.plane.setPosition(copy_positionX * getMaxWidth(), copy_positionY * getMaxHeight(), copy_positionZ * getMaxDepth());
        surface.plane.setOrientation(TXFunctions::txGetRotateQuat(copy_rotateX * copy_rotateMultiply, copy_rotateY * copy_rotateMultiply, copy_rotateZ * copy_rotateMultiply));
        surface.plane.setScale(copy_scaleX, copy_scaleY, copy_scaleZ);

        sizeX = maxX - minX;
        sizeY = maxY - minY;
        sizeZ = maxZ - minZ;
        holdAnchorX = (meshCentroid.x + ((copy_anchorX - 0.5) * sizeX)) * copy_scaleX;
        holdAnchorY = (meshCentroid.y + ((copy_anchorY - 0.5) * sizeY)) * copy_scaleY;
        holdAnchorZ = (meshCentroid.z + ((copy_anchorZ - 0.5) * sizeZ)) * copy_scaleZ;

        // draw
        ofPushMatrix();
        material.begin();
        
        surface.plane.transformGL();
        surface.plane.resetTransform();
        ofTranslate(-holdAnchorX, -holdAnchorY, -holdAnchorZ);
        if (holdDrawWireframe) {
            surface.plane.drawWireframe();
        } else {
            surface.plane.draw();
        };
        surface.plane.restoreTransformGL();
        material.end();
        ofSetColor(255.0f);
        ofPopMatrix();

    }; // end of for all surfaces

    // unbind texture if valid
    if(useImageAsTexture && validTexture) {
        if (useExternalSourceImage) {
            int holdExtSourceID = getExtImageModuleIDSlot("extSourceImageModule");
            (* parentSystem->allModules[holdExtSourceID]->getTexture()).unbind();
        } else {
            sourceImage->getTexture().unbind();
        };
    };
}

////////

void TXDrawBSurfaces2::setupSurface() {
    // dimension is 6 for 36 points, or 8 for 64 points if looped
    int dimension;
    if (useLooping->getBool()) {
        dimension = 8;
    } else {
        dimension = 6;
    };
    surface.setup(getMaxWidth(), getMaxHeight(), dimension, surfaceResolution->getInt());
    surfaceHasChanged = false;
}

void TXDrawBSurfaces2::rebuildPresets() {
    for (int presetNo = 0; presetNo < totalUserPresets; presetNo++){
        for (int pointNo = 0; pointNo < totalCurvePoints; pointNo++){
            ofVec3f startPoint;
            ofVec3f holdPoint;
            // init
            if (initPresetsAsFlatPlane) {
                startPoint.x = planePreset[3 * pointNo];
                startPoint.y = planePreset[3 * pointNo + 1];
                startPoint.z = planePreset[3 * pointNo + 2];
            } else {
                startPoint.zero();
            };
            holdPoint = startPoint;
            // add offsets
            for (int offsetNo = 0; offsetNo < totalPresetBuilderOffsets; offsetNo++){
                holdPoint += arrPointOffsets[offsetNo].getOffset(presetNo, pointNo, startPoint, offsetDistortPointX, offsetDistortPointY, offsetDistortPointZ, offsetRandomSeed);
            };
            // assign
            arrUserPresets[presetNo][(pointNo * 3)] = holdPoint.x;
            arrUserPresets[presetNo][(pointNo * 3) + 1] = holdPoint.y;
            arrUserPresets[presetNo][(pointNo * 3) + 2] = holdPoint.z;
        };
    };
    rebuildPresetsRequested = false;
}


void TXDrawBSurfaces2::windowResized(int w, int h) {
    surfaceHasChanged = true;
}

ofVec3f TXDrawBSurfaces2::getSetData(int setIndexArg, int pointNoArg) {
    ofVec3f holdPoint;
    float * floatArrayPtr;
    if (setIndexArg == 0) {
        floatArrayPtr = planePreset; // set 0 is flat plane preset
    } else {
        floatArrayPtr = arrUserPresets[setIndexArg-1];  // sets 1-20 are user presets
    };
    holdPoint.x = floatArrayPtr[pointNoArg * 3];
    holdPoint.y = floatArrayPtr[(pointNoArg * 3) + 1];
    holdPoint.z = floatArrayPtr[(pointNoArg * 3) + 2];
    return holdPoint;
}

//////

void  TXDrawBSurfaces2::imageAssetSlotChanged(string slotNameArg) {
    if (slotNameArg == "sourceImageAsset") {
        sourceImageHasChanged = true;
    };
}

void  TXDrawBSurfaces2::useImageAsTextureChanged(bool & boolArg) {
    sourceImageHasChanged = true;
    surfaceHasChanged = true;
    retryMapTexture = true;
}

void  TXDrawBSurfaces2::useExternalSourceImageChanged(bool & boolArg) {
    sourceImageHasChanged = true;
    surfaceHasChanged = true;
    retryMapTexture = true;
}

void TXDrawBSurfaces2::loadSourceImage() {
    ofPtr <TXAsset> asset;
    string fileName;
    int sourceImageAssetID = getImageAssetIDSlot("sourceImageAsset").first;
    if (sourceImageAssetID != 0) {
        asset = parentSystem->getAsset(TXASSETTYPE_IMAGE, sourceImageAssetID);
        fileName = asset->getFileName();
        // old:
        // sourceImage.load(fileName);
        parentSystem->imageLoader.loadFromDisk(*newImage, fileName);
    };
}

bool TXDrawBSurfaces2::mapTextureToSurface() {
    ofTexture holdTexture;
    int holdExtSourceID;
    bool validTexture = false;

    retryMapTexture = false;
    // map texture if valid
    if(useImageAsTexture) {
        if (useExternalSourceImage) {
            holdExtSourceID = getExtImageModuleIDSlot("extSourceImageModule");
            if (holdExtSourceID == 0) {
                validTexture = false;
                retryMapTexture = true;
            } else {
                ofPtr<TXModuleBase> holdModule = parentSystem->allModules[holdExtSourceID];
                if (holdModule == NULL) {
                    validTexture = false;
                    retryMapTexture = true;
                } else {
                    if (holdModule->getTexture() == NULL) {
                        validTexture = false;
                        retryMapTexture = true;
                    } else {
                        holdTexture = * parentSystem->allModules[holdExtSourceID]->getTexture();
                        validTexture = true;
                    };
                };
            };
        } else {
            if (!sourceImage->getTexture().isAllocated()) {
                validTexture = false;
                retryMapTexture = true;
            } else {
                holdTexture = sourceImage->getTexture();
                validTexture = true;
            };
        };
        if (validTexture) {
            surface.plane.mapTexCoordsFromTexture(holdTexture);
        };
    };
    return validTexture;
}

int TXDrawBSurfaces2::getTextureWidth() {
    if (sourceImage->getTexture().isAllocated()) {
        return sourceImage->getWidth();
    } else {
        return 0;
    };
}

int TXDrawBSurfaces2::getTextureHeight() {
    if (sourceImage->getTexture().isAllocated()) {
        return sourceImage->getHeight();
    } else {
        return 0;
    };
}

ofTexture * TXDrawBSurfaces2::getTexture() {
    if (sourceImage->getTexture().isAllocated()) {
        return & sourceImage->getTexture();
    } else {
        return NULL;
    };
}

ofPixelsRef TXDrawBSurfaces2::getPixels() {
    return sourceImage->getPixels() ;
}

////////////

void  TXDrawBSurfaces2::message(string stringArg) {
    rebuildPresetsRequested = true;
}

void  TXDrawBSurfaces2::surfaceResolutionChanged(ofAbstractParameter & parameterArg) {
    surfaceHasChanged = true;
}

void  TXDrawBSurfaces2::useLoopingChanged(ofAbstractParameter & parameterArg) {
    surfaceHasChanged = true;
}

void  TXDrawBSurfaces2::presetsChangedBool(bool & inArg) {
    rebuildPresetsRequested = true;
}

void  TXDrawBSurfaces2::presetsChangedInt(int & inArg) {
    rebuildPresetsRequested = true;
}

void  TXDrawBSurfaces2::presetsChangedFloat(float & inArg) {
    rebuildPresetsRequested = true;
}
