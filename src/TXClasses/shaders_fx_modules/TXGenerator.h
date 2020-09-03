/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXDrawBase.h"
//#include "TXMain.h"

// note - glsl shader code downloaded from www.shadertoy.com and www.github.com/patriciogonzalezvivo/sNodes
// ["70s Pattern - uses zoom", "Caramel Clouds", "Clouds", "Cosmos", "Dark Cloud", "Dense Bubbles - uses color 1", "Dense Cloud - uses point, zoom, color 1", "Fire-Ball - uses point, zoom, color 1", "Flow", "Fog - uses zoom, colors 1-4", "Fog 2 - uses zoom, colors 1-4", "Hypnotic Color", "Mountains Texture - uses zoom, color 1", "Noise - uses zoom, colors 1-4", "Particles", "Pattern 1 - uses zoom, color 1", "Pattern 2 - uses zoom, color 1", "Snow", "Space Warp", "Voronoi - uses zoom, colors 1-3", "Voronoi Static - uses zoom, color 1", "Waves Cascade" ]


enum TXGENERATORTYPE {   // SOME REMOVED
    TXGENERATORTYPE_70s,
    // TXGENERATORTYPE_aura,
    TXGENERATORTYPE_caramelClouds,
    TXGENERATORTYPE_clouds,
    TXGENERATORTYPE_cosmos,
    // TXGENERATORTYPE_cyberBrain,
    TXGENERATORTYPE_darkCloud,
    TXGENERATORTYPE_denseBubles,
    TXGENERATORTYPE_denseCloud,
    // TXGENERATORTYPE_eclipse,
    TXGENERATORTYPE_fireBall,
    TXGENERATORTYPE_flow,
    TXGENERATORTYPE_fog,
    TXGENERATORTYPE_fog2,
    // TXGENERATORTYPE_freq,
    TXGENERATORTYPE_hypnoticColor,
    // TXGENERATORTYPE_laserLines,
    // TXGENERATORTYPE_metaBalls,
    // TXGENERATORTYPE_metaBalls2,
    TXGENERATORTYPE_montainsTexture,
    TXGENERATORTYPE_noise,
    TXGENERATORTYPE_particles,
    TXGENERATORTYPE_pattern1,
    TXGENERATORTYPE_pattern2,
    TXGENERATORTYPE_snow,
    TXGENERATORTYPE_spaceWarp,
    // TXGENERATORTYPE_stellar,
    // TXGENERATORTYPE_tunel,
    TXGENERATORTYPE_voronoi,
    TXGENERATORTYPE_voronoiStatic,
    TXGENERATORTYPE_wavesCascade
};
class TXGenerator  :  public TXDrawBase
{
public:
	// constructor
	TXGenerator();
    
    // destructor
    ~TXGenerator();
    
    // NOTE - change totalGeneratorTypes when adding new types:
    static const int totalGeneratorTypes = 22;

	string getShaderFileName(TXGENERATORTYPE shaderNum = TXGENERATORTYPE_clouds);
	void setup();
	void advanceBy(float timeDeltaArg);
	void update();
	void draw();
	void loadRenderShader();
	void allocateTexture();
	void renderTexture(bool clearFirstArg);
    void windowResized(int w, int h);
    void generatorTypeChanged(ofAbstractParameter & dummyParameterArg );
    void renderSizeChanged(int & intArg);
    
    int getTextureWidth(); // overide base class
    int getTextureHeight(); // overide base class
    int getRenderWidth();
    int getRenderHeight();
    
    ofTexture *  getTexture(); // overide base class
    
    ofPtr<TXModParamBool> renderContinuosly;
    ofPtr<TXModParamBool> renderNow;
    ofParameter<int> renderWidthHeightRule;
    ofParameter<int> renderCustomWidth;
    ofParameter<int> renderCustomHeight;
    ofPtr<TXModParamBool> clearBeforeRender;
    ofPtr<TXModParamBool> clearNow;
    
    ofPtr<TXModParamFloat> clearColorHue;
    ofPtr<TXModParamFloat> clearColorSaturation;
    ofPtr<TXModParamFloat> clearColorBrightness;
    ofPtr<TXModParamFloat> clearColorAlpha;
    ofPtr<TXModParamBool> clearColorHSBAsRGB;
    
    ofPtr<TXModParamFloat> pointX;
    ofPtr<TXModParamFloat> pointY;
    ofPtr<TXModParamFloat> zoom;

    ofPtr<TXModParamInt> generatorType;
    ofPtr<TXModParamFloat> bpm;
    ofPtr<TXModParamBool> useMasterBpm;
    ofPtr<TXModParamFloat> cycleTimeBeats;
    ofPtr<TXModParamFloat> cycleTimeDivisor;
    ofPtr<TXModParamFloat> phaseOffset;
    ofPtr<TXModParamBool> frozen;

    ofPtr<TXModParamFloat> color1Hue;
    ofPtr<TXModParamFloat> color1HueRotate;
    ofPtr<TXModParamFloat> color1Saturation;
    ofPtr<TXModParamFloat> color1Brightness;
    ofPtr<TXModParamFloat> color1Alpha;
    ofPtr<TXModParamBool> color1HSBAsRGB;
    
    ofPtr<TXModParamFloat> color2Hue;
    ofPtr<TXModParamFloat> color2HueRotate;
    ofPtr<TXModParamFloat> color2Saturation;
    ofPtr<TXModParamFloat> color2Brightness;
    ofPtr<TXModParamFloat> color2Alpha;
    ofPtr<TXModParamBool> color2HSBAsRGB;
    
    ofPtr<TXModParamFloat> color3Hue;
    ofPtr<TXModParamFloat> color3HueRotate;
    ofPtr<TXModParamFloat> color3Saturation;
    ofPtr<TXModParamFloat> color3Brightness;
    ofPtr<TXModParamFloat> color3Alpha;
    ofPtr<TXModParamBool> color3HSBAsRGB;
    
    ofPtr<TXModParamFloat> color4Hue;
    ofPtr<TXModParamFloat> color4HueRotate;
    ofPtr<TXModParamFloat> color4Saturation;
    ofPtr<TXModParamFloat> color4Brightness;
    ofPtr<TXModParamFloat> color4Alpha;
    ofPtr<TXModParamBool> color4HSBAsRGB;
    
    ofPtr<TXModParamFloat> drawAlpha;
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
    
    ofFbo outImage;
    
private:
    float currentPhase;
    ofMesh drawMesh;
	ofShader drawShader;
	ofShader renderShader;
    bool oldRenderNow;
    bool oldClearNow;
};

