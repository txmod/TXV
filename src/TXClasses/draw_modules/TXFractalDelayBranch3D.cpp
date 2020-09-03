/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXDrawLayersBase.h"
#include "TXFractalDelayBranch3D.h"

// properties

// constructor
TXFractalDelayBranch3D::TXFractalDelayBranch3D () {
    setup ();
};

// methods
void TXFractalDelayBranch3D::setup (string nameArg, bool branchIfTopLevelArg, int fractalBranchRuleArg, int fractalBranchRuleComparatorArg, bool drawBottomLevelOnlyArg, bool applyOffsetLastArg, float offsetXArg, float offsetYArg, float offsetZArg, float anchorXArg, float anchorYArg, float anchorZArg, float scaleXArg, float scaleXLevelDeltaArg, float scaleXRandomArg, float scaleYArg, float scaleYLevelDeltaArg, float scaleYRandomArg, float scaleZArg, float scaleZLevelDeltaArg, float scaleZRandomArg, float angleArg, float angleLevelDeltaArg, float rotateAxisXArg, float rotateAxisYArg, float rotateAxisZArg, float angleRandomArg, float branchProbabilityArg, float subBranchProbabilityArg, int drawLayersRuleArg, bool useScaleXForScaleYArg, bool useScaleXForScaleZArg, int argMaxDelayFrames) {
    
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    clearParameters();
    
    parameters.setName(nameArg);

    // create bool parameters
    holdModParamBoolArgs.name = nameArg + "_branchIfTopLevel";
    holdModParamBoolArgs.fixedValue = branchIfTopLevelArg;
	branchIfTopLevel = createModParameter(holdModParamBoolArgs);
    parameters.add(branchIfTopLevel->parameters);
    
    holdModParamBoolArgs.name = nameArg + "_drawBottomLevelOnly";
    holdModParamBoolArgs.fixedValue = drawBottomLevelOnlyArg;
	drawBottomLevelOnly = createModParameter(holdModParamBoolArgs);
    parameters.add(drawBottomLevelOnly->parameters);
    
    holdModParamBoolArgs.name = nameArg + "_applyOffsetLast";
    holdModParamBoolArgs.fixedValue = applyOffsetLastArg;
	applyOffsetLast = createModParameter(holdModParamBoolArgs);
    parameters.add(applyOffsetLast->parameters);
    
    // create int parameters
    holdModParamIntArgs.name = nameArg + "_branchRule";
    holdModParamIntArgs.fixedValue = fractalBranchRuleArg;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 4;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 4;
	fractalBranchRule = createModParameter(holdModParamIntArgs);
    parameters.add(fractalBranchRule->parameters);
    
    holdModParamIntArgs.name = nameArg + "_branchRuleComparator";
    holdModParamIntArgs.fixedValue = fractalBranchRuleComparatorArg;
    holdModParamIntArgs.hardMin = 1;
    holdModParamIntArgs.hardMax = 10;
    holdModParamIntArgs.softMin = 1;
    holdModParamIntArgs.softMax = 10;
	fractalBranchRuleComparator = createModParameter(holdModParamIntArgs);
    parameters.add(fractalBranchRuleComparator->parameters);
    
    holdModParamIntArgs.name = nameArg + "_drawLayersRule";
    holdModParamIntArgs.fixedValue = drawLayersRuleArg;
    holdModParamIntArgs.hardMin = TXDRAWLAYERSRULE_ALLEXCEPT20;
    holdModParamIntArgs.hardMax = TXDRAWLAYERSRULE_TOTAL - 1;
    holdModParamIntArgs.softMin = TXDRAWLAYERSRULE_ALLEXCEPT20;
    holdModParamIntArgs.softMax = TXDRAWLAYERSRULE_TOTAL - 1;
	drawLayersRule = createModParameter(holdModParamIntArgs);
    parameters.add(drawLayersRule->parameters);
    
    // create float parameters
    holdModParamFloatArgs.name = nameArg + "_offsetX";
    holdModParamFloatArgs.fixedValue = offsetXArg;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -10.0;
    holdModParamFloatArgs.softMax = 10.0;
	offsetX = createModParameter(holdModParamFloatArgs);
    parameters.add(offsetX->parameters);
    
    holdModParamFloatArgs.name = nameArg + "_offsetY";
    holdModParamFloatArgs.fixedValue = offsetYArg;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -10.0;
    holdModParamFloatArgs.softMax = 10.0;
	offsetY = createModParameter(holdModParamFloatArgs);
    parameters.add(offsetY->parameters);
    
    holdModParamFloatArgs.name = nameArg + "_offsetZ";
    holdModParamFloatArgs.fixedValue = offsetZArg;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = -10.0;
    holdModParamFloatArgs.softMax = 10.0;
	offsetZ = createModParameter(holdModParamFloatArgs);
    parameters.add(offsetZ->parameters);
    
    holdModParamFloatArgs.name = nameArg + "_anchorX";
    holdModParamFloatArgs.fixedValue = anchorXArg;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	anchorX = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorX->parameters);
    
    holdModParamFloatArgs.name = nameArg + "_anchorY";
    holdModParamFloatArgs.fixedValue = anchorYArg;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	anchorY = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorY->parameters);
    
    holdModParamFloatArgs.name = nameArg + "_anchorZ";
    holdModParamFloatArgs.fixedValue = anchorZArg;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	anchorZ = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorZ->parameters);
    
    parameters.add(useScaleXForScaleY.set(nameArg + "_useScaleXForScaleY", useScaleXForScaleYArg));
    parameters.add(useScaleXForScaleZ.set(nameArg + "_useScaleXForScaleZ", useScaleXForScaleZArg));
    
    holdModParamFloatArgs.name = nameArg + "_scaleX";
    holdModParamFloatArgs.fixedValue = scaleXArg;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 2.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 2.0;
	scaleX = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleX->parameters);
    
    holdModParamFloatArgs.name = nameArg + "_scaleXLevelDelta";
    holdModParamFloatArgs.fixedValue = scaleYLevelDeltaArg;
    holdModParamFloatArgs.hardMin = -1.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
	scaleXLevelDelta = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleXLevelDelta->parameters);
    
    holdModParamFloatArgs.name = nameArg + "_scaleXRandom";
    holdModParamFloatArgs.fixedValue = scaleXRandomArg;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	scaleXRandom = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleXRandom->parameters);
    
    holdModParamFloatArgs.name = nameArg + "_scaleY";
    holdModParamFloatArgs.fixedValue = scaleYArg;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 2.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 2.0;
	scaleY = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleY->parameters);
    
    holdModParamFloatArgs.name = nameArg + "_scaleYLevelDelta";
    holdModParamFloatArgs.fixedValue = scaleYLevelDeltaArg;
    holdModParamFloatArgs.hardMin = -1.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
	scaleYLevelDelta = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleYLevelDelta->parameters);
    
    holdModParamFloatArgs.name = nameArg + "_scaleYRandom";
    holdModParamFloatArgs.fixedValue = scaleYRandomArg;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	scaleYRandom = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleYRandom->parameters);
    
    holdModParamFloatArgs.name = nameArg + "_scaleZ";
    holdModParamFloatArgs.fixedValue = scaleZArg;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 2.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 2.0;
	scaleZ = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleZ->parameters);
    
    holdModParamFloatArgs.name = nameArg + "_scaleZLevelDelta";
    holdModParamFloatArgs.fixedValue = scaleZLevelDeltaArg;
    holdModParamFloatArgs.hardMin = -1.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
	scaleZLevelDelta = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleZLevelDelta->parameters);
    
    holdModParamFloatArgs.name = nameArg + "_scaleZRandom";
    holdModParamFloatArgs.fixedValue = scaleZRandomArg;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	scaleZRandom = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleZRandom->parameters);
    
    holdModParamFloatArgs.name = nameArg + "_rotateAxisX";
    holdModParamFloatArgs.fixedValue = rotateAxisXArg;
    holdModParamFloatArgs.hardMin = -1.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
	rotateAxisX = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateAxisX->parameters);
    
    holdModParamFloatArgs.name = nameArg + "_rotateAxisY";
    holdModParamFloatArgs.fixedValue = rotateAxisYArg;
    holdModParamFloatArgs.hardMin = -1.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
	rotateAxisY = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateAxisY->parameters);
    
    holdModParamFloatArgs.name = nameArg + "_rotateAxisZ";
    holdModParamFloatArgs.fixedValue = rotateAxisZArg;
    holdModParamFloatArgs.hardMin = -1.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 1.0;
	rotateAxisZ = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateAxisZ->parameters);
    
    holdModParamFloatArgs.name = nameArg + "_angle";
    holdModParamFloatArgs.fixedValue = angleArg;
    holdModParamFloatArgs.hardMin = -720.0;
    holdModParamFloatArgs.hardMax = 720.0;
    holdModParamFloatArgs.softMin = -180.0;
    holdModParamFloatArgs.softMax = 180.0;
	angle = createModParameter(holdModParamFloatArgs);
    parameters.add(angle->parameters);
    
    holdModParamFloatArgs.name = nameArg + "_angleLevelDelta";
    holdModParamFloatArgs.fixedValue = angleLevelDeltaArg;
    holdModParamFloatArgs.hardMin = -180.0;
    holdModParamFloatArgs.hardMax = 180.0;
    holdModParamFloatArgs.softMin = -180.0;
    holdModParamFloatArgs.softMax = 180.0;
	angleLevelDelta = createModParameter(holdModParamFloatArgs);
    parameters.add(angleLevelDelta->parameters);
    
    holdModParamFloatArgs.name = nameArg + "_angleRandom";
    holdModParamFloatArgs.fixedValue = angleRandomArg;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	angleRandom = createModParameter(holdModParamFloatArgs);
    parameters.add(angleRandom->parameters);
    
    holdModParamFloatArgs.name = nameArg + "_branchProbability";
    holdModParamFloatArgs.fixedValue = branchProbabilityArg;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	branchProbability = createModParameter(holdModParamFloatArgs);
    parameters.add(branchProbability->parameters);
    
    holdModParamFloatArgs.name = nameArg + "_subBranchProbability";
    holdModParamFloatArgs.fixedValue = subBranchProbabilityArg;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    subBranchProbability = createModParameter(holdModParamFloatArgs);
    parameters.add(subBranchProbability->parameters);
    
    maxDelayFrames = argMaxDelayFrames;
    
    // Add delays
    offsetXDelay.assign(maxDelayFrames, 0.0);
    offsetYDelay.assign(maxDelayFrames, 0.0);
    offsetZDelay.assign(maxDelayFrames, 0.0);
    anchorXDelay.assign(maxDelayFrames, 0.0);
    anchorYDelay.assign(maxDelayFrames, 0.0);
    anchorZDelay.assign(maxDelayFrames, 0.0);
    scaleXDelay.assign(maxDelayFrames, 0.0);
    scaleXLevelDeltaDelay.assign(maxDelayFrames, 0.0);
    scaleXRandomDelay.assign(maxDelayFrames, 0.0);
    scaleYDelay.assign(maxDelayFrames, 0.0);
    scaleYLevelDeltaDelay.assign(maxDelayFrames, 0.0);
    scaleYRandomDelay.assign(maxDelayFrames, 0.0);
    scaleZDelay.assign(maxDelayFrames, 0.0);
    scaleZLevelDeltaDelay.assign(maxDelayFrames, 0.0);
    scaleZRandomDelay.assign(maxDelayFrames, 0.0);
    rotateAxisXDelay.assign(maxDelayFrames, 0.0);
    rotateAxisYDelay.assign(maxDelayFrames, 0.0);
    rotateAxisZDelay.assign(maxDelayFrames, 0.0);
    angleDelay.assign(maxDelayFrames, 0.0);
    angleLevelDeltaDelay.assign(maxDelayFrames, 0.0);
    angleRandomDelay.assign(maxDelayFrames, 0.0);
    
};

void TXFractalDelayBranch3D::update() {
    // update delays
    currentDelayFrame = (currentDelayFrame + 1) % maxDelayFrames;
    offsetXDelay[currentDelayFrame] = offsetX->getFloat();
    offsetYDelay[currentDelayFrame] = offsetY->getFloat();
    offsetZDelay[currentDelayFrame] = offsetZ->getFloat();
    anchorXDelay[currentDelayFrame] = anchorX->getFloat();
    anchorYDelay[currentDelayFrame] = anchorY->getFloat();
    anchorZDelay[currentDelayFrame] = anchorZ->getFloat();
    scaleXDelay[currentDelayFrame] = scaleX->getFloat();
    scaleXLevelDeltaDelay[currentDelayFrame] = scaleXLevelDelta->getFloat();
    scaleXRandomDelay[currentDelayFrame] = scaleXRandom->getFloat();
    scaleYDelay[currentDelayFrame] = scaleY->getFloat();
    scaleYLevelDeltaDelay[currentDelayFrame] = scaleYLevelDelta->getFloat();
    scaleYRandomDelay[currentDelayFrame] = scaleYRandom->getFloat();
    scaleZDelay[currentDelayFrame] = scaleZ->getFloat();
    scaleZLevelDeltaDelay[currentDelayFrame] = scaleZLevelDelta->getFloat();
    scaleZRandomDelay[currentDelayFrame] = scaleZRandom->getFloat();
    rotateAxisXDelay[currentDelayFrame] = rotateAxisX->getFloat();
    rotateAxisYDelay[currentDelayFrame] = rotateAxisY->getFloat();
    rotateAxisZDelay[currentDelayFrame] = rotateAxisZ->getFloat();
    angleDelay[currentDelayFrame] = angle->getFloat();
    angleLevelDeltaDelay[currentDelayFrame] = angleLevelDelta->getFloat();
    angleRandomDelay[currentDelayFrame] = angleRandom->getFloat();
};

float TXFractalDelayBranch3D::getDelayedVal(const vector<float> & delayVector, const float & delayFrames) {
    int index1, index2;
    float frameNo, proportion, outval;
    frameNo = fmod(maxDelayFrames + currentDelayFrame - delayFrames, (float) maxDelayFrames);
    index1 = ((int) frameNo) % maxDelayFrames;
    index2 = (index1 + 1) % maxDelayFrames;
    proportion = frameNo - index1;
    outval = ofLerp(delayVector[index1], delayVector[index2], proportion);
    return outval;
}

float TXFractalDelayBranch3D::getDelayed_offsetX(const float & delayFrames) {
    float outval;
    outval = getDelayedVal(offsetXDelay, delayFrames);
    return outval;
}

float TXFractalDelayBranch3D::getDelayed_offsetY(const float & delayFrames) {
    float outval;
    outval = getDelayedVal(offsetYDelay, delayFrames);
    return outval;
}

float TXFractalDelayBranch3D::getDelayed_offsetZ(const float & delayFrames) {
    float outval;
    outval = getDelayedVal(offsetZDelay, delayFrames);
    return outval;
}

float TXFractalDelayBranch3D::getDelayed_anchorX(const float & delayFrames) {
    float outval;
    outval = getDelayedVal(anchorXDelay, delayFrames);
    return outval;
}

float TXFractalDelayBranch3D::getDelayed_anchorY(const float & delayFrames) {
    float outval;
    outval = getDelayedVal(anchorYDelay, delayFrames);
    return outval;
}

float TXFractalDelayBranch3D::getDelayed_anchorZ(const float & delayFrames) {
    float outval;
    outval = getDelayedVal(anchorZDelay, delayFrames);
    return outval;
}

float TXFractalDelayBranch3D::getDelayed_scaleX(const float & delayFrames) {
    float outval;
    outval = getDelayedVal(scaleXDelay, delayFrames);
    return outval;
}

float TXFractalDelayBranch3D::getDelayed_scaleXLevelDelta(const float & delayFrames) {
    float outval;
    outval = getDelayedVal(scaleXLevelDeltaDelay, delayFrames);
    return outval;
}

float TXFractalDelayBranch3D::getDelayed_scaleXRandom(const float & delayFrames) {
    float outval;
    outval = getDelayedVal(scaleXRandomDelay, delayFrames);
    return outval;
}

float TXFractalDelayBranch3D::getDelayed_scaleY(const float & delayFrames) {
    float outval;
    outval = getDelayedVal(scaleYDelay, delayFrames);
    return outval;
}

float TXFractalDelayBranch3D::getDelayed_scaleYLevelDelta(const float & delayFrames) {
    float outval;
    outval = getDelayedVal(scaleYLevelDeltaDelay, delayFrames);
    return outval;
}

float TXFractalDelayBranch3D::getDelayed_scaleYRandom(const float & delayFrames) {
    float outval;
    outval = getDelayedVal(scaleYRandomDelay, delayFrames);
    return outval;
}

float TXFractalDelayBranch3D::getDelayed_scaleZ(const float & delayFrames) {
    float outval;
    outval = getDelayedVal(scaleZDelay, delayFrames);
    return outval;
}

float TXFractalDelayBranch3D::getDelayed_scaleZLevelDelta(const float & delayFrames) {
    float outval;
    outval = getDelayedVal(scaleZLevelDeltaDelay, delayFrames);
    return outval;
}

float TXFractalDelayBranch3D::getDelayed_scaleZRandom(const float & delayFrames) {
    float outval;
    outval = getDelayedVal(scaleZRandomDelay, delayFrames);
    return outval;
}

float TXFractalDelayBranch3D::getDelayed_rotateAxisX(const float & delayFrames) {
    float outval;
    outval = getDelayedVal(rotateAxisXDelay, delayFrames);
    return outval;
}

float TXFractalDelayBranch3D::getDelayed_rotateAxisY(const float & delayFrames) {
    float outval;
    outval = getDelayedVal(rotateAxisYDelay, delayFrames);
    return outval;
}

float TXFractalDelayBranch3D::getDelayed_rotateAxisZ(const float & delayFrames) {
    float outval;
    outval = getDelayedVal(rotateAxisZDelay, delayFrames);
    return outval;
}

float TXFractalDelayBranch3D::getDelayed_angle(const float & delayFrames) {
    float outval;
    outval = getDelayedVal(angleDelay, delayFrames);
    return outval;
}

float TXFractalDelayBranch3D::getDelayed_angleLevelDelta(const float & delayFrames) {
    float outval;
    outval = getDelayedVal(angleLevelDeltaDelay, delayFrames);
    return outval;
}

float TXFractalDelayBranch3D::getDelayed_angleRandom(const float & delayFrames) {
    float outval;
    outval = getDelayedVal(angleRandomDelay, delayFrames);
    return outval;
}

//////////////////////////////////////////////////////////////

//NSMutableDictionary * TXFractalDelayBranch3D::getDictionary() {
//    NSMutableDictionary * dictionary;
//    dictionary = [NSMutableDictionary dictionary];
//    NSNumber * holdNum;
//    
//    //add data
//    holdNum = [NSNumber numberWithBool:branchIfTopLevel];
//    [dictionary setObject: holdNum forKey: @"branchIfTopLevel"];
//    holdNum = [NSNumber numberWithInt:fractalBranchRule];
//    [dictionary setObject: holdNum forKey: @"fractalBranchRule"];
//    holdNum = [NSNumber numberWithInt:fractalBranchRuleComparator];
//    [dictionary setObject: holdNum forKey: @"fractalBranchRuleComparator"];
//    holdNum = [NSNumber numberWithBool:drawBottomLevelOnly];
//    [dictionary setObject: holdNum forKey: @"drawBottomLevelOnly"];
//    holdNum = [NSNumber numberWithBool:applyOffsetLast];
//    [dictionary setObject: holdNum forKey: @"applyOffsetLast"];
//    holdNum = [NSNumber numberWithFloat:offsetX];
//    [dictionary setObject: holdNum forKey: @"offsetX"];
//    holdNum = [NSNumber numberWithFloat:offsetY];
//    [dictionary setObject: holdNum forKey: @"offsetY"];
//    holdNum = [NSNumber numberWithFloat:anchorX];
//    [dictionary setObject: holdNum forKey: @"anchorX"];
//    holdNum = [NSNumber numberWithFloat:anchorY];
//    [dictionary setObject: holdNum forKey: @"anchorY"];
//    holdNum = [NSNumber numberWithFloat:scaleX];
//    [dictionary setObject: holdNum forKey: @"scaleX"];
//    holdNum = [NSNumber numberWithFloat:scaleXLevelDelta];
//    [dictionary setObject: holdNum forKey: @"scaleXLevelDelta"];
//    holdNum = [NSNumber numberWithFloat:scaleXRandom];
//    [dictionary setObject: holdNum forKey: @"scaleXRandom"];
//    holdNum = [NSNumber numberWithFloat:scaleY];
//    [dictionary setObject: holdNum forKey: @"scaleY"];
//    holdNum = [NSNumber numberWithFloat:scaleYLevelDelta];
//    [dictionary setObject: holdNum forKey: @"scaleYLevelDelta"];
//    holdNum = [NSNumber numberWithFloat:scaleYRandom];
//    [dictionary setObject: holdNum forKey: @"scaleYRandom"];
//    holdNum = [NSNumber numberWithFloat:angle];
//    [dictionary setObject: holdNum forKey: @"angle"];
//    holdNum = [NSNumber numberWithFloat:angleLevelDelta];
//    [dictionary setObject: holdNum forKey: @"angleLevelDelta"];
//    holdNum = [NSNumber numberWithFloat:angleRandom];
//    [dictionary setObject: holdNum forKey: @"angleRandom"];
//    holdNum = [NSNumber numberWithFloat:branchProbability];
//    [dictionary setObject: holdNum forKey: @"branchProbability"];
//    holdNum = [NSNumber numberWithFloat:subBranchProbability];
//    [dictionary setObject: holdNum forKey: @"subBranchProbability"];
//    return dictionary;
//}
//
//void TXFractalDelayBranch3D::setFromDictionary(NSMutableDictionary * dictionaryArg) {
//    NSNumber * holdNum;
//
//    //get data
//    holdNum = [dictionaryArg objectForKey: @"branchIfTopLevel"];
//    if (holdNum != nil) {
//        branchIfTopLevel = [holdNum boolValue];    
//    };
//    holdNum = [dictionaryArg objectForKey: @"fractalBranchRule"];
//    if (holdNum != nil) {
//        fractalBranchRule = [holdNum intValue];    
//    };
//    holdNum = [dictionaryArg objectForKey: @"fractalBranchRuleComparator"];
//    if (holdNum != nil) {
//        fractalBranchRuleComparator = [holdNum intValue];    
//    };
//    holdNum = [dictionaryArg objectForKey: @"drawBottomLevelOnly"];
//    if (holdNum != nil) {
//        drawBottomLevelOnly = [holdNum boolValue];    
//    };
//    holdNum = [dictionaryArg objectForKey: @"applyOffsetLast"];
//    if (holdNum != nil) {
//        applyOffsetLast = [holdNum boolValue];    
//    };
//    holdNum = [dictionaryArg objectForKey: @"offsetX"];
//    if (holdNum != nil) {
//        offsetX = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"offsetY"];
//    if (holdNum != nil) {
//        offsetY = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"anchorX"];
//    if (holdNum != nil) {
//        anchorX = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"anchorY"];
//    if (holdNum != nil) {
//        anchorY = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"scaleX"];
//    if (holdNum != nil) {
//        scaleX = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"scaleXLevelDelta"];
//    if (holdNum != nil) {
//        scaleXLevelDelta = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"scaleXRandom"];
//    if (holdNum != nil) {
//        scaleXRandom = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"scaleY"];
//    if (holdNum != nil) {
//        scaleY = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"scaleYLevelDelta"];
//    if (holdNum != nil) {
//        scaleYLevelDelta = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"scaleYRandom"];
//    if (holdNum != nil) {
//        scaleYRandom = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"angle"];
//    if (holdNum != nil) {
//        angle = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"angleLevelDelta"];
//    if (holdNum != nil) {
//        angleLevelDelta = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"angleRandom"];
//    if (holdNum != nil) {
//        angleRandom = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"branchProbability"];
//    if (holdNum != nil) {
//        branchProbability = [holdNum floatValue];
//    };
//    holdNum = [dictionaryArg objectForKey: @"subBranchProbability"];
//    if (holdNum != nil) {
//        subBranchProbability = [holdNum floatValue];
//    };
//}


