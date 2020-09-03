/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXDrawBase.h"
#include "TXLFO.h"
#include "TXPerlin.h"
#include "TXParaShape.h"

//enum TXSHAPE3DTYPE {
//    TXSHAPE3DTYPE_SPHERE,
//    TXSHAPE3DTYPE_ICOSPHERE,
//    TXSHAPE3DTYPE_BOX,
//    TXSHAPE3DTYPE_PLANE,
//    TXSHAPE3DTYPE_CYLINDER,
//    TXSHAPE3DTYPE_ROUNDEDCYLINDER,
//    TXSHAPE3DTYPE_UNCAPPEDCYLINDER,
//    TXSHAPE3DTYPE_CONE,
//    TXSHAPE3DTYPE_ROUNDEDCONE,
//    TXSHAPE3DTYPE_UNCAPPEDCONE,
//    //    TXSHAPE3DTYPE_ICOSAHEDRON,  // not working yet
//};
//
//enum TXSHAPE3DDISTORTORDER {
//    TXSHAPE3DDISTORTORDER_WAVETWISTBEND,
//    TXSHAPE3DDISTORTORDER_WAVEBENDTWIST,
//    TXSHAPE3DDISTORTORDER_TWISTBENDWAVE,
//    TXSHAPE3DDISTORTORDER_TWISTWAVEBEND,
//    TXSHAPE3DDISTORTORDER_BENDTWISTWAVE,
//    TXSHAPE3DDISTORTORDER_BENDWAVETWIST,
//    TXSHAPE3DDISTORTORDER_TOTAL
//};
//
//enum TXSHAPE3DDISTORTWAVEFORM {
//    TXSHAPE3DDISTORTWAVEFORM_SINE,
//    TXSHAPE3DDISTORTWAVEFORM_COSINE,
//    TXSHAPE3DDISTORTWAVEFORM_SQUARE,
//    TXSHAPE3DDISTORTWAVEFORM_RAMPUP,
//    TXSHAPE3DDISTORTWAVEFORM_RAMPDOWN,
//    TXSHAPE3DDISTORTWAVEFORM_TRIANGLE,
//    TXSHAPE3DDISTORTWAVEFORM_CUSTOMCURVE,
//    TXSHAPE3DDISTORTWAVEFORM_CUSTOMCURVE_MIRRORED,
//};
//
//enum TXSHAPE3DDISTORTWAVE {
//    TXSHAPE3DDISTORTWAVE_WAVE1,
//    TXSHAPE3DDISTORTWAVE_WAVE2,
//    TXSHAPE3DDISTORTWAVE_WAVE3,
//    TXSHAPE3DDISTORTWAVE_PERLIN1,
//    TXSHAPE3DDISTORTWAVE_PERLIN2,
//    TXSHAPE3DDISTORTWAVE_PERLIN3,
//    TXSHAPE3DDISTORTWAVE_TOTAL
//};
//
//enum TXSHAPE3DDISTORTAXIS {
//    TXSHAPE3DDISTORTAXIS_POSXONY,
//    TXSHAPE3DDISTORTAXIS_POSXONZ,
//    TXSHAPE3DDISTORTAXIS_POSYONX,
//    TXSHAPE3DDISTORTAXIS_POSYONZ,
//    TXSHAPE3DDISTORTAXIS_POSZONX,
//    TXSHAPE3DDISTORTAXIS_POSZONY,
//    TXSHAPE3DDISTORTAXIS_POSYZRADIALONX,
//    TXSHAPE3DDISTORTAXIS_POSXZRADIALONY,
//    TXSHAPE3DDISTORTAXIS_POSXYRADIALONZ,
//    TXSHAPE3DDISTORTAXIS_TOTAL
//};
//
//enum TXSHAPE3DDISTORTTYPE {
//    TXSHAPE3DDISTORTTYPE_MULTIPLYALL,
//    TXSHAPE3DDISTORTTYPE_MULTIPLYPOS,
//    TXSHAPE3DDISTORTTYPE_MULTIPLYNEG,
//    TXSHAPE3DDISTORTTYPE_ADDALL,
//    TXSHAPE3DDISTORTTYPE_ADDPOSSUBTRACTNEG,
//    TXSHAPE3DDISTORTTYPE_ADDPOS,
//    TXSHAPE3DDISTORTTYPE_SUBTRACTNEG,
//    TXSHAPE3DDISTORTTYPE_TOTAL
//};

enum TXSHAPEMULTI3DDISTORTTARGET {
    TXSHAPEMULTI3DDISTORTTARGET_UNIT,
    TXSHAPEMULTI3DDISTORTTARGET_GROUP,
    TXSHAPEMULTI3DDISTORTTARGET_UNITANDGROUP,
};

class TXDrawShape3DMulti  :  public TXDrawBase
{
public:
    
    // NOTE - change when adding new types:
    static const int total3DShapeTypes = (10 + TXParaShape::totalShapes);
    static const int totalDistortionWaveTypes = 8;
    static const int totalPerlinTypes = TXPerlin::totalPerlinTypes;
    static const int numBendTypes = 33;
    static const int maxCopies = 100;

	// constructor
	TXDrawShape3DMulti();

    // destructor
    ~TXDrawShape3DMulti();
    
    // methods
	void setup();
	virtual void update();
	virtual void draw();
    bool applyDistortion(ofVboMesh &inputMesh, ofVboMesh &distortMesh, float sizeX, float sizeY, float sizeZ, int target);
    
    void imageAssetSlotChanged(string slotNameArg);
    void  useImageAsTextureChanged(bool & boolArg);
    void  useExternalSourceImageChanged(bool & boolArg);
    
    void loadSourceImage();
    bool mapTextureToShape();
    int getTextureWidth(); // overide base class
    int getTextureHeight(); // overide base class
    ofTexture *  getTexture(); // overide base class
    ofPixelsRef getPixels(); // overide base class
    float getWaveValue(int & waveType, float & phase, TXParameterFloat256 & customCurve, TXParameterFloat256 & customCurve2, float customCurveMorph);
    float getPerlinValue(int & perlinType, float & perlinFreq, float & perlinOffset, ofVec3f & position, float & argSizeX, float & argSizeY, float & argSizeZ);
    void buildRoundedCylinder(float height, float roundness);
    void buildRoundedCone(float height, float roundness);
    bool isParaShape();

    // listener methods
    void shapeTypeChanged(ofAbstractParameter & parameterArg );
    void  resolutionParaShapeChanged(int & intArg);
    
    // parameters
    
    ofParameter<bool> useImageAsTexture;
    ofParameter<bool> useExternalSourceImage;

    ofPtr<TXModParamInt> shapeType;
    ofPtr<TXModParamInt> numCopies;
    ofParameter<bool>     mergeIntoSuperShape;
    ofPtr<TXModParamBool> fillShape;
    ofPtr<TXModParamInt> distortOrder;
    ofPtr<TXModParamFloat> width;
    ofPtr<TXModParamFloat> widthEnd;
    ofParameter<bool>     widthEndIgnore;
    ofPtr<TXModParamFloat> height;
    ofPtr<TXModParamFloat> heightEnd;
    ofParameter<bool>     heightEndIgnore;
    ofParameter<bool>     useMaxWidthToScaleHeight;
    ofPtr<TXModParamFloat> depth;
    ofPtr<TXModParamFloat> depthEnd;
    ofParameter<bool>     depthEndIgnore;
    ofParameter<bool>     useMaxWidthToScaleDepth;
    ofPtr<TXModParamFloat> radius;
    ofPtr<TXModParamFloat> radiusEnd;
    ofParameter<bool>     radiusEndIgnore;
    ofPtr<TXModParamFloat> roundness;
    ofPtr<TXModParamFloat> roundnessEnd;
    ofParameter<bool>     roundnessEndIgnore;
    ofPtr<TXModParamInt> resolutionWidth;
    ofPtr<TXModParamInt> resolutionHeight;
    ofPtr<TXModParamInt> resolutionDepth;
    ofPtr<TXModParamInt> resolutionRadius;
    ofPtr<TXModParamInt> resolutionIsoSphere;
    ofPtr<TXModParamInt> resolutionCap;
    ofParameter<int>      resolutionParaShape;
    ofParameter<bool>     smoothDistortedParaShape;
    TXParameterFloat256   sizeSpreadCurve;
    TXParameterFloat256   sizeSpreadCurve2;
    ofPtr<TXModParamFloat> sizeSpreadCurveMorph;
    ofPtr<TXModParamFloat> sizeSpreadCurvePhase;

    ofPtr<TXModParamFloat> x1;
    ofPtr<TXModParamFloat> x1End;
    ofParameter<bool>     x1EndIgnore;
    ofParameter<bool>     x1Quantize;
    ofPtr<TXModParamFloat> x2;
    ofPtr<TXModParamFloat> x2End;
    ofParameter<bool>     x2EndIgnore;
    ofParameter<bool>     x2Quantize;
    ofPtr<TXModParamFloat> x3;
    ofPtr<TXModParamFloat> x3End;
    ofParameter<bool>     x3EndIgnore;
    ofParameter<bool>     x3Quantize;
    ofPtr<TXModParamFloat> y1;
    ofPtr<TXModParamFloat> y1End;
    ofParameter<bool>     y1EndIgnore;
    ofParameter<bool>     y1Quantize;
    ofPtr<TXModParamFloat> y2;
    ofPtr<TXModParamFloat> y2End;
    ofParameter<bool>     y2EndIgnore;
    ofParameter<bool>     y2Quantize;
    ofPtr<TXModParamFloat> y3;
    ofPtr<TXModParamFloat> y3End;
    ofParameter<bool>     y3EndIgnore;
    ofParameter<bool>     y3Quantize;
    ofPtr<TXModParamFloat> z1;
    ofPtr<TXModParamFloat> z1End;
    ofParameter<bool>     z1EndIgnore;
    ofParameter<bool>     z1Quantize;
    ofPtr<TXModParamFloat> z2;
    ofPtr<TXModParamFloat> z2End;
    ofParameter<bool>     z2EndIgnore;
    ofParameter<bool>     z2Quantize;
    ofPtr<TXModParamFloat> z3;
    ofPtr<TXModParamFloat> z3End;
    ofParameter<bool>     z3EndIgnore;
    ofParameter<bool>     z3Quantize;
    ofParameter<bool>     useXValsForY;
    ofParameter<bool>     useXValsForZ;
    ofParameter<bool>     ignoreAllXYZVals;
    TXParameterFloat256   xyzValsSpreadCurve;
    TXParameterFloat256   xyzValsSpreadCurve2;
    ofPtr<TXModParamFloat> xyzValsSpreadCurveMorph;
    ofPtr<TXModParamFloat> xyzValsSpreadCurvePhase;

    ofPtr<TXModParamFloat> positionX;
    ofPtr<TXModParamFloat> positionXEnd;
    ofParameter<bool>     positionXEndIgnore;
    ofPtr<TXModParamFloat> positionY;
    ofPtr<TXModParamFloat> positionYEnd;
    ofParameter<bool>     positionYEndIgnore;
    ofPtr<TXModParamFloat> positionZ;
    ofPtr<TXModParamFloat> positionZEnd;
    ofParameter<bool>     positionZEndIgnore;
    TXParameterFloat256   positionXSpreadCurve;
    TXParameterFloat256   positionXSpreadCurve2;
    ofPtr<TXModParamFloat> positionXSpreadCurveMorph;
    ofPtr<TXModParamFloat> positionXSpreadCurvePhase;
    ofParameter<bool>      usePosXSpreadCurveForPosY;
    TXParameterFloat256   positionYSpreadCurve;
    TXParameterFloat256   positionYSpreadCurve2;
    ofPtr<TXModParamFloat> positionYSpreadCurveMorph;
    ofPtr<TXModParamFloat> positionYSpreadCurvePhase;
    ofParameter<bool>      usePosXSpreadCurveForPosZ;
    TXParameterFloat256   positionZSpreadCurve;
    TXParameterFloat256   positionZSpreadCurve2;
    ofPtr<TXModParamFloat> positionZSpreadCurveMorph;
    ofPtr<TXModParamFloat> positionZSpreadCurvePhase;
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
    TXParameterFloat256   rotateXSpreadCurve;
    TXParameterFloat256   rotateXSpreadCurve2;
    ofPtr<TXModParamFloat> rotateXSpreadCurveMorph;
    ofPtr<TXModParamFloat> rotateXSpreadCurvePhase;
    ofParameter<bool>     useRotateXSpreadCurveForRotateY;
    TXParameterFloat256   rotateYSpreadCurve;
    TXParameterFloat256   rotateYSpreadCurve2;
    ofPtr<TXModParamFloat> rotateYSpreadCurveMorph;
    ofPtr<TXModParamFloat> rotateYSpreadCurvePhase;
    ofParameter<bool>     useRotateXSpreadCurveForRotateZ;
    TXParameterFloat256   rotateZSpreadCurve;
    TXParameterFloat256   rotateZSpreadCurve2;
    ofPtr<TXModParamFloat> rotateZSpreadCurveMorph;
    ofPtr<TXModParamFloat> rotateZSpreadCurvePhase;
    TXParameterFloat256   rotateMultiplySpreadCurve;
    TXParameterFloat256   rotateMultiplySpreadCurve2;
    ofPtr<TXModParamFloat> rotateMultiplySpreadCurveMorph;
    ofPtr<TXModParamFloat> rotateMultiplySpreadCurvePhase;
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
    ofPtr<TXModParamFloat> anchorSpreadCurvePhase;
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
    TXParameterFloat256   scaleXSpreadCurve;
    TXParameterFloat256   scaleXSpreadCurve2;
    ofPtr<TXModParamFloat> scaleXSpreadCurveMorph;
    ofPtr<TXModParamFloat> scaleXSpreadCurvePhase;
    ofParameter<bool>     useScaleXSpreadCurveForScaleY;
    TXParameterFloat256   scaleYSpreadCurve;
    TXParameterFloat256   scaleYSpreadCurve2;
    ofPtr<TXModParamFloat> scaleYSpreadCurveMorph;
    ofPtr<TXModParamFloat> scaleYSpreadCurvePhase;
    ofParameter<bool>     useScaleXSpreadCurveForScaleZ;
    TXParameterFloat256   scaleZSpreadCurve;
    TXParameterFloat256   scaleZSpreadCurve2;
    ofPtr<TXModParamFloat> scaleZSpreadCurveMorph;
    ofPtr<TXModParamFloat> scaleZSpreadCurvePhase;

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
    ofPtr<TXModParamFloat> colorSpreadCurvePhase;

    // mesh distortion:
    // oscillation
    ofPtr<TXModParamBool> waveDistortActive;  
    ofPtr<TXModParamInt> wave1Type;
    ofPtr<TXModParamFloat> wave1Phase;
    ofPtr<TXModParamFloat> wave1Freq;
    ofPtr<TXModParamInt> wave2Type;
    ofPtr<TXModParamFloat> wave2Phase;
    ofPtr<TXModParamFloat> wave2Freq;
    ofPtr<TXModParamInt> wave3Type;
    ofPtr<TXModParamFloat> wave3Phase;
    ofPtr<TXModParamFloat> wave3Freq;
    ofPtr<TXModParamInt> wave4Type;
    ofPtr<TXModParamFloat> wave4Phase;
    ofPtr<TXModParamFloat> wave4Freq;
    ofPtr<TXModParamInt> wave5Type;
    ofPtr<TXModParamFloat> wave5Phase;
    ofPtr<TXModParamFloat> wave5Freq;
    TXParameterFloat256   wave1CustomCurve;
    TXParameterFloat256   wave1CustomCurve2;
    ofPtr<TXModParamFloat> wave1CustomCurveMorph;
    TXParameterFloat256   wave2CustomCurve;
    TXParameterFloat256   wave2CustomCurve2;
    ofPtr<TXModParamFloat> wave2CustomCurveMorph;
    TXParameterFloat256   wave3CustomCurve;
    TXParameterFloat256   wave3CustomCurve2;
    ofPtr<TXModParamFloat> wave3CustomCurveMorph;
    TXParameterFloat256   wave4CustomCurve;
    TXParameterFloat256   wave4CustomCurve2;
    ofPtr<TXModParamFloat> wave4CustomCurveMorph;
    TXParameterFloat256   wave5CustomCurve;
    TXParameterFloat256   wave5CustomCurve2;
    ofPtr<TXModParamFloat> wave5CustomCurveMorph;
    ofPtr<TXModParamInt> perlin1Type;
    ofPtr<TXModParamFloat> perlin1Offset;
    ofPtr<TXModParamFloat> perlin1Freq;
    ofPtr<TXModParamInt> perlin2Type;
    ofPtr<TXModParamFloat> perlin2Offset;
    ofPtr<TXModParamFloat> perlin2Freq;
    ofPtr<TXModParamInt> perlin3Type;
    ofPtr<TXModParamFloat> perlin3Offset;
    ofPtr<TXModParamFloat> perlin3Freq;
    ofParameter<bool>     waveDistort1On;
    ofParameter<int>      waveDistort1Target;
    ofPtr<TXModParamFloat> waveDistort1Depth;
    ofPtr<TXModParamInt> waveDistort1Waveform;
    ofPtr<TXModParamInt> waveDistort1Axis;
    ofPtr<TXModParamInt> waveDistort1Type;
    ofParameter<bool>     waveDistort2On;
    ofParameter<int>      waveDistort2Target;
    ofPtr<TXModParamFloat> waveDistort2Depth;
    ofPtr<TXModParamInt> waveDistort2Waveform;
    ofPtr<TXModParamInt> waveDistort2Axis;
    ofPtr<TXModParamInt> waveDistort2Type;
    ofParameter<bool>     waveDistort3On;
    ofParameter<int>      waveDistort3Target;
    ofPtr<TXModParamFloat> waveDistort3Depth;
    ofPtr<TXModParamInt> waveDistort3Waveform;
    ofPtr<TXModParamInt> waveDistort3Axis;
    ofPtr<TXModParamInt> waveDistort3Type;
    ofParameter<bool>     waveDistort4On;
    ofParameter<int>      waveDistort4Target;
    ofPtr<TXModParamFloat> waveDistort4Depth;
    ofPtr<TXModParamInt> waveDistort4Waveform;
    ofPtr<TXModParamInt> waveDistort4Axis;
    ofPtr<TXModParamInt> waveDistort4Type;
    ofParameter<bool>     waveDistort5On;
    ofParameter<int>      waveDistort5Target;
    ofPtr<TXModParamFloat> waveDistort5Depth;
    ofPtr<TXModParamInt> waveDistort5Waveform;
    ofPtr<TXModParamInt> waveDistort5Axis;
    ofPtr<TXModParamInt> waveDistort5Type;
    ofParameter<bool>     waveDistort6On;
    ofParameter<int>      waveDistort6Target;
    ofPtr<TXModParamFloat> waveDistort6Depth;
    ofPtr<TXModParamInt> waveDistort6Waveform;
    ofPtr<TXModParamInt> waveDistort6Axis;
    ofPtr<TXModParamInt> waveDistort6Type;
    
    // twist & bend focus
    ofPtr<TXModParamFloat> focusPointX;
    ofPtr<TXModParamFloat> focusPointY;
    ofPtr<TXModParamFloat> focusPointZ;

    // twist
    ofPtr<TXModParamBool> twistActive;
    ofParameter<int>      twistTarget;
    ofPtr<TXModParamFloat> twistPhase;
    ofPtr<TXModParamInt> twistAxis; // 0=X/ 1=Y/ 2=Z
    ofPtr<TXModParamFloat> twistFreq;
    ofPtr<TXModParamBool> twistMiddleReverse;
    ofPtr<TXModParamBool> useCentroidForTwistFocusPoint;
    
    // bend
    ofPtr<TXModParamBool> bendActive;
    ofParameter<int>      bendTarget;
    ofPtr<TXModParamFloat> bendRadius;
    ofPtr<TXModParamInt> bendType;
    ofPtr<TXModParamBool> bendInflationEffect;
    ofPtr<TXModParamFloat> bendAmountX;
    ofPtr<TXModParamFloat> bendAmountY;
    ofPtr<TXModParamFloat> bendAmountZ;
    ofPtr<TXModParamBool> useCentroidForBendFocusPoint;
    
private:
    ofImage holdImage1;
    ofImage holdImage2;
    ofImage * sourceImage;
    ofImage * newImage;
    ofMaterial material;

    void setDistortOrderIndices(int argA, int argB, int argC);
    void calcDistortedMeshNormals(ofVboMesh &distortedMesh, bool bNormalize = true);
    void distortVertex(ofVec3f & argVertex, float argDepth, int argWaveform, int argAxis, int argType, float argSizeX, float argSizeY, float argSizeZ);

    int distortOrderIndices[4];
    bool sourceImageHasChanged;
    
    ofSpherePrimitive sphere;
    ofIcoSpherePrimitive icoSphere;
    ofCylinderPrimitive cylinder;
    ofConePrimitive cone;
    ofBoxPrimitive box;
    ofPlanePrimitive plane;
    of3dPrimitive roundedCylinder;
    of3dPrimitive roundedCone;
    of3dPrimitive icosahedron;
    of3dPrimitive uncappedCone;
    of3dPrimitive paraShape;
    TXParaShape paraBuilder;
    ofPtr<TXParametricSurfaceBase> paraSurface;
    ofVec3f meshCentroid;
    
    of3dPrimitive * shapePtr;
    of3dPrimitive groupShape;
    vector<ofMeshFace> triangles;
    ofVboMesh roundedTopCapMesh;
    ofVboMesh roundedBottomCapMesh;

    float accumlator;
    float flipper;
    bool applyPosDistortion;
    bool retryMapTexture;
    bool resolutionParaShapeHasChanged = true;
    
    float sizeX, sizeY, sizeZ;
    int texWidth = 1;
    int texHeight = 1;
    bool invertDistortedNormals;

    int   holdwave1Type, holdwave2Type, holdwave3Type, holdwave4Type, holdwave5Type;
    float holdwave1Phase, holdwave2Phase, holdwave3Phase, holdwave4Phase, holdwave5Phase;
    float holdwave1CustomCurveMorph, holdwave2CustomCurveMorph, holdwave3CustomCurveMorph, holdwave4CustomCurveMorph, holdwave5CustomCurveMorph;
    int   holdperlin1Type, holdperlin2Type, holdperlin3Type;
    float holdperlin1Freq, holdperlin2Freq, holdperlin3Freq;
    float holdperlin1Offset, holdperlin2Offset, holdperlin3Offset;
    float holdwave1Freq, holdwave2Freq, holdwave3Freq, holdwave4Freq, holdwave5Freq;
    ofVec2f holdDistortVector;
};



