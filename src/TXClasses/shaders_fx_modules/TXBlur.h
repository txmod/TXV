/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXDrawBase.h"
//#include "TXMain.h"

class TXBlur  :  public TXDrawBase
{
public:
    static const int numLevelsModes = 6;
    static const int numBlendModes = 27;
    static const int numChannelOrders = 6;

	// constructor
	TXBlur();
    
    // destructor
    ~TXBlur();

	void setup();
	void update();
	void draw();

    void imageAssetSlotChanged(string slotNameArg);
    bool loadSourceImage();
    bool getSourceImageHasLoaded();
    
    void allocateTexture(int widthArg, int heightArg);
	void renderTexture();
    int getTextureWidth(); // overide base class
    int getTextureHeight(); // overide base class
    void renderSizeChanged(int & intArg);
    int getRenderWidth();
    int getRenderHeight();
    ofTexture *  getTexture(); // overide base class
    
    ofParameter<bool> useExternalSourceImage;
    ofPtr<TXModParamBool> renderContinuosly;
    ofPtr<TXModParamBool> renderNow;
    ofParameter<int> renderWidthHeightRule;
    ofParameter<int> renderCustomWidth;
    ofParameter<int> renderCustomHeight;
    
    ofPtr<TXModParamFloat> blurDistance;
    ofPtr<TXModParamInt> noPasses;

    ofParameter<float> alphaThreshold;
    ofPtr<TXModParamFloat> drawAlpha;
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
    
private:
    ofImage sourceImage;

	ofShader drawShader;
	ofShader renderShader;
    ofShader blurShaderH;
    ofShader blurShaderV;
    
    ofFbo outImage;
    ofFbo fbo2;
	
    float pixelSizeX;
    float pixelSizeY;
    float sourceImageWidth = 0;
    float sourceImageHeight = 0;    

    ofMesh drawMesh;
    
    bool oldRenderNow;
    bool sourceImageHasLoaded;
    bool outImageIsAllocated;
};

