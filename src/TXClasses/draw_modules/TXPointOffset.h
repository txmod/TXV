/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

/* POINT LAYOUT NOTES
 
 POINT LAYOUT: (11 = row1, col1)
 11  12  13  14
 21  22  23  24
 31  32  33  34
 41  42  43  44
 
 POINT INDEX LAYOUT:
 0   1   2   3
 4   5   6   7
 8   9   10  11
 12  13  14  15
 
 POINT 0 == CORNER 11
 POINT 3 == CORNER 14
 POINT 12 == CORNER 41
 POINT 15 == CORNER 44
 */

 /* PARAMETER NOTES
 
 pointGroup
 - options: AllPoints/ CornerPoints / EdgeControlPoints/ Non-EdgeControlPoints/ AllControlPoints
 
 cornerGroup
 - options: AllCorners/ Corner11 / Corner14 / Corner41 / Corner44 / Corners 11 & 14 / Corners 41 & Corner44 / Corners 11 & 41 / Corners 14 & Corner44
 
 presetScaling
 - options: "multiply by 1.0/ multiply by presetNoRangeScaled (0 : 1)/ multiply by presetNo (1 : presetRange)
 
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"

class TXModuleBase; // define class only

class TXPointOffset 
{
public:
	// constructor
	TXPointOffset ();

 	// methods
	void setup (TXModuleBase * parentArg, string nameArg = "Offset");

    ofVec3f getOffset(int presetNo, int pointNo, ofVec3f startPoint, float offsetDistortPointX, float offsetDistortPointY, float offsetDistortPointZ, int presetRandomSeed);

    void  offsetChangedBool(bool & inArg);
    void  offsetChangedInt(int & inArg);
    void  offsetChangedFloat(float & inArg);

    ofParameterGroup parameters;

    ofParameter<bool>  active;
    ofParameter<int>   presetRangeMin;
    ofParameter<int>   presetRangeMax;
    ofParameter<int>   pointGroup;
    ofParameter<int>   cornerGroup;
    ofParameter<float> fixedValueX;
    ofParameter<float> fixedValueY;
    ofParameter<float> fixedValueZ;
    ofParameter<float> randomValueMaxX;
    ofParameter<float> randomValueMaxY;
    ofParameter<float> randomValueMaxZ;
    ofParameter<float> distortPointDistanceScale;
    ofParameter<int>   presetScaling;

private:

    TXModuleBase * txParentModule;

//    int pointType;
//    int maxDelayFrames = 0;
//    int currentDelayFrame = 0;
    
};
