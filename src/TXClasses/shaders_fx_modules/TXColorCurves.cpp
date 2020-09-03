/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXColorCurves.h"
#include "TXSystem.h"
#include "TXAsset.h"

// constructor
TXColorCurves::TXColorCurves() {
    setup();
}

// destructor
TXColorCurves::~TXColorCurves() {
    // remove listeners to relevent mod parameters:
    ofRemoveListener(redCurve1.parameters.parameterChangedE(),this,&TXColorCurves::redCurveChanged);
    ofRemoveListener(greenCurve1.parameters.parameterChangedE(),this,&TXColorCurves::greenCurveChanged);
    ofRemoveListener(blueCurve1.parameters.parameterChangedE(),this,&TXColorCurves::blueCurveChanged);
    ofRemoveListener(redCurve2.parameters.parameterChangedE(),this,&TXColorCurves::redCurveChanged);
    ofRemoveListener(greenCurve2.parameters.parameterChangedE(),this,&TXColorCurves::greenCurveChanged);
    ofRemoveListener(blueCurve2.parameters.parameterChangedE(),this,&TXColorCurves::blueCurveChanged);
    ofRemoveListener(hueCurve1.parameters.parameterChangedE(),this,&TXColorCurves::hueCurveChanged);
    ofRemoveListener(saturationCurve1.parameters.parameterChangedE(),this,&TXColorCurves::saturationCurveChanged);
    ofRemoveListener(luminosityCurve1.parameters.parameterChangedE(),this,&TXColorCurves::luminosityCurveChanged);
    ofRemoveListener(hueCurve2.parameters.parameterChangedE(),this,&TXColorCurves::hueCurveChanged);
    ofRemoveListener(saturationCurve2.parameters.parameterChangedE(),this,&TXColorCurves::saturationCurveChanged);
    ofRemoveListener(luminosityCurve2.parameters.parameterChangedE(),this,&TXColorCurves::luminosityCurveChanged);
}

void TXColorCurves::addExtraParameters() {
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    holdModParamIntArgs.name = "curvesMode";
    holdModParamIntArgs.fixedValue = TXCOLORRGBHSLCHANNELMODE_RGB;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORRGBHSLCHANNELMODE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORRGBHSLCHANNELMODE_TOTAL - 1;
	curvesMode = createModParameter(holdModParamIntArgs);
    parameters.add(curvesMode->parameters);
    
    holdModParamFloatArgs.name = "curvesMix";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    curvesMix = createModParameter(holdModParamFloatArgs);
    parameters.add(curvesMix->parameters);
    
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
    
    redCurve1.setValueArrayToRamp(0, 1);
    redCurve1.setName("redCurve1");
    parameters.add(redCurve1.parameters);
    
    redCurve2.setValueArrayToRamp(0, 1);
    redCurve2.setName("redCurve2");
    parameters.add(redCurve2.parameters);
    
    holdModParamFloatArgs.name = "redCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    redCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(redCurveMorph->parameters);
    
    greenCurve1.setValueArrayToRamp(0, 1);
    greenCurve1.setName("greenCurve1");
    parameters.add(greenCurve1.parameters);
    
    greenCurve2.setValueArrayToRamp(0, 1);
    greenCurve2.setName("greenCurve2");
    parameters.add(greenCurve2.parameters);
    
    holdModParamFloatArgs.name = "greenCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    greenCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(greenCurveMorph->parameters);
    
    blueCurve1.setValueArrayToRamp(0, 1);
    blueCurve1.setName("blueCurve1");
    parameters.add(blueCurve1.parameters);
    
    blueCurve2.setValueArrayToRamp(0, 1);
    blueCurve2.setName("blueCurve2");
    parameters.add(blueCurve2.parameters);
    
    holdModParamFloatArgs.name = "blueCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    blueCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(blueCurveMorph->parameters);
    
    holdModParamBoolArgs.name = "useRedCurveForGreen";
    holdModParamBoolArgs.fixedValue = false;
    useRedCurveForGreen = createModParameter(holdModParamBoolArgs);
    parameters.add(useRedCurveForGreen->parameters);
    
    holdModParamBoolArgs.name = "useRedCurveForBlue";
    holdModParamBoolArgs.fixedValue = false;
    useRedCurveForBlue = createModParameter(holdModParamBoolArgs);
    parameters.add(useRedCurveForBlue->parameters);
    
    hueCurve1.setValueArrayToRamp(0, 1);
    hueCurve1.setName("hueCurve1");
    parameters.add(hueCurve1.parameters);
    
    hueCurve2.setValueArrayToRamp(0, 1);
    hueCurve2.setName("hueCurve2");
    parameters.add(hueCurve2.parameters);
    
    holdModParamFloatArgs.name = "hueCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    hueCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(hueCurveMorph->parameters);
    
    saturationCurve1.setValueArrayToRamp(0, 1);
    saturationCurve1.setName("saturationCurve1");
    parameters.add(saturationCurve1.parameters);
    
    saturationCurve2.setValueArrayToRamp(0, 1);
    saturationCurve2.setName("saturationCurve2");
    parameters.add(saturationCurve2.parameters);
    
    holdModParamFloatArgs.name = "saturationCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    saturationCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(saturationCurveMorph->parameters);
    
    luminosityCurve1.setValueArrayToRamp(0, 1);
    luminosityCurve1.setName("luminosityCurve1");
    parameters.add(luminosityCurve1.parameters);
    
    luminosityCurve2.setValueArrayToRamp(0, 1);
    luminosityCurve2.setName("luminosityCurve2");
    parameters.add(luminosityCurve2.parameters);
    
    holdModParamFloatArgs.name = "luminosityCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    luminosityCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(luminosityCurveMorph->parameters);
    
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
    holdModParamIntArgs.fixedValue = TXCOLORRGBCHANNELORDER_RGB;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORRGBCHANNELORDER_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORRGBCHANNELORDER_TOTAL - 1;
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
    
    // add listener to relevent mod parameters:
    ofAddListener(redCurve1.parameters.parameterChangedE(),this,&TXColorCurves::redCurveChanged);
    ofAddListener(greenCurve1.parameters.parameterChangedE(),this,&TXColorCurves::greenCurveChanged);
    ofAddListener(blueCurve1.parameters.parameterChangedE(),this,&TXColorCurves::blueCurveChanged);
    ofAddListener(redCurve2.parameters.parameterChangedE(),this,&TXColorCurves::redCurveChanged);
    ofAddListener(greenCurve2.parameters.parameterChangedE(),this,&TXColorCurves::greenCurveChanged);
    ofAddListener(blueCurve2.parameters.parameterChangedE(),this,&TXColorCurves::blueCurveChanged);
    ofAddListener(hueCurve1.parameters.parameterChangedE(),this,&TXColorCurves::hueCurveChanged);
    ofAddListener(saturationCurve1.parameters.parameterChangedE(),this,&TXColorCurves::saturationCurveChanged);
    ofAddListener(luminosityCurve1.parameters.parameterChangedE(),this,&TXColorCurves::luminosityCurveChanged);
    ofAddListener(hueCurve2.parameters.parameterChangedE(),this,&TXColorCurves::hueCurveChanged);
    ofAddListener(saturationCurve2.parameters.parameterChangedE(),this,&TXColorCurves::saturationCurveChanged);
    ofAddListener(luminosityCurve2.parameters.parameterChangedE(),this,&TXColorCurves::luminosityCurveChanged);

    // init
    curvesImageSetup();
    curvesImageHasChanged = false;
    curvesHSLImageHasChanged = false;
}

void TXColorCurves::addExtraListeners() {
    // empty for this module
}

bool TXColorCurves::setExtraUniforms(int sourceImageWidth, int sourceImageHeight) {
    if (curvesImageHasChanged) {
        updateCurvesImagePixels();
        curvesImageHasChanged = false;
    };
    if (curvesHSLImageHasChanged) {
        updateCurvesHSLImagePixels();
        curvesHSLImageHasChanged = false;
    };
    int hold_curvesMode = curvesMode->getInt();
    if (hold_curvesMode >= TXCOLORRGBHSLCHANNELMODE_HSL) {
        renderShader.setUniformTexture("u_curveSampler", curvesHSLImage.getTexture(), 1);
        renderShader.setUniform1f("u_redCurveMorph", hueCurveMorph->getFloat());
        renderShader.setUniform1f("u_greenCurveMorph", saturationCurveMorph->getFloat());
        renderShader.setUniform1f("u_blueCurveMorph", luminosityCurveMorph->getFloat());
    } else {
        renderShader.setUniformTexture("u_curveSampler", curvesImage.getTexture(), 1);
        renderShader.setUniform1f("u_redCurveMorph", redCurveMorph->getFloat());
        renderShader.setUniform1f("u_greenCurveMorph", greenCurveMorph->getFloat());
        renderShader.setUniform1f("u_blueCurveMorph", blueCurveMorph->getFloat());
    };

    renderShader.setUniform1i("u_curvesMode", hold_curvesMode);
    renderShader.setUniform1f("u_curvesMix", curvesMix->getFloat());
    renderShader.setUniform1f("u_inputMin", inputMin->getFloat());
    renderShader.setUniform1f("u_inputMax", max(inputMax->getFloat(), inputMin->getFloat() + 0.001f));
    renderShader.setUniform1f("u_outputMin", outputMin->getFloat());
    renderShader.setUniform1f("u_outputMax", outputMax->getFloat());
    renderShader.setUniform1i("u_useRedCurveForGreen", useRedCurveForGreen->getBool());
    renderShader.setUniform1i("u_useRedCurveForBlue", useRedCurveForBlue->getBool());
    
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

void TXColorCurves::loadRenderShader() {
    string vString = "ColorCurvesShader.vert";
    string fString = "ColorCurvesShader.frag";
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

void TXColorCurves::curvesImageSetup() {
    curvesImage.allocate(512, 1, OF_IMAGE_COLOR_ALPHA);
    curvesHSLImage.allocate(512, 1, OF_IMAGE_COLOR_ALPHA);
}

void  TXColorCurves::redCurveChanged(ofAbstractParameter & parameterArg ) {
    curvesImageHasChanged = true;
}

void  TXColorCurves::greenCurveChanged(ofAbstractParameter & parameterArg ) {
    curvesImageHasChanged = true;
}

void  TXColorCurves::blueCurveChanged(ofAbstractParameter & parameterArg ) {
    curvesImageHasChanged = true;
}

void  TXColorCurves::hueCurveChanged(ofAbstractParameter & parameterArg ) {
    curvesHSLImageHasChanged = true;
}

void  TXColorCurves::saturationCurveChanged(ofAbstractParameter & parameterArg ) {
    curvesHSLImageHasChanged = true;
}

void  TXColorCurves::luminosityCurveChanged(ofAbstractParameter & parameterArg ) {
    curvesHSLImageHasChanged = true;
}

void TXColorCurves::updateCurvesImagePixels() {
    ofColor holdColor;
    for(int x = 0; x < 256; ++x){
        holdColor.set(redCurve1.parameters.getFloat(x) * 255.0f, greenCurve1.parameters.getFloat(x) * 255.0f, blueCurve1.parameters.getFloat(x) * 255.0f, 255.0f);
        curvesImage.setColor(x, 0, holdColor);
        holdColor.set(redCurve2.parameters.getFloat(x) * 255.0f, greenCurve2.parameters.getFloat(x) * 255.0f, blueCurve2.parameters.getFloat(x) * 255.0f, 255.0f);
        curvesImage.setColor(x + 256, 0, holdColor);
    }
    curvesImage.update();
}

void TXColorCurves::updateCurvesHSLImagePixels() {
    ofColor holdColor;
    for(int x = 0; x < 256; ++x){
        holdColor.set(hueCurve1.parameters.getFloat(x) * 255.0f, saturationCurve1.parameters.getFloat(x) * 255.0f, luminosityCurve1.parameters.getFloat(x) * 255.0f, 255.0f);
        curvesHSLImage.setColor(x, 0, holdColor);
        holdColor.set(hueCurve2.parameters.getFloat(x) * 255.0f, saturationCurve2.parameters.getFloat(x) * 255.0f, luminosityCurve2.parameters.getFloat(x) * 255.0f, 255.0f);
        curvesHSLImage.setColor(x + 256, 0, holdColor);
    }
    curvesHSLImage.update();
}

