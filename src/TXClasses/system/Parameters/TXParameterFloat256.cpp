/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXParameterFloat256.h"

// properties
float tempValueArray[256];

// constructor
TXParameterFloat256::TXParameterFloat256(){
    name = "";
    for(int i=0; i<256; i++)
        tempValueArray[i] = 0;
    setup("float256", tempValueArray);
};

// methods

void TXParameterFloat256::setup(string nameArg, float * valueArrayArg){
    
    // initialise parameters
    parameters.clear();
    // parameters.setName(name);
    setName(nameArg);
    for(int i=0; i<256; i++)
    {
        ofParameter<float> floatVal;
        floatVal.set("floatVal" + ofToString(i), valueArrayArg[i]);
        parameters.add(floatVal);
    };
};

string TXParameterFloat256::getName() {
    return name;
}

void TXParameterFloat256::setName(string nameArg){
    name = nameArg;
    parameters.setName(name);
};

float * TXParameterFloat256::getValueArray(){
    for(int i=0; i<256; i++)
    {
        tempValueArray[i] = parameters.getFloat(i);
    };
    return tempValueArray;
}

void TXParameterFloat256::setValueArray(float * valueArrayArg) {
    for(int i=0; i<256; i++)
    {
        parameters.getFloat(i) = valueArrayArg[i];
    };
};

void TXParameterFloat256::setValueArray(ofParameterGroup & groupArg) {
    for(int i=0; i<256; i++)
    {
        parameters.getFloat(i) = groupArg.getFloat(i);
    };
};

void TXParameterFloat256::setValueArrayTo (float valueArg) {
    for(int i=0; i<256; i++)
    {
        parameters.getFloat(i) = valueArg;
    };
};

void TXParameterFloat256::setValueArrayToRamp (float startValueArg, float endValueArg) {
    for(int i=0; i<256; i++)
    {
        float holdVal = i / 255.0f;
        parameters.getFloat(i) = holdVal;
    };
};


float   TXParameterFloat256::interpolatedLookup(float & inputArg){
    float inputClamped = ofClamp(inputArg, 0.0, 1.0);
    float outVal;
    if (inputClamped == 1.0) {
        outVal = parameters.getFloat(255);
    } else if (inputClamped == 0.0) {
        outVal = parameters.getFloat(0);
    } else {
        float inputScaled = inputClamped  * 255.0;
        int minIndex = (int) inputScaled;
        float low = parameters.getFloat(minIndex);
        float high = parameters.getFloat(minIndex + 1);
        if (high == low) {
            outVal = low;
        } else {
            outVal = ofLerp(low, high, inputScaled - minIndex);
        };
    };
    return outVal;
}


float   TXParameterFloat256::interpolatedLookupWithPhase(float & inputArg, float & phaseArg){
    // float modInput = ofClamp(inputArg + phaseArg, 0.0, 1.0);  // TESTING CLAMPED
    // float modInput = ofWrap(inputArg + phaseArg, 0.0, 1.0);
    // float modInput = ofClamp(inputArg, 0.0, 1.0);  // TESTING CLAMPED WITHOUT PHASE
    float modInput = fmod(inputArg + phaseArg, 1.0);
    float outVal;
    // removed - will never be 1 since fmod is used.
//    if (modInput == 1.0) {
//        outVal = parameters.getFloat(255);
//    } else {
        if (modInput == 0.0) {
            outVal = parameters.getFloat(0);
        } else {
            float inputScaled = modInput * 255.0;
            int minIndex = (int) inputScaled;
            float low = parameters.getFloat(minIndex);
            float high = parameters.getFloat(minIndex + 1);
            if (high == low) {
                outVal = low;
            } else {
                outVal = ofLerp(low, high, inputScaled - minIndex);
            };
        };
        return outVal;
//    }
}


