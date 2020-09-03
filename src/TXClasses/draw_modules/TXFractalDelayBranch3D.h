/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"
#include "TXParametersBase.h"

//enum TXFRACTALBRANCHRULE {TXFRACTALBRANCHRULE_ALWAYSBRANCH, TXFRACTALBRANCHRULE_BRANCHIFGREATER, TXFRACTALBRANCHRULE_BRANCHIFLESS, TXFRACTALBRANCHRULE_BRANCHIFEQUAL, TXFRACTALBRANCHRULE_BRANCHIFNOTEQUAL};

class TXFractalDelayBranch3D : public TXParametersBase
{
public:
	// constructor
	TXFractalDelayBranch3D ();

    /*
     Offset X (* sample width) (0-10)	
     Offset Y (* sample height)  (0-10)
     Offset Z (* sample height)  (0-10)
     Anchor X (0-1)
     Anchor Y (0-1)
     Anchor Z (0-1)
     useScaleXForScaleY
     useScaleXForScaleZ
     Scale X (0-1) [ModulationDestination]
     Scale X Level Delta (0-1) 
     Scale X Random (0-1)
     Scale Y (0-1) [ModulationDestination]
     Scale Y Level Delta (0-1)
     Scale Y Random (0-1)
     Scale Z (0-1) [ModulationDestination]
     Scale Z Level Delta (0-1)
     Scale Z Random (0-1)
     Rotate Axis X Random (0-1)
     Rotate Axis Y Random (0-1)
     Rotate Axis Z Random (0-1)
     Angle (±180) [ModulationDestination]
     Angle Level Delta (0-1) 
     Angle Random (0-1)
     BranchIfTopLevel true/false
     Branch Rule: Always Branch/ Branch if level Greater than Comparator/ Branch if level Less than Comparator/ 
       Branch if level Equal to Comparator/ Branch if level Not Equal to Comparator/ 
     Branch Rule Comparator (0-10)
     Branch Probability (0-1)
     Sub-Branch Probability (0-1)
     Apply offset last (after rotation, scale & draw)  true/false
     Draw bottom level only  true/false
     */
    
	// methods
    void setup (string nameArg = "fractalBranch", bool branchIfTopLevelArg = true, int fractalBranchRuleArg = TXFRACTALBRANCHRULE_ALWAYSBRANCH, int fractalBranchRuleComparatorArg = 1, bool drawBottomLevelOnlyArg = false, bool applyOffsetLastArg = true, float offsetXArg = 0, float offsetYArg = 0, float offsetZArg = 0, float anchorXArg = 0.5, float anchorYArg = 0.5, float anchorZArg = 0.0, float scaleXArg = 1, float scaleXLevelDeltaArg = 0, float scaleXRandomArg = 0, float scaleYArg = 1, float scaleYLevelDeltaArg = 0, float scaleYRandomArg = 0, float scaleZArg = 1, float scaleZLevelDeltaArg = 0, float scaleZRandomArg = 0, float rotateAxisXArg = 0, float rotateAxisYArg = 0, float rotateAxisZArg = 1, float angleArg = 0, float angleLevelDeltaArg = 0, float angleRandomArg = 0, float branchProbabilityArg = 1, float subBranchProbabilityArg = 1, int drawLayersRuleArg = 0, bool useScaleXForScaleYArg = false, bool useScaleXForScaleZArg = false, int argMaxDelayFrames = 1000);
    void update();
    float getDelayedVal(const vector<float> & delayVector, const float & delayFrames);
    float getDelayed_offsetX(const float & delayFrames);
    float getDelayed_offsetY(const float & delayFrames);
    float getDelayed_offsetZ(const float & delayFrames);
    float getDelayed_anchorX(const float & delayFrames);
    float getDelayed_anchorY(const float & delayFrames);
    float getDelayed_anchorZ(const float & delayFrames);
    float getDelayed_scaleX(const float & delayFrames);
    float getDelayed_scaleXLevelDelta(const float & delayFrames);
    float getDelayed_scaleXRandom(const float & delayFrames);
    float getDelayed_scaleY(const float & delayFrames);
    float getDelayed_scaleYLevelDelta(const float & delayFrames);
    float getDelayed_scaleYRandom(const float & delayFrames);
    float getDelayed_scaleZ(const float & delayFrames);
    float getDelayed_scaleZLevelDelta(const float & delayFrames);
    float getDelayed_scaleZRandom(const float & delayFrames);
    float getDelayed_rotateAxisX(const float & delayFrames);
    float getDelayed_rotateAxisY(const float & delayFrames);
    float getDelayed_rotateAxisZ(const float & delayFrames);
    float getDelayed_angle(const float & delayFrames);
    float getDelayed_angleLevelDelta(const float & delayFrames);
    float getDelayed_angleRandom(const float & delayFrames);

//    // archive methods
//    NSMutableDictionary * getDictionary();
//    void setFromDictionary(NSMutableDictionary * dataArg);

    // parameters
    
    ofPtr<TXModParamBool> branchIfTopLevel;
    ofPtr<TXModParamBool> drawBottomLevelOnly;
    ofPtr<TXModParamBool> applyOffsetLast;
    ofPtr<TXModParamInt> fractalBranchRule;
	ofPtr<TXModParamInt> fractalBranchRuleComparator;
    
    ofPtr<TXModParamInt> drawLayersRule;
    ofPtr<TXModParamFloat> offsetX;
    ofPtr<TXModParamFloat> offsetY;
    ofPtr<TXModParamFloat> offsetZ;
    ofPtr<TXModParamFloat> anchorX;
    ofPtr<TXModParamFloat> anchorY;
    ofPtr<TXModParamFloat> anchorZ;
    ofParameter<bool> useScaleXForScaleY;
    ofParameter<bool> useScaleXForScaleZ;
    ofPtr<TXModParamFloat> scaleX;
    ofPtr<TXModParamFloat> scaleXLevelDelta;
    ofPtr<TXModParamFloat> scaleXRandom;
    ofPtr<TXModParamFloat> scaleY;
    ofPtr<TXModParamFloat> scaleYLevelDelta;
    ofPtr<TXModParamFloat> scaleYRandom;
    ofPtr<TXModParamFloat> scaleZ;
    ofPtr<TXModParamFloat> scaleZLevelDelta;
    ofPtr<TXModParamFloat> scaleZRandom;
    ofPtr<TXModParamFloat> rotateAxisX;
    ofPtr<TXModParamFloat> rotateAxisY;
    ofPtr<TXModParamFloat> rotateAxisZ;
    ofPtr<TXModParamFloat> angle;
    ofPtr<TXModParamFloat> angleLevelDelta;
    ofPtr<TXModParamFloat> angleRandom;
    ofPtr<TXModParamFloat> branchProbability;
    ofPtr<TXModParamFloat> subBranchProbability;

    // delays
    vector<float> offsetXDelay;
    vector<float> offsetYDelay;
    vector<float> offsetZDelay;
    vector<float> anchorXDelay;
    vector<float> anchorYDelay;
    vector<float> anchorZDelay;
    vector<float> scaleXDelay;
    vector<float> scaleXLevelDeltaDelay;
    vector<float> scaleXRandomDelay;
    vector<float> scaleYDelay;
    vector<float> scaleYLevelDeltaDelay;
    vector<float> scaleYRandomDelay;
    vector<float> scaleZDelay;
    vector<float> scaleZLevelDeltaDelay;
    vector<float> scaleZRandomDelay;
    vector<float> rotateAxisXDelay;
    vector<float> rotateAxisYDelay;
    vector<float> rotateAxisZDelay;
    vector<float> angleDelay;
    vector<float> angleLevelDeltaDelay;
    vector<float> angleRandomDelay;

private:
    
    int currentDelayFrame = 0;
    int maxDelayFrames = 1000; // default 1000
};









