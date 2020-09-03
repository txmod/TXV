/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXDrawBase.h"
//#include "TXMain.h"

enum TXGRADIENTTYPE {
    TXGRADIENTTYPE_HORIZONTAL,
    TXGRADIENTTYPE_VERTICAL,
    TXGRADIENTTYPE_RADIAL,
};

class TXDrawGradient  :  public TXDrawBase
{
public:
	// constructor
	TXDrawGradient();
    
    // destructor
    ~TXDrawGradient();
    
    // NOTE - change totalGradientTypes when adding new types:
    static const int totalGradientTypes = 4;

	void setup();
	void update();
	void draw();
	void loadRenderShader();
	void allocateTexture();
	void renderTexture();
    void windowResized(int w, int h);
    int getTextureWidth(); // overide base class
    int getTextureHeight(); // overide base class
    void renderSizeChanged(int & intArg);
    int getRenderWidth();
    int getRenderHeight();
    ofTexture *  getTexture(); // overide base class

    // parameters
    
    ofPtr<TXModParamBool> renderContinuosly;
    ofPtr<TXModParamBool> renderNow; 
    ofParameter<int> renderWidthHeightRule;
    ofParameter<int> renderCustomWidth;
    ofParameter<int> renderCustomHeight;
    
    ofPtr<TXModParamInt> gradientType;
    ofPtr<TXModParamInt> numColors;
    ofPtr<TXModParamFloat> curveBias;
    ofPtr<TXModParamBool> invert;

    ofPtr<TXModParamFloat> point1X;
    ofPtr<TXModParamFloat> point1Y;
    ofPtr<TXModParamFloat> point2X;
    ofPtr<TXModParamFloat> point2Y;

    ofPtr<TXModParamFloat> color1Hue;
    ofPtr<TXModParamFloat> color1HueRotate;
    ofPtr<TXModParamFloat> color1Saturation;
    ofPtr<TXModParamFloat> color1Brightness;
    ofPtr<TXModParamFloat> color1Alpha;
    ofPtr<TXModParamBool> color1HSBAsRGB;
    
    ofPtr<TXModParamFloat> color2Hue;
    ofPtr<TXModParamFloat> color2HueRotate;
    ofPtr<TXModParamFloat> color2Saturation;
    ofPtr<TXModParamFloat> color2Brightness;
    ofPtr<TXModParamFloat> color2Alpha;
    ofPtr<TXModParamBool> color2HSBAsRGB;
    
    ofPtr<TXModParamFloat> color3Hue;
    ofPtr<TXModParamFloat> color3HueRotate;
    ofPtr<TXModParamFloat> color3Saturation;
    ofPtr<TXModParamFloat> color3Brightness;
    ofPtr<TXModParamFloat> color3Alpha;
    ofPtr<TXModParamBool> color3HSBAsRGB;
    
    ofPtr<TXModParamFloat> color4Hue;
    ofPtr<TXModParamFloat> color4HueRotate;
    ofPtr<TXModParamFloat> color4Saturation;
    ofPtr<TXModParamFloat> color4Brightness;
    ofPtr<TXModParamFloat> color4Alpha;
    ofPtr<TXModParamBool> color4HSBAsRGB;
    
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
    
    ofFbo outImage;
    
private:
    float currentTime;
    ofMesh drawMesh;
	ofShader drawShader;
	ofShader renderShader;
    bool oldRenderNow;
};

