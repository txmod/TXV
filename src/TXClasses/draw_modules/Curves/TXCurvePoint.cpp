/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXCurvePoint.h"
#include "TXFunctions.h"

// properties

// constructor
TXCurvePoint::TXCurvePoint () {
    setup ();
};

// methods
void TXCurvePoint::setup (int pointTypeArg, string nameArg, int maxDelayFramesArg) {
//    TXModParameterBoolArgs holdModParamBoolArgs;
//    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;

    maxDelayFrames = maxDelayFramesArg;
    // set defaults
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;

    // create input paramaters
    clearParameters();
    
    parameters.setName(nameArg);
    
    pointType = pointTypeArg;

    switch (pointType) {

            // 2D -----------------
        case TXPOINTTYPE_2DBEZIER:
            is3DPoint = false;
            isRangePoint = false;
            isRangeOptionPoint = false;
            isDelayPoint = false;
            hasDrawPoint = true;
            hasControl1Point = true;
            hasControl2Point = true;
            break;
        case TXPOINTTYPE_2DBEZIERDELAY:
            is3DPoint = false;
            isRangePoint = false;
            isRangeOptionPoint = false;
            isDelayPoint = true;
            hasDrawPoint = true;
            hasControl1Point = true;
            hasControl2Point = true;
            break;
        case TXPOINTTYPE_2DBEZIERRANGE:
            is3DPoint = false;
            isRangePoint = true;
            isRangeOptionPoint = false;
            isDelayPoint = false;
            hasDrawPoint = true;
            hasControl1Point = true;
            hasControl2Point = true;
            break;
        case TXPOINTTYPE_2DBEZIERRANGEOPTION:
            is3DPoint = false;
            isRangePoint = true;
            isRangeOptionPoint = true;
            isDelayPoint = false;
            hasDrawPoint = true;
            hasControl1Point = true;
            hasControl2Point = true;
            break;
        case TXPOINTTYPE_2DCONTROLPOINT:
            is3DPoint = false;
            isRangePoint = false;
            isRangeOptionPoint = false;
            isDelayPoint = false;
            hasDrawPoint = false;
            hasControl1Point = true;
            hasControl2Point = false;
            break;
        case TXPOINTTYPE_2DCONTROLPOINTDELAY:
            is3DPoint = false;
            isRangePoint = false;
            isRangeOptionPoint = false;
            isDelayPoint = true;
            hasDrawPoint = false;
            hasControl1Point = true;
            hasControl2Point = false;
            break;
        case TXPOINTTYPE_2DCONTROLPOINTRANGE:
            is3DPoint = false;
            isRangePoint = true;
            isRangeOptionPoint = false;
            isDelayPoint = false;
            hasDrawPoint = false;
            hasControl1Point = true;
            hasControl2Point = false;
            break;
        case TXPOINTTYPE_2DCONTROLPOINTRANGEOPTION:
            is3DPoint = false;
            isRangePoint = true;
            isRangeOptionPoint = true;
            isDelayPoint = false;
            hasDrawPoint = false;
            hasControl1Point = true;
            hasControl2Point = false;
            break;
        case TXPOINTTYPE_2DPOINT:
            is3DPoint = false;
            isRangePoint = false;
            isRangeOptionPoint = false;
            isDelayPoint = false;
            hasDrawPoint = true;
            hasControl1Point = false;
            hasControl2Point = false;
            break;
        case TXPOINTTYPE_2DPOINTDELAY:
            is3DPoint = false;
            isRangePoint = false;
            isRangeOptionPoint = false;
            isDelayPoint = true;
            hasDrawPoint = true;
            hasControl1Point = false;
            hasControl2Point = false;
            break;
        case TXPOINTTYPE_2DPOINTRANGE:
            is3DPoint = false;
            isRangePoint = true;
            isRangeOptionPoint = false;
            isDelayPoint = false;
            hasDrawPoint = true;
            hasControl1Point = false;
            hasControl2Point = false;
            break;
        case TXPOINTTYPE_2DPOINTRANGEOPTION:
            is3DPoint = false;
            isRangePoint = true;
            isRangeOptionPoint = true;
            isDelayPoint = false;
            hasDrawPoint = true;
            hasControl1Point = false;
            hasControl2Point = false;
            break;
            
            // 3D -----------------
            
        case TXPOINTTYPE_3DBEZIER:
            is3DPoint = true;
            isRangePoint = false;
            isRangeOptionPoint = false;
            isDelayPoint = false;
            hasDrawPoint = true;
            hasControl1Point = true;
            hasControl2Point = true;
            break;
        case TXPOINTTYPE_3DBEZIERDELAY:
            is3DPoint = true;
            isRangePoint = false;
            isRangeOptionPoint = false;
            isDelayPoint = true;
            hasDrawPoint = true;
            hasControl1Point = true;
            hasControl2Point = true;
            break;
        case TXPOINTTYPE_3DBEZIERRANGE:
            is3DPoint = true;
            isRangePoint = true;
            isRangeOptionPoint = false;
            isDelayPoint = false;
            hasDrawPoint = true;
            hasControl1Point = true;
            hasControl2Point = true;
            break;
        case TXPOINTTYPE_3DBEZIERRANGEOPTION:
            is3DPoint = true;
            isRangePoint = true;
            isRangeOptionPoint = true;
            isDelayPoint = false;
            hasDrawPoint = true;
            hasControl1Point = true;
            hasControl2Point = true;
            break;
        case TXPOINTTYPE_3DCONTROLPOINT:
            is3DPoint = true;
            isRangePoint = false;
            isRangeOptionPoint = false;
            isDelayPoint = false;
            hasDrawPoint = false;
            hasControl1Point = true;
            hasControl2Point = false;
            break;
        case TXPOINTTYPE_3DCONTROLPOINTDELAY:
            is3DPoint = true;
            isRangePoint = false;
            isRangeOptionPoint = false;
            isDelayPoint = true;
            hasDrawPoint = false;
            hasControl1Point = true;
            hasControl2Point = false;
            break;
        case TXPOINTTYPE_3DCONTROLPOINTRANGE:
            is3DPoint = true;
            isRangePoint = true;
            isRangeOptionPoint = false;
            isDelayPoint = false;
            hasDrawPoint = false;
            hasControl1Point = true;
            hasControl2Point = false;
            break;
        case TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION:
            is3DPoint = true;
            isRangePoint = true;
            isRangeOptionPoint = true;
            isDelayPoint = false;
            hasDrawPoint = false;
            hasControl1Point = true;
            hasControl2Point = false;
            break;
        case TXPOINTTYPE_3DPOINT:
            is3DPoint = true;
            isRangePoint = false;
            isRangeOptionPoint = false;
            isDelayPoint = false;
            hasDrawPoint = true;
            hasControl1Point = false;
            hasControl2Point = false;
            break;
        case TXPOINTTYPE_3DPOINTDELAY:
            is3DPoint = true;
            isRangePoint = false;
            isRangeOptionPoint = false;
            isDelayPoint = true;
            hasDrawPoint = true;
            hasControl1Point = false;
            hasControl2Point = false;
            break;
        case TXPOINTTYPE_3DPOINTRANGE:
            is3DPoint = true;
            isRangePoint = true;
            isRangeOptionPoint = false;
            isDelayPoint = false;
            hasDrawPoint = true;
            hasControl1Point = false;
            hasControl2Point = false;
            break;
        case TXPOINTTYPE_3DPOINTRANGEOPTION:
            is3DPoint = true;
            isRangePoint = true;
            isRangeOptionPoint = true;
            isDelayPoint = false;
            hasDrawPoint = true;
            hasControl1Point = false;
            hasControl2Point = false;
            break;
        default:
            // same as TXPOINTTYPE_2DPOINT
            is3DPoint = false;
            isRangePoint = false;
            isRangeOptionPoint = false;
            isDelayPoint = false;
            hasDrawPoint = true;
            hasControl1Point = false;
            hasControl2Point = false;
            break;
    };

    if (hasControl1Point) {
        holdModParamFloatArgs.name = nameArg + "_control1X";
        control1X = createModParameter(holdModParamFloatArgs);
        parameters.add(control1X->parameters);
        
        holdModParamFloatArgs.name = nameArg + "_control1Y";
        control1Y = createModParameter(holdModParamFloatArgs);
        parameters.add(control1Y->parameters);
        
        if (is3DPoint) {
            holdModParamFloatArgs.name = nameArg + "_control1Z";
            control1Z = createModParameter(holdModParamFloatArgs);
            parameters.add(control1Z->parameters);
        };
        
        if (isRangePoint) {
            holdModParamFloatArgs.name = nameArg + "_control1XEnd";
            control1XEnd = createModParameter(holdModParamFloatArgs);
            parameters.add(control1XEnd->parameters);
            
            holdModParamFloatArgs.name = nameArg + "_control1YEnd";
            control1YEnd = createModParameter(holdModParamFloatArgs);
            parameters.add(control1YEnd->parameters);
            
            if (is3DPoint) {
                holdModParamFloatArgs.name = nameArg + "_control1ZEnd";
                control1ZEnd = createModParameter(holdModParamFloatArgs);
                parameters.add(control1ZEnd->parameters);
            };
        };
        if (isRangeOptionPoint) {
            parameters.add(control1XEndIgnore.set(nameArg + "_control1XEndIgnore", false));
            parameters.add(control1YEndIgnore.set(nameArg + "_control1YEndIgnore", false));
            if (is3DPoint) {
                parameters.add(control1ZEndIgnore.set(nameArg + "_control1ZEndIgnore", false));
            };
        };
    };
    
    if (hasControl2Point) {
        holdModParamFloatArgs.name = nameArg + "_control2X";
        control2X = createModParameter(holdModParamFloatArgs);
        parameters.add(control2X->parameters);
        
        holdModParamFloatArgs.name = nameArg + "_control2Y";
        control2Y = createModParameter(holdModParamFloatArgs);
        parameters.add(control2Y->parameters);
        
        if (is3DPoint) {
            holdModParamFloatArgs.name = nameArg + "_control2Z";
            control2Z = createModParameter(holdModParamFloatArgs);
            parameters.add(control2Z->parameters);
            };
        if (isRangePoint) {
            holdModParamFloatArgs.name = nameArg + "_control2XEnd";
            control2XEnd = createModParameter(holdModParamFloatArgs);
            parameters.add(control2XEnd->parameters);
            
            holdModParamFloatArgs.name = nameArg + "_control2YEnd";
            control2YEnd = createModParameter(holdModParamFloatArgs);
            parameters.add(control2YEnd->parameters);
            
            if (is3DPoint) {
                holdModParamFloatArgs.name = nameArg + "_control2ZEnd";
                control2ZEnd = createModParameter(holdModParamFloatArgs);
                parameters.add(control2ZEnd->parameters);
            };
        };
        if (isRangeOptionPoint) {
            parameters.add(control2XEndIgnore.set(nameArg + "_control2XEndIgnore", false));
            parameters.add(control2YEndIgnore.set(nameArg + "_control2YEndIgnore", false));
            if (is3DPoint) {
                parameters.add(control2ZEndIgnore.set(nameArg + "_control2ZEndIgnore", false));
            };
        };
    };
    
    if (hasDrawPoint) {
        holdModParamFloatArgs.name = nameArg + "_drawX";
        drawX = createModParameter(holdModParamFloatArgs);
        parameters.add(drawX->parameters);
        
        holdModParamFloatArgs.name = nameArg + "_drawY";
        drawY = createModParameter(holdModParamFloatArgs);
        parameters.add(drawY->parameters);
        
        if (is3DPoint) {
            holdModParamFloatArgs.name = nameArg + "_drawZ";
            drawZ = createModParameter(holdModParamFloatArgs);
            parameters.add(drawZ->parameters);
        };
        
        if (isRangePoint) {
            holdModParamFloatArgs.name = nameArg + "_drawXEnd";
            drawXEnd = createModParameter(holdModParamFloatArgs);
            parameters.add(drawXEnd->parameters);

            holdModParamFloatArgs.name = nameArg + "_drawYEnd";
            drawYEnd = createModParameter(holdModParamFloatArgs);
            parameters.add(drawYEnd->parameters);
            
            if (is3DPoint) {
                holdModParamFloatArgs.name = nameArg + "_drawZEnd";
                drawZEnd = createModParameter(holdModParamFloatArgs);
                parameters.add(drawZEnd->parameters);
            };
        };
        if (isRangeOptionPoint) {
            parameters.add(drawXEndIgnore.set(nameArg + "_drawXEndIgnore", false));
            parameters.add(drawYEndIgnore.set(nameArg + "_drawYEndIgnore", false));
            if (is3DPoint) {
                parameters.add(drawZEndIgnore.set(nameArg + "_drawZEndIgnore", false));
            };
        };
    };
    
    // Add delays if needed
    if (isDelayPoint) {
        if (hasDrawPoint) {
            drawXDelay.assign(maxDelayFrames, 0.0);
            drawYDelay.assign(maxDelayFrames, 0.0);
            if (is3DPoint) {
                drawZDelay.assign(maxDelayFrames, 0.0);
            };
        };
        if (hasControl1Point) {
            control1XDelay.assign(maxDelayFrames, 0.0);
            control1YDelay.assign(maxDelayFrames, 0.0);
            if (is3DPoint) {
                control1ZDelay.assign(maxDelayFrames, 0.0);
            };
        };
        if (hasControl2Point) {
            control2XDelay.assign(maxDelayFrames, 0.0);
            control2YDelay.assign(maxDelayFrames, 0.0);
            if (is3DPoint) {
                control2ZDelay.assign(maxDelayFrames, 0.0);
            };
        };
    }
};

void TXCurvePoint::update() {
    // update delays if needed
    if (isDelayPoint) {
        currentDelayFrame = (currentDelayFrame + 1) % maxDelayFrames;
        if (hasDrawPoint) {
            drawXDelay[currentDelayFrame] = drawX->getFloat();
            drawYDelay[currentDelayFrame] = drawY->getFloat();
            if (is3DPoint) {
                drawZDelay[currentDelayFrame] = drawZ->getFloat();
            };
        };
        if (hasControl1Point) {
            control1XDelay[currentDelayFrame] = control1X->getFloat();
            control1YDelay[currentDelayFrame] = control1Y->getFloat();
            if (is3DPoint) {
                control1ZDelay[currentDelayFrame] = control1Z->getFloat();
            };
        };
        if (hasControl2Point) {
            control2XDelay[currentDelayFrame] = control2X->getFloat();
            control2YDelay[currentDelayFrame] = control2Y->getFloat();
            if (is3DPoint) {
                control2ZDelay[currentDelayFrame] = control2Z->getFloat();
            };
        };
    }
};

float TXCurvePoint::getDelayedVal(const vector<float> & delayVector, const float & delayFrames) {
    int index1, index2;
    float proportion, outval;
    index1 = ((int) delayFrames) % maxDelayFrames;
    index2 = (index1 + 1) % maxDelayFrames;
    proportion = delayFrames - index1;
    outval = ofLerp(delayVector[index1], delayVector[index2], proportion);
    return outval;
}

//// parameter interpolation NO LONGER NEEDED
//
//float TXCurvePoint::getInterp(ofPtr<TXModParamFloat> param1, ofPtr<TXModParamFloat> param2, float & proportion) {
//    float val1, val2, outVal;
//    if (proportion == 0.0) {
//        outVal = param1->TXModParameter::getFloat();
//    } else if (proportion == 1.0) {
//        outVal = param2->TXModParameter::getFloat();
//    } else {
//        val1 = param1->TXModParameter::getFloat();
//        val2 = param2->TXModParameter::getFloat();
//        if (val1 == val2) {
//            outVal =  val1;
//        } else {
//            outVal =  ofLerp(val1, val2, proportion);
//        }
//    };
//    return outVal;
//};

//// interpolation with Curves NO LONGER NEEDED
//
//float TXCurvePoint::getInterp(float val1, float val2, float & proportion, TXParameterFloat256 & curve1, TXParameterFloat256 & curve2, float & phase, float & curveMorph) {
//    float floatVal, floatVal2, outVal;
//    float warpedProp = TXFunctions::getInterpPhaseCurves (curve1, curve2, proportion, phase, curveMorph);
//    if ((warpedProp == 0.0) || (val1 == val2)) {
//        outVal = val1;
//    } else if (warpedProp == 1.0) {
//        outVal = val2;
//    } else {
//        outVal =  ofLerp(val1, val2, warpedProp);
//    };
//    return outVal;
//};

float TXCurvePoint::getInterpDrawX(float & proportion) {
    if (isRangeOptionPoint && drawXEndIgnore) {
        return drawX->getFloat();
    } else {
        return TXFunctions::getInterp(drawX->getFloat(), drawXEnd->getFloat(), proportion);
    };
};

float TXCurvePoint::getInterpDrawY(float & proportion) {
    if (isRangeOptionPoint && drawYEndIgnore) {
        return drawY->getFloat();
    } else {
        return TXFunctions::getInterp(drawY->getFloat(), drawYEnd->getFloat(), proportion);
    };
};

float TXCurvePoint::getInterpDrawZ(float & proportion) {
    if (isRangeOptionPoint && drawZEndIgnore) {
        return drawZ->getFloat();
    } else {
        return TXFunctions::getInterp(drawZ->getFloat(), drawZEnd->getFloat(), proportion);
    };
};

float TXCurvePoint::getInterpControl1X(float & proportion) {
    if (isRangeOptionPoint && control1XEndIgnore) {
        return control1X->getFloat();
    } else {
        return TXFunctions::getInterp(control1X->getFloat(), control1XEnd->getFloat(), proportion);
    };
};

float TXCurvePoint::getInterpControl1Y(float & proportion) {
    if (isRangeOptionPoint && control1YEndIgnore) {
        return control1Y->getFloat();
    } else {
        return TXFunctions::getInterp(control1Y->getFloat(), control1YEnd->getFloat(), proportion);
    };
};

float TXCurvePoint::getInterpControl1Z(float & proportion) {
    if (isRangeOptionPoint && control1ZEndIgnore) {
        return control1Z->getFloat();
    } else {
        return TXFunctions::getInterp(control1Z->getFloat(), control1ZEnd->getFloat(), proportion);
    };
};

float TXCurvePoint::getInterpControl2X(float & proportion) {
    if (isRangeOptionPoint && control2XEndIgnore) {
        return control2X->getFloat();
    } else {
        return TXFunctions::getInterp(control2X->getFloat(), control2XEnd->getFloat(), proportion);
    };
};

float TXCurvePoint::getInterpControl2Y(float & proportion) {
    if (isRangeOptionPoint && control2YEndIgnore) {
        return control2Y->getFloat();
    } else {
        return TXFunctions::getInterp(control2Y->getFloat(), control2YEnd->getFloat(), proportion);
    };
};

float TXCurvePoint::getInterpControl2Z(float & proportion) {
    if (isRangeOptionPoint && control2ZEndIgnore) {
        return control2Z->getFloat();
    } else {
        return TXFunctions::getInterp(control2Z->getFloat(), control2ZEnd->getFloat(), proportion);
    };
};

//////////////////// Delayed

float TXCurvePoint::getDelayDrawX(float & proportion, const int & delayFrames) {
    int holdDelayFrames;
    float holdFrameNo;
        holdDelayFrames = min(delayFrames, maxDelayFrames);
        if (proportion == 1.0f) {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - holdDelayFrames, (float) maxDelayFrames);
            return getDelayedVal(drawXDelay, holdFrameNo);
        } else {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - (proportion * holdDelayFrames), (float) maxDelayFrames);
            return getDelayedVal(drawXDelay, holdFrameNo);
        };
};

float TXCurvePoint::getDelayDrawY(float & proportion, const int & delayFrames) {
    int holdDelayFrames;
    float holdFrameNo;
        holdDelayFrames = min(delayFrames, maxDelayFrames);
        if (proportion == 1.0f) {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - holdDelayFrames, (float) maxDelayFrames);
            return getDelayedVal(drawYDelay, holdFrameNo);;
        } else {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - (proportion * holdDelayFrames), (float) maxDelayFrames);
            return getDelayedVal(drawYDelay, holdFrameNo);
        };
};

float TXCurvePoint::getDelayDrawZ(float & proportion, const int & delayFrames) {
    int holdDelayFrames;
    float holdFrameNo;
        holdDelayFrames = min(delayFrames, maxDelayFrames);
        if (proportion == 1.0f) {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - holdDelayFrames, (float) maxDelayFrames);
            return getDelayedVal(drawZDelay, holdFrameNo);;
        } else {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - (proportion * holdDelayFrames), (float) maxDelayFrames);
            return getDelayedVal(drawZDelay, holdFrameNo);;
        };
};

float TXCurvePoint::getDelayControl1X(float & proportion, const int & delayFrames) {
    int holdDelayFrames;
    float holdFrameNo;
        holdDelayFrames = min(delayFrames, maxDelayFrames);
        if (proportion == 1.0f) {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - holdDelayFrames, (float) maxDelayFrames);
            return getDelayedVal(control1XDelay, holdFrameNo);;
        } else {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - (proportion * holdDelayFrames), (float) maxDelayFrames);
            return getDelayedVal(control1XDelay, holdFrameNo);;
        };
};

float TXCurvePoint::getDelayControl1Y(float & proportion, const int & delayFrames) {
    int holdDelayFrames;
    float holdFrameNo;
        holdDelayFrames = min(delayFrames, maxDelayFrames);
        if (proportion == 1.0f) {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - holdDelayFrames, (float) maxDelayFrames);
            return getDelayedVal(control1YDelay, holdFrameNo);;
        } else {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - (proportion * holdDelayFrames), (float) maxDelayFrames);
            return getDelayedVal(control1YDelay, holdFrameNo);;
        };
};

float TXCurvePoint::getDelayControl1Z(float & proportion, const int & delayFrames) {
    int holdDelayFrames;
    float holdFrameNo;
        holdDelayFrames = min(delayFrames, maxDelayFrames);
        if (proportion == 1.0f) {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - holdDelayFrames, (float) maxDelayFrames);
            return getDelayedVal(control1ZDelay, holdFrameNo);;
        } else {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - (proportion * holdDelayFrames), (float) maxDelayFrames);
            return getDelayedVal(control1ZDelay, holdFrameNo);;
        };
};

float TXCurvePoint::getDelayControl2X(float & proportion, const int & delayFrames) {
    int holdDelayFrames;
    float holdFrameNo;
        holdDelayFrames = min(delayFrames, maxDelayFrames);
        if (proportion == 1.0f) {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - holdDelayFrames, (float) maxDelayFrames);
            return getDelayedVal(control2XDelay, holdFrameNo);;
        } else {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - (proportion * holdDelayFrames), (float) maxDelayFrames);
            return getDelayedVal(control2XDelay, holdFrameNo);;
        };
};

float TXCurvePoint::getDelayControl2Y(float & proportion, const int & delayFrames) {
    int holdDelayFrames;
    float holdFrameNo;
        holdDelayFrames = min(delayFrames, maxDelayFrames);
        if (proportion == 1.0f) {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - holdDelayFrames, (float) maxDelayFrames);
            return getDelayedVal(control2YDelay, holdFrameNo);;
        } else {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - (proportion * holdDelayFrames), (float) maxDelayFrames);
            return getDelayedVal(control2YDelay, holdFrameNo);;
        };
};

float TXCurvePoint::getDelayControl2Z(float & proportion, const int & delayFrames) {
    int holdDelayFrames;
    float holdFrameNo;
        holdDelayFrames = min(delayFrames, maxDelayFrames);
        if (proportion == 1.0f) {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - holdDelayFrames, (float) maxDelayFrames);
            return getDelayedVal(control2ZDelay, holdFrameNo);;
        } else {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - (proportion * holdDelayFrames), (float) maxDelayFrames);
            return getDelayedVal(control2ZDelay, holdFrameNo);;
        };
};



// =====================================================

// using ease functions

float TXCurvePoint::getInterp(float val1, float val2, float & proportion, const int & easeFunction, const int & easeFunction2, float easeMix) {
    float floatVal, floatVal2, outVal;
    if (easeMix == 0.0) {
        outVal = ofxTweenLite::tween ( val1, val2, proportion, (ofEaseFunction) easeFunction);
    } else {
        if (easeMix == 1.0) {
            outVal = ofxTweenLite::tween ( val1, val2, proportion, (ofEaseFunction) easeFunction2);
            
        } else {
            floatVal = ofxTweenLite::tween ( val1, val2, proportion, (ofEaseFunction) easeFunction);
            floatVal2 = ofxTweenLite::tween ( val1, val2, proportion, (ofEaseFunction) easeFunction2);
            outVal = ofLerp(floatVal, floatVal2, easeMix);
        };
    }
    return outVal;
};

float TXCurvePoint::getInterpDrawX(const float  & index, const float  & total, const int & easeFunction, const int & easeFunction2, const float  & easeMix) {
    if (index == 0 || (isRangeOptionPoint && drawXEndIgnore)) {
        return drawX->getFloat();
    } else if (index == total - 1) {
        return drawXEnd->getFloat();
    } else {
        float proportion =  index /(total-1);
        return getInterp(drawX->getFloat(), drawXEnd->getFloat(), proportion, easeFunction, easeFunction2,  easeMix);
    };
};

float TXCurvePoint::getInterpDrawY(const float  & index, const float  & total, const int & easeFunction, const int & easeFunction2, const float  & easeMix) {
    if (index == 0 || (isRangeOptionPoint && drawYEndIgnore)) {
        return drawY->getFloat();
    } else if (index == total - 1) {
        return drawYEnd->getFloat();
    } else {
        float proportion =  index /(total-1);
        return getInterp(drawY->getFloat(), drawYEnd->getFloat(), proportion, easeFunction, easeFunction2,  easeMix);
    };
};

float TXCurvePoint::getInterpDrawZ(const float  & index, const float  & total, const int & easeFunction, const int & easeFunction2, const float  & easeMix) {
    if (index == 0 || (isRangeOptionPoint && drawZEndIgnore)) {
        return drawZ->getFloat();
    } else if (index == total - 1) {
        return drawZEnd->getFloat();
    } else {
        float proportion =  index /(total-1);
        return getInterp(drawZ->getFloat(), drawZEnd->getFloat(), proportion, easeFunction, easeFunction2,  easeMix);
    };
};

float TXCurvePoint::getInterpControl1X(const float  & index, const float  & total, const int & easeFunction, const int & easeFunction2, const float  & easeMix) {
    if (index == 0 || (isRangeOptionPoint && control1XEndIgnore)) {
        return control1X->getFloat();
    } else if (index == total - 1) {
        return control1XEnd->getFloat();
    } else {
        float proportion =  index /(total-1);
        return getInterp(control1X->getFloat(), control1XEnd->getFloat(), proportion, easeFunction, easeFunction2,  easeMix);
    };
};

float TXCurvePoint::getInterpControl1Y(const float  & index, const float  & total, const int & easeFunction, const int & easeFunction2, const float  & easeMix) {
    if (index == 0 || (isRangeOptionPoint && control1YEndIgnore)) {
        return control1Y->getFloat();
    } else if (index == total - 1) {
        return control1YEnd->getFloat();
    } else {
        float proportion =  index /(total-1);
        return getInterp(control1Y->getFloat(), control1YEnd->getFloat(), proportion, easeFunction, easeFunction2,  easeMix);
    };
};

float TXCurvePoint::getInterpControl1Z(const float  & index, const float  & total, const int & easeFunction, const int & easeFunction2, const float  & easeMix) {
    if (index == 0 || (isRangeOptionPoint && control1ZEndIgnore)) {
        return control1Z->getFloat();
    } else if (index == total - 1) {
        return control1ZEnd->getFloat();
    } else {
        float proportion =  index /(total-1);
        return getInterp(control1Z->getFloat(), control1ZEnd->getFloat(), proportion, easeFunction, easeFunction2,  easeMix);
    };
};

float TXCurvePoint::getInterpControl2X(const float  & index, const float  & total, const int & easeFunction, const int & easeFunction2, const float  & easeMix) {
    if (index == 0 || (isRangeOptionPoint && control2XEndIgnore)) {
        return control2X->getFloat();
    } else if (index == total - 1) {
        return control2XEnd->getFloat();
    } else {
        float proportion =  index /(total-1);
        return getInterp(control2X->getFloat(), control2XEnd->getFloat(), proportion, easeFunction, easeFunction2,  easeMix);
    };
};

float TXCurvePoint::getInterpControl2Y(const float  & index, const float  & total, const int & easeFunction, const int & easeFunction2, const float  & easeMix) {
    if (index == 0 || (isRangeOptionPoint && control2YEndIgnore)) {
        return control2Y->getFloat();
    } else if (index == total - 1) {
        return control2YEnd->getFloat();
    } else {
        float proportion =  index /(total-1);
        return getInterp(control2Y->getFloat(), control2YEnd->getFloat(), proportion, easeFunction, easeFunction2,  easeMix);
    };
};

float TXCurvePoint::getInterpControl2Z(const float  & index, const float  & total, const int & easeFunction, const int & easeFunction2, const float  & easeMix) {
    if (index == 0 || (isRangeOptionPoint && control2ZEndIgnore)) {
        return control2Z->getFloat();
    } else if (index == total - 1) {
        return control2ZEnd->getFloat();
    } else {
        float proportion =  index /(total-1);
        return getInterp(control2Z->getFloat(), control2ZEnd->getFloat(), proportion, easeFunction, easeFunction2,  easeMix);
    };
};

//////////////////// Delayed

float TXCurvePoint::getDelayDrawX(const float & index, const float & total, const int & delayFrames, const int & easeFunction, const int & easeFunction2, const float & easeMix) {
    int holdDelayFrames;
    float holdFrameNo;
    if (index == 0) {
        return drawX->getFloat();
    } else {
        holdDelayFrames = min(delayFrames, maxDelayFrames);
        if (index == total - 1) {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - holdDelayFrames, (float) maxDelayFrames);
            return getDelayedVal(drawXDelay, holdFrameNo);
        } else {
            float proportion =  index /(total-1);
            float curveProportion =  getInterp(0, 1, proportion, easeFunction, easeFunction2,  easeMix);
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - (curveProportion *holdDelayFrames), (float) maxDelayFrames);
            return getDelayedVal(drawXDelay, holdFrameNo);
        };
    }
};

float TXCurvePoint::getDelayDrawY(const float & index, const float & total, const int & delayFrames, const int & easeFunction, const int & easeFunction2, const float & easeMix) {
    int holdDelayFrames;
    float holdFrameNo;
    if (index == 0) {
        return drawY->getFloat();
    } else {
        holdDelayFrames = min(delayFrames, maxDelayFrames);
        if (index == total - 1) {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - holdDelayFrames, (float) maxDelayFrames);
            return getDelayedVal(drawYDelay, holdFrameNo);;
        } else {
            float proportion =  index /(total-1);
            float curveProportion =  getInterp(0, 1, proportion, easeFunction, easeFunction2,  easeMix);
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - (curveProportion *holdDelayFrames), (float) maxDelayFrames);
            return getDelayedVal(drawYDelay, holdFrameNo);
        };
    }
};

float TXCurvePoint::getDelayDrawZ(const float & index, const float & total, const int & delayFrames, const int & easeFunction, const int & easeFunction2, const float & easeMix) {
    int holdDelayFrames;
    float holdFrameNo;
    if (index == 0) {
        return drawZ->getFloat();
    } else {
        holdDelayFrames = min(delayFrames, maxDelayFrames);
        if (index == total - 1) {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - holdDelayFrames, (float) maxDelayFrames);
            return getDelayedVal(drawZDelay, holdFrameNo);;
        } else {
            float proportion =  index /(total-1);
            float curveProportion =  getInterp(0, 1, proportion, easeFunction, easeFunction2,  easeMix);
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - (curveProportion *holdDelayFrames), (float) maxDelayFrames);
            return getDelayedVal(drawZDelay, holdFrameNo);;
        };
    }
};

float TXCurvePoint::getDelayControl1X(const float & index, const float & total, const int & delayFrames, const int & easeFunction, const int & easeFunction2, const float & easeMix) {
    int holdDelayFrames;
    float holdFrameNo;
    if (index == 0) {
        return control1X->getFloat();
    } else {
        holdDelayFrames = min(delayFrames, maxDelayFrames);
        if (index == total - 1) {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - holdDelayFrames, (float) maxDelayFrames);
            return getDelayedVal(control1XDelay, holdFrameNo);;
        } else {
            float proportion =  index /(total-1);
            float curveProportion =  getInterp(0, 1, proportion, easeFunction, easeFunction2,  easeMix);
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - (curveProportion *holdDelayFrames), (float) maxDelayFrames);
            return getDelayedVal(control1XDelay, holdFrameNo);;
        };
    }
};

float TXCurvePoint::getDelayControl1Y(const float & index, const float & total, const int & delayFrames, const int & easeFunction, const int & easeFunction2, const float & easeMix) {
    int holdDelayFrames;
    float holdFrameNo;
    if (index == 0) {
        return control1Y->getFloat();
    } else {
        holdDelayFrames = min(delayFrames, maxDelayFrames);
        if (index == total - 1) {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - holdDelayFrames, (float) maxDelayFrames);
            return getDelayedVal(control1YDelay, holdFrameNo);;
        } else {
            float proportion =  index * (1/(total-1));
            float curveProportion =  getInterp(0, 1, proportion, easeFunction, easeFunction2,  easeMix);
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - (curveProportion *holdDelayFrames), (float) maxDelayFrames);
            return getDelayedVal(control1YDelay, holdFrameNo);;
        };
    }
};

float TXCurvePoint::getDelayControl1Z(const float & index, const float & total, const int & delayFrames, const int & easeFunction, const int & easeFunction2, const float & easeMix) {
    int holdDelayFrames;
    float holdFrameNo;
    if (index == 0) {
        return control1Z->getFloat();
    } else {
        holdDelayFrames = min(delayFrames, maxDelayFrames);
        if (index == total - 1) {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - holdDelayFrames, (float) maxDelayFrames);
            return getDelayedVal(control1ZDelay, holdFrameNo);;
        } else {
            float proportion =  index * (1/(total-1));
            float curveProportion =  getInterp(0, 1, proportion, easeFunction, easeFunction2,  easeMix);
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - (curveProportion *holdDelayFrames), (float) maxDelayFrames);
            return getDelayedVal(control1ZDelay, holdFrameNo);;
        };
    }
};

float TXCurvePoint::getDelayControl2X(const float & index, const float & total, const int & delayFrames, const int & easeFunction, const int & easeFunction2, const float & easeMix) {
    int holdDelayFrames;
    float holdFrameNo;
    if (index == 0) {
        return control2X->getFloat();
    } else {
        holdDelayFrames = min(delayFrames, maxDelayFrames);
        if (index == total - 1) {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - holdDelayFrames, (float) maxDelayFrames);
            return getDelayedVal(control2XDelay, holdFrameNo);;
        } else {
            float proportion =  index /(total-1);
            float curveProportion =  getInterp(0, 1, proportion, easeFunction, easeFunction2,  easeMix);
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - (curveProportion *holdDelayFrames), (float) maxDelayFrames);
            return getDelayedVal(control2XDelay, holdFrameNo);;
        };
    }
};

float TXCurvePoint::getDelayControl2Y(const float & index, const float & total, const int & delayFrames, const int & easeFunction, const int & easeFunction2, const float & easeMix) {
    int holdDelayFrames;
    float holdFrameNo;
    if (index == 0) {
        return control2Y->getFloat();
    } else {
        holdDelayFrames = min(delayFrames, maxDelayFrames);
        if (index == total - 1) {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - holdDelayFrames, (float) maxDelayFrames);
            return getDelayedVal(control2YDelay, holdFrameNo);;
        } else {
            float proportion =  index /(total-1);
            float curveProportion =  getInterp(0, 1, proportion, easeFunction, easeFunction2,  easeMix);
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - (curveProportion *holdDelayFrames), (float) maxDelayFrames);
            return getDelayedVal(control2YDelay, holdFrameNo);;
        };
    }
};

float TXCurvePoint::getDelayControl2Z(const float & index, const float & total, const int & delayFrames, const int & easeFunction, const int & easeFunction2, const float & easeMix) {
    int holdDelayFrames;
    float holdFrameNo;
    if (index == 0) {
        return control2Z->getFloat();
    } else {
        holdDelayFrames = min(delayFrames, maxDelayFrames);
        if (index == total - 1) {
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - holdDelayFrames, (float) maxDelayFrames);
            return getDelayedVal(control2ZDelay, holdFrameNo);;
        } else {
            float proportion =  index /(total-1);
            float curveProportion =  getInterp(0, 1, proportion, easeFunction, easeFunction2,  easeMix);
            holdFrameNo = fmod(maxDelayFrames + currentDelayFrame - (curveProportion *holdDelayFrames), (float) maxDelayFrames);
            return getDelayedVal(control2ZDelay, holdFrameNo);;
        };
    }
};

