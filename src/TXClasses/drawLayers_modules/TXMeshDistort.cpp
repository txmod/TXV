/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXSystem.h"
#include "TXMeshDistort.h"
#include "TXFunctions.h"


// constructor
TXMeshDistort::TXMeshDistort() {
    setup();
}

// destructor
TXMeshDistort::~TXMeshDistort() {
}

void TXMeshDistort::setup(){
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
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
    
    holdModParamBoolArgs.name = "useDepthTesting";
    holdModParamBoolArgs.fixedValue = true;
    useDepthTesting = createModParameter(holdModParamBoolArgs);
    parameters.add(useDepthTesting->parameters);
    
    holdModParamBoolArgs.name = "useLighting";
    holdModParamBoolArgs.fixedValue = true;
    useLighting = createModParameter(holdModParamBoolArgs);
    parameters.add(useLighting->parameters);
    
    parameters.add(smoothLighting.set("smoothLighting", true));
    parameters.add(drawLights.set("drawLights", false));
    
    holdModParamBoolArgs.name = "renderContinuosly";
    holdModParamBoolArgs.fixedValue = true;
    renderContinuosly = createModParameter(holdModParamBoolArgs);
    parameters.add(renderContinuosly->parameters);
    
    holdModParamBoolArgs.name = "renderNow";
    holdModParamBoolArgs.fixedValue = false;
    renderNow = createModParameter(holdModParamBoolArgs);
    parameters.add(renderNow->parameters);
    
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
    
    holdModParamBoolArgs.name = "distortionActive";
    holdModParamBoolArgs.fixedValue = true;
    distortionActive = createModParameter(holdModParamBoolArgs);
    parameters.add(distortionActive->parameters);
    
    holdModParamBoolArgs.name = "distortAfterMatrix";
    holdModParamBoolArgs.fixedValue = true;
    distortAfterMatrix = createModParameter(holdModParamBoolArgs);
    parameters.add(distortAfterMatrix->parameters);
    
    holdModParamIntArgs.name = "wave1Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXMESHDISTORTWAVETYPE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXMESHDISTORTWAVETYPE_TOTAL - 1;
    wave1Type = createModParameter(holdModParamIntArgs);
    parameters.add(wave1Type->parameters);
    
    holdModParamFloatArgs.name = "wave1Phase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    wave1Phase = createModParameter(holdModParamFloatArgs);
    parameters.add(wave1Phase->parameters);
    
    holdModParamFloatArgs.name = "wave1Freq";
    holdModParamFloatArgs.fixedValue = 4.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 20.0;
    wave1Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(wave1Freq->parameters);
    
    holdModParamFloatArgs.name = "wave1AmpX";
    holdModParamFloatArgs.fixedValue = 100.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 100.0;
    wave1AmpX = createModParameter(holdModParamFloatArgs);
    parameters.add(wave1AmpX->parameters);
    
    holdModParamFloatArgs.name = "wave1AmpY";
    holdModParamFloatArgs.fixedValue = 100.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 100.0;
    wave1AmpY = createModParameter(holdModParamFloatArgs);
    parameters.add(wave1AmpY->parameters);
    
    holdModParamFloatArgs.name = "wave1AmpZ";
    holdModParamFloatArgs.fixedValue = 100.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 100.0;
    wave1AmpZ = createModParameter(holdModParamFloatArgs);
    parameters.add(wave1AmpZ->parameters);
    
    holdModParamIntArgs.name = "wave2Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXMESHDISTORTWAVETYPE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXMESHDISTORTWAVETYPE_TOTAL - 1;
    wave2Type = createModParameter(holdModParamIntArgs);
    parameters.add(wave2Type->parameters);
    
    holdModParamFloatArgs.name = "wave2Phase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    wave2Phase = createModParameter(holdModParamFloatArgs);
    parameters.add(wave2Phase->parameters);
    
    holdModParamFloatArgs.name = "wave2Freq";
    holdModParamFloatArgs.fixedValue = 4.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 20.0;
    wave2Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(wave2Freq->parameters);
    
    holdModParamFloatArgs.name = "wave2AmpX";
    holdModParamFloatArgs.fixedValue = 100.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 100.0;
    wave2AmpX = createModParameter(holdModParamFloatArgs);
    parameters.add(wave2AmpX->parameters);
    
    holdModParamFloatArgs.name = "wave2AmpY";
    holdModParamFloatArgs.fixedValue = 100.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 100.0;
    wave2AmpY = createModParameter(holdModParamFloatArgs);
    parameters.add(wave2AmpY->parameters);
    
    holdModParamFloatArgs.name = "wave2AmpZ";
    holdModParamFloatArgs.fixedValue = 100.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 100.0;
    wave2AmpZ = createModParameter(holdModParamFloatArgs);
    parameters.add(wave2AmpZ->parameters);
    
    holdModParamIntArgs.name = "wave3Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXMESHDISTORTWAVETYPE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXMESHDISTORTWAVETYPE_TOTAL - 1;
    wave3Type = createModParameter(holdModParamIntArgs);
    parameters.add(wave3Type->parameters);
    
    holdModParamFloatArgs.name = "wave3Phase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    wave3Phase = createModParameter(holdModParamFloatArgs);
    parameters.add(wave3Phase->parameters);
    
    holdModParamFloatArgs.name = "wave3Freq";
    holdModParamFloatArgs.fixedValue = 4.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 20.0;
    wave3Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(wave3Freq->parameters);
    
    holdModParamFloatArgs.name = "wave3AmpX";
    holdModParamFloatArgs.fixedValue = 100.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 100.0;
    wave3AmpX = createModParameter(holdModParamFloatArgs);
    parameters.add(wave3AmpX->parameters);
    
    holdModParamFloatArgs.name = "wave3AmpY";
    holdModParamFloatArgs.fixedValue = 100.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 100.0;
    wave3AmpY = createModParameter(holdModParamFloatArgs);
    parameters.add(wave3AmpY->parameters);
    
    holdModParamFloatArgs.name = "wave3AmpZ";
    holdModParamFloatArgs.fixedValue = 100.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 100.0;
    wave3AmpZ = createModParameter(holdModParamFloatArgs);
    parameters.add(wave3AmpZ->parameters);
    
    holdModParamIntArgs.name = "wave4Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXMESHDISTORTWAVETYPE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXMESHDISTORTWAVETYPE_TOTAL - 1;
    wave4Type = createModParameter(holdModParamIntArgs);
    parameters.add(wave4Type->parameters);
    
    holdModParamFloatArgs.name = "wave4Phase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    wave4Phase = createModParameter(holdModParamFloatArgs);
    parameters.add(wave4Phase->parameters);
    
    holdModParamFloatArgs.name = "wave4Freq";
    holdModParamFloatArgs.fixedValue = 4.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 20.0;
    wave4Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(wave4Freq->parameters);
    
    holdModParamFloatArgs.name = "wave4AmpX";
    holdModParamFloatArgs.fixedValue = 100.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 100.0;
    wave4AmpX = createModParameter(holdModParamFloatArgs);
    parameters.add(wave4AmpX->parameters);
    
    holdModParamFloatArgs.name = "wave4AmpY";
    holdModParamFloatArgs.fixedValue = 100.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 100.0;
    wave4AmpY = createModParameter(holdModParamFloatArgs);
    parameters.add(wave4AmpY->parameters);
    
    holdModParamFloatArgs.name = "wave4AmpZ";
    holdModParamFloatArgs.fixedValue = 100.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 100.0;
    wave4AmpZ = createModParameter(holdModParamFloatArgs);
    parameters.add(wave4AmpZ->parameters);
    
    holdModParamFloatArgs.name = "alpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	alpha = createModParameter(holdModParamFloatArgs);
    parameters.add(alpha->parameters);
    
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
    holdModParamFloatArgs.softMax = 10.0;
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
    
    /////
    
    holdModParamBoolArgs.name = "light1Active";
    holdModParamBoolArgs.fixedValue = true;
    light1Active = createModParameter(holdModParamBoolArgs);
    parameters.add(light1Active->parameters);
    
    holdModParamIntArgs.name = "light1Type";
    holdModParamIntArgs.fixedValue = TXLIGHTTYPE_POINT;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXLIGHTTYPE_TOTAL-1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXLIGHTTYPE_TOTAL-1;
	light1Type = createModParameter(holdModParamIntArgs);
    parameters.add(light1Type->parameters);
    
    holdModParamFloatArgs.name = "light1DiffuseColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light1DiffuseColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(light1DiffuseColorHue->parameters);
    
    holdModParamFloatArgs.name = "light1DiffuseColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light1DiffuseColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(light1DiffuseColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "light1DiffuseColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light1DiffuseColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(light1DiffuseColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "light1DiffuseColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.4;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light1DiffuseColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(light1DiffuseColorBrightness->parameters);
    
    holdModParamBoolArgs.name = "light1DiffuseColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	light1DiffuseColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(light1DiffuseColorHSBAsRGB->parameters);
    
    parameters.add(light1UseDiffuseColorForAmbient.set("light1UseDiffuseColorForAmbient", false));
    
    holdModParamFloatArgs.name = "light1AmbientColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light1AmbientColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(light1AmbientColorHue->parameters);
    
    holdModParamFloatArgs.name = "light1AmbientColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light1AmbientColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(light1AmbientColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "light1AmbientColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light1AmbientColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(light1AmbientColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "light1AmbientColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.185;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light1AmbientColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(light1AmbientColorBrightness->parameters);
    
    holdModParamBoolArgs.name = "light1AmbientColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	light1AmbientColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(light1AmbientColorHSBAsRGB->parameters);
    
    parameters.add(light1UseDiffuseColorForSpecular.set("light1UseDiffuseColorForSpecular", false));
    
    holdModParamFloatArgs.name = "light1SpecularColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light1SpecularColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(light1SpecularColorHue->parameters);
    
    holdModParamFloatArgs.name = "light1SpecularColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light1SpecularColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(light1SpecularColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "light1SpecularColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light1SpecularColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(light1SpecularColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "light1SpecularColorBrightness";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light1SpecularColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(light1SpecularColorBrightness->parameters);
    
    holdModParamBoolArgs.name = "light1SpecularColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	light1SpecularColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(light1SpecularColorHSBAsRGB->parameters);
    
    holdModParamFloatArgs.name = "light1PositionX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10000.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = -1000.0;
    holdModParamFloatArgs.softMax = 1000;
	light1PositionX = createModParameter(holdModParamFloatArgs);
    parameters.add(light1PositionX->parameters);
    
    holdModParamFloatArgs.name = "light1PositionY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10000.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = -1000;
    holdModParamFloatArgs.softMax = 1000;
	light1PositionY = createModParameter(holdModParamFloatArgs);
    parameters.add(light1PositionY->parameters);
    
    holdModParamFloatArgs.name = "light1PositionZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10000.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = -1000;
    holdModParamFloatArgs.softMax = 1000;
	light1PositionZ = createModParameter(holdModParamFloatArgs);
    parameters.add(light1PositionZ->parameters);
    
    holdModParamFloatArgs.name = "light1OrientationX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	light1OrientationX = createModParameter(holdModParamFloatArgs);
    parameters.add(light1OrientationX->parameters);
    
    holdModParamFloatArgs.name = "light1OrientationY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	light1OrientationY = createModParameter(holdModParamFloatArgs);
    parameters.add(light1OrientationY->parameters);
    
    holdModParamFloatArgs.name = "light1OrientationZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	light1OrientationZ = createModParameter(holdModParamFloatArgs);
    parameters.add(light1OrientationZ->parameters);
    
    holdModParamIntArgs.name = "light1SpotConcentration";
    holdModParamIntArgs.fixedValue = 64;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 128;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 128;
	light1SpotConcentration = createModParameter(holdModParamIntArgs);
    parameters.add(light1SpotConcentration->parameters);
    
    holdModParamFloatArgs.name = "light1SpotlightAngle";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 90.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 90.0;
	light1SpotlightAngle = createModParameter(holdModParamFloatArgs);
    parameters.add(light1SpotlightAngle->parameters);
    
    /////
    
    holdModParamBoolArgs.name = "light2Active";
    holdModParamBoolArgs.fixedValue = false;
    light2Active = createModParameter(holdModParamBoolArgs);
    parameters.add(light2Active->parameters);
    
    holdModParamIntArgs.name = "light2Type";
    holdModParamIntArgs.fixedValue = TXLIGHTTYPE_POINT;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXLIGHTTYPE_TOTAL-1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXLIGHTTYPE_TOTAL-1;
	light2Type = createModParameter(holdModParamIntArgs);
    parameters.add(light2Type->parameters);
    
    holdModParamFloatArgs.name = "light2DiffuseColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light2DiffuseColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(light2DiffuseColorHue->parameters);
    
    holdModParamFloatArgs.name = "light2DiffuseColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light2DiffuseColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(light2DiffuseColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "light2DiffuseColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light2DiffuseColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(light2DiffuseColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "light2DiffuseColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.4;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light2DiffuseColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(light2DiffuseColorBrightness->parameters);
    
    holdModParamBoolArgs.name = "light2DiffuseColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	light2DiffuseColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(light2DiffuseColorHSBAsRGB->parameters);
    
    parameters.add(light2UseDiffuseColorForAmbient.set("light2UseDiffuseColorForAmbient", false));
    
    holdModParamFloatArgs.name = "light2AmbientColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light2AmbientColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(light2AmbientColorHue->parameters);
    
    holdModParamFloatArgs.name = "light2AmbientColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light2AmbientColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(light2AmbientColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "light2AmbientColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light2AmbientColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(light2AmbientColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "light2AmbientColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.185;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light2AmbientColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(light2AmbientColorBrightness->parameters);
    
    holdModParamBoolArgs.name = "light2AmbientColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	light2AmbientColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(light2AmbientColorHSBAsRGB->parameters);
    
    parameters.add(light2UseDiffuseColorForSpecular.set("light2UseDiffuseColorForSpecular", false));
    
    holdModParamFloatArgs.name = "light2SpecularColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light2SpecularColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(light2SpecularColorHue->parameters);
    
    holdModParamFloatArgs.name = "light2SpecularColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light2SpecularColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(light2SpecularColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "light2SpecularColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light2SpecularColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(light2SpecularColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "light2SpecularColorBrightness";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light2SpecularColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(light2SpecularColorBrightness->parameters);
    
    holdModParamBoolArgs.name = "light2SpecularColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	light2SpecularColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(light2SpecularColorHSBAsRGB->parameters);
    
    holdModParamFloatArgs.name = "light2PositionX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10000.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = -1000.0;
    holdModParamFloatArgs.softMax = 1000;
	light2PositionX = createModParameter(holdModParamFloatArgs);
    parameters.add(light2PositionX->parameters);
    
    holdModParamFloatArgs.name = "light2PositionY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10000.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = -1000;
    holdModParamFloatArgs.softMax = 1000;
	light2PositionY = createModParameter(holdModParamFloatArgs);
    parameters.add(light2PositionY->parameters);
    
    holdModParamFloatArgs.name = "light2PositionZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10000.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = -1000;
    holdModParamFloatArgs.softMax = 1000;
	light2PositionZ = createModParameter(holdModParamFloatArgs);
    parameters.add(light2PositionZ->parameters);
    
    holdModParamFloatArgs.name = "light2OrientationX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	light2OrientationX = createModParameter(holdModParamFloatArgs);
    parameters.add(light2OrientationX->parameters);
    
    holdModParamFloatArgs.name = "light2OrientationY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	light2OrientationY = createModParameter(holdModParamFloatArgs);
    parameters.add(light2OrientationY->parameters);
    
    holdModParamFloatArgs.name = "light2OrientationZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	light2OrientationZ = createModParameter(holdModParamFloatArgs);
    parameters.add(light2OrientationZ->parameters);
    
    holdModParamIntArgs.name = "light2SpotConcentration";
    holdModParamIntArgs.fixedValue = 64;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 128;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 128;
	light2SpotConcentration = createModParameter(holdModParamIntArgs);
    parameters.add(light2SpotConcentration->parameters);
    
    holdModParamFloatArgs.name = "light2SpotlightAngle";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 90.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 90.0;
	light2SpotlightAngle = createModParameter(holdModParamFloatArgs);
    parameters.add(light2SpotlightAngle->parameters);
    
    /////
    
    holdModParamBoolArgs.name = "light3Active";
    holdModParamBoolArgs.fixedValue = false;
    light3Active = createModParameter(holdModParamBoolArgs);
    parameters.add(light3Active->parameters);
    
    holdModParamIntArgs.name = "light3Type";
    holdModParamIntArgs.fixedValue = TXLIGHTTYPE_POINT;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXLIGHTTYPE_TOTAL-1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXLIGHTTYPE_TOTAL-1;
	light3Type = createModParameter(holdModParamIntArgs);
    parameters.add(light3Type->parameters);
    
    holdModParamFloatArgs.name = "light3DiffuseColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light3DiffuseColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(light3DiffuseColorHue->parameters);
    
    holdModParamFloatArgs.name = "light3DiffuseColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light3DiffuseColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(light3DiffuseColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "light3DiffuseColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light3DiffuseColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(light3DiffuseColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "light3DiffuseColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.4;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light3DiffuseColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(light3DiffuseColorBrightness->parameters);
    
    holdModParamBoolArgs.name = "light3DiffuseColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	light3DiffuseColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(light3DiffuseColorHSBAsRGB->parameters);
    
    parameters.add(light3UseDiffuseColorForAmbient.set("light3UseDiffuseColorForAmbient", false));
    
    holdModParamFloatArgs.name = "light3AmbientColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light3AmbientColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(light3AmbientColorHue->parameters);
    
    holdModParamFloatArgs.name = "light3AmbientColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light3AmbientColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(light3AmbientColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "light3AmbientColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light3AmbientColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(light3AmbientColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "light3AmbientColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.185;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light3AmbientColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(light3AmbientColorBrightness->parameters);
    
    holdModParamBoolArgs.name = "light3AmbientColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	light3AmbientColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(light3AmbientColorHSBAsRGB->parameters);
    
    parameters.add(light3UseDiffuseColorForSpecular.set("light3UseDiffuseColorForSpecular", false));
    
    holdModParamFloatArgs.name = "light3SpecularColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light3SpecularColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(light3SpecularColorHue->parameters);
    
    holdModParamFloatArgs.name = "light3SpecularColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light3SpecularColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(light3SpecularColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "light3SpecularColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light3SpecularColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(light3SpecularColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "light3SpecularColorBrightness";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light3SpecularColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(light3SpecularColorBrightness->parameters);
    
    holdModParamBoolArgs.name = "light3SpecularColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	light3SpecularColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(light3SpecularColorHSBAsRGB->parameters);
    
    holdModParamFloatArgs.name = "light3PositionX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10000.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = -1000.0;
    holdModParamFloatArgs.softMax = 1000;
	light3PositionX = createModParameter(holdModParamFloatArgs);
    parameters.add(light3PositionX->parameters);
    
    holdModParamFloatArgs.name = "light3PositionY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10000.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = -1000;
    holdModParamFloatArgs.softMax = 1000;
	light3PositionY = createModParameter(holdModParamFloatArgs);
    parameters.add(light3PositionY->parameters);
    
    holdModParamFloatArgs.name = "light3PositionZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10000.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = -1000;
    holdModParamFloatArgs.softMax = 1000;
	light3PositionZ = createModParameter(holdModParamFloatArgs);
    parameters.add(light3PositionZ->parameters);
    
    holdModParamFloatArgs.name = "light3OrientationX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	light3OrientationX = createModParameter(holdModParamFloatArgs);
    parameters.add(light3OrientationX->parameters);
    
    holdModParamFloatArgs.name = "light3OrientationY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	light3OrientationY = createModParameter(holdModParamFloatArgs);
    parameters.add(light3OrientationY->parameters);
    
    holdModParamFloatArgs.name = "light3OrientationZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	light3OrientationZ = createModParameter(holdModParamFloatArgs);
    parameters.add(light3OrientationZ->parameters);
    
    holdModParamIntArgs.name = "light3SpotConcentration";
    holdModParamIntArgs.fixedValue = 64;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 128;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 128;
	light3SpotConcentration = createModParameter(holdModParamIntArgs);
    parameters.add(light3SpotConcentration->parameters);
    
    holdModParamFloatArgs.name = "light3SpotlightAngle";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 90.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 90.0;
	light3SpotlightAngle = createModParameter(holdModParamFloatArgs);
    parameters.add(light3SpotlightAngle->parameters);
    
    /////
    
    holdModParamBoolArgs.name = "cam1Active";
    holdModParamBoolArgs.fixedValue = true;
    cam1Active = createModParameter(holdModParamBoolArgs);
    parameters.add(cam1Active->parameters);
    
    holdModParamIntArgs.name = "cam1PositionMode";
    holdModParamIntArgs.fixedValue = TXCAMERAPOSITIONMODE_USEPOSITIONXYZ;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCAMERAPOSITIONMODE_TOTAL-1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCAMERAPOSITIONMODE_TOTAL-1;
	cam1PositionMode = createModParameter(holdModParamIntArgs);
    parameters.add(cam1PositionMode->parameters);
    
    holdModParamFloatArgs.name = "cam1PositionX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10000.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = -1000.0;
    holdModParamFloatArgs.softMax = 1000;
	cam1PositionX = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1PositionX->parameters);
    
    holdModParamFloatArgs.name = "cam1PositionY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10000.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = -1000;
    holdModParamFloatArgs.softMax = 1000;
	cam1PositionY = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1PositionY->parameters);
    
    holdModParamFloatArgs.name = "cam1PositionZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10000.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = -1000;
    holdModParamFloatArgs.softMax = 1000;
	cam1PositionZ = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1PositionZ->parameters);
    
    holdModParamFloatArgs.name = "cam1TruckX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10000.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = -1000.0;
    holdModParamFloatArgs.softMax = 1000;
	cam1TruckX = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1TruckX->parameters);
    
    holdModParamBoolArgs.name = "cam1TruckXTrigger";
    holdModParamBoolArgs.fixedValue = false;
    cam1TruckXTrigger = createModParameter(holdModParamBoolArgs);
    parameters.add(cam1TruckXTrigger->parameters);
    
    holdModParamFloatArgs.name = "cam1BoomY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10000.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = -1000.0;
    holdModParamFloatArgs.softMax = 1000;
	cam1BoomY = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1BoomY->parameters);
    
    holdModParamBoolArgs.name = "cam1BoomYTrigger";
    holdModParamBoolArgs.fixedValue = false;
    cam1BoomYTrigger = createModParameter(holdModParamBoolArgs);
    parameters.add(cam1BoomYTrigger->parameters);
    
    holdModParamFloatArgs.name = "cam1DollyZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10000.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = -1000.0;
    holdModParamFloatArgs.softMax = 1000;
	cam1DollyZ = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1DollyZ->parameters);
    
    holdModParamBoolArgs.name = "cam1DollyZTrigger";
    holdModParamBoolArgs.fixedValue = false;
    cam1DollyZTrigger = createModParameter(holdModParamBoolArgs);
    parameters.add(cam1DollyZTrigger->parameters);
    
    holdModParamBoolArgs.name = "cam1FreezePosition";
    holdModParamBoolArgs.fixedValue = false;
    cam1FreezePosition = createModParameter(holdModParamBoolArgs);
    parameters.add(cam1FreezePosition->parameters);
    
    holdModParamBoolArgs.name = "cam1ResetToPositionXYZ";
    holdModParamBoolArgs.fixedValue = false;
    cam1ResetToPositionXYZ = createModParameter(holdModParamBoolArgs);
    parameters.add(cam1ResetToPositionXYZ->parameters);
    
    holdModParamFloatArgs.name = "cam1OrbitPointX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10000.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = -1000.0;
    holdModParamFloatArgs.softMax = 1000;
	cam1OrbitPointX = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1OrbitPointX->parameters);
    
    holdModParamFloatArgs.name = "cam1OrbitPointY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10000.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = -1000;
    holdModParamFloatArgs.softMax = 1000;
	cam1OrbitPointY = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1OrbitPointY->parameters);
    
    holdModParamFloatArgs.name = "cam1OrbitPointZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10000.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = -1000;
    holdModParamFloatArgs.softMax = 1000;
	cam1OrbitPointZ = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1OrbitPointZ->parameters);
    
    holdModParamFloatArgs.name = "cam1OrbitLongitude";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	cam1OrbitLongitude = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1OrbitLongitude->parameters);
    
    holdModParamFloatArgs.name = "cam1OrbitLatitude";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	cam1OrbitLatitude = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1OrbitLatitude->parameters);
    
    holdModParamFloatArgs.name = "cam1OrbitRadius";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1000;
	cam1OrbitRadius = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1OrbitRadius->parameters);
    
    /////
    
    holdModParamIntArgs.name = "cam1OrientationMode";
    holdModParamIntArgs.fixedValue = TXCAMERAORIENTATIONMODE_USEROTATIONXYZ;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCAMERAORIENTATIONMODE_TOTAL-1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCAMERAORIENTATIONMODE_TOTAL-1;
	cam1OrientationMode = createModParameter(holdModParamIntArgs);
    parameters.add(cam1OrientationMode->parameters);
    
    holdModParamFloatArgs.name = "cam1RotationX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	cam1RotationX = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1RotationX->parameters);
    
    holdModParamFloatArgs.name = "cam1RotationY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	cam1RotationY = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1RotationY->parameters);
    
    holdModParamFloatArgs.name = "cam1RotationZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	cam1RotationZ = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1RotationZ->parameters);
    
    holdModParamFloatArgs.name = "cam1TiltX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	cam1TiltX = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1TiltX->parameters);
    
    holdModParamBoolArgs.name = "cam1TiltXTrigger";
    holdModParamBoolArgs.fixedValue = false;
    cam1TiltXTrigger = createModParameter(holdModParamBoolArgs);
    parameters.add(cam1TiltXTrigger->parameters);
    
    holdModParamFloatArgs.name = "cam1PanY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	cam1PanY = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1PanY->parameters);
    
    holdModParamBoolArgs.name = "cam1PanYTrigger";
    holdModParamBoolArgs.fixedValue = false;
    cam1PanYTrigger = createModParameter(holdModParamBoolArgs);
    parameters.add(cam1PanYTrigger->parameters);
    
    holdModParamFloatArgs.name = "cam1RollZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	cam1RollZ = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1RollZ->parameters);
    
    holdModParamBoolArgs.name = "cam1RollZTrigger";
    holdModParamBoolArgs.fixedValue = false;
    cam1RollZTrigger = createModParameter(holdModParamBoolArgs);
    parameters.add(cam1RollZTrigger->parameters);
    
    holdModParamBoolArgs.name = "cam1FreezeRotation";
    holdModParamBoolArgs.fixedValue = false;
    cam1FreezeRotation = createModParameter(holdModParamBoolArgs);
    parameters.add(cam1FreezeRotation->parameters);
    
    holdModParamBoolArgs.name = "cam1ResetToRotationXYZ";
    holdModParamBoolArgs.fixedValue = false;
    cam1ResetToRotationXYZ = createModParameter(holdModParamBoolArgs);
    parameters.add(cam1ResetToRotationXYZ->parameters);
    
    holdModParamFloatArgs.name = "cam1LookAtPointX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10000.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = -1000.0;
    holdModParamFloatArgs.softMax = 1000;
	cam1LookAtPointX = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1LookAtPointX->parameters);
    
    holdModParamFloatArgs.name = "cam1LookAtPointY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10000.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = -1000;
    holdModParamFloatArgs.softMax = 1000;
	cam1LookAtPointY = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1LookAtPointY->parameters);
    
    holdModParamFloatArgs.name = "cam1LookAtPointZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10000.0;
    holdModParamFloatArgs.hardMax = 10000.0;
    holdModParamFloatArgs.softMin = -1000;
    holdModParamFloatArgs.softMax = 1000;
	cam1LookAtPointZ = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1LookAtPointZ->parameters);
    
    // add listener to relevent parameters:
    smoothLighting.addListener(this, &TXMeshDistort::smoothLightingChanged);
    
    // initialise
    oldCam1ResetToPositionXYZ = false;
    oldCam1ResetToRotationXYZ = false;
    ofSetSmoothLighting(true);

    oldRenderNow = false;
    oldClearNow = false;

    // set up texture
    allocateTexture();
    registerTexture();

    // load shaders
#ifdef TARGET_OPENGLES
	drawShader.load("shadersES2/AlphaTextureShader.vert","shadersES2/AlphaTextureShader.frag");
#else
	if(ofIsGLProgrammableRenderer()){
		drawShader.load("shadersGL3/AlphaTextureShader.vert", "shadersGL3/AlphaTextureShader.frag");
	}else{
		drawShader.load("shadersGL2/AlphaTextureShader.vert", "shadersGL2/AlphaTextureShader.frag");
	}
#endif
    
    string vString = "_ShaderGroups/FXShaders1Tex/meshDistort.vert";
    string fString = "_ShaderGroups/FXShaders1Tex/meshDistort.frag";
//    string vString = "lightsOrange.vert";
//    string fString = "lightsOrange.frag";
    
#ifdef TARGET_OPENGLES
	renderShader.load("shadersES2/" + vString,"shadersES2/" + fString);
    //	renderShader.load("shadersES2/" + vString, "");
#else
	if(ofIsGLProgrammableRenderer()){
        renderShader.load("shadersGL3/" + vString,"shadersGL3/" + fString);
        //        renderShader.load("shadersGL3/" + vString, "");
	}else{
        renderShader.load("shadersGL2/" + vString,"shadersGL2/" + fString);
        //        renderShader.load("shadersGL2/" + vString, "");
	}
#endif
    
}

void TXMeshDistort::update(){
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
    // check whether to render
    if (newRenderContinuosly || (newRenderNow && (newRenderNow != oldRenderNow)) || clearNowNewTrigger) {
        renderTexture(clearFirst);
    };
    // reset vars
    oldClearNow = newClearNow;
    oldRenderNow = newRenderNow;

    // sets camera position and orientation
    float holdFrameTime = 1.0 / parentSystem->targetFrameRate;
    bool newCam1ResetToPositionXYZ;
    bool holdCam1ResetToPositionXYZ;
    bool newCam1TruckXTrigger;
    bool newCam1BoomYTrigger;
    bool newCam1DollyZTrigger;
    bool holdCam1TruckXTrigger;
    bool holdCam1BoomYTrigger;
    bool holdCam1DollyZTrigger;
    ofVec3f holdOrbitPoint;
    
    switch (cam1PositionMode->getInt()) {
        case TXCAMERAPOSITIONMODE_USEPOSITIONXYZ:
            cam1.setPosition(cam1PositionX->getFloat(), cam1PositionY->getFloat(), cam1PositionZ->getFloat());
            break;
        case TXCAMERAPOSITIONMODE_TRUCKBOOMDOLLY:
            newCam1ResetToPositionXYZ = cam1ResetToPositionXYZ->getBool();
            holdCam1ResetToPositionXYZ = (newCam1ResetToPositionXYZ && (newCam1ResetToPositionXYZ != oldCam1ResetToPositionXYZ));
            // check for reset else move
            if (holdCam1ResetToPositionXYZ) {
                cam1.setPosition(cam1PositionX->getFloat(), cam1PositionY->getFloat(), cam1PositionZ->getFloat());
            } else {
                if (!cam1FreezePosition->getBool()) {
                    cam1.truck(cam1TruckX->getFloat() * holdFrameTime);
                    cam1.boom(cam1BoomY->getFloat() * holdFrameTime);
                    cam1.dolly(cam1DollyZ->getFloat() * holdFrameTime);
                };
            };
            oldCam1ResetToPositionXYZ = newCam1ResetToPositionXYZ;
            break;
        case TXCAMERAPOSITIONMODE_TRIGTRUCKBOOMDOLLY:
            newCam1ResetToPositionXYZ = cam1ResetToPositionXYZ->getBool();
            holdCam1ResetToPositionXYZ = (newCam1ResetToPositionXYZ && (newCam1ResetToPositionXYZ != oldCam1ResetToPositionXYZ));
            // check for reset else move if triggered
            if (holdCam1ResetToPositionXYZ) {
                cam1.setPosition(cam1PositionX->getFloat(), cam1PositionY->getFloat(), cam1PositionZ->getFloat());
            } else {
                if (!cam1FreezePosition->getBool()) {
                    // move if triggered
                    newCam1TruckXTrigger = cam1TruckXTrigger->getBool();
                    newCam1BoomYTrigger = cam1BoomYTrigger->getBool();
                    newCam1DollyZTrigger = cam1DollyZTrigger->getBool();
                    holdCam1TruckXTrigger = (newCam1TruckXTrigger && (newCam1TruckXTrigger != oldCam1TruckXTrigger));
                    holdCam1BoomYTrigger = (newCam1BoomYTrigger && (newCam1BoomYTrigger != oldCam1BoomYTrigger));
                    holdCam1DollyZTrigger = (newCam1DollyZTrigger && (newCam1DollyZTrigger != oldCam1DollyZTrigger));
                    if (holdCam1TruckXTrigger) {
                        cam1.truck(cam1TruckX->getFloat());
                    };
                    if (holdCam1BoomYTrigger) {
                        cam1.boom(cam1BoomY->getFloat());
                    };
                    if (holdCam1DollyZTrigger) {
                        cam1.dolly(cam1DollyZ->getFloat());
                    };
                };
            };
            oldCam1ResetToPositionXYZ = newCam1ResetToPositionXYZ;
            oldCam1TruckXTrigger = newCam1TruckXTrigger;
            oldCam1BoomYTrigger = newCam1BoomYTrigger;
            oldCam1DollyZTrigger = newCam1DollyZTrigger;
            break;
        case TXCAMERAPOSITIONMODE_ORBIT:
            holdOrbitPoint = ofVec3f(cam1OrbitPointX->getFloat(), cam1OrbitPointY->getFloat(), cam1OrbitPointZ->getFloat());
            cam1.orbit(cam1OrbitLongitude->getFloat(), cam1OrbitLatitude->getFloat(), cam1OrbitRadius->getFloat(), holdOrbitPoint);
            break;
        default:
            cam1.setPosition(cam1PositionX->getFloat(), cam1PositionY->getFloat(), cam1PositionZ->getFloat());
            break;
    }
    
    bool newCam1ResetToRotationXYZ;
    bool holdCam1ResetToRotationXYZ;
    bool newCam1TiltXTrigger;
    bool newCam1PanYTrigger;
    bool newCam1RollZTrigger;
    bool holdCam1TiltXTrigger;
    bool holdCam1PanYTrigger;
    bool holdCam1RollZTrigger;
    ofVec3f holdLookAtPoint;
    ofVec3f holdOrientation;
    
    switch (cam1OrientationMode->getInt()) {
        case TXCAMERAORIENTATIONMODE_USEROTATIONXYZ:
            holdOrientation = ofVec3f(cam1RotationX->getFloat(), cam1RotationY->getFloat(), cam1RotationZ->getFloat());
            cam1.setOrientation(holdOrientation);
            break;
        case TXCAMERAORIENTATIONMODE_TILTPANROLL:
            newCam1ResetToRotationXYZ = cam1ResetToRotationXYZ->getBool();
            holdCam1ResetToRotationXYZ = (newCam1ResetToRotationXYZ && (newCam1ResetToRotationXYZ != oldCam1ResetToRotationXYZ));
            // check for reset else move
            if (holdCam1ResetToRotationXYZ) {
                holdOrientation = ofVec3f(cam1RotationX->getFloat(), cam1RotationY->getFloat(), cam1RotationZ->getFloat());
                cam1.setOrientation(holdOrientation);
            } else {
                if (!cam1FreezeRotation->getBool()) {
                    cam1.tilt(cam1TiltX->getFloat() * holdFrameTime);
                    cam1.pan(cam1PanY->getFloat() * holdFrameTime);
                    cam1.roll(cam1RollZ->getFloat() * holdFrameTime);
                };
            };
            oldCam1ResetToRotationXYZ = newCam1ResetToRotationXYZ;
            break;
        case TXCAMERAORIENTATIONMODE_TRIGTILTPANROLL:
            newCam1ResetToRotationXYZ = cam1ResetToRotationXYZ->getBool();
            holdCam1ResetToRotationXYZ = (newCam1ResetToRotationXYZ && (newCam1ResetToRotationXYZ != oldCam1ResetToRotationXYZ));
            // check for reset else move
            if (holdCam1ResetToRotationXYZ) {
                holdOrientation = ofVec3f(cam1RotationX->getFloat(), cam1RotationY->getFloat(), cam1RotationZ->getFloat());
                cam1.setOrientation(holdOrientation);
            } else {
                if (!cam1FreezeRotation->getBool()) {
                    // move if triggered
                    newCam1TiltXTrigger = cam1TiltXTrigger->getBool();
                    newCam1PanYTrigger = cam1PanYTrigger->getBool();
                    newCam1RollZTrigger = cam1RollZTrigger->getBool();
                    holdCam1TiltXTrigger = (newCam1TiltXTrigger && (newCam1TiltXTrigger != oldCam1TiltXTrigger));
                    holdCam1PanYTrigger = (newCam1PanYTrigger && (newCam1PanYTrigger != oldCam1PanYTrigger));
                    holdCam1RollZTrigger = (newCam1RollZTrigger && (newCam1RollZTrigger != oldCam1RollZTrigger));
                    if (holdCam1TiltXTrigger) {
                        cam1.tilt(cam1TiltX->getFloat());
                    };
                    if (holdCam1PanYTrigger) {
                        cam1.pan(cam1PanY->getFloat());
                    };
                    if (holdCam1RollZTrigger) {
                        cam1.roll(cam1RollZ->getFloat());
                    };
                };
            };
            oldCam1ResetToRotationXYZ = newCam1ResetToRotationXYZ;
            oldCam1TiltXTrigger = newCam1TiltXTrigger;
            oldCam1PanYTrigger = newCam1PanYTrigger;
            oldCam1RollZTrigger = newCam1RollZTrigger;
            break;
        case TXCAMERAORIENTATIONMODE_LOOKATPOINT:
            holdLookAtPoint = ofVec3f(cam1LookAtPointX->getFloat(), cam1LookAtPointY->getFloat(), cam1LookAtPointZ->getFloat());
            cam1.lookAt(holdLookAtPoint);
            break;
        default:
            cam1.tilt(cam1RotationX->getFloat());
            cam1.pan(cam1RotationY->getFloat());
            cam1.roll(cam1RotationZ->getFloat());
            break;
    }
}

void TXMeshDistort::draw(){
    // check before drawing
    if (!drawActive->getBool()) {
        return;
    };

    //bool setUniforms = true;
    float drawXAdjusted, drawYAdjusted;
    float holdDrawPosX, holdDrawPosY;
	int   drawWidthPixels, drawHeightPixels;
    float anchorXPixels, anchorYPixels;
    float holdScaleX, holdScaleY;
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
    //    ofLogNotice() << "testing xxx  TXMeshDistort::draw -  widthNextPow2Ratio, heightNextPow2Ratio, outImage.getWidth(), outImage.getHeight()";
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
    //if (setUniforms) {
        drawShader.setUniform1f("u_alpha", alpha->getFloat());
        drawShader.setUniform1f("u_alphaThreshold", parentSystem->alphaThreshold);
        drawShader.setUniformTexture("u_texture0Sampler", outImage.getTexture(0), 0);
    //};
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

void TXMeshDistort::allocateTexture() {
    outImage.allocate(getMaxWidth(), getMaxHeight());
    outImage.begin();
    ofClear(0,255);
    outImage.end();
    pix.allocate(getMaxWidth(), getMaxHeight(), OF_IMAGE_COLOR_ALPHA);
}

void TXMeshDistort::renderTexture(bool clearFirstArg) {
    outImage.begin();
    if (clearFirstArg) {
        ofColor newColor = ofColor::fromHsb(clearColorHue->getFloat() * 255, clearColorSaturation->getFloat() * 255, clearColorBrightness->getFloat() * 255, clearColorAlpha->getFloat() * 255);
        ofEnableAlphaBlending();
        ofClear(newColor);
        ofDisableAlphaBlending();
    };

    bool holduseDepthTesting = useDepthTesting->getBool();
    if (holduseDepthTesting) {
        ofEnableDepthTest();
    } else {
        ofDisableDepthTest();
    };
    
    // begin camera //
    bool holdcam1Active = cam1Active->getBool();
    if (holdcam1Active) {
        cam1.begin();
    };
    
    // enable lighting //
    bool holduseLighting = useLighting->getBool();
    bool holdlight1Active = light1Active->getBool();
    bool holdlight2Active = light2Active->getBool();
    bool holdlight3Active = light3Active->getBool();
    int  holdlight1Type = light1Type->getInt();
    int  holdlight2Type = light2Type->getInt();
    int  holdlight3Type = light3Type->getInt();
  
    if (holduseLighting) {
        ofEnableLighting();
        // activate the lights //
        if (holdlight1Active) {
            light1.enable();
            setLight1DiffuseColor();
            setLight1AmbientColor();
            setLight1SpecularColor();
            setLight1Position();
            setLight1Orientation();
            switch (light1Type->getInt()) {
                case TXLIGHTTYPE_POINT:
                    light1.setPointLight();
                    break;
                case TXLIGHTTYPE_DIRECTIONAL:
                    light1.setDirectional();
                    break;
                case TXLIGHTTYPE_SPOT:
                    light1.setSpotlight();
                    light1.setSpotConcentration(light1SpotConcentration->getInt());
                    light1.setSpotlightCutOff (light1SpotlightAngle->getFloat());
                    break;
                default:
                    break;
            }
        };
        if (holdlight2Active) {
            light2.enable();
            setLight2DiffuseColor();
            setLight2AmbientColor();
            setLight2SpecularColor();
            setLight2Position();
            setLight2Orientation();
            switch (light2Type->getInt()) {
                case TXLIGHTTYPE_POINT:
                    light2.setPointLight();
                    break;
                case TXLIGHTTYPE_DIRECTIONAL:
                    light2.setDirectional();
                    break;
                case TXLIGHTTYPE_SPOT:
                    light2.setSpotlight();
                    light2.setSpotConcentration(light2SpotConcentration->getInt());
                    light2.setSpotlightCutOff (light2SpotlightAngle->getFloat());
                    break;
                default:
                    break;
            }
        };
        if (holdlight3Active) {
            light3.enable();
            setLight3DiffuseColor();
            setLight3AmbientColor();
            setLight3SpecularColor();
            setLight3Position();
            setLight3Orientation();
            switch (light3Type->getInt()) {
                case TXLIGHTTYPE_POINT:
                    light3.setPointLight();
                    break;
                case TXLIGHTTYPE_DIRECTIONAL:
                    light3.setDirectional();
                    break;
                case TXLIGHTTYPE_SPOT:
                    light3.setSpotlight();
                    light3.setSpotConcentration(light3SpotConcentration->getInt());
                    light3.setSpotlightCutOff (light3SpotlightAngle->getFloat());
                    break;
                default:
                    break;
            }
        };
    };

    renderShader.begin();
    renderShader.setUniform1i("distortionActive", (int) distortionActive->getBool());
    renderShader.setUniform1i("distortAfterMatrix", (int) distortAfterMatrix->getBool());
    renderShader.setUniform1i("wave1Type", wave1Type->getInt());
    renderShader.setUniform1i("wave2Type", wave2Type->getInt());
    renderShader.setUniform1i("wave3Type", wave3Type->getInt());
    renderShader.setUniform1i("wave4Type", wave4Type->getInt());
    renderShader.setUniform1f("wave1Phase", wave1Phase->getFloat());
    renderShader.setUniform1f("wave2Phase", wave2Phase->getFloat());
    renderShader.setUniform1f("wave3Phase", wave3Phase->getFloat());
    renderShader.setUniform1f("wave4Phase", wave4Phase->getFloat());
    renderShader.setUniform1f("wave1Freq", wave1Freq->getFloat() / getMaxWidth());
    renderShader.setUniform1f("wave2Freq", wave2Freq->getFloat() / getMaxWidth());
    renderShader.setUniform1f("wave3Freq", wave3Freq->getFloat() / getMaxWidth());
    renderShader.setUniform1f("wave4Freq", wave4Freq->getFloat() / getMaxWidth());
    renderShader.setUniform3f("wave1Amp", wave1AmpX->getFloat(), wave1AmpY->getFloat(), wave1AmpZ->getFloat());
    renderShader.setUniform3f("wave2Amp", wave2AmpX->getFloat(), wave2AmpY->getFloat(), wave2AmpZ->getFloat());
    renderShader.setUniform3f("wave3Amp", wave3AmpX->getFloat(), wave3AmpY->getFloat(), wave3AmpZ->getFloat());
    renderShader.setUniform3f("wave4Amp", wave4AmpX->getFloat(), wave4AmpY->getFloat(), wave4AmpZ->getFloat());

    if (holdcam1Active) {
        renderShader.setUniform1i("LocalViewer", 1);
    } else {
        renderShader.setUniform1i("LocalViewer", 0);
    };
    if ((holdlight1Type != 1) || (holdlight2Type != 1) ||  (holdlight3Type != 1)) {
        renderShader.setUniform1i("NeedEyePosition", 1);
    } else {
        renderShader.setUniform1i("NeedEyePosition", 0);
    };

    // use base to draw layers
    TXDrawLayersBase::draw((TXDRAWLAYERSRULE)drawLayersRule->getInt());
    
    renderShader.end();

    // disable lighting //
    if (holduseLighting) {
        if (holdlight1Active) light1.disable();
        if (holdlight2Active) light2.disable();
        if (holdlight3Active) light3.disable();
        ofDisableLighting();
        if (drawLights) {
            ofSetColor( light1.getDiffuseColor() );
            if(holdlight1Active ) light1.draw();
            ofSetColor( light2.getDiffuseColor() );
            if(holdlight2Active ) light2.draw();
            ofSetColor( light3.getDiffuseColor() );
            if(holdlight3Active ) light3.draw();
        };
    };
    // end camera //
    if (holdcam1Active) {
        cam1.end();
    };
    if (holduseDepthTesting) {
        ofDisableDepthTest();
    };

    ofClearAlpha();
    outImage.end();
    ofSetColor(255.0f);
}

void TXMeshDistort::windowResized(int w, int h) {
    if (maxWidthHeightRule != MAXWIDTHHEIGHTRULE_CUSTOMSIZE) {
        allocateTexture();
        outImage.begin();
        ofColor newColor = ofColor::fromHsb(clearColorHue->getFloat() * 255, clearColorSaturation->getFloat() * 255, clearColorBrightness->getFloat() * 255, clearColorAlpha->getFloat() * 255);
        ofEnableAlphaBlending();
        ofClear(newColor);
        ofDisableAlphaBlending();
        outImage.end();
    };
}

int TXMeshDistort::getTextureWidth() {
    return outImage.getWidth();
}

int TXMeshDistort::getTextureHeight() {
    return outImage.getHeight();
}

ofTexture *  TXMeshDistort::getTexture() {
    return & outImage.getTexture();
}

ofPixelsRef TXMeshDistort::getPixels() {
    outImage.readToPixels(pix);
    return pix;
}

void  TXMeshDistort::smoothLightingChanged(bool & boolArg) {
    if (smoothLighting) {
        ofSetSmoothLighting(true);
    } else {
        ofSetSmoothLighting(false);
    };
}

// set methods
void  TXMeshDistort::setLight1DiffuseColor() {
    ofColor holdColor =  TXFunctions::txGetColor(light1DiffuseColorHue->getFloat(),  light1DiffuseColorSaturation->getFloat(),  light1DiffuseColorBrightness->getFloat(),  1, light1DiffuseColorHueRotate->getFloat(), light1DiffuseColorHSBAsRGB->getBool());
    light1.setDiffuseColor(holdColor);
    if (light1UseDiffuseColorForAmbient) {
        light1.setAmbientColor(holdColor);
    };
    if (light1UseDiffuseColorForSpecular) {
        light1.setSpecularColor(holdColor);
    };
}

void  TXMeshDistort::setLight1AmbientColor() {
    if (light1UseDiffuseColorForAmbient) {
        light1.setAmbientColor(light1.getDiffuseColor());
    } else {
        ofColor holdColor =  TXFunctions::txGetColor(light1AmbientColorHue->getFloat(),  light1AmbientColorSaturation->getFloat(),  light1AmbientColorBrightness->getFloat(),  1, light1AmbientColorHueRotate->getFloat(), light1AmbientColorHSBAsRGB->getBool());
        light1.setAmbientColor(holdColor);
    };
}

void  TXMeshDistort::setLight1SpecularColor() {
    if (light1UseDiffuseColorForSpecular) {
        light1.setSpecularColor(light1.getDiffuseColor());
    } else {
        ofColor holdColor =  TXFunctions::txGetColor(light1SpecularColorHue->getFloat(),  light1SpecularColorSaturation->getFloat(),  light1SpecularColorBrightness->getFloat(),  1, light1SpecularColorHueRotate->getFloat(), light1SpecularColorHSBAsRGB->getBool());
        light1.setSpecularColor(holdColor);
    };
}

void  TXMeshDistort::setLight1Position() {
    light1.setPosition(light1PositionX->getFloat(), light1PositionY->getFloat(), light1PositionZ->getFloat());
}

void  TXMeshDistort::setLight1Orientation() {
    light1.setOrientation(ofVec3f(light1OrientationX->getFloat(), light1OrientationY->getFloat(), light1OrientationZ->getFloat()));
}


void  TXMeshDistort::setLight2DiffuseColor() {
    ofColor holdColor =  TXFunctions::txGetColor(light2DiffuseColorHue->getFloat(),  light2DiffuseColorSaturation->getFloat(),  light2DiffuseColorBrightness->getFloat(),  1, light2DiffuseColorHueRotate->getFloat(), light2DiffuseColorHSBAsRGB->getBool());
    if (light2DiffuseColorHSBAsRGB->getBool()) {
        holdColor.set( light2DiffuseColorHue->getFloat() * 255,  light2DiffuseColorSaturation->getFloat() * 255,  light2DiffuseColorBrightness->getFloat() * 255,  255);
    } else {
        holdColor = ofColor::fromHsb( light2DiffuseColorHue->getFloat() * 255,  light2DiffuseColorSaturation->getFloat() * 255,  light2DiffuseColorBrightness->getFloat() * 255,  255);
    };
    light2.setDiffuseColor(holdColor);
    if (light2UseDiffuseColorForAmbient) {
        light2.setAmbientColor(holdColor);
    };
    if (light2UseDiffuseColorForSpecular) {
        light2.setSpecularColor(holdColor);
    };
}

void  TXMeshDistort::setLight2AmbientColor() {
    if (light2UseDiffuseColorForAmbient) {
        light2.setAmbientColor(light2.getDiffuseColor());
    } else {
        ofColor holdColor =  TXFunctions::txGetColor(light2AmbientColorHue->getFloat(),  light2AmbientColorSaturation->getFloat(),  light2AmbientColorBrightness->getFloat(),  1, light2AmbientColorHueRotate->getFloat(), light2AmbientColorHSBAsRGB->getBool());
        if (light2AmbientColorHSBAsRGB->getBool()) {
            holdColor.set( light2AmbientColorHue->getFloat() * 255,  light2AmbientColorSaturation->getFloat() * 255,  light2AmbientColorBrightness->getFloat() * 255,  255);
        } else {
            holdColor = ofColor::fromHsb( light2AmbientColorHue->getFloat() * 255,  light2AmbientColorSaturation->getFloat() * 255,  light2AmbientColorBrightness->getFloat() * 255,  255);
        };
        light2.setAmbientColor(holdColor);
    };
}

void  TXMeshDistort::setLight2SpecularColor() {
    if (light2UseDiffuseColorForAmbient) {
        light2.setSpecularColor(light2.getDiffuseColor());
    } else {
        ofColor holdColor =  TXFunctions::txGetColor(light2SpecularColorHue->getFloat(),  light2SpecularColorSaturation->getFloat(),  light2SpecularColorBrightness->getFloat(),  1, light2SpecularColorHueRotate->getFloat(), light2SpecularColorHSBAsRGB->getBool());
        if (light2SpecularColorHSBAsRGB->getBool()) {
            holdColor.set( light2SpecularColorHue->getFloat() * 255,  light2SpecularColorSaturation->getFloat() * 255,  light2SpecularColorBrightness->getFloat() * 255,  255);
        } else {
            holdColor = ofColor::fromHsb( light2SpecularColorHue->getFloat() * 255,  light2SpecularColorSaturation->getFloat() * 255,  light2SpecularColorBrightness->getFloat() * 255,  255);
        };
        light2.setSpecularColor(holdColor);
    };
}

void  TXMeshDistort::setLight2Position() {
    light2.setPosition(light2PositionX->getFloat(), light2PositionY->getFloat(), light2PositionZ->getFloat());
}

void  TXMeshDistort::setLight2Orientation() {
    light2.setOrientation(ofVec3f(light2OrientationX->getFloat(), light2OrientationY->getFloat(), light2OrientationZ->getFloat()));
}


void  TXMeshDistort::setLight3DiffuseColor() {
    ofColor holdColor =  TXFunctions::txGetColor(light3DiffuseColorHue->getFloat(),  light3DiffuseColorSaturation->getFloat(),  light3DiffuseColorBrightness->getFloat(),  1, light3DiffuseColorHueRotate->getFloat(), light3DiffuseColorHSBAsRGB->getBool());
    if (light3DiffuseColorHSBAsRGB->getBool()) {
        holdColor.set( light3DiffuseColorHue->getFloat() * 255,  light3DiffuseColorSaturation->getFloat() * 255,  light3DiffuseColorBrightness->getFloat() * 255,  255);
    } else {
        holdColor = ofColor::fromHsb( light3DiffuseColorHue->getFloat() * 255,  light3DiffuseColorSaturation->getFloat() * 255,  light3DiffuseColorBrightness->getFloat() * 255,  255);
    };
    light3.setDiffuseColor(holdColor);
    if (light3UseDiffuseColorForAmbient) {
        light3.setAmbientColor(holdColor);
    };
    if (light3UseDiffuseColorForSpecular) {
        light3.setSpecularColor(holdColor);
    };
}

void  TXMeshDistort::setLight3AmbientColor() {
    if (light3UseDiffuseColorForAmbient) {
        light3.setAmbientColor(light3.getDiffuseColor());
    } else {
        ofColor holdColor =  TXFunctions::txGetColor(light3AmbientColorHue->getFloat(),  light3AmbientColorSaturation->getFloat(),  light3AmbientColorBrightness->getFloat(),  1, light3AmbientColorHueRotate->getFloat(), light3AmbientColorHSBAsRGB->getBool());
        if (light3AmbientColorHSBAsRGB->getBool()) {
            holdColor.set( light3AmbientColorHue->getFloat() * 255,  light3AmbientColorSaturation->getFloat() * 255,  light3AmbientColorBrightness->getFloat() * 255,  255);
        } else {
            holdColor = ofColor::fromHsb( light3AmbientColorHue->getFloat() * 255,  light3AmbientColorSaturation->getFloat() * 255,  light3AmbientColorBrightness->getFloat() * 255,  255);
        };
        light3.setAmbientColor(holdColor);
    };
}

void  TXMeshDistort::setLight3SpecularColor() {
    if (light3UseDiffuseColorForSpecular) {
        light3.setSpecularColor(light3.getDiffuseColor());
    } else {
        ofColor holdColor =  TXFunctions::txGetColor(light3SpecularColorHue->getFloat(),  light3SpecularColorSaturation->getFloat(),  light3SpecularColorBrightness->getFloat(),  1, light3SpecularColorHueRotate->getFloat(), light3SpecularColorHSBAsRGB->getBool());
        if (light3SpecularColorHSBAsRGB->getBool()) {
            holdColor.set( light3SpecularColorHue->getFloat() * 255,  light3SpecularColorSaturation->getFloat() * 255,  light3SpecularColorBrightness->getFloat() * 255,  255);
        } else {
            holdColor = ofColor::fromHsb( light3SpecularColorHue->getFloat() * 255,  light3SpecularColorSaturation->getFloat() * 255,  light3SpecularColorBrightness->getFloat() * 255,  255);
        };
        light3.setSpecularColor(holdColor);
    };
}

void  TXMeshDistort::setLight3Position() {
    light3.setPosition(light3PositionX->getFloat(), light3PositionY->getFloat(), light3PositionZ->getFloat());
}

void  TXMeshDistort::setLight3Orientation() {
    light3.setOrientation(ofVec3f(light3OrientationX->getFloat(), light3OrientationY->getFloat(), light3OrientationZ->getFloat()));
}




