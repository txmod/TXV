/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXDraw3DCurves.h"
#include "TXFunctions.h"

TXDraw3DCurves::TXDraw3DCurves() {
    setup();
}

void TXDraw3DCurves::setup(){
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
    
    holdModParamIntArgs.name = "curveType";
    holdModParamIntArgs.fixedValue = TX2DCURVETYPE_AUTOCURVE;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalCurveTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalCurveTypes - 1;
	curveType = createModParameter(holdModParamIntArgs);
    parameters.add(curveType->parameters);
    
    holdModParamIntArgs.name = "numCurves";
    holdModParamIntArgs.fixedValue = 4;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = maxCurves;
    holdModParamIntArgs.softMin = 1;
    holdModParamIntArgs.softMax = 100;
	numCurves = createModParameter(holdModParamIntArgs);
    parameters.add(numCurves->parameters);
    
    holdModParamIntArgs.name = "numPoints";
    holdModParamIntArgs.fixedValue = 2;
    holdModParamIntArgs.hardMin = 2;
    holdModParamIntArgs.hardMax = maxCurvePoints;
    holdModParamIntArgs.softMin = 2;
    holdModParamIntArgs.softMax = maxCurvePoints;
	numPoints = createModParameter(holdModParamIntArgs);
    parameters.add(numPoints->parameters);
    
    holdModParamIntArgs.name = "lineWidth";
    holdModParamIntArgs.fixedValue = 1;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 100;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 100;
	lineWidth = createModParameter(holdModParamIntArgs);
    parameters.add(lineWidth->parameters);
    
    /*   TESTING XXX - OLD CODE     */

    holdModParamIntArgs.name = "spreadType";
    holdModParamIntArgs.fixedValue = OF_EASE_LINEAR_IN;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = maxSpreadTypes;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = maxSpreadTypes;
    spreadType = createModParameter(holdModParamIntArgs);
    parameters.add(spreadType->parameters);
    
    holdModParamIntArgs.name = "spreadType2";
    holdModParamIntArgs.fixedValue = OF_EASE_LINEAR_IN;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = maxSpreadTypes;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = maxSpreadTypes;
    spreadType2 = createModParameter(holdModParamIntArgs);
    parameters.add(spreadType2->parameters);
    
    holdModParamFloatArgs.name = "spreadTypeMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    spreadTypeMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(spreadTypeMorph->parameters);
    
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
    
    holdModParamFloatArgs.name = "colorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	colorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(colorHue->parameters);
    
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
    
    holdModParamFloatArgs.name = "colorBrightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	colorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(colorBrightness->parameters);
    
    holdModParamFloatArgs.name = "colorAlpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	colorAlpha = createModParameter(holdModParamFloatArgs);
    parameters.add(colorAlpha->parameters);
    
    holdModParamFloatArgs.name = "colorHueEnd";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	colorHueEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(colorHueEnd->parameters);
    
    holdModParamFloatArgs.name = "colorHueRotateEnd";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	colorHueRotateEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(colorHueRotateEnd->parameters);
    
    holdModParamFloatArgs.name = "colorSaturationEnd";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	colorSaturationEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(colorSaturationEnd->parameters);
    
    holdModParamFloatArgs.name = "colorBrightnessEnd";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	colorBrightnessEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(colorBrightnessEnd->parameters);
    
    holdModParamFloatArgs.name = "colorAlphaEnd";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	colorAlphaEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(colorAlphaEnd->parameters);
    
    parameters.add(useColorHueForEndColor.set("useColorHueForEndColor", false));
    parameters.add(useColorSaturationForEndColor.set("useColorSaturationForEndColor", false));
    parameters.add(useColorBrightnessForEndColor.set("useColorBrightnessForEndColor", false));
    parameters.add(useColorAlphaForEndColor.set("useColorAlphaForEndColor", false));
    parameters.add(colorHSBAsRGB.set("colorHSBAsRGB", false));

    parameters.add(useColorForFillColor.set("useColorForFillColor", true));
    parameters.add(swapColorWithFillColor.set("swapColorWithFillColor", false));

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

    parameters.add(usePoint1ForAutoCurveStart.set("usePoint1ForAutoCurveStart", false));
    parameters.add(useLastPointForAutoCurveEnd.set("useLastPointForAutoCurveEnd", false));
    
    // setup points and merge parameters
    arrCurvePoints[0].setup(TXPOINTTYPE_2DPOINTRANGEOPTION, "point1");
    arrCurvePoints[1].setup(TXPOINTTYPE_2DBEZIERRANGEOPTION, "point2");
    arrCurvePoints[2].setup(TXPOINTTYPE_2DBEZIERRANGEOPTION, "point3");
    arrCurvePoints[3].setup(TXPOINTTYPE_2DBEZIERRANGEOPTION, "point4");
    arrCurvePoints[4].setup(TXPOINTTYPE_2DBEZIERRANGEOPTION, "point5");
    arrCurvePoints[5].setup(TXPOINTTYPE_2DBEZIERRANGEOPTION, "point6");
    arrCurvePoints[6].setup(TXPOINTTYPE_2DBEZIERRANGEOPTION, "point7");
    arrCurvePoints[7].setup(TXPOINTTYPE_2DBEZIERRANGEOPTION, "point8");
    autoCurveStart.setup(TXPOINTTYPE_2DCONTROLPOINTRANGEOPTION, "autoCurveStart");
    autoCurveEnd.setup(TXPOINTTYPE_2DCONTROLPOINTRANGEOPTION, "autoCurveEnd");

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
    
    holdModParamFloatArgs.name = "shiftXEnd";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
    shiftXEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(shiftXEnd->parameters);
    
    holdModParamBoolArgs.name = "shiftXEndIgnore";
    holdModParamBoolArgs.fixedValue = false;
    shiftXEndIgnore = createModParameter(holdModParamBoolArgs);
    parameters.add(shiftXEndIgnore->parameters);
    
    holdModParamFloatArgs.name = "shiftY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
    shiftY = createModParameter(holdModParamFloatArgs);
    parameters.add(shiftY->parameters);
    
    holdModParamFloatArgs.name = "shiftYEnd";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
    shiftYEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(shiftYEnd->parameters);
    
    holdModParamBoolArgs.name = "shiftYEndIgnore";
    holdModParamBoolArgs.fixedValue = true;
    shiftYEndIgnore = createModParameter(holdModParamBoolArgs);
    parameters.add(shiftYEndIgnore->parameters);
    
    holdModParamFloatArgs.name = "shiftZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
    shiftZ = createModParameter(holdModParamFloatArgs);
    parameters.add(shiftZ->parameters);
    
    holdModParamFloatArgs.name = "shiftZEnd";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
    shiftZEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(shiftZEnd->parameters);
    
    holdModParamBoolArgs.name = "shiftZEndIgnore";
    holdModParamBoolArgs.fixedValue = true;
    shiftZEndIgnore = createModParameter(holdModParamBoolArgs);
    parameters.add(shiftZEndIgnore->parameters);
    
    shiftXSpreadCurve.setValueArrayToRamp(0, 1);
    shiftXSpreadCurve.setName("shiftXSpreadCurve");
    parameters.add(shiftXSpreadCurve.parameters);
    
    shiftXSpreadCurve2.setValueArrayToRamp(0, 1);
    shiftXSpreadCurve2.setName("shiftXSpreadCurve2");
    parameters.add(shiftXSpreadCurve2.parameters);
    
    holdModParamFloatArgs.name = "shiftXSpreadCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    shiftXSpreadCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(shiftXSpreadCurveMorph->parameters);
    
    shiftYSpreadCurve.setValueArrayToRamp(0, 1);
    shiftYSpreadCurve.setName("shiftYSpreadCurve");
    parameters.add(shiftYSpreadCurve.parameters);
    
    shiftYSpreadCurve2.setValueArrayToRamp(0, 1);
    shiftYSpreadCurve2.setName("shiftYSpreadCurve2");
    parameters.add(shiftYSpreadCurve2.parameters);
    
    holdModParamFloatArgs.name = "shiftYSpreadCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    shiftYSpreadCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(shiftYSpreadCurveMorph->parameters);
    
    shiftZSpreadCurve.setValueArrayToRamp(0, 1);
    shiftZSpreadCurve.setName("shiftZSpreadCurve");
    parameters.add(shiftZSpreadCurve.parameters);
    
    shiftZSpreadCurve2.setValueArrayToRamp(0, 1);
    shiftZSpreadCurve2.setName("shiftZSpreadCurve2");
    parameters.add(shiftZSpreadCurve2.parameters);
    
    holdModParamFloatArgs.name = "shiftZSpreadCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    shiftZSpreadCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(shiftZSpreadCurveMorph->parameters);
    
    parameters.add(useShiftXSpreadCurveForShiftY.set("useShiftXSpreadCurveForShiftY", false));
    parameters.add(useShiftXSpreadCurveForShiftZ.set("useShiftXSpreadCurveForShiftZ", false));
    
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
    
    holdModParamBoolArgs.name = "rotateXEndIgnore";
    holdModParamBoolArgs.fixedValue = true;
    rotateXEndIgnore = createModParameter(holdModParamBoolArgs);
    parameters.add(rotateXEndIgnore->parameters);
    
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
    
    holdModParamBoolArgs.name = "rotateYEndIgnore";
    holdModParamBoolArgs.fixedValue = true;
    rotateYEndIgnore = createModParameter(holdModParamBoolArgs);
    parameters.add(rotateYEndIgnore->parameters);
    
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
    
    holdModParamBoolArgs.name = "rotateZEndIgnore";
    holdModParamBoolArgs.fixedValue = true;
    rotateZEndIgnore = createModParameter(holdModParamBoolArgs);
    parameters.add(rotateZEndIgnore->parameters);
    
    holdModParamFloatArgs.name = "rotateMultiply";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
    rotateMultiply = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateMultiply->parameters);
    
    rotateXSpreadCurve.setValueArrayToRamp(0, 1);
    rotateXSpreadCurve.setName("rotateXSpreadCurve");
    parameters.add(rotateXSpreadCurve.parameters);
    
    rotateXSpreadCurve2.setValueArrayToRamp(0, 1);
    rotateXSpreadCurve2.setName("rotateXSpreadCurve2");
    parameters.add(rotateXSpreadCurve2.parameters);
    
    holdModParamFloatArgs.name = "rotateXSpreadCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    rotateXSpreadCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateXSpreadCurveMorph->parameters);
    
    rotateYSpreadCurve.setValueArrayToRamp(0, 1);
    rotateYSpreadCurve.setName("rotateYSpreadCurve");
    parameters.add(rotateYSpreadCurve.parameters);
    
    rotateYSpreadCurve2.setValueArrayToRamp(0, 1);
    rotateYSpreadCurve2.setName("rotateYSpreadCurve2");
    parameters.add(rotateYSpreadCurve2.parameters);
    
    holdModParamFloatArgs.name = "rotateYSpreadCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    rotateYSpreadCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateYSpreadCurveMorph->parameters);
    
    rotateZSpreadCurve.setValueArrayToRamp(0, 1);
    rotateZSpreadCurve.setName("rotateZSpreadCurve");
    parameters.add(rotateZSpreadCurve.parameters);
    
    rotateZSpreadCurve2.setValueArrayToRamp(0, 1);
    rotateZSpreadCurve2.setName("rotateZSpreadCurve2");
    parameters.add(rotateZSpreadCurve2.parameters);
    
    holdModParamFloatArgs.name = "rotateZSpreadCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    rotateZSpreadCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateZSpreadCurveMorph->parameters);
    
    parameters.add(useRotateXSpreadCurveForRotateY.set("useRotateXSpreadCurveForRotateY", false));
    parameters.add(useRotateXSpreadCurveForRotateZ.set("useRotateXSpreadCurveForRotateZ", false));
    
    holdModParamFloatArgs.name = "anchorX";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    anchorX = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorX->parameters);
    
    holdModParamFloatArgs.name = "anchorXEnd";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    anchorXEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorXEnd->parameters);
    
    holdModParamBoolArgs.name = "anchorXEndIgnore";
    holdModParamBoolArgs.fixedValue = true;
    anchorXEndIgnore = createModParameter(holdModParamBoolArgs);
    parameters.add(anchorXEndIgnore->parameters);
    
    holdModParamFloatArgs.name = "anchorY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    anchorY = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorY->parameters);
    
    holdModParamFloatArgs.name = "anchorYEnd";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    anchorYEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorYEnd->parameters);
    
    holdModParamBoolArgs.name = "anchorYEndIgnore";
    holdModParamBoolArgs.fixedValue = true;
    anchorYEndIgnore = createModParameter(holdModParamBoolArgs);
    parameters.add(anchorYEndIgnore->parameters);
    
    holdModParamFloatArgs.name = "anchorZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 0.0;
    anchorZ = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorZ->parameters);
    
    holdModParamFloatArgs.name = "anchorZEnd";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 0.0;
    anchorZEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorZEnd->parameters);
    
    holdModParamBoolArgs.name = "anchorZEndIgnore";
    holdModParamBoolArgs.fixedValue = true;
    anchorZEndIgnore = createModParameter(holdModParamBoolArgs);
    parameters.add(anchorZEndIgnore->parameters);
    
    anchorXSpreadCurve.setValueArrayToRamp(0, 1);
    anchorXSpreadCurve.setName("anchorXSpreadCurve");
    parameters.add(anchorXSpreadCurve.parameters);
    
    anchorXSpreadCurve2.setValueArrayToRamp(0, 1);
    anchorXSpreadCurve2.setName("anchorXSpreadCurve2");
    parameters.add(anchorXSpreadCurve2.parameters);
    
    holdModParamFloatArgs.name = "anchorXSpreadCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    anchorXSpreadCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorXSpreadCurveMorph->parameters);
    
    anchorYSpreadCurve.setValueArrayToRamp(0, 1);
    anchorYSpreadCurve.setName("anchorYSpreadCurve");
    parameters.add(anchorYSpreadCurve.parameters);
    
    anchorYSpreadCurve2.setValueArrayToRamp(0, 1);
    anchorYSpreadCurve2.setName("anchorYSpreadCurve2");
    parameters.add(anchorYSpreadCurve2.parameters);
    
    holdModParamFloatArgs.name = "anchorYSpreadCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    anchorYSpreadCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorYSpreadCurveMorph->parameters);
    
    anchorZSpreadCurve.setValueArrayToRamp(0, 1);
    anchorZSpreadCurve.setName("anchorZSpreadCurve");
    parameters.add(anchorZSpreadCurve.parameters);
    
    anchorZSpreadCurve2.setValueArrayToRamp(0, 1);
    anchorZSpreadCurve2.setName("anchorZSpreadCurve2");
    parameters.add(anchorZSpreadCurve2.parameters);
    
    holdModParamFloatArgs.name = "anchorZSpreadCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    anchorZSpreadCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorZSpreadCurveMorph->parameters);
    
    parameters.add(useAnchorXSpreadCurveForAnchorY.set("useAnchorXSpreadCurveForAnchorY", false));
    parameters.add(useAnchorXSpreadCurveForAnchorZ.set("useAnchorXSpreadCurveForAnchorZ", false));
    
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
    
    holdModParamBoolArgs.name = "scaleXEndIgnore";
    holdModParamBoolArgs.fixedValue = true;
    scaleXEndIgnore = createModParameter(holdModParamBoolArgs);
    parameters.add(scaleXEndIgnore->parameters);
    
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
    
    holdModParamBoolArgs.name = "scaleYEndIgnore";
    holdModParamBoolArgs.fixedValue = true;
    scaleYEndIgnore = createModParameter(holdModParamBoolArgs);
    parameters.add(scaleYEndIgnore->parameters);
    
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
    
    holdModParamBoolArgs.name = "scaleZEndIgnore";
    holdModParamBoolArgs.fixedValue = true;
    scaleZEndIgnore = createModParameter(holdModParamBoolArgs);
    parameters.add(scaleZEndIgnore->parameters);
    
    parameters.add(useScaleXForScaleY.set("useScaleXForScaleY", false));
    parameters.add(useScaleXForScaleZ.set("useScaleXForScaleZ", false));
    
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
    
    scaleZSpreadCurve.setValueArrayToRamp(0, 1);
    scaleZSpreadCurve.setName("scaleZSpreadCurve");
    parameters.add(scaleZSpreadCurve.parameters);
    
    scaleZSpreadCurve2.setValueArrayToRamp(0, 1);
    scaleZSpreadCurve2.setName("scaleZSpreadCurve2");
    parameters.add(scaleZSpreadCurve2.parameters);
    
    holdModParamFloatArgs.name = "scaleZSpreadCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    scaleZSpreadCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleZSpreadCurveMorph->parameters);
    
    parameters.add(useScaleXSpreadCurveForScaleY.set("useScaleXSpreadCurveForScaleY", false));
    parameters.add(useScaleXSpreadCurveForScaleZ.set("useScaleXSpreadCurveForScaleZ", false));
    
    // load shader
	shader.setGeometryInputType(GL_LINES);
	shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
	shader.setGeometryOutputCount(4);

#ifndef TARGET_OPENGLES
	if(ofIsGLProgrammableRenderer()){
        shader.load ("shadersGL3/lineToRect.vert", "shadersGL3/lineToRect.frag", "shadersGL3/lineToRect.geom");
    }else{
        shader.load ("shadersGL2/lineToRect.vert", "shadersGL2/lineToRect.frag", "shadersGL2/lineToRect.geom");
	}
#endif
}

void TXDraw3DCurves::draw(){
    int num, holdLineWidth, numDraws;
    
    if (!drawActive->getBool()) {
        return;
    };
    int totalCurves = numCurves->getInt();
    int totalPoints = numPoints->getInt();
    int holdCurveType = curveType->getInt();
    bool isStraight = holdCurveType == TX2DCURVETYPE_STRAIGHT;
    bool isBezier = (holdCurveType > TX2DCURVETYPE_STRAIGHT);
    bool isAutoClose = autoClose->getBool();
    bool isAutoCurve = holdCurveType == TX2DCURVETYPE_AUTOCURVE;
    
    /*   TESTING XXX - OLD CODE   */
    int holdSpreadType = spreadType->getInt();
    int holdSpreadType2 = spreadType2->getInt();
    float holdSpreadTypeMorph = spreadTypeMorph->getFloat();
  
    float holdCurveSpreadCurveMorph = curveSpreadCurveMorph->getFloat();
    
    bool drawControlPointsLines = drawControlPoints->getBool();
    bool reverseOrder = reverseCurveOrder->getBool();
    bool isFillShape = fillShape->getBool();

    int holdTransformOrder = transformOrder->getInt();

    float copyShiftX;
    float copyShiftY;
    float copyShiftZ;
    float copyRotateX;
    float copyRotateY;
    float copyRotateZ;
    float copyRotateMultiply;
    float copyAnchorX;
    float copyAnchorY;
    float copyAnchorZ;
    float copyScaleX;
    float copyScaleY;
    float copyScaleZ;
    
    float holdShiftX = shiftX->getFloat();
    float holdShiftY = shiftY->getFloat();
    float holdShiftZ = shiftZ->getFloat();
    float holdRotateMultiply = rotateMultiply->getFloat();
    float holdRotateX = rotateX->getFloat();
    float holdRotateY = rotateY->getFloat();
    float holdRotateZ = rotateZ->getFloat();
    float holdAnchorX = anchorX->getFloat();
    float holdAnchorY = anchorY->getFloat();
    float holdAnchorZ = anchorZ->getFloat();
    float holdScaleX = scaleX->getFloat();
    float holdScaleY = scaleY->getFloat();
    float holdScaleZ = scaleZ->getFloat();
    
    float holdShiftXEnd;
    float holdShiftYEnd;
    float holdShiftZEnd;
    float holdRotateXEnd;
    float holdRotateYEnd;
    float holdRotateZEnd;
    float holdAnchorXEnd;
    float holdAnchorYEnd;
    float holdAnchorZEnd;
    float holdScaleXEnd;
    float holdScaleYEnd;
    float holdScaleZEnd;
    
    float holdShiftXSpreadCurveMorph = shiftXSpreadCurveMorph->getFloat();
    float holdShiftYSpreadCurveMorph;
    float holdShiftZSpreadCurveMorph;
    float holdRotateXSpreadCurveMorph = rotateXSpreadCurveMorph->getFloat();
    float holdRotateYSpreadCurveMorph;
    float holdRotateZSpreadCurveMorph;
    float holdAnchorXSpreadCurveMorph = anchorXSpreadCurveMorph->getFloat();
    float holdAnchorYSpreadCurveMorph;
    float holdAnchorZSpreadCurveMorph;
    float holdScaleXSpreadCurveMorph = scaleXSpreadCurveMorph->getFloat();
    float holdScaleYSpreadCurveMorph;
    float holdScaleZSpreadCurveMorph;
    
    bool holdShiftXEndIgnore = shiftXEndIgnore->getBool();
    bool holdShiftYEndIgnore = shiftYEndIgnore->getBool();
    bool holdShiftZEndIgnore = shiftZEndIgnore->getBool();
    bool holdRotateXEndIgnore = rotateXEndIgnore->getBool();
    bool holdRotateYEndIgnore = rotateYEndIgnore->getBool();
    bool holdRotateZEndIgnore = rotateZEndIgnore->getBool();
    bool holdAnchorXEndIgnore = anchorXEndIgnore->getBool();
    bool holdAnchorYEndIgnore = anchorYEndIgnore->getBool();
    bool holdAnchorZEndIgnore = anchorZEndIgnore->getBool();
    bool holdScaleXEndIgnore = scaleXEndIgnore->getBool();
    bool holdScaleYEndIgnore;
    bool holdScaleZEndIgnore;
    
    if (!holdShiftXEndIgnore) {
        holdShiftXEnd = shiftXEnd->getFloat();
    };
    if (!holdShiftYEndIgnore) {
        holdShiftYEnd = shiftYEnd->getFloat();
    };
    if (!holdShiftZEndIgnore) {
        holdShiftZEnd = shiftZEnd->getFloat();
    };
    if (!holdRotateXEndIgnore) {
        holdRotateXEnd = rotateXEnd->getFloat();
    };
    if (!holdRotateYEndIgnore) {
        holdRotateYEnd = rotateYEnd->getFloat();
    };
    if (!holdRotateZEndIgnore) {
        holdRotateZEnd = rotateZEnd->getFloat();
    };
    if (!holdAnchorXEndIgnore) {
        holdAnchorXEnd = anchorXEnd->getFloat();
    };
    if (!holdAnchorYEndIgnore) {
        holdAnchorYEnd = anchorYEnd->getFloat();
    };
    if (!holdAnchorZEndIgnore) {
        holdAnchorZEnd = anchorZEnd->getFloat();
    };
    if (!holdScaleXEndIgnore) {
        holdScaleXEnd = scaleXEnd->getFloat();
    };
    if (!useScaleXForScaleY) {
        holdScaleYEndIgnore = scaleYEndIgnore->getBool();
        if (!holdScaleYEndIgnore) {
            holdScaleYEnd = scaleYEnd->getFloat();
        };
    };
    if (!useScaleXForScaleZ) {
        holdScaleZEndIgnore = scaleZEndIgnore->getBool();
        if (!holdScaleZEndIgnore) {
            holdScaleZEnd = scaleZEnd->getFloat();
        };
    };
    
    if (isFillShape) {
        // draw twice if filled and fill color is different
        if  (useColorForFillColor == false) {
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
    startH = colorHue->getFloat();
    startHR = colorHueRotate->getFloat();
    startS = colorSaturation->getFloat();
    startB = colorBrightness->getFloat();
    startA = colorAlpha->getFloat();
    if (useColorHueForEndColor) {
        endH = startH;
    } else {
        endH = colorHueEnd->getFloat();
        endHR = colorHueRotateEnd->getFloat();
    };
    if (useColorSaturationForEndColor) {
        endS = startS;
    } else {
        endS = colorSaturationEnd->getFloat();
    };
    if (useColorBrightnessForEndColor) {
        endB = startB;
    } else {
        endB = colorBrightnessEnd->getFloat();
    };
    if (useColorAlphaForEndColor) {
        endA = startA;
    } else {
        endA = colorAlphaEnd->getFloat();
    };
    ;
    ofColor startColor = TXFunctions::txGetColor(startH, startS, startB, startA,  startHR, colorHSBAsRGB);
    ofColor endColor = TXFunctions::txGetColor(endH, endS, endB, endA,  endHR, colorHSBAsRGB);
    ofColor startFillColor, endFillColor;
    float startFillH, startFillHR, startFillS, startFillB, startFillA;
    float endFillH, endFillHR, endFillS, endFillB, endFillA;
    if (useColorForFillColor) {
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

    for (int curveIndex = 0; curveIndex < totalCurves; curveIndex++){
        float curveNo;
        if (reverseOrder) {
            curveNo = curveIndex;
        } else {
            curveNo = totalCurves - 1 - curveIndex;
        };
        float autoCurveStartX, autoCurveStartY, autoCurveEnd1X, autoCurveEnd1Y, autoCurveEnd2X, autoCurveEnd2Y;

        float proportion;
        float curveSpreadProportion;
        float shiftXSpreadProportion;
        float shiftYSpreadProportion;
        float shiftZSpreadProportion;
        float rotateXSpreadProportion;
        float rotateYSpreadProportion;
        float rotateZSpreadProportion;
        float anchorXSpreadProportion;
        float anchorYSpreadProportion;
        float anchorZSpreadProportion;
        float scaleXSpreadProportion;
        float scaleYSpreadProportion;
        float scaleZSpreadProportion;
        if (curveNo == 0) {
            proportion = 0;
        } else if (curveNo == (totalCurves-1)){
            proportion = 1;
        } else {
            proportion = (float) curveNo / (totalCurves-1);
        };
        
        /*   TESTING XXX - OLD CODE */
        
        float proportion2, colorMix;
        vector<ofVec2f> overlayPoints;
        vector<ofVec2f> overlayLinePoints;

        if (totalCurves == 1) {
            if (holdSpreadTypeMorph == 0) {
                colorMix = ofxTweenLite::tween(0, 1.0, 0,  (ofEaseFunction) holdSpreadType);
            } else if (holdSpreadTypeMorph == 1) {
                colorMix = ofxTweenLite::tween(0, 1.0, 0,  (ofEaseFunction) holdSpreadType2);
            } else {
                proportion = ofxTweenLite::tween(0, 1.0, 0,  (ofEaseFunction) holdSpreadType);
                proportion2 = ofxTweenLite::tween(0, 1.0, 0,  (ofEaseFunction) holdSpreadType2);
                colorMix = ofLerp(proportion, proportion2, holdSpreadTypeMorph);
            };
        } else {
            if (holdSpreadTypeMorph == 0) {
                colorMix = ofxTweenLite::tween(0, 1.0, (curveNo / (totalCurves - 1)),  (ofEaseFunction) holdSpreadType);
            } else if (holdSpreadTypeMorph == 1) {
                colorMix = ofxTweenLite::tween(0, 1.0, (curveNo / (totalCurves - 1)),  (ofEaseFunction) holdSpreadType2);
            } else {
                proportion = ofxTweenLite::tween(0, 1.0, (curveNo / (totalCurves - 1)),  (ofEaseFunction) holdSpreadType);
                proportion2 = ofxTweenLite::tween(0, 1.0, (curveNo / (totalCurves - 1)),  (ofEaseFunction) holdSpreadType2);
                colorMix = ofLerp(proportion, proportion2, holdSpreadTypeMorph);
            };
        };
        /*   TESTING XXX - OLD CODE */
        

        shiftXSpreadProportion =  TXFunctions::getInterpCurves(shiftXSpreadCurve, shiftXSpreadCurve2, proportion, holdShiftXSpreadCurveMorph);
        if (useShiftXSpreadCurveForShiftY) {
            shiftYSpreadProportion =  shiftXSpreadProportion;
        } else {
            holdShiftYSpreadCurveMorph = shiftYSpreadCurveMorph->getFloat();
            shiftYSpreadProportion =  TXFunctions::getInterpCurves(shiftYSpreadCurve, shiftYSpreadCurve2, proportion, holdShiftYSpreadCurveMorph);
        };
        if (useShiftXSpreadCurveForShiftZ) {
            shiftZSpreadProportion =  shiftXSpreadProportion;
        } else {
            holdShiftZSpreadCurveMorph = shiftZSpreadCurveMorph->getFloat();
            shiftZSpreadProportion =  TXFunctions::getInterpCurves(shiftZSpreadCurve, shiftZSpreadCurve2, proportion, holdShiftZSpreadCurveMorph);
        };
        
        rotateXSpreadProportion =  TXFunctions::getInterpCurves(rotateXSpreadCurve, rotateXSpreadCurve2, proportion, holdRotateXSpreadCurveMorph);
        if (useRotateXSpreadCurveForRotateY) {
            rotateYSpreadProportion =  rotateXSpreadProportion;
        } else {
            holdRotateYSpreadCurveMorph = rotateYSpreadCurveMorph->getFloat();
            rotateYSpreadProportion =  TXFunctions::getInterpCurves(rotateYSpreadCurve, rotateYSpreadCurve2, proportion, holdRotateYSpreadCurveMorph);
        };
        if (useRotateXSpreadCurveForRotateZ) {
            rotateZSpreadProportion = rotateXSpreadProportion;
        } else {
            holdRotateZSpreadCurveMorph = rotateZSpreadCurveMorph->getFloat();
            rotateZSpreadProportion =  TXFunctions::getInterpCurves(rotateZSpreadCurve, rotateZSpreadCurve2, proportion, holdRotateZSpreadCurveMorph);
        };
        
        anchorXSpreadProportion =  TXFunctions::getInterpCurves(anchorXSpreadCurve, anchorXSpreadCurve2, proportion, holdAnchorXSpreadCurveMorph);
        if (useAnchorXSpreadCurveForAnchorY) {
            anchorYSpreadProportion = anchorXSpreadProportion;
        } else {
            holdAnchorYSpreadCurveMorph = anchorYSpreadCurveMorph->getFloat();
            anchorYSpreadProportion =  TXFunctions::getInterpCurves(anchorYSpreadCurve, anchorYSpreadCurve2, proportion, holdAnchorYSpreadCurveMorph);
        };
        if (useAnchorXSpreadCurveForAnchorZ) {
            anchorZSpreadProportion = anchorXSpreadProportion;
        } else {
            holdAnchorZSpreadCurveMorph = anchorZSpreadCurveMorph->getFloat();
            anchorZSpreadProportion =  TXFunctions::getInterpCurves(anchorZSpreadCurve, anchorZSpreadCurve2, proportion, holdAnchorZSpreadCurveMorph);
        };
        
        scaleXSpreadProportion =  TXFunctions::getInterpCurves(scaleXSpreadCurve, scaleXSpreadCurve2, proportion, holdScaleXSpreadCurveMorph);
        if (useScaleXSpreadCurveForScaleY) {
            scaleYSpreadProportion = scaleXSpreadProportion;
        } else {
            holdScaleYSpreadCurveMorph = scaleYSpreadCurveMorph->getFloat();
            scaleYSpreadProportion =  TXFunctions::getInterpCurves(scaleYSpreadCurve, scaleYSpreadCurve2, proportion, holdScaleYSpreadCurveMorph);
        };
        if (useScaleXSpreadCurveForScaleZ) {
            scaleZSpreadProportion = scaleXSpreadProportion;
        } else {
            holdScaleZSpreadCurveMorph = scaleZSpreadCurveMorph->getFloat();
            scaleZSpreadProportion =  TXFunctions::getInterpCurves(scaleZSpreadCurve, scaleZSpreadCurve2, proportion, holdScaleZSpreadCurveMorph);
        };
        
        if (holdShiftXEndIgnore) {
            copyShiftX = holdShiftX;
        } else {
            copyShiftX = TXFunctions::getInterp(holdShiftX, holdShiftXEnd, shiftXSpreadProportion);
        };
        if (holdShiftYEndIgnore) {
            copyShiftY = holdShiftY;
        } else {
            copyShiftY = TXFunctions::getInterp(holdShiftY, holdShiftYEnd, shiftYSpreadProportion);
        };
        if (holdShiftZEndIgnore) {
            copyShiftZ = holdShiftZ;
        } else {
            copyShiftZ = TXFunctions::getInterp(holdShiftZ, holdShiftZEnd, shiftZSpreadProportion);
        };
        if (holdRotateXEndIgnore) {
            copyRotateX = holdRotateX;
        } else {
            copyRotateX = TXFunctions::getInterp(holdRotateX, holdRotateXEnd, rotateXSpreadProportion);
        };
        if (holdRotateYEndIgnore) {
            copyRotateY = holdRotateY;
        } else {
            copyRotateY = TXFunctions::getInterp(holdRotateY, holdRotateYEnd, rotateYSpreadProportion);
        };
        if (holdRotateZEndIgnore) {
            copyRotateZ = holdRotateZ;
        } else {
            copyRotateZ = TXFunctions::getInterp(holdRotateZ, holdRotateZEnd, rotateZSpreadProportion);
        };
        copyRotateMultiply = holdRotateMultiply;
        if (holdAnchorXEndIgnore) {
            copyAnchorX = holdAnchorX;
        } else {
            copyAnchorX = TXFunctions::getInterp(holdAnchorX, holdAnchorXEnd, anchorXSpreadProportion);
        };
        if (holdAnchorYEndIgnore) {
            copyAnchorY = holdAnchorY;
        } else {
            copyAnchorY = TXFunctions::getInterp(holdAnchorY, holdAnchorYEnd, anchorYSpreadProportion);
        };
        if (holdAnchorZEndIgnore) {
            copyAnchorZ = holdAnchorZ;
        } else {
            copyAnchorZ = TXFunctions::getInterp(holdAnchorZ, holdAnchorZEnd, anchorZSpreadProportion);
        };
        if (holdScaleXEndIgnore) {
            copyScaleX = holdScaleX;
        } else {
            copyScaleX = TXFunctions::getInterp(holdScaleX, holdScaleXEnd, scaleXSpreadProportion);
        };
        if (useScaleXForScaleY) {
            copyScaleY = copyScaleX;
        } else {
            if (holdScaleYEndIgnore) {
                copyScaleY = holdScaleY;
            } else {
                copyScaleY = TXFunctions::getInterp(holdScaleY, holdScaleYEnd, scaleYSpreadProportion);
            };
        };
        if (useScaleXForScaleZ) {
            copyScaleZ = copyScaleX;
        } else {
            if (holdScaleZEndIgnore) {
                copyScaleZ = holdScaleZ;
            } else {
                copyScaleZ = TXFunctions::getInterp(holdScaleZ, holdScaleZEnd, scaleZSpreadProportion);
            };
        };

        
        // transform
        ofPushMatrix();
        ofTranslate(copyAnchorX * getMaxWidth(), copyAnchorY * getMaxHeight(), copyAnchorZ * getMaxDepth());
        switch (holdTransformOrder) {
            case TXTRANSFORMORDER_SHIFTROTATESCALE:
                ofTranslate(copyShiftX * getMaxWidth(), copyShiftY * getMaxHeight(), copyShiftZ * getMaxDepth());
                rotate(copyRotateMultiply * copyRotateX, copyRotateMultiply * copyRotateY, copyRotateMultiply * copyRotateZ);
                ofScale(copyScaleX, copyScaleY, copyScaleZ);
                break;
            case TXTRANSFORMORDER_SHIFTSCALEROTATE:
                ofTranslate(copyShiftX * getMaxWidth(), copyShiftY * getMaxHeight(), copyShiftZ * getMaxDepth());
                ofScale(copyScaleX, copyScaleY, copyScaleZ);
                rotate(copyRotateMultiply * copyRotateX, copyRotateMultiply * copyRotateY, copyRotateMultiply * copyRotateZ);
                break;
            case TXTRANSFORMORDER_ROTATESCALESHIFT:
                rotate(copyRotateMultiply * copyRotateX, copyRotateMultiply * copyRotateY, copyRotateMultiply * copyRotateZ);
                ofScale(copyScaleX, copyScaleY, copyScaleZ);
                ofTranslate(copyShiftX * getMaxWidth(), copyShiftY * getMaxHeight(), copyShiftZ * getMaxDepth());
                break;
            case TXTRANSFORMORDER_ROTATESHIFTSCALE:
                rotate(copyRotateMultiply * copyRotateX, copyRotateMultiply * copyRotateY, copyRotateMultiply * copyRotateZ);
                ofTranslate(copyShiftX * getMaxWidth(), copyShiftY * getMaxHeight(), copyShiftZ * getMaxDepth());
                ofScale(copyScaleX, copyScaleY, copyScaleZ);
                break;
            case TXTRANSFORMORDER_SCALESHIFTROTATE:
                ofScale(copyScaleX, copyScaleY, copyScaleZ);
                ofTranslate(copyShiftX * getMaxWidth(), copyShiftY * getMaxHeight(), copyShiftZ * getMaxDepth());
                rotate(copyRotateMultiply * copyRotateX, copyRotateMultiply * copyRotateY, copyRotateMultiply * copyRotateZ);
                break;
            case TXTRANSFORMORDER_SCALEROTATESHIFT:
                ofScale(copyScaleX, copyScaleY, copyScaleZ);
                rotate(copyRotateMultiply * copyRotateX, copyRotateMultiply * copyRotateY, copyRotateMultiply * copyRotateZ);
                ofTranslate(copyShiftX * getMaxWidth(), copyShiftY * getMaxHeight(), copyShiftZ * getMaxDepth());
                break;
            default:
                ofTranslate(copyShiftX * getMaxWidth(), copyShiftY * getMaxHeight(), copyShiftZ * getMaxDepth());
                rotate(copyRotateMultiply * copyRotateX, copyRotateMultiply * copyRotateY, copyRotateMultiply * copyRotateZ);
                ofScale(copyScaleX, copyScaleY, copyScaleZ);
                break;
        }
        ofTranslate(-copyAnchorX * getMaxWidth(), -copyAnchorY * getMaxHeight(), -copyAnchorZ * getMaxDepth());
        

        // build point coord arrays
        float arrdrawX[maxCurvePoints];
        float arrdrawY[maxCurvePoints];
        float arrcontrol1X[maxCurvePoints];
        float arrcontrol1Y[maxCurvePoints];
        float arrcontrol2X[maxCurvePoints];
        float arrcontrol2Y[maxCurvePoints];
        // for all points
       for (int pointNo = 0; pointNo < totalPoints; pointNo++){
            arrdrawX[pointNo] = getMaxWidth() * arrCurvePoints[pointNo].getInterpDrawX(curveNo, totalCurves, holdSpreadType, holdSpreadType2, holdSpreadTypeMorph);
            arrdrawY[pointNo] = getMaxHeight() * arrCurvePoints[pointNo].getInterpDrawY(curveNo, totalCurves, holdSpreadType, holdSpreadType2, holdSpreadTypeMorph);
            
            if ((pointNo > 0) && isBezier ) {
                arrcontrol1X[pointNo] = getMaxWidth() * arrCurvePoints[pointNo].getInterpControl1X(curveNo, totalCurves, holdSpreadType, holdSpreadType2, holdSpreadTypeMorph);
                arrcontrol1Y[pointNo] = getMaxHeight() * arrCurvePoints[pointNo].getInterpControl1Y(curveNo, totalCurves, holdSpreadType, holdSpreadType2, holdSpreadTypeMorph);
                arrcontrol2X[pointNo] = getMaxWidth() * arrCurvePoints[pointNo].getInterpControl2X(curveNo, totalCurves, holdSpreadType, holdSpreadType2, holdSpreadTypeMorph);
                arrcontrol2Y[pointNo] = getMaxHeight() * arrCurvePoints[pointNo].getInterpControl2Y(curveNo, totalCurves, holdSpreadType, holdSpreadType2, holdSpreadTypeMorph);
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
                    autoCurveStartX = getMaxWidth() * autoCurveStart.getInterpControl1X(curveNo, totalCurves, holdSpreadType, holdSpreadType2, holdSpreadTypeMorph);
                    autoCurveStartY = getMaxHeight() * autoCurveStart.getInterpControl1Y(curveNo, totalCurves, holdSpreadType, holdSpreadType2, holdSpreadTypeMorph);
                };
                if (useLastPointForAutoCurveEnd) {
                    autoCurveEnd1X = arrdrawX[totalPoints - 1];
                    autoCurveEnd1Y = arrdrawY[totalPoints - 1];
                    autoCurveEnd2X = autoCurveEnd1X;
                    autoCurveEnd2Y = autoCurveEnd1Y;
                } else {
                    autoCurveEnd1X = getMaxWidth() * autoCurveEnd.getInterpControl1X(curveNo, totalCurves, holdSpreadType, holdSpreadType2, holdSpreadTypeMorph);
                    autoCurveEnd1Y = getMaxHeight() * autoCurveEnd.getInterpControl1Y(curveNo, totalCurves, holdSpreadType, holdSpreadType2, holdSpreadTypeMorph);
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
                if (swapColorWithFillColor) {
                    ofSetColor(startColor.getLerped(endColor, colorMix));
                } else {
                    ofSetColor(startFillColor.getLerped(endFillColor, colorMix));
                };
            } else {
                if (swapColorWithFillColor) {
                    ofSetColor(startFillColor.getLerped(endFillColor, colorMix));
                } else {
                    ofSetColor(startColor.getLerped(endColor, colorMix));
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
                ofSetCircleResolution(12);
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
        
    }; // end of for all curves
    
    ofPopMatrix();
    ofDisableAlphaBlending();
    ofSetColor(255.0f);
}

void TXDraw3DCurves::rotate(float rotX, float rotY, float rotZ) {
    ofVec3f Znormal(0, 0, 1);
    ofVec3f Xnormal(1, 0, 0);
    //ofVec3f Ynormal(1, 0, 1);
    ofVec3f Ynormal(0, 1, 0);
    
    //ofQuaternion constructor: angle, ofVec3f axis
    ofQuaternion qr (rotZ, Znormal); // quat roll.
    ofQuaternion qp (rotX, Xnormal); // quat pitch.
    ofQuaternion qh (rotY, Ynormal); // quat heading or yaw.
    ofQuaternion qt; // quat total.
    // The order IS IMPORTANT. Apply roll first, then pitch, then heading.
    qt = qr * qp * qh;
    
    ofVec3f qaxis;
    float qangle;
    qt.getRotate(qangle, qaxis);
    ofRotate(qangle, qaxis.x, qaxis.y, qaxis.z);
}

