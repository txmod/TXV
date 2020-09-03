/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXWallpaper.h"
#include "TXSystem.h"
#include "TXAsset.h"

// constructor
TXWallpaper::TXWallpaper() {
    setup();
}

// destructor
TXWallpaper::~TXWallpaper() {
    // remove listeners to relevent mod parameters:
    ofRemoveListener(wallpaperGroup->parameters.parameterChangedE(),this,&TXWallpaper::wallpaperGroupChanged);
    ofRemoveListener(sourceZoomX->parameters.parameterChangedE(),this,&TXWallpaper::sourceZoomChanged);
    ofRemoveListener(sourceZoomY->parameters.parameterChangedE(),this,&TXWallpaper::sourceZoomChanged);
    ofRemoveListener(sourceShiftX->parameters.parameterChangedE(),this,&TXWallpaper::sourceShiftXChanged);
    ofRemoveListener(sourceShiftY->parameters.parameterChangedE(),this,&TXWallpaper::sourceShiftYChanged);
    ofRemoveListener(sourceRotate->parameters.parameterChangedE(),this,&TXWallpaper::sourceRotateChanged);
    ofRemoveListener(tileSize->parameters.parameterChangedE(),this,&TXWallpaper::tileSizeChanged);
    ofRemoveListener(tileAngle->parameters.parameterChangedE(),this,&TXWallpaper::tileAngleChanged);
}

void TXWallpaper::setup(){
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
    
    renderWidthHeightRule.set("renderWidthHeightRule",0,0,6);
    parameters.add(renderWidthHeightRule);
    
    renderCustomWidth.set("renderCustomWidth",1024,1,4096);
    parameters.add(renderCustomWidth);
    
    renderCustomHeight.set("renderCustomHeight",768,1,4096);
    parameters.add(renderCustomHeight);
    
    holdModParamIntArgs.name = "wallpaperGroup";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = numWallpaperGroups - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = numWallpaperGroups - 1;
	wallpaperGroup = createModParameter(holdModParamIntArgs);
    parameters.add(wallpaperGroup->parameters);
    
    holdModParamFloatArgs.name = "sourceZoomX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.001;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 1.0;
    holdModParamFloatArgs.softMax = 3.0;
    sourceZoomX = createModParameter(holdModParamFloatArgs);
    parameters.add(sourceZoomX->parameters);
    
    holdModParamFloatArgs.name = "sourceZoomY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.001;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 1.0;
    holdModParamFloatArgs.softMax = 3.0;
    sourceZoomY = createModParameter(holdModParamFloatArgs);
    parameters.add(sourceZoomY->parameters);
    
    parameters.add(useSourceZoomXForZoomY.set("useSourceZoomXForZoomY", false));
    
    holdModParamFloatArgs.name = "sourceShiftX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -1.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
    sourceShiftX = createModParameter(holdModParamFloatArgs);
    parameters.add(sourceShiftX->parameters);
    
    holdModParamFloatArgs.name = "sourceShiftY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -1.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
    sourceShiftY = createModParameter(holdModParamFloatArgs);
    parameters.add(sourceShiftY->parameters);
    
    holdModParamFloatArgs.name = "sourceRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
    sourceRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(sourceRotate->parameters);
    
    holdModParamFloatArgs.name = "tileSize";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.001;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.001;
    holdModParamFloatArgs.softMax = 1.0;
    tileSize = createModParameter(holdModParamFloatArgs);
    parameters.add(tileSize->parameters);
    
    holdModParamFloatArgs.name = "tileAngle";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
    tileAngle = createModParameter(holdModParamFloatArgs);
    parameters.add(tileAngle->parameters);
    
    parameters.add(alphaThreshold.set("alphaThreshold", 0.03, 0.0, 0.05));
    
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
    
    // add listener to relevent mod parameters:
    ofAddListener(wallpaperGroup->parameters.parameterChangedE(),this,&TXWallpaper::wallpaperGroupChanged);
    ofAddListener(sourceZoomX->parameters.parameterChangedE(),this,&TXWallpaper::sourceZoomChanged);
    ofAddListener(sourceZoomY->parameters.parameterChangedE(),this,&TXWallpaper::sourceZoomChanged);
    ofAddListener(sourceShiftX->parameters.parameterChangedE(),this,&TXWallpaper::sourceShiftXChanged);
    ofAddListener(sourceShiftY->parameters.parameterChangedE(),this,&TXWallpaper::sourceShiftYChanged);
    ofAddListener(sourceRotate->parameters.parameterChangedE(),this,&TXWallpaper::sourceRotateChanged);
    ofAddListener(tileSize->parameters.parameterChangedE(),this,&TXWallpaper::tileSizeChanged);
    ofAddListener(tileAngle->parameters.parameterChangedE(),this,&TXWallpaper::tileAngleChanged);

    // add listener to relevent parameters:
    renderWidthHeightRule.addListener(this, &TXWallpaper::renderSizeChanged);
    renderCustomWidth.addListener(this, &TXWallpaper::renderSizeChanged);
    renderCustomHeight.addListener(this, &TXWallpaper::renderSizeChanged);
    useExternalSourceImage.addListener(this, &TXWallpaper::useExternalSourceImageChanged);
    useSourceZoomXForZoomY.addListener(this, &TXWallpaper::useSourceZoomXForZoomYChanged);
    
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
    
    // load shader
#ifdef TARGET_OPENGLES
	drawShader.load("shadersES2/AlphaTextureShader.vert","shadersES2/AlphaTextureShader.frag");
    ofTextureData texDat = fbo1.getTexture().getTextureData();

#else
	if(ofIsGLProgrammableRenderer()){
		drawShader.load("shadersGL3/AlphaTextureShader.vert", "shadersGL3/AlphaTextureShader.frag");
	}else{
		drawShader.load("shadersGL2/AlphaTextureShader.vert", "shadersGL2/AlphaTextureShader.frag");
	}
#endif

    oldRenderNow = false;
    sourceImageHasLoaded = false;
    sourceImageHasChanged = false;
    windowHasResized = true;
    tileSizeHasChanged = true;

    allocateTexture();
    registerTexture();
}

////////////////

void TXWallpaper::update(){
    bool newRenderContinuosly = renderContinuosly->getBool();
    bool newRenderNow = renderNow->getBool();
    int outSize, scaleAdjust;
    
    if (windowHasResized) {
        allocateTexture();
        tileSizeHasChanged = true;
    };
    if (windowHasResized || sourceImageHasChanged) {
        updateSourceImage();
    };
    sourceImageHasChanged = false;
    windowHasResized = false;
    if (tileSizeHasChanged) {
        int holdWallpaperGroup = wallpaperGroup->getInt();
        if (holdWallpaperGroup == 3 || (holdWallpaperGroup == 5) || (holdWallpaperGroup == 6)) {
            scaleAdjust = 1;
        } else {
            scaleAdjust = 2;
        };
        outSize = (int) (0.5 + (tileSize->getFloat() * scaleAdjust * getTextureWidth())); //round to int
        ornament.setTileSize(outSize);
        tileSizeHasChanged = false;
    };
    // check whether to render
    if (newRenderContinuosly || (newRenderNow && (newRenderNow != oldRenderNow))) {
        renderTexture();
    };
    // reset var
    oldRenderNow = newRenderNow;
}

////////////////

void TXWallpaper::draw(){
    if (!ornament.getTexture().isAllocated()) {
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
    float holdImageWidth = ornament.getTexture().getWidth();
    float holdImageHeight = ornament.getTexture().getHeight();
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
    //    ofLogNotice() << "testing xxx  TXWallpaper::draw -  widthNextPow2Ratio, heightNextPow2Ratio, ornament.getTexture().getWidth(), ornament.getTexture().getHeight()";
    //    ofLogNotice() << widthNextPow2Ratio <<  ", " << heightNextPow2Ratio <<  ", " << ornament.getTexture().getWidth() <<  ", " << ornament.getTexture().getHeight();
    
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
        drawShader.setUniform1f("u_alphaThreshold", alphaThreshold);
        drawShader.setUniformTexture("u_texture0Sampler", ornament.getTexture(), 0);
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

////////////////

void  TXWallpaper::imageAssetSlotChanged(string slotNameArg) {
    if (slotNameArg == "sourceImageAsset") {
        loadSourceImage();
    };
}

bool TXWallpaper::loadSourceImage() {
    ofPtr <TXAsset> asset;
    string fileName;
    int sourceImageAssetID = getImageAssetIDSlot("sourceImageAsset").first;
    sourceImageHasLoaded = false;
    if (sourceImageAssetID != 0) {
        asset = parentSystem->getAsset(TXASSETTYPE_IMAGE, sourceImageAssetID);
        fileName = asset->getFileName();
        if (sourceImage.load(fileName)) {
            sourceImageHasLoaded = true;
            sourceImageHasChanged = true;
        };
    };
    return sourceImageHasLoaded;
}

bool TXWallpaper::getSourceImageHasLoaded() {
    return sourceImageHasLoaded;
}

void TXWallpaper::allocateTexture() {
    int holdWidth, holdHeight;
    holdWidth = getRenderWidth();
    holdHeight = getRenderHeight();

    if ((holdWidth != 0) && (holdHeight != 0)) {
        WALLPAPER_GROUP group;
        int outSize;
        float angle;
        group = (WALLPAPER_GROUP) (wallpaperGroup->getInt() + 9);
        outSize = (int) (0.5 + (tileSize->getFloat() * holdWidth)); //round to int
        angle = ofDegToRad(tileAngle->getFloat());
        ornament.setup(holdWidth, holdHeight,  group, outSize, angle);
    };
}

void TXWallpaper::renderTexture() {
    int holdExtSourceID;
    ofPtr<TXModuleBase> extSourceModule;
    float sourceImageWidth;
    float sourceImageHeight;
    
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
    if ((renderWidthHeightRule == IMAGEFXWIDTHHEIGHTRULE_SOURCEIMAGESIZE)
        && ((sourceImageWidth != ornament.getTexture().getWidth()) || (sourceImageHeight != ornament.getTexture().getHeight()))) {
        allocateTexture();
    };
    // create wallpaper
    if (ornament.getTexture().isAllocated()) {
        //ofEnableAlphaBlending();
        ornament.update();
        //ofDisableAlphaBlending();
    };
}

////////////////

int TXWallpaper::getTextureWidth() {
    return ornament.getTexture().getWidth();
}

int TXWallpaper::getTextureHeight() {
    return ornament.getTexture().getHeight();
}

ofTexture *  TXWallpaper::getTexture() {
    if (ornament.getTexture().isAllocated()) {
        return & ornament.getTexture();
    };
    return NULL;
}

////////////////

void  TXWallpaper::renderSizeChanged(int & intArg) {
    if ((getRenderWidth() != ornament.getTexture().getWidth()) || (getRenderHeight() != ornament.getTexture().getHeight())) {
        // if size changed, reallocate
        allocateTexture();
    };
}

int TXWallpaper::getRenderWidth() {
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
        default:
            return getWindowWidth();
            break;
    }
}

int TXWallpaper::getRenderHeight() {
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
        default:
            return getWindowHeight();
            break;
    }
}

void TXWallpaper::windowResized(int w, int h) {
     windowHasResized = true;
}

////////////////

void  TXWallpaper::wallpaperGroupChanged(ofAbstractParameter & parameterArg ) {
    int group = wallpaperGroup->getInt() + 9;  // offset required by Ornament
    ornament.setWallpaperGroup(group);
    tileSizeHasChanged = true;
}

void  TXWallpaper::sourceZoomChanged(ofAbstractParameter & parameterArg ) {
    updateSourceZoom();
}

void  TXWallpaper::sourceShiftXChanged(ofAbstractParameter & parameterArg ) {
    ornament.setInputShiftX(sourceShiftX->getFloat());
}

void  TXWallpaper::sourceShiftYChanged(ofAbstractParameter & parameterArg ) {
    ornament.setInputShiftY(sourceShiftY->getFloat());
}

void  TXWallpaper::sourceRotateChanged(ofAbstractParameter & parameterArg ) {
    float angle;
    //angle = ofDegToRad(sourceRotate->getFloat());
    angle = sourceRotate->getFloat();
    ornament.setInputRotate(angle);
}


void  TXWallpaper::tileSizeChanged(ofAbstractParameter & parameterArg ) {
    tileSizeHasChanged = true;
}

void  TXWallpaper::tileAngleChanged(ofAbstractParameter & parameterArg ) {
    float angle;
    angle = ofDegToRad(tileAngle->getFloat());
    ornament.setAngle(angle);
}

void  TXWallpaper::useSourceZoomXForZoomYChanged(bool & boolArg) {
    updateSourceZoom();
}

void  TXWallpaper::useExternalSourceImageChanged(bool & boolArg) {
    sourceImageHasChanged = true;
}

void  TXWallpaper::updateSourceZoom() {
    float holdX, holdY;
    holdX = sourceZoomX->getFloat();
    if (useSourceZoomXForZoomY) {
        holdY = holdX;
    } else {
        holdY = sourceZoomY->getFloat();
    };
    ornament.setInputZoomX(holdX);
    ornament.setInputZoomY(holdY);
}

void  TXWallpaper::updateSourceImage() {
    int holdExtSourceID;
    ofPtr<TXModuleBase> extSourceModule;
    if (!sourceImage.getTexture().isAllocated()) {
        allocateTexture();
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
        ornament.loadTexture(*extSourceModule->getTexture());
    } else {
        ornament.loadTexture(sourceImage.getTexture());
    };
}



