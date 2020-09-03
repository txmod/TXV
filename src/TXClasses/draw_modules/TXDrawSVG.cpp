/*
 *  Copyright 2014 Paul Miller. All rights reserved.
 */

#include "TXDrawSVG.h"
#include "TXSystem.h"
#include "TXAsset.h"

TXDrawSVG::TXDrawSVG() {
    setup();
}

void TXDrawSVG::setup(){
//    TXModParameterBoolArgs holdModParamBoolArgs;
//    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
    
    parameters.add(useScaleXForScaleY.set("useScaleXForScaleY", false));
    
    holdModParamFloatArgs.name = "positionX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	positionX = createModParameter(holdModParamFloatArgs);
    parameters.add(positionX->parameters);
    
    holdModParamFloatArgs.name = "positionY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	positionY = createModParameter(holdModParamFloatArgs);
    parameters.add(positionY->parameters);
    
    holdModParamFloatArgs.name = "anchorX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	anchorX = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorX->parameters);
    
    holdModParamFloatArgs.name = "anchorY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	anchorY = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorY->parameters);
    
    holdModParamFloatArgs.name = "rotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	rotate = createModParameter(holdModParamFloatArgs);
    parameters.add(rotate->parameters);
    
    holdModParamFloatArgs.name = "rotateMultiply";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
	rotateMultiply = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateMultiply->parameters);
    
    holdModParamFloatArgs.name = "scaleX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -100.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
	scaleX = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleX->parameters);
    
    holdModParamFloatArgs.name = "scaleY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -100.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
	scaleY = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleY->parameters);
    
    // asset slots
    createSvgAssetSlot("svgAsset");
}

void TXDrawSVG::draw(){
    float holdWidth, holdHeight;
    float holdScaleX, holdScaleY, holdScaleAdjust;
    
    holdWidth = svg.getWidth();
    holdHeight = svg.getHeight();
    
    // check before drawing
    if ((!drawActive->getBool()) || (!(holdWidth > 0.0)) || (!(holdHeight > 0.0))) {
        return;
    };
    int   holdMaxWidth = getMaxWidth();
    int   holdMaxHeight = getMaxHeight();
    float anchorXPixels = anchorX->getFloat() * holdWidth;
    float anchorYPixels = anchorY->getFloat() * holdHeight;
    
    float holdDrawPosX = positionX->getFloat() * holdMaxWidth;
    float holdDrawPosY = positionY->getFloat() * holdMaxHeight;
    
    holdScaleAdjust = fmin(holdMaxWidth, holdMaxHeight) / fmax(holdWidth, holdHeight);
    holdScaleX = scaleX->getFloat() * holdScaleAdjust;
    if (useScaleXForScaleY) {
        holdScaleY = holdScaleX;
    } else {
        holdScaleY = scaleY->getFloat() * holdScaleAdjust;
    };
    // translate, rotate, scale
    ofPushMatrix();
    ofTranslate(holdDrawPosX, holdDrawPosY, 0.0);
    ofRotateZ(rotateMultiply->getFloat() * rotate->getFloat());
    ofScale(holdScaleX, holdScaleY, 1.0);
    
    ofTranslate(-anchorXPixels, -anchorYPixels, 0.0);
    
    // draw
    ofEnableAlphaBlending();
    svg.draw();
    ofDisableAlphaBlending();
    
    ofPopMatrix();
}


void  TXDrawSVG::svgAssetSlotChanged(string slotNameArg) {
    loadSvg();
}

void TXDrawSVG::loadSvg() {
    ofPtr <TXAsset> asset;
    string fileName;
    int svgAssetID = getSvgAssetIDSlot("svgAsset").first;
    if (svgAssetID != 0) {
        asset = parentSystem->getAsset(TXASSETTYPE_SVG, svgAssetID);
        fileName = asset->getFileName();
        // clear before loading
        svg.clear(); //no longer needed?
        svg.load(fileName);
    };
}

