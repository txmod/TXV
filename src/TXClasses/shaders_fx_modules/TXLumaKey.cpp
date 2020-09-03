/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXLumaKey.h"
#include "TXSystem.h"
#include "TXAsset.h"

// constructor
TXLumaKey::TXLumaKey() {
    setup();
}

// destructor
TXLumaKey::~TXLumaKey() {
}


void TXLumaKey::addExtraParameters() {
    TXModParameterBoolArgs holdModParamBoolArgs;
//    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    holdModParamFloatArgs.name = "luma";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	luma = createModParameter(holdModParamFloatArgs);
    parameters.add(luma->parameters);
    
    holdModParamFloatArgs.name = "tolerance";
    holdModParamFloatArgs.fixedValue = 0.02;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	tolerance = createModParameter(holdModParamFloatArgs);
    parameters.add(tolerance->parameters);
    
    holdModParamFloatArgs.name = "fade";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	fade = createModParameter(holdModParamFloatArgs);
    parameters.add(fade->parameters);
    
    holdModParamBoolArgs.name = "showSourceImage2";
    holdModParamBoolArgs.fixedValue = true;
    showSourceImage2 = createModParameter(holdModParamBoolArgs);
    parameters.add(showSourceImage2->parameters);
    
    holdModParamBoolArgs.name = "invert";
    holdModParamBoolArgs.fixedValue = false;
    invert = createModParameter(holdModParamBoolArgs);
    parameters.add(invert->parameters);
    
    holdModParamBoolArgs.name = "maskMode";
    holdModParamBoolArgs.fixedValue = false;
    maskMode = createModParameter(holdModParamBoolArgs);
    parameters.add(maskMode->parameters);
}

void TXLumaKey::loadRenderShader() {
    string vString = "_ShaderGroups/FXShaders2Tex/LumaKey.vert";
    string fString = "_ShaderGroups/FXShaders2Tex/LumaKey.frag";
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

bool TXLumaKey::setExtraUniforms(int sourceImageWidth, int sourceImageHeight, int sourceImage2Width, int sourceImage2Height) {    
    renderShader.setUniform2f("u_texdim0", (float) sourceImageWidth, (float) sourceImageHeight);
    renderShader.setUniform2f("u_texdim1", (float) sourceImage2Width, (float) sourceImage2Height);
    renderShader.setUniform1f("luma", luma->getFloat());
    renderShader.setUniform1f("tolerance", tolerance->getFloat());
    renderShader.setUniform1f("fade", fade->getFloat());
    renderShader.setUniform1i("invert", invert->getBool());
    renderShader.setUniform1i("maskMode", maskMode->getBool());
    renderShader.setUniform1i("showSourceImage2", showSourceImage2->getBool());

    return true;
}

