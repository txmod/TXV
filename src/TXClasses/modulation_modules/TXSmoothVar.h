/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"
#include "TXMain.h"

class TXSmoothVar
{
public:
    // FOR REF:   enum TXSMOOTHTYPE {TXSMOOTHTYPE_EXPONENTIAL, TXSMOOTHTYPE_LINEAR};
    
	// constructor
	TXSmoothVar (int smoothTypeArg = TXSMOOTHTYPE_EXPONENTIAL, float smooothTimeArg = 1.0, float outValueArg = 0.0, float targetValueArg = 0.0, bool circularSmoothingArg = false);

	// methods
	void  setup (int smoothTypeArg = TXSMOOTHTYPE_EXPONENTIAL, float smooothTimeArg = 1.0, float outValueArg = 0.0, float targetValueArg = 0.0, bool circularSmoothingArg = false);
	void  advanceBy(float timeDeltaArg); 
    void  setTime(float timeArg = 0.0);
    float valueAt(float timeArg = 0.0);
    void  resetTime();
    void  setTargetValue(float targetValueArg = 0.0);
    float getTargetValue();
    void  setSmoothType(int smoothTypeArg);
    int   getSmoothType();
    void  setSmoothTime(float smoothTimeArg);
    float getSmoothTime();

	// properties
	
    bool  circularSmoothing;
    float outValue;

    
 protected:
    float targetValue;
 	float smoothTime;
    int   smoothType;
    float currentTime;
    float oldTime;
    float timeDiff;
    float linearRate;
    void  resetLinearRate();  
};

