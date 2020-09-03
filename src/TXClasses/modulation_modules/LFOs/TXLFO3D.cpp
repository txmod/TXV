/*
 *  Created by paul on 09/09/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "TXLFO3D.h"
#include "TXSystem.h"

// properties

// constructor
TXLFO3D::TXLFO3D (string paramNamePrefix, int lfoTypeArg, int randomSmoothTypeArg, int noLevelsArg, float bpmArg, float cycleTimeBeatsArg, float cycleTimeDivisorArg, float phaseOffsetArg, bool reverseXArg, bool reverseYArg, bool reverseZArg, bool swapXAndYArg, bool circularDirectionOutArg, bool useMasterBpmArg, float scaleXArg, float scaleYArg, float scaleZArg, bool frozenArg, float customCurveXMorphArg, float customCurveYMorphArg, float customCurveZMorphArg){
    setup (paramNamePrefix, lfoTypeArg, randomSmoothTypeArg, noLevelsArg, bpmArg, cycleTimeBeatsArg, cycleTimeDivisorArg, phaseOffsetArg, reverseXArg, reverseYArg, reverseZArg, swapXAndYArg, circularDirectionOutArg, useMasterBpmArg, scaleXArg, scaleYArg, scaleZArg, frozenArg, customCurveXMorphArg,  customCurveYMorphArg, customCurveZMorphArg);
};

// destructor
TXLFO3D::~TXLFO3D() {
    // remove listeners to relevent parameters:
    ofRemoveListener(lfoType->parameters.parameterChangedE(),this,&TXLFO3D::lfoTypeChanged);
    ofRemoveListener(randomSmoothType->parameters.parameterChangedE(),this,&TXLFO3D::lfoTypeChanged);
    ofRemoveListener(noLevels->parameters.parameterChangedE(),this,&TXLFO3D::bpmChanged);
    ofRemoveListener(useMasterBpm->parameters.parameterChangedE(),this,&TXLFO3D::bpmChanged);
    ofRemoveListener(bpm->parameters.parameterChangedE(),this,&TXLFO3D::bpmChanged);
    ofRemoveListener(resetClock->parameters.parameterChangedE(),this,&TXLFO3D::resetClockChanged);
    ofRemoveListener(cycleTimeBeats->parameters.parameterChangedE(),this,&TXLFO3D::cycleTimeBeatsChanged);
    ofRemoveListener(cycleTimeDivisor->parameters.parameterChangedE(),this,&TXLFO3D::cycleTimeDivisorChanged);
    ofRemoveListener(phaseOffset->parameters.parameterChangedE(),this,&TXLFO3D::phaseOffsetChanged);
    ofRemoveListener(customCurveX.parameters.parameterChangedE(),this,&TXLFO3D::customCurveXChanged);
    ofRemoveListener(customCurveX2.parameters.parameterChangedE(),this,&TXLFO3D::customCurveX2Changed);
    ofRemoveListener(customCurveY.parameters.parameterChangedE(),this,&TXLFO3D::customCurveYChanged);
    ofRemoveListener(customCurveY2.parameters.parameterChangedE(),this,&TXLFO3D::customCurveY2Changed);
    ofRemoveListener(customCurveZ.parameters.parameterChangedE(),this,&TXLFO3D::customCurveZChanged);
    ofRemoveListener(customCurveZ2.parameters.parameterChangedE(),this,&TXLFO3D::customCurveZ2Changed);
}

// methods
void TXLFO3D::setup (string paramNamePrefix, int lfoTypeArg, int randomSmoothTypeArg, int noLevelsArg, float bpmArg, float cycleTimeBeatsArg, float cycleTimeDivisorArg, float phaseOffsetArg, bool reverseXArg, bool reverseYArg, bool reverseZArg, bool swapXAndYArg, bool circularDirectionOutArg, bool useMasterBpmArg, float scaleXArg, float scaleYArg, float scaleZArg, bool frozenArg, float customCurveXMorphArg, float customCurveYMorphArg, float customCurveZMorphArg) {
    
    float phaseOffsetTime;
    
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
    
    //	  int   lfoType;
    holdModParamIntArgs.name = paramNamePrefix + "lfoType";
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalLFOTypes-1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalLFOTypes-1;
	lfoType = createModParameter(holdModParamIntArgs);
    parameters.add(lfoType->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "randomSmoothType";
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXLFO::numSmoothTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXLFO::numSmoothTypes - 1;
	randomSmoothType = createModParameter(holdModParamIntArgs);
    parameters.add(randomSmoothType->parameters);
    
    //    int   noLevels;
    holdModParamIntArgs.name = paramNamePrefix + "noLevels";
    holdModParamIntArgs.hardMin = 1;
    holdModParamIntArgs.hardMax = maxNoLevels;
    holdModParamIntArgs.softMin = 1;
    holdModParamIntArgs.softMax = maxNoLevels;
	noLevels = createModParameter(holdModParamIntArgs);
    parameters.add(noLevels->parameters);

    //    float bpm;
    holdModParamFloatArgs.name = paramNamePrefix + "bpm";
    holdModParamFloatArgs.hardMin = 0.001;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 0.1;
    holdModParamFloatArgs.softMax = 200.0;
    bpm = createModParameter(holdModParamFloatArgs);
    parameters.add(bpm->parameters);
    
    //    bool  useMasterBpm;
    holdModParamBoolArgs.name = paramNamePrefix + "useMasterBpm";
    useMasterBpm = createModParameter(holdModParamBoolArgs);
    parameters.add(useMasterBpm->parameters);
    
    //    float cycleTimeBeats;
    holdModParamFloatArgs.name = paramNamePrefix + "cycleTimeBeats";
    holdModParamFloatArgs.hardMin = 1.0;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 1.0;
    holdModParamFloatArgs.softMax = 64.0;
    cycleTimeBeats = createModParameter(holdModParamFloatArgs);
    parameters.add(cycleTimeBeats->parameters);
    
    //    float cycleTimeDivisor;
    holdModParamFloatArgs.name = paramNamePrefix + "cycleTimeDivisor";
    holdModParamFloatArgs.hardMin = 1.0;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 1.0;
    holdModParamFloatArgs.softMax = 64.0;
    cycleTimeDivisor = createModParameter(holdModParamFloatArgs);
    parameters.add(cycleTimeDivisor->parameters);
    
    //    float phaseOffset;
    holdModParamFloatArgs.name = paramNamePrefix + "phaseOffset";
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    phaseOffset = createModParameter(holdModParamFloatArgs);
    parameters.add(phaseOffset->parameters);
    
    //    bool  circularDirectionOut;
    holdModParamBoolArgs.name = paramNamePrefix + "circularDirectionOut";
    circularDirectionOut = createModParameter(holdModParamBoolArgs);
    parameters.add(circularDirectionOut->parameters);
    
    //    bool frozen;
    holdModParamBoolArgs.name = paramNamePrefix + "frozen";
    frozen = createModParameter(holdModParamBoolArgs);
    parameters.add(frozen->parameters);
    
    holdModParamBoolArgs.name = "resetClock";
    holdModParamBoolArgs.fixedValue = 0.0;
    resetClock = createModParameter(holdModParamBoolArgs);
    parameters.add(resetClock->parameters);
    
    //    bool  reverseX;
    holdModParamBoolArgs.name = paramNamePrefix + "reverseX";
    reverseX = createModParameter(holdModParamBoolArgs);
    parameters.add(reverseX->parameters);
    
    //    bool  reverseY;
    holdModParamBoolArgs.name = paramNamePrefix + "reverseY";
    reverseY = createModParameter(holdModParamBoolArgs);
    parameters.add(reverseY->parameters);
    
    //    bool  reverseZ;
    holdModParamBoolArgs.name = paramNamePrefix + "reverseZ";
    reverseZ = createModParameter(holdModParamBoolArgs);
    parameters.add(reverseZ->parameters);
    
    //    bool  swapXAndY;
    holdModParamBoolArgs.name = paramNamePrefix + "swapXAndY";
    swapXAndY = createModParameter(holdModParamBoolArgs);
    parameters.add(swapXAndY->parameters);
    
    //    float scaleX;
    holdModParamFloatArgs.name = paramNamePrefix + "scaleX";
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    scaleX = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleX->parameters);
    
    //    float scaleY;
    holdModParamFloatArgs.name = paramNamePrefix + "scaleY";
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    scaleY = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleY->parameters);
    
    //    float scaleZ;
    holdModParamFloatArgs.name = paramNamePrefix + "scaleZ";
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    scaleZ = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleZ->parameters);
        
    customCurveX.setValueArrayToRamp(0, 1);
    customCurveX.setName(paramNamePrefix + "customCurveX");
    parameters.add(customCurveX.parameters);
    
    customCurveX2.setValueArrayToRamp(0, 1);
    customCurveX2.setName(paramNamePrefix + "customCurveX2");
    parameters.add(customCurveX2.parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "customCurveXMorph";
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    customCurveXMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(customCurveXMorph->parameters);
    
    customCurveY.setValueArrayToRamp(0, 1);
    customCurveY.setName(paramNamePrefix + "customCurveY");
    parameters.add(customCurveY.parameters);
    
    customCurveY2.setValueArrayToRamp(0, 1);
    customCurveY2.setName(paramNamePrefix + "customCurveY2");
    parameters.add(customCurveY2.parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "customCurveYMorph";
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    customCurveYMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(customCurveYMorph->parameters);
    
    customCurveZ.setValueArrayToRamp(0, 1);
    customCurveZ.setName(paramNamePrefix + "customCurveZ");
    parameters.add(customCurveZ.parameters);
    
    customCurveZ2.setValueArrayToRamp(0, 1);
    customCurveZ2.setName(paramNamePrefix + "customCurveZ2");
    parameters.add(customCurveZ2.parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "customCurveZMorph";
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    customCurveZMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(customCurveZMorph->parameters);
    
    // create mod source outputs
    positionX = createModSource("positionX", 0.5);
    positionY = createModSource("positionY", 0.5);
    positionZ = createModSource("positionZ", 0.5);
    
    // add listener to relevent parameters:
    ofAddListener(lfoType->parameters.parameterChangedE(),this,&TXLFO3D::lfoTypeChanged);
    ofAddListener(randomSmoothType->parameters.parameterChangedE(),this,&TXLFO3D::lfoTypeChanged);
    ofAddListener(noLevels->parameters.parameterChangedE(),this,&TXLFO3D::bpmChanged);
    ofAddListener(useMasterBpm->parameters.parameterChangedE(),this,&TXLFO3D::bpmChanged);
    ofAddListener(bpm->parameters.parameterChangedE(),this,&TXLFO3D::bpmChanged);
    ofAddListener(resetClock->parameters.parameterChangedE(),this,&TXLFO3D::resetClockChanged);
    ofAddListener(cycleTimeBeats->parameters.parameterChangedE(),this,&TXLFO3D::cycleTimeBeatsChanged);
    ofAddListener(cycleTimeDivisor->parameters.parameterChangedE(),this,&TXLFO3D::cycleTimeDivisorChanged);
    ofAddListener(phaseOffset->parameters.parameterChangedE(),this,&TXLFO3D::phaseOffsetChanged);
    ofAddListener(customCurveX.parameters.parameterChangedE(),this,&TXLFO3D::customCurveXChanged);
    ofAddListener(customCurveX2.parameters.parameterChangedE(),this,&TXLFO3D::customCurveX2Changed);
    ofAddListener(customCurveY.parameters.parameterChangedE(),this,&TXLFO3D::customCurveYChanged);
    ofAddListener(customCurveY2.parameters.parameterChangedE(),this,&TXLFO3D::customCurveY2Changed);
    ofAddListener(customCurveZ.parameters.parameterChangedE(),this,&TXLFO3D::customCurveZChanged);
    ofAddListener(customCurveZ2.parameters.parameterChangedE(),this,&TXLFO3D::customCurveZChanged);

    setNoLevelsFixed(noLevelsArg);
    setCycleTimeBeatsFixed(cycleTimeBeatsArg);
    setCycleTimeDivisorFixed(cycleTimeDivisorArg);
    setBpmFixed(bpmArg);
	lfoType->setFixedValue(lfoTypeArg);
	randomSmoothType->setFixedValue(randomSmoothTypeArg);
    phaseOffset->setFixedValue(phaseOffsetArg);
    reverseX->setFixedValue(reverseXArg);
    reverseY->setFixedValue(reverseYArg);
    reverseZ->setFixedValue(reverseZArg);
    swapXAndY->setFixedValue(swapXAndYArg);
    circularDirectionOut->setFixedValue(circularDirectionOutArg);
    useMasterBpm->setFixedValue(useMasterBpmArg);
    scaleX->setFixedValue(scaleXArg);
    scaleY->setFixedValue(scaleYArg);
    scaleZ->setFixedValue(scaleZArg);
    frozen->setFixedValue(frozenArg);
    customCurveXMorph->setFixedValue(customCurveXMorphArg);
    customCurveYMorph->setFixedValue(customCurveYMorphArg);
    customCurveZMorph->setFixedValue(customCurveZMorphArg);
    
    float holdBpm;
    if (useMasterBpmArg) {
        holdBpm = masterBpm;
    } else {
        holdBpm = bpmArg;
    };
    phaseOffsetTime = phaseOffset->getFloat() * (cycleTimeBeats->getFloat() / cycleTimeDivisor->getFloat())
    * (60 * noLevels->getInt()) / holdBpm;
    currentTime = phaseOffsetTime;
    requestResetClock = true;

    lfoAmp.setUseMasterBpm(false);
    lfoX.setUseMasterBpm(false);
    lfoY.setUseMasterBpm(false);
    lfoZ.setUseMasterBpm(false);
    customCurveXHasChanged = false;
    customCurveX2HasChanged = false;
    customCurveYHasChanged = false;
    customCurveY2HasChanged = false;
    customCurveZHasChanged = false;
    customCurveZ2HasChanged = false;
    
    updateBpm();
    updateCycleTimeBeats();
    updateCycleTimeDivisor();
    updatePhaseOffset();
    updateCurveX();
    updateCurveY();
    updateCurveZ();
};

/*
 0-NOPATTERN------ Aconst1, AStOff,   Xsine, XStOff,  XSp1,    	   Ysine,  YStOff, YSp1
 1-circles ------- Asaw,    AStOn,    Xsine, XStOff,  XSp1,    	   Ycos,   YStOff, YSp1
 2-spirals ------- Asaw,    AStOff,   Xsine  XStOff,  XSp1,    	   Ycos,   YStOff, YSp1
 3-lines --------- Aconst1, AStOff,   Xsaw,  XStOff,  XSp1,        Ysaw,   YStOn,  YSp1/layers
 4-diagonal lines- Aconst1, AStOff,   Xsaw,  XStOff,  XSp1/layers  Ysaw,   YStOff, YSp1
 5-grid ---------- Aconst1, AStOff,   Xsaw,  XStOn,   XSp1,        Ysaw,   YStOn,  YSp1/layers
 6-sine wave------ Aconst1, AStOff,   Xsaw,  XStOff,  XSp1/layers  Ysine,  YStOff, YSp1
 7-spiral sine --- Asine,   AStOff,   Xsine, XStOff,  XSp1,        Ycos,   YStOff, YSp1
 8-zigzag -------- Aconst1, AStOff,   Xtri,  XStOff,  XSp1/layers  Ytri,   YStOff, YSp1
 9-random ---------- Aconst1, AStOff,   Xrandom,  XStOn,   XSp1,        Yrandom,   YStOn,  YSp1/layers
 10-random smoothed- Aconst1, AStOff,   Xrandomsmoothed,  XStOn,   XSp1,        Yrandomsmoothed,   YStOn,  YSp1/layers
 
 */

void  TXLFO3D::lfoTypeChanged(ofAbstractParameter & dummyParameterArg ) {
    updateLfoType();
};

void  TXLFO3D::bpmChanged(ofAbstractParameter & dummyParameterArg ) {
    updateBpm();
}

void  TXLFO3D::resetClockChanged(ofAbstractParameter & dummyParameterArg ) {
    if (resetClock->getBool()){
        requestResetClock = true;
    };
}

void  TXLFO3D::cycleTimeBeatsChanged(ofAbstractParameter & dummyParameterArg ) {
    updateCycleTimeBeats();
}

void  TXLFO3D::cycleTimeDivisorChanged(ofAbstractParameter & dummyParameterArg ) {
    updateCycleTimeDivisor();
}

void  TXLFO3D::phaseOffsetChanged(ofAbstractParameter & dummyParameterArg ) {
    updatePhaseOffset();
}

void  TXLFO3D::customCurveXChanged(ofAbstractParameter & dummyParameterArg ) {
    customCurveXHasChanged = true;
}

void  TXLFO3D::customCurveX2Changed(ofAbstractParameter & dummyParameterArg ) {
    customCurveX2HasChanged = true;
}

void  TXLFO3D::customCurveYChanged(ofAbstractParameter & dummyParameterArg ) {
    customCurveYHasChanged = true;
}

void  TXLFO3D::customCurveY2Changed(ofAbstractParameter & dummyParameterArg ) {
    customCurveY2HasChanged = true;
}

void  TXLFO3D::customCurveZChanged(ofAbstractParameter & dummyParameterArg ) {
    customCurveZHasChanged = true;
}

void  TXLFO3D::customCurveZ2Changed(ofAbstractParameter & dummyParameterArg ) {
    customCurveZ2HasChanged = true;
}

void TXLFO3D::setNoLevelsFixed(float noLevelsArg) {
    noLevels->setFixedValue(ofClamp(noLevelsArg, 1, maxNoLevels));
};

void TXLFO3D::setBpmFixed(float bpmArg){
    bpm->setFixedValue(ofClamp(bpmArg, 1, 1000));
};

void TXLFO3D::setCycleTimeBeatsFixed(float cycleTimeBeatsArg){
    cycleTimeBeats->setFixedValue(ofClamp(cycleTimeBeatsArg, 1, 1000));
};

void TXLFO3D::setCycleTimeDivisorFixed(float cycleTimeDivisorArg){
    cycleTimeDivisor->setFixedValue(ofClamp(cycleTimeDivisorArg, 1, 1000));
};

void TXLFO3D::updateCycleTimeBeats() {
    float holdCycleTimeBeats;
    
    holdCycleTimeBeats = cycleTimeBeats->getFloat();
    lfoAmp.setCycleTimeBeats(holdCycleTimeBeats);
    lfoX.setCycleTimeBeats(holdCycleTimeBeats);
    lfoY.setCycleTimeBeats(holdCycleTimeBeats);
    lfoZ.setCycleTimeBeats(holdCycleTimeBeats);
};

void TXLFO3D::updateCycleTimeDivisor() {
    float holdCycleTimeDivisor;
    
    holdCycleTimeDivisor = cycleTimeDivisor->getFloat();
    lfoAmp.setCycleTimeDivisor(holdCycleTimeDivisor);
    lfoX.setCycleTimeDivisor(holdCycleTimeDivisor);
    lfoY.setCycleTimeDivisor(holdCycleTimeDivisor);
    lfoZ.setCycleTimeDivisor(holdCycleTimeDivisor);
};

void TXLFO3D::updatePhaseOffset() {
    float holdPhaseOffset;
    holdPhaseOffset = phaseOffset->getFloat();
    lfoAmp.setPhaseOffset(holdPhaseOffset);
    lfoX.setPhaseOffset(holdPhaseOffset);
    lfoY.setPhaseOffset(holdPhaseOffset);
    lfoZ.setPhaseOffset(holdPhaseOffset);
};

void TXLFO3D::updateCurveX() {
    lfoX.customCurve.setValueArray(customCurveX.parameters);
};

void TXLFO3D::updateCurveX2() {
    lfoX.customCurve2.setValueArray(customCurveX2.parameters);
};

void TXLFO3D::updateCurveY() {
    lfoY.customCurve.setValueArray(customCurveY.parameters);
};

void TXLFO3D::updateCurveY2() {
    lfoY.customCurve2.setValueArray(customCurveY2.parameters);
};

void TXLFO3D::updateCurveZ() {
    lfoZ.customCurve.setValueArray(customCurveZ.parameters);
};

void TXLFO3D::updateCurveZ2() {
    lfoZ.customCurve2.setValueArray(customCurveZ2.parameters);
};


void TXLFO3D::updateLfoType() {
    switch (lfoType->getInt()) {
        case TXLFO3DTYPE_NOPATTERN:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_SINE);
            lfoY.setLfoType(TXLFOTYPE_SINE);
            lfoZ.setLfoType(TXLFOTYPE_SINE);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            quantiseLfoZ = false;
            break;
            
        case TXLFO3DTYPE_CIRCLES:
            useLfoAmp = true;
            lfoAmp.setLfoType(TXLFOTYPE_SAW);
            lfoX.setLfoType(TXLFOTYPE_SINE);
            lfoY.setLfoType(TXLFOTYPE_COSINE);
            lfoZ.setLfoType(TXLFOTYPE_SINE);
            quantiseLfoAmp = true;
            quantiseLfoX = false;
            quantiseLfoY = false;
            quantiseLfoZ = false;
            break;
            
        case TXLFO3DTYPE_SPIRALS:
            useLfoAmp = true;
            lfoAmp.setLfoType(TXLFOTYPE_SAW);
            lfoX.setLfoType(TXLFOTYPE_SINE);
            lfoY.setLfoType(TXLFOTYPE_COSINE);
            lfoZ.setLfoType(TXLFOTYPE_SAW);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            quantiseLfoZ = false;
            break;
            
        case TXLFO3DTYPE_SPIRALSINE:
            useLfoAmp = true;
            lfoAmp.setLfoType(TXLFOTYPE_SINE);
            lfoX.setLfoType(TXLFOTYPE_SINE);
            lfoY.setLfoType(TXLFOTYPE_COSINE);
            lfoZ.setLfoType(TXLFOTYPE_TRIANGLE);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            quantiseLfoZ = false;
            break;
            
        case TXLFO3DTYPE_SPIRALTRI:
            useLfoAmp = true;
            lfoAmp.setLfoType(TXLFOTYPE_TRIANGLE);
            lfoX.setLfoType(TXLFOTYPE_SINE);
            lfoY.setLfoType(TXLFOTYPE_COSINE);
            lfoZ.setLfoType(TXLFOTYPE_TRIANGLE);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            quantiseLfoZ = false;
            break;
            
        case TXLFO3DTYPE_LINES:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_SAW);
            lfoY.setLfoType(TXLFOTYPE_SAW);
            lfoZ.setLfoType(TXLFOTYPE_SAW);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = true;
            quantiseLfoZ = false;
            break;
            
        case TXLFO3DTYPE_DIAGONALLINES:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_SAW);
            lfoY.setLfoType(TXLFOTYPE_SAW);
            lfoZ.setLfoType(TXLFOTYPE_SAW);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            quantiseLfoZ = false;
            break;
            
        case TXLFO3DTYPE_GRID:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_SAW);
            lfoY.setLfoType(TXLFOTYPE_SAW);
            lfoZ.setLfoType(TXLFOTYPE_SAW);
            quantiseLfoAmp = false;
            quantiseLfoX = true;
            quantiseLfoY = true;
            quantiseLfoZ = true;
            break;
            
        case TXLFO3DTYPE_SINEWAVE:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_SAW);
            lfoY.setLfoType(TXLFOTYPE_SINE);
            lfoZ.setLfoType(TXLFOTYPE_TRIANGLE);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            quantiseLfoZ = false;
            break;
            
        case TXLFO3DTYPE_ZIGZAG:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_TRIANGLE);
            lfoY.setLfoType(TXLFOTYPE_TRIANGLE);
            lfoZ.setLfoType(TXLFOTYPE_TRIANGLE);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            quantiseLfoZ = false;
            break;
            
        case TXLFO3DTYPE_RANDOM:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_RANDOM);
            lfoY.setLfoType(TXLFOTYPE_RANDOM);
            lfoZ.setLfoType(TXLFOTYPE_RANDOM);
            lfoX.setRandomSmoothType(randomSmoothType->getInt());
            lfoY.setRandomSmoothType(randomSmoothType->getInt());
            lfoZ.setRandomSmoothType(randomSmoothType->getInt());
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            quantiseLfoZ = false;
            break;
            
        case TXLFO3DTYPE_RANDOMQUANTISED:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_RANDOMQUANTISED);
            lfoY.setLfoType(TXLFOTYPE_RANDOMQUANTISED);
            lfoZ.setLfoType(TXLFOTYPE_RANDOMQUANTISED);
            lfoX.setRandomSmoothType(randomSmoothType->getInt());
            lfoY.setRandomSmoothType(randomSmoothType->getInt());
            lfoZ.setRandomSmoothType(randomSmoothType->getInt());
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            quantiseLfoZ = false;
            break;
            
        case TXLFO3DTYPE_RANDOMSMOOTHED:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_RANDOMSMOOTHED);
            lfoY.setLfoType(TXLFOTYPE_RANDOMSMOOTHED);
            lfoZ.setLfoType(TXLFOTYPE_RANDOMSMOOTHED);
            lfoX.setRandomSmoothType(randomSmoothType->getInt());
            lfoY.setRandomSmoothType(randomSmoothType->getInt());
            lfoZ.setRandomSmoothType(randomSmoothType->getInt());
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            quantiseLfoZ = false;
            break;
            
        case TXLFO3DTYPE_DOUBLERANDOM:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_DOUBLERANDOM);
            lfoY.setLfoType(TXLFOTYPE_DOUBLERANDOM);
            lfoZ.setLfoType(TXLFOTYPE_DOUBLERANDOM);
            lfoX.setRandomSmoothType(randomSmoothType->getInt());
            lfoY.setRandomSmoothType(randomSmoothType->getInt());
            lfoZ.setRandomSmoothType(randomSmoothType->getInt());
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            quantiseLfoZ = false;
            break;
            
        case TXLFO3DTYPE_DOUBLERANDOMQUANTISED:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_DOUBLERANDOMQUANTISED);
            lfoY.setLfoType(TXLFOTYPE_DOUBLERANDOMQUANTISED);
            lfoZ.setLfoType(TXLFOTYPE_DOUBLERANDOMQUANTISED);
            lfoX.setRandomSmoothType(randomSmoothType->getInt());
            lfoY.setRandomSmoothType(randomSmoothType->getInt());
            lfoZ.setRandomSmoothType(randomSmoothType->getInt());
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            quantiseLfoZ = false;
            break;
            
        case TXLFO3DTYPE_DOUBLERANDOMSMOOTHED:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_DOUBLERANDOMSMOOTHED);
            lfoY.setLfoType(TXLFOTYPE_DOUBLERANDOMSMOOTHED);
            lfoZ.setLfoType(TXLFOTYPE_DOUBLERANDOMSMOOTHED);
            lfoX.setRandomSmoothType(randomSmoothType->getInt());
            lfoY.setRandomSmoothType(randomSmoothType->getInt());
            lfoZ.setRandomSmoothType(randomSmoothType->getInt());
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            quantiseLfoZ = false;
            break;
            
        case TXLFO3DTYPE_TREFOILKNOT:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_TREFOILKNOTX);
            lfoY.setLfoType(TXLFOTYPE_TREFOILKNOTY);
            lfoZ.setLfoType(TXLFOTYPE_TREFOILKNOTZ);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            quantiseLfoZ = false;
            break;
        case TXLFO3DTYPE_CUSTOMCURVE:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_CUSTOMCURVE);
            lfoY.setLfoType(TXLFOTYPE_CUSTOMCURVE);
            lfoZ.setLfoType(TXLFOTYPE_CUSTOMCURVE);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            quantiseLfoZ = false;
            break;
        case TXLFO3DTYPE_CUSTOMCURVE_MIRRORED:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_CUSTOMCURVE_MIRRORED);
            lfoY.setLfoType(TXLFOTYPE_CUSTOMCURVE_MIRRORED);
            lfoZ.setLfoType(TXLFOTYPE_CUSTOMCURVE_MIRRORED);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            quantiseLfoZ = false;
            break;
    }
    resetTime();
};

void TXLFO3D::updateBpm() {
    float speedFast, speedSlow;
    
    if (useMasterBpm->getBool()) {
        speedFast = masterBpm;
    } else {
        speedFast = bpm->getFloat();
    };
    speedSlow = speedFast/ noLevels->getInt();
    
    switch (lfoType->getInt()) {
        case TXLFO3DTYPE_NOPATTERN:
            lfoAmp.setBpm(0);
            lfoX.setBpm(0);
            lfoY.setBpm(0);
            lfoZ.setBpm(0);
            break;
            
        case TXLFO3DTYPE_CIRCLES:
            lfoAmp.setBpm(speedSlow);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedFast);
            lfoZ.setBpm(speedSlow);
            break;
            
        case TXLFO3DTYPE_SPIRALS:
            lfoAmp.setBpm(speedSlow);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedFast);
            lfoZ.setBpm(speedSlow);
            break;
            
        case TXLFO3DTYPE_SPIRALSINE:
            lfoAmp.setBpm(speedSlow);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedFast);
            lfoZ.setBpm(speedSlow);
            break;
            
        case TXLFO3DTYPE_SPIRALTRI:
            lfoAmp.setBpm(speedSlow);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedFast);
            lfoZ.setBpm(speedSlow);
            break;
            
        case TXLFO3DTYPE_LINES:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedSlow);
            lfoZ.setBpm(speedSlow);
            break;
            
        case TXLFO3DTYPE_DIAGONALLINES:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedSlow);
            lfoY.setBpm(speedFast);
            lfoZ.setBpm(speedSlow);
            break;
            
        case TXLFO3DTYPE_GRID:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedSlow);
            lfoZ.setBpm(speedSlow);
            break;
            
        case TXLFO3DTYPE_SINEWAVE:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedSlow);
            lfoY.setBpm(speedFast);
            lfoZ.setBpm(speedFast);
            break;
            
        case TXLFO3DTYPE_ZIGZAG:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedSlow);
            lfoY.setBpm(speedFast);
            lfoZ.setBpm(speedSlow);
            break;
            
        case TXLFO3DTYPE_RANDOM:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedFast);
            lfoZ.setBpm(speedFast);
            break;
            
        case TXLFO3DTYPE_RANDOMQUANTISED:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedFast);
            lfoZ.setBpm(speedFast);
            break;
            
        case TXLFO3DTYPE_RANDOMSMOOTHED:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedFast);
            lfoZ.setBpm(speedFast);
            break;
            
        case TXLFO3DTYPE_DOUBLERANDOM:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedFast);
            lfoZ.setBpm(speedFast);
            break;
            
        case TXLFO3DTYPE_DOUBLERANDOMQUANTISED:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedFast);
            lfoZ.setBpm(speedFast);
            break;
            
        case TXLFO3DTYPE_DOUBLERANDOMSMOOTHED:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedFast);
            lfoZ.setBpm(speedFast);
            break;
            
        case TXLFO3DTYPE_TREFOILKNOT:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedFast);
            lfoZ.setBpm(speedFast);
            break;
            
        case TXLFO3DTYPE_CUSTOMCURVE:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedFast);
            lfoZ.setBpm(speedFast);
            break;
            
        case TXLFO3DTYPE_CUSTOMCURVE_MIRRORED:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedFast);
            lfoZ.setBpm(speedFast);
            break;
            
        default:
            lfoAmp.setBpm(0);
            lfoX.setBpm(0);
            lfoY.setBpm(0);
            lfoZ.setBpm(0);
            break;
    }
}

//void TXLFO3D::setTime(float timeArg){
//    float phaseOffsetTime;
//    float holdBpm;
//    if (frozen) {
//        return;
//    };
//    if (useMasterBpm->getBool()) {
//        holdBpm = masterBpm;
//    } else {
//        holdBpm = bpm->getFloat();
//    };
//    phaseOffsetTime = phaseOffset->getFloat() * (cycleTimeBeats->getFloat() / cycleTimeDivisor->getFloat())
//    * (60 * noLevels->getInt()) / holdBpm;
//    currentTime = timeArg + phaseOffsetTime;
//    lfoAmp.setTime(currentTime, masterBpm);
//    lfoX.setTime(currentTime, masterBpm);
//    lfoY.setTime(currentTime, masterBpm);
//    lfoZ.setTime(currentTime, masterBpm);
//    recalcPosXYZ();
//};

void TXLFO3D::resetTime() {
    float phaseOffsetTime;
    float holdBpm;
    if (useMasterBpm->getBool()) {
        holdBpm = masterBpm;
    } else {
        holdBpm = bpm->getFloat();
    };
    lfoAmp.resetTime();
    lfoX.resetTime();
    lfoY.resetTime();
    lfoZ.resetTime();
    phaseOffsetTime = phaseOffset->getFloat() * (cycleTimeBeats->getFloat() / cycleTimeDivisor->getFloat())
    * (60 * noLevels->getInt()) / holdBpm;
    currentTime = phaseOffsetTime;
    recalcPosXYZ();
}

void TXLFO3D::update() {
    if (customCurveXHasChanged) {
        updateCurveX();
        customCurveXHasChanged = false;
    };
    if (customCurveX2HasChanged) {
        updateCurveX2();
        customCurveX2HasChanged = false;
    };
    if (customCurveYHasChanged) {
        updateCurveY();
        customCurveYHasChanged = false;
    };
    if (customCurveY2HasChanged) {
        updateCurveY2();
        customCurveY2HasChanged = false;
    };
    if (customCurveZ2HasChanged) {
        updateCurveZ2();
        customCurveZ2HasChanged = false;
    };
    if (customCurveZHasChanged) {
        updateCurveZ();
        customCurveZHasChanged = false;
    };
}

// override base class
void TXLFO3D::setMasterBpm(float masterBpmArg){
    masterBpm = masterBpmArg;
    updateBpm();
};

void TXLFO3D::advanceBy(float timeDeltaArg) {
    float phaseOffsetTime;
    float holdBpm;
    if (frozen->getBool()) {
        return;
    };
    if (requestResetClock) {
        resetTime();
        requestResetClock = false;
    };
    if (useMasterBpm->getBool()) {
        holdBpm = masterBpm;
    } else {
        holdBpm = bpm->getFloat();
    };
    currentTime += timeDeltaArg;
    lfoAmp.advanceBy(timeDeltaArg, masterBpm);
    lfoX.advanceBy(timeDeltaArg, masterBpm);
    lfoY.advanceBy(timeDeltaArg, masterBpm);
    lfoZ.advanceBy(timeDeltaArg, masterBpm);
    recalcPosXYZ();
}

void TXLFO3D::recalcPosXYZ() {
    float holdLfoAmp, holdLfoX, holdLfoY, holdLfoZ, holdX, holdY, holdZ, holdXR, holdYR, holdZR;
    float offset, holdScaleX, holdScaleY, holdScaleZ;
    int  holdNoLevels;
    
    if (useLfoAmp) {
        holdLfoAmp = lfoAmp.getValue();
    } else {
        holdLfoAmp = 1;
    };
    holdLfoX = lfoX.getValue();
    holdLfoY = lfoY.getValue();
    holdLfoZ = lfoZ.getValue();
    
    holdNoLevels = noLevels->getInt();
    holdScaleX = scaleX->getFloat();
    holdScaleY = scaleY->getFloat();
    holdScaleZ = scaleZ->getFloat();
    if (quantiseLfoAmp) {
        if (circularDirectionOut->getBool()) {
            holdLfoAmp = ceil (0.00001 + (holdLfoAmp * 0.99999 * holdNoLevels)) / holdNoLevels;
        } else {
            holdLfoAmp = ceil ((1-holdLfoAmp) * holdNoLevels) / holdNoLevels;
        };
    } else {
        if (!circularDirectionOut->getBool() && useLfoAmp) {
            holdLfoAmp = 1 - holdLfoAmp;
        };
    };
    if (quantiseLfoX) {
        holdLfoX = floor (holdLfoX * 0.99999 * holdNoLevels) / max (holdNoLevels - 1, 1);
    };
    if (quantiseLfoY) {
        holdLfoY = floor (holdLfoY * 0.99999 * holdNoLevels) / max (holdNoLevels - 1, 1);
    };
    if (quantiseLfoZ) {
        holdLfoZ = floor (holdLfoZ * 0.99999 * holdNoLevels) / max (holdNoLevels - 1, 1);
    };
    offset = (1 - holdLfoAmp) * 0.5;
    holdX = offset + (holdLfoAmp * holdLfoX);
    holdY = offset + (holdLfoAmp * holdLfoY);
    holdZ = offset + (holdLfoAmp * holdLfoZ);
    
    // adjust for scale, reverse & swapXY
    holdX = (holdX * holdScaleX) + (0.5 * (1 - holdScaleX));
    holdY = (holdY * holdScaleY) + (0.5 * (1 - holdScaleY));
    holdZ = (holdZ * holdScaleZ) + (0.5 * (1 - holdScaleZ));
    if (reverseX->getBool()) {holdXR = (1-holdX);} else {holdXR = holdX;}
    if (reverseY->getBool()) {holdYR = (1-holdY);} else {holdYR = holdY;}
    if (reverseZ->getBool()) {holdZR = (1-holdZ);} else {holdZR = holdZ;}
    if (swapXAndY->getBool()) {positionX->setValue(holdYR);} else  {positionX->setValue(holdXR);};
    if (swapXAndY->getBool()) {positionY->setValue(holdXR);} else  {positionY->setValue(holdYR);};
    positionZ->setValue(holdZR);
};


void TXLFO3D::getAllOutputValues(TXLFO3DValues & dataArg) {
    dataArg.lfoType = lfoType->getInt();
    dataArg.randomSmoothType = randomSmoothType->getInt();
    dataArg.noLevels = noLevels->getInt();
    dataArg.bpm = bpm->getFloat();
    dataArg.useMasterBpm = useMasterBpm->getBool();
    dataArg.frozen = frozen->getBool();
    dataArg.cycleTimeBeats = cycleTimeBeats->getFloat();
    dataArg.cycleTimeDivisor = cycleTimeDivisor->getFloat();
    dataArg.phaseOffset = phaseOffset->getFloat();
    dataArg.circularDirectionOut = circularDirectionOut->getBool();
    dataArg.reverseX = reverseX->getBool();
    dataArg.reverseY = reverseY->getBool();
    dataArg.reverseZ = reverseZ->getBool();
    dataArg.swapXAndY = swapXAndY->getBool();
    dataArg.scaleX = scaleX->getFloat();
    dataArg.scaleY = scaleY->getFloat();
    dataArg.scaleZ = scaleZ->getFloat();
    dataArg.customCurveX.setValueArray(customCurveX.parameters);
    dataArg.customCurveX2.setValueArray(customCurveX2.parameters);
    dataArg.customCurveXMorph = customCurveXMorph->getFloat();
    dataArg.customCurveY.setValueArray(customCurveY.parameters);
    dataArg.customCurveY2.setValueArray(customCurveY2.parameters);
    dataArg.customCurveYMorph = customCurveYMorph->getFloat();
    dataArg.customCurveZ.setValueArray(customCurveZ.parameters);
    dataArg.customCurveZ2.setValueArray(customCurveZ2.parameters);
    dataArg.customCurveZMorph = customCurveZMorph->getFloat();
}

void TXLFO3D::setAllFixedValues(TXLFO3DValues & dataArg) {
    lfoType->setFixedValue(dataArg.lfoType);
    randomSmoothType->setFixedValue(dataArg.randomSmoothType);
    setNoLevelsFixed(dataArg.noLevels);
    setBpmFixed(dataArg.bpm);
    useMasterBpm->setFixedValue(dataArg.useMasterBpm);
    frozen->setFixedValue(dataArg.frozen);
    phaseOffset->setFixedValue(dataArg.phaseOffset);
    setCycleTimeBeatsFixed(dataArg.cycleTimeBeats);
    setCycleTimeDivisorFixed(dataArg.cycleTimeDivisor);
    circularDirectionOut->setFixedValue(dataArg.circularDirectionOut);
    reverseX->setFixedValue(dataArg.reverseX);
    reverseY->setFixedValue(dataArg.reverseY);
    reverseZ->setFixedValue(dataArg.reverseZ);
    swapXAndY->setFixedValue(dataArg.swapXAndY);
    scaleX->setFixedValue(dataArg.scaleX);
    scaleY->setFixedValue(dataArg.scaleY);
    scaleZ->setFixedValue(dataArg.scaleZ);
    customCurveX.setValueArray(dataArg.customCurveX.parameters);
    customCurveX2.setValueArray(dataArg.customCurveX2.parameters);
    customCurveXMorph->setFixedValue(dataArg.customCurveXMorph);
    customCurveY.setValueArray(dataArg.customCurveY.parameters);
    customCurveY2.setValueArray(dataArg.customCurveY2.parameters);
    customCurveYMorph->setFixedValue(dataArg.customCurveYMorph);
    customCurveZ.setValueArray(dataArg.customCurveZ.parameters);
    customCurveZ2.setValueArray(dataArg.customCurveZ2.parameters);
    customCurveZMorph->setFixedValue(dataArg.customCurveZMorph);
   
    updateLfoType();
    updateBpm();
    updateCycleTimeBeats();
    updateCycleTimeDivisor();
    updateCurveX();
    updateCurveX2();
    updateCurveY();
    updateCurveY2();
    updateCurveZ();
    updateCurveZ2();
    
    update();
}


