/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXLevels.h"
#include "TXSystem.h"
#include "TXAsset.h"

// constructor
TXLevels::TXLevels() {
    setup();
}

// destructor
TXLevels::~TXLevels() {
}

void TXLevels::addExtraParameters() {
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    holdModParamIntArgs.name = "levelsMode";
    holdModParamIntArgs.fixedValue = TXLEVELSMODE_RGB;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = numLevelsModes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = numLevelsModes - 1;
	levelsMode = createModParameter(holdModParamIntArgs);
    parameters.add(levelsMode->parameters);
    
    holdModParamFloatArgs.name = "levelsMix";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    levelsMix = createModParameter(holdModParamFloatArgs);
    parameters.add(levelsMix->parameters);
    
    holdModParamFloatArgs.name = "gamma";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.1;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.1;
    holdModParamFloatArgs.softMax = 10.0;
    gamma = createModParameter(holdModParamFloatArgs);
    parameters.add(gamma->parameters);
    
    holdModParamFloatArgs.name = "inputMin";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    inputMin = createModParameter(holdModParamFloatArgs);
    parameters.add(inputMin->parameters);
    
    holdModParamFloatArgs.name = "inputMax";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    inputMax = createModParameter(holdModParamFloatArgs);
    parameters.add(inputMax->parameters);
    
    holdModParamFloatArgs.name = "outputMin";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    outputMin = createModParameter(holdModParamFloatArgs);
    parameters.add(outputMin->parameters);
    
    holdModParamFloatArgs.name = "outputMax";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    outputMax = createModParameter(holdModParamFloatArgs);
    parameters.add(outputMax->parameters);
    
    holdModParamBoolArgs.name = "posterize";
    holdModParamBoolArgs.fixedValue = false;
    posterize = createModParameter(holdModParamBoolArgs);
    parameters.add(posterize->parameters);
    
    holdModParamIntArgs.name = "posterizeSteps";
    holdModParamIntArgs.fixedValue = 3;
    holdModParamIntArgs.hardMin = 1;
    holdModParamIntArgs.hardMax = 50;
    holdModParamIntArgs.softMin = 1;
    holdModParamIntArgs.softMax = 10;
	posterizeSteps = createModParameter(holdModParamIntArgs);
    parameters.add(posterizeSteps->parameters);
    
    holdModParamFloatArgs.name = "posterizeBias";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.1;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.1;
    holdModParamFloatArgs.softMax = 10.0;
    posterizeBias = createModParameter(holdModParamFloatArgs);
    parameters.add(posterizeBias->parameters);
    
    holdModParamIntArgs.name = "channelReorder";
    holdModParamIntArgs.fixedValue = TXLEVELSCHANNELORDER_RGB;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = numChannelOrders - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = numChannelOrders - 1;
	channelReorder = createModParameter(holdModParamIntArgs);
    parameters.add(channelReorder->parameters);
    
    holdModParamFloatArgs.name = "redMultiply";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 3.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	redMultiply = createModParameter(holdModParamFloatArgs);
    parameters.add(redMultiply->parameters);
    
    holdModParamFloatArgs.name = "greenMultiply";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 3.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	greenMultiply = createModParameter(holdModParamFloatArgs);
    parameters.add(greenMultiply->parameters);
    
    holdModParamFloatArgs.name = "blueMultiply";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 3.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	blueMultiply = createModParameter(holdModParamFloatArgs);
    parameters.add(blueMultiply->parameters);
    
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

void TXLevels::addExtraListeners() {
    // empty for this module
}

bool TXLevels::setExtraUniforms(int sourceImageWidth, int sourceImageHeight) {
    renderShader.setUniform1i("u_levelsMode", levelsMode->getInt());
    renderShader.setUniform1f("u_levelsMix", levelsMix->getFloat());
    renderShader.setUniform1f("u_inputMin", inputMin->getFloat());
    renderShader.setUniform1f("u_gamma", gamma->getFloat());
    renderShader.setUniform1f("u_inputMax", max(inputMax->getFloat(), inputMin->getFloat() + 0.001f));
    renderShader.setUniform1f("u_outputMin", outputMin->getFloat());
    renderShader.setUniform1f("u_outputMax", outputMax->getFloat());
    
    renderShader.setUniform1i("u_posterize", posterize->getBool());
    renderShader.setUniform1i("u_posterizeSteps", posterizeSteps->getInt());
    renderShader.setUniform1f("u_posterizeBias", posterizeBias->getFloat());
    renderShader.setUniform1i("u_channelReorder", channelReorder->getInt());
    
    renderShader.setUniform1f("u_redMultiply", redMultiply->getFloat());
    renderShader.setUniform1f("u_greenMultiply", greenMultiply->getFloat());
    renderShader.setUniform1f("u_blueMultiply", blueMultiply->getFloat());
    renderShader.setUniform1i("u_blendMode", blendMode->getInt());
    renderShader.setUniform1f("u_blendMix", blendMix->getFloat());
    renderShader.setUniform1i("u_blendReverse", blendReverse->getBool());
    return true;
}

void TXLevels::loadRenderShader() {
    string vString = "LevelsShader.vert";
    string fString = "LevelsShader.frag";
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

