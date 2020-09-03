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
//class TXModParameterBoolArgs
//{
//public:
//    string name = " ";
//    int    booleanSummingType = BOOLEANSUMMINGTYPE_OR;
//    bool   fixedValue = false;
//    bool   fixedModMix = false;
//    bool   useExtMod = false;
//    float  extModValue = 0.0;  // range 0-1
//};
//


// need to class define first
class TXModParamBool;

template<typename ParameterType>
class TXModParamBoolParam: public ofReadOnlyParameter<ParameterType, TXModParamBool>{
    friend class TXModParamBool;
};

class TXModParamBool : public TXModParameter
{
public:
	// constructor
    TXModParamBool(TXModParameterBoolArgs holdArgs);
    
    // destructor
    ~TXModParamBool();

    // methods
    void setupBool (TXModParameterBoolArgs holdArgs);
    
    bool  getFixedValueBool();
	bool  getBool();
    
    void setFixedValue (bool fixedValueArg);
    void setFixedModMix (bool fixedModMixArg);
    void setBooleanSummingType(bool booleanSummingTypeArg);
    
public:    
//    // archive methods
//    NSMutableDictionary * getDictionary();
//    void setFromDictionary(NSMutableDictionary * dataArg);
//    void setFromClipboardDictionary(NSMutableDictionary * dataArg);
    
	// properties
    
protected:
    
    TXModParamBoolParam<int>  booleanSummingType;
    ofParameter<bool> fixedValue_Bool;
    ofParameter<bool> fixedModMix_Bool;
    bool  boolOut;

};
