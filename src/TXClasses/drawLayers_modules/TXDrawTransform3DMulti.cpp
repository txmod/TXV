/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXDrawTransform3DMulti.h"
#include "TXFunctions.h"


TXDrawTransform3DMulti::TXDrawTransform3DMulti() {
    setup();
}

void TXDrawTransform3DMulti::setup(){
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    
    // create input paramaters
    initialiseParameters();
    
    holdModParamIntArgs.name = "drawLayersRule";
    holdModParamIntArgs.fixedValue = TXDRAWLAYERSRULE_ALLEXCEPT20;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXDRAWLAYERSRULE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXDRAWLAYERSRULE_TOTAL - 1;
	drawLayersRule = createModParameter(holdModParamIntArgs);
    parameters.add(drawLayersRule->parameters);
    
    holdModParamIntArgs.name = "numCopies";
    holdModParamIntArgs.fixedValue = 4;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = maxCopies;
    holdModParamIntArgs.softMin = 1;
    holdModParamIntArgs.softMax = 50;
	numCopies = createModParameter(holdModParamIntArgs);
    parameters.add(numCopies->parameters);
    
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
    
    holdModParamFloatArgs.name = "shiftXSpreadCurvePhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    shiftXSpreadCurvePhase = createModParameter(holdModParamFloatArgs);
    parameters.add(shiftXSpreadCurvePhase->parameters);
    
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
    
    holdModParamFloatArgs.name = "shiftYSpreadCurvePhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    shiftYSpreadCurvePhase = createModParameter(holdModParamFloatArgs);
    parameters.add(shiftYSpreadCurvePhase->parameters);
    
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
    
    holdModParamFloatArgs.name = "shiftZSpreadCurvePhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    shiftZSpreadCurvePhase = createModParameter(holdModParamFloatArgs);
    parameters.add(shiftZSpreadCurvePhase->parameters);
    
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
    
    holdModParamFloatArgs.name = "rotateXSpreadCurvePhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    rotateXSpreadCurvePhase = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateXSpreadCurvePhase->parameters);
    
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
    
    holdModParamFloatArgs.name = "rotateYSpreadCurvePhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    rotateYSpreadCurvePhase = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateYSpreadCurvePhase->parameters);
    
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
    
    holdModParamFloatArgs.name = "rotateZSpreadCurvePhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    rotateZSpreadCurvePhase = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateZSpreadCurvePhase->parameters);
    
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
    
    holdModParamFloatArgs.name = "anchorXSpreadCurvePhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    anchorXSpreadCurvePhase = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorXSpreadCurvePhase->parameters);
    
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
    
    holdModParamFloatArgs.name = "anchorYSpreadCurvePhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    anchorYSpreadCurvePhase = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorYSpreadCurvePhase->parameters);
    
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
    
    holdModParamFloatArgs.name = "anchorZSpreadCurvePhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    anchorZSpreadCurvePhase = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorZSpreadCurvePhase->parameters);
    
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
    
    holdModParamFloatArgs.name = "scaleXSpreadCurvePhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    scaleXSpreadCurvePhase = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleXSpreadCurvePhase->parameters);
    
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
    
    holdModParamFloatArgs.name = "scaleZSpreadCurvePhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    scaleZSpreadCurvePhase = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleZSpreadCurvePhase->parameters);
    
    parameters.add(useScaleXSpreadCurveForScaleY.set("useScaleXSpreadCurveForScaleY", false));
    parameters.add(useScaleXSpreadCurveForScaleZ.set("useScaleXSpreadCurveForScaleZ", false));
    
}

void TXDrawTransform3DMulti::draw(){
    if (!drawActive->getBool()) {
        return;
    };
    int holdNumCopies = numCopies->getInt();
    int holdTransformOrder = transformOrder->getInt();
    int holdDrawLayersRule = drawLayersRule->getInt();
    
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
    
    float holdShiftXSpreadCurvePhase = shiftXSpreadCurvePhase->getFloat();
    float holdShiftYSpreadCurvePhase;
    float holdShiftZSpreadCurvePhase;
    float holdRotateXSpreadCurvePhase = rotateXSpreadCurvePhase->getFloat();
    float holdRotateYSpreadCurvePhase;
    float holdRotateZSpreadCurvePhase;
    float holdAnchorXSpreadCurvePhase = anchorXSpreadCurvePhase->getFloat();
    float holdAnchorYSpreadCurvePhase;
    float holdAnchorZSpreadCurvePhase;
    float holdScaleXSpreadCurvePhase = scaleXSpreadCurvePhase->getFloat();
    float holdScaleYSpreadCurvePhase;
    float holdScaleZSpreadCurvePhase;
    
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
    
    // for (int copyNo = 0; copyNo < (holdNumCopies-1); copyNo++){
    // draw copiesin reverse order
    for (int copyNo = holdNumCopies-1; copyNo > -1; copyNo--){
      float proportion;
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
//        if (copyNo == 0) {
//            proportion = 0;
//        } else if (copyNo == (holdNumCopies-1)){
//            proportion = 1;
//        } else {
//            proportion = (float) copyNo / (holdNumCopies-1);
//        };
        if (holdNumCopies < 2) {
            proportion = 0.5;
        } else {
            proportion = (float) (0.5 + copyNo) / holdNumCopies;
        };
        
        shiftXSpreadProportion =  TXFunctions::getInterpPhaseCurves(shiftXSpreadCurve, shiftXSpreadCurve2, proportion, holdShiftXSpreadCurvePhase, holdShiftXSpreadCurveMorph);
        if (useShiftXSpreadCurveForShiftY) {
            shiftYSpreadProportion =  shiftXSpreadProportion;
        } else {
            holdShiftYSpreadCurvePhase = shiftYSpreadCurvePhase->getFloat();
            holdShiftYSpreadCurveMorph = shiftYSpreadCurveMorph->getFloat();
            shiftYSpreadProportion =  TXFunctions::getInterpPhaseCurves(shiftYSpreadCurve, shiftYSpreadCurve2, proportion, holdShiftYSpreadCurvePhase, holdShiftYSpreadCurveMorph);
        };
        if (useShiftXSpreadCurveForShiftZ) {
            shiftZSpreadProportion =  shiftXSpreadProportion;
        } else {
            holdShiftZSpreadCurvePhase = shiftZSpreadCurvePhase->getFloat();
            holdShiftZSpreadCurveMorph = shiftZSpreadCurveMorph->getFloat();
            shiftZSpreadProportion =  TXFunctions::getInterpPhaseCurves(shiftZSpreadCurve, shiftZSpreadCurve2, proportion, holdShiftZSpreadCurvePhase, holdShiftZSpreadCurveMorph);
        };
        
        rotateXSpreadProportion =  TXFunctions::getInterpPhaseCurves(rotateXSpreadCurve, rotateXSpreadCurve2, proportion, holdRotateXSpreadCurvePhase, holdRotateXSpreadCurveMorph);
        if (useRotateXSpreadCurveForRotateY) {
            rotateYSpreadProportion =  rotateXSpreadProportion;
        } else {
            holdRotateYSpreadCurvePhase = rotateYSpreadCurvePhase->getFloat();
            holdRotateYSpreadCurveMorph = rotateYSpreadCurveMorph->getFloat();
            rotateYSpreadProportion =  TXFunctions::getInterpPhaseCurves(rotateYSpreadCurve, rotateYSpreadCurve2, proportion, holdRotateYSpreadCurvePhase, holdRotateYSpreadCurveMorph);
        };
        if (useRotateXSpreadCurveForRotateZ) {
            rotateZSpreadProportion = rotateXSpreadProportion;
        } else {
            holdRotateZSpreadCurvePhase = rotateZSpreadCurvePhase->getFloat();
            holdRotateZSpreadCurveMorph = rotateZSpreadCurveMorph->getFloat();
            rotateZSpreadProportion =  TXFunctions::getInterpPhaseCurves(rotateZSpreadCurve, rotateZSpreadCurve2, proportion, holdRotateZSpreadCurvePhase, holdRotateZSpreadCurveMorph);
        };
        
        anchorXSpreadProportion =  TXFunctions::getInterpPhaseCurves(anchorXSpreadCurve, anchorXSpreadCurve2, proportion, holdAnchorXSpreadCurvePhase, holdAnchorXSpreadCurveMorph);
        if (useAnchorXSpreadCurveForAnchorY) {
            anchorYSpreadProportion = anchorXSpreadProportion;
        } else {
            holdAnchorYSpreadCurvePhase = anchorYSpreadCurvePhase->getFloat();
            holdAnchorYSpreadCurveMorph = anchorYSpreadCurveMorph->getFloat();
            anchorYSpreadProportion =  TXFunctions::getInterpPhaseCurves(anchorYSpreadCurve, anchorYSpreadCurve2, proportion, holdAnchorYSpreadCurvePhase, holdAnchorYSpreadCurveMorph);
        };
        if (useAnchorXSpreadCurveForAnchorZ) {
            anchorZSpreadProportion = anchorXSpreadProportion;
        } else {
            holdAnchorZSpreadCurvePhase = anchorZSpreadCurvePhase->getFloat();
            holdAnchorZSpreadCurveMorph = anchorZSpreadCurveMorph->getFloat();
            anchorZSpreadProportion =  TXFunctions::getInterpPhaseCurves(anchorZSpreadCurve, anchorZSpreadCurve2, proportion, holdAnchorZSpreadCurvePhase, holdAnchorZSpreadCurveMorph);
        };
        
        scaleXSpreadProportion =  TXFunctions::getInterpPhaseCurves(scaleXSpreadCurve, scaleXSpreadCurve2, proportion, holdScaleXSpreadCurvePhase, holdScaleXSpreadCurveMorph);
        if (useScaleXSpreadCurveForScaleY) {
            scaleYSpreadProportion = scaleXSpreadProportion;
        } else {
            holdScaleYSpreadCurvePhase = scaleYSpreadCurvePhase->getFloat();
            holdScaleYSpreadCurveMorph = scaleYSpreadCurveMorph->getFloat();
            scaleYSpreadProportion =  TXFunctions::getInterpPhaseCurves(scaleYSpreadCurve, scaleYSpreadCurve2, proportion, holdScaleYSpreadCurvePhase, holdScaleYSpreadCurveMorph);
        };
        if (useScaleXSpreadCurveForScaleZ) {
            scaleZSpreadProportion = scaleXSpreadProportion;
        } else {
            holdScaleZSpreadCurvePhase = scaleZSpreadCurvePhase->getFloat();
            holdScaleZSpreadCurveMorph = scaleZSpreadCurveMorph->getFloat();
            scaleZSpreadProportion =  TXFunctions::getInterpPhaseCurves(scaleZSpreadCurve, scaleZSpreadCurve2, proportion, holdScaleZSpreadCurvePhase, holdScaleZSpreadCurveMorph);
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

        // draw layers
        TXDrawLayersBase::draw((TXDRAWLAYERSRULE) holdDrawLayersRule);
        
        ofPopMatrix();
    };
}

void TXDrawTransform3DMulti::rotate(float rotX, float rotY, float rotZ) {
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



