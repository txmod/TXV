/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXSimpleLFO3D.h"
#include "TXSystem.h"

// properties

// constructor
TXSimpleLFO3D::TXSimpleLFO3D (string paramNamePrefix, int lfoTypeArg, int randomSmoothTypeArg, int noLevelsArg, float bpmArg, float cycleTimeBeatsArg, float cycleTimeDivisorArg, float phaseOffsetArg, bool reverseXArg, bool reverseYArg, bool reverseZArg, bool swapXAndYArg, bool circularDirectionOutArg, bool useMasterBpmArg, float scaleXArg, float scaleYArg, float scaleZArg, bool frozenArg, float customCurveXMorphArg, float customCurveYMorphArg, float customCurveZMorphArg){
    setup (paramNamePrefix, lfoTypeArg, randomSmoothTypeArg, noLevelsArg, bpmArg, cycleTimeBeatsArg, cycleTimeDivisorArg, phaseOffsetArg, reverseXArg, reverseYArg, reverseZArg, swapXAndYArg, circularDirectionOutArg, useMasterBpmArg, scaleXArg, scaleYArg, scaleZArg, frozenArg, customCurveXMorphArg,  customCurveYMorphArg, customCurveZMorphArg);
};

// destructor
TXSimpleLFO3D::~TXSimpleLFO3D() {
    // remove listeners to relevent parameters:
    ofRemoveListener(customCurveX.parameters.parameterChangedE(),this,&TXSimpleLFO3D::customCurveXChanged);
    ofRemoveListener(customCurveX2.parameters.parameterChangedE(),this,&TXSimpleLFO3D::customCurveX2Changed);
    ofRemoveListener(customCurveY.parameters.parameterChangedE(),this,&TXSimpleLFO3D::customCurveYChanged);
    ofRemoveListener(customCurveY2.parameters.parameterChangedE(),this,&TXSimpleLFO3D::customCurveY2Changed);
    ofRemoveListener(customCurveZ.parameters.parameterChangedE(),this,&TXSimpleLFO3D::customCurveZChanged);
    ofRemoveListener(customCurveZ2.parameters.parameterChangedE(),this,&TXSimpleLFO3D::customCurveZ2Changed);
}

// methods
void TXSimpleLFO3D::setup (string paramNamePrefix, int lfoTypeArg, int randomSmoothTypeArg, int noLevelsArg, float bpmArg, float cycleTimeBeatsArg, float cycleTimeDivisorArg, float phaseOffsetArg, bool reverseXArg, bool reverseYArg, bool reverseZArg, bool swapXAndYArg, bool circularDirectionOutArg, bool useMasterBpmArg, float scaleXArg, float scaleYArg, float scaleZArg, bool frozenArg, float customCurveXMorphArg, float customCurveYMorphArg, float customCurveZMorphArg) {
    
    float phaseOffsetTime;

    // template
    // xxx.set("xxx", 0, 0, 1);
    // xxx.set("xxx", true);
    // xxx.set("xxx", 0.0, 0.0, 1.0);

    // create input paramaters
    lfoType.set(paramNamePrefix + "lfoType", lfoType, 0, totalLFOTypes - 1);
    randomSmoothType.set(paramNamePrefix + "randomSmoothType", randomSmoothTypeArg, 0, TXLFO::numSmoothTypes - 1);
    bpm.set(paramNamePrefix + "bpm", bpm, 0.001, 1000.0);
    useMasterBpm.set(paramNamePrefix + "useMasterBpm", useMasterBpm);
    cycleTimeBeats.set(paramNamePrefix + "cycleTimeBeats", cycleTimeBeats, 0.01, 1000.0);
    cycleTimeDivisor.set(paramNamePrefix + "cycleTimeDivisor", cycleTimeDivisor, 0.01, 1000.0);
    phaseOffset.set(paramNamePrefix + "phaseOffset", phaseOffset, 0.0, 1.0);
    frozen.set(paramNamePrefix + "frozen", frozen);
    noLevels.set(paramNamePrefix + "noLevels", noLevelsArg, 1, maxNoLevels);
    circularDirectionOut.set(paramNamePrefix + "circularDirectionOut", cycleTimeBeatsArg);
    reverseX.set(paramNamePrefix + "reverseX", reverseXArg);
    reverseY.set(paramNamePrefix + "reverseY", reverseYArg);
    reverseZ.set(paramNamePrefix + "reverseZ", reverseZArg);
    swapXAndY.set(paramNamePrefix + "swapXAndY", swapXAndYArg);
    scaleX.set(paramNamePrefix + "scaleX", scaleXArg, 0.0, 1.0);
    scaleY.set(paramNamePrefix + "scaleY", scaleYArg, 0.0, 1.0);
    scaleZ.set(paramNamePrefix + "scaleZ", scaleZArg, 0.0, 1.0);
    
    
    customCurveX.setValueArrayToRamp(0, 1);
    customCurveX.setName(paramNamePrefix + "customCurveX");
    
    customCurveX2.setValueArrayToRamp(0, 1);
    customCurveX2.setName(paramNamePrefix + "customCurveX2");
    
    customCurveXMorph.set(paramNamePrefix + "customCurveXMorph", customCurveXMorph);
    
    customCurveY.setValueArrayToRamp(0, 1);
    customCurveY.setName(paramNamePrefix + "customCurveY");
    
    customCurveY2.setValueArrayToRamp(0, 1);
    customCurveY2.setName(paramNamePrefix + "customCurveY2");
    
    customCurveYMorph.set(paramNamePrefix + "customCurveYMorph", customCurveYMorph);
    
    customCurveZ.setValueArrayToRamp(0, 1);
    customCurveZ.setName(paramNamePrefix + "customCurveZ");
    
    customCurveZ2.setValueArrayToRamp(0, 1);
    customCurveZ2.setName(paramNamePrefix + "customCurveZ2");
    customCurveZMorph.set(paramNamePrefix + "customCurveZMorph", customCurveZMorph);
    
    // create mod source outputs
    positionX = 0.5;
    positionY = 0.5;
    positionZ = 0.5;
    masterBpm = 60;
    
    // add listener to relevent parameters:
    lfoType.addListener(this,&TXSimpleLFO3D::lfoTypeChangedInt);
    randomSmoothType.addListener(this,&TXSimpleLFO3D::lfoTypeChangedInt);
    noLevels.addListener(this,&TXSimpleLFO3D::bpmChangedInt);
    useMasterBpm.addListener(this,&TXSimpleLFO3D::bpmChangedBool);
    bpm.addListener(this,&TXSimpleLFO3D::bpmChangedFloat);
    cycleTimeBeats.addListener(this,&TXSimpleLFO3D::cycleTimeBeatsChangedFloat);
    cycleTimeDivisor.addListener(this,&TXSimpleLFO3D::cycleTimeDivisorChangedFloat);
    
    ofAddListener(customCurveX.parameters.parameterChangedE(),this,&TXSimpleLFO3D::customCurveXChanged);
    ofAddListener(customCurveX2.parameters.parameterChangedE(),this,&TXSimpleLFO3D::customCurveX2Changed);
    ofAddListener(customCurveY.parameters.parameterChangedE(),this,&TXSimpleLFO3D::customCurveYChanged);
    ofAddListener(customCurveY2.parameters.parameterChangedE(),this,&TXSimpleLFO3D::customCurveY2Changed);
    ofAddListener(customCurveZ.parameters.parameterChangedE(),this,&TXSimpleLFO3D::customCurveZChanged);
    ofAddListener(customCurveZ2.parameters.parameterChangedE(),this,&TXSimpleLFO3D::customCurveZChanged);

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

void  TXSimpleLFO3D::lfoTypeChangedInt(int & dummyParameterArg ) {
    updateLfoType();
};

void  TXSimpleLFO3D::bpmChangedInt(int & dummyParameterArg ) {
    updateBpm();
}

void  TXSimpleLFO3D::bpmChangedBool(bool & dummyParameterArg ) {
    updateBpm();
}

void  TXSimpleLFO3D::bpmChangedFloat(float & dummyParameterArg ) {
    updateBpm();
}

void  TXSimpleLFO3D::cycleTimeBeatsChangedFloat(float & dummyParameterArg ) {
    updateCycleTimeBeats();
}

void  TXSimpleLFO3D::cycleTimeDivisorChangedFloat(float & dummyParameterArg ) {
    updateCycleTimeDivisor();
}

void  TXSimpleLFO3D::customCurveXChanged(ofAbstractParameter & dummyParameterArg ) {
    customCurveXHasChanged = true;
}

void  TXSimpleLFO3D::customCurveX2Changed(ofAbstractParameter & dummyParameterArg ) {
    customCurveX2HasChanged = true;
}

void  TXSimpleLFO3D::customCurveYChanged(ofAbstractParameter & dummyParameterArg ) {
    customCurveYHasChanged = true;
}

void  TXSimpleLFO3D::customCurveY2Changed(ofAbstractParameter & dummyParameterArg ) {
    customCurveY2HasChanged = true;
}

void  TXSimpleLFO3D::customCurveZChanged(ofAbstractParameter & dummyParameterArg ) {
    customCurveZHasChanged = true;
}

void  TXSimpleLFO3D::customCurveZ2Changed(ofAbstractParameter & dummyParameterArg ) {
    customCurveZ2HasChanged = true;
}


void TXSimpleLFO3D::updateCycleTimeBeats() {
    lfoAmp.setCycleTimeBeats(cycleTimeBeats);
    lfoX.setCycleTimeBeats(cycleTimeBeats);
    lfoY.setCycleTimeBeats(cycleTimeBeats);
    lfoZ.setCycleTimeBeats(cycleTimeBeats);
};

void TXSimpleLFO3D::updateCycleTimeDivisor() {
    lfoAmp.setCycleTimeDivisor(cycleTimeDivisor);
    lfoX.setCycleTimeDivisor(cycleTimeDivisor);
    lfoY.setCycleTimeDivisor(cycleTimeDivisor);
    lfoZ.setCycleTimeDivisor(cycleTimeDivisor);
};

void TXSimpleLFO3D::updateCurveX() {
    lfoX.customCurve.setValueArray(customCurveX.getValueArray());
};

void TXSimpleLFO3D::updateCurveX2() {
    lfoX.customCurve2.setValueArray(customCurveX2.getValueArray());
};

void TXSimpleLFO3D::updateCurveY() {
    lfoY.customCurve.setValueArray(customCurveY.getValueArray());
};

void TXSimpleLFO3D::updateCurveY2() {
    lfoY.customCurve2.setValueArray(customCurveY2.getValueArray());
};

void TXSimpleLFO3D::updateCurveZ() {
    lfoZ.customCurve.setValueArray(customCurveZ.getValueArray());
};

void TXSimpleLFO3D::updateCurveZ2() {
    lfoZ.customCurve2.setValueArray(customCurveZ2.getValueArray());
};


void TXSimpleLFO3D::updateLfoType() {
    switch (lfoType) {
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
            lfoX.setRandomSmoothType(randomSmoothType);
            lfoY.setRandomSmoothType(randomSmoothType);
            lfoZ.setRandomSmoothType(randomSmoothType);
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
            lfoX.setRandomSmoothType(randomSmoothType);
            lfoY.setRandomSmoothType(randomSmoothType);
            lfoZ.setRandomSmoothType(randomSmoothType);
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
            lfoX.setRandomSmoothType(randomSmoothType);
            lfoY.setRandomSmoothType(randomSmoothType);
            lfoZ.setRandomSmoothType(randomSmoothType);
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
            lfoX.setRandomSmoothType(randomSmoothType);
            lfoY.setRandomSmoothType(randomSmoothType);
            lfoZ.setRandomSmoothType(randomSmoothType);
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
            lfoX.setRandomSmoothType(randomSmoothType);
            lfoY.setRandomSmoothType(randomSmoothType);
            lfoZ.setRandomSmoothType(randomSmoothType);
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
            lfoX.setRandomSmoothType(randomSmoothType);
            lfoY.setRandomSmoothType(randomSmoothType);
            lfoZ.setRandomSmoothType(randomSmoothType);
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

void TXSimpleLFO3D::updateBpm() {
    float speedFast, speedSlow;
    
    if (useMasterBpm) {
        speedFast = masterBpm;
    } else {
        speedFast = bpm;
    };
    speedSlow = speedFast/ noLevels;

    switch (lfoType) {
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

//void TXSimpleLFO3D::setTime(float timeArg, float masterBpmArg){
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
//     currentTime = timeArg + phaseOffsetTime;
//    lfoAmp.setTime(currentTime, masterBpm);
//    lfoX.setTime(currentTime, masterBpm);
//    lfoY.setTime(currentTime, masterBpm);
//    lfoZ.setTime(currentTime, masterBpm);
//    recalcPosXYZ();
//};

void TXSimpleLFO3D::resetTime() {
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
    lfoZ.resetTime();
    phaseOffsetTime = phaseOffset * holdBpm / (60 * noLevels);
    currentTime = phaseOffsetTime;
    recalcPosXYZ();
}

void TXSimpleLFO3D::update() {
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
void TXSimpleLFO3D::setMasterBpm(float masterBpmArg){
    masterBpm = masterBpmArg;
    updateBpm();
};

void TXSimpleLFO3D::advanceBy(float timeDeltaArg, float masterBpmArg) {
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
    lfoZ.advanceBy(timeDeltaArg, masterBpm);
    recalcPosXYZ();
}

void TXSimpleLFO3D::recalcPosXYZ() {
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
    
    holdNoLevels = noLevels;
    holdScaleX = scaleX;
    holdScaleY = scaleY;
    holdScaleZ = scaleZ;
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
    if (reverseX) {holdXR = (1-holdX);} else {holdXR = holdX;}
    if (reverseY) {holdYR = (1-holdY);} else {holdYR = holdY;}
    if (reverseZ) {holdZR = (1-holdZ);} else {holdZR = holdZ;}
    if (swapXAndY) {positionX = holdYR;} else  {positionX = holdXR;};
    if (swapXAndY) {positionY = holdXR;} else  {positionY = holdYR;};
    positionZ = holdZR;
};


void TXSimpleLFO3D::getAllValues(TXLFO3DValues & dataArg) {
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
    dataArg.reverseZ = reverseZ;
    dataArg.swapXAndY = swapXAndY;
    dataArg.scaleX = scaleX;
    dataArg.scaleY = scaleY;
    dataArg.scaleZ = scaleZ;
    dataArg.customCurveX.setValueArray(customCurveX.getValueArray());
    dataArg.customCurveX2.setValueArray(customCurveX2.getValueArray());
    dataArg.customCurveXMorph = customCurveXMorph;
    dataArg.customCurveY.setValueArray(customCurveY.getValueArray());
    dataArg.customCurveY2.setValueArray(customCurveY2.getValueArray());
    dataArg.customCurveYMorph = customCurveYMorph;
    dataArg.customCurveZ.setValueArray(customCurveZ.getValueArray());
    dataArg.customCurveZ2.setValueArray(customCurveZ2.getValueArray());
    dataArg.customCurveZMorph = customCurveZMorph;
}

void TXSimpleLFO3D::setAllValues(TXLFO3DValues & dataArg) {
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
    reverseZ = dataArg.reverseZ;
    swapXAndY = dataArg.swapXAndY;
    scaleX = dataArg.scaleX;
    scaleY = dataArg.scaleY;
    scaleZ = dataArg.scaleZ;
    customCurveX.setValueArray(dataArg.customCurveX.parameters);
    customCurveX2.setValueArray(dataArg.customCurveX2.parameters);
    customCurveXMorph = dataArg.customCurveXMorph;
    customCurveY.setValueArray(dataArg.customCurveY.parameters);
    customCurveY2.setValueArray(dataArg.customCurveY2.parameters);
    customCurveYMorph = dataArg.customCurveYMorph;
    customCurveZ.setValueArray(dataArg.customCurveZ.parameters);
    customCurveZ2.setValueArray(dataArg.customCurveZ2.parameters);
    customCurveZMorph = dataArg.customCurveZMorph;

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


