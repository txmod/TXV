/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXSmoothMulti.h"

// properties

// constructor
TXSmoothMulti::TXSmoothMulti () {
    setup ();
};

// destructor
TXSmoothMulti::~TXSmoothMulti () {
}

// methods
void TXSmoothMulti::setup () {
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();

    holdModParamIntArgs.name = "smoothType";
    holdModParamFloatArgs.fixedValue = TXSMOOTHTYPE_EXPONENTIAL;
    holdModParamIntArgs.fixedModMix = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 1;
	smoothType = createModParameter(holdModParamIntArgs);
    parameters.add(smoothType->parameters);
    
    holdModParamFloatArgs.name = "smoothTime";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 60;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10;
	smoothTime = createModParameter(holdModParamFloatArgs);
    parameters.add(smoothTime->parameters);
    
    holdModParamFloatArgs.name = "targetValue1";
    holdModParamFloatArgs.fixedValue = 0;
    holdModParamFloatArgs.fixedModMix = 1.0;  // set full by default
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    targetValue1 = createModParameter(holdModParamFloatArgs);
    parameters.add(targetValue1->parameters);
    
    holdModParamBoolArgs.name = "circularSmoothing1";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
    circularSmoothing1 = createModParameter(holdModParamBoolArgs);
    parameters.add(circularSmoothing1->parameters);
    
    holdModParamFloatArgs.name = "targetValue2";
    holdModParamFloatArgs.fixedValue = 0;
    holdModParamFloatArgs.fixedModMix = 1.0;  // set full by default
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    targetValue2 = createModParameter(holdModParamFloatArgs);
    parameters.add(targetValue2->parameters);
    
    holdModParamBoolArgs.name = "circularSmoothing2";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
    circularSmoothing2 = createModParameter(holdModParamBoolArgs);
    parameters.add(circularSmoothing2->parameters);
    
    
    holdModParamFloatArgs.name = "targetValue3";
    holdModParamFloatArgs.fixedValue = 0;
    holdModParamFloatArgs.fixedModMix = 1.0;  // set full by default
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    targetValue3 = createModParameter(holdModParamFloatArgs);
    parameters.add(targetValue3->parameters);
    
    holdModParamBoolArgs.name = "circularSmoothing3";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
    circularSmoothing3 = createModParameter(holdModParamBoolArgs);
    parameters.add(circularSmoothing3->parameters);
    
    holdModParamFloatArgs.name = "targetValue4";
    holdModParamFloatArgs.fixedValue = 0;
    holdModParamFloatArgs.fixedModMix = 1.0;  // set full by default
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    targetValue4 = createModParameter(holdModParamFloatArgs);
    parameters.add(targetValue4->parameters);
    
    holdModParamBoolArgs.name = "circularSmoothing4";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
    circularSmoothing4 = createModParameter(holdModParamBoolArgs);
    parameters.add(circularSmoothing4->parameters);
    
    holdModParamFloatArgs.name = "targetValue5";
    holdModParamFloatArgs.fixedValue = 0;
    holdModParamFloatArgs.fixedModMix = 1.0;  // set full by default
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    targetValue5 = createModParameter(holdModParamFloatArgs);
    parameters.add(targetValue5->parameters);
    
    holdModParamBoolArgs.name = "circularSmoothing5";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
    circularSmoothing5 = createModParameter(holdModParamBoolArgs);
    parameters.add(circularSmoothing5->parameters);
    
    holdModParamFloatArgs.name = "targetValue6";
    holdModParamFloatArgs.fixedValue = 0;
    holdModParamFloatArgs.fixedModMix = 1.0;  // set full by default
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    targetValue6 = createModParameter(holdModParamFloatArgs);
    parameters.add(targetValue6->parameters);
    
    holdModParamBoolArgs.name = "circularSmoothing6";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
    circularSmoothing6 = createModParameter(holdModParamBoolArgs);
    parameters.add(circularSmoothing6->parameters);
    
    holdModParamFloatArgs.name = "targetValue7";
    holdModParamFloatArgs.fixedValue = 0;
    holdModParamFloatArgs.fixedModMix = 1.0;  // set full by default
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    targetValue7 = createModParameter(holdModParamFloatArgs);
    parameters.add(targetValue7->parameters);
    
    holdModParamBoolArgs.name = "circularSmoothing7";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
    circularSmoothing7 = createModParameter(holdModParamBoolArgs);
    parameters.add(circularSmoothing7->parameters);
    
    holdModParamFloatArgs.name = "targetValue8";
    holdModParamFloatArgs.fixedValue = 0;
    holdModParamFloatArgs.fixedModMix = 1.0;  // set full by default
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    targetValue8 = createModParameter(holdModParamFloatArgs);
    parameters.add(targetValue8->parameters);
    
    holdModParamBoolArgs.name = "circularSmoothing8";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
    circularSmoothing8 = createModParameter(holdModParamBoolArgs);
    parameters.add(circularSmoothing8->parameters);
    
    holdModParamFloatArgs.name = "targetValue9";
    holdModParamFloatArgs.fixedValue = 0;
    holdModParamFloatArgs.fixedModMix = 1.0;  // set full by default
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    targetValue9 = createModParameter(holdModParamFloatArgs);
    parameters.add(targetValue9->parameters);
    
    holdModParamBoolArgs.name = "circularSmoothing9";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
    circularSmoothing9 = createModParameter(holdModParamBoolArgs);
    parameters.add(circularSmoothing9->parameters);
    
    holdModParamFloatArgs.name = "targetValue10";
    holdModParamFloatArgs.fixedValue = 0;
    holdModParamFloatArgs.fixedModMix = 1.0;  // set full by default
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    targetValue10 = createModParameter(holdModParamFloatArgs);
    parameters.add(targetValue10->parameters);
    
    holdModParamBoolArgs.name = "circularSmoothing10";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
    circularSmoothing10 = createModParameter(holdModParamBoolArgs);
    parameters.add(circularSmoothing10->parameters);
    
    holdModParamFloatArgs.name = "targetValue11";
    holdModParamFloatArgs.fixedValue = 0;
    holdModParamFloatArgs.fixedModMix = 1.0;  // set full by default
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    targetValue11 = createModParameter(holdModParamFloatArgs);
    parameters.add(targetValue11->parameters);
    
    holdModParamBoolArgs.name = "circularSmoothing11";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
    circularSmoothing11 = createModParameter(holdModParamBoolArgs);
    parameters.add(circularSmoothing11->parameters);
    
    holdModParamFloatArgs.name = "targetValue12";
    holdModParamFloatArgs.fixedValue = 0;
    holdModParamFloatArgs.fixedModMix = 1.0;  // set full by default
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    targetValue12 = createModParameter(holdModParamFloatArgs);
    parameters.add(targetValue12->parameters);
    
    holdModParamBoolArgs.name = "circularSmoothing12";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
    circularSmoothing12 = createModParameter(holdModParamBoolArgs);
    parameters.add(circularSmoothing12->parameters);
    
    // create mod source output
    outValue1 = createModSource("out1", 0);
    outValue2 = createModSource("out2", 0);
    outValue3 = createModSource("out3", 0);
    outValue4 = createModSource("out4", 0);
    outValue5 = createModSource("out5", 0);
    outValue6 = createModSource("out6", 0);
    outValue7 = createModSource("out7", 0);
    outValue8 = createModSource("out8", 0);
    outValue9 = createModSource("out9", 0);
    outValue10 = createModSource("out10", 0);
    outValue11 = createModSource("out11", 0);
    outValue12 = createModSource("out12", 0);
    
};

void  TXSmoothMulti::update() {
    int holdSmoothType = smoothType->getInt();
    float holdSmoothTime = smoothTime->getFloat();
    smoothVal1.setSmoothType(holdSmoothType);
    smoothVal2.setSmoothType(holdSmoothType);
    smoothVal3.setSmoothType(holdSmoothType);
    smoothVal4.setSmoothType(holdSmoothType);
    smoothVal5.setSmoothType(holdSmoothType);
    smoothVal6.setSmoothType(holdSmoothType);
    smoothVal7.setSmoothType(holdSmoothType);
    smoothVal8.setSmoothType(holdSmoothType);
    smoothVal9.setSmoothType(holdSmoothType);
    smoothVal10.setSmoothType(holdSmoothType);
    smoothVal11.setSmoothType(holdSmoothType);
    smoothVal12.setSmoothType(holdSmoothType);

    smoothVal1.setSmoothTime(holdSmoothTime);
    smoothVal2.setSmoothTime(holdSmoothTime);
    smoothVal3.setSmoothTime(holdSmoothTime);
    smoothVal4.setSmoothTime(holdSmoothTime);
    smoothVal5.setSmoothTime(holdSmoothTime);
    smoothVal6.setSmoothTime(holdSmoothTime);
    smoothVal7.setSmoothTime(holdSmoothTime);
    smoothVal8.setSmoothTime(holdSmoothTime);
    smoothVal9.setSmoothTime(holdSmoothTime);
    smoothVal10.setSmoothTime(holdSmoothTime);
    smoothVal11.setSmoothTime(holdSmoothTime);
    smoothVal12.setSmoothTime(holdSmoothTime);

    smoothVal1.setTargetValue(targetValue1->getFloat());
    smoothVal2.setTargetValue(targetValue2->getFloat());
    smoothVal3.setTargetValue(targetValue3->getFloat());
    smoothVal4.setTargetValue(targetValue4->getFloat());
    smoothVal5.setTargetValue(targetValue5->getFloat());
    smoothVal6.setTargetValue(targetValue6->getFloat());
    smoothVal7.setTargetValue(targetValue7->getFloat());
    smoothVal8.setTargetValue(targetValue8->getFloat());
    smoothVal9.setTargetValue(targetValue9->getFloat());
    smoothVal10.setTargetValue(targetValue10->getFloat());
    smoothVal11.setTargetValue(targetValue11->getFloat());
    smoothVal12.setTargetValue(targetValue12->getFloat());

    smoothVal1.circularSmoothing = circularSmoothing1->getBool();
    smoothVal2.circularSmoothing = circularSmoothing2->getBool();
    smoothVal3.circularSmoothing = circularSmoothing3->getBool();
    smoothVal4.circularSmoothing = circularSmoothing4->getBool();
    smoothVal5.circularSmoothing = circularSmoothing5->getBool();
    smoothVal6.circularSmoothing = circularSmoothing6->getBool();
    smoothVal7.circularSmoothing = circularSmoothing7->getBool();
    smoothVal8.circularSmoothing = circularSmoothing8->getBool();
    smoothVal9.circularSmoothing = circularSmoothing9->getBool();
    smoothVal10.circularSmoothing = circularSmoothing10->getBool();
    smoothVal11.circularSmoothing = circularSmoothing11->getBool();
    smoothVal12.circularSmoothing = circularSmoothing12->getBool();
    
    outValue1->setValue(smoothVal1.outValue);
    outValue2->setValue(smoothVal2.outValue);
    outValue3->setValue(smoothVal3.outValue);
    outValue4->setValue(smoothVal4.outValue);
    outValue5->setValue(smoothVal5.outValue);
    outValue6->setValue(smoothVal6.outValue);
    outValue7->setValue(smoothVal7.outValue);
    outValue8->setValue(smoothVal8.outValue);
    outValue9->setValue(smoothVal9.outValue);
    outValue10->setValue(smoothVal10.outValue);
    outValue11->setValue(smoothVal11.outValue);
    outValue12->setValue(smoothVal12.outValue);
}

void TXSmoothMulti::setTime(float timeArg){
    smoothVal1.setTime(timeArg);
    smoothVal2.setTime(timeArg);
    smoothVal3.setTime(timeArg);
    smoothVal4.setTime(timeArg);
    smoothVal5.setTime(timeArg);
    smoothVal6.setTime(timeArg);
    smoothVal7.setTime(timeArg);
    smoothVal8.setTime(timeArg);
    smoothVal9.setTime(timeArg);
    smoothVal10.setTime(timeArg);
    smoothVal11.setTime(timeArg);
    smoothVal12.setTime(timeArg);
    
}

void TXSmoothMulti::advanceBy(float timeDeltaArg) {
    smoothVal1.advanceBy(timeDeltaArg);
    smoothVal2.advanceBy(timeDeltaArg);
    smoothVal3.advanceBy(timeDeltaArg);
    smoothVal4.advanceBy(timeDeltaArg);
    smoothVal5.advanceBy(timeDeltaArg);
    smoothVal6.advanceBy(timeDeltaArg);
    smoothVal7.advanceBy(timeDeltaArg);
    smoothVal8.advanceBy(timeDeltaArg);
    smoothVal9.advanceBy(timeDeltaArg);
    smoothVal10.advanceBy(timeDeltaArg);
    smoothVal11.advanceBy(timeDeltaArg);
    smoothVal12.advanceBy(timeDeltaArg);
}

void  TXSmoothMulti::resetTime() {
    //outValue->setValue(targetValue->getFloat());
    outValue1->setValue(targetValue1->getFloat());
    outValue2->setValue(targetValue2->getFloat());
    outValue3->setValue(targetValue3->getFloat());
    outValue4->setValue(targetValue4->getFloat());
    outValue5->setValue(targetValue5->getFloat());
    outValue6->setValue(targetValue6->getFloat());
    outValue7->setValue(targetValue7->getFloat());
    outValue8->setValue(targetValue8->getFloat());
    outValue9->setValue(targetValue9->getFloat());
    outValue10->setValue(targetValue10->getFloat());
    outValue11->setValue(targetValue11->getFloat());
    outValue12->setValue(targetValue12->getFloat());

    smoothVal1.resetTime();
    smoothVal2.resetTime();
    smoothVal3.resetTime();
    smoothVal4.resetTime();
    smoothVal5.resetTime();
    smoothVal6.resetTime();
    smoothVal7.resetTime();
    smoothVal8.resetTime();
    smoothVal9.resetTime();
    smoothVal10.resetTime();
    smoothVal11.resetTime();
    smoothVal12.resetTime();
}

//NSMutableDictionary * TXSmoothMulti::getDictionary() {
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
//void TXSmoothMulti::setFromDictionary(NSMutableDictionary * dictionaryArg) {
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

