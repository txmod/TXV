/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXDrawVideoCam.h"
#include "TXSystem.h"
#include "TXAsset.h"

// constructor
TXDrawVideoCam::TXDrawVideoCam() {
    setup();
}

// destructor
TXDrawVideoCam::~TXDrawVideoCam() {
}

void TXDrawVideoCam::setup(){
//    TXModParameterBoolArgs holdModParamBoolArgs;
//    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
    
    parameters.add(videoCamActive.set("videoCamActive", true));

    parameters.add(videoDeviceIndex.set("videoDeviceIndex", 0, 0, 10));
    parameters.add(cameraViewWidth.set("cameraViewWidth", 640, 10, 5000));
    parameters.add(cameraViewHeight.set("cameraViewHeight", 480, 10, 5000));
    
    parameters.add(useSamplePosForDrawPos.set("useSamplePosForDrawPos", false));
    parameters.add(useSampleSizeForDrawSize.set("useSampleSizeForDrawSize", false));
    parameters.add(useScaleXForScaleY.set("useScaleXForScaleY", false));
    parameters.add(constrainToEdges.set("constrainToEdges", false));

    parameters.add(alphaThreshold.set("alphaThreshold", 0.03, 0.0, 0.05));
    
    holdModParamFloatArgs.name = "alpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	alpha = createModParameter(holdModParamFloatArgs);
    parameters.add(alpha->parameters);
    
    holdModParamFloatArgs.name = "samplePosX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	samplePosX = createModParameter(holdModParamFloatArgs);
    parameters.add(samplePosX->parameters);
    
    holdModParamFloatArgs.name = "samplePosY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	samplePosY = createModParameter(holdModParamFloatArgs);
    parameters.add(samplePosY->parameters);
    
    holdModParamFloatArgs.name = "sampleWidth";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	sampleWidth = createModParameter(holdModParamFloatArgs);
    parameters.add(sampleWidth->parameters);
    
    holdModParamFloatArgs.name = "sampleHeight";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	sampleHeight = createModParameter(holdModParamFloatArgs);
    parameters.add(sampleHeight->parameters);
    
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
    
    // add listener to relevent parameters:
    videoDeviceIndex.addListener(this, &TXDrawVideoCam::videoDeviceIndexChanged);

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
    
    // register
    registerTexture();
    
    // initalise
    initVideoCam();
}

void TXDrawVideoCam::update(){
    if (videoCamActive) {
        vidGrabber.update();
    };
}

void TXDrawVideoCam::draw(){
    bool setUniforms = true;
    float drawXAdjusted, drawYAdjusted;
    float sampleWScaled, sampleHScaled;
    float holdDrawPosX, holdDrawPosY;
	int   drawWidthPixels, drawHeightPixels;
    float anchorXPixels, anchorYPixels;
    float holdScaleX, holdScaleY;
    // check before drawing
    if (!drawActive->getBool()) {
        return;
    };
    if (!vidGrabber.isInitialized()) {
        return;
    };
    int   holdMaxWidth = getMaxWidth();
    int   holdMaxHeight = getMaxHeight();
    float holdVideoCamWidth = vidGrabber.getWidth();
    float holdVideoCamHeight = vidGrabber.getHeight();
    float holdSamplePosX = samplePosX->getFloat();
    float holdSamplePosY = samplePosY->getFloat();
    float holdSampleWidth = sampleWidth->getFloat();
    float holdSampleHeight = sampleHeight->getFloat();
    float sampleWidthPixels = holdSampleWidth * holdVideoCamWidth;
    float sampleHeightPixels = sampleHeight->getFloat() * holdVideoCamHeight;
    float sampleOffsetX = holdSamplePosX * (1 - holdSampleWidth) * holdMaxWidth;
    float sampleOffsetY = holdSamplePosY * (1 - holdSampleHeight) * holdMaxHeight;
    float fboEdgeOffsetX = 1.0f / holdVideoCamWidth;
    float fboEdgeOffsetY = 1.0f / holdVideoCamHeight;
    //    was set to higher for ipad retina
    //    float fboEdgeOffsetX = 2.0f / holdMovieWidth;
    //    float fboEdgeOffsetY = 2.0f / holdMovieHeight;
    
//    ofLogNotice() << "TXDrawVideoCam::draw - holdVideoCamWidth, holdVideoCamHeight: " << holdVideoCamWidth << ", " << holdVideoCamHeight;

    if (useSamplePosForDrawPos) {
        holdDrawPosX = holdSamplePosX;
        holdDrawPosY = holdSamplePosY;
    } else {
        holdDrawPosX = drawPosX->getFloat();
        holdDrawPosY = drawPosY->getFloat();
    };
    if (useSampleSizeForDrawSize) {
        drawWidthPixels = (int) (fmax(holdSampleWidth * holdMaxWidth, 1));
        drawHeightPixels = (int) (fmax(holdSampleHeight * holdMaxHeight, 1));
    } else {
        drawWidthPixels = (int) (fmax(drawWidth->getFloat() * holdMaxWidth, 1));
        drawHeightPixels = (int) (fmax(drawHeight->getFloat() * holdMaxHeight, 1));
    };
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
    if (! constrainToEdges) {
        drawXAdjusted = holdDrawPosX * holdMaxWidth;
        drawYAdjusted = holdDrawPosY * holdMaxHeight;
    } else {
        sampleWScaled = holdSampleWidth * holdMaxWidth * holdScaleX;
        sampleHScaled = holdSampleHeight * holdMaxHeight * holdScaleY;
        drawXAdjusted = (0.5* sampleWScaled) + ((holdMaxWidth - sampleWScaled) * holdDrawPosX);
        drawYAdjusted = (0.5* sampleHScaled) + ((holdMaxHeight - sampleHScaled) * holdDrawPosY);
    };
    ofPushMatrix();
    ofTranslate(drawXAdjusted, drawYAdjusted, 0.0);
    ofRotateZ(rotateMultiply->getFloat() * rotate->getFloat());
    ofScale(holdScaleX, holdScaleY, 1.0);

//    // testing xxx
//    ofLogNotice() << "testing xxx  TXDrawVideoCam::draw -  widthNextPow2Ratio, heightNextPow2Ratio, outMovie.getWidth(), outMovie.getHeight()";
//    ofLogNotice() << widthNextPow2Ratio <<  ", " << heightNextPow2Ratio <<  ", " << outMovie.getWidth() <<  ", " << outMovie.getHeight();
    
    float tex0X, tex0Y, tex1X, tex1Y, tex2X, tex2Y, tex3X, tex3Y;
#ifdef TARGET_OPENGLES
    // Use widthNextPow2Ratio, heightNextPow2Ratio to adjust texture coords
    float widthNextPow2Ratio = (float) holdMovieWidth /ofNextPow2(holdMovieWidth);
    float heightNextPow2Ratio = (float) holdMovieHeight /ofNextPow2(holdMovieHeight);
    tex0X = (fboEdgeOffsetX + sampleOffsetX) * widthNextPow2Ratio;
    tex0Y = fboEdgeOffsetY * heightNextPow2Ratio;
    tex1X = (holdSampleWidth + sampleOffsetX - fboEdgeOffsetX) * widthNextPow2Ratio;
    tex1Y = fboEdgeOffsetY * heightNextPow2Ratio;
    tex2X = (holdSampleWidth + sampleOffsetX - fboEdgeOffsetX) * widthNextPow2Ratio;
    tex2Y = (holdSampleHeight - fboEdgeOffsetY) * heightNextPow2Ratio;
    tex3X = (fboEdgeOffsetX + sampleOffsetX) * widthNextPow2Ratio;
    tex3Y = (holdSampleHeight - fboEdgeOffsetY) * heightNextPow2Ratio;
#else
    tex0X = fboEdgeOffsetX + sampleOffsetX;
    tex0Y = fboEdgeOffsetY + sampleOffsetY;
    tex1X = (sampleWidthPixels + sampleOffsetX - fboEdgeOffsetX);
    tex1Y = fboEdgeOffsetY + sampleOffsetY;
    tex2X = (sampleWidthPixels + sampleOffsetX - fboEdgeOffsetX);
    tex2Y = (sampleHeightPixels + sampleOffsetY - fboEdgeOffsetY);
    tex3X = fboEdgeOffsetX + sampleOffsetX;
    tex3Y = (sampleHeightPixels + sampleOffsetY - fboEdgeOffsetY);
#endif

   
     //  draw
    drawShader.begin();
    // save time if already set before
    if (setUniforms) {
        drawShader.setUniform1f("u_alpha", alpha->getFloat());
        drawShader.setUniform1f("u_alphaThreshold", alphaThreshold);
        drawShader.setUniformTexture("u_texture0Sampler", vidGrabber.getTexture(), 0);
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
  /*
    // vidGrabber draw - alternative
    vidGrabber.draw( -anchorXPixels, -anchorYPixels, drawWidthPixels - anchorXPixels, drawHeightPixels - anchorYPixels);
 */   
}

void TXDrawVideoCam::initVideoCam() {
    allVideoDevices = vidGrabber.listDevices();
    int holdIndex = ofClamp(videoDeviceIndex, 0, allVideoDevices.size()-1);
    vidGrabber.setDeviceID(allVideoDevices[holdIndex].id);
    vidGrabber.initGrabber(cameraViewWidth, cameraViewHeight, true); 
}

int TXDrawVideoCam::getTextureWidth() {
    if (vidGrabber.isInitialized()) {
        return vidGrabber.getWidth();
    } else {
        return 0;
    }
}

int TXDrawVideoCam::getTextureHeight() {
    if (vidGrabber.isInitialized()) {
        return vidGrabber.getHeight();
    } else {
        return 0;
    }
}

ofTexture *  TXDrawVideoCam::getTexture() {
    if (vidGrabber.isInitialized()) {
        return & vidGrabber.getTexture();
    } else {
        return NULL;
    };
}

ofPixelsRef TXDrawVideoCam::getPixels() {
    return vidGrabber.getPixels() ;
}

void  TXDrawVideoCam::videoDeviceIndexChanged(int & intArg) {
    initVideoCam();
}

void  TXDrawVideoCam::cameraImageWidthChanged(int & intArg) {
    initVideoCam();
}

void  TXDrawVideoCam::cameraImageHeightChanged(int & intArg) {
    initVideoCam();
}


