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

class TXOSCControlIn  : public TXModuleBase
{
public:
	// constructor
	TXOSCControlIn (float startValArg = 0.0);

    // destructor
    ~TXOSCControlIn ();

	// methods
	void  setup (float startValArg =  0.0);
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
    ofPtr<TXModParamFloat> inputMin;
    ofPtr<TXModParamFloat> inputMax;
    ofPtr<TXModParamFloat> smoothTime;
    ofPtr<TXModParamBool> linearSmoothing;
    
    // output
    ofPtr<TXModSource> outValue;
	
	
protected:
    string oldAddress;
    bool  newOSCValueReceived;
    float newOSCValue;

    // smoother
    TXSmoothVar smoothVal;
};

