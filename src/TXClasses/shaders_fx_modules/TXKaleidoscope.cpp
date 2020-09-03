/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXKaleidoscope.h"
#include "TXSystem.h"
#include "TXAsset.h"

// constructor
TXKaleidoscope::TXKaleidoscope() {
    setup();
}

// destructor
TXKaleidoscope::~TXKaleidoscope() {
}


void TXKaleidoscope::addExtraParameters() {
    TXModParameterBoolArgs holdModParamBoolArgs;
    //  TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    holdModParamFloatArgs.name = "numSections";
    holdModParamFloatArgs.fixedValue = 6.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 2.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = 2.0;
    holdModParamFloatArgs.softMax = 10.0;
    numSections = createModParameter(holdModParamFloatArgs);
    parameters.add(numSections->parameters);
    
    holdModParamBoolArgs.name = "quantizeSections";
    holdModParamBoolArgs.fixedValue = false;
    quantizeSections = createModParameter(holdModParamBoolArgs);
    parameters.add(quantizeSections->parameters);
    
    holdModParamFloatArgs.name = "rotationOffset";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    rotationOffset = createModParameter(holdModParamFloatArgs);
    parameters.add(rotationOffset->parameters);
    
}

void TXKaleidoscope::addExtraListeners() {
    
    // empty for this module
    
}

bool TXKaleidoscope::setExtraUniforms(int sourceImageWidth, int sourceImageHeight) {
    if (quantizeSections->getBool()) {
        renderShader.setUniform1f("u_numSections", lrintf (numSections->getFloat()));
    } else {
        renderShader.setUniform1f("u_numSections", numSections->getFloat());
    };
    renderShader.setUniform1f("u_rotationOffset", rotationOffset->getFloat());
    renderShader.setUniform2f("u_texdim0", (float) sourceImageWidth, (float) sourceImageHeight);
    return true;
}

void TXKaleidoscope::loadRenderShader() {
    string vString = "passPosTex0.vert";
    string fString = "kaleido.frag";
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

