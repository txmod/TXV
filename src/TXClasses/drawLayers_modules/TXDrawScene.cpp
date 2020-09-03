/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXSystem.h"
#include "TXDrawScene.h"
#include "TXFunctions.h"


// constructor
TXDrawScene::TXDrawScene() {
    setup();
}

// destructor
TXDrawScene::~TXDrawScene() {
}

void TXDrawScene::setup(){
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    
    // create input paramaters
    initialiseParameters();
    
    holdModParamIntArgs.name = "drawLayersRule";
    holdModParamIntArgs.fixedValue = TXDRAWLAYERSRULE_ALLEXCEPT20;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXDRAWLAYERSRULE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXDRAWLAYERSRULE_TOTAL - 1;
	drawLayersRule = createModParameter(holdModParamIntArgs);
    parameters.add(drawLayersRule->parameters);
    
    holdModParamBoolArgs.name = "useLighting";
    holdModParamBoolArgs.fixedValue = true;
    useLighting = createModParameter(holdModParamBoolArgs);
    parameters.add(useLighting->parameters);
    
    parameters.add(smoothLighting.set("smoothLighting", true));
    parameters.add(drawLights.set("drawLights", false));

    /////

    holdModParamBoolArgs.name = "light1Active";
    holdModParamBoolArgs.fixedValue = true;
    light1Active = createModParameter(holdModParamBoolArgs);
    parameters.add(light1Active->parameters);
    
    holdModParamIntArgs.name = "light1Type";
    holdModParamIntArgs.fixedValue = TXLIGHTTYPE_POINT;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXLIGHTTYPE_TOTAL-1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXLIGHTTYPE_TOTAL-1;
	light1Type = createModParameter(holdModParamIntArgs);
    parameters.add(light1Type->parameters);

    holdModParamFloatArgs.name = "light1DiffuseColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light1DiffuseColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(light1DiffuseColorHue->parameters);
    
    holdModParamFloatArgs.name = "light1DiffuseColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light1DiffuseColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(light1DiffuseColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "light1DiffuseColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light1DiffuseColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(light1DiffuseColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "light1DiffuseColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.4;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light1DiffuseColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(light1DiffuseColorBrightness->parameters);
    
    holdModParamBoolArgs.name = "light1DiffuseColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	light1DiffuseColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(light1DiffuseColorHSBAsRGB->parameters);
    
    parameters.add(light1UseDiffuseColorForAmbient.set("light1UseDiffuseColorForAmbient", false));

    holdModParamFloatArgs.name = "light1AmbientColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light1AmbientColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(light1AmbientColorHue->parameters);
    
    holdModParamFloatArgs.name = "light1AmbientColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light1AmbientColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(light1AmbientColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "light1AmbientColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light1AmbientColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(light1AmbientColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "light1AmbientColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.185;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light1AmbientColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(light1AmbientColorBrightness->parameters);
    
    holdModParamBoolArgs.name = "light1AmbientColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	light1AmbientColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(light1AmbientColorHSBAsRGB->parameters);
    
    parameters.add(light1UseDiffuseColorForSpecular.set("light1UseDiffuseColorForSpecular", false));

    holdModParamFloatArgs.name = "light1SpecularColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light1SpecularColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(light1SpecularColorHue->parameters);
    
    holdModParamFloatArgs.name = "light1SpecularColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light1SpecularColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(light1SpecularColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "light1SpecularColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light1SpecularColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(light1SpecularColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "light1SpecularColorBrightness";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light1SpecularColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(light1SpecularColorBrightness->parameters);
    
    holdModParamBoolArgs.name = "light1SpecularColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	light1SpecularColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(light1SpecularColorHSBAsRGB->parameters);
    
    holdModParamFloatArgs.name = "light1PositionX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
	light1PositionX = createModParameter(holdModParamFloatArgs);
    parameters.add(light1PositionX->parameters);
    
    holdModParamFloatArgs.name = "light1PositionY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
	light1PositionY = createModParameter(holdModParamFloatArgs);
    parameters.add(light1PositionY->parameters);
    
    holdModParamFloatArgs.name = "light1PositionZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
	light1PositionZ = createModParameter(holdModParamFloatArgs);
    parameters.add(light1PositionZ->parameters);
    
    holdModParamFloatArgs.name = "light1OrientationX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	light1OrientationX = createModParameter(holdModParamFloatArgs);
    parameters.add(light1OrientationX->parameters);
    
    holdModParamFloatArgs.name = "light1OrientationY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	light1OrientationY = createModParameter(holdModParamFloatArgs);
    parameters.add(light1OrientationY->parameters);
    
    holdModParamFloatArgs.name = "light1OrientationZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	light1OrientationZ = createModParameter(holdModParamFloatArgs);
    parameters.add(light1OrientationZ->parameters);
    
    holdModParamIntArgs.name = "light1SpotConcentration";
    holdModParamIntArgs.fixedValue = 64;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 128;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 128;
	light1SpotConcentration = createModParameter(holdModParamIntArgs);
    parameters.add(light1SpotConcentration->parameters);
        
    holdModParamFloatArgs.name = "light1SpotlightAngle";
    holdModParamFloatArgs.fixedValue = 45.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 90.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 90.0;
	light1SpotlightAngle = createModParameter(holdModParamFloatArgs);
    parameters.add(light1SpotlightAngle->parameters);
    
    /////
   
    holdModParamBoolArgs.name = "light2Active";
    holdModParamBoolArgs.fixedValue = false;
    light2Active = createModParameter(holdModParamBoolArgs);
    parameters.add(light2Active->parameters);
    
    holdModParamIntArgs.name = "light2Type";
    holdModParamIntArgs.fixedValue = TXLIGHTTYPE_POINT;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXLIGHTTYPE_TOTAL-1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXLIGHTTYPE_TOTAL-1;
	light2Type = createModParameter(holdModParamIntArgs);
    parameters.add(light2Type->parameters);
    
    holdModParamFloatArgs.name = "light2DiffuseColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light2DiffuseColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(light2DiffuseColorHue->parameters);
    
    holdModParamFloatArgs.name = "light2DiffuseColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light2DiffuseColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(light2DiffuseColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "light2DiffuseColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light2DiffuseColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(light2DiffuseColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "light2DiffuseColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.4;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light2DiffuseColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(light2DiffuseColorBrightness->parameters);
    
    holdModParamBoolArgs.name = "light2DiffuseColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	light2DiffuseColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(light2DiffuseColorHSBAsRGB->parameters);
    
    parameters.add(light2UseDiffuseColorForAmbient.set("light2UseDiffuseColorForAmbient", false));

    holdModParamFloatArgs.name = "light2AmbientColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light2AmbientColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(light2AmbientColorHue->parameters);
    
    holdModParamFloatArgs.name = "light2AmbientColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light2AmbientColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(light2AmbientColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "light2AmbientColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light2AmbientColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(light2AmbientColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "light2AmbientColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.185;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light2AmbientColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(light2AmbientColorBrightness->parameters);
    
    holdModParamBoolArgs.name = "light2AmbientColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	light2AmbientColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(light2AmbientColorHSBAsRGB->parameters);
    
    parameters.add(light2UseDiffuseColorForSpecular.set("light2UseDiffuseColorForSpecular", false));
    
    holdModParamFloatArgs.name = "light2SpecularColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light2SpecularColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(light2SpecularColorHue->parameters);
    
    holdModParamFloatArgs.name = "light2SpecularColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light2SpecularColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(light2SpecularColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "light2SpecularColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light2SpecularColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(light2SpecularColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "light2SpecularColorBrightness";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light2SpecularColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(light2SpecularColorBrightness->parameters);
    
    holdModParamBoolArgs.name = "light2SpecularColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	light2SpecularColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(light2SpecularColorHSBAsRGB->parameters);
    
    holdModParamFloatArgs.name = "light2PositionX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
	light2PositionX = createModParameter(holdModParamFloatArgs);
    parameters.add(light2PositionX->parameters);
    
    holdModParamFloatArgs.name = "light2PositionY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
	light2PositionY = createModParameter(holdModParamFloatArgs);
    parameters.add(light2PositionY->parameters);
    
    holdModParamFloatArgs.name = "light2PositionZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
	light2PositionZ = createModParameter(holdModParamFloatArgs);
    parameters.add(light2PositionZ->parameters);
    
    holdModParamFloatArgs.name = "light2OrientationX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	light2OrientationX = createModParameter(holdModParamFloatArgs);
    parameters.add(light2OrientationX->parameters);
    
    holdModParamFloatArgs.name = "light2OrientationY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	light2OrientationY = createModParameter(holdModParamFloatArgs);
    parameters.add(light2OrientationY->parameters);
    
    holdModParamFloatArgs.name = "light2OrientationZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	light2OrientationZ = createModParameter(holdModParamFloatArgs);
    parameters.add(light2OrientationZ->parameters);
    
    holdModParamIntArgs.name = "light2SpotConcentration";
    holdModParamIntArgs.fixedValue = 64;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 128;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 128;
	light2SpotConcentration = createModParameter(holdModParamIntArgs);
    parameters.add(light2SpotConcentration->parameters);
    
    holdModParamFloatArgs.name = "light2SpotlightAngle";
    holdModParamFloatArgs.fixedValue = 45.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 90.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 90.0;
	light2SpotlightAngle = createModParameter(holdModParamFloatArgs);
    parameters.add(light2SpotlightAngle->parameters);
    
    /////
    
    holdModParamBoolArgs.name = "light3Active";
    holdModParamBoolArgs.fixedValue = false;
    light3Active = createModParameter(holdModParamBoolArgs);
    parameters.add(light3Active->parameters);
    
    holdModParamIntArgs.name = "light3Type";
    holdModParamIntArgs.fixedValue = TXLIGHTTYPE_POINT;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXLIGHTTYPE_TOTAL-1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXLIGHTTYPE_TOTAL-1;
	light3Type = createModParameter(holdModParamIntArgs);
    parameters.add(light3Type->parameters);
    
    holdModParamFloatArgs.name = "light3DiffuseColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light3DiffuseColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(light3DiffuseColorHue->parameters);
    
    holdModParamFloatArgs.name = "light3DiffuseColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light3DiffuseColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(light3DiffuseColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "light3DiffuseColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light3DiffuseColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(light3DiffuseColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "light3DiffuseColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.4;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light3DiffuseColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(light3DiffuseColorBrightness->parameters);
    
    holdModParamBoolArgs.name = "light3DiffuseColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	light3DiffuseColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(light3DiffuseColorHSBAsRGB->parameters);
    
    parameters.add(light3UseDiffuseColorForAmbient.set("light3UseDiffuseColorForAmbient", false));
    
    holdModParamFloatArgs.name = "light3AmbientColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light3AmbientColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(light3AmbientColorHue->parameters);
    
    holdModParamFloatArgs.name = "light3AmbientColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light3AmbientColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(light3AmbientColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "light3AmbientColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light3AmbientColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(light3AmbientColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "light3AmbientColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.185;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light3AmbientColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(light3AmbientColorBrightness->parameters);
    
    holdModParamBoolArgs.name = "light3AmbientColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	light3AmbientColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(light3AmbientColorHSBAsRGB->parameters);
    
    parameters.add(light3UseDiffuseColorForSpecular.set("light3UseDiffuseColorForSpecular", false));
    
    holdModParamFloatArgs.name = "light3SpecularColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light3SpecularColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(light3SpecularColorHue->parameters);
    
    holdModParamFloatArgs.name = "light3SpecularColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light3SpecularColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(light3SpecularColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "light3SpecularColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light3SpecularColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(light3SpecularColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "light3SpecularColorBrightness";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	light3SpecularColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(light3SpecularColorBrightness->parameters);
    
    holdModParamBoolArgs.name = "light3SpecularColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	light3SpecularColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(light3SpecularColorHSBAsRGB->parameters);
    
    holdModParamFloatArgs.name = "light3PositionX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
	light3PositionX = createModParameter(holdModParamFloatArgs);
    parameters.add(light3PositionX->parameters);
    
    holdModParamFloatArgs.name = "light3PositionY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
	light3PositionY = createModParameter(holdModParamFloatArgs);
    parameters.add(light3PositionY->parameters);
    
    holdModParamFloatArgs.name = "light3PositionZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
	light3PositionZ = createModParameter(holdModParamFloatArgs);
    parameters.add(light3PositionZ->parameters);
    
    holdModParamFloatArgs.name = "light3OrientationX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	light3OrientationX = createModParameter(holdModParamFloatArgs);
    parameters.add(light3OrientationX->parameters);
    
    holdModParamFloatArgs.name = "light3OrientationY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	light3OrientationY = createModParameter(holdModParamFloatArgs);
    parameters.add(light3OrientationY->parameters);
    
    holdModParamFloatArgs.name = "light3OrientationZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	light3OrientationZ = createModParameter(holdModParamFloatArgs);
    parameters.add(light3OrientationZ->parameters);
    
    holdModParamIntArgs.name = "light3SpotConcentration";
    holdModParamIntArgs.fixedValue = 64;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 128;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 128;
	light3SpotConcentration = createModParameter(holdModParamIntArgs);
    parameters.add(light3SpotConcentration->parameters);
    
    holdModParamFloatArgs.name = "light3SpotlightAngle";
    holdModParamFloatArgs.fixedValue = 45.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 90.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 90.0;
	light3SpotlightAngle = createModParameter(holdModParamFloatArgs);
    parameters.add(light3SpotlightAngle->parameters);
    
    /////
    
    holdModParamIntArgs.name = "cameraSelect";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 2;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 2;
    cameraSelect = createModParameter(holdModParamIntArgs);
    parameters.add(cameraSelect->parameters);
    
    holdModParamBoolArgs.name = "cam1Orthographic";
    holdModParamBoolArgs.fixedValue = false;
    cam1Orthographic = createModParameter(holdModParamBoolArgs);
    parameters.add(cam1Orthographic->parameters);
    
    holdModParamFloatArgs.name = "cam1FieldOfViewDegrees";
    holdModParamFloatArgs.fixedValue = 60.0;
    holdModParamFloatArgs.hardMin = 10.0;
    holdModParamFloatArgs.hardMax = 170.0;
    holdModParamFloatArgs.softMin = 10.0;
    holdModParamFloatArgs.softMax = 170.0;
    cam1FieldOfViewDegrees = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1FieldOfViewDegrees->parameters);
    
    holdModParamFloatArgs.name = "cam1NearClipDistance";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    cam1NearClipDistance = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1NearClipDistance->parameters);
    
    holdModParamFloatArgs.name = "cam1FarClipDistance";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 4.0;
    cam1FarClipDistance = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1FarClipDistance->parameters);
    
    holdModParamFloatArgs.name = "cam1LensOffsetX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1;
    cam1LensOffsetX = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1LensOffsetX->parameters);
    
    holdModParamFloatArgs.name = "cam1LensOffsetY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1;
    cam1LensOffsetY = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1LensOffsetY->parameters);
    
    holdModParamBoolArgs.name = "cam1ForceAspectRatio";
    holdModParamBoolArgs.fixedValue = false;
    cam1ForceAspectRatio = createModParameter(holdModParamBoolArgs);
    parameters.add(cam1ForceAspectRatio->parameters);
    
    holdModParamFloatArgs.name = "cam1AspectRatioWidth";
    holdModParamFloatArgs.fixedValue = 16.0;
    holdModParamFloatArgs.hardMin = 1.0;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 1.0;
    holdModParamFloatArgs.softMax = 100.0;
    cam1AspectRatioWidth = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1AspectRatioWidth->parameters);
    
    holdModParamFloatArgs.name = "cam1AspectRatioHeight";
    holdModParamFloatArgs.fixedValue = 9.0;
    holdModParamFloatArgs.hardMin = 1.0;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 1.0;
    holdModParamFloatArgs.softMax = 100.0;
    cam1AspectRatioHeight = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1AspectRatioHeight->parameters);
    
    holdModParamIntArgs.name = "cam1PositionMode";
    holdModParamIntArgs.fixedValue = TXCAMERAPOSITIONMODE_USEPOSITIONXYZ;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCAMERAPOSITIONMODE_TOTAL-1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCAMERAPOSITIONMODE_TOTAL-1;
	cam1PositionMode = createModParameter(holdModParamIntArgs);
    parameters.add(cam1PositionMode->parameters);
    
    holdModParamFloatArgs.name = "cam1PositionX";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
	cam1PositionX = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1PositionX->parameters);
    
    holdModParamFloatArgs.name = "cam1PositionY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
	cam1PositionY = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1PositionY->parameters);
    
    holdModParamFloatArgs.name = "cam1PositionZ";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
	cam1PositionZ = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1PositionZ->parameters);
    
    holdModParamFloatArgs.name = "cam1TruckX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
	cam1TruckX = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1TruckX->parameters);
    
    holdModParamBoolArgs.name = "cam1TruckXTrigger";
    holdModParamBoolArgs.fixedValue = false;
    cam1TruckXTrigger = createModParameter(holdModParamBoolArgs);
    parameters.add(cam1TruckXTrigger->parameters);
    
    holdModParamFloatArgs.name = "cam1BoomY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
	cam1BoomY = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1BoomY->parameters);
    
    holdModParamBoolArgs.name = "cam1BoomYTrigger";
    holdModParamBoolArgs.fixedValue = false;
    cam1BoomYTrigger = createModParameter(holdModParamBoolArgs);
    parameters.add(cam1BoomYTrigger->parameters);
    
    holdModParamFloatArgs.name = "cam1DollyZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
	cam1DollyZ = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1DollyZ->parameters);
    
    holdModParamBoolArgs.name = "cam1DollyZTrigger";
    holdModParamBoolArgs.fixedValue = false;
    cam1DollyZTrigger = createModParameter(holdModParamBoolArgs);
    parameters.add(cam1DollyZTrigger->parameters);
    
    holdModParamBoolArgs.name = "cam1FreezePosition";
    holdModParamBoolArgs.fixedValue = false;
    cam1FreezePosition = createModParameter(holdModParamBoolArgs);
    parameters.add(cam1FreezePosition->parameters);
    
    holdModParamBoolArgs.name = "cam1ResetToPositionXYZ";
    holdModParamBoolArgs.fixedValue = false;
    cam1ResetToPositionXYZ = createModParameter(holdModParamBoolArgs);
    parameters.add(cam1ResetToPositionXYZ->parameters);
    
    holdModParamFloatArgs.name = "cam1OrbitPointX";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
	cam1OrbitPointX = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1OrbitPointX->parameters);
    
    holdModParamFloatArgs.name = "cam1OrbitPointY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
	cam1OrbitPointY = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1OrbitPointY->parameters);
    
    holdModParamFloatArgs.name = "cam1OrbitPointZ";
    holdModParamFloatArgs.fixedValue = -0.5;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 0.0;
	cam1OrbitPointZ = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1OrbitPointZ->parameters);
    
    holdModParamFloatArgs.name = "cam1OrbitLongitude";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	cam1OrbitLongitude = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1OrbitLongitude->parameters);
    
    holdModParamFloatArgs.name = "cam1OrbitLatitude";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	cam1OrbitLatitude = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1OrbitLatitude->parameters);
    
    holdModParamFloatArgs.name = "cam1OrbitRadius";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 2.0;
	cam1OrbitRadius = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1OrbitRadius->parameters);
        
    /////    
    
    holdModParamIntArgs.name = "cam1OrientationMode";
    holdModParamIntArgs.fixedValue = TXCAMERAORIENTATIONMODE_USEROTATIONXYZ;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCAMERAORIENTATIONMODE_TOTAL-1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCAMERAORIENTATIONMODE_TOTAL-1;
	cam1OrientationMode = createModParameter(holdModParamIntArgs);
    parameters.add(cam1OrientationMode->parameters);
    
    holdModParamFloatArgs.name = "cam1RotationX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	cam1RotationX = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1RotationX->parameters);
    
    holdModParamFloatArgs.name = "cam1RotationY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	cam1RotationY = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1RotationY->parameters);
    
    holdModParamFloatArgs.name = "cam1RotationZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	cam1RotationZ = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1RotationZ->parameters);
    
    holdModParamFloatArgs.name = "cam1TiltX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	cam1TiltX = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1TiltX->parameters);
    
    holdModParamBoolArgs.name = "cam1TiltXTrigger";
    holdModParamBoolArgs.fixedValue = false;
    cam1TiltXTrigger = createModParameter(holdModParamBoolArgs);
    parameters.add(cam1TiltXTrigger->parameters);
    
    holdModParamFloatArgs.name = "cam1PanY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	cam1PanY = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1PanY->parameters);
    
    holdModParamBoolArgs.name = "cam1PanYTrigger";
    holdModParamBoolArgs.fixedValue = false;
    cam1PanYTrigger = createModParameter(holdModParamBoolArgs);
    parameters.add(cam1PanYTrigger->parameters);
    
    holdModParamFloatArgs.name = "cam1RollZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	cam1RollZ = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1RollZ->parameters);
    
    holdModParamBoolArgs.name = "cam1RollZTrigger";
    holdModParamBoolArgs.fixedValue = false;
    cam1RollZTrigger = createModParameter(holdModParamBoolArgs);
    parameters.add(cam1RollZTrigger->parameters);
    
    holdModParamBoolArgs.name = "cam1FreezeRotation";
    holdModParamBoolArgs.fixedValue = false;
    cam1FreezeRotation = createModParameter(holdModParamBoolArgs);
    parameters.add(cam1FreezeRotation->parameters);
    
    holdModParamBoolArgs.name = "cam1ResetToRotationXYZ";
    holdModParamBoolArgs.fixedValue = false;
    cam1ResetToRotationXYZ = createModParameter(holdModParamBoolArgs);
    parameters.add(cam1ResetToRotationXYZ->parameters);
    
    holdModParamFloatArgs.name = "cam1LookAtPointX";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
	cam1LookAtPointX = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1LookAtPointX->parameters);
    
    holdModParamFloatArgs.name = "cam1LookAtPointY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
	cam1LookAtPointY = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1LookAtPointY->parameters);
    
    holdModParamFloatArgs.name = "cam1LookAtPointZ";
    holdModParamFloatArgs.fixedValue = -0.5;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 0.0;
	cam1LookAtPointZ = createModParameter(holdModParamFloatArgs);
    parameters.add(cam1LookAtPointZ->parameters);
    
    /////////
    
    holdModParamBoolArgs.name = "cam2Orthographic";
    holdModParamBoolArgs.fixedValue = false;
    cam2Orthographic = createModParameter(holdModParamBoolArgs);
    parameters.add(cam2Orthographic->parameters);
    
    holdModParamFloatArgs.name = "cam2FieldOfViewDegrees";
    holdModParamFloatArgs.fixedValue = 60.0;
    holdModParamFloatArgs.hardMin = 10.0;
    holdModParamFloatArgs.hardMax = 170.0;
    holdModParamFloatArgs.softMin = 10.0;
    holdModParamFloatArgs.softMax = 170.0;
    cam2FieldOfViewDegrees = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2FieldOfViewDegrees->parameters);
    
    holdModParamFloatArgs.name = "cam2NearClipDistance";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    cam2NearClipDistance = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2NearClipDistance->parameters);
    
    holdModParamFloatArgs.name = "cam2FarClipDistance";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 4.0;
    cam2FarClipDistance = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2FarClipDistance->parameters);
    
    holdModParamFloatArgs.name = "cam2LensOffsetX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1;
    cam2LensOffsetX = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2LensOffsetX->parameters);
    
    holdModParamFloatArgs.name = "cam2LensOffsetY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1;
    cam2LensOffsetY = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2LensOffsetY->parameters);
    
    holdModParamBoolArgs.name = "cam2ForceAspectRatio";
    holdModParamBoolArgs.fixedValue = false;
    cam2ForceAspectRatio = createModParameter(holdModParamBoolArgs);
    parameters.add(cam2ForceAspectRatio->parameters);
    
    holdModParamFloatArgs.name = "cam2AspectRatioWidth";
    holdModParamFloatArgs.fixedValue = 16.0;
    holdModParamFloatArgs.hardMin = 1.0;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 1.0;
    holdModParamFloatArgs.softMax = 100.0;
    cam2AspectRatioWidth = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2AspectRatioWidth->parameters);
    
    holdModParamFloatArgs.name = "cam2AspectRatioHeight";
    holdModParamFloatArgs.fixedValue = 9.0;
    holdModParamFloatArgs.hardMin = 1.0;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 1.0;
    holdModParamFloatArgs.softMax = 100.0;
    cam2AspectRatioHeight = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2AspectRatioHeight->parameters);
    
    holdModParamIntArgs.name = "cam2PositionMode";
    holdModParamIntArgs.fixedValue = TXCAMERAPOSITIONMODE_USEPOSITIONXYZ;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCAMERAPOSITIONMODE_TOTAL-1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCAMERAPOSITIONMODE_TOTAL-1;
    cam2PositionMode = createModParameter(holdModParamIntArgs);
    parameters.add(cam2PositionMode->parameters);
    
    holdModParamFloatArgs.name = "cam2PositionX";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
    cam2PositionX = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2PositionX->parameters);
    
    holdModParamFloatArgs.name = "cam2PositionY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
    cam2PositionY = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2PositionY->parameters);
    
    holdModParamFloatArgs.name = "cam2PositionZ";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
    cam2PositionZ = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2PositionZ->parameters);
    
    holdModParamFloatArgs.name = "cam2TruckX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
    cam2TruckX = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2TruckX->parameters);
    
    holdModParamBoolArgs.name = "cam2TruckXTrigger";
    holdModParamBoolArgs.fixedValue = false;
    cam2TruckXTrigger = createModParameter(holdModParamBoolArgs);
    parameters.add(cam2TruckXTrigger->parameters);
    
    holdModParamFloatArgs.name = "cam2BoomY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
    cam2BoomY = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2BoomY->parameters);
    
    holdModParamBoolArgs.name = "cam2BoomYTrigger";
    holdModParamBoolArgs.fixedValue = false;
    cam2BoomYTrigger = createModParameter(holdModParamBoolArgs);
    parameters.add(cam2BoomYTrigger->parameters);
    
    holdModParamFloatArgs.name = "cam2DollyZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
    cam2DollyZ = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2DollyZ->parameters);
    
    holdModParamBoolArgs.name = "cam2DollyZTrigger";
    holdModParamBoolArgs.fixedValue = false;
    cam2DollyZTrigger = createModParameter(holdModParamBoolArgs);
    parameters.add(cam2DollyZTrigger->parameters);
    
    holdModParamBoolArgs.name = "cam2FreezePosition";
    holdModParamBoolArgs.fixedValue = false;
    cam2FreezePosition = createModParameter(holdModParamBoolArgs);
    parameters.add(cam2FreezePosition->parameters);
    
    holdModParamBoolArgs.name = "cam2ResetToPositionXYZ";
    holdModParamBoolArgs.fixedValue = false;
    cam2ResetToPositionXYZ = createModParameter(holdModParamBoolArgs);
    parameters.add(cam2ResetToPositionXYZ->parameters);
    
    holdModParamFloatArgs.name = "cam2OrbitPointX";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
    cam2OrbitPointX = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2OrbitPointX->parameters);
    
    holdModParamFloatArgs.name = "cam2OrbitPointY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
    cam2OrbitPointY = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2OrbitPointY->parameters);
    
    holdModParamFloatArgs.name = "cam2OrbitPointZ";
    holdModParamFloatArgs.fixedValue = -0.5;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 0.0;
    cam2OrbitPointZ = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2OrbitPointZ->parameters);
    
    holdModParamFloatArgs.name = "cam2OrbitLongitude";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
    cam2OrbitLongitude = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2OrbitLongitude->parameters);
    
    holdModParamFloatArgs.name = "cam2OrbitLatitude";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
    cam2OrbitLatitude = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2OrbitLatitude->parameters);
    
    holdModParamFloatArgs.name = "cam2OrbitRadius";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 2.0;
    cam2OrbitRadius = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2OrbitRadius->parameters);
    
    /////
    
    holdModParamIntArgs.name = "cam2OrientationMode";
    holdModParamIntArgs.fixedValue = TXCAMERAORIENTATIONMODE_USEROTATIONXYZ;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCAMERAORIENTATIONMODE_TOTAL-1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCAMERAORIENTATIONMODE_TOTAL-1;
    cam2OrientationMode = createModParameter(holdModParamIntArgs);
    parameters.add(cam2OrientationMode->parameters);
    
    holdModParamFloatArgs.name = "cam2RotationX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
    cam2RotationX = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2RotationX->parameters);
    
    holdModParamFloatArgs.name = "cam2RotationY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
    cam2RotationY = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2RotationY->parameters);
    
    holdModParamFloatArgs.name = "cam2RotationZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
    cam2RotationZ = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2RotationZ->parameters);
    
    holdModParamFloatArgs.name = "cam2TiltX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
    cam2TiltX = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2TiltX->parameters);
    
    holdModParamBoolArgs.name = "cam2TiltXTrigger";
    holdModParamBoolArgs.fixedValue = false;
    cam2TiltXTrigger = createModParameter(holdModParamBoolArgs);
    parameters.add(cam2TiltXTrigger->parameters);
    
    holdModParamFloatArgs.name = "cam2PanY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
    cam2PanY = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2PanY->parameters);
    
    holdModParamBoolArgs.name = "cam2PanYTrigger";
    holdModParamBoolArgs.fixedValue = false;
    cam2PanYTrigger = createModParameter(holdModParamBoolArgs);
    parameters.add(cam2PanYTrigger->parameters);
    
    holdModParamFloatArgs.name = "cam2RollZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
    cam2RollZ = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2RollZ->parameters);
    
    holdModParamBoolArgs.name = "cam2RollZTrigger";
    holdModParamBoolArgs.fixedValue = false;
    cam2RollZTrigger = createModParameter(holdModParamBoolArgs);
    parameters.add(cam2RollZTrigger->parameters);
    
    holdModParamBoolArgs.name = "cam2FreezeRotation";
    holdModParamBoolArgs.fixedValue = false;
    cam2FreezeRotation = createModParameter(holdModParamBoolArgs);
    parameters.add(cam2FreezeRotation->parameters);
    
    holdModParamBoolArgs.name = "cam2ResetToRotationXYZ";
    holdModParamBoolArgs.fixedValue = false;
    cam2ResetToRotationXYZ = createModParameter(holdModParamBoolArgs);
    parameters.add(cam2ResetToRotationXYZ->parameters);
    
    holdModParamFloatArgs.name = "cam2LookAtPointX";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
    cam2LookAtPointX = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2LookAtPointX->parameters);
    
    holdModParamFloatArgs.name = "cam2LookAtPointY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1;
    cam2LookAtPointY = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2LookAtPointY->parameters);
    
    holdModParamFloatArgs.name = "cam2LookAtPointZ";
    holdModParamFloatArgs.fixedValue = -0.5;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 0.0;
    cam2LookAtPointZ = createModParameter(holdModParamFloatArgs);
    parameters.add(cam2LookAtPointZ->parameters);
    
    // add listener to relevent parameters:
    smoothLighting.addListener(this, &TXDrawScene::smoothLightingChanged);

    // initialise
    oldCam1ResetToPositionXYZ = false;
    oldCam1ResetToRotationXYZ = false;
    ofSetSmoothLighting(true);
    
    // dont' flip vertical axis for both cameras
//    cam1.setVFlip(false);
//    cam2.setVFlip(false);
    cameraRotateZOffset = 180;  //not working so do manually
}

void TXDrawScene::update(){
    // sets camera position and orientation
    float holdFrameTime = 1.0 / parentSystem->targetFrameRate;
    ofVec3f holdOrbitPoint;
    float holdMaxWidth = getMaxWidth();
    float holdMaxHeight = getMaxHeight();
    float holdMaxDepth = getMaxDepth();
    
    int holdcameraSelect = cameraSelect->getInt();
    if (holdcameraSelect == 1) {
        
        bool newCam1ResetToPositionXYZ;
        bool holdCam1ResetToPositionXYZ;
        bool newCam1TruckXTrigger;
        bool newCam1BoomYTrigger;
        bool newCam1DollyZTrigger;
        bool holdCam1TruckXTrigger;
        bool holdCam1BoomYTrigger;
        bool holdCam1DollyZTrigger;
        
        if (cam1Orthographic->getBool()) {
            cam1.enableOrtho();
        } else {
            cam1.disableOrtho();
        };
        cam1.setupPerspective(false, cam1FieldOfViewDegrees->getFloat(), cam1NearClipDistance->getFloat() * holdMaxDepth, cam1FarClipDistance->getFloat() * holdMaxDepth, ofVec2f(cam1LensOffsetX->getFloat(), cam1LensOffsetY->getFloat()));
        if (cam1ForceAspectRatio->getBool() && (cam1Orthographic->getBool() == false)) {
            cam1.setAspectRatio(cam1AspectRatioWidth->getFloat() / cam1AspectRatioHeight->getFloat());
        };
        switch (cam1PositionMode->getInt()) {
            case TXCAMERAPOSITIONMODE_USEPOSITIONXYZ:
                cam1.setPosition(cam1PositionX->getFloat() * holdMaxWidth, cam1PositionY->getFloat() * holdMaxHeight, cam1PositionZ->getFloat() * holdMaxDepth);
                break;
            case TXCAMERAPOSITIONMODE_TRUCKBOOMDOLLY:
                newCam1ResetToPositionXYZ = cam1ResetToPositionXYZ->getBool();
                holdCam1ResetToPositionXYZ = (newCam1ResetToPositionXYZ && (newCam1ResetToPositionXYZ != oldCam1ResetToPositionXYZ));
                // check for reset else move
                if (holdCam1ResetToPositionXYZ) {
                    cam1.setPosition(cam1PositionX->getFloat() * holdMaxWidth, cam1PositionY->getFloat() * holdMaxHeight, cam1PositionZ->getFloat() * holdMaxDepth);
                } else {
                    if (!cam1FreezePosition->getBool()) {
                        cam1.truck(cam1TruckX->getFloat() * holdMaxWidth * holdFrameTime);
                        cam1.boom(cam1BoomY->getFloat() * holdMaxHeight * holdFrameTime);
                        cam1.dolly(cam1DollyZ->getFloat() * holdMaxHeight * holdFrameTime);
                    };
                };
                oldCam1ResetToPositionXYZ = newCam1ResetToPositionXYZ;
                break;
            case TXCAMERAPOSITIONMODE_TRIGTRUCKBOOMDOLLY:
                newCam1ResetToPositionXYZ = cam1ResetToPositionXYZ->getBool();
                holdCam1ResetToPositionXYZ = (newCam1ResetToPositionXYZ && (newCam1ResetToPositionXYZ != oldCam1ResetToPositionXYZ));
                // check for reset else move if triggered
                if (holdCam1ResetToPositionXYZ) {
                    cam1.setPosition(cam1PositionX->getFloat() * holdMaxWidth, cam1PositionY->getFloat() * holdMaxHeight, cam1PositionZ->getFloat() * holdMaxDepth);
                } else {
                    if (!cam1FreezePosition->getBool()) {
                        // move if triggered
                        newCam1TruckXTrigger = cam1TruckXTrigger->getBool();
                        newCam1BoomYTrigger = cam1BoomYTrigger->getBool();
                        newCam1DollyZTrigger = cam1DollyZTrigger->getBool();
                        holdCam1TruckXTrigger = (newCam1TruckXTrigger && (newCam1TruckXTrigger != oldCam1TruckXTrigger));
                        holdCam1BoomYTrigger = (newCam1BoomYTrigger && (newCam1BoomYTrigger != oldCam1BoomYTrigger));
                        holdCam1DollyZTrigger = (newCam1DollyZTrigger && (newCam1DollyZTrigger != oldCam1DollyZTrigger));
                        if (holdCam1TruckXTrigger) {
                            cam1.truck(cam1TruckX->getFloat() * holdMaxWidth);
                        };
                        if (holdCam1BoomYTrigger) {
                            cam1.boom(cam1BoomY->getFloat() * holdMaxHeight);
                        };
                        if (holdCam1DollyZTrigger) {
                            cam1.dolly(cam1DollyZ->getFloat() * holdMaxDepth);
                        };
                    };
                };
                oldCam1ResetToPositionXYZ = newCam1ResetToPositionXYZ;
                oldCam1TruckXTrigger = newCam1TruckXTrigger;
                oldCam1BoomYTrigger = newCam1BoomYTrigger;
                oldCam1DollyZTrigger = newCam1DollyZTrigger;
                break;
            case TXCAMERAPOSITIONMODE_ORBIT:
                holdOrbitPoint = ofVec3f(cam1OrbitPointX->getFloat() * holdMaxWidth, cam1OrbitPointY->getFloat() * holdMaxHeight, cam1OrbitPointZ->getFloat() * holdMaxDepth);
                cam1.orbit(cam1OrbitLongitude->getFloat(), cam1OrbitLatitude->getFloat(), cam1OrbitRadius->getFloat() * holdMaxWidth, holdOrbitPoint);
                break;
            default:
                cam1.setPosition(cam1PositionX->getFloat() * holdMaxWidth, cam1PositionY->getFloat() * holdMaxHeight, cam1PositionZ->getFloat() * holdMaxDepth);
                break;
        }
        
        bool newCam1ResetToRotationXYZ;
        bool holdCam1ResetToRotationXYZ;
        bool newCam1TiltXTrigger;
        bool newCam1PanYTrigger;
        bool newCam1RollZTrigger;
        bool holdCam1TiltXTrigger;
        bool holdCam1PanYTrigger;
        bool holdCam1RollZTrigger;
        ofVec3f holdLookAtPoint;
        ofVec3f holdOrientation;
        
        switch (cam1OrientationMode->getInt()) {
            case TXCAMERAORIENTATIONMODE_USEROTATIONXYZ:
                holdOrientation = ofVec3f(cam1RotationX->getFloat(), cam1RotationY->getFloat(), cam1RotationZ->getFloat()+cameraRotateZOffset);
                cam1.setOrientation(holdOrientation);
                break;
            case TXCAMERAORIENTATIONMODE_TILTPANROLL:
                newCam1ResetToRotationXYZ = cam1ResetToRotationXYZ->getBool();
                holdCam1ResetToRotationXYZ = (newCam1ResetToRotationXYZ && (newCam1ResetToRotationXYZ != oldCam1ResetToRotationXYZ));
                // check for reset else move
                if (holdCam1ResetToRotationXYZ) {
                    holdOrientation = ofVec3f(cam1RotationX->getFloat(), cam1RotationY->getFloat(), cam1RotationZ->getFloat()+cameraRotateZOffset);
                    cam1.setOrientation(holdOrientation);
                } else {
                    if (!cam1FreezeRotation->getBool()) {
                        cam1.tilt(cam1TiltX->getFloat() * holdFrameTime);
                        cam1.pan(cam1PanY->getFloat() * holdFrameTime);
                        cam1.roll(cam1RollZ->getFloat() * holdFrameTime);
                    };
                };
                oldCam1ResetToRotationXYZ = newCam1ResetToRotationXYZ;
                break;
            case TXCAMERAORIENTATIONMODE_TRIGTILTPANROLL:
                newCam1ResetToRotationXYZ = cam1ResetToRotationXYZ->getBool();
                holdCam1ResetToRotationXYZ = (newCam1ResetToRotationXYZ && (newCam1ResetToRotationXYZ != oldCam1ResetToRotationXYZ));
                // check for reset else move
                if (holdCam1ResetToRotationXYZ) {
                    holdOrientation = ofVec3f(cam1RotationX->getFloat(), cam1RotationY->getFloat(), cam1RotationZ->getFloat()+cameraRotateZOffset);
                    cam1.setOrientation(holdOrientation);
                } else {
                    if (!cam1FreezeRotation->getBool()) {
                        // move if triggered
                        newCam1TiltXTrigger = cam1TiltXTrigger->getBool();
                        newCam1PanYTrigger = cam1PanYTrigger->getBool();
                        newCam1RollZTrigger = cam1RollZTrigger->getBool();
                        holdCam1TiltXTrigger = (newCam1TiltXTrigger && (newCam1TiltXTrigger != oldCam1TiltXTrigger));
                        holdCam1PanYTrigger = (newCam1PanYTrigger && (newCam1PanYTrigger != oldCam1PanYTrigger));
                        holdCam1RollZTrigger = (newCam1RollZTrigger && (newCam1RollZTrigger != oldCam1RollZTrigger));
                        if (holdCam1TiltXTrigger) {
                            cam1.tilt(cam1TiltX->getFloat());
                        };
                        if (holdCam1PanYTrigger) {
                            cam1.pan(cam1PanY->getFloat());
                        };
                        if (holdCam1RollZTrigger) {
                            cam1.roll(cam1RollZ->getFloat());
                        };
                    };
                };
                oldCam1ResetToRotationXYZ = newCam1ResetToRotationXYZ;
                oldCam1TiltXTrigger = newCam1TiltXTrigger;
                oldCam1PanYTrigger = newCam1PanYTrigger;
                oldCam1RollZTrigger = newCam1RollZTrigger;
                break;
            case TXCAMERAORIENTATIONMODE_LOOKATPOINT:
                holdLookAtPoint = ofVec3f(cam1LookAtPointX->getFloat() * holdMaxWidth, cam1LookAtPointY->getFloat() * holdMaxHeight, cam1LookAtPointZ->getFloat() * holdMaxDepth);
                cam1.lookAt(holdLookAtPoint);
                break;
            default:
                cam1.tilt(cam1RotationX->getFloat());
                cam1.pan(cam1RotationY->getFloat());
                cam1.roll(cam1RotationZ->getFloat()+cameraRotateZOffset);
                break;
        }
    };
    if (holdcameraSelect == 2) {
        
        bool newCam2ResetToPositionXYZ;
        bool holdCam2ResetToPositionXYZ;
        bool newCam2TruckXTrigger;
        bool newCam2BoomYTrigger;
        bool newCam2DollyZTrigger;
        bool holdCam2TruckXTrigger;
        bool holdCam2BoomYTrigger;
        bool holdCam2DollyZTrigger;
        
        if (cam2Orthographic->getBool()) {
            cam2.enableOrtho();
        } else {
            cam2.disableOrtho();
        };
        cam2.setupPerspective(false, cam2FieldOfViewDegrees->getFloat(), cam2NearClipDistance->getFloat() * holdMaxDepth, cam2FarClipDistance->getFloat() * holdMaxDepth, ofVec2f(cam2LensOffsetX->getFloat(), cam2LensOffsetY->getFloat()));
        if (cam2ForceAspectRatio->getBool() && (cam2Orthographic->getBool() == false)) {
            cam2.setAspectRatio(cam2AspectRatioWidth->getFloat() / cam2AspectRatioHeight->getFloat());
        };
        switch (cam2PositionMode->getInt()) {
            case TXCAMERAPOSITIONMODE_USEPOSITIONXYZ:
                cam2.setPosition(cam2PositionX->getFloat() * holdMaxWidth, cam2PositionY->getFloat() * holdMaxHeight, cam2PositionZ->getFloat() * holdMaxDepth);
                break;
            case TXCAMERAPOSITIONMODE_TRUCKBOOMDOLLY:
                newCam2ResetToPositionXYZ = cam2ResetToPositionXYZ->getBool();
                holdCam2ResetToPositionXYZ = (newCam2ResetToPositionXYZ && (newCam2ResetToPositionXYZ != oldCam2ResetToPositionXYZ));
                // check for reset else move
                if (holdCam2ResetToPositionXYZ) {
                    cam2.setPosition(cam2PositionX->getFloat() * holdMaxWidth, cam2PositionY->getFloat() * holdMaxHeight, cam2PositionZ->getFloat() * holdMaxDepth);
                } else {
                    if (!cam2FreezePosition->getBool()) {
                        cam2.truck(cam2TruckX->getFloat() * holdMaxWidth * holdFrameTime);
                        cam2.boom(cam2BoomY->getFloat() * holdMaxHeight * holdFrameTime);
                        cam2.dolly(cam2DollyZ->getFloat() * holdMaxHeight * holdFrameTime);
                    };
                };
                oldCam2ResetToPositionXYZ = newCam2ResetToPositionXYZ;
                break;
            case TXCAMERAPOSITIONMODE_TRIGTRUCKBOOMDOLLY:
                newCam2ResetToPositionXYZ = cam2ResetToPositionXYZ->getBool();
                holdCam2ResetToPositionXYZ = (newCam2ResetToPositionXYZ && (newCam2ResetToPositionXYZ != oldCam2ResetToPositionXYZ));
                // check for reset else move if triggered
                if (holdCam2ResetToPositionXYZ) {
                    cam2.setPosition(cam2PositionX->getFloat() * holdMaxWidth, cam2PositionY->getFloat() * holdMaxHeight, cam2PositionZ->getFloat() * holdMaxDepth);
                } else {
                    if (!cam2FreezePosition->getBool()) {
                        // move if triggered
                        newCam2TruckXTrigger = cam2TruckXTrigger->getBool();
                        newCam2BoomYTrigger = cam2BoomYTrigger->getBool();
                        newCam2DollyZTrigger = cam2DollyZTrigger->getBool();
                        holdCam2TruckXTrigger = (newCam2TruckXTrigger && (newCam2TruckXTrigger != oldCam2TruckXTrigger));
                        holdCam2BoomYTrigger = (newCam2BoomYTrigger && (newCam2BoomYTrigger != oldCam2BoomYTrigger));
                        holdCam2DollyZTrigger = (newCam2DollyZTrigger && (newCam2DollyZTrigger != oldCam2DollyZTrigger));
                        if (holdCam2TruckXTrigger) {
                            cam2.truck(cam2TruckX->getFloat() * holdMaxWidth);
                        };
                        if (holdCam2BoomYTrigger) {
                            cam2.boom(cam2BoomY->getFloat() * holdMaxHeight);
                        };
                        if (holdCam2DollyZTrigger) {
                            cam2.dolly(cam2DollyZ->getFloat() * holdMaxDepth);
                        };
                    };
                };
                oldCam2ResetToPositionXYZ = newCam2ResetToPositionXYZ;
                oldCam2TruckXTrigger = newCam2TruckXTrigger;
                oldCam2BoomYTrigger = newCam2BoomYTrigger;
                oldCam2DollyZTrigger = newCam2DollyZTrigger;
                break;
            case TXCAMERAPOSITIONMODE_ORBIT:
                holdOrbitPoint = ofVec3f(cam2OrbitPointX->getFloat() * holdMaxWidth, cam2OrbitPointY->getFloat() * holdMaxHeight, cam2OrbitPointZ->getFloat() * holdMaxDepth);
                cam2.orbit(cam2OrbitLongitude->getFloat(), cam2OrbitLatitude->getFloat(), cam2OrbitRadius->getFloat() * holdMaxWidth, holdOrbitPoint);
                break;
            default:
                cam2.setPosition(cam2PositionX->getFloat() * holdMaxWidth, cam2PositionY->getFloat() * holdMaxHeight, cam2PositionZ->getFloat() * holdMaxDepth);
                break;
        }
        
        bool newCam2ResetToRotationXYZ;
        bool holdCam2ResetToRotationXYZ;
        bool newCam2TiltXTrigger;
        bool newCam2PanYTrigger;
        bool newCam2RollZTrigger;
        bool holdCam2TiltXTrigger;
        bool holdCam2PanYTrigger;
        bool holdCam2RollZTrigger;
        ofVec3f holdLookAtPoint;
        ofVec3f holdOrientation;
        
        switch (cam2OrientationMode->getInt()) {
            case TXCAMERAORIENTATIONMODE_USEROTATIONXYZ:
                holdOrientation = ofVec3f(cam2RotationX->getFloat(), cam2RotationY->getFloat(), cam2RotationZ->getFloat()+cameraRotateZOffset);
                cam2.setOrientation(holdOrientation);
                break;
            case TXCAMERAORIENTATIONMODE_TILTPANROLL:
                newCam2ResetToRotationXYZ = cam2ResetToRotationXYZ->getBool();
                holdCam2ResetToRotationXYZ = (newCam2ResetToRotationXYZ && (newCam2ResetToRotationXYZ != oldCam2ResetToRotationXYZ));
                // check for reset else move
                if (holdCam2ResetToRotationXYZ) {
                    holdOrientation = ofVec3f(cam2RotationX->getFloat(), cam2RotationY->getFloat(), cam2RotationZ->getFloat()+cameraRotateZOffset);
                    cam2.setOrientation(holdOrientation);
                } else {
                    if (!cam2FreezeRotation->getBool()) {
                        cam2.tilt(cam2TiltX->getFloat() * holdFrameTime);
                        cam2.pan(cam2PanY->getFloat() * holdFrameTime);
                        cam2.roll(cam2RollZ->getFloat() * holdFrameTime);
                    };
                };
                oldCam2ResetToRotationXYZ = newCam2ResetToRotationXYZ;
                break;
            case TXCAMERAORIENTATIONMODE_TRIGTILTPANROLL:
                newCam2ResetToRotationXYZ = cam2ResetToRotationXYZ->getBool();
                holdCam2ResetToRotationXYZ = (newCam2ResetToRotationXYZ && (newCam2ResetToRotationXYZ != oldCam2ResetToRotationXYZ));
                // check for reset else move
                if (holdCam2ResetToRotationXYZ) {
                    holdOrientation = ofVec3f(cam2RotationX->getFloat(), cam2RotationY->getFloat(), cam2RotationZ->getFloat()+cameraRotateZOffset);
                    cam2.setOrientation(holdOrientation);
                } else {
                    if (!cam2FreezeRotation->getBool()) {
                        // move if triggered
                        newCam2TiltXTrigger = cam2TiltXTrigger->getBool();
                        newCam2PanYTrigger = cam2PanYTrigger->getBool();
                        newCam2RollZTrigger = cam2RollZTrigger->getBool();
                        holdCam2TiltXTrigger = (newCam2TiltXTrigger && (newCam2TiltXTrigger != oldCam2TiltXTrigger));
                        holdCam2PanYTrigger = (newCam2PanYTrigger && (newCam2PanYTrigger != oldCam2PanYTrigger));
                        holdCam2RollZTrigger = (newCam2RollZTrigger && (newCam2RollZTrigger != oldCam2RollZTrigger));
                        if (holdCam2TiltXTrigger) {
                            cam2.tilt(cam2TiltX->getFloat());
                        };
                        if (holdCam2PanYTrigger) {
                            cam2.pan(cam2PanY->getFloat());
                        };
                        if (holdCam2RollZTrigger) {
                            cam2.roll(cam2RollZ->getFloat());
                        };
                    };
                };
                oldCam2ResetToRotationXYZ = newCam2ResetToRotationXYZ;
                oldCam2TiltXTrigger = newCam2TiltXTrigger;
                oldCam2PanYTrigger = newCam2PanYTrigger;
                oldCam2RollZTrigger = newCam2RollZTrigger;
                break;
            case TXCAMERAORIENTATIONMODE_LOOKATPOINT:
                holdLookAtPoint = ofVec3f(cam2LookAtPointX->getFloat() * holdMaxWidth, cam2LookAtPointY->getFloat() * holdMaxHeight, cam2LookAtPointZ->getFloat() * holdMaxDepth);
                cam2.lookAt(holdLookAtPoint);
                break;
            default:
                cam2.tilt(cam2RotationX->getFloat());
                cam2.pan(cam2RotationY->getFloat());
                cam2.roll(cam2RotationZ->getFloat()+cameraRotateZOffset);
                break;
        }
    };
}

void TXDrawScene::draw(){
    if (!drawActive->getBool()) {
        return;
    };
    
    ofEnableDepthTest();
    
    // begin camera //
    int holdcameraSelect = cameraSelect->getInt();
    if (holdcameraSelect == 1) {
        cam1.begin();
    };
    if (holdcameraSelect == 2) {
        cam2.begin();
    };

    // enable lighting //
    bool holduseLighting = useLighting->getBool();
    bool holdlight1Active = light1Active->getBool();
    bool holdlight2Active = light2Active->getBool();
    bool holdlight3Active = light3Active->getBool();

    if (holduseLighting) {
        ofEnableLighting();
        // activate the lights //
        if (holdlight1Active) {
            light1.enable();
            setLight1DiffuseColor();
            setLight1AmbientColor();
            setLight1SpecularColor();
            setLight1Position();
            setLight1Orientation();
            switch (light1Type->getInt()) {
                case TXLIGHTTYPE_POINT:
                    light1.setPointLight();
                    break;
                case TXLIGHTTYPE_DIRECTIONAL:
                    light1.setDirectional();
                    break;
                case TXLIGHTTYPE_SPOT:
                    light1.setSpotlight();
                    light1.setSpotConcentration(light1SpotConcentration->getInt());
                    light1.setSpotlightCutOff (light1SpotlightAngle->getFloat());
                    break;
                default:
                    break;
            }
        };
        if (holdlight2Active) {
            light2.enable();
            setLight2DiffuseColor();
            setLight2AmbientColor();
            setLight2SpecularColor();
            setLight2Position();
            setLight2Orientation();
            switch (light2Type->getInt()) {
                case TXLIGHTTYPE_POINT:
                    light2.setPointLight();
                    break;
                case TXLIGHTTYPE_DIRECTIONAL:
                    light2.setDirectional();
                    break;
                case TXLIGHTTYPE_SPOT:
                    light2.setSpotlight();
                    light2.setSpotConcentration(light2SpotConcentration->getInt());
                    light2.setSpotlightCutOff (light2SpotlightAngle->getFloat());
                    break;
                default:
                    break;
            }
        };
        if (holdlight3Active) {
            light3.enable();
            setLight3DiffuseColor();
            setLight3AmbientColor();
            setLight3SpecularColor();
            setLight3Position();
            setLight3Orientation();
            switch (light3Type->getInt()) {
                case TXLIGHTTYPE_POINT:
                    light3.setPointLight();
                    break;
                case TXLIGHTTYPE_DIRECTIONAL:
                    light3.setDirectional();
                    break;
                case TXLIGHTTYPE_SPOT:
                    light3.setSpotlight();
                    light3.setSpotConcentration(light3SpotConcentration->getInt());
                    light3.setSpotlightCutOff (light3SpotlightAngle->getFloat());
                    break;
                default:
                    break;
            }
        };
    };

    // draw layers
    TXDrawLayersBase::draw((TXDRAWLAYERSRULE)drawLayersRule->getInt());

    // disable lighting //
    if (holduseLighting) {
        if (holdlight1Active) light1.disable();
        if (holdlight2Active) light2.disable();
        if (holdlight3Active) light3.disable();
        ofDisableLighting();
        if (drawLights) {
            ofSetColor( light1.getDiffuseColor() );
            if(holdlight1Active ) light1.draw();
            ofSetColor( light2.getDiffuseColor() );
            if(holdlight2Active ) light2.draw();
            ofSetColor( light3.getDiffuseColor() );
            if(holdlight3Active ) light3.draw();
        };
    };
    // end camera //
    if (holdcameraSelect == 1) {
        cam1.end();
    };
    if (holdcameraSelect == 2) {
        cam2.end();
    };
    ofDisableDepthTest();
    ofSetColor(255.0f);
}
    
void  TXDrawScene::smoothLightingChanged(bool & boolArg) {
    if (smoothLighting) {
        ofSetSmoothLighting(true);
    } else {
        ofSetSmoothLighting(false);
    };
}

// set methods
void  TXDrawScene::setLight1DiffuseColor() {
    ofColor holdColor =  TXFunctions::txGetColor(light1DiffuseColorHue->getFloat(),  light1DiffuseColorSaturation->getFloat(),  light1DiffuseColorBrightness->getFloat(),  1, light1DiffuseColorHueRotate->getFloat(), light1DiffuseColorHSBAsRGB->getBool());
    light1.setDiffuseColor(holdColor);
    if (light1UseDiffuseColorForAmbient) {
        light1.setAmbientColor(holdColor);
    };
    if (light1UseDiffuseColorForSpecular) {
        light1.setSpecularColor(holdColor);
    };
}

void  TXDrawScene::setLight1AmbientColor() {
    if (light1UseDiffuseColorForAmbient) {
        light1.setAmbientColor(light1.getDiffuseColor());
    } else {
        ofColor holdColor =  TXFunctions::txGetColor(light1AmbientColorHue->getFloat(),  light1AmbientColorSaturation->getFloat(),  light1AmbientColorBrightness->getFloat(),  1, light1AmbientColorHueRotate->getFloat(), light1AmbientColorHSBAsRGB->getBool());
        light1.setAmbientColor(holdColor);
    };
}

void  TXDrawScene::setLight1SpecularColor() {
    if (light1UseDiffuseColorForSpecular) {
        light1.setSpecularColor(light1.getDiffuseColor());
    } else {
        ofColor holdColor =  TXFunctions::txGetColor(light1SpecularColorHue->getFloat(),  light1SpecularColorSaturation->getFloat(),  light1SpecularColorBrightness->getFloat(),  1, light1SpecularColorHueRotate->getFloat(), light1SpecularColorHSBAsRGB->getBool());
        light1.setSpecularColor(holdColor);
    };
}

void  TXDrawScene::setLight1Position() {
    light1.setPosition(light1PositionX->getFloat() * getMaxWidth(), light1PositionY->getFloat() * getMaxHeight(), light1PositionZ->getFloat() * getMaxDepth());
}

void  TXDrawScene::setLight1Orientation() {
    light1.setOrientation(ofVec3f(light1OrientationX->getFloat(), light1OrientationY->getFloat(), light1OrientationZ->getFloat()));
}


void  TXDrawScene::setLight2DiffuseColor() {
    ofColor holdColor =  TXFunctions::txGetColor(light2DiffuseColorHue->getFloat(),  light2DiffuseColorSaturation->getFloat(),  light2DiffuseColorBrightness->getFloat(),  1, light2DiffuseColorHueRotate->getFloat(), light2DiffuseColorHSBAsRGB->getBool());
    if (light2DiffuseColorHSBAsRGB->getBool()) {
        holdColor.set( light2DiffuseColorHue->getFloat() * 255,  light2DiffuseColorSaturation->getFloat() * 255,  light2DiffuseColorBrightness->getFloat() * 255,  255);
    } else {
        holdColor = ofColor::fromHsb( light2DiffuseColorHue->getFloat() * 255,  light2DiffuseColorSaturation->getFloat() * 255,  light2DiffuseColorBrightness->getFloat() * 255,  255);
    };
    light2.setDiffuseColor(holdColor);
    if (light2UseDiffuseColorForAmbient) {
        light2.setAmbientColor(holdColor);
    };
    if (light2UseDiffuseColorForSpecular) {
        light2.setSpecularColor(holdColor);
    };
}

void  TXDrawScene::setLight2AmbientColor() {
    if (light2UseDiffuseColorForAmbient) {
        light2.setAmbientColor(light2.getDiffuseColor());
    } else {
        ofColor holdColor =  TXFunctions::txGetColor(light2AmbientColorHue->getFloat(),  light2AmbientColorSaturation->getFloat(),  light2AmbientColorBrightness->getFloat(),  1, light2AmbientColorHueRotate->getFloat(), light2AmbientColorHSBAsRGB->getBool());
        if (light2AmbientColorHSBAsRGB->getBool()) {
            holdColor.set( light2AmbientColorHue->getFloat() * 255,  light2AmbientColorSaturation->getFloat() * 255,  light2AmbientColorBrightness->getFloat() * 255,  255);
        } else {
            holdColor = ofColor::fromHsb( light2AmbientColorHue->getFloat() * 255,  light2AmbientColorSaturation->getFloat() * 255,  light2AmbientColorBrightness->getFloat() * 255,  255);
        };
        light2.setAmbientColor(holdColor);
    };
}

void  TXDrawScene::setLight2SpecularColor() {
    if (light2UseDiffuseColorForAmbient) {
        light2.setSpecularColor(light2.getDiffuseColor());
    } else {
        ofColor holdColor =  TXFunctions::txGetColor(light2SpecularColorHue->getFloat(),  light2SpecularColorSaturation->getFloat(),  light2SpecularColorBrightness->getFloat(),  1, light2SpecularColorHueRotate->getFloat(), light2SpecularColorHSBAsRGB->getBool());
        if (light2SpecularColorHSBAsRGB->getBool()) {
            holdColor.set( light2SpecularColorHue->getFloat() * 255,  light2SpecularColorSaturation->getFloat() * 255,  light2SpecularColorBrightness->getFloat() * 255,  255);
        } else {
            holdColor = ofColor::fromHsb( light2SpecularColorHue->getFloat() * 255,  light2SpecularColorSaturation->getFloat() * 255,  light2SpecularColorBrightness->getFloat() * 255,  255);
        };
        light2.setSpecularColor(holdColor);
    };
}

void  TXDrawScene::setLight2Position() {
    light2.setPosition(light2PositionX->getFloat(), light2PositionY->getFloat(), light2PositionZ->getFloat());
    light2.setPosition(light2PositionX->getFloat() * getMaxWidth(), light2PositionY->getFloat() * getMaxHeight(), light2PositionZ->getFloat() * getMaxDepth());
}

void  TXDrawScene::setLight2Orientation() {
    light2.setOrientation(ofVec3f(light2OrientationX->getFloat(), light2OrientationY->getFloat(), light2OrientationZ->getFloat()));
}


void  TXDrawScene::setLight3DiffuseColor() {
    ofColor holdColor =  TXFunctions::txGetColor(light3DiffuseColorHue->getFloat(),  light3DiffuseColorSaturation->getFloat(),  light3DiffuseColorBrightness->getFloat(),  1, light3DiffuseColorHueRotate->getFloat(), light3DiffuseColorHSBAsRGB->getBool());
    if (light3DiffuseColorHSBAsRGB->getBool()) {
        holdColor.set( light3DiffuseColorHue->getFloat() * 255,  light3DiffuseColorSaturation->getFloat() * 255,  light3DiffuseColorBrightness->getFloat() * 255,  255);
    } else {
        holdColor = ofColor::fromHsb( light3DiffuseColorHue->getFloat() * 255,  light3DiffuseColorSaturation->getFloat() * 255,  light3DiffuseColorBrightness->getFloat() * 255,  255);
    };
    light3.setDiffuseColor(holdColor);
    if (light3UseDiffuseColorForAmbient) {
        light3.setAmbientColor(holdColor);
    };
    if (light3UseDiffuseColorForSpecular) {
        light3.setSpecularColor(holdColor);
    };
}

void  TXDrawScene::setLight3AmbientColor() {
    if (light3UseDiffuseColorForAmbient) {
        light3.setAmbientColor(light3.getDiffuseColor());
    } else {
        ofColor holdColor =  TXFunctions::txGetColor(light3AmbientColorHue->getFloat(),  light3AmbientColorSaturation->getFloat(),  light3AmbientColorBrightness->getFloat(),  1, light3AmbientColorHueRotate->getFloat(), light3AmbientColorHSBAsRGB->getBool());
        if (light3AmbientColorHSBAsRGB->getBool()) {
            holdColor.set( light3AmbientColorHue->getFloat() * 255,  light3AmbientColorSaturation->getFloat() * 255,  light3AmbientColorBrightness->getFloat() * 255,  255);
        } else {
            holdColor = ofColor::fromHsb( light3AmbientColorHue->getFloat() * 255,  light3AmbientColorSaturation->getFloat() * 255,  light3AmbientColorBrightness->getFloat() * 255,  255);
        };
        light3.setAmbientColor(holdColor);
    };
}

void  TXDrawScene::setLight3SpecularColor() {
    if (light3UseDiffuseColorForSpecular) {
        light3.setSpecularColor(light3.getDiffuseColor());
    } else {
        ofColor holdColor =  TXFunctions::txGetColor(light3SpecularColorHue->getFloat(),  light3SpecularColorSaturation->getFloat(),  light3SpecularColorBrightness->getFloat(),  1, light3SpecularColorHueRotate->getFloat(), light3SpecularColorHSBAsRGB->getBool());
        if (light3SpecularColorHSBAsRGB->getBool()) {
            holdColor.set( light3SpecularColorHue->getFloat() * 255,  light3SpecularColorSaturation->getFloat() * 255,  light3SpecularColorBrightness->getFloat() * 255,  255);
        } else {
            holdColor = ofColor::fromHsb( light3SpecularColorHue->getFloat() * 255,  light3SpecularColorSaturation->getFloat() * 255,  light3SpecularColorBrightness->getFloat() * 255,  255);
        };
        light3.setSpecularColor(holdColor);
    };
}

void  TXDrawScene::setLight3Position() {
    light3.setPosition(light3PositionX->getFloat() * getMaxWidth(), light3PositionY->getFloat() * getMaxHeight(), light3PositionZ->getFloat() * getMaxDepth());
}

void  TXDrawScene::setLight3Orientation() {
    light3.setOrientation(ofVec3f(light3OrientationX->getFloat(), light3OrientationY->getFloat(), light3OrientationZ->getFloat()));
}


