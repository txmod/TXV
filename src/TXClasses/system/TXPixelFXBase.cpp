/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXPixelFXBase.h"
#include "TXSystem.h"
#include "TXAsset.h"

// constructor
TXPixelFXBase::TXPixelFXBase() {
    setup();
}

// destructor
TXPixelFXBase::~TXPixelFXBase() {
    
    // remove listeners to relevent parameters:
    useExternalSourceImage.removeListener(this, &TXPixelFXBase::useExternalSourceImageChanged);
}

void TXPixelFXBase::addExtraParameters() {
//    TXModParameterBoolArgs holdModParamBoolArgs;
//    TXModParameterIntArgs holdModParamIntArgs;
//    TXModParameterFloatArgs holdModParamFloatArgs;
    
    //    EXAMPLE CODE:
    //    holdModParamFloatArgs.name = "phase";
    //    holdModParamFloatArgs.fixedValue = 0.0;
    //    holdModParamFloatArgs.fixedModMix = 0.0;
    //    holdModParamFloatArgs.hardMin = 0.0;
    //    holdModParamFloatArgs.hardMax = 1.0;
    //    holdModParamFloatArgs.softMin = 0.0;
    //    holdModParamFloatArgs.softMax = 1.0;
    //    phase = createModParameter(holdModParamFloatArgs);
    //    parameters.add(phase->parameters);
}

void TXPixelFXBase::addExtraListeners() {
    
    //    EXAMPLE CODE:
    // add listener to relevent extra mod parameters:
//    ofAddListener(showEdgeColor->parameters.parameterChangedE(),this,&TXFindEdges::showEdgeColorChanged);
}

//    EXAMPLE CODE:
//void  TXPixelFXBase::showEdgeColorChanged(ofAbstractParameter & parameterArg ) {
//    DO SOMETHING HERE
//}

void TXPixelFXBase::extraSetupAction() {
    
    //    DO SOMETHING HERE
    
}

void TXPixelFXBase::updatePixels() {
    
    //  DO SOMETHING TO PIXELS
    
}

//--------------------------------

void TXPixelFXBase::setup(){
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();

    parameters.add(useExternalSourceImage.set("useExternalSourceImage", false));

    holdModParamBoolArgs.name = "renderContinuosly";
    holdModParamBoolArgs.fixedValue = true;
    renderContinuosly = createModParameter(holdModParamBoolArgs);
    parameters.add(renderContinuosly->parameters);
    
    holdModParamBoolArgs.name = "renderNow";
    holdModParamBoolArgs.fixedValue = false;
    renderNow = createModParameter(holdModParamBoolArgs);
    parameters.add(renderNow->parameters);
    
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
    useExternalSourceImage.addListener(this, &TXPixelFXBase::useExternalSourceImageChanged);
    
    // add listeners
    addExtraListeners();
    
    // asset slot
    createImageAssetSlot("sourceImageAsset");
    
    // external image slots
    createExtImageModuleSlot("extSourceImageModule");
    
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
    
    oldRenderNow = false;
    outImageIsAllocated = false;

    registerTexture();
    extraSetupAction();
}

void TXPixelFXBase::update(){
    bool newRenderContinuosly = renderContinuosly->getBool();
    bool newRenderNow = renderNow->getBool();
    // slow down image change
    if (sourceImageHasChanged) {
        outImageIsAllocated = false;
        loadSourceImage();
        sourceImageHasChanged = false;
    };
    if (!outImageIsAllocated) {
        outImageSetup();
    };
    // check whether to render
    if (newRenderContinuosly || (newRenderNow && (newRenderNow != oldRenderNow))) {
        bool validImage = true;
        int holdWidth = 0, holdHeight = 0;
        // check if valid input image before updating
        if (useExternalSourceImage) {
            int holdSourceID = getExtImageModuleIDSlot("extSourceImageModule");
            if (!parentSystem->isValidModuleID(holdSourceID)) {
                return;
            };
            if (holdSourceID == 0) {
                validImage = false;
            } else {
                if (parentSystem->allModules[holdSourceID]->getTexture() == NULL) {
                    validImage = false;
                } else {
                    holdWidth = parentSystem->allModules[holdSourceID]->getTextureWidth();
                    holdHeight = parentSystem->allModules[holdSourceID]->getTextureHeight();
                };
            };
            // reallocate outImage if size changed
            if ((holdWidth != outImage.getWidth()) || (holdHeight != outImage.getHeight())) {
                outImageSetup();
            };
        } else {
            if (!sourceImage.isAllocated()) {
                validImage = false;
            };
        };
        if (validImage) {
            updatePixels();
        };
    };
    // reset var
    oldRenderNow = newRenderNow;
}

void TXPixelFXBase::draw(){
    if (!outImageIsAllocated) {
        return;
    };
    bool setUniforms = true;
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
    if (setUniforms) {
        drawShader.setUniform1f("u_alpha", drawAlpha->getFloat());
        drawShader.setUniform1f("u_alphaThreshold", parentSystem->alphaThreshold);
        
//        // testing xxx
//        ofLogNotice() << "TXPixelFXBase::draw() - BEFORE outImage.getTexture(): ";
//        ofTexture testTex = outImage.getTexture();
//        ofLogNotice() << "TXPixelFXBase::draw() - AFTER 1 outImage.getTexture(): ";
//        
//
        drawShader.setUniformTexture("u_texture0Sampler", outImage.getTexture(), 0);

//        ofLogNotice() << "TXPixelFXBase::draw() - AFTER 2 outImage.getTexture(): ";
        
    };
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

void  TXPixelFXBase::imageAssetSlotChanged(string slotNameArg) {
    if (slotNameArg == "sourceImageAsset") {
        sourceImageHasChanged = true;
        outImageIsAllocated = false;
    };
}

void  TXPixelFXBase::useExternalSourceImageChanged(bool & boolArg) {
    outImageSetup();
    outImageIsAllocated = false;
}

bool TXPixelFXBase::loadSourceImage() {
    ofPtr <TXAsset> asset;
    string fileName;
    int sourceImageAssetID = getImageAssetIDSlot("sourceImageAsset").first;
    if (sourceImageAssetID != 0) {
        asset = parentSystem->getAsset(TXASSETTYPE_IMAGE, sourceImageAssetID);
        fileName = asset->getFileName();
        
        // old:
        sourceImage.load(fileName);
        
        // testing xxx - restored old and removed loader for now
        //parentSystem->imageLoader.loadFromDisk(sourceImage, fileName);
        return true;
    };
    return false;
}

void TXPixelFXBase::outImageSetup() {
    int holdWidth;
    int holdHeight;
    if (useExternalSourceImage) {
        int holdSourceID = getExtImageModuleIDSlot("extSourceImageModule");
        if (holdSourceID == 0) {
            return;
        };
        holdWidth = parentSystem->allModules[holdSourceID]->getTextureWidth();
        holdHeight = parentSystem->allModules[holdSourceID]->getTextureHeight();
        // check for valid texture
        if ((holdWidth == 0) || (holdHeight == 0)) {
            return;
        };
    } else {
        if (!sourceImage.isAllocated()) {
            return;
        };
        holdWidth = sourceImage.getWidth();
        holdHeight = sourceImage.getHeight();
    };
    outImage.allocate(holdWidth, holdHeight, OF_IMAGE_COLOR_ALPHA);
    outImageIsAllocated = true;
}

int TXPixelFXBase::getTextureWidth() {
    return outImage.getWidth();
}

int TXPixelFXBase::getTextureHeight() {
    return outImage.getHeight();
}

ofTexture *  TXPixelFXBase::getTexture() {
    return & outImage.getTexture();
}

ofPixelsRef TXPixelFXBase::getPixels() {
    return outImage.getPixels() ;
}

