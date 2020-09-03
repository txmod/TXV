/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXBlur.h"
#include "TXSystem.h"
#include "TXAsset.h"

// constructor
TXBlur::TXBlur() {
    setup();
}

// destructor
TXBlur::~TXBlur() {
}

void TXBlur::setup(){
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
    
    renderWidthHeightRule.set("renderWidthHeightRule",0,0,12);
    parameters.add(renderWidthHeightRule);
    
    renderCustomWidth.set("renderCustomWidth",1024,1,4096);
    parameters.add(renderCustomWidth);
    
    renderCustomHeight.set("renderCustomHeight",768,1,4096);
    parameters.add(renderCustomHeight);
    
    holdModParamFloatArgs.name = "blurDistance";
    holdModParamFloatArgs.fixedValue = 1.1;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
    blurDistance = createModParameter(holdModParamFloatArgs);
    parameters.add(blurDistance->parameters);
    
    holdModParamIntArgs.name = "noPasses";
    holdModParamIntArgs.fixedValue = 2;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 20;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 5;
	noPasses = createModParameter(holdModParamIntArgs);
    parameters.add(noPasses->parameters);
    
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
    
    // asset slot
    createImageAssetSlot("sourceImageAsset");
    
    // external image slots
    createExtImageModuleSlot("extSourceImageModule");
    
    // add listener to relevent parameters:
    renderWidthHeightRule.addListener(this, &TXBlur::renderSizeChanged);
    renderCustomWidth.addListener(this, &TXBlur::renderSizeChanged);
    renderCustomHeight.addListener(this, &TXBlur::renderSizeChanged);

    sourceImageHasLoaded = false;

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
	//renderShader.load("shadersES2/_ShaderGroups/FXShaders1Tex/Wobble_GLSL.vert","shadersES2/_ShaderGroups/FXShaders1Tex/Wobble_GLSL.frag");
	blurShaderH.load("shadersES2/simpleBlurHorizontal.vert", "shadersES2/simpleBlurHorizontal.frag");
	blurShaderV.load("shadersES2/simpleBlurVertical.vert",   "shadersES2/simpleBlurVertical.frag");
    //  ?????
    // ofTextureData texDat = fbo1.getTexture().getTextureData();
	pixelSizeX = 1.0f / texDat.tex_w;
	pixelSizeY = 1.0f / texDat.tex_h;

#else
	if(ofIsGLProgrammableRenderer()){
		drawShader.load("shadersGL3/AlphaTextureShader.vert", "shadersGL3/AlphaTextureShader.frag");
        //renderShader.load("shadersGL3/_ShaderGroups/FXShaders1Tex/Wobble_GLSL.vert","shadersGL3/_ShaderGroups/FXShaders1Tex/Wobble_GLSL.frag");
        blurShaderH.load("shadersGL3/simpleBlurHorizontal.vert", "shadersGL3/simpleBlurHorizontal.frag");
        blurShaderV.load("shadersGL3/simpleBlurVertical.vert",   "shadersGL3/simpleBlurVertical.frag");
	}else{
		drawShader.load("shadersGL2/AlphaTextureShader.vert", "shadersGL2/AlphaTextureShader.frag");
        //renderShader.load("shadersGL2/_ShaderGroups/FXShaders1Tex/Wobble_GLSL.vert","shadersGL2/_ShaderGroups/FXShaders1Tex/Wobble_GLSL.frag");
        blurShaderH.load("shadersGL2/simpleBlurHorizontal.vert", "shadersGL2/simpleBlurHorizontal.frag");
        blurShaderV.load("shadersGL2/simpleBlurVertical.vert",   "shadersGL2/simpleBlurVertical.frag");
	}
#endif

    oldRenderNow = false;
    outImageIsAllocated = false;

    registerTexture();
}

void TXBlur::update(){
    bool newRenderContinuosly = renderContinuosly->getBool();
    bool newRenderNow = renderNow->getBool();
    // check whether to render
    if (newRenderContinuosly || (newRenderNow && (newRenderNow != oldRenderNow))) {
        renderTexture();
    };
    // reset var
    oldRenderNow = newRenderNow;
}

void TXBlur::draw(){
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
    //    ofLogNotice() << "testing xxx  TXBlur::draw -  widthNextPow2Ratio, heightNextPow2Ratio, outImage.getWidth(), outImage.getHeight()";
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
        drawShader.setUniform1f("u_alphaThreshold", alphaThreshold);
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

void  TXBlur::imageAssetSlotChanged(string slotNameArg) {
    if (slotNameArg == "sourceImageAsset") {
        loadSourceImage();
    };
}

bool TXBlur::loadSourceImage() {
    ofPtr <TXAsset> asset;
    string fileName;
    int sourceImageAssetID = getImageAssetIDSlot("sourceImageAsset").first;
    sourceImageHasLoaded = false;
    if (sourceImageAssetID != 0) {
        asset = parentSystem->getAsset(TXASSETTYPE_IMAGE, sourceImageAssetID);
        fileName = asset->getFileName();
        if (sourceImage.load(fileName)) {
            sourceImageHasLoaded = true;
        };
    };
    return sourceImageHasLoaded;
}

bool TXBlur::getSourceImageHasLoaded() {
    return sourceImageHasLoaded;
}

void TXBlur::allocateTexture(int widthArg, int heightArg) {
    // testing xxx
    //ofLogNotice() << "testing xxx  TXBlur::allocateTexture -  widthArg, heightArg:  "  << widthArg << "  " <<  heightArg;
    
    outImage.allocate(widthArg, heightArg, GL_RGBA);
    outImage.begin();
    ofEnableAlphaBlending();
    ofClear(0,0);
    ofDisableAlphaBlending();
    outImage.end();
    outImageIsAllocated = true;

    fbo2.allocate(widthArg, heightArg, GL_RGBA);
    fbo2.begin();
    ofEnableAlphaBlending();
    ofClear(0,0);
    ofDisableAlphaBlending();
    fbo2.end();
}

void TXBlur::renderTexture() {
    int holdExtSourceID;
    ofPtr<TXModuleBase> extSourceModule;
    int holdRenderWidth, holdRenderHeight;
    
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
        if (!sourceImageHasLoaded) {
            return;
        };
        sourceImageWidth = sourceImage.getWidth();
        sourceImageHeight = sourceImage.getHeight();
    };
    holdRenderWidth = getRenderWidth();
    holdRenderHeight = getRenderHeight();
    if ((holdRenderWidth != outImage.getWidth()) || (holdRenderHeight != outImage.getHeight())) {
        // if size changed, reallocate
        allocateTexture(holdRenderWidth,holdRenderHeight);
    };
    // draw image
    outImage.begin();
    ofEnableAlphaBlending();
    if (useExternalSourceImage) {
        //renderShader.setUniformTexture("u_texture0Sampler", *extSourceModule->getTexture(), 0);
        extSourceModule->getTexture()->draw(0,0, holdRenderWidth, holdRenderHeight);
        
    } else {
        //renderShader.setUniformTexture("u_texture0Sampler", sourceImage.getTexture(), 0);
        sourceImage.draw(0,0, holdRenderWidth, holdRenderHeight);
    };
    ofDisableAlphaBlending();
    outImage.end();

    // perform blur
	ofFbo * src, * dst;
	src = &outImage;
	dst = &fbo2;
    float blurDist = blurDistance->getFloat();
	
	for(int i = 0; i < noPasses->getInt(); i++)
	{
		//float blurPer =  blurDistance * ofMap(i, 0, noPasses, 1.0/noPasses, 1.0);
		
		//first the horizontal shader, X
		blurShaderH.begin();
#ifdef TARGET_OPENGLES
		blurShaderH.setUniform1f("u_pixelSizeX", pixelSizeX);
#endif
		blurShaderH.setUniform1f("u_blurAmnt", blurDist);
		
		dst->begin();
		ofClear(0,0,0,255);
		
        src->draw(0, 0);
        
		dst->end();
		
		blurShaderH.end();
		
        
		//now the vertical shader, Y
		blurShaderV.begin();
#ifdef TARGET_OPENGLES
		blurShaderV.setUniform1f("u_pixelSizeY", pixelSizeY);
#endif
		blurShaderV.setUniform1f("u_blurAmnt", blurDist);
		
		src->begin();
		ofClear(0,0,0,255);
		
        dst->draw(0,0);
		
		src->end();
		
		blurShaderV.end();
	}		
}

int TXBlur::getTextureWidth() {
    return outImage.getWidth();
}

int TXBlur::getTextureHeight() {
    return outImage.getHeight();
}

ofTexture *  TXBlur::getTexture() {
    if (outImage.isAllocated()) {
        return & outImage.getTexture();
    };
    return NULL;
}

void  TXBlur::renderSizeChanged(int & intArg) {
    if ((getRenderWidth() != outImage.getWidth()) || (getRenderHeight() != outImage.getHeight())) {
        // if size changed, reallocate
        allocateTexture(getRenderWidth(),getRenderHeight());
    };
}

int TXBlur::getRenderWidth() {
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

int TXBlur::getRenderHeight() {
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


