/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXSystem.h"
#include "TXModuleFactory.h"
#include "TXModNode.h"

// properties 

// constructor
TXSystem::TXSystem(){
    setup();
};

// destructor
TXSystem::~TXSystem() {
    imageLoader.stopThread();
}

// methods

void TXSystem::setup(string nameArg) {
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    string holdName;
    int moduleID;
    
    // initialise system
#if defined(_DEBUG)
   //ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetLogLevel(OF_LOG_NOTICE);
    //    ofSetLogLevel(OF_LOG_WARNING);
    ofLogVerbose() << "ofLogVerbose() - test print line";
    ofLogNotice() << "ofLogNotice() - test print line";
    ofLogWarning() << "ofLogWarning() - test print line";
#else
    ofSetLogLevel(OF_LOG_ERROR);
#endif  

    txvVersionString = "089 2020.06.26";  // current version string
    localPort = 1999;    // TXV
    remotePort = 57120; // SuperCollider

    allIDAllocators.clear();
    initOsc();
    parameters.clear();
    
    ofSetCircleResolution(100);
    
    moduleID = getNextIDForType("moduleID");
    if (nameArg == "") {
        holdName = getNextNameForType("TXSystem");
    } else {
        holdName = nameArg;
    }
    baseSetup(this, moduleID, "TXSystem", holdName);
    ofLogNotice() << "TXSystem::setup - name/ ID: " << holdName << moduleID;

    // create input paramaters
    initialiseParameters();
    
    holdModParamBoolArgs.name = "freezeSystem";
    holdModParamBoolArgs.fixedValue = false;
    freezeSystem = createModParameter(holdModParamBoolArgs);
    parameters.add(freezeSystem->parameters);
    
    parameters.add(showFullScreen.set("showFullScreen", false));
    parameters.add(windowSizeMode.set("windowSizeMode", 0, 0, WINDOWSIZEMODE_TOTAL-1));
    parameters.add(customWindowWidth.set("customWindowWidth", 1024, 1, 5000));
    parameters.add(customWindowHeight.set("customWindowHeight", 768, 1, 5000));
    parameters.add(oscLatency.set("oscLatency", 0.0, 0.0, 30));

    holdModParamIntArgs.name = "drawLayersRule";
    holdModParamIntArgs.fixedValue = TXDRAWLAYERSRULE_ALLEXCEPT20;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXDRAWLAYERSRULE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXDRAWLAYERSRULE_TOTAL - 1;
	drawLayersRule = createModParameter(holdModParamIntArgs);
    parameters.add(drawLayersRule->parameters);
    
    parameters.add(antiAliasing.set("antiAliasing", true));
    parameters.add(neverDropFrames.set("neverDropFrames", true));
    parameters.add(showFrameRate.set("showFrameRate", false));
    parameters.add(targetFrameRate.set("targetFrameRate", 30, 1, 100));
    parameters.add(alphaThreshold.set("alphaThreshold", 0.0, 0.0, 0.05));
    
    holdModParamBoolArgs.name = "resetClocks";
    holdModParamBoolArgs.fixedValue = false;
    resetClocks = createModParameter(holdModParamBoolArgs);
    parameters.add(resetClocks->parameters);
    
    holdModParamFloatArgs.name = "masterBpm";
    holdModParamFloatArgs.fixedValue = 120;
    holdModParamFloatArgs.hardMin = 1.0;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 1.0;
    holdModParamFloatArgs.softMax = 1000.0;
    masterBpm = createModParameter(holdModParamFloatArgs);
    parameters.add(masterBpm->parameters);
    
    holdModParamBoolArgs.name = "showBackground";
    holdModParamBoolArgs.fixedValue = true;
    showBackground = createModParameter(holdModParamBoolArgs);
    parameters.add(showBackground->parameters);
    
    holdModParamFloatArgs.name = "backgroundHue";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    backgroundHue = createModParameter(holdModParamFloatArgs);
    parameters.add(backgroundHue->parameters);
    
    holdModParamFloatArgs.name = "backgroundSaturation";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    backgroundSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(backgroundSaturation->parameters);
    
    holdModParamFloatArgs.name = "backgroundBrightness";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    backgroundBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(backgroundBrightness->parameters);
    
    holdModParamFloatArgs.name = "backgroundAlpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    backgroundAlpha = createModParameter(holdModParamFloatArgs);
    parameters.add(backgroundAlpha->parameters);

    holdModParamBoolArgs.name = "backgroundHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	backgroundHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(backgroundHSBAsRGB->parameters);
    
    // add listener to relevent parameters:
    antiAliasing.addListener(this, &TXSystem::antiAliasingChanged);
    neverDropFrames.addListener(this, &TXSystem::neverDropFramesChanged);
    showFullScreen.addListener(this, &TXSystem::showFullScreenChanged);
    targetFrameRate.addListener(this, &TXSystem::targetFrameRateChanged);
    windowSizeMode.addListener(this, &TXSystem::windowSizeModeChanged);
    customWindowWidth.addListener(this, &TXSystem::customWindowWidthChanged);
    customWindowHeight.addListener(this, &TXSystem::customWindowHeightChanged);
    
    // create mod source outputs
    mouseDraggedX = createModSource("mouseDraggedX", 0);
    mouseDraggedY = createModSource("mouseDraggedY", 0);
    mouseMovedX = createModSource("mouseMovedX", 0);
    mouseMovedY = createModSource("mouseMovedY", 0);
    mouseMovedOrDraggedX = createModSource("mouseMovedOrDraggedX", 0);
    mouseMovedOrDraggedY = createModSource("mouseMovedOrDraggedY", 0);
    mouseButtonPressed = createModSource("mouseButtonPressed", 0);

    // other preperations
    currentStatusText = "Ready";
    windowResizeCalled = false;
    openSystemRequested = false;
    saveSystemRequested = false;
    closeTXVRequested = false;
    oldResetClocks = false;
    // set cursor
    ofGetWindowPtr()->showCursor();
    showCursor = true;
    

    // store current vals
    currentWindowWidth = 1024;
    currentWindowHeight = 768;
    
    // TESTING xxx - build a test system:
//    ofPtr<TXModuleBase> lfo1 = addModule("TXLFO");
//    ofPtr<TXModuleBase> lfo2 = addModule("TXLFO");
//    ofPtr<TXModuleBase> drawCircles = addModule("TXDrawCircles");
//    ofPtr<TXModuleBase> node1 = addNode(2, "out", 4, "positionX", 1, 0, true);
//    ofPtr<TXModuleBase> node2 = addNode(3, "out", 4, "positionY", 1, 0, true);
//
//    addDrawConnection(4, 1, 1);

}

void TXSystem::update() {    
    float timeDelta;
    bool  masterBpmHasChanged;
    float currentMasterBpm;

    // No gui for now
    //    if (guiBuilt) {
    //        sync.update();
    //    };
    
    if (closeTXVRequested) {
        ofExit();
        return; 
    };
    
    /*    REMOVED FOR NOW
    if (openSystemRequested) {
        openSystemFromFile();
        openSystemRequested = false;
    } else if (saveSystemRequested) {
        saveSystemToFile();
        saveSystemRequested = false;
    };
     */

    if (windowResizeCalled) {
        windowResizeInform();
    };
    
    checkOscMessages();
    
    bool newResetClocks = resetClocks->getBool();
    if (newResetClocks && !oldResetClocks) {
        resetAllTime();
    };
    oldResetClocks = newResetClocks;
    
    if (makeFullScreenTime != -1) {
        if (ofGetElapsedTimef() > makeFullScreenTime) {
            if (ofGetWindowMode() != OF_FULLSCREEN) {
                ofSetFullscreen(true);
            };
            makeFullScreenTime = -1;
        };
    };
    // store current vals
    currentWindowWidth = ofGetWidth();
    currentWindowHeight = ofGetHeight();
    
    if ((!freezeSystem->getBool()) && (!freezeSystemOverride)) {
        timeDelta = currentTime - oldTime;
        oldTime = currentTime;
        currentMasterBpm = masterBpm->getFloat();
        if (currentMasterBpm !=  oldMasterBpm) {
            masterBpmHasChanged = true;
            oldMasterBpm = currentMasterBpm;
        } else {
            masterBpmHasChanged = false;
        };
        // advance times in all modules
        map<int, ofPtr <TXModuleBase> >::iterator itModule = allModules.begin();
        for (itModule=allModules.begin(); itModule!=allModules.end(); ++itModule)
        {
            if (masterBpmHasChanged) {
                itModule->second->setMasterBpm(currentMasterBpm);
            };
            itModule->second->advanceBy(timeDelta);
        };
        masterBpmHasChanged = false; // reset
        
        applyNodeModulations();
        
        // call update on all modules
        itModule = allModules.begin();
        for (itModule=allModules.begin(); itModule!=allModules.end(); ++itModule)
        {
            itModule->second->update();
        };
        
        // update frame/time
        currentFrameNo = currentFrameNo + 1;
        if (neverDropFrames)
        {
            currentTime = currentFrameNo / (float) targetFrameRate;
        } else {
            currentTime = ofGetElapsedTimef() - startTimeOffset;
        };
    } else {
        // if frozen advance startTimeOffset
        startTimeOffset = startTimeOffset + (ofGetElapsedTimef() - oldElapsedTime);
    };
    oldElapsedTime = ofGetElapsedTimef();
}

void TXSystem::draw() {
    if (!drawActive->getBool()) {
        return;
    };
    // draw background
    if (showBackground->getBool()) {
        ofColor newColor;
        if (backgroundHSBAsRGB->getBool()) {
            newColor.set(backgroundHue->getFloat() * 255, backgroundSaturation->getFloat() * 255, backgroundBrightness->getFloat() * 255, backgroundAlpha->getFloat() * 255);
        } else {
            newColor = ofColor::fromHsb(backgroundHue->getFloat() * 255, backgroundSaturation->getFloat() * 255, backgroundBrightness->getFloat() * 255, backgroundAlpha->getFloat() * 255);
        };
        ofBackground(newColor);
    };
    // init
    ofSetColor(255.0f);
    // draw layers
    TXDrawLayersBase::draw((TXDRAWLAYERSRULE)drawLayersRule->getInt());
    
    // draw gui
    //        if (guiBuilt) {
    //            gui.draw();
    //        };
    if (showFrameRate) {
        ofSetColor(0.0f);
        ofDrawBitmapString("framerate fps: "+ofToString(ofGetFrameRate(), 2), 20, 50);
        ofSetColor(255.0f);
        ofDrawBitmapString("framerate fps: "+ofToString(ofGetFrameRate(), 2), 22, 52);
    };
    if (showTXVText) {
        ofSetColor(255.0f);
        ofDrawBitmapString("TXV     Version: " + txvVersionString + "     Status: " + currentStatusText, 60, 90);
    };
}

//--------------------------------------------------------------

int TXSystem::validateIDAllocator(string idType) {
    bool addNew = false;
    // add IDallocator if needed
    if (allIDAllocators.size() > 0) {
        map<string, ofPtr<TXIDAllocator> >::iterator itIDAllocator = allIDAllocators.find(idType);
        if (itIDAllocator == allIDAllocators.end()) {
            addNew = true;
        };
    } else {
        addNew = true;
    }
    if (addNew) {
        allIDAllocators[idType] = ofPtr<TXIDAllocator>(new TXIDAllocator);
    };
    return 0;
}

int TXSystem::getNextIDForType(string idType) {
    int nextID;
    validateIDAllocator(idType);
    nextID = allIDAllocators[idType]->getNextID();
    return nextID;
}

string TXSystem::getNextNameForType(string idType) {
    int holdID = getNextIDForType(idType);
    string idString = ofToString(holdID, 3, '0');
    std::stringstream ss;
    ss << idType << "_" << holdID;
    string uniqueName = ss.str(); // returns std::string object
    return uniqueName;
}

void TXSystem::adjustNextID(string argIDType, int argID) {
    // make sure next module id is higher than argID
    int storedID;
    validateIDAllocator(argIDType);
    storedID = allIDAllocators[argIDType]->getNextIDWithoutChange();
    if ((argID + 1) > storedID ) {
        allIDAllocators[argIDType]->setNextID(argID + 1);
    }
}

int TXSystem::getWindowWidth() {
    return currentWindowWidth;
}

int TXSystem::getWindowHeight() {
    return currentWindowHeight;
}

ofPtr<TXModuleBase> TXSystem::addModule(string newModuleType, int newModuleID) {
    int holdModuleID;
    float currentMasterBpm;
    string holdName = getNextNameForType(newModuleType);
    if (newModuleID == -1) {
        holdModuleID = getNextIDForType("moduleID");
    } else {
        holdModuleID = newModuleID;
        adjustNextID("moduleID", newModuleID);
    };
    ofLogNotice() << "TXSystem::addModule - name/ ID: " << holdName << " / " << holdModuleID;
    // create new module using factory
    ofPtr<TXModuleBase> newModule(TXModuleFactory::NewTXModule(newModuleType));
    newModule->baseSetup(this, holdModuleID, newModuleType, holdName);
    // init
    currentMasterBpm = masterBpm->getFloat();
    newModule->setMasterBpm(currentMasterBpm);
    // add to collections
    allModules[holdModuleID] = newModule;
    if (newModule->canDraw) {
        allDrawModules[holdModuleID] = newModule;
    };
    if (newModule->canDrawLayers) {
        allDrawLayersModules[holdModuleID] = newModule;
    };
    // rebuildGui();
    return newModule;
}

ofPtr<TXModuleBase> TXSystem::addNode(int sourceModuleID, string sourceName, int destinationModuleID, string destinationName, float modAmount, bool negativeModulation, bool active, int newModuleID) {
    int holdModuleID;
    string holdName = getNextNameForType("TXModNode");
    if (newModuleID == -1) {
        holdModuleID = getNextIDForType("moduleID");
    } else {
        holdModuleID = newModuleID;
        adjustNextID("moduleID", newModuleID);
    };
    ofLogNotice() << "TXSystem::addNode - name / ID: " << holdName << " / " << holdModuleID;
    // create new node
    ofPtr<TXModNode> newNodeModule(new TXModNode);
    newNodeModule->baseSetup(this, holdModuleID, "TXModNode", holdName);
    newNodeModule->setup(sourceModuleID, sourceName, destinationModuleID, destinationName, modAmount, negativeModulation, active);
    // add to collections
    allModules[holdModuleID] = newNodeModule;
    allNodes[holdModuleID] = newNodeModule;
    // rebuildGui();
    return newNodeModule;
}

ofPtr<TXModuleBase>  TXSystem::addDrawConnection(int sourceModuleID, int destinationModuleID, int layerNo, int newModuleID) {
    // NOTE: all inputs must be validated before calling this method
    int holdModuleID;
    string holdName = getNextNameForType("TXDrawConnection");
    if (newModuleID == -1) {
        holdModuleID = getNextIDForType("moduleID");
    } else {
        holdModuleID = newModuleID;
        adjustNextID("moduleID", newModuleID);
    };
    ofLogNotice() << "TXSystem::addDrawConnection - name / ID: " << holdName << " / " << holdModuleID;
    // create new node
    ofPtr<TXDrawConnection> newDrawConnection(new TXDrawConnection);
    newDrawConnection->baseSetup(this, holdModuleID, "TXDrawConnection", holdName);
    newDrawConnection->setup(sourceModuleID, destinationModuleID, layerNo);
    // add to collections
    allModules[holdModuleID] = newDrawConnection;
    allDrawConnections[holdModuleID] = newDrawConnection;
    // rebuildGui();
    return newDrawConnection;
}

ofPtr<TXAsset>  TXSystem::addAsset(int assetType, string fileNameArg, int newAssetID, int assetBankNo) {
    int holdAssetID;
    if (newAssetID == -1) {
        holdAssetID = getNextIDForType(getAssetTypeString(assetType));
    } else {
        holdAssetID = newAssetID;
        adjustNextID(getAssetTypeString(assetType), newAssetID);
    };    
    // create new asset
    ofPtr<TXAsset> newAsset(new TXAsset(assetType, fileNameArg, holdAssetID, assetBankNo));
    // add to collection
    map<int, ofPtr <TXAsset> > * mapPtr = getAssetMap(assetType);
    mapPtr->insert(std::make_pair(holdAssetID, newAsset));
    // rebuildGui();
    return newAsset;
}

bool TXSystem::setNodeConnections(int nodeModuleID, int sourceModuleID, string sourceName, int destinationModuleID, string destinationName) {
    // if inputs valid then update
    if (isValidModuleID(nodeModuleID) && isValidModSource(sourceModuleID, sourceName) && isValidModDestination(destinationModuleID, destinationName)) {
        allNodes[nodeModuleID]->setSourceModuleID(sourceModuleID);
        allNodes[nodeModuleID]->setSourceName(sourceName);
        allNodes[nodeModuleID]->setDestinationModuleID(destinationModuleID);
        allNodes[nodeModuleID]->setDestinationName(destinationName);
        return true;
    } else {
        return false;
    };
}

bool TXSystem::deleteModule(int moduleIDArg) {
    ofLogNotice() << "TXSystem::deleteModule - ID: " << moduleIDArg;
    // mark module for deletion
    map<int, ofPtr <TXModuleBase> >::iterator itMod = allModules.find(moduleIDArg);
    if (itMod != allModules.end()) {
        itMod->second->markForDeletion();
    } else {
        return false;
    };
    
    // remove if referenced in any other modules
    itMod = allModules.begin();
    for (itMod=allModules.begin(); itMod!=allModules.end(); ++itMod)
    {
        itMod->second->removeExtImageModuleReferences(moduleIDArg);
    };

    // mark any connected nodes for deletion
    map<int, ofPtr <TXModNode> >::iterator itNode = allNodes.begin();
    for (itNode=allNodes.begin(); itNode!=allNodes.end(); ++itNode)
    {
        if (
            // itNode->second->getModuleID() == moduleIDArg ||
            itNode->second->getSourceModuleID() == moduleIDArg || 
            itNode->second->getDestinationModuleID() == moduleIDArg)
        {
            itNode->second->markForDeletion();
        }
    };
    
    // now ready to delete
    deleteMarkedModules();
    return true;
}

bool TXSystem::deleteNode(int nodeModuleID) {
    
    // NOTE - THIS ASSUMES THAT ANY NODES MODULATING THIS NODE ARE RECURVSIVELY DELETED BEFORE THIS NODE
    // CURRENTLY THIS IS HANDLED IN THE TX MODULAR BUT COULD BE AN ISSUE IF CONTROLLING TXV DIRECTLY BY OSC
    
    return deleteModule(nodeModuleID);
}

bool TXSystem::deleteAsset(int assetType, int assetID) {
    map<int, ofPtr <TXAsset> > * mapPtr = getAssetMap(assetType);
    map<int, ofPtr <TXAsset> >::iterator itAsset = mapPtr->find(assetID);
    if (itAsset != mapPtr->end()) {
        // remove asset from any modules
        map<int, ofPtr <TXModuleBase> >::iterator itMod = allModules.begin();
        for(; itMod != allModules.end(); ++itMod) {
            if (assetType == TXASSETTYPE_IMAGE) {
                itMod->second->removeImageAssetReferences(assetID);
            } else if (assetType == TXASSETTYPE_MOVIE){
                itMod->second->removeMovieAssetReferences(assetID);
            } else if (assetType == TXASSETTYPE_SVG){
                itMod->second->removeSvgAssetReferences(assetID);
            } else if (assetType == TXASSETTYPE_CUBE){
                itMod->second->removeCubeAssetReferences(assetID);
            } else if (assetType == TXASSETTYPE_3DMODEL){
                itMod->second->remove3DModelAssetReferences(assetID);
            } else if (assetType == TXASSETTYPE_FONT){
                itMod->second->removeFontAssetReferences(assetID);
            };
        }
        // then delete
        mapPtr->erase(itAsset);;
        ofLogNotice() << "TXSystem::deleteAsset - Type, ID: " << assetType << ", " << assetID;
        return true;
    } {
        ofLogNotice() << "Warning Asset Not Found: TXSystem::deleteAsset - Type, ID: " << assetType << ", " << assetID;
    };
    return false;
}

void TXSystem::deleteMarkedModules() {
    
//    if (iter->second == moduleIDArg) {
//        multimap<int, int>::iterator save_iter = iter;
//        ++save_iter;
//        drawLayerModules.erase(iter);
//        iter = save_iter;
//    } else {
//        ++iter;
//    }

    // delete marked from allNodes
    map<int, ofPtr <TXModNode> >::iterator iter1 = allNodes.begin();
    map<int, ofPtr <TXModNode> >::iterator iter1_save;
    for(; iter1 != allNodes.end(); ) {
        if (iter1->second->isMarkedForDeletion()) {
            iter1_save = iter1;
            ++iter1;
            allNodes.erase(iter1_save);
            // ofLogNotice() << "TXSystem::delete a Node";  // testing xxx
        } else {
            ++iter1;
        }
    }
    // delete marked from allModules
    map<int, ofPtr <TXModuleBase> >::iterator iter2 = allModules.begin();
    map<int, ofPtr <TXModuleBase> >::iterator iter2_save;
    for(; iter2 != allModules.end(); ) {
        if (iter2->second->isMarkedForDeletion()) {
            iter2_save = iter2;
            ++iter2;
            allModules.erase(iter2_save);
            // ofLogNotice() << "TXSystem::delete a Module";  // testing xxx
        } else {
            ++iter2;
        }
    }
    // delete marked from allDrawModules
    map<int, ofPtr <TXModuleBase> >::iterator iter3 = allDrawModules.begin();
    map<int, ofPtr <TXModuleBase> >::iterator iter3_save;
    for(; iter3 != allDrawModules.end(); ) {
        if (iter3->second->isMarkedForDeletion()) {
            iter3_save = iter3;
            ++iter3;
            allDrawModules.erase(iter3_save);
            // ofLogNotice() << "TXSystem::delete a DrawModule";  // testing xxx
        } else {
            ++iter3;
        }
    }
    // delete marked from allDrawLayersModules
    map<int, ofPtr <TXModuleBase> >::iterator iter4 = allDrawLayersModules.begin();
    map<int, ofPtr <TXModuleBase> >::iterator iter4_save;
    for(; iter4 != allDrawLayersModules.end(); ) {
        if (iter4->second->isMarkedForDeletion()) {
            iter4_save = iter4;
            ++iter4;
            allDrawLayersModules.erase(iter4_save);
            // ofLogNotice() << "TXSystem::delete a DrawLayersModule";  // testing xxx
        } else {
            ++iter4;
        }
    }
    // delete marked from allDrawConnections
    map<int, ofPtr <TXDrawConnection> >::iterator iter5 = allDrawConnections.begin();
    map<int, ofPtr <TXDrawConnection> >::iterator iter5_save;
    for(; iter5 != allDrawConnections.end(); ) {
        if (iter5->second->isMarkedForDeletion()) {
            iter5_save = iter5;
            ++iter5;
            allDrawConnections.erase(iter5_save);
            // ofLogNotice() << "TXSystem::delete a DrawConnection";  // testing xxx
        } else {
            ++iter5;
        }
    }
}

bool TXSystem::deleteDrawConnection(int moduleIDArg) {
    int sourceModuleID;
    int destinationModuleID;
    int layerNo;
    // check if valid ID
    map<int, ofPtr <TXDrawConnection> >::iterator iter = allDrawConnections.find(moduleIDArg);
    if (iter != allDrawConnections.end()) {
        sourceModuleID = iter->second->getSourceModuleID();
        destinationModuleID = iter->second->getDestinationModuleID();
        layerNo = iter->second->layerNo;
    } else {
        return false;
    };
    if (deleteModule(moduleIDArg)) {
        // if inputs valid then remove
        if (isValidDrawModuleID(sourceModuleID)) {
            if (destinationModuleID == moduleID) {
                removeDrawModule(sourceModuleID, layerNo);
                return true;
            } else if (isValidDrawLayersModuleID(destinationModuleID) ) {
                allDrawLayersModules[destinationModuleID]->removeDrawModule(sourceModuleID, layerNo);
                return true;
            };
        };
    };
    return false;
}

bool TXSystem::setDrawConnection(int moduleIDArg, int sourceModuleIDArg, int destinationModuleIDArg, int layerNoArg, bool activeArg) {
    if (!isValidModuleID(moduleIDArg)) {
        return false;
    };
    
    ofPtr<TXDrawConnection> holdDrawConnection = allDrawConnections[moduleIDArg];
    int prevSourceModuleID = holdDrawConnection->getSourceModuleID();
    int prevLayerNo = holdDrawConnection->layerNo;

    // remove old draw connection
    if (holdDrawConnection->getDestinationModuleID() == moduleID) {
        removeDrawModule(prevSourceModuleID, prevLayerNo);
    } else if (isValidDrawLayersModuleID(destinationModuleIDArg) ) {
        allDrawLayersModules[holdDrawConnection->getDestinationModuleID()]->removeDrawModule(prevSourceModuleID, prevLayerNo);
    } else {
        return false;
    };
    // update draw connection module
    holdDrawConnection->setSourceModuleID(sourceModuleIDArg);
    holdDrawConnection->setDestinationModuleID(destinationModuleIDArg);
    holdDrawConnection->layerNo = layerNoArg;
    
    // set active
    setDrawConnectionActive(moduleIDArg, layerNoArg, activeArg);
    return false;
}

bool TXSystem::setDrawConnectionLayerNo(int moduleIDArg, int oldLayerNo, int newLayerNo) {
    int sourceModuleID;
    int destinationModuleID;
    // check if valid ID
    map<int, ofPtr <TXDrawConnection> >::iterator iter = allDrawConnections.find(moduleIDArg);
    if (iter != allDrawConnections.end()) {
        sourceModuleID = iter->second->getSourceModuleID();
        destinationModuleID = iter->second->getDestinationModuleID();
    } else {
        return false;
    };
    
    // if inputs valid then remove & add again
    if (isValidDrawModuleID(sourceModuleID)) {
        if (destinationModuleID == moduleID) {
            if (oldLayerNo > -1) {
                removeDrawModule(sourceModuleID, oldLayerNo);
            };
            addDrawModule(sourceModuleID, newLayerNo);
            return true;
        } else if (isValidDrawLayersModuleID(destinationModuleID) ) {
            if (oldLayerNo > -1) {
                allDrawLayersModules[destinationModuleID]->removeDrawModule(sourceModuleID, oldLayerNo);
            };
            allDrawLayersModules[destinationModuleID]->addDrawModule(sourceModuleID, newLayerNo);
            return true;
        };
    };
    return false;
}

bool TXSystem::setDrawConnectionActive(int moduleIDArg, int layerNoArg, bool activeArg) {
    int sourceModuleID;
    int destinationModuleID;
    // check if valid ID
    map<int, ofPtr <TXDrawConnection> >::iterator iter = allDrawConnections.find(moduleIDArg);
    if (iter != allDrawConnections.end()) {
        sourceModuleID = iter->second->getSourceModuleID();
        destinationModuleID = iter->second->getDestinationModuleID();
    } else {
        return false;
    };
    
    // if inputs valid then remove or add draw module
    if (isValidDrawModuleID(sourceModuleID)) {
        if (destinationModuleID == moduleID) {
            if (activeArg == false) {
                removeDrawModule(sourceModuleID, layerNoArg);
            } else {
                addDrawModule(sourceModuleID, layerNoArg);
            };
            return true;
        } else if (isValidDrawLayersModuleID(destinationModuleID) ) {
            if (activeArg == false) {
                allDrawLayersModules[destinationModuleID]->removeDrawModule(sourceModuleID, layerNoArg);
            } else {
                allDrawLayersModules[destinationModuleID]->addDrawModule(sourceModuleID, layerNoArg);
            };
            return true;
        };
    };
    return false;
}

/////////////////////////////////////////////

bool TXSystem::isValidModuleID(int moduleIDArg) {
    // system itself is a valid Module
    if (moduleIDArg == moduleID) {
        return true;
    } else {
        map<int, ofPtr <TXModuleBase> >::iterator iterMod = allModules.find(moduleIDArg);
        if (iterMod != allModules.end() && (iterMod->second != NULL)) {
            return true;
        };
    };
    return false;
}

ofTexture * TXSystem::getModuleTexture(int moduleIDArg) {
    // system itself is a valid Module
    if (moduleIDArg == moduleID) {
        return getTexture();
    } else {
        map<int, ofPtr <TXModuleBase> >::iterator iterMod = allModules.find(moduleIDArg);
        if (iterMod != allModules.end() && (iterMod->second != NULL)) {
            return iterMod->second->getTexture();
        };
    };
    return NULL;
}

bool TXSystem::isValidDrawModuleID(int moduleIDArg) {
    bool confirm = false;
    map<int, ofPtr <TXModuleBase> >::iterator iterMod = allDrawModules.find(moduleIDArg);
    if (iterMod != allModules.end() && (iterMod->second != NULL)) {
        confirm = true;
    };
    return confirm;
}

bool TXSystem::isValidDrawLayersModuleID(int moduleIDArg) {
    bool confirm = false;
    map<int, ofPtr <TXModuleBase> >::iterator iterMod = allDrawLayersModules.find(moduleIDArg);
    if (iterMod != allModules.end() && (iterMod->second != NULL)) {
        confirm = true;
    };
    return confirm;
}

bool TXSystem::isValidModSource(int sourceModuleIDArg, string sourceName) {
    bool confirm = false;
    if (moduleID == sourceModuleIDArg) {
        confirm = true;
    } else if (isValidModuleID(sourceModuleIDArg)) {
        if (allModules[sourceModuleIDArg]->isValidModSource(sourceName)) {
            confirm = true;
        };
    };
    return confirm;
}

bool TXSystem::isValidModDestination(int moduleIDArg, string paramaterName) {
    bool confirm = false;
    int pos;
    if (moduleID == moduleIDArg) {
        confirm = true;
    } else if (isValidModuleID(moduleIDArg)) {
        pos = allModules[moduleIDArg]->parameters.getPosition(paramaterName);
        if (pos != -1) {
            // don't allow group
            if (allModules[moduleIDArg]->parameters[pos].getEscapedName() != "group") {
                confirm = true;
            };
        };
    };
    return confirm;
}

bool TXSystem::areValidNodeConnections(int sourceModuleID, string sourceName, int destinationModuleID, string destinationName) {
    if (isValidModSource(sourceModuleID, sourceName) && isValidModDestination(destinationModuleID, destinationName)) {
        return true;
    };
    return false;
}

bool TXSystem::isValidAssetID(int assetTypeArg, int assetIDArg) {
    map<int, ofPtr <TXAsset> > * mapPtr = getAssetMap(assetTypeArg);
    map<int, ofPtr <TXAsset> >::iterator iter = mapPtr->find(assetIDArg);
    if (iter != mapPtr->end()) {
        return true;
    };
    return false;
}

ofPtr <TXAsset> TXSystem::getAsset(int assetTypeArg, int assetIDArg) {
    map<int, ofPtr <TXAsset> > * mapPtr = getAssetMap(assetTypeArg);
    map<int, ofPtr <TXAsset> >::iterator iter = mapPtr->find(assetIDArg);
    if (iter != mapPtr->end()) {
        return iter->second;
    } {
        ofLogNotice() << "!!!Warning Asset Not Found: ";
        ofLogNotice() << "TXSystem::getAsset - Type, ID: " << assetTypeArg << ", " << assetIDArg;
    };
}

map<int, ofPtr <TXAsset> > * TXSystem::getAssetMap(int assetType) {
    map<int, ofPtr <TXAsset> > * mapPtr;
    switch (assetType) {
        case TXASSETTYPE_IMAGE:
            mapPtr = &allImageAssets;
            break;
        case TXASSETTYPE_MOVIE:
            mapPtr = &allMovieAssets;
            break;
        case TXASSETTYPE_SVG:
            mapPtr = &allSvgAssets;
            break;
        case TXASSETTYPE_CUBE:
            mapPtr = &allCubeAssets;
            break;
        case TXASSETTYPE_3DMODEL:
            mapPtr = &allModelAssets;
            break;
        case TXASSETTYPE_FONT:
            mapPtr = &allFontAssets;
            break;
        default:
            mapPtr = &allImageAssets;
            ofLogNotice() << "TXSystem::getAssetMap - ERROR invalid asset type: " << assetType;
            break;
    };
    return mapPtr;
}

bool TXSystem::isMarkedForDel(int moduleIDArg) {
    bool confirm = false;
    map<int, ofPtr <TXModuleBase> >::iterator iterMod = allModules.find(moduleIDArg);
    if (iterMod != allModules.end()) {
        if (iterMod->second->isMarkedForDeletion()) {
            confirm = true;
        };
    } else {
        confirm = true;
    };
    return confirm;
}

string TXSystem::getAssetTypeString(int assetType) {
    string outString;
    switch (assetType) {
        case TXASSETTYPE_IMAGE:
            outString = "TXImageAsset";
            break;
        case TXASSETTYPE_MOVIE:
            outString = "TXMovieAsset";
            break;
        case TXASSETTYPE_SVG:
            outString = "TXSvgAsset";
            break;
        case TXASSETTYPE_CUBE:
            outString = "TXCubeAsset";
            break;
        case TXASSETTYPE_3DMODEL:
            outString = "TX3DModelAsset";
            break;
        case TXASSETTYPE_FONT:
            outString = "TXFontAsset";
            break;
        default:
            outString = "ERROR invalid asset type: " + ofToString(assetType);
            ofLogNotice() << "TXSystem::getAssetTypeString - ERROR invalid asset type: " << assetType;
            break;
    };
    return outString;
}

void TXSystem::deleteAllModules() {
    allNodes.clear();
    allDrawConnections.clear();
    allDrawModules.clear();
    allDrawLayersModules.clear();
    allModules.clear();
    allImageAssets.clear();
    allMovieAssets.clear();
    allSvgAssets.clear();
    allCubeAssets.clear();
    allModelAssets.clear();
    allFontAssets.clear();
    allIDAllocators.clear();
    drawLayerModules.clear();
    
    // this is called to reserve the firstID for "moduleID" used by system
    int moduleID = getNextIDForType("moduleID");
    currentStatusText = "full reset complete. all modules deleted.";
    oldMasterBpm = 0;
}

void TXSystem::applyNodeModulations() {
    // reset all modulations - except for nodes
    resetModulation();
    map<int, ofPtr <TXModuleBase> >::iterator itModule = allModules.begin();
    for (itModule=allModules.begin(); itModule!=allModules.end(); ++itModule)
    {
        // ignore nodes until later in method
        if (itModule->second->getModuleType() != "TXModNode") {
            itModule->second->resetModulation();
        };
    };
    // apply all node modulations
    map<int, ofPtr <TXModNode> >::iterator itNode = allNodes.begin();
    for (itNode=allNodes.begin(); itNode!=allNodes.end(); ++itNode)
    {
        // if active, add modulation
        if (itNode->second->parameters.getBool("active")) {
            int sourceID = itNode->second->getSourceModuleID();
            int destID = itNode->second->getDestinationModuleID();
            string sourceName = itNode->second->getSourceName();
            string destName = itNode->second->getDestinationName();
            ofPtr<TXModuleBase> holdModule;
            bool validSource = false;
            float value;
            float scale;
            bool negativeModulation;
            // validate source & dest
            if (sourceID == moduleID) {
                validSource = true;
                value = modSources[sourceName]->getValue();
            } else {
                if (!isValidModuleID(sourceID)) {
                    ofLogNotice() << "TXSystem::applyNodeModulations() - invalid sourceID: " << sourceID;
                    validSource = false;
                } else {
                    validSource = true;
                    value = allModules[sourceID]->modSources[sourceName]->getValue();
                };
            };
            if (validSource) {
                scale = itNode->second->modParameters["modAmount"]->getFloat();
                negativeModulation = itNode->second->modParameters["negativeModulation"]->getBool();
                if (destID == moduleID) {
                    modParameters[destName]->updateModulation(value, scale, negativeModulation);
                } else {
                    if (isValidModuleID(destID)) {
                        allModules[destID]->modParameters[destName]->updateModulation(value, scale, negativeModulation);
                    } else {
                        ofLogNotice() << "TXSystem::applyNodeModulations() - invalid destID: " << destID;
                    };
                };
            };
        };
        // now reset node's modulation
        itNode->second->resetModulation();
    };
}

unsigned long TXSystem::getCurrentFrameNo(){
    return currentFrameNo;
}

void TXSystem::resetAllTime() {
    // testing xxx
    int count;// for testing

    currentTime = 0;
    startTimeOffset = ofGetElapsedTimef();
    // testing xxx - to get proper start behaviour
    // oldTime = 0 - (1.0 / targetFrameRate);
    oldTime = 0;
    currentFrameNo = 0;
    // reset time for all modules
    count = 0; // for testing
    map<int, ofPtr <TXModuleBase> >::iterator itModule = allModules.begin();
    for (itModule=allModules.begin(); itModule!=allModules.end(); ++itModule)
    {
        itModule->second->resetTime();
    };
};

/*   // gui removed for now
 
 void TXSystem::rebuildGui() {
    
    // TEST CODE:
    
    //    gui.clear();
    //    gui.setup(parameters);
    //    sync.setup((ofParameterGroup&)gui.getParameter(), localPort, host, remotePort);
    //    guiBuilt = true;
    
    // No gui for now
    //    // sync to system parameters directly
    //    sync.setup((ofParameterGroup&) parameters, localPort, host, remotePort);
    
}
 */

float TXSystem::getCurrentTime() {
    return currentTime;
}

//--------------------------------------------------------------

// for listeners

void TXSystem::antiAliasingChanged(bool & antiAliasingArg) {
    if (antiAliasingArg) {
        ofEnableAntiAliasing();
    } else {
        ofDisableAntiAliasing();
    };
}

void TXSystem::neverDropFramesChanged(bool & neverDropFramesArg) {
    resetAllTime();
}

void TXSystem::showFullScreenChanged(bool & showFullScreenArg) {
    // add a delay before turning on FullScreen
    float   makeFullScreenDelay = 0.5;
    
    if (!showFullScreenArg) {
        ofSetFullscreen(false);
    } else {
        makeFullScreenTime = ofGetElapsedTimef() + makeFullScreenDelay;
    };
}

void TXSystem::targetFrameRateChanged(int & targetFrameRateArg) {
    ofSetFrameRate(targetFrameRateArg);
    
}

//--------------------------------------------------------------

void TXSystem::windowSizeModeChanged(int & windowSizeModeArg) {
    updateWindowSize();
}

void  TXSystem::customWindowWidthChanged(int & windowWidthArg) {
    if (windowSizeMode == WINDOWSIZEMODE_CUSTOM) {
        updateWindowSize();
    };
}

void  TXSystem::customWindowHeightChanged(int & windowHeightArg) {
    if (windowSizeMode == WINDOWSIZEMODE_CUSTOM) {
        updateWindowSize();
    };
}

void  TXSystem::updateWindowSize() {
    switch (windowSizeMode) {
        case WINDOWSIZEMODE_CUSTOM:
            ofSetWindowShape(customWindowWidth, customWindowHeight);
            break;
        case WINDOWSIZEMODE_480_360:
            return ;
            ofSetWindowShape(480, 360);
            break;
        case WINDOWSIZEMODE_858_480:
            ofSetWindowShape(858, 480);
            break;
        case WINDOWSIZEMODE_1280_720:
            ofSetWindowShape(1280, 720);
            break;
        case WINDOWSIZEMODE_1920_1080:
            ofSetWindowShape(1920, 1080);
            break;
        case WINDOWSIZEMODE_2560_1440:
            ofSetWindowShape(2560, 1440);
            break;
        case WINDOWSIZEMODE_3840_2160:
            ofSetWindowShape(3840, 2160);
            break;
        default:
            ofSetWindowShape(customWindowWidth, customWindowHeight);
            break;
    }
}

//--------------------------------------------------------------

void TXSystem::keyPressed(int key){
    
    if (key == 'o' || (key == 'O') ){
        openSystemRequested = true;
        saveSystemRequested = false;
    };
    
    if (key == 's' || (key == 'S') ){
        openSystemRequested = false;
        saveSystemRequested = true;
    };
    
    if (key == 'x' || (key == 'X') ){
        closeTXVRequested = true;
    };
    
}

void TXSystem::keyReleased(int key){
    
}

//--------------------------------------------------------------

void TXSystem::mouseMoved(int x, int y ){
    float holdX, holdY;
    // only update if within screen bounds
    if ((x >= 0) && (x <= currentWindowWidth) && (y >= 0) && (y <= currentWindowHeight) ) {
        holdX = (float) x/ currentWindowWidth;
        holdY = (float) y/ currentWindowHeight;
        mouseMovedX->setValue(holdX);
        mouseMovedY->setValue(holdY);
        mouseMovedOrDraggedX->setValue(holdX);
        mouseMovedOrDraggedY->setValue(holdY);
    };
}

void TXSystem::mouseDragged(int x, int y, int button){
    float holdX, holdY;
    // only update if within screen bounds
    if ((x >= 0) && (x <= currentWindowWidth) && (y >= 0) && (y <= currentWindowHeight) ) {
        holdX = (float) x/ currentWindowWidth;
        holdY = (float) y/ currentWindowHeight;
        mouseDraggedX->setValue(holdX);
        mouseDraggedY->setValue(holdY);
        mouseMovedOrDraggedX->setValue(holdX);
        mouseMovedOrDraggedY->setValue(holdY);
    };
}

void TXSystem::mousePressed(int x, int y, int button){
    float holdX, holdY;
    // toggle showCursor
    if (showCursor) {
        ofGetWindowPtr()->hideCursor();
        showCursor = false;
    } else {
        ofGetWindowPtr()->showCursor();
        showCursor = true;
    };
    // only update if within screen bounds
    if ((x >= 0) && (x <= currentWindowWidth) && (y >= 0) && (y <= currentWindowHeight) ) {
        mouseButtonPressed->setValue(1.0);
        holdX = (float) x/ currentWindowWidth;
        holdY = (float) y/ currentWindowHeight;
        mouseDraggedX->setValue(holdX);
        mouseDraggedY->setValue(holdY);
        mouseMovedOrDraggedX->setValue(holdX);
        mouseMovedOrDraggedY->setValue(holdY);
    };
}

void TXSystem::mouseReleased(int x, int y, int button){
    float holdX, holdY;
    mouseButtonPressed->setValue(0.0);
    // apart from mouse release, only update if within screen bounds
    if ((x >= 0) && (x <= currentWindowWidth) && (y >= 0) && (y <= currentWindowHeight) ) {
        holdX = (float) x/ currentWindowWidth;
        holdY = (float) y/ currentWindowHeight;
        mouseMovedX->setValue(holdX);
        mouseMovedY->setValue(holdY);
        mouseMovedOrDraggedX->setValue(holdX);
        mouseMovedOrDraggedY->setValue(holdY);
    };
}

void TXSystem::windowResized(int w, int h) {
    windowResizeCalled = true;
    windowResizeWidth = w;
    windowResizeHeight = h;
}

void TXSystem::windowResizeInform() {
    // tell all modules
    map<int, ofPtr <TXModuleBase> >::iterator itModule = allModules.begin();
    for (itModule=allModules.begin(); itModule!=allModules.end(); ++itModule)
    {
        itModule->second->windowResized(windowResizeWidth, windowResizeHeight);
    };
    windowResizeCalled = false;
}

//--------------------------------------------------------------

/*     // not working yet
 
 void TXSystem::openSystemFromFile(){
 ofXml XML;
 int assetID, moduleID;
 string fileName, moduleType;
 // Open File Dialog
 ofFileDialogResult openFileResult= ofSystemLoadDialog("Select TXV file");
 if (openFileResult.bSuccess){
 // Check if XML file is valid
 if ( XML.load(openFileResult.getPath()) ){
 if(XML.setTo("TXV_System")) {
 // delete all modules & reset
 deleteAllModules();
 resetAllTime();
 // system data
 if(XML.exists("systemData")) {
 XML.setTo("systemData");
 if (XML.exists("module")) {
 XML.setTo("module");
 loadXMLData(XML);
 XML.setToParent();
 };
 XML.setToParent();
 };
 
 // add assets
 if(XML.exists("allImageAssets")) {
 XML.setTo("allImageAssets");
 if(XML.exists("imageAsset"))
 {
 XML.setTo("imageAsset[0]");
 do {
 assetID = XML.getValue<int>("assetID");
 fileName = XML.getValue<string>("fileName");
 addAsset(TXASSETTYPE_IMAGE, fileName, assetID);
 }
 while( XML.setToSibling() );
 XML.setToParent();
 };
 XML.setToParent();
 };
 if(XML.exists("allMovieAssets")) {
 XML.setTo("allMovieAssets");
 if(XML.exists("movieAsset"))
 {
 XML.setTo("movieAsset[0]");
 do {
 assetID = XML.getValue<int>("assetID");
 fileName = XML.getValue<string>("fileName");
 addAsset(TXASSETTYPE_MOVIE, fileName, assetID);
 }
 while( XML.setToSibling() );
 XML.setToParent();
 };
 XML.setToParent();
 };
 if(XML.exists("allSvgAssets")) {
 XML.setTo("allSvgAssets");
 if(XML.exists("svgAsset"))
 {
 XML.setTo("svgAsset[0]");
 do {
 assetID = XML.getValue<int>("assetID");
 fileName = XML.getValue<string>("fileName");
 addAsset(TXASSETTYPE_SVG, fileName, assetID);
 }
 while( XML.setToSibling() );
 XML.setToParent();
 };
 XML.setToParent();
 };
 if(XML.exists("allCubeAssets")) {
 XML.setTo("allCubeAssets");
 if(XML.exists("cubeAsset"))
 {
 XML.setTo("cubeAsset[0]");
 do {
 assetID = XML.getValue<int>("assetID");
 fileName = XML.getValue<string>("fileName");
 addAsset(TXASSETTYPE_CUBE, fileName, assetID);
 }
 while( XML.setToSibling() );
 XML.setToParent();
 };
 XML.setToParent();
 };
 if(XML.exists("allModelAssets")) {
 XML.setTo("allModelAssets");
 if(XML.exists("modelAsset"))
 {
 XML.setTo("modelAsset[0]");
 do {
 assetID = XML.getValue<int>("assetID");
 fileName = XML.getValue<string>("fileName");
 addAsset(TXASSETTYPE_3DMODEL, fileName, assetID);
 }
 while( XML.setToSibling() );
 XML.setToParent();
 };
 XML.setToParent();
 };
 if(XML.exists("allFontAssets")) {
 XML.setTo("allFontAssets");
 if(XML.exists("fontAsset"))
 {
 XML.setTo("fontAsset[0]");
 do {
 assetID = XML.getValue<int>("assetID");
 fileName = XML.getValue<string>("fileName");
 addAsset(TXASSETTYPE_FONT, fileName, assetID);
 }
 while( XML.setToSibling() );
 XML.setToParent();
 };
 XML.setToParent();
 };
 if(XML.exists("allModuleSpecs")) {
 // add modules
 XML.setTo("allModuleSpecs");
 if (XML.exists("moduleSpec"))
 {
 XML.setTo("moduleSpec[0]");
 do {
 moduleID = XML.getValue<int>("moduleID");
 moduleType = XML.getValue<string>("moduleType");
 addModule(moduleType, moduleID);
 }
 while( XML.setToSibling() );
 XML.setToParent();
 };
 XML.setToParent();
 };
 if(XML.exists("allModulesData")) {
 // add data for all modules
 XML.setTo("allModulesData");
 if (XML.exists("module"))
 {
 XML.setTo("module[0]");
 do {
 moduleID = XML.getValue<int>("moduleID");
 if (isValidModuleID(moduleID)) {
 allModules[moduleID]->loadXMLData(XML);
 };
 }
 while( XML.setToSibling() );
 XML.setToParent();
 };
 };
 if(XML.exists("allNodes")) {
 // add nodes
 XML.setTo("allNodes");
 if (XML.exists("module"))
 {
 XML.setTo("module[0]");
 do {
 moduleID = XML.getValue<int>("moduleID");
 int sourceModuleID = XML.getValue<int>("sourceModuleID");
 string sourceName = XML.getValue<string>("sourceName");
 int destinationModuleID = XML.getValue<int>("destinationModuleID");
 string destinationName = XML.getValue<string>("destinationName");
 addNode(sourceModuleID, sourceName, destinationModuleID, destinationName, 0.0, false, false, moduleID);
 allNodes[moduleID]->loadXMLData(XML);
 }
 while( XML.setToSibling() );
 XML.setToParent();
 };
 XML.setToParent();
 };
 if(XML.exists("allDrawConnections")) {
 // add draw connections
 XML.setTo("allDrawConnections");
 if (XML.exists("module"))
 {
 XML.setTo("module[0]");
 do {
 moduleID = XML.getValue<int>("moduleID");
 int sourceModuleID = XML.getValue<int>("sourceModuleID");
 int destinationModuleID = XML.getValue<int>("destinationModuleID");
 int layerNo = XML.getValue<int>("layerNo");
 addDrawConnection(sourceModuleID, destinationModuleID, layerNo, moduleID);
 allDrawConnections[moduleID]->loadXMLData(XML);
 }
 while( XML.setToSibling() );
 XML.setToParent();
 };
 XML.setToParent();
 };
 // log
 ofLogNotice("File opened: "  + openFileResult.getPath() + " loaded.");
 } else {
 ofLogNotice("ERROR - File is not a valid TXV System: "  + openFileResult.getPath());
 };
 } else {
 ofLogNotice("Unable to open file: "  + openFileResult.getPath());
 };
 };
 }
 
 void TXSystem::saveSystemToFile(){
 ofXml XML;
 ofFileDialogResult saveFileResult = ofSystemSaveDialog(ofGetTimestampString() + ".txv", "Save TXV file");
 if (saveFileResult.bSuccess){
 // add root
 XML.addChild("TXV_System");
 XML.setTo("TXV_System");
 
 // system data
 XML.addChild("systemData");
 XML.setTo("systemData");
 ofXml tempXML(getXMLData());
 XML.addXml(tempXML);
 XML.setToParent();
 
 // get assets
 if (allImageAssets.size() > 0) {
 XML.addChild("allImageAssets");
 XML.setTo("allImageAssets");
 for (auto asset: allImageAssets) {
 ofXml tempXML;
 tempXML.addChild("imageAsset");
 tempXML.setTo("imageAsset");
 tempXML.addValue("assetID", ofToString(asset.second->getAssetID()));
 tempXML.addValue("fileName", ofToString(asset.second->getFileName()));
 XML.addXml(tempXML);
 }
 XML.setToParent();
 };
 if (allMovieAssets.size() > 0) {
 XML.addChild("allMovieAssets");
 XML.setTo("allMovieAssets");
 for (auto asset: allMovieAssets) {
 ofXml tempXML;
 tempXML.addChild("movieAsset");
 tempXML.setTo("movieAsset");
 tempXML.addValue("assetID", ofToString(asset.second->getAssetID()));
 tempXML.addValue("fileName", ofToString(asset.second->getFileName()));
 XML.addXml(tempXML);
 }
 XML.setToParent();
 };
 if (allSvgAssets.size() > 0) {
 XML.addChild("allSvgAssets");
 XML.setTo("allSvgAssets");
 for (auto asset: allSvgAssets) {
 ofXml tempXML;
 tempXML.addChild("svgAsset");
 tempXML.setTo("svgAsset");
 tempXML.addValue("assetID", ofToString(asset.second->getAssetID()));
 tempXML.addValue("fileName", ofToString(asset.second->getFileName()));
 XML.addXml(tempXML);
 }
 XML.setToParent();
 };
 if (allCubeAssets.size() > 0) {
 XML.addChild("allCubeAssets");
 XML.setTo("allCubeAssets");
 for (auto asset: allCubeAssets) {
 ofXml tempXML;
 tempXML.addChild("cubeAsset");
 tempXML.setTo("cubeAsset");
 tempXML.addValue("assetID", ofToString(asset.second->getAssetID()));
 tempXML.addValue("fileName", ofToString(asset.second->getFileName()));
 XML.addXml(tempXML);
 }
 XML.setToParent();
 };
 if (allModelAssets.size() > 0) {
 XML.addChild("allModelAssets");
 XML.setTo("allModelAssets");
 for (auto asset: allModelAssets) {
 ofXml tempXML;
 tempXML.addChild("modelAsset");
 tempXML.setTo("modelAsset");
 tempXML.addValue("assetID", ofToString(asset.second->getAssetID()));
 tempXML.addValue("fileName", ofToString(asset.second->getFileName()));
 XML.addXml(tempXML);
 }
 XML.setToParent();
 };
 if (allFontAssets.size() > 0) {
 XML.addChild("allFontAssets");
 XML.setTo("allFontAssets");
 for (auto asset: allFontAssets) {
 ofXml tempXML;
 tempXML.addChild("fontAsset");
 tempXML.setTo("fontAsset");
 tempXML.addValue("assetID", ofToString(asset.second->getAssetID()));
 tempXML.addValue("fileName", ofToString(asset.second->getFileName()));
 XML.addXml(tempXML);
 }
 XML.setToParent();
 };
 if (allModules.size() > 0) {
 // get module Specs
 XML.addChild("allModuleSpecs");
 XML.setTo("allModuleSpecs");
 for (auto module: allModules) {
 if ((module.second->getModuleType() !=  "TXDrawConnection") && (module.second->getModuleType() !=  "TXModNode")) {
 ofXml tempXML;
 tempXML.addChild("moduleSpec");
 tempXML.setTo("moduleSpec");
 tempXML.addValue<int>("moduleID", module.second->getModuleID());
 tempXML.addValue<string>("moduleType", module.second->getModuleType());
 XML.addXml(tempXML);
 };
 }
 XML.setToParent();
 };
 if (allNodes.size() > 0) {
 // get nodes
 XML.addChild("allNodes");
 XML.setTo("allNodes");
 for (auto node: allNodes) {
 ofXml tempXML(node.second->getXMLData());
 tempXML.setTo("module");
 tempXML.addValue<int>("moduleID", node.second->getModuleID());
 tempXML.addValue<int>("sourceModuleID", node.second->getSourceModuleID());
 tempXML.addValue<int>("destinationModuleID", node.second->getDestinationModuleID());
 tempXML.addValue<string>("sourceModuleID", node.second->getSourceName());
 tempXML.addValue<string>("destinationModuleID", node.second->getDestinationName());
 XML.addXml(tempXML);
 }
 XML.setToParent();
 };
 if (allDrawConnections.size() > 0) {
 // get draw connections
 XML.addChild("allDrawConnections");
 XML.setTo("allDrawConnections");
 for (auto drawConnection: allDrawConnections) {
 ofXml tempXML(drawConnection.second->getXMLData());
 tempXML.setTo("module");
 tempXML.addValue<int>("moduleID", drawConnection.second->getModuleID());
 tempXML.addValue<int>("sourceModuleID", drawConnection.second->getSourceModuleID());
 tempXML.addValue<int>("destinationModuleID", drawConnection.second->getDestinationModuleID());
 XML.addXml(tempXML);
 }
 XML.setToParent();
 };
 if (allModules.size() > 0) {
 // get all module data
 XML.addChild("allModulesData");
 XML.setTo("allModulesData");
 for (auto module: allModules) {
 if ((module.second->getModuleType() !=  "TXDrawConnection") && (module.second->getModuleType() !=  "TXModNode")) {
 ofXml tempXML(module.second->getXMLData());
 XML.addXml(tempXML);
 };
 };
 XML.setToParent();
 };
 
 // save file;
 XML.save(saveFileResult.filePath);
 ofLogVerbose("TXV File Saved: "  + saveFileResult.filePath);
 };
 }
 */



