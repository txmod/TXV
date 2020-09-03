
#include "TXModNode.h"
#include "ofApp.h"

// properties

// constructor
TXModNode::TXModNode (int sourceModuleIDArg, string sourceNameArg, int destinationModuleIDArg, string destinationNameArg, float modAmountArg, bool negativeModulationArg, bool activeArg)
{
    setup (sourceModuleIDArg, sourceNameArg, destinationModuleIDArg, destinationNameArg, modAmountArg, negativeModulationArg, activeArg);
};

// methods
void TXModNode::setup (int sourceModuleIDArg, string sourceNameArg, int destinationModuleIDArg, string destinationNameArg, float modAmountArg, bool negativeModulationArg, bool activeArg)
{
    TXModParameterFloatArgs holdModParamFloatArgs;
    TXModParameterBoolArgs holdModParamBoolArgs;
    
    // create input paramaters
    parameters.clear();
    
 	parameters.add(sourceModuleID.set("sourceModuleID", sourceModuleIDArg));
 	parameters.add(destinationModuleID.set("destinationModuleID", destinationModuleIDArg));
 	parameters.add(sourceName.set("sourceName", sourceNameArg));
 	parameters.add(destinationName.set("destinationName", destinationNameArg));
 	parameters.add(active.set("active", activeArg));
   
    holdModParamFloatArgs.name = "modAmount";
    holdModParamFloatArgs.fixedValue = modAmountArg;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    holdModParamFloatArgs.autoScaleModSumming = true;
	modAmount = createModParameter(holdModParamFloatArgs);
    parameters.add(modAmount->parameters);

    holdModParamBoolArgs.name = "negativeModulation";
    holdModParamBoolArgs.fixedValue = (int) negativeModulationArg;
    holdModParamBoolArgs.fixedModMix = 0.0;
	negativeModulation = createModParameter(holdModParamBoolArgs);
    parameters.add(negativeModulation->parameters);
    };

int TXModNode::getSourceModuleID() {
    return sourceModuleID;
}

void  TXModNode::setSourceModuleID(int sourceModuleIDArg) {
    sourceModuleID.set(sourceModuleIDArg);
}

int TXModNode::getDestinationModuleID() {
    return destinationModuleID;
}

void  TXModNode::setDestinationModuleID(int destinationModuleIDArg) {
    destinationModuleID.set(destinationModuleIDArg);
}

string TXModNode::getSourceName() {
    return sourceName;
}

void  TXModNode::setSourceName(string sourceNameArg) {
    sourceName.set(sourceNameArg);
}

string TXModNode::getDestinationName() {
    return destinationName;
}

void  TXModNode::setDestinationName(string destinationNameArg) {
    destinationName.set(destinationNameArg);
}

