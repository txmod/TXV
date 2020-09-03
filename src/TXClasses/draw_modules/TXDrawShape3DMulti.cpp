/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXSystem.h"
#include "TXDrawShape3DMulti.h"
#include "ofxTweenLite.h"
#include "TXFunctions.h"

// constructor
TXDrawShape3DMulti::TXDrawShape3DMulti() {
    setup();
}

// destructor
TXDrawShape3DMulti::~TXDrawShape3DMulti() {
    // remove listeners to relevent parameters:
    ofRemoveListener(shapeType->parameters.parameterChangedE(),this,&TXDrawShape3DMulti::shapeTypeChanged);
}

void TXDrawShape3DMulti::setup(){
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
    
    parameters.add(useImageAsTexture.set("useImageAsTexture", false));
    parameters.add(useExternalSourceImage.set("useExternalSourceImage", false));

    holdModParamIntArgs.name = "shapeType";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = total3DShapeTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = total3DShapeTypes - 1;
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
    
    parameters.add(mergeIntoSuperShape.set("mergeIntoSuperShape", false));
    
    holdModParamBoolArgs.name = "fillShape";
    holdModParamBoolArgs.fixedValue = true;
    holdModParamBoolArgs.fixedModMix = false;
	fillShape = createModParameter(holdModParamBoolArgs);
    parameters.add(fillShape->parameters);
    
    holdModParamIntArgs.name = "distortOrder";
    holdModParamIntArgs.fixedValue = TXSHAPE3DDISTORTORDER_WAVETWISTBEND;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTORDER_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTORDER_TOTAL - 1;
	distortOrder = createModParameter(holdModParamIntArgs);
    parameters.add(distortOrder->parameters);
    
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
    
    holdModParamFloatArgs.name = "depth";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	depth = createModParameter(holdModParamFloatArgs);
    parameters.add(depth->parameters);
    
    holdModParamFloatArgs.name = "depthEnd";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	depthEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(depthEnd->parameters);
    
    parameters.add(depthEndIgnore.set("depthEndIgnore", true));
    
    parameters.add(useMaxWidthToScaleDepth.set("useMaxWidthToScaleDepth", false));
    
    holdModParamFloatArgs.name = "radius";
    holdModParamFloatArgs.fixedValue = 0.2;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	radius = createModParameter(holdModParamFloatArgs);
    parameters.add(radius->parameters);
    
    holdModParamFloatArgs.name = "radiusEnd";
    holdModParamFloatArgs.fixedValue = 0.05;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	radiusEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(radiusEnd->parameters);
    
    parameters.add(radiusEndIgnore.set("radiusEndIgnore", true));
    
    holdModParamFloatArgs.name = "roundness";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	roundness = createModParameter(holdModParamFloatArgs);
    parameters.add(roundness->parameters);
    
    holdModParamFloatArgs.name = "roundnessEnd";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	roundnessEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(roundnessEnd->parameters);
    
    parameters.add(roundnessEndIgnore.set("roundnessEndIgnore", true));
    
    holdModParamIntArgs.name = "resolutionWidth";
    holdModParamIntArgs.fixedValue = 24;
    holdModParamIntArgs.hardMin = 2;
    holdModParamIntArgs.hardMax = 1024;
    holdModParamIntArgs.softMin = 2;
    holdModParamIntArgs.softMax = 128;
	resolutionWidth = createModParameter(holdModParamIntArgs);
    parameters.add(resolutionWidth->parameters);
    
    holdModParamIntArgs.name = "resolutionHeight";
    holdModParamIntArgs.fixedValue = 24;
    holdModParamIntArgs.hardMin = 2;
    holdModParamIntArgs.hardMax = 1024;
    holdModParamIntArgs.softMin = 2;
    holdModParamIntArgs.softMax = 128;
	resolutionHeight = createModParameter(holdModParamIntArgs);
    parameters.add(resolutionHeight->parameters);
    
    holdModParamIntArgs.name = "resolutionDepth";
    holdModParamIntArgs.fixedValue = 24;
    holdModParamIntArgs.hardMin = 2;
    holdModParamIntArgs.hardMax = 1024;
    holdModParamIntArgs.softMin = 2;
    holdModParamIntArgs.softMax = 128;
	resolutionDepth = createModParameter(holdModParamIntArgs);
    parameters.add(resolutionDepth->parameters);
    
    holdModParamIntArgs.name = "resolutionRadius";
    holdModParamIntArgs.fixedValue = 24;
    holdModParamIntArgs.hardMin = 2;
    holdModParamIntArgs.hardMax = 1024;
    holdModParamIntArgs.softMin = 2;
    holdModParamIntArgs.softMax = 128;
	resolutionRadius = createModParameter(holdModParamIntArgs);
    parameters.add(resolutionRadius->parameters);
    
    holdModParamIntArgs.name = "resolutionIsoSphere";
    holdModParamIntArgs.fixedValue = 3;
    holdModParamIntArgs.hardMin = 1;
    holdModParamIntArgs.hardMax = 5;
    holdModParamIntArgs.softMin = 1;
    holdModParamIntArgs.softMax = 5;
	resolutionIsoSphere = createModParameter(holdModParamIntArgs);
    parameters.add(resolutionIsoSphere->parameters);
    
    holdModParamIntArgs.name = "resolutionCap";
    holdModParamIntArgs.fixedValue = 12;
    holdModParamIntArgs.hardMin = 2;
    holdModParamIntArgs.hardMax = 1024;
    holdModParamIntArgs.softMin = 2;
    holdModParamIntArgs.softMax = 128;
	resolutionCap = createModParameter(holdModParamIntArgs);
    parameters.add(resolutionCap->parameters);

    parameters.add(resolutionParaShape.set("resolutionParaShape", 48, 2, 256));

    parameters.add(smoothDistortedParaShape.set("smoothDistortedParaShape", true));

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
    
    holdModParamFloatArgs.name = "x1";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	x1 = createModParameter(holdModParamFloatArgs);
    parameters.add(x1->parameters);
    
    holdModParamFloatArgs.name = "x1End";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	x1End = createModParameter(holdModParamFloatArgs);
    parameters.add(x1End->parameters);
    
    parameters.add(x1EndIgnore.set("x1EndIgnore", true));
    
    parameters.add(x1Quantize.set("x1Quantize", false));
    
    holdModParamFloatArgs.name = "x2";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	x2 = createModParameter(holdModParamFloatArgs);
    parameters.add(x2->parameters);
    
    holdModParamFloatArgs.name = "x2End";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	x2End = createModParameter(holdModParamFloatArgs);
    parameters.add(x2End->parameters);
    
    parameters.add(x2EndIgnore.set("x2EndIgnore", true));
    
    parameters.add(x2Quantize.set("x2Quantize", false));
    
    holdModParamFloatArgs.name = "x3";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	x3 = createModParameter(holdModParamFloatArgs);
    parameters.add(x3->parameters);
    
    holdModParamFloatArgs.name = "x3End";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	x3End = createModParameter(holdModParamFloatArgs);
    parameters.add(x3End->parameters);
    
    parameters.add(x3EndIgnore.set("x3EndIgnore", true));
    
    parameters.add(x3Quantize.set("x3Quantize", false));
    
    holdModParamFloatArgs.name = "y1";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	y1 = createModParameter(holdModParamFloatArgs);
    parameters.add(y1->parameters);
    
    holdModParamFloatArgs.name = "y1End";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	y1End = createModParameter(holdModParamFloatArgs);
    parameters.add(y1End->parameters);
    
    parameters.add(y1EndIgnore.set("y1EndIgnore", true));
    
    parameters.add(y1Quantize.set("y1Quantize", false));
    
    holdModParamFloatArgs.name = "y2";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	y2 = createModParameter(holdModParamFloatArgs);
    parameters.add(y2->parameters);
    
    holdModParamFloatArgs.name = "y2End";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	y2End = createModParameter(holdModParamFloatArgs);
    parameters.add(y2End->parameters);
    
    parameters.add(y2EndIgnore.set("y2EndIgnore", true));
    
    parameters.add(y2Quantize.set("y2Quantize", false));
    
    holdModParamFloatArgs.name = "y3";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	y3 = createModParameter(holdModParamFloatArgs);
    parameters.add(y3->parameters);
    
    holdModParamFloatArgs.name = "y3End";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	y3End = createModParameter(holdModParamFloatArgs);
    parameters.add(y3End->parameters);
    
    parameters.add(y3EndIgnore.set("y3EndIgnore", true));
    
    parameters.add(y3Quantize.set("y3Quantize", false));
    
    holdModParamFloatArgs.name = "z1";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	z1 = createModParameter(holdModParamFloatArgs);
    parameters.add(z1->parameters);
    
    holdModParamFloatArgs.name = "z1End";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	z1End = createModParameter(holdModParamFloatArgs);
    parameters.add(z1End->parameters);
    
    parameters.add(z1EndIgnore.set("z1EndIgnore", true));
    
    parameters.add(z1Quantize.set("z1Quantize", false));
    
    holdModParamFloatArgs.name = "z2";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	z2 = createModParameter(holdModParamFloatArgs);
    parameters.add(z2->parameters);
    
    holdModParamFloatArgs.name = "z2End";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	z2End = createModParameter(holdModParamFloatArgs);
    parameters.add(z2End->parameters);
    
    parameters.add(z2EndIgnore.set("z2EndIgnore", true));
    
    parameters.add(z2Quantize.set("z2Quantize", false));
    
    holdModParamFloatArgs.name = "z3";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	z3 = createModParameter(holdModParamFloatArgs);
    parameters.add(z3->parameters);
    
    holdModParamFloatArgs.name = "z3End";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	z3End = createModParameter(holdModParamFloatArgs);
    parameters.add(z3End->parameters);
    
    parameters.add(z3EndIgnore.set("z3EndIgnore", true));
    
    parameters.add(z3Quantize.set("z3Quantize", false));
    
    parameters.add(useXValsForY.set("useXValsForY", false));
    
    parameters.add(useXValsForZ.set("useXValsForZ", false));
    
    parameters.add(ignoreAllXYZVals.set("ignoreAllXYZVals", false));
    
    xyzValsSpreadCurve.setValueArrayToRamp(0, 1);
    xyzValsSpreadCurve.setName("xyzValsSpreadCurve");
    parameters.add(xyzValsSpreadCurve.parameters);
    
    xyzValsSpreadCurve2.setValueArrayToRamp(0, 1);
    xyzValsSpreadCurve2.setName("xyzValsSpreadCurve2");
    parameters.add(xyzValsSpreadCurve2.parameters);
    
    holdModParamFloatArgs.name = "xyzValsSpreadCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    xyzValsSpreadCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(xyzValsSpreadCurveMorph->parameters);
    
    holdModParamFloatArgs.name = "xyzValsSpreadCurvePhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    xyzValsSpreadCurvePhase = createModParameter(holdModParamFloatArgs);
    parameters.add(xyzValsSpreadCurvePhase->parameters);
    
    holdModParamFloatArgs.name = "positionX";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	positionX = createModParameter(holdModParamFloatArgs);
    parameters.add(positionX->parameters);
    
    holdModParamFloatArgs.name = "positionXEnd";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	positionXEnd = createModParameter(holdModParamFloatArgs);
    parameters.add(positionXEnd->parameters);
    
    parameters.add(positionXEndIgnore.set("positionXEndIgnore", true));
    
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
    
    parameters.add(usePosXSpreadCurveForPosZ.set("usePosXSpreadCurveForPosZ", false));

    positionZSpreadCurve.setValueArrayToRamp(0, 1);
    positionZSpreadCurve.setName("positionZSpreadCurve");
    parameters.add(positionZSpreadCurve.parameters);
    
    positionZSpreadCurve2.setValueArrayToRamp(0, 1);
    positionZSpreadCurve2.setName("positionZSpreadCurve2");
    parameters.add(positionZSpreadCurve2.parameters);
    
    holdModParamFloatArgs.name = "positionZSpreadCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    positionZSpreadCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(positionZSpreadCurveMorph->parameters);
    
    holdModParamFloatArgs.name = "positionZSpreadCurvePhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    positionZSpreadCurvePhase = createModParameter(holdModParamFloatArgs);
    parameters.add(positionZSpreadCurvePhase->parameters);
    
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
    
    parameters.add(useRotateXSpreadCurveForRotateY.set("useRotateXSpreadCurveForRotateY", false));
    
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
    
    parameters.add(useRotateXSpreadCurveForRotateZ.set("useRotateXSpreadCurveForRotateZ", false));
    
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
    
    rotateMultiplySpreadCurve.setValueArrayToRamp(0, 1);
    rotateMultiplySpreadCurve.setName("rotateMultiplySpreadCurve");
    parameters.add(rotateMultiplySpreadCurve.parameters);
    
    rotateMultiplySpreadCurve2.setValueArrayToRamp(0, 1);
    rotateMultiplySpreadCurve2.setName("rotateMultiplySpreadCurve2");
    parameters.add(rotateMultiplySpreadCurve2.parameters);
    
    holdModParamFloatArgs.name = "rotateMultiplySpreadCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    rotateMultiplySpreadCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateMultiplySpreadCurveMorph->parameters);
    
    holdModParamFloatArgs.name = "rotateMultiplySpreadCurvePhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    rotateMultiplySpreadCurvePhase = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateMultiplySpreadCurvePhase->parameters);
    
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
    
    parameters.add(useScaleXSpreadCurveForScaleZ.set("useScaleXSpreadCurveForScaleZ", false));
    
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
    
    holdModParamFloatArgs.name = "colorSpreadCurvePhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    colorSpreadCurvePhase = createModParameter(holdModParamFloatArgs);
    parameters.add(colorSpreadCurvePhase->parameters);
    
    // mesh distortion
    
    holdModParamBoolArgs.name = "waveDistortActive";
    holdModParamBoolArgs.fixedValue = false;
    waveDistortActive = createModParameter(holdModParamBoolArgs);
    parameters.add(waveDistortActive->parameters);
    
    holdModParamIntArgs.name = "wave1Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalDistortionWaveTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalDistortionWaveTypes - 1;
	wave1Type = createModParameter(holdModParamIntArgs);
    parameters.add(wave1Type->parameters);
    
    holdModParamFloatArgs.name = "wave1Phase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    wave1Phase = createModParameter(holdModParamFloatArgs);
    parameters.add(wave1Phase->parameters);
    
    holdModParamFloatArgs.name = "wave1Freq";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 20.0;
    wave1Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(wave1Freq->parameters);
    
    holdModParamIntArgs.name = "wave2Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalDistortionWaveTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalDistortionWaveTypes - 1;
	wave2Type = createModParameter(holdModParamIntArgs);
    parameters.add(wave2Type->parameters);
    
    holdModParamFloatArgs.name = "wave2Phase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    wave2Phase = createModParameter(holdModParamFloatArgs);
    parameters.add(wave2Phase->parameters);
    
    holdModParamFloatArgs.name = "wave2Freq";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 20.0;
    wave2Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(wave2Freq->parameters);
    
    holdModParamIntArgs.name = "wave3Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalDistortionWaveTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalDistortionWaveTypes - 1;
	wave3Type = createModParameter(holdModParamIntArgs);
    parameters.add(wave3Type->parameters);
    
    holdModParamFloatArgs.name = "wave3Phase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    wave3Phase = createModParameter(holdModParamFloatArgs);
    parameters.add(wave3Phase->parameters);
    
    holdModParamFloatArgs.name = "wave3Freq";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 20.0;
    wave3Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(wave3Freq->parameters);
    
    holdModParamIntArgs.name = "wave4Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalDistortionWaveTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalDistortionWaveTypes - 1;
    wave4Type = createModParameter(holdModParamIntArgs);
    parameters.add(wave4Type->parameters);
    
    holdModParamFloatArgs.name = "wave4Phase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    wave4Phase = createModParameter(holdModParamFloatArgs);
    parameters.add(wave4Phase->parameters);
    
    holdModParamFloatArgs.name = "wave4Freq";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 20.0;
    wave4Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(wave4Freq->parameters);
    
    holdModParamIntArgs.name = "wave5Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalDistortionWaveTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalDistortionWaveTypes - 1;
    wave5Type = createModParameter(holdModParamIntArgs);
    parameters.add(wave5Type->parameters);
    
    holdModParamFloatArgs.name = "wave5Phase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    wave5Phase = createModParameter(holdModParamFloatArgs);
    parameters.add(wave5Phase->parameters);
    
    holdModParamFloatArgs.name = "wave5Freq";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 20.0;
    wave5Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(wave5Freq->parameters);
    
    holdModParamIntArgs.name = "perlin1Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalPerlinTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalPerlinTypes - 1;
	perlin1Type = createModParameter(holdModParamIntArgs);
    parameters.add(perlin1Type->parameters);
    
    holdModParamFloatArgs.name = "perlin1Offset";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
    perlin1Offset = createModParameter(holdModParamFloatArgs);
    parameters.add(perlin1Offset->parameters);
    
    holdModParamFloatArgs.name = "perlin1Freq";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 20.0;
    perlin1Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(perlin1Freq->parameters);
    
    holdModParamIntArgs.name = "perlin2Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalPerlinTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalPerlinTypes - 1;
	perlin2Type = createModParameter(holdModParamIntArgs);
    parameters.add(perlin2Type->parameters);
    
    holdModParamFloatArgs.name = "perlin2Offset";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
    perlin2Offset = createModParameter(holdModParamFloatArgs);
    parameters.add(perlin2Offset->parameters);
    
    holdModParamFloatArgs.name = "perlin2Freq";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 20.0;
    perlin2Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(perlin2Freq->parameters);
    
    holdModParamIntArgs.name = "perlin3Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalPerlinTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalPerlinTypes - 1;
	perlin3Type = createModParameter(holdModParamIntArgs);
    parameters.add(perlin3Type->parameters);
    
    holdModParamFloatArgs.name = "perlin3Offset";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
    perlin3Offset = createModParameter(holdModParamFloatArgs);
    parameters.add(perlin3Offset->parameters);
    
    holdModParamFloatArgs.name = "perlin3Freq";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 20.0;
    perlin3Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(perlin3Freq->parameters);
    
    parameters.add(waveDistort1On.set("waveDistort1On", false));
    parameters.add(waveDistort1Target.set("waveDistort1Target", 0, 0, 2));
    
    holdModParamFloatArgs.name = "waveDistort1Depth";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    waveDistort1Depth = createModParameter(holdModParamFloatArgs);
    parameters.add(waveDistort1Depth->parameters);
    
    holdModParamIntArgs.name = "waveDistort1Waveform";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTWAVE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTWAVE_TOTAL - 1;
    waveDistort1Waveform = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort1Waveform->parameters);
    
    holdModParamIntArgs.name = "waveDistort1Axis";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTAXIS_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTAXIS_TOTAL - 1;
    waveDistort1Axis = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort1Axis->parameters);
    
    holdModParamIntArgs.name = "waveDistort1Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTTYPE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTTYPE_TOTAL - 1;
    waveDistort1Type = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort1Type->parameters);
    
    parameters.add(waveDistort2On.set("waveDistort2On", false));
    parameters.add(waveDistort2Target.set("waveDistort2Target", 0, 0, 2));
    
    holdModParamFloatArgs.name = "waveDistort2Depth";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    waveDistort2Depth = createModParameter(holdModParamFloatArgs);
    parameters.add(waveDistort2Depth->parameters);
    
    holdModParamIntArgs.name = "waveDistort2Waveform";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTWAVE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTWAVE_TOTAL - 1;
    waveDistort2Waveform = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort2Waveform->parameters);
    
    holdModParamIntArgs.name = "waveDistort2Axis";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTAXIS_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTAXIS_TOTAL - 1;
    waveDistort2Axis = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort2Axis->parameters);
    
    holdModParamIntArgs.name = "waveDistort2Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTTYPE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTTYPE_TOTAL - 1;
    waveDistort2Type = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort2Type->parameters);
    
    parameters.add(waveDistort3On.set("waveDistort3On", false));
    parameters.add(waveDistort3Target.set("waveDistort3Target", 0, 0, 2));
    
    holdModParamFloatArgs.name = "waveDistort3Depth";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    waveDistort3Depth = createModParameter(holdModParamFloatArgs);
    parameters.add(waveDistort3Depth->parameters);
    
    holdModParamIntArgs.name = "waveDistort3Waveform";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTWAVE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTWAVE_TOTAL - 1;
    waveDistort3Waveform = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort3Waveform->parameters);
    
    holdModParamIntArgs.name = "waveDistort3Axis";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTAXIS_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTAXIS_TOTAL - 1;
    waveDistort3Axis = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort3Axis->parameters);
    
    holdModParamIntArgs.name = "waveDistort3Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTTYPE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTTYPE_TOTAL - 1;
    waveDistort3Type = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort3Type->parameters);
    
    parameters.add(waveDistort4On.set("waveDistort4On", false));
    parameters.add(waveDistort4Target.set("waveDistort4Target", 0, 0, 2));
    
    holdModParamFloatArgs.name = "waveDistort4Depth";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    waveDistort4Depth = createModParameter(holdModParamFloatArgs);
    parameters.add(waveDistort4Depth->parameters);
    
    holdModParamIntArgs.name = "waveDistort4Waveform";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTWAVE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTWAVE_TOTAL - 1;
    waveDistort4Waveform = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort4Waveform->parameters);
    
    holdModParamIntArgs.name = "waveDistort4Axis";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTAXIS_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTAXIS_TOTAL - 1;
    waveDistort4Axis = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort4Axis->parameters);
    
    holdModParamIntArgs.name = "waveDistort4Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTTYPE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTTYPE_TOTAL - 1;
    waveDistort4Type = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort4Type->parameters);
    
    parameters.add(waveDistort5On.set("waveDistort5On", false));
    parameters.add(waveDistort5Target.set("waveDistort5Target", 0, 0, 2));
    
    holdModParamFloatArgs.name = "waveDistort5Depth";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    waveDistort5Depth = createModParameter(holdModParamFloatArgs);
    parameters.add(waveDistort5Depth->parameters);
    
    holdModParamIntArgs.name = "waveDistort5Waveform";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTWAVE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTWAVE_TOTAL - 1;
    waveDistort5Waveform = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort5Waveform->parameters);
    
    holdModParamIntArgs.name = "waveDistort5Axis";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTAXIS_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTAXIS_TOTAL - 1;
    waveDistort5Axis = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort5Axis->parameters);
    
    holdModParamIntArgs.name = "waveDistort5Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTTYPE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTTYPE_TOTAL - 1;
    waveDistort5Type = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort5Type->parameters);
    
    parameters.add(waveDistort6On.set("waveDistort6On", false));
    parameters.add(waveDistort6Target.set("waveDistort6Target", 0, 0, 2));
    
    holdModParamFloatArgs.name = "waveDistort6Depth";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    waveDistort6Depth = createModParameter(holdModParamFloatArgs);
    parameters.add(waveDistort6Depth->parameters);
    
    holdModParamIntArgs.name = "waveDistort6Waveform";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTWAVE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTWAVE_TOTAL - 1;
    waveDistort6Waveform = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort6Waveform->parameters);
    
    holdModParamIntArgs.name = "waveDistort6Axis";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTAXIS_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTAXIS_TOTAL - 1;
    waveDistort6Axis = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort6Axis->parameters);
    
    holdModParamIntArgs.name = "waveDistort6Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTTYPE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTTYPE_TOTAL - 1;
    waveDistort6Type = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort6Type->parameters);
    
    holdModParamFloatArgs.name = "focusPointX";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	focusPointX = createModParameter(holdModParamFloatArgs);
    parameters.add(focusPointX->parameters);
    
    holdModParamFloatArgs.name = "focusPointY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	focusPointY = createModParameter(holdModParamFloatArgs);
    parameters.add(focusPointY->parameters);
    
    holdModParamFloatArgs.name = "focusPointZ";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	focusPointZ = createModParameter(holdModParamFloatArgs);
    parameters.add(focusPointZ->parameters);
    
    holdModParamBoolArgs.name = "twistActive";
    holdModParamBoolArgs.fixedValue = false;
    twistActive = createModParameter(holdModParamBoolArgs);
    parameters.add(twistActive->parameters);
    
    parameters.add(twistTarget.set("twistTarget", 0, 0, 2));

    holdModParamFloatArgs.name = "twistPhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    twistPhase = createModParameter(holdModParamFloatArgs);
    parameters.add(twistPhase->parameters);
    
    holdModParamIntArgs.name = "twistAxis";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 2;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 2;
	twistAxis = createModParameter(holdModParamIntArgs);
    parameters.add(twistAxis->parameters);
    
    holdModParamFloatArgs.name = "twistFreq";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -30.0;
    holdModParamFloatArgs.hardMax = 30.0;
    holdModParamFloatArgs.softMin = -3.0;
    holdModParamFloatArgs.softMax = 3.0;
    twistFreq = createModParameter(holdModParamFloatArgs);
    parameters.add(twistFreq->parameters);
    
    holdModParamBoolArgs.name = "twistMiddleReverse";
    holdModParamBoolArgs.fixedValue = true;
    twistMiddleReverse = createModParameter(holdModParamBoolArgs);
    parameters.add(twistMiddleReverse->parameters);
    
    holdModParamBoolArgs.name = "useCentroidForTwistFocusPoint";
    holdModParamBoolArgs.fixedValue = false;
    useCentroidForTwistFocusPoint = createModParameter(holdModParamBoolArgs);
    parameters.add(useCentroidForTwistFocusPoint->parameters);
    
    holdModParamBoolArgs.name = "bendActive";
    holdModParamBoolArgs.fixedValue = false;
    bendActive = createModParameter(holdModParamBoolArgs);
    parameters.add(bendActive->parameters);
    
    parameters.add(bendTarget.set("bendTarget", 0, 0, 2));
    
    holdModParamFloatArgs.name = "bendRadius";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	bendRadius = createModParameter(holdModParamFloatArgs);
    parameters.add(bendRadius->parameters);
    
    holdModParamIntArgs.name = "bendType";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = numBendTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = numBendTypes - 1;
	bendType = createModParameter(holdModParamIntArgs);
    parameters.add(bendType->parameters);
    
    holdModParamBoolArgs.name = "bendInflationEffect";
    holdModParamBoolArgs.fixedValue = false;
    bendInflationEffect = createModParameter(holdModParamBoolArgs);
    parameters.add(bendInflationEffect->parameters);
    
    holdModParamFloatArgs.name = "bendAmountX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	bendAmountX = createModParameter(holdModParamFloatArgs);
    parameters.add(bendAmountX->parameters);
    
    holdModParamFloatArgs.name = "bendAmountY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	bendAmountY = createModParameter(holdModParamFloatArgs);
    parameters.add(bendAmountY->parameters);
    
    holdModParamFloatArgs.name = "bendAmountZ";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	bendAmountZ = createModParameter(holdModParamFloatArgs);
    parameters.add(bendAmountZ->parameters);
    
    holdModParamBoolArgs.name = "useCentroidForBendFocusPoint";
    holdModParamBoolArgs.fixedValue = false;
    useCentroidForBendFocusPoint = createModParameter(holdModParamBoolArgs);
    parameters.add(useCentroidForBendFocusPoint->parameters);
 
    wave1CustomCurve.setValueArrayToRamp(0, 1);
    wave1CustomCurve.setName("wave1CustomCurve");
    parameters.add(wave1CustomCurve.parameters);
    
    wave1CustomCurve2.setValueArrayToRamp(0, 1);
    wave1CustomCurve2.setName("wave1CustomCurve2");
    parameters.add(wave1CustomCurve2.parameters);
    
    holdModParamFloatArgs.name = "wave1CustomCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    wave1CustomCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(wave1CustomCurveMorph->parameters);
    
    wave2CustomCurve.setValueArrayToRamp(0, 1);
    wave2CustomCurve.setName("wave2CustomCurve");
    parameters.add(wave2CustomCurve.parameters);
    
    wave2CustomCurve2.setValueArrayToRamp(0, 1);
    wave2CustomCurve2.setName("wave2CustomCurve2");
    parameters.add(wave2CustomCurve2.parameters);
    
    holdModParamFloatArgs.name = "wave2CustomCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    wave2CustomCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(wave2CustomCurveMorph->parameters);
    
    wave3CustomCurve.setValueArrayToRamp(0, 1);
    wave3CustomCurve.setName("wave3CustomCurve");
    parameters.add(wave3CustomCurve.parameters);
    
    wave3CustomCurve2.setValueArrayToRamp(0, 1);
    wave3CustomCurve2.setName("wave3CustomCurve2");
    parameters.add(wave3CustomCurve2.parameters);
    
    holdModParamFloatArgs.name = "wave3CustomCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    wave3CustomCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(wave3CustomCurveMorph->parameters);
    
    wave4CustomCurve.setValueArrayToRamp(0, 1);
    wave4CustomCurve.setName("wave4CustomCurve");
    parameters.add(wave4CustomCurve.parameters);
    
    wave4CustomCurve2.setValueArrayToRamp(0, 1);
    wave4CustomCurve2.setName("wave4CustomCurve2");
    parameters.add(wave4CustomCurve2.parameters);
    
    holdModParamFloatArgs.name = "wave4CustomCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    wave4CustomCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(wave4CustomCurveMorph->parameters);
    
    wave5CustomCurve.setValueArrayToRamp(0, 1);
    wave5CustomCurve.setName("wave5CustomCurve");
    parameters.add(wave5CustomCurve.parameters);
    
    wave5CustomCurve2.setValueArrayToRamp(0, 1);
    wave5CustomCurve2.setName("wave5CustomCurve2");
    parameters.add(wave5CustomCurve2.parameters);
    
    holdModParamFloatArgs.name = "wave5CustomCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    wave5CustomCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(wave5CustomCurveMorph->parameters);
    
    // add listener to relevent mod parameters:
     ofAddListener(shapeType->parameters.parameterChangedE(),this,&TXDrawShape3DMulti::shapeTypeChanged);

    // add listener to relevent parameters:
    useImageAsTexture.addListener(this, &TXDrawShape3DMulti::useImageAsTextureChanged);
    useExternalSourceImage.addListener(this, &TXDrawShape3DMulti::useExternalSourceImageChanged);
    resolutionParaShape.addListener(this, &TXDrawShape3DMulti::resolutionParaShapeChanged);

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
    
    accumlator = 0.0;
    flipper = 1.0;
    
    // init 
    applyPosDistortion = false;
    retryMapTexture = false;
    //distortedMesh.setUsage(GL_DYNAMIC_DRAW);
    shapePtr = &sphere;

    sphere.setMode(OF_PRIMITIVE_TRIANGLES);
    icoSphere.setMode(OF_PRIMITIVE_TRIANGLES);
    cylinder.setMode(OF_PRIMITIVE_TRIANGLES);
    cone.setMode(OF_PRIMITIVE_TRIANGLES);
    box.setMode(OF_PRIMITIVE_TRIANGLES);
    plane.setMode(OF_PRIMITIVE_TRIANGLES);
    groupShape.getMesh().setMode(OF_PRIMITIVE_TRIANGLES);
    paraBuilder.setup(resolutionParaShape, resolutionParaShape);
    meshCentroid.zero();
}

void TXDrawShape3DMulti::update() {
    ofImage * tempImage;
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
    };
}

void TXDrawShape3DMulti::draw() {
    if (!drawActive->getBool()) {
        return;
    };
    
    float heightScale, depthScale;
    if (useMaxWidthToScaleHeight) {
        heightScale = getMaxWidth();
    } else {
        heightScale = getMaxHeight();
    };
    if (useMaxWidthToScaleDepth) {
        depthScale = getMaxWidth();
    } else {
        depthScale = getMaxDepth();
    };
    int hold_resolutionWidth;
    int hold_resolutionHeight;
    int hold_resolutionDepth;
    int hold_resolutionRadius;
    int hold_resolutionIsoSphere;
    int hold_resolutionCap;
    int hold_shapeType = shapeType->getInt();
    int hold_numCopies = numCopies->getInt();

    float holdSizeSpreadCurveMorph = sizeSpreadCurveMorph->getFloat();
    float holdXYZValsSpreadCurveMorph = xyzValsSpreadCurveMorph->getFloat();
    float holdPositionXSpreadCurveMorph = positionXSpreadCurveMorph->getFloat();
    float holdPositionYSpreadCurveMorph = positionYSpreadCurveMorph->getFloat();
    float holdPositionZSpreadCurveMorph = positionZSpreadCurveMorph->getFloat();
    float holdRotateXSpreadCurveMorph = rotateXSpreadCurveMorph->getFloat();
    float holdRotateYSpreadCurveMorph = rotateYSpreadCurveMorph->getFloat();
    float holdRotateZSpreadCurveMorph = rotateZSpreadCurveMorph->getFloat();
    float holdRotateMultiplySpreadCurveMorph = rotateMultiplySpreadCurveMorph->getFloat();
    float holdAnchorSpreadCurveMorph = anchorSpreadCurveMorph->getFloat();
    float holdScaleXSpreadCurveMorph = scaleXSpreadCurveMorph->getFloat();
    float holdScaleYSpreadCurveMorph = scaleYSpreadCurveMorph->getFloat();
    float holdScaleZSpreadCurveMorph = scaleZSpreadCurveMorph->getFloat();
    float holdColorSpreadCurveMorph = colorSpreadCurveMorph->getFloat();
    
    float holdSizeSpreadCurvePhase = sizeSpreadCurvePhase->getFloat();
    float holdXYZValsSpreadCurvePhase = xyzValsSpreadCurvePhase->getFloat();
    float holdPositionXSpreadCurvePhase = positionXSpreadCurvePhase->getFloat();
    float holdPositionYSpreadCurvePhase = positionYSpreadCurvePhase->getFloat();
    float holdPositionZSpreadCurvePhase = positionZSpreadCurvePhase->getFloat();
    float holdRotateXSpreadCurvePhase = rotateXSpreadCurvePhase->getFloat();
    float holdRotateYSpreadCurvePhase = rotateYSpreadCurvePhase->getFloat();
    float holdRotateZSpreadCurvePhase = rotateZSpreadCurvePhase->getFloat();
    float holdRotateMultiplySpreadCurvePhase = rotateMultiplySpreadCurvePhase->getFloat();
    float holdAnchorSpreadCurvePhase = anchorSpreadCurvePhase->getFloat();
    float holdScaleXSpreadCurvePhase = scaleXSpreadCurvePhase->getFloat();
    float holdScaleYSpreadCurvePhase = scaleYSpreadCurvePhase->getFloat();
    float holdScaleZSpreadCurvePhase = scaleZSpreadCurvePhase->getFloat();
    float holdColorSpreadCurvePhase = colorSpreadCurvePhase->getFloat();
    
    float hold_width = width->getFloat();
    float hold_height = height->getFloat();
    float hold_depth = depth->getFloat();
    float hold_radius = radius->getFloat();
    float hold_roundness = roundness->getFloat();
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
    
    float hold_widthEnd;
    float hold_heightEnd;
    float hold_depthEnd;
    float hold_radiusEnd;
    float hold_roundnessEnd;
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
    float hold_x1;
    float hold_x1End;
    float hold_x2;
    float hold_x2End;
    float hold_x3;
    float hold_x3End;
    float hold_y1;
    float hold_y1End;
    float hold_y2;
    float hold_y2End;
    float hold_y3;
    float hold_y3End;
    float hold_z1;
    float hold_z1End;
    float hold_z2;
    float hold_z2End;
    float hold_z3;
    float hold_z3End;
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
    
    float copy_width;
    float copy_height;
    float copy_depth;
    float copy_radius;
    float copy_roundness;
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
    float copy_x1;
    float copy_x1End;
    float copy_x2;
    float copy_x2End;
    float copy_x3;
    float copy_x3End;
    float copy_y1;
    float copy_y1End;
    float copy_y2;
    float copy_y2End;
    float copy_y3;
    float copy_y3End;
    float copy_z1;
    float copy_z1End;
    float copy_z2;
    float copy_z2End;
    float copy_z3;
    float copy_z3End;
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
    
    bool widthUsed;
    bool heightUsed;
    bool depthUsed;
    bool radiusUsed;
    bool roundnessUsed;
    bool resolutionIsoSphereUsed;
    bool resolutionCapUsed;
    float superShapeXMin, superShapeYMin, superShapeZMin;
    float superShapeXMax, superShapeYMax, superShapeZMax;
    int count;
    float holdXVals[3];
    float holdYVals[3];
    float holdZVals[3];
    ofVboMesh distortedGroupMesh;

    switch (hold_shapeType) {
        case TXSHAPE3DTYPE_SPHERE:
            widthUsed = false;
            heightUsed = false;
            depthUsed = false;
            radiusUsed = true;
            roundnessUsed = false;
            resolutionIsoSphereUsed = false;
            resolutionCapUsed = false;
            break;
        case TXSHAPE3DTYPE_ICOSPHERE:
            widthUsed = false;
            heightUsed = false;
            depthUsed = false;
            radiusUsed = true;
            roundnessUsed = false;
            resolutionIsoSphereUsed = true;
            resolutionCapUsed = false;
            break;
        case TXSHAPE3DTYPE_BOX:
            widthUsed = true;
            heightUsed = true;
            depthUsed = true;
            radiusUsed = false;
            roundnessUsed = false;
            resolutionIsoSphereUsed = false;
            resolutionCapUsed = false;
            break;
        case TXSHAPE3DTYPE_PLANE:
            widthUsed = true;
            heightUsed = true;
            depthUsed = false;
            radiusUsed = false;
            roundnessUsed = false;
            resolutionIsoSphereUsed = false;
            resolutionCapUsed = false;
            break;
        case TXSHAPE3DTYPE_CYLINDER:
            widthUsed = false;
            heightUsed = true;
            depthUsed = false;
            radiusUsed = true;
            roundnessUsed = false;
            resolutionIsoSphereUsed = false;
            resolutionCapUsed = true;
            break;
        case TXSHAPE3DTYPE_ROUNDEDCYLINDER:
            widthUsed = false;
            heightUsed = true;
            depthUsed = false;
            radiusUsed = true;
            roundnessUsed = true;
            resolutionIsoSphereUsed = false;
            resolutionCapUsed = true;
            break;
        case TXSHAPE3DTYPE_UNCAPPEDCYLINDER:
            widthUsed = false;
            heightUsed = true;
            depthUsed = false;
            radiusUsed = true;
            roundnessUsed = false;
            resolutionIsoSphereUsed = false;
            resolutionCapUsed = false;
            break;
        case TXSHAPE3DTYPE_CONE:
            widthUsed = false;
            heightUsed = true;
            depthUsed = false;
            radiusUsed = true;
            roundnessUsed = false;
            resolutionIsoSphereUsed = false;
            resolutionCapUsed = true;
            break;
        case TXSHAPE3DTYPE_ROUNDEDCONE:
            widthUsed = false;
            heightUsed = true;
            depthUsed = false;
            radiusUsed = true;
            roundnessUsed = true;
            resolutionIsoSphereUsed = false;
            resolutionCapUsed = true;
            break;
        case TXSHAPE3DTYPE_UNCAPPEDCONE:
            widthUsed = false;
            heightUsed = true;
            depthUsed = false;
            radiusUsed = true;
            roundnessUsed = false;
            resolutionIsoSphereUsed = false;
            //cone.setCapped(false);
            resolutionCapUsed = false;
            break;
//        case TXSHAPE3DTYPE_ICOSAHEDRON:
//            widthUsed = false;
//            heightUsed = false;
//            depthUsed = false;
//            radiusUsed = true;
//            roundnessUsed = false;
//            resolutionIsoSphereUsed = false;
//            resolutionCapUsed = false;
//            break;
        default:
            // default = paraShape
            widthUsed = true;
            heightUsed = true;
            depthUsed = true;
            radiusUsed = false;
            roundnessUsed = false;
            resolutionIsoSphereUsed = false;
            resolutionCapUsed = false;
            break;
    }
    
    if (widthUsed) {
        hold_width = width->getFloat();
        hold_resolutionWidth = resolutionWidth->getInt();
        if (!widthEndIgnore) {
            hold_widthEnd = widthEnd->getFloat();
        } else {
            hold_widthEnd = hold_width;
        };
    };
    if (heightUsed) {
        hold_height = height->getFloat();
        hold_resolutionHeight = resolutionHeight->getInt();
        if (!heightEndIgnore) {
            hold_heightEnd = heightEnd->getFloat();
        } else {
            hold_heightEnd = hold_height;
        };
    };
    if (depthUsed) {
        hold_depth = depth->getFloat();
        hold_resolutionDepth = resolutionDepth->getInt();
        if (!depthEndIgnore) {
            hold_depthEnd = depthEnd->getFloat();
        } else {
            hold_depthEnd = hold_depth;
        };
    };
    if (radiusUsed) {
        hold_radius = radius->getFloat();
        hold_resolutionRadius = resolutionRadius->getInt();
        if (!radiusEndIgnore) {
            hold_radiusEnd = radiusEnd->getFloat();
        } else {
            hold_radiusEnd = hold_radius;
        };
    };
    if (roundnessUsed) {
        hold_roundness = roundness->getFloat();
        if (!roundnessEndIgnore) {
            hold_roundnessEnd = roundnessEnd->getFloat();
        } else {
            hold_roundnessEnd = hold_roundness;
        };
    };
    if (resolutionIsoSphereUsed) {
        hold_resolutionIsoSphere = resolutionIsoSphere->getInt();
    };
    if (resolutionCapUsed) {
        hold_resolutionCap = resolutionCap->getInt();
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
    if (isParaShape()) {
        hold_x1 = x1->getFloat();
        if (!x1EndIgnore) {
            hold_x1End = x1End->getFloat();
        } else {
            hold_x1End = hold_x1;
        };
        hold_x2 = x2->getFloat();
        if (!x2EndIgnore) {
            hold_x2End = x2End->getFloat();
        } else {
            hold_x2End = hold_x2;
        };
        hold_x3 = x3->getFloat();
        if (!x3EndIgnore) {
            hold_x3End = x3End->getFloat();
        } else {
            hold_x3End = hold_x3;
        };
        hold_y1 = y1->getFloat();
        if (!y1EndIgnore) {
            hold_y1End = y1End->getFloat();
        } else {
            hold_y1End = hold_y1;
        };
        hold_y2 = y2->getFloat();
        if (!y2EndIgnore) {
            hold_y2End = y2End->getFloat();
        } else {
            hold_y2End = hold_y2;
        };
        hold_y3 = y3->getFloat();
        if (!y3EndIgnore) {
            hold_y3End = y3End->getFloat();
        } else {
            hold_y3End = hold_y3;
        };
        hold_z1 = z1->getFloat();
        if (!z1EndIgnore) {
            hold_z1End = z1End->getFloat();
        } else {
            hold_z1End = hold_z1;
        };
        hold_z2 = z2->getFloat();
        if (!z2EndIgnore) {
            hold_z2End = z2End->getFloat();
        } else {
            hold_z2End = hold_z2;
        };
        hold_z3 = z3->getFloat();
        if (!z3EndIgnore) {
            hold_z3End = z3End->getFloat();
        } else {
            hold_z3End = hold_z3;
        };
    };
    
    // superShape doesn't use material end values
    if (!mergeIntoSuperShape) {
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
    };
    
    // prepare texture
    // tex coords for 3D objects in OF are from 0 -> 1, not 0 -> image.width
    // so we must disable the arb rectangle call to allow 0 -> 1
    bool holdUsingArbTex = ofGetUsingArbTex();
    ofDisableArbTex();
    
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
            if (sourceImage->getTexture().isAllocated()) {
                sourceImage->getTexture().bind();
                validTexture = true;
            };
        };
    };
    // init 
    superShapeXMin = superShapeYMin = superShapeZMin = 10000;
    superShapeXMax = superShapeYMax = superShapeZMax = -10000;

    // for all copies
    for (int copyNo = 0; copyNo < hold_numCopies; copyNo++) {
        ofVboMesh copyMesh;
        ofVboMesh distortedCopyMesh;
        copyMesh.setMode(OF_PRIMITIVE_TRIANGLES);
        
        float proportion;
        if (hold_numCopies < 2) {
            proportion = 0.5;
        } else {
            proportion = (float) (0.5 + copyNo) / hold_numCopies;
        };
        ofColor holdColor;

        // superShape only sets material once ignoring end values
        if (mergeIntoSuperShape) {
            if (copyNo == 0) {
                material.setShininess(hold_materialShininess);
                holdColor = TXFunctions::txGetColor(hold_materialDiffuseColorHue, hold_materialDiffuseColorSaturation, hold_materialDiffuseColorBrightness, 1.0, hold_materialDiffuseColorHueRotate, hold_materialDiffuseColorHSBAsRGB);
                material.setDiffuseColor(holdColor);
                
                if (useDiffuseColorForAmbient) {
                    material.setAmbientColor(material.getDiffuseColor());
                } else {
                    holdColor = TXFunctions::txGetColor(hold_materialAmbientColorHue, hold_materialAmbientColorSaturation, hold_materialAmbientColorBrightness, 1.0, hold_materialAmbientColorHueRotate, hold_materialAmbientColorHSBAsRGB);
                    material.setAmbientColor(holdColor);
                };
                
                if (useDiffuseColorForSpecular) {
                    material.setSpecularColor(material.getDiffuseColor());
                } else {
                    holdColor = TXFunctions::txGetColor(hold_materialSpecularColorHue, hold_materialSpecularColorSaturation, hold_materialSpecularColorBrightness, 1.0, hold_materialSpecularColorHueRotate, hold_materialSpecularColorHSBAsRGB);
                    material.setSpecularColor(holdColor);
                };
                
                if (useDiffuseColorForEmissive) {
                    material.setEmissiveColor(material.getDiffuseColor());
                } else {
                    holdColor = TXFunctions::txGetColor(hold_materialEmissiveColorHue, hold_materialEmissiveColorSaturation, hold_materialEmissiveColorBrightness, 1.0, hold_materialEmissiveColorHueRotate, hold_materialEmissiveColorHSBAsRGB);
                    material.setEmissiveColor(holdColor);
                };
            };
        } else {
            float colorSpreadProportion =  TXFunctions::getInterpPhaseCurves(colorSpreadCurve, colorSpreadCurve2, proportion, holdColorSpreadCurvePhase, holdColorSpreadCurveMorph);
            
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
        };  // end of if (mergeIntoSuperShape)

        float sizeSpreadProportion =  TXFunctions::getInterpPhaseCurves(sizeSpreadCurve, sizeSpreadCurve2, proportion, holdSizeSpreadCurvePhase, holdSizeSpreadCurveMorph);

        if (widthUsed) {
            if (widthEndIgnore) {
                copy_width = hold_width * getMaxWidth();
            } else {
                copy_width = TXFunctions::getInterp(hold_width, hold_widthEnd, sizeSpreadProportion) * getMaxWidth();
            };
        };
        if (heightUsed) {
            if (heightEndIgnore) {
                copy_height = hold_height * heightScale;
            } else {
                copy_height = TXFunctions::getInterp(hold_height, hold_heightEnd, sizeSpreadProportion) *  heightScale;
            };
        };
        if (depthUsed) {
            if (depthEndIgnore) {
                copy_depth = hold_depth * depthScale;
            } else {
                copy_depth = TXFunctions::getInterp(hold_depth, hold_depthEnd, sizeSpreadProportion) * depthScale;
            };
        };
        if (radiusUsed) {
            if (radiusEndIgnore) {
                copy_radius = hold_radius * getMaxWidth();
            } else {
                copy_radius = TXFunctions::getInterp(hold_radius, hold_radiusEnd, sizeSpreadProportion) * getMaxWidth();
            };
        };
        if (roundnessUsed) {
            if (roundnessEndIgnore) {
                copy_roundness = hold_roundness;
            } else {
                copy_roundness = TXFunctions::getInterp(hold_roundness, hold_roundnessEnd, sizeSpreadProportion);
            };
        };

        if (isParaShape()) {
            if (ignoreAllXYZVals) {
                for(int i = 0; i < 3; i++){
                    holdXVals[i] = 1; // default value
                    holdYVals[i] = 1;
                    holdZVals[i] = 1;
                };
            } else {
                
                float xyzValsSpreadProportion =  TXFunctions::getInterpPhaseCurves(xyzValsSpreadCurve, xyzValsSpreadCurve2, proportion, holdXYZValsSpreadCurvePhase, holdXYZValsSpreadCurveMorph);
                
                if (x1EndIgnore) {
                    copy_x1 = hold_x1;
                } else {
                    copy_x1 = TXFunctions::getInterp(hold_x1, hold_x1End, xyzValsSpreadProportion);
                };
                if (x2EndIgnore) {
                    copy_x2 = hold_x2;
                } else {
                    copy_x2 = TXFunctions::getInterp(hold_x2, hold_x2End, xyzValsSpreadProportion);
                };
                if (x3EndIgnore) {
                    copy_x3 = hold_x3;
                } else {
                    copy_x3 = TXFunctions::getInterp(hold_x3, hold_x3End, xyzValsSpreadProportion);
                };
                if (x1Quantize) {
                    holdXVals[0] = lrintf(copy_x1);
                } else {
                    holdXVals[0] = copy_x1;
                };
                if (x2Quantize) {
                    holdXVals[1] = lrintf(copy_x2);
                } else {
                    holdXVals[1] = copy_x2;
                };
                if (x3Quantize) {
                    holdXVals[2] = lrintf(copy_x3);
                } else {
                    holdXVals[2] = copy_x3;
                };
                if (useXValsForY) {
                    for(int i = 0; i < 3; i++){
                        holdYVals[i] = holdXVals[i];
                    };
                } else {
                    if (y1EndIgnore) {
                        copy_y1 = hold_y1;
                    } else {
                        copy_y1 = TXFunctions::getInterp(hold_y1, hold_y1End, xyzValsSpreadProportion);
                    };
                    if (y2EndIgnore) {
                        copy_y2 = hold_y2;
                    } else {
                        copy_y2 = TXFunctions::getInterp(hold_y2, hold_y2End, xyzValsSpreadProportion);
                    };
                    if (y3EndIgnore) {
                        copy_y3 = hold_y3;
                    } else {
                        copy_y3 = TXFunctions::getInterp(hold_y3, hold_y3End, xyzValsSpreadProportion);
                    };
                    if (y1Quantize) {
                        holdYVals[0] = lrintf(copy_y1);
                    } else {
                        holdYVals[0] = copy_y1;
                    };
                    if (y2Quantize) {
                        holdYVals[1] = lrintf(copy_y2);
                    } else {
                        holdYVals[1] = copy_y2;
                    };
                    if (y3Quantize) {
                        holdYVals[2] = lrintf(copy_y3);
                    } else {
                        holdYVals[2] = copy_y3;
                    };
                };
                if (useXValsForZ) {
                    for(int i = 0; i < 3; i++){
                        holdZVals[i] = holdXVals[i];
                    };
                } else {
                    if (z1EndIgnore) {
                        copy_z1 = hold_z1;
                    } else {
                        copy_z1 = TXFunctions::getInterp(hold_z1, hold_z1End, xyzValsSpreadProportion);
                    };
                    if (z2EndIgnore) {
                        copy_z2 = hold_z2;
                    } else {
                        copy_z2 = TXFunctions::getInterp(hold_z2, hold_z2End, xyzValsSpreadProportion);
                    };
                    if (z3EndIgnore) {
                        copy_z3 = hold_z3;
                    } else {
                        copy_z3 = TXFunctions::getInterp(hold_z3, hold_z3End, xyzValsSpreadProportion);
                    };
                    if (z1Quantize) {
                        holdZVals[0] = lrintf(copy_z1);
                    } else {
                        holdZVals[0] = copy_z1;
                    };
                    if (z2Quantize) {
                        holdZVals[1] = lrintf(copy_z2);
                    } else {
                        holdZVals[1] = copy_z2;
                    };
                    if (x3Quantize) {
                        holdZVals[2] = lrintf(copy_z3);
                    } else {
                        holdZVals[2] = copy_z3;
                    };
                };
            };
        };

        float positionXSpreadProportion =  TXFunctions::getInterpPhaseCurves(positionXSpreadCurve, positionXSpreadCurve2, proportion, holdPositionXSpreadCurvePhase, holdPositionXSpreadCurveMorph);
        
        if (positionXEndIgnore) {
            copy_positionX = hold_positionX;
        } else {
            copy_positionX = TXFunctions::getInterp(hold_positionX, hold_positionXEnd, positionXSpreadProportion);
        };
        if (positionYEndIgnore) {
            copy_positionY = hold_positionY;
        } else {
            if (usePosXSpreadCurveForPosY) {
                copy_positionY = TXFunctions::getInterp(hold_positionY, hold_positionYEnd, positionXSpreadProportion);
            } else {
                float positionYSpreadProportion =  TXFunctions::getInterpPhaseCurves(positionYSpreadCurve, positionYSpreadCurve2, proportion, holdPositionYSpreadCurvePhase, holdPositionYSpreadCurveMorph);
                copy_positionY = TXFunctions::getInterp(hold_positionY, hold_positionYEnd, positionYSpreadProportion);
            };
        };
        if (positionZEndIgnore) {
            copy_positionZ = hold_positionZ;
        } else {
            if (usePosXSpreadCurveForPosZ) {
                copy_positionZ = TXFunctions::getInterp(hold_positionZ, hold_positionZEnd, positionXSpreadProportion);
            } else {
                float positionZSpreadProportion =  TXFunctions::getInterpPhaseCurves(positionZSpreadCurve, positionZSpreadCurve2, proportion, holdPositionZSpreadCurvePhase, holdPositionZSpreadCurveMorph);
                copy_positionZ = TXFunctions::getInterp(hold_positionZ, hold_positionZEnd, positionZSpreadProportion);
            };
        };

        float rotateXSpreadProportion =  TXFunctions::getInterpPhaseCurves(rotateXSpreadCurve, rotateXSpreadCurve2, proportion, holdRotateXSpreadCurvePhase, holdRotateXSpreadCurveMorph);

        if (rotateXEndIgnore) {
            copy_rotateX = hold_rotateX;
        } else {
            copy_rotateX = TXFunctions::getInterp(hold_rotateX, hold_rotateXEnd, rotateXSpreadProportion);
        };
        if (rotateYEndIgnore) {
            copy_rotateY = hold_rotateY;
        } else {
            if (useRotateXSpreadCurveForRotateY) {
                copy_rotateY = TXFunctions::getInterp(hold_rotateY, hold_rotateYEnd, rotateXSpreadProportion);
            } else {
                float rotateYSpreadProportion =  TXFunctions::getInterpPhaseCurves(rotateYSpreadCurve, rotateYSpreadCurve2, proportion, holdRotateYSpreadCurvePhase, holdRotateYSpreadCurveMorph);
                copy_rotateY = TXFunctions::getInterp(hold_rotateY, hold_rotateYEnd, rotateYSpreadProportion);
            };
        };
        if (rotateZEndIgnore) {
            copy_rotateZ = hold_rotateZ;
        } else {
            if (useRotateXSpreadCurveForRotateY) {
                copy_rotateZ = TXFunctions::getInterp(hold_rotateZ, hold_rotateZEnd, rotateXSpreadProportion);
            } else {
                float rotateZSpreadProportion =  TXFunctions::getInterpPhaseCurves(rotateZSpreadCurve, rotateZSpreadCurve2, proportion, holdRotateZSpreadCurvePhase, holdRotateZSpreadCurveMorph);
                copy_rotateZ = TXFunctions::getInterp(hold_rotateZ, hold_rotateZEnd, rotateZSpreadProportion);
            };
        };
        if (rotateMultiplyEndIgnore) {
            copy_rotateMultiply = hold_rotateMultiply;
        } else {
            float rotateMultiplySpreadProportion =  TXFunctions::getInterpPhaseCurves(rotateMultiplySpreadCurve, rotateMultiplySpreadCurve2, proportion, holdRotateMultiplySpreadCurvePhase, holdRotateMultiplySpreadCurveMorph);
            copy_rotateMultiply = TXFunctions::getInterp(hold_rotateMultiply, hold_rotateMultiplyEnd, rotateMultiplySpreadProportion);
        };

        float anchorSpreadProportion =  TXFunctions::getInterpPhaseCurves(anchorSpreadCurve, anchorSpreadCurve2, proportion, holdAnchorSpreadCurvePhase, holdAnchorSpreadCurveMorph);

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
        
        float scaleXSpreadProportion =  TXFunctions::getInterpPhaseCurves(scaleXSpreadCurve, scaleXSpreadCurve2, proportion, holdScaleXSpreadCurvePhase, holdScaleXSpreadCurveMorph);

        if (scaleXEndIgnore) {
            copy_scaleX = hold_scaleX;
        } else {
            copy_scaleX = TXFunctions::getInterp(hold_scaleX, hold_scaleXEnd, scaleXSpreadProportion);
        };
        if (useScaleXForScaleY) {
            copy_scaleY = copy_scaleX;
        } else {
            if (scaleYEndIgnore) {
                copy_scaleY = hold_scaleY;
            } else {
                if (useScaleXSpreadCurveForScaleY) {
                    copy_scaleY = TXFunctions::getInterp(hold_scaleY, hold_scaleYEnd, scaleXSpreadProportion);
                } else {
                    float scaleYSpreadProportion =  TXFunctions::getInterpPhaseCurves(scaleYSpreadCurve, scaleYSpreadCurve2, proportion, holdScaleYSpreadCurvePhase, holdScaleYSpreadCurveMorph);
                    copy_scaleY = TXFunctions::getInterp(hold_scaleY, hold_scaleYEnd, scaleYSpreadProportion);
                };
            };
        };
        if (useScaleXForScaleZ) {
            copy_scaleZ = copy_scaleX;
        } else {
            if (scaleZEndIgnore) {
                copy_scaleZ = hold_scaleZ;
            } else {
                if (useScaleXSpreadCurveForScaleZ) {
                    copy_scaleZ = TXFunctions::getInterp(hold_scaleZ, hold_scaleZEnd, scaleXSpreadProportion);
                } else {
                    float scaleZSpreadProportion =  TXFunctions::getInterpPhaseCurves(scaleZSpreadCurve, scaleZSpreadCurve2, proportion, holdScaleZSpreadCurvePhase, holdScaleZSpreadCurveMorph);
                    copy_scaleZ = TXFunctions::getInterp(hold_scaleZ, hold_scaleZEnd, scaleZSpreadProportion);
                };
            };
        };
        switch (hold_shapeType) {
            case TXSHAPE3DTYPE_SPHERE:
                shapePtr = &sphere;
                sphere.set(copy_radius, hold_resolutionRadius, OF_PRIMITIVE_TRIANGLES);
                sizeX = sizeY = sizeZ = copy_radius * 2;
                invertDistortedNormals = true;
                break;
            case TXSHAPE3DTYPE_ICOSPHERE:
                shapePtr = &icoSphere;
                icoSphere.set(copy_radius, hold_resolutionIsoSphere);
                sizeX = sizeY = sizeZ = copy_radius * 2;
                invertDistortedNormals = true;
                break;
            case TXSHAPE3DTYPE_BOX:
                shapePtr = &box;
                box.set(copy_width, copy_height, copy_depth,hold_resolutionWidth, hold_resolutionHeight, hold_resolutionDepth);
                sizeX = copy_width;
                sizeY = copy_height;
                sizeZ = copy_depth;
                invertDistortedNormals = false;
                break;
            case TXSHAPE3DTYPE_PLANE:
                shapePtr = &plane;
                plane.set(copy_width, copy_height, hold_resolutionWidth, hold_resolutionHeight, OF_PRIMITIVE_TRIANGLES);
                sizeX = copy_width;
                sizeY = copy_height;
                sizeZ = copy_width;
                invertDistortedNormals = false;
                break;
            case TXSHAPE3DTYPE_CYLINDER:
                shapePtr = &roundedCylinder;
                sphere.set(copy_radius, hold_resolutionCap, OF_PRIMITIVE_TRIANGLES);
                cylinder.set(copy_radius, copy_height, hold_resolutionRadius, hold_resolutionHeight, hold_resolutionCap, false, OF_PRIMITIVE_TRIANGLES);
                sizeX = sizeZ = copy_radius * 2;
                sizeY = copy_height;
                buildRoundedCylinder(sizeY, 0.001);
                invertDistortedNormals = false;
                break;
            case TXSHAPE3DTYPE_ROUNDEDCYLINDER:
                shapePtr = &roundedCylinder;
                sphere.set(copy_radius, hold_resolutionCap, OF_PRIMITIVE_TRIANGLES);
                cylinder.set(copy_radius, copy_height, hold_resolutionRadius, hold_resolutionHeight, hold_resolutionCap, false, OF_PRIMITIVE_TRIANGLES);
                sizeX = sizeZ = copy_radius * 2;
                sizeY = copy_height;
                buildRoundedCylinder(sizeY, copy_roundness);
                invertDistortedNormals = false;
                break;
            case TXSHAPE3DTYPE_UNCAPPEDCYLINDER:
                shapePtr = &cylinder;
                cylinder.set(copy_radius, copy_height, hold_resolutionRadius, hold_resolutionHeight, hold_resolutionCap, false, OF_PRIMITIVE_TRIANGLES);
                sizeX = sizeZ = copy_radius * 2;
                sizeY = copy_height;
                invertDistortedNormals = false;
                break;
            case TXSHAPE3DTYPE_CONE:
                shapePtr = &cone;
                cone.setHeight(copy_height);
                cone.set(copy_radius, copy_height, hold_resolutionRadius, hold_resolutionHeight, hold_resolutionCap, OF_PRIMITIVE_TRIANGLES);
                sizeX = sizeZ = copy_radius * 2;
                sizeY = copy_height;
                invertDistortedNormals = false;
                break;
            case TXSHAPE3DTYPE_ROUNDEDCONE:
                shapePtr = &roundedCone;
                sphere.set(copy_radius, hold_resolutionCap, OF_PRIMITIVE_TRIANGLES);
                cone.set(copy_radius, copy_height, hold_resolutionRadius, hold_resolutionHeight, 64, OF_PRIMITIVE_TRIANGLES);
                sizeX = sizeZ = copy_radius * 2;
                sizeY = copy_height;
                buildRoundedCone(sizeY, copy_roundness);
                invertDistortedNormals = false;
                break;
            case TXSHAPE3DTYPE_UNCAPPEDCONE:
                shapePtr = &uncappedCone;
                cone.set(copy_radius, copy_height, hold_resolutionRadius, hold_resolutionHeight, 2, OF_PRIMITIVE_TRIANGLE_STRIP);
                uncappedCone.getMesh() = cone.getConeMesh();
                count = uncappedCone.getMesh().getNumIndices();
                uncappedCone.getMesh().setIndex(count-1, uncappedCone.getMesh().getIndex(count-2));
                sizeX = sizeZ = copy_radius * 2;
                sizeY = copy_height;
                invertDistortedNormals = false;
                break;
                //cone.setCapped(false);
//            case TXSHAPE3DTYPE_ICOSAHEDRON:
//                shapePtr = &icosahedron;
//                icoSphere.set(copy_radius, hold_resolutionIsoSphere);
//                sizeX = sizeY = sizeZ = copy_radius * 2;
//                invertDistortedNormals = false;
//                break;
           default:
                // default = paraShape
                shapePtr = &paraShape;
                paraBuilder.setup((hold_shapeType - (total3DShapeTypes - paraBuilder.totalShapes)), resolutionParaShape, resolutionParaShape);
                paraSurface = paraBuilder.getShape();
                if (resolutionParaShapeHasChanged) {
                    paraSurface->setup(resolutionParaShape, resolutionParaShape);
                    resolutionParaShapeHasChanged = false;
                };
                paraSurface->width = copy_width;
                paraSurface->height = copy_height;
                paraSurface->depth = copy_depth;
                paraSurface->textureWidth = texWidth;
                paraSurface->textureHeight = texHeight;
                paraSurface->setXVals(holdXVals);
                paraSurface->setYVals(holdYVals);
                paraSurface->setZVals(holdZVals);
                // always reload
                // TESTING XXX - CHANGED FOR OF0.9.8
                //paraSurface->reload(smoothDistortedParaShape); // OLD
                paraSurface->reload();
                paraShape.enableNormals();
                paraShape.enableTextures();
                paraShape.disableColors();
                paraShape = plane; // init
                // TESTING XXX - CHANGED FOR OF0.9.8
                // OLD
                //            if (smoothDistortedParaShape) {
                //                paraShape.getMesh() = paraSurface->getIndexedMesh();
                //            } else {
                //                paraShape.getMesh() = paraSurface->getMesh();
                //            };
                paraShape.getMesh() = paraSurface->getMesh();
                meshCentroid = paraShape.getMesh().getCentroid();
                sizeX = copy_width;
                sizeY = copy_height;
                sizeZ = copy_depth;
                invertDistortedNormals = false;
                break;
        }

        // check if retry needed to map texture
        if (retryMapTexture) {
            mapTextureToShape();
        };
        
        // superShape merge
        if (mergeIntoSuperShape) {
            copyMesh = shapePtr->getMesh();
            copyMesh.enableTextures();
            copyMesh.disableColors();
            applyPosDistortion = applyDistortion(copyMesh, copyMesh, sizeX, sizeY, sizeZ, TXSHAPEMULTI3DDISTORTTARGET_UNIT);
            // transform each vertex
            ofVec3f holdVertex;
            for(int i = 0; i < copyMesh.getNumVertices(); i++ ) {
                holdVertex = copyMesh.getVertex( i );
                //  subtract anchor offset
                holdVertex = holdVertex - meshCentroid - ofVec3f((copy_anchorX-0.5) * sizeX, (copy_anchorY-0.5) * sizeY, (copy_anchorZ-0.5) * sizeZ);
                // scale
                holdVertex = holdVertex * ofVec3f(copy_scaleX, copy_scaleY, copy_scaleZ);
                // rotate
                holdVertex = TXFunctions::txVectorRotate(holdVertex, copy_rotateMultiply * copy_rotateX, copy_rotateMultiply * copy_rotateY, copy_rotateMultiply * copy_rotateZ);
                //  move to position
                holdVertex = holdVertex + ofVec3f((copy_positionX * getMaxWidth()), (copy_positionY * getMaxHeight()), (copy_positionZ * getMaxDepth()));
                // update vertex
                copyMesh.setVertex( i, holdVertex );
                // keep track of mesh size
                superShapeXMin = min(superShapeXMin, holdVertex.x);
                superShapeYMin = min(superShapeYMin, holdVertex.y);
                superShapeZMin = min(superShapeZMin, holdVertex.z);
                superShapeXMax = max(superShapeXMax, holdVertex.x);
                superShapeYMax = max(superShapeYMax, holdVertex.y);
                superShapeZMax = max(superShapeZMax, holdVertex.z);
            };
            
            /* TESTING XXX 
             // tried using separate triangles but didn't work & much slower:
             copyMesh = shapePtr->getMesh();
            triangles = shapePtr->getMesh().getUniqueFaces();
            for(int j = 0; j < triangles.size(); j++ ) {
                for(int i = 0; i < 3; i++ ) {
                    // transform each vertex
                    ofVec3f holdVertex;
                    holdVertex = triangles[j].getVertex( i );
                    //  move & subtract anchor offset
                    holdVertex = holdVertex - meshCentroid + ofVec3f((copy_positionX * getMaxWidth()) - ((copy_anchorX-0.5) * sizeX), (copy_positionY * getMaxHeight()) - ((copy_anchorY-0.5) * sizeY), (copy_positionZ * getMaxDepth()) - ((copy_anchorZ-0.5) * sizeY));
                    // rotate
                    holdVertex = TXFunctions::txVectorRotate(holdVertex, copy_rotateMultiply * copy_rotateX, copy_rotateMultiply * copy_rotateY, copy_rotateMultiply * copy_rotateZ);
                    // scale
                    holdVertex = holdVertex * ofVec3f(copy_scaleX, copy_scaleY, copy_scaleZ);
                    // update vertex
                    triangles[j].setVertex( i, holdVertex );
                    // keep track of mesh size
                    superShapeXMin = min(superShapeXMin, holdVertex.x);
                    superShapeYMin = min(superShapeYMin, holdVertex.y);
                    superShapeZMin = min(superShapeZMin, holdVertex.z);
                    superShapeXMax = max(superShapeXMax, holdVertex.x);
                    superShapeYMax = max(superShapeYMax, holdVertex.y);
                    superShapeZMax = max(superShapeZMax, holdVertex.z);
                };
            };
            copyMesh.setFromTriangles(triangles);
            */
            if (copyNo == 0) {
                groupShape.getMesh().setMode(OF_PRIMITIVE_TRIANGLES);
                groupShape.getMesh() = copyMesh;
                groupShape.enableTextures();
                groupShape.disableColors();
            } else {
                groupShape.getMesh().append(copyMesh);
            };
        } else {
            // if not superShape draw individual copy
            ofVboMesh holdShapeMesh = shapePtr->getMesh();
            applyPosDistortion = applyDistortion(holdShapeMesh, distortedCopyMesh, sizeX, sizeY, sizeZ, TXSHAPEMULTI3DDISTORTTARGET_UNIT);
            shapePtr->setPosition(copy_positionX * getMaxWidth(), copy_positionY * getMaxHeight(), copy_positionZ * getMaxDepth());
            shapePtr->setOrientation(TXFunctions::txGetRotateQuat(copy_rotateMultiply * copy_rotateX, copy_rotateMultiply * copy_rotateY, copy_rotateMultiply * copy_rotateZ));
            shapePtr->setScale(copy_scaleX, copy_scaleY, copy_scaleZ);
            
            // draw
            ofPushMatrix();
            material.begin();
            ofSetColor(material.getDiffuseColor());
            if (fillShape->getBool()) {
                ofFill();
                if(applyPosDistortion) {
                    shapePtr->transformGL();
                    ofTranslate(-((copy_anchorX-0.5) * sizeX) - meshCentroid.x, -((copy_anchorY-0.5) * sizeY) - meshCentroid.y, -((copy_anchorZ-0.5) * sizeZ) - meshCentroid.z);
                    distortedCopyMesh.draw();
                    shapePtr->restoreTransformGL();
                } else {
                    //shapePtr->transformGL();
                    ofTranslate(-((copy_anchorX-0.5) * sizeX) - meshCentroid.x, -((copy_anchorY-0.5) * sizeY) - meshCentroid.y, -((copy_anchorZ-0.5) * sizeZ) - meshCentroid.z);
                    shapePtr->draw();
                    //shapePtr->restoreTransformGL();
                }
            } else {
                // if not filled, draw wireframe
                ofNoFill();
                if(applyPosDistortion) {
                    shapePtr->transformGL();
                    ofTranslate(-((copy_anchorX-0.5) * sizeX) - meshCentroid.x, -((copy_anchorY-0.5) * sizeY) - meshCentroid.y, -((copy_anchorZ-0.5) * sizeZ) - meshCentroid.z);
                    distortedCopyMesh.drawWireframe();
                    shapePtr->restoreTransformGL();
                } else {
                    //shapePtr->transformGL();
                    ofTranslate(-((copy_anchorX-0.5) * sizeX) - meshCentroid.x, -((copy_anchorY-0.5) * sizeY) - meshCentroid.y, -((copy_anchorZ-0.5) * sizeZ) - meshCentroid.z);
                    shapePtr->drawWireframe();
                    //shapePtr->restoreTransformGL();
                }
            };
            material.end();
            ofSetColor(255.0f);
            ofPopMatrix();
        };
    };
    // end of for all copies
    
    // SuperShape draw
    if (mergeIntoSuperShape) {
        // distort mesh if requested
        ofVboMesh holdGroupMesh = groupShape.getMesh();
        applyPosDistortion = applyDistortion(holdGroupMesh, distortedGroupMesh, superShapeXMax - superShapeXMin, superShapeYMax - superShapeYMin, superShapeZMax - superShapeZMin, TXSHAPEMULTI3DDISTORTTARGET_GROUP);
        ofSetColor(material.getDiffuseColor());
        material.begin();
        ofPushMatrix();
        if (fillShape->getBool()) {
            ofFill();
            if(applyPosDistortion) {
                //groupShape.transformGL();
                distortedGroupMesh.draw();
                //groupShape.restoreTransformGL();
            } else {
                groupShape.draw();
            }
        } else {
            // if not filled, draw wireframe
            ofNoFill();
            if(applyPosDistortion) {
                //groupShape.transformGL();
                distortedGroupMesh.drawWireframe();
                //groupShape.restoreTransformGL();
            } else {
                groupShape.drawWireframe();
            }
        };
        material.end();
        ofSetColor(255.0f);
        ofPopMatrix();
    };
    // unbind texture if valid
    if(useImageAsTexture && validTexture) {
        if (useExternalSourceImage) {
            int holdExtSourceID = getExtImageModuleIDSlot("extSourceImageModule");
            (* parentSystem->allModules[holdExtSourceID]->getTexture()).unbind();
        } else {
            sourceImage->getTexture().unbind();
        };
    };
    // reset UsingArbTex
    if (holdUsingArbTex) {
        ofEnableArbTex();
    };
}

bool TXDrawShape3DMulti::applyDistortion(ofVboMesh &inputMesh, ofVboMesh &distortedMesh, float sizeX, float sizeY, float sizeZ, int target){
    bool holdwaveDistortActive;
    bool holdtwistActive, holdbendActive;
    bool holdIsDistorted;
    holdwaveDistortActive = waveDistortActive->getBool();
    holdtwistActive = twistActive->getBool()  && ((twistTarget == target) || (twistTarget == TXSHAPEMULTI3DDISTORTTARGET_UNITANDGROUP));
    holdbendActive = bendActive->getBool()  && ((bendTarget == target) || (bendTarget == TXSHAPEMULTI3DDISTORTTARGET_UNITANDGROUP));
    if (holdwaveDistortActive || holdtwistActive || holdbendActive) {
        holdIsDistorted = true;
        distortedMesh = inputMesh;
        distortedMesh.enableTextures();
        distortedMesh.disableColors();

        int holddistortOrder;
        float holdtwistPhase, holdtwistFreq;
        int   holdtwistAxis;
        bool  holdbendInflationEffect;
        int   holdbendType;
        float holdbendAmountX, holdbendAmountY, holdbendAmountZ, holdbendRadius;
        bool  holdtwistMiddleReverse, holduseCentroidForTwist, holduseCentroidForBend;
        ofVec3f focusPoint = ofVec3f(0, 0, 0);
        ofVec3f shapeCentroid = ofVec3f(0, 0, 0);
        // prepare vars
        holddistortOrder = distortOrder->getInt();
        if(holdwaveDistortActive) {
            holdwave1Type = wave1Type->getInt();
            holdwave2Type = wave2Type->getInt();
            holdwave3Type = wave3Type->getInt();
            holdwave4Type = wave4Type->getInt();
            holdwave5Type = wave5Type->getInt();
            holdwave1Phase = wave1Phase->getFloat();
            holdwave2Phase = wave2Phase->getFloat();
            holdwave3Phase = wave3Phase->getFloat();
            holdwave4Phase = wave4Phase->getFloat();
            holdwave5Phase = wave5Phase->getFloat();
            holdwave1Freq = wave1Freq->getFloat();
            holdwave2Freq = wave2Freq->getFloat();
            holdwave3Freq = wave3Freq->getFloat();
            holdwave4Freq = wave4Freq->getFloat();
            holdwave5Freq = wave5Freq->getFloat();
            holdwave1CustomCurveMorph = wave1CustomCurveMorph->getFloat();
            holdwave2CustomCurveMorph = wave2CustomCurveMorph->getFloat();
            holdwave3CustomCurveMorph = wave3CustomCurveMorph->getFloat();
            holdwave4CustomCurveMorph = wave4CustomCurveMorph->getFloat();
            holdwave5CustomCurveMorph = wave5CustomCurveMorph->getFloat();
            holdperlin1Type = perlin1Type->getInt();
            holdperlin2Type = perlin2Type->getInt();
            holdperlin3Type = perlin3Type->getInt();
            holdperlin1Freq = perlin1Freq->getFloat();
            holdperlin2Freq = perlin2Freq->getFloat();
            holdperlin3Freq = perlin3Freq->getFloat();
            holdperlin1Offset = perlin1Offset->getFloat();
            holdperlin2Offset = perlin2Offset->getFloat();
            holdperlin3Offset = perlin3Offset->getFloat();
        };
        float holdwaveDistort1Depth;
        int holdwaveDistort1Waveform;
        int holdwaveDistort1Axis;
        int holdwaveDistort1Type;
        float holdwaveDistort2Depth;
        int holdwaveDistort2Waveform;
        int holdwaveDistort2Axis;
        int holdwaveDistort2Type;
        float holdwaveDistort3Depth;
        int holdwaveDistort3Waveform;
        int holdwaveDistort3Axis;
        int holdwaveDistort3Type;
        float holdwaveDistort4Depth;
        int holdwaveDistort4Waveform;
        int holdwaveDistort4Axis;
        int holdwaveDistort4Type;
        float holdwaveDistort5Depth;
        int holdwaveDistort5Waveform;
        int holdwaveDistort5Axis;
        int holdwaveDistort5Type;
        float holdwaveDistort6Depth;
        int holdwaveDistort6Waveform;
        int holdwaveDistort6Axis;
        int holdwaveDistort6Type;
        if (waveDistort1On && ((waveDistort1Target == target) || (waveDistort1Target == TXSHAPEMULTI3DDISTORTTARGET_UNITANDGROUP))) {
            holdwaveDistort1Depth = waveDistort1Depth->getFloat();
            holdwaveDistort1Waveform = waveDistort1Waveform->getInt();
            holdwaveDistort1Axis = waveDistort1Axis->getInt();
            holdwaveDistort1Type = waveDistort1Type->getInt();
        };
        if (waveDistort2On && ((waveDistort2Target == target) || (waveDistort2Target == TXSHAPEMULTI3DDISTORTTARGET_UNITANDGROUP))) {
            holdwaveDistort2Depth = waveDistort2Depth->getFloat();
            holdwaveDistort2Waveform = waveDistort2Waveform->getInt();
            holdwaveDistort2Axis = waveDistort2Axis->getInt();
            holdwaveDistort2Type = waveDistort2Type->getInt();
        };
        if (waveDistort3On && ((waveDistort3Target == target) || (waveDistort3Target == TXSHAPEMULTI3DDISTORTTARGET_UNITANDGROUP))) {
            holdwaveDistort3Depth = waveDistort3Depth->getFloat();
            holdwaveDistort3Waveform = waveDistort3Waveform->getInt();
            holdwaveDistort3Axis = waveDistort3Axis->getInt();
            holdwaveDistort3Type = waveDistort3Type->getInt();
        };
        if (waveDistort4On && ((waveDistort4Target == target) || (waveDistort4Target == TXSHAPEMULTI3DDISTORTTARGET_UNITANDGROUP))) {
            holdwaveDistort4Depth = waveDistort4Depth->getFloat();
            holdwaveDistort4Waveform = waveDistort4Waveform->getInt();
            holdwaveDistort4Axis = waveDistort4Axis->getInt();
            holdwaveDistort4Type = waveDistort4Type->getInt();
        };
        if (waveDistort5On && ((waveDistort5Target == target) || (waveDistort5Target == TXSHAPEMULTI3DDISTORTTARGET_UNITANDGROUP))) {
            holdwaveDistort5Depth = waveDistort5Depth->getFloat();
            holdwaveDistort5Waveform = waveDistort5Waveform->getInt();
            holdwaveDistort5Axis = waveDistort5Axis->getInt();
            holdwaveDistort5Type = waveDistort5Type->getInt();
        };
        if (waveDistort6On && ((waveDistort5Target == target) || (waveDistort6Target == TXSHAPEMULTI3DDISTORTTARGET_UNITANDGROUP))) {
            holdwaveDistort6Depth = waveDistort6Depth->getFloat();
            holdwaveDistort6Waveform = waveDistort6Waveform->getInt();
            holdwaveDistort6Axis = waveDistort6Axis->getInt();
        };
        bool centroidNeeded = false;
        bool focusPointNeeded = false;
        if(holdtwistActive) {
            holdtwistPhase = twistPhase->getFloat();
            holdtwistAxis = twistAxis->getInt();
            holdtwistFreq = twistFreq->getFloat();
            holdtwistMiddleReverse = twistMiddleReverse->getBool();
            holduseCentroidForTwist = useCentroidForTwistFocusPoint->getBool();
            if (holduseCentroidForTwist) {
                centroidNeeded = true;
            } else {
                focusPointNeeded = true;
            };
        };
        if(holdbendActive) {
            holdbendRadius = bendRadius->getFloat();
            holdbendType = bendType->getInt();
            holdbendInflationEffect = bendInflationEffect->getBool();
            holdbendAmountX = bendAmountX->getFloat();
            holdbendAmountY = bendAmountY->getFloat();
            holdbendAmountZ = bendAmountZ->getFloat();
            holduseCentroidForBend = useCentroidForBendFocusPoint->getBool();
            if (holduseCentroidForBend) {
                centroidNeeded = true;
            } else {
                focusPointNeeded = true;
            };
        };
        if (centroidNeeded){
            shapeCentroid = distortedMesh.getCentroid();
        };
        if (focusPointNeeded){
            focusPoint = ofVec3f(focusPointX->getFloat() * getMaxWidth(), focusPointY->getFloat() * getMaxHeight(), focusPointZ->getFloat() * getMaxDepth());
        };
        switch (holddistortOrder) {
            case TXSHAPE3DDISTORTORDER_WAVETWISTBEND:
                setDistortOrderIndices(1,2,3);
                break;
            case TXSHAPE3DDISTORTORDER_WAVEBENDTWIST:
                setDistortOrderIndices(1,3,2);
                break;
            case TXSHAPE3DDISTORTORDER_TWISTBENDWAVE:
                setDistortOrderIndices(2,3,1);
                break;
            case TXSHAPE3DDISTORTORDER_TWISTWAVEBEND:
                setDistortOrderIndices(2,1,3);
                break;
            case TXSHAPE3DDISTORTORDER_BENDTWISTWAVE:
                setDistortOrderIndices(3,2,1);
                break;
            case TXSHAPE3DDISTORTORDER_BENDWAVETWIST:
                setDistortOrderIndices(3,1,2);
                break;
            default:
                setDistortOrderIndices(1,2,3);
                break;
        }
        // change each vertex
        ofVec3f holdVertex, twistCenter, rotatePoint, newVertex, bendPoint;
        TXParameterFloat256 * customCurve;
        
        for(int i = 0; i < distortedMesh.getNumVertices(); i++ ) {
            holdVertex = distortedMesh.getVertex( i );
            // apply distortions in order
            for(int j = 0; j < 3; j++ ) {
                switch (distortOrderIndices[j]) {
                    case 1:
                        // add waves
                        if(holdwaveDistortActive) {
                            if (waveDistort1On && ((waveDistort1Target == target) || (waveDistort1Target == TXSHAPEMULTI3DDISTORTTARGET_UNITANDGROUP))) {
                                distortVertex(holdVertex, holdwaveDistort1Depth, holdwaveDistort1Waveform, holdwaveDistort1Axis, holdwaveDistort1Type, sizeX, sizeY, sizeZ);
                            };
                            if (waveDistort2On && ((waveDistort2Target == target) || (waveDistort2Target == TXSHAPEMULTI3DDISTORTTARGET_UNITANDGROUP))) {
                                distortVertex(holdVertex, holdwaveDistort2Depth, holdwaveDistort2Waveform, holdwaveDistort2Axis, holdwaveDistort2Type, sizeX, sizeY, sizeZ);
                            };
                            if (waveDistort3On && ((waveDistort3Target == target) || (waveDistort3Target == TXSHAPEMULTI3DDISTORTTARGET_UNITANDGROUP))) {
                                distortVertex(holdVertex, holdwaveDistort3Depth, holdwaveDistort3Waveform, holdwaveDistort3Axis, holdwaveDistort3Type, sizeX, sizeY, sizeZ);
                            };
                            if (waveDistort4On && ((waveDistort4Target == target) || (waveDistort4Target == TXSHAPEMULTI3DDISTORTTARGET_UNITANDGROUP))) {
                                distortVertex(holdVertex, holdwaveDistort4Depth, holdwaveDistort4Waveform, holdwaveDistort4Axis, holdwaveDistort4Type, sizeX, sizeY, sizeZ);
                            };
                            if (waveDistort5On && ((waveDistort5Target == target) || (waveDistort5Target == TXSHAPEMULTI3DDISTORTTARGET_UNITANDGROUP))) {
                                distortVertex(holdVertex, holdwaveDistort5Depth, holdwaveDistort5Waveform, holdwaveDistort5Axis, holdwaveDistort5Type, sizeX, sizeY, sizeZ);
                            };
                            if (waveDistort6On && ((waveDistort5Target == target) || (waveDistort6Target == TXSHAPEMULTI3DDISTORTTARGET_UNITANDGROUP))) {
                                distortVertex(holdVertex, holdwaveDistort6Depth, holdwaveDistort6Waveform, holdwaveDistort6Axis, holdwaveDistort6Type, sizeX, sizeY, sizeZ);
                            };
                        };
                        // end of if(holdwaveDistortActive..
                        break;
                    case 2:
                        // add twist
                        if(holdtwistActive) {
                            if (holduseCentroidForTwist) {
                                twistCenter = shapeCentroid;
                            } else {
                                twistCenter = focusPoint;
                            };
                            float rotation;
                            int largeConstant = 100000;
                            if (holdtwistAxis == 0) {
                                rotatePoint = ofVec3f(holdVertex.x, twistCenter.y, twistCenter.z);
                                //rotation = holdVertex.x / getMaxWidth();
                                rotation = holdVertex.x / sizeX;
                                //rotation = fmod(((sizeX * 0.5f) + holdVertex.x) / sizeX, 1.0f);
                                //rotation = ((sizeX * 0.5) + holdVertex.x) / sizeX;
                            } else if (holdtwistAxis == 1) {
                                rotatePoint = ofVec3f(twistCenter.x, holdVertex.y, twistCenter.z);
                                //rotation = holdVertex.y / getMaxHeight();
                                rotation = holdVertex.y / sizeY;
                                //rotation = fmod(((sizeY * 0.5f) + holdVertex.y) / sizeY, 1.0f);
                                //rotation = ((sizeY * 0.5) + holdVertex.y) / sizeY;
                            } else {
                                rotatePoint = ofVec3f(twistCenter.x, twistCenter.y, holdVertex.z);
                                //rotation = holdVertex.z / getMaxDepth();
                                rotation = holdVertex.z / sizeZ;
                                //rotation = fmod(((sizeZ * 0.5f) + holdVertex.z) / sizeZ, 1.0f);
                                //rotation = ((sizeZ * 0.5) + holdVertex.z) / sizeZ;
                            };
                            
                            float rotMultiply;
                            if (holdtwistMiddleReverse && (rotation < 0)) {
                                rotMultiply = -1;
                            } else {
                                rotMultiply = 1;
                            };
                            float offset = rotMultiply * 360 * (holdtwistPhase + (holdtwistFreq * rotation));
                            newVertex = holdVertex;
                            //newVertex.rotate(fmod(offset, 360.0f), rotatePoint);
                            newVertex.rotate(offset, rotatePoint);
                            // set vertex
                            holdVertex = newVertex;
                        };
                        break;
                    case 3:
                        // add bend
                        if (holdbendActive) {
                            if (holduseCentroidForBend) {
                                bendPoint = shapeCentroid;
                            } else {
                                bendPoint = focusPoint;
                            };
                            float radius = holdbendRadius * getMaxWidth();
                            float distance = holdVertex.distance(bendPoint);
                            float tweenedPhase = ofxTweenLite::tween ( 0, 1, distance/ radius, (ofEaseFunction) (holdbendType));
                            ofVec3f diffVecNorm = (holdVertex - bendPoint).getNormalized();
                            ofVec3f adjustedVec = ofVec3f(diffVecNorm.x * holdbendAmountX, diffVecNorm.y * holdbendAmountY, diffVecNorm.z * holdbendAmountZ);
                            // set vertex
                            if (holdbendInflationEffect) {
                                holdVertex = bendPoint + (adjustedVec * radius * tweenedPhase);
                            } else {
                                holdVertex = holdVertex + (adjustedVec * radius * tweenedPhase);
                            };
                        };
                        break;
                    default:
                        // no action
                        break;
                }; // end of switch
            };
            // update vertex
            distortedMesh.setVertex( i, holdVertex );
        };
        // end of for getNumVertices
        calcDistortedMeshNormals(distortedMesh);
    } else {
        holdIsDistorted = false;
    };
    return holdIsDistorted;
}

void TXDrawShape3DMulti::distortVertex(ofVec3f & argVertex, float argDepth, int argWaveform, int argAxis, int argType, float argSizeX, float argSizeY, float argSizeZ) {
    ofVec3f outVertex;
    float holdPhase;
    float axisRatio;
    float waveValue;
    float averageSize;
    
    switch (argAxis) {
        case TXSHAPE3DDISTORTAXIS_POSXONY:
            axisRatio = argVertex.y / sizeY;
            break;
        case TXSHAPE3DDISTORTAXIS_POSXONZ:
            axisRatio = argVertex.z / sizeZ;
            break;
        case TXSHAPE3DDISTORTAXIS_POSYONX:
            axisRatio = argVertex.x / sizeX;
            break;
        case TXSHAPE3DDISTORTAXIS_POSYONZ:
            axisRatio = argVertex.z / sizeZ;
            break;
        case TXSHAPE3DDISTORTAXIS_POSZONX:
            axisRatio = argVertex.x / sizeX;
            break;
        case TXSHAPE3DDISTORTAXIS_POSZONY:
            axisRatio = argVertex.y / sizeY;
            break;
        case TXSHAPE3DDISTORTAXIS_POSYZRADIALONX:
            axisRatio = argVertex.x / sizeX;
            break;
        case TXSHAPE3DDISTORTAXIS_POSXZRADIALONY:
            axisRatio = argVertex.y / sizeY;
            break;
        case TXSHAPE3DDISTORTAXIS_POSXYRADIALONZ:
            axisRatio = argVertex.z / sizeZ;
            break;
        default:
            axisRatio = argVertex.x / sizeX;
            break;
    };
    switch (argWaveform) {
        case TXSHAPE3DDISTORTWAVE_WAVE1:
            holdPhase = fmod(holdwave1Phase + (axisRatio * holdwave1Freq), 1.0f);
            waveValue = getWaveValue(holdwave1Type, holdPhase, wave1CustomCurve, wave1CustomCurve2, holdwave1CustomCurveMorph);
            break;
        case TXSHAPE3DDISTORTWAVE_WAVE2:
            holdPhase = fmod(holdwave2Phase + (axisRatio * holdwave2Freq), 1.0f);
            waveValue = getWaveValue(holdwave2Type, holdPhase, wave2CustomCurve, wave2CustomCurve2, holdwave2CustomCurveMorph);
            break;
        case TXSHAPE3DDISTORTWAVE_WAVE3:
            holdPhase = fmod(holdwave3Phase + (axisRatio * holdwave3Freq), 1.0f);
            waveValue = getWaveValue(holdwave3Type, holdPhase, wave3CustomCurve, wave3CustomCurve2, holdwave3CustomCurveMorph);
            break;
        case TXSHAPE3DDISTORTWAVE_WAVE4:
            holdPhase = fmod(holdwave4Phase + (axisRatio * holdwave4Freq), 1.0f);
            waveValue = getWaveValue(holdwave4Type, holdPhase, wave4CustomCurve, wave4CustomCurve2, holdwave4CustomCurveMorph);
            break;
        case TXSHAPE3DDISTORTWAVE_WAVE5:
            holdPhase = fmod(holdwave5Phase + (axisRatio * holdwave5Freq), 1.0f);
            waveValue = getWaveValue(holdwave5Type, holdPhase, wave5CustomCurve, wave5CustomCurve2, holdwave5CustomCurveMorph);
            break;
        case TXSHAPE3DDISTORTWAVE_PERLIN1:
            waveValue = getPerlinValue(holdperlin1Type, holdperlin1Freq, holdperlin1Offset, argVertex, argSizeX, argSizeY, argSizeZ);
            break;
        case TXSHAPE3DDISTORTWAVE_PERLIN2:
            waveValue = getPerlinValue(holdperlin2Type, holdperlin2Freq, holdperlin2Offset, argVertex, argSizeX, argSizeY, argSizeZ);
            break;
        case TXSHAPE3DDISTORTWAVE_PERLIN3:
            waveValue = getPerlinValue(holdperlin3Type, holdperlin3Freq, holdperlin3Offset, argVertex, argSizeX, argSizeY, argSizeZ);
            break;
        default:
            break;
    };
    
    switch (argAxis) {
        case TXSHAPE3DDISTORTAXIS_POSXONY:
            switch (argType) {
                case TXSHAPE3DDISTORTTYPE_MULTIPLYALL:
                    argVertex.x *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYPOS:
                    if (argVertex.x >= 0) {
                        argVertex.x *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYNEG:
                    if (argVertex.x < 0) {
                        argVertex.x *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDALL:
                    argVertex.x += argDepth * waveValue * sizeX;
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOSSUBTRACTNEG:
                    if (argVertex.x >= 0) {
                        argVertex.x += argDepth * waveValue * sizeX;
                    };
                    if (argVertex.x < 0) {
                        argVertex.x -= argDepth * waveValue * sizeX;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOS:
                    if (argVertex.x >= 0) {
                        argVertex.x += argDepth * waveValue * sizeX;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_SUBTRACTNEG:
                    if (argVertex.x < 0) {
                        argVertex.x -= argDepth * waveValue * sizeX;
                    };
                    break;
                default:
                    break;
            };
            break;
        case TXSHAPE3DDISTORTAXIS_POSXONZ:
            switch (argType) {
                case TXSHAPE3DDISTORTTYPE_MULTIPLYALL:
                    argVertex.x *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYPOS:
                    if (argVertex.x >= 0) {
                        argVertex.x *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYNEG:
                    if (argVertex.x < 0) {
                        argVertex.x *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDALL:
                    argVertex.x += argDepth * waveValue * sizeX;
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOSSUBTRACTNEG:
                    if (argVertex.x >= 0) {
                        argVertex.x += argDepth * waveValue * sizeX;
                    };
                    if (argVertex.x < 0) {
                        argVertex.x -= argDepth * waveValue * sizeX;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOS:
                    if (argVertex.x >= 0) {
                        argVertex.x += argDepth * waveValue * sizeX;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_SUBTRACTNEG:
                    if (argVertex.x < 0) {
                        argVertex.x -= argDepth * waveValue * sizeX;
                    };
                    break;
                default:
                    break;
            };
            break;
        case TXSHAPE3DDISTORTAXIS_POSYONX:
            switch (argType) {
                case TXSHAPE3DDISTORTTYPE_MULTIPLYALL:
                    argVertex.y *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYPOS:
                    if (argVertex.y >= 0) {
                        argVertex.y *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYNEG:
                    if (argVertex.y < 0) {
                        argVertex.y *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDALL:
                    argVertex.y += argDepth * waveValue * sizeY;
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOSSUBTRACTNEG:
                    if (argVertex.y >= 0) {
                        argVertex.y += argDepth * waveValue * sizeY;
                    };
                    if (argVertex.y < 0) {
                        argVertex.y -= argDepth * waveValue * sizeY;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOS:
                    if (argVertex.y >= 0) {
                        argVertex.y += argDepth * waveValue * sizeY;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_SUBTRACTNEG:
                    if (argVertex.y < 0) {
                        argVertex.y -= argDepth * waveValue * sizeY;
                    };
                    break;
                default:
                    break;
            };
            break;
        case TXSHAPE3DDISTORTAXIS_POSYONZ:
            if (argType == 0) {
                argVertex.y += argDepth * waveValue * sizeY;
            } else {
                argVertex.y *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
            };
            // TESTING XXX ===========
            switch (argType) {
                case TXSHAPE3DDISTORTTYPE_MULTIPLYALL:
                    argVertex.y *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYPOS:
                    if (argVertex.y >= 0) {
                        argVertex.y *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYNEG:
                    if (argVertex.y < 0) {
                        argVertex.y *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDALL:
                    argVertex.y += argDepth * waveValue * sizeY;
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOSSUBTRACTNEG:
                    if (argVertex.y >= 0) {
                        argVertex.y += argDepth * waveValue * sizeY;
                    };
                    if (argVertex.y < 0) {
                        argVertex.y -= argDepth * waveValue * sizeY;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOS:
                    if (argVertex.y >= 0) {
                        argVertex.y += argDepth * waveValue * sizeY;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_SUBTRACTNEG:
                    if (argVertex.y < 0) {
                        argVertex.y -= argDepth * waveValue * sizeY;
                    };
                    break;
                default:
                    break;
            };
            break;
        case TXSHAPE3DDISTORTAXIS_POSZONX:
            switch (argType) {
                case TXSHAPE3DDISTORTTYPE_MULTIPLYALL:
                    argVertex.z *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYPOS:
                    if (argVertex.z >= 0) {
                        argVertex.z *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYNEG:
                    if (argVertex.z < 0) {
                        argVertex.z *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDALL:
                    argVertex.z += argDepth * waveValue * sizeZ;
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOSSUBTRACTNEG:
                    if (argVertex.z >= 0) {
                        argVertex.z += argDepth * waveValue * sizeZ;
                    };
                    if (argVertex.z < 0) {
                        argVertex.z -= argDepth * waveValue * sizeZ;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOS:
                    if (argVertex.z >= 0) {
                        argVertex.z += argDepth * waveValue * sizeZ;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_SUBTRACTNEG:
                    if (argVertex.z < 0) {
                        argVertex.z -= argDepth * waveValue * sizeZ;
                    };
                    break;
                default:
                    break;
            };
            break;
        case TXSHAPE3DDISTORTAXIS_POSZONY:
            switch (argType) {
                case TXSHAPE3DDISTORTTYPE_MULTIPLYALL:
                    argVertex.z *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYPOS:
                    if (argVertex.z >= 0) {
                        argVertex.z *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYNEG:
                    if (argVertex.z < 0) {
                        argVertex.z *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDALL:
                    argVertex.z += argDepth * waveValue * sizeZ;
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOSSUBTRACTNEG:
                    if (argVertex.z >= 0) {
                        argVertex.z += argDepth * waveValue * sizeZ;
                    };
                    if (argVertex.z < 0) {
                        argVertex.z -= argDepth * waveValue * sizeZ;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOS:
                    if (argVertex.z >= 0) {
                        argVertex.z += argDepth * waveValue * sizeZ;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_SUBTRACTNEG:
                    if (argVertex.z < 0) {
                        argVertex.z -= argDepth * waveValue * sizeZ;
                    };
                    break;
                default:
                    break;
            };
            break;
        case TXSHAPE3DDISTORTAXIS_POSYZRADIALONX:
            switch (argType) {
                case TXSHAPE3DDISTORTTYPE_MULTIPLYALL:
                    argVertex.y *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    argVertex.z *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYPOS:
                    if (argVertex.y >= 0) {
                        argVertex.y *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    if (argVertex.z >= 0) {
                        argVertex.z *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYNEG:
                    if (argVertex.y < 0) {
                        argVertex.y *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    if (argVertex.z < 0) {
                        argVertex.z *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDALL:
                    holdDistortVector = ofVec2f(argVertex.y, argVertex.z);
                    averageSize = (sizeY + sizeZ) * 0.5;
                    holdDistortVector.scale(holdDistortVector.length() + (argDepth * waveValue * averageSize));
                    argVertex.y += holdDistortVector.x;
                    argVertex.z += holdDistortVector.y;
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOSSUBTRACTNEG:
                    holdDistortVector = ofVec2f(argVertex.y, argVertex.z);
                    averageSize = (sizeY + sizeZ) * 0.5;
                    holdDistortVector.scale(holdDistortVector.length() + (argDepth * waveValue * averageSize));
                    if (argVertex.y >= 0) {
                        argVertex.y += holdDistortVector.x;
                    } else {
                        argVertex.y -= holdDistortVector.x;
                    };
                    if (argVertex.z >= 0) {
                        argVertex.z += holdDistortVector.y;
                    } else {
                        argVertex.z -= holdDistortVector.y;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOS:
                    holdDistortVector = ofVec2f(argVertex.y, argVertex.z);
                    averageSize = (sizeY + sizeZ) * 0.5;
                    holdDistortVector.scale(holdDistortVector.length() + (argDepth * waveValue * averageSize));
                    if (argVertex.y >= 0) {
                        argVertex.y += holdDistortVector.x;
                    };
                    if (argVertex.z >= 0) {
                        argVertex.z += holdDistortVector.y;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_SUBTRACTNEG:
                    holdDistortVector = ofVec2f(argVertex.y, argVertex.z);
                    averageSize = (sizeY + sizeZ) * 0.5;
                    holdDistortVector.scale(holdDistortVector.length() + (argDepth * waveValue * averageSize));
                    if (argVertex.y < 0) {
                        argVertex.y -= holdDistortVector.x;
                    };
                    if (argVertex.z < 0) {
                        argVertex.z -= holdDistortVector.y;
                    };
                    break;
                default:
                    break;
            };
            break;
        case TXSHAPE3DDISTORTAXIS_POSXZRADIALONY:
            switch (argType) {
                case TXSHAPE3DDISTORTTYPE_MULTIPLYALL:
                    argVertex.x *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    argVertex.z *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYPOS:
                    if (argVertex.x >= 0) {
                        argVertex.x *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    if (argVertex.z >= 0) {
                        argVertex.z *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYNEG:
                    if (argVertex.x < 0) {
                        argVertex.x *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    if (argVertex.z < 0) {
                        argVertex.z *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDALL:
                    holdDistortVector = ofVec2f(argVertex.x, argVertex.z);
                    averageSize = (sizeX + sizeZ) * 0.5;
                    holdDistortVector.scale(holdDistortVector.length() + (argDepth * waveValue * averageSize));
                    argVertex.x += holdDistortVector.x;
                    argVertex.z += holdDistortVector.y;
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOSSUBTRACTNEG:
                    holdDistortVector = ofVec2f(argVertex.x, argVertex.z);
                    averageSize = (sizeX + sizeZ) * 0.5;
                    holdDistortVector.scale(holdDistortVector.length() + (argDepth * waveValue * averageSize));
                    if (argVertex.x >= 0) {
                        argVertex.x += holdDistortVector.x;
                    };
                    if (argVertex.x < 0) {
                        argVertex.x -= holdDistortVector.x;
                    };
                    
                    if (argVertex.z >= 0) {
                        argVertex.z += holdDistortVector.y;
                    };
                    if (argVertex.z < 0) {
                        argVertex.z -= holdDistortVector.y;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOS:
                    holdDistortVector = ofVec2f(argVertex.x, argVertex.z);
                    averageSize = (sizeX + sizeZ) * 0.5;
                    holdDistortVector.scale(holdDistortVector.length() + (argDepth * waveValue * averageSize));
                    if (argVertex.x >= 0) {
                        argVertex.x += holdDistortVector.x;
                    };
                    if (argVertex.z >= 0) {
                        argVertex.z += holdDistortVector.y;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_SUBTRACTNEG:
                    holdDistortVector = ofVec2f(argVertex.x, argVertex.z);
                    averageSize = (sizeX + sizeZ) * 0.5;
                    holdDistortVector.scale(holdDistortVector.length() + (argDepth * waveValue * averageSize));
                    if (argVertex.x < 0) {
                        argVertex.x -= holdDistortVector.x;
                    };
                    if (argVertex.z < 0) {
                        argVertex.z -= holdDistortVector.y;
                    };
                    break;
                default:
                    break;
            };
            break;
        case TXSHAPE3DDISTORTAXIS_POSXYRADIALONZ:
            switch (argType) {
                case TXSHAPE3DDISTORTTYPE_MULTIPLYALL:
                    argVertex.x *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    argVertex.y *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYPOS:
                    if (argVertex.x >= 0) {
                        argVertex.x *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    if (argVertex.y >= 0) {
                        argVertex.y *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYNEG:
                    if (argVertex.x < 0) {
                        argVertex.x *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    if (argVertex.y < 0) {
                        argVertex.y *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDALL:
                    holdDistortVector = ofVec2f(argVertex.x, argVertex.y);
                    averageSize = (sizeX + sizeY) * 0.5;
                    holdDistortVector.scale(holdDistortVector.length() + (argDepth * waveValue * averageSize));
                    argVertex.x += holdDistortVector.x;
                    argVertex.y += holdDistortVector.y;
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOSSUBTRACTNEG:
                    holdDistortVector = ofVec2f(argVertex.x, argVertex.y);
                    averageSize = (sizeX + sizeY) * 0.5;
                    holdDistortVector.scale(holdDistortVector.length() + (argDepth * waveValue * averageSize));
                    if (argVertex.x >= 0) {
                        argVertex.x += holdDistortVector.x;
                    };
                    if (argVertex.x < 0) {
                        argVertex.x -= holdDistortVector.x;
                    };
                    
                    if (argVertex.y >= 0) {
                        argVertex.y += holdDistortVector.y;
                    };
                    if (argVertex.y < 0) {
                        argVertex.y -= holdDistortVector.y;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOS:
                    holdDistortVector = ofVec2f(argVertex.x, argVertex.y);
                    averageSize = (sizeX + sizeY) * 0.5;
                    holdDistortVector.scale(holdDistortVector.length() + (argDepth * waveValue * averageSize));
                    if (argVertex.x >= 0) {
                        argVertex.x += holdDistortVector.x;
                    };
                    if (argVertex.y >= 0) {
                        argVertex.y += holdDistortVector.y;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_SUBTRACTNEG:
                    holdDistortVector = ofVec2f(argVertex.x, argVertex.y);
                    averageSize = (sizeX + sizeY) * 0.5;
                    holdDistortVector.scale(holdDistortVector.length() + (argDepth * waveValue * averageSize));
                    if (argVertex.x < 0) {
                        argVertex.x -= holdDistortVector.x;
                    };
                    if (argVertex.y < 0) {
                        argVertex.y -= holdDistortVector.y;
                    };
                    break;
                default:
                    break;
            };
            break;
        default:
            break;
    };
}

////////////////////////////// listeners

void  TXDrawShape3DMulti::imageAssetSlotChanged(string slotNameArg) {
    if (slotNameArg == "sourceImageAsset") {
        sourceImageHasChanged = true;
    };
}
void  TXDrawShape3DMulti::useImageAsTextureChanged(bool & boolArg) {
    retryMapTexture = true;
}
void  TXDrawShape3DMulti::useExternalSourceImageChanged(bool & boolArg) {
    retryMapTexture = true;
}

void TXDrawShape3DMulti::loadSourceImage() {
    ofPtr <TXAsset> asset;
    string fileName;
    int sourceImageAssetID = getImageAssetIDSlot("sourceImageAsset").first;
    if (sourceImageAssetID != 0) {
        asset = parentSystem->getAsset(TXASSETTYPE_IMAGE, sourceImageAssetID);
        fileName = asset->getFileName();
        parentSystem->imageLoader.loadFromDisk(*newImage, fileName);
    };
}

bool TXDrawShape3DMulti::mapTextureToShape() {
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
            if (!(sourceImage->getTexture().isAllocated())) {
                validTexture = false;
                retryMapTexture = true;
            } else {
                holdTexture = sourceImage->getTexture();
                validTexture = true;
            };
        };
        if (validTexture) {
            texWidth = holdTexture.getWidth();
            texHeight = holdTexture.getHeight();
            switch (shapeType->getInt()) {
                case TXSHAPE3DTYPE_SPHERE:
                    sphere.mapTexCoordsFromTexture( holdTexture);
                    break;
                case TXSHAPE3DTYPE_ICOSPHERE:
                    icoSphere.mapTexCoordsFromTexture( holdTexture);
                    break;
                case TXSHAPE3DTYPE_BOX:
                    box.mapTexCoordsFromTexture( holdTexture);
                    break;
                case TXSHAPE3DTYPE_PLANE:
                    // resize the plane to the size of the texture //
                    plane.resizeToTexture( holdTexture);
                    break;
                case TXSHAPE3DTYPE_CYLINDER:
                    sphere.mapTexCoordsFromTexture( holdTexture);
                    cylinder.mapTexCoordsFromTexture( holdTexture);
                    break;
                case TXSHAPE3DTYPE_ROUNDEDCYLINDER:
                    sphere.mapTexCoordsFromTexture( holdTexture);
                    cylinder.mapTexCoordsFromTexture( holdTexture);
                    break;
                case TXSHAPE3DTYPE_UNCAPPEDCYLINDER:
                    cylinder.mapTexCoordsFromTexture( holdTexture);
                    break;
                case TXSHAPE3DTYPE_CONE:
                    cone.mapTexCoordsFromTexture( holdTexture);
                    break;
                case TXSHAPE3DTYPE_ROUNDEDCONE:
                    sphere.mapTexCoordsFromTexture( holdTexture);
                    cone.mapTexCoordsFromTexture( holdTexture);
                    break;
                case TXSHAPE3DTYPE_UNCAPPEDCONE:
                    cone.mapTexCoordsFromTexture( holdTexture);
                    //uncappedCone.mapTexCoordsFromTexture( holdTexture);
                    break;
//                case TXSHAPE3DTYPE_ICOSAHEDRON:
//                    icosahedron.mapTexCoordsFromTexture( holdTexture);
//                    break;
                default:
                    // default = paraShape
                    paraShape.mapTexCoordsFromTexture( holdTexture);
                    break;
            }
        };
    };
    return validTexture;
}

int TXDrawShape3DMulti::getTextureWidth() {
    if (sourceImage->getTexture().isAllocated()) {
        return sourceImage->getWidth();
    } else {
        return 0;
    };
}

int TXDrawShape3DMulti::getTextureHeight() {
    if (sourceImage->getTexture().isAllocated()) {
        return sourceImage->getHeight();
    } else {
        return 0;
    };
}

ofTexture * TXDrawShape3DMulti::getTexture() {
    if (sourceImage->getTexture().isAllocated()) {
        return & sourceImage->getTexture();
    } else {
        return NULL;
    };
}

ofPixelsRef TXDrawShape3DMulti::getPixels() {
    return sourceImage->getPixels() ;
}
//////////////////////////////

float TXDrawShape3DMulti::getWaveValue(int & waveType, float & phase, TXParameterFloat256 & customCurve, TXParameterFloat256 & customCurve2, float customCurveMorph) {
    float outValue, holdVal;
    // adjust phase for negative values
    if (phase < 0) {
       phase = phase + 1;
    };
    switch (waveType) {
        case TXSHAPE3DDISTORTWAVEFORM_SINE:
            outValue = 0.5 + (0.5 * sin(TWO_PI * phase));
            break;
        case TXSHAPE3DDISTORTWAVEFORM_COSINE:
            outValue = 0.5 + (0.5 * cos(TWO_PI * phase));
            break;
        case TXSHAPE3DDISTORTWAVEFORM_SQUARE:
            outValue = (int) phase >= 0.5;
            break;
        case TXSHAPE3DDISTORTWAVEFORM_RAMPUP:
            outValue = phase;
            break;
        case TXSHAPE3DDISTORTWAVEFORM_RAMPDOWN:
            outValue = 1 - phase;
            break;
        case TXSHAPE3DDISTORTWAVEFORM_TRIANGLE:
            outValue = abs(1.0f - (2.0f * fmod(phase + 0.75f, 1.0f)));
            break;
        case TXSHAPE3DDISTORTWAVEFORM_CUSTOMCURVE:
            outValue = TXFunctions::getInterpCurves(customCurve, customCurve2, phase, customCurveMorph);
            break;
        case TXSHAPE3DDISTORTWAVEFORM_CUSTOMCURVE_MIRRORED:
            if (phase<0.5) {
                holdVal = 2 * phase;
            } else {
                holdVal = 1 - (2 * (phase - 0.5));
            };
            outValue = TXFunctions::getInterpCurves(customCurve, customCurve2, phase, customCurveMorph);
            break;
        default:
            // default rampup
            outValue = phase;
            break;
    }
    return outValue;
}

float TXDrawShape3DMulti::getPerlinValue(int & perlinType, float & perlinFreq, float & perlinOffset, ofVec3f & position, float & argSizeX, float & argSizeY, float & argSizeZ) {
    float holdValue, holdPerlin;
    int holdSign;
    float outValue, phase, offsetX, offsetY, offsetZ;
    // based on trefoil knot
    // trefoilX = sin t + 2 sin 2t;
    // trefoilY = cos t - 2 cos 2t;
    // trefoilZ = - sin 3t;
    phase = perlinOffset * TWO_PI;
    offsetX = 0.1666666666 * (sin(phase) + (2 * sin(2 * phase)));
    offsetY = 0.1666666666 * (cos(phase) - (2 * cos(2 * phase)));
    offsetZ = 0.1666666666 * -sin(3 * phase);
    holdPerlin = ofSignedNoise(offsetX + (position.x * perlinFreq / argSizeX),
                               offsetY + (position.y * perlinFreq / argSizeY),
                               offsetZ + (position.z * perlinFreq / argSizeZ));
    switch (perlinType) {
        case PERLINTYPE_NORMAL:
            outValue = (holdPerlin + 1) / 2;
            break;
        case PERLINTYPE_QUANTISED:
            holdValue = (holdPerlin + 1) / 2;
            if (holdValue < 0.5) {
                outValue = 0.0;
            } else {
                outValue = 1.0;
            }
            break;
//        case PERLINTYPE_SQUARED:
//            if (holdPerlin < 0) {holdSign = -1;} else {holdSign = 1;};
//            holdValue = pow(abs(holdPerlin), 0.5f) * holdSign;
//            outValue = (holdValue + 1) / 2;
//            break;
//            // NOTE PERLINTYPE_RANDOMWALK IS v SIMILAR TO ORIGINAL PERLINTYPE_NORMAL
//        case PERLINTYPE_RANDOMWALK:
//            holdPerlin = holdPerlin / 25;
//            if ( ((accumlator + (holdPerlin * flipper)) > 1) || ((accumlator + (holdPerlin * flipper)) < 0)) {
//                flipper = flipper * -1;
//            };
//            accumlator += (holdPerlin * flipper);
//            outValue = accumlator;
//            break;
        default:
            outValue = 0.0;
            break;
    };
    return outValue;
}
//////////////////////////////

void TXDrawShape3DMulti::buildRoundedCylinder(float height, float roundness) {
    // invert sphere triangles
    int totalIndices = sphere.getMesh().getNumIndices();
    ofIndexType hold1, hold3;
    for( int i=0; i < totalIndices; i+=3 ){
        hold1 = sphere.getMesh().getIndex(i);
        hold3 = sphere.getMesh().getIndex(min(i+2, totalIndices-1));
        sphere.getMesh().setIndex(i, hold3);
        sphere.getMesh().setIndex(min(i+2, totalIndices-1), hold1);
    };
    roundedCylinder.getMesh() = cylinder.getMesh();
    roundedTopCapMesh = sphere.getMesh();
    roundedBottomCapMesh = sphere.getMesh();
    int totalVertices = sphere.getMesh().getNumVertices();
    ofVec3f holdTopVertex;
    ofVec3f holdBottomVertex;
    float halfHeight = height * 0.5;
    float holdRoundness = max(0.001f, roundness);
    // flatten bottom/top of top/bottom cap
    for(int i = 0; i < totalVertices; i++ ) {
        holdTopVertex = roundedTopCapMesh.getVertex( i );
        holdBottomVertex = holdTopVertex;
        // change relevent vertices
        if (holdTopVertex.y < 0.0) {
            holdTopVertex.y = 0.0;
        } else if (holdTopVertex.y > 0.0) {
            holdTopVertex.y = holdTopVertex.y * holdRoundness;
        };
        holdTopVertex.y = holdTopVertex.y + halfHeight;
        roundedTopCapMesh.setVertex(i, holdTopVertex);
        
        if (holdBottomVertex.y > 0.0) {
            holdBottomVertex.y = 0.0;
        } else if (holdBottomVertex.y < 0.0) {
            holdBottomVertex.y = holdBottomVertex.y * holdRoundness;
        };
        holdBottomVertex.y = holdBottomVertex.y - halfHeight;
        roundedBottomCapMesh.setVertex(i, holdBottomVertex);
    }
    roundedCylinder.getMesh().append(roundedTopCapMesh);
    roundedCylinder.getMesh().append(roundedBottomCapMesh);
}

void TXDrawShape3DMulti::buildRoundedCone(float height, float roundness) {
    // invert sphere triangles
    int totalIndices = sphere.getMesh().getNumIndices();
    ofIndexType hold1, hold3;
    for( int i=0; i < totalIndices; i+=3 ){
        hold1 = sphere.getMesh().getIndex(i);
        hold3 = sphere.getMesh().getIndex(min(i+2, totalIndices-1));
        sphere.getMesh().setIndex(i, hold3);
        sphere.getMesh().setIndex(min(i+2, totalIndices-1), hold1);
    };
    roundedCone.getMesh() = cone.getMesh();
    roundedTopCapMesh = sphere.getMesh();
    int totalVertices = sphere.getMesh().getNumVertices();
    ofVec3f holdTopVertex;
    float halfHeight = height * 0.5;
    float holdRoundness = max(0.001f, roundness);
    for(int i = 0; i < totalVertices; i++ ) {
        holdTopVertex = roundedTopCapMesh.getVertex( i );
        // change relevent vertices
        if (holdTopVertex.y < 0.0) {
            holdTopVertex.y = 0.0;
        } else if (holdTopVertex.y > 0.0) {
            holdTopVertex.y = holdTopVertex.y * holdRoundness;
        };
        holdTopVertex.y = holdTopVertex.y + halfHeight;
        roundedTopCapMesh.setVertex(i, holdTopVertex);
    }
    roundedCone.getMesh().append(roundedTopCapMesh);
}

bool TXDrawShape3DMulti::isParaShape() {
    return (shapeType->getInt() >= (total3DShapeTypes - TXParaShape::totalShapes));
};

//////////////////////////////

void TXDrawShape3DMulti::setDistortOrderIndices(int argA, int argB, int argC) {
    distortOrderIndices[0] = argA;
    distortOrderIndices[1] = argB;
    distortOrderIndices[2] = argC;
}

// listener methods

void  TXDrawShape3DMulti::shapeTypeChanged(ofAbstractParameter & parameterArg ){
    retryMapTexture = true;
    resolutionParaShapeHasChanged = true;
}

void  TXDrawShape3DMulti::resolutionParaShapeChanged(int & intArg) {
    resolutionParaShapeHasChanged = true;
}

void TXDrawShape3DMulti::calcDistortedMeshNormals(ofVboMesh &distortedMesh, bool bNormalize){
    int ia;
    int ib;
    int ic;
    int holdNumIndices = distortedMesh.getNumIndices();
    int holdNumVertices = distortedMesh.getNumVertices();
    // reset normals
    for( int i=0; i < distortedMesh.getVertices().size(); i++ ) distortedMesh.getNormals()[i] = ofPoint(0,0,0);
    // if no indices, use vertices
    if (holdNumIndices == 0) {
        for( int i=0; i < holdNumVertices; i+=3 ){
            ofVec3f verta = distortedMesh.getVertices()[i];
            ofVec3f vertb = distortedMesh.getVertices()[min(i+1, holdNumVertices-1)];
            ofVec3f vertc = distortedMesh.getVertices()[min(i+2, holdNumVertices-1)];
            ofVec3f e1 = verta - vertb;
            ofVec3f e2 = vertc - vertb;
            ofVec3f no = e2.cross( e1 );
            if (invertDistortedNormals) {
                distortedMesh.getNormals()[i] -= no;
                distortedMesh.getNormals()[min(i+1, holdNumVertices-1)] -= no;
                distortedMesh.getNormals()[min(i+2, holdNumVertices-1)] -= no;
            } else {
                distortedMesh.getNormals()[i] += no;
                distortedMesh.getNormals()[min(i+1, holdNumVertices-1)] += no;
                distortedMesh.getNormals()[min(i+2, holdNumVertices-1)] += no;
            };
        }
    } else {
        if (distortedMesh.getMode() == OF_PRIMITIVE_TRIANGLES) {
            for( int i=0; i < holdNumIndices; i+=3 ){
                ia = distortedMesh.getIndices()[i];
                ib = distortedMesh.getIndices()[min(i+1, holdNumIndices-1)];
                ic = distortedMesh.getIndices()[min(i+2, holdNumIndices-1)];
                ofVec3f e1 = distortedMesh.getVertices()[ia] - distortedMesh.getVertices()[ib];
                ofVec3f e2 = distortedMesh.getVertices()[ic] - distortedMesh.getVertices()[ib];
                ofVec3f no = e2.cross( e1 );
                if (invertDistortedNormals) {
                    distortedMesh.getNormals()[ia] -= no;
                    distortedMesh.getNormals()[ib] -= no;
                    distortedMesh.getNormals()[ic] -= no;
                } else {
                    distortedMesh.getNormals()[ia] += no;
                    distortedMesh.getNormals()[ib] += no;
                    distortedMesh.getNormals()[ic] += no;
                };
            }
        } else {
            // OF_PRIMITIVE_TRIANGLE_STRIP
            for( int i=0; i < holdNumIndices; i++ ){
                ia = distortedMesh.getIndices()[max(i-1, 0)];
                ib = distortedMesh.getIndices() [i];
                ic = distortedMesh.getIndices()[min(i+1, holdNumIndices-1)];
                ofVec3f e1 = distortedMesh.getVertices()[ia] - distortedMesh.getVertices()[ib];
                ofVec3f e2 = distortedMesh.getVertices()[ic] - distortedMesh.getVertices()[ib];
                ofVec3f no = e2.cross( e1 );
                // depending on clockwise / winding order, subtract no if normals are flipped.
                if (invertDistortedNormals) {
                    distortedMesh.getNormals()[ib] -= no;
                } else {
                    distortedMesh.getNormals()[ib] += no;
                };
            }
        };
    };
    
    if (bNormalize) {
        for(int i=0; i < distortedMesh.getNormals().size(); i++ ) {
            distortedMesh.getNormals()[i].normalize();
        }
    }
}


