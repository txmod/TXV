/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXModParamFloat.h"

// constructor


TXModParamFloat::TXModParamFloat(TXModParameterFloatArgs holdArgs){
    setupFloat(holdArgs);
};

// destructor
TXModParamFloat::~TXModParamFloat() {
    removeListener();
}

// methods

void TXModParamFloat::setupFloat(TXModParameterFloatArgs holdArgs){
    modParameterType = MODPARAMTYPE_FLOAT;

    parameters.clear();
    
    fixedValue_Float.set("fixedValue", holdArgs.fixedValue, holdArgs.softMin, holdArgs.softMax);
    fixedModMix_Float.set("fixedModMix", holdArgs.fixedModMix, 0.0, 1.0);
    useExtMod.set("useExtMod", holdArgs.useExtMod);
    extModValue.set("extModValue", holdArgs.extModValue, 0.0, 1.0);
    softMin_Float.set("softMin", holdArgs.softMin, holdArgs.hardMin, holdArgs.hardMax);
    softMax_Float.set("softMax", holdArgs.softMax, holdArgs.hardMin, holdArgs.hardMax);
    hardMin_Float.set("hardMin", holdArgs.hardMin, holdArgs.hardMin, holdArgs.hardMax);
    hardMax_Float.set("hardMax", holdArgs.hardMax, holdArgs.hardMin, holdArgs.hardMax);
    autoScaleModSumming.set("autoScaleModSumming", holdArgs.autoScaleModSumming);
    
    setName(holdArgs.name);
    
    parameters.setName(holdArgs.name);
    parameters.add(fixedValue_Float);
    parameters.add(fixedModMix_Float);
    parameters.add(useExtMod);
    parameters.add(extModValue);
    parameters.add(softMin_Float);
    parameters.add(softMax_Float);
    parameters.add(hardMin_Float);
    parameters.add(hardMax_Float);
    parameters.add(autoScaleModSumming);
    
    addListener();
    hasChanged = true;
    modulationAdded = true;
    resetModulation();
    
    floatOut = 0.0f;
};

float TXModParamFloat::getFixedValueFloatUnmapped() {
    float outVal;
    if (softMin_Float == softMax_Float) {
        outVal = 0.0;
    } else {
        outVal = ofMap(fixedValue_Float, softMin_Float, softMax_Float, 0.0, 1.0);
    };
    return outVal;
};

float TXModParamFloat::getFixedValueFloat() {
    return fixedValue_Float;
}

float TXModParamFloat::getFloatUnmapped() {
    float outVal, modValueNormalised;
    if (fixedModMix_Float == 0.0) {
        outVal = getFixedValueFloatUnmapped();
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
            outVal = (getFixedValueFloatUnmapped() * (1 - fixedModMix_Float)) + (modValueNormalised * fixedModMix_Float);
        };
    };
    return outVal;
}

float TXModParamFloat::getFloat() {
    if (hasChanged) {
        hasChanged = false;
        if (softMin_Float == softMax_Float) {
            floatOut = softMin_Float;
        } else {
            floatOut = ofMap(getFloatUnmapped(), 0.0, 1.0, softMin_Float, softMax_Float);
        };
    };
    return floatOut;
}

void TXModParamFloat::setFixedValue (float fixedValueArg, bool adjustMinMax) {
    switch (modParameterType) {
        case MODPARAMTYPE_BOOL:
            setFixedValue ((bool)fixedValueArg, adjustMinMax);
            break;
            
        case MODPARAMTYPE_INT:
            setFixedValue ((int)fixedValueArg, adjustMinMax);
            break;
            
        default:
            // MODPARAMTYPE_FLOAT
            float inValClamped = ofClamp(fixedValueArg, hardMin_Float, hardMax_Float);
            if (adjustMinMax) {
                if (softMin_Float <= softMax_Float) {
                    if (softMin_Float > inValClamped) {
                        setSoftMin(inValClamped);
                    } else if (softMax_Float < inValClamped) {
                        setSoftMax(inValClamped);
                    };
                } else {
                    if (softMin_Float < inValClamped) {
                        setSoftMin(inValClamped);
                    } else if (softMax_Float > inValClamped) {
                        setSoftMax(inValClamped);
                    };
                };
            } else {
                inValClamped= ofClamp(fixedValueArg, softMin_Float, softMax_Float);
            };
            fixedValue_Float.set(inValClamped);
            break;
    }
};

void TXModParamFloat::setFixedModMix (float fixedModMixArg) {
    fixedModMix_Float.set(fixedModMixArg);
};

void TXModParamFloat::setSoftMin (float softMinArg) {
    softMin_Float.set(ofClamp(softMinArg, hardMin_Float, hardMax_Float));
    fixedValue_Float.setMin(softMin_Float);
};

void TXModParamFloat::setSoftMax (float softMaxArg) {
    softMax_Float.set(ofClamp(softMaxArg, hardMin_Float, hardMax_Float));
    fixedValue_Float.setMax(softMax_Float);
};

void TXModParamFloat::maximiseRangeSoftMinMax() {
    softMin_Float.set(hardMin_Float);
    softMax_Float.set(hardMax_Float);
};

void TXModParamFloat::setAutoScaleModSumming(bool autoScaleModSummingArg) {
    autoScaleModSumming.set(autoScaleModSummingArg);
};

