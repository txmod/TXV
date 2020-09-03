/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXTileMask.h"
#include "TXSystem.h"
#include "TXAsset.h"

// constructor
TXTileMask::TXTileMask() {
    setup();
}

// destructor
TXTileMask::~TXTileMask() {
}

void TXTileMask::addExtraParameters() {
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    parameters.add(useExternalMaskImage.set("useExternalMaskImage", false));
    
    holdModParamIntArgs.name = "maskType";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXMASKTYPE_FEATHEREDDIAMOND;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXMASKTYPE_FEATHEREDDIAMOND;
    maskType = createModParameter(holdModParamIntArgs);
    parameters.add(maskType->parameters);
    
    parameters.add(invertMask.set("invertMask", false));
    
    holdModParamFloatArgs.name = "feathering";
    holdModParamFloatArgs.fixedValue = 0.2;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    feathering = createModParameter(holdModParamFloatArgs);
    parameters.add(feathering->parameters);
    
    parameters.add(useSamplePosForRenderPos.set("useSamplePosForRenderPos", false));
    parameters.add(useSampleSizeForRenderSize.set("useSampleSizeForRenderSize", false));
    parameters.add(constrainToEdges.set("constrainToEdges", false));
    
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
    
    holdModParamFloatArgs.name = "numTiles";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 1.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 1.0;
    holdModParamFloatArgs.softMax = 10.0;
    numTiles = createModParameter(holdModParamFloatArgs);
    parameters.add(numTiles->parameters);
    
    holdModParamBoolArgs.name = "mirrorTileX";
    holdModParamBoolArgs.fixedValue = true;
    mirrorTileX = createModParameter(holdModParamBoolArgs);
    parameters.add(mirrorTileX->parameters);
    
    holdModParamBoolArgs.name = "mirrorTileY";
    holdModParamBoolArgs.fixedValue = true;
    mirrorTileY = createModParameter(holdModParamBoolArgs);
    parameters.add(mirrorTileY->parameters);
    
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
    createImageAssetSlot("maskImageAsset");
    
    // external image slots
    createExtImageModuleSlot("extMaskImageModule");
    
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
}

void TXTileMask::addExtraListeners() {
    // empty for this module
}

bool TXTileMask::setExtraUniforms(int sourceImageWidth, int sourceImageHeight) {
    // empty for this module

    return true;
}

void TXTileMask::extraUpdateAction() {
    if (maskImageHasChanged) {
        loadMaskImage();
        maskImageHasChanged = false;
    };
}

void TXTileMask::loadRenderShader() {
    // load shaders
#ifdef TARGET_OPENGLES
    renderShader.load("shadersES2/AlphaTextureTileShader.vert","shadersES2/AlphaTextureTileShader.frag");
    renderWithMaskShader.load("shadersES2/AlphaTexMaskShader.vert","shadersES2/AlphaTexMaskShader.frag");
    renderWithMaskTexShader.load("shadersES2/AlphaTexMaskShader.vert","shadersES2/AlphaTexMaskTexShader.frag");
#else
    if(ofIsGLProgrammableRenderer()){
        renderShader.load("shadersGL3/AlphaTextureTileShader.vert", "shadersGL3/AlphaTextureTileShader.frag");
        renderWithMaskShader.load("shadersGL3/AlphaTexMaskShader.vert","shadersGL3/AlphaTexMaskShader.frag");
        renderWithMaskTexShader.load("shadersGL3/AlphaTexMaskShader.vert","shadersGL3/AlphaTexMaskTexShader.frag");
    }else{
        renderShader.load("shadersGL2/AlphaTextureTileShader.vert", "shadersGL2/AlphaTextureTileShader.frag");
        renderWithMaskShader.load("shadersGL2/AlphaTexMaskShader.vert","shadersGL2/AlphaTexMaskShader.frag");
        renderWithMaskTexShader.load("shadersGL2/AlphaTexMaskShader.vert","shadersGL2/AlphaTexMaskTexShader.frag");
    }
#endif
    
}

void TXTileMask::renderTexture(bool clearFirstArg) {
    int holdExtSourceID;
    ofPtr<TXModuleBase> extSourceModule;
    float maskImageWidth;
    float maskImageHeight;
    int holdSourceID;
    int holdMaskID;
    int holdMaskType;
    float drawXAdjusted, drawYAdjusted;
    float drawWScaled, drawHScaled;
    float holdDrawPosX, holdDrawPosY;
    int   drawWidthPixels, drawHeightPixels;
    float holdScaleX, holdScaleY;
    float normLeft, normRight, normTop, normBottom;
   
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
    holdMaskType = maskType->getInt();
    if (holdMaskType == 1) {
        if (!useExternalMaskImage) {
            if (!maskImage.getTexture().isAllocated()) {
                return;
            };
        };
    };
    if ((holdMaskType == 1) && useExternalMaskImage) {
        holdMaskID = getExtImageModuleIDSlot("extMaskImageModule");
        // check for valid module & texture
        if (!parentSystem->isValidModuleID(holdMaskID)) {
            return;
        };
        if (parentSystem->allModules[holdMaskID]->getTexture() == NULL) {
            return;
        };
        maskImageWidth = parentSystem->allModules[holdMaskID]->getTextureWidth();
        maskImageHeight = parentSystem->allModules[holdMaskID]->getTextureHeight();
    } else {
        maskImageWidth = maskImage.getWidth();
        maskImageHeight = maskImage.getHeight();
    };
    // if size changed, reallocate
    if ((renderWidthHeightRule == IMAGEFXWIDTHHEIGHTRULE_SOURCEIMAGESIZE) &&((sourceImageWidth != outImage.getWidth()) || (sourceImageHeight != outImage.getHeight()))) {
        allocateTexture();
    };
    int outImageWidth = outImage.getWidth();
    int outImageHeight = outImage.getHeight();
    
    int   holdMaxWidth = getMaxWidth();
    int   holdMaxHeight = getMaxHeight();
    float holdSamplePosX = samplePosX->getFloat();
    float holdSamplePosY = samplePosY->getFloat();
    float holdSampleWidth = sampleWidth->getFloat();
    float holdSampleHeight = sampleHeight->getFloat();
    float holdNumTiles = numTiles->getFloat();
    float holdDrawWidth = drawWidth->getFloat();
    float holdDrawHeight = drawHeight->getFloat();
    float anchorXPixels, anchorYPixels;
    float fboEdgeOffsetX = 1.0f / sourceImageWidth;
    float fboEdgeOffsetY = 1.0f / sourceImageHeight;
    //    was set to higher for ipad retina
    //    float fboEdgeOffsetX = 2.0f / sourceImageWidth;
    //    float fboEdgeOffsetY = 2.0f / sourceImageHeight;
    
    float sourceImageRatioW, sourceImageRatioH;
    float sourceImageScaleX, sourceImageScaleY;
    float drawBorderX, drawBorderY;
    float scaledImageWidth, scaledImageHeight;
    float ratioOrig, ratioTarget;
    float tex0X, tex0Y, tex1X, tex1Y, tex2X, tex2Y, tex3X, tex3Y;
    float texBorderX, texBorderY;
    float texImageWidth, texImageHeight;
    float sampleWidthPixels, sampleHeightPixels;
    float sampleOffsetX, sampleOffsetY;
    
    switch (sourceImageScaleMode->getInt()) {
        case TXIMAGESCALEMODE_SCALETOFIT:
            sourceImageRatioW = (float) holdMaxWidth / sourceImageWidth;
            sourceImageRatioH = (float) holdMaxHeight / sourceImageHeight;
            sourceImageScaleX = min(sourceImageRatioW, sourceImageRatioH);
            sourceImageScaleY = sourceImageScaleX;
            scaledImageWidth = sourceImageWidth * sourceImageScaleX;
            scaledImageHeight = sourceImageHeight * sourceImageScaleY;
            drawBorderX = (holdMaxWidth - scaledImageWidth) * 0.5;
            drawBorderY = (holdMaxHeight - scaledImageHeight) * 0.5;
            texImageWidth = sourceImageWidth;
            texImageHeight = sourceImageHeight;
            texBorderX = 0;
            texBorderY = 0;
            break;
        case TXIMAGESCALEMODE_SCALETOFILL:
            scaledImageWidth = holdMaxWidth;
            scaledImageHeight = holdMaxHeight;
            drawBorderX = 0;
            drawBorderY = 0;
            ratioOrig = (float) sourceImageWidth / sourceImageHeight;
            ratioTarget = (float) holdMaxWidth / holdMaxHeight;
            if (ratioOrig > ratioTarget) {
                texImageWidth = sourceImageHeight * ratioTarget;
                texImageHeight = sourceImageHeight;
                texBorderX =  (sourceImageWidth - texImageWidth ) * 0.5;
                texBorderY = 0;
            } else {
                texImageWidth = sourceImageWidth;
                texImageHeight = sourceImageWidth / ratioTarget;
                texBorderX = 0;
                texBorderY = (sourceImageHeight - texImageHeight ) * 0.5;
            };
            break;
        case TXIMAGESCALEMODE_STRETCHTOFILL:
            scaledImageWidth = holdMaxWidth;
            scaledImageHeight = holdMaxHeight;
            drawBorderX = 0;
            drawBorderY = 0;
            texImageWidth = sourceImageWidth;
            texImageHeight = sourceImageHeight;
            texBorderX = 0;
            texBorderY = 0;
            break;
        default:
            scaledImageWidth = holdMaxWidth;
            scaledImageHeight = holdMaxHeight;
            drawBorderX = 0;
            drawBorderY = 0;
            texImageWidth = sourceImageWidth;
            texImageHeight = sourceImageHeight;
            texBorderX = 0;
            texBorderY = 0;
            break;
    };

    // open image
    outImage.begin();
    
    if (useSamplePosForRenderPos) {
        holdDrawPosX = holdSamplePosX;
        holdDrawPosY = holdSamplePosY;
    } else {
        holdDrawPosX = drawPosX->getFloat();
        holdDrawPosY = drawPosY->getFloat();
    };
    if (useSampleSizeForRenderSize) {
        drawWidthPixels = (int) (fmax(holdSampleWidth * scaledImageWidth, 1));
        drawHeightPixels = (int) (fmax(holdSampleHeight * scaledImageHeight, 1));
    } else {
        drawWidthPixels = (int) (fmax(holdDrawWidth * scaledImageWidth, 1));
        drawHeightPixels = (int) (fmax(holdDrawHeight * scaledImageHeight, 1));
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
        drawXAdjusted = holdDrawPosX * scaledImageWidth;
        drawYAdjusted = holdDrawPosY * scaledImageHeight;
    } else {
        drawWScaled = drawWidthPixels * holdScaleX;
        drawHScaled = drawHeightPixels * holdScaleY;
        drawXAdjusted = (0.5* drawWScaled) + ((scaledImageWidth - drawWScaled) * holdDrawPosX);
        drawYAdjusted = (0.5* drawHScaled) + ((scaledImageHeight - drawHScaled) * holdDrawPosY);
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
    
    // WARNING - THIS TARGET_OPENGLES CODE IS OUT OF DATE AND PROBABLY WRONG!!
    /*
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
     if (holdMaskType > 0) {
     if (holdMaskType == 1) {
     float maskWidthNextPow2Ratio = (float) maskImageWidth /ofNextPow2(maskImageWidth);
     float maskHeightNextPow2Ratio = (float) maskImageHeight /ofNextPow2(maskImageHeight);
     float maskFboEdgeOffsetX = 1.0f / maskImageWidth;
     float maskFboEdgeOffsetY = 1.0f / maskImageHeight;
     normLeft = maskFboEdgeOffsetX * maskWidthNextPow2Ratio;
     normRight = (1.0 - maskFboEdgeOffsetX) * maskWidthNextPow2Ratio;
     normTop = maskFboEdgeOffsetY * maskHeightNextPow2Ratio;
     normBottom = (1.0 - maskFboEdgeOffsetY) * maskHeightNextPow2Ratio;
     } else {
     normLeft = 0.0;
     normRight = 1.0;
     normTop = 0.0;
     normBottom = 1.0;
     };
     };
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
    if (holdMaskType > 0) {
        if (holdMaskType == 1) {
            float maskFboEdgeOffsetX = 1.0f / maskImageWidth;
            float maskFboEdgeOffsetY = 1.0f / maskImageHeight;
            normLeft = maskImageWidth * maskFboEdgeOffsetX;
            normRight = maskImageWidth * (1.0 - maskFboEdgeOffsetX);
            normTop = maskImageHeight * maskFboEdgeOffsetY;
            normBottom = maskImageHeight * (1.0 - maskFboEdgeOffsetY);
        } else {
            normLeft = 0.0;
            normRight = 1.0;
            normTop = 0.0;
            normBottom = 1.0;
        };
    };
#endif
    
    //  choose shader
    if (holdMaskType == 0) {
        holdShader = & renderShader;
    } else if (holdMaskType == 1) {
        holdShader = & renderWithMaskTexShader;
    } else {
        holdShader = & renderWithMaskShader;
    };
    //holdShader->bindDefaults();
    holdShader->begin();

    
    // if (setUniforms) {     // save time if already set before
    if (useExternalSourceImage) {
        renderShader.setUniformTexture("u_texture0Sampler", *extSourceModule->getTexture(), 0);
    } else {
        holdShader->setUniformTexture("u_texture0Sampler", sourceImage.getTexture(), 0);
    };
    holdShader->setUniform1f("u_alpha", alpha->getFloat());
    holdShader->setUniform1f("u_alphaThreshold", parentSystem->alphaThreshold);
    holdShader->setUniform1f("u_numTiles", holdNumTiles);
    if (holdNumTiles > 1.0f) {
        holdShader->setUniform1i("u_mirrorTileX", (int) mirrorTileX->getBool());
        holdShader->setUniform1i("u_mirrorTileY", (int) mirrorTileY->getBool());
        holdShader->setUniform1f("u_texXMin", tex0X);
        holdShader->setUniform1f("u_texYMin", tex0Y);
        holdShader->setUniform1f("u_texXMax", tex2X);
        holdShader->setUniform1f("u_texYMax", tex2Y);
    };
    if (holdMaskType > 0) {
        holdShader->setUniform1i("u_maskType", holdMaskType);
        holdShader->setUniform1i("u_invertMask", (int) invertMask);
        if (holdMaskType == 1) {
            if (useExternalMaskImage) {
                ofTexture * maskTex = parentSystem->allModules[holdMaskID]->getTexture();
                holdShader->setUniformTexture("u_texture1Sampler", * maskTex, 1);
            } else {
                holdShader->setUniformTexture("u_texture1Sampler", maskImage.getTexture(), 1);
            };
        } else {
            holdShader->setUniform1f("u_feathering", feathering->getFloat());
        };
    };
    // }; // end of if (setUniforms)
    
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
    if (holdMaskType > 0) {
        // NOTE - MASK TEXTURE COORDS HELD IN NORMAL(X/Y) FOR CONVENIENCE
        drawMesh.setNormal(0, ofVec3f(normLeft, normTop, 0));
        drawMesh.setNormal(1, ofVec3f(normRight, normTop, 0));
        drawMesh.setNormal(2, ofVec3f(normRight, normBottom, 0));
        drawMesh.setNormal(3, ofVec3f(normLeft, normBottom, 0));
    };
    
    // draw
    ofEnableAlphaBlending();
    drawMesh.draw();
    ofDisableAlphaBlending();
    
    ofPopMatrix();
    holdShader->end();
    
    ofClearAlpha();
    // close image
    outImage.end();
}
// end of renderTexture

void  TXTileMask::imageAssetSlotChanged(string slotNameArg) {
    if (slotNameArg == "sourceImageAsset") {
        sourceImageHasChanged = true;
    } else {
        maskImageHasChanged = true;
    };
}

void TXTileMask::loadMaskImage() {
    ofPtr <TXAsset> asset;
    string fileName;
    int maskImageAssetID = getImageAssetIDSlot("maskImageAsset").first;
    if (maskImageAssetID != 0) {
        asset = parentSystem->getAsset(TXASSETTYPE_IMAGE, maskImageAssetID);
        fileName = asset->getFileName();
        // old:
        //      maskImage.load(fileName);
        parentSystem->imageLoader.loadFromDisk(maskImage, fileName);
    };
}



