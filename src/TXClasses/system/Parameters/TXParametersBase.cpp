/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXParametersBase.h"

void TXParametersBase::clearParameters() {
    parameters.clear();
    modParameters.clear();
}

ofPtr<TXModParamBool> TXParametersBase::createModParameter(TXModParameterBoolArgs args) {
    ofPtr<TXModParamBool> newModParameter(new TXModParamBool(args));
    modParameters[args.name] = newModParameter;
    return newModParameter;
}

ofPtr<TXModParamInt> TXParametersBase::createModParameter(TXModParameterIntArgs args) {
    ofPtr<TXModParamInt> newModParameter(new TXModParamInt(args));
    modParameters[args.name] = newModParameter;
    return newModParameter;
}

ofPtr<TXModParamFloat> TXParametersBase::createModParameter(TXModParameterFloatArgs args) {
    ofPtr<TXModParamFloat> newModParameter(new TXModParamFloat(args));
    modParameters[args.name] = newModParameter;
    return newModParameter;
}

void TXParametersBase::mergeParameters(ofParameterGroup parametersArg, map<string, ofPtr <TXModParameter> > modParametersArg) {
    for(int i=0;i<parametersArg.size();i++){
        parameters.add(parametersArg[i]);
    };
    modParameters.insert(modParametersArg.begin(), modParametersArg.end());
}

void TXParametersBase::mergeParameters(ofParameterGroup parametersArg) {
    for(int i=0;i<parametersArg.size();i++){
        parameters.add(parametersArg[i]);
    };
}
