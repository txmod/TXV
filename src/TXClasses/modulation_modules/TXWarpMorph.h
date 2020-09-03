/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"
#include "TXModuleBase.h"

enum TXWARPMORPHTYPE {
    TXWARPMORPHTYPE_LINEAR,
    TXWARPMORPHTYPE_EXPONENTIAL,
    TXWARPMORPHTYPE_MINUS_EXPONENTIAL,
    TXWARPMORPHTYPE_5,
    TXWARPMORPHTYPE_4,
    TXWARPMORPHTYPE_3,
    TXWARPMORPHTYPE_2,
    TXWARPMORPHTYPE_MINUS_2,
    TXWARPMORPHTYPE_MINUS_3,
    TXWARPMORPHTYPE_MINUS_4,
    TXWARPMORPHTYPE_MINUS_5,
    TXWARPMORPHTYPE_PHASESHIFT_90,
    TXWARPMORPHTYPE_PHASESHIFT_180,
    TXWARPMORPHTYPE_PHASESHIFT_270,
    TXWARPMORPHTYPE_CUSTOMCURVE,
    TXWARPMORPHTYPE_CUSTOMCURVE2,
};

class TXWarpMorph : public TXModuleBase
{
public:
    // NOTE - change totalWarpTypes when adding new types:
    const int totalWarpTypes = 16;

	
// constructor
	TXWarpMorph (int warpTypeArg = TXWARPMORPHTYPE_LINEAR, int warpType2Arg = TXWARPMORPHTYPE_LINEAR, float warpTypeMorphArg = 0.0, float inputMinArg = 0.0, float inputMaxArg = 1.0, float outputMinArg = 0.0, float outputMaxArg = 1.0, bool useQuantize = false, int quantizeSteps = 4);

	// methods
	void  setup (int warpTypeArg = TXWARPMORPHTYPE_LINEAR, int warpType2Arg = TXWARPMORPHTYPE_LINEAR, float warpTypeMorphArg = 0.0, float inputMinArg = 0.0, float inputMaxArg = 1.0, float outputMinArg = 0.0, float outputMaxArg = 1.0, bool useQuantize = false, int quantizeSteps = 4);
    void resetTime();
    void advanceBy(float timeDeltaArg);
	void calculateOutput();
    float applyCurve(int curveType, float inVal);
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
    ofPtr<TXModParamInt> warpType2;
    ofPtr<TXModParamFloat> warpTypeMorph;
	ofPtr<TXModParamFloat> inputMin;
    ofPtr<TXModParamFloat> inputMax;
	ofPtr<TXModParamFloat> outputMin;
    ofPtr<TXModParamFloat> outputMax;
    ofPtr<TXModParamBool> useQuantize;
    ofPtr<TXModParamInt> quantizeSteps;
    
    TXParameterFloat256 customCurve;
    TXParameterFloat256 customCurve2;
    
    ofPtr<TXModSource> outValue;
	

protected:

};

