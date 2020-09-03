/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "TXSharedObject.h"

class TXModSource : public TXSharedObject
{
public:
    // Note: value is clamped to range 0-1
    
	// constructor
	TXModSource (string sourceNameArg = " ", float valueArg = 0.0);
	// methods
	void setup (string sourceNameArg = " ", float valueArg = 0.0);
    string getName();
    void setName(string nameArg);
	float getValue();
    void setValue (float valueArg);

	// properties
	
protected:
    string name;
    float value;
};

