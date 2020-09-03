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

class TXOSCControlIn3D  : public TXModuleBase
{
public:
	// constructor
	TXOSCControlIn3D (float startVal1Arg = 0.0, float startVal2Arg = 0.0, float startVal3Arg = 0.0);

    // destructor
    ~TXOSCControlIn3D ();

	// methods
	void  setup (float startVal1Arg = 0.0, float startVal2Arg = 0.0, float startVal3Arg = 0.0);
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
    ofPtr<TXModParamFloat> input3Min;
    ofPtr<TXModParamFloat> input3Max;
    ofPtr<TXModParamFloat> smoothTime;
    ofPtr<TXModParamBool> linearSmoothing;
    
    // output
    ofPtr<TXModSource> outValue1;
    ofPtr<TXModSource> outValue2;
    ofPtr<TXModSource> outValue3;
	
	
protected:
    string oldAddress;
    bool  newOSCValue1Received;
    bool  newOSCValue2Received;
    bool  newOSCValue3Received;
    float newOSCValue1;
    float newOSCValue2;
    float newOSCValue3;

    // smoother
    TXSmoothVar smoothVal1;
    TXSmoothVar smoothVal2;
    TXSmoothVar smoothVal3;
};

