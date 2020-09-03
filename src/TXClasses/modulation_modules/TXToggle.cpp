/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXToggle.h"

// properties

// constructor
TXToggle::TXToggle (float startValArg){
    setup (startValArg);
};

// methods
void TXToggle::setup (float startValArg) {
    TXModParameterBoolArgs holdModParamBoolArgs;
//    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
    
    holdModParamFloatArgs.name = "inputValue";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    inputValue = createModParameter(holdModParamFloatArgs);
    parameters.add(inputValue->parameters);

    holdModParamFloatArgs.name = "triggerThreshold";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    triggerThreshold = createModParameter(holdModParamFloatArgs);
    parameters.add(triggerThreshold->parameters);
    
    holdModParamBoolArgs.name = "resetToZero";
    holdModParamBoolArgs.fixedValue = 0;
    resetToZero = createModParameter(holdModParamBoolArgs);
    parameters.add(resetToZero->parameters);
    
    // create mod source output
    outValue = createModSource("out", startValArg);
    
    inputPrevious = startValArg;
};

void TXToggle::resetTime() {
    calculateOutput();
}

void TXToggle::advanceBy(float timeDeltaArg) {
    calculateOutput();
}

void  TXToggle::calculateOutput(){
    float holdInput = inputValue->getFloat();
    if (resetToZero->getBool()) {
        outValue->setValue(0.0);
    } else {
        // toggle if rising above threshold
        float holdTrigThresh = triggerThreshold->getFloat();
        if ((inputPrevious < holdTrigThresh) && (holdInput >= holdTrigThresh)) {
            toggleValue();
        };
    };
    inputPrevious = holdInput;
}

void  TXToggle::toggleValue () {
    if (outValue->getValue() == 0.0) {
        outValue->setValue(1.0);
    } else {
        outValue->setValue(0.0);
    };
}

//NSMutableDictionary * TXToggle::getDictionary() {
//    NSMutableDictionary * dictionary;
//    dictionary = [NSMutableDictionary dictionary];
//    NSNumber * holdNum;
//    
//    //add data
//    holdNum = [NSNumber numberWithFloat:currentValue];
//    [dictionary setObject: holdNum forKey: @"currentValue"];
//    holdNum = [NSNumber numberWithFloat:triggerThreshold];
//    [dictionary setObject: holdNum forKey: @"triggerThreshold"];
//
//    return dictionary;
//}
//
//void TXToggle::setFromDictionary(NSMutableDictionary * dictionaryArg) {
//    NSNumber * holdNum;
//    
//    //get data
//    holdNum = [dictionaryArg objectForKey: @"currentValue"];
//    if (holdNum != nil) {
//        currentValue = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"triggerThreshold"];
//    if (holdNum != nil) {
//        setTriggerThreshold([holdNum floatValue]);    
//    };
//}
//
