/*
 *  TXFluidParticle.h
 *  Amended from ofxMSAFluid Demo
 *
 */

#pragma once

#include "MSACore.h"
#include "MSAFluidSolver.h"
#include "TXParameterFloat256.h"


class TXFluidParticle {
public:	
    ofVec2f	pos, vel;
    bool	alive;
    float	lifetime;
    float	age;
    float	mass;
    ofColor startColor1;
    ofColor startColor2;
    bool lockColors;
	
    void init(float x, float y, float lifetimeArg, float startDelay, ofColor startColor1Arg, ofColor startColor2Arg, bool lockColorsArg, float massArg);

    void advanceBy(float timeDeltaArg);

    void update( const msa::fluid::Solver &solver);

    // OLD:
    // void updateVertexArrays(int i, float* posBuffer, float* colBuffer, ofColor &color1, ofColor &color2, TXParameterFloat256 &particleColorMixCurve, float &speedXAlpha, float &speedXBrightness, float &width, float &height);

	void updateVertexArrays(int i, ofVec3f* arrVertices, ofFloatColor* arrColors, ofColor &color1, ofColor &color2, TXParameterFloat256 &particleColorMixCurve, float &speedXAlpha, float &speedXBrightness, float &width, float &height);

};

