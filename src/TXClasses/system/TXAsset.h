/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"

enum TXASSETTYPE {
    TXASSETTYPE_IMAGE,
    TXASSETTYPE_MOVIE,
    TXASSETTYPE_SVG,
    TXASSETTYPE_CUBE,
    TXASSETTYPE_3DMODEL,
    TXASSETTYPE_FONT
};

class TXAsset
{
public:
	// constructor
	TXAsset (int assetTypeArg, string fileNameArg, int assetIDArg, int assetBankNoArg);
    
	// methods
	void   setup (int assetTypeArg, string fileNameArg, int assetIDArg, int assetBankNoArg);
	int    getAssetType();
    string getAssetTypeString();
    void   setAssetType(int assetTypeArg);
	int    getAssetID();
    void   setAssetID(int assetIDArg);
	string getFileName();
    void   setFileName(string fileNameArg);
	bool   getFileExists();
    int    getAssetBankNo();
    void   setAssetBankNo(int assetBankNoArg);
    
	// properties
    ofParameterGroup parameters;
    ofParameter<int> assetType;
    ofParameter<string> fileName;
    ofParameter<int> assetID;
    ofParameter<int> assetBankNo;
    
protected:
        
};

