/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXSoftThreshold.h"
#include "TXSystem.h"
#include "TXAsset.h"

// constructor
TXSoftThreshold::TXSoftThreshold() {
    setup();
}

// destructor
TXSoftThreshold::~TXSoftThreshold() {
}


void TXSoftThreshold::addExtraParameters() {
    TXModParameterBoolArgs holdModParamBoolArgs;
    //    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    holdModParamFloatArgs.name = "softEdge";
    holdModParamFloatArgs.fixedValue = 0.001;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    softEdge = createModParameter(holdModParamFloatArgs);
    parameters.add(softEdge->parameters);
    
    holdModParamFloatArgs.name = "threshold";
    holdModParamFloatArgs.fixedValue = 0.3;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    threshold = createModParameter(holdModParamFloatArgs);
    parameters.add(threshold->parameters);
    
    holdModParamBoolArgs.name = "invert";
    holdModParamBoolArgs.fixedValue = false;
    invert = createModParameter(holdModParamBoolArgs);
    parameters.add(invert->parameters);
    
    holdModParamBoolArgs.name = "maskMode";
    holdModParamBoolArgs.fixedValue = false;
    maskMode = createModParameter(holdModParamBoolArgs);
    parameters.add(maskMode->parameters);
}

void TXSoftThreshold::addExtraListeners() {
    
    // empty for this module
    
}

bool TXSoftThreshold::setExtraUniforms(int sourceImageWidth, int sourceImageHeight) {
    renderShader.setUniform1f("softEdge", softEdge->getFloat());
    renderShader.setUniform1f("threshold", threshold->getFloat());
    renderShader.setUniform1i("invert", (int)  invert->getBool());
    renderShader.setUniform1i("maskMode", (int)  maskMode->getBool());
    return true;
}

void TXSoftThreshold::loadRenderShader() {
    string vString = "passPosTex0.vert";
    string fString = "softThreshold.fs";
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

