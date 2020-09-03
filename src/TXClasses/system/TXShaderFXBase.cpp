/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXShaderFXBase.h"
#include "TXSystem.h"
#include "TXAsset.h"

// constructor
TXShaderFXBase::TXShaderFXBase() {
    setup();
}

// destructor
TXShaderFXBase::~TXShaderFXBase() {
}

void TXShaderFXBase::addExtraImageParameters() {

    // Empty for this module
    
    //    EXAMPLE CODE:
    //    parameters.add(useExternalBlendImage.set("useExternalBlendImage", false));
}

void TXShaderFXBase::addExtraParameters() {
    //    TXModParameterBoolArgs holdModParamBoolArgs;
    //    TXModParameterIntArgs holdModParamIntArgs;
    //    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // Empty for this module
    
    //    EXAMPLE CODE:
    //    holdModParamFloatArgs.name = "clearColorHue";
    //    holdModParamFloatArgs.fixedValue = 0.5;
    //    holdModParamFloatArgs.fixedModMix = 0.0;
    //    holdModParamFloatArgs.hardMin = 0.0;
    //    holdModParamFloatArgs.hardMax = 1.0;
    //    holdModParamFloatArgs.softMin = 0.0;
    //    holdModParamFloatArgs.softMax = 1.0;
    //    holdModParamFloatArgs.autoScaleModSumming = true;
    //    clearColorHue = createModParameter(holdModParamFloatArgs);
    //    parameters.add(clearColorHue->parameters);
}

void TXShaderFXBase::addExtraListeners() {
    
    // Empty for this module
    
    //    EXAMPLE CODE:
    // add listener to relevent extra mod parameters:
//    ofAddListener(showEdgeColor->parameters.parameterChangedE(),this,&TXFindEdges::showEdgeColorChanged);
}

void TXShaderFXBase::loadRenderShader() {

    // Empty for this module

    //    EXAMPLE CODE:
    //    string vString = "passPosTex0.vert";
    //    string fString = "Wobble_GLSL.frag";
    //#ifdef TARGET_OPENGLES
    //	renderShader.load("shadersES2/_ShaderGroups/FXShaders1Tex/" + vString,"shadersES2/_ShaderGroups/FXShaders1Tex/" + fString);
    //#else
    //	if(ofIsGLProgrammableRenderer()){
    //        renderShader.load("shadersGL3/_ShaderGroups/FXShaders1Tex/" + vString,"shadersGL3/_ShaderGroups/FXShaders1Tex/" + fString);
    //	}else{
    //        renderShader.load("shadersGL2/_ShaderGroups/FXShaders1Tex/" + vString,"shadersGL2/_ShaderGroups/FXShaders1Tex/" + fString);
    //	}
    //#endif
}

void TXShaderFXBase::extraSetupAction() {

    // Empty for this module
    
    //    OVERRIDE IF REQUIRED
    
}

void TXShaderFXBase::extraUpdateAction() {
    
    // Empty for this module
    
    //    OVERRIDE IF REQUIRED
    
}

bool TXShaderFXBase::setExtraUniforms(int sourceImageWidth, int sourceImageHeight) {

    // Empty for this module

    //    EXAMPLE CODE:
    //    renderShader.setUniform1f("phase", phase->getFloat());
    
    return true;
}

//    EXAMPLE CODE:
//void  TXShaderFXBase::showEdgeColorChanged(ofAbstractParameter & parameterArg ) {
//    loadRenderShader();
//}

//--------------------------------

void TXShaderFXBase::setup(){
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();

    // asset slot
    createImageAssetSlot("sourceImageAsset");
    
    // external image slots
    createExtImageModuleSlot("extSourceImageModule");
    
    parameters.add(useExternalSourceImage.set("useExternalSourceImage", false));
    
    holdModParamIntArgs.name = "sourceImageScaleMode";
    holdModParamIntArgs.fixedValue = TXIMAGESCALEMODE_SCALETOFIT;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 2;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 2;
	sourceImageScaleMode = createModParameter(holdModParamIntArgs);
    parameters.add(sourceImageScaleMode->parameters);
    
    // allow extra image parameters in subclasses
    addExtraImageParameters();

    holdModParamBoolArgs.name = "renderContinuosly";
    holdModParamBoolArgs.fixedValue = true;
    renderContinuosly = createModParameter(holdModParamBoolArgs);
    parameters.add(renderContinuosly->parameters);
    
    holdModParamBoolArgs.name = "renderNow";
    holdModParamBoolArgs.fixedValue = false;
    renderNow = createModParameter(holdModParamBoolArgs);
    parameters.add(renderNow->parameters);
    
    renderWidthHeightRule.set("renderWidthHeightRule",0,0,12);
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
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    holdModParamFloatArgs.autoScaleModSumming = true;
    clearColorAlpha = createModParameter(holdModParamFloatArgs);
    parameters.add(clearColorAlpha->parameters);
    
    parameters.add(clearColorHSBAsRGB.set("clearColorHSBAsRGB", false));
    
    addExtraParameters();
    
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
    
    // add listener to relevent parameters:
    renderWidthHeightRule.addListener(this, &TXShaderFXBase::renderSizeChanged);
    renderCustomWidth.addListener(this, &TXShaderFXBase::renderSizeChanged);
    renderCustomHeight.addListener(this, &TXShaderFXBase::renderSizeChanged);
    
    // add extra listeners
    addExtraListeners();
    
    // set up drawMesh
    drawMesh.clear();
    drawMesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    // top left
    drawMesh.addTexCoord(ofVec2f(0, 0));
    drawMesh.addVertex(ofVec3f(0, 0, 0));
    drawMesh.addColor(ofFloatColor(1, 1, 1, 1));
    drawMesh.addNormal(ofVec3f(0, 0, 0));
    // top right
    drawMesh.addTexCoord(ofVec2f(1, 0));
    drawMesh.addVertex(ofVec3f(0, 0, 0));
    drawMesh.addColor(ofFloatColor(1, 1, 1, 1));
    drawMesh.addNormal(ofVec3f(0, 0, 0));
    // bottom right
    drawMesh.addTexCoord(ofVec2f(1, 1));
    drawMesh.addVertex(ofVec3f(0, 1, 0));
    drawMesh.addColor(ofFloatColor(1, 1, 1, 1));
    drawMesh.addNormal(ofVec3f(0, 0, 0));
    // bottom left
    drawMesh.addTexCoord(ofVec2f(0, 1));
    drawMesh.addVertex(ofVec3f(0, 1, 0));
    drawMesh.addColor(ofFloatColor(1, 1, 1, 1));
    drawMesh.addNormal(ofVec3f(0, 0, 0));
    
    // load shaders
    loadDrawShader();
    loadRenderShader();

    sourceImageHasChanged = false;
    oldRenderNow = false;
    outImageIsAllocated = false;

    allocateTexture();
    registerTexture();
    extraSetupAction();
}

void TXShaderFXBase::update(){
    bool newRenderContinuosly = renderContinuosly->getBool();
    bool newRenderNow = renderNow->getBool();
    bool newClearBeforeRender = clearBeforeRender->getBool();
    bool newClearNow = clearNow->getBool();
    bool clearNowNewTrigger = (newClearNow && !oldClearNow);
    bool clearFirst = false;
    if (sourceImageHasChanged) {
        loadSourceImage();
        sourceImageHasChanged = false;
    };
    // run extra update actions if needed
    extraUpdateAction();
    // check whether to clear
    if (newClearBeforeRender || clearNowNewTrigger) {
        clearTexture();
    };
    // check whether to render
    if (newRenderContinuosly || (newRenderNow && oldRenderNow)) {
        renderTexture(clearFirst);
    };
    // reset vars
    oldClearNow = newClearNow;
    oldRenderNow = newRenderNow;
}

void TXShaderFXBase::draw(){
    if (!outImageIsAllocated) {
        return;
    };
    
    // TODO: setUniforms always true for now
//    bool setUniforms = true; 
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
//    drawWidthPixels = (int) (fmax(drawWidth->getFloat() * holdMaxWidth, 1));
//    drawHeightPixels = (int) (fmax(drawHeight->getFloat() * holdMaxHeight, 1));
    drawWidthPixels = (fmax(drawWidth->getFloat() * holdMaxWidth, 1));
    drawHeightPixels =  (fmax(drawHeight->getFloat() * holdMaxHeight, 1));
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
//    if (setUniforms) {
        drawShader.setUniformTexture("u_texture0Sampler", outImage.getTexture(0), 0);
        drawShader.setUniform1f("u_alpha", drawAlpha->getFloat());
        drawShader.setUniform1f("u_alphaThreshold", parentSystem->alphaThreshold);
//    };
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

// listener methods

void  TXShaderFXBase::imageAssetSlotChanged(string slotNameArg) {
    if (slotNameArg == "sourceImageAsset") {
        sourceImageHasChanged = true;
    };
}

void TXShaderFXBase::loadDrawShader(){
    string vString = "AlphaTextureShader.vert";
    string fString = "AlphaTextureShader.frag";
#ifdef TARGET_OPENGLES
	drawShader.load("shadersES2/" + vString,"shadersES2/" + fString);
#else
	if(ofIsGLProgrammableRenderer()){
        drawShader.load("shadersGL3/" + vString,"shadersGL3/" + fString);
	}else{
        drawShader.load("shadersGL2/" + vString,"shadersGL2/" + fString);
	}
#endif
}

void TXShaderFXBase::loadSourceImage() {
    ofPtr <TXAsset> asset;
    string fileName;
    int sourceImageAssetID = getImageAssetIDSlot("sourceImageAsset").first;
    if (sourceImageAssetID != 0) {
        asset = parentSystem->getAsset(TXASSETTYPE_IMAGE, sourceImageAssetID);
        fileName = asset->getFileName();
        parentSystem->imageLoader.loadFromDisk(sourceImage, fileName);
    };
}

void TXShaderFXBase::allocateTexture() {
    int holdWidth, holdHeight;
    holdWidth = getRenderWidth();
    holdHeight = getRenderHeight();
    if ((holdWidth != 0) && (holdHeight != 0)) {
        
#ifdef TARGET_OPENGLES
        outImage.allocate(holdWidth, holdHeight, GL_RGBA);
        //ofLogWarning("ofApp") << "TXShaderFXBase::allocateTexture() - GL_RGBA32F_ARB is not available for OPENGLES.  Using RGBA.";
#else
        outImage.allocate(holdWidth, holdHeight, GL_RGBA32F_ARB);
        //ofLogNotice() << "TXShaderFXBase::allocateTexture() - GL_RGBA32F_ARB: ";
#endif
        
        outImageIsAllocated = true;
        clearTexture();
    };
}

void TXShaderFXBase::clearTexture() {
    outImage.begin();
    ofColor newColor;
    if (clearColorHSBAsRGB) {
        newColor.set (clearColorHue->getFloat() * 255, clearColorSaturation->getFloat() * 255, clearColorBrightness->getFloat() * 255, clearColorAlpha->getFloat() * 255);
    } else {
        newColor = ofColor::fromHsb(clearColorHue->getFloat() * 255, clearColorSaturation->getFloat() * 255, clearColorBrightness->getFloat() * 255, clearColorAlpha->getFloat() * 255);
    };
    ofEnableAlphaBlending();
    ofClear(newColor);
    ofDisableAlphaBlending();
    outImage.end();
}

void TXShaderFXBase::renderTexture(bool clearFirstArg) {
    int holdExtSourceID;
    ofPtr<TXModuleBase> extSourceModule;

    if (clearFirstArg) {
        clearTexture();
    };
    if (useExternalSourceImage) {
        holdExtSourceID = getExtImageModuleIDSlot("extSourceImageModule");
        if (!parentSystem->isValidModuleID(holdExtSourceID)) {
            return;
        };
        extSourceModule = parentSystem->allModules[holdExtSourceID];
        if (extSourceModule->getTexture() == NULL) {
            return;
        };
        sourceImageWidth = extSourceModule->getTextureWidth();
        sourceImageHeight = extSourceModule->getTextureHeight();
    } else {
        if (!sourceImage.getTexture().isAllocated()) {
            return;
        };
        sourceImageWidth = sourceImage.getWidth();
        sourceImageHeight = sourceImage.getHeight();
    };
    // if size changed, reallocate
    if ((renderWidthHeightRule == IMAGEFXWIDTHHEIGHTRULE_SOURCEIMAGESIZE) &&((sourceImageWidth != outImage.getWidth()) || (sourceImageHeight != outImage.getHeight()))) {
            allocateTexture();
    };
    int outImageWidth = outImage.getWidth();
    int outImageHeight = outImage.getHeight();
    
    float sourceImageRatioW, sourceImageRatioH;
    float sourceImageScaleX, sourceImageScaleY;
    float sourceImageOffsetX, sourceImageOffsetY;
    float scaledWidth, scaledHeight;
    
    switch (sourceImageScaleMode->getInt()) {
        case TXIMAGESCALEMODE_SCALETOFIT:
            sourceImageRatioW = (float) outImageWidth / sourceImageWidth;
            sourceImageRatioH = (float) outImageHeight / sourceImageHeight;
            sourceImageScaleX = min(sourceImageRatioW, sourceImageRatioH);
            sourceImageScaleY = sourceImageScaleX;
            scaledWidth = sourceImageWidth * sourceImageScaleX;
            scaledHeight = sourceImageHeight * sourceImageScaleY;
            sourceImageOffsetX = (outImageWidth - scaledWidth) * 0.5;
            sourceImageOffsetY = (outImageHeight - scaledHeight) * 0.5;
            break;
        case TXIMAGESCALEMODE_SCALETOFILL:
            sourceImageRatioW = (float) outImageWidth / sourceImageWidth;
            sourceImageRatioH = (float) outImageHeight / sourceImageHeight;
            sourceImageScaleX = max(sourceImageRatioW, sourceImageRatioH);
            sourceImageScaleY = sourceImageScaleX;
            scaledWidth = sourceImageWidth * sourceImageScaleX;
            scaledHeight = sourceImageHeight * sourceImageScaleY;
            sourceImageOffsetX = (outImageWidth - scaledWidth ) * 0.5;
            sourceImageOffsetY = (outImageHeight - scaledHeight) * 0.5;
            break;
        case TXIMAGESCALEMODE_STRETCHTOFILL:
            scaledWidth = outImageWidth;
            scaledHeight = outImageHeight;
            sourceImageScaleX = (float) outImageWidth / sourceImageWidth;
            sourceImageScaleY = (float) outImageHeight / sourceImageHeight;
            sourceImageOffsetX = 0;
            sourceImageOffsetY = 0;
            break;
        default:
            scaledWidth = outImageWidth;
            scaledHeight = outImageHeight;
            sourceImageScaleX = (float) outImageWidth / sourceImageWidth;
            sourceImageScaleY = (float) outImageHeight / sourceImageHeight;
            sourceImageOffsetX = 0;
            sourceImageOffsetY = 0;
            break;
    };
    
    // open image
    outImage.begin();
    ofEnableAlphaBlending();
    renderShader.begin();
    // check if method is successful
    if (setExtraUniforms(sourceImageWidth, sourceImageHeight)) {
        // draw image
        ofPushMatrix();
        ofTranslate(sourceImageOffsetX, sourceImageOffsetY, 0.0);
        ofScale(sourceImageScaleX, sourceImageScaleY, 1.0);

        if (useExternalSourceImage) {
            renderShader.setUniformTexture("u_texture0Sampler", *extSourceModule->getTexture(), 0);
            extSourceModule->getTexture()->draw(0, 0);
            
        } else {
            renderShader.setUniformTexture("u_texture0Sampler", sourceImage.getTexture(), 0);
            sourceImage.getTexture().draw(0, 0);
        };
        ofPopMatrix();
    };
    renderShader.end();
    ofDisableAlphaBlending();
    ofClearAlpha();
    outImage.end();
}

int TXShaderFXBase::getTextureWidth() {
    return outImage.getWidth();
}

int TXShaderFXBase::getTextureHeight() {
    return outImage.getHeight();
}

ofTexture *  TXShaderFXBase::getTexture() {
    return & outImage.getTexture();
}

ofPixelsRef TXShaderFXBase::getPixels() {
    outImage.readToPixels(pix);
    return pix;
}

void  TXShaderFXBase::renderSizeChanged(int & intArg) {
    if ((getRenderWidth() != outImage.getWidth()) || (getRenderHeight() != outImage.getHeight())) {
        // if size changed, reallocate
        allocateTexture();
    };
}

int TXShaderFXBase::getRenderWidth() {
    switch (renderWidthHeightRule) {
        case IMAGEFXWIDTHHEIGHTRULE_SCREENWIDTHHEIGHT:
            return getWindowWidth();
            break;
        case IMAGEFXWIDTHHEIGHTRULE_MAXSCREENWIDTHHEIGHT:
            return max(getWindowWidth(), getWindowHeight());
            break;
        case IMAGEFXWIDTHHEIGHTRULE_MINSCREENWIDTHHEIGHT:
            return min(getWindowWidth(), getWindowHeight());
            break;
        case IMAGEFXWIDTHHEIGHTRULE_SQUARESCREENWIDTH:
            return getWindowWidth();
            break;
        case IMAGEFXWIDTHHEIGHTRULE_SQUARESCREENHEIGHT:
            return getWindowHeight();
            break;
        case IMAGEFXWIDTHHEIGHTRULE_CUSTOMSIZE:
            return renderCustomWidth;
            break;
        case IMAGEFXWIDTHHEIGHTRULE_SOURCEIMAGESIZE:
            return sourceImageWidth;
            break;
        case IMAGEFXWIDTHHEIGHTRULE_640_480:
            return 640;
            break;
        case IMAGEFXWIDTHHEIGHTRULE_640_360:
            return 640;
            break;
        case IMAGEFXWIDTHHEIGHTRULE_1280_720:
            return 1280;
            break;
        case IMAGEFXWIDTHHEIGHTRULE_1920_1080:
            return 1920;
            break;
        case IMAGEFXWIDTHHEIGHTRULE_2560_1440:
            return 2560;
            break;
        case IMAGEFXWIDTHHEIGHTRULE_3840_2160:
            return 3840;
            break;
        default:
            return getWindowWidth();
            break;
    }
}

int TXShaderFXBase::getRenderHeight() {
    switch (renderWidthHeightRule) {
        case IMAGEFXWIDTHHEIGHTRULE_SCREENWIDTHHEIGHT:
            return getWindowHeight();
            break;
        case IMAGEFXWIDTHHEIGHTRULE_MAXSCREENWIDTHHEIGHT:
            return max(getWindowWidth(), getWindowHeight());
            break;
        case IMAGEFXWIDTHHEIGHTRULE_MINSCREENWIDTHHEIGHT:
            return min(getWindowWidth(), getWindowHeight());
            break;
        case IMAGEFXWIDTHHEIGHTRULE_SQUARESCREENWIDTH:
            return getWindowWidth();
            break;
        case IMAGEFXWIDTHHEIGHTRULE_SQUARESCREENHEIGHT:
            return getWindowHeight();
            break;
        case IMAGEFXWIDTHHEIGHTRULE_CUSTOMSIZE:
            return renderCustomHeight;
            break;
        case IMAGEFXWIDTHHEIGHTRULE_SOURCEIMAGESIZE:
            return sourceImageHeight;
            break;
        case IMAGEFXWIDTHHEIGHTRULE_640_480:
            return 480;
            break;
        case IMAGEFXWIDTHHEIGHTRULE_640_360:
            return 360;
            break;
        case IMAGEFXWIDTHHEIGHTRULE_1280_720:
            return 720;
            break;
        case IMAGEFXWIDTHHEIGHTRULE_1920_1080:
            return 1080;
            break;
        case IMAGEFXWIDTHHEIGHTRULE_2560_1440:
            return 1440;
            break;
        case IMAGEFXWIDTHHEIGHTRULE_3840_2160:
            return 2160;
            break;
        default:
            return getWindowHeight();
            break;
    }
}

void TXShaderFXBase::windowResized(int w, int h) {
    if ((renderWidthHeightRule != IMAGEFXWIDTHHEIGHTRULE_CUSTOMSIZE) && (renderWidthHeightRule != IMAGEFXWIDTHHEIGHTRULE_SOURCEIMAGESIZE))
    {
        allocateTexture();
    };
}



