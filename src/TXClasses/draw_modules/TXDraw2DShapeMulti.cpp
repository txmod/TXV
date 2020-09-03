/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXSystem.h"
#include "TXDraw2DShapeMulti.h"
#include "TXFunctions.h"

TXDraw2DShapeMulti::TXDraw2DShapeMulti() {
    setup();
}

// destructor
TXDraw2DShapeMulti::~TXDraw2DShapeMulti() {
}

void TXDraw2DShapeMulti::setup(){
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
    
    holdModParamIntArgs.name = "shapeType";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = total2DShapeTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = total2DShapeTypes - 1;
	shapeType = createModParameter(holdModParamIntArgs);
    parameters.add(shapeType->parameters);
    
    holdModParamIntArgs.name = "numCopies";
    holdModParamIntArgs.fixedValue = 6;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = maxCopies;
    holdModParamIntArgs.softMin = 1;
    holdModParamIntArgs.softMax = 20;
	numCopies = createModParameter(holdModParamIntArgs);
    parameters.add(numCopies->parameters);
    
    holdModParamIntArgs.name = "lineWidth";
    holdModParamIntArgs.fixedValue = 2;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 10;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 10;
    lineWidth = createModParameter(holdModParamIntArgs);
    parameters.add(lineWidth->parameters);
    
    holdModParamBoolArgs.name = "fillShape";
    holdModParamBoolArgs.fixedValue = true;
    holdModParamBoolArgs.fixedModMix = false;
	fillShape = createModParameter(holdModParamBoolArgs);
    parameters.add(fillShape->parameters);
    
    holdModParamFloatArgs.name = "width";
    holdModParamFloatArgs.fixedValue = 0.05;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	width = createModParameter(holdModParamFloatArgs);
    parameters.add(width->parameters);
    
    holdModParamFloatArgs.name = "widthEnd";
    holdModParamFloatArgs.fixedValue = 0.05;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	widthEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(widthEnd->parameters);
    
    parameters.add(widthEndIgnore.set("widthEndIgnore", true));
    
    holdModParamFloatArgs.name = "height";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	height = createModParameter(holdModParamFloatArgs);
    parameters.add(height->parameters);
    
    holdModParamFloatArgs.name = "heightEnd";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	heightEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(heightEnd->parameters);
    
    parameters.add(heightEndIgnore.set("heightEndIgnore", true));
    
    parameters.add(useMaxWidthToScaleHeight.set("useMaxWidthToScaleHeight", false));
    
    holdModParamFloatArgs.name = "roundness";
    holdModParamFloatArgs.fixedValue = 0.2;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    roundness = createModParameter(holdModParamFloatArgs);
    parameters.add(roundness->parameters);
    
    holdModParamFloatArgs.name = "roundnessEnd";
    holdModParamFloatArgs.fixedValue = 0.2;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    roundnessEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(roundnessEnd->parameters);
    
    parameters.add(roundnessEndIgnore.set("roundnessEndIgnore", true));
    
    holdModParamFloatArgs.name = "thickness";
    holdModParamFloatArgs.fixedValue = 0.2;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    thickness = createModParameter(holdModParamFloatArgs);
    parameters.add(thickness->parameters);
    
    holdModParamFloatArgs.name = "thicknessEnd";
    holdModParamFloatArgs.fixedValue = 0.2;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    thicknessEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(thicknessEnd->parameters);
    
    parameters.add(thicknessEndIgnore.set("thicknessEndIgnore", true));
    
    holdModParamIntArgs.name = "circleResolution";
    holdModParamIntArgs.fixedValue = 32;
    holdModParamIntArgs.hardMin = 3;
    holdModParamIntArgs.hardMax = 1024;
    holdModParamIntArgs.softMin = 3;
    holdModParamIntArgs.softMax = 128;
	circleResolution = createModParameter(holdModParamIntArgs);
    parameters.add(circleResolution->parameters);
    
    sizeSpreadCurve.setValueArrayToRamp(0, 1);
    sizeSpreadCurve.setName("sizeSpreadCurve");
    parameters.add(sizeSpreadCurve.parameters);
    
    sizeSpreadCurve2.setValueArrayToRamp(0, 1);
    sizeSpreadCurve2.setName("sizeSpreadCurve2");
    parameters.add(sizeSpreadCurve2.parameters);
    
    holdModParamFloatArgs.name = "sizeSpreadCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    sizeSpreadCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(sizeSpreadCurveMorph->parameters);
    
    holdModParamFloatArgs.name = "sizeSpreadCurvePhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    sizeSpreadCurvePhase = createModParameter(holdModParamFloatArgs);
    parameters.add(sizeSpreadCurvePhase->parameters);
    
    holdModParamFloatArgs.name = "colorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	colorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(colorHue->parameters);
    
    holdModParamFloatArgs.name = "colorHueEnd";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	colorHueEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(colorHueEnd->parameters);
    
    parameters.add(colorHueEndIgnore.set("colorHueEndIgnore", true));
    
    holdModParamFloatArgs.name = "colorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	colorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(colorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "colorSaturation";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	colorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(colorSaturation->parameters);
    
    holdModParamFloatArgs.name = "colorSaturationEnd";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	colorSaturationEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(colorSaturationEnd->parameters);
    
    parameters.add(colorSaturationEndIgnore.set("colorSaturationEndIgnore", true));
    
    holdModParamFloatArgs.name = "colorBrightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	colorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(colorBrightness->parameters);
    
    holdModParamFloatArgs.name = "colorBrightnessEnd";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	colorBrightnessEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(colorBrightnessEnd->parameters);
    
    parameters.add(colorBrightnessEndIgnore.set("colorBrightnessEndIgnore", true));
    
    holdModParamFloatArgs.name = "colorAlpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	colorAlpha = createModParameter(holdModParamFloatArgs);
    parameters.add(colorAlpha->parameters);
    
    holdModParamFloatArgs.name = "colorAlphaEnd";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	colorAlphaEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(colorAlphaEnd->parameters);
    
    parameters.add(colorAlphaEndIgnore.set("colorAlphaEndIgnore", true));
    
    holdModParamBoolArgs.name = "colorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	colorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(colorHSBAsRGB->parameters);
    
    holdModParamBoolArgs.name = "useFillColorForLineColor";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
    useFillColorForLineColor = createModParameter(holdModParamBoolArgs);
    parameters.add(useFillColorForLineColor->parameters);
    
    holdModParamBoolArgs.name = "swapFillColorAndLineColor";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
    swapFillColorAndLineColor = createModParameter(holdModParamBoolArgs);
    parameters.add(swapFillColorAndLineColor->parameters);
    
    holdModParamFloatArgs.name = "lineColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    lineColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(lineColorHue->parameters);
    
    holdModParamFloatArgs.name = "lineColorHueEnd";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    lineColorHueEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(lineColorHueEnd->parameters);
    
    parameters.add(lineColorHueEndIgnore.set("lineColorHueEndIgnore", true));
    
    holdModParamFloatArgs.name = "lineColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    lineColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(lineColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "lineColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    lineColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(lineColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "lineColorSaturationEnd";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    lineColorSaturationEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(lineColorSaturationEnd->parameters);
    
    parameters.add(lineColorSaturationEndIgnore.set("lineColorSaturationEndIgnore", true));
    
    holdModParamFloatArgs.name = "lineColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    lineColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(lineColorBrightness->parameters);
    
    holdModParamFloatArgs.name = "lineColorBrightnessEnd";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    lineColorBrightnessEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(lineColorBrightnessEnd->parameters);
    
    parameters.add(lineColorBrightnessEndIgnore.set("lineColorBrightnessEndIgnore", true));
    
    holdModParamFloatArgs.name = "lineColorAlpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    lineColorAlpha = createModParameter(holdModParamFloatArgs);
    parameters.add(lineColorAlpha->parameters);
    
    holdModParamFloatArgs.name = "lineColorAlphaEnd";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    lineColorAlphaEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(lineColorAlphaEnd->parameters);
    
    parameters.add(lineColorAlphaEndIgnore.set("lineColorAlphaEndIgnore", true));
    
    holdModParamBoolArgs.name = "lineColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
    lineColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(lineColorHSBAsRGB->parameters);
    
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
    
    holdModParamFloatArgs.name = "colorSpreadCurvePhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    colorSpreadCurvePhase = createModParameter(holdModParamFloatArgs);
    parameters.add(colorSpreadCurvePhase->parameters);
    
    holdModParamFloatArgs.name = "centrePositionX";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	centrePositionX = createModParameter(holdModParamFloatArgs);
    parameters.add(centrePositionX->parameters);
    
    holdModParamFloatArgs.name = "centrePositionY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	centrePositionY = createModParameter(holdModParamFloatArgs);
    parameters.add(centrePositionY->parameters);
    
    holdModParamFloatArgs.name = "positionX";
    holdModParamFloatArgs.fixedValue = -0.3;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
	positionX = createModParameter(holdModParamFloatArgs);
    parameters.add(positionX->parameters);
    
    holdModParamFloatArgs.name = "positionXEnd";
    holdModParamFloatArgs.fixedValue = 0.3;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
	positionXEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(positionXEnd->parameters);
    
    parameters.add(positionXEndIgnore.set("positionXEndIgnore", false));
    
    holdModParamFloatArgs.name = "positionY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
	positionY = createModParameter(holdModParamFloatArgs);
    parameters.add(positionY->parameters);
    
    holdModParamFloatArgs.name = "positionYEnd";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
	positionYEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(positionYEnd->parameters);
    
    parameters.add(positionYEndIgnore.set("positionYEndIgnore", true));
    
    positionXSpreadCurve.setValueArrayToRamp(0, 1);
    positionXSpreadCurve.setName("positionXSpreadCurve");
    parameters.add(positionXSpreadCurve.parameters);
    
    positionXSpreadCurve2.setValueArrayToRamp(0, 1);
    positionXSpreadCurve2.setName("positionXSpreadCurve2");
    parameters.add(positionXSpreadCurve2.parameters);
    
    holdModParamFloatArgs.name = "positionXSpreadCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    positionXSpreadCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(positionXSpreadCurveMorph->parameters);
    
    holdModParamFloatArgs.name = "positionXSpreadCurvePhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    positionXSpreadCurvePhase = createModParameter(holdModParamFloatArgs);
    parameters.add(positionXSpreadCurvePhase->parameters);
    
    parameters.add(usePosXSpreadCurveForPosY.set("usePosXSpreadCurveForPosY", false));

    positionYSpreadCurve.setValueArrayToRamp(0, 1);
    positionYSpreadCurve.setName("positionYSpreadCurve");
    parameters.add(positionYSpreadCurve.parameters);
    
    positionYSpreadCurve2.setValueArrayToRamp(0, 1);
    positionYSpreadCurve2.setName("positionYSpreadCurve2");
    parameters.add(positionYSpreadCurve2.parameters);
    
    holdModParamFloatArgs.name = "positionYSpreadCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    positionYSpreadCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(positionYSpreadCurveMorph->parameters);
    
    holdModParamFloatArgs.name = "positionYSpreadCurvePhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    positionYSpreadCurvePhase = createModParameter(holdModParamFloatArgs);
    parameters.add(positionYSpreadCurvePhase->parameters);
    
    holdModParamFloatArgs.name = "rotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	rotate = createModParameter(holdModParamFloatArgs);
    parameters.add(rotate->parameters);
    
    holdModParamFloatArgs.name = "rotateEnd";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	rotateEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateEnd->parameters);
    
    parameters.add(rotateEndIgnore.set("rotateEndIgnore", true));
    
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
    
    holdModParamFloatArgs.name = "rotateSpreadCurvePhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    rotateSpreadCurvePhase = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateSpreadCurvePhase->parameters);
    
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
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 3.0;
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
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 3.0;
	anchorYEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorYEnd->parameters);
    
    parameters.add(anchorYEndIgnore.set("anchorYEndIgnore", true));
    
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
    
    holdModParamFloatArgs.name = "anchorSpreadCurvePhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    anchorSpreadCurvePhase = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorSpreadCurvePhase->parameters);
    
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
    
    parameters.add(useScaleXForScaleY.set("useScaleXForScaleY", false));
    
    scaleXSpreadCurve.setValueArrayToRamp(0, 1);
    scaleXSpreadCurve.setName("scaleXSpreadCurve");
    parameters.add(scaleXSpreadCurve.parameters);
    
    scaleXSpreadCurve2.setValueArrayToRamp(0, 1);
    scaleXSpreadCurve2.setName("scaleXSpreadCurve2");
    parameters.add(scaleXSpreadCurve2.parameters);
    
    holdModParamFloatArgs.name = "scaleXSpreadCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    scaleXSpreadCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleXSpreadCurveMorph->parameters);
    
    holdModParamFloatArgs.name = "scaleXSpreadCurvePhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    scaleXSpreadCurvePhase = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleXSpreadCurvePhase->parameters);
    
    parameters.add(useScaleXSpreadCurveForScaleY.set("useScaleXSpreadCurveForScaleY", false));
    
    scaleYSpreadCurve.setValueArrayToRamp(0, 1);
    scaleYSpreadCurve.setName("scaleYSpreadCurve");
    parameters.add(scaleYSpreadCurve.parameters);
    
    scaleYSpreadCurve2.setValueArrayToRamp(0, 1);
    scaleYSpreadCurve2.setName("scaleYSpreadCurve2");
    parameters.add(scaleYSpreadCurve2.parameters);
    
    holdModParamFloatArgs.name = "scaleYSpreadCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    scaleYSpreadCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleYSpreadCurveMorph->parameters);
    
    holdModParamFloatArgs.name = "scaleYSpreadCurvePhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    scaleYSpreadCurvePhase = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleYSpreadCurvePhase->parameters);
    
}

void TXDraw2DShapeMulti::draw(){
    ofColor holdFillColor, holdLineColor;
    bool holdIsFilled;
    int keepRectMode = ofGetRectMode();
    int defaultCircleResolution = 32;
    
    if (!drawActive->getBool()) {
        return;
    };
    if (fillShape->getBool()) {
        ofFill();
        holdIsFilled = true;
    } else {
        ofNoFill();
        holdIsFilled = false;
    };
    int holdShapeType = shapeType->getInt();
    int holdNumCopies = numCopies->getInt();
    int holdLineWidth = lineWidth->getInt();
    
    int maxWidth =  getMaxWidth();
    int maxHeight =  getMaxHeight();
    
    float copyWidth;
    float copyHeight;
    float copyRoundness;
    float copyThickness;
    float copyFillColorHue;
    float copyFillColorSaturation;
    float copyFillColorBrightness;
    float copyFillColorAlpha;
    float copyLineColorHue;
    float copyLineColorSaturation;
    float copyLineColorBrightness;
    float copyLineColorAlpha;
    float copyPositionX;
    float copyPositionY;
    float copyRotate;
    float copyRotateMultiply;
    float copyAnchorX;
    float copyAnchorY;
    float copyScaleX;
    float copyScaleY;
    
    float holdWidth;
    float holdHeight;
    float holdroundness;
    float holdthickness;
    int   holdCircleResolution;
    float holdFillColorHue = colorHue->getFloat();
    float holdFillColorHueRotate = colorHueRotate->getFloat();
    float holdFillColorSaturation = colorSaturation->getFloat();
    float holdFillColorBrightness = colorBrightness->getFloat();
    float holdFillColorAlpha = colorAlpha->getFloat();
    float holdFillColorHSBAsRGB = colorHSBAsRGB->getBool();
    float holdLineColorHue = lineColorHue->getFloat();
    float holdLineColorHueRotate = lineColorHueRotate->getFloat();
    float holdLineColorSaturation = lineColorSaturation->getFloat();
    float holdLineColorBrightness = lineColorBrightness->getFloat();
    float holdLineColorAlpha = lineColorAlpha->getFloat();
    float holdLineColorHSBAsRGB = lineColorHSBAsRGB->getBool();
    float holdCentrePositionX = centrePositionX->getFloat();
    float holdCentrePositionY = centrePositionY->getFloat();
    float holdPositionX = positionX->getFloat();
    float holdPositionY = positionY->getFloat();
    float holdRotate = rotate->getFloat();
    float holdRotateMultiply = rotateMultiply->getFloat();
    float holdAnchorX = anchorX->getFloat();
    float holdAnchorY = anchorY->getFloat();
    float holdScaleX = scaleX->getFloat();
    float holdScaleY = scaleY->getFloat();
    
    float holdWidthEnd;
    float holdHeightEnd;
    float holdroundnessEnd;
    float holdthicknessEnd;
    float holdFillColorHueEnd;
    float holdFillColorSaturationEnd;
    float holdFillColorBrightnessEnd;
    float holdFillColorAlphaEnd;
    float holdLineColorHueEnd;
    float holdLineColorSaturationEnd;
    float holdLineColorBrightnessEnd;
    float holdLineColorAlphaEnd;
    float holdPositionXEnd;
    float holdPositionYEnd;
    float holdRotateEnd;
    float holdRotateMultiplyEnd;
    float holdAnchorXEnd;
    float holdAnchorYEnd;
    float holdScaleXEnd;
    float holdScaleYEnd;
    
    bool holdUseFillColorForLineColor = useFillColorForLineColor->getBool();
    bool holdSwapFillColorAndLineColor = swapFillColorAndLineColor->getBool();

    float holdSizeSpreadCurveMorph = sizeSpreadCurveMorph->getFloat();
    float holdColorSpreadCurveMorph = colorSpreadCurveMorph->getFloat();
    float holdPosXSpreadCurveMorph = positionXSpreadCurveMorph->getFloat();
    float holdPosYSpreadCurveMorph = positionYSpreadCurveMorph->getFloat();
    float holdRotateSpreadCurveMorph = rotateSpreadCurveMorph->getFloat();
    float holdAnchorSpreadCurveMorph = anchorSpreadCurveMorph->getFloat();
    float holdScaleXSpreadCurveMorph = scaleXSpreadCurveMorph->getFloat();
    float holdScaleYSpreadCurveMorph = scaleYSpreadCurveMorph->getFloat();
    
    float holdSizeSpreadCurvePhase = sizeSpreadCurvePhase->getFloat();
    float holdColorSpreadCurvePhase = colorSpreadCurvePhase->getFloat();
    float holdPosXSpreadCurvePhase = positionXSpreadCurvePhase->getFloat();
    float holdPosYSpreadCurvePhase = positionYSpreadCurvePhase->getFloat();
    float holdRotateSpreadCurvePhase = rotateSpreadCurvePhase->getFloat();
    float holdAnchorSpreadCurvePhase = anchorSpreadCurvePhase->getFloat();
    float holdScaleXSpreadCurvePhase = scaleXSpreadCurvePhase->getFloat();
    float holdScaleYSpreadCurvePhase = scaleYSpreadCurvePhase->getFloat();
    
    bool heightUsed;
    bool roundnessUsed;
    bool thicknessUsed;
    bool circleResolutionUsed;
    
    switch (holdShapeType) {
        case TX2DSHAPETYPE_CIRCLE:
            heightUsed = false;
            roundnessUsed = false;
            thicknessUsed = false;
            circleResolutionUsed = true;
            break;
        case TX2DSHAPETYPE_ELLIPSE:
            heightUsed = true;
            roundnessUsed = false;
            thicknessUsed = false;
            circleResolutionUsed = true;
            break;
        case TX2DSHAPETYPE_SQUARE:
            heightUsed = false;
            roundnessUsed = false;
            thicknessUsed = false;
            circleResolutionUsed = false;
            break;
        case TX2DSHAPETYPE_RECTANGLE:
            heightUsed = true;
            roundnessUsed = false;
            thicknessUsed = false;
            circleResolutionUsed = false;
            break;
        case TX2DSHAPETYPE_ROUNDRECTANGLE:
            heightUsed = true;
            roundnessUsed = true;
            thicknessUsed = false;
            circleResolutionUsed = true;
            break;
        case TX2DSHAPETYPE_STAR:
            heightUsed = true;
            roundnessUsed = false;
            thicknessUsed = false;
            circleResolutionUsed = true;
            break;
        case TX2DSHAPETYPE_ISOSCELES_TRIANGLE:
            heightUsed = true;
            roundnessUsed = false;
            thicknessUsed = false;
            circleResolutionUsed = false;
            break;
        case TX2DSHAPETYPE_RIGHT_TRIANGLE:
            heightUsed = true;
            roundnessUsed = false;
            thicknessUsed = false;
            circleResolutionUsed = false;
            break;
        case TX2DSHAPETYPE_DIAMOND:
            heightUsed = true;
            roundnessUsed = false;
            thicknessUsed = false;
            circleResolutionUsed = false;
            break;
        case TX2DSHAPETYPE_CRESCENT:
            heightUsed = true;
            roundnessUsed = false;
            thicknessUsed = true;
            circleResolutionUsed = true;
            break;
        case TX2DSHAPETYPE_RING:
            heightUsed = false;
            roundnessUsed = false;
            thicknessUsed = true;
            circleResolutionUsed = true;
            break;
        default:
            heightUsed = false;
            roundnessUsed = false;
            circleResolutionUsed = true;
            break;
    }

    holdWidth = width->getFloat();
    if (heightUsed) {
        holdHeight = height->getFloat();
    };
    if (roundnessUsed) {
        holdroundness = roundness->getFloat();
        if (!roundnessEndIgnore) {
            holdroundnessEnd = roundnessEnd->getFloat();
        };
    };
    if (thicknessUsed) {
        holdthickness = thickness->getFloat();
        if (!thicknessEndIgnore) {
            holdthicknessEnd = thicknessEnd->getFloat();
        };
    };
    if (circleResolutionUsed) {
        holdCircleResolution = circleResolution->getInt();
    };


    if (!widthEndIgnore) {
        holdWidthEnd = widthEnd->getFloat();
    };
    if (heightUsed) {
        if (!heightEndIgnore) {
            holdHeightEnd = heightEnd->getFloat();
        };
    };
    
    if (!lineColorHueEndIgnore) {
        holdLineColorHueEnd = lineColorHueEnd->getFloat();
    };
    if (!lineColorSaturationEndIgnore) {
        holdLineColorSaturationEnd = lineColorSaturationEnd->getFloat();
    };
    if (!lineColorBrightnessEndIgnore) {
        holdLineColorBrightnessEnd = lineColorBrightnessEnd->getFloat();
    };
    if (!lineColorAlphaEndIgnore) {
        holdLineColorAlphaEnd = lineColorAlphaEnd->getFloat();
    };
    
    if (!colorHueEndIgnore) {
        holdFillColorHueEnd = colorHueEnd->getFloat();
    };
    if (!colorSaturationEndIgnore) {
        holdFillColorSaturationEnd = colorSaturationEnd->getFloat();
    };
    if (!colorBrightnessEndIgnore) {
        holdFillColorBrightnessEnd = colorBrightnessEnd->getFloat();
    };
    if (!colorAlphaEndIgnore) {
        holdFillColorAlphaEnd = colorAlphaEnd->getFloat();
    };
    
    if (!positionXEndIgnore) {
        holdPositionXEnd = positionXEnd->getFloat();
    };
    if (!positionYEndIgnore) {
        holdPositionYEnd = positionYEnd->getFloat();
    };
    if (!rotateEndIgnore) {
        holdRotateEnd = rotateEnd->getFloat();
    };
    if (!rotateMultiplyEndIgnore) {
        holdRotateMultiplyEnd = rotateMultiplyEnd->getFloat();
    };
    if (!anchorXEndIgnore) {
        holdAnchorXEnd = anchorXEnd->getFloat();
    };
    if (!anchorYEndIgnore) {
        holdAnchorYEnd = anchorYEnd->getFloat();
    };
    if (!scaleXEndIgnore) {
        holdScaleXEnd = scaleXEnd->getFloat();
    };
    if (!useScaleXForScaleY) {
        if (!scaleYEndIgnore) {
            holdScaleYEnd = scaleYEnd->getFloat();
        };
    };
        
    // draw copies in reverse order
    for (int ind = 0; ind < holdNumCopies; ind++) {
        int copyNo = holdNumCopies - 1 - ind;
        float proportion;
        if (holdNumCopies < 2) {
            proportion = 0.5;
        } else {
            proportion = (float) (0.5 + copyNo) / holdNumCopies;
        };
        float sizeSpreadProportion =  TXFunctions::getInterpPhaseCurves(sizeSpreadCurve, sizeSpreadCurve2, proportion,
                                                                        holdSizeSpreadCurvePhase, holdSizeSpreadCurveMorph);
        float colorSpreadProportion =  TXFunctions::getInterpPhaseCurves(colorSpreadCurve, colorSpreadCurve2, proportion,
                                                                         holdColorSpreadCurvePhase, holdColorSpreadCurveMorph);
        float positionXSpreadProportion =  TXFunctions::getInterpPhaseCurves(positionXSpreadCurve, positionXSpreadCurve2, proportion,
                                                                             holdPosXSpreadCurvePhase, holdPosXSpreadCurveMorph);
        float positionYSpreadProportion =  TXFunctions::getInterpPhaseCurves(positionYSpreadCurve, positionYSpreadCurve2, proportion,
                                                                             holdPosYSpreadCurvePhase, holdPosYSpreadCurveMorph);
        float rotateSpreadProportion =  TXFunctions::getInterpPhaseCurves(rotateSpreadCurve, rotateSpreadCurve2, proportion,
                                                                          holdRotateSpreadCurvePhase, holdRotateSpreadCurveMorph);
        float anchorSpreadProportion =  TXFunctions::getInterpPhaseCurves(anchorSpreadCurve, anchorSpreadCurve2, proportion,
                                                                          holdAnchorSpreadCurvePhase, holdAnchorSpreadCurveMorph);
        float scaleXSpreadProportion =  TXFunctions::getInterpPhaseCurves(scaleXSpreadCurve, scaleXSpreadCurve2, proportion,
                                                                          holdScaleXSpreadCurvePhase, holdScaleXSpreadCurveMorph);
        float scaleYSpreadProportion =  TXFunctions::getInterpPhaseCurves(scaleYSpreadCurve, scaleYSpreadCurve2, proportion,
                                                                          holdScaleYSpreadCurvePhase, holdScaleYSpreadCurveMorph);
        float shapeWidth, shapeHeight, shapeRoundness;
        int shapeResolution;

        if (colorHueEndIgnore) {
            copyFillColorHue = holdFillColorHue;
        } else {
            copyFillColorHue = TXFunctions::getInterp(holdFillColorHue, holdFillColorHueEnd, colorSpreadProportion);
        };
        if (colorSaturationEndIgnore) {
            copyFillColorSaturation = holdFillColorSaturation;
        } else {
            copyFillColorSaturation = TXFunctions::getInterp(holdFillColorSaturation, holdFillColorSaturationEnd, colorSpreadProportion);
        };
        if (colorBrightnessEndIgnore) {
            copyFillColorBrightness = holdFillColorBrightness;
        } else {
            copyFillColorBrightness = TXFunctions::getInterp(holdFillColorBrightness, holdFillColorBrightnessEnd, colorSpreadProportion);
        };
        if (colorAlphaEndIgnore) {
            copyFillColorAlpha = holdFillColorAlpha;
        } else {
            copyFillColorAlpha = TXFunctions::getInterp(holdFillColorAlpha, holdFillColorAlphaEnd, colorSpreadProportion);
        };
        
        if (lineColorHueEndIgnore) {
            copyLineColorHue = holdLineColorHue;
        } else {
            copyLineColorHue = TXFunctions::getInterp(holdLineColorHue, holdLineColorHueEnd, colorSpreadProportion);
        };
        if (lineColorSaturationEndIgnore) {
            copyLineColorSaturation = holdLineColorSaturation;
        } else {
            copyLineColorSaturation = TXFunctions::getInterp(holdLineColorSaturation, holdLineColorSaturationEnd, colorSpreadProportion);
        };
        if (lineColorBrightnessEndIgnore) {
            copyLineColorBrightness = holdLineColorBrightness;
        } else {
            copyLineColorBrightness = TXFunctions::getInterp(holdLineColorBrightness, holdLineColorBrightnessEnd, colorSpreadProportion);
        };
        if (lineColorAlphaEndIgnore) {
            copyLineColorAlpha = holdLineColorAlpha;
        } else {
            copyLineColorAlpha = TXFunctions::getInterp(holdLineColorAlpha, holdLineColorAlphaEnd, colorSpreadProportion);
        };
        
        holdFillColor = TXFunctions::txGetColor(copyFillColorHue, copyFillColorSaturation, copyFillColorBrightness, copyFillColorAlpha, holdFillColorHueRotate, holdFillColorHSBAsRGB);

        if (holdUseFillColorForLineColor) {
            holdLineColor =  holdFillColor;
        } else {
            if (holdSwapFillColorAndLineColor) {
                holdLineColor =  holdFillColor;
                holdFillColor =  TXFunctions::txGetColor(copyLineColorHue, copyLineColorSaturation, copyLineColorBrightness, copyLineColorAlpha, holdLineColorHueRotate, holdLineColorHSBAsRGB);
            } else {
                holdLineColor =  TXFunctions::txGetColor(copyLineColorHue, copyLineColorSaturation, copyLineColorBrightness, copyLineColorAlpha, holdLineColorHueRotate, holdLineColorHSBAsRGB);
            };
        };
    
        if (widthEndIgnore) {
            copyWidth = holdWidth;
        } else {
            copyWidth = TXFunctions::getInterp(holdWidth, holdWidthEnd, sizeSpreadProportion);
        };
        if (heightUsed) {
            if (heightEndIgnore) {
                copyHeight = holdHeight;
            } else {
                copyHeight = TXFunctions::getInterp(holdHeight, holdHeightEnd, sizeSpreadProportion);
            };
        };
        if (roundnessUsed) {
            if (roundnessEndIgnore) {
                copyRoundness = holdroundness;
            } else {
                copyRoundness = TXFunctions::getInterp(holdroundness, holdroundnessEnd, sizeSpreadProportion);
            };
        };
        if (thicknessUsed) {
            if (thicknessEndIgnore) {
                copyThickness = holdthickness;
            } else {
                copyThickness = TXFunctions::getInterp(holdthickness, holdthicknessEnd, sizeSpreadProportion);
            };
        };
        
        
        if (positionXEndIgnore) {
            copyPositionX = holdPositionX;
        } else {
            copyPositionX = TXFunctions::getInterp(holdPositionX, holdPositionXEnd, positionXSpreadProportion);
        };
        if (positionYEndIgnore) {
            copyPositionY = holdPositionY;
        } else {
            if (usePosXSpreadCurveForPosY) {
                copyPositionY = TXFunctions::getInterp(holdPositionY, holdPositionYEnd, positionXSpreadProportion);
            } else {
                copyPositionY = TXFunctions::getInterp(holdPositionY, holdPositionYEnd, positionYSpreadProportion);
            };
        };
        if (rotateEndIgnore) {
            copyRotate = holdRotate;
        } else {
            copyRotate = TXFunctions::getInterp(holdRotate, holdRotateEnd, rotateSpreadProportion);
        };
        if (rotateMultiplyEndIgnore) {
            copyRotateMultiply = holdRotateMultiply;
        } else {
            copyRotateMultiply = TXFunctions::getInterp(holdRotateMultiply, holdRotateMultiplyEnd, rotateSpreadProportion);
        };
        if (anchorXEndIgnore) {
            copyAnchorX = holdAnchorX;
        } else {
            copyAnchorX = TXFunctions::getInterp(holdAnchorX, holdAnchorXEnd, anchorSpreadProportion);
        };
        if (anchorYEndIgnore) {
            copyAnchorY = holdAnchorY;
        } else {
            copyAnchorY = TXFunctions::getInterp(holdAnchorY, holdAnchorYEnd, anchorSpreadProportion);
        };
        if (scaleXEndIgnore) {
            copyScaleX = holdScaleX;
        } else {
            copyScaleX = TXFunctions::getInterp(holdScaleX, holdScaleXEnd, scaleXSpreadProportion);
        };
        if (useScaleXForScaleY) {
            copyScaleY = copyScaleX;
        } else {
            if (scaleYEndIgnore) {
                copyScaleY = holdScaleY;
            } else {
                if (useScaleXSpreadCurveForScaleY) {
                    copyScaleY = TXFunctions::getInterp(holdScaleY, holdScaleYEnd, scaleXSpreadProportion);
                } else {
                    copyScaleY = TXFunctions::getInterp(holdScaleY, holdScaleYEnd, scaleYSpreadProportion);
                };
            };
        };

        shapeWidth = copyWidth * maxWidth;
        if (heightUsed) {
            float heightScale;
            if (useMaxWidthToScaleHeight) {
                heightScale = maxWidth;
            } else {
                heightScale = maxHeight;
            };
            shapeHeight = copyHeight * heightScale;
        } else {
            shapeHeight = shapeWidth;
        };
        // scale anchor to shape size
        if (holdShapeType == TX2DSHAPETYPE_STAR) {
            float starSize = max(shapeWidth, shapeHeight);
            copyAnchorX = (copyAnchorX - 0.5) * starSize;
            copyAnchorY = (copyAnchorY - 0.5) * starSize;
        } else {
            copyAnchorX = (copyAnchorX - 0.5) * shapeWidth;
            copyAnchorY = (copyAnchorY - 0.5) * shapeHeight;
        };

        // transform
        ofPushMatrix();
        ofTranslate((holdCentrePositionX + copyPositionX) * maxWidth, (holdCentrePositionY + copyPositionY) * maxHeight, 0.0f);
        ofRotateZ(copyRotateMultiply * copyRotate);
        ofScale(copyScaleX, copyScaleY, 1.0f);

        // draw
        ofEnableAlphaBlending();
        switch (holdShapeType) {
            case TX2DSHAPETYPE_CIRCLE:
                shape.drawEllipse(shapeWidth, shapeWidth, holdCircleResolution, holdFillColor, holdLineColor, holdLineWidth, holdIsFilled, copyAnchorX, copyAnchorY);
                break;
            case TX2DSHAPETYPE_ELLIPSE:
                shape.drawEllipse(shapeWidth, shapeHeight, holdCircleResolution, holdFillColor, holdLineColor, holdLineWidth, holdIsFilled, copyAnchorX, copyAnchorY);
                break;
            case TX2DSHAPETYPE_SQUARE:
                shape.drawRectangle(shapeWidth, shapeWidth, holdFillColor, holdLineColor, holdLineWidth, holdIsFilled, copyAnchorX, copyAnchorY);
                break;
            case TX2DSHAPETYPE_RECTANGLE:
                shape.drawRectangle(shapeWidth, shapeHeight, holdFillColor, holdLineColor, holdLineWidth, holdIsFilled, copyAnchorX, copyAnchorY);
                break;
            case TX2DSHAPETYPE_ROUNDRECTANGLE:
                shapeRoundness = copyRoundness * min(shapeWidth, shapeHeight) * 0.5;
                shapeResolution = holdCircleResolution * 4;
                shape.drawRoundRectangle(shapeWidth, shapeHeight, shapeRoundness, shapeResolution, holdFillColor, holdLineColor, holdLineWidth, holdIsFilled, copyAnchorX, copyAnchorY);
                break;
            case TX2DSHAPETYPE_STAR:
                shape.drawStar(shapeWidth, shapeHeight, holdCircleResolution, holdFillColor, holdLineColor, holdLineWidth, holdIsFilled, copyAnchorX, copyAnchorY);
                break;
            case TX2DSHAPETYPE_ISOSCELES_TRIANGLE:
                shape.drawIsoscelesTriangle(shapeWidth, shapeHeight, holdFillColor, holdLineColor, holdLineWidth, holdIsFilled, copyAnchorX, copyAnchorY);
                break;
            case TX2DSHAPETYPE_RIGHT_TRIANGLE:
                shape.drawRightTriangle(shapeWidth, shapeHeight, holdFillColor, holdLineColor, holdLineWidth, holdIsFilled, copyAnchorX, copyAnchorY);
                break;
            case TX2DSHAPETYPE_DIAMOND:
                shape.drawDiamond(shapeWidth, shapeHeight, holdFillColor, holdLineColor, holdLineWidth, holdIsFilled, copyAnchorX, copyAnchorY);
                break;
            case TX2DSHAPETYPE_CRESCENT:
                shape.drawCrescent(shapeWidth, shapeHeight, holdCircleResolution, copyThickness, holdFillColor, holdLineColor, holdLineWidth, holdIsFilled, copyAnchorX, copyAnchorY);
                break;
            case TX2DSHAPETYPE_RING:
                shape.drawRing(shapeWidth, holdCircleResolution, copyThickness, holdFillColor, holdLineColor, holdLineWidth, holdIsFilled, copyAnchorX, copyAnchorY);
                break;
            default:
                shape.drawEllipse(shapeWidth, shapeWidth, holdCircleResolution, holdFillColor, holdLineColor, holdLineWidth, holdIsFilled, copyAnchorX, copyAnchorY);
                break;
        }
        ofDisableAlphaBlending();
        
        ofPopMatrix();
        ofSetColor(255.0f);
    };
}

//void TXDraw2DShapeMulti::drawStar(float & argRadius1, float & argRadius2, int & argNumPoints, ofColor & argColor, bool & argIsFilled, float & argAnchorX, float & argAnchorY){
//    ofPoint holdPoint;
//    float holdRadius;
//    float twoPIPhase;
//    int totalPoints = argNumPoints * 2;
//    
//    holdStar.clear();
//    
//    for (int i=0; i<totalPoints; i++){
//        twoPIPhase = TWO_PI *  (i+1) / totalPoints;
//        if ((i % 2) == 0) {
//            holdRadius = argRadius1;
//        } else {
//            holdRadius = argRadius2;
//        };
//        holdPoint.set(holdRadius * sin(twoPIPhase), holdRadius * cos(twoPIPhase));
//        if (i == 0) {
//            holdStar.moveTo(holdPoint);
//        } else {
//            holdStar.lineTo(holdPoint);
//        }
//	}
//    holdStar.close();
//    holdStar.setColor(argColor);
//    holdStar.setFilled(argIsFilled);
//    holdStar.draw(-argAnchorX, -argAnchorY);
//}
//
