/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXDraw2DShape.h"
#include "TXFunctions.h"

TXDraw2DShape::TXDraw2DShape() {
    setup();
}

// destructor
TXDraw2DShape::~TXDraw2DShape() {
}

void TXDraw2DShape::setup(string paramNamePrefix){
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
    
    holdModParamIntArgs.name = paramNamePrefix + "shapeType";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = total2DShapeTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = total2DShapeTypes - 1;
	shapeType = createModParameter(holdModParamIntArgs);
    parameters.add(shapeType->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "lineWidth";
    holdModParamIntArgs.fixedValue = 2;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 10;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 10;
    lineWidth = createModParameter(holdModParamIntArgs);
    parameters.add(lineWidth->parameters);
    
    holdModParamBoolArgs.name = paramNamePrefix + "fillShape";
    holdModParamBoolArgs.fixedValue = true;
    holdModParamBoolArgs.fixedModMix = false;
	fillShape = createModParameter(holdModParamBoolArgs);
    parameters.add(fillShape->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "width";
    holdModParamFloatArgs.fixedValue = 0.2;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	width = createModParameter(holdModParamFloatArgs);
    parameters.add(width->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "height";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	height = createModParameter(holdModParamFloatArgs);
    parameters.add(height->parameters);
    
    parameters.add(useMaxWidthToScaleHeight.set(paramNamePrefix + "useMaxWidthToScaleHeight", false));
    
    holdModParamFloatArgs.name = paramNamePrefix + "roundness";
    holdModParamFloatArgs.fixedValue = 0.2;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    roundness = createModParameter(holdModParamFloatArgs);
    parameters.add(roundness->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "thickness";
    holdModParamFloatArgs.fixedValue = 0.2;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    thickness = createModParameter(holdModParamFloatArgs);
    parameters.add(thickness->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "circleResolution";
    holdModParamIntArgs.fixedValue = 32;
    holdModParamIntArgs.hardMin = 3;
    holdModParamIntArgs.hardMax = 1024;
    holdModParamIntArgs.softMin = 3;
    holdModParamIntArgs.softMax = 128;
	circleResolution = createModParameter(holdModParamIntArgs);
    parameters.add(circleResolution->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "colorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	colorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(colorHue->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "colorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	colorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(colorHueRotate->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "colorSaturation";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	colorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(colorSaturation->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "colorBrightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	colorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(colorBrightness->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "colorAlpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	colorAlpha = createModParameter(holdModParamFloatArgs);
    parameters.add(colorAlpha->parameters);
    
    holdModParamBoolArgs.name = paramNamePrefix + "colorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	colorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(colorHSBAsRGB->parameters);
    
    holdModParamBoolArgs.name = paramNamePrefix + "useFillColorForLineColor";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
    useFillColorForLineColor = createModParameter(holdModParamBoolArgs);
    parameters.add(useFillColorForLineColor->parameters);
    
    holdModParamBoolArgs.name = paramNamePrefix + "swapFillColorAndLineColor";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
    swapFillColorAndLineColor = createModParameter(holdModParamBoolArgs);
    parameters.add(swapFillColorAndLineColor->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "lineColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    lineColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(lineColorHue->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "lineColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    lineColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(lineColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "lineColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    lineColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(lineColorSaturation->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "lineColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    lineColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(lineColorBrightness->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "lineColorAlpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    lineColorAlpha = createModParameter(holdModParamFloatArgs);
    parameters.add(lineColorAlpha->parameters);
    
    holdModParamBoolArgs.name = paramNamePrefix + "lineColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
    lineColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(lineColorHSBAsRGB->parameters);
    
/////////////
    
    holdModParamFloatArgs.name = paramNamePrefix + "positionX";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	positionX = createModParameter(holdModParamFloatArgs);
    parameters.add(positionX->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "positionY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	positionY = createModParameter(holdModParamFloatArgs);
    parameters.add(positionY->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "rotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	rotate = createModParameter(holdModParamFloatArgs);
    parameters.add(rotate->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "rotateMultiply";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
	rotateMultiply = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateMultiply->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "anchorX";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	anchorX = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorX->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "anchorY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	anchorY = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorY->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "scaleX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 3.0;
	scaleX = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleX->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "scaleY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 3.0;
	scaleY = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleY->parameters);
    
    parameters.add(useScaleXForScaleY.set(paramNamePrefix + "useScaleXForScaleY", false));

}

 void TXDraw2DShape::draw(){
     int num;
     float holdWidth, holdThickness, holdHeight, holdRoundness;
     float holdPosX, holdPosY;
     float holdScaleX, holdScaleY;
     float holdAnchorX, holdAnchorY;
     float heightScale;
     int holdCircleResolution;
     bool holdIsFilled;
     ofColor holdFillColor, holdLineColor;
     float holdLineWidth;

     if (!drawActive->getBool()) {
         return;
     };
     holdLineWidth = lineWidth->getInt();
     holdIsFilled = fillShape->getBool();
     holdFillColor =  TXFunctions::txGetColor(colorHue->getFloat(),  colorSaturation->getFloat(),  colorBrightness->getFloat(),  colorAlpha->getFloat(), colorHueRotate->getFloat(), colorHSBAsRGB->getBool());
     if (useFillColorForLineColor->getBool()) {
         holdLineColor =  holdFillColor;
     } else if (swapFillColorAndLineColor->getBool()) {
         holdLineColor =  holdFillColor;
         holdFillColor =  TXFunctions::txGetColor(lineColorHue->getFloat(),  lineColorSaturation->getFloat(),  lineColorBrightness->getFloat(),  lineColorAlpha->getFloat(), lineColorHueRotate->getFloat(), lineColorHSBAsRGB->getBool());
     } else {
         holdLineColor =  TXFunctions::txGetColor(lineColorHue->getFloat(),  lineColorSaturation->getFloat(),  lineColorBrightness->getFloat(),  lineColorAlpha->getFloat(), lineColorHueRotate->getFloat(), lineColorHSBAsRGB->getBool());
     };
     holdScaleX = scaleX->getFloat();
     if (useScaleXForScaleY) {
         holdScaleY = holdScaleX;
     } else {
         holdScaleY = scaleY->getFloat();
     };
     
     ofPushMatrix();
     
     ofTranslate(positionX->getFloat() * getMaxWidth(), positionY->getFloat() * getMaxHeight(), 0.0);
     ofRotateZ(rotateMultiply->getFloat() * rotate->getFloat());
     ofScale(holdScaleX, holdScaleY, 1.0);

     if (useMaxWidthToScaleHeight) {
         heightScale = getMaxWidth();
     } else {
         heightScale = getMaxHeight();
     };

     ofEnableAlphaBlending();
     switch (shapeType->getInt()) {
         case TX2DSHAPETYPE_CIRCLE:
             holdWidth = width->getFloat() * getMaxWidth();
             holdAnchorX = (anchorX->getFloat() - 0.5) * holdWidth;
             holdAnchorY = (anchorY->getFloat() - 0.5) * holdWidth;
             holdCircleResolution = circleResolution->getInt();
             drawEllipse(holdWidth, holdWidth, holdCircleResolution, holdFillColor, holdLineColor, holdLineWidth, holdIsFilled, holdAnchorX, holdAnchorY);
             break;
         case TX2DSHAPETYPE_ELLIPSE:
             holdWidth = width->getFloat() * getMaxWidth();
             holdHeight = height->getFloat() * heightScale;
             holdAnchorX = (anchorX->getFloat() - 0.5) * holdWidth;
             holdAnchorY = (anchorY->getFloat() - 0.5) * holdHeight;
             holdCircleResolution = circleResolution->getInt();
             drawEllipse(holdWidth, holdHeight, holdCircleResolution, holdFillColor, holdLineColor, holdLineWidth, holdIsFilled, holdAnchorX, holdAnchorY);
             break;
         case TX2DSHAPETYPE_SQUARE:
             holdWidth = width->getFloat() * getMaxWidth();
             holdAnchorX = (anchorX->getFloat() - 0.5) * holdWidth;
             holdAnchorY = (anchorY->getFloat() - 0.5) * holdWidth;
             drawRectangle(holdWidth, holdWidth, holdFillColor, holdLineColor, holdLineWidth, holdIsFilled, holdAnchorX, holdAnchorY);
             break;
         case TX2DSHAPETYPE_RECTANGLE:
             holdWidth = width->getFloat() * getMaxWidth();
             holdHeight = height->getFloat() * heightScale;
             holdAnchorX = (anchorX->getFloat() - 0.5) * holdWidth;
             holdAnchorY = (anchorY->getFloat() - 0.5) * holdHeight;
             drawRectangle(holdWidth, holdHeight, holdFillColor, holdLineColor, holdLineWidth, holdIsFilled, holdAnchorX, holdAnchorY);
             break;
         case TX2DSHAPETYPE_ROUNDRECTANGLE:
             holdWidth = width->getFloat() * getMaxWidth();
             holdHeight = height->getFloat() * heightScale;
             holdRoundness = roundness->getFloat() * min(holdWidth, holdHeight) * 0.5;
             holdAnchorX = (anchorX->getFloat() - 0.5) * holdWidth;
             holdAnchorY = (anchorY->getFloat() - 0.5) * holdHeight;
             holdCircleResolution = circleResolution->getInt() * 4;
             drawRoundRectangle(holdWidth, holdHeight, holdRoundness, holdCircleResolution, holdFillColor, holdLineColor, holdLineWidth, holdIsFilled, holdAnchorX, holdAnchorY);
             break;
         case TX2DSHAPETYPE_STAR:
             holdWidth = width->getFloat() * getMaxWidth();
             holdHeight = height->getFloat() * heightScale;
             holdAnchorX = (anchorX->getFloat() - 0.5) * max(holdWidth, holdHeight);
             holdAnchorY = (anchorY->getFloat() - 0.5) * max(holdWidth, holdHeight);
             holdCircleResolution = circleResolution->getInt();
             drawStar(holdWidth, holdHeight, holdCircleResolution, holdFillColor, holdLineColor, holdLineWidth, holdIsFilled, holdAnchorX, holdAnchorY);
             break;
         case TX2DSHAPETYPE_ISOSCELES_TRIANGLE:
             holdWidth = width->getFloat() * getMaxWidth();
             holdHeight = height->getFloat() * heightScale;
             holdAnchorX = (anchorX->getFloat() - 0.5) * max(holdWidth, holdHeight);
             holdAnchorY = (anchorY->getFloat() - 0.5) * max(holdWidth, holdHeight);
             drawIsoscelesTriangle(holdWidth, holdHeight, holdFillColor, holdLineColor, holdLineWidth, holdIsFilled, holdAnchorX, holdAnchorY);
             break;
         case TX2DSHAPETYPE_RIGHT_TRIANGLE:
             holdWidth = width->getFloat() * getMaxWidth();
             holdHeight = height->getFloat() * heightScale;
             holdAnchorX = (anchorX->getFloat() - 0.5) * max(holdWidth, holdHeight);
             holdAnchorY = (anchorY->getFloat() - 0.5) * max(holdWidth, holdHeight);
             drawRightTriangle(holdWidth, holdHeight, holdFillColor, holdLineColor, holdLineWidth, holdIsFilled, holdAnchorX, holdAnchorY);
             break;
         case TX2DSHAPETYPE_DIAMOND:
             holdWidth = width->getFloat() * getMaxWidth();
             holdHeight = height->getFloat() * heightScale;
             holdAnchorX = (anchorX->getFloat() - 0.5) * max(holdWidth, holdHeight);
             holdAnchorY = (anchorY->getFloat() - 0.5) * max(holdWidth, holdHeight);
             drawDiamond(holdWidth, holdHeight, holdFillColor, holdLineColor, holdLineWidth, holdIsFilled, holdAnchorX, holdAnchorY);
             break;
         case TX2DSHAPETYPE_CRESCENT:
             holdWidth = width->getFloat() * getMaxWidth();
             holdThickness = thickness->getFloat();
             holdHeight = height->getFloat() * heightScale;
             holdAnchorX = (anchorX->getFloat() - 0.5) * max(holdWidth, holdHeight);
             holdAnchorY = (anchorY->getFloat() - 0.5) * max(holdWidth, holdHeight);
             holdCircleResolution = circleResolution->getInt();
             drawCrescent(holdWidth, holdHeight, holdCircleResolution, holdThickness, holdFillColor, holdLineColor, holdLineWidth, holdIsFilled, holdAnchorX, holdAnchorY);
             break;
         case TX2DSHAPETYPE_RING:
             holdWidth = width->getFloat() * getMaxWidth();
             holdThickness = thickness->getFloat();
             holdHeight = height->getFloat() * heightScale;
             holdAnchorX = (anchorX->getFloat() - 0.5) * max(holdWidth, holdHeight);
             holdAnchorY = (anchorY->getFloat() - 0.5) * max(holdWidth, holdHeight);
             holdCircleResolution = circleResolution->getInt();
             drawRing(holdWidth, holdCircleResolution, holdThickness, holdFillColor, holdLineColor, holdLineWidth, holdIsFilled, holdAnchorX, holdAnchorY);
             break;
         default:
             holdWidth = width->getFloat() * getMaxWidth();
             holdAnchorX = (anchorX->getFloat() - 0.5) * holdWidth;
             holdAnchorY = (anchorY->getFloat() - 0.5) * holdWidth;
             holdCircleResolution = circleResolution->getInt();
             drawEllipse(holdWidth, holdWidth, holdCircleResolution, holdFillColor, holdLineColor, holdLineWidth, holdIsFilled, holdAnchorX, holdAnchorY);
             break;
     }
     ofDisableAlphaBlending();

     ofPopMatrix();
 }

void TXDraw2DShape::drawPath(int argLineWidth, ofColor & argColor,  ofColor & argLineColor, bool & argIsFilled, float & argAnchorX, float & argAnchorY){
//    holdPath.setFilled(argIsFilled);
//    holdPath.setFillColor(argColor);
//    holdPath.setStrokeColor(argLineColor);
//    holdPath.setStrokeWidth(argLineWidth);
//    holdPath.draw(-argAnchorX, -argAnchorY);
    if (argIsFilled) {
        holdPath.setFilled(true);
        holdPath.setFillColor(argColor);
        holdPath.setStrokeWidth(0);
        holdPath.draw(-argAnchorX, -argAnchorY);
    };
    if (argLineWidth > 0) {
        holdPath.setFilled(false);
        holdPath.setStrokeColor(argLineColor);
        holdPath.setStrokeWidth(argLineWidth);
        holdPath.draw(-argAnchorX, -argAnchorY);
    };
}

void TXDraw2DShape::drawEllipse(float & argWidth, float & argHeight, int & argCircleResolution, ofColor & argColor,  ofColor & argLineColor, int argLineWidth, bool & argIsFilled, float & argAnchorX, float & argAnchorY){
//    holdPath.clear();
//    holdPath.ellipse(0, 0, argWidth,  argHeight);
//    holdPath.setCircleResolution(argCircleResolution);
//    drawPath(argLineWidth, argColor, argLineColor, argIsFilled, argAnchorX, argAnchorY);
    ofPushStyle();
    ofSetCircleResolution(argCircleResolution);
    if (argIsFilled) {
        ofFill();
        ofSetColor(argColor);
        ofSetLineWidth(0);
        ofDrawEllipse(0, 0, argWidth,  argHeight);
    };
    if (argLineWidth > 0) {
        ofNoFill();
        ofSetColor(argLineColor);
        ofSetLineWidth(argLineWidth);
        ofDrawEllipse(0, 0, argWidth,  argHeight);
    }
    ofPopStyle();
}

void TXDraw2DShape::drawRectangle(float & argWidth, float & argHeight, ofColor & argColor,  ofColor & argLineColor, int argLineWidth, bool & argIsFilled, float & argAnchorX, float & argAnchorY){
    holdPath.clear();
    holdPath.rectangle(argWidth * -0.5, argHeight * -0.5, argWidth,  argHeight);
    drawPath(argLineWidth, argColor, argLineColor, argIsFilled, argAnchorX, argAnchorY);
}

void TXDraw2DShape::drawRoundRectangle(float & argWidth, float & argHeight, float & argRadius, int & argCircleResolution, ofColor & argColor,  ofColor & argLineColor, int argLineWidth, bool & argIsFilled, float & argAnchorX, float & argAnchorY){
    holdPath.clear();
    holdPath.setCircleResolution(argCircleResolution);
    holdPath.rectRounded(argWidth * -0.5, argHeight * -0.5, argWidth,  argHeight, argRadius);
    drawPath(argLineWidth, argColor, argLineColor, argIsFilled, argAnchorX, argAnchorY);
}

void TXDraw2DShape::drawStar(float & argRadius1, float & argRadius2, int & argNumPoints, ofColor & argColor,  ofColor & argLineColor, int argLineWidth, bool & argIsFilled, float & argAnchorX, float & argAnchorY){
    ofPoint holdPoint;
    float holdRadius;
    float twoPIPhase;
    int totalPoints = argNumPoints * 2;

    holdPath.clear();
    for (int i=0; i<totalPoints; i++){
        twoPIPhase = TWO_PI *  (i+1) / totalPoints;
        if ((i % 2) == 0) {
            holdRadius = argRadius1 * 0.5;
        } else {
            holdRadius = argRadius2 * 0.5;
        };
        holdPoint.set(holdRadius * sin(twoPIPhase), holdRadius * cos(twoPIPhase));
        if (i == 0) {
            holdPath.moveTo(holdPoint);
        } else {
            holdPath.lineTo(holdPoint);
        }
	}
    holdPath.close();
    drawPath(argLineWidth, argColor, argLineColor, argIsFilled, argAnchorX, argAnchorY);
}

void TXDraw2DShape::drawIsoscelesTriangle(float & argWidth, float & argHeight, ofColor & argColor,  ofColor & argLineColor, int argLineWidth, bool & argIsFilled, float & argAnchorX, float & argAnchorY) {
    ofPoint offset, point1, point2, point3;
    offset.set(argWidth * -0.5, argHeight * -0.5);
    point1.set(0, 0);
    point2.set(argWidth * 0.5, argHeight);
    point3.set(argWidth, 0);

    holdPath.clear();
    holdPath.moveTo(point1 + offset);
    holdPath.lineTo(point2 + offset);
    holdPath.lineTo(point3 + offset);
    holdPath.lineTo(point1 + offset);
    holdPath.close();
    drawPath(argLineWidth, argColor, argLineColor, argIsFilled, argAnchorX, argAnchorY);
}

void TXDraw2DShape::drawRightTriangle(float & argWidth, float & argHeight, ofColor & argColor,  ofColor & argLineColor, int argLineWidth, bool & argIsFilled, float & argAnchorX, float & argAnchorY) {
    ofPoint offset, point1, point2, point3;
    offset.set(argWidth * -0.5, argHeight * -0.5);
    point1.set(0, 0);
    point2.set(0, argHeight);
    point3.set(argWidth, 0);
    
    holdPath.clear();
    holdPath.moveTo(point1 + offset);
    holdPath.lineTo(point2 + offset);
    holdPath.lineTo(point3 + offset);
    holdPath.lineTo(point1 + offset);
    holdPath.close();
    drawPath(argLineWidth, argColor, argLineColor, argIsFilled, argAnchorX, argAnchorY);
}

void TXDraw2DShape::drawDiamond(float & argWidth, float & argHeight, ofColor & argColor,  ofColor & argLineColor, int argLineWidth, bool & argIsFilled, float & argAnchorX, float & argAnchorY){
    ofPoint offset, point1, point2, point3, point4;
    offset.set(argWidth * -0.5, argHeight * -0.5);
    point1.set(argWidth * 0.5, 0);
    point2.set(0, argHeight * 0.5);
    point3.set(argWidth * 0.5, argHeight);
    point4.set(argWidth, argHeight * 0.5);
    
    holdPath.clear();
    holdPath.moveTo(point1 + offset);
    holdPath.lineTo(point2 + offset);
    holdPath.lineTo(point3 + offset);
    holdPath.lineTo(point4 + offset);
    holdPath.lineTo(point1 + offset);
    holdPath.close();
    drawPath(argLineWidth, argColor, argLineColor, argIsFilled, argAnchorX, argAnchorY);
}

void TXDraw2DShape::drawCrescent(float & argWidth, float & argHeight, int & argCurveResolution, float & argThickness, ofColor & argColor,  ofColor & argLineColor, int argLineWidth, bool & argIsFilled, float & argAnchorX, float & argAnchorY) {
    ofPoint offset, point1, point2, control1, control2, control1a, control2a;
    offset.set(argWidth * -0.5, argHeight * -0.5);
    point1.set(0, 0);
    point2.set(0, argHeight);
    control1.set(argWidth, 0);
    control2.set(argWidth, argHeight);
    control1a.set(argWidth * (1 - argThickness), 0);
    control2a.set(argWidth * (1 - argThickness), argHeight);
    
    holdPath.clear();
    holdPath.setCurveResolution(argCurveResolution);
    holdPath.moveTo(point1 + offset);
    holdPath.bezierTo(control1 + offset, control2 + offset, point2 + offset);
    holdPath.bezierTo(control2a + offset, control1a + offset, point1 + offset);
    holdPath.close();
    drawPath(argLineWidth, argColor, argLineColor, argIsFilled, argAnchorX, argAnchorY);
}

void TXDraw2DShape::drawRing(float & argWidth, int & argCurveResolution, float & argThickness, ofColor & argColor,  ofColor & argLineColor, int argLineWidth, bool & argIsFilled, float & argAnchorX, float & argAnchorY){
    ofPoint offset, point1, point2, point3, point4;
    ofPoint control1, control2, control3, control4;
    ofPoint control1a, control2a, control3a, control4a;
    float margin, controlMargin, controlWidthOffset;
    controlWidthOffset = 1.333333333 * argWidth * 0.5;
    offset.set(argWidth * -0.5, argWidth * -0.5);
    point1.set(argWidth * 0.5, 0);
    point2.set(argWidth * 0.5, argWidth);
    control1.set(argWidth * 0.5 + controlWidthOffset, 0);
    control2.set(argWidth * 0.5 + controlWidthOffset, argWidth);
    control1a.set(argWidth * 0.5 - controlWidthOffset, 0);
    control2a.set(argWidth * 0.5 - controlWidthOffset, argWidth);
    
    holdPath.clear();
    holdPath.setCurveResolution(argCurveResolution);
    holdPath.moveTo(point1 + offset);
    holdPath.bezierTo(control1 + offset, control2 + offset, point2 + offset);
    holdPath.bezierTo(control2a + offset, control1a + offset, point1 + offset);
    //holdPath.close();
    if (argThickness < 1) {
        margin = argWidth * 0.5 * argThickness;
        controlMargin = 1.333333333 * margin;
        point3.set(argWidth * 0.5, margin);
        point4.set(argWidth * 0.5, argWidth - margin);
        control3.set(argWidth * 0.5 + controlWidthOffset - controlMargin, margin);
        control4.set(argWidth * 0.5 + controlWidthOffset - controlMargin, argWidth - margin);
        control3a.set(argWidth * 0.5 - controlWidthOffset + controlMargin, margin);
        control4a.set(argWidth * 0.5 - controlWidthOffset + controlMargin, argWidth - margin);
        holdPath.moveTo(point3 + offset);
        holdPath.bezierTo(control3 + offset, control4 + offset, point4 + offset);
        holdPath.bezierTo(control4a + offset, control3a + offset, point3 + offset);
    };
    holdPath.close();
    drawPath(argLineWidth, argColor, argLineColor, argIsFilled, argAnchorX, argAnchorY);
}
