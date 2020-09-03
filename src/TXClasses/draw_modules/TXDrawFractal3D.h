/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "TXDrawLayersBase.h"
#include "TXFractalBranch3D.h"

class TXDrawFractal3D  :  public TXDrawLayersBase
{
public:
	TXDrawFractal3D();

    static const int numFractalBranches = 10;

	void setup();
	virtual void draw();
    void drawFractalBranch(int levelArg);
    
    TXFractalBranch3D arrFractalBranches[numFractalBranches];
    
    ofPtr<TXModParamInt> fractalTreeLevels;
    ofPtr<TXModParamInt> fractalTreeBranches;
    ofPtr<TXModParamFloat> cellWidth;
    ofPtr<TXModParamFloat> cellHeight;
    ofPtr<TXModParamFloat> cellDepth;
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
