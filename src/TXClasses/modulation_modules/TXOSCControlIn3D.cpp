/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXOSCControlIn3D.h"
#include "TXSystem.h"

// properties

// constructor
TXOSCControlIn3D::TXOSCControlIn3D (float startVal1Arg, float startVal2Arg, float startVal3Arg){
    setup (startVal1Arg, startVal2Arg, startVal3Arg);
};

// destructor
TXOSCControlIn3D::~TXOSCControlIn3D () {
    // deregister OSC with parentSystem
    parentSystem->deregisterOscAddressesForModule(moduleID);

    // remove listeners to relevent mod parameters:
    ofRemoveListener(smoothTime->parameters.parameterChangedE(),this,&TXOSCControlIn3D::smoothTimeChanged);
    ofRemoveListener(linearSmoothing->parameters.parameterChangedE(),this,&TXOSCControlIn3D::linearSmoothingChanged);
}

// methods
void TXOSCControlIn3D::setup (float startVal1Arg, float startVal2Arg, float startVal3Arg) {
    TXModParameterBoolArgs holdModParamBoolArgs;
//    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
    
    holdModParamBoolArgs.name = "active";
    holdModParamBoolArgs.fixedValue = true;
    active = createModParameter(holdModParamBoolArgs);
    parameters.add(active->parameters);
    
    parameters.add(oscAddress.set("oscAddress", "/Example/text"));

    holdModParamFloatArgs.name = "input1Min";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -1000000.0;
    holdModParamFloatArgs.hardMax = 1000000.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    input1Min = createModParameter(holdModParamFloatArgs);
    parameters.add(input1Min->parameters);
    
    holdModParamFloatArgs.name = "input1Max";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -1000000.0;
    holdModParamFloatArgs.hardMax = 1000000.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    input1Max = createModParameter(holdModParamFloatArgs);
    parameters.add(input1Max->parameters);
    
    holdModParamFloatArgs.name = "input2Min";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -1000000.0;
    holdModParamFloatArgs.hardMax = 1000000.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    input2Min = createModParameter(holdModParamFloatArgs);
    parameters.add(input2Min->parameters);
    
    holdModParamFloatArgs.name = "input2Max";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -1000000.0;
    holdModParamFloatArgs.hardMax = 1000000.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    input2Max = createModParameter(holdModParamFloatArgs);
    parameters.add(input2Max->parameters);
    
    holdModParamFloatArgs.name = "input3Min";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -1000000.0;
    holdModParamFloatArgs.hardMax = 1000000.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    input3Min = createModParameter(holdModParamFloatArgs);
    parameters.add(input3Min->parameters);
    
    holdModParamFloatArgs.name = "input3Max";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -1000000.0;
    holdModParamFloatArgs.hardMax = 1000000.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    input3Max = createModParameter(holdModParamFloatArgs);
    parameters.add(input3Max->parameters);
    
    holdModParamFloatArgs.name = "smoothTime";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 2.0;
	smoothTime = createModParameter(holdModParamFloatArgs);
    parameters.add(smoothTime->parameters);
    
    holdModParamBoolArgs.name = "linearSmoothing";
    holdModParamBoolArgs.fixedValue = false;
    linearSmoothing = createModParameter(holdModParamBoolArgs);
    parameters.add(linearSmoothing->parameters);
    
    // add listener to relevent parameters:
    oscAddress.addListener(this, &TXOSCControlIn3D::oscAddressChanged);
    ofAddListener(smoothTime->parameters.parameterChangedE(),this,&TXOSCControlIn3D::smoothTimeChanged);
    ofAddListener(linearSmoothing->parameters.parameterChangedE(),this,&TXOSCControlIn3D::linearSmoothingChanged);

    // create mod source output
    outValue1 = createModSource("out1", startVal1Arg);
    outValue2 = createModSource("out2", startVal2Arg);
    outValue3 = createModSource("out3", startVal3Arg);
    
    oldAddress = "";
    newOSCValue1Received = false;
    newOSCValue2Received = false;
    newOSCValue3Received = false;
    newOSCValue1 = 0.0;
    newOSCValue2 = 0.0;
    newOSCValue3 = 0.0;
};

void  TXOSCControlIn3D::update() {
    outValue1->setValue(smoothVal1.outValue);
    outValue2->setValue(smoothVal2.outValue);
    outValue3->setValue(smoothVal3.outValue);
}

void  TXOSCControlIn3D::advanceBy(float timeDeltaArg) {
    // store new osc val
    if (newOSCValue1Received) {
        smoothVal1.setTargetValue(newOSCValue1);
        newOSCValue1Received = false;
    };
    if (newOSCValue2Received) {
        smoothVal2.setTargetValue(newOSCValue2);
        newOSCValue2Received = false;
    };
    if (newOSCValue3Received) {
        smoothVal3.setTargetValue(newOSCValue3);
        newOSCValue3Received = false;
    };
    smoothVal1.advanceBy(timeDeltaArg);
    smoothVal2.advanceBy(timeDeltaArg);
    smoothVal3.advanceBy(timeDeltaArg);
}

void  TXOSCControlIn3D::resetTime() {
    smoothVal1.resetTime();
    smoothVal2.resetTime();
    smoothVal3.resetTime();
}

void  TXOSCControlIn3D::oscAddressChanged(string & stringArg) {
    if ((oldAddress != "") && (oldAddress != "/")) {
        parentSystem->deregisterOscAddress(oscAddress, moduleID);
    };
    oldAddress = oscAddress;

    // register oscAddress with parentSystem
    if ((oscAddress.get() != "") && (oscAddress.get() != "/")) {
        parentSystem->registerOscAddress(oscAddress, moduleID);
    };
}

void  TXOSCControlIn3D::processOscMsg(ofxOscMessage msg) {
    bool validNumber1 = false;
    bool validNumber2 = false;
    bool validNumber3 = false;
    float newValue, mapVal;
    //int holdInt;
    
    if (active->getBool()) {
        if (msg.getAddress() == oscAddress.get()) {
            // if a float or int is received update vals
            if (msg.getNumArgs() >= 1) {
                if (msg.getArgTypeName(0)== "int32") {
                    newValue = msg.getArgAsInt32(0);
                    validNumber1 = true;
                } else if (msg.getArgTypeName(0)== "float") {
                    newValue = msg.getArgAsFloat(0);
                    validNumber1 = true;
                };
                if (validNumber1) {
                    float min = input1Min->getFloat();
                    float max = input1Max->getFloat();
                    // divide by zero prevention
                    if (fabs(min - max) < FLT_EPSILON){
                        mapVal = 0;
                    } else {
                        // map & clip to 0-1
                        mapVal = ofMap(newValue, min, max, 0.0, 1.0, true);
                    };
                    newOSCValue1Received = true;
                    newOSCValue1 = mapVal;
                };
            };
            if (msg.getNumArgs() >= 2) {
                if (msg.getArgTypeName(1)== "int32") {
                    newValue = msg.getArgAsInt32(1);
                    validNumber2 = true;
                } else if (msg.getArgTypeName(1)== "float") {
                    newValue = msg.getArgAsFloat(1);
                    validNumber2 = true;
                };
                if (validNumber2) {
                    float min = input2Min->getFloat();
                    float max = input2Max->getFloat();
                    // divide by zero prevention
                    if (fabs(min - max) < FLT_EPSILON){
                        mapVal = 0;
                    } else {
                        // map & clip to 0-1
                        mapVal = ofMap(newValue, min, max, 0.0, 1.0, true);
                    };
                    newOSCValue2Received = true;
                    newOSCValue2 = mapVal;
                };
            };
            if (msg.getNumArgs() >= 3) {
                if (msg.getArgTypeName(2)== "int32") {
                    newValue = msg.getArgAsInt32(2);
                    validNumber3 = true;
                } else if (msg.getArgTypeName(2)== "float") {
                    newValue = msg.getArgAsFloat(2);
                    validNumber3 = true;
                };
                if (validNumber3) {
                    float min = input3Min->getFloat();
                    float max = input3Max->getFloat();
                    // divide by zero prevention
                    if (fabs(min - max) < FLT_EPSILON){
                        mapVal = 0;
                    } else {
                        // map & clip to 0-1
                        mapVal = ofMap(newValue, min, max, 0.0, 1.0, true);
                    };
                    newOSCValue3Received = true;
                    newOSCValue3 = mapVal;
                };
            };
        };
    };
}

void  TXOSCControlIn3D::smoothTimeChanged(ofAbstractParameter & parameterArg ) {
    smoothVal1.setSmoothTime(smoothTime->getFloat());
    smoothVal2.setSmoothTime(smoothTime->getFloat());
    smoothVal3.setSmoothTime(smoothTime->getFloat());
}

void  TXOSCControlIn3D::linearSmoothingChanged(ofAbstractParameter & parameterArg ) {
    if (linearSmoothing->getBool()) {
        smoothVal1.setSmoothType(TXSMOOTHTYPE_LINEAR);
        smoothVal2.setSmoothType(TXSMOOTHTYPE_LINEAR);
        smoothVal3.setSmoothType(TXSMOOTHTYPE_LINEAR);
    } else {
        smoothVal1.setSmoothType(TXSMOOTHTYPE_EXPONENTIAL);
        smoothVal2.setSmoothType(TXSMOOTHTYPE_EXPONENTIAL);
        smoothVal3.setSmoothType(TXSMOOTHTYPE_EXPONENTIAL);
    }
}


