/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXSlideShow.h"
#include "TXSystem.h"
#include "TXAsset.h"
#include "ofxTweenLite.h"

// constructor
TXSlideShow::TXSlideShow() {
    setup();
}

// destructor
TXSlideShow::~TXSlideShow() {
    // remove listeners to relevent parameters:
    ofRemoveListener(xFadeType->parameters.parameterChangedE(),this,&TXSlideShow::xFadeTypeChanged);
}

void TXSlideShow::addExtraParameters() {
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    parameters.add(folderName.set("folderName", ""));

    holdModParamBoolArgs.name = "randomiseOrder";
    holdModParamBoolArgs.fixedValue = false;
    randomiseOrder = createModParameter(holdModParamBoolArgs);
    parameters.add(randomiseOrder->parameters);
    
    holdModParamFloatArgs.name = "holdTimeFixed";
    holdModParamFloatArgs.fixedValue = 3.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.1;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 0.1;
    holdModParamFloatArgs.softMax = 10.0;
    holdTimeFixed = createModParameter(holdModParamFloatArgs);
    parameters.add(holdTimeFixed->parameters);
    
    holdModParamFloatArgs.name = "holdTimeRandom";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
    holdTimeRandom = createModParameter(holdModParamFloatArgs);
    parameters.add(holdTimeRandom->parameters);
    
    holdModParamIntArgs.name = "xFadeType";
    holdModParamIntArgs.fixedValue = TXSLIDERXFADETYPE_SINE_INOUT;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = numXFadeTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = numXFadeTypes - 1;
    xFadeType = createModParameter(holdModParamIntArgs);
    parameters.add(xFadeType->parameters);
    
    holdModParamFloatArgs.name = "xFadeTimeFixed";
    holdModParamFloatArgs.fixedValue = 3.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.1;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 0.1;
    holdModParamFloatArgs.softMax = 10.0;
    xFadeTimeFixed = createModParameter(holdModParamFloatArgs);
    parameters.add(xFadeTimeFixed->parameters);
    
    holdModParamFloatArgs.name = "xFadeTimeRandom";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
    xFadeTimeRandom = createModParameter(holdModParamFloatArgs);
    parameters.add(xFadeTimeRandom->parameters);
    
    holdModParamBoolArgs.name = "runSlideShow";
    holdModParamBoolArgs.fixedValue = false;
    runSlideShow = createModParameter(holdModParamBoolArgs);
    parameters.add(runSlideShow->parameters);
    
    holdModParamBoolArgs.name = "pauseSlideShow";
    holdModParamBoolArgs.fixedValue = false;
    pauseSlideShow = createModParameter(holdModParamBoolArgs);
    parameters.add(pauseSlideShow->parameters);
    
    holdModParamBoolArgs.name = "triggerXFadeForwards";
    holdModParamBoolArgs.fixedValue = false;
    triggerXFadeForwards = createModParameter(holdModParamBoolArgs);
    parameters.add(triggerXFadeForwards->parameters);
    
    holdModParamBoolArgs.name = "triggerXFadeBackwards";
    holdModParamBoolArgs.fixedValue = false;
    triggerXFadeBackwards = createModParameter(holdModParamBoolArgs);
    parameters.add(triggerXFadeBackwards->parameters);
    
    holdModParamBoolArgs.name = "triggerXFadeToRandom";
    holdModParamBoolArgs.fixedValue = false;
    triggerXFadeToRandom = createModParameter(holdModParamBoolArgs);
    parameters.add(triggerXFadeToRandom->parameters);
    
    holdModParamBoolArgs.name = "jumpToFirstImage";
    holdModParamBoolArgs.fixedValue = false;
    jumpToFirstImage = createModParameter(holdModParamBoolArgs);
    parameters.add(jumpToFirstImage->parameters);
    
    holdModParamBoolArgs.name = "jumpToNextImage";
    holdModParamBoolArgs.fixedValue = false;
    jumpToNextImage = createModParameter(holdModParamBoolArgs);
    parameters.add(jumpToNextImage->parameters);
    
    holdModParamBoolArgs.name = "jumpToPreviousImage";
    holdModParamBoolArgs.fixedValue = false;
    jumpToPreviousImage = createModParameter(holdModParamBoolArgs);
    parameters.add(jumpToPreviousImage->parameters);
    
    holdModParamBoolArgs.name = "jumpToRandomImage";
    holdModParamBoolArgs.fixedValue = false;
    jumpToRandomImage = createModParameter(holdModParamBoolArgs);
    parameters.add(jumpToRandomImage->parameters);
    
    // add listener to relevent parameters:
    folderName.addListener(this, &TXSlideShow::folderNameChanged);
    
    ofAddListener(xFadeType->parameters.parameterChangedE(),this,&TXSlideShow::xFadeTypeChanged);
}

void TXSlideShow::extraSetupAction() {
    // call superclass method
    TXShaderFX2TexBase::extraSetupAction();
    
    // init
    sourceImage.allocate(640, 480, OF_IMAGE_COLOR_ALPHA);
    sourceImage2.allocate(640, 480, OF_IMAGE_COLOR_ALPHA);
    sourceImage3.allocate(640, 480, OF_IMAGE_COLOR_ALPHA);
    sourceImage4.allocate(640, 480, OF_IMAGE_COLOR_ALPHA);
    nextImageIndex = 0;
    previousImageIndex = 0;
    canUseLoader = false;
    validDir = false;
    oldTriggerXFadeForwards = false;
    oldTriggerXFadeBackwards = false;
    oldTriggerXFadeToRandom = false;
    oldJumpToFirstImage = false;
    oldJumpToNextImage = false;
    oldJumpToPreviousImage = false;
    oldJumpToRandomImage = false;
    holdModeIsActive = false;
    xFadeModeIsActive = false;
    reverseXFade = false;
    holdPeriod = 3.0;
    xFadePeriod = 3.0;
    holdTimer = 0.0;
    xFadeTimer = 0.0;
    blendMix = 0.0;
    blendMixEased = 0.0;
    blendImage1 = &sourceImage;
    blendImage2 = &sourceImage2;
    nextImage = &sourceImage3;
    previousImage = &sourceImage4;
    sourceImageScaleMode->setFixedValue(1); // "scale & crop to fill"
}

void TXSlideShow::loadRenderShader() {
    string vString = "passPosTex0Norm0.vert";
    string fString = "BlendTextureShader.frag";
#ifdef TARGET_OPENGLES
	renderShader.load("shadersES2/" + vString,"shadersES2/" + fString);
#else
	if(ofIsGLProgrammableRenderer()){
        renderShader.load("shadersGL3/" + vString,"shadersGL3/" + fString);
	}else{
        renderShader.load("shadersGL2/" + vString,"shadersGL2/" + fString);
	}
#endif
}

bool TXSlideShow::setExtraUniforms(int sourceImageWidth, int sourceImageHeight, int sourceImage2Width, int sourceImage2Height) {
    // for blend
    renderShader.setUniform2f("u_texdim0", (float) sourceImageWidth, (float) sourceImageHeight);
    renderShader.setUniform2f("u_texdim1", (float) sourceImage2Width, (float) sourceImage2Height);
    renderShader.setUniform1i("u_blendMode", 0);  // mix blend mode
    renderShader.setUniform1f("u_blendMix", blendMixEased);
    renderShader.setUniform1i("u_blendReverse", 0);

    return true;
}

//--------------------------------------------------------------

// listener methods

void  TXSlideShow::folderNameChanged(string & stringArg) {
    openFolder();
}

void  TXSlideShow::xFadeTypeChanged(ofAbstractParameter & dummyParameterArg ) {
    blendMixEased = ofxTweenLite::tween (0.0, 1.0, blendMix, (ofEaseFunction) (xFadeTypeOffset + xFadeType->getInt()));
}

//--------------------------------------------------------------

void TXSlideShow::setBlendMix(float blendMixArg) {
    blendMix = blendMixArg;
    blendMixEased = ofxTweenLite::tween (0.0, 1.0, blendMix, (ofEaseFunction) (xFadeTypeOffset + xFadeType->getInt()));
}

//--------------------------------------------------------------

// modified version of TXShaderFX2TexBase::renderTexture:

void TXSlideShow::renderTexture(bool clearFirstArg) {
    float sourceImageWidth;
    float sourceImageHeight;
    float sourceImage2Width;
    float sourceImage2Height;
    if (!(blendImage1->isAllocated() && blendImage2->isAllocated())) {
        return;
    };
    sourceImageWidth = blendImage1->getWidth();
    sourceImageHeight = blendImage1->getHeight();
    sourceImage2Width = blendImage2->getWidth();
    sourceImage2Height = blendImage2->getHeight();
    // if size changed, reallocate
    if ((renderWidthHeightRule == IMAGEFXWIDTHHEIGHTRULE_SOURCEIMAGESIZE) && ((sourceImageWidth != outImage.getWidth()) || (sourceImageHeight != outImage.getHeight()))) {
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
    if (validDir) {
        renderShader.begin();
        // check if method is successful
        if (setExtraUniforms(sourceImageWidth, sourceImageHeight, sourceImage2Width, sourceImage2Height)) {
            renderShader.setUniformTexture("u_texture0Sampler", blendImage1->getTexture(), 0);
            renderShader.setUniformTexture("u_texture1Sampler", blendImage2->getTexture(), 1);
            
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
            switch (sourceImageScaleMode->getInt()) {  // NOTE: this module ignores sourceImage2ScaleMode
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
    };
    ofDisableAlphaBlending();
    ofClearAlpha();
    outImage.end();
}

//--------------------------------------------------------------

void TXSlideShow::advanceBy(float timeDeltaArg) {
    bool holdRunSlideShow = runSlideShow->getBool();
    bool holdJumpToFirstImage = jumpToFirstImage->getBool();
    bool holdJumpToNextImage = jumpToNextImage->getBool();
    bool holdJumpToPreviousImage = jumpToPreviousImage->getBool();
    bool holdJumpToRandomImage = jumpToRandomImage->getBool();
    bool holdTriggerXFadeForwards = triggerXFadeForwards->getBool();
    bool holdTriggerXFadeBackwards = triggerXFadeBackwards->getBool();
    bool holdTriggerXFadeToRandom = triggerXFadeToRandom->getBool();
    bool holdRandomiseOrder = randomiseOrder->getBool();
    bool holdpauseSlideShow = pauseSlideShow->getBool();
    if (validDir) {
        // check switches
        if (holdRunSlideShow) {
            // if not running, start slide show with XFade
            if ((holdModeIsActive == false) && (xFadeModeIsActive == false)) {
                if (blendMix == 1.0) {
                    rotateToNextImage();
                };
                startXFade();
            };
        };
        if (holdJumpToFirstImage && (oldJumpToFirstImage == false)) {
            loadFirstImage(false);
        } else if (holdJumpToNextImage && (oldJumpToNextImage == false)) {
            rotateToNextImage();
        } else if (holdJumpToPreviousImage && (oldJumpToPreviousImage == false)) {
            rotateToPreviousImage();
        } else if (holdJumpToRandomImage && (oldJumpToRandomImage == false)) {
            loadRandomImage();
        };
        if (holdTriggerXFadeForwards && (oldTriggerXFadeForwards == false)) {
            if (blendMix == 1.0) {
                rotateToNextImage();
            };
            startXFade();
        } else if (holdTriggerXFadeBackwards && (oldTriggerXFadeBackwards == false)) {
            if (blendMix == 0.0) {
                rotateToPreviousImage();
            };
            startXFade(true);
        } else if (holdTriggerXFadeToRandom && (oldTriggerXFadeToRandom == false)) {
            if (blendMix == 1.0) {
                rotateToNextImage(getRandomIndex());
            };
            startXFade();
        };
        // advance timer & trigger next step
        if (!holdpauseSlideShow && (holdRunSlideShow || xFadeModeIsActive)) {
            if (xFadeModeIsActive) {
                xFadeTimer+= timeDeltaArg;
                // load new image if end of xFadePeriod
                if (xFadeTimer >= xFadePeriod) {
                    xFadeModeIsActive = false;
                    //xFadeTimer = 0.0;
                    // check random
                    if (holdRandomiseOrder) {
                        randomiseNextImageIndex();
                    };
                    if (reverseXFade) {
                        rotateToPreviousImage();
                        setBlendMix(1.0);
                    } else {
                        rotateToNextImage();
                        setBlendMix(0.0);
                    };
                    if (holdRunSlideShow) {
                        startHoldPeriod();
                    };
                } else {
                    if (reverseXFade) {
                        setBlendMix(1.0 - (xFadeTimer / xFadePeriod));
                    } else {
                        setBlendMix(xFadeTimer / xFadePeriod);
                    };
                };
            } else if (holdModeIsActive) {
                holdTimer+= timeDeltaArg;
                // check for end of holdPeriod
                if (holdTimer >= holdPeriod) {
                    startXFade();
                };
            };
        };
    };
    oldRunSlideShow = holdRunSlideShow;
    oldTriggerXFadeForwards = holdTriggerXFadeForwards;
    oldTriggerXFadeBackwards = holdTriggerXFadeBackwards;
    oldTriggerXFadeToRandom = holdTriggerXFadeToRandom;
    oldJumpToFirstImage = holdJumpToFirstImage;
    oldJumpToNextImage = holdJumpToNextImage;
    oldJumpToPreviousImage = holdJumpToPreviousImage;
    oldJumpToRandomImage = holdJumpToRandomImage;
}

//--------------------------------------------------------------

void  TXSlideShow::startXFade(bool reverseArg) {
    if (validDir) {
        xFadePeriod = xFadeTimeFixed->getFloat() + ofRandom(xFadeTimeRandom->getFloat());
        xFadeModeIsActive = true;
        holdModeIsActive = false;
        reverseXFade = reverseArg;
        xFadeTimer = 0.0;
        if (reverseXFade) {
            setBlendMix(1.0);
        } else {
            setBlendMix(0.0);
        };
    };
}

void  TXSlideShow::startHoldPeriod() {
    if (validDir) {
        holdPeriod = holdTimeFixed->getFloat() + ofRandom(holdTimeRandom->getFloat());
        holdModeIsActive = true;
        xFadeModeIsActive = false;
        reverseXFade = false;
        holdTimer = 0.0;
    };
}

//--------------------------------------------------------------

//void  TXSlideShow::clearImages() {
//    sourceImage.clear();
//    sourceImage2.clear();
//    sourceImage3.clear();
//    sourceImage3.clear();
//}

void  TXSlideShow::openFolder() {
    string holdFolderName = folderName;
    validDir = false;
    if ((holdFolderName == "") || (holdFolderName == " ")) {
        clearTexture();
        return;
    };
    dir.allowExt("png");
    dir.allowExt("jpg");
    dir.allowExt("jpeg");
    dir.allowExt("gif");
    dir.allowExt("tif");
    dir.allowExt("tiff");
    dir.listDir(folderName);
    dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order
    if (!(dir.exists() && dir.isDirectory())) {
        clearTexture();
        return;
    };
    
    // at least 3 photos needed for slideshow
    if( dir.size() > 2){
        validDir = true;
        loadFirstImage(randomiseOrder->getBool());
    };
    // clear output image
    clearTexture();
}


void  TXSlideShow::incrementImageIndices() {
    if (validDir) {
        nextImageIndex++;
        nextImageIndex %= dir.size();
        previousImageIndex++;
        previousImageIndex %= dir.size();
    };
}

void  TXSlideShow::decrementImageIndices() {
    if (validDir) {
        nextImageIndex--;
        if (nextImageIndex < 0) {
            nextImageIndex = dir.size() - 1;
        };
        previousImageIndex--;
        if (previousImageIndex < 0) {
            previousImageIndex = dir.size() - 1;
        };
    };
}

void  TXSlideShow::randomiseNextImageIndex() {
    if (validDir) {
        nextImageIndex = (int) (0.5 + getRandomIndex());
    };
}

int TXSlideShow::getRandomIndex() {
    int outVal;
    if (validDir) {
        outVal = ofRandom(dir.size() - 1);
    } else {
        outVal = 0;
    };
    return outVal;
}

void  TXSlideShow::loadFirstImage(bool randomiseArg) {
    if (validDir) {
        canUseLoader = false;
        blendImage1 = &sourceImage;
        blendImage2 = &sourceImage2;
        nextImage = &sourceImage3;
        previousImage = &sourceImage4;
        if (randomiseArg) {
            loadRandomImage();
        } else {
            if (blendMix == 1.0) {
                loadBlendImage1(1);
                loadBlendImage2(0);
            } else {
                loadBlendImage1(0);
                loadBlendImage2(1);
            };
            loadNextImage(2);
            loadPreviousImage(dir.size() - 1);
            nextImageIndex = 2;
            previousImageIndex = dir.size() - 1;
        };
        holdTimer = 0.0;
        xFadeTimer = 0.0;
        setBlendMix(0.0);
        canUseLoader = true;
    };
}

void  TXSlideShow::loadBlendImage1(int indexArg) {
    ofImage * tempImage;
    if (validDir) {
        if (!canUseLoader) {
            blendImage1->load(dir.getPath(indexArg));  // use loader instead
        } else {
            parentSystem->imageLoader.loadFromDisk(*blendImage1, dir.getPath(indexArg));
        };
    };
}

void  TXSlideShow::loadBlendImage2(int indexArg) {
    ofImage * tempImage;
    if (validDir) {
        if (!canUseLoader) {
            blendImage2->load(dir.getPath(indexArg));  // use loader instead
        } else {
            parentSystem->imageLoader.loadFromDisk(*blendImage2, dir.getPath(indexArg));
        };
    };
}

void  TXSlideShow::loadNextImage(int indexArg) {
    ofImage * tempImage;
    if (validDir) {
        nextImageIndex = indexArg;
        if (!canUseLoader) {
            nextImage->load(dir.getPath(nextImageIndex));  // use loader instead
        } else {
            parentSystem->imageLoader.loadFromDisk(*nextImage, dir.getPath(nextImageIndex));
        };
    };
}

void  TXSlideShow::loadPreviousImage(int indexArg) {
    ofImage * tempImage;
    if (validDir) {
        previousImageIndex = indexArg;
        if (!canUseLoader) {
            previousImage->load(dir.getPath(previousImageIndex));  // use loader instead
        } else {
            parentSystem->imageLoader.loadFromDisk(*previousImage, dir.getPath(previousImageIndex));
        };
    };
}

void  TXSlideShow::rotateToNextImage(int nextIndexOptionalArg) {
    ofImage * tempImage;
    if (validDir) {
        // rotate images forwards
        tempImage = previousImage;
        previousImage = blendImage1;
        blendImage1 = blendImage2;
        blendImage2 = nextImage;
        nextImage = tempImage;
        if (nextIndexOptionalArg != -1) {
            loadBlendImage2(nextIndexOptionalArg);
        };
        incrementImageIndices();
        loadNextImage(nextImageIndex);
        setBlendMix(0.0);
    };
}

void  TXSlideShow::rotateToPreviousImage() {
    ofImage * tempImage;
    int holdNextImageIndex;
    if (validDir) {
        // rotate images backwards
        tempImage = nextImage;
        nextImage = blendImage2;
        blendImage2 = blendImage1;
        blendImage1 = previousImage;
        previousImage = tempImage;
        decrementImageIndices();
        // previousImage->load(dir.getPath(previousImageIndex));
        parentSystem->imageLoader.loadFromDisk(*previousImage, dir.getPath(previousImageIndex));
        holdTimer = 0.0;
        xFadeTimer = 0.0;
        setBlendMix(0.0);
    };
}

void TXSlideShow::loadRandomImage() {
    int holdIndex, ind1, ind2;
    holdIndex = getRandomIndex();
    previousImageIndex = holdIndex;
    holdIndex++;
    holdIndex %= dir.size();
    ind1 = holdIndex;
    holdIndex++;
    holdIndex %= dir.size();
    ind2 = holdIndex;
    holdIndex++;
    holdIndex %= dir.size();
    nextImageIndex = holdIndex;
    if (blendMix == 1.0) {
        loadBlendImage1(ind2);
        loadBlendImage2(ind1);
    } else {
        loadBlendImage1(ind1);
        loadBlendImage2(ind2);
    };
    loadNextImage(nextImageIndex);
    loadPreviousImage(previousImageIndex);
}

