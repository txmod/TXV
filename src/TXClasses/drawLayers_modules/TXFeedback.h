/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXDrawLayersBase.h"
//#include "TXMain.h"

class TXFeedback  :  public TXDrawLayersBase
{
public:
	// constructor
	TXFeedback();
    
    // destructor 
    ~TXFeedback();

	void setup();
	void update();
	void draw();
	void renderTexture(bool clearFirstArg);
	void allocateTextures();
    void windowResized(int w, int h);
    int getTextureWidth(); // overide base class
    int getTextureHeight(); // overide base class
    ofTexture *  getTexture(); // overide base class

    // parameters
     
    ofPtr<TXModParamInt> drawLayersRule;
    ofPtr<TXModParamBool> renderContinuosly;
    ofPtr<TXModParamBool> renderNow;
    ofPtr<TXModParamBool> clearNow;
    ofPtr<TXModParamBool> freezeFeedback;

    ofPtr<TXModParamFloat> clearColorHue;
    ofPtr<TXModParamFloat> clearColorSaturation;
    ofPtr<TXModParamFloat> clearColorBrightness;
    ofPtr<TXModParamFloat> clearColorAlpha;
    ofParameter<bool>  clearColorHSBAsRGB;
    ofParameter<float> alphaThreshold;
    ofPtr<TXModParamFloat> feedbackAlpha;
    ofPtr<TXModParamFloat> feedbackBrightness;
    ofPtr<TXModParamFloat> feedbackShiftX;
    ofPtr<TXModParamBool> quantiseFeedbackShiftX;
    ofPtr<TXModParamFloat> feedbackShiftY;
    ofPtr<TXModParamBool> quantiseFeedbackShiftY;
    ofPtr<TXModParamFloat> feedbackAnchorX;
    ofPtr<TXModParamBool> quantiseFeedbackAnchorX;
    ofPtr<TXModParamFloat> feedbackAnchorY;
    ofPtr<TXModParamBool> quantiseFeedbackAnchorY;
    ofPtr<TXModParamFloat> feedbackRotate;
    ofPtr<TXModParamFloat> feedbackRotateMultiply;
    ofPtr<TXModParamFloat> feedbackScaleX;
    ofPtr<TXModParamFloat> feedbackScaleY;
    ofParameter<bool> useFeedbackScaleXForScaleY;
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
	// FBO pointers
    ofFbo * feedbackImage;
    ofFbo * outputImage;
    
	// FBOs
    ofFbo fbos[2];
    
    ofMesh drawMesh;
	ofShader drawShader;
    ofShader feedbackShader;
    bool oldRenderNow;
    bool oldClearNow;
    int fboFlag;
};

