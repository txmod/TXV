/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"
#include "TXModuleBase.h"
#include "TXSmoothVar.h"

class TXSmoothMulti : public TXModuleBase
{
public:
	// constructor
	TXSmoothMulti ();

    // destructor
    ~TXSmoothMulti ();
    
	// methods
	void  setup ();
    void  update();
	void  advanceBy(float timeDeltaArg);
    void  setTime(float timeArg = 0.0);
    void  resetTime();

//    // archive methods
//    NSMutableDictionary * getDictionary();
//    void  setFromDictionary(NSMutableDictionary * dataArg);

	// properties
    ofPtr<TXModParamInt> smoothType;
	ofPtr<TXModParamFloat> smoothTime;
    ofPtr<TXModParamFloat> targetValue1;
    ofPtr<TXModParamFloat> targetValue2;
    ofPtr<TXModParamFloat> targetValue3;
    ofPtr<TXModParamFloat> targetValue4;
    ofPtr<TXModParamFloat> targetValue5;
    ofPtr<TXModParamFloat> targetValue6;
    ofPtr<TXModParamFloat> targetValue7;
    ofPtr<TXModParamFloat> targetValue8;
    ofPtr<TXModParamFloat> targetValue9;
    ofPtr<TXModParamFloat> targetValue10;
    ofPtr<TXModParamFloat> targetValue11;
    ofPtr<TXModParamFloat> targetValue12;
    ofPtr<TXModParamBool> circularSmoothing1;
    ofPtr<TXModParamBool> circularSmoothing2;
    ofPtr<TXModParamBool> circularSmoothing3;
    ofPtr<TXModParamBool> circularSmoothing4;
    ofPtr<TXModParamBool> circularSmoothing5;
    ofPtr<TXModParamBool> circularSmoothing6;
    ofPtr<TXModParamBool> circularSmoothing7;
    ofPtr<TXModParamBool> circularSmoothing8;
    ofPtr<TXModParamBool> circularSmoothing9;
    ofPtr<TXModParamBool> circularSmoothing10;
    ofPtr<TXModParamBool> circularSmoothing11;
    ofPtr<TXModParamBool> circularSmoothing12;
    
    ofPtr<TXModSource> outValue1;
    ofPtr<TXModSource> outValue2;
    ofPtr<TXModSource> outValue3;
    ofPtr<TXModSource> outValue4;
    ofPtr<TXModSource> outValue5;
    ofPtr<TXModSource> outValue6;
    ofPtr<TXModSource> outValue7;
    ofPtr<TXModSource> outValue8;
    ofPtr<TXModSource> outValue9;
    ofPtr<TXModSource> outValue10;
    ofPtr<TXModSource> outValue11;
    ofPtr<TXModSource> outValue12;
    
 protected:
    // smoother
    TXSmoothVar smoothVal1;
    TXSmoothVar smoothVal2;
    TXSmoothVar smoothVal3;
    TXSmoothVar smoothVal4;
    TXSmoothVar smoothVal5;
    TXSmoothVar smoothVal6;
    TXSmoothVar smoothVal7;
    TXSmoothVar smoothVal8;
    TXSmoothVar smoothVal9;
    TXSmoothVar smoothVal10;
    TXSmoothVar smoothVal11;
    TXSmoothVar smoothVal12;


};

