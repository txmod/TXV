/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "TXDrawLayersBase.h"
#include "TXFractalBranch.h"

class TXDrawFractal  :  public TXDrawLayersBase
{
public:
	TXDrawFractal();

    static const int numFractalBranches = 10;

	void setup();
	virtual void draw();
    void drawFractalBranch(int levelArg);
    
    TXFractalBranch arrFractalBranches[numFractalBranches];
    
    ofPtr<TXModParamInt> fractalTreeLevels;
    ofPtr<TXModParamInt> fractalTreeBranches;
    ofPtr<TXModParamFloat> cellWidth;
    ofPtr<TXModParamFloat> cellHeight;
    ofPtr<TXModParamInt> randomSeed;
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
