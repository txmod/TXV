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
//class TXModParameterIntArgs
//{
//public:
//    string name = " ";
//    bool   autoScaleModSumming = true;
//    int    fixedValue = 0;
//    float  fixedModMix = 0.0;  // range 0-1
//    bool   useExtMod = false;
//    float  extModValue = 0.0;  // range 0-1
//    int    hardMin = 0;
//    int    hardMax = 1;
//    int    softMin = 0;
//    int    softMax = 1;
//};
//

// need to class define first
class TXModParamInt;

template<typename ParameterType>
class TXModParamIntParam: public ofReadOnlyParameter<ParameterType, TXModParamInt>{
    friend class TXModParamInt;
};

class TXModParamInt : public TXModParameter
{
public:
	//// constructor
    TXModParamInt(TXModParameterIntArgs holdArgs);
    
    // destructor
    ~TXModParamInt();
    
	// methods
    void setupInt (TXModParameterIntArgs holdArgs);
    
	float getFixedValueIntUnmapped();
    int   getFixedValueInt();
    float getIntUnmapped();
	int   getInt();
    
    void setFixedValue (int fixedValueArg, bool adjustMinMax = false);
    void setFixedModMix (float fixedModMixArg);
    void setSoftMin (int softMinArg);
    void setSoftMax (int softMaxArg);
    void maximiseRangeSoftMinMax();
    void setAutoScaleModSumming(bool autoScaleModSummingArg);
    
public:    
//    // archive methods
//    NSMutableDictionary * getDictionary();
//    void setFromDictionary(NSMutableDictionary * dataArg);
//    void setFromClipboardDictionary(NSMutableDictionary * dataArg);
    
	// properties
    
protected:

    TXModParamIntParam<bool> autoScaleModSumming;
    TXModParamIntParam<int> hardMin_Int;
    TXModParamIntParam<int> hardMax_Int;
    ofParameter<int> softMin_Int;
    ofParameter<int> softMax_Int;
    ofParameter<int> fixedValue_Int;
    ofParameter<float> fixedModMix_Float;
    int intOut;
    
};
