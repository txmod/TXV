/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"
#include "TXModuleBase.h"

// NOTE - change totalLFOTypes when adding new LFO types:

enum TXLFOTYPE {TXLFOTYPE_SINE,
    TXLFOTYPE_COSINE,
    TXLFOTYPE_SQUARE,
    TXLFOTYPE_PULSE,
    TXLFOTYPE_TRIANGLE,
    TXLFOTYPE_SAW,
    TXLFOTYPE_SAWREVERSE,
    TXLFOTYPE_RANDOM,
    TXLFOTYPE_RANDOMQUANTISED,
    TXLFOTYPE_RANDOMSMOOTHED,
    TXLFOTYPE_DOUBLERANDOM,
    TXLFOTYPE_DOUBLERANDOMQUANTISED,
    TXLFOTYPE_DOUBLERANDOMSMOOTHED,
    TXLFOTYPE_TREFOILKNOTX,
    TXLFOTYPE_TREFOILKNOTY,
    TXLFOTYPE_TREFOILKNOTZ,
    TXLFOTYPE_CUSTOMCURVE,
    TXLFOTYPE_CUSTOMCURVE_MIRRORED,
};

enum TXLFOSMOOTHTYPE {
    // for ref: in ofxTweenLite: enum ofEaseFunction
    // NB smoothTypeOffset = 9 because 1st 9 aren't used here:
    //    TXLFOSMOOTHTYPE_BACK_IN,
    //    TXLFOSMOOTHTYPE_BACK_OUT,
    //    TXLFOSMOOTHTYPE_BACK_INOUT,
    //    TXLFOSMOOTHTYPE_BOUNCE_IN,
    //    TXLFOSMOOTHTYPE_BOUNCE_OUT,
    //    TXLFOSMOOTHTYPE_BOUNCE_INOUT,
    //    TXLFOSMOOTHTYPE_CIRC_IN,
    //    TXLFOSMOOTHTYPE_CIRC_OUT,
    //    TXLFOSMOOTHTYPE_CIRC_INOUT,
    TXLFOSMOOTHTYPE_CUBIC_IN,
    TXLFOSMOOTHTYPE_CUBIC_OUT,
    TXLFOSMOOTHTYPE_CUBIC_INOUT,
    TXLFOSMOOTHTYPE_ELASTIC_IN,
    TXLFOSMOOTHTYPE_ELASTIC_OUT,
    TXLFOSMOOTHTYPE_ELASTIC_INOUT,
    TXLFOSMOOTHTYPE_EXPO_IN,
    TXLFOSMOOTHTYPE_EXPO_OUT,
    TXLFOSMOOTHTYPE_EXPO_INOUT,
    TXLFOSMOOTHTYPE_LINEAR_IN,
    TXLFOSMOOTHTYPE_LINEAR_OUT,
    TXLFOSMOOTHTYPE_LINEAR_INOUT,
    TXLFOSMOOTHTYPE_QUAD_IN,
    TXLFOSMOOTHTYPE_QUAD_OUT,
    TXLFOSMOOTHTYPE_QUAD_INOUT,
    TXLFOSMOOTHTYPE_QUART_IN,
    TXLFOSMOOTHTYPE_QUART_OUT,
    TXLFOSMOOTHTYPE_QUART_INOUT,
    TXLFOSMOOTHTYPE_QUINT_IN,
    TXLFOSMOOTHTYPE_QUINT_OUT,
    TXLFOSMOOTHTYPE_QUINT_INOUT,
    TXLFOSMOOTHTYPE_SINE_IN,
    TXLFOSMOOTHTYPE_SINE_OUT,
    TXLFOSMOOTHTYPE_SINE_INOUT
};

class TXLFOArgs
{
public:
    int lfoType = 0;
    int randomSmoothType = TXLFOSMOOTHTYPE_SINE_INOUT;
    float bpm = 120.0;
    float cycleTimeBeats = 1.0;
    float cycleTimeDivisor = 1.0;
    float phaseOffset = 0.0;
    float pulseWidth = 0.5;
    bool useMasterBpm = true;
    bool frozen = false;
    float customCurveMorph = 0.0;
};

class TXLFO  : public TXModuleBase
{
public:
	// NOTE
    // Output range is 0 to +1
    // Pulse Width is only relevent to TXLFOTYPE_PULSE
    
    // NOTE - change totalLFOTypes when adding new LFO types:
    static const int totalLFOTypes = 18;
    static const int numSmoothTypes = 24;
    static const int smoothTypeOffset = 9;

	// constructor
	TXLFO ();
	TXLFO (TXLFOArgs holdArgs);

    // destructor
    ~TXLFO ();
    
	// methods
	void setup (TXLFOArgs holdArgs);
	void advanceBy(float timeDeltaArg); 
    //void setTime(float timeArg = 0);
    void resetTime();
    void resetTime(int randSeed);
	void calculateOutput();
	float getValue();
//    ofPtr<TXModParameter>   getLfoType();
    void  setLfoTypeFixed(int lfoTypeFixedArg);
//    ofPtr<TXModParameter>   getRandomSmoothType();
    void  setRandomSmoothTypeFixed(int randomSmoothTypeFixedArg);
//	ofPtr<TXModParameter> getBpm();
    void  setBpmFixed(float bpmArg);
//    ofPtr<TXModParameter> getCycleTimeBeats();
    void  setCycleTimeBeatsFixed(float cycleTimeBeatsFixedArg);
//    ofPtr<TXModParameter> getCycleTimeDivisor();
    void  setCycleTimeDivisorFixed(float cycleTimeDivisorFixedArg);
//    ofPtr<TXModParameter> getPhaseOffset();
    void  setPhaseOffsetFixed(float phaseOffsetFixedArg);
//    ofPtr<TXModParameter> getPulseWidth();
    void  setPulseWidthFixed(float pulseWidthFixedArg);
//    ofPtr<TXModParameter>  getUseMasterBpm();
    void  setUseMasterBpmFixed(bool useMasterBpmFixedArg);
//    ofPtr<TXModParameter>  getFrozen(); 
    void  setFrozenFixed(bool frozenFixedArg);
    float * getCustomCurve();
    float * getCustomCurve2();
    void setCustomCurve (float * valueArrayArg);
    void setCustomCurve (ofParameterGroup & groupArg);
    void setCustomCurve2 (float * valueArrayArg);
    void setCustomCurve2 (ofParameterGroup & groupArg);
	void maximiseParameterRanges();
    void resetClockChanged(ofAbstractParameter & dummyParameterArg );
    
    ofPtr<TXModParamInt> lfoType;
    ofPtr<TXModParamInt> randomSmoothType;
    ofPtr<TXModParamFloat> bpm;
    ofPtr<TXModParamFloat> cycleTimeBeats;
    ofPtr<TXModParamFloat> cycleTimeDivisor;
    ofPtr<TXModParamFloat> phaseOffset;
    ofPtr<TXModParamFloat> pulseWidth;
    ofPtr<TXModParamBool> useMasterBpm;
    ofPtr<TXModParamBool> frozen;
    ofPtr<TXModParamBool> resetClock;
    
    TXParameterFloat256   customCurve;
    TXParameterFloat256   customCurve2;
    ofPtr<TXModParamFloat> customCurveMorph;

    ofPtr<TXModSource> outValue;

protected:
    void  updateRandomiser(bool forceNewNumber = false, int randSeed = -1);
    
    float currentTime;
    float randPhase;
    float oldRandPhase;
	float phase;
    float oldPhase;
    float oldPhaseOffset;
    float doubleRandMultiply;
    bool  requestResetClock;
};


// enum ofEaseFunction
//{
//    OF_EASE_BACK_IN         = 0,
//    OF_EASE_BACK_OUT        = 1,
//    OF_EASE_BACK_INOUT      = 2,
//    OF_EASE_BOUNCE_IN       = 3,
//    OF_EASE_BOUNCE_OUT      = 4,
//    OF_EASE_BOUNCE_INOUT    = 5,
//    OF_EASE_CIRC_IN         = 6,
//    OF_EASE_CIRC_OUT        = 7,
//    OF_EASE_CIRC_INOUT      = 8,
//    OF_EASE_CUBIC_IN        = 9,
//    OF_EASE_CUBIC_OUT       = 10,
//    OF_EASE_CUBIC_INOUT     = 11,
//    OF_EASE_ELASTIC_IN      = 12,
//    OF_EASE_ELASTIC_OUT     = 13,
//    OF_EASE_ELASTIC_INOUT   = 14,
//    OF_EASE_EXPO_IN         = 15,
//    OF_EASE_EXPO_OUT        = 16,
//    OF_EASE_EXPO_INOUT      = 17,
//    OF_EASE_LINEAR_IN       = 18,
//    OF_EASE_LINEAR_OUT      = 19,
//    OF_EASE_LINEAR_INOUT    = 20,
//    OF_EASE_QUAD_IN         = 21,
//    OF_EASE_QUAD_OUT        = 22,
//    OF_EASE_QUAD_INOUT      = 23,
//    OF_EASE_QUART_IN        = 24,
//    OF_EASE_QUART_OUT       = 25,
//    OF_EASE_QUART_INOUT     = 26,
//    OF_EASE_QUINT_IN        = 27,
//    OF_EASE_QUINT_OUT       = 28,
//    OF_EASE_QUINT_INOUT     = 29,
//    OF_EASE_SINE_IN         = 30,
//    OF_EASE_SINE_OUT        = 31,
//    OF_EASE_SINE_INOUT      = 32
//    };


