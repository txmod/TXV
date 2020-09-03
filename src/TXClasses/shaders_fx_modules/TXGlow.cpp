/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXGlow.h"
#include "TXSystem.h"
#include "TXAsset.h"

// constructor
TXGlow::TXGlow() {
    setup();
}

// destructor
TXGlow::~TXGlow() {
}


void TXGlow::addExtraParameters() {
    //  TXModParameterBoolArgs holdModParamBoolArgs;
    //  TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    holdModParamFloatArgs.name = "glow";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    glow = createModParameter(holdModParamFloatArgs);
    parameters.add(glow->parameters);
    
}

void TXGlow::addExtraListeners() {
    
    // empty for this module
    
}

bool TXGlow::setExtraUniforms(int sourceImageWidth, int sourceImageHeight) {
    renderShader.setUniform1f("glow", glow->getFloat());
    return true;
}

void TXGlow::loadRenderShader() {
    string vString = "passPosTex0.vert";
    string fString = "glow.fs";
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

