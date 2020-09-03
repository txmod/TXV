/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXOSCControlIn2D.h"
#include "TXSystem.h"

// properties

// constructor
TXOSCControlIn2D::TXOSCControlIn2D (float startVal1Arg, float startVal2Arg){
    setup (startVal1Arg, startVal2Arg);
};

// destructor
TXOSCControlIn2D::~TXOSCControlIn2D () {
    // deregister OSC with parentSystem
    parentSystem->deregisterOscAddressesForModule(moduleID);

    // remove listeners to relevent mod parameters:
    ofRemoveListener(smoothTime->parameters.parameterChangedE(),this,&TXOSCControlIn2D::smoothTimeChanged);
    ofRemoveListener(linearSmoothing->parameters.parameterChangedE(),this,&TXOSCControlIn2D::linearSmoothingChanged);
}

// methods
void TXOSCControlIn2D::setup (float startVal1Arg, float startVal2Arg) {
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
    oscAddress.addListener(this, &TXOSCControlIn2D::oscAddressChanged);
    ofAddListener(smoothTime->parameters.parameterChangedE(),this,&TXOSCControlIn2D::smoothTimeChanged);
    ofAddListener(linearSmoothing->parameters.parameterChangedE(),this,&TXOSCControlIn2D::linearSmoothingChanged);

    // create mod source output
    outValue1 = createModSource("out1", startVal1Arg);
    outValue2 = createModSource("out2", startVal2Arg);
    
    oldAddress = "";
    newOSCValue1Received = false;
    newOSCValue2Received = false;
    newOSCValue1 = 0.0;
    newOSCValue2 = 0.0;
};

void  TXOSCControlIn2D::update() {
    outValue1->setValue(smoothVal1.outValue);
    outValue2->setValue(smoothVal2.outValue);
}

void  TXOSCControlIn2D::advanceBy(float timeDeltaArg) {
    // store new osc val
    if (newOSCValue1Received) {
        smoothVal1.setTargetValue(newOSCValue1);
        newOSCValue1Received = false;
    };
    if (newOSCValue2Received) {
        smoothVal2.setTargetValue(newOSCValue2);
        newOSCValue2Received = false;
    };
    smoothVal1.advanceBy(timeDeltaArg);
    smoothVal2.advanceBy(timeDeltaArg);
}

void  TXOSCControlIn2D::resetTime() {
    smoothVal1.resetTime();
    smoothVal2.resetTime();
}

void  TXOSCControlIn2D::oscAddressChanged(string & stringArg) {
    if ((oldAddress != "") && (oldAddress != "/")) {
        parentSystem->deregisterOscAddress(oscAddress, moduleID);
    };
    oldAddress = oscAddress;

    // register oscAddress with parentSystem
    if ((oscAddress.get() != "") && (oscAddress.get() != "/")) {
        parentSystem->registerOscAddress(oscAddress, moduleID);
    };
}

void  TXOSCControlIn2D::processOscMsg(ofxOscMessage msg) {
    bool validNumber1 = false;
    bool validNumber2 = false;
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
        };
    };
}

void  TXOSCControlIn2D::smoothTimeChanged(ofAbstractParameter & parameterArg ) {
    smoothVal1.setSmoothTime(smoothTime->getFloat());
    smoothVal2.setSmoothTime(smoothTime->getFloat());
}

void  TXOSCControlIn2D::linearSmoothingChanged(ofAbstractParameter & parameterArg ) {
    if (linearSmoothing->getBool()) {
        smoothVal1.setSmoothType(TXSMOOTHTYPE_LINEAR);
        smoothVal2.setSmoothType(TXSMOOTHTYPE_LINEAR);
    } else {
        smoothVal1.setSmoothType(TXSMOOTHTYPE_EXPONENTIAL);
        smoothVal2.setSmoothType(TXSMOOTHTYPE_EXPONENTIAL);
    }
}


