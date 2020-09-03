/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXSimpleLFO2D.h"
#include "TXSystem.h"

// properties

// constructor
TXSimpleLFO2D::TXSimpleLFO2D (string paramNamePrefix, int lfoTypeArg, int randomSmoothTypeArg, int noLevelsArg, float bpmArg, float cycleTimeBeatsArg, float cycleTimeDivisorArg, float phaseOffsetArg, bool reverseXArg, bool reverseYArg, bool swapXAndYArg, bool circularDirectionOutArg, bool useMasterBpmArg, float scaleXArg, float scaleYArg, bool frozenArg, float customCurveXMorphArg, float customCurveYMorphArg){
    setup (paramNamePrefix, lfoTypeArg, randomSmoothTypeArg, noLevelsArg, bpmArg, cycleTimeBeatsArg, cycleTimeDivisorArg, phaseOffsetArg, reverseXArg, reverseYArg, swapXAndYArg, circularDirectionOutArg, useMasterBpmArg, scaleXArg, scaleYArg, frozenArg, customCurveXMorphArg,  customCurveYMorphArg);
};

// destructor
TXSimpleLFO2D::~TXSimpleLFO2D() {
    // remove listeners to relevent parameters:
    ofRemoveListener(customCurveX.parameters.parameterChangedE(),this,&TXSimpleLFO2D::customCurveXChanged);
    ofRemoveListener(customCurveX2.parameters.parameterChangedE(),this,&TXSimpleLFO2D::customCurveX2Changed);
    ofRemoveListener(customCurveY.parameters.parameterChangedE(),this,&TXSimpleLFO2D::customCurveYChanged);
    ofRemoveListener(customCurveY2.parameters.parameterChangedE(),this,&TXSimpleLFO2D::customCurveY2Changed);
}

// methods
void TXSimpleLFO2D::setup (string paramNamePrefix, int lfoTypeArg, int randomSmoothTypeArg, int noLevelsArg, float bpmArg, float cycleTimeBeatsArg, float cycleTimeDivisorArg, float phaseOffsetArg, bool reverseXArg, bool reverseYArg, bool swapXAndYArg, bool circularDirectionOutArg, bool useMasterBpmArg, float scaleXArg, float scaleYArg, bool frozenArg, float customCurveXMorphArg, float customCurveYMorphArg) {
    
    float phaseOffsetTime;
    
    // create input paramaters
    lfoType.set(paramNamePrefix + "lfoType", lfoType, 0, totalLFOTypes - 1);
    randomSmoothType.set(paramNamePrefix + "randomSmoothType", randomSmoothTypeArg, 0, TXLFO::numSmoothTypes - 1);
    bpm.set(paramNamePrefix + "bpm", bpm, 0.001, 1000.0);
    useMasterBpm.set(paramNamePrefix + "useMasterBpm", useMasterBpm);
    cycleTimeBeats.set(paramNamePrefix + "cycleTimeBeats", cycleTimeBeats, 0.01, 1000.0);
    cycleTimeDivisor.set(paramNamePrefix + "cycleTimeDivisor", cycleTimeDivisor, 0.01, 1000.0);
    phaseOffset.set(paramNamePrefix + "phaseOffset", phaseOffset, 0.0, 1.0);
    frozen.set(paramNamePrefix + "frozen", frozen);
    customCurveX.setValueArrayToRamp(0, 1);
    customCurveX.setName(paramNamePrefix + "customCurveX");
    customCurveX2.setValueArrayToRamp(0, 1);
    customCurveX2.setName(paramNamePrefix + "customCurveX2");
    customCurveXMorph.set(paramNamePrefix + "customCurveXMorph", customCurveXMorph);
    customCurveYMorph.set(paramNamePrefix + "customCurveYMorph", customCurveYMorph);
    noLevels.set(paramNamePrefix + "noLevels", noLevelsArg, 1, maxNoLevels);
    circularDirectionOut.set(paramNamePrefix + "circularDirectionOut", cycleTimeBeatsArg);
    reverseX.set(paramNamePrefix + "reverseX", reverseXArg);
    reverseY.set(paramNamePrefix + "reverseY", reverseYArg);
    swapXAndY.set(paramNamePrefix + "swapXAndY", swapXAndYArg);
    scaleX.set(paramNamePrefix + "scaleX", scaleXArg, 0.0, 1.0);
    scaleY.set(paramNamePrefix + "scaleY", scaleYArg, 0.0, 1.0);

    customCurveX.setValueArrayToRamp(0, 1);
    customCurveX.setName(paramNamePrefix + "customCurveX");
    customCurveX2.setValueArrayToRamp(0, 1);
    customCurveX2.setName(paramNamePrefix + "customCurveX2");
    customCurveXMorph.set(paramNamePrefix + "customCurveXMorph", customCurveXMorphArg, 0.0, 1.0);
    customCurveY.setValueArrayToRamp(0, 1);
    customCurveY.setName(paramNamePrefix + "customCurveY");
    customCurveY2.setValueArrayToRamp(0, 1);
    customCurveY2.setName(paramNamePrefix + "customCurveY2");
    customCurveYMorph.set(paramNamePrefix + "customCurveYMorph", customCurveYMorphArg, 0.0, 1.0);
    
    // init
    positionX = 0.5;
    positionY = 0.5;
    masterBpm = 60;
    
    // add listener to relevent parameters:

    lfoType.addListener(this,&TXSimpleLFO2D::lfoTypeChangedInt);
    randomSmoothType.addListener(this,&TXSimpleLFO2D::lfoTypeChangedInt);
    noLevels.addListener(this,&TXSimpleLFO2D::bpmChangedInt);
    useMasterBpm.addListener(this,&TXSimpleLFO2D::bpmChangedBool);
    bpm.addListener(this,&TXSimpleLFO2D::bpmChangedFloat);
    cycleTimeBeats.addListener(this,&TXSimpleLFO2D::cycleTimeBeatsChangedFloat);
    cycleTimeDivisor.addListener(this,&TXSimpleLFO2D::cycleTimeDivisorChangedFloat);
    
    ofAddListener(customCurveX.parameters.parameterChangedE(),this,&TXSimpleLFO2D::customCurveXChanged);
    ofAddListener(customCurveX2.parameters.parameterChangedE(),this,&TXSimpleLFO2D::customCurveX2Changed);
    ofAddListener(customCurveY.parameters.parameterChangedE(),this,&TXSimpleLFO2D::customCurveYChanged);
    ofAddListener(customCurveY2.parameters.parameterChangedE(),this,&TXSimpleLFO2D::customCurveY2Changed);
    
    float holdBpm;
    if (useMasterBpmArg) {
        holdBpm = masterBpm;
    } else {
        holdBpm = bpmArg;
    };
    phaseOffsetTime = phaseOffsetArg * holdBpm / (60 * noLevelsArg);
    currentTime = phaseOffsetTime; 
    requestResetClock = true;
    
    lfoAmp.setUseMasterBpm(false);
    lfoX.setUseMasterBpm(false);
    lfoY.setUseMasterBpm(false);
    customCurveXHasChanged = false;
    customCurveX2HasChanged = false;
    customCurveYHasChanged = false;
    customCurveY2HasChanged = false;

    updateBpm();
    updateCycleTimeBeats();
    updateCycleTimeDivisor();
    updateCurveX();
    updateCurveY();
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


void  TXSimpleLFO2D::lfoTypeChangedInt(int & dummyParameterArg ) {
    updateLfoType();
};

void  TXSimpleLFO2D::bpmChangedInt(int & dummyParameterArg ) {
    updateBpm();
}

void  TXSimpleLFO2D::bpmChangedBool(bool & dummyParameterArg ) {
    updateBpm();
}

void  TXSimpleLFO2D::bpmChangedFloat(float & dummyParameterArg ) {
    updateBpm();
}

void  TXSimpleLFO2D::cycleTimeBeatsChangedFloat(float & dummyParameterArg ) {
    updateCycleTimeBeats();
}

void  TXSimpleLFO2D::cycleTimeDivisorChangedFloat(float & dummyParameterArg ) {
    updateCycleTimeDivisor();
}

void  TXSimpleLFO2D::customCurveXChanged(ofAbstractParameter & dummyParameterArg ) {
    customCurveXHasChanged = true;
}

void  TXSimpleLFO2D::customCurveX2Changed(ofAbstractParameter & dummyParameterArg ) {
    customCurveX2HasChanged = true;
}

void  TXSimpleLFO2D::customCurveYChanged(ofAbstractParameter & dummyParameterArg ) {
    customCurveYHasChanged = true;
}

void  TXSimpleLFO2D::customCurveY2Changed(ofAbstractParameter & dummyParameterArg ) {
    customCurveY2HasChanged = true;
}

void TXSimpleLFO2D::updateCycleTimeBeats() {
    lfoAmp.setCycleTimeBeats(cycleTimeBeats);
    lfoX.setCycleTimeBeats(cycleTimeBeats);
    lfoY.setCycleTimeBeats(cycleTimeBeats);
};

void TXSimpleLFO2D::updateCycleTimeDivisor() {
    lfoAmp.setCycleTimeDivisor(cycleTimeDivisor);
    lfoX.setCycleTimeDivisor(cycleTimeDivisor);
    lfoY.setCycleTimeDivisor(cycleTimeDivisor);
};

void TXSimpleLFO2D::updateCurveX() {
    lfoX.customCurve.setValueArray(customCurveX.parameters);
};

void TXSimpleLFO2D::updateCurveX2() {
    lfoX.customCurve2.setValueArray(customCurveX2.parameters);
};

void TXSimpleLFO2D::updateCurveY() {
    lfoY.customCurve.setValueArray(customCurveY.parameters);
};

void TXSimpleLFO2D::updateCurveY2() {
    lfoY.customCurve2.setValueArray(customCurveY2.parameters);
};

void TXSimpleLFO2D::updateLfoType() {
    switch (lfoType) {
        case TXLFO2DTYPE_NOPATTERN:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_SINE);
            lfoY.setLfoType(TXLFOTYPE_SINE);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            break;
            
        case TXLFO2DTYPE_CIRCLES:
            useLfoAmp = true;
            lfoAmp.setLfoType(TXLFOTYPE_SAW);
            lfoX.setLfoType(TXLFOTYPE_SINE);
            lfoY.setLfoType(TXLFOTYPE_COSINE);
            quantiseLfoAmp = true;
            quantiseLfoX = false;
            quantiseLfoY = false;
            break;
            
        case TXLFO2DTYPE_SPIRALS:
            useLfoAmp = true;
            lfoAmp.setLfoType(TXLFOTYPE_SAW);
            lfoX.setLfoType(TXLFOTYPE_SINE);
            lfoY.setLfoType(TXLFOTYPE_COSINE);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            break;
            
        case TXLFO2DTYPE_SPIRALSINE:
            useLfoAmp = true;
            lfoAmp.setLfoType(TXLFOTYPE_SINE);
            lfoX.setLfoType(TXLFOTYPE_SINE);
            lfoY.setLfoType(TXLFOTYPE_COSINE);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            break;
            
        case TXLFO2DTYPE_SPIRALTRI:
            useLfoAmp = true;
            lfoAmp.setLfoType(TXLFOTYPE_TRIANGLE);
            lfoX.setLfoType(TXLFOTYPE_SINE);
            lfoY.setLfoType(TXLFOTYPE_COSINE);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            break;
            
        case TXLFO2DTYPE_LINES:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_SAW);
            lfoY.setLfoType(TXLFOTYPE_SAW);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = true;
            break;
            
        case TXLFO2DTYPE_DIAGONALLINES:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_SAW);
            lfoY.setLfoType(TXLFOTYPE_SAW);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            break;
            
        case TXLFO2DTYPE_GRID:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_SAW);
            lfoY.setLfoType(TXLFOTYPE_SAW);
            quantiseLfoAmp = false;
            quantiseLfoX = true;
            quantiseLfoY = true;
            break;
            
        case TXLFO2DTYPE_SINEWAVE:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_SAW);
            lfoY.setLfoType(TXLFOTYPE_SINE);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            break;
            
        case TXLFO2DTYPE_ZIGZAG:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_TRIANGLE);
            lfoY.setLfoType(TXLFOTYPE_TRIANGLE);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            break;
            
        case TXLFO2DTYPE_RANDOM:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_RANDOM);
            lfoY.setLfoType(TXLFOTYPE_RANDOM);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            break;
            
        case TXLFO2DTYPE_RANDOMQUANTISED:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_RANDOMQUANTISED);
            lfoY.setLfoType(TXLFOTYPE_RANDOMQUANTISED);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            break;
            
        case TXLFO2DTYPE_RANDOMSMOOTHED:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_RANDOMSMOOTHED);
            lfoY.setLfoType(TXLFOTYPE_RANDOMSMOOTHED);
            lfoX.setRandomSmoothType(randomSmoothType);
            lfoY.setRandomSmoothType(randomSmoothType);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            break;
            
        case TXLFO2DTYPE_DOUBLERANDOM:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_DOUBLERANDOM);
            lfoY.setLfoType(TXLFOTYPE_DOUBLERANDOM);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            break;
            
        case TXLFO2DTYPE_DOUBLERANDOMQUANTISED:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_DOUBLERANDOMQUANTISED);
            lfoY.setLfoType(TXLFOTYPE_DOUBLERANDOMQUANTISED);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            break;
            
        case TXLFO2DTYPE_DOUBLERANDOMSMOOTHED:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_DOUBLERANDOMSMOOTHED);
            lfoY.setLfoType(TXLFOTYPE_DOUBLERANDOMSMOOTHED);
            lfoX.setRandomSmoothType(randomSmoothType);
            lfoY.setRandomSmoothType(randomSmoothType);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            break;
        case TXLFO2DTYPE_CUSTOMCURVE:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_CUSTOMCURVE);
            lfoY.setLfoType(TXLFOTYPE_CUSTOMCURVE);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            break;
        case TXLFO2DTYPE_CUSTOMCURVE_MIRRORED:
            useLfoAmp = false;
            lfoAmp.setLfoType(TXLFOTYPE_SQUARE);
            lfoX.setLfoType(TXLFOTYPE_CUSTOMCURVE_MIRRORED);
            lfoY.setLfoType(TXLFOTYPE_CUSTOMCURVE_MIRRORED);
            quantiseLfoAmp = false;
            quantiseLfoX = false;
            quantiseLfoY = false;
            break;
    }
    resetTime();
}

void TXSimpleLFO2D::updateBpm() {
    float speedFast, speedSlow;
    
    if (useMasterBpm) {
        speedFast = masterBpm;
    } else {
        speedFast = bpm;
    };
    speedSlow = speedFast/ noLevels;

    switch (lfoType) {
        case TXLFO2DTYPE_NOPATTERN:
            lfoAmp.setBpm(0);
            lfoX.setBpm(0);
            lfoY.setBpm(0);
            break;
            
        case TXLFO2DTYPE_CIRCLES:
            lfoAmp.setBpm(speedSlow);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedFast);
            break;
            
        case TXLFO2DTYPE_SPIRALS:
            lfoAmp.setBpm(speedSlow);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedFast);
            break;
            
        case TXLFO2DTYPE_SPIRALSINE:
            lfoAmp.setBpm(speedSlow);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedFast);
            break;
            
        case TXLFO2DTYPE_SPIRALTRI:
            lfoAmp.setBpm(speedSlow);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedFast);
            break;
            
        case TXLFO2DTYPE_LINES:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedSlow);
            break;
            
        case TXLFO2DTYPE_DIAGONALLINES:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedSlow);
            lfoY.setBpm(speedFast);
            break;
            
        case TXLFO2DTYPE_GRID:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedSlow);
            break;
            
        case TXLFO2DTYPE_SINEWAVE:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedSlow);
            lfoY.setBpm(speedFast);
            break;
            
        case TXLFO2DTYPE_ZIGZAG:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedSlow);
            lfoY.setBpm(speedFast);
            break;
            
        case TXLFO2DTYPE_RANDOM:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedFast);
            break;
            
        case TXLFO2DTYPE_RANDOMQUANTISED:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedFast);
            break;
            
        case TXLFO2DTYPE_RANDOMSMOOTHED:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedFast);
            break;
            
        case TXLFO2DTYPE_DOUBLERANDOM:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedFast);
            break;
            
        case TXLFO2DTYPE_DOUBLERANDOMQUANTISED:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedFast);
            break;
            
        case TXLFO2DTYPE_DOUBLERANDOMSMOOTHED:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedFast);
            break;
            
        case TXLFO2DTYPE_CUSTOMCURVE:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedFast);
            break;
            
        case TXLFO2DTYPE_CUSTOMCURVE_MIRRORED:
            lfoAmp.setBpm(0);
            lfoX.setBpm(speedFast);
            lfoY.setBpm(speedFast);
            break;
            
        default:
            lfoAmp.setBpm(0);
            lfoX.setBpm(0);
            lfoY.setBpm(0);
            break;
    }
}

//void TXSimpleLFO2D::setTime(float timeArg, float masterBpmArg){
//    float phaseOffsetTime;
//    float holdBpm;
//    
//    masterBpm = masterBpmArg;
//    if (frozen) {
//        return;
//    };
//    if (useMasterBpm) {
//        holdBpm = masterBpm;
//    } else {
//        holdBpm = bpm;
//    };
//    phaseOffsetTime = phaseOffset * holdBpm / (60 * noLevels);
//    currentTime = timeArg + phaseOffsetTime;
//    lfoAmp.setTime(currentTime, masterBpm);
//    lfoX.setTime(currentTime, masterBpm);
//    lfoY.setTime(currentTime, masterBpm);
//    recalcPosXY();
//};

void TXSimpleLFO2D::resetTime() {
    float phaseOffsetTime;
    float holdBpm;
    if (useMasterBpm) {
        holdBpm = masterBpm;
    } else {
        holdBpm = bpm;
    };
    lfoAmp.resetTime();
    lfoX.resetTime();
    lfoY.resetTime();
    phaseOffsetTime = phaseOffset * holdBpm / (60 * noLevels);
    currentTime = phaseOffsetTime;
    recalcPosXY();
}

void TXSimpleLFO2D::update() {
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
}

// override base class
void TXSimpleLFO2D::setMasterBpm(float masterBpmArg){
    masterBpm = masterBpmArg;
    updateBpm();
};

void TXSimpleLFO2D::advanceBy(float timeDeltaArg, float masterBpmArg) {
    float phaseOffsetTime;
    float holdBpm;
    
    masterBpm = masterBpmArg;
    if (frozen) {
        return;
    };
    if (requestResetClock) {
        resetTime();
        requestResetClock = false;
    };
    if (useMasterBpm) {
        holdBpm = masterBpm;
    } else {
        holdBpm = bpm;
    };
    currentTime += timeDeltaArg;
    lfoAmp.advanceBy(timeDeltaArg, masterBpm);
    lfoX.advanceBy(timeDeltaArg, masterBpm);
    lfoY.advanceBy(timeDeltaArg, masterBpm);
    recalcPosXY();
}

void TXSimpleLFO2D::recalcPosXY() {
    float holdLfoAmp, holdLfoX, holdLfoY, holdX, holdY, holdXR, holdYR;
    float offset, holdScaleX, holdScaleY;
    int  holdNoLevels;
    
    if (useLfoAmp) {
        holdLfoAmp = lfoAmp.getValue();
    } else {
        holdLfoAmp = 1;
    };
    holdLfoX = lfoX.getValue();
    holdLfoY = lfoY.getValue();
    holdNoLevels = noLevels;
    holdScaleX = scaleX;
    holdScaleY = scaleY;
    if (quantiseLfoAmp) {
        if (circularDirectionOut) {
            holdLfoAmp = ceil (0.00001 + (holdLfoAmp * 0.99999 * holdNoLevels)) / holdNoLevels;
        } else {
            holdLfoAmp = ceil ((1-holdLfoAmp) * holdNoLevels) / holdNoLevels;
        };
    } else {
        if (!circularDirectionOut && useLfoAmp) {
            holdLfoAmp = 1 - holdLfoAmp;
        };
    };
    if (quantiseLfoX) {
        holdLfoX = floor (holdLfoX * 0.99999 * holdNoLevels) / max (holdNoLevels - 1, 1);
    };
    if (quantiseLfoY) {
        holdLfoY = floor (holdLfoY * 0.99999 * holdNoLevels) / max (holdNoLevels - 1, 1);
    };
    offset = (1 - holdLfoAmp) * 0.5;
    holdX = offset + (holdLfoAmp * holdLfoX);
    holdY = offset + (holdLfoAmp * holdLfoY);
    
    // adjust for scale, reverse & swapXY
    holdX = (holdX * holdScaleX) + (0.5 * (1 - holdScaleX));
    holdY = (holdY * holdScaleY) + (0.5 * (1 - holdScaleY));
    if (reverseX) {holdXR = (1-holdX);} else {holdXR = holdX;}
    if (reverseY) {holdYR = (1-holdY);} else {holdYR = holdY;}
    if (swapXAndY) {positionX = holdYR;} else  {positionX = holdXR;};
    if (swapXAndY) {positionY = holdXR;} else  {positionY = holdYR;};
};



void TXSimpleLFO2D::getAllValues(TXLFO2DValues & dataArg) {
    //add data
    
    dataArg.lfoType = lfoType;
    dataArg.randomSmoothType = randomSmoothType;
    dataArg.noLevels = noLevels;
    dataArg.bpm = bpm;
    dataArg.useMasterBpm = useMasterBpm;
    dataArg.frozen = frozen;
    dataArg.cycleTimeBeats = cycleTimeBeats;
    dataArg.cycleTimeDivisor = cycleTimeDivisor;
    dataArg.phaseOffset = phaseOffset;
    dataArg.circularDirectionOut = circularDirectionOut;
    dataArg.reverseX = reverseX;
    dataArg.reverseY = reverseY;
    dataArg.swapXAndY = swapXAndY;
    dataArg.scaleX = scaleX;
    dataArg.scaleY = scaleY;
    dataArg.customCurveX.setValueArray(customCurveX.parameters);
    dataArg.customCurveX2.setValueArray(customCurveX2.parameters);
    dataArg.customCurveXMorph = customCurveXMorph;
    dataArg.customCurveY.setValueArray(customCurveY.parameters);
    dataArg.customCurveY2.setValueArray(customCurveY2.parameters);
    dataArg.customCurveYMorph = customCurveYMorph;
}

void TXSimpleLFO2D::setAllValues(TXLFO2DValues & dataArg) {
    lfoType = dataArg.lfoType;
    randomSmoothType = dataArg.randomSmoothType;
    noLevels = dataArg.noLevels;
    bpm = dataArg.bpm;
    useMasterBpm = dataArg.useMasterBpm;
    frozen = dataArg.frozen;
    cycleTimeBeats = dataArg.cycleTimeBeats;
    cycleTimeDivisor = dataArg.cycleTimeDivisor;
    phaseOffset = dataArg.phaseOffset;
    circularDirectionOut = dataArg.circularDirectionOut;
    reverseX = dataArg.reverseX;
    reverseY = dataArg.reverseY;
    swapXAndY = dataArg.swapXAndY;
    scaleX = dataArg.scaleX;
    scaleY = dataArg.scaleY;
    customCurveX.setValueArray(dataArg.customCurveX.parameters);
    customCurveX2.setValueArray(dataArg.customCurveX2.parameters);
    customCurveXMorph = dataArg.customCurveXMorph;
    customCurveY.setValueArray(dataArg.customCurveY.parameters);
    customCurveY2.setValueArray(dataArg.customCurveY2.parameters);
    customCurveYMorph = dataArg.customCurveYMorph;
    
    updateLfoType();
    updateBpm();
    updateCycleTimeBeats();
    updateCycleTimeDivisor();
    updateCurveX();
    updateCurveX2();
    updateCurveY();
    updateCurveY2();
    
    update();
}


