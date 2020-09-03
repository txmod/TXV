/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXLUT.h"
#include "TXSystem.h"
#include "TXAsset.h"

// constructor
TXLUT::TXLUT() {
    setup();
}

// destructor
TXLUT::~TXLUT() {
}


void TXLUT::addExtraParameters() {
    
    // empty for this module
    
}

void TXLUT::addExtraListeners() {
    
    // empty for this module
    
}

void TXLUT::extraSetupAction() {
    
    // asset slots
    createCubeAssetSlot("cubeAsset");
    
}

void TXLUT::updatePixels() {
    
    ofPixels pix;
    
    if (!useExternalSourceImage) {
        if (!sourceImage.isAllocated()) {
            return;
        };
    };
    
    if (useExternalSourceImage) {
        int holdSourceID = getExtImageModuleIDSlot("extSourceImageModule");
        pix = parentSystem->allModules[holdSourceID]->getPixels();
    } else {
        pix = sourceImage.getPixels();
    };
    
    for(int y = 0; y < pix.getHeight(); y++){
        for(int x = 0; x < pix.getWidth(); x++){
            
            ofColor color = pix.getColor(x, y);
            
            if (LUTloaded) {
                int lutPos [3];
                for (int i=0; i<3; i++) {
                    lutPos[i] = color[i] / 8;
                    if (lutPos[i]==31) {
                        lutPos[i]=30;
                    }
                }
                ofVec3f start = lut[lutPos[0]][lutPos[1]][lutPos[2]];
                ofVec3f end = lut[lutPos[0]+1][lutPos[1]+1][lutPos[2]+1];
                
                for (int i=0; i<3; i++) {
                    float amount = (color[i] % 8) / 8.0f;
                    color[i]= (start[i] + amount * (end[i] - start[i])) * 255;
                }
            }
            outImage.setColor(x, y, color);
        }
    }
    outImage.update();
}

//--------------------------------------------------------------
void  TXLUT::cubeAssetSlotChanged(string slotNameArg) {
    loadLUT();
}

//--------------------------------------------------------------
void TXLUT::loadLUT(){
	LUTloaded=false;
	
    ofPtr <TXAsset> asset;
    string fileName;
    int cubeAssetID = getCubeAssetIDSlot("cubeAsset").first;
    if (cubeAssetID != 0) {
        asset = parentSystem->getAsset(TXASSETTYPE_CUBE, cubeAssetID);
        fileName = asset->getFileName();
        ofFile file(fileName);
        string line;
        for(int i = 0; i < 5; i++) {
            getline(file, line);
            //ofLog() << "Skipped line: " << line;
        }
        for(int z=0; z<32; z++){
            for(int y=0; y<32; y++){
                for(int x=0; x<32; x++){
                    ofVec3f cur;
                    file >> cur.x >> cur.y >> cur.z;
                    lut[x][y][z] = cur;
                }
            }
        }
        LUTloaded = true;
    };
}
//--------------------------------------------------------------
