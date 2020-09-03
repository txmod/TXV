/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXDrawMovie.h"
#include "TXSystem.h"
#include "TXAsset.h"

// constructor
TXDrawMovie::TXDrawMovie() {
    setup();
}

// destructor
TXDrawMovie::~TXDrawMovie() {
    // remove listeners to relevent parameters:
    ofRemoveListener(speed->parameters.parameterChangedE(),this,&TXDrawMovie::speedHasChanged);
    ofRemoveListener(loopType->parameters.parameterChangedE(),this,&TXDrawMovie::loopTypeHasChanged);
}

void TXDrawMovie::setup(){
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
    
    holdModParamIntArgs.name = "movieScaleMode";
    holdModParamIntArgs.fixedValue = TXIMAGESCALEMODE_SCALETOFIT;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 2;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 2;
	movieScaleMode = createModParameter(holdModParamIntArgs);
    parameters.add(movieScaleMode->parameters);
    
    holdModParamFloatArgs.name = "speed";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -3.0;
    holdModParamFloatArgs.softMax = 3.0;
	speed = createModParameter(holdModParamFloatArgs);
    parameters.add(speed->parameters);
    
    parameters.add(readMovieAlpha.set("readMovieAlpha", false));

    holdModParamIntArgs.name = "loopType";
    holdModParamIntArgs.fixedValue = OF_LOOP_NORMAL;
    holdModParamIntArgs.hardMin = OF_LOOP_NONE;
    holdModParamIntArgs.hardMax = OF_LOOP_NORMAL;
    holdModParamIntArgs.softMin = OF_LOOP_NONE;
    holdModParamIntArgs.softMax = OF_LOOP_NORMAL;
	loopType = createModParameter(holdModParamIntArgs);
    parameters.add(loopType->parameters);
    
    holdModParamBoolArgs.name = "play";
    holdModParamBoolArgs.fixedValue = false;
    play = createModParameter(holdModParamBoolArgs);
    parameters.add(play->parameters);
    
    holdModParamBoolArgs.name = "pause";
    holdModParamBoolArgs.fixedValue = false;
    pause = createModParameter(holdModParamBoolArgs);
    parameters.add(pause->parameters);
    
    holdModParamBoolArgs.name = "goToFirstFrame";
    holdModParamBoolArgs.fixedValue = false;
    goToFirstFrame = createModParameter(holdModParamBoolArgs);
    parameters.add(goToFirstFrame->parameters);
    
    holdModParamBoolArgs.name = "goToNextFrame";
    holdModParamBoolArgs.fixedValue = false;
    goToNextFrame = createModParameter(holdModParamBoolArgs);
    parameters.add(goToNextFrame->parameters);
    
    holdModParamBoolArgs.name = "goToPreviousFrame";
    holdModParamBoolArgs.fixedValue = false;
    goToPreviousFrame = createModParameter(holdModParamBoolArgs);
    parameters.add(goToPreviousFrame->parameters);
    
    holdModParamFloatArgs.name = "position";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	position = createModParameter(holdModParamFloatArgs);
    parameters.add(position->parameters);
    
    parameters.add(useSamplePosForDrawPos.set("useSamplePosForDrawPos", false));
    parameters.add(useSampleSizeForDrawSize.set("useSampleSizeForDrawSize", false));
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
    
    parameters.add(useScaleXForScaleY.set("useScaleXForScaleY", false));

    // add listener to relevent mod parameters:
    readMovieAlpha.addListener(this, &TXDrawMovie::readMovieAlphaChanged);
    ofAddListener(speed->parameters.parameterChangedE(),this,&TXDrawMovie::speedHasChanged);
    ofAddListener(loopType->parameters.parameterChangedE(),this,&TXDrawMovie::loopTypeHasChanged);

    // asset slots
    createMovieAssetSlot("movieAsset");
    
    movieHasLoaded = false;

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
    
    // init vars
    speedChanged = false;
    loopTypeChanged = false;
    oldPause = false;
    oldPlay = false;
    oldPosition = 0.0;
    oldGoToNextFrame = false;
    oldGoToPreviousFrame = false;
    oldGoToFirstFrame = false;
    forceStop = false;

    // register
    registerTexture();
}

void TXDrawMovie::update(){
    float newPosition = position->getFloat();
    float newGoToNextFrame = goToNextFrame->getBool();
    float newGoToPreviousFrame = goToPreviousFrame->getBool();
    float newGoToFirstFrame = goToFirstFrame->getBool();
    bool newPause = pause->getBool();
    bool newPlay = play->getBool();
    
    if (speedChanged && !newPause) {
        outMovie.setSpeed(speed->getFloat());
    };
    if (loopTypeChanged) {
        outMovie.setLoopState((ofLoopType) loopType->getInt());
    };
    // prioritise updates to avoid conflicts - lower priority ignored
    if (newPosition != oldPosition) {
        outMovie.setPosition(newPosition);
    } else if (newGoToNextFrame && !oldGoToNextFrame) {
            outMovie.nextFrame();
    } else if (newGoToPreviousFrame && !oldGoToPreviousFrame) {
        outMovie.previousFrame();
    } else if (newGoToFirstFrame && !oldGoToFirstFrame) {
        outMovie.firstFrame();
    };
    if (newPlay != oldPlay) {
        if (newPlay) {
            outMovie.firstFrame();
            outMovie.play();
            if (newPause) {
                outMovie.setPaused(true);
            }
        } else {
            //outMovie.setPaused(true);
            outMovie.stop();
        };
    } else {
        if ((newPause != oldPause) && newPlay) {
            outMovie.setPaused(newPause);
        };
    };
    if (forceStop) {
        outMovie.stop();
        forceStop = false;
    };
    // reset vars
    oldPause = newPause;
    oldPlay = newPlay;
    oldPosition = newPosition;
    oldGoToNextFrame = newGoToNextFrame;
    oldGoToPreviousFrame = newGoToPreviousFrame;
    oldGoToFirstFrame = newGoToFirstFrame;
    speedChanged = false;
    loopTypeChanged = false;
    
    // now ready to update
    outMovie.update();
}

void TXDrawMovie::draw(){
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
    if (!movieHasLoaded) {
        return;
    };
    if (!(outMovie.isLoaded() && outMovie.isInitialized())) {
        return;
    };
    
    int   holdMaxWidth = getMaxWidth();
    int   holdMaxHeight = getMaxHeight();
    float holdMovieWidth = outMovie.getWidth();
    float holdMovieHeight = outMovie.getHeight();
    float holdSamplePosX = samplePosX->getFloat();
    float holdSamplePosY = samplePosY->getFloat();
    float holdSampleWidth = sampleWidth->getFloat();
    float holdSampleHeight = sampleHeight->getFloat();
    float fboEdgeOffsetX = 1.0f / holdMovieWidth;
    float fboEdgeOffsetY = 1.0f / holdMovieHeight;
    //    was set to higher for ipad retina
    //    float fboEdgeOffsetX = 2.0f / holdMovieWidth;
    //    float fboEdgeOffsetY = 2.0f / holdMovieHeight;
    
    float movieRatioW, movieRatioH;
    float movieScaleX, movieScaleY;
    float drawBorderX, drawBorderY;
    float scaledMovieWidth, scaledMovieHeight;
    float ratioOrig, ratioTarget;
    float tex0X, tex0Y, tex1X, tex1Y, tex2X, tex2Y, tex3X, tex3Y;    
    float texBorderX, texBorderY;
    float texImageWidth, texImageHeight;
    float sampleWidthPixels, sampleHeightPixels;
    float sampleOffsetX, sampleOffsetY;
    
    switch (movieScaleMode->getInt()) {
        case TXIMAGESCALEMODE_SCALETOFIT:
            movieRatioW = (float) holdMaxWidth / holdMovieWidth;
            movieRatioH = (float) holdMaxHeight / holdMovieHeight;
            movieScaleX = min(movieRatioW, movieRatioH);
            movieScaleY = movieScaleX;
            scaledMovieWidth = holdMovieWidth * movieScaleX;
            scaledMovieHeight = holdMovieHeight * movieScaleY;
            drawBorderX = (holdMaxWidth - scaledMovieWidth) * 0.5;
            drawBorderY = (holdMaxHeight - scaledMovieHeight) * 0.5;
            texImageWidth = holdMovieWidth;
            texImageHeight = holdMovieHeight;
            texBorderX = 0;
            texBorderY = 0;
            break;
        case TXIMAGESCALEMODE_SCALETOFILL:
            scaledMovieWidth = holdMaxWidth;
            scaledMovieHeight = holdMaxHeight;
            drawBorderX = 0;
            drawBorderY = 0;
            ratioOrig = (float) holdMovieWidth / holdMovieHeight;
            ratioTarget = (float) holdMaxWidth / holdMaxHeight;
            if (ratioOrig > ratioTarget) {
                texImageWidth = holdMovieHeight * ratioTarget;
                texImageHeight = holdMovieHeight;
                texBorderX =  (holdMovieWidth - texImageWidth ) * 0.5;
                texBorderY = 0;
            } else {
                texImageWidth = holdMovieWidth;
                texImageHeight = holdMovieWidth / ratioTarget;
                texBorderX = 0;
                texBorderY = (holdMovieHeight - texImageHeight ) * 0.5;
            };
            break;
        case TXIMAGESCALEMODE_STRETCHTOFILL:
            scaledMovieWidth = holdMaxWidth;
            scaledMovieHeight = holdMaxHeight;
            drawBorderX = 0;
            drawBorderY = 0;
            texImageWidth = holdMovieWidth;
            texImageHeight = holdMovieHeight;
            texBorderX = 0;
            texBorderY = 0;
            break;
        default:
            scaledMovieWidth = holdMaxWidth;
            scaledMovieHeight = holdMaxHeight;
            drawBorderX = 0;
            drawBorderY = 0;
            texImageWidth = holdMovieWidth;
            texImageHeight = holdMovieHeight;
            texBorderX = 0;
            texBorderY = 0;
            break;
    };

    if (useSamplePosForDrawPos) {
        holdDrawPosX = holdSamplePosX;
        holdDrawPosY = holdSamplePosY;
    } else {
        holdDrawPosX = drawPosX->getFloat();
        holdDrawPosY = drawPosY->getFloat();
    };
    if (useSampleSizeForDrawSize) {
        drawWidthPixels = (int) (fmax(holdSampleWidth * scaledMovieWidth, 1));
        drawHeightPixels = (int) (fmax(holdSampleHeight * scaledMovieHeight, 1));
    } else {
        drawWidthPixels = (int) (fmax(drawWidth->getFloat() * scaledMovieWidth, 1));
        drawHeightPixels = (int) (fmax(drawHeight->getFloat() * scaledMovieHeight, 1));
    };
    anchorXPixels = anchorX->getFloat() * drawWidthPixels;
    anchorYPixels = anchorY->getFloat() * drawHeightPixels;
    
    holdScaleX = scaleX->getFloat();
    if (useScaleXForScaleY) {
        holdScaleY = holdScaleX;
    } else {
        holdScaleY = scaleY->getFloat();
    };
    // translate, rotate, scale
    if (! constrainToEdges) {
        drawXAdjusted = holdDrawPosX * scaledMovieWidth;
        drawYAdjusted = holdDrawPosY * scaledMovieHeight;
    } else {
        sampleWScaled = holdSampleWidth * scaledMovieWidth * holdScaleX;
        sampleHScaled = holdSampleHeight * scaledMovieHeight * holdScaleY;
        drawXAdjusted = (0.5* sampleWScaled) + ((scaledMovieWidth - sampleWScaled) * holdDrawPosX);
        drawYAdjusted = (0.5* sampleHScaled) + ((scaledMovieHeight - sampleHScaled) * holdDrawPosY);
    };
    ofPushMatrix();
    ofTranslate(drawBorderX + drawXAdjusted, drawBorderY + drawYAdjusted, 0.0);
    ofRotateZ(rotateMultiply->getFloat() * rotate->getFloat());
    ofScale(holdScaleX, holdScaleY, 1.0);

    sampleWidthPixels = holdSampleWidth * texImageWidth;
    sampleHeightPixels = holdSampleHeight * texImageHeight;
    sampleOffsetX = holdSamplePosX * (1 - holdSampleWidth) * texImageWidth;
    sampleOffsetY = holdSamplePosY * (1 - holdSampleHeight) * texImageHeight;
    
#ifdef TARGET_OPENGLES
    
    /*
    // WARNING - OLD TARGET_OPENGLES CODE - UNTESTED
     // Use widthNextPow2Ratio, heightNextPow2Ratio to adjust texture coords
     float widthNextPow2Ratio = (float) sourceImageWidth /ofNextPow2(sourceImageWidth);
     float heightNextPow2Ratio = (float) sourceImageHeight /ofNextPow2(sourceImageHeight);
     tex0X = (texBorderX + fboEdgeOffsetX + sampleOffsetX) * widthNextPow2Ratio;
     tex0Y = (texBorderY + fboEdgeOffsetY + sampleOffsetY) * heightNextPow2Ratio;
     tex1X = (texBorderX + holdSampleWidth + sampleOffsetX - fboEdgeOffsetX) * widthNextPow2Ratio;
     tex1Y = (texBorderY + fboEdgeOffsetY + sampleOffsetY) * heightNextPow2Ratio;
     tex2X = (texBorderX + holdSampleWidth + sampleOffsetX - fboEdgeOffsetX) * widthNextPow2Ratio;
     tex2Y = (texBorderY + holdSampleHeight + sampleOffsetY - fboEdgeOffsetY) * heightNextPow2Ratio;
     tex3X = (texBorderX + fboEdgeOffsetX + sampleOffsetX) * widthNextPow2Ratio;
     tex3Y = (texBorderY + holdSampleHeight + sampleOffsetY - fboEdgeOffsetY) * heightNextPow2Ratio;
     */
#else
    tex0X = texBorderX + fboEdgeOffsetX + sampleOffsetX;
    tex0Y = texBorderY + fboEdgeOffsetY + sampleOffsetY;
    tex1X = texBorderX + sampleWidthPixels + sampleOffsetX - fboEdgeOffsetX;
    tex1Y = texBorderY + fboEdgeOffsetY + sampleOffsetY;
    tex2X = texBorderX + sampleWidthPixels + sampleOffsetX - fboEdgeOffsetX;
    tex2Y = texBorderY + sampleHeightPixels + sampleOffsetY - fboEdgeOffsetY;
    tex3X = texBorderX + fboEdgeOffsetX + sampleOffsetX;
    tex3Y = texBorderY + sampleHeightPixels + sampleOffsetY - fboEdgeOffsetY;
#endif

   
     //  draw
    drawShader.begin();
    // save time if already set before
    if (setUniforms) {
        drawShader.setUniform1f("u_alpha", alpha->getFloat());
        drawShader.setUniform1f("u_alphaThreshold", alphaThreshold);
        drawShader.setUniformTexture("u_texture0Sampler", outMovie.getTexture(), 0);
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
    // direct movie draw - alternative
    outMovie.draw( -anchorXPixels, -anchorYPixels, drawWidthPixels - anchorXPixels, drawHeightPixels - anchorYPixels);
 */   
}

bool TXDrawMovie::loadMovie() {
    ofPtr <TXAsset> asset;
    string fileName;
    int movieAssetID = getMovieAssetIDSlot("movieAsset").first;
    if (movieHasLoaded) {
        outMovie.closeMovie();
        movieHasLoaded = false;
    };
    if (movieAssetID != 0) {
        asset = parentSystem->getAsset(TXASSETTYPE_MOVIE, movieAssetID);
        fileName = asset->getFileName();
        outMovie.stop();
        if (readMovieAlpha) {
            outMovie.setPixelFormat(OF_PIXELS_RGBA);
        } else {
            outMovie.setPixelFormat(OF_PIXELS_RGB);
        };        
        if (outMovie.load(fileName)) {
            movieHasLoaded = true;
            if (play->getBool()) {
                outMovie.play();
                outMovie.setPaused(pause->getBool());
            } else {
                forceStop = true;
            };
            // ofLogNotice() << "TXDrawMovie::loadMovie - movieHasLoaded:" << fileName;
        } else {
            ofLogNotice() << "TXDrawMovie::loadMovie - movie failed to Load: " << fileName;
        };
    };
    return movieHasLoaded;
}

bool TXDrawMovie::getMovieHasLoaded() {
    return movieHasLoaded;
}

int TXDrawMovie::getTextureWidth() {
    if (movieHasLoaded) {
        return outMovie.getWidth();
    } else {
        return 0;
    }
}

int TXDrawMovie::getTextureHeight() {
    if (movieHasLoaded) {
        return outMovie.getHeight();
    } else {
        return 0;
    }
}

ofTexture *  TXDrawMovie::getTexture() {
    if (movieHasLoaded) {
        // return outMovie.getTexture();  //OLD
        return &outMovie.getTexture();
    } else {
        return NULL;
    };
}

ofPixelsRef TXDrawMovie::getPixels() {
    return outMovie.getPixels() ;
}

void  TXDrawMovie::movieAssetSlotChanged(string slotNameArg) {
    loadMovie();
}

void  TXDrawMovie::readMovieAlphaChanged(bool & readMovieAlphaArg) {
    loadMovie();
}

void TXDrawMovie::speedHasChanged(ofAbstractParameter & parameterArg ) {
    speedChanged = true;
}

void TXDrawMovie::loopTypeHasChanged(ofAbstractParameter & parameterArg ) {
    loopTypeChanged = true;
}




