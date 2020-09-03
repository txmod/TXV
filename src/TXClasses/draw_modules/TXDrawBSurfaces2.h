/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

/* Version 2, with 36 points and optional looping, but no mirroring
 
 
 POINT LAYOUT NOTES
 
 POINT LAYOUT: (11 = row1, col1)
 11  12  13  14  15  16
 21  22  23  24  25  26
 31  32  33  34  35  36
 41  42  43  44  45  46
 51  52  53  54  55  56
 61  62  63  64  65  66
 
6X6 POINT INDEX LAYOUT:
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

 8X8 POINT INDEX LAYOUT WITH EXTRA LOOP POINTS:
 0   1   2   3   4    5   6   7
 8   9   10  11  12  13  14  15
 16  17  18  19  20  21  22  23
 24  25  26  27  28  29  30  31
 32  33  34  35  36  37  38  39
 40  41  42  43  44  45  46  47
 48  49  50  51  52  53  54  55
 56  57  58  59  60  61  62  63
 
 */

/* === PARAMETER NOTES =====
 
 Morph Type
 - options: 
 No Morph - use points
 No Morph - use Points Morph Preset A
 No Morph - use Points Morph Preset B
 No Morph - use Points Morph Preset C
 No Morph - use Points Morph Preset D
 No Morph - use Points Morph Preset E
 Linear Morph - 2 Presets A - B
 Linear Morph - 3 Presets A - C
 Linear Morph - 4 Presets A - D
 Linear Morph - 5 Presets A - E
 2D Morph - 4 Presets A - D
 2D Morph - 5 Presets A - E

 Preset Building Parameters:

 pointGroup
 - options: AllPoints/ CornerPoints / EdgeControlPoints/ Non-EdgeControlPoints/ MidSurfaceControlPoints/ AllControlPoints
 
 cornerGroup
 - options: AllCorners/ Corner11 / Corner16 / Corner61 / Corner66 / Corners 11 & 16 / Corners 61 & Corner66 / Corners 11 & 61 / Corners 16 & Corner66
 
 presetScaling
 - options: multiply by 1.0 / multiply by presetNoScaled(range:0.1-1.0)/ multiply by presetNo(range:1-10)
*/

#pragma once

#include "ofMain.h"
#include "TXDrawBase.h"
#include "TXCurvePoint.h"
#include "TXPointOffset2.h"
#include "TXBezierSurface.h"
//#include "TXMain.h"

//enum TXPOINTSMORPHTYPE {
//    TXPOINTSMORPHTYPE_NOMORPH,
//    TXPOINTSMORPHTYPE_SOLOMORPHPRESETA,
//    TXPOINTSMORPHTYPE_SOLOMORPHPRESETB,
//    TXPOINTSMORPHTYPE_SOLOMORPHPRESETC,
//    TXPOINTSMORPHTYPE_SOLOMORPHPRESETD,
//    TXPOINTSMORPHTYPE_SOLOMORPHPRESETE,
//    TXPOINTSMORPHTYPE_LINEAR2SETS,
//    TXPOINTSMORPHTYPE_LINEAR3SETS,
//    TXPOINTSMORPHTYPE_LINEAR4SETS,
//    TXPOINTSMORPHTYPE_LINEAR5SETS,
//    TXPOINTSMORPHTYPE_2D4SETS,
//    TXPOINTSMORPHTYPE_2D5SETS,
//    TXPOINTSMORPHTYPE_TOTAL,
//};

class TXDrawBSurfaces2  :  public TXDrawBase {

public:
    const static int maxSurfaces = 100;

	// constructor
	TXDrawBSurfaces2();
    
    // destructor    
    ~TXDrawBSurfaces2();

	void setup();
	void update();
	void draw();
	void setupSurface();
    void rebuildPresets();
    void windowResized(int w, int h);
    ofVec3f getSetData(int setIndexArg, int pointNoArg);
    
    void imageAssetSlotChanged(string slotNameArg);
    void  useImageAsTextureChanged(bool & boolArg);
    void  useExternalSourceImageChanged(bool & boolArg);
    
    void loadSourceImage();
    bool mapTextureToSurface();
    int getTextureWidth(); // overide base class
    int getTextureHeight(); // overide base class
    ofTexture *  getTexture(); // overide base class
    ofPixelsRef getPixels(); // overide base class

    // listener methods
    void  message(string stringArg = "");
    void  surfaceResolutionChanged(ofAbstractParameter & parameterArg );
    void  useLoopingChanged(ofAbstractParameter & parameterArg );
    void  presetsChangedBool(bool & inArg);
    void  presetsChangedInt(int & inArg);
    void  presetsChangedFloat(float & inArg);

    // parameters
    
    ofParameter<bool> useImageAsTexture;
    ofParameter<bool> useExternalSourceImage;
    
    ofPtr<TXModParamInt> numSurfaces;
    ofPtr<TXModParamInt> surfaceResolution;
    ofPtr<TXModParamBool> drawWireframe;
    
    ofPtr<TXModParamBool> useLooping;
    
    ofPtr<TXModParamInt> pointsMorphType;
    ofPtr<TXModParamBool> usePointsToOffsetMorph;
    ofPtr<TXModParamFloat> pointsMorphX;
    ofPtr<TXModParamFloat> pointsMorphXEnd;
    ofParameter<bool>     pointsMorphXEndIgnore;
    ofPtr<TXModParamFloat> pointsMorphY;
    ofPtr<TXModParamFloat> pointsMorphYEnd;
    ofParameter<bool>     pointsMorphYEndIgnore;
    ofPtr<TXModParamInt> pointsMorphPresetA;
    ofPtr<TXModParamInt> pointsMorphPresetB;
    ofPtr<TXModParamInt> pointsMorphPresetC;
    ofPtr<TXModParamInt> pointsMorphPresetD;
    ofPtr<TXModParamInt> pointsMorphPresetE;
    TXParameterFloat256   pointsSpreadCurve;
    TXParameterFloat256   pointsSpreadCurve2;
    ofPtr<TXModParamFloat> pointsSpreadCurveMorph;
    
	// material:
    ofPtr<TXModParamFloat> materialShininess; // 0 - 128
    ofPtr<TXModParamFloat> materialShininessEnd;
    ofParameter<bool>     materialShininessEndIgnore;
    ofPtr<TXModParamFloat> materialDiffuseColorHue;
    ofPtr<TXModParamFloat> materialDiffuseColorHueEnd;
    ofParameter<bool>     materialDiffuseColorHueEndIgnore;
    ofPtr<TXModParamFloat> materialDiffuseColorHueRotate;
    ofPtr<TXModParamFloat> materialDiffuseColorSaturation;
    ofPtr<TXModParamFloat> materialDiffuseColorSaturationEnd;
    ofParameter<bool>     materialDiffuseColorSaturationEndIgnore;
    ofPtr<TXModParamFloat> materialDiffuseColorBrightness;
    ofPtr<TXModParamFloat> materialDiffuseColorBrightnessEnd;
    ofParameter<bool>     materialDiffuseColorBrightnessEndIgnore;
    ofPtr<TXModParamBool> materialDiffuseColorHSBAsRGB;
    ofParameter<bool>     useDiffuseColorForAmbient;
    ofPtr<TXModParamFloat> materialAmbientColorHue;
    ofPtr<TXModParamFloat> materialAmbientColorHueEnd;
    ofParameter<bool>     materialAmbientColorHueEndIgnore;
    ofPtr<TXModParamFloat> materialAmbientColorHueRotate;
    ofPtr<TXModParamFloat> materialAmbientColorSaturation;
    ofPtr<TXModParamFloat> materialAmbientColorSaturationEnd;
    ofParameter<bool>     materialAmbientColorSaturationEndIgnore;
    ofPtr<TXModParamFloat> materialAmbientColorBrightness;
    ofPtr<TXModParamFloat> materialAmbientColorBrightnessEnd;
    ofParameter<bool>     materialAmbientColorBrightnessEndIgnore;
    ofPtr<TXModParamBool> materialAmbientColorHSBAsRGB;
    ofParameter<bool>     useDiffuseColorForSpecular;
    ofPtr<TXModParamFloat> materialSpecularColorHue;
    ofPtr<TXModParamFloat> materialSpecularColorHueEnd;
    ofParameter<bool>     materialSpecularColorHueEndIgnore;
    ofPtr<TXModParamFloat> materialSpecularColorHueRotate;
    ofPtr<TXModParamFloat> materialSpecularColorSaturation;
    ofPtr<TXModParamFloat> materialSpecularColorSaturationEnd;
    ofParameter<bool>     materialSpecularColorSaturationEndIgnore;
    ofPtr<TXModParamFloat> materialSpecularColorBrightness;
    ofPtr<TXModParamFloat> materialSpecularColorBrightnessEnd;
    ofParameter<bool>     materialSpecularColorBrightnessEndIgnore;
    ofPtr<TXModParamBool> materialSpecularColorHSBAsRGB;
    ofParameter<bool>     useDiffuseColorForEmissive;
    ofPtr<TXModParamFloat> materialEmissiveColorHue;
    ofPtr<TXModParamFloat> materialEmissiveColorHueEnd;
    ofParameter<bool>     materialEmissiveColorHueEndIgnore;
    ofPtr<TXModParamFloat> materialEmissiveColorHueRotate;
    ofPtr<TXModParamFloat> materialEmissiveColorSaturation;
    ofPtr<TXModParamFloat> materialEmissiveColorSaturationEnd;
    ofParameter<bool>     materialEmissiveColorSaturationEndIgnore;
    ofPtr<TXModParamFloat> materialEmissiveColorBrightness;
    ofPtr<TXModParamFloat> materialEmissiveColorBrightnessEnd;
    ofParameter<bool>     materialEmissiveColorBrightnessEndIgnore;
    ofPtr<TXModParamBool> materialEmissiveColorHSBAsRGB;
    TXParameterFloat256   colorSpreadCurve;
    TXParameterFloat256   colorSpreadCurve2;
    ofPtr<TXModParamFloat> colorSpreadCurveMorph;
    
    ofPtr<TXModParamFloat> positionX;
    ofPtr<TXModParamFloat> positionXEnd;
    ofParameter<bool>     positionXEndIgnore;
    ofPtr<TXModParamFloat> positionY;
    ofPtr<TXModParamFloat> positionYEnd;
    ofParameter<bool>     positionYEndIgnore;
    ofPtr<TXModParamFloat> positionZ;
    ofPtr<TXModParamFloat> positionZEnd;
    ofParameter<bool>     positionZEndIgnore;
    TXParameterFloat256   positionSpreadCurve;
    TXParameterFloat256   positionSpreadCurve2;
    ofPtr<TXModParamFloat> positionSpreadCurveMorph;
    ofPtr<TXModParamFloat> rotateX;
    ofPtr<TXModParamFloat> rotateXEnd;
    ofParameter<bool>     rotateXEndIgnore;
    ofPtr<TXModParamFloat> rotateY;
    ofPtr<TXModParamFloat> rotateYEnd;
    ofParameter<bool>     rotateYEndIgnore;
    ofPtr<TXModParamFloat> rotateZ;
    ofPtr<TXModParamFloat> rotateZEnd;
    ofParameter<bool>     rotateZEndIgnore;
    ofPtr<TXModParamFloat> rotateMultiply;
    ofPtr<TXModParamFloat> rotateMultiplyEnd;
    ofParameter<bool>     rotateMultiplyEndIgnore;
    TXParameterFloat256   rotateSpreadCurve;
    TXParameterFloat256   rotateSpreadCurve2;
    ofPtr<TXModParamFloat> rotateSpreadCurveMorph;
    ofPtr<TXModParamFloat> anchorX;
    ofPtr<TXModParamFloat> anchorXEnd;
    ofParameter<bool>     anchorXEndIgnore;
    ofPtr<TXModParamFloat> anchorY;
    ofPtr<TXModParamFloat> anchorYEnd;
    ofParameter<bool>     anchorYEndIgnore;
    ofPtr<TXModParamFloat> anchorZ;
    ofPtr<TXModParamFloat> anchorZEnd;
    ofParameter<bool>     anchorZEndIgnore;
    TXParameterFloat256   anchorSpreadCurve;
    TXParameterFloat256   anchorSpreadCurve2;
    ofPtr<TXModParamFloat> anchorSpreadCurveMorph;
    ofPtr<TXModParamFloat> scaleX;
    ofPtr<TXModParamFloat> scaleXEnd;
    ofParameter<bool>     scaleXEndIgnore;
    ofPtr<TXModParamFloat> scaleY;
    ofPtr<TXModParamFloat> scaleYEnd;
    ofParameter<bool>     scaleYEndIgnore;
    ofPtr<TXModParamFloat> scaleZ;
    ofPtr<TXModParamFloat> scaleZEnd;
    ofParameter<bool>     scaleZEndIgnore;
    ofParameter<bool>     useScaleXForScaleY;
    ofParameter<bool>     useScaleXForScaleZ;
    TXParameterFloat256   scaleSpreadCurve;
    TXParameterFloat256   scaleSpreadCurve2;
    ofPtr<TXModParamFloat> scaleSpreadCurveMorph;
    
    // preset build parameters
    ofParameter<bool>  initPresetsAsFlatPlane;
    ofParameter<float> offsetDistortPointX;
    ofParameter<float> offsetDistortPointY;
    ofParameter<float> offsetDistortPointZ;
    ofParameter<int>   offsetRandomSeed;
    
private:
    ofImage holdImage1;
    ofImage holdImage2;
    ofImage * sourceImage;
    ofImage * newImage;
    bool sourceImageHasChanged;
    bool retryMapTexture;
    
    static const int totalPresetBuilderOffsets = 20;
    static const int totalUserPresets = 20;
    static const int totalNumPointsPresets = totalUserPresets + 1;
    static const int totalCurvePoints = 36;
    static const int totalCurvePlusLoopPoints = 64;
    
    TXCurvePoint arrCurvePoints[totalCurvePoints];
    TXPointOffset2 arrPointOffsets[totalPresetBuilderOffsets];
    float contolPointsData[108];
    float morphPointsData[108];
    TXBezierSurface surface;
    bool surfaceHasChanged;
    bool rebuildPresetsRequested;

    ofMaterial material;
    float sizeX, sizeY, sizeZ;
    ofVec3f meshCentroid;

    float arrUserPresets[totalUserPresets][108];
    float planePreset[108] = {
        // Preset 0
        -0.25,-0.25,0,-0.25,-0.15,0,-0.25,-0.05,0,-0.25,0.05,0,-0.25,0.15,0,-0.25,0.25,0,-0.15,-0.25,0,-0.15,-0.15,0,-0.15,-0.05,0,-0.15,0.05,0,-0.15,0.15,0,-0.15,0.25,0,-0.05,-0.25,0,-0.05,-0.15,0,-0.05,-0.05,0,-0.05,0.05,0,-0.05,0.15,0,-0.05,0.25,0,0.05,-0.25,0,0.05,-0.15,0,0.05,-0.05,0,0.05,0.05,0,0.05,0.15,0,0.05,0.25,0,0.15,-0.25,0,0.15,-0.15,0,0.15,-0.05,0,0.15,0.05,0,0.15,0.15,0,0.15,0.25,0,0.25,-0.25,0,0.25,-0.15,0,0.25,-0.05,0,0.25,0.05,0,0.25,0.15,0,0.25,0.25,0,
    };
 };


