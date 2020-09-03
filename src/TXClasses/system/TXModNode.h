/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"

#include "TXModuleBase.h"
#include "TXModParameter.h"
//#include "TXMain.h"

class TXModNode;

template<typename ParameterType>
class TXModNodeParam: public ofReadOnlyParameter<ParameterType, TXModNode>{
    friend class TXModNode;
};

class TXModNode  :  public TXModuleBase
{
public:
	// constructor
	TXModNode (int sourceModuleIDArg = 0, string sourceNameArg = "", int destinationModuleIDArg = 0, string destinationNameArg = "", float modAmountArg = 1.0, bool negativeModulationArg = false, bool activeArg = false);
    
	// methods
	void setup (int sourceModuleIDArg = 0, string sourceNameArg = "", int destinationModuleIDArg = 0, string destinationNameArg = "", float modAmountArg = 1.0, bool negativeModulationArg = false, bool activeArg = false);
	int getSourceModuleID();
    void  setSourceModuleID(int sourceModuleIDArg);
	int getDestinationModuleID();
    void  setDestinationModuleID(int destinationModuleIDArg);
	string getSourceName();
    void  setSourceName(string sourceNameArg);
	string getDestinationName();
    void  setDestinationName(string destinationNameArg);
    
	// properties
    TXModNodeParam<int> sourceModuleID;
    TXModNodeParam<int> destinationModuleID;
    TXModNodeParam<string> sourceName;
    TXModNodeParam<string> destinationName;
    ofParameter<bool> active;
    ofPtr<TXModParamFloat> modAmount;
    ofPtr<TXModParamBool> negativeModulation;
    
protected:
        
};

