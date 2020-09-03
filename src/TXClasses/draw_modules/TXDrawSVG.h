/*
 *  Copyright 2014 Paul Miller. All rights reserved.
 */

/* NOTE OF HACK
 
 - extra method ofxSVG::clear() added
 
 */

#pragma once

#include "ofMain.h"
#include "TXDrawBase.h"
#include "ofxSVG.h"
//#include "TXMain.h"

class TXDrawSVG  :  public TXDrawBase
{
public:
    
	TXDrawSVG();

    void svgAssetSlotChanged(string slotNameArg);
    void loadSvg();

	void setup();
	virtual void draw();
    
    ofParameter<bool> useScaleXForScaleY;
    ofPtr<TXModParamFloat> positionX;
    ofPtr<TXModParamFloat> positionY;
    ofPtr<TXModParamFloat> anchorX;
    ofPtr<TXModParamFloat> anchorY;
    ofPtr<TXModParamFloat> rotate;
    ofPtr<TXModParamFloat> rotateMultiply;
    ofPtr<TXModParamFloat> scaleX;
    ofPtr<TXModParamFloat> scaleY;
    
    ofxSVG svg;

};

