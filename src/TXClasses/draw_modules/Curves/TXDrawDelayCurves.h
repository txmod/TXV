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

class TXDrawDelayCurves  :  public TXDrawBase
{
public:
    
    // NOTE - see class TXDrawCurves re: total2DcurveTypes
    const static int total2DcurveTypes = 5;
    const static int maxDelayFrames = 1000;
    const static int maxCurves = 1000;
    const static int maxCurvePoints = 8;
    const static int maxSpreadTypes = 32;

	TXDrawDelayCurves();

	void setup();
	void update();
	virtual void draw();

    ofPtr<TXModParamInt> delayFrames;
    ofPtr<TXModParamInt> curveType;
    ofPtr<TXModParamInt> numPoints;
    ofPtr<TXModParamInt> numCurves;
    ofPtr<TXModParamInt> lineWidth;
    ofPtr<TXModParamBool> autoClose;
    ofPtr<TXModParamBool> fillShape;
    ofPtr<TXModParamInt> windingMode;  // 0: ODD, 1: NONZERO
    ofPtr<TXModParamInt> curveResolution;
    ofPtr<TXModParamBool> reverseCurveOrder;
    ofPtr<TXModParamBool> drawControlPoints;
    ofParameter<bool> usePoint1ForAutoCurveStart;
    ofParameter<bool> useLastPointForAutoCurveEnd;
    
    TXParameterFloat256   positionSpreadCurve;
    TXParameterFloat256   positionSpreadCurve2;
    ofPtr<TXModParamFloat> positionSpreadCurveMorph;
    ofPtr<TXModParamFloat> positionSpreadCurvePhase;
    
    ofPtr<TXModParamFloat> lineColorHue;
    ofPtr<TXModParamFloat> lineColorHueRotate;
    ofPtr<TXModParamFloat> lineColorSaturation;
    ofPtr<TXModParamFloat> lineColorBrightness;
    ofPtr<TXModParamFloat> lineColorAlpha;
    ofPtr<TXModParamFloat> lineColorHueEnd;
    ofPtr<TXModParamFloat> lineColorHueRotateEnd;
    ofPtr<TXModParamFloat> lineColorSaturationEnd;
    ofPtr<TXModParamFloat> lineColorBrightnessEnd;
    ofPtr<TXModParamFloat> lineColorAlphaEnd;
    ofParameter<bool> lineColorHSBAsRGB;
    ofParameter<bool> useLineColorHueForEndColor;
    ofParameter<bool> useLineColorSaturationForEndColor;
    ofParameter<bool> useLineColorBrightnessForEndColor;
    ofParameter<bool> useLineColorAlphaForEndColor;
    
    ofParameter<bool> useLineColorForFillColor;
    ofParameter<bool> swapLineColorWithFillColor;
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

    TXParameterFloat256   colorSpreadCurve;
    TXParameterFloat256   colorSpreadCurve2;
    ofPtr<TXModParamFloat> colorSpreadCurveMorph;
    ofPtr<TXModParamFloat> colorSpreadCurvePhase;
    
    TXCurvePoint arrCurvePoints[maxCurvePoints];
    TXCurvePoint autoCurveStart;
    TXCurvePoint autoCurveEnd;

    ofPtr<TXModParamInt> transformOrder;
    ofPtr<TXModParamFloat> shiftX;
    ofPtr<TXModParamFloat> shiftY;
    ofPtr<TXModParamFloat> drawWidth;
    ofPtr<TXModParamFloat> drawHeight;
    ofPtr<TXModParamFloat> anchorX;
    ofPtr<TXModParamFloat> anchorY;
    ofPtr<TXModParamFloat> rotate;
    ofPtr<TXModParamFloat> scaleX;
    ofPtr<TXModParamFloat> scaleY;
    ofParameter<bool> useScaleXForScaleY;

private:
    ofShader shader;
    bool useShader;
};

