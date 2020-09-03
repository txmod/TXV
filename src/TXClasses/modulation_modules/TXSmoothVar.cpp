/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXSmoothVar.h"

// properties

// constructor
TXSmoothVar::TXSmoothVar (int smoothTypeArg, float smooothTimeArg, float outValueArg, float targetValueArg, bool circularSmoothingArg) {
    setup (smoothTypeArg, smooothTimeArg, outValueArg, targetValueArg, circularSmoothingArg);
};

// methods
void TXSmoothVar::setup (int smoothTypeArg, float smooothTimeArg, float outValueArg, float targetValueArg, bool circularSmoothingArg) {
    
    smoothType = smoothTypeArg;
	smoothTime = smooothTimeArg;
    outValue = outValueArg;
    targetValue = targetValueArg;
    circularSmoothing = circularSmoothingArg;
    currentTime = 0.0;
    resetLinearRate();
};

void TXSmoothVar::setTime(float timeArg){
    float valueDiff, newVal, holdValue, holdSmoothTime;
    
    oldTime = currentTime;
    currentTime = timeArg;
    timeDiff = currentTime - oldTime;
    if (smoothType == TXSMOOTHTYPE_EXPONENTIAL) {
        holdSmoothTime = smoothTime * 0.125;
    } else {
        holdSmoothTime = smoothTime;
    };
    if ((timeDiff > 0) && (targetValue != outValue)) {
        valueDiff = targetValue - outValue;
        if (timeDiff < holdSmoothTime) {
            switch (smoothType) {
                case TXSMOOTHTYPE_EXPONENTIAL:
                    if (circularSmoothing) {
                        if (abs(valueDiff) > 0.5) {
                            if (valueDiff > 0) {
                                valueDiff = valueDiff-1;
                            } else {
                                valueDiff = valueDiff+1;
                            }
                        };
                        holdValue = outValue;
                        holdValue = holdValue + (valueDiff * timeDiff / holdSmoothTime);
                        while (holdValue > 1 ) holdValue = holdValue - 1;
                        while (holdValue < 0 ) holdValue = holdValue + 1;
                        outValue = holdValue;
                    } else {
                        outValue = outValue + (valueDiff * timeDiff / holdSmoothTime);
                    };
                    break;
                default:
                    // i.e. case TXSMOOTHTYPE_LINEAR:
                    if (linearRate == 0 ) {
                        newVal = targetValue;
                    } else {
                        newVal = outValue + (timeDiff * linearRate);
                    }
                    if (circularSmoothing) {
                        while (newVal > 1 ) newVal -= 1;
                        while (newVal < 0 ) newVal += 1;
                        outValue = newVal;
                    } else {
                        if (linearRate < 0){
                            if (newVal < targetValue) {
                                outValue = targetValue;
                            } else {
                                outValue = newVal;
                            };
                        } else {
                            if (newVal > targetValue) {
                                outValue = targetValue;
                            } else {
                                outValue = newVal;
                            };
                        };
                    };
                    break;
            }
        } else {
            outValue = targetValue;
        };
    };
}

float TXSmoothVar::valueAt(float timeArg) {
    setTime(timeArg);
    return outValue;
}

void TXSmoothVar::advanceBy(float timeDeltaArg) {
    if (timeDeltaArg > 0) {
        setTime(currentTime + timeDeltaArg);
    };
}

void TXSmoothVar::resetLinearRate(){
    float valueDiff = targetValue - outValue;
    if ((smoothTime > 0.02) && (abs(valueDiff) > 0.0001)) {
        if (circularSmoothing) {
            if (abs(valueDiff) > 0.5) {
                if (valueDiff > 0) {
                    valueDiff = valueDiff-1;
                } else {
                    valueDiff = valueDiff+1;
                };
            };
        };
        linearRate = valueDiff / smoothTime;
    } else {
        linearRate = 0;
    };
}

void  TXSmoothVar::resetTime() {
    outValue = targetValue;
    currentTime = 0.0;
    resetLinearRate();
}

float TXSmoothVar::getTargetValue() {
    return targetValue;
}

void TXSmoothVar::setTargetValue(float targetValueArg) {
    if (targetValue != targetValueArg) {
        targetValue = targetValueArg;
        resetLinearRate();
    };
}

void  TXSmoothVar::setSmoothType(int smoothTypeArg) {
    if (smoothType != smoothTypeArg) {
        smoothType = smoothTypeArg;
        resetLinearRate();
    };
}

int  TXSmoothVar::getSmoothType() {
    return smoothType;
}

void  TXSmoothVar::setSmoothTime(float smoothTimeArg) {
    smoothTime = smoothTimeArg;
    resetLinearRate();
}

float  TXSmoothVar::getSmoothTime() {
    return smoothTime;
}

