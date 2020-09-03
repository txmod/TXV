/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"
#include "TXModuleBase.h"

class TXSampleHold  : public TXModuleBase
{
public:
	// constructor
	TXSampleHold (float startValArg = 0.0, bool holdArg = false, bool bypassArg = false);

	// methods
	void setup (float startValArg = 0.0, float holdArg = false, bool bypassArg = false);
    void resetTime();
    void advanceBy(float timeDeltaArg);
	void calculateOutput();
//    void setHold (bool holdArg);
//    void setHoldF (float holdFArg);
//    void setBypass (bool bypassArg);
//	bool getHold(); 
//	bool getBypass(); 

//    // archive methods
//    NSMutableDictionary * getDictionary();
//    void setFromDictionary(NSMutableDictionary * dataArg);

	// properties

    ofPtr<TXModParamFloat> inputValue;
    ofPtr<TXModParamBool> hold;
    ofPtr<TXModParamBool> bypass;
    
    ofPtr<TXModSource> outValue; 
	
protected:
    //float currentValue;
    float holdValue;
};

