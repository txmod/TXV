/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXFindEdges.h"
#include "TXSystem.h"
#include "TXAsset.h"

// constructor
TXFindEdges::TXFindEdges() {
    setup();
}

// destructor
TXFindEdges::~TXFindEdges() {
    // remove listeners to relevent parameters:
    ofRemoveListener(showEdgeColor->parameters.parameterChangedE(),this,&TXFindEdges::showEdgeColorChanged);
}

void TXFindEdges::addExtraParameters() {
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    holdModParamBoolArgs.name = "showEdgeColor";
    holdModParamBoolArgs.fixedValue = true;
    showEdgeColor = createModParameter(holdModParamBoolArgs);
    parameters.add(showEdgeColor->parameters);

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

void TXFindEdges::addExtraListeners() {
    // add listener to relevent mod parameters:
    ofAddListener(showEdgeColor->parameters.parameterChangedE(),this,&TXFindEdges::showEdgeColorChanged);
}

bool TXFindEdges::setExtraUniforms(int sourceImageWidth, int sourceImageHeight) {
    renderShader.setUniform1i("u_blendMode", blendMode->getInt());
    renderShader.setUniform1f("u_blendMix", blendMix->getFloat());
    renderShader.setUniform1i("u_blendReverse", blendReverse->getBool());
    return true;
}

void TXFindEdges::loadRenderShader() {
    string vString = "passPosTex0.vert";
    string fString;
    if (showEdgeColor->getBool()) {
        fString = "edgeDetectionColor.fs";
    } else {
        fString = "edgeDetection.fs";
    };
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

void  TXFindEdges::showEdgeColorChanged(ofAbstractParameter & parameterArg ) {
    loadRenderShader();
}

