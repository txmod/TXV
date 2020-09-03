/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXBloom.h"
#include "TXSystem.h"
#include "TXAsset.h"

// constructor
TXBloom::TXBloom() {
    setup();
}

// destructor
TXBloom::~TXBloom() {
}


void TXBloom::addExtraParameters() {
    //  TXModParameterBoolArgs holdModParamBoolArgs;
    //  TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    holdModParamFloatArgs.name = "bloom";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    bloom = createModParameter(holdModParamFloatArgs);
    parameters.add(bloom->parameters);
    
}

void TXBloom::addExtraListeners() {
    
    // empty for this module
    
}

bool TXBloom::setExtraUniforms(int sourceImageWidth, int sourceImageHeight) {
    renderShader.setUniform1f("bloom", bloom->getFloat());
    return true;
}

void TXBloom::loadRenderShader() {
    string vString = "passPosTex0.vert";
    string fString = "bloom.frag";
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

