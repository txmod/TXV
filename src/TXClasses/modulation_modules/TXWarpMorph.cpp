/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXWarpMorph.h"

// properties

// constructor
TXWarpMorph::TXWarpMorph (int warpTypeArg, int warpType2Arg, float warpTypeMorphArg, float inputMinArg, float inputMaxArg, float outputMinArg, float outputMaxArg, bool useQuantizeArg, int quantizeStepsArg) {
    setup (warpTypeArg, warpType2Arg, warpTypeMorphArg, inputMinArg, inputMaxArg, outputMinArg, outputMaxArg, useQuantizeArg, quantizeStepsArg);
};

// methods
void TXWarpMorph::setup (int warpTypeArg, int warpType2Arg, float warpTypeMorphArg, float inputMinArg, float inputMaxArg, float outputMinArg, float outputMaxArg, bool useQuantizeArg, int quantizeStepsArg) {
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
    
    holdModParamIntArgs.name = "warpType2";
    holdModParamIntArgs.fixedValue = warpTypeArg;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalWarpTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalWarpTypes - 1;
    warpType2 = createModParameter(holdModParamIntArgs);
    parameters.add(warpType2->parameters);
    
    holdModParamFloatArgs.name = "warpTypeMorph";
    holdModParamFloatArgs.fixedValue = warpTypeMorphArg;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    warpTypeMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(warpTypeMorph->parameters);
    
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
    
    customCurve2.setValueArrayToRamp(0, 1);
    customCurve2.setName("customCurve2");
    parameters.add(customCurve2.parameters);
    
    // create mod source output
    outValue = createModSource("out", 0);
};

// methods

//void  TXWarpMorph:: setInputMin(float inputMinArg) {
//    inputMin = fmin(1, fmax(0, inputMinArg));
//    if (inputMax < inputMin) {
//        inputMax = inputMin;
//    };
//}
//void  TXWarpMorph:: setInputMax(float inputMaxArg) {
//    inputMax = fmin(1, fmax(0, inputMaxArg));
//    if (inputMin > inputMax) {
//        inputMin = inputMax;
//    };
//}
//void  TXWarpMorph:: setOutputMin(float outputMinArg) {
//    outputMin = fmin(1, fmax(0, outputMinArg));
//}
//void  TXWarpMorph:: setOutputMax(float outputMaxArg) {
//    outputMax = fmin(1, fmax(0, outputMaxArg));
//}
//
//void  TXWarpMorph:: setUseQuantize(bool useQuantizeArg){
//    useQuantize = useQuantizeArg;
//}
//
//void  TXWarpMorph:: setQuantizeSteps(int quantizeStepsArg){
//    quantizeSteps = ofClamp(quantizeStepsArg, 2, 1000);
//}

void TXWarpMorph::resetTime() {
    calculateOutput();
}

void TXWarpMorph::advanceBy(float timeDeltaArg) {
    calculateOutput();
}

void TXWarpMorph:: calculateOutput() {
    float inputMinAdjusted, inputMaxAdjusted, inLimit, scaleWarp, curveWarp, curveWarp2;
    float holdOutputMin, holdOutputMax, holdWarpTypeMorph;
    int holdWarpType, holdWarpType2, holdQuantiseSteps;
    
    holdWarpType = warpType->getInt();
    holdWarpType2 = warpType2->getInt();
    holdWarpTypeMorph = warpTypeMorph->getFloat();
    holdQuantiseSteps = quantizeSteps->getInt();
    
    // avoid divide by zero error
    if (holdWarpType == TXWARPMORPHTYPE_EXPONENTIAL || (holdWarpType == TXWARPMORPHTYPE_MINUS_EXPONENTIAL)
        || holdWarpType2 == TXWARPMORPHTYPE_EXPONENTIAL || (holdWarpType2 == TXWARPMORPHTYPE_MINUS_EXPONENTIAL)) {
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

    // apply curves
    if (holdWarpTypeMorph == 0.0) {
        curveWarp = applyCurve(holdWarpType, scaleWarp);
    } else if (holdWarpTypeMorph == 1.0) {
        curveWarp = applyCurve(holdWarpType2, scaleWarp);
    } else {
        curveWarp = ofLerp(applyCurve(holdWarpType, scaleWarp), applyCurve(holdWarpType2, scaleWarp), holdWarpTypeMorph) ;
    };
    // map to o/p range
    holdOutputMin = outputMin->getFloat();
    holdOutputMax = outputMax->getFloat();
    outValue->setValue(holdOutputMin + (curveWarp * (holdOutputMax - holdOutputMin)));
}

float TXWarpMorph:: applyCurve(int curveType, float inVal) {
    float outVal;
    switch (curveType) {
        case TXWARPMORPHTYPE_LINEAR:
            outVal = inVal;
            break;
        case TXWARPMORPHTYPE_EXPONENTIAL:
            outVal = pow(10000, (inVal-0.0001) / 0.9999) * 0.0001;
            break;
        case TXWARPMORPHTYPE_MINUS_EXPONENTIAL:
            outVal = 1 - (pow(10000, ((1-inVal) - 0.0001) / 0.9999) * 0.0001);
            break;
        case TXWARPMORPHTYPE_5:
            outVal = pow(inVal, 5);
            break;
        case TXWARPMORPHTYPE_4:
            outVal = pow(inVal, 4);
            break;
        case TXWARPMORPHTYPE_3:
            outVal = pow(inVal, 3);
            break;
        case TXWARPMORPHTYPE_2:
            outVal = pow(inVal, 2);
            break;
        case TXWARPMORPHTYPE_MINUS_2:
            outVal = 1 - (pow((1-inVal), 2));
            break;
        case TXWARPMORPHTYPE_MINUS_3:
            outVal = 1 - (pow((1-inVal), 3));
            break;
        case TXWARPMORPHTYPE_MINUS_4:
            outVal = 1 - (pow((1-inVal), 4));
            break;
        case TXWARPMORPHTYPE_MINUS_5:
            outVal = 1 - (pow((1-inVal), 5));
            break;
        case TXWARPMORPHTYPE_PHASESHIFT_90:
            outVal = fmod(inVal + 0.25, 1.0);
            break;
        case TXWARPMORPHTYPE_PHASESHIFT_180:
            outVal = fmod(inVal + 0.5, 1.0);
            break;
        case TXWARPMORPHTYPE_PHASESHIFT_270:
            outVal = fmod(inVal + 0.75, 1.0);
            break;
        case TXWARPMORPHTYPE_CUSTOMCURVE:
            outVal = customCurve.interpolatedLookup(inVal);
            break;
        case TXWARPMORPHTYPE_CUSTOMCURVE2:
            outVal = customCurve2.interpolatedLookup(inVal);
            break;
        default:
            // default is LINEAR
            outVal = inVal;
            break;
    }
    return outVal;
}

//NSMutableDictionary * TXWarpMorph::getDictionary() {
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
//void TXWarpMorph::setFromDictionary(NSMutableDictionary * dictionaryArg) {
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
