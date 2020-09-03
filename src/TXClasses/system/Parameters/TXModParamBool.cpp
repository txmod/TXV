/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXModParamBool.h"

// constructor

TXModParamBool::TXModParamBool(TXModParameterBoolArgs holdArgs){
    setupBool(holdArgs);
};

// destructor
TXModParamBool::~TXModParamBool() {
    removeListener();
}

// methods

void TXModParamBool::setupBool(TXModParameterBoolArgs holdArgs){
    modParameterType = MODPARAMTYPE_BOOL;

    parameters.clear();
    
    fixedValue_Bool.set("fixedValue", holdArgs.fixedValue);
    fixedModMix_Bool.set("fixedModMix", holdArgs.fixedModMix, 0, 1);
    useExtMod.set("useExtMod", holdArgs.useExtMod);
    extModValue.set("extModValue", holdArgs.extModValue, 0.0, 1.0);
    booleanSummingType.set("booleanSummingType", holdArgs.booleanSummingType);
    
    setName(holdArgs.name);
    
    parameters.setName(holdArgs.name);
    parameters.add(fixedValue_Bool);
    parameters.add(fixedModMix_Bool);
    parameters.add(useExtMod);
    parameters.add(extModValue);
    parameters.add(booleanSummingType);
    
    addListener();
    hasChanged = true;
    modulationAdded = true;
    resetModulation();
    
    boolOut = false;
};

bool TXModParamBool::getFixedValueBool() {
    return fixedValue_Bool;
}

bool TXModParamBool::getBool() {
    float modValueNormalised;
    
    if (hasChanged) {
        hasChanged = false;
        if (!fixedModMix_Bool) {
            boolOut = (fixedValue_Bool >= 0.5);
        } else {
            if (useExtMod) {
                boolOut = (extModValue >= 0.5);
            } else {
                switch (booleanSummingType) {
                    case BOOLEANSUMMINGTYPE_OR:
                        boolOut = (modValue > modMin);
                        break;
                    case BOOLEANSUMMINGTYPE_AND:
                        boolOut = (modValue == modMax);
                        break;
                    default:
                        // BOOLEANSUMMINGTYPE_ROUNDEDAVERAGE
                        modValueNormalised = (modValue / max (1.0f, (modMax - modMin))) - modMin;
                        boolOut = (modValueNormalised >= 0.5);
                        break;
                }
            };
        };
    }
    return boolOut;
};

void TXModParamBool::setFixedValue (bool fixedValueArg) {
    fixedValue_Bool.set(fixedValueArg);
};

void TXModParamBool::setFixedModMix (bool fixedModMixArg) {
    fixedModMix_Bool.set(fixedModMixArg);
};

void TXModParamBool::setBooleanSummingType(bool booleanSummingTypeArg) {
    booleanSummingType.set(booleanSummingTypeArg);
};

