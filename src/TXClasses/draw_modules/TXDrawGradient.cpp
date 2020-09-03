/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXSystem.h"
#include "TXDrawGradient.h"
#include "TXFunctions.h"

// constructor
TXDrawGradient::TXDrawGradient() {
    setup();
}

// destructor
TXDrawGradient::~TXDrawGradient() {
}

void TXDrawGradient::setup(){
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
    
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
    
    holdModParamIntArgs.name = "gradientType";
    holdModParamIntArgs.fixedValue = TXGRADIENTTYPE_HORIZONTAL;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalGradientTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalGradientTypes - 1;
	gradientType = createModParameter(holdModParamIntArgs);
    parameters.add(gradientType->parameters);
    
    holdModParamIntArgs.name = "numColors";
    holdModParamIntArgs.fixedValue = 4;
    holdModParamIntArgs.hardMin = 2;
    holdModParamIntArgs.hardMax = 4;
    holdModParamIntArgs.softMin = 2;
    holdModParamIntArgs.softMax = 4;
	numColors = createModParameter(holdModParamIntArgs);
    parameters.add(numColors->parameters);
    
    holdModParamFloatArgs.name = "curveBias";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	curveBias = createModParameter(holdModParamFloatArgs);
    parameters.add(curveBias->parameters);
    
    holdModParamBoolArgs.name = "invert";
    holdModParamBoolArgs.fixedValue = false;
    invert = createModParameter(holdModParamBoolArgs);
    parameters.add(invert->parameters);

    holdModParamFloatArgs.name = "point1X";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	point1X = createModParameter(holdModParamFloatArgs);
    parameters.add(point1X->parameters);
    
    holdModParamFloatArgs.name = "point1Y";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	point1Y = createModParameter(holdModParamFloatArgs);
    parameters.add(point1Y->parameters);
    
    holdModParamFloatArgs.name = "point2X";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	point2X = createModParameter(holdModParamFloatArgs);
    parameters.add(point2X->parameters);
    
    holdModParamFloatArgs.name = "point2Y";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	point2Y = createModParameter(holdModParamFloatArgs);
    parameters.add(point2Y->parameters);
    
    holdModParamFloatArgs.name = "color1Hue";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    color1Hue = createModParameter(holdModParamFloatArgs);
    parameters.add(color1Hue->parameters);
    
    holdModParamFloatArgs.name = "color1HueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    color1HueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(color1HueRotate->parameters);
    
    holdModParamFloatArgs.name = "color1Saturation";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color1Saturation = createModParameter(holdModParamFloatArgs);
    parameters.add(color1Saturation->parameters);
    
    holdModParamFloatArgs.name = "color1Brightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color1Brightness = createModParameter(holdModParamFloatArgs);
    parameters.add(color1Brightness->parameters);
    
    holdModParamFloatArgs.name = "color1Alpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color1Alpha = createModParameter(holdModParamFloatArgs);
    parameters.add(color1Alpha->parameters);
    
    holdModParamBoolArgs.name = "color1HSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    color1HSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(color1HSBAsRGB->parameters);
    
    holdModParamFloatArgs.name = "color2Hue";
    holdModParamFloatArgs.fixedValue = 0.25;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    color2Hue = createModParameter(holdModParamFloatArgs);
    parameters.add(color2Hue->parameters);
    
    holdModParamFloatArgs.name = "color2HueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    color2HueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(color2HueRotate->parameters);
    
    holdModParamFloatArgs.name = "color2Saturation";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color2Saturation = createModParameter(holdModParamFloatArgs);
    parameters.add(color2Saturation->parameters);
    
    holdModParamFloatArgs.name = "color2Brightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color2Brightness = createModParameter(holdModParamFloatArgs);
    parameters.add(color2Brightness->parameters);
    
    holdModParamFloatArgs.name = "color2Alpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color2Alpha = createModParameter(holdModParamFloatArgs);
    parameters.add(color2Alpha->parameters);
    
    holdModParamBoolArgs.name = "color2HSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    color2HSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(color2HSBAsRGB->parameters);
    
    holdModParamFloatArgs.name = "color3Hue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    color3Hue = createModParameter(holdModParamFloatArgs);
    parameters.add(color3Hue->parameters);
    
    holdModParamFloatArgs.name = "color3HueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    color3HueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(color3HueRotate->parameters);
    
    holdModParamFloatArgs.name = "color3Saturation";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color3Saturation = createModParameter(holdModParamFloatArgs);
    parameters.add(color3Saturation->parameters);
    
    holdModParamFloatArgs.name = "color3Brightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color3Brightness = createModParameter(holdModParamFloatArgs);
    parameters.add(color3Brightness->parameters);
    
    holdModParamFloatArgs.name = "color3Alpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color3Alpha = createModParameter(holdModParamFloatArgs);
    parameters.add(color3Alpha->parameters);
    
    holdModParamBoolArgs.name = "color3HSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    color3HSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(color3HSBAsRGB->parameters);
    
    holdModParamFloatArgs.name = "color4Hue";
    holdModParamFloatArgs.fixedValue = 0.75;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    color4Hue = createModParameter(holdModParamFloatArgs);
    parameters.add(color4Hue->parameters);
    
    holdModParamFloatArgs.name = "color4HueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    color4HueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(color4HueRotate->parameters);
    
    holdModParamFloatArgs.name = "color4Saturation";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color4Saturation = createModParameter(holdModParamFloatArgs);
    parameters.add(color4Saturation->parameters);
    
    holdModParamFloatArgs.name = "color4Brightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color4Brightness = createModParameter(holdModParamFloatArgs);
    parameters.add(color4Brightness->parameters);
    
    holdModParamFloatArgs.name = "color4Alpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color4Alpha = createModParameter(holdModParamFloatArgs);
    parameters.add(color4Alpha->parameters);
    
    holdModParamBoolArgs.name = "color4HSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    color4HSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(color4HSBAsRGB->parameters);
    
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
    renderWidthHeightRule.addListener(this, &TXDrawGradient::renderSizeChanged);
    renderCustomWidth.addListener(this, &TXDrawGradient::renderSizeChanged);
    renderCustomHeight.addListener(this, &TXDrawGradient::renderSizeChanged);

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
    
    oldRenderNow = false;
    currentTime = 0;

    // load draw shader
#ifdef TARGET_OPENGLES
	drawShader.load("shadersES2/AlphaTextureShader.vert","shadersES2/AlphaTextureShader.frag");
#else
	if(ofIsGLProgrammableRenderer()){
		drawShader.load("shadersGL3/AlphaTextureShader.vert", "shadersGL3/AlphaTextureShader.frag");
	}else{
		drawShader.load("shadersGL2/AlphaTextureShader.vert", "shadersGL2/AlphaTextureShader.frag");
	}
#endif
    // load render shader
    loadRenderShader();

    // set up texture
    allocateTexture();
    registerTexture();
}

void TXDrawGradient::update(){
    bool newRenderContinuosly = renderContinuosly->getBool();
    bool newRenderNow = renderNow->getBool();
    // check whether to render
    if (newRenderContinuosly || (newRenderNow && (newRenderNow != oldRenderNow))) {
        renderTexture();
    };
    // reset var
    oldRenderNow = newRenderNow;
}

void TXDrawGradient::draw(){
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
    
    //    // testing xxx
    //    ofLogNotice() << "testing xxx  TXDrawGradient::draw -  widthNextPow2Ratio, heightNextPow2Ratio, outImage.getWidth(), outImage.getHeight()";
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
    if (setUniforms) {
        drawShader.setUniform1f("u_alpha", drawAlpha->getFloat());
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
    
    ofPopMatrix();
    drawShader.end();
}

void TXDrawGradient::loadRenderShader() {
    string fileNameVert = "GradientShader.vert";
    string fileNameFrag = "GradientShader.frag";
    
#ifdef TARGET_OPENGLES
	renderShader.load("shadersES2/"+fileNameVert, "shadersES2/"+fileNameFrag);
#else
	if(ofIsGLProgrammableRenderer()){
        renderShader.load("shadersGL3/"+fileNameVert, "shadersGL3/"+fileNameFrag);
	}else{
        renderShader.load("shadersGL2/"+fileNameVert, "shadersGL2/"+fileNameFrag);
	}
#endif
    
}

void TXDrawGradient::allocateTexture() {
    
#ifdef TARGET_OPENGLES
    outImage.allocate(getRenderWidth(), getRenderHeight(), GL_RGBA);
    //ofLogWarning("ofApp") << "TXDrawGradient::allocateTexture() - GL_RGBA32F_ARB is not available for OPENGLES.  Using RGBA.";
#else
    outImage.allocate(getRenderWidth(), getRenderHeight(), GL_RGBA32F_ARB);
    //ofLogNotice() << "TXDrawGradient::allocateTexture() - GL_RGBA32F_ARB: ";
#endif
    
    outImage.begin();
    ofClear(0,255);
    outImage.end();
}

void TXDrawGradient::renderTexture() {
    float holdWidth = outImage.getWidth();
    float holdHeight = outImage.getHeight();
    
    outImage.begin();
    ofClear(0,255);
    
    ofColor color1;
    ofColor color2;
    ofColor color3;
    ofColor color4;
    
    color1 = TXFunctions::txGetColor(color1Hue->getFloat(), color1Saturation->getFloat(), color1Brightness->getFloat(), color1Alpha->getFloat(),
                                     color1HueRotate->getFloat(), color1HSBAsRGB->getBool());
    color2 = TXFunctions::txGetColor(color2Hue->getFloat(), color2Saturation->getFloat(), color2Brightness->getFloat(), color2Alpha->getFloat(),
                                     color2HueRotate->getFloat(), color2HSBAsRGB->getBool());
    color3 = TXFunctions::txGetColor(color3Hue->getFloat(), color3Saturation->getFloat(), color3Brightness->getFloat(), color3Alpha->getFloat(),
                                     color3HueRotate->getFloat(), color3HSBAsRGB->getBool());
    color4 = TXFunctions::txGetColor(color4Hue->getFloat(), color4Saturation->getFloat(), color4Brightness->getFloat(), color4Alpha->getFloat(),
                                     color4HueRotate->getFloat(), color4HSBAsRGB->getBool());
    
    renderShader.begin();

    // set uniforms
    renderShader.setUniform2f("resolution", holdWidth, holdHeight);
    renderShader.setUniform4f("color1", color1.r/255.0f, color1.g/255.0f, color1.b/255.0f, color1.a/255.0f);
    renderShader.setUniform4f("color2", color2.r/255.0f, color2.g/255.0f, color2.b/255.0f, color2.a/255.0f);
    renderShader.setUniform4f("color3", color3.r/255.0f, color3.g/255.0f, color3.b/255.0f, color3.a/255.0f);
    renderShader.setUniform4f("color4", color4.r/255.0f, color4.g/255.0f, color4.b/255.0f, color4.a/255.0f);

    renderShader.setUniform2f("point1", point1X->getFloat(), point1Y->getFloat());
    renderShader.setUniform2f("point2", point2X->getFloat(), point2Y->getFloat());
    renderShader.setUniform1i("gradientType", gradientType->getInt());
    renderShader.setUniform1i("numColors", numColors->getInt());
    renderShader.setUniform1f("curveBias", curveBias->getFloat());
    renderShader.setUniform1i("invert", (int) invert->getBool());
    
    ofDrawRectangle(0,0,holdWidth, holdHeight);
    renderShader.end();
    outImage.end();
}

void TXDrawGradient::windowResized(int w, int h) {
    if (maxWidthHeightRule != MAXWIDTHHEIGHTRULE_CUSTOMSIZE) {
        allocateTexture();
        outImage.begin();
        ofClear(0,255);
        outImage.end();
    };
}

int TXDrawGradient::getTextureWidth() {
    return outImage.getWidth();
}

int TXDrawGradient::getTextureHeight() {
    return outImage.getHeight();
}

ofTexture *  TXDrawGradient::getTexture() {
    return & outImage.getTexture();
}

void  TXDrawGradient::renderSizeChanged(int & intArg) {
    if ((getRenderWidth() != outImage.getWidth()) || (getRenderHeight() != outImage.getHeight())) {
        // if size changed, reallocate
        allocateTexture();
    };
}

int TXDrawGradient::getRenderWidth() {
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

int TXDrawGradient::getRenderHeight() {
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

