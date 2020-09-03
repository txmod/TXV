/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXSystem.h"
#include "TXFunctions.h"
#include "TXEnvMap.h"

// constructor
TXEnvMap::TXEnvMap() {
    setup();
}

// destructor
TXEnvMap::~TXEnvMap() {
}

void TXEnvMap::setup(){
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
    
    parameters.add(useExternalEnvMapImage.set("useExternalEnvMapImage", false));

    holdModParamBoolArgs.name = "mirrorImageRight";
    holdModParamBoolArgs.fixedValue = false;
    mirrorImageRight = createModParameter(holdModParamBoolArgs);
    parameters.add(mirrorImageRight->parameters);
    
    holdModParamFloatArgs.name = "environmentRotation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    environmentRotation = createModParameter(holdModParamFloatArgs);
    parameters.add(environmentRotation->parameters);
    
    holdModParamFloatArgs.name = "blurTopBottom";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    blurTopBottom = createModParameter(holdModParamFloatArgs);
    parameters.add(blurTopBottom->parameters);
    
    holdModParamIntArgs.name = "drawLayersRule";
    holdModParamIntArgs.fixedValue = TXDRAWLAYERSRULE_ALLEXCEPT20;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXDRAWLAYERSRULE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXDRAWLAYERSRULE_TOTAL - 1;
	drawLayersRule = createModParameter(holdModParamIntArgs);
    parameters.add(drawLayersRule->parameters);
    
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
    
    holdModParamFloatArgs.name = "clearColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    clearColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(clearColorHueRotate->parameters);
    
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
    holdModParamBoolArgs.fixedModMix = false;
    clearColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(clearColorHSBAsRGB->parameters);
    
    holdModParamFloatArgs.name = "lightEffectMix";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    lightEffectMix = createModParameter(holdModParamFloatArgs);
    parameters.add(lightEffectMix->parameters);
    
    holdModParamFloatArgs.name = "lightPosX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
    lightPosX = createModParameter(holdModParamFloatArgs);
    parameters.add(lightPosX->parameters);
    
    holdModParamFloatArgs.name = "lightPosY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
    lightPosY = createModParameter(holdModParamFloatArgs);
    parameters.add(lightPosY->parameters);
    
    holdModParamFloatArgs.name = "lightPosZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 0.0;
    lightPosZ = createModParameter(holdModParamFloatArgs);
    parameters.add(lightPosZ->parameters);
    
    holdModParamFloatArgs.name = "baseColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    baseColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(baseColorHue->parameters);
    
    holdModParamFloatArgs.name = "baseColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    baseColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(baseColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "baseColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    baseColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(baseColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "baseColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.4;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    baseColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(baseColorBrightness->parameters);
    
    holdModParamBoolArgs.name = "baseColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
    baseColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(baseColorHSBAsRGB->parameters);
    
    holdModParamFloatArgs.name = "baseEnvColorMix";
    holdModParamFloatArgs.fixedValue = 0.75;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    baseEnvColorMix = createModParameter(holdModParamFloatArgs);
    parameters.add(baseEnvColorMix->parameters);
    
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
    
    // asset slots
    createImageAssetSlot("envMapImageAsset");
    
    // external image slots
    createExtImageModuleSlot("extEnvMapImageModule");
    
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

    string vString = "_ShaderGroups/FXShaders1Tex/envMap.vert";
    string fString = "_ShaderGroups/FXShaders1Tex/envMap.frag";
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

    oldRenderNow = false;
    oldClearNow = false;

    // set up texture
    allocateTexture();
    registerTexture();
}

void TXEnvMap::update(){
    // slow down image change
    if (envMapImageHasChanged) {
        loadEnvMapImage();
        envMapImageHasChanged = false;
    };

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
}

void TXEnvMap::draw(){
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
    //    ofLogNotice() << "testing xxx  TXEnvMap::draw -  widthNextPow2Ratio, heightNextPow2Ratio, outImage.getWidth(), outImage.getHeight()";
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
    drawShader.setUniform1f("u_alpha", drawAlpha->getFloat());
    drawShader.setUniform1f("u_alphaThreshold", parentSystem->alphaThreshold);
    drawShader.setUniformTexture("u_texture0Sampler", outImage.getTexture(0), 0);
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

void TXEnvMap::allocateTexture() {
    outImage.allocate(getMaxWidth(), getMaxHeight());
    outImage.begin();
    ofClear(0,255);
    outImage.end();
    pix.allocate(getMaxWidth(), getMaxHeight(), OF_IMAGE_COLOR_ALPHA);
}

void TXEnvMap::renderTexture(bool clearFirstArg) {
    int holdID;
    float envMapImageWidth;
    float envMapImageHeight;
    if (!useExternalEnvMapImage) {
        if (!envMapImage.getTexture().isAllocated()) {
            return;
        };
    };
    if (useExternalEnvMapImage) {
        holdID = getExtImageModuleIDSlot("extEnvMapImageModule");
        if (!parentSystem->isValidModuleID(holdID)) {
            return;
        };
        if (parentSystem->allModules[holdID]->getTexture() == NULL) {
            return;
        };
        envMapImageWidth = parentSystem->allModules[holdID]->getTextureWidth();
        envMapImageHeight = parentSystem->allModules[holdID]->getTextureHeight();
    } else {
        envMapImageWidth = envMapImage.getWidth();
        envMapImageHeight = envMapImage.getHeight();
    };

    ofEnableDepthTest();
    
    outImage.begin();
    if (clearFirstArg) {
        ofColor newColor =  TXFunctions::txGetColor(clearColorHue->getFloat(),  clearColorSaturation->getFloat(),  clearColorBrightness->getFloat(),  clearColorAlpha->getFloat(), clearColorHueRotate->getFloat(), clearColorHSBAsRGB->getBool());
        ofEnableAlphaBlending();
        ofClear(newColor);
        ofDisableAlphaBlending();
    };
    renderShader.begin();
    
    ofColor baseColor =  TXFunctions::txGetColor(baseColorHue->getFloat(),  baseColorSaturation->getFloat(),  baseColorBrightness->getFloat(),  1.0, baseColorHueRotate->getFloat(), baseColorHSBAsRGB->getBool());
    
    renderShader.setUniform3f("BaseColor", baseColor.r/255.0, baseColor.g/255.0, baseColor.b/255.0);
    renderShader.setUniform1f("BaseEnvMixRatio", baseEnvColorMix->getFloat());
    renderShader.setUniform1f("LightMixRatio", lightEffectMix->getFloat());
    renderShader.setUniform3f("LightPos", lightPosX->getFloat() * getMaxWidth(), lightPosY->getFloat() * getMaxHeight(), lightPosZ->getFloat() * getMaxDepth());
    if (useExternalEnvMapImage) {
        ofTexture * sourceTex = parentSystem->allModules[holdID]->getTexture();
        renderShader.setUniformTexture("EnvMap", * sourceTex, 0);
    } else {
        renderShader.setUniformTexture("EnvMap", envMapImage.getTexture(), 0);
    };
    renderShader.setUniform2f("ImageSize", envMapImageWidth, envMapImageHeight);
    renderShader.setUniform1f("ImageWidthRecip", 1.0f  / envMapImageWidth);
    renderShader.setUniform1i("Mirror", mirrorImageRight->getBool());
    renderShader.setUniform1f("Rotation", 1.0 + (environmentRotation->getFloat() / 360));
    renderShader.setUniform1f("BlurTopBottom", blurTopBottom->getFloat());
 
    // use base to draw layers
    TXDrawLayersBase::draw((TXDRAWLAYERSRULE)drawLayersRule->getInt());
    
    ofDisableDepthTest();
    renderShader.end();
    ofClearAlpha();
    outImage.end();
}

void TXEnvMap::windowResized(int w, int h) {
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

////////

void  TXEnvMap::imageAssetSlotChanged(string slotNameArg) {
    envMapImageHasChanged = true;
}

void TXEnvMap::loadEnvMapImage() {
    ofPtr <TXAsset> asset;
    string fileName;
    int envMapImageAssetID = getImageAssetIDSlot("envMapImageAsset").first;
    if (envMapImageAssetID != 0) {
        asset = parentSystem->getAsset(TXASSETTYPE_IMAGE, envMapImageAssetID);
        fileName = asset->getFileName();
        // old:
        //        if (envMapImage.load(fileName)) {
        //            envMapImageHasLoaded = true;
        //        };
        parentSystem->imageLoader.loadFromDisk(envMapImage, fileName);
    };
}

///////

int TXEnvMap::getTextureWidth() {
    return outImage.getWidth();
}

int TXEnvMap::getTextureHeight() {
    return outImage.getHeight();
}

ofTexture *  TXEnvMap::getTexture() {
    return & outImage.getTexture();
}

ofPixelsRef TXEnvMap::getPixels() {
    outImage.readToPixels(pix);
    return pix;
}

