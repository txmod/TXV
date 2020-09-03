/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXDrawBase.h"
#include "TXDraw2DShape.h"
//#include "TXMain.h"

//0 circle(w), 1 ellipse(w/h), 2 square(w), 3 rectangle(w/h), 4 roundRect(w/h/roundness)
//5 Star -Width, Height,
//6 Triangle 1 (equilateral) - Width, Height,
//7 Triangle 2 - Width, Height,
//8 Diamond - Width, Height
//9 Crescent - Width, Height , Thickness(0-1), circleResolution
//10 Ring - Width,  Thickness(0-1), circleResolution

//enum TX2DSHAPETYPE {
//    TX2DSHAPETYPE_CIRCLE,
//    TX2DSHAPETYPE_ELLIPSE,
//    TX2DSHAPETYPE_SQUARE,
//    TX2DSHAPETYPE_RECTANGLE,
//    TX2DSHAPETYPE_ROUNDRECTANGLE,
//    TX2DSHAPETYPE_STAR,
//    TX2DSHAPETYPE_ISOSCELES_TRIANGLE,
//    TX2DSHAPETYPE_RIGHT_TRIANGLE,
//    TX2DSHAPETYPE_DIAMOND,
//    TX2DSHAPETYPE_CRESCENT,
//    TX2DSHAPETYPE_RING,
//};

class TXDraw2DShapeMulti  :  public TXDrawBase
{
public:
    
    // NOTE - change when adding new types:
    const int total2DShapeTypes = 11;
    const static int maxCopies = 1000;

	// constructor
	TXDraw2DShapeMulti();
    
    // destructor
    ~TXDraw2DShapeMulti();

	void setup();
	virtual void draw();
	//void drawStar(float & argRadius1, float & argRadius2, int & argNumPoints, ofColor & argColor, bool & argIsFilled, float & argAnchorX, float & argAnchorY);
    
    ofPtr<TXModParamInt> shapeType;
    ofPtr<TXModParamInt> numCopies;
    ofPtr<TXModParamInt> lineWidth;
    ofPtr<TXModParamBool> fillShape;
    ofPtr<TXModParamFloat> width;
    ofPtr<TXModParamFloat> widthEnd;
    ofParameter<bool>     widthEndIgnore;
    ofPtr<TXModParamFloat> height;
    ofPtr<TXModParamFloat> heightEnd;
    ofParameter<bool>     heightEndIgnore;
    ofParameter<bool>     useMaxWidthToScaleHeight;
    ofPtr<TXModParamFloat> roundness;
    ofPtr<TXModParamFloat> roundnessEnd;
    ofParameter<bool>     roundnessEndIgnore;
    ofPtr<TXModParamFloat> thickness;
    ofPtr<TXModParamFloat> thicknessEnd;
    ofParameter<bool>     thicknessEndIgnore;
    ofPtr<TXModParamInt> circleResolution;
    TXParameterFloat256   sizeSpreadCurve;
    TXParameterFloat256   sizeSpreadCurve2;
    ofPtr<TXModParamFloat> sizeSpreadCurveMorph;
    ofPtr<TXModParamFloat> sizeSpreadCurvePhase;
    
    ofPtr<TXModParamFloat> colorHue;
    ofPtr<TXModParamFloat> colorHueEnd;
    ofParameter<bool>     colorHueEndIgnore;
    ofPtr<TXModParamFloat> colorHueRotate;
    ofPtr<TXModParamFloat> colorSaturation;
    ofPtr<TXModParamFloat> colorSaturationEnd;
    ofParameter<bool>     colorSaturationEndIgnore;
    ofPtr<TXModParamFloat> colorBrightness;
    ofPtr<TXModParamFloat> colorBrightnessEnd;
    ofParameter<bool>     colorBrightnessEndIgnore;
    ofPtr<TXModParamFloat> colorAlpha;
    ofPtr<TXModParamFloat> colorAlphaEnd;
    ofParameter<bool>     colorAlphaEndIgnore;
    ofPtr<TXModParamBool> colorHSBAsRGB;
    ofPtr<TXModParamBool> useFillColorForLineColor;
    ofPtr<TXModParamBool> swapFillColorAndLineColor;
    ofPtr<TXModParamFloat> lineColorHue;
    ofPtr<TXModParamFloat> lineColorHueEnd;
    ofParameter<bool>     lineColorHueEndIgnore;
    ofPtr<TXModParamFloat> lineColorHueRotate;
    ofPtr<TXModParamFloat> lineColorSaturation;
    ofPtr<TXModParamFloat> lineColorSaturationEnd;
    ofParameter<bool>     lineColorSaturationEndIgnore;
    ofPtr<TXModParamFloat> lineColorBrightness;
    ofPtr<TXModParamFloat> lineColorBrightnessEnd;
    ofParameter<bool>     lineColorBrightnessEndIgnore;
    ofPtr<TXModParamFloat> lineColorAlpha;
    ofPtr<TXModParamFloat> lineColorAlphaEnd;
    ofParameter<bool>     lineColorAlphaEndIgnore;
    ofPtr<TXModParamBool> lineColorHSBAsRGB;
    TXParameterFloat256   colorSpreadCurve;
    TXParameterFloat256   colorSpreadCurve2;
    ofPtr<TXModParamFloat> colorSpreadCurveMorph;
    ofPtr<TXModParamFloat> colorSpreadCurvePhase;

    ofPtr<TXModParamFloat> centrePositionX;
    ofPtr<TXModParamFloat> centrePositionY;
    ofPtr<TXModParamFloat> positionX;
    ofPtr<TXModParamFloat> positionXEnd;
    ofParameter<bool>     positionXEndIgnore;
    ofPtr<TXModParamFloat> positionY;
    ofPtr<TXModParamFloat> positionYEnd;
    ofParameter<bool>     positionYEndIgnore;
    TXParameterFloat256   positionXSpreadCurve;
    TXParameterFloat256   positionXSpreadCurve2;
    ofPtr<TXModParamFloat> positionXSpreadCurveMorph;
    ofPtr<TXModParamFloat> positionXSpreadCurvePhase;
    ofParameter<bool>      usePosXSpreadCurveForPosY;
    TXParameterFloat256   positionYSpreadCurve;
    TXParameterFloat256   positionYSpreadCurve2;
    ofPtr<TXModParamFloat> positionYSpreadCurveMorph;
    ofPtr<TXModParamFloat> positionYSpreadCurvePhase;
    ofPtr<TXModParamFloat> rotate;
    ofPtr<TXModParamFloat> rotateEnd;
    ofParameter<bool>     rotateEndIgnore;
    ofPtr<TXModParamFloat> rotateMultiply;
    ofPtr<TXModParamFloat> rotateMultiplyEnd;
    ofParameter<bool>     rotateMultiplyEndIgnore;
    TXParameterFloat256   rotateSpreadCurve;
    TXParameterFloat256   rotateSpreadCurve2;
    ofPtr<TXModParamFloat> rotateSpreadCurveMorph;
    ofPtr<TXModParamFloat> rotateSpreadCurvePhase;
    ofPtr<TXModParamFloat> anchorX;
    ofPtr<TXModParamFloat> anchorXEnd;
    ofParameter<bool>     anchorXEndIgnore;
    ofPtr<TXModParamFloat> anchorY;
    ofPtr<TXModParamFloat> anchorYEnd;
    ofParameter<bool>     anchorYEndIgnore;
    TXParameterFloat256   anchorSpreadCurve;
    TXParameterFloat256   anchorSpreadCurve2;
    ofPtr<TXModParamFloat> anchorSpreadCurveMorph;
    ofPtr<TXModParamFloat> anchorSpreadCurvePhase;
    ofPtr<TXModParamFloat> scaleX;
    ofPtr<TXModParamFloat> scaleXEnd;
    ofParameter<bool>     scaleXEndIgnore;
    ofPtr<TXModParamFloat> scaleY;
    ofPtr<TXModParamFloat> scaleYEnd;
    ofParameter<bool>     scaleYEndIgnore;
    ofParameter<bool>     useScaleXForScaleY;
    TXParameterFloat256   scaleXSpreadCurve;
    TXParameterFloat256   scaleXSpreadCurve2;
    ofPtr<TXModParamFloat> scaleXSpreadCurveMorph;
    ofPtr<TXModParamFloat> scaleXSpreadCurvePhase;
    ofParameter<bool>     useScaleXSpreadCurveForScaleY;
    TXParameterFloat256   scaleYSpreadCurve;
    TXParameterFloat256   scaleYSpreadCurve2;
    ofPtr<TXModParamFloat> scaleYSpreadCurveMorph;
    ofPtr<TXModParamFloat> scaleYSpreadCurvePhase;
    
private:
	ofPath holdStar;
    TXDraw2DShape shape;
};

