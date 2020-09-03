/*
 *  TXFluidParticles.cpp
 *  Amended from ofxMSAFluid Demo
 *
 */

#include "TXFluidParticles.h"

// constructor
TXFluidParticles::TXFluidParticles() {
	curIndex = 0;
    setup();
}

// destructor
TXFluidParticles::~TXFluidParticles() {
}

void TXFluidParticles::setup() {
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    
    parameters.add(maximumActiveParticles.set("maximumActiveParticles", 10000, 100, MAX_PARTICLES));
    
    holdModParamIntArgs.name = "numParticlesPerTrigger";
    holdModParamIntArgs.fixedValue = 10;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 1000;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 100;
	numParticlesPerTrigger = createModParameter(holdModParamIntArgs);
    parameters.add(numParticlesPerTrigger->parameters);
    
    holdModParamFloatArgs.name = "particleStartDelayRand";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	particleStartDelayRand = createModParameter(holdModParamFloatArgs);
    parameters.add(particleStartDelayRand->parameters);
    
    holdModParamFloatArgs.name = "particleLifetime";
    holdModParamFloatArgs.fixedValue = 10.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
	particleLifetime = createModParameter(holdModParamFloatArgs);
    parameters.add(particleLifetime->parameters);
    
    holdModParamFloatArgs.name = "particleLifetimeRandom";
    holdModParamFloatArgs.fixedValue = 2.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1000.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
	particleLifetimeRandom = createModParameter(holdModParamFloatArgs);
    parameters.add(particleLifetimeRandom->parameters);
    
    holdModParamFloatArgs.name = "particleSpreadDiameter";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	particleSpreadDiameter = createModParameter(holdModParamFloatArgs);
    parameters.add(particleSpreadDiameter->parameters);
    
    holdModParamFloatArgs.name = "particlePosX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	particlePosX = createModParameter(holdModParamFloatArgs);
    parameters.add(particlePosX->parameters);
    
    holdModParamFloatArgs.name = "particlePosY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	particlePosY = createModParameter(holdModParamFloatArgs);
    parameters.add(particlePosY->parameters);
    
    holdModParamBoolArgs.name = "useForce1PosForParticles";
    holdModParamBoolArgs.fixedValue = true;
	useForce1PosForParticles = createModParameter(holdModParamBoolArgs);
    parameters.add(useForce1PosForParticles->parameters);
    
    holdModParamFloatArgs.name = "randomParticlePosX";
    holdModParamFloatArgs.fixedValue = 0.015;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	randomParticlePosX = createModParameter(holdModParamFloatArgs);
    parameters.add(randomParticlePosX->parameters);
    
    holdModParamFloatArgs.name = "randomParticlePosY";
    holdModParamFloatArgs.fixedValue = 0.015;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	randomParticlePosY = createModParameter(holdModParamFloatArgs);
    parameters.add(randomParticlePosY->parameters);
    
    holdModParamBoolArgs.name = "lockParticleColorsAtStart";
    holdModParamBoolArgs.fixedValue = false;
	lockParticleColorsAtStart = createModParameter(holdModParamBoolArgs);
    parameters.add(lockParticleColorsAtStart->parameters);
    
    holdModParamFloatArgs.name = "particleSpeedXAlpha";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -100.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
	particleSpeedXAlpha = createModParameter(holdModParamFloatArgs);
    parameters.add(particleSpeedXAlpha->parameters);
    
    holdModParamFloatArgs.name = "particleSpeedXBrightness";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -100.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
	particleSpeedXBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(particleSpeedXBrightness->parameters);
    
    holdModParamFloatArgs.name = "particleColor1Hue";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	particleColor1Hue = createModParameter(holdModParamFloatArgs);
    parameters.add(particleColor1Hue->parameters);
    
    holdModParamFloatArgs.name = "particleColor1Saturation";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	particleColor1Saturation = createModParameter(holdModParamFloatArgs);
    parameters.add(particleColor1Saturation->parameters);
    
    holdModParamFloatArgs.name = "particleColor1Brightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	particleColor1Brightness = createModParameter(holdModParamFloatArgs);
    parameters.add(particleColor1Brightness->parameters);
    
    holdModParamFloatArgs.name = "particleColor1Alpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	particleColor1Alpha = createModParameter(holdModParamFloatArgs);
    parameters.add(particleColor1Alpha->parameters);
    
    holdModParamBoolArgs.name = "particleColor1HSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    particleColor1HSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(particleColor1HSBAsRGB->parameters);
    
    holdModParamFloatArgs.name = "particleColor2Hue";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	particleColor2Hue = createModParameter(holdModParamFloatArgs);
    parameters.add(particleColor2Hue->parameters);
    
    holdModParamFloatArgs.name = "particleColor2Saturation";
    holdModParamFloatArgs.fixedValue = 0.6;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	particleColor2Saturation = createModParameter(holdModParamFloatArgs);
    parameters.add(particleColor2Saturation->parameters);
    
    holdModParamFloatArgs.name = "particleColor2Brightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	particleColor2Brightness = createModParameter(holdModParamFloatArgs);
    parameters.add(particleColor2Brightness->parameters);
    
    holdModParamFloatArgs.name = "particleColor2Alpha";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	particleColor2Alpha = createModParameter(holdModParamFloatArgs);
    parameters.add(particleColor2Alpha->parameters);
    
    holdModParamBoolArgs.name = "particleColor2HSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    particleColor2HSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(particleColor2HSBAsRGB->parameters);
    
    particleColorMixCurve.setValueArrayToRamp(0, 1);
    particleColorMixCurve.setName("particleColorMixCurve");
    parameters.add(particleColorMixCurve.parameters);
    
    // create shape & merge parameters
    shape.setup("shape_");
    shape.positionX->setSoftMin(-20.0f);
    shape.positionX->setSoftMax(20.0f);
    shape.positionY->setSoftMin(-20.0f);
    shape.positionY->setSoftMax(20.0f);
    mergeParameters(shape.parameters, shape.modParameters);
 
    // add listener to relevent parameters:
    maximumActiveParticles.addListener(this, &TXFluidParticles::maximumActiveParticlesChanged);
 
    // init
    killParticles();
}

void TXFluidParticles::advanceBy(float timeDeltaArg) {
	for(int i=0; i<maximumActiveParticles; i++) {
        particles[i].advanceBy(timeDeltaArg);
	};
}

void TXFluidParticles::trigger(const ofVec2f &force1Pos) {
    ofColor currentColor1;
    ofColor currentColor2;
    if (particleColor1HSBAsRGB->getBool()) {
        currentColor1.set(particleColor1Hue->getFloat() * 255.0f, particleColor1Saturation->getFloat() * 255.0f, particleColor1Brightness->getFloat() * 255.0f, particleColor1Alpha->getFloat() * 255.0f);
    } else {
        currentColor1 = ofColor::fromHsb(particleColor1Hue->getFloat() * 255.0f, particleColor1Saturation->getFloat() * 255.0f, particleColor1Brightness->getFloat() * 255.0f, particleColor1Alpha->getFloat() * 255.0f);
    };
    if (particleColor2HSBAsRGB->getBool()) {
        currentColor2.set(particleColor2Hue->getFloat() * 255.0f, particleColor2Saturation->getFloat() * 255.0f, particleColor2Brightness->getFloat() * 255.0f, particleColor2Alpha->getFloat() * 255.0f);
    } else {
        currentColor2 = ofColor::fromHsb(particleColor2Hue->getFloat() * 255.0f, particleColor2Saturation->getFloat() * 255.0f, particleColor2Brightness->getFloat() * 255.0f, particleColor2Alpha->getFloat() * 255.0f);
    };
    ofVec2f pos;
    if (useForce1PosForParticles->getBool()) {
        pos = force1Pos;
    } else {
        pos = ofVec2f(particlePosX->getFloat(), particlePosY->getFloat());
    }
    float life = particleLifetime->getFloat();
    float lifeRand = particleLifetimeRandom->getFloat();
    float delayRand = particleStartDelayRand->getFloat();
    float randX = randomParticlePosX->getFloat();
    float randY = randomParticlePosY->getFloat();
    float spreadDiameter = particleSpreadDiameter->getFloat();
    bool lockColors = lockParticleColorsAtStart->getBool();
    // add particles
    for(int i=0; i<numParticlesPerTrigger->getInt(); i++) {
        ofVec2f holdPos = pos + ofVec2f(ofRandom(randX), ofRandom(randY)) + (msa::Rand::randVec2f() * spreadDiameter);
        float holdLifetime = life + ofRandom(lifeRand);
        float holdDelayRand = ofRandom(delayRand);
        float mass = ofRandom(0.8, 1.0);
		addParticle(holdPos, holdLifetime, holdDelayRand, currentColor1, currentColor2, lockColors, mass);
    };
}

void TXFluidParticles::addParticle(const ofVec2f &pos, float &lifetimeArg, float &startDelay, ofColor &startColor1Arg, ofColor &startColor2Arg, bool &lockColors, float &massArg){
    // init & increment index
    particles[curIndex].init(pos.x, pos.y, lifetimeArg, startDelay, startColor1Arg, startColor2Arg, lockColors, massArg);
	curIndex++;
	if(curIndex >= maximumActiveParticles) curIndex = 0;
}

void TXFluidParticles::updateAndDraw(const msa::fluid::Solver &solver, float &width, float &height) {
    ofColor currentColor1;
    ofColor currentColor2;
    if (particleColor1HSBAsRGB->getBool()) {
        currentColor1.set(particleColor1Hue->getFloat() * 255.0f, particleColor1Saturation->getFloat() * 255.0f, particleColor1Brightness->getFloat() * 255.0f, particleColor1Alpha->getFloat() * 255.0f);
    } else {
        currentColor1 = ofColor::fromHsb(particleColor1Hue->getFloat() * 255.0f, particleColor1Saturation->getFloat() * 255.0f, particleColor1Brightness->getFloat() * 255.0f, particleColor1Alpha->getFloat() * 255.0f);
    };
    if (particleColor2HSBAsRGB->getBool()) {
        currentColor2.set(particleColor2Hue->getFloat() * 255.0f, particleColor2Saturation->getFloat() * 255.0f, particleColor2Brightness->getFloat() * 255.0f, particleColor2Alpha->getFloat() * 255.0f);
    } else {
        currentColor2 = ofColor::fromHsb(particleColor2Hue->getFloat() * 255.0f, particleColor2Saturation->getFloat() * 255.0f, particleColor2Brightness->getFloat() * 255.0f, particleColor2Alpha->getFloat() * 255.0f);
    };
    float speedXAlpha = particleSpeedXAlpha->getFloat();
    float speedXBrightness = particleSpeedXBrightness->getFloat();

    // update
	for(int i=0; i<maximumActiveParticles; i++) {
        particles[i].update(solver);
        particles[i].updateVertexArrays(i, arrVertices, arrColors, currentColor1, currentColor2, particleColorMixCurve, speedXAlpha, speedXBrightness, width, height);
	}
    
    // draw
    draw();
}

void TXFluidParticles::draw() {
    mesh.clear();
    mesh.setMode(OF_PRIMITIVE_POINTS);
    mesh.addVertices(arrVertices, maximumActiveParticles);
    mesh.addColors(arrColors, maximumActiveParticles);
    
    ofEnableAlphaBlending();
    mesh.draw();
    ofDisableAlphaBlending();
}

void  TXFluidParticles::killParticles(int startIndex) {
    ofColor clearCol = ofFloatColor(0.0,0.0);
	for(int i=startIndex; i<MAX_PARTICLES; i++) {
        particles[i].alive = false;
        arrColors[i] = clearCol;
	}
}

void  TXFluidParticles::maximumActiveParticlesChanged(int & intArg) {
    // kill non-active particles
    killParticles(intArg);
}


