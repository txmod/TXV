/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXDrawTransform3DDelay.h"
//#include "ofxTweenLite.h"
#include "TXFunctions.h"
#include "TXSystem.h"

TXDrawTransform3DDelay::TXDrawTransform3DDelay() {
    setup();
}

void TXDrawTransform3DDelay::setup(){
//    TXModParameterBoolArgs holdModParamBoolArgs;
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
    
    holdModParamIntArgs.name = "delayFrames";
    holdModParamIntArgs.fixedValue = 60;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = maxDelayFrames;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = maxDelayFrames;
	delayFrames = createModParameter(holdModParamIntArgs);
    parameters.add(delayFrames->parameters);
    
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
    
    holdModParamFloatArgs.name = "shiftY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
	shiftY = createModParameter(holdModParamFloatArgs);
    parameters.add(shiftY->parameters);
    
    holdModParamFloatArgs.name = "shiftZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
	shiftZ = createModParameter(holdModParamFloatArgs);
    parameters.add(shiftZ->parameters);
    
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
    
    holdModParamFloatArgs.name = "anchorY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	anchorY = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorY->parameters);
    
    holdModParamFloatArgs.name = "anchorZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 0.0;
	anchorZ = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorZ->parameters);
    
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

    // init delays
    shiftXDelay.assign(maxDelayFrames, 0.0);
    shiftYDelay.assign(maxDelayFrames, 0.0);
    shiftZDelay.assign(maxDelayFrames, 0.0);
    rotateXDelay.assign(maxDelayFrames, 0.0);
    rotateYDelay.assign(maxDelayFrames, 0.0);
    rotateZDelay.assign(maxDelayFrames, 0.0);
    anchorXDelay.assign(maxDelayFrames, 0.0);
    anchorYDelay.assign(maxDelayFrames, 0.0);
    anchorZDelay.assign(maxDelayFrames, 0.0);
    scaleXDelay.assign(maxDelayFrames, 0.0);
    scaleYDelay.assign(maxDelayFrames, 0.0);
    scaleZDelay.assign(maxDelayFrames, 0.0);

}

void TXDrawTransform3DDelay::update() {
    currentDelayFrame = (currentDelayFrame + 1) % (maxDelayFrames);
    shiftXDelay[currentDelayFrame] = shiftX->getFloat();
    shiftYDelay[currentDelayFrame] = shiftY->getFloat();
    shiftZDelay[currentDelayFrame] = shiftZ->getFloat();
    rotateXDelay[currentDelayFrame] = rotateX->getFloat();
    rotateYDelay[currentDelayFrame] = rotateY->getFloat();
    rotateZDelay[currentDelayFrame] = rotateZ->getFloat();
    anchorXDelay[currentDelayFrame] = anchorX->getFloat();
    anchorYDelay[currentDelayFrame] = anchorY->getFloat();
    anchorZDelay[currentDelayFrame] = anchorZ->getFloat();
    scaleXDelay[currentDelayFrame] = scaleX->getFloat();
    scaleYDelay[currentDelayFrame] = scaleY->getFloat();
    scaleZDelay[currentDelayFrame] = scaleZ->getFloat();
};

void TXDrawTransform3DDelay::draw(){
    if (!drawActive->getBool()) {
        return;
    };
    int holdNumCopies = numCopies->getInt();
    int holdTransformOrder = transformOrder->getInt();
    int holdDrawLayersRule = drawLayersRule->getInt();

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
    
    float holdRotateMultiply = rotateMultiply->getFloat();
    int holdDelayFrames = min(delayFrames->getInt(), (int)parentSystem->getCurrentFrameNo() - 1);
    
    // draw copies in reverse order
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
        float shiftXFrameNo = fmod(maxDelayFrames + currentDelayFrame - (shiftXSpreadProportion *holdDelayFrames), maxDelayFrames);
        float shiftYFrameNo = fmod(maxDelayFrames + currentDelayFrame - (shiftYSpreadProportion *holdDelayFrames), maxDelayFrames);
        float shiftZFrameNo = fmod(maxDelayFrames + currentDelayFrame - (shiftZSpreadProportion *holdDelayFrames), maxDelayFrames);
        float rotateXFrameNo = fmod(maxDelayFrames + currentDelayFrame - (rotateXSpreadProportion *holdDelayFrames), maxDelayFrames);
        float rotateYFrameNo = fmod(maxDelayFrames + currentDelayFrame - (rotateYSpreadProportion *holdDelayFrames), maxDelayFrames);
        float rotateZFrameNo = fmod(maxDelayFrames + currentDelayFrame - (rotateZSpreadProportion *holdDelayFrames), maxDelayFrames);
        float anchorXFrameNo = fmod(maxDelayFrames + currentDelayFrame - (anchorXSpreadProportion *holdDelayFrames), maxDelayFrames);
        float anchorYFrameNo = fmod(maxDelayFrames + currentDelayFrame - (anchorYSpreadProportion *holdDelayFrames), maxDelayFrames);
        float anchorZFrameNo = fmod(maxDelayFrames + currentDelayFrame - (anchorZSpreadProportion *holdDelayFrames), maxDelayFrames);
        float scaleXFrameNo = fmod(maxDelayFrames + currentDelayFrame - (scaleXSpreadProportion *holdDelayFrames), maxDelayFrames);
        float scaleYFrameNo = fmod(maxDelayFrames + currentDelayFrame - (scaleYSpreadProportion *holdDelayFrames), maxDelayFrames);
        float scaleZFrameNo = fmod(maxDelayFrames + currentDelayFrame - (scaleZSpreadProportion *holdDelayFrames), maxDelayFrames);

        float holdAnchorX = getDelayedVal(anchorXDelay, anchorXFrameNo) * getMaxWidth();
        float holdAnchorY = getDelayedVal(anchorYDelay, anchorYFrameNo) * getMaxHeight();
        float holdAnchorZ = getDelayedVal(anchorZDelay, anchorZFrameNo) * getMaxDepth();
        float holdRotateX = holdRotateMultiply * getDelayedVal(rotateXDelay, rotateXFrameNo);
        float holdRotateY = holdRotateMultiply * getDelayedVal(rotateYDelay, rotateYFrameNo);
        float holdRotateZ = holdRotateMultiply * getDelayedVal(rotateZDelay, rotateZFrameNo);
        float holdShiftX = getDelayedVal(shiftXDelay, shiftXFrameNo) * getMaxWidth();
        float holdShiftY = getDelayedVal(shiftYDelay, shiftYFrameNo) * getMaxHeight();
        float holdShiftZ = getDelayedVal(shiftZDelay, shiftZFrameNo) * getMaxDepth();
        float holdScaleX, holdScaleY, holdScaleZ;
        holdScaleX = getDelayedVal(scaleXDelay, scaleXFrameNo);
        if (useScaleXForScaleY) {
            holdScaleY = holdScaleX;
        } else {
            holdScaleY = getDelayedVal(scaleYDelay, scaleYFrameNo);
        };
        if (useScaleXForScaleZ) {
            holdScaleZ = holdScaleX;
        } else {
            holdScaleZ = getDelayedVal(scaleZDelay, scaleZFrameNo);
        };
        ofPushMatrix();
        ofTranslate(holdAnchorX, holdAnchorY, holdAnchorZ);
        switch (holdTransformOrder) {
            case TXTRANSFORMORDER_SHIFTROTATESCALE:
                ofTranslate(holdShiftX, holdShiftY, holdShiftZ);
                rotate(holdRotateX, holdRotateY, holdRotateZ);
                ofScale(holdScaleX, holdScaleY, holdScaleZ);
                break;
            case TXTRANSFORMORDER_SHIFTSCALEROTATE:
                ofTranslate(holdShiftX, holdShiftY, holdShiftZ);
                ofScale(holdScaleX, holdScaleY, holdScaleZ);
                rotate(holdRotateX, holdRotateY, holdRotateZ);
                break;
            case TXTRANSFORMORDER_ROTATESCALESHIFT:
                rotate(holdRotateX, holdRotateY, holdRotateZ);
                ofScale(holdScaleX, holdScaleY, holdScaleZ);
                ofTranslate(holdShiftX, holdShiftY, holdShiftZ);
                break;
            case TXTRANSFORMORDER_ROTATESHIFTSCALE:
                rotate(holdRotateX, holdRotateY, holdRotateZ);
                ofTranslate(holdShiftX, holdShiftY, holdShiftZ);
                ofScale(holdScaleX, holdScaleY, holdScaleZ);
                break;
            case TXTRANSFORMORDER_SCALESHIFTROTATE:
                ofScale(holdScaleX, holdScaleY, holdScaleZ);
                ofTranslate(holdShiftX, holdShiftY, holdShiftZ);
                rotate(holdRotateX, holdRotateY, holdRotateZ);
                break;
            case TXTRANSFORMORDER_SCALEROTATESHIFT:
                ofScale(holdScaleX, holdScaleY, holdScaleZ);
                rotate(holdRotateX, holdRotateY, holdRotateZ);
                ofTranslate(holdShiftX, holdShiftY, holdShiftZ);
                break;
            default:
                ofTranslate(holdShiftX, holdShiftY, holdShiftZ);
                rotate(holdRotateX, holdRotateY, holdRotateZ);
                ofScale(holdScaleX, holdScaleY, holdScaleZ);
                break;
        }
        ofTranslate(-holdAnchorX, -holdAnchorY, -holdAnchorZ);
        
        // draw layers
        TXDrawLayersBase::draw((TXDRAWLAYERSRULE) holdDrawLayersRule);
        
        ofPopMatrix();
    };
}

void TXDrawTransform3DDelay::rotate(float rotX, float rotY, float rotZ) {
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

float TXDrawTransform3DDelay::getDelayedVal(const vector<float> & delayVector, const float & delayFrames) {
    int index1, index2;
    float proportion, outval;
    index1 = (int) delayFrames;
    index2 = (index1 + 1) % maxDelayFrames;
    proportion = delayFrames - index1;
    outval = ofLerp(delayVector[index1], delayVector[index2], proportion);
    return outval;
}


