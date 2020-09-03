/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXFeedback.h"
#include "TXFunctions.h"

// constructor
TXFeedback::TXFeedback() {
    setup();
}

// destructor
TXFeedback::~TXFeedback() {
}

void TXFeedback::setup(){
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
    holdModParamBoolArgs.fixedValue = true;
    renderContinuosly = createModParameter(holdModParamBoolArgs);
    parameters.add(renderContinuosly->parameters);
    
    holdModParamBoolArgs.name = "renderNow";
    holdModParamBoolArgs.fixedValue = false;
    renderNow = createModParameter(holdModParamBoolArgs);
    parameters.add(renderNow->parameters);

    holdModParamBoolArgs.name = "freezeFeedback";
    holdModParamBoolArgs.fixedValue = false;
    freezeFeedback = createModParameter(holdModParamBoolArgs);
    parameters.add(freezeFeedback->parameters);
    
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
    
    parameters.add(alphaThreshold.set("alphaThreshold", 0.03, 0.0, 0.05));
        
    holdModParamFloatArgs.name = "feedbackAlpha";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	feedbackAlpha = createModParameter(holdModParamFloatArgs);
    parameters.add(feedbackAlpha->parameters);
    
    holdModParamFloatArgs.name = "feedbackBrightness";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	feedbackBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(feedbackBrightness->parameters);
    
    holdModParamFloatArgs.name = "feedbackShiftX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -100.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = -100.0;
    holdModParamFloatArgs.softMax = 100.0;
	feedbackShiftX = createModParameter(holdModParamFloatArgs);
    parameters.add(feedbackShiftX->parameters);
    
    holdModParamBoolArgs.name = "quantiseFeedbackShiftX";
    holdModParamBoolArgs.fixedValue = false;
    quantiseFeedbackShiftX = createModParameter(holdModParamBoolArgs);
    parameters.add(quantiseFeedbackShiftX->parameters);
    
    holdModParamFloatArgs.name = "feedbackShiftY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -100.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = -100.0;
    holdModParamFloatArgs.softMax = 100.0;
	feedbackShiftY = createModParameter(holdModParamFloatArgs);
    parameters.add(feedbackShiftY->parameters);
    
    holdModParamBoolArgs.name = "quantiseFeedbackShiftY";
    holdModParamBoolArgs.fixedValue = false;
    quantiseFeedbackShiftY = createModParameter(holdModParamBoolArgs);
    parameters.add(quantiseFeedbackShiftY->parameters);
    
    holdModParamFloatArgs.name = "feedbackAnchorX";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	feedbackAnchorX = createModParameter(holdModParamFloatArgs);
    parameters.add(feedbackAnchorX->parameters);
    
    holdModParamBoolArgs.name = "quantiseFeedbackAnchorX";
    holdModParamBoolArgs.fixedValue = false;
    quantiseFeedbackAnchorX = createModParameter(holdModParamBoolArgs);
    parameters.add(quantiseFeedbackAnchorX->parameters);
    
    holdModParamFloatArgs.name = "feedbackAnchorY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	feedbackAnchorY = createModParameter(holdModParamFloatArgs);
    parameters.add(feedbackAnchorY->parameters);
    
    holdModParamBoolArgs.name = "quantiseFeedbackAnchorY";
    holdModParamBoolArgs.fixedValue = false;
    quantiseFeedbackAnchorY = createModParameter(holdModParamBoolArgs);
    parameters.add(quantiseFeedbackAnchorY->parameters);
    
    holdModParamFloatArgs.name = "feedbackRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	feedbackRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(feedbackRotate->parameters);
    
    holdModParamFloatArgs.name = "feedbackRotateMultiply";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
	feedbackRotateMultiply = createModParameter(holdModParamFloatArgs);
    parameters.add(feedbackRotateMultiply->parameters);
    
    holdModParamFloatArgs.name = "feedbackScaleX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 3.0;
	feedbackScaleX = createModParameter(holdModParamFloatArgs);
    parameters.add(feedbackScaleX->parameters);
    
    holdModParamFloatArgs.name = "feedbackScaleY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 3.0;
	feedbackScaleY = createModParameter(holdModParamFloatArgs);
    parameters.add(feedbackScaleY->parameters);

    parameters.add(useFeedbackScaleXForScaleY.set("useFeedbackScaleXForScaleY", false));

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
    feedbackShader.load("shadersES2/AlphaBrightnessShader.vert","shadersES2/AlphaBrightnessShader.frag");
#else
	if(ofIsGLProgrammableRenderer()){
		drawShader.load("shadersGL3/AlphaTextureShader.vert", "shadersGL3/AlphaTextureShader.frag");
        feedbackShader.load("shadersGL3/AlphaBrightnessShader.vert","shadersGL3/AlphaBrightnessShader.frag");
	}else{
		drawShader.load("shadersGL2/AlphaTextureShader.vert", "shadersGL2/AlphaTextureShader.frag");
        feedbackShader.load("shadersGL2/AlphaBrightnessShader.vert","shadersGL2/AlphaBrightnessShader.frag");
	}
#endif

    oldRenderNow = false;
    oldClearNow = false;

    // set up texture
    allocateTextures();
    registerTexture();
}

void TXFeedback::update(){
    bool newRenderContinuosly = renderContinuosly->getBool();
    bool newRenderNow = renderNow->getBool();
    bool newClearNow = clearNow->getBool();
    bool clearNowNewTrigger = (newClearNow && (newClearNow != oldClearNow));
    // check whether to render
    if (newRenderContinuosly
        || (newRenderNow && (newRenderNow != oldRenderNow))
        || clearNowNewTrigger)
    {
        renderTexture(clearNowNewTrigger);
    };
    // reset vars
    oldClearNow = newClearNow;
    oldRenderNow = newRenderNow;
}

void TXFeedback::draw(){
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
    float holdImageWidth = outputImage->getWidth();
    float holdImageHeight = outputImage->getHeight();
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
    drawXAdjusted = holdDrawPosX * holdMaxWidth;
    drawYAdjusted = holdDrawPosY * holdMaxHeight;
    
    //  use shader
    drawShader.begin();

    ofPushMatrix();

    // translate, rotate, scale
    ofTranslate(drawXAdjusted, drawYAdjusted, 0.0);
    ofRotateZ(rotateMultiply->getFloat() * rotate->getFloat());
    ofScale(holdScaleX, holdScaleY, 1.0);
    
    //    // testing xxx
    //    ofLogNotice() << "testing xxx  TXRenderImage::draw -  widthNextPow2Ratio, heightNextPow2Ratio, outputImage->getWidth(), outputImage->getHeight()";
    //    ofLogNotice() << widthNextPow2Ratio <<  ", " << heightNextPow2Ratio <<  ", " << outputImage->getWidth() <<  ", " << outputImage->getHeight();
    
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
    // save time if already set before
    if (setUniforms) {
        drawShader.setUniform1f("u_alpha", drawAlpha->getFloat());
        drawShader.setUniform1f("u_alphaThreshold", alphaThreshold);
        drawShader.setUniformTexture("u_texture0Sampler", outputImage->getTexture(0), 0);
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

void TXFeedback::renderTexture(bool clearFirstArg) {
    float holdFeedbackAnchorX, holdFeedbackAnchorY;

    // swap images
    feedbackImage = &(fbos[(fboFlag)%2]);
    outputImage = &(fbos[++(fboFlag)%2]);

    
    // reset AnchorPoint
    if (!quantiseFeedbackAnchorX->getBool()) {
        holdFeedbackAnchorX = TXFunctions::quantise(feedbackAnchorX->getFloat() * feedbackImage->getWidth());
    } else {
        holdFeedbackAnchorX = feedbackAnchorX->getFloat() * feedbackImage->getWidth();
    };
    if (!quantiseFeedbackAnchorY->getBool()) {
        holdFeedbackAnchorY = TXFunctions::quantise(feedbackAnchorY->getFloat() * feedbackImage->getHeight());
    } else {
        holdFeedbackAnchorY = feedbackAnchorY->getFloat() * feedbackImage->getHeight();
    };

    //  clear images
    ofColor newColor;
    if (clearColorHSBAsRGB) {
        newColor.set (clearColorHue->getFloat() * 255, clearColorSaturation->getFloat() * 255, clearColorBrightness->getFloat() * 255, clearColorAlpha->getFloat() * 255);
    } else {
        newColor = ofColor::fromHsb(clearColorHue->getFloat() * 255, clearColorSaturation->getFloat() * 255, clearColorBrightness->getFloat() * 255, clearColorAlpha->getFloat() * 255);
    };
    outputImage->begin();
    ofClear(newColor);
    outputImage->end();
    if (clearFirstArg) {
        feedbackImage->begin();
        ofClear(newColor);
        feedbackImage->end();
    } else {
        
        // draw to outputImage FBO
        outputImage->begin();
        
        // use shader
        feedbackShader.begin();
        float holdFbAlpha = feedbackAlpha->getFloat();
        feedbackShader.setUniform1f("u_alpha", pow(holdFbAlpha, 0.5f) );
        feedbackShader.setUniform1f("u_brightness", feedbackBrightness->getFloat() );

        // push matrix
        ofPushMatrix();
                
        // translate & rotate & scale
        float holdFeedbackScaleX, holdFeedbackScaleY;
        float holdFeedbackShiftX, holdFeedbackShiftY;
        float holdFeedbackRotate, holdFeedbackRotateMultiply;
        
        ofTranslate(holdFeedbackAnchorX, holdFeedbackAnchorY, 0.0);
        if (!freezeFeedback->getBool()) {
            holdFeedbackScaleX = feedbackScaleX->getFloat();
            if (useFeedbackScaleXForScaleY) {
                holdFeedbackScaleY = holdFeedbackScaleX;
            } else {
                holdFeedbackScaleY = feedbackScaleY->getFloat();
            };
            holdFeedbackShiftX = feedbackShiftX->getFloat();
            holdFeedbackShiftY = feedbackShiftY->getFloat();
            holdFeedbackRotate = feedbackRotate->getFloat();
            holdFeedbackRotateMultiply = feedbackRotateMultiply->getFloat();

//// testing xxx
//            ofLogNotice() << "TXFeedback::renderTexture() - holdFeedbackAnchorX, holdFeedbackAnchorY: " << holdFeedbackAnchorX << ", " << holdFeedbackAnchorY;
//            ofLogNotice() << "TXFeedback::renderTexture() - holdFeedbackShiftX, holdFeedbackShiftY: " << holdFeedbackShiftX << ", " << holdFeedbackShiftY;
//            ofLogNotice() << "TXFeedback::renderTexture() - holdFeedbackRotate, holdFeedbackRotateMultiply: " << holdFeedbackRotate << ", " << holdFeedbackRotateMultiply;
            
            ofTranslate(holdFeedbackShiftX, holdFeedbackShiftY, 0.0);
            ofRotateZ(holdFeedbackRotate * holdFeedbackRotateMultiply);
            ofScale(holdFeedbackScaleX, holdFeedbackScaleY, 1.0);
        };
        
        ofTranslate(-holdFeedbackAnchorX, -holdFeedbackAnchorY, 0.0);

        ofEnableAlphaBlending();

        // draw feedbackImage
        feedbackImage->draw(0, 0);
        
        ofPopMatrix();
        
        feedbackShader.end();
        
        // use base to draw layers
        TXDrawLayersBase::draw((TXDRAWLAYERSRULE)drawLayersRule->getInt());

        ofClearAlpha();
        
        ofDisableAlphaBlending();

        outputImage->end();
    };
}

void TXFeedback::allocateTextures() {
	// FBO settings
	ofFbo::Settings tmpFBOSettings = ofFbo::Settings();
	tmpFBOSettings.width  =  getMaxWidth();
	tmpFBOSettings.height =  getMaxHeight();
	tmpFBOSettings.useDepth = false;
	tmpFBOSettings.useStencil = false;
	tmpFBOSettings.internalformat = GL_RGBA;
    
    fbos[0].allocate(tmpFBOSettings);
    fbos[1].allocate(tmpFBOSettings);
    
    fbos[0].begin();
    ofClear(0,255);
    fbos[0].end();
    
    fbos[1].begin();
    ofClear(0,255);
    fbos[1].end();
    
    feedbackImage = &fbos[0];
    outputImage = &fbos[1];
    fboFlag = 0;
}

void TXFeedback::windowResized(int w, int h) {
    if (maxWidthHeightRule != MAXWIDTHHEIGHTRULE_CUSTOMSIZE) {
        allocateTextures();
        ofColor newColor;
        if (clearColorHSBAsRGB) {
            newColor.set (clearColorHue->getFloat() * 255, clearColorSaturation->getFloat() * 255, clearColorBrightness->getFloat() * 255, clearColorAlpha->getFloat() * 255);
        } else {
            newColor = ofColor::fromHsb(clearColorHue->getFloat() * 255, clearColorSaturation->getFloat() * 255, clearColorBrightness->getFloat() * 255, clearColorAlpha->getFloat() * 255);
        };
        fbos[0].begin();
        ofEnableAlphaBlending();
        ofClear(newColor);
        ofDisableAlphaBlending();
        fbos[0].end();
        fbos[1].begin();
        ofEnableAlphaBlending();
        ofClear(newColor);
        ofDisableAlphaBlending();
        fbos[1].end();
    };
}

int TXFeedback::getTextureWidth() {
    return outputImage->getWidth();
}

int TXFeedback::getTextureHeight() {
    return outputImage->getHeight();
}

ofTexture *  TXFeedback::getTexture() {
    return & outputImage->getTexture();
}
