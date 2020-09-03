/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXColorize.h"
#include "TXSystem.h"
#include "TXAsset.h"
#include "TXFunctions.h"

// constructor
TXColorize::TXColorize() {
    setup();
}

// destructor
TXColorize::~TXColorize() {
    // remove listeners to relevent mod parameters:
    ofRemoveListener(curveA1.parameters.parameterChangedE(),this,&TXColorize::curvesChanged);
    ofRemoveListener(curveA2.parameters.parameterChangedE(),this,&TXColorize::curvesChanged);
    ofRemoveListener(curveB1.parameters.parameterChangedE(),this,&TXColorize::curvesChanged);
    ofRemoveListener(curveB2.parameters.parameterChangedE(),this,&TXColorize::curvesChanged);
    ofRemoveListener(curveC1.parameters.parameterChangedE(),this,&TXColorize::curvesChanged);
    ofRemoveListener(curveC2.parameters.parameterChangedE(),this,&TXColorize::curvesChanged);
    ofRemoveListener(curveD1.parameters.parameterChangedE(),this,&TXColorize::curvesChanged);
    ofRemoveListener(curveD2.parameters.parameterChangedE(),this,&TXColorize::curvesChanged);
    ofRemoveListener(band1FadeCurve.parameters.parameterChangedE(),this,&TXColorize::curvesChanged);
    ofRemoveListener(band2FadeCurve.parameters.parameterChangedE(),this,&TXColorize::curvesChanged);
    ofRemoveListener(band3FadeCurve.parameters.parameterChangedE(),this,&TXColorize::curvesChanged);
    ofRemoveListener(band4FadeCurve.parameters.parameterChangedE(),this,&TXColorize::curvesChanged);
}

void TXColorize::addExtraParameters() {
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;

    holdModParamFloatArgs.name = "band1Level";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 3.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band1Level = createModParameter(holdModParamFloatArgs);
    parameters.add(band1Level->parameters);
    
    holdModParamFloatArgs.name = "band1SelectionMin";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band1SelectionMin = createModParameter(holdModParamFloatArgs);
    parameters.add(band1SelectionMin->parameters);
    
    holdModParamFloatArgs.name = "band1SelectionMax";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band1SelectionMax = createModParameter(holdModParamFloatArgs);
    parameters.add(band1SelectionMax->parameters);
    
    holdModParamIntArgs.name = "band1SelectionChannel";
    holdModParamIntArgs.fixedValue = TXCOLORRGBHSLCHANNEL_LUMINOSITY;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORRGBHSLCHANNEL_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORRGBHSLCHANNEL_TOTAL - 1;
	band1SelectionChannel = createModParameter(holdModParamIntArgs);
    parameters.add(band1SelectionChannel->parameters);
    
    holdModParamFloatArgs.name = "band1TintMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band1TintMix = createModParameter(holdModParamFloatArgs);
    parameters.add(band1TintMix->parameters);
    
    holdModParamBoolArgs.name = "band1TintVaryBrightness";
    holdModParamBoolArgs.fixedValue = false;
    band1TintVaryBrightness = createModParameter(holdModParamBoolArgs);
    parameters.add(band1TintVaryBrightness->parameters);
    
    holdModParamFloatArgs.name = "band1TintColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band1TintColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(band1TintColorHue->parameters);
    
    holdModParamFloatArgs.name = "band1TintColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band1TintColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(band1TintColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "band1TintColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band1TintColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(band1TintColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "band1TintColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band1TintColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(band1TintColorBrightness->parameters);
    
     holdModParamBoolArgs.name = "band1TintColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
    band1TintColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(band1TintColorHSBAsRGB->parameters);
    
     holdModParamIntArgs.name = "band1Mod1Type";
    holdModParamIntArgs.fixedValue = TXCOLORIZEMODTYPE_NONE;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORIZEMODTYPE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORIZEMODTYPE_TOTAL - 1;
    band1Mod1Type = createModParameter(holdModParamIntArgs);
    parameters.add(band1Mod1Type->parameters);
    
    holdModParamIntArgs.name = "band1Mod1Channel";
    holdModParamIntArgs.fixedValue = TXCOLORRGBHSLCHANNEL_LUMINOSITY;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORRGBHSLCHANNEL_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORRGBHSLCHANNEL_TOTAL - 1;
    band1Mod1Channel = createModParameter(holdModParamIntArgs);
    parameters.add(band1Mod1Channel->parameters);
    
    holdModParamIntArgs.name = "band1Mod1Curve";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORIZEMODCURVE_TOTAL;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORIZEMODCURVE_TOTAL;
    band1Mod1Curve = createModParameter(holdModParamIntArgs);
    parameters.add(band1Mod1Curve->parameters);
    
    holdModParamFloatArgs.name = "band1Mod1Freq";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.01;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.1;
    holdModParamFloatArgs.softMax = 10.0;
    band1Mod1Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(band1Mod1Freq->parameters);
    
    holdModParamIntArgs.name = "band1Mod1PhaseBase";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = numPhaseBaseTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = numPhaseBaseTypes - 1;
    band1Mod1PhaseBase = createModParameter(holdModParamIntArgs);
    parameters.add(band1Mod1PhaseBase->parameters);
    
    holdModParamFloatArgs.name = "band1Mod1PhaseOffset";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band1Mod1PhaseOffset = createModParameter(holdModParamFloatArgs);
    parameters.add(band1Mod1PhaseOffset->parameters);
    
    holdModParamIntArgs.name = "band1Mod2Type";
    holdModParamIntArgs.fixedValue = TXCOLORIZEMODTYPE_NONE;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORIZEMODTYPE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORIZEMODTYPE_TOTAL - 1;
    band1Mod2Type = createModParameter(holdModParamIntArgs);
    parameters.add(band1Mod2Type->parameters);
    
    holdModParamIntArgs.name = "band1Mod2Channel";
    holdModParamIntArgs.fixedValue = TXCOLORRGBHSLCHANNEL_LUMINOSITY;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORRGBHSLCHANNEL_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORRGBHSLCHANNEL_TOTAL - 1;
    band1Mod2Channel = createModParameter(holdModParamIntArgs);
    parameters.add(band1Mod2Channel->parameters);
    
    holdModParamIntArgs.name = "band1Mod2Curve";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORIZEMODCURVE_TOTAL;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORIZEMODCURVE_TOTAL;
    band1Mod2Curve = createModParameter(holdModParamIntArgs);
    parameters.add(band1Mod2Curve->parameters);
    
    holdModParamFloatArgs.name = "band1Mod2Freq";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.01;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.1;
    holdModParamFloatArgs.softMax = 10.0;
    band1Mod2Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(band1Mod2Freq->parameters);
    
    holdModParamIntArgs.name = "band1Mod2PhaseBase";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = numPhaseBaseTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = numPhaseBaseTypes - 1;
    band1Mod2PhaseBase = createModParameter(holdModParamIntArgs);
    parameters.add(band1Mod2PhaseBase->parameters);
    
    holdModParamFloatArgs.name = "band1Mod2PhaseOffset";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band1Mod2PhaseOffset = createModParameter(holdModParamFloatArgs);
    parameters.add(band1Mod2PhaseOffset->parameters);
    
    holdModParamFloatArgs.name = "band2Level";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 3.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band2Level = createModParameter(holdModParamFloatArgs);
    parameters.add(band2Level->parameters);
    
    holdModParamFloatArgs.name = "band2SelectionMin";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band2SelectionMin = createModParameter(holdModParamFloatArgs);
    parameters.add(band2SelectionMin->parameters);
    
    holdModParamFloatArgs.name = "band2SelectionMax";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band2SelectionMax = createModParameter(holdModParamFloatArgs);
    parameters.add(band2SelectionMax->parameters);
    
    holdModParamIntArgs.name = "band2SelectionChannel";
    holdModParamIntArgs.fixedValue = TXCOLORRGBHSLCHANNEL_LUMINOSITY;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORRGBHSLCHANNEL_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORRGBHSLCHANNEL_TOTAL - 1;
    band2SelectionChannel = createModParameter(holdModParamIntArgs);
    parameters.add(band2SelectionChannel->parameters);
    
    holdModParamFloatArgs.name = "band2TintMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band2TintMix = createModParameter(holdModParamFloatArgs);
    parameters.add(band2TintMix->parameters);
    
    holdModParamBoolArgs.name = "band2TintVaryBrightness";
    holdModParamBoolArgs.fixedValue = false;
    band2TintVaryBrightness = createModParameter(holdModParamBoolArgs);
    parameters.add(band2TintVaryBrightness->parameters);
    
    holdModParamFloatArgs.name = "band2TintColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band2TintColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(band2TintColorHue->parameters);
    
    holdModParamFloatArgs.name = "band2TintColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band2TintColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(band2TintColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "band2TintColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band2TintColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(band2TintColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "band2TintColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band2TintColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(band2TintColorBrightness->parameters);
    
    holdModParamBoolArgs.name = "band2TintColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
    band2TintColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(band2TintColorHSBAsRGB->parameters);
    
    holdModParamIntArgs.name = "band2Mod1Type";
    holdModParamIntArgs.fixedValue = TXCOLORIZEMODTYPE_NONE;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORIZEMODTYPE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORIZEMODTYPE_TOTAL - 1;
    band2Mod1Type = createModParameter(holdModParamIntArgs);
    parameters.add(band2Mod1Type->parameters);
    
    holdModParamIntArgs.name = "band2Mod1Channel";
    holdModParamIntArgs.fixedValue = TXCOLORRGBHSLCHANNEL_LUMINOSITY;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORRGBHSLCHANNEL_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORRGBHSLCHANNEL_TOTAL - 1;
    band2Mod1Channel = createModParameter(holdModParamIntArgs);
    parameters.add(band2Mod1Channel->parameters);
    
    holdModParamIntArgs.name = "band2Mod1Curve";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORIZEMODCURVE_TOTAL;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORIZEMODCURVE_TOTAL;
    band2Mod1Curve = createModParameter(holdModParamIntArgs);
    parameters.add(band2Mod1Curve->parameters);
    
    holdModParamFloatArgs.name = "band2Mod1Freq";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.01;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.1;
    holdModParamFloatArgs.softMax = 10.0;
    band2Mod1Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(band2Mod1Freq->parameters);
    
    holdModParamIntArgs.name = "band2Mod1PhaseBase";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = numPhaseBaseTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = numPhaseBaseTypes - 1;
    band2Mod1PhaseBase = createModParameter(holdModParamIntArgs);
    parameters.add(band2Mod1PhaseBase->parameters);
    
    holdModParamFloatArgs.name = "band2Mod1PhaseOffset";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band2Mod1PhaseOffset = createModParameter(holdModParamFloatArgs);
    parameters.add(band2Mod1PhaseOffset->parameters);
    
    holdModParamIntArgs.name = "band2Mod2Type";
    holdModParamIntArgs.fixedValue = TXCOLORIZEMODTYPE_NONE;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORIZEMODTYPE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORIZEMODTYPE_TOTAL - 1;
    band2Mod2Type = createModParameter(holdModParamIntArgs);
    parameters.add(band2Mod2Type->parameters);
    
    holdModParamIntArgs.name = "band2Mod2Channel";
    holdModParamIntArgs.fixedValue = TXCOLORRGBHSLCHANNEL_LUMINOSITY;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORRGBHSLCHANNEL_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORRGBHSLCHANNEL_TOTAL - 1;
    band2Mod2Channel = createModParameter(holdModParamIntArgs);
    parameters.add(band2Mod2Channel->parameters);
    
    holdModParamIntArgs.name = "band2Mod2Curve";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORIZEMODCURVE_TOTAL;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORIZEMODCURVE_TOTAL;
    band2Mod2Curve = createModParameter(holdModParamIntArgs);
    parameters.add(band2Mod2Curve->parameters);
    
    holdModParamFloatArgs.name = "band2Mod2Freq";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.01;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.1;
    holdModParamFloatArgs.softMax = 10.0;
    band2Mod2Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(band2Mod2Freq->parameters);
    
    holdModParamIntArgs.name = "band2Mod2PhaseBase";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = numPhaseBaseTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = numPhaseBaseTypes - 1;
    band2Mod2PhaseBase = createModParameter(holdModParamIntArgs);
    parameters.add(band2Mod2PhaseBase->parameters);
    
    holdModParamFloatArgs.name = "band2Mod2PhaseOffset";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band2Mod2PhaseOffset = createModParameter(holdModParamFloatArgs);
    parameters.add(band2Mod2PhaseOffset->parameters);
    
    holdModParamFloatArgs.name = "band3Level";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 3.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band3Level = createModParameter(holdModParamFloatArgs);
    parameters.add(band3Level->parameters);
    
    holdModParamFloatArgs.name = "band3SelectionMin";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band3SelectionMin = createModParameter(holdModParamFloatArgs);
    parameters.add(band3SelectionMin->parameters);
    
    holdModParamFloatArgs.name = "band3SelectionMax";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band3SelectionMax = createModParameter(holdModParamFloatArgs);
    parameters.add(band3SelectionMax->parameters);
    
    holdModParamIntArgs.name = "band3SelectionChannel";
    holdModParamIntArgs.fixedValue = TXCOLORRGBHSLCHANNEL_LUMINOSITY;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORRGBHSLCHANNEL_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORRGBHSLCHANNEL_TOTAL - 1;
    band3SelectionChannel = createModParameter(holdModParamIntArgs);
    parameters.add(band3SelectionChannel->parameters);
    
    holdModParamFloatArgs.name = "band3TintMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band3TintMix = createModParameter(holdModParamFloatArgs);
    parameters.add(band3TintMix->parameters);
    
    holdModParamBoolArgs.name = "band3TintVaryBrightness";
    holdModParamBoolArgs.fixedValue = false;
    band3TintVaryBrightness = createModParameter(holdModParamBoolArgs);
    parameters.add(band3TintVaryBrightness->parameters);
    
    holdModParamFloatArgs.name = "band3TintColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band3TintColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(band3TintColorHue->parameters);
    
    holdModParamFloatArgs.name = "band3TintColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band3TintColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(band3TintColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "band3TintColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band3TintColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(band3TintColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "band3TintColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band3TintColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(band3TintColorBrightness->parameters);
    
    holdModParamBoolArgs.name = "band3TintColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
    band3TintColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(band3TintColorHSBAsRGB->parameters);
    
    holdModParamIntArgs.name = "band3Mod1Type";
    holdModParamIntArgs.fixedValue = TXCOLORIZEMODTYPE_NONE;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORIZEMODTYPE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORIZEMODTYPE_TOTAL - 1;
    band3Mod1Type = createModParameter(holdModParamIntArgs);
    parameters.add(band3Mod1Type->parameters);
    
    holdModParamIntArgs.name = "band3Mod1Channel";
    holdModParamIntArgs.fixedValue = TXCOLORRGBHSLCHANNEL_LUMINOSITY;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORRGBHSLCHANNEL_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORRGBHSLCHANNEL_TOTAL - 1;
    band3Mod1Channel = createModParameter(holdModParamIntArgs);
    parameters.add(band3Mod1Channel->parameters);
    
    holdModParamIntArgs.name = "band3Mod1Curve";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORIZEMODCURVE_TOTAL;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORIZEMODCURVE_TOTAL;
    band3Mod1Curve = createModParameter(holdModParamIntArgs);
    parameters.add(band3Mod1Curve->parameters);
    
    holdModParamFloatArgs.name = "band3Mod1Freq";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.01;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.1;
    holdModParamFloatArgs.softMax = 10.0;
    band3Mod1Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(band3Mod1Freq->parameters);
    
    holdModParamIntArgs.name = "band3Mod1PhaseBase";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = numPhaseBaseTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = numPhaseBaseTypes - 1;
    band3Mod1PhaseBase = createModParameter(holdModParamIntArgs);
    parameters.add(band3Mod1PhaseBase->parameters);
    
    holdModParamFloatArgs.name = "band3Mod1PhaseOffset";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band3Mod1PhaseOffset = createModParameter(holdModParamFloatArgs);
    parameters.add(band3Mod1PhaseOffset->parameters);
    
    holdModParamIntArgs.name = "band3Mod2Type";
    holdModParamIntArgs.fixedValue = TXCOLORIZEMODTYPE_NONE;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORIZEMODTYPE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORIZEMODTYPE_TOTAL - 1;
    band3Mod2Type = createModParameter(holdModParamIntArgs);
    parameters.add(band3Mod2Type->parameters);
    
    holdModParamIntArgs.name = "band3Mod2Channel";
    holdModParamIntArgs.fixedValue = TXCOLORRGBHSLCHANNEL_LUMINOSITY;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORRGBHSLCHANNEL_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORRGBHSLCHANNEL_TOTAL - 1;
    band3Mod2Channel = createModParameter(holdModParamIntArgs);
    parameters.add(band3Mod2Channel->parameters);
    
    holdModParamIntArgs.name = "band3Mod2Curve";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORIZEMODCURVE_TOTAL;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORIZEMODCURVE_TOTAL;
    band3Mod2Curve = createModParameter(holdModParamIntArgs);
    parameters.add(band3Mod2Curve->parameters);
    
    holdModParamFloatArgs.name = "band3Mod2Freq";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.01;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.1;
    holdModParamFloatArgs.softMax = 10.0;
    band3Mod2Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(band3Mod2Freq->parameters);
    
    holdModParamIntArgs.name = "band3Mod2PhaseBase";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = numPhaseBaseTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = numPhaseBaseTypes - 1;
    band3Mod2PhaseBase = createModParameter(holdModParamIntArgs);
    parameters.add(band3Mod2PhaseBase->parameters);
    
    holdModParamFloatArgs.name = "band3Mod2PhaseOffset";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band3Mod2PhaseOffset = createModParameter(holdModParamFloatArgs);
    parameters.add(band3Mod2PhaseOffset->parameters);
    
    holdModParamFloatArgs.name = "band4Level";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 3.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band4Level = createModParameter(holdModParamFloatArgs);
    parameters.add(band4Level->parameters);
    
    holdModParamFloatArgs.name = "band4SelectionMin";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band4SelectionMin = createModParameter(holdModParamFloatArgs);
    parameters.add(band4SelectionMin->parameters);
    
    holdModParamFloatArgs.name = "band4SelectionMax";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band4SelectionMax = createModParameter(holdModParamFloatArgs);
    parameters.add(band4SelectionMax->parameters);
    
    holdModParamIntArgs.name = "band4SelectionChannel";
    holdModParamIntArgs.fixedValue = TXCOLORRGBHSLCHANNEL_LUMINOSITY;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORRGBHSLCHANNEL_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORRGBHSLCHANNEL_TOTAL - 1;
    band4SelectionChannel = createModParameter(holdModParamIntArgs);
    parameters.add(band4SelectionChannel->parameters);
    
    holdModParamFloatArgs.name = "band4TintMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band4TintMix = createModParameter(holdModParamFloatArgs);
    parameters.add(band4TintMix->parameters);
    
    holdModParamBoolArgs.name = "band4TintVaryBrightness";
    holdModParamBoolArgs.fixedValue = false;
    band4TintVaryBrightness = createModParameter(holdModParamBoolArgs);
    parameters.add(band4TintVaryBrightness->parameters);
    
    holdModParamFloatArgs.name = "band4TintColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band4TintColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(band4TintColorHue->parameters);
    
    holdModParamFloatArgs.name = "band4TintColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band4TintColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(band4TintColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = "band4TintColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band4TintColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(band4TintColorSaturation->parameters);
    
    holdModParamFloatArgs.name = "band4TintColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band4TintColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(band4TintColorBrightness->parameters);
    
    holdModParamBoolArgs.name = "band4TintColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
    band4TintColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(band4TintColorHSBAsRGB->parameters);
    
    holdModParamIntArgs.name = "band4Mod1Type";
    holdModParamIntArgs.fixedValue = TXCOLORIZEMODTYPE_NONE;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORIZEMODTYPE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORIZEMODTYPE_TOTAL - 1;
    band4Mod1Type = createModParameter(holdModParamIntArgs);
    parameters.add(band4Mod1Type->parameters);
    
    holdModParamIntArgs.name = "band4Mod1Channel";
    holdModParamIntArgs.fixedValue = TXCOLORRGBHSLCHANNEL_LUMINOSITY;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORRGBHSLCHANNEL_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORRGBHSLCHANNEL_TOTAL - 1;
    band4Mod1Channel = createModParameter(holdModParamIntArgs);
    parameters.add(band4Mod1Channel->parameters);
    
    holdModParamIntArgs.name = "band4Mod1Curve";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORIZEMODCURVE_TOTAL;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORIZEMODCURVE_TOTAL;
    band4Mod1Curve = createModParameter(holdModParamIntArgs);
    parameters.add(band4Mod1Curve->parameters);
    
    holdModParamFloatArgs.name = "band4Mod1Freq";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.01;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.1;
    holdModParamFloatArgs.softMax = 10.0;
    band4Mod1Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(band4Mod1Freq->parameters);
    
    holdModParamIntArgs.name = "band4Mod1PhaseBase";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = numPhaseBaseTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = numPhaseBaseTypes - 1;
    band4Mod1PhaseBase = createModParameter(holdModParamIntArgs);
    parameters.add(band4Mod1PhaseBase->parameters);
    
    holdModParamFloatArgs.name = "band4Mod1PhaseOffset";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band4Mod1PhaseOffset = createModParameter(holdModParamFloatArgs);
    parameters.add(band4Mod1PhaseOffset->parameters);
    
    holdModParamIntArgs.name = "band4Mod2Type";
    holdModParamIntArgs.fixedValue = TXCOLORIZEMODTYPE_NONE;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORIZEMODTYPE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORIZEMODTYPE_TOTAL - 1;
    band4Mod2Type = createModParameter(holdModParamIntArgs);
    parameters.add(band4Mod2Type->parameters);
    
    holdModParamIntArgs.name = "band4Mod2Channel";
    holdModParamIntArgs.fixedValue = TXCOLORRGBHSLCHANNEL_LUMINOSITY;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORRGBHSLCHANNEL_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORRGBHSLCHANNEL_TOTAL - 1;
    band4Mod2Channel = createModParameter(holdModParamIntArgs);
    parameters.add(band4Mod2Channel->parameters);
    
    holdModParamIntArgs.name = "band4Mod2Curve";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXCOLORIZEMODCURVE_TOTAL;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXCOLORIZEMODCURVE_TOTAL;
    band4Mod2Curve = createModParameter(holdModParamIntArgs);
    parameters.add(band4Mod2Curve->parameters);
    
    holdModParamFloatArgs.name = "band4Mod2Freq";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.01;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.1;
    holdModParamFloatArgs.softMax = 10.0;
    band4Mod2Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(band4Mod2Freq->parameters);
    
    holdModParamIntArgs.name = "band4Mod2PhaseBase";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = numPhaseBaseTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = numPhaseBaseTypes - 1;
    band4Mod2PhaseBase = createModParameter(holdModParamIntArgs);
    parameters.add(band4Mod2PhaseBase->parameters);
    
    holdModParamFloatArgs.name = "band4Mod2PhaseOffset";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    band4Mod2PhaseOffset = createModParameter(holdModParamFloatArgs);
    parameters.add(band4Mod2PhaseOffset->parameters);
    
    curveA1.setValueArrayToRamp(0, 1);
    curveA1.setName("curveA1");
    parameters.add(curveA1.parameters);
    
    curveA2.setValueArrayToRamp(0, 1);
    curveA2.setName("curveA2");
    parameters.add(curveA2.parameters);
    
    holdModParamFloatArgs.name = "curveAMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    curveAMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(curveAMorph->parameters);
    
    curveB1.setValueArrayToRamp(0, 1);
    curveB1.setName("curveB1");
    parameters.add(curveB1.parameters);
    
    curveB2.setValueArrayToRamp(0, 1);
    curveB2.setName("curveB2");
    parameters.add(curveB2.parameters);
    
    holdModParamFloatArgs.name = "curveBMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    curveBMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(curveBMorph->parameters);
    
    curveC1.setValueArrayToRamp(0, 1);
    curveC1.setName("curveC1");
    parameters.add(curveC1.parameters);
    
    curveC2.setValueArrayToRamp(0, 1);
    curveC2.setName("curveC2");
    parameters.add(curveC2.parameters);
    
    holdModParamFloatArgs.name = "curveCMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    curveCMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(curveCMorph->parameters);
    
    curveD1.setValueArrayToRamp(0, 1);
    curveD1.setName("curveD1");
    parameters.add(curveD1.parameters);
    
    curveD2.setValueArrayToRamp(0, 1);
    curveD2.setName("curveD2");
    parameters.add(curveD2.parameters);
    
    holdModParamFloatArgs.name = "curveDMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    curveDMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(curveDMorph->parameters);
    
    band1FadeCurve.setValueArrayTo(1.0f);
    band1FadeCurve.setName("band1FadeCurve");
    parameters.add(band1FadeCurve.parameters);
    
    band2FadeCurve.setValueArrayTo(1.0f);
    band2FadeCurve.setName("band2FadeCurve");
    parameters.add(band2FadeCurve.parameters);
    
    band3FadeCurve.setValueArrayTo(1.0f);
    band3FadeCurve.setName("band3FadeCurve");
    parameters.add(band3FadeCurve.parameters);
    
    band4FadeCurve.setValueArrayTo(1.0f);
    band4FadeCurve.setName("band4FadeCurve");
    parameters.add(band4FadeCurve.parameters);
    
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
    ofAddListener(curveA1.parameters.parameterChangedE(),this,&TXColorize::curvesChanged);
    ofAddListener(curveA2.parameters.parameterChangedE(),this,&TXColorize::curvesChanged);
    ofAddListener(curveB1.parameters.parameterChangedE(),this,&TXColorize::curvesChanged);
    ofAddListener(curveB2.parameters.parameterChangedE(),this,&TXColorize::curvesChanged);
    ofAddListener(curveC1.parameters.parameterChangedE(),this,&TXColorize::curvesChanged);
    ofAddListener(curveC2.parameters.parameterChangedE(),this,&TXColorize::curvesChanged);
    ofAddListener(curveD1.parameters.parameterChangedE(),this,&TXColorize::curvesChanged);
    ofAddListener(curveD2.parameters.parameterChangedE(),this,&TXColorize::curvesChanged);
    ofAddListener(band1FadeCurve.parameters.parameterChangedE(),this,&TXColorize::curvesChanged);
    ofAddListener(band2FadeCurve.parameters.parameterChangedE(),this,&TXColorize::curvesChanged);
    ofAddListener(band3FadeCurve.parameters.parameterChangedE(),this,&TXColorize::curvesChanged);
    ofAddListener(band4FadeCurve.parameters.parameterChangedE(),this,&TXColorize::curvesChanged);

    // init
    curvesImageSetup();
    curvesImageHasChanged = false;
}

void TXColorize::addExtraListeners() {
    // empty for this module
}

bool TXColorize::setExtraUniforms(int sourceImageWidth, int sourceImageHeight) {
    if (curvesImageHasChanged) {
        updateCurvesImagePixels();
        curvesImageHasChanged = false;
    };

    ofColor band1TintColor =  TXFunctions::txGetColor(band1TintColorHue->getFloat(),  band1TintColorSaturation->getFloat(),  band1TintColorBrightness->getFloat(),  1.0f, band1TintColorHueRotate->getFloat(), band1TintColorHSBAsRGB->getBool());
    ofColor band2TintColor =  TXFunctions::txGetColor(band2TintColorHue->getFloat(),  band2TintColorSaturation->getFloat(),  band2TintColorBrightness->getFloat(),  1.0f, band2TintColorHueRotate->getFloat(), band2TintColorHSBAsRGB->getBool());
    ofColor band3TintColor =  TXFunctions::txGetColor(band3TintColorHue->getFloat(),  band3TintColorSaturation->getFloat(),  band3TintColorBrightness->getFloat(),  1.0f, band3TintColorHueRotate->getFloat(), band3TintColorHSBAsRGB->getBool());
    ofColor band4TintColor =  TXFunctions::txGetColor(band4TintColorHue->getFloat(),  band4TintColorSaturation->getFloat(),  band4TintColorBrightness->getFloat(),  1.0f, band4TintColorHueRotate->getFloat(), band4TintColorHSBAsRGB->getBool());

    renderShader.setUniform2f("u_texdim0", (float) sourceImageWidth, (float) sourceImageHeight);

    renderShader.setUniform1f("u_band1Level", band1Level->getFloat());
    renderShader.setUniform1f("u_band1SelectionMin", band1SelectionMin->getFloat());
    renderShader.setUniform1f("u_band1SelectionMax", band1SelectionMax->getFloat());
    renderShader.setUniform1i("u_band1SelectionChannel", band1SelectionChannel->getInt());
    renderShader.setUniform1f("u_band1TintMix", band1TintMix->getFloat());
    renderShader.setUniform1i("u_band1TintVaryBrightness", band1TintVaryBrightness->getBool());
    renderShader.setUniform3f("u_band1TintColor", band1TintColor.r / 255.0f, band1TintColor.g / 255.0f, band1TintColor.b / 255.0f);
    renderShader.setUniform1i("u_band1Mod1Type", band1Mod1Type->getInt());
    renderShader.setUniform1i("u_band1Mod1Channel", band1Mod1Channel->getInt());
    renderShader.setUniform1i("u_band1Mod1Curve", band1Mod1Curve->getInt());
    renderShader.setUniform1f("u_band1Mod1Freq", band1Mod1Freq->getFloat());
    renderShader.setUniform1i("u_band1Mod1PhaseBase", band1Mod1PhaseBase->getInt());
    renderShader.setUniform1f("u_band1Mod1PhaseOffset", band1Mod1PhaseOffset->getFloat());
    renderShader.setUniform1i("u_band1Mod2Type", band1Mod2Type->getInt());
    renderShader.setUniform1i("u_band1Mod2Channel", band1Mod2Channel->getInt());
    renderShader.setUniform1i("u_band1Mod2Curve", band1Mod2Curve->getInt());
    renderShader.setUniform1f("u_band1Mod2Freq", band1Mod2Freq->getFloat());
    renderShader.setUniform1i("u_band1Mod2PhaseBase", band1Mod2PhaseBase->getInt());
    renderShader.setUniform1f("u_band1Mod2PhaseOffset", band1Mod2PhaseOffset->getFloat());
    
    renderShader.setUniform1f("u_band2Level", band2Level->getFloat());
    renderShader.setUniform1f("u_band2SelectionMin", band2SelectionMin->getFloat());
    renderShader.setUniform1f("u_band2SelectionMax", band2SelectionMax->getFloat());
    renderShader.setUniform1i("u_band2SelectionChannel", band2SelectionChannel->getInt());
    renderShader.setUniform1f("u_band2TintMix", band2TintMix->getFloat());
    renderShader.setUniform1i("u_band2TintVaryBrightness", band2TintVaryBrightness->getBool());
    renderShader.setUniform3f("u_band2TintColor", band2TintColor.r / 255.0f, band2TintColor.g / 255.0f, band2TintColor.b / 255.0f);
    renderShader.setUniform1i("u_band2Mod1Type", band2Mod1Type->getInt());
    renderShader.setUniform1i("u_band2Mod1Channel", band2Mod1Channel->getInt());
    renderShader.setUniform1i("u_band2Mod1Curve", band2Mod1Curve->getInt());
    renderShader.setUniform1f("u_band2Mod1Freq", band2Mod1Freq->getFloat());
    renderShader.setUniform1i("u_band2Mod1PhaseBase", band2Mod1PhaseBase->getInt());
    renderShader.setUniform1f("u_band2Mod1PhaseOffset", band2Mod1PhaseOffset->getFloat());
    renderShader.setUniform1i("u_band2Mod2Type", band2Mod2Type->getInt());
    renderShader.setUniform1i("u_band2Mod2Channel", band2Mod2Channel->getInt());
    renderShader.setUniform1i("u_band2Mod2Curve", band2Mod2Curve->getInt());
    renderShader.setUniform1f("u_band2Mod2Freq", band2Mod2Freq->getFloat());
    renderShader.setUniform1i("u_band2Mod2PhaseBase", band2Mod2PhaseBase->getInt());
    renderShader.setUniform1f("u_band2Mod2PhaseOffset", band2Mod2PhaseOffset->getFloat());
    
    renderShader.setUniform1f("u_band3Level", band3Level->getFloat());
    renderShader.setUniform1f("u_band3SelectionMin", band3SelectionMin->getFloat());
    renderShader.setUniform1f("u_band3SelectionMax", band3SelectionMax->getFloat());
    renderShader.setUniform1i("u_band3SelectionChannel", band3SelectionChannel->getInt());
    renderShader.setUniform1f("u_band3TintMix", band3TintMix->getFloat());
    renderShader.setUniform1i("u_band3TintVaryBrightness", band3TintVaryBrightness->getBool());
    renderShader.setUniform3f("u_band3TintColor", band3TintColor.r / 255.0f, band3TintColor.g / 255.0f, band3TintColor.b / 255.0f);
    renderShader.setUniform1i("u_band3Mod1Type", band3Mod1Type->getInt());
    renderShader.setUniform1i("u_band3Mod1Channel", band3Mod1Channel->getInt());
    renderShader.setUniform1i("u_band3Mod1Curve", band3Mod1Curve->getInt());
    renderShader.setUniform1f("u_band3Mod1Freq", band3Mod1Freq->getFloat());
    renderShader.setUniform1i("u_band3Mod1PhaseBase", band3Mod1PhaseBase->getInt());
    renderShader.setUniform1f("u_band3Mod1PhaseOffset", band3Mod1PhaseOffset->getFloat());
    renderShader.setUniform1i("u_band3Mod2Type", band3Mod2Type->getInt());
    renderShader.setUniform1i("u_band3Mod2Channel", band3Mod2Channel->getInt());
    renderShader.setUniform1i("u_band3Mod2Curve", band3Mod2Curve->getInt());
    renderShader.setUniform1f("u_band3Mod2Freq", band3Mod2Freq->getFloat());
    renderShader.setUniform1i("u_band3Mod2PhaseBase", band3Mod2PhaseBase->getInt());
    renderShader.setUniform1f("u_band3Mod2PhaseOffset", band3Mod2PhaseOffset->getFloat());
    
    renderShader.setUniform1f("u_band4Level", band4Level->getFloat());
    renderShader.setUniform1f("u_band4SelectionMin", band4SelectionMin->getFloat());
    renderShader.setUniform1f("u_band4SelectionMax", band4SelectionMax->getFloat());
    renderShader.setUniform1i("u_band4SelectionChannel", band4SelectionChannel->getInt());
    renderShader.setUniform1f("u_band4TintMix", band4TintMix->getFloat());
    renderShader.setUniform1i("u_band4TintVaryBrightness", band4TintVaryBrightness->getBool());
    renderShader.setUniform3f("u_band4TintColor", band4TintColor.r / 255.0f, band4TintColor.g / 255.0f, band4TintColor.b / 255.0f);
    renderShader.setUniform1i("u_band4Mod1Type", band4Mod1Type->getInt());
    renderShader.setUniform1i("u_band4Mod1Channel", band4Mod1Channel->getInt());
    renderShader.setUniform1i("u_band4Mod1Curve", band4Mod1Curve->getInt());
    renderShader.setUniform1f("u_band4Mod1Freq", band4Mod1Freq->getFloat());
    renderShader.setUniform1i("u_band4Mod1PhaseBase", band4Mod1PhaseBase->getInt());
    renderShader.setUniform1f("u_band4Mod1PhaseOffset", band4Mod1PhaseOffset->getFloat());
    renderShader.setUniform1i("u_band4Mod2Type", band4Mod2Type->getInt());
    renderShader.setUniform1i("u_band4Mod2Channel", band4Mod2Channel->getInt());
    renderShader.setUniform1i("u_band4Mod2Curve", band4Mod2Curve->getInt());
    renderShader.setUniform1f("u_band4Mod2Freq", band4Mod2Freq->getFloat());
    renderShader.setUniform1i("u_band4Mod2PhaseBase", band4Mod2PhaseBase->getInt());
    renderShader.setUniform1f("u_band4Mod2PhaseOffset", band4Mod2PhaseOffset->getFloat());

    renderShader.setUniformTexture("u_curveSampler", curvesImage.getTexture(), 1);

    renderShader.setUniform1f("u_curveAMorph", curveAMorph->getFloat());
    renderShader.setUniform1f("u_curveBMorph", curveBMorph->getFloat());
    renderShader.setUniform1f("u_curveCMorph", curveCMorph->getFloat());
    renderShader.setUniform1f("u_curveDMorph", curveDMorph->getFloat());

    renderShader.setUniform1i("u_blendMode", blendMode->getInt());
    renderShader.setUniform1f("u_blendMix", blendMix->getFloat());
    renderShader.setUniform1i("u_blendReverse", blendReverse->getBool());
    return true;
}

void TXColorize::loadRenderShader() {
    string vString = "ColorizeShader.vert";
    string fString = "ColorizeShader.frag";
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

void TXColorize::curvesImageSetup() {
    curvesImage.allocate(768, 1, OF_IMAGE_COLOR_ALPHA);
}

void  TXColorize::curvesChanged(ofAbstractParameter & parameterArg) {
    curvesImageHasChanged = true;
}

void TXColorize::updateCurvesImagePixels() {
    ofColor holdColor;
    for(int x = 0; x < 256; x++){
        holdColor.set(curveA1.parameters.getFloat(x) * 255.0f, curveB1.parameters.getFloat(x) * 255.0f,
                      curveC1.parameters.getFloat(x) * 255.0f, curveD1.parameters.getFloat(x) * 255.0f);
        curvesImage.setColor(x, 0, holdColor);
        holdColor.set(curveA2.parameters.getFloat(x) * 255.0f, curveB2.parameters.getFloat(x) * 255.0f,
                      curveC2.parameters.getFloat(x) * 255.0f, curveD2.parameters.getFloat(x) * 255.0f);
        curvesImage.setColor(x + 256, 0, holdColor);
        holdColor.set(band1FadeCurve.parameters.getFloat(x) * 255.0f, band2FadeCurve.parameters.getFloat(x) * 255.0f,
                      band3FadeCurve.parameters.getFloat(x) * 255.0f, band4FadeCurve.parameters.getFloat(x) * 255.0f);
        curvesImage.setColor(x + 512, 0, holdColor);
    }
    curvesImage.update();
}


