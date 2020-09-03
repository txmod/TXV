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

class TXDrawConnection; 

template<typename ParameterType>
class TXDrawConnectionParam: public ofReadOnlyParameter<ParameterType, TXDrawConnection>{
    friend class TXDrawConnection;
};

class TXDrawConnection  :  public TXModuleBase
{
public:
	// constructor
	TXDrawConnection (int sourceModuleIDArg = 0, int destinationModuleIDArg = 0, int layerNoArg = 0);
    
	// methods
	void  setup (int sourceModuleIDArg = 0, int destinationModuleIDArg = 0, int layerNoArg = 0);
	int   getSourceModuleID();
    void  setSourceModuleID(int sourceModuleIDArg);
	int   getDestinationModuleID();
    void  setDestinationModuleID(int destinationModuleIDArg);
    void  layerNoChanged(int & newLayerNo);
    void  activeChanged(bool & activeArg);
    
	// properties
    TXDrawConnectionParam<int> sourceModuleID;
    TXDrawConnectionParam<int> destinationModuleID;
    ofParameter<int> layerNo;
    ofParameter<bool> active;
    
protected:
    int oldLayerNo;
    bool oldActive;
};


