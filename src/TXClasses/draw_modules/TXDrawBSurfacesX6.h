/*
 *  Copyright 2013 Paul Miller. All rights reserved.
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
 - options: AllPoints/ CornerPoints / EdgeControlPoints/ Non-EdgeControlPoints/ AllControlPoints
 
 cornerGroup
 - options: AllCorners/ Corner11 / Corner14 / Corner41 / Corner44 / Corners 11 & 14 / Corners 41 & Corner44 / Corners 11 & 41 / Corners 14 & Corner44
 
 presetScaling
 - options: multiply by 1.0 / multiply by presetNoScaled(range:0.1-1.0)/ multiply by presetNo(range:1-10)
*/

#pragma once

#include "ofMain.h"
#include "TXDrawBase.h"
#include "TXCurvePoint.h"
#include "TXPointOffset.h"
#include "TXBezierSurface.h"
//#include "TXMain.h"

enum TXBSURFACEX6DRAWMODE {
    TXBSURFACEX6DRAWMODE_ALLSURFACES,
    TXBSURFACEX6DRAWMODE_FRONTONLY,
    TXBSURFACEX6DRAWMODE_BACKONLY,
    TXBSURFACEX6DRAWMODE_SIDESONLY,
    TXBSURFACEX6DRAWMODE_FRONTANDBACK,
    TXBSURFACEX6DRAWMODE_TOTALMODES,
};

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

class TXDrawBSurfacesX6  :  public TXDrawBase {

public:
    const static int maxSurfaces = 100;

	// constructor
	TXDrawBSurfacesX6();
    
    // destructor    
    ~TXDrawBSurfacesX6();

	void setup();
	void update();
	void draw();
	void setupSurface();
	void buildFront(int morphTypeArg, float morphXArg, float morphYArg, bool usePointsToOffsetMorphArg);
	void buildBack(int morphTypeArg, float morphXArg, float morphYArg, bool usePointsToOffsetMorphArg);
	void buildSides();
    void rebuildPresets();
    void windowResized(int w, int h);
    ofVec3f getSetData(int setIndexArg, int pointNoArg);
    
    void imageAssetSlotChanged(string slotNameArg);
    void  useImageAsTextureChanged(bool & boolArg);
    void  useExternalSourceImageChanged(bool & boolArg);
    
    void loadSourceImage();
    bool mapTextureToSurface(bool mapGroupShapeArg = false);
    int getTextureWidth(); // overide base class
    int getTextureHeight(); // overide base class
    ofTexture *  getTexture(); // overide base class
    ofPixelsRef getPixels(); // overide base class

    // listener methods
    void  message(string stringArg = "");
    void  surfaceResolutionChanged(ofAbstractParameter & parameterArg );
    void  presetsChangedBool(bool & inArg);
    void  presetsChangedInt(int & inArg);
    void  presetsChangedFloat(float & inArg);

    // parameters
    
    ofParameter<bool> useImageAsTexture;
    ofParameter<bool> useExternalSourceImage;
    
    ofPtr<TXModParamInt> numSurfaces;
    ofPtr<TXModParamInt> surfaceResolution;
    ofPtr<TXModParamBool> drawWireframe;
    ofPtr<TXModParamInt> drawMode;
    
    ofPtr<TXModParamInt> pointsMorphType;
    ofPtr<TXModParamBool> usePointsToOffsetMorph;
    ofPtr<TXModParamFloat> pointsMorphX;
    ofPtr<TXModParamFloat> pointsMorphXEnd;
    ofParameter<bool>     pointsMorphXEndIgnore;
    ofPtr<TXModParamFloat> pointsMorphY;
    ofPtr<TXModParamFloat> pointsMorphYEnd;
    ofParameter<bool>     pointsMorphYEndIgnore;
    ofPtr<TXModParamInt> pointsMorphFrontPresetA;
    ofPtr<TXModParamInt> pointsMorphFrontPresetB;
    ofPtr<TXModParamInt> pointsMorphFrontPresetC;
    ofPtr<TXModParamInt> pointsMorphFrontPresetD;
    ofPtr<TXModParamInt> pointsMorphFrontPresetE;
    ofPtr<TXModParamInt> pointsMorphBackPresetA;
    ofPtr<TXModParamInt> pointsMorphBackPresetB;
    ofPtr<TXModParamInt> pointsMorphBackPresetC;
    ofPtr<TXModParamInt> pointsMorphBackPresetD;
    ofPtr<TXModParamInt> pointsMorphBackPresetE;
    ofPtr<TXModParamFloat> pointsBackShiftX;
    ofPtr<TXModParamFloat> pointsBackShiftXEnd;
    ofParameter<bool>     pointsBackShiftXEndIgnore;
    ofPtr<TXModParamFloat> pointsBackShiftY;
    ofPtr<TXModParamFloat> pointsBackShiftYEnd;
    ofParameter<bool>     pointsBackShiftYEndIgnore;
    ofPtr<TXModParamFloat> pointsBackShiftZ;
    ofPtr<TXModParamFloat> pointsBackShiftZEnd;
    ofParameter<bool>     pointsBackShiftZEndIgnore;
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
    static const int totalNumPointsPresets = 51; // 1+20+30
    static const int totalCurvePoints = 16;
    
    TXCurvePoint arrCurvePointsFront[totalCurvePoints];
    TXCurvePoint arrCurvePointsBack[totalCurvePoints];
    TXPointOffset arrPointOffsets[totalPresetBuilderOffsets];
    vector<ofVec3f> arrFrontPoints;
    vector<ofVec3f> arrBackPoints;
    vector<ofVec3f> arrSidePoints[4];
    float controlPointsFrontData[48];
    float controlPointsBackData[48];
//    float morphPointsFrontData[48];
//    float morphPointsBackData[48];
    TXBezierSurface frontSurface;
    TXBezierSurface backSurface;
    TXBezierSurface sideSurfaces[4];

    ofMaterial material;
    of3dPrimitive groupShape;
    ofVec3f meshCentroid;
    ofVec3f pointsBackShift;
    float sizeX, sizeY, sizeZ;
    float minX, minY, minZ;
    float maxX, maxY, maxZ;
    bool surfaceHasChanged;
    bool rebuildPresetsRequested;
    bool frontNeeded;
    bool backNeeded;
    bool sidesNeeded;
    
    float planePreset[48] = {
        // Preset 0
        -0.25,-0.25,0,-0.25,-0.15,0,-0.25,-0.05,0,-0.25,0.05,0,-0.15,-0.25,0,-0.15,-0.15,0,-0.15,-0.05,0,-0.15,0.05,0,-0.05,-0.25,0,-0.05,-0.15,0,-0.05,-0.05,0,-0.05,0.05,0,0.05,-0.25,0,0.05,-0.15,0,0.05,-0.05,0,0.05,0.05,0,
    };
    float arrUserPresets[totalUserPresets][48];
    

    float arrPrebuiltPresets[30][48] = {
        // Preset 1
        0.4,0.5,0.4, 0.46666666, 0.5,0.4,0.53333332, 0.5,0.4,0.6,0.5,0.4, 0.4, 0.5,0.46666666,0.46666666, 0.5,0.46666666,0.53333332, 0.5,0.46666666,0.59999998, 0.5,0.46666666,0.4, 0.5,0.53333332,0.46666666, 0.5,0.53333332,0.53333332, 0.5,0.53333332,0.59999998, 0.5,0.53333332,0.4,0.5,0.6, 0.46666666, 0.5,0.59999998,0.53333332, 0.5,0.59999998,0.6,0.5,0.6,
        // Preset 2
        0.4,0.5,0.4, 0.459999992, 0.57202837228775,0.38,0.539999984, 0.63543456554413,0.38,0.6,0.5,0.4, 0.38, 0.64710316419601,0.459999992,0.459999992, 0.62662998199463,0.459999992,0.539999984, 0.62093903779984,0.459999992,0.619999976, 0.64408662080765,0.459999992,0.38, 0.60138579368591,0.539999984,0.459999992, 0.56378209352493,0.539999984,0.539999984, 0.63215634584427,0.539999984,0.619999976, 0.56022979974747,0.539999984,0.4,0.5,0.6, 0.459999992, 0.59612477779388,0.619999976,0.539999984, 0.65580030441284,0.619999976,0.6,0.5,0.6,
        // Preset 3
        0.4,0.5,0.4, 0.453333324, 0.80488512039185,0.36,0.546666648, 0.63818492412567,0.36,0.6,0.5,0.4, 0.36, 0.72463132858276,0.453333324,0.453333324, 0.81967217445374,0.453333324,0.546666648, 0.66822432994843,0.453333324,0.639999972, 0.81636919498444,0.453333324,0.36, 0.76947917461395,0.546666648,0.453333324, 0.81504776000977,0.546666648,0.546666648, 0.77983147621155,0.546666648,0.639999972, 0.76341297149658,0.546666648,0.4,0.5,0.6, 0.453333324, 0.7220706653595,0.639999972,0.546666648, 0.71176352024078,0.639999972,0.6,0.5,0.6,
        // Preset 4
        0.4,0.5,0.4, 0.446666656, 0.92201139211655,0.34,0.553333312, 0.73564764738083,0.34,0.6,0.5,0.4, 0.34, 0.97350848197937,0.446666656,0.446666656, 0.83117580890656,0.446666656,0.553333312, 0.97969140291214,0.446666656,0.659999968, 0.75543873786926,0.446666656,0.34, 0.70189147472382,0.553333312,0.446666656, 0.81513669967651,0.553333312,0.553333312, 0.74000326871872,0.553333312,0.659999968, 0.77845366477966,0.553333312,0.4,0.5,0.6, 0.446666656, 0.97071011543274,0.659999968,0.553333312, 0.87596458673477,0.659999968,0.6,0.5,0.6,
        // Preset 5
        0.4,0.5,0.4, 0.439999988, 0.90499533653259,0.32,0.559999976, 0.87223819732666,0.32,0.6,0.5,0.4, 0.32, 0.96677788734436,0.439999988,0.439999988, 0.98042587280273,0.439999988,0.559999976, 1.0992206478119,0.439999988,0.679999964, 0.90440291404724,0.439999988,0.32, 1.0242971324921,0.559999976,0.439999988, 0.81418084144592,0.559999976,0.559999976, 1.1254231834412,0.559999976,0.679999964, 0.78471840858459,0.559999976,0.4,0.5,0.6, 0.439999988, 0.8191552066803,0.679999964,0.559999976, 0.87377952575684,0.679999964,0.6,0.5,0.6,
        // Preset 6
        0.4,0.5,0.4, 0.53696297560825, 0.54731305837631,0.33713078022003,0.6327841264942, 0.51355065107346,0.34197432518005,0.6,0.5,0.4, 0.40743785381317, 0.5582209944725,0.37909679912656,0.53461488639011, 0.52425651550293,0.37654541038602,0.55198240110663, 0.59173406362534,0.420723121396,0.6602103064863, 0.58630678653717,0.41727316879361,0.47046075344086, 0.51678868532181,0.4625301747149,0.47105975304736, 0.57861397266388,0.51874358938394,0.58128033706931, 0.55951761007309,0.49451315687357,0.65938668950479, 0.59222874641418,0.45429306314645,0.4,0.5,0.6, 0.54135414515628, 0.53381860256195,0.5390327341297,0.62244669029501, 0.57303196191788,0.56032854387549,0.6,0.5,0.6,
        // Preset 7
        0.4,0.5,0.4, 0.53204249720251, 0.55744600296021,0.29184597969055,0.61478815278363, 0.65020554065704,0.29814170837402,0.6,0.5,0.4, 0.36443527698517, 0.68219544887543,0.38320608215875,0.48297342638647, 0.56940400600433,0.33974998074121,0.61271262368512, 0.51635544300079,0.43453993874139,0.64939783634174, 0.65337657928467,0.43299706059045,0.48906355857849, 0.53806080818176,0.4551566949953,0.63398553709662, 0.59458389282227,0.46707869683398,0.58081848820996, 0.58408887386322,0.51555884991779,0.75823231758105, 0.5503021478653,0.36416946564807,0.4,0.5,0.6, 0.49013492445624, 0.55538856983185,0.53498289338788,0.72352116307568, 0.67581334114075,0.52413232080182,0.6,0.5,0.6,
        // Preset 8
        0.4,0.5,0.4, 0.52099063203989, 0.53009753227234,0.37561913490295,0.76430636021014, 0.73715909719467,0.42665223836899,0.6,0.5,0.4, 0.39856885910034, 0.54913967847824,0.47164532792136,0.48172251985727, 0.7156298995018,0.26137684237524,0.78872243734714, 0.77779549360275,0.41308487307593,0.67159612316663, 0.66825529336929,0.45719576727911,0.54023591518402, 0.7454293847084,0.24398092769711,0.5885008315867, 0.66503864526749,0.22752972387402,0.6144279179227, 0.68779000043869,0.35491230033963,0.69844832558209, 0.68010025024414,0.28401332639783,0.4,0.5,0.6, 0.67529346750436, 0.69454001188278,0.27851086293353,0.61810465427753, 0.79614405632019,0.24435861741199,0.6,0.5,0.6,
        // Preset 9
        0.4,0.5,0.4, 0.51243918172559, 0.64243187904358,0.29287307739258,0.7114837978689, 0.71045966148376,0.21000059127808,0.6,0.5,0.4, 0.50983521461487, 0.86914639472961,0.46664652055286,0.67276885740002, 0.57933840751648,0.4444865149834,0.65195797427576, 0.89962849617004,0.10175785249255,0.99900845742346, 0.61869058609009,0.36363114541553,0.71240303039551, 0.67885675430298,0.29047003161475,0.70366819135388, 0.60685801506042,0.1108107126908,0.85112994655054, 0.64092764854431,0.26760135066077,0.69897898888708, 0.85814018249512,0.3177814043717,0.4,0.5,0.6, 0.59976499311169, 0.80156617164612,0.20704523640222,0.94307082637231, 0.74565563201904,0.14417001324243,0.6,0.5,0.6,
        // Preset 10
        0.4,0.5,0.4, 0.4776203459285, 0.86445373296738,0.15537327528,0.7268765341803, 0.87088531255722,0.38235813379288,0.6,0.5,0.4, 0.73066668510437, 0.7426570057869,0.0051757097244263,0.70630846677048, 0.91747939586639,0.41104638576508,0.8266838562056, 0.98177093267441,0.13818287849426,0.99490234428116, 0.74632108211517,0.27961212396622,0.55292491912842, 0.9523411989212,0.32514351606369,0.56086520610077, 0.79979753494263,0.24191170930862,0.68100873346771, 0.8273857831955,0.47767210006714,0.94153949790665, 0.64270162582397,0.26744508743286,0.4,0.5,0.6, 0.76367799697144, 0.91384536027908,0.0071930885314941,1.0588274967238, 0.94652926921844,0.45803672075272,0.6,0.5,0.6,
        // Preset 11
        0.4,0.5,0.4, 0.53346864138736, 0.56887450218201,0.50681408589862,0.59440123865393, 0.54723905324936,0.50686293732687,0.6,0.5,0.4, 0.43848560333252, 0.5139683008194,0.48732875370114,0.48341365014209, 0.58635506629944,0.48266720502487,0.6225372178295, 0.55055775642395,0.48902053509845,0.67980877860468, 0.54221620559692,0.52254469017661,0.40280892133713, 0.55571900606155,0.60236219928918,0.48955813799991, 0.51973439455032,0.53073358051022,0.60170898268011, 0.59931817054749,0.61288715062363,0.63131354554575, 0.51856416463852,0.56286117438083,0.4,0.5,0.6, 0.49656090890063, 0.55432044267654,0.66018050208856,0.57552684376028, 0.55671534538269,0.62651411732983,0.6,0.5,0.6,
        // Preset 12
        0.4,0.5,0.4, 0.49875878672278, 0.64421758651733,0.58915760409399,0.68730929097485, 0.69595794677734,0.59694702409833,0.6,0.5,0.4, 0.41468389987946, 0.69929888248444,0.48072072105951,0.62097951750433, 0.68491353988647,0.49974170653931,0.63562693795514, 0.6871000289917,0.63424950461066,0.70981677593219, 0.68395323753357,0.54975517503461,0.55772951602936, 0.53179664611816,0.59755479966296,0.6428893743006, 0.63219647407532,0.55726739929376,0.71191997727704, 0.62848615646362,0.60901266989929,0.64309350074756, 0.53413510322571,0.74321467230109,0.4,0.5,0.6, 0.57006801943457, 0.50347423553467,0.67595234516864,0.69542472562146, 0.52645764350891,0.77038832202722,0.6,0.5,0.6,
        // Preset 13
        0.4,0.5,0.4, 0.51963318393884, 0.57052932977676,0.73909634190149,0.81998816105243, 0.57557964324951,0.71332302962436,0.6,0.5,0.4, 0.37354560136795, 0.69240425825119,0.49628468644186,0.64396165416895, 0.58475329875946,0.60865132539383,0.67351816269275, 0.55631047487259,0.58614383505045,0.66075230974728, 0.62554494142532,0.78490560654407,0.57740185499191, 0.6309965133667,0.71566145204633,0.4714717964953, 0.61208604574203,0.74765255074179,0.63997399183627, 0.51414561271667,0.62993100342972,0.67281413216168, 0.68298999071121,0.64190059200098,0.4,0.5,0.6, 0.54164804027734, 0.53805418014526,0.61020525209149,0.78696805807468, 0.52015633583069,0.61289868900565,0.6,0.5,0.6,
        // Preset 14
        0.4,0.5,0.4, 0.55622580281934, 0.59655985832214,0.79261069082349,0.90245407565515, 0.63821449279785,0.86466435955225,0.6,0.5,0.4, 0.68773476600647, 0.51969623565674,0.7839810008385,0.71270883313855, 0.78262844085693,0.79548307387939,0.76225608333032, 0.73794441223145,0.54245463124951,0.92262491440894, 0.65130205154419,0.88917465701868,0.40342876434326, 0.83515043258667,0.66033308398291,0.77939622632703, 0.70840291976929,0.73352095757617,0.67959440692346, 0.52930364608765,0.74438001570923,0.97950963235022, 0.60924706459045,0.81755687436414,0.4,0.5,0.6, 0.51180212728223, 0.58533821105957,0.62409942965186,0.61117685779016, 0.53039717674255,0.66533291939502,0.6,0.5,0.6,
        // Preset 15
        0.4,0.5,0.4, 0.64644925055725, 0.64434605836868,0.56176181762329,0.65562275763, 0.69211721420288,0.80252166447861,0.6,0.5,0.4, 0.40356801748276, 0.55320566892624,0.73344560861588,0.48177562413437, 0.65696519613266,0.63298567264191,0.84018859978165, 0.91835963726044,0.74978728947861,0.98043701224991, 0.93195074796677,0.87162597563599,0.35551511049271, 0.91298699378967,0.44914897680283,0.56583504138214, 0.81705546379089,0.74555816381088,0.62278471107925, 0.89476799964905,0.96130009350998,0.87382176690765, 0.62129509449005,0.92381580260132,0.4,0.5,0.6, 0.53153626380188, 0.82554984092712,0.84199645249954,0.8497836362883, 0.95879173278809,0.66134579835159,0.6,0.5,0.6,
        // Preset 16
        0.4,0.5,0.4, 0.48693213199704, 0.59094488382339,0.40405412435532,0.55170690534769, 0.6395116186142,0.33380306482315,0.6,0.5,0.4, 0.46025940314992, 0.61472403764725,0.41591643487109,0.51984052577806, 0.65957754611969,0.44174908791675,0.57776488962096, 0.6239541387558,0.45836689864291,0.6744651862527, 0.63532911300659,0.4927604595293,0.49391431863111, 0.61604677200317,0.56126680443076,0.53559802609812, 0.63995307445526,0.49642088482169,0.6024223170803, 0.58000004053116,0.52313877413062,0.65758140687535, 0.65112856388092,0.49315097400931,0.4,0.5,0.6, 0.59375730248238, 0.64715238571167,0.56031042083185,0.65447946066732, 0.63180650234222,0.56935218318384,0.6,0.5,0.6,
        // Preset 17
        0.4,0.5,0.4, 0.59266320210046, 0.71756600856781,0.41470982074738,0.51210834561481, 0.78246972084045,0.31943329811096,0.6,0.5,0.4, 0.4608276871058, 0.6496546459198,0.45115794996893,0.60128723491702, 0.81495780467987,0.35658037523901,0.54674651569943, 0.63293616294861,0.47320432524359,0.60325282597708, 0.63196966171265,0.38557045321143,0.51038978209103, 0.80667042255402,0.46413827618909,0.64309688754232, 0.68575925350189,0.48878136357617,0.60639986777999, 0.69986907958984,0.54519916257214,0.77824672085091, 0.67350987911224,0.59442008218121,0.4,0.5,0.6, 0.66126883481919, 0.68623170375824,0.52967576087939,0.65334741167551, 0.65235943317413,0.58477260173785,0.6,0.5,0.6,
        // Preset 18
        0.4,0.5,0.4, 0.75936840521857, 0.95790131568909,0.42712098121643,0.69067113041013, 0.72048966169357,0.31979170799255,0.6,0.5,0.4, 0.69535735058974, 0.84169174909592,0.32221463249384,0.72550584375615, 0.72667851924896,0.55930102394281,0.56488172005931, 0.71620027303696,0.29126129673181,0.57215361677492, 0.76809071779251,0.49032272623239,0.76070972844965, 0.80448800802231,0.43536654802676,0.75353167113236, 0.94197725534439,0.59682923647281,0.66653411336875, 0.71704999685287,0.60914644094821,0.65101134617826, 0.72997845888138,0.44633621069308,0.4,0.5,0.6, 0.80727193572137, 0.68759776830673,0.76806260008389,0.83657370914596, 0.74183024644852,0.64235390085751,0.6,0.5,0.6,
        // Preset 19
        0.4,0.5,0.4, 0.674108514724, 1.0698060417175,0.22920535087585,0.58632795512244, 1.0589196586609,0.39835956573486,0.6,0.5,0.4, 0.84961257521564, 0.84435690879822,0.51950377217969,0.61784865150885, 1.0109217071533,0.25261963597974,0.66476614908197, 1.1366250419617,0.55317267171582,0.8129330076933, 1.0122150802612,0.40054587117871,0.68578257779289, 0.96130827903748,0.65086369021814,0.65595227644633, 1.0516130828857,0.41275677188318,0.96463825813505, 0.9846108341217,0.47047609790247,0.94829329309221, 1.1276857280731,0.53652200206201,0.4,0.5,0.6, 0.75142698269136, 0.98927725791931,0.52874355530859,0.66182290242939, 1.028950586319,0.60115456795813,0.6,0.5,0.6,
        // Preset 20
        0.4,0.5,0.4, 0.5508670425415, 1.245850610733,0.27685844898224,0.73197670936584, 1.0395776510239,0.41712933778763,0.6,0.5,0.4, 0.52728173216499, 0.91889147758484,0.32236337123138,0.7984619446627, 1.21715747118,0.45963328538162,0.99376401384987, 0.95455287694931,0.59291243014557,0.90586033543266, 1.0723034620285,0.20986973700745,1.003614452233, 1.0070385217667,0.5116674792334,0.93021860395879, 1.1329999446869,0.30579959269012,0.59484740768881, 0.93510209321976,0.5877600204512,0.71805086409063, 1.0309548854828,0.40868263359512,0.4,0.5,0.6, 1.0326251481382, 0.94971017837524,0.7692386942453,0.82327319129388, 0.84996204376221,0.5387095051355,0.6,0.5,0.6,
        
        // PRESETS 21-30 ARE RANDOM 
        // Preset 21
        0.4,1,0.5,0.1,0.8,0.8,1,0.6,0.3,0.2,0.9,0.7,0.2,0.3,0.9,0,0.5,0.5,0.8,0.7,0,0,0.2,1,0.5,0.3,0.5,0.4,0.5,0.3,0.6,0.6,0,0.1,0.5,0.6,0.6,1,0.2,0.7,0.9,0.6,0.1,0.8,0.9,0,0.5,0.6,
        // Preset 22
        0.2,0.3,0.6,0.3,0.7,0.2,0.9,0.6,0.4,0.8,0.3,0.5,0.4,0.8,0.9,0.8,0.7,1,0.3,0.7,0,0.7,0.7,0.7,0.6,0.1,0.5,0.2,0.5,0.5,0.2,0.9,1,0.9,0.7,0.6,0.9,0.4,0,0.2,0.4,1,0.9,0.4,0.3,0,0.7,0.4,
        // Preset 23
        0.4,0.9,0.3,1,0.6,0.2,0.6,0.3,0.1,0.6,0.6,0.2,0.1,0.7,0.7,0,0.9,0.4,1,1,0.6,0.9,0.9,0.2,0.3,0.7,0.6,0.8,0.7,1,0.2,0.7,1,0.4,0,0.3,0.5,0.4,0,0.7,0.8,0.2,1,0.3,0.5,0.3,0.5,0.5,
        // Preset 24
        1,0.8,1,0.5,1,1,0.7,0.3,0,0.7,0.3,1,0.4,0.4,1,0.6,0.6,0.8,0.4,0.5,0.3,0,0.5,0.7,0.6,1,0.4,0.4,0.1,0.1,0.7,0.7,1,0,0,0.5,1,0.4,0.9,0,0.5,0.9,0.9,0,0.5,0.7,0.5,0.4,
        // Preset 25
        0.8,0.3,1,0.7,0.4,0.9,0.8,0.3,0.2,1,0.8,0.9,0.9,0.1,0.6,0.4,0.3,0.6,0,1,0.1,0.1,0.4,0.3,0.2,0.4,1,1,0,0.5,1,0.9,0,0,0.8,0.1,0,0.3,0.7,0.1,0.8,0.6,0.6,0.1,0.2,0.9,0.4,1,
        // Preset 26
        0.8,0.9,1,0.3,0.7,0.8,0.5,1,1,0.3,0.6,0.3,0.8,0.4,0.6,0.8,0.6,0.2,0.4,0.9,0,0.8,0.3,0.8,0.3,0.8,0.3,0.6,0.6,0.1,0.2,0.6,0.1,0.8,0.6,0.4,0,0.1,0.2,0.1,0,1,0,0.8,0.2,0.1,0.4,0.6,
        // Preset 27
        0.6,0.4,0.4,1,0.3,0.9,0.5,0,0.2,1,0.1,0.1,0.4,0,0.5,0.2,0.1,0.2,0,0.5,0,0.2,0.5,0.8,0.1,0.7,0,0,0.8,0.2,0.2,0.6,0.1,0.2,0.9,0.5,0.6,0.1,0.1,0.7,0.8,0.8,0.6,0.2,1,0.4,0.1,0.8,
        // Preset 28
        0.1,0.6,0.9,0.1,0.7,0.3,0.4,0,0.2,0.2,0.3,0.4,0.3,0.7,1,0.4,0.7,0,0.4,0.4,0.6,0.7,1,0.2,0.5,0.4,0.3,0.3,0.1,0.4,0.1,1,0.6,0.1,0,0.3,0.9,0.7,0.7,1,0.1,0.5,0.5,0.7,0.1,0.3,0.4,0.6,
        // Preset 29
        0,0.4,0.3,1,0.5,0.7,1,0.7,0.8,0.4,0.5,0.9,0.2,0.2,0.6,0.8,0.1,1,0.9,0.6,0.3,0.1,0.8,0.3,1,1,0,1,0.7,0.2,0.6,0.1,1,0,0.5,0.3,0.2,0.7,0,0.8,0.7,0.6,0.1,0.7,0.1,0.5,0.9,0.8,
        // Preset 30
        1,1,0,0.7,0.9,0.2,0.3,0,0.7,0.6,0.7,0,0.6,0.9,0.4,0.2,0.5,0.2,0.7,0.2,0.3,1,0.8,1,0.7,1,0.7,1,0.9,1,0.3,0.4,0.9,0.9,0.9,0.5,0.5,0.2,0.6,0.2,0.1,1,0.5,0.2,0.5,0.8,0.9,0.5,
    };
    
 };

