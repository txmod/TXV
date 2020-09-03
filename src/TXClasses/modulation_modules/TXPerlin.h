/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"
#include "TXModuleBase.h"

enum PERLINTYPE {
    PERLINTYPE_NORMAL,
    PERLINTYPE_QUANTISED
//    PERLINTYPE_SQUARED,   // no longer used
//    PERLINTYPE_RANDOMWALK // no longer used
};

class TXPerlin  : public TXModuleBase
{
public:
	// Output range is 0 to +1

    // NOTE - change totalPerlinTypes when adding new types:
    static const int totalPerlinTypes = 2;

	// constructor
	TXPerlin (int perlinTypeArg = PERLINTYPE_NORMAL, float speedArg = 1.0, float speedDivisorArg = 1.0,
              float phaseOffsetArg = 0.0, bool useMasterBpmArg = true, bool frozenArg = false);

	// methods
	void setup (int perlinTypeArg = PERLINTYPE_NORMAL, float speedArg = 1.0, float speedDivisorArg = 1.0,
                float phaseOffsetArg = 0.0, bool useMasterBpmArg = true, bool frozenArg = false);
	void advanceBy(float timeDeltaArg); 
    void setTime(float timeArg = 0);
    void calculateOutput();
    float getValue();
    
//    // archive methods
//    NSMutableDictionary * getDictionary();
//    void setFromDictionary(NSMutableDictionary * dataArg);

	// properties
    
    ofPtr<TXModParamInt> perlinType;
    ofPtr<TXModParamFloat> speed;
    ofPtr<TXModParamFloat> speedDivisor;
    ofPtr<TXModParamBool> useMasterBpm;
    ofPtr<TXModParamBool> frozen;

    ofPtr<TXModSource> outValue;

protected:
    float currentTime;
	float phase;
    float accumlator;
    float flipper;

};
