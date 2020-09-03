/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"

#include "TXAsset.h"
#include "TXDrawConnection.h"
#include "TXDrawLayersBase.h"
#include "TXIDAllocator.h"
#include "ofxOscParameterSync.h"
#include "ofxThreadedImageLoader.h"
//#include "SoundManager.h"
//#include "ofxGui.h"

class TXModNode;

class TXSystem : public TXDrawLayersBase 
{
    
public:
	// constructor
	TXSystem();

    // destructor
    ~TXSystem();
	// methods
    
    void setup(string argName = "");
    void update();
    virtual void draw();
    
    int validateIDAllocator(string idType);
    int getNextIDForType(string idType);
    string getNextNameForType(string idType);
    void adjustNextID(string argIDType, int argID);
    int getWindowWidth();
    int getWindowHeight();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void windowResizeInform();
    // void openSystemFromFile();    // not working yet
    // void saveSystemToFile();      // not working yet

    ofPtr<TXModuleBase> addModule(string moduleType, int newModuleID = -1);
    bool deleteModule(int moduleID);
    ofPtr<TXModuleBase> addNode(int sourceModuleID, string sourceName, int destinationModuleID, string destinationName, float modAmount, bool negativeModulation, bool active, int newModuleID = -1);
    ofPtr<TXModuleBase> addDrawConnection(int sourceModuleID, int destinationModuleID, int layerNo, int newModuleID = -1);
    ofPtr<TXAsset> addAsset(int assetType, string fileNameArg, int newAssetID = -1, int assetBankNo = 0);
    ofPtr <TXAsset> getAsset(int assetTypeArg, int assetIDArg);
    bool setNodeConnections(int nodeModuleID, int sourceModuleID, string sourceName, int destinationModuleID, string destinationName);
    bool deleteNode(int nodeModuleID);
    bool deleteAsset(int assetType, int assetID);
    void deleteMarkedModules();
    void deleteAllModules();
    bool deleteDrawConnection(int moduleIDArg);
    bool setDrawConnection(int moduleIDArg, int sourceModuleIDArg, int destinationModuleIDArg, int layerNoArg, bool activeArg);
    bool setDrawConnectionLayerNo(int moduleIDArg, int oldLayerNo, int newLayerNo);
    bool setDrawConnectionActive(int moduleIDArg, int layerNo, bool activeArg);
    void resetAllTime();
    // void rebuildGui();
    void applyNodeModulations();
    unsigned long getCurrentFrameNo();
    bool isValidModuleID(int moduleIDArg);
    ofTexture * getModuleTexture(int moduleIDArg);

    void registerOscAddress(string oscAddressArg, int moduleIDArg);
    void deregisterOscAddress(string oscAddressArg, int moduleIDArg);
    void deregisterOscAddressesForModule(int moduleIDArg);
    float getCurrentTime();
    
protected:
    bool isValidDrawModuleID(int moduleIDArg);
    bool isValidDrawLayersModuleID(int moduleIDArg);
    bool isValidModSource(int moduleIDArg, string paramaterName);
    bool isValidModDestination(int moduleIDArg, string paramaterName);
    bool areValidNodeConnections(int sourceModuleID, string sourceName, int destinationModuleID, string destinationName);
    bool isValidAssetID(int assetTypeArg, int assetIDArg);
    map<int, ofPtr <TXAsset> > * getAssetMap(int assetType);
    string getAssetTypeString(int assetType);
    bool isMarkedForDel(int moduleIDArg);
    
    // OSC methods
    void initOsc();
    void checkOscMessages();
    void redirectOscMsg(ofxOscMessage &msg);
    bool redirectSystemOscMsg(ofxOscMessage &msg);
    void processNonSystemOscMsg(ofxOscMessage &msg);
    void sendOscReply(string reply, ofxOscMessage &msg);
    void sendOscAddModuleConfirm(string reply, ofxOscMessage &msg, int moduleID, string moduleType, string moduleName, bool canDraw, bool canDrawLayers, int numModInputs, int numModOutputs, int hasTexture = 0);
    void sendOscAddAssetConfirm(string reply, ofxOscMessage &msg, int assetType, string  assetTypeString, int assetID, string fileName, bool fileExists, int assetBankNo);
    void oscSync(ofxOscMessage &msg, bool sendReply = true);
    void oscSyncStart(ofxOscMessage &msg);
    void oscSyncStop(ofxOscMessage &msg);
    void oscPing(ofxOscMessage &msg);
    void oscSystemData(ofxOscMessage &msg);
    void oscAddAsset(ofxOscMessage &msg);
    void oscDeleteAsset(ofxOscMessage &msg);
    void oscAddModule(ofxOscMessage &msg);
    void oscDeleteModule(ofxOscMessage &msg);
    void oscAddNode(ofxOscMessage &msg);
    void oscDeleteNode(ofxOscMessage &msg);
    void oscSetNodeConnections(ofxOscMessage &msg);
    void oscAddDrawConnection(ofxOscMessage &msg);
    void oscSetDrawConnection(ofxOscMessage &msg);
    void oscDeleteDrawConnection(ofxOscMessage &msg);
    void oscSetModuleParameter(ofxOscMessage &msg);
    void oscSetModuleParameterFloat256(ofxOscMessage &msg);
    void oscSetModuleAsset(ofxOscMessage &msg);
    void oscSetModuleExtImageModule(ofxOscMessage &msg);
    void oscSetIgnoreOscLatency(ofxOscMessage &msg);
    void oscPrintModuleParameters(ofxOscMessage &msg);
    void oscPrintModuleOutputs(ofxOscMessage &msg);
    
    //  listeners 
    void antiAliasingChanged(bool & antiAliasingArg);
    void neverDropFramesChanged(bool & neverDropFramesArg);
    void showFullScreenChanged(bool & showFullScreenArg);
    void targetFrameRateChanged(int & targetFrameRateArg);
    void windowSizeModeChanged(int & windowSizeModeArg);
    void customWindowWidthChanged(int & windowWidthArg);
    void customWindowHeightChanged(int & windowHeightArg);
    void updateWindowSize();

//    // archive methods
//    NSMutableDictionary * getDictionary();
//    void setFromDictionary(NSMutableDictionary * dataArg);

	// properties
public:    
    map<int, ofPtr<TXModuleBase> > allModules;
    map<int, ofPtr<TXModuleBase> > allDrawModules;
    map<int, ofPtr<TXModuleBase> > allDrawLayersModules;
    map<int, ofPtr<TXModNode> > allNodes;
    map<int, ofPtr<TXDrawConnection> > allDrawConnections;
    map<string, ofPtr<TXIDAllocator> > allIDAllocators;
    map<int, ofPtr<TXAsset> > allImageAssets;
    map<int, ofPtr<TXAsset> > allMovieAssets;
    map<int, ofPtr<TXAsset> > allSvgAssets;
    map<int, ofPtr<TXAsset> > allCubeAssets;
    map<int, ofPtr<TXAsset> > allModelAssets;
    map<int, ofPtr<TXAsset> > allFontAssets; 
    multimap<string, int> oscAddresses;  // oscAddress, moduleID
    
    enum WINDOWSIZEMODE {
        WINDOWSIZEMODE_CUSTOM, // 0 default
        WINDOWSIZEMODE_480_360, // 1
        WINDOWSIZEMODE_858_480, // 2
        WINDOWSIZEMODE_1280_720, // 3
        WINDOWSIZEMODE_1920_1080, // 4
        WINDOWSIZEMODE_2560_1440, // 5
        WINDOWSIZEMODE_3840_2160, // 6
        WINDOWSIZEMODE_TOTAL,
    };
    
    // parameters
    ofPtr<TXModParamBool> freezeSystem;
    ofParameter<bool> showFullScreen;
    ofParameter<int> windowSizeMode;
    ofParameter<int> customWindowWidth;
    ofParameter<int> customWindowHeight;
    ofParameter<float> oscLatency;
    ofPtr<TXModParamInt> drawLayersRule;
    ofParameter<bool> antiAliasing;
    ofParameter<bool> neverDropFrames;
    ofParameter<bool> showFrameRate;
    ofParameter<int> targetFrameRate;
    ofParameter<float> alphaThreshold;
    ofPtr<TXModParamBool> resetClocks;
    ofPtr<TXModParamFloat> masterBpm;
    ofPtr<TXModParamBool> showBackground;
    ofPtr<TXModParamFloat> backgroundHue;
    ofPtr<TXModParamFloat> backgroundSaturation;
    ofPtr<TXModParamFloat> backgroundBrightness;
    ofPtr<TXModParamFloat> backgroundAlpha;
    ofPtr<TXModParamBool> backgroundHSBAsRGB;
    
    ofPtr<TXModSource> mouseDraggedX;
    ofPtr<TXModSource> mouseDraggedY;
    ofPtr<TXModSource> mouseMovedX;
    ofPtr<TXModSource> mouseMovedY;
    ofPtr<TXModSource> mouseMovedOrDraggedX;
    ofPtr<TXModSource> mouseMovedOrDraggedY;
    ofPtr<TXModSource> mouseButtonPressed;

    // ofxPanel gui;   // gui removed for now
    // bool guiBuilt = false;
    // ofxOscParameterSync sync;
    ofxOscSender oscSender;
	ofxOscReceiver oscReceiver;
    ofxThreadedImageLoader imageLoader; 
    
protected:
    string txvVersionString = "";
    unsigned long currentFrameNo = 0;
    bool    openSystemRequested;
    bool    saveSystemRequested;
    bool    closeTXVRequested;
    float   currentTime;
    float   oldTime;
    float   oldElapsedTime;
    float   startTimeOffset;
    bool    freezeSystemOverride = false;
    bool    ignoreOscLatency = false;
    float   oldMasterBpm;
    bool    oldResetClocks = false;
    bool    showTXVText = true;
    string  currentStatusText;
    float   makeFullScreenTime = -1;
    bool    showCursor = true;
    bool    windowResizeCalled;
    int     windowResizeWidth;
    int     windowResizeHeight;
    int     currentWindowWidth;
    int     currentWindowHeight;
    
    // OSC
    map<int, ofxOscMessage> storedOscMessages;
    const string host = "localhost";
    int  localPort;    // TXV
    int  remotePort; // SuperCollider
    const int  systemCode = 1000000;
    const int  oscDataOffset = 5;
   // oscDataOffset is 5 because: OSC Message Args: [int systemCode, int msgSeqNo, float msgTime, string systemData1, string systemData2, dataArgs...
    vector<float> oscTimeDifferences;
    float maxTimeDifference;
    bool oscSyncInProgress;
};

