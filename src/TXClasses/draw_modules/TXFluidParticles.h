/*
 *  TXFluidParticles.h
 *  Amended from ofxMSAFluid Demo
 *
 */
#pragma once

#include "TXParametersBase.h"
#include "TXFluidParticle.h"
#include "TXDraw2DShape.h"


#define MAX_PARTICLES  50000

class TXFluidParticles: public TXParametersBase {
public:
    
    ofVec3f arrVertices[MAX_PARTICLES];
    ofFloatColor arrColors[MAX_PARTICLES];
    int curIndex;
	
    TXFluidParticle particles[MAX_PARTICLES];
	
	// constructor
	TXFluidParticles();
    
    // destructor
    ~TXFluidParticles();
    
	void setup();
    void advanceBy(float timeDeltaArg);
	void trigger(const ofVec2f &force1Pos);
	void addParticle(const ofVec2f &pos, float &lifetimeArg, float &startDelay, ofColor &startColor1Arg, ofColor &startColor2Arg, bool &lockColors, float &massArg);
    void updateAndDraw(const msa::fluid::Solver &solver, float &width, float &height);
    void draw();
    void killParticles(int startIndex = 0);

    // listener methods
    void maximumActiveParticlesChanged(int & intArg);
    
    // parameters
    
    ofParameter<int>      maximumActiveParticles;
    ofPtr<TXModParamInt> numParticlesPerTrigger;
    ofPtr<TXModParamFloat> particleStartDelayRand;
    ofPtr<TXModParamFloat> particleLifetime;
    ofPtr<TXModParamFloat> particleLifetimeRandom;
    
    ofPtr<TXModParamFloat> particleSpreadDiameter;
    ofPtr<TXModParamFloat> particlePosX;
    ofPtr<TXModParamFloat> particlePosY;
    ofPtr<TXModParamBool> useForce1PosForParticles;
    ofPtr<TXModParamFloat> randomParticlePosX;
    ofPtr<TXModParamFloat> randomParticlePosY;
    
    ofPtr<TXModParamBool> lockParticleColorsAtStart;
    ofPtr<TXModParamFloat> particleSpeedXAlpha;
    ofPtr<TXModParamFloat> particleSpeedXBrightness;
    
    ofPtr<TXModParamFloat> particleColor1Hue;
    ofPtr<TXModParamFloat> particleColor1Saturation;
    ofPtr<TXModParamFloat> particleColor1Brightness;
    ofPtr<TXModParamFloat> particleColor1Alpha;
    ofPtr<TXModParamBool> particleColor1HSBAsRGB;
    
    ofPtr<TXModParamFloat> particleColor2Hue;
    ofPtr<TXModParamFloat> particleColor2Saturation;
    ofPtr<TXModParamFloat> particleColor2Brightness;
    ofPtr<TXModParamFloat> particleColor2Alpha;
    ofPtr<TXModParamBool> particleColor2HSBAsRGB;
    
    TXParameterFloat256   particleColorMixCurve;
    
protected:
    TXDraw2DShape shape;
    ofMesh mesh;
};

// NOTE these shape parameters shouldn't be updated from gui:
//ofPtr<TXModParamFloat> positionX;
//ofPtr<TXModParamFloat> positionY;
//ofPtr<TXModParamFloat> colorHue;
//ofPtr<TXModParamFloat> colorSaturation;
//ofPtr<TXModParamFloat> colorBrightness;
//ofPtr<TXModParamFloat> colorAlpha;
//ofPtr<TXModParamBool> colorHSBAsRGB;


