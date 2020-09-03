/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

// NOTE: THIS IS THE OLD VERSION - NEW VERSION IS TXDrawShape3D

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
//    TXSHAPE3DDISTORTWAVE_WAVE4,
//    TXSHAPE3DDISTORTWAVE_WAVE5,
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

class TXDrawShape3D  :  public TXDrawBase
{
public:
    
    // NOTE - change when adding new types:
    static const int total3DShapeTypes = (10 + TXParaShape::totalShapes);
    static const int totalDistortionWaveTypes = 8;
    static const int totalPerlinTypes = TXPerlin::totalPerlinTypes;
    static const int numBendTypes = 33;

	// constructor
	TXDrawShape3D();

    // destructor
    ~TXDrawShape3D();
    
    // methods
	void setup(string paramNamePrefixArg = "");
	virtual void update();
	virtual void draw();
    
    void windowResized(int w, int h);
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

    ofColor getCurrentDiffuseColor();
    ofColor getCurrentAmbientColor();
    ofColor getCurrentSpecularColor();
    ofColor getCurrentEmissiveColor();
    void setMaterialDiffuseColor(ofColor colorArg);
    void setMaterialAmbientColor(ofColor colorArg);
    void setMaterialSpecularColor(ofColor colorArg);
    void setMaterialEmissiveColor(ofColor colorArg);
    void materialShininessChanged(ofAbstractParameter & parameterArg );
    void materialDiffuseColorChanged(ofAbstractParameter & parameterArg );
    void materialAmbientColorChanged(ofAbstractParameter & parameterArg );
    void materialSpecularColorChanged(ofAbstractParameter & parameterArg );
    void materialEmissiveColorChanged(ofAbstractParameter & parameterArg );
    void useDiffuseColorForAmbientChanged(bool & boolArg);
    void useDiffuseColorForSpecularChanged(bool & boolArg);
    void useDiffuseColorForEmissiveChanged(bool & boolArg);

    // parameters
    
    ofParameter<bool> useImageAsTexture;
    ofParameter<bool> useExternalSourceImage;

    ofPtr<TXModParamInt> shapeType;
    ofPtr<TXModParamBool> fillShape;
    ofPtr<TXModParamInt> distortOrder;
    ofPtr<TXModParamFloat> width;
    ofPtr<TXModParamFloat> height;
    ofParameter<bool>     useMaxWidthToScaleHeight;
    ofPtr<TXModParamFloat> depth;
    ofParameter<bool>     useMaxWidthToScaleDepth;
    ofPtr<TXModParamFloat> radius;
    ofPtr<TXModParamFloat> roundness;
    ofPtr<TXModParamInt> resolutionWidth;
    ofPtr<TXModParamInt> resolutionHeight;
    ofPtr<TXModParamInt> resolutionDepth;
    ofPtr<TXModParamInt> resolutionRadius;
    ofPtr<TXModParamInt> resolutionIsoSphere;
    ofPtr<TXModParamInt> resolutionCap;
    ofParameter<int>      resolutionParaShape;
    ofParameter<bool>     smoothDistortedParaShape;
    
    ofPtr<TXModParamFloat> x1;
    ofParameter<bool>  x1Quantize;
    ofPtr<TXModParamFloat> x2;
    ofParameter<bool>  x2Quantize;
    ofPtr<TXModParamFloat> x3;
    ofParameter<bool>  x3Quantize;
    ofPtr<TXModParamFloat> y1;
    ofParameter<bool>  y1Quantize;
    ofPtr<TXModParamFloat> y2;
    ofParameter<bool>  y2Quantize;
    ofPtr<TXModParamFloat> y3;
    ofParameter<bool>  y3Quantize;
    ofPtr<TXModParamFloat> z1;
    ofParameter<bool>  z1Quantize;
    ofPtr<TXModParamFloat> z2;
    ofParameter<bool>  z2Quantize;
    ofPtr<TXModParamFloat> z3;
    ofParameter<bool>  z3Quantize;
    ofParameter<bool>  useXValsForY;
    ofParameter<bool>  useXValsForZ;
    ofParameter<bool>  ignoreAllXYZVals;
    
    ofPtr<TXModParamFloat> positionX;
    ofPtr<TXModParamFloat> positionY;
    ofPtr<TXModParamFloat> positionZ;
    ofPtr<TXModParamFloat> rotateX;
    ofPtr<TXModParamFloat> rotateY;
    ofPtr<TXModParamFloat> rotateZ;
    ofPtr<TXModParamFloat> rotateMultiply;
    ofPtr<TXModParamFloat> anchorX;
    ofPtr<TXModParamFloat> anchorY;
    ofPtr<TXModParamFloat> anchorZ;
    ofPtr<TXModParamFloat> scaleX;
    ofPtr<TXModParamFloat> scaleY;
    ofPtr<TXModParamFloat> scaleZ;
    ofParameter<bool> useScaleXForScaleY;
    ofParameter<bool> useScaleXForScaleZ;

	// material:
    ofPtr<TXModParamFloat> materialShininess; // 0 - 128
    ofPtr<TXModParamFloat> materialDiffuseColorHue;
    ofPtr<TXModParamFloat> materialDiffuseColorHueRotate;
    ofPtr<TXModParamFloat> materialDiffuseColorSaturation;
    ofPtr<TXModParamFloat> materialDiffuseColorBrightness;
    ofPtr<TXModParamBool> materialDiffuseColorHSBAsRGB;
    ofParameter<bool> useDiffuseColorForAmbient;
    ofPtr<TXModParamFloat> materialAmbientColorHue;
    ofPtr<TXModParamFloat> materialAmbientColorHueRotate;
    ofPtr<TXModParamFloat> materialAmbientColorSaturation;
    ofPtr<TXModParamFloat> materialAmbientColorBrightness;
    ofPtr<TXModParamBool> materialAmbientColorHSBAsRGB;
    ofParameter<bool> useDiffuseColorForSpecular;
    ofPtr<TXModParamFloat> materialSpecularColorHue;
    ofPtr<TXModParamFloat> materialSpecularColorHueRotate;
    ofPtr<TXModParamFloat> materialSpecularColorSaturation;
    ofPtr<TXModParamFloat> materialSpecularColorBrightness;
    ofPtr<TXModParamBool> materialSpecularColorHSBAsRGB;
    ofParameter<bool> useDiffuseColorForEmissive;
    ofPtr<TXModParamFloat> materialEmissiveColorHue;
    ofPtr<TXModParamFloat> materialEmissiveColorHueRotate;
    ofPtr<TXModParamFloat> materialEmissiveColorSaturation;
    ofPtr<TXModParamFloat> materialEmissiveColorBrightness;
    ofPtr<TXModParamBool> materialEmissiveColorHSBAsRGB;

    // mesh distortion:
    // oscillation
    ofPtr<TXModParamBool> waveDistortActive;  // bool
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
    ofPtr<TXModParamFloat> waveDistort1Depth;
    ofPtr<TXModParamInt> waveDistort1Waveform;
    ofPtr<TXModParamInt> waveDistort1Axis;
    ofPtr<TXModParamInt> waveDistort1Type;
    ofParameter<bool>     waveDistort2On;
    ofPtr<TXModParamFloat> waveDistort2Depth;
    ofPtr<TXModParamInt> waveDistort2Waveform;
    ofPtr<TXModParamInt> waveDistort2Axis;
    ofPtr<TXModParamInt> waveDistort2Type;
    ofParameter<bool>     waveDistort3On;
    ofPtr<TXModParamFloat> waveDistort3Depth;
    ofPtr<TXModParamInt> waveDistort3Waveform;
    ofPtr<TXModParamInt> waveDistort3Axis;
    ofPtr<TXModParamInt> waveDistort3Type;
    ofParameter<bool>     waveDistort4On;
    ofPtr<TXModParamFloat> waveDistort4Depth;
    ofPtr<TXModParamInt> waveDistort4Waveform;
    ofPtr<TXModParamInt> waveDistort4Axis;
    ofPtr<TXModParamInt> waveDistort4Type;
    ofParameter<bool>     waveDistort5On;
    ofPtr<TXModParamFloat> waveDistort5Depth;
    ofPtr<TXModParamInt> waveDistort5Waveform;
    ofPtr<TXModParamInt> waveDistort5Axis;
    ofPtr<TXModParamInt> waveDistort5Type;
    ofParameter<bool>     waveDistort6On;
    ofPtr<TXModParamFloat> waveDistort6Depth;
    ofPtr<TXModParamInt> waveDistort6Waveform;
    ofPtr<TXModParamInt> waveDistort6Axis;
    ofPtr<TXModParamInt> waveDistort6Type;

    // twist & bend focus
    ofPtr<TXModParamFloat> focusPointX;
    ofPtr<TXModParamFloat> focusPointY;
    ofPtr<TXModParamFloat> focusPointZ;

    // twist
    ofPtr<TXModParamBool> twistActive;  // bool
    ofPtr<TXModParamFloat> twistPhase;
    ofPtr<TXModParamInt> twistAxis; // 0=X/ 1=Y/ 2=Z
    ofPtr<TXModParamFloat> twistFreq;
    ofPtr<TXModParamBool> twistMiddleReverse;
    ofPtr<TXModParamBool> useCentroidForTwistFocusPoint;
    
    // bend
    ofPtr<TXModParamBool> bendActive;  // bool
    ofPtr<TXModParamFloat> bendRadius;
    ofPtr<TXModParamInt> bendType;
    ofPtr<TXModParamBool> bendInflationEffect;  // bool
    ofPtr<TXModParamFloat> bendAmountX;
    ofPtr<TXModParamFloat> bendAmountY;
    ofPtr<TXModParamFloat> bendAmountZ;
    ofPtr<TXModParamBool> useCentroidForBendFocusPoint;
    
private:
    ofImage holdImage1;
    ofImage holdImage2;
    ofImage * sourceImage;
    ofImage * newImage;
    string paramNamePrefix;
    ofMaterial material;
    
    void setDistortOrderIndices(int argA, int argB, int argC);
    void calcDistortedMeshNormals(bool bNormalize = true);
    void distortVertex(ofVec3f & argVertex, float argDepth, int argWaveform, int argAxis, int argType, float argSizeX, float argSizeY, float argSizeZ);

    int distortOrderIndices[3];
    bool sourceImageHasChanged;
    
    ofSpherePrimitive sphere;
    ofIcoSpherePrimitive icoSphere;
    ofCylinderPrimitive cylinder;
    ofConePrimitive cone;
    ofBoxPrimitive box;
    ofPlanePrimitive plane;
    of3dPrimitive roundedCylinder;
    of3dPrimitive roundedCone;
//    of3dPrimitive icosahedron;
    of3dPrimitive uncappedCone;
    of3dPrimitive paraShape;
    TXParaShape paraBuilder;
    ofPtr<TXParametricSurfaceBase> paraSurface;
    ofVec3f paraMeshCentroid;

    of3dPrimitive * shapePtr;
    of3dPrimitive distortedShape;
    ofVboMesh distortedMesh;
    ofVboMesh icosahedronMesh;
    ofVboMesh roundedTopCapMesh;
    ofVboMesh roundedBottomCapMesh;
    ofMesh tempMesh;

    float accumlator;
    float flipper;
    bool applyPosDistortion;
    bool retryMapTexture;
    bool resolutionParaShapeHasChanged = true;

    bool materialDiffuseColorHasChanged;
    bool materialAmbientColorHasChanged;
    bool materialSpecularColorHasChanged;
    bool materialEmissiveColorHasChanged;

    float sizeX, sizeY, sizeZ;
    int texWidth = 0;
    int texHeight = 0;
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

