/*
 *  Copyright 2014 Paul Miller. All rights reserved.
 */

#include "TXDrawFluid.h"
#include "TXSystem.h"

// constructor
TXDrawFluid::TXDrawFluid() {
    setup();
}

// destructor
TXDrawFluid::~TXDrawFluid() {
    // remove listeners to relevent mod parameters:
    ofRemoveListener(drawMode->parameters.parameterChangedE(),this,&TXDrawFluid::drawModeChanged);
    ofRemoveListener(wrapX->parameters.parameterChangedE(),this,&TXDrawFluid::wrapXChanged);
    ofRemoveListener(wrapY->parameters.parameterChangedE(),this,&TXDrawFluid::wrapYChanged);
    ofRemoveListener(viscocity->parameters.parameterChangedE(),this,&TXDrawFluid::viscocityChanged);
    ofRemoveListener(colorDiffusion->parameters.parameterChangedE(),this,&TXDrawFluid::colorDiffusionChanged);
    ofRemoveListener(fadeSpeed->parameters.parameterChangedE(),this,&TXDrawFluid::fadeSpeedChanged);
    ofRemoveListener(deltaTime->parameters.parameterChangedE(),this,&TXDrawFluid::deltaTimeChanged);
    ofRemoveListener(solverIterations->parameters.parameterChangedE(),this,&TXDrawFluid::solverIterationsChanged);
    ofRemoveListener(doVorticityConfinement->parameters.parameterChangedE(),this,&TXDrawFluid::doVorticityConfinementChanged);
    ofRemoveListener(doRGB->parameters.parameterChangedE(),this,&TXDrawFluid::doRGBChanged);
    ofRemoveListener(triggerParticlesNow->parameters.parameterChangedE(),this,&TXDrawFluid::triggerParticlesNowChanged);
    ofRemoveListener(killAllParticlesNow->parameters.parameterChangedE(),this,&TXDrawFluid::killAllParticlesNowChanged);
}

void TXDrawFluid::setup(){
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
    
    holdModParamBoolArgs.name = "drawFluid";
    holdModParamBoolArgs.fixedValue = true;
	drawFluid = createModParameter(holdModParamBoolArgs);
    parameters.add(drawFluid->parameters);
    
    parameters.add(fluidCellsX.set("fluidCellsX", 150, 10, 1000));
    parameters.add(fluidCellsY.set("fluidCellsY", 150, 10, 1000));
    
    holdModParamIntArgs.name = "drawMode";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalDrawModes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalDrawModes - 1;
	drawMode = createModParameter(holdModParamIntArgs);
    parameters.add(drawMode->parameters);
    
    holdModParamBoolArgs.name = "frozen";
    holdModParamBoolArgs.fixedValue = false;
	frozen = createModParameter(holdModParamBoolArgs);
    parameters.add(frozen->parameters);
    
    holdModParamFloatArgs.name = "viscocity";
    holdModParamFloatArgs.fixedValue = 0.01;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 0.1;
	viscocity = createModParameter(holdModParamFloatArgs);
    parameters.add(viscocity->parameters);
    
    holdModParamFloatArgs.name = "colorDiffusion";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 0.3;
	colorDiffusion = createModParameter(holdModParamFloatArgs);
    parameters.add(colorDiffusion->parameters);
    
    holdModParamFloatArgs.name = "colorMultiply";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 100.0;
	colorMultiply = createModParameter(holdModParamFloatArgs);
    parameters.add(colorMultiply->parameters);
    
    holdModParamFloatArgs.name = "forceMultiply";
    holdModParamFloatArgs.fixedValue = 20.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 100.0;
	forceMultiply = createModParameter(holdModParamFloatArgs);
    parameters.add(forceMultiply->parameters);
    
    holdModParamFloatArgs.name = "fadeSpeed";
    holdModParamFloatArgs.fixedValue = 0.05;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	fadeSpeed = createModParameter(holdModParamFloatArgs);
    parameters.add(fadeSpeed->parameters);
    
    holdModParamFloatArgs.name = "deltaTime";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.001;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.001;
    holdModParamFloatArgs.softMax = 5.0;
	deltaTime = createModParameter(holdModParamFloatArgs);
    parameters.add(deltaTime->parameters);
    
    holdModParamBoolArgs.name = "wrapX";
    holdModParamBoolArgs.fixedValue = true;
	wrapX = createModParameter(holdModParamBoolArgs);
    parameters.add(wrapX->parameters);
    
    holdModParamBoolArgs.name = "wrapY";
    holdModParamBoolArgs.fixedValue = true;
	wrapY = createModParameter(holdModParamBoolArgs);
    parameters.add(wrapY->parameters);
    
    holdModParamIntArgs.name = "solverIterations";
    holdModParamIntArgs.fixedValue = 10;
    holdModParamIntArgs.hardMin = 1;
    holdModParamIntArgs.hardMax = 100;
    holdModParamIntArgs.softMin = 1;
    holdModParamIntArgs.softMax = 50;
	solverIterations = createModParameter(holdModParamIntArgs);
    parameters.add(solverIterations->parameters);
    
    holdModParamBoolArgs.name = "doVorticityConfinement";
    holdModParamBoolArgs.fixedValue = false;
	doVorticityConfinement = createModParameter(holdModParamBoolArgs);
    parameters.add(doVorticityConfinement->parameters);
    
    holdModParamBoolArgs.name = "doRGB";
    holdModParamBoolArgs.fixedValue = true;
	doRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(doRGB->parameters);
    
    holdModParamBoolArgs.name = "color1Active";
    holdModParamBoolArgs.fixedValue = false;
	color1Active = createModParameter(holdModParamBoolArgs);
    parameters.add(color1Active->parameters);
    
    holdModParamFloatArgs.name = "color1PosX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color1PosX = createModParameter(holdModParamFloatArgs);
    parameters.add(color1PosX->parameters);
    
    holdModParamFloatArgs.name = "color1PosY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color1PosY = createModParameter(holdModParamFloatArgs);
    parameters.add(color1PosY->parameters);
    
    holdModParamFloatArgs.name = "color1Hue";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color1Hue = createModParameter(holdModParamFloatArgs);
    parameters.add(color1Hue->parameters);
    
    holdModParamFloatArgs.name = "color1Saturation";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color1Saturation = createModParameter(holdModParamFloatArgs);
    parameters.add(color1Saturation->parameters);
    
    holdModParamFloatArgs.name = "color1Brightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color1Brightness = createModParameter(holdModParamFloatArgs);
    parameters.add(color1Brightness->parameters);
    
    holdModParamFloatArgs.name = "color1Alpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color1Alpha = createModParameter(holdModParamFloatArgs);
    parameters.add(color1Alpha->parameters);
    
    holdModParamBoolArgs.name = "color1HSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    color1HSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(color1HSBAsRGB->parameters);
    
    holdModParamBoolArgs.name = "color2Active";
    holdModParamBoolArgs.fixedValue = false;
	color2Active = createModParameter(holdModParamBoolArgs);
    parameters.add(color2Active->parameters);
    
    holdModParamFloatArgs.name = "color2PosX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color2PosX = createModParameter(holdModParamFloatArgs);
    parameters.add(color2PosX->parameters);
    
    holdModParamFloatArgs.name = "color2PosY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color2PosY = createModParameter(holdModParamFloatArgs);
    parameters.add(color2PosY->parameters);
    
    holdModParamFloatArgs.name = "color2Hue";
    holdModParamFloatArgs.fixedValue = 0.25;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color2Hue = createModParameter(holdModParamFloatArgs);
    parameters.add(color2Hue->parameters);
    
    holdModParamFloatArgs.name = "color2Saturation";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color2Saturation = createModParameter(holdModParamFloatArgs);
    parameters.add(color2Saturation->parameters);
    
    holdModParamFloatArgs.name = "color2Brightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color2Brightness = createModParameter(holdModParamFloatArgs);
    parameters.add(color2Brightness->parameters);
    
    holdModParamFloatArgs.name = "color2Alpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color2Alpha = createModParameter(holdModParamFloatArgs);
    parameters.add(color2Alpha->parameters);
    
    holdModParamBoolArgs.name = "color2HSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    color2HSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(color2HSBAsRGB->parameters);
    
    holdModParamBoolArgs.name = "color3Active";
    holdModParamBoolArgs.fixedValue = false;
	color3Active = createModParameter(holdModParamBoolArgs);
    parameters.add(color3Active->parameters);
    
    holdModParamFloatArgs.name = "color3PosX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color3PosX = createModParameter(holdModParamFloatArgs);
    parameters.add(color3PosX->parameters);
    
    holdModParamFloatArgs.name = "color3PosY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color3PosY = createModParameter(holdModParamFloatArgs);
    parameters.add(color3PosY->parameters);
    
    holdModParamFloatArgs.name = "color3Hue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color3Hue = createModParameter(holdModParamFloatArgs);
    parameters.add(color3Hue->parameters);
    
    holdModParamFloatArgs.name = "color3Saturation";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color3Saturation = createModParameter(holdModParamFloatArgs);
    parameters.add(color3Saturation->parameters);
    
    holdModParamFloatArgs.name = "color3Brightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color3Brightness = createModParameter(holdModParamFloatArgs);
    parameters.add(color3Brightness->parameters);
    
    holdModParamFloatArgs.name = "color3Alpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color3Alpha = createModParameter(holdModParamFloatArgs);
    parameters.add(color3Alpha->parameters);
    
    holdModParamBoolArgs.name = "color3HSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    color3HSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(color3HSBAsRGB->parameters);
    
    holdModParamBoolArgs.name = "color4Active";
    holdModParamBoolArgs.fixedValue = false;
	color4Active = createModParameter(holdModParamBoolArgs);
    parameters.add(color4Active->parameters);
    
    holdModParamFloatArgs.name = "color4PosX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color4PosX = createModParameter(holdModParamFloatArgs);
    parameters.add(color4PosX->parameters);
    
    holdModParamFloatArgs.name = "color4PosY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color4PosY = createModParameter(holdModParamFloatArgs);
    parameters.add(color4PosY->parameters);
    
    holdModParamFloatArgs.name = "color4Hue";
    holdModParamFloatArgs.fixedValue = 0.75;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color4Hue = createModParameter(holdModParamFloatArgs);
    parameters.add(color4Hue->parameters);
    
    holdModParamFloatArgs.name = "color4Saturation";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color4Saturation = createModParameter(holdModParamFloatArgs);
    parameters.add(color4Saturation->parameters);
    
    holdModParamFloatArgs.name = "color4Brightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color4Brightness = createModParameter(holdModParamFloatArgs);
    parameters.add(color4Brightness->parameters);
    
    holdModParamFloatArgs.name = "color4Alpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	color4Alpha = createModParameter(holdModParamFloatArgs);
    parameters.add(color4Alpha->parameters);
    
    holdModParamBoolArgs.name = "color4HSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    color4HSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(color4HSBAsRGB->parameters);
    
    ///////////////////
    
    holdModParamBoolArgs.name = "force1Active";
    holdModParamBoolArgs.fixedValue = false;
	force1Active = createModParameter(holdModParamBoolArgs);
    parameters.add(force1Active->parameters);
    
    holdModParamFloatArgs.name = "force1X";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -1.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
	force1X = createModParameter(holdModParamFloatArgs);
    parameters.add(force1X->parameters);
    
    holdModParamFloatArgs.name = "force1Y";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -1.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
	force1Y = createModParameter(holdModParamFloatArgs);
    parameters.add(force1Y->parameters);
    
    holdModParamBoolArgs.name = "useForce1YAsDirection";
    holdModParamBoolArgs.fixedValue = false;
	useForce1YAsDirection = createModParameter(holdModParamBoolArgs);
    parameters.add(useForce1YAsDirection->parameters);
    
    holdModParamFloatArgs.name = "force1PosX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	force1PosX = createModParameter(holdModParamFloatArgs);
    parameters.add(force1PosX->parameters);
    
    holdModParamFloatArgs.name = "force1PosY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	force1PosY = createModParameter(holdModParamFloatArgs);
    parameters.add(force1PosY->parameters);
    
    holdModParamBoolArgs.name = "useColor1PosForForce1";
    holdModParamBoolArgs.fixedValue = false;
	useColor1PosForForce1 = createModParameter(holdModParamBoolArgs);
    parameters.add(useColor1PosForForce1->parameters);
    
    holdModParamFloatArgs.name = "force1PosSpeedToForce";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -100.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = -10.0;
    holdModParamFloatArgs.softMax = 10.0;
	force1PosSpeedToForce = createModParameter(holdModParamFloatArgs);
    parameters.add(force1PosSpeedToForce->parameters);
    
    holdModParamBoolArgs.name = "force2Active";
    holdModParamBoolArgs.fixedValue = false;
	force2Active = createModParameter(holdModParamBoolArgs);
    parameters.add(force2Active->parameters);
    
    holdModParamFloatArgs.name = "force2X";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -1.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
	force2X = createModParameter(holdModParamFloatArgs);
    parameters.add(force2X->parameters);
    
    holdModParamFloatArgs.name = "force2Y";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -1.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
	force2Y = createModParameter(holdModParamFloatArgs);
    parameters.add(force2Y->parameters);
    
    holdModParamBoolArgs.name = "useForce2YAsDirection";
    holdModParamBoolArgs.fixedValue = false;
	useForce2YAsDirection = createModParameter(holdModParamBoolArgs);
    parameters.add(useForce2YAsDirection->parameters);
    
    holdModParamFloatArgs.name = "force2PosX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	force2PosX = createModParameter(holdModParamFloatArgs);
    parameters.add(force2PosX->parameters);
    
    holdModParamFloatArgs.name = "force2PosY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	force2PosY = createModParameter(holdModParamFloatArgs);
    parameters.add(force2PosY->parameters);
    
    holdModParamBoolArgs.name = "useColor2PosForForce2";
    holdModParamBoolArgs.fixedValue = false;
	useColor2PosForForce2 = createModParameter(holdModParamBoolArgs);
    parameters.add(useColor2PosForForce2->parameters);
    
    holdModParamFloatArgs.name = "force2PosSpeedToForce";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -100.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = -10.0;
    holdModParamFloatArgs.softMax = 10.0;
	force2PosSpeedToForce = createModParameter(holdModParamFloatArgs);
    parameters.add(force2PosSpeedToForce->parameters);
    
    holdModParamBoolArgs.name = "force3Active";
    holdModParamBoolArgs.fixedValue = false;
	force3Active = createModParameter(holdModParamBoolArgs);
    parameters.add(force3Active->parameters);
    
    holdModParamFloatArgs.name = "force3X";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -1.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
	force3X = createModParameter(holdModParamFloatArgs);
    parameters.add(force3X->parameters);
    
    holdModParamFloatArgs.name = "force3Y";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -1.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
	force3Y = createModParameter(holdModParamFloatArgs);
    parameters.add(force3Y->parameters);
    
    holdModParamBoolArgs.name = "useForce3YAsDirection";
    holdModParamBoolArgs.fixedValue = false;
	useForce3YAsDirection = createModParameter(holdModParamBoolArgs);
    parameters.add(useForce3YAsDirection->parameters);
    
    holdModParamFloatArgs.name = "force3PosX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	force3PosX = createModParameter(holdModParamFloatArgs);
    parameters.add(force3PosX->parameters);
    
    holdModParamFloatArgs.name = "force3PosY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	force3PosY = createModParameter(holdModParamFloatArgs);
    parameters.add(force3PosY->parameters);
    
    holdModParamBoolArgs.name = "useColor3PosForForce3";
    holdModParamBoolArgs.fixedValue = false;
	useColor3PosForForce3 = createModParameter(holdModParamBoolArgs);
    parameters.add(useColor3PosForForce3->parameters);
    
    holdModParamFloatArgs.name = "force3PosSpeedToForce";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -100.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = -10.0;
    holdModParamFloatArgs.softMax = 10.0;
	force3PosSpeedToForce = createModParameter(holdModParamFloatArgs);
    parameters.add(force3PosSpeedToForce->parameters);
    
    holdModParamBoolArgs.name = "force4Active";
    holdModParamBoolArgs.fixedValue = false;
	force4Active = createModParameter(holdModParamBoolArgs);
    parameters.add(force4Active->parameters);
    
    holdModParamFloatArgs.name = "force4X";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -1.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
	force4X = createModParameter(holdModParamFloatArgs);
    parameters.add(force4X->parameters);
    
    holdModParamFloatArgs.name = "force4Y";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -1.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
	force4Y = createModParameter(holdModParamFloatArgs);
    parameters.add(force4Y->parameters);
    
    holdModParamBoolArgs.name = "useForce4YAsDirection";
    holdModParamBoolArgs.fixedValue = false;
	useForce4YAsDirection = createModParameter(holdModParamBoolArgs);
    parameters.add(useForce4YAsDirection->parameters);
    
    holdModParamFloatArgs.name = "force4PosX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	force4PosX = createModParameter(holdModParamFloatArgs);
    parameters.add(force4PosX->parameters);
    
    holdModParamFloatArgs.name = "force4PosY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	force4PosY = createModParameter(holdModParamFloatArgs);
    parameters.add(force4PosY->parameters);
    
    holdModParamBoolArgs.name = "useColor4PosForForce4";
    holdModParamBoolArgs.fixedValue = false;
	useColor4PosForForce4 = createModParameter(holdModParamBoolArgs);
    parameters.add(useColor4PosForForce4->parameters);
    
    holdModParamFloatArgs.name = "force4PosSpeedToForce";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -100.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = -10.0;
    holdModParamFloatArgs.softMax = 10.0;
	force4PosSpeedToForce = createModParameter(holdModParamFloatArgs);
    parameters.add(force4PosSpeedToForce->parameters);
    
    ///////////////////

    holdModParamFloatArgs.name = "width";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	width = createModParameter(holdModParamFloatArgs);
    parameters.add(width->parameters);
    
    holdModParamFloatArgs.name = "height";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	height = createModParameter(holdModParamFloatArgs);
    parameters.add(height->parameters);
    
    holdModParamFloatArgs.name = "positionX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	positionX = createModParameter(holdModParamFloatArgs);
    parameters.add(positionX->parameters);
    
    holdModParamFloatArgs.name = "positionY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	positionY = createModParameter(holdModParamFloatArgs);
    parameters.add(positionY->parameters);
    
    holdModParamFloatArgs.name = "anchorX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	anchorX = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorX->parameters);
    
    holdModParamFloatArgs.name = "anchorY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	anchorY = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorY->parameters);
    
    holdModParamFloatArgs.name = "rotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	rotate = createModParameter(holdModParamFloatArgs);
    parameters.add(rotate->parameters);
    
    holdModParamFloatArgs.name = "rotateMultiply";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
	rotateMultiply = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateMultiply->parameters);
    
    holdModParamFloatArgs.name = "scaleX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -100.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
	scaleX = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleX->parameters);
    
    holdModParamFloatArgs.name = "scaleY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -100.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
	scaleY = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleY->parameters);
    
    parameters.add(useScaleXForScaleY.set("useScaleXForScaleY", false));

    holdModParamBoolArgs.name = "drawParticles";
    holdModParamBoolArgs.fixedValue = true;
	drawParticles = createModParameter(holdModParamBoolArgs);
    parameters.add(drawParticles->parameters);
    
    holdModParamBoolArgs.name = "triggerParticlesContinuosly";
    holdModParamBoolArgs.fixedValue = false;
	triggerParticlesContinuosly = createModParameter(holdModParamBoolArgs);
    parameters.add(triggerParticlesContinuosly->parameters);
    
    holdModParamBoolArgs.name = "triggerParticlesNow";
    holdModParamBoolArgs.fixedValue = false;
	triggerParticlesNow = createModParameter(holdModParamBoolArgs);
    parameters.add(triggerParticlesNow->parameters);
    
    holdModParamBoolArgs.name = "useForce1ToTriggerParticles";
    holdModParamBoolArgs.fixedValue = true;
	useForce1ToTriggerParticles = createModParameter(holdModParamBoolArgs);
    parameters.add(useForce1ToTriggerParticles->parameters);
    
    holdModParamBoolArgs.name = "killAllParticlesNow";
    holdModParamBoolArgs.fixedValue = false;
	killAllParticlesNow = createModParameter(holdModParamBoolArgs);
    parameters.add(killAllParticlesNow->parameters);
    
    // merge particle parameters
    mergeParameters(particles.parameters, particles.modParameters);
    
    // add listener to relevent parameters:
    fluidCellsX.addListener(this, &TXDrawFluid::fluidCellsXChanged);
    fluidCellsY.addListener(this, &TXDrawFluid::fluidCellsYChanged);
    
    ofAddListener(drawMode->parameters.parameterChangedE(),this,&TXDrawFluid::drawModeChanged);
    ofAddListener(wrapX->parameters.parameterChangedE(),this,&TXDrawFluid::wrapXChanged);
    ofAddListener(wrapY->parameters.parameterChangedE(),this,&TXDrawFluid::wrapYChanged);
    ofAddListener(viscocity->parameters.parameterChangedE(),this,&TXDrawFluid::viscocityChanged);
    ofAddListener(colorDiffusion->parameters.parameterChangedE(),this,&TXDrawFluid::colorDiffusionChanged);
    ofAddListener(fadeSpeed->parameters.parameterChangedE(),this,&TXDrawFluid::fadeSpeedChanged);
    ofAddListener(deltaTime->parameters.parameterChangedE(),this,&TXDrawFluid::deltaTimeChanged);
    ofAddListener(solverIterations->parameters.parameterChangedE(),this,&TXDrawFluid::solverIterationsChanged);
    ofAddListener(doVorticityConfinement->parameters.parameterChangedE(),this,&TXDrawFluid::doVorticityConfinementChanged);
    ofAddListener(doRGB->parameters.parameterChangedE(),this,&TXDrawFluid::doRGBChanged);
    ofAddListener(triggerParticlesNow->parameters.parameterChangedE(),this,&TXDrawFluid::triggerParticlesNowChanged);
    ofAddListener(killAllParticlesNow->parameters.parameterChangedE(),this,&TXDrawFluid::killAllParticlesNowChanged);
    
    // init
    resizeFluid = true;
    triggerParticlesNowConfirmed = false;
    killAllParticlesNowConfirmed = false;
    oldTriggerParticlesNow = false;
    oldKillAllParticlesNow = false;
    oldForce1Pos = ofVec2f(0.0, 0.0);
    oldForce2Pos = ofVec2f(0.0, 0.0);
    oldForce3Pos = ofVec2f(0.0, 0.0);
    oldForce4Pos = ofVec2f(0.0, 0.0);
    
	fluidSolver.setup(fluidCellsX, fluidCellsY);
    fluidSolver.enableRGB(true).setFadeSpeed(0.05).setDeltaT(1.0).setVisc(0.01).setColorDiffusion(0);
	fluidDrawer.setup(&fluidSolver);
}

void TXDrawFluid::advanceBy(float timeDeltaArg) {
    if (!frozen->getBool()) {
        particles.advanceBy(timeDeltaArg);
    };
}

void TXDrawFluid::update(){
    if(resizeFluid) 	{
        fluidSolver.setSize(fluidCellsX, fluidCellsY);
        fluidDrawer.setup(&fluidSolver);
        resizeFluid = false;
    }
    if (!frozen->getBool()) {
        fluidSolver.update();
        addColorsForces();

        // check whether to kill particles
        if (killAllParticlesNowConfirmed) {
            particles.killParticles();
            killAllParticlesNowConfirmed = false;
        };

        // check whether to trigger particles
        bool holdTriggerParticlesContinuosly = triggerParticlesContinuosly->getBool();
        bool force1Trigger;
        if (useForce1ToTriggerParticles->getBool() && force1Active->getBool()) {
            force1Trigger = true;
        } else {
            force1Trigger = false;
        };
        if (holdTriggerParticlesContinuosly || triggerParticlesNowConfirmed || force1Trigger) {
            if (useColor1PosForForce1->getBool()) {
                particles.trigger(ofVec2f(color1PosX->getFloat(), color1PosY->getFloat()));
            } else {
                particles.trigger(ofVec2f(force1PosX->getFloat(), force1PosY->getFloat()));
            };
            triggerParticlesNowConfirmed = false;
        };
    };
}

void TXDrawFluid::draw(){
    float holdScaleX, holdScaleY;
    
    int   holdMaxWidth = getMaxWidth();
    int   holdMaxHeight = getMaxHeight();
    float holdWidth = holdMaxWidth * width->getFloat();
    float holdHeight = holdMaxHeight * height->getFloat();
    
    
    // check before drawing
    if (!drawActive->getBool()) {
        return;
    };
    
    if ((drawFluid->getBool()) && (holdWidth > 0.0) && (holdHeight > 0.0)) {
        float anchorXPixels = anchorX->getFloat() * holdWidth;
        float anchorYPixels = anchorY->getFloat() * holdHeight;
        
        float holdDrawPosX = positionX->getFloat() * holdMaxWidth;
        float holdDrawPosY = positionY->getFloat() * holdMaxHeight;
        
        holdScaleX = scaleX->getFloat();
        if (useScaleXForScaleY) {
            holdScaleY = holdScaleX;
        } else {
            holdScaleY = scaleY->getFloat();
        };
        // translate, rotate, scale
        ofPushMatrix();
        ofTranslate(holdDrawPosX, holdDrawPosY, 0.0);
        ofRotateZ(rotateMultiply->getFloat() * rotate->getFloat());
        ofScale(holdScaleX, holdScaleY, 1.0);
        
        ofTranslate(-anchorXPixels, -anchorYPixels, 0.0);
        
        // draw
        ofEnableAlphaBlending();
        fluidDrawer.draw(0, 0, holdWidth, holdHeight);
        ofDisableAlphaBlending();
        
        ofPopMatrix();
    };
    
    if (drawParticles->getBool()) {
        if (frozen->getBool()) {
            particles.draw();
        } else {
            particles.updateAndDraw(fluidSolver, holdWidth, holdHeight);
        };
    };
    
}

void TXDrawFluid::addColorsForces(){
    ofColor color1;
    ofColor color2;
    ofColor color3;
    ofColor color4;
    ofVec2f pos, force, vel;
    float holdForceMultiply = forceMultiply->getFloat();
    float holdColorMultiply = colorMultiply->getFloat();
    
    if (color1Active->getBool()) {
        if (color1HSBAsRGB->getBool()) {
            color1.set(color1Hue->getFloat() * 255, color1Saturation->getFloat() * 255, color1Brightness->getFloat() * 255, color1Alpha->getFloat() * 255);
        } else {
            color1 = ofColor::fromHsb(color1Hue->getFloat() * 255, color1Saturation->getFloat() * 255, color1Brightness->getFloat() * 255, color1Alpha->getFloat() * 255);
        };
        pos = ofVec2f(color1PosX->getFloat(), color1PosY->getFloat());
        fluidSolver.addColorAtPos(pos, color1 * holdColorMultiply);
    };
    if (color2Active->getBool()) {
        if (color2HSBAsRGB->getBool()) {
            color2.set(color2Hue->getFloat() * 255, color2Saturation->getFloat() * 255, color2Brightness->getFloat() * 255, color2Alpha->getFloat() * 255);
        } else {
            color2 = ofColor::fromHsb(color2Hue->getFloat() * 255, color2Saturation->getFloat() * 255, color2Brightness->getFloat() * 255, color2Alpha->getFloat() * 255);
        };
        pos = ofVec2f(color2PosX->getFloat(), color2PosY->getFloat());
        fluidSolver.addColorAtPos(pos, color2 * holdColorMultiply);
    };
    if (color3Active->getBool()) {
        if (color3HSBAsRGB->getBool()) {
            color3.set(color3Hue->getFloat() * 255, color3Saturation->getFloat() * 255, color3Brightness->getFloat() * 255, color3Alpha->getFloat() * 255);
        } else {
            color3 = ofColor::fromHsb(color3Hue->getFloat() * 255, color3Saturation->getFloat() * 255, color3Brightness->getFloat() * 255, color3Alpha->getFloat() * 255);
        };
        pos = ofVec2f(color3PosX->getFloat(), color3PosY->getFloat());
        fluidSolver.addColorAtPos(pos, color3 * holdColorMultiply);
    };
    if (color4Active->getBool()) {
        if (color4HSBAsRGB->getBool()) {
            color4.set(color4Hue->getFloat() * 255, color4Saturation->getFloat() * 255, color4Brightness->getFloat() * 255, color4Alpha->getFloat() * 255);
        } else {
            color4 = ofColor::fromHsb(color4Hue->getFloat() * 255, color4Saturation->getFloat() * 255, color4Brightness->getFloat() * 255, color4Alpha->getFloat() * 255);
        };
        pos = ofVec2f(color4PosX->getFloat(), color4PosY->getFloat());
        fluidSolver.addColorAtPos(pos, color4 * holdColorMultiply);
    };
    
    if (force1Active->getBool()) {
        if (useColor1PosForForce1->getBool()) {
            pos = ofVec2f(color1PosX->getFloat(), color1PosY->getFloat());
        } else {
            pos = ofVec2f(force1PosX->getFloat(), force1PosY->getFloat());
        };
        vel = (pos - oldForce1Pos) * force1PosSpeedToForce->getFloat();
        oldForce1Pos = pos;
        force = vel + getForce(force1X->getFloat(), force1Y->getFloat(), useForce1YAsDirection->getBool());
        fluidSolver.addForceAtPos(pos, force * holdForceMultiply);
    };
    if (force2Active->getBool()) {
        if (useColor2PosForForce2->getBool()) {
            pos = ofVec2f(color2PosX->getFloat(), color2PosY->getFloat());
        } else {
            pos = ofVec2f(force2PosX->getFloat(), force2PosY->getFloat());
        };
        vel = (pos - oldForce2Pos) * force2PosSpeedToForce->getFloat();
        oldForce2Pos = pos;
        force = vel + getForce(force2X->getFloat(), force2Y->getFloat(), useForce2YAsDirection->getBool());
        fluidSolver.addForceAtPos(pos, force * holdForceMultiply);
    };
    if (force3Active->getBool()) {
        if (useColor3PosForForce3->getBool()) {
            pos = ofVec2f(color3PosX->getFloat(), color3PosY->getFloat());
        } else {
            pos = ofVec2f(force3PosX->getFloat(), force3PosY->getFloat());
        };
        vel = (pos - oldForce3Pos) * force3PosSpeedToForce->getFloat();
        oldForce3Pos = pos;
        force = vel + getForce(force3X->getFloat(), force3Y->getFloat(), useForce3YAsDirection->getBool());
        fluidSolver.addForceAtPos(pos, force * holdForceMultiply);
    };
    if (force4Active->getBool()) {
        if (useColor4PosForForce4->getBool()) {
            pos = ofVec2f(color4PosX->getFloat(), color4PosY->getFloat());
        } else {
            pos = ofVec2f(force4PosX->getFloat(), force4PosY->getFloat());
        };
        vel = (pos - oldForce4Pos) * force4PosSpeedToForce->getFloat();
        oldForce4Pos = pos;
        force = vel + getForce(force4X->getFloat(), force4Y->getFloat(), useForce4YAsDirection->getBool());
        fluidSolver.addForceAtPos(pos, force * holdForceMultiply);
    };
}

ofVec2f TXDrawFluid::getForce(float forceX, float forceY, bool forceYAsDirection) {
    float holdX, holdY;
    ofVec2f outForce;
    if (forceYAsDirection) {
        holdX = sin(forceY * TWO_PI) * forceX;
        holdY = cos(forceY * TWO_PI) * forceX;
        outForce = ofVec2f(holdX, holdY);
    } else {
        outForce = ofVec2f(forceX, forceY);
    };
    return outForce;
}

//////////////////////////////

void  TXDrawFluid::fluidCellsXChanged(int & intArg) {
    resizeFluid = true;
}

void  TXDrawFluid::fluidCellsYChanged(int & intArg) {
    resizeFluid = true;
}

void  TXDrawFluid::drawModeChanged(ofAbstractParameter & parameterArg ) {
    fluidDrawer.setDrawMode((msa::fluid::DrawMode) drawMode->getInt());
}

void  TXDrawFluid::wrapXChanged(ofAbstractParameter & parameterArg ) {
    fluidSolver.setWrap(wrapX->getBool(), wrapY->getBool());
}

void  TXDrawFluid::wrapYChanged(ofAbstractParameter & parameterArg ) {
    fluidSolver.setWrap(wrapX->getBool(), wrapY->getBool());
}

void  TXDrawFluid::viscocityChanged(ofAbstractParameter & parameterArg ) {
    // scale value
    fluidSolver.viscocity = viscocity->getFloat() * 0.01;
}

void  TXDrawFluid::colorDiffusionChanged(ofAbstractParameter & parameterArg ) {
    // scale value
    fluidSolver.colorDiffusion = colorDiffusion->getFloat() * 0.001;
}

void  TXDrawFluid::fadeSpeedChanged(ofAbstractParameter & parameterArg ) {
    // scale value
    fluidSolver.fadeSpeed = fadeSpeed->getFloat() * 0.1;
}

void  TXDrawFluid::deltaTimeChanged(ofAbstractParameter & parameterArg ) {
    fluidSolver.deltaT = deltaTime->getFloat();
}

void  TXDrawFluid::solverIterationsChanged(ofAbstractParameter & parameterArg ) {
    fluidSolver.solverIterations = solverIterations->getInt();
}

void  TXDrawFluid::doVorticityConfinementChanged(ofAbstractParameter & parameterArg ) {
    fluidSolver.doVorticityConfinement = doVorticityConfinement->getBool();
}

void  TXDrawFluid::doRGBChanged(ofAbstractParameter & parameterArg ) {
    fluidSolver.doRGB = doRGB->getBool();
}


void  TXDrawFluid::triggerParticlesNowChanged(ofAbstractParameter & parameterArg){
    bool holdtriggerParticlesNow = triggerParticlesNow->getBool();
    // if changed to on, confirm
    if ((oldTriggerParticlesNow == false) && (holdtriggerParticlesNow == true)) {
        triggerParticlesNowConfirmed = true;
    };
    oldTriggerParticlesNow = holdtriggerParticlesNow;
}

void  TXDrawFluid::killAllParticlesNowChanged(ofAbstractParameter & parameterArg){
    bool holdkillAllParticlesNow = killAllParticlesNow->getBool();
    // if changed to on
    if ((oldKillAllParticlesNow == false) && (holdkillAllParticlesNow == true)) {
        killAllParticlesNowConfirmed = true;
    };
    oldKillAllParticlesNow = holdkillAllParticlesNow;
}




