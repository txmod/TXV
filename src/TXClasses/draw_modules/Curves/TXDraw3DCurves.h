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

class TXDraw3DCurves  :  public TXDrawBase
{
public:
    
    // NOTE - adjust totalCurveTypes when adding new types:
    const static int totalCurveTypes = 5;
    const static int maxCurves = 1000;
    const static int maxCurvePoints = 8;
    const static int maxSpreadTypes = 32;
    
    TXDraw3DCurves();
    
    void setup();
    virtual void draw();
    void rotate(float rotX, float rotY, float rotZ);
    
    ofPtr<TXModParamInt> curveType;
    ofPtr<TXModParamInt> numCurves;
    ofPtr<TXModParamInt> numPoints;
    ofPtr<TXModParamInt> lineWidth;

    // OLD
        ofPtr<TXModParamInt> spreadType;
        ofPtr<TXModParamInt> spreadType2;
        ofPtr<TXModParamFloat> spreadTypeMorph;
    TXParameterFloat256   curveSpreadCurve;
    TXParameterFloat256   curveSpreadCurve2;
    ofPtr<TXModParamFloat> curveSpreadCurveMorph;

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
    
    ofPtr<TXModParamInt> transformOrder;
    ofPtr<TXModParamFloat> shiftX;
    ofPtr<TXModParamFloat> shiftXEnd;
    ofPtr<TXModParamBool> shiftXEndIgnore;
    ofPtr<TXModParamFloat> shiftY;
    ofPtr<TXModParamFloat> shiftYEnd;
    ofPtr<TXModParamBool> shiftYEndIgnore;
    ofPtr<TXModParamFloat> shiftZ;
    ofPtr<TXModParamFloat> shiftZEnd;
    ofPtr<TXModParamBool> shiftZEndIgnore;
    TXParameterFloat256   shiftXSpreadCurve;
    TXParameterFloat256   shiftXSpreadCurve2;
    ofPtr<TXModParamFloat> shiftXSpreadCurveMorph;
    TXParameterFloat256   shiftYSpreadCurve;
    TXParameterFloat256   shiftYSpreadCurve2;
    ofPtr<TXModParamFloat> shiftYSpreadCurveMorph;
    TXParameterFloat256   shiftZSpreadCurve;
    TXParameterFloat256   shiftZSpreadCurve2;
    ofPtr<TXModParamFloat> shiftZSpreadCurveMorph;
    ofParameter<bool> useShiftXSpreadCurveForShiftY;
    ofParameter<bool> useShiftXSpreadCurveForShiftZ;
    ofPtr<TXModParamFloat> rotateX;
    ofPtr<TXModParamFloat> rotateXEnd;
    ofPtr<TXModParamBool> rotateXEndIgnore;
    ofPtr<TXModParamFloat> rotateY;
    ofPtr<TXModParamFloat> rotateYEnd;
    ofPtr<TXModParamBool> rotateYEndIgnore;
    ofPtr<TXModParamFloat> rotateZ;
    ofPtr<TXModParamFloat> rotateZEnd;
    ofPtr<TXModParamBool> rotateZEndIgnore;
    ofPtr<TXModParamFloat> rotateMultiply;
    TXParameterFloat256   rotateXSpreadCurve;
    TXParameterFloat256   rotateXSpreadCurve2;
    ofPtr<TXModParamFloat> rotateXSpreadCurveMorph;
    TXParameterFloat256   rotateYSpreadCurve;
    TXParameterFloat256   rotateYSpreadCurve2;
    ofPtr<TXModParamFloat> rotateYSpreadCurveMorph;
    TXParameterFloat256   rotateZSpreadCurve;
    TXParameterFloat256   rotateZSpreadCurve2;
    ofPtr<TXModParamFloat> rotateZSpreadCurveMorph;
    ofParameter<bool> useRotateXSpreadCurveForRotateY;
    ofParameter<bool> useRotateXSpreadCurveForRotateZ;
    ofPtr<TXModParamFloat> anchorX;
    ofPtr<TXModParamFloat> anchorXEnd;
    ofPtr<TXModParamBool> anchorXEndIgnore;
    ofPtr<TXModParamFloat> anchorY;
    ofPtr<TXModParamFloat> anchorYEnd;
    ofPtr<TXModParamBool> anchorYEndIgnore;
    ofPtr<TXModParamFloat> anchorZ;
    ofPtr<TXModParamFloat> anchorZEnd;
    ofPtr<TXModParamBool> anchorZEndIgnore;
    TXParameterFloat256   anchorXSpreadCurve;
    TXParameterFloat256   anchorXSpreadCurve2;
    ofPtr<TXModParamFloat> anchorXSpreadCurveMorph;
    TXParameterFloat256   anchorYSpreadCurve;
    TXParameterFloat256   anchorYSpreadCurve2;
    ofPtr<TXModParamFloat> anchorYSpreadCurveMorph;
    TXParameterFloat256   anchorZSpreadCurve;
    TXParameterFloat256   anchorZSpreadCurve2;
    ofPtr<TXModParamFloat> anchorZSpreadCurveMorph;
    ofParameter<bool> useAnchorXSpreadCurveForAnchorY;
    ofParameter<bool> useAnchorXSpreadCurveForAnchorZ;
    ofPtr<TXModParamFloat> scaleX;
    ofPtr<TXModParamFloat> scaleXEnd;
    ofPtr<TXModParamBool> scaleXEndIgnore;
    ofPtr<TXModParamFloat> scaleY;
    ofPtr<TXModParamFloat> scaleYEnd;
    ofPtr<TXModParamBool> scaleYEndIgnore;
    ofPtr<TXModParamFloat> scaleZ;
    ofPtr<TXModParamFloat> scaleZEnd;
    ofPtr<TXModParamBool> scaleZEndIgnore;
    ofParameter<bool> useScaleXForScaleY;
    ofParameter<bool> useScaleXForScaleZ;
    TXParameterFloat256   scaleXSpreadCurve;
    TXParameterFloat256   scaleXSpreadCurve2;
    ofPtr<TXModParamFloat> scaleXSpreadCurveMorph;
    TXParameterFloat256   scaleYSpreadCurve;
    TXParameterFloat256   scaleYSpreadCurve2;
    ofPtr<TXModParamFloat> scaleYSpreadCurveMorph;
    TXParameterFloat256   scaleZSpreadCurve;
    TXParameterFloat256   scaleZSpreadCurve2;
    ofPtr<TXModParamFloat> scaleZSpreadCurveMorph;
    ofParameter<bool> useScaleXSpreadCurveForScaleY;
    ofParameter<bool> useScaleXSpreadCurveForScaleZ;

    TXCurvePoint arrCurvePoints[maxCurvePoints];
    TXCurvePoint autoCurveStart;
    TXCurvePoint autoCurveEnd;
    
private:
    ofShader shader;
    bool useShader;
};
