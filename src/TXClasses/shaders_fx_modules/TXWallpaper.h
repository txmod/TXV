/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXDrawBase.h"
#include "Ornament.h"
//#include "TXMain.h"

class TXWallpaper  :  public TXDrawBase
{
public:
    static const int numWallpaperGroups = 8;

	// constructor
	TXWallpaper();
    
    // destructor
    ~TXWallpaper();

	void setup();
	void update();
	void draw();

    void imageAssetSlotChanged(string slotNameArg);
    bool loadSourceImage();
    bool getSourceImageHasLoaded();
    void allocateTexture();
    void renderTexture();
    int getTextureWidth(); // overide base class
    int getTextureHeight(); // overide base class
    ofTexture *  getTexture(); // overide base class
    void renderSizeChanged(int & intArg);
    int getRenderWidth();
    int getRenderHeight();
    void windowResized(int w, int h);    
    
    // listener methods
    void  wallpaperGroupChanged(ofAbstractParameter & parameterArg );
    void  sourceZoomChanged(ofAbstractParameter & parameterArg );
    void  sourceShiftXChanged(ofAbstractParameter & parameterArg );
    void  sourceShiftYChanged(ofAbstractParameter & parameterArg );
    void  sourceRotateChanged(ofAbstractParameter & parameterArg );
    void  tileSizeChanged(ofAbstractParameter & parameterArg );
    void  tileAngleChanged(ofAbstractParameter & parameterArg );
    void  useSourceZoomXForZoomYChanged(bool & boolArg);
    void  useExternalSourceImageChanged(bool & boolArg);
    void updateSourceZoom();
    void updateSourceImage();
    
    //render parameters
    ofParameter<bool> useExternalSourceImage;
    ofPtr<TXModParamInt> sourceImageScaleMode;
    ofPtr<TXModParamBool> renderContinuosly;
    ofPtr<TXModParamBool> renderNow;
    ofParameter<int> renderWidthHeightRule;
    ofParameter<int> renderCustomWidth;
    ofParameter<int> renderCustomHeight;
    
    ofPtr<TXModParamInt> wallpaperGroup;
    ofPtr<TXModParamFloat> sourceZoomX;
    ofPtr<TXModParamFloat> sourceZoomY;
    ofParameter<bool> useSourceZoomXForZoomY;
    ofPtr<TXModParamFloat> sourceShiftX;
    ofPtr<TXModParamFloat> sourceShiftY;
    ofPtr<TXModParamFloat> sourceRotate;
    ofPtr<TXModParamFloat> tileSize;
    ofPtr<TXModParamFloat> tileAngle;

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
    float sourceImageWidth = 0;
    float sourceImageHeight = 0;

    Ornament ornament;

    ofImage sourceImage;

	ofShader drawShader;
	
    ofMesh drawMesh;
    
    bool oldRenderNow;
    bool sourceImageHasLoaded;
    bool sourceImageHasChanged;
    bool windowHasResized;
    bool tileSizeHasChanged;
};

