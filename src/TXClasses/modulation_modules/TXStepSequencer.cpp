/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXStepSequencer.h"
#include "TXFunctions.h"
#include "TXSystem.h"

// properties

// constructor
TXStepSequencer::TXStepSequencer (float bpmArg, float stepTimeBeatsArg, float stepTimeDivisorArg, bool useMasterBpmArg, int numValidStepsArg, bool useSmoothingArg, int smoothTypeArg, bool frozenArg, float triggerThresholdArg, int envTypeArg, bool randomiseStepOrderArg, bool playLoopedArg, float releaseTimeArg){
    setup (bpmArg, stepTimeBeatsArg, stepTimeDivisorArg, useMasterBpmArg, numValidStepsArg, useSmoothingArg, smoothTypeArg, frozenArg, triggerThresholdArg,  envTypeArg, randomiseStepOrderArg, playLoopedArg, releaseTimeArg);
    
};

// destructor
TXStepSequencer::~TXStepSequencer() {
    // remove listeners for relevent parameters:
    ofRemoveListener(numValidSteps->parameters.parameterChangedE(),this,&TXStepSequencer::numValidStepsChanged);
    ofRemoveListener(randomiseStepOrder->parameters.parameterChangedE(),this,&TXStepSequencer::randomiseStepOrderChanged);
    ofRemoveListener(playLooped->parameters.parameterChangedE(),this,&TXStepSequencer::playLoopedChanged);
    ofRemoveListener(resetClock->parameters.parameterChangedE(),this,&TXStepSequencer::resetClockChanged);
}

// methods
void TXStepSequencer::setup (float bpmArg, float stepTimeBeatsArg, float stepTimeDivisorArg, bool useMasterBpmArg, int numValidStepsArg, bool useSmoothingArg, int smoothTypeArg, bool frozenArg, float triggerThresholdArg, int envTypeArg, bool randomiseStepOrderArg, bool playLoopedArg, float releaseTimeArg) {
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
    
    holdModParamBoolArgs.name = "playLooped";
    holdModParamBoolArgs.fixedValue = playLoopedArg;
    playLooped = createModParameter(holdModParamBoolArgs);
    parameters.add(playLooped->parameters);
    
    holdModParamIntArgs.name = "envType";
    holdModParamIntArgs.fixedValue = envTypeArg;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = numEnvTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = numEnvTypes - 1;
    envType = createModParameter(holdModParamIntArgs);
    parameters.add(envType->parameters);
    
    holdModParamFloatArgs.name = "triggerThreshold";
    holdModParamFloatArgs.fixedValue = triggerThresholdArg;
    holdModParamFloatArgs.hardMin = 0.001;
    holdModParamFloatArgs.hardMax = 0.999;
    holdModParamFloatArgs.softMin = 0.001;
    holdModParamFloatArgs.softMax = 0.999;
    triggerThreshold = createModParameter(holdModParamFloatArgs);
    parameters.add(triggerThreshold->parameters);
    
    holdModParamFloatArgs.name = "triggerInput";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 1.0; // set full by default
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    triggerInput = createModParameter(holdModParamFloatArgs);
    parameters.add(triggerInput->parameters);
    
    holdModParamFloatArgs.name = "releaseTime";
    holdModParamFloatArgs.fixedValue = releaseTimeArg;
    holdModParamFloatArgs.fixedModMix = 1.0; // set full by default
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
    releaseTime = createModParameter(holdModParamFloatArgs);
    parameters.add(releaseTime->parameters);
    
    holdModParamBoolArgs.name = "randomiseStepOrder";
    holdModParamBoolArgs.fixedValue = randomiseStepOrderArg;
    randomiseStepOrder = createModParameter(holdModParamBoolArgs);
    parameters.add(randomiseStepOrder->parameters);
    
    parameters.add(baselineZero.set("baselineZero", true));

    holdModParamBoolArgs.name = "frozen";
    holdModParamBoolArgs.fixedValue = frozenArg;
    frozen = createModParameter(holdModParamBoolArgs);
    parameters.add(frozen->parameters);
    
    holdModParamBoolArgs.name = "resetClock";
    holdModParamBoolArgs.fixedValue = 0.0;
    resetClock = createModParameter(holdModParamBoolArgs);
    parameters.add(resetClock->parameters);
    
    holdModParamIntArgs.name = "numValidSteps";
    holdModParamIntArgs.fixedValue = numValidStepsArg;
    holdModParamIntArgs.hardMin = 2;
    holdModParamIntArgs.hardMax = maxSequencerSteps;
    holdModParamIntArgs.softMin = 2;
    holdModParamIntArgs.softMax = maxSequencerSteps;
    numValidSteps = createModParameter(holdModParamIntArgs);
    parameters.add(numValidSteps->parameters);
    
    holdModParamBoolArgs.name = "useMasterBpm";
    holdModParamBoolArgs.fixedValue = useMasterBpmArg;
    useMasterBpm = createModParameter(holdModParamBoolArgs);
    parameters.add(useMasterBpm->parameters);
    
    holdModParamFloatArgs.name = "bpm";
    holdModParamFloatArgs.fixedValue = bpmArg;
    holdModParamFloatArgs.hardMin = 0.001;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 0.1;
    holdModParamFloatArgs.softMax = 200.0;
    bpm = createModParameter(holdModParamFloatArgs);
    parameters.add(bpm->parameters);
    
    holdModParamFloatArgs.name = "stepTimeBeats";
    holdModParamFloatArgs.fixedValue = stepTimeBeatsArg;
    holdModParamFloatArgs.hardMin = 0.01;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 1.0;
    holdModParamFloatArgs.softMax = 64.0;
    stepTimeBeats = createModParameter(holdModParamFloatArgs);
    parameters.add(stepTimeBeats->parameters);
    
    holdModParamFloatArgs.name = "stepTimeDivisor";
    holdModParamFloatArgs.fixedValue = stepTimeDivisorArg;
    holdModParamFloatArgs.hardMin = 0.01;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 1.0;
    holdModParamFloatArgs.softMax = 64.0;
    stepTimeDivisor = createModParameter(holdModParamFloatArgs);
    parameters.add(stepTimeDivisor->parameters);
    
    holdModParamBoolArgs.name = "useSmoothing";
    holdModParamBoolArgs.fixedValue = useSmoothingArg;
    useSmoothing = createModParameter(holdModParamBoolArgs);
    parameters.add(useSmoothing->parameters);
    
    holdModParamIntArgs.name = "smoothType";
    holdModParamIntArgs.fixedValue = smoothTypeArg;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = numSmoothTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = numSmoothTypes - 1;
	smoothType = createModParameter(holdModParamIntArgs);
    parameters.add(smoothType->parameters);
    
    parameters.add(smoothingReturnToStep1.set("smoothingReturnToStep1", false));

    parameters.add(stepValues[0].set("step01Value", 0.0, 0.0, 1.0));
    parameters.add(stepValues[1].set("step02Value", 0.0, 0.0, 1.0));
    parameters.add(stepValues[2].set("step03Value", 0.0, 0.0, 1.0));
    parameters.add(stepValues[3].set("step04Value", 0.0, 0.0, 1.0));
    parameters.add(stepValues[4].set("step05Value", 0.0, 0.0, 1.0));
    parameters.add(stepValues[5].set("step06Value", 0.0, 0.0, 1.0));
    parameters.add(stepValues[6].set("step07Value", 0.0, 0.0, 1.0));
    parameters.add(stepValues[7].set("step08Value", 0.0, 0.0, 1.0));
    parameters.add(stepValues[8].set("step09Value", 0.0, 0.0, 1.0));
    parameters.add(stepValues[9].set("step10Value", 0.0, 0.0, 1.0));
    parameters.add(stepValues[10].set("step11Value", 0.0, 0.0, 1.0));
    parameters.add(stepValues[11].set("step12Value", 0.0, 0.0, 1.0));
    parameters.add(stepValues[12].set("step13Value", 0.0, 0.0, 1.0));
    parameters.add(stepValues[13].set("step14Value", 0.0, 0.0, 1.0));
    parameters.add(stepValues[14].set("step15Value", 0.0, 0.0, 1.0));
    parameters.add(stepValues[15].set("step16Value", 0.0, 0.0, 1.0));
    
    parameters.add(stepTimeProportions[0].set("step01TimeProportion", 1.0, 0.0, 1.0));
    parameters.add(stepTimeProportions[1].set("step02TimeProportion", 1.0, 0.0, 1.0));
    parameters.add(stepTimeProportions[2].set("step03TimeProportion", 1.0, 0.0, 1.0));
    parameters.add(stepTimeProportions[3].set("step04TimeProportion", 1.0, 0.0, 1.0));
    parameters.add(stepTimeProportions[4].set("step05TimeProportion", 1.0, 0.0, 1.0));
    parameters.add(stepTimeProportions[5].set("step06TimeProportion", 1.0, 0.0, 1.0));
    parameters.add(stepTimeProportions[6].set("step07TimeProportion", 1.0, 0.0, 1.0));
    parameters.add(stepTimeProportions[7].set("step08TimeProportion", 1.0, 0.0, 1.0));
    parameters.add(stepTimeProportions[8].set("step09TimeProportion", 1.0, 0.0, 1.0));
    parameters.add(stepTimeProportions[9].set("step10TimeProportion", 1.0, 0.0, 1.0));
    parameters.add(stepTimeProportions[10].set("step11TimeProportion", 1.0, 0.0, 1.0));
    parameters.add(stepTimeProportions[11].set("step12TimeProportion", 1.0, 0.0, 1.0));
    parameters.add(stepTimeProportions[12].set("step13TimeProportion", 1.0, 0.0, 1.0));
    parameters.add(stepTimeProportions[13].set("step14TimeProportion", 1.0, 0.0, 1.0));
    parameters.add(stepTimeProportions[14].set("step15TimeProportion", 1.0, 0.0, 1.0));
    parameters.add(stepTimeProportions[15].set("step16TimeProportion", 1.0, 0.0, 1.0));
    
    parameters.add(stepSmoothProportions[0].set("step01SmoothProportion", 1.0, 0.0, 1.0));
    parameters.add(stepSmoothProportions[1].set("step02SmoothProportion", 1.0, 0.0, 1.0));
    parameters.add(stepSmoothProportions[2].set("step03SmoothProportion", 1.0, 0.0, 1.0));
    parameters.add(stepSmoothProportions[3].set("step04SmoothProportion", 1.0, 0.0, 1.0));
    parameters.add(stepSmoothProportions[4].set("step05SmoothProportion", 1.0, 0.0, 1.0));
    parameters.add(stepSmoothProportions[5].set("step06SmoothProportion", 1.0, 0.0, 1.0));
    parameters.add(stepSmoothProportions[6].set("step07SmoothProportion", 1.0, 0.0, 1.0));
    parameters.add(stepSmoothProportions[7].set("step08SmoothProportion", 1.0, 0.0, 1.0));
    parameters.add(stepSmoothProportions[8].set("step09SmoothProportion", 1.0, 0.0, 1.0));
    parameters.add(stepSmoothProportions[9].set("step10SmoothProportion", 1.0, 0.0, 1.0));
    parameters.add(stepSmoothProportions[10].set("step11SmoothProportion", 1.0, 0.0, 1.0));
    parameters.add(stepSmoothProportions[11].set("step12SmoothProportion", 1.0, 0.0, 1.0));
    parameters.add(stepSmoothProportions[12].set("step13SmoothProportion", 1.0, 0.0, 1.0));
    parameters.add(stepSmoothProportions[13].set("step14SmoothProportion", 1.0, 0.0, 1.0));
    parameters.add(stepSmoothProportions[14].set("step15SmoothProportion", 1.0, 0.0, 1.0));
    parameters.add(stepSmoothProportions[15].set("step16SmoothProportion", 1.0, 0.0, 1.0));
    
    // add listeners to ofParameters
    stepTimeProportions[0].addListener(this, &TXStepSequencer::stepTimeChanged);
    stepTimeProportions[1].addListener(this, &TXStepSequencer::stepTimeChanged);
    stepTimeProportions[2].addListener(this, &TXStepSequencer::stepTimeChanged);
    stepTimeProportions[3].addListener(this, &TXStepSequencer::stepTimeChanged);
    stepTimeProportions[4].addListener(this, &TXStepSequencer::stepTimeChanged);
    stepTimeProportions[5].addListener(this, &TXStepSequencer::stepTimeChanged);
    stepTimeProportions[6].addListener(this, &TXStepSequencer::stepTimeChanged);
    stepTimeProportions[7].addListener(this, &TXStepSequencer::stepTimeChanged);
    stepTimeProportions[8].addListener(this, &TXStepSequencer::stepTimeChanged);
    stepTimeProportions[9].addListener(this, &TXStepSequencer::stepTimeChanged);
    stepTimeProportions[10].addListener(this, &TXStepSequencer::stepTimeChanged);
    stepTimeProportions[11].addListener(this, &TXStepSequencer::stepTimeChanged);
    stepTimeProportions[12].addListener(this, &TXStepSequencer::stepTimeChanged);
    stepTimeProportions[13].addListener(this, &TXStepSequencer::stepTimeChanged);
    stepTimeProportions[14].addListener(this, &TXStepSequencer::stepTimeChanged);
    stepTimeProportions[15].addListener(this, &TXStepSequencer::stepTimeChanged);

    // add listeners to TXModParameters
    ofAddListener(numValidSteps->parameters.parameterChangedE(),this,&TXStepSequencer::numValidStepsChanged);
    ofAddListener(randomiseStepOrder->parameters.parameterChangedE(),this,&TXStepSequencer::randomiseStepOrderChanged);
    ofAddListener(playLooped->parameters.parameterChangedE(),this,&TXStepSequencer::playLoopedChanged);
    ofAddListener(resetClock->parameters.parameterChangedE(),this,&TXStepSequencer::resetClockChanged);
    
    // create mod source output
    outValue = createModSource("out", 0);
    
    requestResetClock = false;
    resetTime();
    resetAllSteps();
    updateSumTimes();
    updateRandomSteps();
    setExtTrigger(false);
    
    triggerInputPrevious = 0.0;
    envRunning = false;
    goToFirstStep = false;
    smoothedOutVal.setSmoothTime(0);
    smoothedOutVal.setSmoothType(TXSMOOTHTYPE_EXPONENTIAL);
};


void TXStepSequencer::resetTime() {
    //currentTime = 0.0;
    currentStepIndex = numValidSteps->getInt() - 1;
    previousStepIndex = currentStepIndex;
    phase = 0.0;
    oldSmoothTarget = 0.0;
    stepChanged = false;
    envRunning = false;
    updateRandomSteps();
    calculateOutput();
    smoothedOutVal.resetTime();
}

void TXStepSequencer::resetAllSteps(float valueArg, float timeProportionAArg, float smoothProportionArg) {
    for (int i = 0; i < maxSequencerSteps; i++) {
        stepValues[i] = valueArg;
        stepTimeProportions[i] = timeProportionAArg;
        stepSmoothProportions[i] = smoothProportionArg;
    };
    updateSumTimes();
    updateRandomSteps();
    calculateOutput();
}

void TXStepSequencer::advanceBy(float timeDeltaArg) {
    float holdSpeed, holdSumPrevStep, holdTotalBeats, holdPhase;
    float holdBeats, oldPhase, holdStepTimeBeats, holdStepTimeDivisor, holdStepSmoothProportion;
    int holdNumValidSteps, holdIndex;
    bool holdRandomiseStepOrder = randomiseStepOrder->getBool();
    bool holdPlayLooped = playLooped->getBool();

    holdStepTimeBeats = stepTimeBeats->getFloat() / stepTimeDivisor->getFloat();
    holdNumValidSteps = numValidSteps->getInt();
    holdTotalBeats = sumTimes[holdNumValidSteps-1] * holdStepTimeBeats;
    
    if (frozen->getBool()) {
        return;
    };
    if (requestResetClock) {
        resetTime();
        requestResetClock = false;
    };
    
    // advance time
    //currentTime += timeDeltaArg;
    if (useMasterBpm->getBool()) {
        holdSpeed =  masterBpm /  60;
    } else {
        holdSpeed = bpm->getFloat() / 60 ;
    };
    
    oldPhase = phase;
    holdPhase = timeDeltaArg * holdSpeed / holdTotalBeats;
    phase = phase + holdPhase;
    if (holdPlayLooped) {
        phase = fmod(phase, 1.0f);
    } else {
        checkTriggerInputs();
    };

    if (phase < oldPhase) {
        updateRandomSteps();
    };
    
    // jump to first step
    if (goToFirstStep || (playLoopedHasChanged && holdPlayLooped)) {
        phase = 0.0;
        stepPhase = 0.0;
        previousStepIndex = numValidSteps->getInt() - 1;
        currentStepIndex = 0;
        stepChanged = false;
        if (holdRandomiseStepOrder) {
            holdIndex = randomIndices[currentStepIndex];
        } else {
            holdIndex = currentStepIndex;
        };
        oldSmoothTarget = stepValues[holdIndex];
    };

    // kill if running as env and too old
    if (!holdPlayLooped && (phase > 1.0)) {
        envRunning = false;
        phase = 0.0;
    } else {
        holdBeats = phase * holdTotalBeats;
        if (!goToFirstStep) {
            updateCurrentStepIndex(holdBeats, holdStepTimeBeats, holdRandomiseStepOrder);
        };
        if (currentStepIndex == 0) {
            holdSumPrevStep = 0;
        } else {
            if (holdRandomiseStepOrder) {
                holdSumPrevStep = randomSumTimes[previousStepIndex] * holdStepTimeBeats;
            } else {
                holdSumPrevStep = sumTimes[previousStepIndex] * holdStepTimeBeats;
            };
        };
        holdStepSmoothProportion = stepSmoothProportions[currentStepIndex];
        if (holdStepSmoothProportion == 0.0) {
            stepPhase = 1;
        } else {
            stepPhase = fminf(1.0, (holdBeats - holdSumPrevStep) / (holdStepSmoothProportion * stepTimeProportions[currentStepIndex] * holdStepTimeBeats));
            
        };
    };
    // check if release smoothing needed
    if (envRunning || holdPlayLooped) {
        smoothedOutVal.setSmoothTime(0);
    } else {
        smoothedOutVal.setSmoothTime(releaseTime->getFloat());
    };
    smoothedOutVal.advanceBy(timeDeltaArg);
    calculateOutput();

    // reset
    playLoopedHasChanged = false;
    goToFirstStep = false;
}
void  TXStepSequencer::updateCurrentStepIndex(float beatsArg, float stepTimeBeatsArg,  bool randomiseStepOrderArg) {
    int holdIndex = 0;
    
    if (randomiseStepOrderArg) {
        while (beatsArg > (randomSumTimes[holdIndex] * stepTimeBeatsArg)) {
            holdIndex++;
        };
    } else {
        while (beatsArg > (sumTimes[holdIndex]) * stepTimeBeatsArg) {
            holdIndex++;
        };
    };
    if (holdIndex != currentStepIndex) {
        previousStepIndex = currentStepIndex;
        currentStepIndex = holdIndex;
        stepChanged = true;
    };
}

void TXStepSequencer::calculateOutput() {
    int holdCurrentIndex, nextIndex, holdNumValidSteps, holdEaseFunction;
    float holdCurrentVal, holdNextVal, holdSmoothVal;
    bool holdRandomiseStepOrder, holdUseSmoothing, holdPlayLooped;
    
    holdNumValidSteps = numValidSteps->getInt();
    holdRandomiseStepOrder = randomiseStepOrder->getBool();
    holdUseSmoothing = useSmoothing->getBool();
    holdPlayLooped = playLooped->getBool();
    
    // if triggered envelope, and not running, get baseline val
    if (!holdPlayLooped) {
        if (!envRunning) {
            if (baselineZero) {
                setOutputTarget(0.0);
                return;
            }else {
                if (holdUseSmoothing && smoothingReturnToStep1) {
                    if (holdRandomiseStepOrder) {
                        holdCurrentIndex = randomIndices[0];
                    } else {
                        holdCurrentIndex = 0;
                    };
                } else {
                    if (holdRandomiseStepOrder) {
                        holdCurrentIndex = randomIndices[holdNumValidSteps - 1];
                    } else {
                        holdCurrentIndex = holdNumValidSteps - 1;
                    };
                };
                holdCurrentVal = stepValues[holdCurrentIndex];    
                setOutputTarget(holdCurrentVal);
                return;
            };
        };
    };

    if (holdRandomiseStepOrder) {
        holdCurrentIndex = randomIndices[currentStepIndex];
    } else {
        holdCurrentIndex = currentStepIndex;
    };
    holdCurrentVal = stepValues[holdCurrentIndex];    

    if (holdUseSmoothing) {
        // check whether to hold step val or return to step 1
        if ((!holdPlayLooped) && (holdCurrentIndex == (holdNumValidSteps - 1))  && (!smoothingReturnToStep1)) {
            nextIndex = holdCurrentIndex;
            holdNextVal = holdCurrentVal;
        } else {
            if (holdRandomiseStepOrder) {
                if (holdCurrentIndex == (holdNumValidSteps - 1)) {
                    nextIndex = randomIndices[0];
                } else {
                    nextIndex = randomIndices[holdCurrentIndex + 1];
                };
            } else {
                if (holdCurrentIndex == (holdNumValidSteps - 1)) {
                    nextIndex = 0;
                } else {
                    nextIndex = holdCurrentIndex + 1;
                };
            };
            holdNextVal = stepValues[nextIndex];
        };
        if (stepChanged) {
            oldSmoothTarget = newSmoothTarget;
            stepChanged = false;
        };
        newSmoothTarget = holdNextVal;
        holdEaseFunction = smoothType->getInt() + smoothTypeOffset;
        holdSmoothVal = getInterp(oldSmoothTarget, newSmoothTarget, stepPhase, holdEaseFunction);
        setOutputTarget(holdSmoothVal);
    } else {
        setOutputTarget(holdCurrentVal);
    };
}

void TXStepSequencer::setOutputTarget(float val) {
    smoothedOutVal.setTargetValue(val);
    outValue->setValue(smoothedOutVal.outValue);
}

//////////////////////////////////////////////////////////////

void  TXStepSequencer::checkTriggerInputs(){
    float holdTriggerThreshold, holdTriggerInput;
    holdTriggerThreshold = triggerThreshold->getFloat();
    holdTriggerInput = triggerInput->getFloat();
    // if falling below threshold
    if ((triggerInputPrevious >= holdTriggerThreshold) && (holdTriggerInput < holdTriggerThreshold)) {
        if (envType->getInt() == TXSTEPSEQENVTYPE_GATED) {
            envRunning = false;
        };
    } else {
        // if rising above threshold
        if ((triggerInputPrevious < holdTriggerThreshold) && (holdTriggerInput >= holdTriggerThreshold)) {
            triggerEnvNow();
        };
    };
    triggerInputPrevious = holdTriggerInput;
    // check external trigger
    if (extTrigger) {
        triggerEnvNow();
        extTrigger = false;
    };
}

void  TXStepSequencer::triggerEnvNow() {
    bool holdPlayLooped = playLooped->getBool();
    // only trigger if not looped
    if (!holdPlayLooped) {
        if (envRunning == true)  {
            if (envType->getInt() == TXSTEPSEQENVTYPE_FIXEDALLOWRETRIG) {
                goToFirstStep = true;
            };
        } else {
            envRunning = true;
            goToFirstStep = true;
        };
    };
}

void  TXStepSequencer::stopEnvNow() {
    envRunning = false;
}

//////////////////////////////////////////////////////////////

float TXStepSequencer::getValue() {
    return outValue->getValue();
}

float TXStepSequencer::getInterp(float val1, float val2, float proportion, int easeFunction) {
    float floatVal;
    if ((proportion == 0) || (val1 == val2)) {
        floatVal =  val1;
    } else if (proportion == 1) {
        floatVal =  val2;
    } else {
        floatVal = ofxTweenLite::tween ( val1, val2, proportion, (ofEaseFunction) easeFunction);
    };
    return floatVal;
};

bool TXStepSequencer::getExtTrigger() {
    return extTrigger;
}

void  TXStepSequencer::setExtTrigger(float extTriggerArg) {
    extTrigger = extTriggerArg;
}

//////////////////////////////////////////////////////////////

void  TXStepSequencer::playLoopedChanged(ofAbstractParameter & parameterArg) {
    playLoopedHasChanged = true;
}

void  TXStepSequencer::stepTimeChanged(float & floatArg) {
    updateSumTimes();
    updateRandomSteps();
}

void  TXStepSequencer::numValidStepsChanged(ofAbstractParameter & parameterArg) {
    resetTime();
}

void  TXStepSequencer::randomiseStepOrderChanged(ofAbstractParameter & parameterArg) {
    updateRandomSteps();
}

void  TXStepSequencer::resetClockChanged(ofAbstractParameter & dummyParameterArg ) {
    if (resetClock->getBool()){
        requestResetClock = true;
    };
}

//////////////////////////////////////////////////////////////

float TXStepSequencer::getSumTime(int stepNoArg) {
    return sumTimes[stepNoArg];
}

void  TXStepSequencer::updateSumTimes() {
    float sum = 0, timeBeats;
    for (int i = 0; i < maxSequencerSteps; i++) {
        timeBeats = stepTimeProportions[i];
        sum = sum + timeBeats;
        sumTimes[i] = sum;
    };
}  

void  TXStepSequencer::updateRandomSteps() {
    int   holdRandomInt, holdNumValidSteps;
    float sum = 0, timeBeats;
    holdNumValidSteps = numValidSteps->getInt();
    if (randomiseStepOrder->getBool()) {
        for (int i = 0; i < holdNumValidSteps; i++) {
            holdRandomInt = (ofRandom(holdNumValidSteps-1) + 0.5);
            randomIndices[i] = holdRandomInt;
            timeBeats = stepTimeProportions[holdRandomInt];
            sum = sum + timeBeats;
            randomSumTimes[i] = sum;
        };
    };
}  

