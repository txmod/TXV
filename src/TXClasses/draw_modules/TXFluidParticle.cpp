/*
 *  TXFluidParticle.cpp
 *  Amended from ofxMSAFluid Demo
 *
 */

#include "TXFluidParticle.h"

static const float MOMENTUM = 0.5f;
static const float FLUID_FORCE = 0.6f;
static const float RECIPR_255 = (1.0f / 255.0f);

void TXFluidParticle::init(float x, float y, float lifetimeArg, float startDelay, ofColor startColor1Arg, ofColor startColor2Arg, bool lockColorsArg, float massArg) {
	pos = ofVec2f( x, y );
	vel = ofVec2f(0, 0);
    alive = true;
	mass = massArg;
    lifetime = lifetimeArg;
    age = 0-startDelay;
    startColor1 = startColor1Arg;
    startColor2 = startColor2Arg;
    lockColors = lockColorsArg;
}

void TXFluidParticle::advanceBy(float timeDeltaArg) {
    if (alive) {
        age += timeDeltaArg;
        if (age > lifetime) {
            alive = false;
        };
    };
}

void TXFluidParticle::update( const msa::fluid::Solver &solver) {
	if(!alive) {
		return;
    };
	
	vel = solver.getVelocityAtPos(pos) * (mass * FLUID_FORCE ) + vel * MOMENTUM;
	pos += vel;	
	
	// bounce off edges
	if( pos.x < 0 ) {
		pos.x = 0;
		vel.x *= -1;
	}
	else if( pos.x > 1.0 ) {
		pos.x = 1.0;
		vel.x *= -1;
	}
	
	if( pos.y < 0 ) {
		pos.y = 0;
		vel.y *= -1;
	}
	else if( pos.y > 1.0 ) {
		pos.y = 1.0;
		vel.y *= -1;
	}
}

/*
void TXFluidParticle::updateVertexArrays(int i, float* posBuffer, float* colBuffer, ofColor &color1, ofColor &color2, TXParameterFloat256 &particleColorMixCurve, float &speedXAlpha, float &speedXBrightness, float &width, float &height) {
    
    // position
	int vi = i * 2;
	posBuffer[vi++] = pos.x * width;
	posBuffer[vi++] = pos.y * height;
    
    // colour
    ofColor col;
    float holdR, holdG, holdB, holdA;
    float lerpAmt = particleColorMixCurve.interpolatedLookup(age/lifetime);
    if (alive && (age >= 0)) {
        if (lockColors) {
            col = startColor1.lerp(startColor2, lerpAmt);
        } else {
            col = color1.lerp(color2, lerpAmt);
        };
        float speed = vel.length();
        float multiplyBrightness = 1.0 + (speed * speedXBrightness);
        float multiplyAlpha = 1.0 + (speed * speedXAlpha);
        holdR = col.r * multiplyBrightness * RECIPR_255;
        holdG = col.g * multiplyBrightness * RECIPR_255;
        holdB = col.b * multiplyBrightness * RECIPR_255;
        holdA = col.a * multiplyAlpha * RECIPR_255;
    } else {
        holdR = 0.0;
        holdG = 0.0;
        holdB = 0.0;
        holdA = 0.0;
    };
    
	int ci = i * 4;
    colBuffer[ci++] = holdR;
    colBuffer[ci++] = holdG;
    colBuffer[ci++] = holdB;
    colBuffer[ci++] = holdA;
}
 */

void TXFluidParticle::updateVertexArrays(int i, ofVec3f* arrVertices, ofFloatColor* arrColors, ofColor &color1, ofColor &color2, TXParameterFloat256 &particleColorMixCurve, float &speedXAlpha, float &speedXBrightness, float &width, float &height) {
    
    // position
	arrVertices[i].x = pos.x * width;
	arrVertices[i].y = pos.y * height;
    
    // colour
    ofColor col;
    ofFloatColor outCol;
    float holdR, holdG, holdB, holdA, holdLookup;
    if (alive && (age >= 0)) {
        float lerpAmt;
        if (age == 0) {
            holdLookup = 0.0f;
            lerpAmt = particleColorMixCurve.interpolatedLookup(holdLookup);
        } else {
            holdLookup = age/lifetime;
            lerpAmt = particleColorMixCurve.interpolatedLookup(holdLookup);
        };
        if (lockColors) {
            col = startColor1.getLerped(startColor2, lerpAmt);
        } else {
            col = color1.getLerped(color2, lerpAmt);
        };
        float speed = vel.length();
        float multiplyBrightness = (1.0 + (speed * speedXBrightness)) * RECIPR_255;
        float multiplyAlpha = (1.0 + (speed * speedXAlpha)) * RECIPR_255;
        holdR = col.r * multiplyBrightness;
        holdG = col.g * multiplyBrightness;
        holdB = col.b * multiplyBrightness;
        holdA = col.a * multiplyAlpha;
        outCol = ofFloatColor(holdR, holdG, holdB, holdA);
    } else {
       outCol = ofFloatColor(0.0,0.0);
    };
    arrColors[i] = outCol;
}



