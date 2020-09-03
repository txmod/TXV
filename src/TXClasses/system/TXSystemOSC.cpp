/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 *
 *  This file contains all the TXSystem methods for dealing with OSC message
 *
 */

#include "TXSystem.h"
#include "TXModuleFactory.h"


void TXSystem::initOsc() {
    oscSender.setup(host, remotePort);
    oscReceiver.setup(localPort);
    maxTimeDifference = 0;
    oscSyncInProgress = false;
}

void TXSystem::checkOscMessages() {
	ofxOscMessage msg;
    float elapsedTime = ofGetElapsedTimef();
    float msgTime;
    float executionTime;
    bool keepLooping;
    bool processMsg;
   

    if(oscReceiver.hasWaitingMessages()){
        while(oscReceiver.hasWaitingMessages()){
            oscReceiver.getNextMessage(msg);
            redirectOscMsg(msg);
        };
    };
    
    /*
    // testing xxx
     if (storedOscMessages.size() > 0) {
         // ofLogNotice() << "================ " ;
        //  ofLogNotice() << "TXSystem::checkOscMessages() - currentFrameNo: " << currentFrameNo;
        ofLogNotice() << "TXSystem::checkOscMessages() - storedOscMessages.size():  " << storedOscMessages.size();
     };
     */
    
    // process storedOscMessages
    keepLooping = true;
    map<int, ofxOscMessage>::iterator iterMsg = storedOscMessages.begin();
    while (keepLooping && (iterMsg!=storedOscMessages.end()))
    {
        msg = iterMsg->second;
        // if no latency, process all messages, else process messages while execution time !> current time
        if (ignoreOscLatency || (oscLatency == 0)) {
            processMsg = true;
        } else {
            processMsg = false;
            if (msg.getArgType(2) == OFXOSC_TYPE_FLOAT) {
                msgTime = msg.getArgAsFloat(2);
                executionTime = msgTime + maxTimeDifference + oscLatency;
                if (executionTime > elapsedTime) {
                    keepLooping = false;
                } else {
                    processMsg = true;
                };
            };
        };
        if (processMsg) {
            redirectSystemOscMsg(msg);
            iterMsg = storedOscMessages.erase(iterMsg);
        } else {
            ++iterMsg;
        };
    };
    
}

void TXSystem::redirectOscMsg(ofxOscMessage &msg) {
    int msgNo;
    string method;
    ofxOscMessage msgCopy;
    vector<string> address = ofSplitString(msg.getAddress(),"/",true);
    if (address.size() > 1) {
        // if address[1] is system name
        if (address[1] == getName()) {
            // if system code is valid
            if (msg.getArgType(0) == OFXOSC_TYPE_INT32) {
                if (msg.getArgAsInt32(0) == systemCode) {
                    
                    // systemData1/2 not currently used
                    // string systemData1;
                    // string systemData2;
                    
                    // Redirect based on address
                    method = address[2];
                    
                    // process sync messages immediately
                    if (method == "sync")  {
                        oscSync(msg);
                    } else if (method == "syncStart") {
                        oscSyncStart(msg);
                        // ofLogNotice() << "TXSystem: Received Sync Start";   // testing xxx
                    } else if (method == "syncStop") {
                        oscSyncStop(msg);
                    } else if (method == "setIgnoreOscLatency") {
                        oscSetIgnoreOscLatency(msg);
                    } else {
                        // add other messages to sorted array (map)
                        if (msg.getArgType(1) == OFXOSC_TYPE_INT32) {
                            msgNo = msg.getArgAsInt32(1);
                            msgCopy.copy(msg);
                            storedOscMessages[msgNo] = msgCopy;
                        };
                    };
                } else {
                    sendOscReply("Error: Invalid System Code" + ofToString(msg.getArgAsInt32(0)), msg);
                };
            } else {
                sendOscReply("Error: Invalid System Code - type not int32", msg);
            };
        } else {
            processNonSystemOscMsg(msg);
        };
    } else {
        processNonSystemOscMsg(msg);
    };
}


bool TXSystem::redirectSystemOscMsg(ofxOscMessage &msg) {
    // OSC SYSTEM Messages expected arg format is: [int systemCode, int msgSeqNo, float msgTime, string systemData1, string systemData2,  ...dataArgs]
    vector<string> address = ofSplitString(msg.getAddress(),"/",true);
    string method = address[2];
    bool pauseAfterMsg = false;
    
    // testing xxx
    //if (method != "setModuleParameter") {
    //    ofLogNotice() << "TXSystem::checkOscMessages() - msg.address: " << msg.getAddress();
    //};
    
    // check for valid system actions
    if (method == "setModuleParameter") {
        oscSetModuleParameter(msg);
    } else if (method == "setModuleParameterFloat256") {
        oscSetModuleParameterFloat256(msg);
    } else if (method == "freezeSystem") {
        freezeSystemOverride = true;
        sendOscReply("Confirmation: Freeze System", msg);
        pauseAfterMsg = true;
    } else if (method == "unfreezeSystem") {
        freezeSystemOverride = false;
        sendOscReply("Confirmation: Unfreeze System", msg);
        pauseAfterMsg = true;
    } else if (method == "ping") {
        oscPing(msg);
    } else if (method == "systemData") {
        oscSystemData(msg);
        // ofLogNotice() << "TXSystem: Sent System Data";   // testing xxx
        currentStatusText = "System Connected.";
        pauseAfterMsg = true;
    } else if (method == "killTXV") {
        sendOscReply("Confirmation: TXV has been stopped and closed.", msg);
        ofLogNotice() << "TXSystem: Confirmation: TXV has been stopped and closed.";
        ofExit();
    } else if (method == "deleteAllModules") {
        deleteAllModules();
        sendOscReply("Confirmation: Deleted All Modules", msg);
        ofLogNotice() << "TXSystem: Confirmation: Deleted All Modules";
        currentStatusText = "Ready.";
        showTXVText = true; // turn on system text
        pauseAfterMsg = true;
    } else if (method == "resetAllTime") {
        resetAllTime();
        sendOscReply("Confirmation: Reset All Time", msg);
        pauseAfterMsg = true;
        ofLogNotice() << "TXSystem: Confirmation: Reset All Time";
    } else if (method == "addAsset") {
        oscAddAsset(msg);
        showTXVText = false; // turn off system text
        pauseAfterMsg = true;
    } else if (method == "deleteAsset") {
        oscDeleteAsset(msg);
        pauseAfterMsg = true;
    } else if (method == "addModule") {
        oscAddModule(msg);
        showTXVText = false; // turn off system text
        pauseAfterMsg = true;
    } else if (method == "deleteModule") {
        oscDeleteModule(msg);
        pauseAfterMsg = true;
    } else if (method == "deleteNode") {
        oscDeleteNode(msg);
        pauseAfterMsg = true;
    } else if (method == "addNode") {
        oscAddNode(msg);
        pauseAfterMsg = true;
    } else if (method == "setNodeConnections") {
        oscSetNodeConnections(msg);
    } else if (method == "addDrawConnection") {
        oscAddDrawConnection(msg);
        pauseAfterMsg = true;
    } else if (method == "setDrawConnection") {
        oscSetDrawConnection(msg);
    } else if (method == "deleteDrawConnection") {
        oscDeleteDrawConnection(msg);
        pauseAfterMsg = true;
    } else if (method == "setModuleAsset") {
        oscSetModuleAsset(msg);
    } else if (method == "setModuleExtImageModule") {
        oscSetModuleExtImageModule(msg);
    } else if (method == "printModuleInputsOutputs") {
        oscPrintModuleParameters(msg);
        oscPrintModuleOutputs(msg);
    } else {
        sendOscReply("Error: Invalid System Action: " + method, msg);
    };
    return pauseAfterMsg;
}

void TXSystem::processNonSystemOscMsg(ofxOscMessage &msg) {
    // pass osc msg to relevent modules
    multimap<string, int>::iterator iterOscAddress;
    for (iterOscAddress=oscAddresses.begin(); iterOscAddress!=oscAddresses.end(); ++iterOscAddress)
    {
        // if address matches then call module
        if (iterOscAddress->first == msg.getAddress()) {
            map<int, ofPtr <TXModuleBase> >::iterator iterModule = parentSystem->allModules.find(iterOscAddress->second);
            if (iterModule != parentSystem->allModules.end()) {
                iterModule->second->processOscMsg(msg);
            };
        };
    }
}

void TXSystem::registerOscAddress(string oscAddressArg, int moduleIDArg) {
    if (oscAddressArg != "") {
        oscAddresses.insert(std::make_pair(oscAddressArg, moduleIDArg));
    };
}

void TXSystem::deregisterOscAddress(string oscAddressArg, int moduleIDArg) {
    bool found = false;
    for (multimap<string, int>::iterator iter = oscAddresses.begin(); iter != oscAddresses.end();)
    {
        if (!found && (iter->first == oscAddressArg) && (iter->second == moduleIDArg)) {
            multimap<string, int>::iterator save_iter = iter;
            ++save_iter;
            oscAddresses.erase(iter);
            iter = save_iter;
            found = true; // only erase 1 instance
        } else {
            ++iter;
        }
    }
}

void TXSystem::deregisterOscAddressesForModule(int moduleIDArg) {
    // remove all OSC addresses for moduleID
    for (multimap<string, int>::iterator iter = oscAddresses.begin(); iter != oscAddresses.end();)
    {
        if (iter->second == moduleIDArg) {
            multimap<string, int>::iterator save_iter = iter;
            ++save_iter;
            oscAddresses.erase(iter);
            iter = save_iter;
        } else {
            ++iter;
        }
    }
}

void TXSystem::sendOscReply(string reply, ofxOscMessage &msg) {
    ofxOscMessage outMsg;
    int msgSeqNo = getNextIDForType("oscMsgNo");
    int replyToMsgSeqNo = -1;
    if (msg.getArgType(1) == OFXOSC_TYPE_INT32) {
        replyToMsgSeqNo = msg.getArgAsInt32(1);
    };
    outMsg.setAddress("/TX_Modular_System/OSCReply");
    outMsg.setRemoteEndpoint(msg.getRemoteIp(), msg.getRemotePort());
    // reply msg format: [int msgSeqNo, int replyToMsgSeqNo, string sendAddress, string reply]
    outMsg.addIntArg(msgSeqNo);
    outMsg.addIntArg(replyToMsgSeqNo);
    outMsg.addStringArg(msg.getAddress());
    outMsg.addStringArg(reply);
    oscSender.sendMessage(outMsg);

    // testing xxx
    // ofLogNotice() << "=============================================    ";
    // ofLogNotice() << "TXSystem::sendOscReply() - reply: " << reply;
}

void TXSystem::sendOscAddModuleConfirm(string reply, ofxOscMessage &msg, int moduleID, string moduleType, string moduleName, bool canDraw, bool canDrawLayers, int numModInputs, int numModOutputs, int hasTexture) {
    ofxOscMessage outMsg;
    int msgSeqNo = getNextIDForType("oscMsgNo");
    int replyToMsgSeqNo = -1;
    if (msg.getArgType(1) == OFXOSC_TYPE_INT32) {
        replyToMsgSeqNo = msg.getArgAsInt32(1);
    };
    outMsg.setAddress("/TX_Modular_System/OSCReply");
    outMsg.setRemoteEndpoint(msg.getRemoteIp(), msg.getRemotePort());
    // reply msg format: [int msgSeqNo, int replyToMsgSeqNo, string sendAddress, string reply, int moduleID, sting moduleType, string moduleName, int canDraw, int canDrawLayers, int numModInputs, int numModOutputs, int numExtImageModuleSlots]
    outMsg.addIntArg(msgSeqNo);
    outMsg.addIntArg(replyToMsgSeqNo);
    outMsg.addStringArg(msg.getAddress());
    outMsg.addStringArg(reply);
    outMsg.addIntArg(moduleID);
    outMsg.addStringArg(moduleType);
    outMsg.addStringArg(moduleName);
    outMsg.addIntArg(canDraw);
    outMsg.addIntArg(canDrawLayers);
    outMsg.addIntArg(numModInputs);
    outMsg.addIntArg(numModOutputs);
    outMsg.addIntArg(hasTexture);
    // send
    oscSender.sendMessage(outMsg);
}

void TXSystem::sendOscAddAssetConfirm(string reply, ofxOscMessage &msg, int assetType, string  assetTypeString, int assetID, string fileName, bool fileExists, int assetBankNo) {
    ofxOscMessage outMsg;
    int msgSeqNo = getNextIDForType("oscMsgNo");
    int replyToMsgSeqNo = -1;
    if (msg.getArgType(1) == OFXOSC_TYPE_INT32) {
        replyToMsgSeqNo = msg.getArgAsInt32(1);
    };
    outMsg.setAddress("/TX_Modular_System/OSCReply");
    outMsg.setRemoteEndpoint(msg.getRemoteIp(), msg.getRemotePort());
    // reply msg format: [int msgSeqNo, int replyToMsgSeqNo, string sendAddress, string reply, int assetType, string  assetTypeString, int assetID, string fileName, bool fileExists]
    outMsg.addIntArg(msgSeqNo);
    outMsg.addIntArg(replyToMsgSeqNo);
    outMsg.addStringArg(msg.getAddress());
    outMsg.addStringArg(reply);
    outMsg.addIntArg(assetType);
    outMsg.addStringArg(assetTypeString);
    outMsg.addIntArg(assetID);
    outMsg.addStringArg(fileName);
    outMsg.addIntArg(fileExists);
    outMsg.addIntArg(assetBankNo);
    // send
    oscSender.sendMessage(outMsg);
}

void TXSystem::oscSyncStart(ofxOscMessage &msg) {
    oscSyncInProgress = true;
    oscTimeDifferences.clear();
    oscSync(msg, false);
    sendOscReply("Sync Start Received", msg);
}

void TXSystem::oscSyncStop(ofxOscMessage &msg) {
    oscTimeDifferences.clear();
    oscSync(msg, false);
    sendOscReply("Sync Stop Received", msg);
    oscSyncInProgress = false;
}

void TXSystem::oscSync(ofxOscMessage &msg, bool sendReply) {
    // OSC Message: [int systemCode, int msgSeqNo, float msgTime, string systemData1, string systemData2, ]
    float msgTime;
    float timeDiff;
    float maxTimeDiff;
    float ellapsedTime;
    if (oscSyncInProgress && (msg.getArgType(2) == OFXOSC_TYPE_FLOAT)) {
        msgTime = msg.getArgAsFloat(2);
        ellapsedTime = ofGetElapsedTimef();
        timeDiff = ellapsedTime - msgTime;
        maxTimeDifference = timeDiff;
        oscTimeDifferences.push_back(timeDiff);
        // keep size to last 20
        if (oscTimeDifferences.size() > 20) {
            oscTimeDifferences.erase(oscTimeDifferences.begin());
        }
        for (auto timeDifference: oscTimeDifferences) {
            maxTimeDifference = max(maxTimeDifference, timeDifference);
        }
        if (sendReply) {
            sendOscReply("Sync Received", msg);
        };
    };
}

void TXSystem::oscPing(ofxOscMessage &msg) {
    sendOscReply("Ping Back", msg);
}

void TXSystem::oscSystemData(ofxOscMessage &msg) {
    if ((msg.getNumArgs() >= (oscDataOffset + 1)) && (msg.getArgType(oscDataOffset) == OFXOSC_TYPE_INT32)) {
        remotePort = msg.getArgAsInt32(oscDataOffset);
        oscSender.setup(host, remotePort);
    };
    // send confirmation
    sendOscAddModuleConfirm("Confirmation: System Data", msg, getModuleID(), "TXSystem", getName(), canDraw, canDrawLayers, modParameters.size(), modSources.size(), hasTexture);
}
void TXSystem::oscAddAsset(ofxOscMessage &msg) {
    // OSC Message: [int systemCode, int msgSeqNo, float msgTime, string systemData1, string systemData2, int assetType, string fileName, int assetID, int assetBankNo]
    if ((msg.getNumArgs() >= (oscDataOffset + 4)) && (msg.getArgType(oscDataOffset) == OFXOSC_TYPE_INT32) && (msg.getArgType(oscDataOffset + 1) == OFXOSC_TYPE_STRING) && (msg.getArgType(oscDataOffset + 2) == OFXOSC_TYPE_INT32) && (msg.getArgType(oscDataOffset + 3) == OFXOSC_TYPE_INT32)) {
        int assetType = msg.getArgAsInt32(oscDataOffset);
        string fileName = msg.getArgAsString(oscDataOffset + 1);
        int assetID = msg.getArgAsInt32(oscDataOffset + 2);
        int assetBankNo= msg.getArgAsInt32(oscDataOffset + 3);
        // don't add if id already exists
        if (isValidAssetID(assetType, assetID)) {
            sendOscReply("Error: Unable to add asset. Invalid asset ID: " +  ofToString(assetID) , msg);
        } else {
            ofPtr<TXAsset> newAsset = addAsset(assetType, fileName, assetID, assetBankNo);
            // send confirmation

//            void TXSystem::sendOscAddAssetConfirm(string reply, ofxOscMessage &msg, int assetType, string  assetTypeString, int assetID, string fileName, bool fileExists, int assetBankNo) {

                sendOscAddAssetConfirm("Confirmation: Add Asset", msg, newAsset->getAssetType(), newAsset->getAssetTypeString(), newAsset->getAssetID(), newAsset->getFileName(), newAsset->getFileExists(), newAsset->getAssetBankNo());
        };
    };
}

void TXSystem::oscDeleteAsset(ofxOscMessage &msg) {
    // OSC Message: [int systemCode, int msgSeqNo, float msgTime, string systemData1, string systemData2, int assetType, int assetID]
    if ((msg.getNumArgs() >= (oscDataOffset + 2)) && (msg.getArgType(oscDataOffset) == OFXOSC_TYPE_INT32) && (msg.getArgType(oscDataOffset + 1) == OFXOSC_TYPE_INT32)) {
        int assetType = msg.getArgAsInt32(oscDataOffset);
        int assetID = msg.getArgAsInt32(oscDataOffset + 1);
        if (deleteAsset(assetType, assetID)) {
            sendOscReply("Confirmation: Asset Deleted", msg);
        } else {
            sendOscReply("Error: Unable to delete asset. Invalid data", msg);
        };
    } else {
        sendOscReply("Error: Unable to delete asset. Invalid data", msg);
    };
}

void TXSystem::oscAddModule(ofxOscMessage &msg) {
    // OSC Message: [int systemCode, int msgSeqNo, float msgTime, string systemData1, string systemData2, string modType, int newModuleID]
    if ((msg.getNumArgs() >= (oscDataOffset + 2)) && (msg.getArgType(oscDataOffset) == OFXOSC_TYPE_STRING) && (msg.getArgType(oscDataOffset + 1) == OFXOSC_TYPE_INT32)) {
        string modType = msg.getArgAsString(oscDataOffset);
        int newModuleID = msg.getArgAsInt32(oscDataOffset + 1);
        // don't add if id already exists
        if (isValidModuleID(newModuleID)) {
            sendOscReply("Error: Unable to add module. Invalid Module ID: " +  ofToString(newModuleID) , msg);
        } else {
            if (TXModuleFactory::isValidModuleType(modType)) {
                ofPtr<TXModuleBase> newModule = addModule(modType, newModuleID);
                // send confirmation
                sendOscAddModuleConfirm("Confirmation: Module Added", msg, newModule->getModuleID(), modType, newModule->getName(), newModule->canDraw, newModule->canDrawLayers, newModule->modParameters.size(), newModule->modSources.size(), newModule->hasTexture);
            } else {
                sendOscReply("Error: Unable to add module. Invalid Module Type: " + modType, msg);
            };
        };
    };
}

void TXSystem::oscDeleteModule(ofxOscMessage &msg) {
    // OSC Message: [int systemCode, int msgSeqNo, float msgTime, string systemData1, string systemData2, int moduleID]
    if ((msg.getNumArgs() >= (oscDataOffset + 1)) && (msg.getArgType(oscDataOffset) == OFXOSC_TYPE_INT32)) {
        if (deleteModule(msg.getArgAsInt32(oscDataOffset))) {
            sendOscReply("Confirmation: Module Deleted", msg);
        } else {
            sendOscReply("Error: Unable to delete module. Invalid Module ID", msg);
        };
    } else {
        sendOscReply("Error: Unable to delete module. Invalid Module ID", msg);
    };
}

void TXSystem::oscAddNode(ofxOscMessage &msg) {
    // OSC Message: [int systemCode, int msgSeqNo, float msgTime, string systemData1, string systemData2, int sourceModuleID, string sourceName, int destinationModuleID, string destinationName, float modAmount, int negativeModulation, int active, int nodeModuleID]
    if ((msg.getNumArgs() >= (oscDataOffset + 8)) && (msg.getArgType(oscDataOffset) == OFXOSC_TYPE_INT32) && (msg.getArgType(oscDataOffset + 1) == OFXOSC_TYPE_STRING) && (msg.getArgType(oscDataOffset + 2) == OFXOSC_TYPE_INT32) && (msg.getArgType(oscDataOffset + 3) == OFXOSC_TYPE_STRING) && (msg.getArgType(oscDataOffset + 4)== OFXOSC_TYPE_FLOAT) && (msg.getArgType(oscDataOffset + 5)== OFXOSC_TYPE_INT32) && (msg.getArgType(oscDataOffset + 6)== OFXOSC_TYPE_INT32)  && (msg.getArgType(oscDataOffset + 7)== OFXOSC_TYPE_INT32))
    {
        int sourceModuleID = msg.getArgAsInt32(oscDataOffset);
        string sourceName = msg.getArgAsString(oscDataOffset + 1);
        int destinationModuleID = msg.getArgAsInt32(oscDataOffset + 2);
        string destinationName = msg.getArgAsString(oscDataOffset + 3);
        int newModuleID = msg.getArgAsInt32(oscDataOffset + 7);
        // don't add if id already exists
        if (isValidModuleID(newModuleID)) {
            sendOscReply("Error: Unable to add node. ID already exists: " +  ofToString(newModuleID) , msg);
        } else {
            if (areValidNodeConnections(sourceModuleID, sourceName, destinationModuleID, destinationName)) {
                ofPtr<TXModuleBase> newModule = addNode(sourceModuleID, sourceName, destinationModuleID, destinationName, msg.getArgAsFloat(oscDataOffset + 4), (bool) msg.getArgAsInt32(oscDataOffset + 5), (bool) msg.getArgAsInt32(oscDataOffset + 6), newModuleID);
                // send confirmation
                sendOscAddModuleConfirm("Confirmation: Node Added", msg, newModule->getModuleID(), "TXModNode", newModule->getName(), newModule->canDraw, newModule->canDrawLayers, newModule->modParameters.size(), newModule->modSources.size(), newModule->hasTexture);
            };
        };
    };
}

void TXSystem::oscSetNodeConnections(ofxOscMessage &msg) {
    // OSC Message: [int systemCode, int msgSeqNo, float msgTime, string systemData1, string systemData2, int moduleIDArg, int sourceModuleID, string sourceName, int destinationModuleID, string destinationName]
    if ((msg.getNumArgs() >= (oscDataOffset + 5)) && (msg.getArgType(oscDataOffset) == OFXOSC_TYPE_INT32) && (msg.getArgType(oscDataOffset + 1) == OFXOSC_TYPE_INT32) && (msg.getArgType(oscDataOffset + 2) == OFXOSC_TYPE_STRING) && (msg.getArgType(oscDataOffset + 3) == OFXOSC_TYPE_INT32) && (msg.getArgType(oscDataOffset + 4)== OFXOSC_TYPE_STRING))
    {
        int moduleIDArg = msg.getArgAsInt32(oscDataOffset);
        int sourceModuleID = msg.getArgAsInt32(oscDataOffset + 1);
        string sourceName = msg.getArgAsString(oscDataOffset + 2);
        int destinationModuleID = msg.getArgAsInt32(oscDataOffset + 3);
        string destinationName = msg.getArgAsString(oscDataOffset + 4);
        // set if valid
        if (isValidModuleID(moduleIDArg) && areValidNodeConnections(sourceModuleID, sourceName, destinationModuleID, destinationName)) {
            setNodeConnections(moduleIDArg, sourceModuleID, sourceName, destinationModuleID, destinationName);
        } else {
            sendOscReply("Error: Unable to Set Node Connections - Invalid Data ", msg);
        };
    } else {
        sendOscReply("Error: Unable to Set Node Connections - Invalid Data ", msg);
    };
}

void TXSystem::oscDeleteNode(ofxOscMessage &msg) {
    // OSC Message: [int systemCode, int msgSeqNo, float msgTime, string systemData1, string systemData2, int nodeModuleID]
    if ((msg.getNumArgs() >= (oscDataOffset + 1)) && (msg.getArgType(oscDataOffset) == OFXOSC_TYPE_INT32)) {
        if (deleteNode(msg.getArgAsInt32(oscDataOffset))) {
            sendOscReply("Confirmation: Node Deleted", msg);
        } else {
            sendOscReply("Error: Unable to Delete Node. Invalid Node Module ID", msg);
        };
    } else {
        sendOscReply("Error: Unable to Delete Node. Invalid Node Module ID", msg);
    };
}

void TXSystem::oscAddDrawConnection(ofxOscMessage &msg) {
    // OSC Message: [int systemCode, int msgSeqNo, float msgTime, string systemData1, string systemData2, int sourceModuleID, int destinationModuleID, int layerNo, int newModuleID]
    if ((msg.getNumArgs() >= (oscDataOffset + 4)) && (msg.getArgType(oscDataOffset) == OFXOSC_TYPE_INT32) && (msg.getArgType(oscDataOffset + 1) == OFXOSC_TYPE_INT32) && (msg.getArgType(oscDataOffset + 2) == OFXOSC_TYPE_INT32)  && (msg.getArgType(oscDataOffset + 3) == OFXOSC_TYPE_INT32))
    {
        int sourceModuleID = msg.getArgAsInt32(oscDataOffset);
        int destinationModuleID = msg.getArgAsInt32(oscDataOffset + 1);
        int layerNo = msg.getArgAsInt32(oscDataOffset + 2);
        int newModuleID = msg.getArgAsInt32(oscDataOffset + 3);
        // don't add if id already exists
        if (isValidModuleID(newModuleID)) {
            sendOscReply("Error: Unable to add Draw Connection. Invalid Module ID: " +  ofToString(newModuleID) , msg);
        } else {
            if (isValidDrawModuleID(sourceModuleID)) {
                // if destination is system then add source module
                if (destinationModuleID == moduleID) {
                    ofPtr<TXModuleBase> newModule = addDrawConnection(sourceModuleID, destinationModuleID, layerNo, newModuleID);
                    // send confirmation
                    sendOscAddModuleConfirm("Confirmation: Draw Connection Added", msg, newModule->getModuleID(), "TXDrawConnection", newModule->getName(), newModule->canDraw, newModule->canDrawLayers, newModule->modParameters.size(), newModule->modSources.size(), newModule->hasTexture);
                    
                    // else if destination is valid then add source module
                } else if (isValidDrawLayersModuleID(destinationModuleID) ) {
                    ofPtr<TXModuleBase> newModule = addDrawConnection(sourceModuleID, destinationModuleID, layerNo, newModuleID);
                    // send confirmation
                    sendOscAddModuleConfirm("Confirmation: Draw Connection Added", msg, newModule->getModuleID(), "TXDrawConnection", newModule->getName(), newModule->canDraw, newModule->canDrawLayers, newModule->modParameters.size(), newModule->modSources.size(), newModule->hasTexture);
                } else {
                    sendOscReply("Error: Unable to Add Draw Connection - Invalid destinationModuleID", msg);
                };
            } else {
                sendOscReply("Error: Unable to Add Draw Connection - Invalid sourceModuleID", msg);
            };
        };
    } else {
        sendOscReply("Error: Unable to Add Draw Connection - ID not found", msg);
    };
}

void TXSystem::oscSetDrawConnection(ofxOscMessage &msg) {
    // OSC Message: [int systemCode, int msgSeqNo, float msgTime, string systemData1, string systemData2, int moduleID, int sourceModuleID, int destinationModuleID, int layerNo, int active]
    if ((msg.getNumArgs() >= (oscDataOffset + 5)) && (msg.getArgType(oscDataOffset) == OFXOSC_TYPE_INT32) && (msg.getArgType(oscDataOffset + 1) == OFXOSC_TYPE_INT32) && (msg.getArgType(oscDataOffset + 2) == OFXOSC_TYPE_INT32)  && (msg.getArgType(oscDataOffset + 3) == OFXOSC_TYPE_INT32)  && (msg.getArgType(oscDataOffset + 4) == OFXOSC_TYPE_INT32))
    {
        int moduleID = msg.getArgAsInt32(oscDataOffset);
        int sourceModuleID = msg.getArgAsInt32(oscDataOffset + 1);
        int destinationModuleID = msg.getArgAsInt32(oscDataOffset + 2);
        int layerNo = msg.getArgAsInt32(oscDataOffset + 3);
        int active = msg.getArgAsInt32(oscDataOffset + 4);
        
        if (setDrawConnection(moduleID, sourceModuleID, destinationModuleID, layerNo, (bool) active)) {
            sendOscReply("Confirmation: Draw Connection Set", msg);
        } else {
            sendOscReply("Error: Unable to Set Draw Connection - Invalid Data", msg);
        };
    } else {
        sendOscReply("Error: Unable to Set Draw Connection - Invalid Data", msg);
    };
}

void TXSystem::oscDeleteDrawConnection(ofxOscMessage &msg) {
    // OSC Message: [int systemCode, int msgSeqNo, float msgTime, string systemData1, string systemData2, int moduleID]
    if ((msg.getNumArgs() >= (oscDataOffset + 1)) && (msg.getArgType(oscDataOffset) == OFXOSC_TYPE_INT32))
    {
        if (deleteDrawConnection(msg.getArgAsInt32(oscDataOffset))) {
            sendOscReply("Confirmation: Draw Connection Deleted", msg);
        } else {
            sendOscReply("Error: Unable to Delete Draw Connection - Error: Invalid ID", msg);
        };
    } else {
        sendOscReply("Error: Unable to Delete Draw Connection - ID not an Integer", msg);
    };
}

void TXSystem::oscSetModuleParameter(ofxOscMessage &msg) {
    // OSC Message: [int systemCode, int msgSeqNo, float msgTime, string systemData1, string systemData2, int moduleID, string parameterNameString, [anyType] newValue]
    if ((msg.getNumArgs() >= (oscDataOffset + 3)) && (msg.getArgType(oscDataOffset) == OFXOSC_TYPE_INT32) && (msg.getArgType(oscDataOffset + 1) == OFXOSC_TYPE_STRING))
    {
        int msgModuleID = msg.getArgAsInt32(oscDataOffset);
        
        // ignore message if id not known
        if (!isValidModuleID(msgModuleID)) {
            return;
        };
        string msgAddress = msg.getArgAsString(oscDataOffset + 1);
        vector<string> address = ofSplitString(msgAddress,"/",true);
        ofParameterGroup holdGroup;
        if (msgModuleID == moduleID) {
            holdGroup =  parameters;
        } else {
            holdGroup = allModules[msgModuleID]->parameters;
        };
        
        for(int i=1;i<address.size();i++){
            // if not last element then try and get group
            if (i != (address.size() - 1)) {
                if (!holdGroup.contains(address[i])) {
                    ofLogNotice() << "TXSystem::oscSetModuleParameter() -  Invalid Parameter Name :" << address[i];
                    return;
                }
                if (holdGroup.get(address[i]).type() != typeid(ofParameterGroup).name()) {
                    ofLogNotice() << "TXSystem::oscSetModuleParameter() -  Invalid Group - wrong type, Name :" << address[i];
                    return;
                }
                holdGroup = holdGroup.getGroup(address[i]);
                if (holdGroup.size() == 0) {
                    ofLogNotice() << "TXSystem::oscSetModuleParameter() -  Invalid Group - size 0, Name: " << address[i];
                    return;
                }
            } else {
                int pos = holdGroup.getPosition(address[i]);
                if (pos == -1) {
                    ofLogNotice() << "TXSystem::oscSetModuleParameter() -  Invalid Parameter Name/Group: " << address[i] << ", " << holdGroup.getName();
                    return;
                }
                string pType = holdGroup.get(pos).type();
                if(pType==typeid(ofParameter<int>).name() && msg.getArgType(oscDataOffset + 2)==OFXOSC_TYPE_INT32){
                    if (msg.getArgType(oscDataOffset + 2)==OFXOSC_TYPE_INT32) {
                        holdGroup.getInt(address[i]) = msg.getArgAsInt32(oscDataOffset + 2);
                    } else if (msg.getArgType(oscDataOffset + 2)==OFXOSC_TYPE_FLOAT) {
                        holdGroup.getInt(address[i]) = (int) msg.getArgAsFloat(oscDataOffset + 2);
                    }
                }else if(pType==typeid(ofParameter<float>).name()){
                    if (msg.getArgType(oscDataOffset + 2)==OFXOSC_TYPE_INT32) {
                        holdGroup.getFloat(address[i]) = msg.getArgAsInt32(oscDataOffset + 2);
                    } else if (msg.getArgType(oscDataOffset + 2)==OFXOSC_TYPE_FLOAT) {
                        holdGroup.getFloat(address[i]) = msg.getArgAsFloat(oscDataOffset + 2);
                    }
                }else if(pType==typeid(ofParameter<bool>).name()){
                    if (msg.getArgType(oscDataOffset + 2)==OFXOSC_TYPE_INT32) {
                        holdGroup.getBool(address[i]) = msg.getArgAsInt32(oscDataOffset + 2);
                    } else if (msg.getArgType(oscDataOffset + 2)==OFXOSC_TYPE_FLOAT) {
                        holdGroup.getBool(address[i]) = (int) msg.getArgAsFloat(oscDataOffset + 2);
                    }
                }else if(msg.getArgType(oscDataOffset + 2)==OFXOSC_TYPE_STRING){
                    holdGroup.getString(address[i]) = msg.getArgAsString(oscDataOffset + 2);
                }
            }
        };
    };
}

void TXSystem::oscSetModuleParameterFloat256(ofxOscMessage &msg) {
    // OSC Message: [int systemCode, int msgSeqNo, float msgTime, string systemData1, string systemData2, int moduleID, string parameterNameString, float0, float1, ...]
    if ((msg.getNumArgs() >= (oscDataOffset + 3)) && (msg.getArgType(oscDataOffset) == OFXOSC_TYPE_INT32) && (msg.getArgType(oscDataOffset + 1) == OFXOSC_TYPE_STRING))
    {
        int msgModuleID = msg.getArgAsInt32(oscDataOffset);
        
        // ignore message if id not known
        if (!isValidModuleID(msgModuleID)) {
            return;
        };
        string msgAddress = msg.getArgAsString(oscDataOffset + 1);
        vector<string> address = ofSplitString(msgAddress,"/",true);
        ofParameterGroup holdGroup;
        if (msgModuleID == moduleID) {
            holdGroup =  parameters;
        } else {
            holdGroup = allModules[msgModuleID]->parameters;
        };
        
        for(int i=1;i<address.size();i++){
            //            // if not last element then try and get group
            //            if (i != (address.size() - 1)) {
            //                if (!holdGroup.contains(address[i])) {
            //                    ofLogNotice() << "TXSystem::oscSetModuleParameter() -  Invalid Parameter Name :" << address[i];
            //                    return;
            //                }
            //                if (holdGroup.get(address[i]).type() != typeid(ofParameterGroup).name()) {
            //                    ofLogNotice() << "TXSystem::oscSetModuleParameter() -  Invalid Group - wrong type, Name :" << address[i];
            //                    return;
            //                }
            //                holdGroup = holdGroup.getGroup(address[i]);
            //                if (holdGroup.size() == 0) {
            //                    ofLogNotice() << "TXSystem::oscSetModuleParameter() -  Invalid Group - size 0, Name: " << address[i];
            //                    return;
            //                }
            //            } else {
            int pos = holdGroup.getPosition(address[i]);
            if (pos == -1) {
                ofLogNotice() << "TXSystem::oscSetModuleParameterFloat256() -  Invalid Parameter Name/Group: " << address[i] << ", " << holdGroup.getName();
                return;
            }
            
            ofParameterGroup floatArrayGroup = holdGroup.getGroup(pos);
            float holdVal;
            for(int i=0; i<256; i++) {
                if (msg.getArgType(oscDataOffset + 2+i)==OFXOSC_TYPE_FLOAT) {
                    holdVal = msg.getArgAsFloat(oscDataOffset + 2+i);
                    floatArrayGroup.getFloat(i) = holdVal;
                };
            };
            //            };
        };
    };
}

void TXSystem::oscSetModuleAsset(ofxOscMessage &msg) {
    // OSC Message: [int systemCode, int msgSeqNo, float msgTime, string systemData1, string systemData2, int moduleID, string assetNameString, int newAssetID]
    if ((msg.getNumArgs() >= (oscDataOffset + 4)) && (msg.getArgType(oscDataOffset) == OFXOSC_TYPE_INT32) && (msg.getArgType(oscDataOffset + 1) == OFXOSC_TYPE_STRING) && (msg.getArgType(oscDataOffset + 2) == OFXOSC_TYPE_INT32) && (msg.getArgType(oscDataOffset + 3) == OFXOSC_TYPE_INT32))
    {
        int msgModuleID = msg.getArgAsInt32(oscDataOffset);
        string assetNameString = msg.getArgAsString(oscDataOffset + 1);
        vector<string> assetNameSplit = ofSplitString(assetNameString,"/",true);
        int newAssetID = msg.getArgAsInt32(oscDataOffset + 2);
        int newBankNo = msg.getArgAsInt32(oscDataOffset + 3);
        
        if (isValidModuleID(msgModuleID)) {
            // set asset
            if (assetNameSplit[1] == "image") {
                allModules[msgModuleID]->setImageAssetSlot(assetNameSplit[2], newAssetID, newBankNo);
            } else if (assetNameSplit[1] == "movie") {
                allModules[msgModuleID]->setMovieAssetSlot(assetNameSplit[2], newAssetID, newBankNo);
            } else if (assetNameSplit[1] == "svg") {
                allModules[msgModuleID]->setSvgAssetSlot(assetNameSplit[2], newAssetID, newBankNo);
            } else if (assetNameSplit[1] == "cube") {
                allModules[msgModuleID]->setCubeAssetSlot(assetNameSplit[2], newAssetID, newBankNo);
            } else if (assetNameSplit[1] == "3DModel") {
                allModules[msgModuleID]->set3DModelAssetSlot(assetNameSplit[2], newAssetID, newBankNo);
            } else if (assetNameSplit[1] == "font") {
                allModules[msgModuleID]->setFontAssetSlot(assetNameSplit[2], newAssetID, newBankNo);
            } else {
                ofLogNotice() << "TXSystem::oscSetModuleAsset() -  Invalid assetName: " << assetNameString;
            };
        } else {
            ofLogNotice() << "TXSystem::oscSetModuleAsset() -  Invalid moduleID: " << msgModuleID;
            return;
        };
    };
}

void TXSystem::oscSetModuleExtImageModule(ofxOscMessage &msg) {
    // OSC Message: [int systemCode, int msgSeqNo, float msgTime, string systemData1, string systemData2, int moduleID, string xtImageModuleNameString, int newModuleID]
    if ((msg.getNumArgs() >= (oscDataOffset + 3)) && (msg.getArgType(oscDataOffset) == OFXOSC_TYPE_INT32) && (msg.getArgType(oscDataOffset + 1) == OFXOSC_TYPE_STRING) && (msg.getArgType(oscDataOffset + 2) == OFXOSC_TYPE_INT32))
    {
        int msgModuleID = msg.getArgAsInt32(oscDataOffset);
        string extImageModuleNameString = msg.getArgAsString(oscDataOffset + 1);
        vector<string> extImageModuleNameSplit = ofSplitString(extImageModuleNameString,"/",true);
        int newExtImageModuleID = msg.getArgAsInt32(oscDataOffset + 2);
        if (isValidModuleID(msgModuleID)) {
            // set extImageModule
            allModules[msgModuleID]->setExtImageModuleSlot(extImageModuleNameSplit[1], newExtImageModuleID);
        } else {
            ofLogNotice() << "TXSystem::oscSetModuleExtImageModule() -  Invalid moduleID: " << msgModuleID;
            return;
        };
    };
}

void TXSystem::oscSetIgnoreOscLatency(ofxOscMessage &msg) {
    // OSC Message: [int systemCode, int msgSeqNo, float msgTime, string systemData1, string systemData2, int boolAsInt]
    if ((msg.getNumArgs() >= (oscDataOffset + 1)) && (msg.getArgType(oscDataOffset) == OFXOSC_TYPE_INT32)) {
        int boolArg = msg.getArgAsInt32(oscDataOffset);
        if (boolArg == 1) {
            ignoreOscLatency = true;
            sendOscReply("Confirmation: IgnoreOscLatency is switched on", msg);
        } else {
            ignoreOscLatency = false;
            sendOscReply("Confirmation: IgnoreOscLatency is switched off", msg);
        };
    } else {
        sendOscReply("Error: Unable to set IgnoreOscLatency. Invalid data", msg);
    };
    
}

void TXSystem::oscPrintModuleParameters(ofxOscMessage &msg) {
    if ((msg.getNumArgs() >= (oscDataOffset + 1)) && (msg.getArgType(oscDataOffset) == OFXOSC_TYPE_INT32)) {
        int moduleIDArg = msg.getArgAsInt32(oscDataOffset);
        if (isValidModuleID(moduleIDArg)) {
            if (moduleIDArg == moduleID) {
                printModuleParameters();
            } else {
                allModules[moduleIDArg]->printModuleParameters();
            }
        };
    };
}

void TXSystem::oscPrintModuleOutputs(ofxOscMessage &msg) {
    if ((msg.getNumArgs() >= (oscDataOffset + 1)) && (msg.getArgType(oscDataOffset) == OFXOSC_TYPE_INT32)) {
        int moduleIDArg = msg.getArgAsInt32(oscDataOffset);
        if (isValidModuleID(moduleIDArg)) {
            if (moduleIDArg == moduleID) {
                printModuleOutputs();
            } else {
                allModules[moduleIDArg]->printModuleOutputs();
            }
        };
    };
}

