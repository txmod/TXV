/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXSimpleLFO.h"
#include "TXSystem.h"
#include "TXFunctions.h"
#include "ofxTweenLite.h"
#include "TXLFO.h"

// properties

// constructor
TXSimpleLFO::TXSimpleLFO(){
    TXSimpleLFOArgs holdArgs;
    setup(holdArgs);
};

TXSimpleLFO::TXSimpleLFO(TXSimpleLFOArgs holdArgs){
    setup(holdArgs);
};

// methods
void TXSimpleLFO::setup (TXSimpleLFOArgs holdLFOArgs) {    
 
    // set inputs
    lfoType = holdLFOArgs.lfoType;
    randomSmoothType = holdLFOArgs.randomSmoothType;
    bpm = holdLFOArgs.bpm;
    useMasterBpm = holdLFOArgs.useMasterBpm;
    cycleTimeBeats = holdLFOArgs.cycleTimeBeats;
    cycleTimeDivisor = holdLFOArgs.cycleTimeDivisor;
    phaseOffset = holdLFOArgs.phaseOffset;
    pulseWidth = holdLFOArgs.pulseWidth;
    frozen = holdLFOArgs.frozen;
    customCurve.setValueArrayToRamp(0, 1);
    customCurve.setName("customCurve");
    customCurve2.setValueArrayToRamp(0, 1);
    customCurve2.setName("customCurve2");
    customCurveMorph = holdLFOArgs.customCurveMorph;
    
    // init
    outValue = 0;
    masterBpm = 60;
    currentTime = 0.0;
    requestResetClock = true;
    oldPhaseOffset = 0.0;
    phase = holdLFOArgs.phaseOffset;
    randPhase = ofRandom(1.0);
    oldRandPhase = ofRandom(1.0);
    doubleRandMultiply = 1;
    updateRandomiser(true); // force new random no
    calculateOutput();
}

//void TXSimpleLFO::setTime(float timeArg, float masterBpmArg){
//	float holdPhase;
//    float holdSpeed;
//    
//    masterBpm = masterBpmArg;
//    if (frozen) {
//        return;
//    };
//    if (useMasterBpm) {
//        holdSpeed = masterBpm / 60;
//    } else {
//        holdSpeed = bpm / 60;
//    };
//    currentTime = timeArg;
//    holdPhase = timeArg * doubleRandMultiply * holdSpeed  * cycleTimeDivisor / cycleTimeBeats;
//    phase = phaseOffset + fmod(holdPhase, 1.0f);
//    updateRandomiser();
//    calculateOutput();
//}

void TXSimpleLFO::resetTime() {
    resetTime(-1);
}

void TXSimpleLFO::resetTime(int randSeed) {
    currentTime = 0.0;
    phase = phaseOffset;
    oldPhaseOffset = phaseOffset;
    updateRandomiser(true, randSeed); // force new random no
    calculateOutput();
}

void TXSimpleLFO::advanceBy(float timeDeltaArg, float masterBpmArg) {
	float holdPhase;
    float holdSpeed;
    float changePhaseOffset;
    masterBpm = masterBpmArg;
    if (frozen) {
        return;
    };
    if (requestResetClock) {
        resetTime();
        requestResetClock = false;
    };
    if (useMasterBpm) {
        holdSpeed = masterBpm / 60;
    } else {
        holdSpeed = bpm / 60;
    };
    currentTime += timeDeltaArg;
    holdPhase = (phase + (timeDeltaArg * doubleRandMultiply * holdSpeed  * cycleTimeDivisor / cycleTimeBeats));
    changePhaseOffset = phaseOffset - oldPhaseOffset;
    // use abs val if random LFO
    if ((lfoType == TXLFOTYPE_RANDOM)
        || (lfoType == TXLFOTYPE_RANDOMQUANTISED)
        || (lfoType == TXLFOTYPE_RANDOMSMOOTHED)
        || (lfoType == TXLFOTYPE_DOUBLERANDOM)
        || (lfoType == TXLFOTYPE_DOUBLERANDOMQUANTISED)
        || (lfoType == TXLFOTYPE_DOUBLERANDOMSMOOTHED)
        )
    {
        changePhaseOffset = fabs(changePhaseOffset);
    };
    phase = fmod(1.0 + changePhaseOffset + holdPhase, 1.0f);
    updateRandomiser();    
    calculateOutput();
    oldPhaseOffset = phaseOffset;
}

float TXSimpleLFO::getPhase() {
    return phase;
}

float TXSimpleLFO::getValue() {
    return outValue;
}

void TXSimpleLFO::calculateOutput() {
    float twoPIPhase = TWO_PI * phase;
    float holdVal, holdMorph;
    switch (lfoType) {
        case TXLFOTYPE_SINE:
            outValue = 0.5 + (0.5 * sin(twoPIPhase));
            break;
        case TXLFOTYPE_COSINE:
            outValue = 0.5 + (0.5 * cos(twoPIPhase));
            break;
        case TXLFOTYPE_SQUARE:
            outValue = (float) (phase < 0.5);
            break;
        case TXLFOTYPE_PULSE:
            outValue = (float) (phase < min(max((float)pulseWidth, 0.001f),0.999f));
            break;
        case TXLFOTYPE_TRIANGLE:
            outValue = abs(1.0f - (2.0f * fmod(phase + 0.75f, 1.0f)));
            break;
        case TXLFOTYPE_SAW:
            outValue = phase;
            break;
        case TXLFOTYPE_SAWREVERSE:
            outValue = (1 - phase);
            break;
        case TXLFOTYPE_RANDOM:
            outValue = randPhase;
            break;
        case TXLFOTYPE_RANDOMQUANTISED:
            outValue = (int)(randPhase + 0.5);
            break;
        case TXLFOTYPE_RANDOMSMOOTHED:
            outValue = ofxTweenLite::tween (oldRandPhase, randPhase, phase, (ofEaseFunction) (randomSmoothType + smoothTypeOffset));

            // testing XXX
            
//            ofLogNotice() << "TXSimpleLFO::calculateOutput() - phase " << phase;
////            ofLogNotice() << "TXSimpleLFO::calculateOutput() - oldRandPhase " << oldRandPhase;
////            ofLogNotice() << "TXSimpleLFO::calculateOutput() - randPhase " << randPhase;
//            ofLogNotice() << "TXSimpleLFO::calculateOutput() - (randPhase -  oldRandPhase)" << (randPhase -  oldRandPhase);
//            ofLogNotice() << "- - -" ;

            break;
        case TXLFOTYPE_DOUBLERANDOM:
            outValue = randPhase;
            break;
        case TXLFOTYPE_DOUBLERANDOMQUANTISED:
            outValue = (int)(randPhase + 0.5);
            break;
        case TXLFOTYPE_DOUBLERANDOMSMOOTHED:
            outValue = ofxTweenLite::tween (oldRandPhase, randPhase, phase, (ofEaseFunction) (randomSmoothType + smoothTypeOffset));
            break;
        case TXLFOTYPE_TREFOILKNOTX:
            // trefoilX = sin t + 2 sin 2t;
            holdVal = 0.3333333333 * (sin(twoPIPhase) + (2 * sin(2 * twoPIPhase)));
            outValue = 0.5 + (0.5 * holdVal);
            break;
        case TXLFOTYPE_TREFOILKNOTY:
            // trefoilY = cos t - 2 cos 2t;
            holdVal = 0.3333333333 * (cos(twoPIPhase) - (2 * cos(2 * twoPIPhase)));
            outValue = 0.5 + (0.5 * holdVal);
            break;
        case TXLFOTYPE_TREFOILKNOTZ:
            // trefoilZ = - sin 3t;
            holdVal = 0.3333333333 * -sin(3 * twoPIPhase);
            // holdVal =  -sin(3 * twoPIPhase);
            outValue = 0.5 + (0.5 * holdVal);
            break;
        case TXLFOTYPE_CUSTOMCURVE:
            holdMorph = customCurveMorph;
            outValue = TXFunctions::getInterpCurves(customCurve, customCurve2, phase, holdMorph);
            break;
        case TXLFOTYPE_CUSTOMCURVE_MIRRORED:
            holdMorph = customCurveMorph;
            if (phase<0.5) {
                holdVal = 2 * phase;
            } else {
                holdVal = 1 - (2 * (phase - 0.5));
            };
            outValue = TXFunctions::getInterpCurves(customCurve, customCurve2, holdVal, holdMorph);
            break;
        default:
            outValue = phase;
            break;
    }
}

int   TXSimpleLFO::getLfoType(){
    return lfoType;
}

void  TXSimpleLFO::setLfoType(int lfoTypeArg){
    lfoType = lfoTypeArg;
    updateRandomiser();
}

int   TXSimpleLFO::getRandomSmoothType(){
    return randomSmoothType;
}

void  TXSimpleLFO::setRandomSmoothType(int randomSmoothTypeArg){
    randomSmoothType = randomSmoothTypeArg;
}

float TXSimpleLFO::getBpm() {
    return bpm;
} 

void  TXSimpleLFO::setBpm(float bpmArg){
    bpm = bpmArg;
    updateRandomiser();
}

float TXSimpleLFO::getCycleTimeBeats(){
    return cycleTimeBeats;
}

void  TXSimpleLFO::setCycleTimeBeats(float cycleTimeBeatsArg){
    cycleTimeBeats = (float)fmax(cycleTimeBeatsArg, 0.001);
}

float TXSimpleLFO::getCycleTimeDivisor(){
    return cycleTimeDivisor;
}

void  TXSimpleLFO::setCycleTimeDivisor(float cycleTimeDivisorArg){
    cycleTimeDivisor = (float)fmax(cycleTimeDivisorArg, 0.001f);
}

float TXSimpleLFO::getPhaseOffset(){
    return phaseOffset;
}

void  TXSimpleLFO::setPhaseOffset(float phaseOffsetArg){
    phaseOffset = phaseOffsetArg;
}

float TXSimpleLFO::getPulseWidth(){
    return pulseWidth;
}

void  TXSimpleLFO::setPulseWidth(float pulseWidthArg){
    pulseWidth = pulseWidthArg;
}

bool  TXSimpleLFO::getUseMasterBpm(){
    return useMasterBpm;
}

void  TXSimpleLFO::setUseMasterBpm(bool useMasterBpmArg){
    useMasterBpm = useMasterBpmArg;
    updateRandomiser();
}

bool  TXSimpleLFO::getFrozen(){
    return frozen;
}

void  TXSimpleLFO::setFrozen(bool frozenArg){
    frozen = frozenArg;
}

float * TXSimpleLFO::getCustomCurve(){
    return customCurve.getValueArray();
}

float * TXSimpleLFO::getCustomCurve2(){
    return customCurve2.getValueArray();
}

void TXSimpleLFO::setCustomCurve (float * valueArrayArg) {
    customCurve.setValueArray(valueArrayArg);
}

void TXSimpleLFO::setCustomCurve (ofParameterGroup & groupArg) {
    customCurve.parameters = groupArg;
}

void TXSimpleLFO::setCustomCurve2 (float * valueArrayArg) {
    customCurve2.setValueArray(valueArrayArg);
}

void TXSimpleLFO::setCustomCurve2 (ofParameterGroup & groupArg) {
    customCurve2.parameters = groupArg;
}

//////////////////////////////////////////////////////////////

void TXSimpleLFO::updateRandomiser(bool forceNewNumber, int randSeed) {
    int holdlfoType = lfoType;
    // for random types only
    if ((holdlfoType == TXLFOTYPE_RANDOM)
        || (holdlfoType == TXLFOTYPE_RANDOMQUANTISED)
        || (holdlfoType == TXLFOTYPE_RANDOMSMOOTHED)
        || (holdlfoType == TXLFOTYPE_DOUBLERANDOM)
        || (holdlfoType == TXLFOTYPE_DOUBLERANDOMQUANTISED)
        || (holdlfoType == TXLFOTYPE_DOUBLERANDOMSMOOTHED)
        )
    {
        // if forced or phase falls, generate new random no.
        if (forceNewNumber || (phase < oldPhase)) {
            if (randSeed != -1) {
                ofSeedRandom(randSeed);
            }else {
                ofSeedRandom();
            };
            oldRandPhase = randPhase;
            randPhase = ofRandom(1.0);
            phase = 0;
            if ((holdlfoType == TXLFOTYPE_DOUBLERANDOM)
                || (holdlfoType == TXLFOTYPE_DOUBLERANDOMQUANTISED)
                || (holdlfoType == TXLFOTYPE_DOUBLERANDOMSMOOTHED)
                ){
                doubleRandMultiply = pow(2, ofRandom(-2.0, 2.0));
            } else {
                doubleRandMultiply = 1.0;
            };
        };
        oldPhase = phase;
    };
}

