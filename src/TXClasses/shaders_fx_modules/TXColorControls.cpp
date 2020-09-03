/*
 *  Copyright 2014 Paul Miller. All rights reserved.
 */

#include "TXColorControls.h"
#include "TXSystem.h"
#include "TXAsset.h"

// constructor
TXColorControls::TXColorControls() {
    setup();
}

// destructor
TXColorControls::~TXColorControls() {
}

void TXColorControls::addExtraParameters() {
    TXModParameterBoolArgs holdModParamBoolArgs;
//    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    holdModParamFloatArgs.name = "brightness";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 4.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 2.0;
    brightness = createModParameter(holdModParamFloatArgs);
    parameters.add(brightness->parameters);
    
    holdModParamFloatArgs.name = "contrast";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 4.0;
    holdModParamFloatArgs.softMin = 0.25;
    holdModParamFloatArgs.softMax = 2.0;
    contrast = createModParameter(holdModParamFloatArgs);
    parameters.add(contrast->parameters);
    
    holdModParamFloatArgs.name = "contrastMidPoint";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 4.0;
    holdModParamFloatArgs.softMin = 0.25;
    holdModParamFloatArgs.softMax = 2.0;
    contrastMidPoint = createModParameter(holdModParamFloatArgs);
    parameters.add(contrastMidPoint->parameters);
    
    holdModParamFloatArgs.name = "saturation";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 4.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 2.0;
    saturation = createModParameter(holdModParamFloatArgs);
    parameters.add(saturation->parameters);
    
    holdModParamBoolArgs.name = "useHueshift";
    holdModParamBoolArgs.fixedValue = false;
    useHueshift = createModParameter(holdModParamBoolArgs);
    parameters.add(useHueshift->parameters);
    
    holdModParamFloatArgs.name = "hueshift";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    hueshift = createModParameter(holdModParamFloatArgs);
    parameters.add(hueshift->parameters);
        
    holdModParamBoolArgs.name = "invert";
    holdModParamBoolArgs.fixedValue = false;
    invert = createModParameter(holdModParamBoolArgs);
    parameters.add(invert->parameters);
    
    holdModParamFloatArgs.name = "fxMix";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    fxMix = createModParameter(holdModParamFloatArgs);
    parameters.add(fxMix->parameters);
    
}

void TXColorControls::addExtraListeners() {
    // empty for this module
}

bool TXColorControls::setExtraUniforms(int sourceImageWidth, int sourceImageHeight) {
    renderShader.setUniform1f("u_brightness", brightness->getFloat());
    renderShader.setUniform1f("u_contrast", contrast->getFloat());
    renderShader.setUniform1f("u_contrastMidPoint", contrastMidPoint->getFloat());
    renderShader.setUniform1f("u_saturation", saturation->getFloat());
    renderShader.setUniform1i("u_useHueshift", useHueshift->getBool());
    renderShader.setUniform1f("u_hueshift", hueshift->getFloat());
    renderShader.setUniform1i("u_invert", invert->getBool());
    renderShader.setUniform1f("u_fxMix", fxMix->getFloat());
    
    return true;
}

void TXColorControls::loadRenderShader() {
    string vString = "ColorControlsHueShiftInv.vert";
    string fString = "ColorControlsHueShiftInv.frag";
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

