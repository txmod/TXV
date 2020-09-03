/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h" 
//#include "TXModuleBase.h" 
//#include "TXDrawBase.h"
#include "TXDrawLayersBase.h"

//class TX_template;
//
//template<typename ParameterType>
//class TX_templateParam: public ofReadOnlyParameter<ParameterType,TX_template>{
//    friend class TX_template;
//};

class TX_template  :  public TXDrawLayersBase
{
public:
	// constructor
	TX_template();

    // destructor
    ~TX_template();

	void setup();
	virtual void draw();
    
    // listener methods
    void  xxxINTChanged(ofAbstractParameter & parameterArg );
    void  testParameterIChanged(int & intArg);

    ofPtr<TXModParamInt> xxxINT;
    ofPtr<TXModParamFloat> xxxFLOAT;
    ofPtr<TXModParamBool> xxxBOOL;

    TXParameterFloat256 customCurve;

    ofParameter<int> testParameterI;
    ofParameter<float> testParameterF;
    ofParameter<bool> testParameterB;
    ofParameter<string> testParameterS;

    ofPtr<TXModSource> outValue;
    
//	TX_templateParam<int> imageAssetID;
    
    ofImage outImage;
};

