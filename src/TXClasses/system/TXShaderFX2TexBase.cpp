/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXShaderFX2TexBase.h"
#include "TXSystem.h"
#include "TXAsset.h"

// constructor
TXShaderFX2TexBase::TXShaderFX2TexBase() {
    setup();
}

// destructor
TXShaderFX2TexBase::~TXShaderFX2TexBase() {
}

void TXShaderFX2TexBase::addExtraImageParameters() {
    TXModParameterIntArgs holdModParamIntArgs;
    
    // asset slot
    createImageAssetSlot("sourceImage2Asset");
    
    // external image slots
    createExtImageModuleSlot("extSourceImage2Module");
    
    parameters.add(useExternalSourceImage2.set("useExternalSourceImage2", false));

    holdModParamIntArgs.name = "sourceImage2ScaleMode";
    holdModParamIntArgs.fixedValue = TXIMAGESCALEMODE_SCALETOFIT;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 2;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 2;
	sourceImage2ScaleMode = createModParameter(holdModParamIntArgs);
    parameters.add(sourceImage2ScaleMode->parameters);
}

void TXShaderFX2TexBase::addExtraParameters() {
    
    // empty for this module
    
    //    OVERRIDE IF REQUIRED
    //    TXModParameterBoolArgs holdModParamBoolArgs;
    //    TXModParameterIntArgs holdModParamIntArgs;
    //    TXModParameterFloatArgs holdModParamFloatArgs;
}

void TXShaderFX2TexBase::addExtraListeners() {
    
    // empty for this module
    
    //    OVERRIDE IF REQUIRED
}

void TXShaderFX2TexBase::loadRenderShader() {
    
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

void TXShaderFX2TexBase::extraSetupAction() {
    // NB if overriding, sub-modules should call this method as well
    
    // set up renderMesh - required for 2 tex
    renderMesh.clear();
    renderMesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    // top left
    renderMesh.addTexCoord(ofVec2f(0, 0));
    renderMesh.addVertex(ofVec3f(0, 0, 0));
    renderMesh.addColor(ofFloatColor(1, 1, 1, 1));
    renderMesh.addNormal(ofVec3f(0, 0, 0));
    // top right
    renderMesh.addTexCoord(ofVec2f(0, 0));
    renderMesh.addVertex(ofVec3f(0, 0, 0));
    renderMesh.addColor(ofFloatColor(1, 1, 1, 1));
    renderMesh.addNormal(ofVec3f(0, 0, 0));
    // bottom right
    renderMesh.addTexCoord(ofVec2f(0, 1));
    renderMesh.addVertex(ofVec3f(0, 1, 0));
    renderMesh.addColor(ofFloatColor(1, 1, 1, 1));
    renderMesh.addNormal(ofVec3f(0, 0, 0));
    // bottom left
    renderMesh.addTexCoord(ofVec2f(0, 1));
    renderMesh.addVertex(ofVec3f(0, 1, 0));
    renderMesh.addColor(ofFloatColor(1, 1, 1, 1));
    renderMesh.addNormal(ofVec3f(0, 0, 0));
}

bool TXShaderFX2TexBase::setExtraUniforms(int sourceImageWidth, int sourceImageHeight, int sourceImage2Width, int sourceImage2Height) {
    
    // Empty for this module
    
    //    EXAMPLE CODE:
    //    renderShader.setUniform1f("phase", phase->getFloat());
    
    return true;
}

//--------------------------------------------------------------

void TXShaderFX2TexBase::renderTexture(bool clearFirstArg) {
    int holdExtSourceImageID;
    ofPtr<TXModuleBase> extSourceImageModule;
    float sourceImageWidth;
    float sourceImageHeight;
    int holdExtSourceImage2ID;
    ofPtr<TXModuleBase> extSourceImage2Module;
    float sourceImage2Width;
    float sourceImage2Height;
    
    if (useExternalSourceImage) {
        holdExtSourceImageID = getExtImageModuleIDSlot("extSourceImageModule");
        
        extSourceImageModule = parentSystem->allModules[holdExtSourceImageID];
        // check for valid module & texture
        if (!parentSystem->isValidModuleID(holdExtSourceImageID)) {
            return;
        };
        if (extSourceImageModule->getTexture() == NULL) {
            return;
        };
        sourceImageWidth = extSourceImageModule->getTextureWidth();
        sourceImageHeight = extSourceImageModule->getTextureHeight();
    } else {
        if (!sourceImage.getTexture().isAllocated()) {
            return;
        };
        sourceImageWidth = sourceImage.getWidth();
        sourceImageHeight = sourceImage.getHeight();
    };
    if (useExternalSourceImage2) {
        holdExtSourceImage2ID = getExtImageModuleIDSlot("extSourceImage2Module");
        extSourceImage2Module = parentSystem->allModules[holdExtSourceImage2ID];
        // check for valid module & texture
        if (extSourceImage2Module == NULL) {
            return;
        };
        if (extSourceImage2Module->getTexture() == NULL) {
            return;
        };
        sourceImage2Width = extSourceImage2Module->getTextureWidth();
        sourceImage2Height = extSourceImage2Module->getTextureHeight();
    } else {
        if (!(sourceImage2HasLoaded && sourceImage2.isAllocated())) {
            return;
        };
        sourceImage2Width = sourceImage2.getWidth();
        sourceImage2Height = sourceImage2.getHeight();
    };
    // if size changed, reallocate
    if ((renderWidthHeightRule == IMAGEFXWIDTHHEIGHTRULE_SOURCEIMAGESIZE) &&((sourceImageWidth != outImage.getWidth()) || (sourceImageHeight != outImage.getHeight()))) {
        allocateTexture();
    };
    // draw prep
    outImage.begin();
    ofEnableAlphaBlending();
    if (clearFirstArg) {
        ofColor newColor;
        if (clearColorHSBAsRGB) {
            newColor.set (clearColorHue->getFloat() * 255, clearColorSaturation->getFloat() * 255, clearColorBrightness->getFloat() * 255, clearColorAlpha->getFloat() * 255);
        } else {
            newColor = ofColor::fromHsb(clearColorHue->getFloat() * 255, clearColorSaturation->getFloat() * 255, clearColorBrightness->getFloat() * 255, clearColorAlpha->getFloat() * 255);
        };
        ofClear(newColor);
    };
    renderShader.begin();
    // check if method is successful
    if (setExtraUniforms(sourceImageWidth, sourceImageHeight, sourceImage2Width, sourceImage2Height)) {
        if (useExternalSourceImage) {
            renderShader.setUniformTexture("u_texture0Sampler", *extSourceImageModule->getTexture(), 0);
            
        } else {
            renderShader.setUniformTexture("u_texture0Sampler", sourceImage.getTexture(), 0);
        };
        if (useExternalSourceImage2) {
            renderShader.setUniformTexture("u_texture1Sampler", *extSourceImage2Module->getTexture(), 1);
            
        } else {
            renderShader.setUniformTexture("u_texture1Sampler", sourceImage2.getTexture(), 1);
        };
        int outImageWidth = outImage.getWidth();
        int outImageHeight = outImage.getHeight();

        float sourceImageRatioW, sourceImageRatioH, sourceImage2RatioW, sourceImage2RatioH;
        float sourceImageScale, sourceImage2Scale;
        float sourceImageOffsetX, sourceImageOffsetY, sourceImage2OffsetX, sourceImage2OffsetY;
        
        switch (sourceImageScaleMode->getInt()) {
            case TXIMAGESCALEMODE_SCALETOFIT:
                sourceImageRatioW = (float) sourceImageWidth/ outImageWidth;
                sourceImageRatioH = (float) sourceImageHeight / outImageHeight;
                sourceImageScale = max(sourceImageRatioW, sourceImageRatioH);
                sourceImageOffsetX = ((outImageWidth * sourceImageScale) - sourceImageWidth )* 0.5;
                sourceImageOffsetY = ((outImageHeight * sourceImageScale) - sourceImageHeight) * 0.5;
                break;
            case TXIMAGESCALEMODE_SCALETOFILL:
                sourceImageRatioW = (float) sourceImageWidth / outImageWidth;
                sourceImageRatioH = (float) sourceImageHeight / outImageHeight;
                sourceImageScale = min(sourceImageRatioW, sourceImageRatioH);
                sourceImageOffsetX = ((outImageWidth * sourceImageScale) - sourceImageWidth )* 0.5;
                sourceImageOffsetY = ((outImageHeight * sourceImageScale) - sourceImageHeight) * 0.5;
                break;
            case TXIMAGESCALEMODE_STRETCHTOFILL:
                sourceImageOffsetX = 0;
                sourceImageOffsetY = 0;
                break;
            default:
                sourceImageOffsetX = 0;
                sourceImageOffsetY = 0;
                break;
        };
        switch (sourceImage2ScaleMode->getInt()) {
            case TXIMAGESCALEMODE_SCALETOFIT:
                 sourceImage2RatioW = (float)  sourceImage2Width/ outImageWidth;
                 sourceImage2RatioH = (float)  sourceImage2Height / outImageHeight;
                 sourceImage2Scale = max( sourceImage2RatioW,  sourceImage2RatioH);
                 sourceImage2OffsetX = ((outImageWidth *  sourceImage2Scale) -  sourceImage2Width )* 0.5;
                 sourceImage2OffsetY = ((outImageHeight *  sourceImage2Scale) -  sourceImage2Height) * 0.5;
                break;
            case TXIMAGESCALEMODE_SCALETOFILL:
                 sourceImage2RatioW = (float)  sourceImage2Width / outImageWidth;
                 sourceImage2RatioH = (float)  sourceImage2Height / outImageHeight;
                 sourceImage2Scale = min( sourceImage2RatioW,  sourceImage2RatioH);
                 sourceImage2OffsetX = ((outImageWidth *  sourceImage2Scale) -  sourceImage2Width )* 0.5;
                 sourceImage2OffsetY = ((outImageHeight *  sourceImage2Scale) -  sourceImage2Height) * 0.5;
                break;
            case TXIMAGESCALEMODE_STRETCHTOFILL:
                sourceImage2OffsetX = 0;
                sourceImage2OffsetY = 0;
                break;
            default:
                sourceImage2OffsetX = 0;
                sourceImage2OffsetY = 0;
                break;
        }        

#ifdef TARGET_OPENGLES
        // Use widthNextPow2Ratio, heightNextPow2Ratio to adjust texture coords
        float widthNextPow2Ratio = (float) outImageWidth /ofNextPow2(outImageWidth);
        float heightNextPow2Ratio = (float) outImageHeight /ofNextPow2(outImageHeight);
        float sourceImageFboEdgeOffsetX = 1.0f / sourceImageWidth;
        float sourceImageFboEdgeOffsetY = 1.0f / sourceImageHeight;
        tex1Left = sourceImageFboEdgeOffsetX * widthNextPow2Ratio;
        tex1Top = sourceImageFboEdgeOffsetY * heightNextPow2Ratio;
        tex1Right = (holdSampleWidth - sourceImageFboEdgeOffsetX) * widthNextPow2Ratio;
        tex1Bottom = (holdSampleHeight - sourceImageFboEdgeOffsetY) * heightNextPow2Ratio;

        float sourceImage2WidthNextPow2Ratio = (float) sourceImage2Width /ofNextPow2(sourceImage2Width);
        float sourceImage2HeightNextPow2Ratio = (float) sourceImage2Height /ofNextPow2(sourceImage2Height);
        float sourceImage2FboEdgeOffsetX = 1.0f / sourceImage2Width;
        float sourceImage2FboEdgeOffsetY = 1.0f / sourceImage2Height;
        tex2Left = sourceImage2FboEdgeOffsetX * sourceImage2WidthNextPow2Ratio;
        tex2Right = (1.0 - sourceImage2FboEdgeOffsetX) * sourceImage2WidthNextPow2Ratio;
        tex2Top = sourceImage2FboEdgeOffsetY * sourceImage2HeightNextPow2Ratio;
        tex2Bottom = (1.0 - sourceImage2FboEdgeOffsetY) * sourceImage2HeightNextPow2Ratio;
#else
//        float sourceImageFboEdgeOffsetX = 1.0f / sourceImageWidth;
//        float sourceImageFboEdgeOffsetY = 1.0f / sourceImageHeight;
        float sourceImageFboEdgeOffsetX = 1.0;
        float sourceImageFboEdgeOffsetY = 1.0;
        tex1Left = sourceImageFboEdgeOffsetX;
        tex1Top = sourceImageFboEdgeOffsetY;
        tex1Right = sourceImageWidth - sourceImageFboEdgeOffsetX;
        tex1Bottom = sourceImageHeight - sourceImageFboEdgeOffsetY;

//        float sourceImage2FboEdgeOffsetX = 1.0f / sourceImage2Width;
//        float sourceImage2FboEdgeOffsetY = 1.0f / sourceImage2Height;
        float sourceImage2FboEdgeOffsetX = 1.0;
        float sourceImage2FboEdgeOffsetY = 1.0;
        tex2Left = sourceImage2FboEdgeOffsetX;
        tex2Top = sourceImage2FboEdgeOffsetY;
        tex2Right = sourceImage2Width - sourceImage2FboEdgeOffsetX;
        tex2Bottom = sourceImage2Height - sourceImage2FboEdgeOffsetY;
#endif
        
        // top left
        renderMesh.setTexCoord(0, ofVec2f(tex1Left - sourceImageOffsetX, tex1Top - sourceImageOffsetY));
        renderMesh.setVertex(0, ofVec3f(0, 0, 0));
        // top right
        renderMesh.setTexCoord(1, ofVec2f(tex1Right + sourceImageOffsetX, tex1Top - sourceImageOffsetY));
        renderMesh.setVertex(1, ofVec3f(outImageWidth, 0, 0));
        // bottom right
        renderMesh.setTexCoord(2, ofVec2f(tex1Right + sourceImageOffsetX, tex1Bottom + sourceImageOffsetY));
        renderMesh.setVertex(2, ofVec3f(outImageWidth, outImageHeight, 0));
        // bottom left
        renderMesh.setTexCoord(3, ofVec2f(tex1Left - sourceImageOffsetX, tex1Bottom + sourceImageOffsetY));
        renderMesh.setVertex(3, ofVec3f(0, outImageHeight, 0));
        
        // NOTE - SECOND TEXTURE COORDS HELD IN NORMAL(X/Y) FOR CONVENIENCE
        renderMesh.setNormal(0, ofVec3f(tex2Left - sourceImage2OffsetX, tex2Top - sourceImage2OffsetY, 0));
        renderMesh.setNormal(1, ofVec3f(tex2Right + sourceImage2OffsetX, tex2Top - sourceImage2OffsetY, 0));
        renderMesh.setNormal(2, ofVec3f(tex2Right + sourceImage2OffsetX, tex2Bottom + sourceImage2OffsetY, 0));
        renderMesh.setNormal(3, ofVec3f(tex2Left - sourceImage2OffsetX, tex2Bottom + sourceImage2OffsetY, 0));
        
        // draw
        renderMesh.draw();
    };
    renderShader.end();
    ofDisableAlphaBlending();
    ofClearAlpha();
    outImage.end();
}

//--------------------------------------------------------------

bool TXShaderFX2TexBase::loadSourceImage2() {
    ofPtr <TXAsset> asset;
    string fileName;
    int sourceImage2AssetID = getImageAssetIDSlot("sourceImage2Asset").first;
    sourceImage2HasLoaded = false;
    if (sourceImage2AssetID != 0) {
        asset = parentSystem->getAsset(TXASSETTYPE_IMAGE, sourceImage2AssetID);
        fileName = asset->getFileName();
        // old:
        //        if (sourceImage2.load(fileName)) {
        //            sourceImage2HasLoaded = true;
        //        };
        parentSystem->imageLoader.loadFromDisk(sourceImage2, fileName);
        sourceImage2HasLoaded = true;
    };
    return sourceImage2HasLoaded;
}

bool TXShaderFX2TexBase::getSourceImage2HasLoaded() {
    return sourceImage2HasLoaded;
}

void  TXShaderFX2TexBase::imageAssetSlotChanged(string slotNameArg) {
    if (slotNameArg == "sourceImageAsset") {
        loadSourceImage();
    };
    if (slotNameArg == "sourceImage2Asset") {
        loadSourceImage2();
    };
}

