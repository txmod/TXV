/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 *
 *  NOTE: TXSimpleLFO is not a TX Module. It's just to be used inside other modules,
 *        such as TXLFO2D/3D, TXSimpleLFO2D/3D and TXParticles/3D.
 *
 *        It doesn't have modulatable parameters
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"
//#include "TXModuleBase.h"
#include "TXLFO.h"


class TXSimpleLFOArgs
{
public:
    int lfoType = 0;
    int randomSmoothType = TXLFOSMOOTHTYPE_SINE_INOUT;
    float bpm = 120.0;
    float cycleTimeBeats = 1.0;
    float cycleTimeDivisor = 1.0;
    float phaseOffset = 0.0;
    float pulseWidth = 0.5;
    bool useMasterBpm = false;
    bool frozen = false;
    float customCurveMorph = 0.0;
};

class TXSimpleLFO 
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
	TXSimpleLFO ();
	TXSimpleLFO (TXSimpleLFOArgs holdArgs);

	// methods
	void setup (TXSimpleLFOArgs holdArgs);
	void advanceBy(float timeDeltaArg, float masterBpmArg);
    // void setTime(float timeArg, float masterBpmArg);
    void resetTime();
    void resetTime(int randSeed);
	void calculateOutput();
    float getPhase();
	float getValue();
    int   getLfoType();
    void  setLfoType(int lfoTypeArg);
    int   getRandomSmoothType();
    void  setRandomSmoothType(int randomSmoothTypeArg);
	float getBpm();
    void  setBpm(float bpmArg);
    float getCycleTimeBeats();
    void  setCycleTimeBeats(float cycleTimeBeatsArg);
    float getCycleTimeDivisor();
    void  setCycleTimeDivisor(float cycleTimeDivisorArg);
    float getPhaseOffset();
    void  setPhaseOffset(float phaseOffsetArg);
    float getPulseWidth();
    void  setPulseWidth(float pulseWidthArg);
    bool  getUseMasterBpm();
    void  setUseMasterBpm(bool useMasterBpmArg);
    bool  getFrozen();
    void  setFrozen(bool frozenArg);
    float * getCustomCurve();
    float * getCustomCurve2();
    void setCustomCurve (float * valueArrayArg);
    void setCustomCurve (ofParameterGroup & groupArg);
    void setCustomCurve2 (float * valueArrayArg);
    void setCustomCurve2 (ofParameterGroup & groupArg);
    
    int lfoType;
    int randomSmoothType;
    float bpm;
    float cycleTimeBeats;
    float cycleTimeDivisor;
    float phaseOffset;
    float pulseWidth;
    bool useMasterBpm;
    bool frozen;
    
    TXParameterFloat256   customCurve;
    TXParameterFloat256   customCurve2;
    bool customCurveMorph;

    float outValue;
    float masterBpm;

protected:
    void  updateRandomiser(bool forceNewNumber = false, int randSeed = -1);
    
    float currentTime;
    float randPhase;
    float oldRandPhase;
	float phase;
    float oldPhase;
    float oldPhaseOffset;
    float oldTime;
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


