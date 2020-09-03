/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXModParamBool.h"
#include "TXModParamInt.h"
#include "TXModParamFloat.h"
#include "TXParameterFloat256.h"

class TXParametersBase
{
public:

    ofParameterGroup parameters;
    map<string, ofPtr <TXModParameter> > modParameters;

    void clearParameters();
    
    ofPtr<TXModParamBool> createModParameter(TXModParameterBoolArgs args);
    ofPtr<TXModParamInt> createModParameter(TXModParameterIntArgs args);
    ofPtr<TXModParamFloat> createModParameter(TXModParameterFloatArgs args);
        
    void mergeParameters(ofParameterGroup parametersArg, map<string, ofPtr <TXModParameter> > modParametersArg);
    
    void mergeParameters(ofParameterGroup parametersArg);
    
};

