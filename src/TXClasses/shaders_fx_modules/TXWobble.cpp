/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXWobble.h"
#include "TXSystem.h"
#include "TXAsset.h"

// constructor
TXWobble::TXWobble() {
    setup();
}

// destructor
TXWobble::~TXWobble() {
}


void TXWobble::addExtraParameters() {
    //    TXModParameterBoolArgs holdModParamBoolArgs;
    //    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    holdModParamFloatArgs.name = "phase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    phase = createModParameter(holdModParamFloatArgs);
    parameters.add(phase->parameters);
    
    holdModParamFloatArgs.name = "freqX";
    holdModParamFloatArgs.fixedValue = 20.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 100.0;
    freqX = createModParameter(holdModParamFloatArgs);
    parameters.add(freqX->parameters);
    
    holdModParamFloatArgs.name = "freqY";
    holdModParamFloatArgs.fixedValue = 20.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 100.0;
    freqY = createModParameter(holdModParamFloatArgs);
    parameters.add(freqY->parameters);
    
    holdModParamFloatArgs.name = "ampX";
    holdModParamFloatArgs.fixedValue = 20.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 100.0;
    ampX = createModParameter(holdModParamFloatArgs);
    parameters.add(ampX->parameters);
    
    holdModParamFloatArgs.name = "ampY";
    holdModParamFloatArgs.fixedValue = 20.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 100.0;
    ampY = createModParameter(holdModParamFloatArgs);
    parameters.add(ampY->parameters);
    
}

void TXWobble::addExtraListeners() {
    
    // empty for this module
    
}

bool TXWobble::setExtraUniforms(int sourceImageWidth, int sourceImageHeight) {
    renderShader.setUniform1f("phase", phase->getFloat());
    renderShader.setUniform2f("freq", freqX->getFloat()/sourceImageWidth, freqY->getFloat()/sourceImageHeight);
    renderShader.setUniform2f("amp", ampX->getFloat(), ampY->getFloat());
    return true;
}

void TXWobble::loadRenderShader() {
    string vString = "passPosTex0.vert";
    string fString = "Wobble_GLSL.frag";
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

