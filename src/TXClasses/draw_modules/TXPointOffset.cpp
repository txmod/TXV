/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXPointOffset.h"
#include "TXModuleBase.h"

// properties

// constructor
TXPointOffset::TXPointOffset () {
};

// methods

void TXPointOffset::setup (TXModuleBase * parentArg, string nameArg) {

    txParentModule = parentArg;
    
    parameters.clear();
    parameters.setName(nameArg);
    
    parameters.add(active.set(nameArg + "Active", false));
    parameters.add(presetRangeMin.set(nameArg + "presetRangeMin", 1, 1, 20));
    parameters.add(presetRangeMax.set(nameArg + "presetRangeMax", 20, 1, 20));
    parameters.add(pointGroup.set(nameArg + "PointGroup", 0, 0, 4));
    parameters.add(cornerGroup.set(nameArg + "CornerGroup", 0, 0, 8));
    parameters.add(fixedValueX.set(nameArg + "FixedValueX", 0.0, -3.0, 3.0));
    parameters.add(fixedValueY.set(nameArg + "FixedValueY", 0.0, -3.0, 3.0));
    parameters.add(fixedValueZ.set(nameArg + "FixedValueZ", 0.0, -3.0, 3.0));
    parameters.add(randomValueMaxX.set(nameArg + "RandomValueMaxX", 0.0, -3.0, 3.0));
    parameters.add(randomValueMaxY.set(nameArg + "RandomValueMaxY", 0.0, -3.0, 3.0));
    parameters.add(randomValueMaxZ.set(nameArg + "RandomValueMaxZ", 0.0, -3.0, 3.0));
    parameters.add(distortPointDistanceScale.set(nameArg + "DistortPointDistanceScale", 0.0, -3.0, 3.0));
    parameters.add(presetScaling.set(nameArg + "PresetScaling", 0, 0, 2));

    // add listener to relevent parameters:
    active.addListener(this, &TXPointOffset::offsetChangedBool);
    
    presetRangeMin.addListener(this, &TXPointOffset::offsetChangedInt);
    presetRangeMax.addListener(this, &TXPointOffset::offsetChangedInt);
    pointGroup.addListener(this, &TXPointOffset::offsetChangedInt);
    cornerGroup.addListener(this, &TXPointOffset::offsetChangedInt);

    fixedValueX.addListener(this, &TXPointOffset::offsetChangedFloat);
    fixedValueY.addListener(this, &TXPointOffset::offsetChangedFloat);
    fixedValueZ.addListener(this, &TXPointOffset::offsetChangedFloat);
    randomValueMaxX.addListener(this, &TXPointOffset::offsetChangedFloat);
    randomValueMaxY.addListener(this, &TXPointOffset::offsetChangedFloat);
    randomValueMaxZ.addListener(this, &TXPointOffset::offsetChangedFloat);
    distortPointDistanceScale.addListener(this, &TXPointOffset::offsetChangedFloat);

    presetScaling.addListener(this, &TXPointOffset::offsetChangedInt);
};

ofVec3f TXPointOffset::getOffset(int presetNo, int pointNo, ofVec3f startPoint, float offsetDistortPointX, float offsetDistortPointY, float offsetDistortPointZ, int presetRandomSeed) {
    
    ofVec3f totalOffset, randOffset, distortOffset;
    float multiplyVal;
    bool validPresetRange = false;
    bool validPointGroup = false;
    bool validCornerGroup = false;
    int minPresetInd = min(presetRangeMin, presetRangeMax) - 1;
    int maxPresetInd = max(presetRangeMin, presetRangeMax) - 1;
    
    if ((presetNo >= minPresetInd) && (presetNo <= maxPresetInd)) {
        validPresetRange = true;
    };

    // pointGroup
    switch (pointGroup) {
        case 0: // AllPoints
            validPointGroup = true;
            break;
        case 1: // CornerPoints
            if ((pointNo == 0)
                || (pointNo == 3)
                || (pointNo == 12)
                || (pointNo == 15)
                ) {
                validPointGroup = true;
            };
            break;
        case 2: // EdgeControlPoints
            if ((pointNo == 1)
                || (pointNo == 2)
                || (pointNo == 4)
                || (pointNo == 7)
                || (pointNo == 8)
                || (pointNo == 9)
                || (pointNo == 13)
                || (pointNo == 14)
                ) {
                validPointGroup = true;
            };
            break;
        case 3: // Non-EdgeControlPoints
            if ((pointNo == 5)
                || (pointNo == 6)
                || (pointNo == 9)
                || (pointNo == 10)
                ) {
                validPointGroup = true;
            };
            break;
        case 4: // AllControlPoints
            if ((pointNo == 1)
                || (pointNo == 2)
                || (pointNo == 4)
                || (pointNo == 7)
                || (pointNo == 8)
                || (pointNo == 9)
                || (pointNo == 13)
                || (pointNo == 14)
                || (pointNo == 5)
                || (pointNo == 6)
                || (pointNo == 9)
                || (pointNo == 10)
                ) {
                validPointGroup = true;
            };
            break;
        default:
            break;
    }
    
    // cornerGroup
    switch (cornerGroup) {
        case 0: // AllCorners
            validCornerGroup = true;
            break;
        case 1: // Corner 11
            if ((pointNo == 0)
                || (pointNo == 1)
                || (pointNo == 4)
                || (pointNo == 5)
                ) {
                validCornerGroup = true;
            };
            break;
        case 2: // Corner 14
            if ((pointNo == 2)
                || (pointNo == 3)
                || (pointNo == 6)
                || (pointNo == 7)
                ) {
                validCornerGroup = true;
            };
            break;
        case 3: // Corner 41
            if ((pointNo == 8)
                || (pointNo == 9)
                || (pointNo == 12)
                || (pointNo == 13)
                ) {
                validCornerGroup = true;
            };
            break;
        case 4: // Corner 44
            if ((pointNo == 10)
                || (pointNo == 11)
                || (pointNo == 14)
                || (pointNo == 15)
                ) {
                validCornerGroup = true;
            };
            break;
        case 5: // Corners 11 & 14
            if ((pointNo == 0)
                || (pointNo == 1)
                || (pointNo == 2)
                || (pointNo == 3)
                || (pointNo == 4)
                || (pointNo == 5)
                || (pointNo == 6)
                || (pointNo == 7)
                ) {
                validCornerGroup = true;
            };
            break;
        case 6: // Corners 41 & 44
            if ((pointNo == 8)
                || (pointNo == 9)
                || (pointNo == 10)
                || (pointNo == 11)
                || (pointNo == 12)
                || (pointNo == 13)
                || (pointNo == 14)
                || (pointNo == 15)
                ) {
                validCornerGroup = true;
            };
            break;
        case 7: // Corners 11 & 41
            if ((pointNo == 0)
                || (pointNo == 1)
                || (pointNo == 4)
                || (pointNo == 5)
                || (pointNo == 8)
                || (pointNo == 9)
                || (pointNo == 12)
                || (pointNo == 13)
                ) {
                validCornerGroup = true;
            };
            break;
        case 8: // Corners 14 & 44
            if ((pointNo == 2)
                || (pointNo == 3)
                || (pointNo == 6)
                || (pointNo == 7)
                || (pointNo == 10)
                || (pointNo == 11)
                || (pointNo == 14)
                || (pointNo == 15)
                ) {
                validCornerGroup = true;
            };
            break;
        default:
            break;
    }
    
    totalOffset.zero();
    
    if (active && validPresetRange && validPointGroup && validCornerGroup) {
        totalOffset += ofVec3f(fixedValueX, fixedValueY, fixedValueZ);
        
        ofSeedRandom(presetRandomSeed + (presetNo * 100) + (pointNo * 10000));
        randOffset.x = ofRandomuf() * randomValueMaxX;
        randOffset.y = ofRandomuf() * randomValueMaxY;
        randOffset.z = ofRandomuf() * randomValueMaxZ;
        totalOffset += randOffset;
        
        distortOffset = (startPoint - ofVec3f(offsetDistortPointX, offsetDistortPointY, offsetDistortPointZ)) * distortPointDistanceScale;
        totalOffset += distortOffset;
        
        switch (presetScaling) {
            case 0: // multiply by 1
                break;
            case 1: // multiply by presetNoRangeScaled (1/presetRange : 1)
                if (maxPresetInd != minPresetInd) {
                    totalOffset *= (1 + presetNo - minPresetInd) / (maxPresetInd - minPresetInd);
                };
                break;
            case 2: // multiply by presetNo (1 : presetRange)
                if (maxPresetInd != minPresetInd) {
                    totalOffset *= (1 + presetNo - minPresetInd) ;
                };
                break;
            default:
                break;
        }
    };
    
    return totalOffset;
};

void  TXPointOffset::offsetChangedBool(bool & inArg) {
    txParentModule->message();
}

void  TXPointOffset::offsetChangedInt(int & inArg) {
    txParentModule->message();
}

void  TXPointOffset::offsetChangedFloat(float & inArg) {
    txParentModule->message();
}


