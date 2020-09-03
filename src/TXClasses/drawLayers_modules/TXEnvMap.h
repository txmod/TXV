/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXDrawLayersBase.h"
//#include "TXMain.h"

class TXEnvMap  :  public TXDrawLayersBase
{
public:
	// constructor
	TXEnvMap();
    
    // destructor
    ~TXEnvMap();

	void setup();
	void update();
	void draw();
    
    void imageAssetSlotChanged(string slotNameArg);
    void loadEnvMapImage();
    void  useExternalEnvMapImageChanged(bool & boolArg);

	void allocateTexture();
	void renderTexture(bool clearFirstArg);
    void windowResized(int w, int h);
    int getTextureWidth(); // overide base class
    int getTextureHeight(); // overide base class
    ofTexture *  getTexture(); // overide base class
    ofPixelsRef getPixels(); // overide base class
    
    // parameters
    
    ofParameter<bool> useExternalEnvMapImage;
    ofPtr<TXModParamBool> mirrorImageRight;
    ofPtr<TXModParamFloat> environmentRotation;
    ofPtr<TXModParamFloat> blurTopBottom;
    ofPtr<TXModParamInt> drawLayersRule;
    ofPtr<TXModParamBool> renderContinuosly;
    ofPtr<TXModParamBool> renderNow;
    ofPtr<TXModParamBool> clearBeforeRender;
    ofPtr<TXModParamBool> clearNow;

    ofPtr<TXModParamFloat> clearColorHue;
    ofPtr<TXModParamFloat> clearColorHueRotate;
    ofPtr<TXModParamFloat> clearColorSaturation;
    ofPtr<TXModParamFloat> clearColorBrightness;
    ofPtr<TXModParamFloat> clearColorAlpha;
    ofPtr<TXModParamBool> clearColorHSBAsRGB;
    
    ofPtr<TXModParamFloat> lightEffectMix;
    ofPtr<TXModParamFloat> lightPosX;
    ofPtr<TXModParamFloat> lightPosY;
    ofPtr<TXModParamFloat> lightPosZ;
    ofPtr<TXModParamFloat> baseColorHue;
    ofPtr<TXModParamFloat> baseColorHueRotate;
    ofPtr<TXModParamFloat> baseColorSaturation;
    ofPtr<TXModParamFloat> baseColorBrightness;
    ofPtr<TXModParamBool> baseColorHSBAsRGB;
    ofPtr<TXModParamFloat> baseEnvColorMix;

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
    
    ofImage envMapImage;
    ofFbo outImage;
    
private:
    ofPixels pix;
    ofMesh drawMesh;
	ofShader drawShader;
	ofShader renderShader;
    bool oldRenderNow;
    bool oldClearNow;
    bool envMapImageHasChanged;
};

//////////


