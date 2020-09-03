/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXConvolution.h"
#include "TXSystem.h"
#include "TXAsset.h"

// constructor
TXConvolution::TXConvolution() {
    setup();
}

// destructor
TXConvolution::~TXConvolution() {
}


void TXConvolution::addExtraParameters() {
    //TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    holdModParamFloatArgs.name = "mix";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    mix = createModParameter(holdModParamFloatArgs);
    parameters.add(mix->parameters);
    
    holdModParamIntArgs.name = "kernelType";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXKERNELTYPE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXKERNELTYPE_TOTAL - 1;
	kernelType = createModParameter(holdModParamIntArgs);
    parameters.add(kernelType->parameters);
    
    holdModParamFloatArgs.name = "bias";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -128.0;
    holdModParamFloatArgs.hardMax = 128.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
    bias = createModParameter(holdModParamFloatArgs);
    parameters.add(bias->parameters);
    
    holdModParamFloatArgs.name = "kernel1";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -30.0;
    holdModParamFloatArgs.hardMax = 30.0;
    holdModParamFloatArgs.softMin = -10.0;
    holdModParamFloatArgs.softMax = 10.0;
    kernel1 = createModParameter(holdModParamFloatArgs);
    parameters.add(kernel1->parameters);
    
    holdModParamFloatArgs.name = "kernel2";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -30.0;
    holdModParamFloatArgs.hardMax = 30.0;
    holdModParamFloatArgs.softMin = -10.0;
    holdModParamFloatArgs.softMax = 10.0;
    kernel2 = createModParameter(holdModParamFloatArgs);
    parameters.add(kernel2->parameters);
    
    holdModParamFloatArgs.name = "kernel3";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -30.0;
    holdModParamFloatArgs.hardMax = 30.0;
    holdModParamFloatArgs.softMin = -10.0;
    holdModParamFloatArgs.softMax = 10.0;
    kernel3 = createModParameter(holdModParamFloatArgs);
    parameters.add(kernel3->parameters);
    
    holdModParamFloatArgs.name = "kernel4";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -30.0;
    holdModParamFloatArgs.hardMax = 30.0;
    holdModParamFloatArgs.softMin = -10.0;
    holdModParamFloatArgs.softMax = 10.0;
    kernel4 = createModParameter(holdModParamFloatArgs);
    parameters.add(kernel4->parameters);
    
    holdModParamFloatArgs.name = "kernel5";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -30.0;
    holdModParamFloatArgs.hardMax = 30.0;
    holdModParamFloatArgs.softMin = -10.0;
    holdModParamFloatArgs.softMax = 10.0;
    kernel5 = createModParameter(holdModParamFloatArgs);
    parameters.add(kernel5->parameters);
    
    holdModParamFloatArgs.name = "kernel6";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -30.0;
    holdModParamFloatArgs.hardMax = 30.0;
    holdModParamFloatArgs.softMin = -10.0;
    holdModParamFloatArgs.softMax = 10.0;
    kernel6 = createModParameter(holdModParamFloatArgs);
    parameters.add(kernel6->parameters);
    
    holdModParamFloatArgs.name = "kernel7";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -30.0;
    holdModParamFloatArgs.hardMax = 30.0;
    holdModParamFloatArgs.softMin = -10.0;
    holdModParamFloatArgs.softMax = 10.0;
    kernel7 = createModParameter(holdModParamFloatArgs);
    parameters.add(kernel7->parameters);
    
    holdModParamFloatArgs.name = "kernel8";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -30.0;
    holdModParamFloatArgs.hardMax = 30.0;
    holdModParamFloatArgs.softMin = -10.0;
    holdModParamFloatArgs.softMax = 10.0;
    kernel8 = createModParameter(holdModParamFloatArgs);
    parameters.add(kernel8->parameters);

    holdModParamFloatArgs.name = "kernel9";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -30.0;
    holdModParamFloatArgs.hardMax = 30.0;
    holdModParamFloatArgs.softMin = -10.0;
    holdModParamFloatArgs.softMax = 10.0;
    kernel9 = createModParameter(holdModParamFloatArgs);
    parameters.add(kernel9->parameters);

}

void TXConvolution::addExtraListeners() {
    
    // empty for this module
    
}

bool TXConvolution::setExtraUniforms(int sourceImageWidth, int sourceImageHeight) {
    float k0, k1, k2, k3, k4, k5, k6, k7, k8;
    switch (kernelType->getInt()) {
        case TXKERNELTYPE_BLUR1:
            k0 = 0.11;
            k1 = 0.11;
            k2 = 0.11;
            k3 = 0.11;
            k4 = 0.11;
            k5 = 0.11;
            k6 = 0.11;
            k7 = 0.11;
            k8 = 0.11;
            break;
        case TXKERNELTYPE_BLUR2:
            k0 = 0.11;
            k1 = 0.11;
            k2 = 0.11;
            k3 = 0.11;
            k4 = 0.66;
            k5 = 0.11;
            k6 = 0.11;
            k7 = 0.11;
            k8 = 0.11;
            break;
        case TXKERNELTYPE_FINDEDGE1:
            k0 = -1;
            k1 = -1;
            k2 = -1;
            k3 = -1;
            k4 = 8;
            k5 = -1;
            k6 = -1;
            k7 = -1;
            k8 = -1;
            break;
        case TXKERNELTYPE_FINDEDGE2:
            k0 = -1;
            k1 = -1;
            k2 = -1;
            k3 = -1;
            k4 = 12;
            k5 = -1;
            k6 = -1;
            k7 = -1;
            k8 = -1;
            break;
        case TXKERNELTYPE_FINDVERTICALEDGE1:
            k0 = -1;
            k1 = 0;
            k2 = 1;
            k3 = -2;
            k4 = 0;
            k5 = 2;
            k6 = -1;
            k7 = 0;
            k8 = 1;
            break;
        case TXKERNELTYPE_FINDVERTICALEDGE2:
            k0 = -1;
            k1 = 0;
            k2 = 1;
            k3 = -3;
            k4 = 0;
            k5 = 2;
            k6 = -1;
            k7 = 0;
            k8 = 1;
            break;
        case TXKERNELTYPE_FINDHORIZONTALEDGE1:
            k0 = -1;
            k1 = -2;
            k2 = -1;
            k3 = 0;
            k4 = 0;
            k5 = 0;
            k6 = 1;
            k7 = 2;
            k8 = 1;
            break;
        case TXKERNELTYPE_FINDHORIZONTALEDGE2:
            k0 = -1;
            k1 = -2;
            k2 = -1;
            k3 = 0;
            k4 = 0;
            k5 = 0;
            k6 = 2;
            k7 = 3;
            k8 = 2;
            break;
        case TXKERNELTYPE_SHARPEN1:
            k0 = 0;
            k1 = -1;
            k2 = 0;
            k3 = -1;
            k4 = 4;
            k5 = -1;
            k6 = 0;
            k7 = -1;
            k8 = 0;
            break;
        case TXKERNELTYPE_SHARPEN2:
            k0 = 0;
            k1 = -1;
            k2 = 0;
            k3 = -1;
            k4 = 5;
            k5 = -1;
            k6 = 0;
            k7 = -1;
            k8 = 0;
            break;
        case TXKERNELTYPE_SHARPEN3:
            k0 = 0;
            k1 = -1;
            k2 = 0;
            k3 = -1;
            k4 = 6;
            k5 = -1;
            k6 = 0;
            k7 = -1;
            k8 = 0;
            break;
        case TXKERNELTYPE_EMBOSS1:
            k0 = -2;
            k1 = -2;
            k2 = 0;
            k3 = -2;
            k4 = 6;
            k5 = 0;
            k6 = 0;
            k7 = 0;
            k8 = 0;
            break;
        case TXKERNELTYPE_EMBOSS2:
            k0 = -2;
            k1 = -1;
            k2 = 0;
            k3 = -1;
            k4 = 1;
            k5 = 1;
            k6 = 0;
            k7 = 1;
            k8 = 2;
            break;
        case TXKERNELTYPE_CUSTOMISE:
            k0 = kernel1->getFloat();
            k1 = kernel2->getFloat();
            k2 = kernel3->getFloat();
            k3 = kernel4->getFloat();
            k4 = kernel5->getFloat();
            k5 = kernel6->getFloat();
            k6 = kernel7->getFloat();
            k7 = kernel8->getFloat();
            k8 = kernel9->getFloat();
            break;
        default:
            k0 = 0;
            k1 = 0;
            k2 = 0;
            k3 = 0;
            k4 = 1;
            k5 = 0;
            k6 = 0;
            k7 = 0;
            k8 = 0;
            break;
    }
    float holdBias = bias->getFloat();

    renderShader.setUniform1f("mix", mix->getFloat());
    renderShader.setUniform1f("kernel0", k0 + holdBias);
    renderShader.setUniform1f("kernel1", k1 + holdBias);
    renderShader.setUniform1f("kernel2", k2 + holdBias);
    renderShader.setUniform1f("kernel3", k3 + holdBias);
    renderShader.setUniform1f("kernel4", k4 + holdBias);
    renderShader.setUniform1f("kernel5", k5 + holdBias);
    renderShader.setUniform1f("kernel6", k6 + holdBias);
    renderShader.setUniform1f("kernel7", k7 + holdBias);
    renderShader.setUniform1f("kernel8", k8 + holdBias);
    return true;
}

void TXConvolution::loadRenderShader() {
    string vString = "passPosTex0.vert";
    string fString = "convolution.fs";
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

