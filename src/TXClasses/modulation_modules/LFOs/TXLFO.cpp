/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXLFO.h"
#include "TXSystem.h"
#include "TXFunctions.h"
#include "ofxTweenLite.h"

// properties

// constructor
TXLFO::TXLFO(){
    TXLFOArgs holdArgs;
    setup(holdArgs);
};

// destructor
TXLFO::~TXLFO() {
    // remove listeners to relevent parameters:
    ofRemoveListener(resetClock->parameters.parameterChangedE(),this,&TXLFO::resetClockChanged);
}
TXLFO::TXLFO(TXLFOArgs holdArgs){
    setup(holdArgs);
};

// methods
void TXLFO::setup (TXLFOArgs holdLFOArgs) {
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
    
    holdModParamIntArgs.name = "lfoType";
    holdModParamIntArgs.fixedValue = holdLFOArgs.lfoType;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalLFOTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalLFOTypes - 1;
	lfoType = createModParameter(holdModParamIntArgs);
    parameters.add(lfoType->parameters);

    holdModParamIntArgs.name = "randomSmoothType";
    holdModParamIntArgs.fixedValue = holdLFOArgs.randomSmoothType;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = numSmoothTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = numSmoothTypes - 1;
	randomSmoothType = createModParameter(holdModParamIntArgs);
    parameters.add(randomSmoothType->parameters);
    
    holdModParamFloatArgs.name = "bpm";
    holdModParamFloatArgs.fixedValue = holdLFOArgs.bpm;
    holdModParamFloatArgs.hardMin = 0.001;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 0.1;
    holdModParamFloatArgs.softMax = 200.0;
	bpm = createModParameter(holdModParamFloatArgs);
    parameters.add(bpm->parameters);
    
    holdModParamBoolArgs.name = "useMasterBpm";
    holdModParamBoolArgs.fixedValue = holdLFOArgs.useMasterBpm;
	useMasterBpm = createModParameter(holdModParamBoolArgs);
    parameters.add(useMasterBpm->parameters);
    
    holdModParamFloatArgs.name = "cycleTimeBeats";
    holdModParamFloatArgs.fixedValue = holdLFOArgs.cycleTimeBeats;
    holdModParamFloatArgs.hardMin = 0.01;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 1.0;
    holdModParamFloatArgs.softMax = 64.0;
	cycleTimeBeats = createModParameter(holdModParamFloatArgs);
    parameters.add(cycleTimeBeats->parameters);
    
    holdModParamFloatArgs.name = "cycleTimeDivisor";
    holdModParamFloatArgs.fixedValue = holdLFOArgs.cycleTimeDivisor;
    holdModParamFloatArgs.hardMin = 0.01;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 1.0;
    holdModParamFloatArgs.softMax = 64.0;
	cycleTimeDivisor = createModParameter(holdModParamFloatArgs);
    parameters.add(cycleTimeDivisor->parameters);
    
    holdModParamFloatArgs.name = "phaseOffset";
    holdModParamFloatArgs.fixedValue = holdLFOArgs.phaseOffset;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	phaseOffset = createModParameter(holdModParamFloatArgs);
    parameters.add(phaseOffset->parameters);
    
    holdModParamFloatArgs.name = "pulseWidth";
    holdModParamFloatArgs.fixedValue = holdLFOArgs.pulseWidth;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	pulseWidth = createModParameter(holdModParamFloatArgs);
    parameters.add(pulseWidth->parameters);

    holdModParamBoolArgs.name = "frozen";
    holdModParamBoolArgs.fixedValue = holdLFOArgs.frozen;
    frozen = createModParameter(holdModParamBoolArgs);
    parameters.add(frozen->parameters);
    
    holdModParamBoolArgs.name = "resetClock";
    holdModParamBoolArgs.fixedValue = 0.0;
    resetClock = createModParameter(holdModParamBoolArgs);
    parameters.add(resetClock->parameters);
    
    customCurve.setValueArrayToRamp(0, 1);
    customCurve.setName("customCurve");
    parameters.add(customCurve.parameters);
    
    customCurve2.setValueArrayToRamp(0, 1);
    customCurve2.setName("customCurve2");
    parameters.add(customCurve2.parameters);
    
    holdModParamFloatArgs.name = "customCurveMorph";
    holdModParamFloatArgs.fixedValue = holdLFOArgs.customCurveMorph;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    customCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(customCurveMorph->parameters);
    
    // create mod source output
    outValue = createModSource("out", 0);

    // add listener to relevent parameters:
    ofAddListener(resetClock->parameters.parameterChangedE(),this,&TXLFO::resetClockChanged);

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

//void TXLFO::setTime(float timeArg){
//	float holdPhase;
//    float holdSpeed;
//    if (frozen->getBool()) {
//        return;
//    };
//    if (useMasterBpm->getBool()) {
//        holdSpeed = masterBpm / 60;
//    } else {
//        holdSpeed = bpm->getFloat() / 60;
//    };
//    currentTime = timeArg;
//    holdPhase = timeArg * doubleRandMultiply * holdSpeed  * cycleTimeDivisor->getFloat() / cycleTimeBeats->getFloat();
//    phase = fmod(phaseOffset->getFloat() + holdPhase, 1.0f);
//    updateRandomiser();
//    calculateOutput();
//}

void TXLFO::resetTime(int randSeed) {
    currentTime = 0.0;
    phase = phaseOffset->getFloat();
    oldPhaseOffset = phase;
    updateRandomiser(true, randSeed); // force new random no
    calculateOutput();
}

void TXLFO::resetTime() {    
    resetTime(-1);
}

void TXLFO::advanceBy(float timeDeltaArg) {
	float holdPhase, holdSpeed, holdPhaseOffset, changePhaseOffset;
    int holdlfoType;
    if (frozen->getBool()) {
        return;
    };
    if (requestResetClock) {
        resetTime();
        requestResetClock = false;
    };
    if (useMasterBpm->getBool()) {
        holdSpeed = masterBpm / 60;
    } else {
        holdSpeed = bpm->getFloat() / 60;
    };
    currentTime += timeDeltaArg;
    holdPhaseOffset = phaseOffset->getFloat();
    holdPhase = (phase + (timeDeltaArg * doubleRandMultiply * holdSpeed  * cycleTimeDivisor->getFloat() / cycleTimeBeats->getFloat()));
    changePhaseOffset = holdPhaseOffset - oldPhaseOffset;
    // use abs val if random LFO
    if ((holdlfoType == TXLFOTYPE_RANDOM)
        || (holdlfoType == TXLFOTYPE_RANDOMQUANTISED)
        || (holdlfoType == TXLFOTYPE_RANDOMSMOOTHED)
        || (holdlfoType == TXLFOTYPE_DOUBLERANDOM)
        || (holdlfoType == TXLFOTYPE_DOUBLERANDOMQUANTISED)
        || (holdlfoType == TXLFOTYPE_DOUBLERANDOMSMOOTHED)
        )
    {
        changePhaseOffset = fabs(changePhaseOffset);
    };
    phase = fmod(1.0 + changePhaseOffset + holdPhase, 1.0f);
    updateRandomiser();
    calculateOutput();
    oldPhaseOffset = holdPhaseOffset;
}

float TXLFO::getValue() {
    return outValue->getValue();
}

void TXLFO::calculateOutput() {
    float twoPIPhase = TWO_PI * phase;
    float holdVal, holdMorph;
    switch (lfoType->getInt()) {
        case TXLFOTYPE_SINE:
            outValue->setValue(0.5 + (0.5 * sin(twoPIPhase)));
            break;
        case TXLFOTYPE_COSINE:
            outValue->setValue(0.5 + (0.5 * cos(twoPIPhase)));
            break;
        case TXLFOTYPE_SQUARE:
            outValue->setValue((float) (phase < 0.5));
            break;
        case TXLFOTYPE_PULSE:
            outValue->setValue((float) (phase < min(max(pulseWidth->getFloat(), 0.001f),0.999f)));
            break;
        case TXLFOTYPE_TRIANGLE:
            outValue->setValue(abs(1.0f - (2.0f * fmod(phase + 0.75f, 1.0f))));
            break;
        case TXLFOTYPE_SAW:
            outValue->setValue(phase);
            break;
        case TXLFOTYPE_SAWREVERSE:
            outValue->setValue((1 - phase));
            break;
        case TXLFOTYPE_RANDOM:
            outValue->setValue(randPhase);
            break;
        case TXLFOTYPE_RANDOMQUANTISED:
            outValue->setValue((int)(randPhase + 0.5));
            break;
        case TXLFOTYPE_RANDOMSMOOTHED:
            outValue->setValue(ofxTweenLite::tween ( oldRandPhase, randPhase, phase, (ofEaseFunction) (randomSmoothType->getInt() + smoothTypeOffset)));
            break;
        case TXLFOTYPE_DOUBLERANDOM:
            outValue->setValue(randPhase);
            break;
        case TXLFOTYPE_DOUBLERANDOMQUANTISED:
            outValue->setValue((int)(randPhase + 0.5));
            break;
        case TXLFOTYPE_DOUBLERANDOMSMOOTHED:
            outValue->setValue(ofxTweenLite::tween ( oldRandPhase, randPhase, phase, (ofEaseFunction) (randomSmoothType->getInt() + smoothTypeOffset)));
            break;
        case TXLFOTYPE_TREFOILKNOTX:
            // trefoilX = sin t + 2 sin 2t;
            holdVal = 0.3333333333 * (sin(twoPIPhase) + (2 * sin(2 * twoPIPhase)));
            outValue->setValue(0.5 + (0.5 * holdVal));
            break;
        case TXLFOTYPE_TREFOILKNOTY:
            // trefoilY = cos t - 2 cos 2t;
            holdVal = 0.3333333333 * (cos(twoPIPhase) - (2 * cos(2 * twoPIPhase)));
            outValue->setValue(0.5 + (0.5 * holdVal));
            break;
        case TXLFOTYPE_TREFOILKNOTZ:
            // trefoilZ = - sin 3t;
            holdVal = 0.3333333333 * -sin(3 * twoPIPhase);
            // holdVal = -sin(3 * twoPIPhase);
            outValue->setValue(0.5 + (0.5 * holdVal));
            break;
        case TXLFOTYPE_CUSTOMCURVE:
            holdMorph =customCurveMorph->getFloat();
            outValue->setValue(TXFunctions::getInterpCurves(customCurve, customCurve2, phase, holdMorph));
            break;
        case TXLFOTYPE_CUSTOMCURVE_MIRRORED:
            holdMorph = customCurveMorph->getFloat();
            if (phase<0.5) {
                holdVal = 2 * phase;
            } else {
                holdVal = 1 - (2 * (phase - 0.5));
            };
            outValue->setValue(TXFunctions::getInterpCurves(customCurve, customCurve2, holdVal, holdMorph));
            break;
        default:
            outValue->setValue(phase);
            break;
    }
}

//ofPtr<TXModParameter>   TXLFO::getLfoType(){
//    return lfoType;
//}

void  TXLFO::setLfoTypeFixed(int lfoTypeFixedArg){
    lfoType->setFixedValue(lfoTypeFixedArg);
    updateRandomiser();
}

//ofPtr<TXModParameter>   TXLFO::getRandomSmoothType(){
//    return randomSmoothType;
//}

void  TXLFO::setRandomSmoothTypeFixed(int randomSmoothTypeFixedArg){
    randomSmoothType->setFixedValue(randomSmoothTypeFixedArg);
}

//ofPtr<TXModParameter> TXLFO::getBpm() {
//    return bpm;
//} 

void  TXLFO::setBpmFixed(float bpmFixedArg){
    bpm->setFixedValue(bpmFixedArg);
    updateRandomiser();
}

//ofPtr<TXModParameter> TXLFO::getCycleTimeBeats(){
//    return cycleTimeBeats;
//}

void  TXLFO::setCycleTimeBeatsFixed(float cycleTimeBeatsFixedArg){
    cycleTimeBeats->setFixedValue((float)fmax(cycleTimeBeatsFixedArg, 0.001f));
}

//ofPtr<TXModParameter> TXLFO::getCycleTimeDivisor(){
//    return cycleTimeDivisor;
//}

void  TXLFO::setCycleTimeDivisorFixed(float cycleTimeDivisorFixedArg){
    cycleTimeDivisor->setFixedValue((float)fmax(cycleTimeDivisorFixedArg, 0.001f));
}

//ofPtr<TXModParameter> TXLFO::getPhaseOffset(){
//    return phaseOffset;
//}

void  TXLFO::setPhaseOffsetFixed(float phaseOffsetFixedArg){
    phaseOffset->setFixedValue(phaseOffsetFixedArg);
}

//ofPtr<TXModParameter> TXLFO::getPulseWidth(){
//    return pulseWidth;
//}

void  TXLFO::setPulseWidthFixed(float pulseWidthFixedArg){
    pulseWidth->setFixedValue(pulseWidthFixedArg);
}

//ofPtr<TXModParameter>  TXLFO::getUseMasterBpm(){
//    return useMasterBpm;
//}

void  TXLFO::setUseMasterBpmFixed(bool useMasterBpmFixedArg){
    useMasterBpm->setFixedValue(useMasterBpmFixedArg);
    updateRandomiser();
}

//ofPtr<TXModParameter>  TXLFO::getFrozen(){
//    return frozen;
//}

void  TXLFO::setFrozenFixed(bool frozenFixedArg){
    frozen->setFixedValue(frozenFixedArg);
}

float * TXLFO::getCustomCurve(){
    return customCurve.getValueArray();
}

float * TXLFO::getCustomCurve2(){
    return customCurve2.getValueArray();
}

void TXLFO::setCustomCurve (float * valueArrayArg) {
    customCurve.setValueArray(valueArrayArg);
}

void TXLFO::setCustomCurve (ofParameterGroup & groupArg) {
    customCurve.parameters = groupArg;
}

void TXLFO::setCustomCurve2 (float * valueArrayArg) {
    customCurve2.setValueArray(valueArrayArg);
}

void TXLFO::setCustomCurve2 (ofParameterGroup & groupArg) {
    customCurve2.parameters = groupArg;
}

void TXLFO::maximiseParameterRanges() {
    lfoType->maximiseRangeSoftMinMax();
    randomSmoothType->maximiseRangeSoftMinMax();
    bpm->maximiseRangeSoftMinMax();
    cycleTimeBeats->maximiseRangeSoftMinMax();
    cycleTimeDivisor->maximiseRangeSoftMinMax();
    phaseOffset->maximiseRangeSoftMinMax();
    pulseWidth->maximiseRangeSoftMinMax();
}

void  TXLFO::resetClockChanged(ofAbstractParameter & dummyParameterArg ) {
    if (resetClock->getBool()){
        requestResetClock = true;
    };
}

//////////////////////////////////////////////////////////////

void TXLFO::updateRandomiser(bool forceNewNumber, int randSeed) {
    int holdlfoType = lfoType->getInt();
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
            // } else {
                // ofSeedRandom();
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

