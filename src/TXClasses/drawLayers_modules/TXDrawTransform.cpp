/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXDrawTransform.h"

TXDrawTransform::TXDrawTransform() {
    setup();
}

void TXDrawTransform::setup(){
//    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    
    // create input paramaters
    initialiseParameters();
    
    holdModParamIntArgs.name = "drawLayersRule";
    holdModParamIntArgs.fixedValue = TXDRAWLAYERSRULE_ALLEXCEPT20;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXDRAWLAYERSRULE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXDRAWLAYERSRULE_TOTAL - 1;
	drawLayersRule = createModParameter(holdModParamIntArgs);
    parameters.add(drawLayersRule->parameters);
    
    holdModParamIntArgs.name = "transformOrder";
    holdModParamIntArgs.fixedValue = TXTRANSFORMORDER_SHIFTROTATESCALE;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXTRANSFORMORDER_TOTAL-1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXTRANSFORMORDER_TOTAL-1;
	transformOrder = createModParameter(holdModParamIntArgs);
    parameters.add(transformOrder->parameters);
    
    holdModParamFloatArgs.name = "shiftX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
	shiftX = createModParameter(holdModParamFloatArgs);
    parameters.add(shiftX->parameters);
    
    holdModParamFloatArgs.name = "shiftY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
	shiftY = createModParameter(holdModParamFloatArgs);
    parameters.add(shiftY->parameters);
    
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
    
    parameters.add(useScaleXForScaleY.set("useScaleXForScaleY", false));
}

void TXDrawTransform::draw(){
    if (!drawActive->getBool()) {
        return;
    };
    float holdAnchorX = anchorX->getFloat() * getMaxWidth();
    float holdAnchorY = anchorY->getFloat() * getMaxHeight();
    float holdScaleX, holdScaleY;
    
    holdScaleX = scaleX->getFloat();
    if (useScaleXForScaleY) {
        holdScaleY = holdScaleX;
    } else {
        holdScaleY = scaleY->getFloat();
    };
    ofPushMatrix();
    ofTranslate(holdAnchorX, holdAnchorY, 0.0);
    switch (transformOrder->getInt()) {
        case TXTRANSFORMORDER_SHIFTROTATESCALE:
            ofTranslate(shiftX->getFloat() * getMaxWidth(), shiftY->getFloat() * getMaxHeight(), 0.0);
            rotate();
            ofScale(holdScaleX, holdScaleY, 1.0);
            break;
        case TXTRANSFORMORDER_SHIFTSCALEROTATE:
            ofTranslate(shiftX->getFloat() * getMaxWidth(), shiftY->getFloat() * getMaxHeight(), 0.0);
            ofScale(holdScaleX, holdScaleY, 1.0);
            rotate();
            break;
        case TXTRANSFORMORDER_ROTATESCALESHIFT:
            rotate();
            ofScale(holdScaleX, holdScaleY, 1.0);
            ofTranslate(shiftX->getFloat() * getMaxWidth(), shiftY->getFloat() * getMaxHeight(), 0.0);
            break;
        case TXTRANSFORMORDER_ROTATESHIFTSCALE:
            rotate();
            ofTranslate(shiftX->getFloat() * getMaxWidth(), shiftY->getFloat() * getMaxHeight(), 0.0);
            ofScale(holdScaleX, holdScaleY, 1.0);
            break;
        case TXTRANSFORMORDER_SCALESHIFTROTATE:
            ofScale(holdScaleX, holdScaleY, 1.0);
            ofTranslate(shiftX->getFloat() * getMaxWidth(), shiftY->getFloat() * getMaxHeight(), 0.0);
            rotate();
            break;
        case TXTRANSFORMORDER_SCALEROTATESHIFT:
            ofScale(holdScaleX, holdScaleY, 1.0);
            rotate();
            ofTranslate(shiftX->getFloat() * getMaxWidth(), shiftY->getFloat() * getMaxHeight(), 0.0);
            break;
        default:
            ofTranslate(shiftX->getFloat() * getMaxWidth(), shiftY->getFloat() * getMaxHeight(), 0.0);
            rotate();
            ofScale(holdScaleX, holdScaleY, 1.0);
            break;
    }
    ofTranslate(-holdAnchorX, -holdAnchorY, 0.0);
    
    // draw layers
    TXDrawLayersBase::draw((TXDRAWLAYERSRULE)drawLayersRule->getInt());
    
    ofPopMatrix();
}
    
void TXDrawTransform::rotate() {
    float holdRotateMultiply = rotateMultiply->getFloat();
    ofRotateX(holdRotateMultiply * rotateX->getFloat());
    ofRotateY(holdRotateMultiply * rotateY->getFloat());
    ofRotateZ(holdRotateMultiply * rotateZ->getFloat());
}
