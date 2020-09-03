/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXSystem.h"
#include "TXRenderImage.h"

// constructor
TXRenderImage::TXRenderImage() {
    setup();
}

// destructor
TXRenderImage::~TXRenderImage() {
    // stop if recording
    stopVideoRecording();
    // remove listeners to relevent parameters:
    ofRemoveListener(recordVideo->parameters.parameterChangedE(),this,&TXRenderImage::recordVideoChanged);
    ofRemoveListener(recordImageSeq->parameters.parameterChangedE(),this,&TXRenderImage::recordImageSeqChanged);
    imageSeqRecorder.waitForThread();
}

void TXRenderImage::setup(){
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
    
    holdModParamBoolArgs.name = "renderContinuosly";
    holdModParamBoolArgs.fixedValue = false;
    renderContinuosly = createModParameter(holdModParamBoolArgs);
    parameters.add(renderContinuosly->parameters);
    
    holdModParamBoolArgs.name = "renderNow";
    holdModParamBoolArgs.fixedValue = false;
    renderNow = createModParameter(holdModParamBoolArgs);
    parameters.add(renderNow->parameters);
    
    renderWidthHeightRule.set("renderWidthHeightRule",0,0,11);
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
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    holdModParamFloatArgs.autoScaleModSumming = true;
    clearColorAlpha = createModParameter(holdModParamFloatArgs);
    parameters.add(clearColorAlpha->parameters);
    
    parameters.add(clearColorHSBAsRGB.set("clearColorHSBAsRGB", false));
    
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

    holdModParamBoolArgs.name = "recordVideo";
    holdModParamBoolArgs.fixedValue = false;
    recordVideo = createModParameter(holdModParamBoolArgs);
    parameters.add(recordVideo->parameters);
    
    holdModParamBoolArgs.name = "pauseRecordVideo";
    holdModParamBoolArgs.fixedValue = false;
    pauseRecordVideo = createModParameter(holdModParamBoolArgs);
    parameters.add(pauseRecordVideo->parameters);
    
    parameters.add(maxVideoRecordTimeMinutes.set("maxVideoRecordTimeMinutes", 0.0, 0.0, 600.0));
    parameters.add(recordVideoFolder.set("recordVideoFolder", "/Users/XXXUserName/Movies/TXV_Movies"));
    parameters.add(recordVideoFileNamePrefix.set("recordVideoFileNamePrefix", "TXV_Movie_"));
    parameters.add(recordVideoCodec.set("recordVideoCodec", TXVIDRECCODEC_MPEG4, 0, TXVIDRECCODEC_TOTAL-1));
//    parameters.add(recordVideoFileType.set("recordVideoFileType", TXVIDREC_FILEEXT_MOV, 0, TXVIDREC_FILEEXT_TOTAL-1));
    parameters.add(recordVideoBitrate.set("recordVideoBitrate", TXVIDEOBITRATE_2000K, 0, TXVIDEOBITRATE_TOTAL-1));
    parameters.add(recordVideoConstantRateFactor.set("recordVideoConstantRateFactor", 23, 0, 35));
    parameters.add(recordVideoH6245SpeedPreset.set("recordVideoH6245SpeedPreset", TXVIDREC_H2645SPEEDPRESET_MEDIUM, 0, TXVIDREC_H2645SPEEDPRESET_TOTAL-1));
    
/* AUDIO REMOVED FOR NOW
    parameters.add(recordAudioWithVideo.set("recordAudioWithVideo", false));
    parameters.add(recordAudioBitrate.set("recordAudioBitrate", TXAUDIOBITRATE_256K, 0, TXAUDIOBITRATE_TOTAL-1));
    parameters.add(recordAudioDeviceID.set("recordAudioDeviceID", 0, 0, 20));
*/
    
    holdModParamBoolArgs.name = "saveImageNow";
    holdModParamBoolArgs.fixedValue = false;
    saveImageNow = createModParameter(holdModParamBoolArgs);
    parameters.add(saveImageNow->parameters);
    
    parameters.add(saveImageFolder.set("saveImageFolder", "/Users/XXXUserName/Pictures/TXV_Images"));
    parameters.add(saveImageFileNamePrefix.set("saveImageFileNamePrefix", "TXV_Image_"));
    parameters.add(saveImageFormat.set("saveImageFormat", 1, 0, 2));

    holdModParamBoolArgs.name = "recordImageSeq";
    holdModParamBoolArgs.fixedValue = false;
    recordImageSeq = createModParameter(holdModParamBoolArgs);
    parameters.add(recordImageSeq->parameters);
    
    holdModParamBoolArgs.name = "pauseRecordImageSeq";
    holdModParamBoolArgs.fixedValue = false;
    pauseRecordImageSeq = createModParameter(holdModParamBoolArgs);
    parameters.add(pauseRecordImageSeq->parameters);
    
    parameters.add(maxImageSeqRecordTimeMinutes.set("maxImageSeqRecordTimeMinutes", 0.0, 0.0, 600.0));
    parameters.add(imageSeqFolder.set("imageSeqFolder", "/Users/XXXUserName/Movies/TXV_ImageSeqFolders/TXV_ImageSeqTEST01"));
    parameters.add(imageSeqFileNamePrefix.set("imageSeqFileNamePrefix", "TXV_ImageSeqTEST01_"));
    parameters.add(imageSeqFormat.set("imageSeqFormat", 0, 0, 2));

    // add listener to relevent parameters:
    renderWidthHeightRule.addListener(this, &TXRenderImage::renderSizeChanged);
    renderCustomWidth.addListener(this, &TXRenderImage::renderSizeChanged);
    renderCustomHeight.addListener(this, &TXRenderImage::renderSizeChanged);
    imageSeqFolder.addListener(this, &TXRenderImage::imageSeqSettingsChanged);
    imageSeqFileNamePrefix.addListener(this, &TXRenderImage::imageSeqSettingsChanged);
    imageSeqFormat.addListener(this, &TXRenderImage::imageSeqFormatChanged);

    // add listener to relevent mod parameters:
    ofAddListener(recordVideo->parameters.parameterChangedE(),this,&TXRenderImage::recordVideoChanged);
    ofAddListener(recordImageSeq->parameters.parameterChangedE(),this,&TXRenderImage::recordImageSeqChanged);

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
#else
	if(ofIsGLProgrammableRenderer()){
		drawShader.load("shadersGL3/AlphaTextureShader.vert", "shadersGL3/AlphaTextureShader.frag");
	}else{
		drawShader.load("shadersGL2/AlphaTextureShader.vert", "shadersGL2/AlphaTextureShader.frag");
	}
#endif

    // init
    oldRenderNow = false;
    oldClearNow = false;
    oldSaveImageNow = false;
    isRecordingVideo = false;

    // set up texture
    allocateTexture();
    registerTexture();

    setupVideoRecording();
    setupImageSequenceRecorder();
}

void TXRenderImage::update(){
    bool newRenderContinuosly = renderContinuosly->getBool();
    bool newRenderNow = renderNow->getBool();
    bool newClearBeforeRender = clearBeforeRender->getBool();
    bool newClearNow = clearNow->getBool();
    bool clearNowNewTrigger = (newClearNow && !oldClearNow);
    bool clearFirst = false;
    bool isVideoPaused = pauseRecordVideo->getBool();
    bool newSaveImageNow = saveImageNow->getBool();
    bool isImageSeqPaused = pauseRecordImageSeq->getBool();
    bool readToPixDone = false;
    
    // check whether to clear
    if (newClearBeforeRender || clearNowNewTrigger) {
        clearFirst = true;
    };
    // check whether to render
    if (newRenderContinuosly || (newRenderNow && !oldRenderNow) || clearNowNewTrigger) {
        renderTexture(clearFirst);
    };
    // reset vars
    oldClearNow = newClearNow;
    oldRenderNow = newRenderNow;
    
    // check whether to save/record
    if (outImage.isAllocated()) {
        
        // record video frame
        if (isRecordingVideo) {
            if(!isVideoPaused){
                outImage.readToPixels(recordPix);
                readToPixDone = true;
                // remove alpha component
                recordPix.setImageType(OF_IMAGE_COLOR);
                vidRecorder.addFrame(recordPix);
                numRecordedVideoFrames++;
            };
            // stop recording if reached maxVideoRecordTimeMinutes
            if (maxVideoRecordTimeMinutes > 0.0) {
                float vidRecTimeMins = numRecordedVideoFrames / (60.0 * parentSystem->targetFrameRate);
                if (vidRecTimeMins >= maxVideoRecordTimeMinutes) {
                    stopVideoRecording();
                };
            };
        }
        // save image
        if (newSaveImageNow && !oldSaveImageNow) {
            saveImage();
        };
        // reset var
        oldSaveImageNow = newSaveImageNow;
        
        // record image sequence frame
        if (imageSeqRecorderSetupRequired) {
            setupImageSequenceRecorder();
            imageSeqRecorderSetupRequired = false;
        };
        if (isRecordingImageSeq) {
            if(!isImageSeqPaused){
                if (!readToPixDone) {
                    outImage.readToPixels(recordPix);
                };
                imageSeqRecorder.addFrame(recordPix);
                numRecordedImageSeqFrames++;
            };
            // stop recording if reached maxImageSeqRecordTimeMinutes
            if (maxImageSeqRecordTimeMinutes > 0.0) {
                float imageSeqRecTimeMins = numRecordedImageSeqFrames / (60.0 * parentSystem->targetFrameRate);
                if (imageSeqRecTimeMins >= maxImageSeqRecordTimeMinutes) {
                    stopImageSeqRecording();
                };
            };
        };
    };
}

void TXRenderImage::draw(){
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
    
    float tex0X, tex0Y, tex1X, tex1Y, tex2X, tex2Y, tex3X, tex3Y;
#ifdef TARGET_OPENGLES
    // Use widthNextPow2Ratio, heightNextPow2Ratio to adjust texture coords
    float widthNextPow2Ratio = (float) holdImageWidth /ofNextPow2(holdImageWidth);
    float heightNextPow2Ratio = (float) holdImageHeight /ofNextPow2(holdImageHeight);
    tex0X = (fboEdgeOffsetX) * widthNextPow2Ratio;
    tex0Y = fboEdgeOffsetY * heightNextPow2Ratio;
    tex1X = (holdImageWidth - fboEdgeOffsetX) * widthNextPow2Ratio;
    tex1Y = fboEdgeOffsetY * heightNextPow2Ratio;
    tex2X = (holdImageWidth - fboEdgeOffsetX) * widthNextPow2Ratio;
    tex2Y = (holdImageHeight - fboEdgeOffsetY) * heightNextPow2Ratio;
    tex3X = (fboEdgeOffsetX) * widthNextPow2Ratio;
    tex3Y = (holdImageHeight - fboEdgeOffsetY) * heightNextPow2Ratio;
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
        drawShader.setUniform1f("u_alpha", alpha->getFloat());
        drawShader.setUniform1f("u_alphaThreshold", parentSystem->alphaThreshold);
        drawShader.setUniformTexture("u_texture0Sampler", outImage.getTexture(0), 0); 
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
    
    drawShader.end();
    ofPopMatrix();
}

void TXRenderImage::allocateTexture() {
    
#ifdef TARGET_OPENGLES
    outImage.allocate(getRenderWidth(), getRenderHeight(), GL_RGBA);
    //ofLogWarning("ofApp") << "TXRenderImage::allocateTexture() - GL_RGBA32F_ARB is not available for OPENGLES.  Using RGBA.";
#else
    outImage.allocate(getRenderWidth(), getRenderHeight(), GL_RGBA32F_ARB);    
    //ofLogNotice() << "TXRenderImage::allocateTexture() - GL_RGBA32F_ARB: ";
#endif

    clearTexture();
    pix.allocate(getRenderWidth(), getRenderHeight(), OF_IMAGE_COLOR_ALPHA);
}

void TXRenderImage::clearTexture() {
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

void TXRenderImage::renderTexture(bool clearFirstArg) {
    ofColor newColor;
    if (clearFirstArg) {
        clearTexture();
    };
    outImage.begin();
    
    // use base method to draw layers
    TXDrawLayersBase::draw((TXDRAWLAYERSRULE)drawLayersRule->getInt());
    
    ofClearAlpha();
    outImage.end();
}

void TXRenderImage::windowResized(int w, int h) {
    if (renderWidthHeightRule != MAXWIDTHHEIGHTRULE_CUSTOMSIZE) {
        allocateTexture();
    };
}

//////////////////////////////

int TXRenderImage::getTextureWidth() {
    return outImage.getWidth();
}

int TXRenderImage::getTextureHeight() {
    return outImage.getHeight();
}

ofTexture *  TXRenderImage::getTexture() {
    if (outImage.isAllocated()) {
        return & outImage.getTexture();
    } else {
        return NULL;
    }
}

ofPixelsRef TXRenderImage::getPixels() {
    outImage.readToPixels(pix);
    return pix;
}

//////////////////////////////

void TXRenderImage::setupVideoRecording() {
    vidRecorder.setFfmpegLocation(ofFilePath::getAbsolutePath("ffmpeg", true));
    /*AUDIO REMOVED FOR NOW
     vidRecorder.setAudioCodec("mp3");
     //soundStream.listDevices();
    */
}

void TXRenderImage::startVideoRecording() {
    if(!vidRecorder.isInitialized()) {
        string folder = recordVideoFolder;
        string nameString = recordVideoFileNamePrefix;
        string prefix = ofFilePath::getAbsolutePath (folder + "/" + nameString, false);
        string vidcodec;
        string extension = "mov";
        string videoBitRate;
        // string audioBitRate;  // AUDIO REMOVED FOR NOW
        string pixelFormat;
        string speedPreset;
        stringstream extraText;
        ofDirectory holdDir;

        // check for valid folder
        holdDir.open(ofFilePath::getAbsolutePath(folder, false ));
        if (holdDir.exists()) {
            // init
            isRecordingVideo = true;
            numRecordedVideoFrames = 0;
            
            switch (recordVideoBitrate) {
                case TXVIDEOBITRATE_400K:
                    videoBitRate = "400k";
                    break;
                case TXVIDEOBITRATE_800K:
                    videoBitRate = "800k";
                    break;
                case TXVIDEOBITRATE_1000K:
                    videoBitRate = "1000k";
                    break;
                case TXVIDEOBITRATE_1200K:
                    videoBitRate = "1200k";
                    break;
                case TXVIDEOBITRATE_1500K:
                    videoBitRate = "1500k";
                    break;
                case TXVIDEOBITRATE_2000K:
                    videoBitRate = "2000k";
                    break;
                case TXVIDEOBITRATE_3000K:
                    videoBitRate = "3000k";
                    break;
                case TXVIDEOBITRATE_4000K:
                    videoBitRate = "4000k";
                    break;
                case TXVIDEOBITRATE_5000K:
                    videoBitRate = "5000k";
                    break;
                case TXVIDEOBITRATE_6000K:
                    videoBitRate = "6000k";
                    break;
                case TXVIDEOBITRATE_7000K:
                    videoBitRate = "7000k";
                    break;
                case TXVIDEOBITRATE_8000K:
                    videoBitRate = "7000k";
                    break;
                case TXVIDEOBITRATE_10000K:
                    videoBitRate = "10000k";
                    break;
                case TXVIDEOBITRATE_12000K:
                    videoBitRate = "12000k";
                    break;
                case TXVIDEOBITRATE_14000K:
                    videoBitRate = "14000k";
                    break;
                case TXVIDEOBITRATE_16000K:
                    videoBitRate = "16000k";
                    break;
                case TXVIDEOBITRATE_18000K:
                    videoBitRate = "18000k";
                    break;
                case TXVIDEOBITRATE_20000K:
                    videoBitRate = "20000k";
                    break;
                case TXVIDEOBITRATE_25000K:
                    videoBitRate = "25000k";
                    break;
                case TXVIDEOBITRATE_30000K:
                    videoBitRate = "30000k";
                    break;
                case TXVIDEOBITRATE_35000K:
                    videoBitRate = "35000k";
                    break;
                case TXVIDEOBITRATE_40000K:
                    videoBitRate = "40000k";
                    break;
                case TXVIDEOBITRATE_45000K:
                    videoBitRate = "45000k";
                    break;
                case TXVIDEOBITRATE_50000K:
                    videoBitRate = "50000k";
                    break;
                case TXVIDEOBITRATE_55000K:
                    videoBitRate = "55000k";
                    break;
                case TXVIDEOBITRATE_60000K:
                    videoBitRate = "60000k";
                    break;
                case TXVIDEOBITRATE_70000K:
                    videoBitRate = "70000k";
                    break;
                case TXVIDEOBITRATE_80000K:
                    videoBitRate = "80000k";
                    break;
                case TXVIDEOBITRATE_90000K:
                    videoBitRate = "90000k";
                    break;
                case TXVIDEOBITRATE_100000K:
                    videoBitRate = "100000k";
                    break;
                default:
                    videoBitRate = "2000k";
                    break;
            }
            vidRecorder.setVideoBitrate(videoBitRate);
            
            switch (recordVideoH6245SpeedPreset) {
                case TXVIDREC_H2645SPEEDPRESET_VERYSLOW:
                    speedPreset = "veryslow";
                    break;
                case TXVIDREC_H2645SPEEDPRESET_SLOWER:
                    speedPreset = "slower";
                    break;
                case TXVIDREC_H2645SPEEDPRESET_SLOW:
                    speedPreset = "slow";
                    break;
                case TXVIDREC_H2645SPEEDPRESET_MEDIUM:
                    speedPreset = "medium";
                    break;
                case TXVIDREC_H2645SPEEDPRESET_FAST:
                    speedPreset = "fast";
                    break;
                case TXVIDREC_H2645SPEEDPRESET_FASTER:
                    speedPreset = "faster";
                    break;
                case TXVIDREC_H2645SPEEDPRESET_VERYFAST:
                    speedPreset = "veryfast";
                    break;
                default:
                    speedPreset = "medium";
                    break;
            }
            
            //        switch (recordVideoFileType) {
            //            case TXVIDREC_FILEEXT_MOV:
            //                extension = "mov";
            //                break;
            //            case TXVIDREC_FILEEXT_MP4:
            //                extension = "mp4";
            //                break;
            //            case TXVIDREC_FILEEXT_AVI:
            //                extension = "avi";
            //                break;
            //            default:
            //                extension = "mp4";
            //                break;
            //        }
            
            switch (recordVideoCodec) {
                case TXVIDRECCODEC_MPEG4:
                    vidcodec = "mpeg4";
                    extraText << " -b:v " << videoBitRate;
                    break;
                case TXVIDRECCODEC_H264:
                    //vidcodec = "libx264";
                    vidcodec = "libx264rgb";
                    extraText << " -b:v " << videoBitRate << " -preset " << speedPreset;
                    break;
                case TXVIDRECCODEC_H264_CRF:
                    //vidcodec = "libx264";
                    vidcodec = "libx264rgb";
                    extraText << " -crf " << recordVideoConstantRateFactor << " -preset " << speedPreset;
                    break;
                case TXVIDRECCODEC_H265:
                    vidcodec = "hevc";
                    extraText << " -b:v " << videoBitRate << " -preset " << speedPreset;
                    break;
                case TXVIDRECCODEC_H265_CRF:
                    vidcodec = "hevc";
                    extraText << " -crf " << recordVideoConstantRateFactor << " -preset " << speedPreset;
                    break;
                case TXVIDRECCODEC_PRORES_LT:
                    vidcodec = "prores_ks";
                    extraText << " -profile:v 1";
                    // extension = "mov"; // force mov extension
                    break;
                case TXVIDRECCODEC_PRORES_STANDARD:
                    vidcodec = "prores_ks";
                    extraText << " -profile:v 2";
                    // extension = "mov"; // force mov extension
                    break;
                case TXVIDRECCODEC_PRORES_HQ:
                    vidcodec = "prores_ks";
                    extraText << " -profile:v 3";
                    // extension = "mov"; // force mov extension
                    break;
                case TXVIDRECCODEC_PRORES_4444:
                    vidcodec = "prores_ks";
                    extraText << " -profile:v 4";
                    // extension = "mov"; // force mov extension
                    break;
                case TXVIDRECCODEC_PRORES_4444XQ:
                    vidcodec = "prores_ks";
                    extraText << " -profile:v 5";
                    // extension = "mov"; // force mov extension
                    break;
                case TXVIDRECCODEC_RAWVIDEO:
                    vidcodec = "rawvideo";
                    // extension = "mov"; // force mov extension
                    break;
                default:
                    vidcodec = "mpeg4";
                    extraText << " -b:v " << videoBitRate;
                    break;
            }
            vidRecorder.setVideoCodec(vidcodec);
            
            /* AUDIO REMOVED FOR NOW
             switch (recordAudioBitrate) {
             case TXAUDIOBITRATE_128K:
             audioBitRate = "128k";
             break;
             case TXAUDIOBITRATE_160K:
             audioBitRate = "160k";
             break;
             case TXAUDIOBITRATE_192K:
             audioBitRate = "192k";
             break;
             case TXAUDIOBITRATE_256K:
             audioBitRate = "256k";
             break;
             case TXAUDIOBITRATE_320K:
             audioBitRate = "320k";
             break;
             default:
             audioBitRate = "256k";
             break;
             }
             vidRecorder.setAudioBitrate(audioBitRate);
             soundStream.setDeviceID(recordAudioDeviceID);
             soundStream.setup(0, audioChannels, audioSampleRate, 256, 4);
             
             // OLD CODE
             if (recordAudioWithVideo) {
             // video and audio
             vidRecorder.setup(prefix + ofGetTimestampString() + "." + extension, outImage.getWidth(), outImage.getHeight(), parentSystem->targetFrameRate, audioSampleRate, audioChannels);
             } else {
             // video only
             vidRecorder.setup(prefix + ofGetTimestampString() + "." + extension, outImage.getWidth(), outImage.getHeight(), parentSystem->targetFrameRate);
             }
             */
            string format = "%Y%m%d_%H%M%S%i";
            string fileName = prefix + "_" + ofGetTimestampString(format) + "." + extension;
            string absFilePath = ofFilePath::getAbsolutePath(fileName);
            
            stringstream outputSettings;
            outputSettings
            << " -vcodec " << vidcodec << extraText.str()
            << " \"" << absFilePath << "\"";
            
            vidRecorder.setupCustomOutput(outImage.getWidth(), outImage.getHeight(), parentSystem->targetFrameRate, 0, 0, outputSettings.str());
            
            // Start recording
            vidRecorder.start();
        };
    };
}

void TXRenderImage::stopVideoRecording() {
    if (isRecordingVideo) {
        isRecordingVideo = false;
        vidRecorder.close();
    };
}

//////////

string TXRenderImage::getImageFormatString(int intArg) {
    string formatString;
    switch (intArg) {
        case 0:
            formatString = "jpg";
            break;
        case 1:
            formatString = "png";
            break;
        case 2:
            formatString = "bmp";
            break;
        default:
            formatString = "jpg";
            break;
    }
    return formatString;
}

void TXRenderImage::saveImage() {
    string folder = saveImageFolder;
    string nameString = saveImageFileNamePrefix;
    string prefix = ofFilePath::getAbsolutePath (folder + "/" +nameString, false);
    ofDirectory holdDir;
    
    // check for valid folder
    holdDir.open(ofFilePath::getAbsolutePath(folder, false ));
    if (holdDir.exists()) {
        ofSaveImage(getPixels(), prefix + "_" + ofGetTimestampString() + "." + getImageFormatString(saveImageFormat));
    }
}

//////////

void TXRenderImage::setupImageSequenceRecorder() {
    string folder = imageSeqFolder;
    string nameString = imageSeqFileNamePrefix;
    string prefix = ofFilePath::getAbsolutePath (folder + "/" +nameString, false);
    imageSeqRecorder.setPrefix(prefix);
    imageSeqRecorder.setFormat(getImageFormatString(imageSeqFormat));
}

void TXRenderImage::startImageSeqRecording() {
    isRecordingImageSeq = true;
    numRecordedImageSeqFrames = 0;
    ofDirectory holdDir;
    // check for valid folder
    holdDir.open(ofFilePath::getAbsolutePath(imageSeqFolder, false));
    if (holdDir.exists()) {
        if (!imageSeqRecorder.isThreadRunning()) {
            imageSeqRecorder.startThread(false);
        };
    };
    
}

void TXRenderImage::stopImageSeqRecording() {
    if (isRecordingImageSeq) {
        isRecordingImageSeq = false;
    };
}

//////////

void  TXRenderImage::recordVideoChanged(ofAbstractParameter & parameterArg ) {
     if (recordVideo->getBool()) {
         startVideoRecording();
     } else {
         stopVideoRecording();
     };
}

void  TXRenderImage::renderSizeChanged(int & intArg) {
    if ((getRenderWidth() != outImage.getWidth()) || (getRenderHeight() != outImage.getHeight())) {
        // if size changed, reallocate
        allocateTexture();
    };
}

void  TXRenderImage::imageSeqSettingsChanged(string & stringArg) {
    imageSeqRecorderSetupRequired = true;
}

void  TXRenderImage::imageSeqFormatChanged(int & intArg) {
    imageSeqRecorderSetupRequired = true;
}

void  TXRenderImage::recordImageSeqChanged(ofAbstractParameter & parameterArg ) {
    if (recordImageSeq->getBool()) {
        startImageSeqRecording();
    } else {
        stopImageSeqRecording();
    };
}

//////////

int TXRenderImage::getRenderWidth() {
    switch (renderWidthHeightRule) {
        case MAXWIDTHHEIGHTRULE_SCREENWIDTHHEIGHT:
            return getWindowWidth();
            break;
        case MAXWIDTHHEIGHTRULE_MAXSCREENWIDTHHEIGHT:
            return max(getWindowWidth(), getWindowHeight());
            break;
        case MAXWIDTHHEIGHTRULE_MINSCREENWIDTHHEIGHT:
            return min(getWindowWidth(), getWindowHeight());
            break;
        case MAXWIDTHHEIGHTRULE_SQUARESCREENWIDTH:
            return getWindowWidth();
            break;
        case MAXWIDTHHEIGHTRULE_SQUARESCREENHEIGHT:
            return getWindowHeight();
            break;
        case MAXWIDTHHEIGHTRULE_CUSTOMSIZE:
            return renderCustomWidth;
            break;
        case MAXWIDTHHEIGHTRULE_480_360:
            return 480;
            break;
        case MAXWIDTHHEIGHTRULE_858_480:
            return 858;
            break;
        case MAXWIDTHHEIGHTRULE_1280_720:
            return 1280;
            break;
        case MAXWIDTHHEIGHTRULE_1920_1080:
            return 1920;
            break;
        case MAXWIDTHHEIGHTRULE_2560_1440:
            return 2560;
            break;
        case MAXWIDTHHEIGHTRULE_3840_2160:
            return 3840;
            break;
        default:
            return getWindowWidth();
            break;
    }
}

int TXRenderImage::getRenderHeight() {
    switch (renderWidthHeightRule) {
        case MAXWIDTHHEIGHTRULE_SCREENWIDTHHEIGHT:
            return getWindowHeight();
            break;
        case MAXWIDTHHEIGHTRULE_MAXSCREENWIDTHHEIGHT:
            return max(getWindowWidth(), getWindowHeight());
            break;
        case MAXWIDTHHEIGHTRULE_MINSCREENWIDTHHEIGHT:
            return min(getWindowWidth(), getWindowHeight());
            break;
        case MAXWIDTHHEIGHTRULE_SQUARESCREENWIDTH:
            return getWindowWidth();
            break;
        case MAXWIDTHHEIGHTRULE_SQUARESCREENHEIGHT:
            return getWindowHeight();
            break;
        case MAXWIDTHHEIGHTRULE_CUSTOMSIZE:
            return renderCustomHeight;
            break;
        case MAXWIDTHHEIGHTRULE_480_360:
            return 360;
            break;
        case MAXWIDTHHEIGHTRULE_858_480:
            return 480;
            break;
        case MAXWIDTHHEIGHTRULE_1280_720:
            return 720;
            break;
        case MAXWIDTHHEIGHTRULE_1920_1080:
            return 1080;
            break;
        case MAXWIDTHHEIGHTRULE_2560_1440:
            return 1440;
            break;
        case MAXWIDTHHEIGHTRULE_3840_2160:
            return 2160;
            break;
        default:
            return getWindowHeight();
            break;
    }
}

