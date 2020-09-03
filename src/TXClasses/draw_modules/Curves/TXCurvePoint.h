/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"
#include "TXParametersBase.h"
#include "ofxTweenLite.h"

enum TXPOINTTYPE {
    TXPOINTTYPE_2DBEZIER,
    TXPOINTTYPE_2DBEZIERDELAY,
    TXPOINTTYPE_2DBEZIERRANGE,
    TXPOINTTYPE_2DBEZIERRANGEOPTION,
    TXPOINTTYPE_2DCONTROLPOINT,
    TXPOINTTYPE_2DCONTROLPOINTDELAY,
    TXPOINTTYPE_2DCONTROLPOINTRANGE,
    TXPOINTTYPE_2DCONTROLPOINTRANGEOPTION,
    TXPOINTTYPE_2DPOINT,
    TXPOINTTYPE_2DPOINTDELAY,
    TXPOINTTYPE_2DPOINTRANGE,
    TXPOINTTYPE_2DPOINTRANGEOPTION,
    TXPOINTTYPE_3DBEZIER,
    TXPOINTTYPE_3DBEZIERDELAY,
    TXPOINTTYPE_3DBEZIERRANGE,
    TXPOINTTYPE_3DBEZIERRANGEOPTION,
    TXPOINTTYPE_3DCONTROLPOINT,
    TXPOINTTYPE_3DCONTROLPOINTDELAY,
    TXPOINTTYPE_3DCONTROLPOINTRANGE,
    TXPOINTTYPE_3DCONTROLPOINTRANGEOPTION,
    TXPOINTTYPE_3DPOINT,
    TXPOINTTYPE_3DPOINTDELAY,
    TXPOINTTYPE_3DPOINTRANGE,
    TXPOINTTYPE_3DPOINTRANGEOPTION,
};

class TXCurvePoint : public TXParametersBase
{
public:
	// constructor
	TXCurvePoint ();

 	// methods
	void setup (int pointTypeArg = TXPOINTTYPE_2DPOINT, string nameArg = "curvePoint", int maxDelayFramesArg = 1000);
    // if using frameDelay, setup separately:
    void update();
    
    float getDelayedVal(const vector<float> & delayVector, const float & delayFrames);
    
    // parameter interpolation NO LONGER NEEDED
    // float getInterp(ofPtr<TXModParamFloat> param1, ofPtr<TXModParamFloat> param2, float & proportion);
    
    //// interpolation with Curves NO LONGER NEEDED
    // float getInterp(float val1, float val2, float & proportion, TXParameterFloat256 & curve1, TXParameterFloat256 & curve2, float & phase, float & curveMorph);
    
    float getInterpDrawX(float & proportion);
    float getInterpDrawY(float & proportion);
    float getInterpDrawZ(float & proportion);
    
    float getInterpControl1X(float & proportion);
    float getInterpControl1Y(float & proportion);
    float getInterpControl1Z(float & proportion);
    
    float getInterpControl2X(float & proportion);
    float getInterpControl2Y(float & proportion);
    float getInterpControl2Z(float & proportion);
    
    float getDelayDrawX(float & proportion, const int & delayFrames);
    float getDelayDrawY(float & proportion, const int & delayFrames);
    float getDelayDrawZ(float & proportion, const int & delayFrames);
    
    float getDelayControl1X(float & proportion, const int & delayFrames);
    float getDelayControl1Y(float & proportion, const int & delayFrames);
    float getDelayControl1Z(float & proportion, const int & delayFrames);
    
    float getDelayControl2X(float & proportion, const int & delayFrames);
    float getDelayControl2Y(float & proportion, const int & delayFrames);
    float getDelayControl2Z(float & proportion, const int & delayFrames);
    
    // LEGACY METHODS using ease functions
    
    float getInterp(float val1, float val2, float & proportion, const int & easeFunction = OF_EASE_LINEAR_IN, const int & easeFunction2 = OF_EASE_LINEAR_IN, float easeMix = 0.0);

    float getInterpDrawX(const float & index, const float & total, const int & easeFunction = OF_EASE_LINEAR_IN, const int & easeFunction2 = OF_EASE_LINEAR_IN, const float & easeMix = 0.0);
    float getInterpDrawY(const float & index, const float & total, const int & easeFunction = OF_EASE_LINEAR_IN, const int & easeFunction2 = OF_EASE_LINEAR_IN, const float & easeMix = 0.0);
    float getInterpDrawZ(const float & index, const float & total, const int & easeFunction = OF_EASE_LINEAR_IN, const int & easeFunction2 = OF_EASE_LINEAR_IN, const float & easeMix = 0.0);
    
    float getInterpControl1X(const float & index, const float & total, const int & easeFunction = OF_EASE_LINEAR_IN, const int & easeFunction2 = OF_EASE_LINEAR_IN, const float & easeMix = 0.0);
    float getInterpControl1Y(const float & index, const float & total, const int & easeFunction = OF_EASE_LINEAR_IN, const int & easeFunction2 = OF_EASE_LINEAR_IN, const float & easeMix = 0.0);
    float getInterpControl1Z(const float & index, const float & total, const int & easeFunction = OF_EASE_LINEAR_IN, const int & easeFunction2 = OF_EASE_LINEAR_IN, const float & easeMix = 0.0);
    
    float getInterpControl2X(const float & index, const float & total, const int & easeFunction = OF_EASE_LINEAR_IN, const int & easeFunction2 = OF_EASE_LINEAR_IN, const float & easeMix = 0.0);
    float getInterpControl2Y(const float & index, const float & total, const int & easeFunction = OF_EASE_LINEAR_IN, const int & easeFunction2 = OF_EASE_LINEAR_IN, const float & easeMix = 0.0);
    float getInterpControl2Z(const float & index, const float & total, const int & easeFunction = OF_EASE_LINEAR_IN, const int & easeFunction2 = OF_EASE_LINEAR_IN, const float & easeMix = 0.0);
    
    float getDelayDrawX(const float & index, const float & total, const int & delayFrames, const int & easeFunction = OF_EASE_LINEAR_IN, const int & easeFunction2 = OF_EASE_LINEAR_IN, const float & easeMix = 0.0);
    float getDelayDrawY(const float & index, const float & total, const int & delayFrames, const int & easeFunction = OF_EASE_LINEAR_IN, const int & easeFunction2 = OF_EASE_LINEAR_IN, const float & easeMix = 0.0);
    float getDelayDrawZ(const float & index, const float & total, const int & delayFrames, const int & easeFunction = OF_EASE_LINEAR_IN, const int & easeFunction2 = OF_EASE_LINEAR_IN, const float & easeMix = 0.0);
    
    float getDelayControl1X(const float & index, const float & total, const int & delayFrames, const int & easeFunction = OF_EASE_LINEAR_IN, const int & easeFunction2 = OF_EASE_LINEAR_IN, const float & easeMix = 0.0);
    float getDelayControl1Y(const float & index, const float & total, const int & delayFrames, const int & easeFunction = OF_EASE_LINEAR_IN, const int & easeFunction2 = OF_EASE_LINEAR_IN, const float & easeMix = 0.0);
    float getDelayControl1Z(const float & index, const float & total, const int & delayFrames, const int & easeFunction = OF_EASE_LINEAR_IN, const int & easeFunction2 = OF_EASE_LINEAR_IN, const float & easeMix = 0.0);
    
    float getDelayControl2X(const float & index, const float & total, const int & delayFrames, const int & easeFunction = OF_EASE_LINEAR_IN, const int & easeFunction2 = OF_EASE_LINEAR_IN, const float & easeMix = 0.0);
    float getDelayControl2Y(const float & index, const float & total, const int & delayFrames, const int & easeFunction = OF_EASE_LINEAR_IN, const int & easeFunction2 = OF_EASE_LINEAR_IN, const float & easeMix = 0.0);
    float getDelayControl2Z(const float & index, const float & total, const int & delayFrames, const int & easeFunction = OF_EASE_LINEAR_IN, const int & easeFunction2 = OF_EASE_LINEAR_IN, const float & easeMix = 0.0);
    
    ofPtr<TXModParamFloat> drawX;
    ofPtr<TXModParamFloat> drawY;
    ofPtr<TXModParamFloat> drawZ;
    ofPtr<TXModParamFloat> control1X;
    ofPtr<TXModParamFloat> control1Y;
    ofPtr<TXModParamFloat> control1Z;
    ofPtr<TXModParamFloat> control2X;
    ofPtr<TXModParamFloat> control2Y;
    ofPtr<TXModParamFloat> control2Z;
    
    ofPtr<TXModParamFloat> drawXEnd;
    ofPtr<TXModParamFloat> drawYEnd;
    ofPtr<TXModParamFloat> drawZEnd;
    ofPtr<TXModParamFloat> control1XEnd;
    ofPtr<TXModParamFloat> control1YEnd;
    ofPtr<TXModParamFloat> control1ZEnd;
    ofPtr<TXModParamFloat> control2XEnd;
    ofPtr<TXModParamFloat> control2YEnd;
    ofPtr<TXModParamFloat> control2ZEnd;
    
    ofParameter<bool> drawXEndIgnore;
    ofParameter<bool> drawYEndIgnore;
    ofParameter<bool> drawZEndIgnore;
    ofParameter<bool> control1XEndIgnore;
    ofParameter<bool> control1YEndIgnore;
    ofParameter<bool> control1ZEndIgnore;
    ofParameter<bool> control2XEndIgnore;
    ofParameter<bool> control2YEndIgnore;
    ofParameter<bool> control2ZEndIgnore;

private:

    int pointType;
    int maxDelayFrames = 0;
    int currentDelayFrame = 0;
    
    bool is3DPoint;
    bool isRangePoint;
    bool isRangeOptionPoint;
    bool isDelayPoint;
    bool hasDrawPoint;
    bool hasControl1Point;
    bool hasControl2Point;
    
    // delay lines
    vector<float> drawXDelay;
    vector<float> drawYDelay;
    vector<float> drawZDelay;
    vector<float> control1XDelay;
    vector<float> control1YDelay;
    vector<float> control1ZDelay;
    vector<float> control2XDelay;
    vector<float> control2YDelay;
    vector<float> control2ZDelay;
};
// for ref:
// in ofxTweenLite:
// enum ofEaseFunction
//{
//    OF_EASE_BACK_IN         = 0,
//    OF_EASE_BACK_OUT        = 1,
//    OF_EASE_BACK_INOUT      = 2,
//    OF_EASE_BOUNCE_IN       = 3,
//    OF_EASE_BOUNCE_OUT      = 4,
//    OF_EASE_BOUNCE_INOUT    = 5,
//    OF_EASE_CIRC_IN         = 6,
//    OF_EASE_CIRC_OUT        = 7,
//    OF_EASE_CIRC_INOUT      = 8,
//    OF_EASE_CUBIC_IN        = 9,
//    OF_EASE_CUBIC_OUT       = 10,
//    OF_EASE_CUBIC_INOUT     = 11,
//    OF_EASE_ELASTIC_IN      = 12,
//    OF_EASE_ELASTIC_OUT     = 13,
//    OF_EASE_ELASTIC_INOUT   = 14,
//    OF_EASE_EXPO_IN         = 15,
//    OF_EASE_EXPO_OUT        = 16,
//    OF_EASE_EXPO_INOUT      = 17,
//    OF_EASE_LINEAR_IN       = 18,
//    OF_EASE_LINEAR_OUT      = 19,
//    OF_EASE_LINEAR_INOUT    = 20,
//    OF_EASE_QUAD_IN         = 21,
//    OF_EASE_QUAD_OUT        = 22,
//    OF_EASE_QUAD_INOUT      = 23,
//    OF_EASE_QUART_IN        = 24,
//    OF_EASE_QUART_OUT       = 25,
//    OF_EASE_QUART_INOUT     = 26,
//    OF_EASE_QUINT_IN        = 27,
//    OF_EASE_QUINT_OUT       = 28,
//    OF_EASE_QUINT_INOUT     = 29,
//    OF_EASE_SINE_IN         = 30,
//    OF_EASE_SINE_OUT        = 31,
//    OF_EASE_SINE_INOUT      = 32
//    };



