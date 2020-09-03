/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TX_template.h"
#include "TXSystem.h"

TX_template::TX_template() {
    setup();

    // testing xxx
    ofLogNotice() << "================ " ;
    ofLogNotice() << "TXShaderFXBase::renderTexture() - xx " << "xx";

    // testing xxx
    if (parentSystem->getCurrentFrameNo() % 90 == 0) { // reduce frequency
        ofLogNotice() << "================ " ;
        ofLogNotice() << "TXShaderFXBase::renderTexture() - xx " << "xx";
    };
    
}

// destructor
TX_template::~TX_template() {
    // remove listeners to relevent mod parameters:
    ofRemoveListener(xxxINT->parameters.parameterChangedE(),this,&TX_template::xxxINTChanged);
}

void TX_template::setup(){
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
    
    holdModParamIntArgs.name = "xxxINT";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 10;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 10;
	xxxINT = createModParameter(holdModParamIntArgs);
    parameters.add(xxxINT->parameters);
    
    holdModParamFloatArgs.name = "xxxFLOAT";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    xxxFLOAT = createModParameter(holdModParamFloatArgs);
    parameters.add(xxxFLOAT->parameters);
    
    holdModParamBoolArgs.name = "xxxBOOL";
    holdModParamBoolArgs.fixedValue = false;
    xxxBOOL = createModParameter(holdModParamBoolArgs);
    parameters.add(xxxBOOL->parameters);

    customCurve.setValueArrayToRamp(0, 1);
    customCurve.setName("customCurve");
    parameters.add(customCurve.parameters);
    
    parameters.add(testParameterI.set("testParameterI", 1, 1, 100));
    parameters.add(testParameterF.set("testParameterF", 0.0, 0.0, 1.0));
    parameters.add(testParameterB.set("testParameterB", false));
    
    // add listener to relevent mod parameters:
    ofAddListener(xxxINT->parameters.parameterChangedE(),this,&TX_template::xxxINTChanged);

    // add listener to relevent parameters:
    testParameterI.addListener(this, &TX_template::testParameterIChanged);

    // create mod source output
    outValue = createModSource("out", 0);

    // asset slots
    createImageAssetSlot("inputImage");
}

void  TX_template::xxxINTChanged(ofAbstractParameter & parameterArg ) {
    
    // SOME ACTION HERE
    
}

void  TX_template::testParameterIChanged(int & intArg) {
    
    // SOME ACTION HERE
    
}

 void TX_template::draw(){
     int xxx;
     // e.g. see TXDrawLayersBase::draw() for drawing layers
}
