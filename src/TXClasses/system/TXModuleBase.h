/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

// removed for now:
//#import <Foundation/Foundation.h>

#include "ofMain.h"
//#include "ofxGui.h"
#include "ofxOsc.h"

#include "TXSharedObject.h"
#include "TXParametersBase.h"
#include "TXModSource.h"

#include "TXMain.h"

class TXSystem;

class TXModuleBase : public TXSharedObject, public TXParametersBase  // abstract data type
{
public:

    // NOTE - make sure to add default constructor to all modules
    
	// constructor
	TXModuleBase ();

	// methods
    
	void baseSetup (TXSystem * parentSystemArg, int moduleIDArg, string moduleTypeArg, string moduleNameArg);
    virtual void setParentSystem(TXSystem * parentSystemArg);
    virtual void initialiseParameters();
	int getModuleID();
	void setModuleID(int moduleIDArg);
	string getModuleType();
	void setModuleType(string moduleTypeArg);
	string getName();
	void setName(string nameArg);
	bool getFreezeModule();
	void setFreezeModule(bool freezeModuleArg);
    int getWindowWidth();
    int getWindowHeight();

    // dummy methods - can be overridden in subclasses
    virtual void update();
    virtual void windowResized(int w, int h);
    virtual void message(string stringArg = "");

	// for TXDrawBase modules
    virtual void draw();
    
	// for  TXDrawLayersBase modules
    virtual void addDrawModule(int moduleIDArg, int layerNoArg);
    virtual void removeDrawModule(int moduleIDArg, int layerNoArg);
    
	// for time-based modules
    virtual void resetTime();
    virtual void setMasterBpm(float masterBpmArg);
    virtual void advanceBy(float timeDeltaArg);
    
    // for osc modules
    virtual void  processOscMsg(ofxOscMessage msg);

    // override super class
    virtual void markForDeletion();

    ofPtr<TXModSource> createModSource(string name, float value);
    bool isValidModSource(string sourceName);
    void resetModulation();
    
    ofXml getXMLData();
    bool loadXMLData(ofXml & XML);
    void printModuleParameters();
    void printImageAssetSlots();
    void printExtImageModuleSlots();
    void printMovieAssetSlots();
    void printSvgAssetSlots();
    void print3DModelAssetSlots();
    void printCubeAssetSlots();
    void printFontAssetSlots();
    void printParameterGroup(ofParameterGroup groupArg, string prefixArg = "/");
    void printModuleOutputs();
    
	// assets
    void createImageAssetSlot(string slotNameArg);
    bool setImageAssetSlot(string slotNameArg, int imageAssetIDArg, int assetBankNoArg);
    pair<int, int> getImageAssetIDSlot(string slotNameArg);
    void removeImageAssetReferences(int imageAssetIDArg);
    virtual void imageAssetSlotChanged(string slotNameArg);

    void createMovieAssetSlot(string slotNameArg);
    bool setMovieAssetSlot(string slotNameArg, int movieAssetIDArg, int assetBankNoArg);
    pair<int, int> getMovieAssetIDSlot(string slotNameArg);
    void removeMovieAssetReferences(int movieAssetIDArg);
    virtual void movieAssetSlotChanged(string slotNameArg);
    
    void createSvgAssetSlot(string slotNameArg);
    bool setSvgAssetSlot(string slotNameArg, int svgAssetIDArg, int assetBankNoArg);
    pair<int, int> getSvgAssetIDSlot(string slotNameArg);
    void removeSvgAssetReferences(int svgAssetIDArg);
    virtual void svgAssetSlotChanged(string slotNameArg);
    
    void create3DModelAssetSlot(string slotNameArg);
    bool set3DModelAssetSlot(string slotNameArg, int arg3DModelAssetID, int assetBankNo);
    pair<int, int> get3DModelAssetIDSlot(string slotNameArg);
    void remove3DModelAssetReferences(int arg3DModelAssetID);
    virtual void a3DModelAssetSlotChanged(string slotNameArg);

    void createCubeAssetSlot(string slotNameArg);
    bool setCubeAssetSlot(string slotNameArg, int cubeAssetIDArg, int assetBankNoArg);
    pair<int, int> getCubeAssetIDSlot(string slotNameArg);
    void removeCubeAssetReferences(int cubeAssetIDArg);
    virtual void cubeAssetSlotChanged(string slotNameArg);

    void createFontAssetSlot(string slotNameArg);
    bool setFontAssetSlot(string slotNameArg, int fontAssetIDArg, int assetBankNoArg);
    pair<int, int> getFontAssetIDSlot(string slotNameArg);
    void removeFontAssetReferences(int fontAssetIDArg);
    virtual void fontAssetSlotChanged(string slotNameArg);

	// external image module slots
    void createExtImageModuleSlot(string slotNameArg);
    bool setExtImageModuleSlot(string slotNameArg, int extImageModuleIDArg);
    int getExtImageModuleIDSlot(string slotNameArg);
    void removeExtImageModuleReferences(int extImageModuleIDArg);
    virtual void extImageModuleSlotChanged(string slotNameArg);
    
	// for texture modules -  override as needed
    void registerTexture();
    virtual ofTexture * getTexture();
    virtual int getTextureWidth();
    virtual int getTextureHeight();
    virtual ofPixelsRef getPixels();
    
    
//    // archive methods
//    virtual NSMutableDictionary * getDictionary() = 0; // make into pure virtual functions
//    virtual void setFromDictionary(NSMutableDictionary * dataArg) = 0;

	// properties

public:
    map<string, ofPtr <TXModSource> > modSources;
    multimap<int, int> drawLayerModules;  // layerNo, moduleID
    map<string, int> extImageModuleSlots; // slotName, moduleID
    map<string, pair<int, int> > imageAssetSlots; // slotName, assetID
    map<string, pair<int, int> > movieAssetSlots;
    map<string, pair<int, int> > svgAssetSlots;
    map<string, pair<int, int> > map3DModelAssetSlots;
    map<string, pair<int, int> > cubeAssetSlots;
    map<string, pair<int, int> > fontAssetSlots;
    
    bool canDraw;
    bool canDrawLayers;
    bool hasTexture;
    float masterBpm;

protected:
	TXSystem * parentSystem;
    int moduleID;
    string moduleType;
    string name;
    bool freezeModule;
    
};

