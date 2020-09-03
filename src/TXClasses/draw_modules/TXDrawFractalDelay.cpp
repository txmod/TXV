/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXDrawFractalDelay.h"

TXDrawFractalDelay::TXDrawFractalDelay() {
    setup();
}

void TXDrawFractalDelay::setup(){
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    // create input paramaters
    initialiseParameters();
    
    holdModParamIntArgs.name = "fractalTreeLevels";
    holdModParamIntArgs.fixedValue = 2;
    holdModParamIntArgs.hardMin = 1;
    holdModParamIntArgs.hardMax = 10;
    holdModParamIntArgs.softMin = 1;
    holdModParamIntArgs.softMax = 10;
	fractalTreeLevels = createModParameter(holdModParamIntArgs);
    parameters.add(fractalTreeLevels->parameters);
    
    holdModParamIntArgs.name = "fractalTreeBranches";
    holdModParamIntArgs.fixedValue = 2;
    holdModParamIntArgs.hardMin = 1;
    holdModParamIntArgs.hardMax = 10;
    holdModParamIntArgs.softMin = 1;
    holdModParamIntArgs.softMax = 10;
	fractalTreeBranches = createModParameter(holdModParamIntArgs);
    parameters.add(fractalTreeBranches->parameters);
    
    holdModParamFloatArgs.name = "cellWidth";
    holdModParamFloatArgs.fixedValue = 0.2;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	cellWidth = createModParameter(holdModParamFloatArgs);
    parameters.add(cellWidth->parameters);
    
    holdModParamFloatArgs.name = "cellHeight";
    holdModParamFloatArgs.fixedValue = 0.2;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	cellHeight = createModParameter(holdModParamFloatArgs);
    parameters.add(cellHeight->parameters);
    
    holdModParamIntArgs.name = "randomSeed";
    holdModParamIntArgs.fixedValue = 100;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 10000;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 10000;
	randomSeed = createModParameter(holdModParamIntArgs);
    parameters.add(randomSeed->parameters);
    
    holdModParamIntArgs.name = "maxLevelDelayFrames";
    holdModParamIntArgs.fixedValue = 60;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = maxDelayFrames;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 100;
    maxLevelDelayFrames = createModParameter(holdModParamIntArgs);
    parameters.add(maxLevelDelayFrames->parameters);
    
    holdModParamFloatArgs.name = "level1DelayRatio";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    level1DelayRatio = createModParameter(holdModParamFloatArgs);
    parameters.add(level1DelayRatio->parameters);
    
    holdModParamFloatArgs.name = "level2DelayRatio";
    holdModParamFloatArgs.fixedValue = 0.11111;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    level2DelayRatio = createModParameter(holdModParamFloatArgs);
    parameters.add(level2DelayRatio->parameters);
    
    holdModParamFloatArgs.name = "level3DelayRatio";
    holdModParamFloatArgs.fixedValue = 0.22222;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    level3DelayRatio = createModParameter(holdModParamFloatArgs);
    parameters.add(level3DelayRatio->parameters);
    
    holdModParamFloatArgs.name = "level4DelayRatio";
    holdModParamFloatArgs.fixedValue = 0.33333;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    level4DelayRatio = createModParameter(holdModParamFloatArgs);
    parameters.add(level4DelayRatio->parameters);
    
    holdModParamFloatArgs.name = "level5DelayRatio";
    holdModParamFloatArgs.fixedValue = 0.44444;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    level5DelayRatio = createModParameter(holdModParamFloatArgs);
    parameters.add(level5DelayRatio->parameters);
    
    holdModParamFloatArgs.name = "level6DelayRatio";
    holdModParamFloatArgs.fixedValue = 0.555555;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    level6DelayRatio = createModParameter(holdModParamFloatArgs);
    parameters.add(level6DelayRatio->parameters);
    
    holdModParamFloatArgs.name = "level7DelayRatio";
    holdModParamFloatArgs.fixedValue = 0.66666;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    level7DelayRatio = createModParameter(holdModParamFloatArgs);
    parameters.add(level7DelayRatio->parameters);
    
    holdModParamFloatArgs.name = "level8DelayRatio";
    holdModParamFloatArgs.fixedValue = 0.77777;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    level8DelayRatio = createModParameter(holdModParamFloatArgs);
    parameters.add(level8DelayRatio->parameters);
    
    holdModParamFloatArgs.name = "level9DelayRatio";
    holdModParamFloatArgs.fixedValue = 0.88888;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    level9DelayRatio = createModParameter(holdModParamFloatArgs);
    parameters.add(level9DelayRatio->parameters);
    
    holdModParamFloatArgs.name = "level10DelayRatio";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    level10DelayRatio = createModParameter(holdModParamFloatArgs);
    parameters.add(level10DelayRatio->parameters);
    
    holdModParamFloatArgs.name = "level1RandDelayMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    level1RandDelayMix = createModParameter(holdModParamFloatArgs);
    parameters.add(level1RandDelayMix->parameters);
    
    holdModParamFloatArgs.name = "level2RandDelayMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    level2RandDelayMix = createModParameter(holdModParamFloatArgs);
    parameters.add(level2RandDelayMix->parameters);
    
    holdModParamFloatArgs.name = "level3RandDelayMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    level3RandDelayMix = createModParameter(holdModParamFloatArgs);
    parameters.add(level3RandDelayMix->parameters);
    
    holdModParamFloatArgs.name = "level4RandDelayMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    level4RandDelayMix = createModParameter(holdModParamFloatArgs);
    parameters.add(level4RandDelayMix->parameters);
    
    holdModParamFloatArgs.name = "level5RandDelayMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    level5RandDelayMix = createModParameter(holdModParamFloatArgs);
    parameters.add(level5RandDelayMix->parameters);
    
    holdModParamFloatArgs.name = "level6RandDelayMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    level6RandDelayMix = createModParameter(holdModParamFloatArgs);
    parameters.add(level6RandDelayMix->parameters);
    
    holdModParamFloatArgs.name = "level7RandDelayMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    level7RandDelayMix = createModParameter(holdModParamFloatArgs);
    parameters.add(level7RandDelayMix->parameters);
    
    holdModParamFloatArgs.name = "level8RandDelayMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    level8RandDelayMix = createModParameter(holdModParamFloatArgs);
    parameters.add(level8RandDelayMix->parameters);
    
    holdModParamFloatArgs.name = "level9RandDelayMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    level9RandDelayMix = createModParameter(holdModParamFloatArgs);
    parameters.add(level9RandDelayMix->parameters);
    
    holdModParamFloatArgs.name = "level10RandDelayMix";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    level10RandDelayMix = createModParameter(holdModParamFloatArgs);
    parameters.add(level10RandDelayMix->parameters);
    
    arrFractalBranches[0].setup("branch01");
    arrFractalBranches[1].setup("branch02");
    arrFractalBranches[2].setup("branch03");
    arrFractalBranches[3].setup("branch04");
    arrFractalBranches[4].setup("branch05");
    arrFractalBranches[5].setup("branch06");
    arrFractalBranches[6].setup("branch07");
    arrFractalBranches[7].setup("branch08");
    arrFractalBranches[8].setup("branch09");
    arrFractalBranches[9].setup("branch10");

    mergeParameters(arrFractalBranches[0].parameters, arrFractalBranches[0].modParameters);
    mergeParameters(arrFractalBranches[1].parameters, arrFractalBranches[1].modParameters);
    mergeParameters(arrFractalBranches[2].parameters, arrFractalBranches[2].modParameters);
    mergeParameters(arrFractalBranches[3].parameters, arrFractalBranches[3].modParameters);
    mergeParameters(arrFractalBranches[4].parameters, arrFractalBranches[4].modParameters);
    mergeParameters(arrFractalBranches[5].parameters, arrFractalBranches[5].modParameters);
    mergeParameters(arrFractalBranches[6].parameters, arrFractalBranches[6].modParameters);
    mergeParameters(arrFractalBranches[7].parameters, arrFractalBranches[7].modParameters);
    mergeParameters(arrFractalBranches[8].parameters, arrFractalBranches[8].modParameters);
    mergeParameters(arrFractalBranches[9].parameters, arrFractalBranches[9].modParameters);
}

void TXDrawFractalDelay::update() {
    for (int branchNo = 0; branchNo < numFractalBranches; branchNo++){
        arrFractalBranches[branchNo].update();
    };
};

void TXDrawFractalDelay::draw(){
    if (!drawActive->getBool()) {
        return;
    };
    ofPushMatrix();
    // reset random seed
    srand(randomSeed->getInt());
    // draw branch
    drawFractalBranch(fractalTreeLevels->getInt());
    ofPopMatrix();
}

void TXDrawFractalDelay::drawFractalBranch(int levelArg) {
    float holdOffsetX, holdOffsetY, holdAngle, holdScaleX, holdScaleY, holdLevelDelayFrames;
    float holdBranchRandom, holdSubBranchRandom, holdAngleRandom, holdScaleXRandom, holdScaleYRandom, holdDelayRandom;
    bool  makeBranch;
    float holdAnchorX;
    float holdAnchorY;
    int holdDrawLayersRule;    
    float holdScaleXDelay;
    float holdScaleXLevelDeltaDelay;
    float holdScaleXRandomDelay;
    float holdScaleYDelay;
    float holdScaleYLevelDeltaDelay;
    float holdScaleYRandomDelay;
    float holdAngleDelay;
    float holdAngleLevelDeltaDelay;
    float holdAngleRandomDelay;
    
    // levelArg  = 0 ends recursion
    if (levelArg > 0) {
        for (int branchNo = 0; branchNo < fractalTreeBranches->getInt(); branchNo++){
            // update rand vals
            holdBranchRandom = (rand() % 1000) * 0.001;
            holdSubBranchRandom = (rand() % 1000) * 0.001;
            holdAngleRandom = (rand() % 1000) * 0.001;
            holdScaleXRandom = (rand() % 1000) * 0.001;
            holdScaleYRandom = (rand() % 1000) * 0.001;
            holdDelayRandom = (rand() % 1000) * 0.001;
            
            // check branch rule
            switch (arrFractalBranches[branchNo].fractalBranchRule->getInt()) {
                case TXFRACTALBRANCHRULE_ALWAYSBRANCH:
                    makeBranch = true;
                    break;
                case TXFRACTALBRANCHRULE_BRANCHIFGREATER:
                    if (levelArg > arrFractalBranches[branchNo].fractalBranchRuleComparator->getInt()) {
                        makeBranch = true;
                    } else {
                        makeBranch = false;
                    }
                    break;
                case TXFRACTALBRANCHRULE_BRANCHIFLESS:
                    if (levelArg < arrFractalBranches[branchNo].fractalBranchRuleComparator->getInt()) {
                        makeBranch = true;
                    } else {
                        makeBranch = false;
                    }
                    break;
                case TXFRACTALBRANCHRULE_BRANCHIFEQUAL:
                    if (levelArg == arrFractalBranches[branchNo].fractalBranchRuleComparator->getInt()) {
                        makeBranch = true;
                    } else {
                        makeBranch = false;
                    }
                    break;
                case TXFRACTALBRANCHRULE_BRANCHIFNOTEQUAL:
                    if (levelArg != arrFractalBranches[branchNo].fractalBranchRuleComparator->getInt()) {
                        makeBranch = true;
                    } else {
                        makeBranch = false;
                    }
                    break;
                default:
                    makeBranch = true;
                    break;
            }
            // check top level rule
            if (levelArg == fractalTreeLevels->getInt() && arrFractalBranches[branchNo].branchIfTopLevel->getBool() == false) {
                makeBranch = false;
            };
            
            // check whether to branch
            if (makeBranch && ((arrFractalBranches[branchNo].branchProbability->getFloat() + holdBranchRandom) >= 1) )  {

                // get delay for level
                switch (levelArg) {
                    case 1:
                        holdLevelDelayFrames = maxLevelDelayFrames->getInt()
                        * ofLerp(level1DelayRatio->getFloat(), holdDelayRandom, level1RandDelayMix->getFloat());
                        break;
                    case 2:
                        holdLevelDelayFrames = maxLevelDelayFrames->getInt()
                        * ofLerp(level2DelayRatio->getFloat(), holdDelayRandom, level2RandDelayMix->getFloat());
                        break;
                    case 3:
                        holdLevelDelayFrames = maxLevelDelayFrames->getInt()
                        * ofLerp(level3DelayRatio->getFloat(), holdDelayRandom, level3RandDelayMix->getFloat());
                        break;
                    case 4:
                        holdLevelDelayFrames = maxLevelDelayFrames->getInt()
                        * ofLerp(level4DelayRatio->getFloat(), holdDelayRandom, level4RandDelayMix->getFloat());
                        break;
                    case 5:
                        holdLevelDelayFrames = maxLevelDelayFrames->getInt()
                        * ofLerp(level5DelayRatio->getFloat(), holdDelayRandom, level5RandDelayMix->getFloat());
                        break;
                    case 6:
                        holdLevelDelayFrames = maxLevelDelayFrames->getInt()
                        * ofLerp(level6DelayRatio->getFloat(), holdDelayRandom, level6RandDelayMix->getFloat());
                        break;
                    case 7:
                        holdLevelDelayFrames = maxLevelDelayFrames->getInt()
                        * ofLerp(level7DelayRatio->getFloat(), holdDelayRandom, level7RandDelayMix->getFloat());
                        break;
                    case 8:
                        holdLevelDelayFrames = maxLevelDelayFrames->getInt()
                        * ofLerp(level8DelayRatio->getFloat(), holdDelayRandom, level8RandDelayMix->getFloat());
                        break;
                    case 9:
                        holdLevelDelayFrames = maxLevelDelayFrames->getInt()
                        * ofLerp(level9DelayRatio->getFloat(), holdDelayRandom, level9RandDelayMix->getFloat());
                        break;
                    case 10:
                        holdLevelDelayFrames = maxLevelDelayFrames->getInt()
                        * ofLerp(level10DelayRatio->getFloat(), holdDelayRandom, level10RandDelayMix->getFloat());
                        break;
                    default:
                        holdLevelDelayFrames = 0;
                        break;
                };
                
                /*
                // OLD
                holdOffsetX = arrFractalBranches[branchNo].offsetX->getFloat() * cellWidth->getFloat() * getMaxWidth();
                holdOffsetY = arrFractalBranches[branchNo].offsetY->getFloat() * cellHeight->getFloat() * getMaxHeight();
                holdAngle = arrFractalBranches[branchNo].angle->getFloat() + (levelArg * arrFractalBranches[branchNo].angleLevelDelta->getFloat()) + (arrFractalBranches[branchNo].angleRandom->getFloat() * 180 * ((holdAngleRandom * 2) -1) );
                holdScaleX = arrFractalBranches[branchNo].scaleX->getFloat() + (levelArg * arrFractalBranches[branchNo].scaleXLevelDelta->getFloat()) + (arrFractalBranches[branchNo].scaleXRandom->getFloat() * holdScaleXRandom);
                if (arrFractalBranches[branchNo].useScaleXForScaleY == true) {
                    holdScaleY = holdScaleX;
                } else {
                    holdScaleY = arrFractalBranches[branchNo].scaleY->getFloat() + (levelArg * arrFractalBranches[branchNo].scaleYLevelDelta->getFloat()) + (arrFractalBranches[branchNo].scaleYRandom->getFloat() * holdScaleYRandom);
                };
                holdAnchorX = getMaxWidth() * arrFractalBranches[branchNo].anchorX->getFloat();
                holdAnchorY = getMaxHeight() * arrFractalBranches[branchNo].anchorY->getFloat();
                 */
                
                holdOffsetX = arrFractalBranches[branchNo].getDelayed_offsetX(holdLevelDelayFrames) * cellWidth->getFloat() * getMaxWidth();
                holdOffsetY = arrFractalBranches[branchNo].getDelayed_offsetY(holdLevelDelayFrames) * cellHeight->getFloat() * getMaxHeight();
                holdAngleDelay = arrFractalBranches[branchNo].getDelayed_angle(holdLevelDelayFrames);
                holdAngleLevelDeltaDelay = arrFractalBranches[branchNo].getDelayed_angleLevelDelta(holdLevelDelayFrames);
                holdAngleRandomDelay = arrFractalBranches[branchNo].getDelayed_angleRandom(holdLevelDelayFrames);
                holdAngle = holdAngleDelay + (levelArg * holdAngleLevelDeltaDelay) + (holdAngleRandomDelay * 180 * ((holdAngleRandom * 2) -1) );
                holdScaleXDelay = arrFractalBranches[branchNo].getDelayed_scaleX(holdLevelDelayFrames);
                holdScaleXLevelDeltaDelay = arrFractalBranches[branchNo].getDelayed_scaleXLevelDelta(holdLevelDelayFrames);
                holdScaleXRandomDelay = arrFractalBranches[branchNo].getDelayed_scaleXRandom(holdLevelDelayFrames);
                holdScaleYDelay = arrFractalBranches[branchNo].getDelayed_scaleY(holdLevelDelayFrames);
                holdScaleYLevelDeltaDelay = arrFractalBranches[branchNo].getDelayed_scaleYLevelDelta(holdLevelDelayFrames);
                holdScaleYRandomDelay = arrFractalBranches[branchNo].getDelayed_scaleYRandom(holdLevelDelayFrames);
                holdScaleX = holdScaleXDelay + (levelArg * holdScaleXLevelDeltaDelay) + (holdScaleXRandomDelay * holdScaleXRandom);
                if (arrFractalBranches[branchNo].useScaleXForScaleY) {
                    holdScaleY = holdScaleX;
                } else {
                    holdScaleY = holdScaleYDelay + (levelArg * holdScaleYLevelDeltaDelay) + (holdScaleYRandomDelay * holdScaleYRandom);
                };
                holdAnchorX = getMaxWidth() * arrFractalBranches[branchNo].getDelayed_anchorX(holdLevelDelayFrames);
                holdAnchorY = getMaxHeight() * arrFractalBranches[branchNo].getDelayed_anchorY(holdLevelDelayFrames);
                
                bool holdapplyOffsetLast = arrFractalBranches[branchNo].applyOffsetLast->getBool();
                bool holddrawBottomLevelOnly = arrFractalBranches[branchNo].drawBottomLevelOnly->getBool();

                ofPushMatrix();
                ofTranslate(holdAnchorX, holdAnchorY);
                // translate if needed
                if (! holdapplyOffsetLast) {
                    ofTranslate(holdOffsetX, holdOffsetY);
                };
                ofScale(holdScaleX, holdScaleY, 1.0);
                ofRotateZ(holdAngle);
                // draw if needed
                if ( (! holddrawBottomLevelOnly) || (holddrawBottomLevelOnly && levelArg == 1)) {
                    holdDrawLayersRule = arrFractalBranches[branchNo].drawLayersRule->getInt();
                    ofTranslate(-holdAnchorX, -holdAnchorY);
                    // draw layers
                    TXDrawLayersBase::draw((TXDRAWLAYERSRULE) holdDrawLayersRule);
                };
                // translate if needed
                if (holdapplyOffsetLast) {
                    ofTranslate(holdOffsetX, holdOffsetY);
                };
                // use sub branch probability
                if ((arrFractalBranches[branchNo].subBranchProbability->getFloat() + holdSubBranchRandom) >= 1)  {
                    drawFractalBranch(levelArg - 1);
                }
                ofPopMatrix();
            }
        }
    }
}


