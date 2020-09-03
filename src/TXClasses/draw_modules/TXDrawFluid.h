/*
 *  Copyright 2014 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXDrawBase.h"
//#include "TXMain.h"
#include "MSAFluid.h"
#include "TXFluidParticles.h"


// NOTE - change totalDrawModes when adding new modes:
enum TXDRAWFLUIDDRAWMODE {
    TXDRAWFLUIDDRAWMODE_DRAWCOLOR,
    TXDRAWFLUIDDRAWMODE_DRAWMOTION,
    TXDRAWFLUIDDRAWMODE_DRAWSPEED,
    TXDRAWFLUIDDRAWMODE_DRAWVECTORS,
};

class TXDrawFluid  :  public TXDrawBase
{
public:
    static const int totalDrawModes = 4;
    
	// constructor
	TXDrawFluid();
    
    // destructor
    ~TXDrawFluid();
    
	void setup();
	void advanceBy(float timeDeltaArg);
    void update();
	void draw();
    void addColorsForces();
    ofVec2f getForce(float forceX, float forceY, bool forceYAsDirection);
    
    // listener methods
    void  fluidCellsXChanged(int & intArg);
    void  fluidCellsYChanged(int & intArg);
    void  triggerParticlesNowChanged(ofAbstractParameter & parameterArg);
    void  killAllParticlesNowChanged(ofAbstractParameter & parameterArg);
    
    void  drawModeChanged(ofAbstractParameter & parameterArg );
    void  wrapXChanged(ofAbstractParameter & parameterArg );
    void  wrapYChanged(ofAbstractParameter & parameterArg );
    void  viscocityChanged(ofAbstractParameter & parameterArg );
    void  colorDiffusionChanged(ofAbstractParameter & parameterArg );
    void  fadeSpeedChanged(ofAbstractParameter & parameterArg );
    void  deltaTimeChanged(ofAbstractParameter & parameterArg );
    void  solverIterationsChanged(ofAbstractParameter & parameterArg );
    void  doVorticityConfinementChanged(ofAbstractParameter & parameterArg );
    void  doRGBChanged(ofAbstractParameter & parameterArg );
    
    // parameters

    ofParameter<int>      fluidCellsX;
    ofParameter<int>      fluidCellsY;
    
    ofPtr<TXModParamBool> drawFluid;
    ofPtr<TXModParamInt> drawMode;
    ofPtr<TXModParamBool> frozen; // bool
    ofPtr<TXModParamFloat> colorMultiply;
    ofPtr<TXModParamFloat> forceMultiply;
    ofPtr<TXModParamBool> wrapX;
    ofPtr<TXModParamBool> wrapY;
    ofPtr<TXModParamFloat> viscocity;
    ofPtr<TXModParamFloat> colorDiffusion;
    ofPtr<TXModParamFloat> fadeSpeed;
    ofPtr<TXModParamFloat> deltaTime;
    ofPtr<TXModParamInt> solverIterations;
    ofPtr<TXModParamBool> doVorticityConfinement; // bool
    ofPtr<TXModParamBool> doRGB; // bool
    
    ofPtr<TXModParamBool> color1Active;
    ofPtr<TXModParamFloat> color1PosX;
    ofPtr<TXModParamFloat> color1PosY;
    ofPtr<TXModParamFloat> color1Hue;
    ofPtr<TXModParamFloat> color1Saturation;
    ofPtr<TXModParamFloat> color1Brightness;
    ofPtr<TXModParamFloat> color1Alpha;
    ofPtr<TXModParamBool> color1HSBAsRGB;
    
    ofPtr<TXModParamBool> color2Active;
    ofPtr<TXModParamFloat> color2PosX;
    ofPtr<TXModParamFloat> color2PosY;
    ofPtr<TXModParamFloat> color2Hue;
    ofPtr<TXModParamFloat> color2Saturation;
    ofPtr<TXModParamFloat> color2Brightness;
    ofPtr<TXModParamFloat> color2Alpha;
    ofPtr<TXModParamBool> color2HSBAsRGB;
    
    ofPtr<TXModParamBool> color3Active;
    ofPtr<TXModParamFloat> color3PosX;
    ofPtr<TXModParamFloat> color3PosY;
    ofPtr<TXModParamFloat> color3Hue;
    ofPtr<TXModParamFloat> color3Saturation;
    ofPtr<TXModParamFloat> color3Brightness;
    ofPtr<TXModParamFloat> color3Alpha;
    ofPtr<TXModParamBool> color3HSBAsRGB;
    
    ofPtr<TXModParamBool> color4Active;
    ofPtr<TXModParamFloat> color4PosX;
    ofPtr<TXModParamFloat> color4PosY;
    ofPtr<TXModParamFloat> color4Hue;
    ofPtr<TXModParamFloat> color4Saturation;
    ofPtr<TXModParamFloat> color4Brightness;
    ofPtr<TXModParamFloat> color4Alpha;
    ofPtr<TXModParamBool> color4HSBAsRGB;
    
    ofPtr<TXModParamBool> force1Active;
    ofPtr<TXModParamFloat> force1X;
    ofPtr<TXModParamFloat> force1Y;
    ofPtr<TXModParamBool> useForce1YAsDirection;
    ofPtr<TXModParamFloat> force1PosX;
    ofPtr<TXModParamFloat> force1PosY;
    ofPtr<TXModParamBool> useColor1PosForForce1;
    ofPtr<TXModParamFloat> force1PosSpeedToForce;
    
    ofPtr<TXModParamBool> force2Active;
    ofPtr<TXModParamFloat> force2X;
    ofPtr<TXModParamFloat> force2Y;
    ofPtr<TXModParamBool> useForce2YAsDirection;
    ofPtr<TXModParamFloat> force2PosX;
    ofPtr<TXModParamFloat> force2PosY;
    ofPtr<TXModParamBool> useColor2PosForForce2;
    ofPtr<TXModParamFloat> force2PosSpeedToForce;
    
    ofPtr<TXModParamBool> force3Active;
    ofPtr<TXModParamFloat> force3X;
    ofPtr<TXModParamFloat> force3Y;
    ofPtr<TXModParamBool> useForce3YAsDirection;
    ofPtr<TXModParamFloat> force3PosX;
    ofPtr<TXModParamFloat> force3PosY;
    ofPtr<TXModParamBool> useColor3PosForForce3;
    ofPtr<TXModParamFloat> force3PosSpeedToForce;
    
    ofPtr<TXModParamBool> force4Active;
    ofPtr<TXModParamFloat> force4X;
    ofPtr<TXModParamFloat> force4Y;
    ofPtr<TXModParamBool> useForce4YAsDirection;
    ofPtr<TXModParamFloat> force4PosX;
    ofPtr<TXModParamFloat> force4PosY;
    ofPtr<TXModParamBool> useColor4PosForForce4;
    ofPtr<TXModParamFloat> force4PosSpeedToForce;
    
    ofPtr<TXModParamFloat> width;
    ofPtr<TXModParamFloat> height;
    ofPtr<TXModParamFloat> positionX;
    ofPtr<TXModParamFloat> positionY;
    ofPtr<TXModParamFloat> anchorX;
    ofPtr<TXModParamFloat> anchorY;
    ofPtr<TXModParamFloat> rotate;
    ofPtr<TXModParamFloat> rotateMultiply;
    ofPtr<TXModParamFloat> scaleX;
    ofPtr<TXModParamFloat> scaleY;
    ofParameter<bool>     useScaleXForScaleY;
        
    ofPtr<TXModParamBool> drawParticles;
    ofPtr<TXModParamBool> triggerParticlesContinuosly;
    ofPtr<TXModParamBool> triggerParticlesNow;
    ofPtr<TXModParamBool> useForce1ToTriggerParticles;
    ofPtr<TXModParamBool> killAllParticlesNow;

private:
	msa::fluid::Solver    fluidSolver;
	msa::fluid::DrawerGl  fluidDrawer;
    TXFluidParticles      particles;
    
    bool  resizeFluid;
    bool  triggerParticlesNowConfirmed;
    bool  killAllParticlesNowConfirmed;
    bool  oldTriggerParticlesNow;
    bool  oldKillAllParticlesNow;
    ofVec2f oldForce1Pos;
    ofVec2f oldForce2Pos;
    ofVec2f oldForce3Pos;
    ofVec2f oldForce4Pos;
};

