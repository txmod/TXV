/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "TXDrawLayersBase.h"
#include "TXFractalDelayBranch3D.h"

class TXDrawFractalDelay3D  :  public TXDrawLayersBase
{
public:
	TXDrawFractalDelay3D();

    static const int numFractalBranches = 10;
    static const int maxDelayFrames = 1000;

	void setup();
    void update();
	virtual void draw();
    void drawFractalBranch(int levelArg);
    
    TXFractalDelayBranch3D arrFractalBranches[numFractalBranches];
    
    ofPtr<TXModParamInt> fractalTreeLevels;
    ofPtr<TXModParamInt> fractalTreeBranches;
    ofPtr<TXModParamFloat> cellWidth;
    ofPtr<TXModParamFloat> cellHeight;
    ofPtr<TXModParamFloat> cellDepth;
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
//    float offsetZ;
//    float anchorX;
//    float anchorY;
//    float anchorZ;
//	  bool  useScaleXForScaleY;
//	  bool  useScaleXForScaleZ;
//    float scaleX;
//    float scaleXLevelDelta;
//    float scaleXRandom;
//    float scaleY;
//    float scaleYLevelDelta;
//    float scaleYRandom;
//    float scaleZ;
//    float scaleZLevelDelta;
//    float scaleZRandom;
//    float rotateAxisX;
//    float rotateAxisY;
//    float rotateAxisZ;
//    float angleLevelDelta;
//    float angleRandom;
//    float branchProbability;
//    float subBranchProbability;
//
//    // delay lines
//    vector<float> offsetXDelay;
//    vector<float> offsetYDelay;
//    vector<float> offsetZDelay;
//    vector<float> anchorXDelay;
//    vector<float> anchorYDelay;
//    vector<float> anchorZDelay;
//    vector<float> scaleXDelay;
//    vector<float> scaleXLevelDeltaDelay;
//    vector<float> scaleXRandomDelay;
//    vector<float> scaleYDelay;
//    vector<float> scaleYLevelDeltaDelay;
//    vector<float> scaleYRandomDelay;
//    vector<float> scaleZDelay;
//    vector<float> scaleZLevelDeltaDelay;
//    vector<float> scaleZRandomDelay;
//    vector<float> rotateAxisXDelay;
//    vector<float> rotateAxisYDelay;
//    vector<float> rotateAxisZDelay;
//    vector<float> angleDelay;
//    vector<float> angleLevelDeltaDelay;
//    vector<float> angleRandomDelay;
