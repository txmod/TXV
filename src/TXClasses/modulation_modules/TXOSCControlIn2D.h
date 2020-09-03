/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"
#include "TXModuleBase.h"
#include "ofxOsc.h"
#include "TXSmoothVar.h"

class TXOSCControlIn2D  : public TXModuleBase
{
public:
	// constructor
	TXOSCControlIn2D (float startValArg = 0.0, float startVal2Arg = 0.0);

    // destructor
    ~TXOSCControlIn2D ();

	// methods
	void  setup (float startValArg = 0.0, float startVal2Arg = 0.0);
    void  update();
	void  advanceBy(float timeDeltaArg);
    void  resetTime();

    void  oscAddressChanged(string & stringArg);
    void  processOscMsg(ofxOscMessage msg);
    void  smoothTimeChanged(ofAbstractParameter & parameterArg );
    void  linearSmoothingChanged(ofAbstractParameter & parameterArg );

//    // archive methods
//    NSMutableDictionary * getDictionary();
//    void setFromDictionary(NSMutableDictionary * dataArg);

    // parameters
     
    ofPtr<TXModParamBool> active;
    ofParameter<string> oscAddress;
    ofPtr<TXModParamFloat> input1Min;
    ofPtr<TXModParamFloat> input1Max;
    ofPtr<TXModParamFloat> input2Min;
    ofPtr<TXModParamFloat> input2Max;
    ofPtr<TXModParamFloat> smoothTime;
    ofPtr<TXModParamBool> linearSmoothing;
    
    // output
    ofPtr<TXModSource> outValue1;
    ofPtr<TXModSource> outValue2;
	
protected:
    string oldAddress;
    bool  newOSCValue1Received;
    bool  newOSCValue2Received;
    float newOSCValue1;
    float newOSCValue2;

    // smoother
    TXSmoothVar smoothVal1;
    TXSmoothVar smoothVal2;
};

