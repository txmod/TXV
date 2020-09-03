/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXDrawFractal3D.h"

TXDrawFractal3D::TXDrawFractal3D() {
    setup();
}

void TXDrawFractal3D::setup(){
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
    
    holdModParamFloatArgs.name = "cellDepth";
    holdModParamFloatArgs.fixedValue = 0.2;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	cellDepth = createModParameter(holdModParamFloatArgs);
    parameters.add(cellDepth->parameters);
    
    holdModParamIntArgs.name = "randomSeed";
    holdModParamIntArgs.fixedValue = 100;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 10000;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 10000;
	randomSeed = createModParameter(holdModParamIntArgs);
    parameters.add(randomSeed->parameters);
    
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

void TXDrawFractal3D::draw(){
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

void TXDrawFractal3D::drawFractalBranch(int levelArg) {
    float holdOffsetX, holdOffsetY, holdOffsetZ;
    float holdScaleX, holdScaleY, holdScaleZ;
    float holdAngle, holdRotateAxisX, holdRotateAxisY, holdRotateAxisZ;
    float holdBranchRandom, holdSubBranchRandom, holdAngleRandom, holdScaleXRandom, holdScaleYRandom, holdScaleZRandom;
    bool  makeBranch;
    bool holdapplyOffsetLast;
    bool holddrawBottomLevelOnly;
    // bool setUniformTexture; // not used now
    float holdAnchorX, holdAnchorY, holdAnchorZ;
    int holdDrawLayersRule;
    //    setUniformTexture = true;
    
    // levelArg  = 0 ends recursion
    if (levelArg > 0) {
        for (int branchNo = 0; branchNo < fractalTreeBranches->getInt(); branchNo++){
            // update rand vals
            holdBranchRandom = (rand() % 1000) * 0.001;
            holdSubBranchRandom = (rand() % 1000) * 0.001;
            holdAngleRandom = (rand() % 1000) * 0.001;
            holdScaleXRandom = (rand() % 1000) * 0.001;
            holdScaleYRandom = (rand() % 1000) * 0.001;
            holdScaleZRandom = (rand() % 1000) * 0.001;
            
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
                holdOffsetX = arrFractalBranches[branchNo].offsetX->getFloat() * cellWidth->getFloat() * getMaxWidth();
                holdOffsetY = arrFractalBranches[branchNo].offsetY->getFloat() * cellHeight->getFloat() * getMaxHeight();
                holdOffsetZ = arrFractalBranches[branchNo].offsetZ->getFloat() * cellDepth->getFloat() * getMaxDepth();
                holdRotateAxisX = arrFractalBranches[branchNo].rotateAxisX->getFloat() ;
                holdRotateAxisY = arrFractalBranches[branchNo].rotateAxisY->getFloat() ;
                holdRotateAxisZ = arrFractalBranches[branchNo].rotateAxisZ->getFloat() ;
                holdAngle = arrFractalBranches[branchNo].angle->getFloat() + (levelArg * arrFractalBranches[branchNo].angleLevelDelta->getFloat()) + (arrFractalBranches[branchNo].angleRandom->getFloat() * 180 * ((holdAngleRandom * 2) -1) );
                holdScaleX = arrFractalBranches[branchNo].scaleX->getFloat() + (levelArg * arrFractalBranches[branchNo].scaleXLevelDelta->getFloat()) + (arrFractalBranches[branchNo].scaleXRandom->getFloat() * holdScaleXRandom);
                if (arrFractalBranches[branchNo].useScaleXForScaleY) {
                    holdScaleY = holdScaleX;
                } else {
                    holdScaleY = arrFractalBranches[branchNo].scaleY->getFloat() + (levelArg * arrFractalBranches[branchNo].scaleYLevelDelta->getFloat()) + (arrFractalBranches[branchNo].scaleYRandom->getFloat() * holdScaleYRandom);
                };
                if (arrFractalBranches[branchNo].useScaleXForScaleZ) {
                    holdScaleZ = holdScaleX;
                } else {
                    holdScaleZ = arrFractalBranches[branchNo].scaleZ->getFloat() + (levelArg * arrFractalBranches[branchNo].scaleZLevelDelta->getFloat()) + (arrFractalBranches[branchNo].scaleZRandom->getFloat() * holdScaleZRandom);
                };
                holdAnchorX = getMaxWidth() * arrFractalBranches[branchNo].anchorX->getFloat();
                holdAnchorY = getMaxHeight() * arrFractalBranches[branchNo].anchorY->getFloat();
                holdAnchorZ = getMaxDepth() * arrFractalBranches[branchNo].anchorZ->getFloat();
                holddrawBottomLevelOnly= arrFractalBranches[branchNo].drawBottomLevelOnly->getBool();
                holdapplyOffsetLast = arrFractalBranches[branchNo].applyOffsetLast->getBool();
                
                ofPushMatrix();
                // adjust for anchor
                ofTranslate(holdAnchorX, holdAnchorY, holdAnchorZ);
                ofScale(holdScaleX, holdScaleY, holdScaleZ);
                ofRotate(holdAngle, holdRotateAxisX * TWO_PI, holdRotateAxisY * TWO_PI, holdRotateAxisZ * TWO_PI);
                // translate if needed
                if (! holdapplyOffsetLast) {
                    ofTranslate(holdOffsetX, holdOffsetY, holdOffsetZ);
                };
                ofTranslate(-holdAnchorX, -holdAnchorY, -holdAnchorZ);
                // draw if needed
                if ( (! holddrawBottomLevelOnly) || (holddrawBottomLevelOnly && levelArg == 1)) {
                    holdDrawLayersRule = arrFractalBranches[branchNo].drawLayersRule->getInt();
                    // draw layers
                    TXDrawLayersBase::draw((TXDRAWLAYERSRULE) holdDrawLayersRule);
                    // not needed for now:
                    //if (setUniformTexture) setUniformTexture = false;
                };
                // translate if needed
                if (holdapplyOffsetLast) {
                    ofTranslate(holdOffsetX, holdOffsetY, holdOffsetZ);
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

