/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXPerlin.h"
#include "TXSystem.h"

// properties

// constructor
TXPerlin::TXPerlin (int perlinTypeArg, float speedArg, float speedDivisorArg, float phaseOffsetArg, bool useMasterBpmArg, bool frozenArg){
    setup (perlinTypeArg, speedArg, speedDivisorArg, phaseOffsetArg, useMasterBpmArg, frozenArg);
};

// methods
void TXPerlin::setup (int perlinTypeArg, float speedArg, float speedDivisorArg, float phaseOffsetArg, bool useMasterBpmArg, bool frozenArg) {
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
    
    holdModParamIntArgs.name = "perlinType";
    holdModParamIntArgs.fixedValue = perlinTypeArg;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalPerlinTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalPerlinTypes - 1;
	perlinType = createModParameter(holdModParamIntArgs);
    parameters.add(perlinType->parameters);
    
    holdModParamFloatArgs.name = "speed";
    holdModParamFloatArgs.fixedValue = speedArg;
    holdModParamFloatArgs.hardMin = 0.001;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.01;
    holdModParamFloatArgs.softMax = 10.0;
	speed = createModParameter(holdModParamFloatArgs);
    parameters.add(speed->parameters);
    
    holdModParamBoolArgs.name = "useMasterBpm";
    holdModParamBoolArgs.fixedValue = useMasterBpmArg;
	useMasterBpm = createModParameter(holdModParamBoolArgs);
    parameters.add(useMasterBpm->parameters);
    
    holdModParamFloatArgs.name = "speedDivisor";
    holdModParamFloatArgs.fixedValue = speedDivisorArg;
    holdModParamFloatArgs.hardMin = 0.01;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 1.0;
    holdModParamFloatArgs.softMax = 64.0;
	speedDivisor = createModParameter(holdModParamFloatArgs);
    parameters.add(speedDivisor->parameters);
    
    holdModParamBoolArgs.name = "frozen";
    holdModParamBoolArgs.fixedValue = frozenArg;
	frozen = createModParameter(holdModParamBoolArgs);
    parameters.add(frozen->parameters);
    
    // create mod source output
    outValue = createModSource("out", 0);
    
    phase = 0.0;
    currentTime = 0.0;
    accumlator = 0.0;
    flipper = 1.0;
};

void TXPerlin::setTime(float timeArg){
	float holdPhase;
    float holdSpeed, holdSpeedDivisor;
    if (frozen->getBool()) {
        return;
    };
    if (useMasterBpm->getBool()) {
        holdSpeed = masterBpm / 60;
    } else {
        holdSpeed = speed->getFloat();
    };
    currentTime = timeArg;
    // speed is slowed by factor of 10 (looks best)
    holdSpeedDivisor = 10 * fmax(speedDivisor->getFloat(), 0.001);
    holdPhase = timeArg * holdSpeed / holdSpeedDivisor;
    phase = fmod(holdPhase, 1.0f);
    calculateOutput();
}

void TXPerlin::advanceBy(float timeDeltaArg) {
//	float holdPhase;
    float holdSpeed, holdSpeedDivisor;
    if (frozen->getBool()) {
        return;
    };
    if (useMasterBpm->getBool()) {
        holdSpeed = masterBpm / 60;
    } else {
        holdSpeed = speed->getFloat();
    };
    currentTime += timeDeltaArg;
    holdSpeedDivisor = fmax(speedDivisor->getFloat(), 0.001);
    phase = (phase + (timeDeltaArg * holdSpeed / holdSpeedDivisor));
    calculateOutput();
}

float TXPerlin::getValue() {
    return outValue->getValue();
}

void TXPerlin::calculateOutput() {
    float holdVal, holdSpeed, holdPerlin;
    int holdSign;
    switch (perlinType->getInt()) {
            
        case PERLINTYPE_NORMAL:
            holdVal = ofSignedNoise(phase);
            holdVal = (holdVal + 1) / 2;
            outValue->setValue(holdVal);
            break;
        case PERLINTYPE_QUANTISED:
            holdVal = ofSignedNoise(phase);
            holdVal = (holdVal + 1) / 2;
            if (holdVal < 0.5) {
                holdVal = 0;
            } else {
                holdVal = 1;
            }
            outValue->setValue(holdVal);
            break;
            
            //  no longer used
//        case PERLINTYPE_SQUARED:
//            holdVal = ofSignedNoise(phase);
//            if (holdVal < 0) {holdSign = -1;} else {holdSign = 1;};
//            holdVal = pow(abs(holdVal), 0.5f) * holdSign;
//            holdVal = (holdVal + 1) / 2;
//            outValue->setValue(holdVal);
//            break;
//        case PERLINTYPE_RANDOMWALK:   // NOTE PERLINTYPE_RANDOMWALK IS v SIMILAR TO ORIGINAL PERLINTYPE_NORMAL
//            if (useMasterBpm->getBool()) {
//                holdSpeed = masterBpm / (60 * speedDivisor->getFloat());
//            } else {
//                holdSpeed = speed->getFloat()/ speedDivisor->getFloat();
//            };
//            holdPerlin = ofSignedNoise(phase) / 5;
//            if ( ((accumlator + (holdPerlin * flipper)) > 1) || ((accumlator + (holdPerlin * flipper)) < 0)) {
//                flipper = flipper * -1;
//            };
//            accumlator += (holdPerlin * flipper);
//            outValue->setValue(accumlator);
//            break;
            
        default:
            return;
            break;
    }
}

//NSMutableDictionary * TXPerlin::getDictionary() {
//    NSMutableDictionary * dictionary;
//    dictionary = [NSMutableDictionary dictionary];
//    NSNumber * holdNum;
//    //add data
//    holdNum = [NSNumber numberWithInt:perlinType];
//    [dictionary setObject: holdNum forKey: @"perlinType"];
//    holdNum = [NSNumber numberWithFloat:speed];
//    [dictionary setObject: holdNum forKey: @"speed"];
//    holdNum = [NSNumber numberWithFloat:speedDivisor];
//    [dictionary setObject: holdNum forKey: @"speedDivisor"];
//    holdNum = [NSNumber numberWithFloat:phaseOffset];
//    [dictionary setObject: holdNum forKey: @"phaseOffset"];
//    holdNum = [NSNumber numberWithBool:useMasterBpm];
//    [dictionary setObject: holdNum forKey: @"useMasterBpm"];
//    return dictionary;
//}
//
//void TXPerlin::setFromDictionary(NSMutableDictionary * dictionaryArg) {
//    NSNumber * holdNum;
//    //get data
//    holdNum = [dictionaryArg objectForKey: @"perlinType"];
//    if (holdNum != nil) {
//        perlinType = [holdNum intValue];    
//    };
//    holdNum = [dictionaryArg objectForKey: @"speed"];
//    if (holdNum != nil) {
//        speed = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"speedDivisor"];
//    if (holdNum != nil) {
//        speedDivisor = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"phaseOffset"];
//    if (holdNum != nil) {
//        phaseOffset = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"useMasterBpm"];
//    if (holdNum != nil) {
//        useMasterBpm = [holdNum boolValue];    
//    };
//}


