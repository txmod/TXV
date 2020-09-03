/*
 *  Copyright 2014 Paul Miller. All rights reserved.
 */

#include "TXDrawText3D.h"
#include "TXSystem.h"
#include "TXFunctions.h"

TXDrawText3D::TXDrawText3D() {
    setup();
}

void TXDrawText3D::setup(){
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
    
    parameters.add(textString.set("textString", " "));
    
    holdModParamIntArgs.name = "fontsize";
    holdModParamIntArgs.fixedValue = 24;
    holdModParamIntArgs.hardMin = 1;
    holdModParamIntArgs.hardMax = 1000;
    holdModParamIntArgs.softMin = 1;
    holdModParamIntArgs.softMax = 200;
    fontsize = createModParameter(holdModParamIntArgs);
    parameters.add(fontsize->parameters);
    
    parameters.add(scaleFontToWidth_1024.set("scaleFontToWidth_1024", true));

    holdModParamIntArgs.name = "depth";
    holdModParamIntArgs.fixedValue = 24;
    holdModParamIntArgs.hardMin = 1;
    holdModParamIntArgs.hardMax = 1000;
    holdModParamIntArgs.softMin = 1;
    holdModParamIntArgs.softMax = 1000;
    depth = createModParameter(holdModParamIntArgs);
    parameters.add(depth->parameters);
    
    holdModParamIntArgs.name = "depthResolution";
    holdModParamIntArgs.fixedValue = 1;
    holdModParamIntArgs.hardMin = 1;
    holdModParamIntArgs.hardMax = 1000;
    holdModParamIntArgs.softMin = 1;
    holdModParamIntArgs.softMax = 1000;
    depthResolution = createModParameter(holdModParamIntArgs);
    parameters.add(depthResolution->parameters);
    
    holdModParamFloatArgs.name = "fontSimplify";
    holdModParamFloatArgs.fixedValue = 0.3;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    fontSimplify = createModParameter(holdModParamFloatArgs);
    parameters.add(fontSimplify->parameters);
    
    holdModParamFloatArgs.name = "spaceSize";
    holdModParamFloatArgs.fixedValue = 5.0;
    holdModParamFloatArgs.hardMin = 0.01;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 0.01;
    holdModParamFloatArgs.softMax = 50.0;
    spaceSize = createModParameter(holdModParamFloatArgs);
    parameters.add(spaceSize->parameters);
    
    holdModParamFloatArgs.name = "letterSpacing";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.01;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.01;
    holdModParamFloatArgs.softMax = 10.0;
    letterSpacing = createModParameter(holdModParamFloatArgs);
    parameters.add(letterSpacing->parameters);
    
    holdModParamBoolArgs.name = "drawLetterFrontSolid";
    holdModParamBoolArgs.fixedValue = true;
    drawLetterFrontSolid = createModParameter(holdModParamBoolArgs);
    parameters.add(drawLetterFrontSolid->parameters);
    
    holdModParamBoolArgs.name = "drawLetterFrontWireframe";
    holdModParamBoolArgs.fixedValue = false;
    drawLetterFrontWireframe = createModParameter(holdModParamBoolArgs);
    parameters.add(drawLetterFrontWireframe->parameters);
    
    holdModParamBoolArgs.name = "drawLetterBackSolid";
    holdModParamBoolArgs.fixedValue = true;
    drawLetterBackSolid = createModParameter(holdModParamBoolArgs);
    parameters.add(drawLetterBackSolid->parameters);
    
    holdModParamBoolArgs.name = "drawLetterBackWireframe";
    holdModParamBoolArgs.fixedValue = false;
    drawLetterBackWireframe = createModParameter(holdModParamBoolArgs);
    parameters.add(drawLetterBackWireframe->parameters);
    
    holdModParamBoolArgs.name = "drawLetterSidesSolid";
    holdModParamBoolArgs.fixedValue = true;
    drawLetterSidesSolid = createModParameter(holdModParamBoolArgs);
    parameters.add(drawLetterSidesSolid->parameters);
    
    holdModParamBoolArgs.name = "drawLetterSidesWireframe";
    holdModParamBoolArgs.fixedValue = false;
    drawLetterSidesWireframe = createModParameter(holdModParamBoolArgs);
    parameters.add(drawLetterSidesWireframe->parameters);
    
    parameters.add(useColorFrontForColorBack.set("useColorFrontForColorBack", false));
    
    parameters.add(useColorFrontForColorSides.set("useColorFrontForColorSides", false));
    
    holdModParamFloatArgs.name = "colorFrontHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    colorFrontHue = createModParameter(holdModParamFloatArgs);
    parameters.add(colorFrontHue->parameters);
    
    holdModParamFloatArgs.name = "colorFrontHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    colorFrontHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(colorFrontHueRotate->parameters);
    
    holdModParamFloatArgs.name = "colorFrontSaturation";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    colorFrontSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(colorFrontSaturation->parameters);
    
    holdModParamFloatArgs.name = "colorFrontBrightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    colorFrontBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(colorFrontBrightness->parameters);
    
    holdModParamBoolArgs.name = "colorFrontHSBAsRGB";
    holdModParamBoolArgs.fixedValue = true;
    colorFrontHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(colorFrontHSBAsRGB->parameters);
    
    holdModParamFloatArgs.name = "colorBackHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    colorBackHue = createModParameter(holdModParamFloatArgs);
    parameters.add(colorBackHue->parameters);
    
    holdModParamFloatArgs.name = "colorBackHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    colorBackHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(colorBackHueRotate->parameters);
    
    holdModParamFloatArgs.name = "colorBackSaturation";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    colorBackSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(colorBackSaturation->parameters);
    
    holdModParamFloatArgs.name = "colorBackBrightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    colorBackBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(colorBackBrightness->parameters);
    
    holdModParamBoolArgs.name = "colorBackHSBAsRGB";
    holdModParamBoolArgs.fixedValue = true;
    colorBackHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(colorBackHSBAsRGB->parameters);
    
    holdModParamFloatArgs.name = "colorSidesHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    colorSidesHue = createModParameter(holdModParamFloatArgs);
    parameters.add(colorSidesHue->parameters);
    
    holdModParamFloatArgs.name = "colorSidesHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    colorSidesHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(colorSidesHueRotate->parameters);
    
    holdModParamFloatArgs.name = "colorSidesSaturation";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    colorSidesSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(colorSidesSaturation->parameters);
    
    holdModParamFloatArgs.name = "colorSidesBrightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    colorSidesBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(colorSidesBrightness->parameters);
    
    holdModParamBoolArgs.name = "colorSidesHSBAsRGB";
    holdModParamBoolArgs.fixedValue = true;
    colorSidesHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(colorSidesHSBAsRGB->parameters);
    
    holdModParamFloatArgs.name = "positionX";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    positionX = createModParameter(holdModParamFloatArgs);
    parameters.add(positionX->parameters);
    
    holdModParamFloatArgs.name = "positionY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    positionY = createModParameter(holdModParamFloatArgs);
    parameters.add(positionY->parameters);
    
    holdModParamFloatArgs.name = "positionZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 0.0;
    positionZ = createModParameter(holdModParamFloatArgs);
    parameters.add(positionZ->parameters);
    
    holdModParamFloatArgs.name = "rotateX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
    rotateX = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateX->parameters);
    
    holdModParamFloatArgs.name = "rotateY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
    rotateY = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateY->parameters);
    
    holdModParamFloatArgs.name = "rotateZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
    rotateZ = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateZ->parameters);
    
    holdModParamFloatArgs.name = "rotateMultiply";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
    rotateMultiply = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateMultiply->parameters);
    
    holdModParamFloatArgs.name = "anchorX";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    anchorX = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorX->parameters);
    
    holdModParamFloatArgs.name = "anchorY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    anchorY = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorY->parameters);
    
    holdModParamFloatArgs.name = "anchorZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    anchorZ = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorZ->parameters);
    
    holdModParamFloatArgs.name = "scaleX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 3.0;
    scaleX = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleX->parameters);
    
    holdModParamFloatArgs.name = "scaleY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 3.0;
    scaleY = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleY->parameters);
    
    holdModParamFloatArgs.name = "scaleZ";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 3.0;
    scaleZ = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleZ->parameters);
    
    parameters.add(useScaleXForScaleY.set("useScaleXForScaleY", false));
    parameters.add(useScaleXForScaleZ.set("useScaleXForScaleZ", false));
    
    // asset slots
    createFontAssetSlot("fontAsset");

    // add listener to relevent parameters:
    textString.addListener(this, &TXDrawText3D::textStringChanged);
    
    // init
    fontNeedsLoading = false;
    textNeedsLoading = false;
    textLoaded = false;

    old_fontsize = -1;
    old_depth = -1;
    old_depthResolution = -1;
    old_fontSimplify = -1;
    old_spaceSize = -1;
    old_letterSpacing = -1;
    old_scaleFontToWidth_1024 = false;
}

void TXDrawText3D::draw(){
    // check before drawing
    if (!drawActive->getBool()) {
        return;
    };
    
    // reload text/font if needed
    int hold_fontsize = fontsize->getInt();
    int hold_depth = depth->getInt();
    int hold_depthResolution = depthResolution->getInt();
    float hold_fontSimplify = fontSimplify->getFloat();
    float hold_spaceSize = spaceSize->getFloat();
    float hold_letterSpacing = letterSpacing->getFloat();
    float fontScale;
    int   holdMaxWidth = getMaxWidth();
    int   holdMaxHeight = getMaxHeight();
    int   holdMaxDepth = getMaxDepth();

    if (scaleFontToWidth_1024 == true) {
        fontScale = holdMaxWidth / 1024.0f;
    } else {
        fontScale = 1.0f;
    };

    if (fontNeedsLoading)
    {
        loadText(hold_fontsize * fontScale, hold_depth, hold_depthResolution, hold_fontSimplify, hold_letterSpacing, hold_spaceSize);
    } else {
        if ((old_fontsize != hold_fontsize)  || (old_fontSimplify != hold_fontSimplify)  || (old_spaceSize != hold_spaceSize)
            || (old_letterSpacing != hold_letterSpacing)|| (old_scaleFontToWidth_1024 != scaleFontToWidth_1024))
        {
            text3D.adjustFont(hold_fontsize * fontScale, hold_fontSimplify, hold_letterSpacing, hold_spaceSize);
        };
        if ((old_depth != hold_depth)  || (old_depthResolution != hold_depthResolution))
        {
            text3D.adjustDepth(hold_depth, hold_depthResolution);
        };
        if (textNeedsLoading) {
            text3D.setText(textString);
        };
    };
    text3D.updateMeshes();
    
    // reset
    fontNeedsLoading = false;
    textNeedsLoading = false;
    old_fontsize = hold_fontsize;
    old_depth = hold_depth;
    old_depthResolution = hold_depthResolution;
    old_fontSimplify = hold_fontSimplify;
    old_spaceSize = hold_spaceSize;
    old_letterSpacing = hold_letterSpacing;
    old_scaleFontToWidth_1024 = scaleFontToWidth_1024;
    
    float holdWidth = text3D.getWidth();
    float holdHeight = text3D.getHeight();
    // check whether to draw
    if ((!(holdWidth > 0.0)) || (!(holdHeight > 0.0) || (!text3D.getFontLoaded()))) {
        return;
    };
    float anchorXPixels = anchorX->getFloat() * holdWidth;
    float anchorYPixels = anchorY->getFloat() * holdHeight;
    float anchorZPixels = anchorZ->getFloat() * holdHeight;
    float holdDrawPosX = positionX->getFloat() * holdMaxWidth;
    float holdDrawPosY = positionY->getFloat() * holdMaxHeight;
    float holdDrawPosZ = positionZ->getFloat() * holdMaxDepth;
    
    float holdScaleX, holdScaleY, holdScaleZ;
    holdScaleX = scaleX->getFloat();
    if (useScaleXForScaleY) {
        holdScaleY = holdScaleX;
    } else {
        holdScaleY = scaleY->getFloat();
    };
    if (useScaleXForScaleZ) {
        holdScaleZ = holdScaleX;
    } else {
        holdScaleZ = scaleZ->getFloat();
    };
    
    bool hold_drawLetterFrontSolid = drawLetterFrontSolid->getBool();
    bool hold_drawLetterFrontWireframe = drawLetterFrontWireframe->getBool();
    bool hold_drawLetterBackSolid = drawLetterBackSolid->getBool();
    bool hold_drawLetterBackWireframe = drawLetterBackWireframe->getBool();
    bool hold_drawLetterSidesSolid = drawLetterSidesSolid->getBool();
    bool hold_drawLetterSidesWireframe = drawLetterSidesWireframe->getBool();
    ofColor frontColor, backColor, sidesColor;
    if (hold_drawLetterFrontSolid || hold_drawLetterFrontWireframe || useColorFrontForColorBack || useColorFrontForColorSides) {
        frontColor = TXFunctions::txGetColor(colorFrontHue->getFloat(),  colorFrontSaturation->getFloat(),  colorFrontBrightness->getFloat(),  1.0, colorFrontHueRotate->getFloat(), colorFrontHSBAsRGB->getBool());
    };
    if (hold_drawLetterBackSolid || hold_drawLetterBackWireframe) {
        if (useColorFrontForColorBack) {
            backColor = frontColor;
        } else {
            backColor = TXFunctions::txGetColor(colorBackHue->getFloat(),  colorBackSaturation->getFloat(),  colorBackBrightness->getFloat(),  1.0, colorBackHueRotate->getFloat(), colorBackHSBAsRGB->getBool());
        };
    };
    if (hold_drawLetterSidesSolid || hold_drawLetterSidesWireframe) {
        if (useColorFrontForColorSides) {
            sidesColor = frontColor;
        } else {
            sidesColor = TXFunctions::txGetColor(colorSidesHue->getFloat(),  colorSidesSaturation->getFloat(),  colorSidesBrightness->getFloat(),  1.0, colorSidesHueRotate->getFloat(), colorSidesHSBAsRGB->getBool());
        };
    };

    // translate, rotate, scale
    ofPushMatrix();
    ofTranslate(holdDrawPosX, holdDrawPosY, holdDrawPosZ);
    
    float hold_rotateMultiply = rotateMultiply->getFloat();
    TXFunctions::rotate(hold_rotateMultiply * rotateX->getFloat(), hold_rotateMultiply * rotateY->getFloat(), hold_rotateMultiply * rotateZ->getFloat());
    
    ofScale(holdScaleX, holdScaleY, holdScaleZ);
    
    ofTranslate(-anchorXPixels, -anchorYPixels, anchorZPixels);
    
    // draw
    ofEnableAlphaBlending();
    
    for(int i=0; i<text3D.letters.size(); i++)
    {
        ofSetColor(frontColor);
        if (hold_drawLetterFrontSolid) {
            text3D.letters[i].front.draw();
        }
        if (hold_drawLetterFrontWireframe) {
            text3D.letters[i].front.drawWireframe();
        }
        ofSetColor(backColor);
        if (hold_drawLetterBackSolid) {
            text3D.letters[i].back.draw();
        }
        if (hold_drawLetterBackWireframe) {
            text3D.letters[i].back.drawWireframe();
        }
        ofSetColor(sidesColor);
        if (hold_drawLetterSidesSolid) {
            text3D.letters[i].side.draw();
        }
        if (hold_drawLetterSidesWireframe) {
            text3D.letters[i].side.drawWireframe();
        }
    }
    
    ofDisableAlphaBlending();
    
    ofPopMatrix();
}

void TXDrawText3D::windowResized(int w, int h) {
    fontNeedsLoading = true;
}

void  TXDrawText3D::fontAssetSlotChanged(string slotNameArg) {
    fontNeedsLoading = true;
}

void  TXDrawText3D::textStringChanged(string & stringArg) {
    textNeedsLoading = true;
}

void TXDrawText3D::loadText(int fontsize, int depth, int depthResolution, float fontSimplify, float letterSpacing, float spaceSize) {
    ofPtr <TXAsset> asset;
    string fileName;
    int fontAssetID = getFontAssetIDSlot("fontAsset").first;
    textLoaded = false;
    if (fontAssetID != 0) {
        asset = parentSystem->getAsset(TXASSETTYPE_FONT, fontAssetID);
        fileName = asset->getFileName();

        text3D.init(fileName, fontsize, depth, depthResolution, textString, fontSimplify, letterSpacing, spaceSize);

        textLoaded = text3D.getFontLoaded();
    };
}

