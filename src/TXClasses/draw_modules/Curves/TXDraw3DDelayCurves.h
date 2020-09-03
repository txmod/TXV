/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXDrawBase.h"
#include "TXCurvePoint.h"
//#include "TXMain.h"

// , ["Automatic curve", "Straight line", "Bezier curve using control point 1", "Bezier curve using control point 1, smoothed", "Bezier curve using control points 1 & 2"]

//enum TX2DCURVETYPE {TX2DCURVETYPE_AUTOCURVE, TX2DCURVETYPE_STRAIGHT, TX2DCURVETYPE_BEZIER1, TX2DCURVETYPE_BEZIER2, TX2DCURVETYPE_BEZIER3};

class TXDraw3DDelayCurves  :  public TXDrawBase
{
public:
    
    // NOTE - see class TXDraw2DCurves re: totalCurveTypes
    const static int totalCurveTypes = 5;
    const static int maxDelayFrames = 1000;
    const static int maxCurves = 1000;
    const static int maxCurvePoints = 8;
    const static int maxSpreadTypes = 32;

	TXDraw3DDelayCurves();

	void setup();
	void update();
	virtual void draw();

    ofPtr<TXModParamInt> delayFrames;
    ofPtr<TXModParamInt> curveType;
    ofPtr<TXModParamInt> numCurves;
    ofPtr<TXModParamInt> numPoints;
    ofPtr<TXModParamInt> lineWidth;
    ofPtr<TXModParamInt> spreadType;
    ofPtr<TXModParamInt> spreadType2;
    ofPtr<TXModParamFloat> spreadTypeMorph;
    ofPtr<TXModParamBool> autoClose;
    ofPtr<TXModParamBool> fillShape;
    ofPtr<TXModParamInt> windingMode;  // 0: ODD, 1: NONZERO
    ofPtr<TXModParamInt> curveResolution;
    ofPtr<TXModParamBool> reverseCurveOrder;
    ofPtr<TXModParamBool> drawControlPoints;
    
    ofPtr<TXModParamFloat> colorHue;
    ofPtr<TXModParamFloat> colorHueRotate;
    ofPtr<TXModParamFloat> colorSaturation;
    ofPtr<TXModParamFloat> colorBrightness;
    ofPtr<TXModParamFloat> colorAlpha;
    ofPtr<TXModParamFloat> colorHueEnd;
    ofPtr<TXModParamFloat> colorHueRotateEnd;
    ofPtr<TXModParamFloat> colorSaturationEnd;
    ofPtr<TXModParamFloat> colorBrightnessEnd;
    ofPtr<TXModParamFloat> colorAlphaEnd;
    ofParameter<bool> colorHSBAsRGB;
    ofParameter<bool> useColorHueForEndColor;
    ofParameter<bool> useColorSaturationForEndColor;
    ofParameter<bool> useColorBrightnessForEndColor;
    ofParameter<bool> useColorAlphaForEndColor;
    
    ofParameter<bool> useColorForFillColor;
    ofParameter<bool> swapColorWithFillColor;
    ofPtr<TXModParamFloat> fillColorHue;
    ofPtr<TXModParamFloat> fillColorHueRotate;
    ofPtr<TXModParamFloat> fillColorSaturation;
    ofPtr<TXModParamFloat> fillColorBrightness;
    ofPtr<TXModParamFloat> fillColorAlpha;
    ofPtr<TXModParamFloat> fillColorHueEnd;
    ofPtr<TXModParamFloat> fillColorHueRotateEnd;
    ofPtr<TXModParamFloat> fillColorSaturationEnd;
    ofPtr<TXModParamFloat> fillColorBrightnessEnd;
    ofPtr<TXModParamFloat> fillColorAlphaEnd;
    ofParameter<bool> fillColorHSBAsRGB;
    ofParameter<bool> useFillColorHueForEndColor;
    ofParameter<bool> useFillColorSaturationForEndColor;
    ofParameter<bool> useFillColorBrightnessForEndColor;
    ofParameter<bool> useFillColorAlphaForEndColor;

    ofParameter<bool> usePoint1ForAutoCurveStart;
    ofParameter<bool> useLastPointForAutoCurveEnd;

    TXCurvePoint arrCurvePoints[maxCurvePoints];
    TXCurvePoint autoCurveStart;
    TXCurvePoint autoCurveEnd;

private:
    ofShader shader;
    bool useShader;
};

