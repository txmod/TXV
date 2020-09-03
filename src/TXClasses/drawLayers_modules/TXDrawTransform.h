/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXDrawLayersBase.h"
//#include "TXMain.h"

class TXDrawTransform  :  public TXDrawLayersBase
{
public:
	TXDrawTransform();

	void setup();
    void draw();
    void rotate();

    // parameters
    
    ofPtr<TXModParamInt> drawLayersRule;
    ofPtr<TXModParamInt> transformOrder;
    ofPtr<TXModParamFloat> shiftX;
    ofPtr<TXModParamFloat> shiftY;
    ofPtr<TXModParamFloat> rotateX;
    ofPtr<TXModParamFloat> rotateY;
    ofPtr<TXModParamFloat> rotateZ;
    ofPtr<TXModParamFloat> rotateMultiply;
    ofPtr<TXModParamFloat> anchorX;
    ofPtr<TXModParamFloat> anchorY;
    ofPtr<TXModParamFloat> scaleX;
    ofPtr<TXModParamFloat> scaleY;
    ofParameter<bool> useScaleXForScaleY;

};

