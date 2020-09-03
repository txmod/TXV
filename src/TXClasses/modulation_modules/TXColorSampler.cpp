/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXColorSampler.h"
#include "TXSystem.h"
#include "TXAsset.h"

// constructor
TXColorSampler::TXColorSampler() {
    setup();
}

// destructor
TXColorSampler::~TXColorSampler() {
    // remove listeners to relevent mod parameters:
    ofRemoveListener(color1SmoothTime->parameters.parameterChangedE(),this,&TXColorSampler::color1SmoothTimeChanged);
    ofRemoveListener(color2SmoothTime->parameters.parameterChangedE(),this,&TXColorSampler::color2SmoothTimeChanged);
    ofRemoveListener(color3SmoothTime->parameters.parameterChangedE(),this,&TXColorSampler::color3SmoothTimeChanged);
    ofRemoveListener(color4SmoothTime->parameters.parameterChangedE(),this,&TXColorSampler::color4SmoothTimeChanged);
}

void TXColorSampler::setup(){
    TXModParameterBoolArgs holdModParamBoolArgs;
//    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
    
    parameters.add(useExternalSourceImage.set("useExternalSourceImage", false));

    holdModParamBoolArgs.name = "sample1Active";
    holdModParamBoolArgs.fixedValue = true;
	sample1Active = createModParameter(holdModParamBoolArgs);
    parameters.add(sample1Active->parameters);
    
    holdModParamFloatArgs.name = "sample1PosX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	sample1PosX = createModParameter(holdModParamFloatArgs);
    parameters.add(sample1PosX->parameters);
    
    holdModParamFloatArgs.name = "sample1PosY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	sample1PosY = createModParameter(holdModParamFloatArgs);
    parameters.add(sample1PosY->parameters);
    
    holdModParamFloatArgs.name = "color1SmoothTime";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 60.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 2.0;
    color1SmoothTime = createModParameter(holdModParamFloatArgs);
    parameters.add(color1SmoothTime->parameters);
    
    holdModParamBoolArgs.name = "sample2Active";
    holdModParamBoolArgs.fixedValue = true;
	sample2Active = createModParameter(holdModParamBoolArgs);
    parameters.add(sample2Active->parameters);
    
    holdModParamFloatArgs.name = "sample2PosX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	sample2PosX = createModParameter(holdModParamFloatArgs);
    parameters.add(sample2PosX->parameters);
    
    holdModParamFloatArgs.name = "sample2PosY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	sample2PosY = createModParameter(holdModParamFloatArgs);
    parameters.add(sample2PosY->parameters);
    
    holdModParamFloatArgs.name = "color2SmoothTime";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 60.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 2.0;
    color2SmoothTime = createModParameter(holdModParamFloatArgs);
    parameters.add(color2SmoothTime->parameters);
    
    holdModParamBoolArgs.name = "sample3Active";
    holdModParamBoolArgs.fixedValue = true;
	sample3Active = createModParameter(holdModParamBoolArgs);
    parameters.add(sample3Active->parameters);
    
    holdModParamFloatArgs.name = "sample3PosX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	sample3PosX = createModParameter(holdModParamFloatArgs);
    parameters.add(sample3PosX->parameters);
    
    holdModParamFloatArgs.name = "sample3PosY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	sample3PosY = createModParameter(holdModParamFloatArgs);
    parameters.add(sample3PosY->parameters);
    
    holdModParamFloatArgs.name = "color3SmoothTime";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 60.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 2.0;
    color3SmoothTime = createModParameter(holdModParamFloatArgs);
    parameters.add(color3SmoothTime->parameters);
    
    holdModParamBoolArgs.name = "sample4Active";
    holdModParamBoolArgs.fixedValue = true;
	sample4Active = createModParameter(holdModParamBoolArgs);
    parameters.add(sample4Active->parameters);
    
    holdModParamFloatArgs.name = "sample4PosX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	sample4PosX = createModParameter(holdModParamFloatArgs);
    parameters.add(sample4PosX->parameters);
    
    holdModParamFloatArgs.name = "sample4PosY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	sample4PosY = createModParameter(holdModParamFloatArgs);
    parameters.add(sample4PosY->parameters);
    
    holdModParamFloatArgs.name = "color4SmoothTime";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 60.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 2.0;
    color4SmoothTime = createModParameter(holdModParamFloatArgs);
    parameters.add(color4SmoothTime->parameters);
    
    // create mod source outputs
    color1Red = createModSource("color1Red", 0);
    color1Green = createModSource("color1Green", 0);
    color1Blue = createModSource("color1Blue", 0);
    color1Hue = createModSource("color1Hue", 0);
    color1Saturation = createModSource("color1Saturation", 0);
    color1Brightness = createModSource("color1Brightness", 0);
    color1Alpha = createModSource("color1Alpha", 0);
    
    color2Red = createModSource("color2Red", 0);
    color2Green = createModSource("color2Green", 0);
    color2Blue = createModSource("color2Blue", 0);
    color2Hue = createModSource("color2Hue", 0);
    color2Saturation = createModSource("color2Saturation", 0);
    color2Brightness = createModSource("color2Brightness", 0);
    color2Alpha = createModSource("color2Alpha", 0);
    
    color3Red = createModSource("color3Red", 0);
    color3Green = createModSource("color3Green", 0);
    color3Blue = createModSource("color3Blue", 0);
    color3Hue = createModSource("color3Hue", 0);
    color3Saturation = createModSource("color3Saturation", 0);
    color3Brightness = createModSource("color3Brightness", 0);
    color3Alpha = createModSource("color3Alpha", 0);
    
    color4Red = createModSource("color4Red", 0);
    color4Green = createModSource("color4Green", 0);
    color4Blue = createModSource("color4Blue", 0);
    color4Hue = createModSource("color4Hue", 0);
    color4Saturation = createModSource("color4Saturation", 0);
    color4Brightness = createModSource("color4Brightness", 0);
    color4Alpha = createModSource("color4Alpha", 0);
    
    // add listener to relevent mod parameters:
    ofAddListener(color1SmoothTime->parameters.parameterChangedE(),this,&TXColorSampler::color1SmoothTimeChanged);
    ofAddListener(color2SmoothTime->parameters.parameterChangedE(),this,&TXColorSampler::color2SmoothTimeChanged);
    ofAddListener(color3SmoothTime->parameters.parameterChangedE(),this,&TXColorSampler::color3SmoothTimeChanged);
    ofAddListener(color4SmoothTime->parameters.parameterChangedE(),this,&TXColorSampler::color4SmoothTimeChanged);

    // asset slot
    createImageAssetSlot("sourceImageAsset");
    
    // external image slot
    createExtImageModuleSlot("extSourceImageModule");
    
    // initialise
    sourceImageHasLoaded = false;
}

void TXColorSampler::update(){
    // check if valid input image before updating
    if (useExternalSourceImage) {
        int holdSourceID = getExtImageModuleIDSlot("extSourceImageModule");
        if (!parentSystem->isValidModuleID(holdSourceID)) {
            return;
        };
        if (holdSourceID == 0) {
            return;
        } else {
            if (parentSystem->allModules[holdSourceID]->getTexture() == NULL) {
                return;
            };
        };
    } else {
        if (!sourceImageHasLoaded) {
            return;
        };
    };
    updateOutputs();
}

void TXColorSampler::updateOutputs() {
    ofPixels pix;
    int holdPosX, holdPosY;
    float hue, saturation, brightness;
    float scaleRatio = 1.0f / 255.0;
    ofColor color1;
    ofColor color2;
    ofColor color3;
    ofColor color4;
    ofColor smoothColor1;
    ofColor smoothColor2;
    ofColor smoothColor3;
    ofColor smoothColor4;
    float currentTime = parentSystem->getCurrentTime();
    
    if (useExternalSourceImage) {
        int holdSourceID = getExtImageModuleIDSlot("extSourceImageModule");
        pix = parentSystem->allModules[holdSourceID]->getPixels();
    } else {
        pix = sourceImage.getPixels();
    };
    
    // sample color at each point if active
    if (sample1Active->getBool()) {
        holdPosX = (int) (sample1PosX->getFloat() * (pix.getWidth() - 1));
        holdPosY = (int) (sample1PosY->getFloat() * (pix.getHeight() - 1));
        color1 = pix.getColor(holdPosX, holdPosY);
        
        smoothColor1R.setTargetValue(color1.r);
        smoothColor1G.setTargetValue(color1.g);
        smoothColor1B.setTargetValue(color1.b);
        smoothColor1A.setTargetValue(color1.a);
        smoothColor1R.setTime(currentTime);
        smoothColor1G.setTime(currentTime);
        smoothColor1B.setTime(currentTime);
        smoothColor1A.setTime(currentTime);
        smoothColor1.set(smoothColor1R.outValue, smoothColor1G.outValue, smoothColor1B.outValue, smoothColor1A.outValue);
        
        color1Red->setValue(smoothColor1.g * scaleRatio);
        color1Green->setValue(smoothColor1.g * scaleRatio);
        color1Blue->setValue(smoothColor1.b * scaleRatio);
        smoothColor1.getHsb(hue, saturation, brightness);
        color1Hue->setValue(hue * scaleRatio);
        color1Saturation->setValue(saturation * scaleRatio);
        color1Brightness->setValue(brightness * scaleRatio);
        color1Alpha->setValue(smoothColor1.a * scaleRatio);
        
    };
    if (sample2Active->getBool()) {
        holdPosX = (int) (sample2PosX->getFloat() * (pix.getWidth() - 1));
        holdPosY = (int) (sample2PosY->getFloat() * (pix.getHeight() - 1));
        color2 = pix.getColor(holdPosX, holdPosY);
        
        smoothColor2R.setTargetValue(color2.r);
        smoothColor2G.setTargetValue(color2.g);
        smoothColor2B.setTargetValue(color2.b);
        smoothColor2A.setTargetValue(color2.a);
        smoothColor2R.setTime(currentTime);
        smoothColor2G.setTime(currentTime);
        smoothColor2B.setTime(currentTime);
        smoothColor2A.setTime(currentTime);
        smoothColor2.set(smoothColor2R.outValue, smoothColor2G.outValue, smoothColor2B.outValue, smoothColor2A.outValue);
        
        color2Red->setValue(smoothColor2.r * scaleRatio);
        color2Green->setValue(smoothColor2.g * scaleRatio);
        color2Blue->setValue(smoothColor2.b * scaleRatio);
        smoothColor2.getHsb(hue, saturation, brightness);
        color2Hue->setValue(hue * scaleRatio);
        color2Saturation->setValue(saturation * scaleRatio);
        color2Brightness->setValue(brightness * scaleRatio);
        color2Alpha->setValue(smoothColor2.a);
    };
    if (sample3Active->getBool()) {
        holdPosX = (int) (sample3PosX->getFloat() * (pix.getWidth() - 1));
        holdPosY = (int) (sample3PosY->getFloat() * (pix.getHeight() - 1));
        color3 = pix.getColor(holdPosX, holdPosY);
        
        smoothColor3R.setTargetValue(color3.r);
        smoothColor3G.setTargetValue(color3.g);
        smoothColor3B.setTargetValue(color3.b);
        smoothColor3A.setTargetValue(color3.a);
        smoothColor3R.setTime(currentTime);
        smoothColor3G.setTime(currentTime);
        smoothColor3B.setTime(currentTime);
        smoothColor3A.setTime(currentTime);
        smoothColor3.set(smoothColor3R.outValue, smoothColor3G.outValue, smoothColor3B.outValue, smoothColor3A.outValue);
        
        color3Red->setValue(smoothColor3.r * scaleRatio);
        color3Green->setValue(smoothColor3.g * scaleRatio);
        color3Blue->setValue(smoothColor3.b * scaleRatio);
        smoothColor3.getHsb(hue, saturation, brightness);
        color3Hue->setValue(hue * scaleRatio);
        color3Saturation->setValue(saturation * scaleRatio);
        color3Brightness->setValue(brightness * scaleRatio);
        color3Alpha->setValue(smoothColor3.a);
    };
    if (sample4Active->getBool()) {
        holdPosX = (int) (sample4PosX->getFloat() * (pix.getWidth() - 1));
        holdPosY = (int) (sample4PosY->getFloat() * (pix.getHeight() - 1));
        color4 = pix.getColor(holdPosX, holdPosY);
        
        smoothColor4R.setTargetValue(color4.r);
        smoothColor4G.setTargetValue(color4.g);
        smoothColor4B.setTargetValue(color4.b);
        smoothColor4A.setTargetValue(color4.a);
        smoothColor4R.setTime(currentTime);
        smoothColor4G.setTime(currentTime);
        smoothColor4B.setTime(currentTime);
        smoothColor4A.setTime(currentTime);
        smoothColor4.set(smoothColor4R.outValue, smoothColor4G.outValue, smoothColor4B.outValue, smoothColor4A.outValue);
        
        color4Red->setValue(smoothColor4.r * scaleRatio);
        color4Green->setValue(smoothColor4.g * scaleRatio);
        color4Blue->setValue(smoothColor4.b * scaleRatio);
        smoothColor4.getHsb(hue, saturation, brightness);
        color4Hue->setValue(hue * scaleRatio);
        color4Saturation->setValue(saturation * scaleRatio);
        color4Brightness->setValue(brightness * scaleRatio);
        color4Alpha->setValue(smoothColor4.a);
    };
}

void  TXColorSampler::imageAssetSlotChanged(string slotNameArg) {
    if (slotNameArg == "sourceImageAsset") {
        loadSourceImage();
    };
}

bool TXColorSampler::loadSourceImage() {
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

bool TXColorSampler::getSourceImageHasLoaded() {
    return sourceImageHasLoaded;
}

void  TXColorSampler::color1SmoothTimeChanged(ofAbstractParameter & parameterArg ) {
    float holdSmoothTime = color1SmoothTime->getFloat();
    smoothColor1R.setSmoothTime(holdSmoothTime);
    smoothColor1G.setSmoothTime(holdSmoothTime);
    smoothColor1B.setSmoothTime(holdSmoothTime);
    smoothColor1A.setSmoothTime(holdSmoothTime);
}

void  TXColorSampler::color2SmoothTimeChanged(ofAbstractParameter & parameterArg ) {
    float holdSmoothTime = color2SmoothTime->getFloat();
    smoothColor2R.setSmoothTime(holdSmoothTime);
    smoothColor2G.setSmoothTime(holdSmoothTime);
    smoothColor2B.setSmoothTime(holdSmoothTime);
    smoothColor2A.setSmoothTime(holdSmoothTime);
}

void  TXColorSampler::color3SmoothTimeChanged(ofAbstractParameter & parameterArg ) {
    float holdSmoothTime = color3SmoothTime->getFloat();
    smoothColor3R.setSmoothTime(holdSmoothTime);
    smoothColor3G.setSmoothTime(holdSmoothTime);
    smoothColor3B.setSmoothTime(holdSmoothTime);
    smoothColor3A.setSmoothTime(holdSmoothTime);
}

void  TXColorSampler::color4SmoothTimeChanged(ofAbstractParameter & parameterArg ) {
    float holdSmoothTime = color4SmoothTime->getFloat();
    smoothColor4R.setSmoothTime(holdSmoothTime);
    smoothColor4G.setSmoothTime(holdSmoothTime);
    smoothColor4B.setSmoothTime(holdSmoothTime);
    smoothColor4A.setSmoothTime(holdSmoothTime);
}


