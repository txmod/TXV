/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

/*
 ====== TEMPLATE FOR PIXEL-BASED RENDERED FX
 */


#pragma once

#include "ofMain.h"
#include "TXDrawBase.h"
//#include "TXMain.h"

class TXPixelFXBase  :  public TXDrawBase
{
public:
	// constructor
	TXPixelFXBase();
    
    // destructor
    ~TXPixelFXBase();
    
    //------ overide these methods in FX modules:
	virtual void addExtraParameters();
    virtual void addExtraListeners();
    virtual void extraSetupAction();
	virtual void updatePixels();
	//------------------------------------------

    void setup();
	void update();
	void draw();

    void imageAssetSlotChanged(string slotNameArg);
    void useExternalSourceImageChanged(bool & boolArg);
    bool loadSourceImage();
    
    void outImageSetup();
    int getTextureWidth(); // overide base class
    int getTextureHeight(); // overide base class
    ofTexture * getTexture(); // overide base class
    ofPixelsRef getPixels(); // overide base class

    //render parameters
    ofParameter<bool> useExternalSourceImage;
    ofPtr<TXModParamBool> renderContinuosly;
    ofPtr<TXModParamBool> renderNow;
    
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
	ofImage outImage;
    

protected:
    bool sourceImageHasChanged;
    ofMesh drawMesh;
	ofShader drawShader;
    bool oldRenderNow;
    bool outImageIsAllocated;

public:
    // Extra methods & parameters:
    //    EXAMPLE CODE:
    //    void  showEdgeColorChanged(ofAbstractParameter & parameterArg );
    
    //    ofPtr<TXModParamFloat> phase;

};

