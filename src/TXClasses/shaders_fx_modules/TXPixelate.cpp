/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXPixelate.h"
#include "TXSystem.h"
#include "TXAsset.h"

// constructor
TXPixelate::TXPixelate() {
    setup();
}

// destructor
TXPixelate::~TXPixelate() {
}


void TXPixelate::addExtraParameters() {
//    TXModParameterBoolArgs holdModParamBoolArgs;
    //    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    holdModParamFloatArgs.name = "pixelWidth";
    holdModParamFloatArgs.fixedValue = 10.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 1.0;
    holdModParamFloatArgs.softMax = 100.0;
    pixelWidth = createModParameter(holdModParamFloatArgs);
    parameters.add(pixelWidth->parameters);

    holdModParamFloatArgs.name = "pixelHeight";
    holdModParamFloatArgs.fixedValue = 10.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 1.0;
    holdModParamFloatArgs.softMax = 100.0;
    pixelHeight = createModParameter(holdModParamFloatArgs);
    parameters.add(pixelHeight->parameters);
    
    parameters.add(usePixelWidthForHeight.set("usePixelWidthForHeight", false));

    holdModParamFloatArgs.name = "mix";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    mix = createModParameter(holdModParamFloatArgs);
    parameters.add(mix->parameters);
    
}

void TXPixelate::addExtraListeners() {
    
    // empty for this module
    
}

bool TXPixelate::setExtraUniforms(int sourceImageWidth, int sourceImageHeight) {
    float holdPixelWidth, holdPixelHeight;
    holdPixelWidth = pixelWidth->getFloat();
    if (usePixelWidthForHeight) {
        holdPixelHeight = holdPixelWidth;
    } else {
        holdPixelHeight = pixelHeight->getFloat();
    };
    renderShader.setUniform1f("pixelWidth", holdPixelWidth);
    renderShader.setUniform1f("pixelHeight", holdPixelHeight);
    renderShader.setUniform1f("dryWetMix", mix->getFloat());
    return true;
}

void TXPixelate::loadRenderShader() {
    string vString = "passPosTex0.vert";
    string fString = "pixelate.fs";
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

