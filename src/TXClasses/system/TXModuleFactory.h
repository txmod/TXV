/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
//#include "TXMain.h"
#include "TXModuleBase.h"

 #include "TXBlend.h"
#include "TXBloom.h"
#include "TXBlur.h"
#include "TXColorControls.h"
#include "TXColorize.h"
#include "TXColorCurves.h"
#include "TXColorSampler.h"
#include "TXConvolution.h"
#include "TXDraw2DCurves.h" // old version
#include "TXDraw2DDelayCurves.h" // old version
#include "TXDraw2DShape.h"
#include "TXDraw2DShapeMulti.h"
#include "TXDraw3DModel.h"
//#include "TXDraw3DShape.h" // old version
//#include "TXDraw3DShapeMulti.h" // old version
#include "TXDrawBSurfaces.h"
#include "TXDrawBSurfaces2.h"
#include "TXDrawBSurfacesX6.h"
#include "TXDraw3DWorld.h" // old version
//#include "TXDrawCircles.h" // old version
#include "TXDrawCurves.h"
#include "TXDrawDelayCurves.h"
#include "TXDrawFluid.h"
#include "TXDrawFractal.h"
#include "TXDrawFractal3D.h"
#include "TXDrawFractalDelay.h"
#include "TXDrawFractalDelay3D.h"
#include "TXDrawGradient.h"
#include "TXDrawImage.h"
 #include "TXDrawMovie.h"
// #include "TXDrawMovieOSX.h"  // not compiling removed for now
#include "TXDrawParticles.h" // not compiling removed for now
#include "TXDrawParticles3D.h" // not compiling removed for now
#include "TXDrawScene.h"
#include "TXDrawShape3D.h"
#include "TXDrawShape3DMulti.h"
#include "TXDrawSVG.h"
#include "TXDrawText3D.h"
#include "TXDrawTransform.h"
#include "TXDrawTransform3D.h"
#include "TXDrawTransform3DDelay.h"
#include "TXDrawTransform3DMulti.h"
#include "TXDrawVideoCam.h"
#include "TXEnvMap.h"
#include "TXFeedback.h"
#include "TXFindEdges.h"
#include "TXGenerator.h"
#include "TXGlow.h"
#include "TXKaleidoscope.h"
//#include "TXLeapMotion.h"  // not linking with leap lib so removed for now
#include "TXLevels.h"
#include "TXLFO.h"
#include "TXLFO2D.h"
#include "TXLFO3D.h"
#include "TXLumaKey.h"
#include "TXLUT.h"
#include "TXLUTFast.h"
#include "TXMeshDistort.h"
//#include "TXMeshDistortHemi.h"  // not working well removed for now
#include "TXOSCControlIn.h"
#include "TXOSCControlIn2D.h"
#include "TXOSCControlIn3D.h"
#include "TXPerlin.h"
#include "TXPixelate.h"
#include "TXRenderImage.h"
#include "TXSampleHold.h"
#include "TXSlideShow.h"
#include "TXSmooth.h"
#include "TXSmoothMulti.h"
#include "TXSoftThreshold.h"
#include "TXStepSequencer.h"
#include "TXThreshold.h"
#include "TXTileMask.h"
// #include "TXTablet.h"  // removed for now
#include "TXToggle.h"
#include "TXWallpaper.h"
#include "TXWarp.h"
#include "TXWarpMorph.h"
#include "TXWaveTerrain.h"
#include "TXWobble.h"

class TXModuleFactory
{
public:

    static bool isValidModuleType(const string &description)
    {
        const char* names[] = {
            "TXBlend",
            "TXBloom",
            "TXBlur",
            "TXColorControls",
            "TXColorCurves",
            "TXColorize",
            "TXColorSampler",
            "TXConvolution",
            "TXDraw2DCurves",
            "TXDraw2DDelayCurves",
            "TXDraw2DShape",
            "TXDraw2DShapeMulti",
            "TXDraw3DModel",
            "TXDraw3DShape", // old version
            "TXDraw3DShapeMulti", // old version
            "TXDrawBSurfaces",
            "TXDrawBSurfaces2",
            "TXDrawBSurfacesX6",
            "TXDraw3DWorld",
            "TXDrawCircles", // old version
            "TXDrawCurves",
            "TXDrawDelayCurves",
            "TXDrawFluid",
            "TXDrawFractal",
            "TXDrawFractal3D",
            "TXDrawFractalDelay",
            "TXDrawFractalDelay3D",
            "TXDrawGradient",
            "TXDrawImage",
            "TXDrawMovie",
            "TXDrawMovieOSX",
            "TXDrawParticles",
            "TXDrawParticles3D",
            "TXDrawScene",
            "TXDrawShape3D",
            "TXDrawShape3DMulti",
            "TXDrawSVG",
            "TXDrawText3D",
            "TXDrawTransform",
            "TXDrawTransform3D",
            "TXDrawTransform3DDelay",
            "TXDrawTransform3DMulti",
            "TXDrawVideoCam",
            "TXEnvMap",
            "TXFeedback",
            "TXFindEdges",
            "TXGenerator",
            "TXGlow",
            "TXKaleidoscope",
            "TXLeapMotion",
            "TXLevels",
            "TXLFO",
            "TXLFO2D",
            "TXLFO3D",
            "TXLumaKey",
            "TXLUT",
            "TXLUTFast",
            "TXMeshDistort",
            // "TXMeshDistortHemi",
            "TXOSCControlIn",
            "TXOSCControlIn2D",
            "TXOSCControlIn3D",
            "TXPerlin",
            "TXPixelate",
            "TXRenderImage",
            "TXSampleHold",
            "TXSlideShow",
            "TXSmooth",
            "TXSmoothMulti",
            "TXSoftThreshold",
            "TXStepSequencer",
            "TXThreshold",
            "TXTileMask",
            "TXTablet",
            "TXToggle",
            "TXWallpaper",
            "TXWarp",
            "TXWarpMorph",
            "TXWaveTerrain",
            "TXWobble",
        };
        vector<string> vNames(names, names + sizeof(names)/sizeof(names[0]));
        vector<string>::iterator iter = find(vNames.begin(), vNames.end(), description);
        if (iter == vNames.end()) {
            return false;
        } else {
            return true;
        };
    }
    
    static ofPtr<TXModuleBase> NewTXModule(const string &description)
    {
        if (description == "TXBlend")
            return ofPtr<TXModuleBase>(new TXBlend);
        if (description == "TXBloom")
            return ofPtr<TXModuleBase>(new TXBloom);
        if (description == "TXBlur")
            return ofPtr<TXModuleBase>(new TXBlur);
        if (description == "TXColorControls")
            return ofPtr<TXModuleBase>(new TXColorControls);
        if (description == "TXColourControls")
            return ofPtr<TXModuleBase>(new TXColorControls);
        if (description == "TXColorCurves")
            return ofPtr<TXModuleBase>(new TXColorCurves);
        if (description == "TXColorize")
            return ofPtr<TXModuleBase>(new TXColorize);
        if (description == "TXColorSampler")
            return ofPtr<TXModuleBase>(new TXColorSampler);
        if (description == "TXConvolution")
            return ofPtr<TXModuleBase>(new TXConvolution);
        if (description == "TXDraw2DCurves")
            return ofPtr<TXModuleBase>(new TXDraw2DCurves);
        if (description == "TXDraw2DDelayCurves")
            return ofPtr<TXModuleBase>(new TXDraw2DDelayCurves);
        if (description == "TXDraw2DShape")
            return ofPtr<TXModuleBase>(new TXDraw2DShape);
        if (description == "TXDraw2DShapeMulti")
            return ofPtr<TXModuleBase>(new TXDraw2DShapeMulti);
        if (description == "TXDraw3DModel")
            return ofPtr<TXModuleBase>(new TXDraw3DModel);
//        if (description == "TXDraw3DShape") // old version
//            return ofPtr<TXModuleBase>(new TXDraw3DShape);
//        if (description == "TXDraw3DShapeMulti") // old version
//            return ofPtr<TXModuleBase>(new TXDraw3DShapeMulti);
        if (description == "TXDrawBSurfaces")
            return ofPtr<TXModuleBase>(new TXDrawBSurfaces);
        if (description == "TXDrawBSurfaces2")
            return ofPtr<TXModuleBase>(new TXDrawBSurfaces2);
        if (description == "TXDrawBSurfacesX6")
            return ofPtr<TXModuleBase>(new TXDrawBSurfacesX6);
        if (description == "TXDraw3DWorld")
            return ofPtr<TXModuleBase>(new TXDraw3DWorld);
//        if (description == "TXDrawCircles")
//            return ofPtr<TXModuleBase>(new TXDrawCircles);
        if (description == "TXDrawCurves")
            return ofPtr<TXModuleBase>(new TXDrawCurves);
        if (description == "TXDrawDelayCurves")
            return ofPtr<TXModuleBase>(new TXDrawDelayCurves);
        if (description == "TXDrawFluid")
            return ofPtr<TXModuleBase>(new TXDrawFluid);
        if (description == "TXDrawFractal")
            return ofPtr<TXModuleBase>(new TXDrawFractal);
        if (description == "TXDrawFractal3D")
            return ofPtr<TXModuleBase>(new TXDrawFractal3D);
        if (description == "TXDrawFractalDelay")
            return ofPtr<TXModuleBase>(new TXDrawFractalDelay);
        if (description == "TXDrawFractalDelay3D")
            return ofPtr<TXModuleBase>(new TXDrawFractalDelay3D);
        if (description == "TXDrawGradient")
            return ofPtr<TXModuleBase>(new TXDrawGradient);
        if (description == "TXDrawImage")
            return ofPtr<TXModuleBase>(new TXDrawImage);
        if (description == "TXDrawMovie")
            return ofPtr<TXModuleBase>(new TXDrawMovie);
//        if (description == "TXDrawMovieOSX")
//            return ofPtr<TXModuleBase>(new TXDrawMovieOSX);
        if (description == "TXDrawParticles")
            return ofPtr<TXModuleBase>(new TXDrawParticles);
        if (description == "TXDrawParticles3D")
            return ofPtr<TXModuleBase>(new TXDrawParticles3D);
        if (description == "TXDrawScene")
            return ofPtr<TXModuleBase>(new TXDrawScene);
        if (description == "TXDrawShape3D")
            return ofPtr<TXModuleBase>(new TXDrawShape3D);
        if (description == "TXDrawShape3DMulti")
            return ofPtr<TXModuleBase>(new TXDrawShape3DMulti);
        if (description == "TXDrawSVG")
            return ofPtr<TXModuleBase>(new TXDrawSVG);
        if (description == "TXDrawText3D")
            return ofPtr<TXModuleBase>(new TXDrawText3D);
        if (description == "TXDrawTransform")
            return ofPtr<TXModuleBase>(new TXDrawTransform);
        if (description == "TXDrawTransform3D")
            return ofPtr<TXModuleBase>(new TXDrawTransform3D);
        if (description == "TXDrawTransform3DDelay")
            return ofPtr<TXModuleBase>(new TXDrawTransform3DDelay);
        if (description == "TXDrawTransform3DMulti")
            return ofPtr<TXModuleBase>(new TXDrawTransform3DMulti);
        if (description == "TXDrawVideoCam")
            return ofPtr<TXModuleBase>(new TXDrawVideoCam);
        if (description == "TXEnvMap")
            return ofPtr<TXModuleBase>(new TXEnvMap);
        if (description == "TXFeedback")
            return ofPtr<TXModuleBase>(new TXFeedback);
        if (description == "TXFindEdges")
            return ofPtr<TXModuleBase>(new TXFindEdges);
        if (description == "TXGenerator")
            return ofPtr<TXModuleBase>(new TXGenerator);
        if (description == "TXGlow")
            return ofPtr<TXModuleBase>(new TXGlow);
        if (description == "TXKaleidoscope")
            return ofPtr<TXModuleBase>(new TXKaleidoscope);
//        if (description == "TXLeapMotion")
//            return ofPtr<TXModuleBase>(new TXLeapMotion);
        if (description == "TXLevels")
            return ofPtr<TXModuleBase>(new TXLevels);
        if (description == "TXLFO")
            return ofPtr<TXModuleBase>(new TXLFO);
        if (description == "TXLFO2D")
            return ofPtr<TXModuleBase>(new TXLFO2D);
        if (description == "TXLFO3D")
            return ofPtr<TXModuleBase>(new TXLFO3D);
        if (description == "TXLumaKey")
            return ofPtr<TXModuleBase>(new TXLumaKey);
        if (description == "TXLUT")
            return ofPtr<TXModuleBase>(new TXLUT);
        if (description == "TXLUTFast")
            return ofPtr<TXModuleBase>(new TXLUTFast);
        if (description == "TXMeshDistort")
            return ofPtr<TXModuleBase>(new TXMeshDistort);
        //if (description == "TXMeshDistortHemi")
        //    return ofPtr<TXModuleBase>(new TXMeshDistortHemi);
        if (description == "TXOSCControlIn")
            return ofPtr<TXModuleBase>(new TXOSCControlIn);
        if (description == "TXOSCControlIn2D")
            return ofPtr<TXModuleBase>(new TXOSCControlIn2D);
        if (description == "TXOSCControlIn3D")
            return ofPtr<TXModuleBase>(new TXOSCControlIn3D);
        if (description == "TXPerlin")
            return ofPtr<TXModuleBase>(new TXPerlin);
        if (description == "TXPixelate")
            return ofPtr<TXModuleBase>(new TXPixelate);
        if (description == "TXRenderImage")
            return ofPtr<TXModuleBase>(new TXRenderImage);
        if (description == "TXSampleHold")
            return ofPtr<TXModuleBase>(new TXSampleHold);
        if (description == "TXSlideShow")
            return ofPtr<TXModuleBase>(new TXSlideShow);
        if (description == "TXSmooth")
            return ofPtr<TXModuleBase>(new TXSmooth);
        if (description == "TXSmoothMulti")
            return ofPtr<TXModuleBase>(new TXSmoothMulti);
        if (description == "TXSoftThreshold")
            return ofPtr<TXModuleBase>(new TXSoftThreshold);
        if (description == "TXStepSequencer")
            return ofPtr<TXModuleBase>(new TXStepSequencer);
        if (description == "TXThreshold")
            return ofPtr<TXModuleBase>(new TXThreshold);
        if (description == "TXTileMask")
            return ofPtr<TXModuleBase>(new TXTileMask);
//        if (description == "TXTablet")
//            return ofPtr<TXModuleBase>(new TXTablet);
        if (description == "TXToggle")
            return ofPtr<TXModuleBase>(new TXToggle);
        if (description == "TXWallpaper")
            return ofPtr<TXModuleBase>(new TXWallpaper);
        if (description == "TXWarp")
            return ofPtr<TXModuleBase>(new TXWarp);
        if (description == "TXWarpMorph")
            return ofPtr<TXModuleBase>(new TXWarpMorph);
        if (description == "TXWaveTerrain")
            return ofPtr<TXModuleBase>(new TXWaveTerrain);
        if (description == "TXWobble")
            return ofPtr<TXModuleBase>(new TXWobble);
        
    }
    
};