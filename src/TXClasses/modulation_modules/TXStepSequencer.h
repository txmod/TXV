/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"
#include "TXModuleBase.h"
#include "TXSmoothVar.h"
#include "ofxTweenLite.h"

enum TXSTEPSEQSMOOTHTYPE {
    // for ref: in ofxTweenLite: enum ofEaseFunction
    // NB smoothTypeOffset = 9 because 1st 9 aren't used here:
    //    TXSTEPSEQSMOOTHTYPE_BACK_IN,
    //    TXSTEPSEQSMOOTHTYPE_BACK_OUT,
    //    TXSTEPSEQSMOOTHTYPE_BACK_INOUT,
    //    TXSTEPSEQSMOOTHTYPE_BOUNCE_IN,
    //    TXSTEPSEQSMOOTHTYPE_BOUNCE_OUT,
    //    TXSTEPSEQSMOOTHTYPE_BOUNCE_INOUT,
    //    TXSTEPSEQSMOOTHTYPE_CIRC_IN,
    //    TXSTEPSEQSMOOTHTYPE_CIRC_OUT,
    //    TXSTEPSEQSMOOTHTYPE_CIRC_INOUT,
    TXSTEPSEQSMOOTHTYPE_CUBIC_IN,
    TXSTEPSEQSMOOTHTYPE_CUBIC_OUT,
    TXSTEPSEQSMOOTHTYPE_CUBIC_INOUT,
    TXSTEPSEQSMOOTHTYPE_ELASTIC_IN,
    TXSTEPSEQSMOOTHTYPE_ELASTIC_OUT,
    TXSTEPSEQSMOOTHTYPE_ELASTIC_INOUT,
    TXSTEPSEQSMOOTHTYPE_EXPO_IN,
    TXSTEPSEQSMOOTHTYPE_EXPO_OUT,
    TXSTEPSEQSMOOTHTYPE_EXPO_INOUT,
    TXSTEPSEQSMOOTHTYPE_LINEAR_IN,
    TXSTEPSEQSMOOTHTYPE_LINEAR_OUT,
    TXSTEPSEQSMOOTHTYPE_LINEAR_INOUT,
    TXSTEPSEQSMOOTHTYPE_QUAD_IN,
    TXSTEPSEQSMOOTHTYPE_QUAD_OUT,
    TXSTEPSEQSMOOTHTYPE_QUAD_INOUT,
    TXSTEPSEQSMOOTHTYPE_QUART_IN,
    TXSTEPSEQSMOOTHTYPE_QUART_OUT,
    TXSTEPSEQSMOOTHTYPE_QUART_INOUT,
    TXSTEPSEQSMOOTHTYPE_QUINT_IN,
    TXSTEPSEQSMOOTHTYPE_QUINT_OUT,
    TXSTEPSEQSMOOTHTYPE_QUINT_INOUT,
    TXSTEPSEQSMOOTHTYPE_SINE_IN,
    TXSTEPSEQSMOOTHTYPE_SINE_OUT,
    TXSTEPSEQSMOOTHTYPE_SINE_INOUT
};

enum TXSTEPSEQENVTYPE {TXSTEPSEQENVTYPE_GATED, TXSTEPSEQENVTYPE_FIXEDALLOWRETRIG, TXSTEPSEQENVTYPE_FIXEDNORETRIG};
//Gated- envelope is gated by trigger input   
//Fixed Length, no retriggering - envelope always completes
//Fixed Length, allow retriggering - envelope always completes

class TXStepSequencer  : public TXModuleBase
{
public:
	// NOTE Output range is 0 to +1

    static const int maxSequencerSteps = 16;
    static const int numSmoothTypes = 24;
    static const int numEnvTypes = 3;
    static const int smoothTypeOffset = 9;  // because 1st 9 aren't used - see above

	// constructor
	TXStepSequencer (float bpmArg = 60.0, float stepTimeBeatsArg = 1.0, float stepTimeDivisorArg = 1.0, bool useMasterBpmArg = true, int numValidStepsArg = 16, bool useSmoothingArg = true, int smoothTypeArg = TXSTEPSEQSMOOTHTYPE_LINEAR_IN, bool frozenArg = false, float triggerThresholdArg = 0.5, int envTypeArg = TXSTEPSEQENVTYPE_FIXEDALLOWRETRIG, bool randomiseStepOrderArg = false, bool playLoopedArg = true, float releaseTimeArg = 0.0);
    
    // destructor
    ~TXStepSequencer ();

	// methods
	void setup (float bpmArg = 120.0, float stepTimeBeatsArg = 1.0, float stepTimeDivisorArg = 1.0, bool useMasterBpmArg = true, int numValidStepsArg = 16, bool useSmoothingArg = true, int smoothTypeArg = TXSTEPSEQSMOOTHTYPE_LINEAR_IN, bool frozenArg = false, float triggerThresholdArg = 0.5, int envTypeArg = TXSTEPSEQENVTYPE_FIXEDALLOWRETRIG, bool randomiseStepOrderArg = false, bool playLoopedArg = true, float releaseTimeArg = 0.0);
    void  resetTime();
    void  resetAllSteps(float valueArg = 0.0, float timeProportionAArg = 1.0, float smoothProportionArg = 1.0);
	void  advanceBy(float timeDeltaArg);
    void  updateCurrentStepIndex(float beatsArg, float stepTimeBeatsArg,  bool randomiseStepOrderArg);
    void  calculateOutput();
    void  setOutputTarget(float val);
    void  checkTriggerInputs();
    void  triggerEnvNow();
    void  stopEnvNow();
    
	float getValue();
    float getInterp(float val1, float val2, float proportion, int easeFunction = OF_EASE_LINEAR_IN);
    bool  getExtTrigger();
    void  setExtTrigger(float extTriggerArg);
	
    void  playLoopedChanged(ofAbstractParameter & parameterArg);
    void  stepTimeChanged(float & floatArg);
    void  numValidStepsChanged(ofAbstractParameter & parameterArg);
    void  randomiseStepOrderChanged(ofAbstractParameter & parameterArg);
    void  resetClockChanged(ofAbstractParameter & dummyParameterArg );

    float getSumTime(int stepNoArg);
    void  updateSumTimes();
    void  updateRandomSteps();

	// properties

public:
    ofPtr<TXModParamBool>  playLooped;
    ofPtr<TXModParamInt>   envType;
    ofPtr<TXModParamFloat> triggerThreshold;
    ofPtr<TXModParamFloat> triggerInput;
    ofPtr<TXModParamFloat> releaseTime;
    ofPtr<TXModParamBool>  randomiseStepOrder;
    ofParameter<bool>      baselineZero;
    ofPtr<TXModParamBool>  frozen;
    ofPtr<TXModParamBool>  resetClock;
    ofPtr<TXModParamInt>   numValidSteps;
    ofPtr<TXModParamBool>  useMasterBpm;
    ofPtr<TXModParamFloat> bpm;
    ofPtr<TXModParamFloat> stepTimeBeats;
    ofPtr<TXModParamFloat> stepTimeDivisor;
    ofPtr<TXModParamBool>  useSmoothing;
    ofParameter<bool>      smoothingReturnToStep1;
    ofPtr<TXModParamInt>   smoothType;

    ofParameter<float> stepValues[maxSequencerSteps];
    ofParameter<float> stepTimeProportions[maxSequencerSteps];
    ofParameter<float> stepSmoothProportions[maxSequencerSteps];

    ofPtr<TXModSource> outValue;

protected:
    float sumTimes[maxSequencerSteps];
    float randomSumTimes[maxSequencerSteps];
    int   randomIndices[maxSequencerSteps];

    int   currentStepIndex;
    int   previousStepIndex;
	float phase;
	float stepPhase;
    
    float oldSmoothTarget;
    float newSmoothTarget;
    bool  stepChanged;
    
    bool  playLoopedHasChanged;
    float triggerInputPrevious;
    bool  envRunning;
    bool  extTrigger;
    bool  goToFirstStep;
    bool  requestResetClock;

    TXSmoothVar smoothedOutVal;
};


