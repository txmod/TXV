/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXLUTFast.h"
#include "TXSystem.h"
#include "TXAsset.h"

// constructor
TXLUTFast::TXLUTFast() {
    setup();
}

// destructor
TXLUTFast::~TXLUTFast() {
}


void TXLUTFast::addExtraParameters() {
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    holdModParamIntArgs.name = "blendMode";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = numBlendModes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = numBlendModes - 1;
	blendMode = createModParameter(holdModParamIntArgs);
    parameters.add(blendMode->parameters);
    
    holdModParamFloatArgs.name = "blendMix";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	blendMix = createModParameter(holdModParamFloatArgs);
    parameters.add(blendMix->parameters);
    
    holdModParamBoolArgs.name = "blendReverse";
    holdModParamBoolArgs.fixedValue = false;
    blendReverse = createModParameter(holdModParamBoolArgs);
    parameters.add(blendReverse->parameters);
}

void TXLUTFast::addExtraListeners() {
    
    // empty for this module
    
}

void TXLUTFast::extraSetupAction() {
    
    // asset slots
    createCubeAssetSlot("cubeAsset");
    
    // allocate texture
    int mapSize = 32;
    LUTImage.allocate(mapSize * mapSize, mapSize,GL_RGB32F);
}

void TXLUTFast::loadRenderShader() {
    string vString = "_ShaderGroups/FXShaders1Tex/passPosTex0.vert";
    string fString = "_ShaderGroups/FXShaders2Tex/LUT.fs";
#ifdef TARGET_OPENGLES
	renderShader.load("shadersES2/" + vString,"shadersES2/" + fString);
#else
	if(ofIsGLProgrammableRenderer()){
        renderShader.load("shadersGL3/" + vString,"shadersGL3/" + fString);
	}else{
        renderShader.load("shadersGL2/" + vString,"shadersGL2/" + fString);
	}
#endif
}

bool TXLUTFast::setExtraUniforms(int sourceImageWidth, int sourceImageHeight) {    
    //    add LUT texture 
    renderShader.setUniformTexture("u_texture1Sampler", LUTImage.getTexture(), 1);
    renderShader.setUniform1i("u_blendMode", blendMode->getInt());
    renderShader.setUniform1f("u_blendMix", blendMix->getFloat());
    renderShader.setUniform1i("u_blendReverse", blendReverse->getBool());
    return true;
}

//--------------------------------------------------------------
void  TXLUTFast::cubeAssetSlotChanged(string slotNameArg) {
    loadLUT();
}

//--------------------------------------------------------------
void TXLUTFast::loadLUT(){
	LUTloaded=false;
	
    ofPtr <TXAsset> asset;
    string fileName;
    int cubeAssetID = getCubeAssetIDSlot("cubeAsset").first;
    if (cubeAssetID != 0) {
        asset = parentSystem->getAsset(TXASSETTYPE_CUBE, cubeAssetID);
        fileName = asset->getFileName();

        if (loadLUT(fileName)) {
            LUTloaded = true;
        };
    };
}

/*
 // OLD
 bool TXLUTFast::loadLUT(string lutFile){
    ofBuffer buffer = ofBufferFromFile(lutFile);
    
    return loadLUT(buffer);
}

bool TXLUTFast::loadLUT(ofBuffer &buffer){
    buffer.resetLineReader();
    
    int mapSize = 32;
    
    float * pixels = new float[mapSize * mapSize * mapSize * 3];
    
    //LUTImage.getTexture().allocate(mapSize * mapSize, mapSize,GL_RGB32F);
    
    //ofDirectory dir;
    
    for(int z=0; z<mapSize ; z++){
        for(int y=0; y<mapSize; y++){
            for(int x=0; x<mapSize; x++){
                string content = buffer.getNextLine();
                
                int pos = x + y*mapSize + z*mapSize*mapSize;
                
                vector <string> splitString = ofSplitString(content, " ", true, true);
                
                if (splitString.size() >=3) {
                    pixels[pos*3 + 0] = ofToFloat(splitString[0]);
                    pixels[pos*3 + 1] = ofToFloat(splitString[1]);
                    pixels[pos*3 + 2] = ofToFloat(splitString[2]);
                }
            }
        }
    }
    
    LUTImage.getTexture().loadData( pixels, mapSize * mapSize, mapSize, GL_RGB);
    
    return true;
}
 */


bool TXLUTFast::loadLUT(string path){
    float pixels[32 * 32 * 32 * 3];
    
    ofFile file(path);
    string line;
    for(int i = 0; i < 5; i++) {
        getline(file, line);
        //ofLog() << "Skipped line: " << line;
    }
    for(int z=0; z<32; z++){
        for(int y=0; y<32; y++){
            for(int x=0; x<32; x++){
                int pos = x + y*32 + z*32*32;
                ofVec3f cur;
                file >> cur.x >> cur.y >> cur.z;
                pixels[pos*3 + 0] = cur.x;
                pixels[pos*3 + 1] = cur.y;
                pixels[pos*3 + 2] = cur.z;
            }
        }
    }
    
    LUTImage.getTexture().loadData( pixels, 32 * 32, 32, GL_RGB);

    return true;
}


