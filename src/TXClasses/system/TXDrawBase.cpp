/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXDrawBase.h"
#include "TXSystem.h"

// constructor
TXDrawBase::TXDrawBase ()
{
    canDraw = true;
}

void TXDrawBase::initialiseParameters(string paramNamePrefix) {
    TXModParameterBoolArgs holdModParamBoolArgs;
//    TXModParameterIntArgs holdModParamIntArgs;
//    TXModParameterFloatArgs holdModParamFloatArgs;

    // run base init before adding parameters
    TXModuleBase::initialiseParameters();
    
    holdModParamBoolArgs.name = paramNamePrefix + "drawActive";
    holdModParamBoolArgs.fixedValue = true;
    holdModParamBoolArgs.fixedModMix = false;
	drawActive = createModParameter(holdModParamBoolArgs);
    parameters.add(drawActive->parameters);
    
    maxWidthHeightRule.set(paramNamePrefix + "maxWidthHeightRule",0,0,11);
    parameters.add(maxWidthHeightRule);
    
    maxDepthRule.set(paramNamePrefix + "maxDepthRule",0,0,4);
    parameters.add(maxDepthRule);

    customMaxWidth.set(paramNamePrefix + "customMaxWidth",1024,1,4096);
    parameters.add(customMaxWidth);

    customMaxHeight.set(paramNamePrefix + "customMaxHeight",768,1,4096);
    parameters.add(customMaxHeight);

    customMaxDepth.set(paramNamePrefix + "customMaxDepth",1024,1,4096);
    parameters.add(customMaxDepth);
}

int TXDrawBase::getMaxWidth() {    
    switch (maxWidthHeightRule) {
        case MAXWIDTHHEIGHTRULE_SCREENWIDTHHEIGHT:
            return getWindowWidth();
            break;
        case MAXWIDTHHEIGHTRULE_MAXSCREENWIDTHHEIGHT:
            return max(getWindowWidth(), getWindowHeight());
            break;
        case MAXWIDTHHEIGHTRULE_MINSCREENWIDTHHEIGHT:
            return min(getWindowWidth(), getWindowHeight());
            break;
        case MAXWIDTHHEIGHTRULE_SQUARESCREENWIDTH:
            return getWindowWidth();
            break;
        case MAXWIDTHHEIGHTRULE_SQUARESCREENHEIGHT:
            return getWindowHeight();
            break;
        case MAXWIDTHHEIGHTRULE_CUSTOMSIZE:
            return customMaxWidth;
            break;
        case MAXWIDTHHEIGHTRULE_480_360:
            return 480;
            break;
        case MAXWIDTHHEIGHTRULE_858_480:
            return 858;
            break;
        case MAXWIDTHHEIGHTRULE_1280_720:
            return 1280;
            break;
        case MAXWIDTHHEIGHTRULE_1920_1080:
            return 1920;
            break;
        case MAXWIDTHHEIGHTRULE_2560_1440:
            return 2560;
            break;
        case MAXWIDTHHEIGHTRULE_3840_2160:
            return 3840;
            break;
        default:
            return getWindowWidth();
            break;
    }
}

int TXDrawBase::getMaxHeight() {
    switch (maxWidthHeightRule) {
        case MAXWIDTHHEIGHTRULE_SCREENWIDTHHEIGHT:
            return getWindowHeight();
            break;
        case MAXWIDTHHEIGHTRULE_MAXSCREENWIDTHHEIGHT:
            return max(getWindowWidth(), getWindowHeight());
            break;
        case MAXWIDTHHEIGHTRULE_MINSCREENWIDTHHEIGHT:
            return min(getWindowWidth(), getWindowHeight());
            break;
        case MAXWIDTHHEIGHTRULE_SQUARESCREENWIDTH:
            return getWindowWidth();
            break;
        case MAXWIDTHHEIGHTRULE_SQUARESCREENHEIGHT:
            return getWindowHeight();
            break;
        case MAXWIDTHHEIGHTRULE_CUSTOMSIZE:
            return customMaxHeight;
            break;
        case MAXWIDTHHEIGHTRULE_480_360:
            return 360;
            break;
        case MAXWIDTHHEIGHTRULE_858_480:
            return 480;
            break;
        case MAXWIDTHHEIGHTRULE_1280_720:
            return 720;
            break;
        case MAXWIDTHHEIGHTRULE_1920_1080:
            return 1080;
            break;
        case MAXWIDTHHEIGHTRULE_2560_1440:
            return 1440;
            break;
        case MAXWIDTHHEIGHTRULE_3840_2160:
            return 2160;
            break;
        default:
            return getWindowHeight();
            break;
    }
}

int TXDrawBase::getMaxDepth() {
    switch (maxDepthRule) {
        case MAXDEPTHRULE_SCREENWIDTH:
            return getWindowWidth();
            break;
        case MAXDEPTHRULE_SCREENHEIGHT:
            return getWindowHeight();
            break;
        case MAXDEPTHRULE_MAXSCREENWIDTHHEIGHT:
            return max(getWindowWidth(), getWindowHeight());
            break;
        case MAXDEPTHRULE_MINSCREENWIDTHHEIGHT:
            return min(getWindowWidth(), getWindowHeight());
            break;
        case MAXDEPTHRULE_CUSTOMDEPTH:
            return customMaxDepth;
            break;
        default:
            return getWindowWidth();
            break;
    }
}

