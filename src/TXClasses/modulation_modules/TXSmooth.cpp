/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXSmooth.h"

// properties

// constructor
TXSmooth::TXSmooth (int smoothTypeArg, float smooothTimeArg, float outValueArg, float targetValueArg, bool circularSmoothingArg) {
    setup (smoothTypeArg, smooothTimeArg, outValueArg, targetValueArg, circularSmoothingArg);
};

// destructor
TXSmooth::~TXSmooth () {
}

// methods
void TXSmooth::setup (int smoothTypeArg, float smooothTimeArg, float outValueArg, float targetValueArg, bool circularSmoothingArg) {
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();

    holdModParamIntArgs.name = "smoothType";
    holdModParamIntArgs.fixedModMix = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 1;
	smoothType = createModParameter(holdModParamIntArgs);
    parameters.add(smoothType->parameters);
    
    holdModParamFloatArgs.name = "targetValue";
    holdModParamFloatArgs.fixedModMix = 1.0;  // set full by default
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    targetValue = createModParameter(holdModParamFloatArgs);
    parameters.add(targetValue->parameters);

    holdModParamFloatArgs.name = "smoothTime";
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 60;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10;
	smoothTime = createModParameter(holdModParamFloatArgs);
    parameters.add(smoothTime->parameters);
    
    holdModParamBoolArgs.name = "circularSmoothing";
    holdModParamBoolArgs.fixedModMix = false;
    circularSmoothing = createModParameter(holdModParamBoolArgs);
    parameters.add(circularSmoothing->parameters);
    
    // create mod source output
    outValue = createModSource("out", outValueArg);
    
    smoothType->setFixedValue(smoothTypeArg);
	smoothTime->setFixedValue(smooothTimeArg);
    targetValue->setFixedValue(targetValueArg);
    circularSmoothing->setFixedValue(circularSmoothingArg);
//    currentTime = 0.0;
//    resetLinearRate();
};

void  TXSmooth::update() {
    smoothVal.setSmoothType(smoothType->getInt());
    smoothVal.setTargetValue(targetValue->getFloat());
    smoothVal.setSmoothTime(smoothTime->getFloat());
    smoothVal.circularSmoothing = circularSmoothing->getBool();
    outValue->setValue(smoothVal.outValue);
}

void TXSmooth::setTime(float timeArg){
    smoothVal.setTime(timeArg);
    
}

void TXSmooth::advanceBy(float timeDeltaArg) {
    smoothVal.advanceBy(timeDeltaArg);
}

float TXSmooth::getValue() {
    return outValue->getValue();
}

float TXSmooth::getValueAt(float timeArg){
    setTime(timeArg);    
    return this->getValue();
}
//ofPtr<TXModParameter> TXSmooth::getSmoothType(){
//    return smoothType;
//} 
//
//void  TXSmooth::setSmoothTypeFixed(int smoothTypeArg){
//    if (smoothType->getFixedValueInt() != smoothTypeArg) {
//        smoothType->setFixedValue(smoothTypeArg);
//    };
//}
//
//ofPtr<TXModParameter>  TXSmooth::getSmoothTime(){
//    return smoothTime;
//} 
//
//void  TXSmooth::setSmoothTimeFixed(float smoothTimeArg){
//    if (smoothTime->getFixedValueFloat() != smoothTimeArg) {
//        smoothTime->setFixedValue(smoothTimeArg);
//    };
//}
//
//ofPtr<TXModParameter>  TXSmooth::getTargetValue(){
//    return targetValue;
//} 
//
//void TXSmooth::setTargetValueFixed(float targetValueArg){
//    if (targetValue->getFixedValueFloat() != targetValueArg) {
//        targetValue->setFixedValue(targetValueArg);
//    }
//}
//
//void  TXSmooth::setCircularSmoothingFixed(bool circularSmoothingArg) {
//    circularSmoothing->setFixedValue(circularSmoothingArg);
//}

//ofPtr<TXModParameter>  TXSmooth::getCircularSmoothing(){
//    return circularSmoothing;
//}


float TXSmooth::getOutValue() {
    return outValue->getValue();
} 

void  TXSmooth::setOutValue(float outValueArg) {
    outValue->setValue(outValueArg);
}

void  TXSmooth::resetTime() {
    outValue->setValue(targetValue->getFloat());
//    currentTime = 0.0;
//    resetLinearRate();
    smoothVal.resetTime();
}

//NSMutableDictionary * TXSmooth::getDictionary() {
//    NSMutableDictionary * dictionary;
//    dictionary = [NSMutableDictionary dictionary];
//    //add data
//    [dictionary setObject: smoothTime->getDictionary() forKey: @"smoothTime"];
//    [dictionary setObject: targetValue->getDictionary() forKey: @"targetValue"];
//    [dictionary setObject: circularSmoothing->getDictionary() forKey: @"circularSmoothing"];
//    [dictionary setObject: smoothType->getDictionary() forKey: @"smoothType"];
//    return dictionary;
//}
//
//void TXSmooth::setFromDictionary(NSMutableDictionary * dictionaryArg) {
//    NSMutableDictionary * holdDictionary;
//    //get data
//    holdDictionary = [dictionaryArg objectForKey: @"smoothTime"];
//    if (holdDictionary != nil) {
//        smoothTime->setFromDictionary(holdDictionary);
//    };
//    holdDictionary = [dictionaryArg objectForKey: @"targetValue"];
//    if (holdDictionary != nil) {
//        targetValue->setFromDictionary(holdDictionary);
//    };
//    holdDictionary = [dictionaryArg objectForKey: @"circularSmoothing"];
//    if (holdDictionary != nil) {
//        circularSmoothing->setFromDictionary(holdDictionary);
//    };
//    holdDictionary = [dictionaryArg objectForKey: @"smoothType"];
//    if (holdDictionary != nil) {
//        smoothType->setFromDictionary(holdDictionary);
//    };
//}

