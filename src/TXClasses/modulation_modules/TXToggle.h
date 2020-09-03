/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"
#include "TXModuleBase.h"

class TXToggle  : public TXModuleBase
{
public:
	// constructor
	TXToggle (float startValArg = 0.0);

	// methods
	void  setup (float startValArg =  0.0);
    void resetTime();
    void advanceBy(float timeDeltaArg);
	void calculateOutput();
    void  toggleValue ();

//    // archive methods
//    NSMutableDictionary * getDictionary();
//    void setFromDictionary(NSMutableDictionary * dataArg);

	// properties
    
    ofPtr<TXModParamFloat> inputValue;
    ofPtr<TXModParamFloat> triggerThreshold;
    ofPtr<TXModParamBool>  resetToZero;
    
    // output
    ofPtr<TXModSource> outValue;
	
	
protected:
    float inputPrevious;
};

