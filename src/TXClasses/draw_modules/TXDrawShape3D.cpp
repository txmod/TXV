/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

// NOTE: THIS IS THE OLD VERSION - NEW VERSION IS TXDrawShape3D

#include "TXSystem.h"
#include "TXDrawShape3D.h"
#include "ofxTweenLite.h"
#include "TXFunctions.h"

// constructor
TXDrawShape3D::TXDrawShape3D() {
    setup();
}

// destructor
TXDrawShape3D::~TXDrawShape3D() {
    // remove listeners to relevent parameters:
    ofRemoveListener(shapeType->parameters.parameterChangedE(),this,&TXDrawShape3D::shapeTypeChanged);
    ofRemoveListener(materialShininess->parameters.parameterChangedE(),this,&TXDrawShape3D::materialShininessChanged);
    
    ofRemoveListener(materialDiffuseColorHue->parameters.parameterChangedE(),this,&TXDrawShape3D::materialDiffuseColorChanged);
    ofRemoveListener(materialDiffuseColorHueRotate->parameters.parameterChangedE(),this,&TXDrawShape3D::materialDiffuseColorChanged);
    ofRemoveListener(materialDiffuseColorSaturation->parameters.parameterChangedE(),this,&TXDrawShape3D::materialDiffuseColorChanged);
    ofRemoveListener(materialDiffuseColorBrightness->parameters.parameterChangedE(),this,&TXDrawShape3D::materialDiffuseColorChanged);
    ofRemoveListener(materialDiffuseColorHSBAsRGB->parameters.parameterChangedE(),this,&TXDrawShape3D::materialDiffuseColorChanged);
    
    ofRemoveListener(materialAmbientColorHue->parameters.parameterChangedE(),this,&TXDrawShape3D::materialAmbientColorChanged);
    ofRemoveListener(materialAmbientColorHueRotate->parameters.parameterChangedE(),this,&TXDrawShape3D::materialAmbientColorChanged);
    ofRemoveListener(materialAmbientColorSaturation->parameters.parameterChangedE(),this,&TXDrawShape3D::materialAmbientColorChanged);
    ofRemoveListener(materialAmbientColorBrightness->parameters.parameterChangedE(),this,&TXDrawShape3D::materialAmbientColorChanged);
    ofRemoveListener(materialAmbientColorHSBAsRGB->parameters.parameterChangedE(),this,&TXDrawShape3D::materialAmbientColorChanged);
    
    ofRemoveListener(materialSpecularColorHue->parameters.parameterChangedE(),this,&TXDrawShape3D::materialSpecularColorChanged);
    ofRemoveListener(materialSpecularColorHueRotate->parameters.parameterChangedE(),this,&TXDrawShape3D::materialSpecularColorChanged);
    ofRemoveListener(materialSpecularColorSaturation->parameters.parameterChangedE(),this,&TXDrawShape3D::materialSpecularColorChanged);
    ofRemoveListener(materialSpecularColorBrightness->parameters.parameterChangedE(),this,&TXDrawShape3D::materialSpecularColorChanged);
    ofRemoveListener(materialSpecularColorHSBAsRGB->parameters.parameterChangedE(),this,&TXDrawShape3D::materialSpecularColorChanged);
    
    ofRemoveListener(materialEmissiveColorHue->parameters.parameterChangedE(),this,&TXDrawShape3D::materialEmissiveColorChanged);
    ofRemoveListener(materialEmissiveColorHueRotate->parameters.parameterChangedE(),this,&TXDrawShape3D::materialEmissiveColorChanged);
    ofRemoveListener(materialEmissiveColorSaturation->parameters.parameterChangedE(),this,&TXDrawShape3D::materialEmissiveColorChanged);
    ofRemoveListener(materialEmissiveColorBrightness->parameters.parameterChangedE(),this,&TXDrawShape3D::materialEmissiveColorChanged);
    ofRemoveListener(materialEmissiveColorHSBAsRGB->parameters.parameterChangedE(),this,&TXDrawShape3D::materialEmissiveColorChanged);
}

void TXDrawShape3D::setup(string paramNamePrefixArg){
    TXModParameterBoolArgs holdModParamBoolArgs;
    TXModParameterIntArgs holdModParamIntArgs;
    TXModParameterFloatArgs holdModParamFloatArgs;
    paramNamePrefix = paramNamePrefixArg;
    
    // create input paramaters
    initialiseParameters(paramNamePrefix);
    
    parameters.add(useImageAsTexture.set(paramNamePrefix + "useImageAsTexture", false));
    parameters.add(useExternalSourceImage.set(paramNamePrefix + "useExternalSourceImage", false));

    holdModParamIntArgs.name = paramNamePrefix + "shapeType";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = total3DShapeTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = total3DShapeTypes - 1;
	shapeType = createModParameter(holdModParamIntArgs);
    parameters.add(shapeType->parameters);
    
    holdModParamBoolArgs.name = paramNamePrefix + "fillShape";
    holdModParamBoolArgs.fixedValue = true;
    holdModParamBoolArgs.fixedModMix = false;
	fillShape = createModParameter(holdModParamBoolArgs);
    parameters.add(fillShape->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "distortOrder";
    holdModParamIntArgs.fixedValue = TXSHAPE3DDISTORTORDER_WAVETWISTBEND;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTORDER_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTORDER_TOTAL - 1;
	distortOrder = createModParameter(holdModParamIntArgs);
    parameters.add(distortOrder->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "width";
    holdModParamFloatArgs.fixedValue = 0.2;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	width = createModParameter(holdModParamFloatArgs);
    parameters.add(width->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "height";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	height = createModParameter(holdModParamFloatArgs);
    parameters.add(height->parameters);
    
    parameters.add(useMaxWidthToScaleHeight.set(paramNamePrefix + "useMaxWidthToScaleHeight", false));
    
    holdModParamFloatArgs.name = paramNamePrefix + "depth";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	depth = createModParameter(holdModParamFloatArgs);
    parameters.add(depth->parameters);
    
    parameters.add(useMaxWidthToScaleDepth.set(paramNamePrefix + "useMaxWidthToScaleDepth", false));
    
    holdModParamFloatArgs.name = paramNamePrefix + "radius";
    holdModParamFloatArgs.fixedValue = 0.2;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	radius = createModParameter(holdModParamFloatArgs);
    parameters.add(radius->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "roundness";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	roundness = createModParameter(holdModParamFloatArgs);
    parameters.add(roundness->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "resolutionWidth";
    holdModParamIntArgs.fixedValue = 24;
    holdModParamIntArgs.hardMin = 2;
    holdModParamIntArgs.hardMax = 1024;
    holdModParamIntArgs.softMin = 2;
    holdModParamIntArgs.softMax = 128;
	resolutionWidth = createModParameter(holdModParamIntArgs);
    parameters.add(resolutionWidth->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "resolutionHeight";
    holdModParamIntArgs.fixedValue = 24;
    holdModParamIntArgs.hardMin = 2;
    holdModParamIntArgs.hardMax = 1024;
    holdModParamIntArgs.softMin = 2;
    holdModParamIntArgs.softMax = 128;
	resolutionHeight = createModParameter(holdModParamIntArgs);
    parameters.add(resolutionHeight->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "resolutionDepth";
    holdModParamIntArgs.fixedValue = 24;
    holdModParamIntArgs.hardMin = 2;
    holdModParamIntArgs.hardMax = 1024;
    holdModParamIntArgs.softMin = 2;
    holdModParamIntArgs.softMax = 128;
	resolutionDepth = createModParameter(holdModParamIntArgs);
    parameters.add(resolutionDepth->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "resolutionRadius";
    holdModParamIntArgs.fixedValue = 24;
    holdModParamIntArgs.hardMin = 2;
    holdModParamIntArgs.hardMax = 1024;
    holdModParamIntArgs.softMin = 2;
    holdModParamIntArgs.softMax = 128;
	resolutionRadius = createModParameter(holdModParamIntArgs);
    parameters.add(resolutionRadius->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "resolutionIsoSphere";
    holdModParamIntArgs.fixedValue = 3;
    holdModParamIntArgs.hardMin = 1;
    holdModParamIntArgs.hardMax = 5;
    holdModParamIntArgs.softMin = 1;
    holdModParamIntArgs.softMax = 5;
	resolutionIsoSphere = createModParameter(holdModParamIntArgs);
    parameters.add(resolutionIsoSphere->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "resolutionCap";
    holdModParamIntArgs.fixedValue = 12;
    holdModParamIntArgs.hardMin = 2;
    holdModParamIntArgs.hardMax = 1024;
    holdModParamIntArgs.softMin = 2;
    holdModParamIntArgs.softMax = 128;
	resolutionCap = createModParameter(holdModParamIntArgs);
    parameters.add(resolutionCap->parameters);
    
    parameters.add(resolutionParaShape.set(paramNamePrefix + "resolutionParaShape", 48, 2, 256));
    
    parameters.add(smoothDistortedParaShape.set(paramNamePrefix + "smoothDistortedParaShape", true));

    holdModParamFloatArgs.name = paramNamePrefix + "x1";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	x1 = createModParameter(holdModParamFloatArgs);
    parameters.add(x1->parameters);
    
    parameters.add(x1Quantize.set(paramNamePrefix + "x1Quantize", false));
    
    holdModParamFloatArgs.name = paramNamePrefix + "x2";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	x2 = createModParameter(holdModParamFloatArgs);
    parameters.add(x2->parameters);
    
    parameters.add(x2Quantize.set(paramNamePrefix + "x2Quantize", false));
    
    holdModParamFloatArgs.name = paramNamePrefix + "x3";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	x3 = createModParameter(holdModParamFloatArgs);
    parameters.add(x3->parameters);
    
    parameters.add(x3Quantize.set(paramNamePrefix + "x3Quantize", false));
    
    holdModParamFloatArgs.name = paramNamePrefix + "y1";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	y1 = createModParameter(holdModParamFloatArgs);
    parameters.add(y1->parameters);
    
    parameters.add(y1Quantize.set(paramNamePrefix + "y1Quantize", false));
    
    holdModParamFloatArgs.name = paramNamePrefix + "y2";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	y2 = createModParameter(holdModParamFloatArgs);
    parameters.add(y2->parameters);
    
    parameters.add(y2Quantize.set(paramNamePrefix + "y2Quantize", false));
    
    holdModParamFloatArgs.name = paramNamePrefix + "y3";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	y3 = createModParameter(holdModParamFloatArgs);
    parameters.add(y3->parameters);
    
    parameters.add(y3Quantize.set(paramNamePrefix + "y3Quantize", false));
        
    holdModParamFloatArgs.name = paramNamePrefix + "z1";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	z1 = createModParameter(holdModParamFloatArgs);
    parameters.add(z1->parameters);
    
    parameters.add(z1Quantize.set(paramNamePrefix + "z1Quantize", false));
    
    holdModParamFloatArgs.name = paramNamePrefix + "z2";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	z2 = createModParameter(holdModParamFloatArgs);
    parameters.add(z2->parameters);
    
    parameters.add(z2Quantize.set(paramNamePrefix + "z2Quantize", false));
    
    holdModParamFloatArgs.name = paramNamePrefix + "z3";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -2.0;
    holdModParamFloatArgs.softMax = 2.0;
	z3 = createModParameter(holdModParamFloatArgs);
    parameters.add(z3->parameters);
    
    parameters.add(z3Quantize.set(paramNamePrefix + "z3Quantize", false));
    
    parameters.add(useXValsForY.set(paramNamePrefix + "useXValsForY", false));
    
    parameters.add(useXValsForZ.set(paramNamePrefix + "useXValsForZ", false));
    parameters.add(ignoreAllXYZVals.set(paramNamePrefix + "ignoreAllXYZVals", false));

    holdModParamFloatArgs.name = paramNamePrefix + "positionX";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	positionX = createModParameter(holdModParamFloatArgs);
    parameters.add(positionX->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "positionY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	positionY = createModParameter(holdModParamFloatArgs);
    parameters.add(positionY->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "positionZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = -1.0;
    holdModParamFloatArgs.softMax = 0.0;
	positionZ = createModParameter(holdModParamFloatArgs);
    parameters.add(positionZ->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "rotateX";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	rotateX = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateX->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "rotateY";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	rotateY = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateY->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "rotateZ";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -360.0;
    holdModParamFloatArgs.hardMax = 360.0;
    holdModParamFloatArgs.softMin = -360.0;
    holdModParamFloatArgs.softMax = 360.0;
	rotateZ = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateZ->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "rotateMultiply";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
	rotateMultiply = createModParameter(holdModParamFloatArgs);
    parameters.add(rotateMultiply->parameters);
        
    holdModParamFloatArgs.name = paramNamePrefix + "anchorX";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	anchorX = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorX->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "anchorY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	anchorY = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorY->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "anchorZ";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	anchorZ = createModParameter(holdModParamFloatArgs);
    parameters.add(anchorZ->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "scaleX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 3.0;
	scaleX = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleX->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "scaleY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 3.0;
	scaleY = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleY->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "scaleZ";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = -10.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 3.0;
	scaleZ = createModParameter(holdModParamFloatArgs);
    parameters.add(scaleZ->parameters);
    
    parameters.add(useScaleXForScaleY.set(paramNamePrefix + "useScaleXForScaleY", false));
    parameters.add(useScaleXForScaleZ.set(paramNamePrefix + "useScaleXForScaleZ", false));
    
	// material:
    holdModParamFloatArgs.name = paramNamePrefix + "materialShininess";
    holdModParamFloatArgs.fixedValue = 25.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 128.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 128.0;
	materialShininess = createModParameter(holdModParamFloatArgs);
    parameters.add(materialShininess->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "materialDiffuseColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialDiffuseColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(materialDiffuseColorHue->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "materialDiffuseColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialDiffuseColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(materialDiffuseColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "materialDiffuseColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialDiffuseColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(materialDiffuseColorSaturation->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "materialDiffuseColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialDiffuseColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(materialDiffuseColorBrightness->parameters);
    
    holdModParamBoolArgs.name = paramNamePrefix + "materialDiffuseColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	materialDiffuseColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(materialDiffuseColorHSBAsRGB->parameters);
    
    parameters.add(useDiffuseColorForAmbient.set(paramNamePrefix + "useDiffuseColorForAmbient", false));
    
    holdModParamFloatArgs.name = paramNamePrefix + "materialAmbientColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialAmbientColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(materialAmbientColorHue->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "materialAmbientColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialAmbientColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(materialAmbientColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "materialAmbientColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialAmbientColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(materialAmbientColorSaturation->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "materialAmbientColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialAmbientColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(materialAmbientColorBrightness->parameters);
    
    holdModParamBoolArgs.name = paramNamePrefix + "materialAmbientColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	materialAmbientColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(materialAmbientColorHSBAsRGB->parameters);
    
    parameters.add(useDiffuseColorForSpecular.set(paramNamePrefix + "useDiffuseColorForSpecular", false));
    
    holdModParamFloatArgs.name = paramNamePrefix + "materialSpecularColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialSpecularColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(materialSpecularColorHue->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "materialSpecularColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialSpecularColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(materialSpecularColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "materialSpecularColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialSpecularColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(materialSpecularColorSaturation->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "materialSpecularColorBrightness";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialSpecularColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(materialSpecularColorBrightness->parameters);
    
    holdModParamBoolArgs.name = paramNamePrefix + "materialSpecularColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	materialSpecularColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(materialSpecularColorHSBAsRGB->parameters);
    
    parameters.add(useDiffuseColorForEmissive.set(paramNamePrefix + "useDiffuseColorForEmissive", false));
    
    holdModParamFloatArgs.name = paramNamePrefix + "materialEmissiveColorHue";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialEmissiveColorHue = createModParameter(holdModParamFloatArgs);
    parameters.add(materialEmissiveColorHue->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "materialEmissiveColorHueRotate";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialEmissiveColorHueRotate = createModParameter(holdModParamFloatArgs);
    parameters.add(materialEmissiveColorHueRotate->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "materialEmissiveColorSaturation";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialEmissiveColorSaturation = createModParameter(holdModParamFloatArgs);
    parameters.add(materialEmissiveColorSaturation->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "materialEmissiveColorBrightness";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	materialEmissiveColorBrightness = createModParameter(holdModParamFloatArgs);
    parameters.add(materialEmissiveColorBrightness->parameters);
    
    holdModParamBoolArgs.name = paramNamePrefix + "materialEmissiveColorHSBAsRGB";
    holdModParamBoolArgs.fixedValue = false;
    holdModParamBoolArgs.fixedModMix = false;
	materialEmissiveColorHSBAsRGB = createModParameter(holdModParamBoolArgs);
    parameters.add(materialEmissiveColorHSBAsRGB->parameters);
    
    // mesh distortion
    
    holdModParamBoolArgs.name = paramNamePrefix + "waveDistortActive";
    holdModParamBoolArgs.fixedValue = false;
    waveDistortActive = createModParameter(holdModParamBoolArgs);
    parameters.add(waveDistortActive->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "wave1Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalDistortionWaveTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalDistortionWaveTypes - 1;
	wave1Type = createModParameter(holdModParamIntArgs);
    parameters.add(wave1Type->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "wave1Phase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    wave1Phase = createModParameter(holdModParamFloatArgs);
    parameters.add(wave1Phase->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "wave1Freq";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 20.0;
    wave1Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(wave1Freq->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "wave2Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalDistortionWaveTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalDistortionWaveTypes - 1;
	wave2Type = createModParameter(holdModParamIntArgs);
    parameters.add(wave2Type->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "wave2Phase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    wave2Phase = createModParameter(holdModParamFloatArgs);
    parameters.add(wave2Phase->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "wave2Freq";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 20.0;
    wave2Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(wave2Freq->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "wave3Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalDistortionWaveTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalDistortionWaveTypes - 1;
    wave3Type = createModParameter(holdModParamIntArgs);
    parameters.add(wave3Type->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "wave3Phase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    wave3Phase = createModParameter(holdModParamFloatArgs);
    parameters.add(wave3Phase->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "wave3Freq";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 20.0;
    wave3Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(wave3Freq->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "wave4Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalDistortionWaveTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalDistortionWaveTypes - 1;
    wave4Type = createModParameter(holdModParamIntArgs);
    parameters.add(wave4Type->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "wave4Phase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    wave4Phase = createModParameter(holdModParamFloatArgs);
    parameters.add(wave4Phase->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "wave4Freq";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 20.0;
    wave4Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(wave4Freq->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "wave5Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalDistortionWaveTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalDistortionWaveTypes - 1;
    wave5Type = createModParameter(holdModParamIntArgs);
    parameters.add(wave5Type->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "wave5Phase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    wave5Phase = createModParameter(holdModParamFloatArgs);
    parameters.add(wave5Phase->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "wave5Freq";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 20.0;
    wave5Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(wave5Freq->parameters);
    
    // perlins
    
    holdModParamIntArgs.name = paramNamePrefix + "perlin1Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalPerlinTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalPerlinTypes - 1;
	perlin1Type = createModParameter(holdModParamIntArgs);
    parameters.add(perlin1Type->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "perlin1Offset";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
    perlin1Offset = createModParameter(holdModParamFloatArgs);
    parameters.add(perlin1Offset->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "perlin1Freq";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 20.0;
    perlin1Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(perlin1Freq->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "perlin2Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalPerlinTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalPerlinTypes - 1;
	perlin2Type = createModParameter(holdModParamIntArgs);
    parameters.add(perlin2Type->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "perlin2Offset";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
    perlin2Offset = createModParameter(holdModParamFloatArgs);
    parameters.add(perlin2Offset->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "perlin2Freq";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 20.0;
    perlin2Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(perlin2Freq->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "perlin3Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = totalPerlinTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = totalPerlinTypes - 1;
	perlin3Type = createModParameter(holdModParamIntArgs);
    parameters.add(perlin3Type->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "perlin3Offset";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 10.0;
    perlin3Offset = createModParameter(holdModParamFloatArgs);
    parameters.add(perlin3Offset->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "perlin3Freq";
    holdModParamFloatArgs.fixedValue = 0.1;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 100.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 20.0;
    perlin3Freq = createModParameter(holdModParamFloatArgs);
    parameters.add(perlin3Freq->parameters);
    
    parameters.add(waveDistort1On.set(paramNamePrefix + "waveDistort1On", false));
    
    holdModParamFloatArgs.name = paramNamePrefix + "waveDistort1Depth";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    waveDistort1Depth = createModParameter(holdModParamFloatArgs);
    parameters.add(waveDistort1Depth->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "waveDistort1Waveform";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTWAVE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTWAVE_TOTAL - 1;
    waveDistort1Waveform = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort1Waveform->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "waveDistort1Axis";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTAXIS_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTAXIS_TOTAL - 1;
    waveDistort1Axis = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort1Axis->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "waveDistort1Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTTYPE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTTYPE_TOTAL - 1;
    waveDistort1Type = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort1Type->parameters);
 
    parameters.add(waveDistort2On.set(paramNamePrefix + "waveDistort2On", false));
    
    holdModParamFloatArgs.name = paramNamePrefix + "waveDistort2Depth";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    waveDistort2Depth = createModParameter(holdModParamFloatArgs);
    parameters.add(waveDistort2Depth->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "waveDistort2Waveform";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTWAVE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTWAVE_TOTAL - 1;
    waveDistort2Waveform = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort2Waveform->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "waveDistort2Axis";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTAXIS_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTAXIS_TOTAL - 1;
    waveDistort2Axis = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort2Axis->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "waveDistort2Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTTYPE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTTYPE_TOTAL - 1;
    waveDistort2Type = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort2Type->parameters);
    
    parameters.add(waveDistort3On.set(paramNamePrefix + "waveDistort3On", false));
    
    holdModParamFloatArgs.name = paramNamePrefix + "waveDistort3Depth";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    waveDistort3Depth = createModParameter(holdModParamFloatArgs);
    parameters.add(waveDistort3Depth->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "waveDistort3Waveform";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTWAVE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTWAVE_TOTAL - 1;
    waveDistort3Waveform = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort3Waveform->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "waveDistort3Axis";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTAXIS_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTAXIS_TOTAL - 1;
    waveDistort3Axis = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort3Axis->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "waveDistort3Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTTYPE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTTYPE_TOTAL - 1;
    waveDistort3Type = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort3Type->parameters);
    
    parameters.add(waveDistort4On.set(paramNamePrefix + "waveDistort4On", false));
    
    holdModParamFloatArgs.name = paramNamePrefix + "waveDistort4Depth";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    waveDistort4Depth = createModParameter(holdModParamFloatArgs);
    parameters.add(waveDistort4Depth->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "waveDistort4Waveform";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTWAVE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTWAVE_TOTAL - 1;
    waveDistort4Waveform = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort4Waveform->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "waveDistort4Axis";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTAXIS_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTAXIS_TOTAL - 1;
    waveDistort4Axis = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort4Axis->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "waveDistort4Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTTYPE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTTYPE_TOTAL - 1;
    waveDistort4Type = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort4Type->parameters);
    
    parameters.add(waveDistort5On.set(paramNamePrefix + "waveDistort5On", false));
    
    holdModParamFloatArgs.name = paramNamePrefix + "waveDistort5Depth";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    waveDistort5Depth = createModParameter(holdModParamFloatArgs);
    parameters.add(waveDistort5Depth->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "waveDistort5Waveform";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTWAVE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTWAVE_TOTAL - 1;
    waveDistort5Waveform = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort5Waveform->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "waveDistort5Axis";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTAXIS_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTAXIS_TOTAL - 1;
    waveDistort5Axis = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort5Axis->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "waveDistort5Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTTYPE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTTYPE_TOTAL - 1;
    waveDistort5Type = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort5Type->parameters);
    
    parameters.add(waveDistort6On.set(paramNamePrefix + "waveDistort6On", false));
    
    holdModParamFloatArgs.name = paramNamePrefix + "waveDistort6Depth";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 10.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    waveDistort6Depth = createModParameter(holdModParamFloatArgs);
    parameters.add(waveDistort6Depth->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "waveDistort6Waveform";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTWAVE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTWAVE_TOTAL - 1;
    waveDistort6Waveform = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort6Waveform->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "waveDistort6Axis";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTAXIS_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTAXIS_TOTAL - 1;
    waveDistort6Axis = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort6Axis->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "waveDistort6Type";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = TXSHAPE3DDISTORTTYPE_TOTAL - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = TXSHAPE3DDISTORTTYPE_TOTAL - 1;
    waveDistort6Type = createModParameter(holdModParamIntArgs);
    parameters.add(waveDistort6Type->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "focusPointX";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	focusPointX = createModParameter(holdModParamFloatArgs);
    parameters.add(focusPointX->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "focusPointY";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	focusPointY = createModParameter(holdModParamFloatArgs);
    parameters.add(focusPointY->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "focusPointZ";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = -20.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	focusPointZ = createModParameter(holdModParamFloatArgs);
    parameters.add(focusPointZ->parameters);
    
    holdModParamBoolArgs.name = paramNamePrefix + "twistActive";
    holdModParamBoolArgs.fixedValue = false;
    twistActive = createModParameter(holdModParamBoolArgs);
    parameters.add(twistActive->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "twistPhase";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    twistPhase = createModParameter(holdModParamFloatArgs);
    parameters.add(twistPhase->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "twistAxis";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = 2;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = 2;
	twistAxis = createModParameter(holdModParamIntArgs);
    parameters.add(twistAxis->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "twistFreq";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = -30.0;
    holdModParamFloatArgs.hardMax = 30.0;
    holdModParamFloatArgs.softMin = -3.0;
    holdModParamFloatArgs.softMax = 3.0;
    twistFreq = createModParameter(holdModParamFloatArgs);
    parameters.add(twistFreq->parameters);
    
    holdModParamBoolArgs.name = paramNamePrefix + "twistMiddleReverse";
    holdModParamBoolArgs.fixedValue = true;
    twistMiddleReverse = createModParameter(holdModParamBoolArgs);
    parameters.add(twistMiddleReverse->parameters);
    
    holdModParamBoolArgs.name = paramNamePrefix + "useCentroidForTwistFocusPoint";
    holdModParamBoolArgs.fixedValue = false;
    useCentroidForTwistFocusPoint = createModParameter(holdModParamBoolArgs);
    parameters.add(useCentroidForTwistFocusPoint->parameters);
    
    holdModParamBoolArgs.name = paramNamePrefix + "bendActive";
    holdModParamBoolArgs.fixedValue = false;
    bendActive = createModParameter(holdModParamBoolArgs);
    parameters.add(bendActive->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "bendRadius";
    holdModParamFloatArgs.fixedValue = 0.5;
    holdModParamFloatArgs.fixedModMix = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 20.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	bendRadius = createModParameter(holdModParamFloatArgs);
    parameters.add(bendRadius->parameters);
    
    holdModParamIntArgs.name = paramNamePrefix + "bendType";
    holdModParamIntArgs.fixedValue = 0;
    holdModParamIntArgs.hardMin = 0;
    holdModParamIntArgs.hardMax = numBendTypes - 1;
    holdModParamIntArgs.softMin = 0;
    holdModParamIntArgs.softMax = numBendTypes - 1;
	bendType = createModParameter(holdModParamIntArgs);
    parameters.add(bendType->parameters);
    
    holdModParamBoolArgs.name = paramNamePrefix + "bendInflationEffect";
    holdModParamBoolArgs.fixedValue = false;
    bendInflationEffect = createModParameter(holdModParamBoolArgs);
    parameters.add(bendInflationEffect->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "bendAmountX";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	bendAmountX = createModParameter(holdModParamFloatArgs);
    parameters.add(bendAmountX->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "bendAmountY";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	bendAmountY = createModParameter(holdModParamFloatArgs);
    parameters.add(bendAmountY->parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "bendAmountZ";
    holdModParamFloatArgs.fixedValue = 1.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
	bendAmountZ = createModParameter(holdModParamFloatArgs);
    parameters.add(bendAmountZ->parameters);
    
    holdModParamBoolArgs.name = paramNamePrefix + "useCentroidForBendFocusPoint";
    holdModParamBoolArgs.fixedValue = false;
    useCentroidForBendFocusPoint = createModParameter(holdModParamBoolArgs);
    parameters.add(useCentroidForBendFocusPoint->parameters);
 
    wave1CustomCurve.setValueArrayToRamp(0, 1);
    wave1CustomCurve.setName(paramNamePrefix + "wave1CustomCurve");
    parameters.add(wave1CustomCurve.parameters);
    
    wave1CustomCurve2.setValueArrayToRamp(0, 1);
    wave1CustomCurve2.setName(paramNamePrefix + "wave1CustomCurve2");
    parameters.add(wave1CustomCurve2.parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "wave1CustomCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    wave1CustomCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(wave1CustomCurveMorph->parameters);
    
    wave2CustomCurve.setValueArrayToRamp(0, 1);
    wave2CustomCurve.setName(paramNamePrefix + "wave2CustomCurve");
    parameters.add(wave2CustomCurve.parameters);
    
    wave2CustomCurve2.setValueArrayToRamp(0, 1);
    wave2CustomCurve2.setName(paramNamePrefix + "wave2CustomCurve2");
    parameters.add(wave2CustomCurve2.parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "wave2CustomCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    wave2CustomCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(wave2CustomCurveMorph->parameters);
    
    wave3CustomCurve.setValueArrayToRamp(0, 1);
    wave3CustomCurve.setName(paramNamePrefix + "wave3CustomCurve");
    parameters.add(wave3CustomCurve.parameters);
    
    wave3CustomCurve2.setValueArrayToRamp(0, 1);
    wave3CustomCurve2.setName(paramNamePrefix + "wave3CustomCurve2");
    parameters.add(wave3CustomCurve2.parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "wave3CustomCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    wave3CustomCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(wave3CustomCurveMorph->parameters);
    
    wave4CustomCurve.setValueArrayToRamp(0, 1);
    wave4CustomCurve.setName(paramNamePrefix + "wave4CustomCurve");
    parameters.add(wave4CustomCurve.parameters);
    
    wave4CustomCurve2.setValueArrayToRamp(0, 1);
    wave4CustomCurve2.setName(paramNamePrefix + "wave4CustomCurve2");
    parameters.add(wave4CustomCurve2.parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "wave4CustomCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    wave4CustomCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(wave4CustomCurveMorph->parameters);
    
    wave5CustomCurve.setValueArrayToRamp(0, 1);
    wave5CustomCurve.setName(paramNamePrefix + "wave5CustomCurve");
    parameters.add(wave5CustomCurve.parameters);
    
    wave5CustomCurve2.setValueArrayToRamp(0, 1);
    wave5CustomCurve2.setName(paramNamePrefix + "wave5CustomCurve2");
    parameters.add(wave5CustomCurve2.parameters);
    
    holdModParamFloatArgs.name = paramNamePrefix + "wave5CustomCurveMorph";
    holdModParamFloatArgs.fixedValue = 0.0;
    holdModParamFloatArgs.hardMin = 0.0;
    holdModParamFloatArgs.hardMax = 1.0;
    holdModParamFloatArgs.softMin = 0.0;
    holdModParamFloatArgs.softMax = 1.0;
    wave5CustomCurveMorph = createModParameter(holdModParamFloatArgs);
    parameters.add(wave5CustomCurveMorph->parameters);
    
    // add listener to relevent parameters:
    resolutionParaShape.addListener(this, &TXDrawShape3D::resolutionParaShapeChanged);
    useDiffuseColorForAmbient.addListener(this, &TXDrawShape3D::useDiffuseColorForAmbientChanged);
    useDiffuseColorForSpecular.addListener(this, &TXDrawShape3D::useDiffuseColorForSpecularChanged);
    useDiffuseColorForEmissive.addListener(this, &TXDrawShape3D::useDiffuseColorForEmissiveChanged);

    // add listener to relevent mod parameters:
     ofAddListener(shapeType->parameters.parameterChangedE(),this,&TXDrawShape3D::shapeTypeChanged);
    ofAddListener(materialShininess->parameters.parameterChangedE(),this,&TXDrawShape3D::materialShininessChanged);

    ofAddListener(materialDiffuseColorHue->parameters.parameterChangedE(),this,&TXDrawShape3D::materialDiffuseColorChanged);
    ofAddListener(materialDiffuseColorHueRotate->parameters.parameterChangedE(),this,&TXDrawShape3D::materialDiffuseColorChanged);
    ofAddListener(materialDiffuseColorSaturation->parameters.parameterChangedE(),this,&TXDrawShape3D::materialDiffuseColorChanged);
    ofAddListener(materialDiffuseColorBrightness->parameters.parameterChangedE(),this,&TXDrawShape3D::materialDiffuseColorChanged);
    ofAddListener(materialDiffuseColorHSBAsRGB->parameters.parameterChangedE(),this,&TXDrawShape3D::materialDiffuseColorChanged);

    ofAddListener(materialAmbientColorHue->parameters.parameterChangedE(),this,&TXDrawShape3D::materialAmbientColorChanged);
    ofAddListener(materialAmbientColorHueRotate->parameters.parameterChangedE(),this,&TXDrawShape3D::materialAmbientColorChanged);
    ofAddListener(materialAmbientColorSaturation->parameters.parameterChangedE(),this,&TXDrawShape3D::materialAmbientColorChanged);
    ofAddListener(materialAmbientColorBrightness->parameters.parameterChangedE(),this,&TXDrawShape3D::materialAmbientColorChanged);
    ofAddListener(materialAmbientColorHSBAsRGB->parameters.parameterChangedE(),this,&TXDrawShape3D::materialAmbientColorChanged);

    ofAddListener(materialSpecularColorHue->parameters.parameterChangedE(),this,&TXDrawShape3D::materialSpecularColorChanged);
    ofAddListener(materialSpecularColorHueRotate->parameters.parameterChangedE(),this,&TXDrawShape3D::materialSpecularColorChanged);
    ofAddListener(materialSpecularColorSaturation->parameters.parameterChangedE(),this,&TXDrawShape3D::materialSpecularColorChanged);
    ofAddListener(materialSpecularColorBrightness->parameters.parameterChangedE(),this,&TXDrawShape3D::materialSpecularColorChanged);
    ofAddListener(materialSpecularColorHSBAsRGB->parameters.parameterChangedE(),this,&TXDrawShape3D::materialSpecularColorChanged);

    ofAddListener(materialEmissiveColorHue->parameters.parameterChangedE(),this,&TXDrawShape3D::materialEmissiveColorChanged);
    ofAddListener(materialEmissiveColorHueRotate->parameters.parameterChangedE(),this,&TXDrawShape3D::materialEmissiveColorChanged);
    ofAddListener(materialEmissiveColorSaturation->parameters.parameterChangedE(),this,&TXDrawShape3D::materialEmissiveColorChanged);
    ofAddListener(materialEmissiveColorBrightness->parameters.parameterChangedE(),this,&TXDrawShape3D::materialEmissiveColorChanged);
    ofAddListener(materialEmissiveColorHSBAsRGB->parameters.parameterChangedE(),this,&TXDrawShape3D::materialEmissiveColorChanged);

    // add listener to relevent parameters:
    useImageAsTexture.addListener(this, &TXDrawShape3D::useImageAsTextureChanged);
    useExternalSourceImage.addListener(this, &TXDrawShape3D::useExternalSourceImageChanged);

    // asset slots
    createImageAssetSlot("sourceImageAsset");
    
    // external image slots
    createExtImageModuleSlot("extSourceImageModule");
    
    // register Texture
    registerTexture();

    // initialise material
    material.setShininess(25.0);
    setMaterialDiffuseColor(getCurrentDiffuseColor());
    setMaterialAmbientColor(getCurrentAmbientColor());
    setMaterialSpecularColor(getCurrentSpecularColor());
    setMaterialEmissiveColor(getCurrentEmissiveColor());
    
    // init image ptrs
    sourceImage = &holdImage1;
    newImage = &holdImage2;
    
    accumlator = 0.0;
    flipper = 1.0;
    
    // init 
    applyPosDistortion = false;
    retryMapTexture = false;
    //distortedMesh.setUsage(GL_DYNAMIC_DRAW);
    shapePtr = &sphere;
    sphere.setMode(OF_PRIMITIVE_TRIANGLES);
    icoSphere.setMode(OF_PRIMITIVE_TRIANGLES);
    cylinder.setMode(OF_PRIMITIVE_TRIANGLES);
    cone.setMode(OF_PRIMITIVE_TRIANGLES);
    //uncappedCone.getMesh().setMode(OF_PRIMITIVE_TRIANGLES);
    box.setMode(OF_PRIMITIVE_TRIANGLES);
    plane.setMode(OF_PRIMITIVE_TRIANGLES);
    //paraBuilder.setup(0, resolutionParaShape, resolutionParaShape);
}

void TXDrawShape3D::update(){
    float holdWidth, holdHeight, holdDepth, holdRadius, holdRoundness;
    int holdResolutionWidth, holdResolutionHeight, holdResolutionDepth, holdResolutionRadius, holdResolutionIsoSphere, holdResolutionCap;
    int count;
    int holdShapeType = shapeType->getInt();
    float holdXVals[3];
    float holdYVals[3];
    float holdZVals[3];
    float heightScale, depthScale;
    ofImage * tempImage;

    if (useMaxWidthToScaleHeight) {
        heightScale = getMaxWidth();
    } else {
        heightScale = getMaxHeight();
    };
    if (useMaxWidthToScaleDepth) {
        depthScale = getMaxWidth();
    } else {
        depthScale = getMaxDepth();
    };
    
    if (sourceImageHasChanged) {
        loadSourceImage();
        sourceImageHasChanged = false;
    };
    // if new image loaded then swap images & remap
    if (newImage->getTexture().isAllocated()) {
        tempImage = sourceImage;
        sourceImage = newImage;
        newImage = tempImage;
        newImage->clear();
        retryMapTexture = true;
    };
        
    if (materialDiffuseColorHasChanged) {
        setMaterialDiffuseColor(getCurrentDiffuseColor());
    };
    if (materialAmbientColorHasChanged) {
        setMaterialAmbientColor(getCurrentAmbientColor());
    };
    if (materialSpecularColorHasChanged) {
        setMaterialSpecularColor(getCurrentSpecularColor());
    };
    if (materialEmissiveColorHasChanged) {
        setMaterialEmissiveColor(getCurrentEmissiveColor());
    };
    switch (holdShapeType) {
        case TXSHAPE3DTYPE_SPHERE:
            shapePtr = &sphere;
            holdRadius = radius->getFloat() * getMaxWidth();
            holdResolutionRadius = resolutionRadius->getInt();
            sphere.set(holdRadius, holdResolutionRadius, OF_PRIMITIVE_TRIANGLES);
            sizeX = sizeY = sizeZ = holdRadius * 2;
            invertDistortedNormals = true;
            break;
        case TXSHAPE3DTYPE_ICOSPHERE:
            shapePtr = &icoSphere;
            holdRadius = radius->getFloat() * getMaxWidth();
            holdResolutionIsoSphere = resolutionIsoSphere->getInt();
            icoSphere.set(holdRadius, holdResolutionIsoSphere);
            sizeX = sizeY = sizeZ = holdRadius * 2;
            invertDistortedNormals = true;
            break;
        case TXSHAPE3DTYPE_BOX:
            shapePtr = &box;
            holdWidth = width->getFloat() * getMaxWidth();
            holdHeight = height->getFloat() * heightScale;
            holdDepth = depth->getFloat() * depthScale;
            holdResolutionWidth = resolutionWidth->getInt();
            holdResolutionHeight = resolutionHeight->getInt();
            holdResolutionDepth = resolutionDepth->getInt();
            box.set(holdWidth, holdHeight, holdDepth, holdResolutionWidth, holdResolutionHeight, holdResolutionDepth);
            sizeX = holdWidth;
            sizeY = holdHeight;
            sizeZ = holdDepth;
            invertDistortedNormals = false;
            break;
        case TXSHAPE3DTYPE_PLANE:
            shapePtr = &plane;
            holdWidth = width->getFloat() * getMaxWidth();
            holdHeight = height->getFloat() * heightScale;
            holdResolutionWidth = resolutionWidth->getInt();
            holdResolutionHeight = resolutionHeight->getInt();
            plane.set(holdWidth, holdHeight, holdResolutionWidth, holdResolutionHeight, OF_PRIMITIVE_TRIANGLES);
            sizeX = holdWidth;
            sizeY = holdHeight;
            sizeZ = holdWidth;
            invertDistortedNormals = false;
            break;
        case TXSHAPE3DTYPE_CYLINDER:
            shapePtr = &roundedCylinder;
            holdHeight = height->getFloat() * heightScale;
            holdRadius = radius->getFloat() * getMaxWidth();
            holdRoundness = 0.001;
            holdResolutionRadius = resolutionRadius->getInt();
            holdResolutionHeight = resolutionHeight->getInt();
            holdResolutionCap = resolutionCap->getInt();
            sphere.set(holdRadius, holdResolutionCap, OF_PRIMITIVE_TRIANGLES);
            cylinder.set(holdRadius, holdHeight, holdResolutionRadius, holdResolutionHeight, holdResolutionCap, false, OF_PRIMITIVE_TRIANGLES);
            sizeX = sizeZ = holdRadius * 2;
            sizeY = holdHeight;
            buildRoundedCylinder(sizeY, holdRoundness);
            invertDistortedNormals = false;
            break;
        case TXSHAPE3DTYPE_ROUNDEDCYLINDER:
            shapePtr = &roundedCylinder;
            holdHeight = height->getFloat() * heightScale;
            holdRadius = radius->getFloat() * getMaxWidth();
            holdRoundness = roundness->getFloat();
            holdResolutionRadius = resolutionRadius->getInt();
            holdResolutionHeight = resolutionHeight->getInt();
            holdResolutionCap = resolutionCap->getInt();
            sphere.set(holdRadius, holdResolutionCap, OF_PRIMITIVE_TRIANGLES);
            cylinder.set(holdRadius, holdHeight, holdResolutionRadius, holdResolutionHeight, holdResolutionCap, false, OF_PRIMITIVE_TRIANGLES);
            sizeX = sizeZ = holdRadius * 2;
            sizeY = holdHeight;
            buildRoundedCylinder(sizeY, holdRoundness);
            invertDistortedNormals = false;
            break;
        case TXSHAPE3DTYPE_UNCAPPEDCYLINDER:
            shapePtr = &cylinder;
            holdHeight = height->getFloat() * heightScale;
            holdRadius = radius->getFloat() * getMaxWidth();
            holdResolutionRadius = resolutionRadius->getInt();
            holdResolutionHeight = resolutionHeight->getInt();
            cylinder.set(holdRadius, holdHeight, holdResolutionRadius, holdResolutionHeight, holdResolutionCap, false, OF_PRIMITIVE_TRIANGLES);
            sizeX = sizeZ = holdRadius * 2;
            sizeY = holdHeight;
            cylinder.setCapped(false);
            invertDistortedNormals = false;
            break;
        case TXSHAPE3DTYPE_CONE:
            shapePtr = &cone;
            holdHeight = height->getFloat() * heightScale;
            holdRadius = radius->getFloat() * getMaxWidth();
            holdResolutionRadius = resolutionRadius->getInt();
            holdResolutionHeight = resolutionHeight->getInt();
            holdResolutionCap = resolutionCap->getInt();
            cone.set(holdRadius, holdHeight, holdResolutionRadius, holdResolutionHeight, holdResolutionCap, OF_PRIMITIVE_TRIANGLES);
            sizeX = sizeZ = holdRadius * 2;
            sizeY = holdHeight;
            invertDistortedNormals = false;
            break;
        case TXSHAPE3DTYPE_ROUNDEDCONE:
            shapePtr = &roundedCone;
            holdHeight = height->getFloat() * heightScale;
            holdRadius = radius->getFloat() * getMaxWidth();
            holdRoundness = roundness->getFloat();
            holdResolutionRadius = resolutionRadius->getInt();
            holdResolutionHeight = resolutionHeight->getInt();
            holdResolutionCap = resolutionCap->getInt();
            sphere.set(holdRadius, holdResolutionCap, OF_PRIMITIVE_TRIANGLES);
            cone.set(holdRadius, holdHeight, holdResolutionRadius, holdResolutionHeight, 64, OF_PRIMITIVE_TRIANGLES);
            sizeX = sizeZ = holdRadius * 2;
            sizeY = holdHeight;
            buildRoundedCone(sizeY, holdRoundness);
            invertDistortedNormals = false;
            break;
        case TXSHAPE3DTYPE_UNCAPPEDCONE:
            shapePtr = &uncappedCone;
            holdHeight = height->getFloat() * heightScale;
            holdRadius = radius->getFloat() * getMaxWidth();
            holdResolutionRadius = resolutionRadius->getInt();
            holdResolutionHeight = resolutionHeight->getInt();
            cone.set(holdRadius, holdHeight, holdResolutionRadius, holdResolutionHeight, 2, OF_PRIMITIVE_TRIANGLE_STRIP);
            uncappedCone.getMesh() = cone.getConeMesh();
            count = uncappedCone.getMesh().getNumIndices();
            uncappedCone.getMesh().setIndex(count-1, uncappedCone.getMesh().getIndex(count-2));
            sizeX = sizeZ = holdRadius * 2;
            sizeY = holdHeight;
            invertDistortedNormals = false;
            break;
//        case TXSHAPE3DTYPE_ICOSAHEDRON:
//            shapePtr = &icosahedron;
//            holdRadius = radius->getFloat() * getMaxWidth();
//            icosahedron.getMesh() = icosahedronMesh.icosahedron(holdRadius);
//            sizeX = sizeY = sizeZ = holdRadius * 2;
//                invertDistortedNormals = false;
//            break;
            default:
            // default = paraShape
            shapePtr = &paraShape;
            paraBuilder.setup((holdShapeType - (total3DShapeTypes - paraBuilder.totalShapes)), resolutionParaShape, resolutionParaShape);
            paraSurface = paraBuilder.getShape();
            if (resolutionParaShapeHasChanged) {
                paraSurface->setup(resolutionParaShape, resolutionParaShape);
                resolutionParaShapeHasChanged = false;
            };
            holdWidth = width->getFloat() * getMaxWidth();
            holdHeight = height->getFloat() * heightScale;
            holdDepth = depth->getFloat() * depthScale;
            if (ignoreAllXYZVals) {
                for(int i = 0; i < 3; i++){
                    holdXVals[i] = 1; // default value
                    holdYVals[i] = 1;
                    holdZVals[i] = 1;
                };
            } else {
                if (x1Quantize) {
                    holdXVals[0] = lrintf(x1->getFloat());
                } else {
                    holdXVals[0] = x1->getFloat();
                };
                if (x2Quantize) {
                    holdXVals[1] = lrintf(x2->getFloat());
                } else {
                    holdXVals[1] = x2->getFloat();
                };
                if (x3Quantize) {
                    holdXVals[2] = lrintf(x3->getFloat());
                } else {
                    holdXVals[2] = x3->getFloat();
                };
                if (useXValsForY) {
                    for(int i = 0; i < 3; i++){
                        holdYVals[i] = holdXVals[i];
                    };
                } else {
                    if (y1Quantize) {
                        holdYVals[0] = lrintf(y1->getFloat());
                    } else {
                        holdYVals[0] = y1->getFloat();
                    };
                    if (y2Quantize) {
                        holdYVals[1] = lrintf(y2->getFloat());
                    } else {
                        holdYVals[1] = y2->getFloat();
                    };
                    if (y3Quantize) {
                        holdYVals[2] = lrintf(y3->getFloat());
                    } else {
                        holdYVals[2] = y3->getFloat();
                    };
                };
                if (useXValsForZ) {
                    for(int i = 0; i < 3; i++){
                        holdZVals[i] = holdXVals[i];
                    };
                } else {
                    if (z1Quantize) {
                        holdZVals[0] = lrintf(z1->getFloat());
                    } else {
                        holdZVals[0] = z1->getFloat();
                    };
                    if (z2Quantize) {
                        holdZVals[1] = lrintf(z2->getFloat());
                    } else {
                        holdZVals[1] = z2->getFloat();
                    };
                    if (x3Quantize) {
                        holdZVals[2] = lrintf(z3->getFloat());
                    } else {
                        holdZVals[2] = z3->getFloat();
                    };
                };
            };
            paraSurface->width = holdWidth;
            paraSurface->height = holdHeight;
            paraSurface->depth = holdDepth;
            paraSurface->textureWidth = fmax(texWidth, 1);
            paraSurface->textureHeight = fmax(texHeight, 1);
            paraSurface->setXVals(holdXVals);
            paraSurface->setYVals(holdYVals);
            paraSurface->setZVals(holdZVals);
            // always reload
            // TESTING XXX - CHANGED FOR OF0.9.8
            //paraSurface->reload(smoothDistortedParaShape); // OLD
            paraSurface->reload();
            paraShape.enableNormals();
            paraShape.enableTextures();
            paraShape.disableColors();
            paraShape = plane; // init
            // TESTING XXX - CHANGED FOR OF0.9.8
            // OLD
            //            if (smoothDistortedParaShape) {
            //                paraShape.getMesh() = paraSurface->getIndexedMesh();
            //            } else {
            //                paraShape.getMesh() = paraSurface->getMesh();
            //            };
            paraShape.getMesh() = paraSurface->getMesh();
            paraMeshCentroid = paraShape.getMesh().getCentroid();
            sizeX = holdWidth;
            sizeY = holdHeight;
            sizeZ = holdDepth;
            invertDistortedNormals = false;
            break;
    }
    // check if retry needed to map texture 
    if (retryMapTexture) {
        mapTextureToShape();
    };

    // apply position distortion
    bool holdwaveDistortActive, holdtwistActive, holdbendActive;
    holdwaveDistortActive = waveDistortActive->getBool();
    holdtwistActive = twistActive->getBool();
    holdbendActive = bendActive->getBool();
    if (holdwaveDistortActive || holdtwistActive || holdbendActive) {
        applyPosDistortion = true;
        distortedMesh = shapePtr->getMesh();
        distortedMesh.enableTextures();
        distortedMesh.disableColors();

        int holddistortOrder;
        float holdtwistPhase, holdtwistFreq;
        int   holdtwistAxis;
        bool  holdbendInflationEffect;
        int   holdbendType;
        float holdbendAmountX, holdbendAmountY, holdbendAmountZ, holdbendRadius;
        bool  holdtwistMiddleReverse, holduseCentroidForTwist, holduseCentroidForBend;
        ofVec3f focusPoint = ofVec3f(0, 0, 0);
        ofVec3f shapeCentroid = ofVec3f(0, 0, 0);
        // prepare vars
        holddistortOrder = distortOrder->getInt();

        if(holdwaveDistortActive) {
            holdwave1Type = wave1Type->getInt();
            holdwave2Type = wave2Type->getInt();
            holdwave3Type = wave3Type->getInt();
            holdwave4Type = wave4Type->getInt();
            holdwave5Type = wave5Type->getInt();
            holdwave1CustomCurveMorph = wave1CustomCurveMorph->getFloat();
            holdwave2CustomCurveMorph = wave2CustomCurveMorph->getFloat();
            holdwave3CustomCurveMorph = wave3CustomCurveMorph->getFloat();
            holdwave4CustomCurveMorph = wave4CustomCurveMorph->getFloat();
            holdwave5CustomCurveMorph = wave5CustomCurveMorph->getFloat();
            holdwave1Phase = wave1Phase->getFloat();
            holdwave2Phase = wave2Phase->getFloat();
            holdwave3Phase = wave3Phase->getFloat();
            holdwave4Phase = wave4Phase->getFloat();
            holdwave5Phase = wave5Phase->getFloat();
            holdwave1Freq = wave1Freq->getFloat();
            holdwave2Freq = wave2Freq->getFloat();
            holdwave3Freq = wave3Freq->getFloat();
            holdwave4Freq = wave4Freq->getFloat();
            holdwave5Freq = wave5Freq->getFloat();
            holdperlin1Type = perlin1Type->getInt();
            holdperlin2Type = perlin2Type->getInt();
            holdperlin3Type = perlin3Type->getInt();
            holdperlin1Freq = perlin1Freq->getFloat();
            holdperlin2Freq = perlin2Freq->getFloat();
            holdperlin3Freq = perlin3Freq->getFloat();
            holdperlin1Offset = perlin1Offset->getFloat();
            holdperlin2Offset = perlin2Offset->getFloat();
            holdperlin3Offset = perlin3Offset->getFloat();
        };
        float holdwaveDistort1Depth;
        int holdwaveDistort1Waveform;
        int holdwaveDistort1Axis;
        int holdwaveDistort1Type;
        float holdwaveDistort2Depth;
        int holdwaveDistort2Waveform;
        int holdwaveDistort2Axis;
        int holdwaveDistort2Type;
        float holdwaveDistort3Depth;
        int holdwaveDistort3Waveform;
        int holdwaveDistort3Axis;
        int holdwaveDistort3Type;
        float holdwaveDistort4Depth;
        int holdwaveDistort4Waveform;
        int holdwaveDistort4Axis;
        int holdwaveDistort4Type;
        float holdwaveDistort5Depth;
        int holdwaveDistort5Waveform;
        int holdwaveDistort5Axis;
        int holdwaveDistort5Type;
        float holdwaveDistort6Depth;
        int holdwaveDistort6Waveform;
        int holdwaveDistort6Axis;
        int holdwaveDistort6Type;
        if (waveDistort1On) {
            holdwaveDistort1Depth = waveDistort1Depth->getFloat();
            holdwaveDistort1Waveform = waveDistort1Waveform->getInt();
            holdwaveDistort1Axis = waveDistort1Axis->getInt();
            holdwaveDistort1Type = waveDistort1Type->getInt();
        };
        if (waveDistort2On) {
            holdwaveDistort2Depth = waveDistort2Depth->getFloat();
            holdwaveDistort2Waveform = waveDistort2Waveform->getInt();
            holdwaveDistort2Axis = waveDistort2Axis->getInt();
            holdwaveDistort2Type = waveDistort2Type->getInt();
        };
        if (waveDistort3On) {
            holdwaveDistort3Depth = waveDistort3Depth->getFloat();
            holdwaveDistort3Waveform = waveDistort3Waveform->getInt();
            holdwaveDistort3Axis = waveDistort3Axis->getInt();
            holdwaveDistort3Type = waveDistort3Type->getInt();
        };
        if (waveDistort4On) {
            holdwaveDistort4Depth = waveDistort4Depth->getFloat();
            holdwaveDistort4Waveform = waveDistort4Waveform->getInt();
            holdwaveDistort4Axis = waveDistort4Axis->getInt();
            holdwaveDistort4Type = waveDistort4Type->getInt();
        };
        if (waveDistort5On) {
            holdwaveDistort5Depth = waveDistort5Depth->getFloat();
            holdwaveDistort5Waveform = waveDistort5Waveform->getInt();
            holdwaveDistort5Axis = waveDistort5Axis->getInt();
            holdwaveDistort5Type = waveDistort5Type->getInt();
        };
        if (waveDistort6On) {
            holdwaveDistort6Depth = waveDistort6Depth->getFloat();
            holdwaveDistort6Waveform = waveDistort6Waveform->getInt();
            holdwaveDistort6Axis = waveDistort6Axis->getInt();
        };
        bool centroidNeeded = false;
        bool focusPointNeeded = false;
        if(holdtwistActive) {
            holdtwistPhase = twistPhase->getFloat();
            holdtwistAxis = twistAxis->getInt();
            holdtwistFreq = twistFreq->getFloat();
            holdtwistMiddleReverse = twistMiddleReverse->getBool();
            holduseCentroidForTwist = useCentroidForTwistFocusPoint->getBool();
            if (holduseCentroidForTwist) {
                centroidNeeded = true;
            } else {
                focusPointNeeded = true;
            };
        };
        if(holdbendActive) {
            holdbendRadius = bendRadius->getFloat();
            holdbendType = bendType->getInt();
            holdbendInflationEffect = bendInflationEffect->getBool();
            holdbendAmountX = bendAmountX->getFloat();
            holdbendAmountY = bendAmountY->getFloat();
            holdbendAmountZ = bendAmountZ->getFloat();
            holduseCentroidForBend = useCentroidForBendFocusPoint->getBool();
            if (holduseCentroidForBend) {
                centroidNeeded = true;
            } else {
                focusPointNeeded = true;
            };
        };
        if (centroidNeeded){
            shapeCentroid = distortedMesh.getCentroid();
        };
        if (focusPointNeeded){
            focusPoint = ofVec3f(focusPointX->getFloat() * getMaxWidth(), focusPointY->getFloat() * getMaxHeight(), focusPointZ->getFloat() * getMaxDepth());
        };        
        switch (holddistortOrder) {
            case TXSHAPE3DDISTORTORDER_WAVETWISTBEND:
                setDistortOrderIndices(1,2,3);
                break;
            case TXSHAPE3DDISTORTORDER_WAVEBENDTWIST:
                setDistortOrderIndices(1,3,2);
                break;
            case TXSHAPE3DDISTORTORDER_TWISTBENDWAVE:
                setDistortOrderIndices(2,3,1);
                break;
            case TXSHAPE3DDISTORTORDER_TWISTWAVEBEND:
                setDistortOrderIndices(2,1,3);
                break;
            case TXSHAPE3DDISTORTORDER_BENDTWISTWAVE:
                setDistortOrderIndices(3,2,1);
                break;
            case TXSHAPE3DDISTORTORDER_BENDWAVETWIST:
                setDistortOrderIndices(3,1,2);
                break;
            default:
                setDistortOrderIndices(1,2,3);
                break;
        };
        // change each vertex
        ofVec3f holdVertex, twistCenter, rotatePoint, newVertex, bendPoint;
        TXParameterFloat256 * customCurve;
        
        for(int i = 0; i < distortedMesh.getNumVertices(); i++ ) {
            holdVertex = distortedMesh.getVertex( i );
            // apply distortions in order
            for(int j = 0; j < 3; j++ ) {
                switch (distortOrderIndices[j]) {
                    case 1:
                        // add waves
                        if(holdwaveDistortActive) {
                            if (waveDistort1On) {
                                distortVertex(holdVertex, holdwaveDistort1Depth, holdwaveDistort1Waveform, holdwaveDistort1Axis, holdwaveDistort1Type, sizeX, sizeY, sizeZ);
                            };
                            if (waveDistort2On) {
                                distortVertex(holdVertex, holdwaveDistort2Depth, holdwaveDistort2Waveform, holdwaveDistort2Axis, holdwaveDistort2Type, sizeX, sizeY, sizeZ);
                            };
                            if (waveDistort3On) {
                                distortVertex(holdVertex, holdwaveDistort3Depth, holdwaveDistort3Waveform, holdwaveDistort3Axis, holdwaveDistort3Type, sizeX, sizeY, sizeZ);
                            };
                            if (waveDistort4On) {
                                distortVertex(holdVertex, holdwaveDistort4Depth, holdwaveDistort4Waveform, holdwaveDistort4Axis, holdwaveDistort4Type, sizeX, sizeY, sizeZ);
                            };
                            if (waveDistort5On) {
                                distortVertex(holdVertex, holdwaveDistort5Depth, holdwaveDistort5Waveform, holdwaveDistort5Axis, holdwaveDistort5Type, sizeX, sizeY, sizeZ);
                            };
                            if (waveDistort6On) {
                                distortVertex(holdVertex, holdwaveDistort6Depth, holdwaveDistort6Waveform, holdwaveDistort6Axis, holdwaveDistort6Type, sizeX, sizeY, sizeZ);
                            };
                        };
                        // end of if(holdwaveDistortActive..
                        break;
                    case 2:
                        // add twist
                        if(holdtwistActive) {
                            if (holduseCentroidForTwist) {
                                twistCenter = shapeCentroid;
                            } else {
                                twistCenter = focusPoint;
                            };
                            float rotation;
                            if (holdtwistAxis == 0) {
                                rotatePoint = ofVec3f(holdVertex.x, twistCenter.y, twistCenter.z);
                                rotation = holdVertex.x / sizeX;
                            } else if (holdtwistAxis == 1) {
                                rotatePoint = ofVec3f(twistCenter.x, holdVertex.y, twistCenter.z);
                                rotation = holdVertex.y / sizeY;
                            } else {
                                rotatePoint = ofVec3f(twistCenter.x, twistCenter.y, holdVertex.z);
                                rotation = holdVertex.z / sizeZ;
                            };
                            
                            float rotMultiply;
                            if (holdtwistMiddleReverse && (rotation < 0)) {
                                rotMultiply = -1;
                            } else {
                                rotMultiply = 1;
                            };
                            float offset = rotMultiply * 360 * (holdtwistPhase + (holdtwistFreq * rotation));
                            newVertex = holdVertex;
                            //newVertex.rotate(fmod(offset, 360.0f), rotatePoint);
                            newVertex.rotate(offset, rotatePoint);
                            // set vertex
                            holdVertex = newVertex;
                        };
                        break;
                    case 3:
                        // add bend
                        if (holdbendActive) {
                            if (holduseCentroidForBend) {
                                bendPoint = shapeCentroid;
                            } else {
                                bendPoint = focusPoint;
                            };
                            float radius = holdbendRadius * getMaxWidth();
                            float distance = holdVertex.distance(bendPoint);
                            float tweenedPhase = ofxTweenLite::tween ( 0, 1, distance/ radius, (ofEaseFunction) (holdbendType));
                            ofVec3f diffVecNorm = (holdVertex - bendPoint).getNormalized();
                            ofVec3f adjustedVec = ofVec3f(diffVecNorm.x * holdbendAmountX, diffVecNorm.y * holdbendAmountY, diffVecNorm.z * holdbendAmountZ);
                            // set vertex
                            if (holdbendInflationEffect) {
                                holdVertex = bendPoint + (adjustedVec * radius * tweenedPhase);
                            } else {
                                holdVertex = holdVertex + (adjustedVec * radius * tweenedPhase);
                            };
                        };
                        break;
                    default:
                        // no action
                        break;
                }; // end of switch
            };
            // update vertex
            distortedMesh.setVertex( i, holdVertex );
        };
        // end of for getNumVertices
        calcDistortedMeshNormals();
    } else {
        applyPosDistortion = false;
    };
}

void TXDrawShape3D::draw(){
    float holdRotateMultiply = rotateMultiply->getFloat();
    float holdRotateX = holdRotateMultiply * rotateX->getFloat();
    float holdRotateY = holdRotateMultiply * rotateY->getFloat();
    float holdRotateZ = holdRotateMultiply * rotateZ->getFloat();
    float holdAnchorX, holdAnchorY, holdAnchorZ;
    float holdScaleX, holdScaleY, holdScaleZ;
    
    if (!drawActive->getBool()) {
        return;
    };
    if (shapePtr == NULL) {
        return;
    };
    
    holdScaleX = scaleX->getFloat();
    if (useScaleXForScaleY) {
        holdScaleY = holdScaleX;
    } else {
        holdScaleY = scaleY->getFloat();
    };
    if (useScaleXForScaleZ) {
        holdScaleZ = holdScaleX;
    } else {
        holdScaleZ = scaleZ->getFloat();
    };
    if (isParaShape()) {
        holdAnchorX = (paraMeshCentroid.x + ((anchorX->getFloat() - 0.5) * sizeX)) * holdScaleX;
        holdAnchorY = (paraMeshCentroid.y + ((anchorY->getFloat() - 0.5) * sizeY)) * holdScaleY;
        holdAnchorZ = (paraMeshCentroid.z + ((anchorZ->getFloat() - 0.5) * sizeZ)) * holdScaleZ;
    } else {
        holdAnchorX = (anchorX->getFloat() - 0.5) * sizeX * holdScaleX;
        holdAnchorY = (anchorY->getFloat() - 0.5) * sizeY * holdScaleY;
        holdAnchorZ = (anchorZ->getFloat() - 0.5) * sizeZ * holdScaleZ;
    };

    shapePtr->setPosition(positionX->getFloat() * getMaxWidth(), positionY->getFloat() * getMaxHeight(), positionZ->getFloat() * getMaxDepth());
    shapePtr->setOrientation(ofVec3f(holdRotateX, holdRotateY, holdRotateZ));
    shapePtr->setScale(holdScaleX, holdScaleY, holdScaleZ);
    
    // tex coords for 3D objects in OF are from 0 -> 1, not 0 -> image.width
    // so we must disable the arb rectangle call to allow 0 -> 1
    bool holdUsingArbTex = ofGetUsingArbTex();
    ofDisableArbTex();

//    // testing xxx - makes no difference to parashape texture bug??:
//      // ofDisableArb if not paraShapes
//    if (!isParaShape()) {
//        ofDisableArbTex();
//        // testing xxx
//    } else {
//        ofEnableArbTex();
//    };
    
    // bind texture if valid
    bool validTexture = false;
    int holdExtSourceID;    
    if(useImageAsTexture) {
        if (useExternalSourceImage) {
            holdExtSourceID = getExtImageModuleIDSlot("extSourceImageModule");
            if (holdExtSourceID != 0) {
                if (parentSystem->getModuleTexture(holdExtSourceID) != NULL) {
                    (* parentSystem->getModuleTexture(holdExtSourceID)).bind();
                    validTexture = true;
                };
            };
        } else {
            if (sourceImage->getTexture().isAllocated()) {
                sourceImage->getTexture().bind();
                validTexture = true;
            };
        };
    };

    // draw
    ofPushMatrix();
    material.begin();
    ofSetColor(material.getDiffuseColor());
    if (fillShape->getBool()) {
        ofFill();
        if(applyPosDistortion) {
            shapePtr->transformGL();
            ofTranslate(-holdAnchorX, -holdAnchorY, -holdAnchorZ);
            distortedMesh.draw();
            shapePtr->restoreTransformGL();
        } else {
            shapePtr->transformGL();
            shapePtr->resetTransform();
            ofTranslate(-holdAnchorX, -holdAnchorY, -holdAnchorZ);
            shapePtr->draw();
            shapePtr->restoreTransformGL();
        }
    } else {
        // if not filled, draw wireframe
        ofNoFill();
        if(applyPosDistortion) {
            shapePtr->transformGL();
            ofTranslate(-holdAnchorX, -holdAnchorY, -holdAnchorZ);
            distortedMesh.drawWireframe();
            shapePtr->restoreTransformGL();
        } else {
            shapePtr->transformGL();
            shapePtr->resetTransform();
            ofTranslate(-holdAnchorX, -holdAnchorY, -holdAnchorZ);
            shapePtr->drawWireframe();
            shapePtr->restoreTransformGL();
        }
    };
    material.end();
    ofSetColor(255.0f);
    ofPopMatrix();
    
    // unbind texture if valid
    if(useImageAsTexture && validTexture) {
        if (useExternalSourceImage) {
            int holdExtSourceID = getExtImageModuleIDSlot("extSourceImageModule");
            (* parentSystem->allModules[holdExtSourceID]->getTexture()).unbind();
        } else {
            sourceImage->getTexture().unbind();
        };
    };
    // reset UsingArbTex
    if (holdUsingArbTex) {
        ofEnableArbTex();
    };
}

void TXDrawShape3D::distortVertex(ofVec3f & argVertex, float argDepth, int argWaveform, int argAxis, int argType, float argSizeX, float argSizeY, float argSizeZ) {
    ofVec3f outVertex;
    float holdPhase;
    float axisRatio;
    float waveValue;
    float averageSize;
    
    switch (argAxis) {
        case TXSHAPE3DDISTORTAXIS_POSXONY:
            axisRatio = argVertex.y / sizeY;
            break;
        case TXSHAPE3DDISTORTAXIS_POSXONZ:
            axisRatio = argVertex.z / sizeZ;
            break;
        case TXSHAPE3DDISTORTAXIS_POSYONX:
            axisRatio = argVertex.x / sizeX;
            break;
        case TXSHAPE3DDISTORTAXIS_POSYONZ:
            axisRatio = argVertex.z / sizeZ;
            break;
        case TXSHAPE3DDISTORTAXIS_POSZONX:
            axisRatio = argVertex.x / sizeX;
            break;
        case TXSHAPE3DDISTORTAXIS_POSZONY:
            axisRatio = argVertex.y / sizeY;
            break;
        case TXSHAPE3DDISTORTAXIS_POSYZRADIALONX:
            axisRatio = argVertex.x / sizeX;
            break;
        case TXSHAPE3DDISTORTAXIS_POSXZRADIALONY:
            axisRatio = argVertex.y / sizeY;
            break;
        case TXSHAPE3DDISTORTAXIS_POSXYRADIALONZ:
            axisRatio = argVertex.z / sizeZ;
            break;
        default:
            axisRatio = argVertex.x / sizeX;
            break;
    };
    switch (argWaveform) {
        case TXSHAPE3DDISTORTWAVE_WAVE1:
            holdPhase = fmod(holdwave1Phase + (axisRatio * holdwave1Freq), 1.0f);
            waveValue = getWaveValue(holdwave1Type, holdPhase, wave1CustomCurve, wave1CustomCurve2, holdwave1CustomCurveMorph);
            break;
        case TXSHAPE3DDISTORTWAVE_WAVE2:
            holdPhase = fmod(holdwave2Phase + (axisRatio * holdwave2Freq), 1.0f);
            waveValue = getWaveValue(holdwave2Type, holdPhase, wave2CustomCurve, wave2CustomCurve2, holdwave2CustomCurveMorph);
            break;
        case TXSHAPE3DDISTORTWAVE_WAVE3:
            holdPhase = fmod(holdwave3Phase + (axisRatio * holdwave3Freq), 1.0f);
            waveValue = getWaveValue(holdwave3Type, holdPhase, wave3CustomCurve, wave3CustomCurve2, holdwave3CustomCurveMorph);
            break;
        case TXSHAPE3DDISTORTWAVE_WAVE4:
            holdPhase = fmod(holdwave4Phase + (axisRatio * holdwave4Freq), 1.0f);
            waveValue = getWaveValue(holdwave4Type, holdPhase, wave4CustomCurve, wave4CustomCurve2, holdwave4CustomCurveMorph);
            break;
        case TXSHAPE3DDISTORTWAVE_WAVE5:
            holdPhase = fmod(holdwave5Phase + (axisRatio * holdwave5Freq), 1.0f);
            waveValue = getWaveValue(holdwave5Type, holdPhase, wave5CustomCurve, wave5CustomCurve2, holdwave5CustomCurveMorph);
            break;
        case TXSHAPE3DDISTORTWAVE_PERLIN1:
            waveValue = getPerlinValue(holdperlin1Type, holdperlin1Freq, holdperlin1Offset, argVertex, argSizeX, argSizeY, argSizeZ);
            break;
        case TXSHAPE3DDISTORTWAVE_PERLIN2:
            waveValue = getPerlinValue(holdperlin2Type, holdperlin2Freq, holdperlin2Offset, argVertex, argSizeX, argSizeY, argSizeZ);
            break;
        case TXSHAPE3DDISTORTWAVE_PERLIN3:
            waveValue = getPerlinValue(holdperlin3Type, holdperlin3Freq, holdperlin3Offset, argVertex, argSizeX, argSizeY, argSizeZ);
            break;
        default:
            break;
    };
    
    switch (argAxis) {
        case TXSHAPE3DDISTORTAXIS_POSXONY:
            switch (argType) {
                case TXSHAPE3DDISTORTTYPE_MULTIPLYALL:
                    argVertex.x *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYPOS:
                    if (argVertex.x >= 0) {
                        argVertex.x *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYNEG:
                    if (argVertex.x < 0) {
                        argVertex.x *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDALL:
                    argVertex.x += argDepth * waveValue * sizeX;
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOSSUBTRACTNEG:
                    if (argVertex.x >= 0) {
                        argVertex.x += argDepth * waveValue * sizeX;
                    };
                    if (argVertex.x < 0) {
                        argVertex.x -= argDepth * waveValue * sizeX;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOS:
                    if (argVertex.x >= 0) {
                        argVertex.x += argDepth * waveValue * sizeX;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_SUBTRACTNEG:
                    if (argVertex.x < 0) {
                        argVertex.x -= argDepth * waveValue * sizeX;
                    };
                    break;
                default:
                    break;
            };
            break;
        case TXSHAPE3DDISTORTAXIS_POSXONZ:
            switch (argType) {
                case TXSHAPE3DDISTORTTYPE_MULTIPLYALL:
                    argVertex.x *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYPOS:
                    if (argVertex.x >= 0) {
                        argVertex.x *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYNEG:
                    if (argVertex.x < 0) {
                        argVertex.x *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDALL:
                    argVertex.x += argDepth * waveValue * sizeX;
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOSSUBTRACTNEG:
                    if (argVertex.x >= 0) {
                        argVertex.x += argDepth * waveValue * sizeX;
                    };
                    if (argVertex.x < 0) {
                        argVertex.x -= argDepth * waveValue * sizeX;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOS:
                    if (argVertex.x >= 0) {
                        argVertex.x += argDepth * waveValue * sizeX;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_SUBTRACTNEG:
                    if (argVertex.x < 0) {
                        argVertex.x -= argDepth * waveValue * sizeX;
                    };
                    break;
                default:
                    break;
            };
            break;
        case TXSHAPE3DDISTORTAXIS_POSYONX:
            switch (argType) {
                case TXSHAPE3DDISTORTTYPE_MULTIPLYALL:
                    argVertex.y *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYPOS:
                    if (argVertex.y >= 0) {
                        argVertex.y *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYNEG:
                    if (argVertex.y < 0) {
                        argVertex.y *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDALL:
                    argVertex.y += argDepth * waveValue * sizeY;
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOSSUBTRACTNEG:
                    if (argVertex.y >= 0) {
                        argVertex.y += argDepth * waveValue * sizeY;
                    };
                    if (argVertex.y < 0) {
                        argVertex.y -= argDepth * waveValue * sizeY;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOS:
                    if (argVertex.y >= 0) {
                        argVertex.y += argDepth * waveValue * sizeY;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_SUBTRACTNEG:
                    if (argVertex.y < 0) {
                        argVertex.y -= argDepth * waveValue * sizeY;
                    };
                    break;
                default:
                    break;
            };
            break;
        case TXSHAPE3DDISTORTAXIS_POSYONZ:
            if (argType == 0) {
                argVertex.y += argDepth * waveValue * sizeY;
            } else {
                argVertex.y *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
            };
            // TESTING XXX ===========
            switch (argType) {
                case TXSHAPE3DDISTORTTYPE_MULTIPLYALL:
                    argVertex.y *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYPOS:
                    if (argVertex.y >= 0) {
                        argVertex.y *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYNEG:
                    if (argVertex.y < 0) {
                        argVertex.y *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDALL:
                    argVertex.y += argDepth * waveValue * sizeY;
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOSSUBTRACTNEG:
                    if (argVertex.y >= 0) {
                        argVertex.y += argDepth * waveValue * sizeY;
                    };
                    if (argVertex.y < 0) {
                        argVertex.y -= argDepth * waveValue * sizeY;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOS:
                    if (argVertex.y >= 0) {
                        argVertex.y += argDepth * waveValue * sizeY;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_SUBTRACTNEG:
                    if (argVertex.y < 0) {
                        argVertex.y -= argDepth * waveValue * sizeY;
                    };
                    break;
                default:
                    break;
            };
            break;
        case TXSHAPE3DDISTORTAXIS_POSZONX:
            switch (argType) {
                case TXSHAPE3DDISTORTTYPE_MULTIPLYALL:
                    argVertex.z *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYPOS:
                    if (argVertex.z >= 0) {
                        argVertex.z *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYNEG:
                    if (argVertex.z < 0) {
                        argVertex.z *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDALL:
                    argVertex.z += argDepth * waveValue * sizeZ;
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOSSUBTRACTNEG:
                    if (argVertex.z >= 0) {
                        argVertex.z += argDepth * waveValue * sizeZ;
                    };
                    if (argVertex.z < 0) {
                        argVertex.z -= argDepth * waveValue * sizeZ;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOS:
                    if (argVertex.z >= 0) {
                        argVertex.z += argDepth * waveValue * sizeZ;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_SUBTRACTNEG:
                    if (argVertex.z < 0) {
                        argVertex.z -= argDepth * waveValue * sizeZ;
                    };
                    break;
                default:
                    break;
            };
            break;
        case TXSHAPE3DDISTORTAXIS_POSZONY:
            switch (argType) {
                case TXSHAPE3DDISTORTTYPE_MULTIPLYALL:
                    argVertex.z *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYPOS:
                    if (argVertex.z >= 0) {
                        argVertex.z *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYNEG:
                    if (argVertex.z < 0) {
                        argVertex.z *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDALL:
                    argVertex.z += argDepth * waveValue * sizeZ;
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOSSUBTRACTNEG:
                    if (argVertex.z >= 0) {
                        argVertex.z += argDepth * waveValue * sizeZ;
                    };
                    if (argVertex.z < 0) {
                        argVertex.z -= argDepth * waveValue * sizeZ;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOS:
                    if (argVertex.z >= 0) {
                        argVertex.z += argDepth * waveValue * sizeZ;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_SUBTRACTNEG:
                    if (argVertex.z < 0) {
                        argVertex.z -= argDepth * waveValue * sizeZ;
                    };
                    break;
                default:
                    break;
            };
            break;
        case TXSHAPE3DDISTORTAXIS_POSYZRADIALONX:
            switch (argType) {
                case TXSHAPE3DDISTORTTYPE_MULTIPLYALL:
                    argVertex.y *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    argVertex.z *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYPOS:
                    if (argVertex.y >= 0) {
                        argVertex.y *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    if (argVertex.z >= 0) {
                        argVertex.z *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYNEG:
                    if (argVertex.y < 0) {
                        argVertex.y *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    if (argVertex.z < 0) {
                        argVertex.z *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDALL:
                    holdDistortVector = ofVec2f(argVertex.y, argVertex.z);
                    averageSize = (sizeY + sizeZ) * 0.5;
                    holdDistortVector.scale(holdDistortVector.length() + (argDepth * waveValue * averageSize));
                    argVertex.y += holdDistortVector.x;
                    argVertex.z += holdDistortVector.y;
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOSSUBTRACTNEG:
                    holdDistortVector = ofVec2f(argVertex.y, argVertex.z);
                    averageSize = (sizeY + sizeZ) * 0.5;
                    holdDistortVector.scale(holdDistortVector.length() + (argDepth * waveValue * averageSize));
                    if (argVertex.y >= 0) {
                        argVertex.y += holdDistortVector.x;
                    } else {
                        argVertex.y -= holdDistortVector.x;
                    };
                    if (argVertex.z >= 0) {
                        argVertex.z += holdDistortVector.y;
                    } else {
                        argVertex.z -= holdDistortVector.y;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOS:
                    holdDistortVector = ofVec2f(argVertex.y, argVertex.z);
                    averageSize = (sizeY + sizeZ) * 0.5;
                    holdDistortVector.scale(holdDistortVector.length() + (argDepth * waveValue * averageSize));
                    if (argVertex.y >= 0) {
                        argVertex.y += holdDistortVector.x;
                    };
                    if (argVertex.z >= 0) {
                        argVertex.z += holdDistortVector.y;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_SUBTRACTNEG:
                    holdDistortVector = ofVec2f(argVertex.y, argVertex.z);
                    averageSize = (sizeY + sizeZ) * 0.5;
                    holdDistortVector.scale(holdDistortVector.length() + (argDepth * waveValue * averageSize));
                    if (argVertex.y < 0) {
                        argVertex.y -= holdDistortVector.x;
                    };
                    if (argVertex.z < 0) {
                        argVertex.z -= holdDistortVector.y;
                    };
                    break;
                default:
                    break;
            };
            break;
        case TXSHAPE3DDISTORTAXIS_POSXZRADIALONY:
            switch (argType) {
                case TXSHAPE3DDISTORTTYPE_MULTIPLYALL:
                    argVertex.x *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    argVertex.z *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYPOS:
                    if (argVertex.x >= 0) {
                        argVertex.x *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    if (argVertex.z >= 0) {
                        argVertex.z *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYNEG:
                    if (argVertex.x < 0) {
                        argVertex.x *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    if (argVertex.z < 0) {
                        argVertex.z *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDALL:
                    holdDistortVector = ofVec2f(argVertex.x, argVertex.z);
                    averageSize = (sizeX + sizeZ) * 0.5;
                    holdDistortVector.scale(holdDistortVector.length() + (argDepth * waveValue * averageSize));
                    argVertex.x += holdDistortVector.x;
                    argVertex.z += holdDistortVector.y;
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOSSUBTRACTNEG:
                    holdDistortVector = ofVec2f(argVertex.x, argVertex.z);
                    averageSize = (sizeX + sizeZ) * 0.5;
                    holdDistortVector.scale(holdDistortVector.length() + (argDepth * waveValue * averageSize));
                    if (argVertex.x >= 0) {
                        argVertex.x += holdDistortVector.x;
                    };
                    if (argVertex.x < 0) {
                        argVertex.x -= holdDistortVector.x;
                    };
                    
                    if (argVertex.z >= 0) {
                        argVertex.z += holdDistortVector.y;
                    };
                    if (argVertex.z < 0) {
                        argVertex.z -= holdDistortVector.y;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOS:
                    holdDistortVector = ofVec2f(argVertex.x, argVertex.z);
                    averageSize = (sizeX + sizeZ) * 0.5;
                    holdDistortVector.scale(holdDistortVector.length() + (argDepth * waveValue * averageSize));
                    if (argVertex.x >= 0) {
                        argVertex.x += holdDistortVector.x;
                    };
                    if (argVertex.z >= 0) {
                        argVertex.z += holdDistortVector.y;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_SUBTRACTNEG:
                    holdDistortVector = ofVec2f(argVertex.x, argVertex.z);
                    averageSize = (sizeX + sizeZ) * 0.5;
                    holdDistortVector.scale(holdDistortVector.length() + (argDepth * waveValue * averageSize));
                    if (argVertex.x < 0) {
                        argVertex.x -= holdDistortVector.x;
                    };
                    if (argVertex.z < 0) {
                        argVertex.z -= holdDistortVector.y;
                    };
                    break;
                default:
                    break;
            };
            break;
        case TXSHAPE3DDISTORTAXIS_POSXYRADIALONZ:
            switch (argType) {
                case TXSHAPE3DDISTORTTYPE_MULTIPLYALL:
                    argVertex.x *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    argVertex.y *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYPOS:
                    if (argVertex.x >= 0) {
                        argVertex.x *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    if (argVertex.y >= 0) {
                        argVertex.y *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_MULTIPLYNEG:
                    if (argVertex.x < 0) {
                        argVertex.x *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    if (argVertex.y < 0) {
                        argVertex.y *= (fmax(1, argDepth) - argDepth) + (argDepth * waveValue);
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDALL:
                    holdDistortVector = ofVec2f(argVertex.x, argVertex.y);
                    averageSize = (sizeX + sizeY) * 0.5;
                    holdDistortVector.scale(holdDistortVector.length() + (argDepth * waveValue * averageSize));
                    argVertex.x += holdDistortVector.x;
                    argVertex.y += holdDistortVector.y;
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOSSUBTRACTNEG:
                    holdDistortVector = ofVec2f(argVertex.x, argVertex.y);
                    averageSize = (sizeX + sizeY) * 0.5;
                    holdDistortVector.scale(holdDistortVector.length() + (argDepth * waveValue * averageSize));
                    if (argVertex.x >= 0) {
                        argVertex.x += holdDistortVector.x;
                    };
                    if (argVertex.x < 0) {
                        argVertex.x -= holdDistortVector.x;
                    };
                    
                    if (argVertex.y >= 0) {
                        argVertex.y += holdDistortVector.y;
                    };
                    if (argVertex.y < 0) {
                        argVertex.y -= holdDistortVector.y;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_ADDPOS:
                    holdDistortVector = ofVec2f(argVertex.x, argVertex.y);
                    averageSize = (sizeX + sizeY) * 0.5;
                    holdDistortVector.scale(holdDistortVector.length() + (argDepth * waveValue * averageSize));
                    if (argVertex.x >= 0) {
                        argVertex.x += holdDistortVector.x;
                    };
                    if (argVertex.y >= 0) {
                        argVertex.y += holdDistortVector.y;
                    };
                    break;
                case TXSHAPE3DDISTORTTYPE_SUBTRACTNEG:
                    holdDistortVector = ofVec2f(argVertex.x, argVertex.y);
                    averageSize = (sizeX + sizeY) * 0.5;
                    holdDistortVector.scale(holdDistortVector.length() + (argDepth * waveValue * averageSize));
                    if (argVertex.x < 0) {
                        argVertex.x -= holdDistortVector.x;
                    };
                    if (argVertex.y < 0) {
                        argVertex.y -= holdDistortVector.y;
                    };
                    break;
                default:
                    break;
            };
            break;
        default:
            break;
    };
}

void TXDrawShape3D::windowResized(int w, int h) {
    retryMapTexture = true;
}

void  TXDrawShape3D::imageAssetSlotChanged(string slotNameArg) {
    if (slotNameArg == "sourceImageAsset") {
        sourceImageHasChanged = true;
    };
}

void  TXDrawShape3D::useImageAsTextureChanged(bool & boolArg) {
    retryMapTexture = true;
}

void  TXDrawShape3D::useExternalSourceImageChanged(bool & boolArg) {
    retryMapTexture = true;
}

void TXDrawShape3D::loadSourceImage() {
    ofPtr <TXAsset> asset;
    string fileName;
    int sourceImageAssetID = getImageAssetIDSlot("sourceImageAsset").first;
    if (sourceImageAssetID != 0) {
        asset = parentSystem->getAsset(TXASSETTYPE_IMAGE, sourceImageAssetID);
        fileName = asset->getFileName();
        // load newImage
        parentSystem->imageLoader.loadFromDisk(*newImage, fileName);
    };
}

bool TXDrawShape3D::mapTextureToShape() {
    ofTexture holdTexture;
    int holdExtSourceID;
    bool validTexture = false;
    
    retryMapTexture = false;
    // map texture if valid
    if(useImageAsTexture) {
        if (useExternalSourceImage) {
            holdExtSourceID = getExtImageModuleIDSlot("extSourceImageModule");
            if (holdExtSourceID == 0) {
                retryMapTexture = true;
                return validTexture;
            } else {
                ofPtr<TXModuleBase> holdModule = parentSystem->allModules[holdExtSourceID];
                if (holdModule == NULL) {
                    retryMapTexture = true;
                    return validTexture;
                } else {
                    if (holdModule->getTexture() == NULL) {
                        retryMapTexture = true;
                        return validTexture;
                    } else {
                        holdTexture = * parentSystem->allModules[holdExtSourceID]->getTexture();
                        validTexture = true;
                    };
                };
            };
        } else {
            if (!sourceImage->getTexture().isAllocated()) {
                retryMapTexture = true;
                return validTexture;
            } else {
                holdTexture = sourceImage->getTexture();
                validTexture = true;
            };
        };
        if (validTexture) {
            texWidth = holdTexture.getWidth();
            texHeight = holdTexture.getHeight();
            if ((texWidth <= 0) || (texHeight <= 0)) {
                retryMapTexture = true;
                return validTexture;
            };
            switch (shapeType->getInt()) {
                case TXSHAPE3DTYPE_SPHERE:
                    sphere.mapTexCoordsFromTexture( holdTexture);
                    break;
                case TXSHAPE3DTYPE_ICOSPHERE:
                    icoSphere.mapTexCoordsFromTexture( holdTexture);
                    break;
                case TXSHAPE3DTYPE_BOX:
                    box.mapTexCoordsFromTexture( holdTexture);
                    break;
                case TXSHAPE3DTYPE_PLANE:
                    plane.mapTexCoordsFromTexture( holdTexture);
                    break;
                case TXSHAPE3DTYPE_CYLINDER:
                    sphere.mapTexCoordsFromTexture( holdTexture);
                    cylinder.mapTexCoordsFromTexture( holdTexture);
                    break;
                case TXSHAPE3DTYPE_ROUNDEDCYLINDER:
                    sphere.mapTexCoordsFromTexture( holdTexture);
                    cylinder.mapTexCoordsFromTexture( holdTexture);
                    break;
                case TXSHAPE3DTYPE_UNCAPPEDCYLINDER:
                    cylinder.mapTexCoordsFromTexture( holdTexture);
                    break;
                case TXSHAPE3DTYPE_CONE:
                    cone.mapTexCoordsFromTexture( holdTexture);
                    break;
                case TXSHAPE3DTYPE_ROUNDEDCONE:
                    sphere.mapTexCoordsFromTexture( holdTexture);
                    cone.mapTexCoordsFromTexture( holdTexture);
                    break;
                case TXSHAPE3DTYPE_UNCAPPEDCONE:
                    cone.mapTexCoordsFromTexture( holdTexture);
                    //uncappedCone.mapTexCoordsFromTexture( holdTexture);
                    break;
//                case TXSHAPE3DTYPE_ICOSAHEDRON:
//                    icosahedron.mapTexCoordsFromTexture( holdTexture);
//                    break;
                default:
                    // default = paraShape
                    paraShape.mapTexCoordsFromTexture( holdTexture);
                    break;
            }
        };
    };
}

int TXDrawShape3D::getTextureWidth() {
    if (sourceImage->getTexture().isAllocated()) {
        return sourceImage->getWidth();
    } else {
        return 0;
    };
}

int TXDrawShape3D::getTextureHeight() {
    if (sourceImage->getTexture().isAllocated()) {
        return sourceImage->getHeight();
    } else {
        return 0;
    };
}

ofTexture * TXDrawShape3D::getTexture() {
    if (sourceImage->getTexture().isAllocated()) {
        return & sourceImage->getTexture();
    } else {
        return NULL;
    };
}

ofPixelsRef TXDrawShape3D::getPixels() {
    return sourceImage->getPixels() ;
}

float TXDrawShape3D::getWaveValue(int & waveType, float & phase, TXParameterFloat256 & customCurve, TXParameterFloat256 & customCurve2, float customCurveMorph) {
    float outValue, holdVal;
    // adjust phase for negative values
    if (phase < 0) {
       phase = phase + 1;
    };
    switch (waveType) {
        case TXSHAPE3DDISTORTWAVEFORM_SINE:
            outValue = 0.5 + (0.5 * sin(TWO_PI * phase));
            break;
        case TXSHAPE3DDISTORTWAVEFORM_COSINE:
            outValue = 0.5 + (0.5 * cos(TWO_PI * phase));
            break;
        case TXSHAPE3DDISTORTWAVEFORM_SQUARE:
            outValue = (int) phase >= 0.5;
            break;
        case TXSHAPE3DDISTORTWAVEFORM_RAMPUP:
            outValue = phase;
            break;
        case TXSHAPE3DDISTORTWAVEFORM_RAMPDOWN:
            outValue = 1 - phase;
            break;
        case TXSHAPE3DDISTORTWAVEFORM_TRIANGLE:
            outValue = abs(1.0f - (2.0f * fmod(phase + 0.75f, 1.0f)));
            break;
        case TXSHAPE3DDISTORTWAVEFORM_CUSTOMCURVE:
            outValue = TXFunctions::getInterpCurves(customCurve, customCurve2, phase, customCurveMorph);
            break;
        case TXSHAPE3DDISTORTWAVEFORM_CUSTOMCURVE_MIRRORED:
            if (phase<0.5) {
                holdVal = 2 * phase;
            } else {
                holdVal = 1 - (2 * (phase - 0.5));
            };
            outValue = TXFunctions::getInterpCurves(customCurve, customCurve2, holdVal, customCurveMorph);
            break;
        default:
            // default rampup
            outValue = phase;
            break;
    }
    return outValue;
}

float TXDrawShape3D::getPerlinValue(int & perlinType, float & perlinFreq, float & perlinOffset, ofVec3f & position, float & argSizeX, float & argSizeY, float & argSizeZ) {
    float holdValue, holdPerlin;
    int holdSign;
    float outValue, phase, offsetX, offsetY, offsetZ;
    // based on trefoil knot
    // trefoilX = sin t + 2 sin 2t;
    // trefoilY = cos t - 2 cos 2t;
    // trefoilZ = - sin 3t;
    phase = perlinOffset * TWO_PI;
    offsetX = 0.1666666666 * (sin(phase) + (2 * sin(2 * phase)));
    offsetY = 0.1666666666 * (cos(phase) - (2 * cos(2 * phase)));
    offsetZ = 0.1666666666 * -sin(3 * phase);
    holdPerlin = ofSignedNoise(offsetX + (position.x * perlinFreq / argSizeX),
                               offsetY + (position.y * perlinFreq / argSizeY),
                               offsetZ + (position.z * perlinFreq / argSizeZ));
    switch (perlinType) {
        case PERLINTYPE_NORMAL:
            outValue = (holdPerlin + 1) / 2;
            break;
        case PERLINTYPE_QUANTISED:
            holdValue = (holdPerlin + 1) / 2;
            if (holdValue < 0.5) {
                outValue = 0.0;
            } else {
                outValue = 1.0;
            }
            break;
//        case PERLINTYPE_SQUARED:
//            if (holdPerlin < 0) {holdSign = -1;} else {holdSign = 1;};
//            holdValue = pow(abs(holdPerlin), 0.5f) * holdSign;
//            outValue = (holdValue + 1) / 2;
//            break;
//            // NOTE PERLINTYPE_RANDOMWALK IS v SIMILAR TO ORIGINAL PERLINTYPE_NORMAL
//        case PERLINTYPE_RANDOMWALK:
//            holdPerlin = holdPerlin / 25;
//            if ( ((accumlator + (holdPerlin * flipper)) > 1) || ((accumlator + (holdPerlin * flipper)) < 0)) {
//                flipper = flipper * -1;
//            };
//            accumlator += (holdPerlin * flipper);
//            outValue = accumlator;
//            break;
        default:
            outValue = 0.0;
            break;
    };
    return outValue;
}

void TXDrawShape3D::buildRoundedCylinder(float height, float roundness) {
    // invert sphere triangles
    int totalIndices = sphere.getMesh().getNumIndices();
    ofIndexType hold1, hold3;
    for( int i=0; i < totalIndices; i+=3 ){
        hold1 = sphere.getMesh().getIndex(i);
        hold3 = sphere.getMesh().getIndex(min(i+2, totalIndices-1));
        sphere.getMesh().setIndex(i, hold3);
        sphere.getMesh().setIndex(min(i+2, totalIndices-1), hold1);
    };
    roundedCylinder.getMesh() = cylinder.getMesh();
    roundedTopCapMesh = sphere.getMesh();
    roundedBottomCapMesh = sphere.getMesh();
    int totalVertices = sphere.getMesh().getNumVertices();
    ofVec3f holdTopVertex;
    ofVec3f holdBottomVertex;
    float halfHeight = height * 0.5;
    float holdRoundness = max(0.001f, roundness);
    // flatten bottom/top of top/bottom cap
    for(int i = 0; i < totalVertices; i++ ) {
        holdTopVertex = roundedTopCapMesh.getVertex( i );
        holdBottomVertex = holdTopVertex;
        // change relevent vertices
        if (holdTopVertex.y < 0.0) {
            holdTopVertex.y = 0.0;
        } else if (holdTopVertex.y > 0.0) {
            holdTopVertex.y = holdTopVertex.y * holdRoundness;
        };
        holdTopVertex.y = holdTopVertex.y + halfHeight;
        roundedTopCapMesh.setVertex(i, holdTopVertex);

        if (holdBottomVertex.y > 0.0) {
            holdBottomVertex.y = 0.0;
        } else if (holdBottomVertex.y < 0.0) {
            holdBottomVertex.y = holdBottomVertex.y * holdRoundness;
        };
        holdBottomVertex.y = holdBottomVertex.y - halfHeight;
        roundedBottomCapMesh.setVertex(i, holdBottomVertex);
    }
    roundedCylinder.getMesh().append(roundedTopCapMesh);
    roundedCylinder.getMesh().append(roundedBottomCapMesh);
}

void TXDrawShape3D::buildRoundedCone(float height, float roundness) {
    // invert sphere triangles
    int totalIndices = sphere.getMesh().getNumIndices();
    ofIndexType hold1, hold3;
    for( int i=0; i < totalIndices; i+=3 ){
        hold1 = sphere.getMesh().getIndex(i);
        hold3 = sphere.getMesh().getIndex(min(i+2, totalIndices-1));
        sphere.getMesh().setIndex(i, hold3);
        sphere.getMesh().setIndex(min(i+2, totalIndices-1), hold1);
    };
    roundedCone.getMesh() = cone.getMesh();
    roundedTopCapMesh = sphere.getMesh();
    int totalVertices = sphere.getMesh().getNumVertices();
    ofVec3f holdTopVertex;
    float halfHeight = height * 0.5;
    float holdRoundness = max(0.001f, roundness);
    for(int i = 0; i < totalVertices; i++ ) {
        holdTopVertex = roundedTopCapMesh.getVertex( i );
        // change relevent vertices
        if (holdTopVertex.y < 0.0) {
            holdTopVertex.y = 0.0;
        } else if (holdTopVertex.y > 0.0) {
            holdTopVertex.y = holdTopVertex.y * holdRoundness;
        };
        holdTopVertex.y = holdTopVertex.y + halfHeight;
        roundedTopCapMesh.setVertex(i, holdTopVertex);
    }
    roundedCone.getMesh().append(roundedTopCapMesh);
}

bool TXDrawShape3D::isParaShape() {
    return (shapeType->getInt() >= (total3DShapeTypes - TXParaShape::totalShapes));
};

// listener methods

ofColor TXDrawShape3D::getCurrentDiffuseColor() {
    return TXFunctions::txGetColor(materialDiffuseColorHue->getFloat(),  materialDiffuseColorSaturation->getFloat(),  materialDiffuseColorBrightness->getFloat(),  1.0, materialDiffuseColorHueRotate->getFloat(), materialDiffuseColorHSBAsRGB->getBool());
}

ofColor TXDrawShape3D::getCurrentAmbientColor() {
    if (useDiffuseColorForAmbient) {
        return material.getDiffuseColor();
    } else {
        return TXFunctions::txGetColor(materialAmbientColorHue->getFloat(),  materialAmbientColorSaturation->getFloat(),  materialAmbientColorBrightness->getFloat(),  1.0, materialAmbientColorHueRotate->getFloat(), materialAmbientColorHSBAsRGB->getBool());
    }
}

ofColor TXDrawShape3D::getCurrentSpecularColor() {
    if (useDiffuseColorForSpecular) {
        return material.getDiffuseColor();
    } else {
        return TXFunctions::txGetColor(materialSpecularColorHue->getFloat(),  materialSpecularColorSaturation->getFloat(),  materialSpecularColorBrightness->getFloat(),  1.0, materialSpecularColorHueRotate->getFloat(), materialSpecularColorHSBAsRGB->getBool());
    }
}

ofColor TXDrawShape3D::getCurrentEmissiveColor() {
    if (useDiffuseColorForEmissive) {
        return material.getDiffuseColor();
    } else {
        return TXFunctions::txGetColor(materialEmissiveColorHue->getFloat(),  materialEmissiveColorSaturation->getFloat(),  materialEmissiveColorBrightness->getFloat(),  1.0, materialEmissiveColorHueRotate->getFloat(), materialEmissiveColorHSBAsRGB->getBool());
    }
}

void TXDrawShape3D::setMaterialDiffuseColor(ofColor colorArg) {
    material.setDiffuseColor(colorArg);
    materialDiffuseColorHasChanged = false;
}
void TXDrawShape3D::setMaterialAmbientColor(ofColor colorArg) {
    material.setAmbientColor(colorArg);
    materialAmbientColorHasChanged = false;
}
void TXDrawShape3D::setMaterialSpecularColor(ofColor colorArg) {
    material.setSpecularColor(colorArg);
    materialSpecularColorHasChanged = false;
}
void TXDrawShape3D::setMaterialEmissiveColor(ofColor colorArg) {
    material.setEmissiveColor(colorArg);
    materialEmissiveColorHasChanged = false;
}

void  TXDrawShape3D::shapeTypeChanged(ofAbstractParameter & parameterArg ){
    retryMapTexture = true;
    resolutionParaShapeHasChanged = true;
}

void  TXDrawShape3D::resolutionParaShapeChanged(int & intArg) {
    resolutionParaShapeHasChanged = true;
}

void  TXDrawShape3D::materialShininessChanged(ofAbstractParameter & parameterArg ){
    material.setShininess(materialShininess->getFloat());
}

void  TXDrawShape3D::materialDiffuseColorChanged(ofAbstractParameter & parameterArg ){
    materialDiffuseColorHasChanged = true;
}

void  TXDrawShape3D::materialAmbientColorChanged(ofAbstractParameter & parameterArg ){
    materialAmbientColorHasChanged = true;
}

void  TXDrawShape3D::materialSpecularColorChanged(ofAbstractParameter & parameterArg ){
    materialSpecularColorHasChanged = true;
}

void  TXDrawShape3D::materialEmissiveColorChanged(ofAbstractParameter & parameterArg ){
    materialEmissiveColorHasChanged = true;
}

void  TXDrawShape3D::useDiffuseColorForAmbientChanged(bool & boolArg) {
    materialAmbientColorHasChanged = true;
}

void  TXDrawShape3D::useDiffuseColorForSpecularChanged(bool & boolArg) {
    materialSpecularColorHasChanged = true;
}

void  TXDrawShape3D::useDiffuseColorForEmissiveChanged(bool & boolArg) {
    materialEmissiveColorHasChanged = true;
}

void TXDrawShape3D::setDistortOrderIndices(int argA, int argB, int argC) {
    distortOrderIndices[0] = argA;
    distortOrderIndices[1] = argB;
    distortOrderIndices[2] = argC;
}

void TXDrawShape3D::calcDistortedMeshNormals(bool bNormalize){
    int ia;
    int ib;
    int ic;
    int holdNumIndices = distortedMesh.getNumIndices();
    int holdNumVertices = distortedMesh.getNumVertices();
    // reset normals
    for( int i=0; i < distortedMesh.getVertices().size(); i++ ) distortedMesh.getNormals()[i] = ofPoint(0,0,0);
    // if no indices, use vertices
    if (holdNumIndices == 0) {
            for( int i=0; i < holdNumVertices; i+=3 ){
                ofVec3f verta = distortedMesh.getVertices()[i];
                ofVec3f vertb = distortedMesh.getVertices()[min(i+1, holdNumVertices-1)];
                ofVec3f vertc = distortedMesh.getVertices()[min(i+2, holdNumVertices-1)];
                ofVec3f e1 = verta - vertb;
                ofVec3f e2 = vertc - vertb;
                ofVec3f no = e2.cross( e1 );
                if (invertDistortedNormals) {
                    distortedMesh.getNormals()[i] -= no;
                    distortedMesh.getNormals()[min(i+1, holdNumVertices-1)] -= no;
                    distortedMesh.getNormals()[min(i+2, holdNumVertices-1)] -= no;
                } else {
                    distortedMesh.getNormals()[i] += no;
                    distortedMesh.getNormals()[min(i+1, holdNumVertices-1)] += no;
                    distortedMesh.getNormals()[min(i+2, holdNumVertices-1)] += no;
                };
            }
    } else {
        if (distortedMesh.getMode() == OF_PRIMITIVE_TRIANGLES) {
            for( int i=0; i < holdNumIndices; i+=3 ){
                ia = distortedMesh.getIndices()[i];
                ib = distortedMesh.getIndices()[min(i+1, holdNumIndices-1)];
                ic = distortedMesh.getIndices()[min(i+2, holdNumIndices-1)];
                ofVec3f e1 = distortedMesh.getVertices()[ia] - distortedMesh.getVertices()[ib];
                ofVec3f e2 = distortedMesh.getVertices()[ic] - distortedMesh.getVertices()[ib];
                ofVec3f no = e2.cross( e1 );
                if (invertDistortedNormals) {
                    distortedMesh.getNormals()[ia] -= no;
                    distortedMesh.getNormals()[ib] -= no;
                    distortedMesh.getNormals()[ic] -= no;
                } else {
                    distortedMesh.getNormals()[ia] += no;
                    distortedMesh.getNormals()[ib] += no;
                    distortedMesh.getNormals()[ic] += no;
                };
            }
        } else {
            // OF_PRIMITIVE_TRIANGLE_STRIP
            for( int i=0; i < holdNumIndices; i++ ){
                ia = distortedMesh.getIndices()[max(i-1, 0)];
                ib = distortedMesh.getIndices() [i];
                ic = distortedMesh.getIndices()[min(i+1, holdNumIndices-1)];
                ofVec3f e1 = distortedMesh.getVertices()[ia] - distortedMesh.getVertices()[ib];
                ofVec3f e2 = distortedMesh.getVertices()[ic] - distortedMesh.getVertices()[ib];
                ofVec3f no = e2.cross( e1 );
                // depending on clockwise / winding order, subtract no if normals are flipped.
                if (invertDistortedNormals) {
                    distortedMesh.getNormals()[ib] -= no;
                } else {
                    distortedMesh.getNormals()[ib] += no;
                };
            }
        };
    };

    if (bNormalize) {
        for(int i=0; i < distortedMesh.getNormals().size(); i++ ) {
            distortedMesh.getNormals()[i].normalize();
        }
    };
}


