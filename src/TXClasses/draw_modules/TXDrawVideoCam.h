/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXDrawBase.h"

class TXDrawVideoCam  :  public TXDrawBase
{
public:
	// constructor
	TXDrawVideoCam();
    
    // destructor
    ~TXDrawVideoCam();

	void setup();
    void update();
    void draw();
    void initVideoCam();

    int getTextureWidth(); // overide base class
    int getTextureHeight(); // overide base class
    ofTexture *  getTexture(); // overide base class
    ofPixelsRef getPixels(); // overide base class

    void videoDeviceIndexChanged(int & intArg);
    void cameraImageWidthChanged(int & intArg);
    void cameraImageHeightChanged(int & intArg);

    // parameters
    
    ofParameter<bool> videoCamActive;
    
    ofParameter<int> videoDeviceIndex;
    ofParameter<int> cameraViewWidth;
    ofParameter<int> cameraViewHeight;
    
    ofParameter<bool> useSamplePosForDrawPos;
    ofParameter<bool> useSampleSizeForDrawSize;
    ofParameter<bool> constrainToEdges;
    ofParameter<float> alphaThreshold;
    ofPtr<TXModParamFloat> alpha;
    ofPtr<TXModParamFloat> samplePosX;
    ofPtr<TXModParamFloat> samplePosY;
    ofPtr<TXModParamFloat> sampleWidth;
    ofPtr<TXModParamFloat> sampleHeight;
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
    ofVideoGrabber vidGrabber;
    vector<ofVideoDevice> allVideoDevices;

    ofMesh drawMesh;
	ofShader drawShader;
    
};

//vector<ofVideoDevice> listDevices();
//bool				isFrameNew();
//void				update();
//void				close();
//bool				initGrabber(int w, int h){return initGrabber(w,h,true);}
//bool				initGrabber(int w, int h, bool bTexture);


