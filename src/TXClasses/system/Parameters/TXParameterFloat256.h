/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"
#include "TXSharedObject.h"

class TXParameterFloat256 : public TXSharedObject
{
public:
	// constructor
    TXParameterFloat256();
    
	// methods
    void setup(string nameArg, float * valueArrayArg);
        
    string getName();
    void setName(string nameArg);
    
	float * getValueArray();
	void setValueArray (float * valueArrayArg);
	void setValueArray (ofParameterGroup & groupArg);
	void setValueArrayTo (float valueArg);
	void setValueArrayToRamp (float startValueArg, float endValueArg);
    float interpolatedLookup(float & inputArg);
    float interpolatedLookupWithPhase(float & inputArg, float & phaseArg);
    
	// properties
public:
    ofParameterGroup parameters;
    
protected:
    
    string name;
};

