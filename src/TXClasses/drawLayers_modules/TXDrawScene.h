/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXDrawLayersBase.h"
//#include "TXMain.h"

//enum TXLIGHTTYPE {TXLIGHTTYPE_POINT, TXLIGHTTYPE_DIRECTIONAL, TXLIGHTTYPE_SPOT, TXLIGHTTYPE_TOTAL};
//
//enum TXCAMERAPOSITIONMODE {TXCAMERAPOSITIONMODE_USEPOSITIONXYZ, TXCAMERAPOSITIONMODE_TRUCKBOOMDOLLY, TXCAMERAPOSITIONMODE_TRIGTRUCKBOOMDOLLY, TXCAMERAPOSITIONMODE_ORBIT, TXCAMERAPOSITIONMODE_TOTAL};
//
//enum TXCAMERAORIENTATIONMODE {TXCAMERAORIENTATIONMODE_USEROTATIONXYZ, TXCAMERAORIENTATIONMODE_TILTPANROLL, TXCAMERAORIENTATIONMODE_TRIGTILTPANROLL, TXCAMERAORIENTATIONMODE_LOOKATPOINT, TXCAMERAORIENTATIONMODE_TOTAL};
//

class TXDrawScene  :  public TXDrawLayersBase
{
public:
	// constructor
	TXDrawScene();
    
    // destructor
    ~TXDrawScene();

	void setup();
    void update();
    void draw();

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
    ofPtr<TXModParamBool> useLighting;

    ofParameter<bool> smoothLighting;
    ofParameter<bool> drawLights;

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

    ofPtr<TXModParamInt> cameraSelect; // 0:off, 1:cam1, 2:cam2
    // cam1
    ofPtr<TXModParamBool> cam1Orthographic;
    ofPtr<TXModParamFloat> cam1FieldOfViewDegrees;
    ofPtr<TXModParamFloat> cam1NearClipDistance;
    ofPtr<TXModParamFloat> cam1FarClipDistance;
    ofPtr<TXModParamFloat> cam1LensOffsetX;
    ofPtr<TXModParamFloat> cam1LensOffsetY;
    ofPtr<TXModParamBool> cam1ForceAspectRatio; // only for non-orthographic i.e. perspective
    ofPtr<TXModParamFloat> cam1AspectRatioWidth;
    ofPtr<TXModParamFloat> cam1AspectRatioHeight;
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
    
    // cam2
    ofPtr<TXModParamBool> cam2Orthographic;
    ofPtr<TXModParamFloat> cam2FieldOfViewDegrees;
    ofPtr<TXModParamFloat> cam2NearClipDistance;
    ofPtr<TXModParamFloat> cam2FarClipDistance;
    ofPtr<TXModParamFloat> cam2LensOffsetX;
    ofPtr<TXModParamFloat> cam2LensOffsetY;
    ofPtr<TXModParamBool> cam2ForceAspectRatio; // only for non-orthographic i.e. perspective
    ofPtr<TXModParamFloat> cam2AspectRatioWidth;
    ofPtr<TXModParamFloat> cam2AspectRatioHeight;
    ofPtr<TXModParamInt> cam2PositionMode;  // enum
    ofPtr<TXModParamFloat> cam2PositionX;
    ofPtr<TXModParamFloat> cam2PositionY;
    ofPtr<TXModParamFloat> cam2PositionZ;
    ofPtr<TXModParamFloat> cam2TruckX;
    ofPtr<TXModParamBool> cam2TruckXTrigger;
    ofPtr<TXModParamFloat> cam2BoomY;
    ofPtr<TXModParamBool> cam2BoomYTrigger;
    ofPtr<TXModParamFloat> cam2DollyZ;
    ofPtr<TXModParamBool> cam2DollyZTrigger;
    ofPtr<TXModParamBool> cam2FreezePosition;
    ofPtr<TXModParamBool> cam2ResetToPositionXYZ;
    ofPtr<TXModParamFloat> cam2OrbitPointX;
    ofPtr<TXModParamFloat> cam2OrbitPointY;
    ofPtr<TXModParamFloat> cam2OrbitPointZ;;
    ofPtr<TXModParamFloat> cam2OrbitLongitude;
    ofPtr<TXModParamFloat> cam2OrbitLatitude;
    ofPtr<TXModParamFloat> cam2OrbitRadius;
    ofPtr<TXModParamInt> cam2OrientationMode;  // enum
    ofPtr<TXModParamFloat> cam2RotationX;
    ofPtr<TXModParamFloat> cam2RotationY;
    ofPtr<TXModParamFloat> cam2RotationZ;
    ofPtr<TXModParamFloat> cam2TiltX;
    ofPtr<TXModParamBool> cam2TiltXTrigger;
    ofPtr<TXModParamFloat> cam2PanY;
    ofPtr<TXModParamBool> cam2PanYTrigger;
    ofPtr<TXModParamFloat> cam2RollZ;
    ofPtr<TXModParamBool> cam2RollZTrigger;
    ofPtr<TXModParamBool> cam2FreezeRotation;
    ofPtr<TXModParamBool> cam2ResetToRotationXYZ;
    ofPtr<TXModParamFloat> cam2LookAtPointX;
    ofPtr<TXModParamFloat> cam2LookAtPointY;
    ofPtr<TXModParamFloat> cam2LookAtPointZ;

private:
    ofLight light1;
	ofLight light2;
	ofLight light3;
    
    ofCamera cam1;
    ofCamera cam2;
	
    bool oldCam1ResetToPositionXYZ;
    bool oldCam1TruckXTrigger;
    bool oldCam1BoomYTrigger;
    bool oldCam1DollyZTrigger;
    bool oldCam1ResetToRotationXYZ;
    bool oldCam1TiltXTrigger;
    bool oldCam1PanYTrigger;
    bool oldCam1RollZTrigger;

    bool oldCam2ResetToPositionXYZ;
    bool oldCam2TruckXTrigger;
    bool oldCam2BoomYTrigger;
    bool oldCam2DollyZTrigger;
    bool oldCam2ResetToRotationXYZ;
    bool oldCam2TiltXTrigger;
    bool oldCam2PanYTrigger;
    bool oldCam2RollZTrigger;
    float cameraRotateZOffset;
};

