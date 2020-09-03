/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#include "TXDrawTransform3D.h"

TXDrawTransform3D::TXDrawTransform3D() {
    setup();
}

void TXDrawTransform3D::setup(){
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
    
    holdModParamFloatArgs.name = "shiftZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
	shiftZ = createModParameter(holdModParamFloatArgs);
    parameters.add(shiftZ->parameters);
    
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
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	anchorX = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorX->parameters);
    
    holdModParamFloatArgs.name = "anchorY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	anchorY = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorY->parameters);
    
    holdModParamFloatArgs.name = "anchorZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 0.0;
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
}

void TXDrawTransform3D::draw(){
    if (!drawActive->getBool()) {
        return;
    };
    float holdAnchorX = anchorX->getFloat() * getMaxWidth();
    float holdAnchorY = anchorY->getFloat() * getMaxHeight();
    float holdAnchorZ = anchorZ->getFloat() * getMaxDepth();
    float holdRotateMultiply = rotateMultiply->getFloat();
    float holdRotateX = holdRotateMultiply * rotateX->getFloat();
    float holdRotateY = holdRotateMultiply * rotateY->getFloat();
    float holdRotateZ = holdRotateMultiply * rotateZ->getFloat();
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
    ofPushMatrix();
    ofTranslate(holdAnchorX, holdAnchorY, holdAnchorZ);
    switch (transformOrder->getInt()) {
        case TXTRANSFORMORDER_SHIFTROTATESCALE:
            ofTranslate(shiftX->getFloat() * getMaxWidth(), shiftY->getFloat() * getMaxHeight(), shiftZ->getFloat() * getMaxDepth());
            rotate(holdRotateX, holdRotateY, holdRotateZ);
            ofScale(holdScaleX, holdScaleY, holdScaleZ);
            break;
        case TXTRANSFORMORDER_SHIFTSCALEROTATE:
            ofTranslate(shiftX->getFloat() * getMaxWidth(), shiftY->getFloat() * getMaxHeight(), shiftZ->getFloat() * getMaxDepth());
            ofScale(holdScaleX, holdScaleY, holdScaleZ);
            rotate(holdRotateX, holdRotateY, holdRotateZ);
            break;
        case TXTRANSFORMORDER_ROTATESCALESHIFT:
            rotate(holdRotateX, holdRotateY, holdRotateZ);
            ofScale(holdScaleX, holdScaleY, holdScaleZ);
            ofTranslate(shiftX->getFloat() * getMaxWidth(), shiftY->getFloat() * getMaxHeight(), shiftZ->getFloat() * getMaxDepth());
            break;
        case TXTRANSFORMORDER_ROTATESHIFTSCALE:
            rotate(holdRotateX, holdRotateY, holdRotateZ);
            ofTranslate(shiftX->getFloat() * getMaxWidth(), shiftY->getFloat() * getMaxHeight(), shiftZ->getFloat() * getMaxDepth());
            ofScale(holdScaleX, holdScaleY, holdScaleZ);
            break;
        case TXTRANSFORMORDER_SCALESHIFTROTATE:
            ofScale(holdScaleX, holdScaleY, holdScaleZ);
            ofTranslate(shiftX->getFloat() * getMaxWidth(), shiftY->getFloat() * getMaxHeight(), shiftZ->getFloat() * getMaxDepth());
            rotate(holdRotateX, holdRotateY, holdRotateZ);
            break;
        case TXTRANSFORMORDER_SCALEROTATESHIFT:
            ofScale(holdScaleX, holdScaleY, holdScaleZ);
            rotate(holdRotateX, holdRotateY, holdRotateZ);
            ofTranslate(shiftX->getFloat() * getMaxWidth(), shiftY->getFloat() * getMaxHeight(), shiftZ->getFloat() * getMaxDepth());
            break;
        default:
            ofTranslate(shiftX->getFloat() * getMaxWidth(), shiftY->getFloat() * getMaxHeight(), shiftZ->getFloat() * getMaxDepth());
            rotate(holdRotateX, holdRotateY, holdRotateZ);
            ofScale(holdScaleX, holdScaleY, holdScaleZ);
            break;
    }
    ofTranslate(-holdAnchorX, -holdAnchorY, -holdAnchorZ);

    // draw layers
    TXDrawLayersBase::draw((TXDRAWLAYERSRULE)drawLayersRule->getInt());
    
    ofPopMatrix();
}
    
void TXDrawTransform3D::rotate(float rotX, float rotY, float rotZ) {
    ofVec3f Znormal(0, 0, 1);
    ofVec3f Xnormal(1, 0, 0);
    //ofVec3f Ynormal(1, 0, 1);
    ofVec3f Ynormal(0, 1, 0);
    
	//ofQuaternion constructor: angle, ofVec3f axis
    ofQuaternion qr (rotZ, Znormal); // quat roll.
    ofQuaternion qp (rotX, Xnormal); // quat pitch.
    ofQuaternion qh (rotY, Ynormal); // quat heading or yaw.
    ofQuaternion qt; // quat total.
    // The order IS IMPORTANT. Apply roll first, then pitch, then heading.
    qt = qr * qp * qh;
    
    ofVec3f qaxis;
    float qangle;
    qt.getRotate(qangle, qaxis);
    ofRotate(qangle, qaxis.x, qaxis.y, qaxis.z);
}
