/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXDrawLayersBase.h"
//#include "TXMain.h"

class TXDrawTransform3D  :  public TXDrawLayersBase
{
public:
	TXDrawTransform3D();

	void setup();
    void draw();
    void rotate(float rotX, float rotY, float rotZ);

    // parameters
    
    ofPtr<TXModParamInt> drawLayersRule;
    ofPtr<TXModParamInt> transformOrder;
    ofPtr<TXModParamFloat> shiftX;
    ofPtr<TXModParamFloat> shiftY;
    ofPtr<TXModParamFloat> shiftZ;
    ofPtr<TXModParamFloat> rotateX;
    ofPtr<TXModParamFloat> rotateY;
    ofPtr<TXModParamFloat> rotateZ;
    ofPtr<TXModParamFloat> rotateMultiply;
    ofPtr<TXModParamFloat> anchorX;
    ofPtr<TXModParamFloat> anchorY;
    ofPtr<TXModParamFloat> anchorZ;
    ofPtr<TXModParamFloat> scaleX;
    ofPtr<TXModParamFloat> scaleY;
    ofPtr<TXModParamFloat> scaleZ;
    ofParameter<bool> useScaleXForScaleY;
    ofParameter<bool> useScaleXForScaleZ;

};

