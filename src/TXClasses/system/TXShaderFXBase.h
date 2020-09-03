/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

/*
 ====== TEMPLATE FOR RENDERED FX
  
 */


#pragma once

#include "ofMain.h"
#include "TXDrawBase.h"
//#include "TXMain.h"

class TXShaderFXBase  :  public TXDrawBase
{
public:
    static const int numBlendModes = 27;

	// constructor
	TXShaderFXBase();
    
    // destructor
    ~TXShaderFXBase();
    
    //------ overide virtual methods in FX modules as needed:
    virtual void addExtraImageParameters();
	virtual void addExtraParameters();
    virtual void addExtraListeners();
	virtual void loadRenderShader();
    virtual void extraSetupAction();
    virtual void extraUpdateAction();
    virtual bool setExtraUniforms(int sourceImageWidth, int sourceImageHeight);
	//------------------------------------------

    void setup();
	void update();
	void draw();

    // listener methods
    virtual void imageAssetSlotChanged(string slotNameArg);

    void loadDrawShader();
    void loadSourceImage();
    
    void allocateTexture();
    void clearTexture();
	virtual void renderTexture(bool clearFirstArg); // can be overridden
    int getTextureWidth(); // overide base class
    int getTextureHeight(); // overide base class
    ofTexture *  getTexture(); // overide base class
    ofPixelsRef getPixels(); // overide base class
    void renderSizeChanged(int & intArg);
    int getRenderWidth();
    int getRenderHeight();
    void windowResized(int w, int h);

    //render parameters
    ofParameter<bool> useExternalSourceImage;
    ofPtr<TXModParamInt> sourceImageScaleMode;
    ofPtr<TXModParamBool> renderContinuosly;
    ofPtr<TXModParamBool> renderNow;
    ofParameter<int> renderWidthHeightRule;
    ofParameter<int> renderCustomWidth;
    ofParameter<int> renderCustomHeight;
    ofPtr<TXModParamBool> clearBeforeRender;
    ofPtr<TXModParamBool> clearNow;
    ofPtr<TXModParamFloat> clearColorHue;
    ofPtr<TXModParamFloat> clearColorSaturation;
    ofPtr<TXModParamFloat> clearColorBrightness;
    ofPtr<TXModParamFloat> clearColorAlpha;
    ofParameter<bool>  clearColorHSBAsRGB;
    
    //draw parameters
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
   
    ofImage sourceImage;
    ofFbo outImage;
    
protected:
	ofShader drawShader;
	ofShader renderShader;

    ofPixels pix;
    ofMesh drawMesh;
    bool oldRenderNow;
    bool oldClearNow;
    bool sourceImageHasChanged;
    bool outImageIsAllocated;
    float sourceImageWidth = 0;
    float sourceImageHeight = 0;

public:
    // Extra methods & parameters in subclasses:
    //    EXAMPLE CODE:
    //    void  showEdgeColorChanged(ofAbstractParameter & parameterArg );
    
    //    ofPtr<TXModParamInt> copies;
    //    ofPtr<TXModParamFloat> freqX;
    //    ofPtr<TXModParamFloat> freqY;
    //    ofPtr<TXModParamFloat> ampX;
    //    ofPtr<TXModParamFloat> ampY;

};

