/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"
#include "TXModuleBase.h"

enum TXWARPTYPE {
    TXWARPTYPE_LINEAR,
    TXWARPTYPE_EXPONENTIAL,
    TXWARPTYPE_MINUS_EXPONENTIAL,
    TXWARPTYPE_5,
    TXWARPTYPE_4,
    TXWARPTYPE_3,
    TXWARPTYPE_2,
    TXWARPTYPE_MINUS_2,
    TXWARPTYPE_MINUS_3,
    TXWARPTYPE_MINUS_4,
    TXWARPTYPE_MINUS_5,
    TXWARPTYPE_PHASESHIFT_90,
    TXWARPTYPE_PHASESHIFT_180,
    TXWARPTYPE_PHASESHIFT_270,
    TXWARPTTYPE_CUSTOMCURVE,
};

class TXWarp : public TXModuleBase
{
public:
    // NOTE - change totalWarpTypes when adding new types:
    const int totalWarpTypes = 15;

	
// constructor
	TXWarp (int warpTypeArg = TXWARPTYPE_LINEAR, float inputMinArg = 0.0, float inputMaxArg = 1.0, float outputMinArg = 0.0, float outputMaxArg = 1.0, bool useQuantize = false, int quantizeSteps = 4);

	// methods
	void  setup (int warpTypeArg = TXWARPTYPE_LINEAR, float inputMinArg = 0.0, float inputMaxArg = 1.0, float outputMinArg = 0.0, float outputMaxArg = 1.0, bool useQuantize = false, int quantizeSteps = 4);
    void resetTime();
    void advanceBy(float timeDeltaArg);
	void calculateOutput();
//	float getInputMin(); 
//    void  setInputMin(float inputMinArg);
//	float getInputMax(); 
//    void  setInputMax(float inputMaxArg);
//	float getOutputMin(); 
//    void  setOutputMin(float outputMinArg);
//	float getOutputMax(); 
//    void  setOutputMax(float outputMaxArg);
//	bool  getUseQuantize(); 
//    void  setUseQuantize(bool useQuantizeArg);
//	int   getQuantizeSteps(); 
//    void  setQuantizeSteps(int quantizeStepsArg);

//    // archive methods
//    NSMutableDictionary * getDictionary();
//    void  setFromDictionary(NSMutableDictionary * dataArg);

	// properties
    
    ofPtr<TXModParamFloat> inputValue;
    ofPtr<TXModParamInt> warpType;
	ofPtr<TXModParamFloat> inputMin;
    ofPtr<TXModParamFloat> inputMax;
	ofPtr<TXModParamFloat> outputMin;
    ofPtr<TXModParamFloat> outputMax;
    ofPtr<TXModParamBool> useQuantize;
    ofPtr<TXModParamInt> quantizeSteps;
    
    TXParameterFloat256 customCurve;
    
    ofPtr<TXModSource> outValue;
	

protected:
};

