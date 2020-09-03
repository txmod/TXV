
#include "TXDrawConnection.h"
#include "ofApp.h"
#include "TXSystem.h"

// properties

// constructor
TXDrawConnection::TXDrawConnection (int sourceModuleIDArg, int destinationModuleIDArg, int layerNoArg)
{
    setup (sourceModuleIDArg, destinationModuleIDArg, layerNoArg);
}

// methods
void TXDrawConnection::setup (int sourceModuleIDArg, int destinationModuleIDArg, int layerNoArg)
{
    // create input paramaters
    parameters.clear();
    
    parameters.setName("Draw Connection");
 	parameters.add(sourceModuleID.set("sourceModuleID", sourceModuleIDArg));
 	parameters.add(destinationModuleID.set("destinationModuleID", destinationModuleIDArg));
 	parameters.add(layerNo.set("layerNo", 1, 1, 20));
    parameters.add(active.set("active", true));     // always active when created
    
    // add listener
    layerNo.addListener(this, &TXDrawConnection::layerNoChanged);
    active.addListener(this, &TXDrawConnection::activeChanged);
    
    oldLayerNo = -1;
    oldActive = true;
}

int TXDrawConnection::getSourceModuleID() {
    return sourceModuleID;
}

void  TXDrawConnection::setSourceModuleID(int sourceModuleIDArg) {
    sourceModuleID.set(sourceModuleIDArg);
}

int TXDrawConnection::getDestinationModuleID() {
    return destinationModuleID;
}

void  TXDrawConnection::setDestinationModuleID(int destinationModuleIDArg) {
    destinationModuleID.set(destinationModuleIDArg);
}

void  TXDrawConnection::layerNoChanged(int & newLayerNo) {
    if (oldLayerNo != newLayerNo) {
        parentSystem->setDrawConnectionLayerNo(this->getModuleID(), oldLayerNo, newLayerNo);
        oldLayerNo = newLayerNo;
    };
}

void  TXDrawConnection::activeChanged(bool & activeArg) {
    if (oldActive != activeArg) {
        parentSystem->setDrawConnectionActive(this->getModuleID(), layerNo, activeArg);
        oldActive = activeArg;
    };
}

