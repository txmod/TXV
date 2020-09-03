/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXDrawLayersBase.h"
//#include "TXMain.h"

enum TXMESHDISTORTWAVETYPE {
    TXMESHDISTORTWAVETYPE_SINE,
    TXMESHDISTORTWAVETYPE_COSINE,
    TXMESHDISTORTWAVETYPE_SQUARE,
    TXMESHDISTORTWAVETYPE_RAMPUP,
    TXMESHDISTORTWAVETYPE_RAMPDOWN,
    TXMESHDISTORTWAVETYPE_TRIANGLE,
    TXMESHDISTORTWAVETYPE_PERLIN,
    TXMESHDISTORTWAVETYPE_TOTAL,
};

//enum TXLIGHTTYPE {TXLIGHTTYPE_POINT, TXLIGHTTYPE_DIRECTIONAL, TXLIGHTTYPE_SPOT, TXLIGHTTYPE_TOTAL};
//
//enum TXCAMERAPOSITIONMODE {TXCAMERAPOSITIONMODE_USEPOSITIONXYZ, TXCAMERAPOSITIONMODE_TRUCKBOOMDOLLY, TXCAMERAPOSITIONMODE_TRIGTRUCKBOOMDOLLY, TXCAMERAPOSITIONMODE_ORBIT, TXCAMERAPOSITIONMODE_TOTAL};
//
//enum TXCAMERAORIENTATIONMODE {TXCAMERAORIENTATIONMODE_USEROTATIONXYZ, TXCAMERAORIENTATIONMODE_TILTPANROLL, TXCAMERAORIENTATIONMODE_TRIGTILTPANROLL, TXCAMERAORIENTATIONMODE_LOOKATPOINT, TXCAMERAORIENTATIONMODE_TOTAL};

class TXMeshDistort  :  public TXDrawLayersBase
{
public:
	// constructor
	TXMeshDistort();
    
    // destructor
    ~TXMeshDistort();

	void setup();
	void update();
	void draw();
	void allocateTexture();
	void renderTexture(bool clearFirstArg);
    void windowResized(int w, int h);
    int getTextureWidth(); // overide base class
    int getTextureHeight(); // overide base class
    ofTexture *  getTexture(); // overide base class
    ofPixelsRef getPixels(); // overide base class
    
    // set methods
    void setLight1DiffuseColor();
    void setLight1AmbientColor();
    void setLight1SpecularColor();
    void setLight1Position();
    void setLight1Orientation();
    
    void setLight2DiffuseColor();
    void setLight2AmbientColor();
    void setLight2SpecularColor();
    void setLight2Position();
    void setLight2Orientation();
    
    void setLight3DiffuseColor();
    void setLight3AmbientColor();
    void setLight3SpecularColor();
    void setLight3Position();
    void setLight3Orientation();
    
    // listener methods
    void  smoothLightingChanged(bool & boolArg);
    
    // parameters

    ofPtr<TXModParamInt> drawLayersRule;
    ofPtr<TXModParamBool> useDepthTesting;
    ofPtr<TXModParamBool> useLighting;
    
    ofParameter<bool> smoothLighting;
    ofParameter<bool> drawLights;
    
    ofPtr<TXModParamBool> renderContinuosly;
    ofPtr<TXModParamBool> renderNow;
    ofPtr<TXModParamBool> clearBeforeRender;
    ofPtr<TXModParamBool> clearNow;

    ofPtr<TXModParamFloat> clearColorHue;
    ofPtr<TXModParamFloat> clearColorSaturation;
    ofPtr<TXModParamFloat> clearColorBrightness;
    ofPtr<TXModParamFloat> clearColorAlpha;
    
    ofPtr<TXModParamBool> distortionActive;
    ofPtr<TXModParamBool> distortAfterMatrix;
    ofPtr<TXModParamInt> wave1Type;
    ofPtr<TXModParamFloat> wave1Phase;
    ofPtr<TXModParamFloat> wave1Freq;
    ofPtr<TXModParamFloat> wave1AmpX;
    ofPtr<TXModParamFloat> wave1AmpY;
    ofPtr<TXModParamFloat> wave1AmpZ;
    ofPtr<TXModParamInt> wave2Type;
    ofPtr<TXModParamFloat> wave2Freq;
    ofPtr<TXModParamFloat> wave2Phase;
    ofPtr<TXModParamFloat> wave2AmpX;
    ofPtr<TXModParamFloat> wave2AmpY;
    ofPtr<TXModParamFloat> wave2AmpZ;
    ofPtr<TXModParamInt> wave3Type;
    ofPtr<TXModParamFloat> wave3Phase;
    ofPtr<TXModParamFloat> wave3Freq;
    ofPtr<TXModParamFloat> wave3AmpX;
    ofPtr<TXModParamFloat> wave3AmpY;
    ofPtr<TXModParamFloat> wave3AmpZ;
    ofPtr<TXModParamInt> wave4Type;
    ofPtr<TXModParamFloat> wave4Phase;
    ofPtr<TXModParamFloat> wave4Freq;
    ofPtr<TXModParamFloat> wave4AmpX;
    ofPtr<TXModParamFloat> wave4AmpY;
    ofPtr<TXModParamFloat> wave4AmpZ;

    ofPtr<TXModParamFloat> alpha;
    ofPtr<TXModParamFloat> drawPosX;
    ofPtr<TXModParamFloat> drawPosY;
    ofPtr<TXModParamFloat> drawWidth;
    ofPtr<TXModParamFloat> drawHeight;
    ofPtr<TXModParamFloat> anchorX;
    ofPtr<TXModParamFloat> anchorY;
    ofPtr<TXModParamFloat> rotate;
    ofPtr<TXModParamFloat> rotateMultiply;
    ofPtr<TXModParamFloat> scaleX;
    ofPtr<TXModParamFloat> scaleY;
    ofParameter<bool> useScaleXForScaleY;
    
    ofPtr<TXModParamBool> light1Active;
    ofPtr<TXModParamInt> light1Type; // enum
    ofPtr<TXModParamFloat> light1DiffuseColorHue;
    ofPtr<TXModParamFloat> light1DiffuseColorHueRotate;
    ofPtr<TXModParamFloat> light1DiffuseColorSaturation;
    ofPtr<TXModParamFloat> light1DiffuseColorBrightness;
    ofPtr<TXModParamBool> light1DiffuseColorHSBAsRGB;
    ofParameter<bool> light1UseDiffuseColorForAmbient;
    ofPtr<TXModParamFloat> light1AmbientColorHue;
    ofPtr<TXModParamFloat> light1AmbientColorHueRotate;
    ofPtr<TXModParamFloat> light1AmbientColorSaturation;
    ofPtr<TXModParamFloat> light1AmbientColorBrightness;
    ofPtr<TXModParamBool> light1AmbientColorHSBAsRGB;
    ofParameter<bool> light1UseDiffuseColorForSpecular;
    ofPtr<TXModParamFloat> light1SpecularColorHue;
    ofPtr<TXModParamFloat> light1SpecularColorHueRotate;
    ofPtr<TXModParamFloat> light1SpecularColorSaturation;
    ofPtr<TXModParamFloat> light1SpecularColorBrightness;
    ofPtr<TXModParamBool> light1SpecularColorHSBAsRGB;
    ofPtr<TXModParamFloat> light1PositionX;
    ofPtr<TXModParamFloat> light1PositionY;
    ofPtr<TXModParamFloat> light1PositionZ;
    ofPtr<TXModParamFloat> light1OrientationX;
    ofPtr<TXModParamFloat> light1OrientationY;
    ofPtr<TXModParamFloat> light1OrientationZ;
    ofPtr<TXModParamInt> light1SpotConcentration;  // range 0 - 128
    ofPtr<TXModParamFloat> light1SpotlightAngle; // range 0 - 90
    
    ofPtr<TXModParamBool> light2Active;
    ofPtr<TXModParamInt> light2Type; // enum
    ofPtr<TXModParamFloat> light2DiffuseColorHue;
    ofPtr<TXModParamFloat> light2DiffuseColorHueRotate;
    ofPtr<TXModParamFloat> light2DiffuseColorSaturation;
    ofPtr<TXModParamFloat> light2DiffuseColorBrightness;
    ofPtr<TXModParamBool> light2DiffuseColorHSBAsRGB;
    ofParameter<bool> light2UseDiffuseColorForAmbient;
    ofPtr<TXModParamFloat> light2AmbientColorHue;
    ofPtr<TXModParamFloat> light2AmbientColorHueRotate;
    ofPtr<TXModParamFloat> light2AmbientColorSaturation;
    ofPtr<TXModParamFloat> light2AmbientColorBrightness;
    ofPtr<TXModParamBool> light2AmbientColorHSBAsRGB;
    ofParameter<bool> light2UseDiffuseColorForSpecular;
    ofPtr<TXModParamFloat> light2SpecularColorHue;
    ofPtr<TXModParamFloat> light2SpecularColorHueRotate;
    ofPtr<TXModParamFloat> light2SpecularColorSaturation;
    ofPtr<TXModParamFloat> light2SpecularColorBrightness;
    ofPtr<TXModParamBool> light2SpecularColorHSBAsRGB;
    ofPtr<TXModParamFloat> light2PositionX;
    ofPtr<TXModParamFloat> light2PositionY;
    ofPtr<TXModParamFloat> light2PositionZ;
    ofPtr<TXModParamFloat> light2OrientationX;
    ofPtr<TXModParamFloat> light2OrientationY;
    ofPtr<TXModParamFloat> light2OrientationZ;
    ofPtr<TXModParamInt> light2SpotConcentration;  // range 0 - 128
    ofPtr<TXModParamFloat> light2SpotlightAngle; // range 0 - 90
    
    ofPtr<TXModParamBool> light3Active;
    ofPtr<TXModParamInt> light3Type; // enum
    ofPtr<TXModParamFloat> light3DiffuseColorHue;
    ofPtr<TXModParamFloat> light3DiffuseColorHueRotate;
    ofPtr<TXModParamFloat> light3DiffuseColorSaturation;
    ofPtr<TXModParamFloat> light3DiffuseColorBrightness;
    ofPtr<TXModParamBool> light3DiffuseColorHSBAsRGB;
    ofParameter<bool> light3UseDiffuseColorForAmbient;
    ofPtr<TXModParamFloat> light3AmbientColorHue;
    ofPtr<TXModParamFloat> light3AmbientColorHueRotate;
    ofPtr<TXModParamFloat> light3AmbientColorSaturation;
    ofPtr<TXModParamFloat> light3AmbientColorBrightness;
    ofPtr<TXModParamBool> light3AmbientColorHSBAsRGB;
    ofParameter<bool> light3UseDiffuseColorForSpecular;
    ofPtr<TXModParamFloat> light3SpecularColorHue;
    ofPtr<TXModParamFloat> light3SpecularColorHueRotate;
    ofPtr<TXModParamFloat> light3SpecularColorSaturation;
    ofPtr<TXModParamFloat> light3SpecularColorBrightness;
    ofPtr<TXModParamBool> light3SpecularColorHSBAsRGB;
    ofPtr<TXModParamFloat> light3PositionX;
    ofPtr<TXModParamFloat> light3PositionY;
    ofPtr<TXModParamFloat> light3PositionZ;
    ofPtr<TXModParamFloat> light3OrientationX;
    ofPtr<TXModParamFloat> light3OrientationY;
    ofPtr<TXModParamFloat> light3OrientationZ;
    ofPtr<TXModParamInt> light3SpotConcentration;  // range 0 - 128
    ofPtr<TXModParamFloat> light3SpotlightAngle; // range 0 - 90
    
    ofPtr<TXModParamBool> cam1Active;
    ofPtr<TXModParamInt> cam1PositionMode;  // enum
    ofPtr<TXModParamFloat> cam1PositionX;
    ofPtr<TXModParamFloat> cam1PositionY;
    ofPtr<TXModParamFloat> cam1PositionZ;
    ofPtr<TXModParamFloat> cam1TruckX;
    ofPtr<TXModParamBool> cam1TruckXTrigger;
    ofPtr<TXModParamFloat> cam1BoomY;
    ofPtr<TXModParamBool> cam1BoomYTrigger;
    ofPtr<TXModParamFloat> cam1DollyZ;
    ofPtr<TXModParamBool> cam1DollyZTrigger;
    ofPtr<TXModParamBool> cam1FreezePosition;
    ofPtr<TXModParamBool> cam1ResetToPositionXYZ;
    ofPtr<TXModParamFloat> cam1OrbitPointX;
    ofPtr<TXModParamFloat> cam1OrbitPointY;
    ofPtr<TXModParamFloat> cam1OrbitPointZ;
    ofPtr<TXModParamFloat> cam1OrbitLongitude;
    ofPtr<TXModParamFloat> cam1OrbitLatitude;
    ofPtr<TXModParamFloat> cam1OrbitRadius;
    ofPtr<TXModParamInt> cam1OrientationMode;  // enum
    ofPtr<TXModParamFloat> cam1RotationX;
    ofPtr<TXModParamFloat> cam1RotationY;
    ofPtr<TXModParamFloat> cam1RotationZ;
    ofPtr<TXModParamFloat> cam1TiltX;
    ofPtr<TXModParamBool> cam1TiltXTrigger;
    ofPtr<TXModParamFloat> cam1PanY;
    ofPtr<TXModParamBool> cam1PanYTrigger;
    ofPtr<TXModParamFloat> cam1RollZ;
    ofPtr<TXModParamBool> cam1RollZTrigger;
    ofPtr<TXModParamBool> cam1FreezeRotation; 
    ofPtr<TXModParamBool> cam1ResetToRotationXYZ;
    ofPtr<TXModParamFloat> cam1LookAtPointX;
    ofPtr<TXModParamFloat> cam1LookAtPointY;
    ofPtr<TXModParamFloat> cam1LookAtPointZ;
    
    ofFbo outImage;
    
private:
    ofPixels pix;
    ofMesh drawMesh;
	ofShader drawShader;
	ofShader renderShader;
    bool oldRenderNow;
    bool oldClearNow;

    ofLight light1;
	ofLight light2;
	ofLight light3;
    
    ofEasyCam cam1;
	
    bool oldCam1ResetToPositionXYZ;
    bool oldCam1TruckXTrigger;
    bool oldCam1BoomYTrigger;
    bool oldCam1DollyZTrigger;
    bool oldCam1ResetToRotationXYZ;
    bool oldCam1TiltXTrigger;
    bool oldCam1PanYTrigger;
    bool oldCam1RollZTrigger;
};

