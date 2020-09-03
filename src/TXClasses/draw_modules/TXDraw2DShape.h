/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXDrawBase.h"
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

class TXDraw2DShape  :  public TXDrawBase
{
public:
    
    // NOTE - change when adding new types:
    const int total2DShapeTypes = 11;

	// constructor
	TXDraw2DShape();
    
    // destructor
    ~TXDraw2DShape();

	void setup(string paramNamePrefix = "");
	virtual void draw();
    void drawPath(int argLineWidth, ofColor & argColor,  ofColor & argLineColor, bool & argIsFilled, float & argAnchorX, float & argAnchorY);
    void drawEllipse(float & argWidth, float & argHeight, int & argCircleResolution, ofColor & argColor,  ofColor & argLineColor, int argLineWidth, bool & argIsFilled, float & argAnchorX, float & argAnchorY);
    void drawRectangle(float & argWidth, float & argHeight, ofColor & argColor,  ofColor & argLineColor, int argLineWidth, bool & argIsFilled, float & argAnchorX, float & argAnchorY);
    void drawRoundRectangle(float & argWidth, float & argHeight, float & argRadius, int & argCircleResolution, ofColor & argColor,  ofColor & argLineColor, int argLineWidth, bool & argIsFilled, float & argAnchorX, float & argAnchorY);
    void drawStar(float & argRadius1, float & argRadius2, int & argNumPoints, ofColor & argColor,  ofColor & argLineColor, int argLineWidth, bool & argIsFilled, float & argAnchorX, float & argAnchorY);
    void drawIsoscelesTriangle(float & argWidth, float & argHeight, ofColor & argColor,  ofColor & argLineColor, int argLineWidth, bool & argIsFilled, float & argAnchorX, float & argAnchorY);
    void drawRightTriangle(float & argWidth, float & argHeight, ofColor & argColor,  ofColor & argLineColor, int argLineWidth, bool & argIsFilled, float & argAnchorX, float & argAnchorY);
    void drawDiamond(float & argWidth, float & argHeight, ofColor & argColor,  ofColor & argLineColor, int argLineWidth, bool & argIsFilled, float & argAnchorX, float & argAnchorY);
    void drawCrescent(float & argWidth, float & argHeight, int & argCurveResolution, float & argThickness, ofColor & argColor,  ofColor & argLineColor, int argLineWidth, bool & argIsFilled, float & argAnchorX, float & argAnchorY);
    void drawRing(float & argWidth, int & argCurveResolution, float & argThickness, ofColor & argColor,  ofColor & argLineColor, int argLineWidth, bool & argIsFilled, float & argAnchorX, float & argAnchorY);
    
    ofPtr<TXModParamInt> shapeType;
    ofPtr<TXModParamBool> fillShape;
    ofPtr<TXModParamFloat> width;
    ofPtr<TXModParamFloat> height;
    ofParameter<bool>     useMaxWidthToScaleHeight;
    ofPtr<TXModParamFloat> roundness;
    ofPtr<TXModParamFloat> thickness;
    ofPtr<TXModParamInt> circleResolution;
    ofPtr<TXModParamFloat> colorHue;
    ofPtr<TXModParamFloat> colorHueRotate;
    ofPtr<TXModParamFloat> colorSaturation;
    ofPtr<TXModParamFloat> colorBrightness;
    ofPtr<TXModParamFloat> colorAlpha;
    ofPtr<TXModParamBool> colorHSBAsRGB;
    ofPtr<TXModParamInt> lineWidth;
    ofPtr<TXModParamBool> useFillColorForLineColor;
    ofPtr<TXModParamBool> swapFillColorAndLineColor;
    ofPtr<TXModParamFloat> lineColorHue;
    ofPtr<TXModParamFloat> lineColorHueRotate;
    ofPtr<TXModParamFloat> lineColorSaturation;
    ofPtr<TXModParamFloat> lineColorBrightness;
    ofPtr<TXModParamFloat> lineColorAlpha;
    ofPtr<TXModParamBool> lineColorHSBAsRGB;
    ofPtr<TXModParamFloat> positionX;
    ofPtr<TXModParamFloat> positionY;
    ofPtr<TXModParamFloat> rotate;
    ofPtr<TXModParamFloat> rotateMultiply;
    ofPtr<TXModParamFloat> anchorX;
    ofPtr<TXModParamFloat> anchorY;
    ofPtr<TXModParamFloat> scaleX;
    ofPtr<TXModParamFloat> scaleY;
    ofParameter<bool>     useScaleXForScaleY;

private:
    ofPath holdPath;
    
};

