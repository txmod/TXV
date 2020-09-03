/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXOSCControlIn.h"
#include "TXSystem.h"

// properties

// constructor
TXOSCControlIn::TXOSCControlIn (float startValArg){
    setup (startValArg);
};

// destructor
TXOSCControlIn::~TXOSCControlIn () {
    // deregister OSC with parentSystem
    parentSystem->deregisterOscAddressesForModule(moduleID);

    // remove listeners to relevent mod parameters:
    ofRemoveListener(smoothTime->parameters.parameterChangedE(),this,&TXOSCControlIn::smoothTimeChanged);
    ofRemoveListener(linearSmoothing->parameters.parameterChangedE(),this,&TXOSCControlIn::linearSmoothingChanged);
}

// methods
void TXOSCControlIn::setup (float startValArg) {
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

    holdModParamFloatArgs.name = "inputMin";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -1000000.0;
    holdModParamFloatArgs.hardMax = 1000000.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    inputMin = createModParameter(holdModParamFloatArgs);
    parameters.add(inputMin->parameters);
    
    holdModParamFloatArgs.name = "inputMax";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -1000000.0;
    holdModParamFloatArgs.hardMax = 1000000.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    inputMax = createModParameter(holdModParamFloatArgs);
    parameters.add(inputMax->parameters);
    
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
    oscAddress.addListener(this, &TXOSCControlIn::oscAddressChanged);
    ofAddListener(smoothTime->parameters.parameterChangedE(),this,&TXOSCControlIn::smoothTimeChanged);
    ofAddListener(linearSmoothing->parameters.parameterChangedE(),this,&TXOSCControlIn::linearSmoothingChanged);

    // create mod source output
    outValue = createModSource("out", startValArg);
    
    oldAddress = "";
    newOSCValueReceived = false;
    newOSCValue = 0.0;
};

void  TXOSCControlIn::update() {
    outValue->setValue(smoothVal.outValue);
}

void  TXOSCControlIn::advanceBy(float timeDeltaArg) {
    // store new osc val
    if (newOSCValueReceived) {
        smoothVal.setTargetValue(newOSCValue);
        newOSCValueReceived = false;
    };
    smoothVal.advanceBy(timeDeltaArg);
}

void  TXOSCControlIn::resetTime() {
    smoothVal.resetTime();
}

void  TXOSCControlIn::oscAddressChanged(string & stringArg) {
    if ((oldAddress != "") && (oldAddress != "/")) {
        parentSystem->deregisterOscAddress(oscAddress, moduleID);
    };
    oldAddress = oscAddress;

    // register oscAddress with parentSystem
    if ((oscAddress.get() != "") && (oscAddress.get() != "/")) {
        parentSystem->registerOscAddress(oscAddress, moduleID);
    };
}

void  TXOSCControlIn::processOscMsg(ofxOscMessage msg) {
    bool validNumber = false;
    float newValue, mapVal;
    //int holdInt;
    
    if (active->getBool()) {
        if (msg.getAddress() == oscAddress.get()) {
            // if a float or int is received
            if (msg.getNumArgs() >= 1) {
                if (msg.getArgTypeName(0)== "int32") {
                    newValue = msg.getArgAsInt32(0);
                    validNumber = true;
                } else if (msg.getArgTypeName(0)== "float") {
                    newValue = msg.getArgAsFloat(0);
                    validNumber = true;
                };
                if (validNumber) {
                    float min = inputMin->getFloat();
                    float max = inputMax->getFloat();
                    // divide by zero prevention
                    if (fabs(min - max) < FLT_EPSILON){
                        mapVal = 0;
                    } else {
                        // map & clip to 0-1
                        mapVal = ofMap(newValue, min, max, 0.0, 1.0, true);
                    };
                    newOSCValueReceived = true;
                    newOSCValue = mapVal;
                };
            };
        };
    };
}

void  TXOSCControlIn::smoothTimeChanged(ofAbstractParameter & parameterArg ) {
    smoothVal.setSmoothTime(smoothTime->getFloat());
}

void  TXOSCControlIn::linearSmoothingChanged(ofAbstractParameter & parameterArg ) {
    if (linearSmoothing->getBool()) {
        smoothVal.setSmoothType(TXSMOOTHTYPE_LINEAR);
    } else {
        smoothVal.setSmoothType(TXSMOOTHTYPE_EXPONENTIAL);
    }
}


