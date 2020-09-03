/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXBlend.h"
#include "TXSystem.h"
#include "TXAsset.h"

// constructor
TXBlend::TXBlend() {
    setup();
}

// destructor
TXBlend::~TXBlend() {
}

void TXBlend::addExtraParameters() {
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
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

void TXBlend::loadRenderShader() {
//    string vString = "AlphaBrightnessShader.vert";
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

bool TXBlend::setExtraUniforms(int sourceImageWidth, int sourceImageHeight, int sourceImage2Width, int sourceImage2Height) {    
    // for blend
    renderShader.setUniform2f("u_texdim0", (float) sourceImageWidth, (float) sourceImageHeight);
    renderShader.setUniform2f("u_texdim1", (float) sourceImage2Width, (float) sourceImage2Height);
    renderShader.setUniform1i("u_blendMode", blendMode->getInt());
    renderShader.setUniform1f("u_blendMix", blendMix->getFloat());
    renderShader.setUniform1i("u_blendReverse", blendReverse->getBool());

    return true;
}
