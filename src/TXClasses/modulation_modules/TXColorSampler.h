/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXPixelFXBase.h"
#include "TXSmoothVar.h"

class TXColorSampler  :  public TXModuleBase
{
public:
	// constructor
	TXColorSampler();
    
    // destructor
    ~TXColorSampler();
    
	void setup();
	void update();
    
	void updateOutputs();
    void imageAssetSlotChanged(string slotNameArg);
    bool loadSourceImage();
    bool getSourceImageHasLoaded();
    void  color1SmoothTimeChanged(ofAbstractParameter & parameterArg );
    void  color2SmoothTimeChanged(ofAbstractParameter & parameterArg );
    void  color3SmoothTimeChanged(ofAbstractParameter & parameterArg );
    void  color4SmoothTimeChanged(ofAbstractParameter & parameterArg );
	
    // parameters
    
    ofParameter<bool> useExternalSourceImage;

    ofPtr<TXModParamBool> sample1Active;  // bool
    ofPtr<TXModParamFloat> sample1PosX;
    ofPtr<TXModParamFloat> sample1PosY;
    ofPtr<TXModParamBool> sample2Active;  // bool
    ofPtr<TXModParamFloat> sample2PosX;
    ofPtr<TXModParamFloat> sample2PosY;
    ofPtr<TXModParamBool> sample3Active;  // bool
    ofPtr<TXModParamFloat> sample3PosX;
    ofPtr<TXModParamFloat> sample3PosY;
    ofPtr<TXModParamBool> sample4Active;  // bool
    ofPtr<TXModParamFloat> sample4PosX;
    ofPtr<TXModParamFloat> sample4PosY;
    
    ofPtr<TXModParamFloat> color1SmoothTime;
    ofPtr<TXModParamFloat> color2SmoothTime;
    ofPtr<TXModParamFloat> color3SmoothTime;
    ofPtr<TXModParamFloat> color4SmoothTime;

    // outputs
    ofPtr<TXModSource> color1Red;
    ofPtr<TXModSource> color1Green;
    ofPtr<TXModSource> color1Blue;
    ofPtr<TXModSource> color1Hue;
    ofPtr<TXModSource> color1Saturation;
    ofPtr<TXModSource> color1Brightness;
    ofPtr<TXModSource> color1Alpha;
    
    ofPtr<TXModSource> color2Red;
    ofPtr<TXModSource> color2Green;
    ofPtr<TXModSource> color2Blue;
    ofPtr<TXModSource> color2Hue;
    ofPtr<TXModSource> color2Saturation;
    ofPtr<TXModSource> color2Brightness;
    ofPtr<TXModSource> color2Alpha;
    
    ofPtr<TXModSource> color3Red;
    ofPtr<TXModSource> color3Green;
    ofPtr<TXModSource> color3Blue;
    ofPtr<TXModSource> color3Hue;
    ofPtr<TXModSource> color3Saturation;
    ofPtr<TXModSource> color3Brightness;
    ofPtr<TXModSource> color3Alpha;
    
    ofPtr<TXModSource> color4Red;
    ofPtr<TXModSource> color4Green;
    ofPtr<TXModSource> color4Blue;
    ofPtr<TXModSource> color4Hue;
    ofPtr<TXModSource> color4Saturation;
    ofPtr<TXModSource> color4Brightness;
    ofPtr<TXModSource> color4Alpha;
    
    ofImage sourceImage;
    
protected:
    bool sourceImageHasLoaded;
    
    TXSmoothVar smoothColor1R;
    TXSmoothVar smoothColor1G;
    TXSmoothVar smoothColor1B;
    TXSmoothVar smoothColor1A;
    TXSmoothVar smoothColor2R;
    TXSmoothVar smoothColor2G;
    TXSmoothVar smoothColor2B;
    TXSmoothVar smoothColor2A;
    TXSmoothVar smoothColor3R;
    TXSmoothVar smoothColor3G;
    TXSmoothVar smoothColor3B;
    TXSmoothVar smoothColor3A;
    TXSmoothVar smoothColor4R;
    TXSmoothVar smoothColor4G;
    TXSmoothVar smoothColor4B;
    TXSmoothVar smoothColor4A;
};
