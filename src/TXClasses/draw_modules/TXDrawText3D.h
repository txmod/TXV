/*
 *  Copyright 2014 Paul Miller. All rights reserved.
 */

/* NOTE OF HACK
 
 - extra method ofxSVG::clear() added
 
 */

#pragma once

#include "ofMain.h"
#include "TXDrawBase.h"
#include "TXExtrudedText.h"

class TXDrawText3D  :  public TXDrawBase
{
public:
    
	TXDrawText3D();

    void fontAssetSlotChanged(string slotNameArg);
    void textStringChanged(string & stringArg);
    void loadText(int fontsize, int depth, int depthResolution, float fontSimplify, float letterSpacing, float spaceSize);

	void setup();
    virtual void draw();
    void windowResized(int w, int h);
    
    ofParameter<string> textString;
    ofPtr<TXModParamInt> fontsize;
    ofParameter<bool> scaleFontToWidth_1024;
    ofPtr<TXModParamInt> depth;
    ofPtr<TXModParamInt> depthResolution;
    ofPtr<TXModParamFloat> fontSimplify;
    ofPtr<TXModParamFloat> spaceSize;
    ofPtr<TXModParamFloat> letterSpacing;

    ofPtr<TXModParamFloat> positionX;
    ofPtr<TXModParamFloat> positionY;
    ofPtr<TXModParamFloat> positionZ;
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

    ofPtr<TXModParamBool> drawLetterFrontSolid;
    ofPtr<TXModParamBool> drawLetterFrontWireframe;
    ofPtr<TXModParamBool> drawLetterBackSolid;
    ofPtr<TXModParamBool> drawLetterBackWireframe;
    ofPtr<TXModParamBool> drawLetterSidesSolid;
    ofPtr<TXModParamBool> drawLetterSidesWireframe;  
    ofParameter<bool> useColorFrontForColorBack;
    ofParameter<bool> useColorFrontForColorSides;
    ofPtr<TXModParamFloat> colorFrontHue;
    ofPtr<TXModParamFloat> colorFrontHueRotate;
    ofPtr<TXModParamFloat> colorFrontSaturation;
    ofPtr<TXModParamFloat> colorFrontBrightness;
    ofPtr<TXModParamBool> colorFrontHSBAsRGB;
    ofPtr<TXModParamFloat> colorBackHue;
    ofPtr<TXModParamFloat> colorBackHueRotate;
    ofPtr<TXModParamFloat> colorBackSaturation;
    ofPtr<TXModParamFloat> colorBackBrightness;
    ofPtr<TXModParamBool> colorBackHSBAsRGB;
    ofPtr<TXModParamFloat> colorSidesHue;
    ofPtr<TXModParamFloat> colorSidesHueRotate;
    ofPtr<TXModParamFloat> colorSidesSaturation;
    ofPtr<TXModParamFloat> colorSidesBrightness;
    ofPtr<TXModParamBool> colorSidesHSBAsRGB;

protected:
    ofTrueTypeFont holdFont;
    TXExtrudedText text3D;
//    ofTTFCharacter holdChar;  // ofTTFCharacter = ofPath
//    vector<ofTTFCharacter> holdStringAsPoints;

    bool fontNeedsLoading;
    bool textNeedsLoading;
    bool textLoaded;

    int old_fontsize;
    int old_depth;
    int old_depthResolution;
    float old_fontSimplify;
    float old_spaceSize;
    float old_letterSpacing;
    bool old_scaleFontToWidth_1024;

};



