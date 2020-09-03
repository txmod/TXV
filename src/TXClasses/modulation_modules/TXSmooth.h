/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"
#include "TXModuleBase.h"
#include "TXSmoothVar.h"

class TXSmooth : public TXModuleBase
{
public:
	// constructor
	TXSmooth (int smoothTypeArg = TXSMOOTHTYPE_EXPONENTIAL, float smooothTimeArg = 1.0, float outValueArg = 0.0, float targetValueArg = 0.0, bool circularSmoothingArg = false);

    // destructor
    ~TXSmooth ();
    
	// methods
	void  setup (int smoothTypeArg = TXSMOOTHTYPE_EXPONENTIAL, float smooothTimeArg = 1.0, float outValueArg = 0.0, float targetValueArg = 0.0, bool circularSmoothingArg = false);
    void  update();
	void  advanceBy(float timeDeltaArg);
    void  setTime(float timeArg = 0.0);
	float getValue(); 
	float getValueAt(float timeArg);
    
// OLD
//	ofPtr<TXModParameter> getSmoothType();
//    void  setSmoothTypeFixed(int smoothTypeArg = TXSMOOTHTYPE_EXPONENTIAL);
//	ofPtr<TXModParameter> getSmoothTime();
//    void  setSmoothTimeFixed(float smooothTimeFixedArg = 1.0);
//	ofPtr<TXModParameter> getTargetValue();
//    void  setTargetValueFixed(float targetValueFixedArg = 0.0);
//	ofPtr<TXModParameter> getCircularSmoothing();
//    void  setCircularSmoothingFixed(bool circularSmoothingFixedArg = false);
    
	float getOutValue();
    void  setOutValue(float outValueArg = 0.0);
    void  resetTime();

//    // archive methods
//    NSMutableDictionary * getDictionary();
//    void  setFromDictionary(NSMutableDictionary * dataArg);

	// properties
	
    ofPtr<TXModParamInt> smoothType;
    ofPtr<TXModParamFloat> targetValue;
	ofPtr<TXModParamFloat> smoothTime;
    ofPtr<TXModParamBool> circularSmoothing;
    
    ofPtr<TXModSource> outValue;
    
 protected:
    // smoother
    TXSmoothVar smoothVal;

};

