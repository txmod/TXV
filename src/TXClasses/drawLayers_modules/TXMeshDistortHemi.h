/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */



//  NB THIS DOESN'T SEEM TO WORK VERY WELL - ABANDONED FOR NOW...

#pragma once

#include "ofMain.h"
#include "TXDrawLayersBase.h"
//#include "TXMain.h"

class TXMeshDistortHemi  :  public TXDrawLayersBase
{
public:
	// constructor
	TXMeshDistortHemi();
    
    // destructor
    ~TXMeshDistortHemi();

	void setup();
	void update();
	void draw();
	void allocateTexture();
	void renderTexture(bool clearFirstArg);
    void windowResized(int w, int h);
    int getTextureWidth(); // overide base class
    int getTextureHeight(); // overide base class
    ofTexture *  getTexture(); // overide base class
    ofPixelsRef getPixels(); // overide base class
    
    // parameters
    
    ofPtr<TXModParamInt> drawLayersRule;
    ofPtr<TXModParamBool> renderContinuosly;
    ofPtr<TXModParamBool> renderNow;
    ofPtr<TXModParamBool> clearBeforeRender;
    ofPtr<TXModParamBool> clearNow;

    ofPtr<TXModParamFloat> clearColorHue;
    ofPtr<TXModParamFloat> clearColorSaturation;
    ofPtr<TXModParamFloat> clearColorBrightness;
    ofPtr<TXModParamFloat> clearColorAlpha;
    
    ofPtr<TXModParamFloat> phase;
    ofPtr<TXModParamFloat> freqX;
    ofPtr<TXModParamFloat> freqY;
    ofPtr<TXModParamFloat> freqZ;
    ofPtr<TXModParamFloat> ampX;
    ofPtr<TXModParamFloat> ampY;
    ofPtr<TXModParamFloat> ampZ;
    ofPtr<TXModParamBool> useHemiLight;

    ofPtr<TXModParamFloat> alpha;
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
    
    ofFbo outImage;
    
private:
    ofPixels pix;
    ofMesh drawMesh;
	ofShader drawShader;
	ofShader renderShader;
    bool oldRenderNow;
    bool oldClearNow;
};

