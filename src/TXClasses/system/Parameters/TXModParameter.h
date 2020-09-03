/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"
#include "TXSharedObject.h"

enum MODPARAMTYPE {
    MODPARAMTYPE_BOOL,
    MODPARAMTYPE_INT,
    MODPARAMTYPE_FLOAT
};

enum BOOLEANSUMMINGTYPE {
    BOOLEANSUMMINGTYPE_OR,
    BOOLEANSUMMINGTYPE_AND,
    BOOLEANSUMMINGTYPE_ROUNDEDAVERAGE
};

class TXModParameterBoolArgs
{
public:
    string name = " ";
    int    booleanSummingType = BOOLEANSUMMINGTYPE_OR;
    bool   fixedValue = false;
    bool   fixedModMix = false;
    bool   useExtMod = false;
    float  extModValue = 0.0;  // range 0-1
};

class TXModParameterIntArgs
{
public:
    string name = " ";
    bool   autoScaleModSumming = true;
    int    fixedValue = 0;
    float  fixedModMix = 0.0;  // range 0-1
    bool   useExtMod = false;
    float  extModValue = 0.0;  // range 0-1
    int    hardMin = 0;
    int    hardMax = 1;
    int    softMin = 0;
    int    softMax = 1;
};

class TXModParameterFloatArgs
{
public:
    string name = " ";
    bool   autoScaleModSumming = true;
    float  fixedValue = 0.0;
    float  fixedModMix = 0.0;  // range 0-1
    bool   useExtMod = false;
    float  extModValue = 0.0;  // range 0-1
    float  hardMin = 0.0;
    float  hardMax = 1.0;
    float  softMin = 0.0;
    float  softMax = 1.0;
};


class TXModParameter : public TXSharedObject
{
public:
	// constructor
    TXModParameter();
    
	// methods
    string getName();
    void setName(string nameArg);

	void resetModulation();
    void updateModulation (float valueArg, float scaleArg, bool negativeArg);

    // listener
    void  addListener();
    void  removeListener();
    void  parametersChanged(ofAbstractParameter & parameterArg );

    // virtual methods
    virtual float getFixedValueIntUnmapped();
	virtual float getFixedValueFloatUnmapped();
    virtual bool  getFixedValueBool();
    virtual int   getFixedValueInt();
    virtual float getFixedValueFloat();
    virtual float getFloatUnmapped();
	virtual float getFloat();
    virtual float getIntUnmapped();
	virtual int   getInt();
	virtual bool  getBool();
    
//    virtual void setFixedValue (bool fixedValueArg);
//    virtual void setFixedValue (int fixedValueArg, bool adjustMinMax = false);
//    virtual void setFixedValue (float fixedValueArg, bool adjustMinMax = false);
//    virtual void setFixedModMix (bool fixedModMixArg);
//    virtual void setFixedModMix (float fixedModMixArg);
//    virtual void setSoftMin (int softMinArg);
//    virtual void setSoftMin (float softMinArg);
//    virtual void setSoftMax (int softMaxArg);
//    virtual void setSoftMax (float softMaxArg);
//    virtual void maximiseRangeSoftMinMax();
//    virtual void setAutoScaleModSumming(bool autoScaleModSummingArg);
//    virtual void setBooleanSummingType(bool booleanSummingTypeArg);
    
public:    
//    // archive methods
//    NSMutableDictionary * getDictionary();
//    void setFromDictionary(NSMutableDictionary * dataArg);
//    void setFromClipboardDictionary(NSMutableDictionary * dataArg);
    
	// properties
public:
    ofParameterGroup parameters;
    
protected:
    int  modParameterType;
    float modValue;
    float modMin;
    float modMax;
    string name;
    bool hasChanged;
    bool modulationAdded;

    ofParameter<bool> useExtMod;
    ofParameter<float> extModValue;

};
