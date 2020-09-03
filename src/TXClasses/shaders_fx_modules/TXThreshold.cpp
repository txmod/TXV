/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXThreshold.h"
#include "TXSystem.h"
#include "TXAsset.h"

// constructor
TXThreshold::TXThreshold() {
    setup();
}

// destruTXThresholdtor
TXThreshold::~TXThreshold() {
}

void TXThreshold::addExtraParameters() {
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    holdModParamFloatArgs.name = "threshold";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    threshold = createModParameter(holdModParamFloatArgs);
    parameters.add(threshold->parameters);
    
    holdModParamFloatArgs.name = "aboveColorHue";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    aboveColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(aboveColorHue->parameters);
    
    holdModParamFloatArgs.name = "aboveColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    aboveColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(aboveColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "aboveColorBrightness";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    aboveColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(aboveColorBrightness->parameters);
    
    holdModParamFloatArgs.name = "aboveColorAlpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    aboveColorAlpha = createModParameter(holdModParamFloatArgs);
    parameters.add(aboveColorAlpha->parameters);
    
    holdModParamFloatArgs.name = "belowColorHue";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    belowColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(belowColorHue->parameters);
    
    holdModParamFloatArgs.name = "belowColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    belowColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(belowColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "belowColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    belowColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(belowColorBrightness->parameters);
    
    holdModParamFloatArgs.name = "belowColorAlpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    belowColorAlpha = createModParameter(holdModParamFloatArgs);
    parameters.add(belowColorAlpha->parameters);
    
    holdModParamBoolArgs.name = "useSampledAboveColor";
    holdModParamBoolArgs.fixedValue = false;
    useSampledAboveColor = createModParameter(holdModParamBoolArgs);
    parameters.add(useSampledAboveColor->parameters);
    
    holdModParamBoolArgs.name = "useSampledBelowColor";
    holdModParamBoolArgs.fixedValue = false;
    useSampledBelowColor = createModParameter(holdModParamBoolArgs);
    parameters.add(useSampledBelowColor->parameters);
    
    holdModParamFloatArgs.name = "aboveSamplePosX";
    holdModParamFloatArgs.fixedValue = 0.75;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    aboveSamplePosX = createModParameter(holdModParamFloatArgs);
    parameters.add(aboveSamplePosX->parameters);
    
    holdModParamFloatArgs.name = "aboveSamplePosY";
    holdModParamFloatArgs.fixedValue = 0.75;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    aboveSamplePosY = createModParameter(holdModParamFloatArgs);
    parameters.add(aboveSamplePosY->parameters);
    
    holdModParamFloatArgs.name = "belowSamplePosX";
    holdModParamFloatArgs.fixedValue = 0.25;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    belowSamplePosX = createModParameter(holdModParamFloatArgs);
    parameters.add(belowSamplePosX->parameters);
    
    holdModParamFloatArgs.name = "belowSamplePosY";
    holdModParamFloatArgs.fixedValue = 0.25;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    belowSamplePosY = createModParameter(holdModParamFloatArgs);
    parameters.add(belowSamplePosY->parameters);
    
    holdModParamBoolArgs.name = "swapColors";
    holdModParamBoolArgs.fixedValue = false;
    swapColors = createModParameter(holdModParamBoolArgs);
    parameters.add(swapColors->parameters);

    holdModParamIntArgs.name = "blendMode";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = numBlendModes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = numBlendModes - 1;
	blendMode = createModParameter(holdModParamIntArgs);
    parameters.add(blendMode->parameters);
    
    holdModParamFloatArgs.name = "blendMix";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	blendMix = createModParameter(holdModParamFloatArgs);
    parameters.add(blendMix->parameters);
    
    holdModParamBoolArgs.name = "blendReverse";
    holdModParamBoolArgs.fixedValue = false;
    blendReverse = createModParameter(holdModParamBoolArgs);
    parameters.add(blendReverse->parameters);
}

void TXThreshold::addExtraListeners() {
    // empty for this module
}

bool TXThreshold::setExtraUniforms(int sourceImageWidth, int sourceImageHeight) {
    ofColor belowColor = ofColor::fromHsb(belowColorHue->getFloat() * 255, belowColorSaturation->getFloat() * 255, belowColorBrightness->getFloat() * 255, belowColorAlpha->getFloat() * 255);
    ofColor aboveColor = ofColor::fromHsb(aboveColorHue->getFloat() * 255, aboveColorSaturation->getFloat() * 255, aboveColorBrightness->getFloat() * 255, aboveColorAlpha->getFloat() * 255);

    renderShader.setUniform1f("threshold", threshold->getFloat());
    renderShader.setUniform1i("useSampledAboveColor", (int) useSampledAboveColor->getBool());
    renderShader.setUniform1i("useSampledBelowColor", (int) useSampledBelowColor->getBool());
    if (swapColors->getBool()){
        renderShader.setUniform4f("aboveColor", belowColor.r/255.0f, belowColor.g/255.0f, belowColor.b/255.0f, belowColor.a/255.0f);
        renderShader.setUniform4f("belowColor", aboveColor.r/255.0f, aboveColor.g/255.0f, aboveColor.b/255.0f, aboveColor.a/255.0f);
        renderShader.setUniform2f("aboveSamplePos", sourceImageWidth * belowSamplePosX->getFloat(), sourceImageHeight *  belowSamplePosY->getFloat());
        renderShader.setUniform2f("belowSamplePos", sourceImageWidth * aboveSamplePosX->getFloat(), sourceImageHeight * aboveSamplePosY->getFloat());
    } else {
        renderShader.setUniform4f("aboveColor", aboveColor.r/255.0f, aboveColor.g/255.0f, aboveColor.b/255.0f, aboveColor.a/255.0f);
        renderShader.setUniform4f("belowColor", belowColor.r/255.0f, belowColor.g/255.0f, belowColor.b/255.0f, belowColor.a/255.0f);
        renderShader.setUniform2f("aboveSamplePos", sourceImageWidth * aboveSamplePosX->getFloat(), sourceImageHeight *  aboveSamplePosY->getFloat());
        renderShader.setUniform2f("belowSamplePos", sourceImageWidth * belowSamplePosX->getFloat(), sourceImageHeight *  belowSamplePosY->getFloat());
    };
    renderShader.setUniform1i("u_blendMode", blendMode->getInt());
    renderShader.setUniform1f("u_blendMix", blendMix->getFloat());
    renderShader.setUniform1i("u_blendReverse", blendReverse->getBool());
    return true;
}

void TXThreshold::loadRenderShader() {
    string vString = "passPosTex0.vert";
    string fString = "threshold.frag";

#ifdef TARGET_OPENGLES
	renderShader.load("shadersES2/_ShaderGroups/FXShaders1Tex/" + vString,"shadersES2/_ShaderGroups/FXShaders1Tex/" + fString);
#else
	if(ofIsGLProgrammableRenderer()){
        renderShader.load("shadersGL3/_ShaderGroups/FXShaders1Tex/" + vString,"shadersGL3/_ShaderGroups/FXShaders1Tex/" + fString);
	}else{
        renderShader.load("shadersGL2/_ShaderGroups/FXShaders1Tex/" + vString,"shadersGL2/_ShaderGroups/FXShaders1Tex/" + fString);
	}
#endif
}



