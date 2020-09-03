/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "TXDrawLayersBase.h"
#include "TXFractalDelayBranch.h"

class TXDrawFractalDelay  :  public TXDrawLayersBase
{
public:
	TXDrawFractalDelay();

    static const int numFractalBranches = 10;
    static const int maxDelayFrames = 1000;

	void setup();
    void update();
	virtual void draw();
    void drawFractalBranch(int levelArg);
    
    TXFractalDelayBranch arrFractalBranches[numFractalBranches];
    
    ofPtr<TXModParamInt> fractalTreeLevels;
    ofPtr<TXModParamInt> fractalTreeBranches;
    ofPtr<TXModParamFloat> cellWidth;
    ofPtr<TXModParamFloat> cellHeight;
    ofPtr<TXModParamInt> randomSeed;
    ofPtr<TXModParamInt> maxLevelDelayFrames;
    ofPtr<TXModParamFloat> level1DelayRatio;
    ofPtr<TXModParamFloat> level2DelayRatio;
    ofPtr<TXModParamFloat> level3DelayRatio;
    ofPtr<TXModParamFloat> level4DelayRatio;
    ofPtr<TXModParamFloat> level5DelayRatio;
    ofPtr<TXModParamFloat> level6DelayRatio;
    ofPtr<TXModParamFloat> level7DelayRatio;
    ofPtr<TXModParamFloat> level8DelayRatio;
    ofPtr<TXModParamFloat> level9DelayRatio;
    ofPtr<TXModParamFloat> level10DelayRatio;
    ofPtr<TXModParamFloat> level1RandDelayMix;
    ofPtr<TXModParamFloat> level2RandDelayMix;
    ofPtr<TXModParamFloat> level3RandDelayMix;
    ofPtr<TXModParamFloat> level4RandDelayMix;
    ofPtr<TXModParamFloat> level5RandDelayMix;
    ofPtr<TXModParamFloat> level6RandDelayMix;
    ofPtr<TXModParamFloat> level7RandDelayMix;
    ofPtr<TXModParamFloat> level8RandDelayMix;
    ofPtr<TXModParamFloat> level9RandDelayMix;
    ofPtr<TXModParamFloat> level10RandDelayMix;
};

//  FRACTAL BRANCH PROPERTIES
//	  bool branchIfTopLevel;
//    bool drawBottomLevelOnly;
//    bool applyOffsetLast;
//    int  fractalBranchRule;
//	  int  fractalBranchRuleComparator;
//    int drawLayersRule;
//    float offsetX;
//    float offsetY;
//    float anchorX;
//    float anchorY;
//	  bool  useScaleXForScaleY;
//    float scaleX;
//    float scaleXLevelDelta;
//    float scaleXRandom;
//    float scaleY;
//    float scaleYLevelDelta;
//    float scaleYRandom;
//    float angle;
//    float angleLevelDelta;
//    float angleRandom;
//    float branchProbability;
//    float subBranchProbability;
//
//    // delay lines
//    vector<float> offsetXDelay;
//    vector<float> offsetYDelay;
//    vector<float> anchorXDelay;
//    vector<float> anchorYDelay;
//    vector<float> scaleXDelay;
//    vector<float> scaleXLevelDeltaDelay;
//    vector<float> scaleXRandomDelay;
//    vector<float> scaleYDelay;
//    vector<float> scaleYLevelDeltaDelay;
//    vector<float> scaleYRandomDelay;
//    vector<float> angleDelay;
//    vector<float> angleLevelDeltaDelay;
//    vector<float> angleRandomDelay;
//    vector<float> branchProbabilityDelay;
//    vector<float> subBranchProbabilityDelay;
//
//    float getDelayed_offsetX(const float & delayFrames);
//    float getDelayed_offsetY(const float & delayFrames);
//    float getDelayed_anchorX(const float & delayFrames);
//    float getDelayed_anchorY(const float & delayFrames);
//    float getDelayed_scaleX(const float & delayFrames);
//    float getDelayed_scaleXLevelDelta(const float & delayFrames);
//    float getDelayed_scaleXRandom(const float & delayFrames);
//    float getDelayed_scaleY(const float & delayFrames);
//    float getDelayed_scaleYLevelDelta(const float & delayFrames);
//    float getDelayed_scaleYRandom(const float & delayFrames);
//    float getDelayed_angle(const float & delayFrames);
//    float getDelayed_angleLevelDelta(const float & delayFrames);
//    float getDelayed_angleRandom(const float & delayFrames);
