/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXWarp.h"

// properties

// constructor
TXWarp::TXWarp (int warpTypeArg, float inputMinArg, float inputMaxArg, float outputMinArg, float outputMaxArg, bool useQuantizeArg, int quantizeStepsArg) {
    setup (warpTypeArg, inputMinArg, inputMaxArg, outputMinArg, outputMaxArg, useQuantizeArg, quantizeStepsArg);
};

// methods
void TXWarp::setup (int warpTypeArg, float inputMinArg, float inputMaxArg, float outputMinArg, float outputMaxArg, bool useQuantizeArg, int quantizeStepsArg) {
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
    
    holdModParamFloatArgs.name = "inputValue";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 1.0;  // set full by default
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    inputValue = createModParameter(holdModParamFloatArgs);
    parameters.add(inputValue->parameters);

    holdModParamIntArgs.name = "warpType";
    holdModParamIntArgs.fixedValue = warpTypeArg;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalWarpTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalWarpTypes - 1;
	warpType = createModParameter(holdModParamIntArgs);
    parameters.add(warpType->parameters);
    
    holdModParamFloatArgs.name = "inputMin";
    holdModParamFloatArgs.fixedValue = inputMinArg;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    inputMin = createModParameter(holdModParamFloatArgs);
    parameters.add(inputMin->parameters);
    
    holdModParamFloatArgs.name = "inputMax";
    holdModParamFloatArgs.fixedValue = inputMaxArg;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    inputMax = createModParameter(holdModParamFloatArgs);
    parameters.add(inputMax->parameters);
    
    holdModParamFloatArgs.name = "outputMin";
    holdModParamFloatArgs.fixedValue = outputMinArg;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    outputMin = createModParameter(holdModParamFloatArgs);
    parameters.add(outputMin->parameters);
    
    holdModParamFloatArgs.name = "outputMax";
    holdModParamFloatArgs.fixedValue = outputMaxArg;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    outputMax = createModParameter(holdModParamFloatArgs);
    parameters.add(outputMax->parameters);
    
    holdModParamBoolArgs.name = "useQuantize";
    holdModParamBoolArgs.fixedValue = useQuantizeArg;
    useQuantize = createModParameter(holdModParamBoolArgs);
    parameters.add(useQuantize->parameters);
    
    holdModParamIntArgs.name = "quantizeSteps";
    holdModParamIntArgs.fixedValue = quantizeStepsArg;
    holdModParamIntArgs.hardMin = 2;
    holdModParamIntArgs.hardMax = 128;
    holdModParamIntArgs.softMin = 2;
    holdModParamIntArgs.softMax = 20;
	quantizeSteps = createModParameter(holdModParamIntArgs);
    parameters.add(quantizeSteps->parameters);
    
    customCurve.setValueArrayToRamp(0, 1);
    customCurve.setName("customCurve");
    parameters.add(customCurve.parameters);
    
    // create mod source output
    outValue = createModSource("out", 0);
};

// methods

//void  TXWarp:: setInputMin(float inputMinArg) {
//    inputMin = fmin(1, fmax(0, inputMinArg));
//    if (inputMax < inputMin) {
//        inputMax = inputMin;
//    };
//}
//void  TXWarp:: setInputMax(float inputMaxArg) {
//    inputMax = fmin(1, fmax(0, inputMaxArg));
//    if (inputMin > inputMax) {
//        inputMin = inputMax;
//    };
//}
//void  TXWarp:: setOutputMin(float outputMinArg) {
//    outputMin = fmin(1, fmax(0, outputMinArg));
//}
//void  TXWarp:: setOutputMax(float outputMaxArg) {
//    outputMax = fmin(1, fmax(0, outputMaxArg));
//}
//
//void  TXWarp:: setUseQuantize(bool useQuantizeArg){
//    useQuantize = useQuantizeArg;
//}
//
//void  TXWarp:: setQuantizeSteps(int quantizeStepsArg){
//    quantizeSteps = ofClamp(quantizeStepsArg, 2, 1000);
//}

void TXWarp::resetTime() {
    calculateOutput();
}

void TXWarp::advanceBy(float timeDeltaArg) {
    calculateOutput();
}

void TXWarp:: calculateOutput() {
    float inputMinAdjusted, inputMaxAdjusted, inLimit, scaleWarp, curveWarp;
    float holdOutputMin, holdOutputMax;
    int holdWarpType, holdQuantiseSteps;
    
    holdWarpType = warpType->getInt();
    holdQuantiseSteps = quantizeSteps->getInt();
    
    // avoid divide by zero error
    if (holdWarpType == TXWARPTYPE_EXPONENTIAL || (holdWarpType == TXWARPTYPE_MINUS_EXPONENTIAL)) {
        inputMinAdjusted = fmax(inputMin->getFloat(), 0.0001);
        inputMaxAdjusted = fmax(inputMax->getFloat(), 0.0001);
    } else {
        inputMinAdjusted = inputMin->getFloat();
        inputMaxAdjusted = inputMax->getFloat();
    };
    // apply limits
    inLimit = fmin(inputMaxAdjusted, fmax(inputMinAdjusted, inputValue->getFloat()) );	
    // scale to limits
    scaleWarp = (inLimit - inputMinAdjusted)  / fmax((inputMaxAdjusted - inputMinAdjusted), 0.001);	
    
    // Quantize
    if (useQuantize->getBool()) {
        scaleWarp = ((int) ((scaleWarp * (holdQuantiseSteps - 0.00001)) + (1/holdQuantiseSteps))) / (float) (holdQuantiseSteps - 1);
    }; 

    // apply curve 
    switch (holdWarpType) {
        case TXWARPTYPE_LINEAR:
            curveWarp = scaleWarp;
            break;
        case TXWARPTYPE_EXPONENTIAL:
            curveWarp = pow(10000, (scaleWarp-0.0001) / 0.9999) * 0.0001;
            break;                 
        case TXWARPTYPE_MINUS_EXPONENTIAL:
            curveWarp = 1 - (pow(10000, ((1-scaleWarp) - 0.0001) / 0.9999) * 0.0001);
            break;                 
        case TXWARPTYPE_5:
            curveWarp = pow(scaleWarp, 5);
            break;            
        case TXWARPTYPE_4:
            curveWarp = pow(scaleWarp, 4);
            break;            
        case TXWARPTYPE_3:
            curveWarp = pow(scaleWarp, 3);
            break;            
        case TXWARPTYPE_2:
            curveWarp = pow(scaleWarp, 2);
            break;            
        case TXWARPTYPE_MINUS_2:
            curveWarp = 1 - (pow((1-scaleWarp), 2));
            break;            
        case TXWARPTYPE_MINUS_3:
            curveWarp = 1 - (pow((1-scaleWarp), 3));
            break;            
        case TXWARPTYPE_MINUS_4:
            curveWarp = 1 - (pow((1-scaleWarp), 4));
            break;            
        case TXWARPTYPE_MINUS_5:
            curveWarp = 1 - (pow((1-scaleWarp), 5));
            break;            
        case TXWARPTYPE_PHASESHIFT_90:
            curveWarp = fmod(scaleWarp + 0.25, 1.0);
            break;            
        case TXWARPTYPE_PHASESHIFT_180:
            curveWarp = fmod(scaleWarp + 0.5, 1.0);
            break;            
        case TXWARPTYPE_PHASESHIFT_270:
            curveWarp = fmod(scaleWarp + 0.75, 1.0);
            break;
        case TXWARPTTYPE_CUSTOMCURVE:
            curveWarp = customCurve.interpolatedLookup(scaleWarp);
            break;
        default:
            // default is LINEAR
            curveWarp = scaleWarp;
            break;
    }
    // map to o/p range
    holdOutputMin = outputMin->getFloat();
    holdOutputMax = outputMax->getFloat();
    outValue->setValue(holdOutputMin + (curveWarp * (holdOutputMax - holdOutputMin)));
}


//NSMutableDictionary * TXWarp::getDictionary() {
//    NSMutableDictionary * dictionary;
//    dictionary = [NSMutableDictionary dictionary];
//    NSNumber * holdNum;
//    //add data
//    holdNum = [NSNumber numberWithInt:warpType];
//    [dictionary setObject: holdNum forKey: @"warpType"];
//    holdNum = [NSNumber numberWithFloat:inputMin];
//    [dictionary setObject: holdNum forKey: @"inputMin"];
//    holdNum = [NSNumber numberWithFloat:inputMax];
//    [dictionary setObject: holdNum forKey: @"inputMax"];
//    holdNum = [NSNumber numberWithFloat:outputMin];
//    [dictionary setObject: holdNum forKey: @"outputMin"];
//    holdNum = [NSNumber numberWithFloat:outputMax];
//    [dictionary setObject: holdNum forKey: @"outputMax"];
//    holdNum = [NSNumber numberWithBool:useQuantize];
//    [dictionary setObject: holdNum forKey: @"useQuantize"];
//    holdNum = [NSNumber numberWithInt:quantizeSteps];
//    [dictionary setObject: holdNum forKey: @"quantizeSteps"];
//
//    return dictionary;
//}
//
//void TXWarp::setFromDictionary(NSMutableDictionary * dictionaryArg) {
//    NSNumber * holdNum;
//    //get data
//    holdNum = [dictionaryArg objectForKey: @"warpType"];
//    if (holdNum != nil) {
//        setWarpType([holdNum intValue]);    
//    };
//    holdNum = [dictionaryArg objectForKey: @"inputMin"];
//    if (holdNum != nil) {
//        setInputMin([holdNum floatValue]);
//    };
//    holdNum = [dictionaryArg objectForKey: @"inputMax"];
//    if (holdNum != nil) {
//        setInputMax([holdNum floatValue]);
//    };
//    holdNum = [dictionaryArg objectForKey: @"outputMin"];
//    if (holdNum != nil) {
//        setOutputMin([holdNum floatValue]);
//    };
//    holdNum = [dictionaryArg objectForKey: @"outputMax"];
//    if (holdNum != nil) {
//        setOutputMax([holdNum floatValue]);
//    };
//    holdNum = [dictionaryArg objectForKey: @"useQuantize"];
//    if (holdNum != nil) {
//        setUseQuantize([holdNum boolValue]);
//    };
//    holdNum = [dictionaryArg objectForKey: @"quantizeSteps"];
//    if (holdNum != nil) {
//        setQuantizeSteps([holdNum intValue]);
//    };
//    
//}
//
