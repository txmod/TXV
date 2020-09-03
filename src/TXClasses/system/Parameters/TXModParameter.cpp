/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXModParameter.h"

// properties

// constructor
TXModParameter::TXModParameter(){
     // DEFAULT
};

// methods

void TXModParameter::addListener() {
    // remove listeners to relevent mod parameters:
    ofAddListener(parameters.parameterChangedE(),this,&TXModParameter::parametersChanged);
}

void TXModParameter::removeListener() {
    // remove listeners to relevent mod parameters:
    ofRemoveListener(parameters.parameterChangedE(),this,&TXModParameter::parametersChanged);
}

void  TXModParameter::parametersChanged(ofAbstractParameter & parameterArg ) {
    hasChanged = true;
}

string TXModParameter::getName() {
    return name;
}

void TXModParameter::setName(string nameArg){
    name = nameArg;
    parameters.setName(name);
};

void TXModParameter::resetModulation() {
    if (modulationAdded) {
        modulationAdded = false;
        modValue = 0.0;
        modMin = 0.0;
        modMax = 0.0;
    };
};

void TXModParameter::updateModulation (float valueArg, float scaleArg, bool negativeArg) {
    float holdValue;
    if (scaleArg != 0.0) {
        // round value if bool
        if (modParameterType == MODPARAMTYPE_BOOL) {
            if (valueArg < (scaleArg * 0.5f)) {
                holdValue = 0;
            } else {
                holdValue = scaleArg;
            };
        } else {
            holdValue = valueArg;
        };
        if (negativeArg) {
            modValue -= (holdValue * scaleArg);
            modMin -= scaleArg;
        } else {
            modValue += (holdValue * scaleArg);
            modMax += scaleArg;
        };
        // notify dummy parameter to trigger listeners
        // changed for OF0.9.8
        //parameters.notifyParameterChanged(extModValue);
        ofNotifyEvent(parameters.parameterChangedE(), extModValue);
        modulationAdded = true;
    };
};

/////////////// virtual methods

float TXModParameter::getFixedValueIntUnmapped() {
    ofLogNotice() << "TXModParameter::getFixedValueIntUnmapped() - ERROR base class called - ModParameter: " << getName();
    return 0.0f;
};

float TXModParameter::getFixedValueFloatUnmapped() {
    ofLogNotice() << "TXModParameter::getFixedValueFloatUnmapped() - ERROR base class called - ModParameter: " << getName();
    return 0.0f;
};

bool TXModParameter::getFixedValueBool() {
    ofLogNotice() << "TXModParameter::getFixedValueBool() - ERROR base class called - ModParameter: " << getName();
    return false;
}

int TXModParameter::getFixedValueInt() {
    ofLogNotice() << "TXModParameter::getFixedValueInt() - ERROR base class called - ModParameter: " << getName();
    return 0;
}

float TXModParameter::getFixedValueFloat() {
    ofLogNotice() << "TXModParameter::getFixedValueFloat() - ERROR base class called - ModParameter: " << getName();
    return 0.0f;
}


float TXModParameter::getFloatUnmapped() {
    ofLogNotice() << "TXModParameter::getFloatUnmapped() - ERROR base class called - ModParameter: " << getName();
    return 0.0f;
}

float TXModParameter::getFloat() {
    ofLogNotice() << "TXModParameter::getFloat() - ERROR base class called - ModParameter: " << getName();
    return 0.0f;
}

float TXModParameter::getIntUnmapped() {
    ofLogNotice() << "TXModParameter::getIntUnmapped() - ERROR base class called - ModParameter: " << getName();
    return 0.0f;
}

int TXModParameter::getInt() {
    ofLogNotice() << "TXModParameter::getInt() - ERROR base class called. ModParameter: " << getName();
    return 0;
}

bool TXModParameter::getBool() {
    ofLogNotice() << "TXModParameter::getBool() - ERROR base class called - ModParameter: " << getName();
    return false;
};

//void TXModParameter::setFixedValue (bool fixedValueArg) {
//};
//
//void TXModParameter::setFixedValue (int fixedValueArg, bool adjustMinMax) {
//};
//
//void TXModParameter::setFixedValue (float fixedValueArg, bool adjustMinMax) {
//};
//
//void TXModParameter::setFixedModMix (bool fixedModMixArg) {
//};
//
//void TXModParameter::setFixedModMix (float fixedModMixArg) {
//};
//
//void TXModParameter::setSoftMin (int softMinArg) {
//};
//
//void TXModParameter::setSoftMin (float softMinArg) {
//};
//
//void TXModParameter::setSoftMax (int softMaxArg) {
//};
//
//void TXModParameter::setSoftMax (float softMaxArg) {
//};
//
//void TXModParameter::maximiseRangeSoftMinMax() {
//};
//
//void TXModParameter::setAutoScaleModSumming(bool autoScaleModSummingArg) {
//};
//
//void TXModParameter::setBooleanSummingType(bool booleanSummingTypeArg) {
//};


//NSMutableDictionary * TXModParameter::getDictionary() {
//    NSMutableDictionary * dictionary;
//    dictionary = [NSMutableDictionary dictionary];
//    NSNumber * holdNum;
//    NSString * holdString;
//    //add data
//    holdNum = [NSNumber numberWithFloat:hardMin];
//    [dictionary setObject: holdNum forKey: @"hardMin"];
//    holdNum = [NSNumber numberWithFloat:hardMax];
//    [dictionary setObject: holdNum forKey: @"hardMax"];
//    holdNum = [NSNumber numberWithFloat:softMin];
//    [dictionary setObject: holdNum forKey: @"softMin"];
//    holdNum = [NSNumber numberWithFloat:softMax];
//    [dictionary setObject: holdNum forKey: @"softMax"];
//    holdNum = [NSNumber numberWithFloat:fixedValue];
//    [dictionary setObject: holdNum forKey: @"fixedValue"];
//    holdNum = [NSNumber numberWithFloat:fixedModMix];
//    [dictionary setObject: holdNum forKey: @"fixedModMix"];
//    holdNum = [NSNumber numberWithFloat:modMin];
//    [dictionary setObject: holdNum forKey: @"modMin"];
//    holdNum = [NSNumber numberWithFloat:modMax];
//    [dictionary setObject: holdNum forKey: @"modMax"];
//    holdString = [NSString stringWithUTF8String:name.c_str()];
//    [dictionary setObject: holdString forKey: @"name"];
//    holdNum = [NSNumber numberWithBool:autoScaleModSumming];
//    [dictionary setObject: holdNum forKey: @"autoScaleModSumming"];
//    return dictionary;
//}
//
//void TXModParameter::setFromDictionary(NSMutableDictionary * dictionaryArg) {
//    NSNumber * holdNum;
//    NSString * holdString;
//    //get data
//    holdNum = [dictionaryArg objectForKey: @"hardMin"];
//    if (holdNum != nil) {
//        hardMin = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"hardMax"];
//    if (holdNum != nil) {
//        hardMax = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"softMin"];
//    if (holdNum != nil) {
//        softMin = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"softMax"];
//    if (holdNum != nil) {
//        softMax = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"fixedValue"];
//    if (holdNum != nil) {
//        fixedValue = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"fixedModMix"];
//    if (holdNum != nil) {
//        fixedModMix = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"modMin"];
//    if (holdNum != nil) {
//        modMin = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"modMax"];
//    if (holdNum != nil) {
//        modMax = [holdNum floatValue];
//    };
//    holdString = [dictionaryArg objectForKey: @"name"];
//    if (holdString != nil) {
//        name = [holdString UTF8String];
//    };
//    holdNum = [dictionaryArg objectForKey: @"autoScaleModSumming"];
//    if (holdNum != nil) {
//        autoScaleModSumming = [holdNum boolValue];
//    };
//    
//}
//void TXModParameter::setFromClipboardDictionary(NSMutableDictionary * dictionaryArg) {
//    NSNumber * holdNum;
////    NSString * holdString;
//    //get data
//    holdNum = [dictionaryArg objectForKey: @"softMin"];
//    if (holdNum != nil) {
//        softMin = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"softMax"];
//    if (holdNum != nil) {
//        softMax = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"fixedValue"];
//    if (holdNum != nil) {
//        fixedValue = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"fixedModMix"];
//    if (holdNum != nil) {
//        fixedModMix = [holdNum floatValue];
//    };
//}




