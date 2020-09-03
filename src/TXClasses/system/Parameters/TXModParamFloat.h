/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "TXModParameter.h"

//enum MODPARAMTYPE {
//    MODPARAMTYPE_BOOL,
//    MODPARAMTYPE_INT,
//    MODPARAMTYPE_FLOAT
//};
//
//enum BOOLEANSUMMINGTYPE {
//    BOOLEANSUMMINGTYPE_OR,
//    BOOLEANSUMMINGTYPE_AND,
//    BOOLEANSUMMINGTYPE_ROUNDEDAVERAGE
//};
//
//class TXModParameterFloatArgs
//{
//public:
//    string name = " ";
//    bool   autoScaleModSumming = true;
//    float  fixedValue = 0.0;
//    float  fixedModMix = 0.0;  // range 0-1
//    bool   useExtMod = false;
//    float  extModValue = 0.0;  // range 0-1
//    float  hardMin = 0.0;
//    float  hardMax = 1.0;
//    float  softMin = 0.0;
//    float  softMax = 1.0;
//};

// need to class define first
class TXModParamFloat;

template<typename ParameterType>
class TXModParamFloatParam: public ofReadOnlyParameter<ParameterType, TXModParamFloat>{
    friend class TXModParamFloat;
};

class TXModParamFloat : public TXModParameter
{
public:
	//// constructor
    TXModParamFloat(TXModParameterFloatArgs holdArgs);
    
    // destructor
    ~TXModParamFloat();
    
	// methods
    void setupFloat (TXModParameterFloatArgs holdArgs);
    
	float getFixedValueFloatUnmapped();
    float getFixedValueFloat();
    float getFloatUnmapped();
	float getFloat();
    
    void setFixedValue (float fixedValueArg, bool adjustMinMax = false);
    void setFixedModMix (float fixedModMixArg);
    void setSoftMin (float softMinArg);
    void setSoftMax (float softMaxArg);
    void maximiseRangeSoftMinMax();
    void setAutoScaleModSumming(bool autoScaleModSummingArg);
    
public:    
//    // archive methods
//    NSMutableDictionary * getDictionary();
//    void setFromDictionary(NSMutableDictionary * dataArg);
//    void setFromClipboardDictionary(NSMutableDictionary * dataArg);
    
	// properties
    
protected:

    TXModParamFloatParam<bool> autoScaleModSumming;
    TXModParamFloatParam<float> hardMin_Float;
    TXModParamFloatParam<float> hardMax_Float;
    ofParameter<float> softMin_Float;
    ofParameter<float> softMax_Float;
    ofParameter<float> fixedValue_Float;
    ofParameter<float> fixedModMix_Float;
    float floatOut;
    
};
