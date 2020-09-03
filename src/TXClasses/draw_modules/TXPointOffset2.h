/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

// NOTE - VERSION 2 IS FOR 6 X 6 BSURFACE

/* POINT LAYOUT NOTES
 
 POINT LAYOUT: (11 = row1, col1)
 11  12  13  14  15  16
 21  22  23  24  25  26
 31  32  33  34  35  36
 41  42  43  44  45  46
 51  52  53  54  55  56
 61  62  63  64  65  66
 
 POINT INDEX LAYOUT:
 0   1   2   3   4    5
 6   7   8   9   10  11
 12  13  14  15  16  17
 18  19  20  21  22  23
 24  25  26  27  28  29
 30  31  32  33  34  35
 
 POINT 0 == CORNER 11
 POINT 6 == CORNER 16
 POINT 30 == CORNER 61
 POINT 35 == CORNER 66
 */

/* === PARAMETER NOTES =====

 Preset Building Parameters:
 
 pointGroup
 - options: AllPoints/ CornerPoints / EdgeControlPoints/ Non-EdgeControlPoints/ MidSurfaceControlPoints; AllControlPoints
 
 cornerGroup
 - options: AllCorners/ Corner11 / Corner16 / Corner61 / Corner66 / Corners 11 & 16 / Corners 61 & Corner66 / Corners 11 & 61 / Corners 16 & Corner66
 
 presetScaling
 - options: multiply by 1.0 / multiply by presetNoScaled(range:0.1-1.0)/ multiply by presetNo(range:1-10)
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"

class TXModuleBase; // define class only

class TXPointOffset2 
{
public:
	// constructor
	TXPointOffset2 ();

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
