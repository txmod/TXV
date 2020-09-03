/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"

#include "TXModuleBase.h"
//#include "TXMain.h"


/*
 360p (SD) 480 x 360
 480p (SD) 858 x 480
 720p (Half HD)1280 x 720
 1080p (Full HD) 1920 x 1080
 1440p (2k) 2560 x 1440
 2160p (4k) 3840 x 2160
 */

enum MAXWIDTHHEIGHTRULE {
    MAXWIDTHHEIGHTRULE_SCREENWIDTHHEIGHT, // 0
    MAXWIDTHHEIGHTRULE_MAXSCREENWIDTHHEIGHT, // 1
    MAXWIDTHHEIGHTRULE_MINSCREENWIDTHHEIGHT, // 2
    MAXWIDTHHEIGHTRULE_SQUARESCREENWIDTH, // 3
    MAXWIDTHHEIGHTRULE_SQUARESCREENHEIGHT, // 4
    MAXWIDTHHEIGHTRULE_CUSTOMSIZE, // 5
    MAXWIDTHHEIGHTRULE_480_360, // 6
    MAXWIDTHHEIGHTRULE_858_480, // 7
    MAXWIDTHHEIGHTRULE_1280_720, // 8
    MAXWIDTHHEIGHTRULE_1920_1080, // 9
    MAXWIDTHHEIGHTRULE_2560_1440, // 10
    MAXWIDTHHEIGHTRULE_3840_2160, // 11
};

enum MAXDEPTHRULE {
    MAXDEPTHRULE_SCREENWIDTH,
    MAXDEPTHRULE_SCREENHEIGHT,
    MAXDEPTHRULE_MAXSCREENWIDTHHEIGHT,
    MAXDEPTHRULE_MINSCREENWIDTHHEIGHT,
    MAXDEPTHRULE_CUSTOMDEPTH,
};

class TXDrawBase : public TXModuleBase  // abstract data type
{
public:
    
	// constructor
	TXDrawBase ();

    virtual void initialiseParameters(string paramNamePrefix = "");
    
    int getMaxWidth();
    int getMaxHeight();
    int getMaxDepth();

    ofPtr<TXModParamBool> drawActive;
    ofParameter<int> maxWidthHeightRule;
    ofParameter<int> maxDepthRule;
    ofParameter<int> customMaxWidth;
    ofParameter<int> customMaxHeight;
    ofParameter<int> customMaxDepth;
};


