/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXDrawLayersBase.h"
//#include "TXMain.h"

class TXDrawTransform3DDelay  :  public TXDrawLayersBase
{
public:
	TXDrawTransform3DDelay();

    const static int maxDelayFrames = 1000;
    const static int maxCopies = 1000;
    const static int maxSpreadTypes = 32;

	void setup();
    void update();
    void draw();
    void rotate(float rotX, float rotY, float rotZ);
    float getDelayedVal(const vector<float> & delayVector, const float & delayFrames);

    // parameters
    ofPtr<TXModParamInt> drawLayersRule;
    ofPtr<TXModParamInt> delayFrames;
    ofPtr<TXModParamInt> numCopies;
    ofPtr<TXModParamInt> transformOrder;
    ofPtr<TXModParamFloat> shiftX;
    ofPtr<TXModParamFloat> shiftY;
    ofPtr<TXModParamFloat> shiftZ;
    TXParameterFloat256   shiftXSpreadCurve;
    TXParameterFloat256   shiftXSpreadCurve2;
    ofPtr<TXModParamFloat> shiftXSpreadCurveMorph;
    ofPtr<TXModParamFloat> shiftXSpreadCurvePhase;
    TXParameterFloat256   shiftYSpreadCurve;
    TXParameterFloat256   shiftYSpreadCurve2;
    ofPtr<TXModParamFloat> shiftYSpreadCurveMorph;
    ofPtr<TXModParamFloat> shiftYSpreadCurvePhase;
    TXParameterFloat256   shiftZSpreadCurve;
    TXParameterFloat256   shiftZSpreadCurve2;
    ofPtr<TXModParamFloat> shiftZSpreadCurveMorph;
    ofPtr<TXModParamFloat> shiftZSpreadCurvePhase;
    ofParameter<bool> useShiftXSpreadCurveForShiftY;
    ofParameter<bool> useShiftXSpreadCurveForShiftZ;
    ofPtr<TXModParamFloat> rotateX;
    ofPtr<TXModParamFloat> rotateY;
    ofPtr<TXModParamFloat> rotateZ;
    ofPtr<TXModParamFloat> rotateMultiply;
    TXParameterFloat256   rotateXSpreadCurve;
    TXParameterFloat256   rotateXSpreadCurve2;
    ofPtr<TXModParamFloat> rotateXSpreadCurveMorph;
    ofPtr<TXModParamFloat> rotateXSpreadCurvePhase;
    TXParameterFloat256   rotateYSpreadCurve;
    TXParameterFloat256   rotateYSpreadCurve2;
    ofPtr<TXModParamFloat> rotateYSpreadCurveMorph;
    ofPtr<TXModParamFloat> rotateYSpreadCurvePhase;
    TXParameterFloat256   rotateZSpreadCurve;
    TXParameterFloat256   rotateZSpreadCurve2;
    ofPtr<TXModParamFloat> rotateZSpreadCurveMorph;
    ofPtr<TXModParamFloat> rotateZSpreadCurvePhase;
    ofParameter<bool> useRotateXSpreadCurveForRotateY;
    ofParameter<bool> useRotateXSpreadCurveForRotateZ;
    ofPtr<TXModParamFloat> anchorX;
    ofPtr<TXModParamFloat> anchorY;
    ofPtr<TXModParamFloat> anchorZ;
    TXParameterFloat256   anchorXSpreadCurve;
    TXParameterFloat256   anchorXSpreadCurve2;
    ofPtr<TXModParamFloat> anchorXSpreadCurveMorph;
    ofPtr<TXModParamFloat> anchorXSpreadCurvePhase;
    TXParameterFloat256   anchorYSpreadCurve;
    TXParameterFloat256   anchorYSpreadCurve2;
    ofPtr<TXModParamFloat> anchorYSpreadCurveMorph;
    ofPtr<TXModParamFloat> anchorYSpreadCurvePhase;
    TXParameterFloat256   anchorZSpreadCurve;
    TXParameterFloat256   anchorZSpreadCurve2;
    ofPtr<TXModParamFloat> anchorZSpreadCurveMorph;
    ofPtr<TXModParamFloat> anchorZSpreadCurvePhase;
    ofParameter<bool> useAnchorXSpreadCurveForAnchorY;
    ofParameter<bool> useAnchorXSpreadCurveForAnchorZ;
    ofPtr<TXModParamFloat> scaleX;
    ofPtr<TXModParamFloat> scaleY;
    ofPtr<TXModParamFloat> scaleZ;
    ofParameter<bool> useScaleXForScaleY;
    ofParameter<bool> useScaleXForScaleZ;
    TXParameterFloat256   scaleXSpreadCurve;
    TXParameterFloat256   scaleXSpreadCurve2;
    ofPtr<TXModParamFloat> scaleXSpreadCurveMorph;
    ofPtr<TXModParamFloat> scaleXSpreadCurvePhase;
    TXParameterFloat256   scaleYSpreadCurve;
    TXParameterFloat256   scaleYSpreadCurve2;
    ofPtr<TXModParamFloat> scaleYSpreadCurveMorph;
    ofPtr<TXModParamFloat> scaleYSpreadCurvePhase;
    TXParameterFloat256   scaleZSpreadCurve;
    TXParameterFloat256   scaleZSpreadCurve2;
    ofPtr<TXModParamFloat> scaleZSpreadCurveMorph;
    ofPtr<TXModParamFloat> scaleZSpreadCurvePhase;
    ofParameter<bool> useScaleXSpreadCurveForScaleY;
    ofParameter<bool> useScaleXSpreadCurveForScaleZ;

    // delay lines
    vector<float> shiftXDelay;
    vector<float> shiftYDelay;
    vector<float> shiftZDelay;
    vector<float> rotateXDelay;
    vector<float> rotateYDelay;
    vector<float> rotateZDelay;
    vector<float> anchorXDelay;
    vector<float> anchorYDelay;
    vector<float> anchorZDelay;
    vector<float> scaleXDelay;
    vector<float> scaleYDelay;
    vector<float> scaleZDelay;
    
protected:
    int currentDelayFrame = 0;

};

