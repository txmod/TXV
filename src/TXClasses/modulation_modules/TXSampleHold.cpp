/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXSampleHold.h"

// properties

// constructor
TXSampleHold::TXSampleHold (float startValArg, bool holdArg, bool bypassArg){
    setup (startValArg, holdArg, bypassArg);
};

// methods
void TXSampleHold::setup (float startValArg, float holdArg, bool bypassArg) {
    TXModParameterBoolArgs holdModParamBoolArgs;
//    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
    
    holdModParamFloatArgs.name = "inputValue";
    holdModParamFloatArgs.fixedModMix = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    inputValue = createModParameter(holdModParamFloatArgs);
    parameters.add(inputValue->parameters);

    holdModParamBoolArgs.name = "hold";
    holdModParamBoolArgs.fixedValue = holdArg;
    hold = createModParameter(holdModParamBoolArgs);
    parameters.add(hold->parameters);
    
    holdModParamBoolArgs.name = "bypass";
    holdModParamBoolArgs.fixedValue = bypassArg;
    bypass = createModParameter(holdModParamBoolArgs);
    parameters.add(bypass->parameters);
    
    // create mod source output
    outValue = createModSource("out", startValArg);

	holdValue = startValArg;
};

void TXSampleHold::resetTime() {
    calculateOutput();
}

void TXSampleHold::advanceBy(float timeDeltaArg) {
    calculateOutput();
}

void TXSampleHold::calculateOutput() {
    if ( (! bypass->getBool()) && hold->getBool()) {
        outValue->setValue(holdValue);
    } else {
        holdValue = inputValue->getFloat();
        outValue->setValue(holdValue);
    };
}

//void TXSampleHold::setHold (bool holdArg) {
//	hold = holdArg;
//};
//
//void TXSampleHold::setHoldF (float holdArg) {
//    if (holdArg < 0.5) {
//        hold = false;
//    } else {
//        if (! hold) {
//            holdValue = currentValue;
//        };
//        hold = true;
//    };
//};
//
//void TXSampleHold::setBypass (bool bypassArg) {
//	bypass = bypassArg;
//};

//bool TXSampleHold::getHold() {
//	return hold;
//};
//
//bool TXSampleHold::getBypass() {
//	return bypass;
//}; 

//NSMutableDictionary * TXSampleHold::getDictionary() {
//    NSMutableDictionary * dictionary;
//    dictionary = [NSMutableDictionary dictionary];
//    NSNumber * holdNum;
//    //add data
//    holdNum = [NSNumber numberWithFloat:currentValue];
//    [dictionary setObject: holdNum forKey: @"currentValue"];
//    holdNum = [NSNumber numberWithFloat:holdValue];
//    [dictionary setObject: holdNum forKey: @"holdValue"];
//
//    holdNum = [NSNumber numberWithBool:hold];
//    [dictionary setObject: holdNum forKey: @"hold"];
//    holdNum = [NSNumber numberWithBool:bypass];
//    [dictionary setObject: holdNum forKey: @"bypass"];
//    
//    return dictionary;
//}
//
//void TXSampleHold::setFromDictionary(NSMutableDictionary * dictionaryArg) {
//    NSNumber * holdNum;
//    //get data
//    holdNum = [dictionaryArg objectForKey: @"currentValue"];
//    if (holdNum != nil) {
//        currentValue = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"holdValue"];
//    if (holdNum != nil) {
//        holdValue = [holdNum floatValue];
//    };
//
//    holdNum = [dictionaryArg objectForKey: @"hold"];
//    if (holdNum != nil) {
//        hold = [holdNum boolValue];    
//    };
//    holdNum = [dictionaryArg objectForKey: @"bypass"];
//    if (holdNum != nil) {
//        bypass = [holdNum boolValue];    
//    };
//
//}
//
