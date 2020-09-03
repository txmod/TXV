/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXDrawBase.h"
//#include "ofxThreadedImageLoader.h"

class TXDrawImage : public TXDrawBase
{
public:
    // constructor
    TXDrawImage();
    
    // destructor
    ~TXDrawImage();

	void setup();
    void update();
    void draw();

    void imageAssetSlotChanged(string slotNameArg);
    void loadSourceImage();
    void loadMaskImage();
    int getTextureWidth(); // overide base class
    int getTextureHeight(); // overide base class
    ofTexture *  getTexture(); // overide base class
    ofPixelsRef getPixels(); // overide base class
    
    ofPtr<TXModParamInt> sourceImageScaleMode;
    ofParameter<bool> useExternalSourceImage;
    ofParameter<bool> useExternalMaskImage;
    ofPtr<TXModParamInt> maskType;
    ofParameter<bool> invertMask;
    ofPtr<TXModParamFloat> feathering;
    
    ofParameter<bool> useSamplePosForDrawPos;
    ofParameter<bool> useSampleSizeForDrawSize;
    ofParameter<bool> constrainToEdges;
    ofPtr<TXModParamFloat> alpha;
    ofPtr<TXModParamFloat> samplePosX;
    ofPtr<TXModParamFloat> samplePosY;
    ofPtr<TXModParamFloat> sampleWidth;
    ofPtr<TXModParamFloat> sampleHeight;
    ofPtr<TXModParamFloat> numTiles;
    ofPtr<TXModParamBool> mirrorTileX;
    ofPtr<TXModParamBool> mirrorTileY;
    ofPtr<TXModParamFloat> drawPosX;
    ofPtr<TXModParamFloat> drawPosY;
    ofPtr<TXModParamFloat> drawWidth;
    ofPtr<TXModParamFloat> drawHeight;
    ofPtr<TXModParamFloat> anchorX;
    ofPtr<TXModParamFloat> anchorY;
    ofPtr<TXModParamFloat> rotate;
    ofPtr<TXModParamFloat> rotateMultiply;
    ofPtr<TXModParamFloat> scaleX;
    ofPtr<TXModParamFloat> scaleY;
    ofParameter<bool> useScaleXForScaleY;

    ofImage sourceImage;
    ofImage maskImage;
    
private:
    bool sourceImageHasChanged;
    bool maskImageHasChanged;
    ofMesh drawMesh;
	ofShader drawShader;
	ofShader drawWithMaskShader;
	ofShader drawWithMaskTexShader;

};

