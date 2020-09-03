/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXDrawDelayCurves.h"
#include "TXFunctions.h"
#include "TXSystem.h"

TXDrawDelayCurves::TXDrawDelayCurves() {
    setup();
}

void TXDrawDelayCurves::setup(){
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
    
    holdModParamIntArgs.name = "delayFrames";
    holdModParamIntArgs.fixedValue = 60;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = maxDelayFrames;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = maxDelayFrames;
	delayFrames = createModParameter(holdModParamIntArgs);
    parameters.add(delayFrames->parameters);
    
    holdModParamIntArgs.name = "curveType";
    holdModParamIntArgs.fixedValue = TX2DCURVETYPE_AUTOCURVE;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = total2DcurveTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = total2DcurveTypes - 1;
	curveType = createModParameter(holdModParamIntArgs);
    parameters.add(curveType->parameters);
    
    holdModParamIntArgs.name = "numPoints";
    holdModParamIntArgs.fixedValue = 2;
    holdModParamIntArgs.hardMin = 2;
    holdModParamIntArgs.hardMax = maxCurvePoints;
    holdModParamIntArgs.softMin = 2;
    holdModParamIntArgs.softMax = maxCurvePoints;
    numPoints = createModParameter(holdModParamIntArgs);
    parameters.add(numPoints->parameters);
    
    holdModParamIntArgs.name = "numCurves";
    holdModParamIntArgs.fixedValue = 4;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = maxCurves;
    holdModParamIntArgs.softMin = 1;
    holdModParamIntArgs.softMax = 100;
	numCurves = createModParameter(holdModParamIntArgs);
    parameters.add(numCurves->parameters);
    
    holdModParamIntArgs.name = "lineWidth";
    holdModParamIntArgs.fixedValue = 1;
    holdModParamIntArgs.hardMin = 1;
    holdModParamIntArgs.hardMax = 100;
    holdModParamIntArgs.softMin = 1;
    holdModParamIntArgs.softMax = 100;
    lineWidth = createModParameter(holdModParamIntArgs);
    parameters.add(lineWidth->parameters);
    
    holdModParamBoolArgs.name = "autoClose";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	autoClose = createModParameter(holdModParamBoolArgs);
    parameters.add(autoClose->parameters);
    
    holdModParamBoolArgs.name = "fillShape";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	fillShape = createModParameter(holdModParamBoolArgs);
    parameters.add(fillShape->parameters);
    
    holdModParamIntArgs.name = "windingMode";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 1;
    windingMode = createModParameter(holdModParamIntArgs);
    parameters.add(windingMode->parameters);
    
    holdModParamIntArgs.name = "curveResolution";
    holdModParamIntArgs.fixedValue = 64;
    holdModParamIntArgs.hardMin = 2;
    holdModParamIntArgs.hardMax = 1024;
    holdModParamIntArgs.softMin = 2;
    holdModParamIntArgs.softMax = 128;
	curveResolution = createModParameter(holdModParamIntArgs);
    parameters.add(curveResolution->parameters);
    
    holdModParamBoolArgs.name = "reverseCurveOrder";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
    reverseCurveOrder = createModParameter(holdModParamBoolArgs);
    parameters.add(reverseCurveOrder->parameters);
    
    holdModParamBoolArgs.name = "drawControlPoints";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
    drawControlPoints = createModParameter(holdModParamBoolArgs);
    parameters.add(drawControlPoints->parameters);
    
    parameters.add(usePoint1ForAutoCurveStart.set("usePoint1ForAutoCurveStart", false));
    parameters.add(useLastPointForAutoCurveEnd.set("useLastPointForAutoCurveEnd", false));
    
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
    
    holdModParamFloatArgs.name = "positionSpreadCurvePhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    positionSpreadCurvePhase = createModParameter(holdModParamFloatArgs);
    parameters.add(positionSpreadCurvePhase->parameters);
    
    holdModParamFloatArgs.name = "lineColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	lineColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(lineColorHue->parameters);
    
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
    
    holdModParamFloatArgs.name = "lineColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	lineColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(lineColorBrightness->parameters);
    
    holdModParamFloatArgs.name = "lineColorAlpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	lineColorAlpha = createModParameter(holdModParamFloatArgs);
    parameters.add(lineColorAlpha->parameters);
    
    holdModParamFloatArgs.name = "lineColorHueEnd";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	lineColorHueEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(lineColorHueEnd->parameters);
    
    holdModParamFloatArgs.name = "lineColorHueRotateEnd";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	lineColorHueRotateEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(lineColorHueRotateEnd->parameters);
    
    holdModParamFloatArgs.name = "lineColorSaturationEnd";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	lineColorSaturationEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(lineColorSaturationEnd->parameters);
    
    holdModParamFloatArgs.name = "lineColorBrightnessEnd";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	lineColorBrightnessEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(lineColorBrightnessEnd->parameters);
    
    holdModParamFloatArgs.name = "lineColorAlphaEnd";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	lineColorAlphaEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(lineColorAlphaEnd->parameters);
    
    parameters.add(lineColorHSBAsRGB.set("lineColorHSBAsRGB", false));
    parameters.add(useLineColorHueForEndColor.set("useLineColorHueForEndColor", false));
    parameters.add(useLineColorSaturationForEndColor.set("useLineColorSaturationForEndColor", false));
    parameters.add(useLineColorBrightnessForEndColor.set("useLineColorBrightnessForEndColor", false));
    parameters.add(useLineColorAlphaForEndColor.set("useLineColorAlphaForEndColor", false));
    
    parameters.add(useLineColorForFillColor.set("useLineColorForFillColor", true));
    parameters.add(swapLineColorWithFillColor.set("swapLineColorWithFillColor", false));
    
    holdModParamFloatArgs.name = "fillColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    fillColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(fillColorHue->parameters);
    
    holdModParamFloatArgs.name = "fillColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    fillColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(fillColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "fillColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    fillColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(fillColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "fillColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    fillColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(fillColorBrightness->parameters);
    
    holdModParamFloatArgs.name = "fillColorAlpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    fillColorAlpha = createModParameter(holdModParamFloatArgs);
    parameters.add(fillColorAlpha->parameters);
    
    holdModParamFloatArgs.name = "fillColorHueEnd";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    fillColorHueEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(fillColorHueEnd->parameters);
    
    holdModParamFloatArgs.name = "fillColorHueRotateEnd";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    fillColorHueRotateEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(fillColorHueRotateEnd->parameters);
    
    holdModParamFloatArgs.name = "fillColorSaturationEnd";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    fillColorSaturationEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(fillColorSaturationEnd->parameters);
    
    holdModParamFloatArgs.name = "fillColorBrightnessEnd";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    fillColorBrightnessEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(fillColorBrightnessEnd->parameters);
    
    holdModParamFloatArgs.name = "fillColorAlphaEnd";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    fillColorAlphaEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(fillColorAlphaEnd->parameters);
    
    parameters.add(useFillColorHueForEndColor.set("useFillColorHueForEndColor", false));
    parameters.add(useFillColorSaturationForEndColor.set("useFillColorSaturationForEndColor", false));
    parameters.add(useFillColorBrightnessForEndColor.set("useFillColorBrightnessForEndColor", false));
    parameters.add(useFillColorAlphaForEndColor.set("useFillColorAlphaForEndColor", false));
    parameters.add(fillColorHSBAsRGB.set("fillColorHSBAsRGB", false));

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
    
    holdModParamIntArgs.name = "transformOrder";
    holdModParamIntArgs.fixedValue = TXTRANSFORMORDER_SHIFTROTATESCALE;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXTRANSFORMORDER_TOTAL-1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXTRANSFORMORDER_TOTAL-1;
    transformOrder = createModParameter(holdModParamIntArgs);
    parameters.add(transformOrder->parameters);
    
    holdModParamFloatArgs.name = "shiftX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
    shiftX = createModParameter(holdModParamFloatArgs);
    parameters.add(shiftX->parameters);
    
    holdModParamFloatArgs.name = "shiftY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
    shiftY = createModParameter(holdModParamFloatArgs);
    parameters.add(shiftY->parameters);
    
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
    
    // setup points and merge parameters
    arrCurvePoints[0].setup(TXPOINTTYPE_2DPOINTDELAY, "point1", maxDelayFrames);
    arrCurvePoints[1].setup(TXPOINTTYPE_2DBEZIERDELAY, "point2", maxDelayFrames);
    arrCurvePoints[2].setup(TXPOINTTYPE_2DBEZIERDELAY, "point3", maxDelayFrames);
    arrCurvePoints[3].setup(TXPOINTTYPE_2DBEZIERDELAY, "point4", maxDelayFrames);
    arrCurvePoints[4].setup(TXPOINTTYPE_2DBEZIERDELAY, "point5", maxDelayFrames);
    arrCurvePoints[5].setup(TXPOINTTYPE_2DBEZIERDELAY, "point6", maxDelayFrames);
    arrCurvePoints[6].setup(TXPOINTTYPE_2DBEZIERDELAY, "point7", maxDelayFrames);
    arrCurvePoints[7].setup(TXPOINTTYPE_2DBEZIERDELAY, "point8", maxDelayFrames);
    autoCurveStart.setup(TXPOINTTYPE_2DCONTROLPOINTDELAY, "autoCurveStart");
    autoCurveEnd.setup(TXPOINTTYPE_2DCONTROLPOINTDELAY, "autoCurveEnd");
    
    mergeParameters(arrCurvePoints[0].parameters, arrCurvePoints[0].modParameters);
    mergeParameters(arrCurvePoints[1].parameters, arrCurvePoints[1].modParameters);
    mergeParameters(arrCurvePoints[2].parameters, arrCurvePoints[2].modParameters);
    mergeParameters(arrCurvePoints[3].parameters, arrCurvePoints[3].modParameters);
    mergeParameters(arrCurvePoints[4].parameters, arrCurvePoints[4].modParameters);
    mergeParameters(arrCurvePoints[5].parameters, arrCurvePoints[5].modParameters);
    mergeParameters(arrCurvePoints[6].parameters, arrCurvePoints[6].modParameters);
    mergeParameters(arrCurvePoints[7].parameters, arrCurvePoints[7].modParameters);
    mergeParameters(autoCurveStart.parameters, autoCurveStart.modParameters);
    mergeParameters(autoCurveEnd.parameters, autoCurveEnd.modParameters);

	shader.setGeometryInputType(GL_LINES);
	shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
	shader.setGeometryOutputCount(4);

    // load shader
#ifndef TARGET_OPENGLES
	if(ofIsGLProgrammableRenderer()){
        shader.load ("shadersGL3/lineToRect.vert", "shadersGL3/lineToRect.frag", "shadersGL3/lineToRect.geom");
    }else{
        shader.load ("shadersGL2/lineToRect.vert", "shadersGL2/lineToRect.frag", "shadersGL2/lineToRect.geom");
	}
#endif
}

void TXDrawDelayCurves::update() {
    for (int pointNo = 0; pointNo < numPoints->getInt(); pointNo++){
        arrCurvePoints[pointNo].update();
    };
};

 void TXDrawDelayCurves::draw(){
     int num, holdLineWidth, numDraws;

     if (!drawActive->getBool()) {
         return;
     };
     int totalCurves = numCurves->getInt();
     int totalPoints = numPoints->getInt();
     int holdCurveType = curveType->getInt();
     bool isAutoCurve = holdCurveType == TX2DCURVETYPE_AUTOCURVE;
     bool isStraight = holdCurveType == TX2DCURVETYPE_STRAIGHT;
     bool isBezier = (holdCurveType > TX2DCURVETYPE_STRAIGHT);
     bool isAutoClose = autoClose->getBool();
     bool drawControlPointsLines = drawControlPoints->getBool();
     bool reverseOrder = reverseCurveOrder->getBool();
     bool isFillShape = fillShape->getBool();

     float holdPositionSpreadCurveMorph = positionSpreadCurveMorph->getFloat();
     float holdPositionSpreadCurvePhase = positionSpreadCurvePhase->getFloat();
     float holdColorSpreadCurveMorph = colorSpreadCurveMorph->getFloat();
     float holdColorSpreadCurvePhase = colorSpreadCurvePhase->getFloat();
     
     float holdAnchorX = anchorX->getFloat() * getMaxWidth();
     float holdAnchorY = anchorY->getFloat() * getMaxHeight();
     float holdRotate = rotate->getFloat();
     float holdScaleX, holdScaleY;
     
     holdScaleX = scaleX->getFloat();
     if (useScaleXForScaleY) {
         holdScaleY = holdScaleX;
     } else {
         holdScaleY = scaleY->getFloat();
     };
     ofPushMatrix();
     ofTranslate(holdAnchorX, holdAnchorY, 0.0);
     switch (transformOrder->getInt()) {
         case TXTRANSFORMORDER_SHIFTROTATESCALE:
             ofTranslate(shiftX->getFloat() * getMaxWidth(), shiftY->getFloat() * getMaxHeight(), 0.0);
             ofRotateZ(holdRotate);
             ofScale(holdScaleX, holdScaleY, 1.0);
             break;
         case TXTRANSFORMORDER_SHIFTSCALEROTATE:
             ofTranslate(shiftX->getFloat() * getMaxWidth(), shiftY->getFloat() * getMaxHeight(), 0.0);
             ofScale(holdScaleX, holdScaleY, 1.0);
             ofRotateZ(holdRotate);
             break;
         case TXTRANSFORMORDER_ROTATESCALESHIFT:
             ofRotateZ(holdRotate);
             ofScale(holdScaleX, holdScaleY, 1.0);
             ofTranslate(shiftX->getFloat() * getMaxWidth(), shiftY->getFloat() * getMaxHeight(), 0.0);
             break;
         case TXTRANSFORMORDER_ROTATESHIFTSCALE:
             ofRotateZ(holdRotate);
             ofTranslate(shiftX->getFloat() * getMaxWidth(), shiftY->getFloat() * getMaxHeight(), 0.0);
             ofScale(holdScaleX, holdScaleY, 1.0);
             break;
         case TXTRANSFORMORDER_SCALESHIFTROTATE:
             ofScale(holdScaleX, holdScaleY, 1.0);
             ofTranslate(shiftX->getFloat() * getMaxWidth(), shiftY->getFloat() * getMaxHeight(), 0.0);
             ofRotateZ(holdRotate);
             break;
         case TXTRANSFORMORDER_SCALEROTATESHIFT:
             ofScale(holdScaleX, holdScaleY, 1.0);
             ofRotateZ(holdRotate);
             ofTranslate(shiftX->getFloat() * getMaxWidth(), shiftY->getFloat() * getMaxHeight(), 0.0);
             break;
         default:
             ofTranslate(shiftX->getFloat() * getMaxWidth(), shiftY->getFloat() * getMaxHeight(), 0.0);
             ofRotateZ(holdRotate);
             ofScale(holdScaleX, holdScaleY, 1.0);
             break;
     }
     ofTranslate(-holdAnchorX, -holdAnchorY, 0.0);
     
     if (isFillShape) {
         // draw twice if filled and fill color is different
         if  (useLineColorForFillColor == false) {
             numDraws = 2;
         } else {
             numDraws = 1;
         }
     } else {
         numDraws = 1;
     };
     ofSetCurveResolution(curveResolution->getInt());
     ofEnableAlphaBlending();
     if ((windingMode->getInt() == 0) || (isStraight && (totalPoints == 2))) {
         ofSetPolyMode(OF_POLY_WINDING_ODD);
     } else {
         ofSetPolyMode(OF_POLY_WINDING_NONZERO);
     };

     // colors
     float startH, startHR, startS, startB, startA;
     float endH, endHR, endS, endB, endA;
     startH = lineColorHue->getFloat();
     startHR = lineColorHueRotate->getFloat();
     startS = lineColorSaturation->getFloat();
     startB = lineColorBrightness->getFloat();
     startA = lineColorAlpha->getFloat();
     if (useLineColorHueForEndColor) {
         endH = startH;
     } else {
         endH = lineColorHueEnd->getFloat();
         endHR = lineColorHueRotateEnd->getFloat();
     };
     if (useLineColorSaturationForEndColor) {
         endS = startS;
     } else {
         endS = lineColorSaturationEnd->getFloat();
     };
     if (useLineColorBrightnessForEndColor) {
         endB = startB;
     } else {
         endB = lineColorBrightnessEnd->getFloat();
     };
     if (useLineColorAlphaForEndColor) {
         endA = startA;
     } else {
         endA = lineColorAlphaEnd->getFloat();
     };
     ;
     ofColor startColor = TXFunctions::txGetColor(startH, startS, startB, startA,  startHR, lineColorHSBAsRGB);
     ofColor endColor = TXFunctions::txGetColor(endH, endS, endB, endA,  endHR, lineColorHSBAsRGB);
     ofColor startFillColor, endFillColor;
     float startFillH, startFillHR, startFillS, startFillB, startFillA;
     float endFillH, endFillHR, endFillS, endFillB, endFillA;
     if (useLineColorForFillColor) {
         startFillColor = startColor;
         endFillColor = endColor;
     } else {
         startFillH = fillColorHue->getFloat();
         startFillHR = fillColorHueRotate->getFloat();
         startFillS = fillColorSaturation->getFloat();
         startFillB = fillColorBrightness->getFloat();
         startFillA = fillColorAlpha->getFloat();
         if (useFillColorHueForEndColor) {
             endFillH = startFillH;
         } else {
             endFillH = fillColorHueEnd->getFloat();
             endFillHR = fillColorHueRotateEnd->getFloat();
         };
         if (useFillColorSaturationForEndColor) {
             endFillS = startFillS;
         } else {
             endFillS = fillColorSaturationEnd->getFloat();
         };
         if (useFillColorBrightnessForEndColor) {
             endFillB = startFillB;
         } else {
             endFillB = fillColorBrightnessEnd->getFloat();
         };
         if (useFillColorAlphaForEndColor) {
             endFillA = startFillA;
         } else {
             endFillA = fillColorAlphaEnd->getFloat();
         };
         ;
         startFillColor = TXFunctions::txGetColor(startFillH, startFillS, startFillB, startFillA,  startFillHR, fillColorHSBAsRGB);
         endFillColor = TXFunctions::txGetColor(endFillH, endFillS, endFillB, endFillA,  endFillHR, fillColorHSBAsRGB);
     };

    // for all curves

     // for all curves
     for (int curveIndex = 0; curveIndex < totalCurves; curveIndex++){
         float curveNo;
         float autoCurveStartX, autoCurveStartY, autoCurveEnd1X, autoCurveEnd1Y, autoCurveEnd2X, autoCurveEnd2Y;
         float proportion, colorSpreadProportion, positionSpreadProportion;
         vector<ofVec2f> overlayPoints;
         vector<ofVec2f> overlayLinePoints;

         if (reverseOrder) {
             curveNo = curveIndex;
         } else {
             curveNo = totalCurves - 1 - curveIndex;
         };
         if (totalCurves == 1) {
             proportion = 0.5;
         } else {
             proportion = (float) (0.5 + curveNo) / totalCurves;
         };
         colorSpreadProportion =  TXFunctions::getInterpPhaseCurves(colorSpreadCurve, colorSpreadCurve2, proportion, holdColorSpreadCurvePhase, holdColorSpreadCurveMorph);
         positionSpreadProportion =  TXFunctions::getInterpPhaseCurves(positionSpreadCurve, positionSpreadCurve2, proportion, holdPositionSpreadCurvePhase, holdPositionSpreadCurveMorph);

         // build point coord arrays
         float arrdrawX[maxCurvePoints];
         float arrdrawY[maxCurvePoints];
         float arrcontrol1X[maxCurvePoints];
         float arrcontrol1Y[maxCurvePoints];
         float arrcontrol2X[maxCurvePoints];
         float arrcontrol2Y[maxCurvePoints];
         // for all points
         int holdDelayFrames = min(delayFrames->getInt(), (int)parentSystem->getCurrentFrameNo() - 1);
         for (int pointNo = 0; pointNo < totalPoints; pointNo++){
             int x1,y1,x2,y2,x3,y3;
             arrdrawX[pointNo] = getMaxWidth() * arrCurvePoints[pointNo].getDelayDrawX(positionSpreadProportion, holdDelayFrames);
             arrdrawY[pointNo] = getMaxHeight() * arrCurvePoints[pointNo].getDelayDrawY(positionSpreadProportion, holdDelayFrames);
             
             if ((pointNo > 0) && (curveType->getInt() > TX2DCURVETYPE_STRAIGHT) ) {
                 arrcontrol1X[pointNo] = getMaxWidth() * arrCurvePoints[pointNo].getDelayControl1X(positionSpreadProportion, holdDelayFrames);
                 arrcontrol1Y[pointNo] = getMaxHeight() * arrCurvePoints[pointNo].getDelayControl1Y(positionSpreadProportion, holdDelayFrames);
                 
                 arrcontrol2X[pointNo] = getMaxWidth() * arrCurvePoints[pointNo].getDelayControl2X(positionSpreadProportion, holdDelayFrames);
                 arrcontrol2Y[pointNo] = getMaxHeight() * arrCurvePoints[pointNo].getDelayControl2Y(positionSpreadProportion, holdDelayFrames);
             };
         }; // end of for all points
         
         // AutoCurve settings
         if (isAutoCurve) {
             if (isAutoClose || isFillShape) {
                 autoCurveStartX = arrdrawX[totalPoints - 1];
                 autoCurveStartY = arrdrawY[totalPoints - 1];
                 autoCurveEnd1X = arrdrawX[0];
                 autoCurveEnd1Y = arrdrawY[0];
                 autoCurveEnd2X = arrdrawX[1];
                 autoCurveEnd2Y = arrdrawY[1];
             } else {
                 if (usePoint1ForAutoCurveStart) {
                     autoCurveStartX = arrdrawX[0];
                     autoCurveStartY = arrdrawY[0];
                 } else {
                     autoCurveStartX = getMaxWidth() * autoCurveStart.getDelayControl1X(positionSpreadProportion, holdDelayFrames);
                     autoCurveStartY = getMaxHeight() * autoCurveStart.getDelayControl1Y(positionSpreadProportion, holdDelayFrames);
                 };
                 if (useLastPointForAutoCurveEnd) {
                     autoCurveEnd1X = arrdrawX[totalPoints - 1];
                     autoCurveEnd1Y = arrdrawY[totalPoints - 1];
                     autoCurveEnd2X = autoCurveEnd1X;
                     autoCurveEnd2Y = autoCurveEnd1Y;
                 } else {
                     autoCurveEnd1X = getMaxWidth() * autoCurveEnd.getDelayControl1X(positionSpreadProportion, holdDelayFrames);
                     autoCurveEnd1Y = getMaxHeight() * autoCurveEnd.getDelayControl1Y(positionSpreadProportion, holdDelayFrames);
                     autoCurveEnd2X = autoCurveEnd1X;
                     autoCurveEnd2Y = autoCurveEnd1Y;
                 };
             };
         }; // end of if (isAutoCurve)
         
         // draw twice if filled and fill color is different
         for (int drawNo = 0; drawNo < numDraws; drawNo++){
             if ((isFillShape == false) || ((numDraws == 2) && (drawNo == 1))) {
                 ofNoFill();
             } else {
                 ofFill();
             };
             
             // use shader for width > 10
             useShader = false;
             // thin line if drawing fill only
             bool drawingFillOnly;
             if (numDraws == 2 && (drawNo == 0)) {
                 drawingFillOnly = true;
                 holdLineWidth = 0;
                 ofSetLineWidth(0);
             } else {
                 drawingFillOnly = false;
                 holdLineWidth = lineWidth->getInt();
#ifdef TARGET_OPENGLES
                 ofSetLineWidth(holdLineWidth);
#else
                 if (ofIsGLProgrammableRenderer()){
                     // NOTE ofSetLineWidth() doesn't work in new renderer
                     if (holdLineWidth > 1) {
                         //
                         // NOTE - CAN'T GET SHADER TO WORK IN NEW RENDERER
                         // REMOVE FOR NOW
                         //useShader = true;
                     };
                 } else {
                     if (holdLineWidth <= 10){
                         ofSetLineWidth(holdLineWidth);
                     } else {
                         ofSetLineWidth(0);
                         useShader = true;
                     };
                 };
#endif
             };
             if (useShader) {
                 shader.begin();
                 shader.setUniform1f("thickness", holdLineWidth);
             };
             if (drawingFillOnly) {
                 if (swapLineColorWithFillColor) {
                     ofSetColor(startColor.getLerped(endColor, colorSpreadProportion));
                 } else {
                     ofSetColor(startFillColor.getLerped(endFillColor, colorSpreadProportion));
                 };
             } else {
                 if (swapLineColorWithFillColor) {
                     ofSetColor(startFillColor.getLerped(endFillColor, colorSpreadProportion));
                 } else {
                     ofSetColor(startColor.getLerped(endColor, colorSpreadProportion));
                 };
             };
             
             ofBeginShape();
             // for all points
             for (int pointNo = 0; pointNo < totalPoints; pointNo++){
                 float drawX,drawY,control1X,control1Y,control2X,control2Y;
                 drawX = arrdrawX[pointNo];
                 drawY = arrdrawY[pointNo];
                 if ((pointNo > 0) && isBezier ) {
                     control1X = arrcontrol1X[pointNo];
                     control1Y = arrcontrol1Y[pointNo];
                 };
                 if (isStraight) {
                     ofVertex(drawX,drawY);
                     if (drawControlPointsLines) {
                         overlayPoints.push_back(ofVec2f(drawX,drawY));
                         overlayLinePoints.push_back(ofVec2f(drawX,drawY));
                         if (pointNo > 0) {
                             overlayLinePoints.push_back(ofVec2f(drawX,drawY));
                         };
                     };
                 } else {
                     // first vertex
                     if (pointNo == 0) {
                         if (isAutoCurve) {
                             // insert point before first point for AutoCurve
                             ofCurveVertex(autoCurveStartX,autoCurveStartY);
                             if (drawControlPointsLines) {
                                 overlayPoints.push_back(ofVec2f(autoCurveStartX,autoCurveStartY));
                                 overlayLinePoints.push_back(ofVec2f(autoCurveStartX,autoCurveStartY));
                             };
                             ofCurveVertex(drawX,drawY);
                             if (drawControlPointsLines) {
                                 overlayPoints.push_back(ofVec2f(drawX,drawY));
                                 overlayLinePoints.push_back(ofVec2f(drawX,drawY));
                                 overlayLinePoints.push_back(ofVec2f(drawX,drawY));
                             };
                         } else {
                             // first point is always just a vertex for bezier
                             ofVertex(drawX,drawY);
                             if (drawControlPointsLines) {
                                 overlayPoints.push_back(ofVec2f(drawX,drawY));
                                 overlayLinePoints.push_back(ofVec2f(drawX,drawY));
                             };
                         };
                     } else {
                         //all other vertices
                         switch (holdCurveType) {
                             case TX2DCURVETYPE_AUTOCURVE:
                                 ofCurveVertex(drawX, drawY);
                                 if (drawControlPointsLines) {
                                     overlayPoints.push_back(ofVec2f(drawX,drawY));
                                     overlayLinePoints.push_back(ofVec2f(drawX,drawY));
                                     overlayLinePoints.push_back(ofVec2f(drawX,drawY));
                                 };
                                 // add extra points after last point for AutoCurve
                                 if (pointNo == (totalPoints - 1)) {
                                     if (isAutoClose || isFillShape) {
                                         ofCurveVertex(autoCurveEnd1X, autoCurveEnd1Y);
                                         if (drawControlPointsLines) {
                                             overlayPoints.push_back(ofVec2f(autoCurveEnd1X, autoCurveEnd1Y));
                                             overlayLinePoints.push_back(ofVec2f(autoCurveEnd1X, autoCurveEnd1Y));
                                             overlayLinePoints.push_back(ofVec2f(autoCurveEnd1X, autoCurveEnd1Y));
                                         };
                                     };
                                     ofCurveVertex(autoCurveEnd2X, autoCurveEnd2Y);
                                     if (drawControlPointsLines) {
                                         overlayPoints.push_back(ofVec2f(autoCurveEnd2X, autoCurveEnd2Y));
                                         overlayLinePoints.push_back(ofVec2f(autoCurveEnd2X, autoCurveEnd2Y));
                                     };
                                 };
                                 break;
                             case TX2DCURVETYPE_BEZIER1:
                                 // control pt 2 = control pt 1
                                 ofBezierVertex(control1X, control1Y, control1X, control1Y,drawX,drawY);
                                 if (drawControlPointsLines) {
                                     overlayPoints.push_back(ofVec2f(control1X, control1Y));
                                     overlayPoints.push_back(ofVec2f(control1X, control1Y));
                                     overlayPoints.push_back(ofVec2f(drawX,drawY));
                                     overlayLinePoints.push_back(ofVec2f(control1X, control1Y));
                                     overlayLinePoints.push_back(ofVec2f(control1X, control1Y));
                                     overlayLinePoints.push_back(ofVec2f(drawX,drawY));
                                     overlayLinePoints.push_back(ofVec2f(drawX,drawY));
                                 };
                                 break;
                             case TX2DCURVETYPE_BEZIER2:
                                 if (pointNo == (totalPoints - 1)) {
                                     control2X = drawX;
                                     control2Y = drawY;
                                 } else {
                                     // for smooth curves, control pt 2 is a mirror (centred at draw point) of next point's control pt 1
                                     control2X = drawX + (drawX - arrcontrol1X[pointNo + 1]);
                                     control2Y = drawY + (drawY - arrcontrol1Y[pointNo + 1]);
                                 };
                                 ofBezierVertex(control1X,control1Y,control2X,control2Y,drawX,drawY);
                                 if (drawControlPointsLines) {
                                     overlayPoints.push_back(ofVec2f(control1X, control1Y));
                                     overlayPoints.push_back(ofVec2f(control2X,control2Y));
                                     overlayPoints.push_back(ofVec2f(drawX,drawY));
                                     overlayLinePoints.push_back(ofVec2f(control1X, control1Y));
                                     overlayLinePoints.push_back(ofVec2f(control2X,control2Y));
                                     overlayLinePoints.push_back(ofVec2f(drawX,drawY));
                                     overlayLinePoints.push_back(ofVec2f(drawX,drawY));
                                 };
                                 // add extra point to close smooth bezier if required
                                 if ((pointNo == (totalPoints - 1)) && (isAutoClose || isFillShape)) {
                                     float prevdrawX, prevdrawY, prevCont2X, prevCont2Y, nextCont1X, nextCont1Y;
                                     prevdrawX = arrdrawX[totalPoints - 1];
                                     prevdrawY = arrdrawY[totalPoints - 1];
                                     prevCont2X = arrcontrol1X[totalPoints - 1];
                                     prevCont2Y = arrcontrol1Y[totalPoints - 1];
                                     nextCont1X = arrcontrol1X[1];
                                     nextCont1Y = arrcontrol1Y[1];
                                     drawX = arrdrawX[0];
                                     drawY = arrdrawY[0];
                                     // control pts are mirror (centred at draw point) of next point's control pt
                                     control1X = prevdrawX + (prevdrawX - prevCont2X);
                                     control1Y = prevdrawY + (prevdrawY - prevCont2Y);
                                     control2X = drawX + (drawX - nextCont1X);
                                     control2Y = drawY + (drawY - nextCont1Y);
                                     ofBezierVertex(control1X, control1Y, control2X, control2Y, drawX, drawY);
                                     if (drawControlPointsLines) {
                                         overlayPoints.push_back(ofVec2f(control1X, control1Y));
                                         overlayPoints.push_back(ofVec2f(control2X,control2Y));
                                         overlayPoints.push_back(ofVec2f(drawX,drawY));
                                         overlayLinePoints.push_back(ofVec2f(control1X, control1Y));
                                         overlayLinePoints.push_back(ofVec2f(control2X,control2Y));
                                         overlayLinePoints.push_back(ofVec2f(drawX,drawY));
                                         overlayLinePoints.push_back(ofVec2f(drawX,drawY));
                                     };
                                 };
                                 break;
                             case TX2DCURVETYPE_BEZIER3:
                                 // use both control points
                                 control2X = arrcontrol2X[pointNo];
                                 control2Y = arrcontrol2Y[pointNo];
                                 ofBezierVertex(control1X, control1Y, control2X, control2Y, drawX, drawY);
                                 if (drawControlPointsLines) {
                                     overlayPoints.push_back(ofVec2f(control1X, control1Y));
                                     overlayPoints.push_back(ofVec2f(control2X,control2Y));
                                     overlayPoints.push_back(ofVec2f(drawX,drawY));
                                     overlayLinePoints.push_back(ofVec2f(control1X, control1Y));
                                     overlayLinePoints.push_back(ofVec2f(control2X,control2Y));
                                     overlayLinePoints.push_back(ofVec2f(drawX,drawY));
                                     overlayLinePoints.push_back(ofVec2f(drawX,drawY));
                                 };
                                 break;
                             default:
                                 ofCurveVertex(drawX, drawY);
                                 if (drawControlPointsLines) {
                                     overlayPoints.push_back(ofVec2f(drawX,drawY));
                                 };
                                 break;
                         };
                     };
                 }; // end of if TX2DCURVETYPE_STRAIGHT
             }; // end of for all points
             
             ofEndShape(isAutoClose);
             
             if (useShader) {
                 shader.end();
             };
             
             // draw control points & lines
             if (drawControlPointsLines && (drawNo == (numDraws - 1))) {
                 ofFill();
                 ofSetCircleResolution(8);
                 for (int pointNo = 0; pointNo < overlayPoints.size(); pointNo++){
                     ofSetColor(255);
                     ofDrawCircle(overlayPoints[pointNo].x, overlayPoints[pointNo].y, 5.0);
                     ofSetColor(0);
                     ofDrawCircle(overlayPoints[pointNo].x, overlayPoints[pointNo].y, 3.0);
                 };
                 
                 int evenLinePoints = overlayLinePoints.size() - (overlayLinePoints.size() % 2);
                 for (int pointNo = 0; pointNo < evenLinePoints; pointNo += 2){
                     ofSetColor(255);
                     ofSetLineWidth(3);
                     ofDrawLine(overlayLinePoints[pointNo].x, overlayLinePoints[pointNo].y, overlayLinePoints[pointNo+1].x, overlayLinePoints[pointNo+1].y);
                     ofSetColor(0);
                     ofSetLineWidth(1);
                     ofDrawLine(overlayLinePoints[pointNo].x, overlayLinePoints[pointNo].y, overlayLinePoints[pointNo+1].x, overlayLinePoints[pointNo+1].y);
                 };
             };
             
         }; // end of for numDraws
         
     };// for all curves
     
     ofPopMatrix();
     ofDisableAlphaBlending();
     ofSetColor(255.0f);
}

