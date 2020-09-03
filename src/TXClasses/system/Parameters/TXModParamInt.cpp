/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXModParamInt.h"

// constructor

TXModParamInt::TXModParamInt(TXModParameterIntArgs holdArgs){
    setupInt(holdArgs);
};

// destructor
TXModParamInt::~TXModParamInt() {
    removeListener();
}

// methods

void TXModParamInt::setupInt(TXModParameterIntArgs holdArgs){
    modParameterType = MODPARAMTYPE_INT;

    parameters.clear();
    
    fixedValue_Int.set("fixedValue", holdArgs.fixedValue, holdArgs.softMin, holdArgs.softMax);
    fixedModMix_Float.set("fixedModMix", holdArgs.fixedModMix, 0.0, 1.0);
    useExtMod.set("useExtMod", holdArgs.useExtMod);
    extModValue.set("extModValue", holdArgs.extModValue, 0.0, 1.0);
    softMin_Int.set("softMin", holdArgs.softMin, holdArgs.hardMin, holdArgs.hardMax);
    softMax_Int.set("softMax", holdArgs.softMax, holdArgs.hardMin, holdArgs.hardMax);
    hardMin_Int.set("hardMin", holdArgs.hardMin, holdArgs.hardMin, holdArgs.hardMax);
    hardMax_Int.set("hardMax", holdArgs.hardMax, holdArgs.hardMin, holdArgs.hardMax);
    autoScaleModSumming.set("autoScaleModSumming", holdArgs.autoScaleModSumming);
    
    setName(holdArgs.name);
    
    parameters.setName(holdArgs.name);
    parameters.add(fixedValue_Int);
    parameters.add(fixedModMix_Float);
    parameters.add(useExtMod);
    parameters.add(extModValue);
    parameters.add(softMin_Int);
    parameters.add(softMax_Int);
    parameters.add(hardMin_Int);
    parameters.add(hardMax_Int);
    parameters.add(autoScaleModSumming);
    
    addListener();
    hasChanged = true;
    modulationAdded = true;
    resetModulation();

    intOut = 0;
};

float TXModParamInt::getFixedValueIntUnmapped() {
    float outVal;
    if (softMin_Int == softMax_Int) {
        outVal = 0.0;
    } else {
        outVal = ofMap(fixedValue_Int, softMin_Int, softMax_Int,  0.0, 1.0);
    };
    return outVal;
};

int TXModParamInt::getFixedValueInt() {
    return fixedValue_Int;
}

float TXModParamInt::getIntUnmapped() {
    float modValueNormalised, outVal;
    if (fixedModMix_Float == 0.0) {
        outVal = getFixedValueIntUnmapped();
    } else {
        if (useExtMod) {
            modValueNormalised = extModValue;
        } else {
            if (autoScaleModSumming) {
                // calculate modValueNormalised - normalise if sum of scaling > 1
                modValueNormalised = (modValue - modMin) / max (1.0f, (modMax - modMin));
            } else {
                modValueNormalised = ofClamp(modValue, 0.0, 1.0);
            };
        };
        if (fixedModMix_Float == 1.0) {
            outVal = modValueNormalised;
        } else {
            outVal = (getFixedValueIntUnmapped() * (1 - fixedModMix_Float)) + (modValueNormalised * fixedModMix_Float);
        };
    };
    return outVal;
}

int TXModParamInt::getInt() {
    float holdVal;
    if (hasChanged) {
        hasChanged = false;
        if (softMin_Int == softMax_Int) {
            holdVal = softMin_Int;
        } else {
            holdVal = ofMap(getIntUnmapped(), 0, 1, softMin_Int, softMax_Int);
        };
        if (holdVal > 0) {
            intOut = (int) (holdVal + 0.5);
        } else {
            intOut = (int) (holdVal - 0.5);
        };
    };
    return intOut;
}
void TXModParamInt::setFixedValue (int fixedValueArg, bool adjustMinMax) {
    switch (modParameterType) {
        case MODPARAMTYPE_BOOL:
            setFixedValue ((bool)fixedValueArg, adjustMinMax);
            break;
            
        case MODPARAMTYPE_FLOAT:
            setFixedValue ((float)fixedValueArg, adjustMinMax);
            break;
            
        default:
            // MODPARAMTYPE_INT
            int inValClamped = ofClamp(fixedValueArg, hardMin_Int, hardMax_Int);
            if (adjustMinMax) {
                if (softMin_Int <= softMax_Int) {
                    if (softMin_Int > inValClamped) {
                        setSoftMin(inValClamped);
                    } else if (softMax_Int < inValClamped) {
                        setSoftMax(inValClamped);
                    };
                } else {
                    if (softMin_Int < inValClamped) {
                        setSoftMin(inValClamped);
                    } else if (softMax_Int > inValClamped) {
                        setSoftMax(inValClamped);
                    };
                };
            } else {
                inValClamped= ofClamp(fixedValueArg, softMin_Int, softMax_Int);
            };
            fixedValue_Int.set(inValClamped);
            break;
    }
};

void TXModParamInt::setFixedModMix (float fixedModMixArg) {
    fixedModMix_Float.set(fixedModMixArg);
};

void TXModParamInt::setSoftMin (int softMinArg) {
    softMin_Int.set(ofClamp(softMinArg, hardMin_Int, hardMax_Int));
    fixedValue_Int.setMin(softMin_Int);
};

void TXModParamInt::setSoftMax (int softMaxArg) {
    softMax_Int.set(ofClamp(softMaxArg, hardMin_Int, hardMax_Int));
    fixedValue_Int.setMax(softMax_Int);
};


void TXModParamInt::maximiseRangeSoftMinMax() {
    softMin_Int.set(hardMin_Int);
    softMax_Int.set(hardMax_Int);
};

void TXModParamInt::setAutoScaleModSumming(bool autoScaleModSummingArg) {
    autoScaleModSumming.set(autoScaleModSummingArg);
};

