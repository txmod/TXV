/*
 *  Copyright 2018 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXDrawBase.h"
//#include "TXMain.h"



//enum TXWaveTerrainTYPE {
//    TXWaveTerrainTYPE_70s,
//    TXWaveTerrainTYPE_wavesCascade
//};


class TXWaveTerrain  :  public TXDrawBase
{
public:
	// constructor
	TXWaveTerrain();
    
    // destructor
    ~TXWaveTerrain();
    
    // NOTE - change totalTerrainStructureTypes when adding new types:
    static const int totalTerrainStructureTypes = 11;
    static const int totalUnaryOpProcesses = 56;
    static const int totalBinaryOpProcesses = 49;
    static const int totalColoringMethods = 20;
    
	void setup();
	void update();
	void draw();
	void allocateTexture();
    void renderTexture(bool clearFirstArg);
    void windowResized(int w, int h);
    int getTextureWidth(); // overide base class
    int getTextureHeight(); // overide base class
    void renderSizeChanged(int & intArg);
    int getRenderWidth();
    int getRenderHeight();
    ofTexture *  getTexture(); // overide base class
    
    void colorMixImageChanged(ofAbstractParameter & dummyParameterArg );
    void curvesImageChanged(ofAbstractParameter & dummyParameterArg );
    void curvesHSLImageChanged(ofAbstractParameter & dummyParameterArg );
    void shaderCodeChangedI(int & intArg);
    void shaderCodeChangedB(bool & boolArg);
    void curvesImageSetup();
    void updateColorMixImagePixels();
    void updateCurvesImagePixels();
    void updateCurvesHSLImagePixels();
	void loadRenderShader();
    
    string getVertexShader();
    string getFragmentShader();
    string getLayerAUniforms();
    void   setLayerAUniforms();
    string getLayerAValue();
    string getLayerBUniforms();
    void   setLayerBUniforms();
    string getLayerBValue();
    string getLayerCUniforms();
    void   setLayerCUniforms();
    string getLayerCValue();
    string getLayerDUniforms();
    void   setLayerDUniforms();
    string getLayerDValue();
    string getGLSLFunctions();
    string getUnaryOpProcess(int index);
    string getBinaryOpProcess(int index);
    string getUnaryOrBinaryOpProcess(int index);      //" TWOPI  TWOOVERPI   SQRTTWO "

    // WaveTerrain Parameters
    // Global:
    ofParameter<int>       terrainStructure;  // using 1/2/3/4 layers
    
    ofParameter<int>       layerABJoinProcess;  // binaryOpFuncs
    ofParameter<int>       layerBCJoinProcess;
    ofParameter<int>       layerCDJoinProcess;
    
    ofPtr<TXModParamFloat> squeezeX;
    ofPtr<TXModParamFloat> squeezeY;
    ofPtr<TXModParamFloat> skewX;
    ofPtr<TXModParamFloat> skewY;
    ofParameter<int>       outputRangeProcess;    //  options: clip/ fold/ wrap
    ofPtr<TXModParamFloat> outputRangeMin;  // default 0
    ofPtr<TXModParamFloat> outputRangeMax;  // default 1
    
    // Curves
    TXParameterFloat256    colorMixCurveA;
    TXParameterFloat256    colorMixCurveB;
    ofPtr<TXModParamFloat> colorMixCurveMorph;
    ofPtr<TXModParamFloat> colorMixCurvePhase;
    
    TXParameterFloat256    lookupCurve1A;   // curve index 0
    TXParameterFloat256    lookupCurve1B;
    ofPtr<TXModParamFloat> lookupCurve1Morph;
    ofPtr<TXModParamFloat> lookupCurve1Phase;
    TXParameterFloat256    lookupCurve2A;   // curve index 1
    TXParameterFloat256    lookupCurve2B;
    ofPtr<TXModParamFloat> lookupCurve2Morph;
    ofPtr<TXModParamFloat> lookupCurve2Phase;
    TXParameterFloat256    lookupCurve3A;   // curve index 2
    TXParameterFloat256    lookupCurve3B;
    ofPtr<TXModParamFloat> lookupCurve3Morph;
    ofPtr<TXModParamFloat> lookupCurve3Phase;
    TXParameterFloat256    lookupCurve4A;   // curve index 3
    TXParameterFloat256    lookupCurve4B;
    ofPtr<TXModParamFloat> lookupCurve4Morph;
    ofPtr<TXModParamFloat> lookupCurve4Phase;
    
    ofPtr<TXModParamFloat> perlinLayer1Mix;  // defaults: 0.533, 0.267, 0.133, 0.067
    ofPtr<TXModParamFloat> perlinLayer2Mix;
    ofPtr<TXModParamFloat> perlinLayer3Mix;
    ofPtr<TXModParamFloat> perlinLayer4Mix;

    ofParameter<int>       coloringMethod;
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
    
    TXParameterFloat256    colorHueCurveA;   // HSL curve index 0
    TXParameterFloat256    colorHueCurveB;
    ofPtr<TXModParamFloat> colorHueCurveMorph;
    ofPtr<TXModParamFloat> colorHueCurveRotate;
    TXParameterFloat256    colorSaturationCurveA;   // HSL curve index 1
    TXParameterFloat256    colorSaturationCurveB;
    ofPtr<TXModParamFloat> colorSaturationCurveMorph;
    TXParameterFloat256    colorBrightnessCurveA;   // HSL curve index 2
    TXParameterFloat256    colorBrightnessCurveB;
    ofPtr<TXModParamFloat> colorBrightnessCurveMorph;
    TXParameterFloat256    colorAlphaCurveA;   // HSL curve index 3
    TXParameterFloat256    colorAlphaCurveB;
    ofPtr<TXModParamFloat> colorAlphaCurveMorph;
    
    // Layers:
    ofParameter<bool>      layerA_usePolarCoords;
    ofPtr<TXModParamFloat> layerA_rotate;
    ofPtr<TXModParamFloat> layerA_inputXMin;
    ofPtr<TXModParamFloat> layerA_inputXMax;
    ofPtr<TXModParamFloat> layerA_inputYMin;
    ofPtr<TXModParamFloat> layerA_inputYMax;
    ofParameter<bool>      layerA_offsetProcs12InSeries;
    
    ofParameter<bool>      layerA_offsetProcess1Active;
    ofParameter<int>       layerA_offsetProcess1Type;   // unaryOpFuncs
    ofPtr<TXModParamFloat> layerA_offsetProcess1MultInputX;
    ofPtr<TXModParamFloat> layerA_offsetProcess1AddInputX;
    ofPtr<TXModParamFloat> layerA_offsetProcess1MultOutputX;
    ofPtr<TXModParamFloat> layerA_offsetProcess1MultInputY;
    ofPtr<TXModParamFloat> layerA_offsetProcess1AddInputY;
    ofPtr<TXModParamFloat> layerA_offsetProcess1MultOutputY;
    
    ofParameter<bool>      layerA_offsetProcess2Active;
    ofParameter<int>       layerA_offsetProcess2Type;   // unaryOpFuncs
    ofPtr<TXModParamFloat> layerA_offsetProcess2MultInputX;
    ofPtr<TXModParamFloat> layerA_offsetProcess2AddInputX;
    ofPtr<TXModParamFloat> layerA_offsetProcess2MultOutputX;
    ofPtr<TXModParamFloat> layerA_offsetProcess2MultInputY;
    ofPtr<TXModParamFloat> layerA_offsetProcess2AddInputY;
    ofPtr<TXModParamFloat> layerA_offsetProcess2MultOutputY;
    
    ofParameter<int>       layerA_generatorProcessType;  // unaryOpFuncs
    ofParameter<int>       layerA_genInputXYProcess;     // binaryOpFuncs
    ofPtr<TXModParamFloat> layerA_genInputXMult;
    ofPtr<TXModParamInt>   layerA_genInputXPower;
    ofPtr<TXModParamFloat> layerA_genInputYMult;
    ofPtr<TXModParamInt>   layerA_genInputYPower;
    ofPtr<TXModParamFloat> layerA_genInputMult;
    ofPtr<TXModParamFloat> layerA_genInputOffset;
    
    ofParameter<bool>      layerA_postProcess1Active;
    ofParameter<int>       layerA_postProcess1Type;       // unaryOpFuncs & binaryOpFuncs
    ofPtr<TXModParamFloat> layerA_postProcess1YVal;
    ofParameter<bool>      layerA_postProcess2Active;
    ofParameter<int>       layerA_postProcess2Type;
    ofPtr<TXModParamFloat> layerA_postProcess2YVal;
    ofParameter<bool>      layerA_postProcess3Active;
    ofParameter<int>       layerA_postProcess3Type;
    ofPtr<TXModParamFloat> layerA_postProcess3YVal;
    
    ofParameter<bool>      layerB_usePolarCoords;
    ofPtr<TXModParamFloat> layerB_rotate;
    ofPtr<TXModParamFloat> layerB_inputXMin;
    ofPtr<TXModParamFloat> layerB_inputXMax;
    ofPtr<TXModParamFloat> layerB_inputYMin;
    ofPtr<TXModParamFloat> layerB_inputYMax;
    ofParameter<bool>      layerB_offsetProcs12InSeries;
    
    ofParameter<bool>      layerB_offsetProcess1Active;
    ofParameter<int>       layerB_offsetProcess1Type;   // unaryOpFuncs
    ofPtr<TXModParamFloat> layerB_offsetProcess1MultInputX;
    ofPtr<TXModParamFloat> layerB_offsetProcess1AddInputX;
    ofPtr<TXModParamFloat> layerB_offsetProcess1MultOutputX;
    ofPtr<TXModParamFloat> layerB_offsetProcess1MultInputY;
    ofPtr<TXModParamFloat> layerB_offsetProcess1AddInputY;
    ofPtr<TXModParamFloat> layerB_offsetProcess1MultOutputY;
    
    ofParameter<bool>      layerB_offsetProcess2Active;
    ofParameter<int>       layerB_offsetProcess2Type;   // unaryOpFuncs
    ofPtr<TXModParamFloat> layerB_offsetProcess2MultInputX;
    ofPtr<TXModParamFloat> layerB_offsetProcess2AddInputX;
    ofPtr<TXModParamFloat> layerB_offsetProcess2MultOutputX;
    ofPtr<TXModParamFloat> layerB_offsetProcess2MultInputY;
    ofPtr<TXModParamFloat> layerB_offsetProcess2AddInputY;
    ofPtr<TXModParamFloat> layerB_offsetProcess2MultOutputY;
    
    ofParameter<int>       layerB_generatorProcessType;  // unaryOpFuncs
    ofParameter<int>       layerB_genInputXYProcess;     // binaryOpFuncs
    ofPtr<TXModParamFloat> layerB_genInputXMult;
    ofPtr<TXModParamInt>   layerB_genInputXPower;
    ofPtr<TXModParamFloat> layerB_genInputYMult;
    ofPtr<TXModParamInt>   layerB_genInputYPower;
    ofPtr<TXModParamFloat> layerB_genInputMult;
    ofPtr<TXModParamFloat> layerB_genInputOffset;
    
    ofParameter<bool>      layerB_postProcess1Active;
    ofParameter<int>       layerB_postProcess1Type;       // unaryOpFuncs & binaryOpFuncs
    ofPtr<TXModParamFloat> layerB_postProcess1YVal;
    ofParameter<bool>      layerB_postProcess2Active;
    ofParameter<int>       layerB_postProcess2Type;
    ofPtr<TXModParamFloat> layerB_postProcess2YVal;
    ofParameter<bool>      layerB_postProcess3Active;
    ofParameter<int>       layerB_postProcess3Type;
    ofPtr<TXModParamFloat> layerB_postProcess3YVal;
    
    ofParameter<bool>      layerC_usePolarCoords;
    ofPtr<TXModParamFloat> layerC_rotate;
    ofPtr<TXModParamFloat> layerC_inputXMin;
    ofPtr<TXModParamFloat> layerC_inputXMax;
    ofPtr<TXModParamFloat> layerC_inputYMin;
    ofPtr<TXModParamFloat> layerC_inputYMax;
    ofParameter<bool>      layerC_offsetProcs12InSeries;
    
    ofParameter<bool>      layerC_offsetProcess1Active;
    ofParameter<int>       layerC_offsetProcess1Type;   // unaryOpFuncs
    ofPtr<TXModParamFloat> layerC_offsetProcess1MultInputX;
    ofPtr<TXModParamFloat> layerC_offsetProcess1AddInputX;
    ofPtr<TXModParamFloat> layerC_offsetProcess1MultOutputX;
    ofPtr<TXModParamFloat> layerC_offsetProcess1MultInputY;
    ofPtr<TXModParamFloat> layerC_offsetProcess1AddInputY;
    ofPtr<TXModParamFloat> layerC_offsetProcess1MultOutputY;
    
    ofParameter<bool>      layerC_offsetProcess2Active;
    ofParameter<int>       layerC_offsetProcess2Type;   // unaryOpFuncs
    ofPtr<TXModParamFloat> layerC_offsetProcess2MultInputX;
    ofPtr<TXModParamFloat> layerC_offsetProcess2AddInputX;
    ofPtr<TXModParamFloat> layerC_offsetProcess2MultOutputX;
    ofPtr<TXModParamFloat> layerC_offsetProcess2MultInputY;
    ofPtr<TXModParamFloat> layerC_offsetProcess2AddInputY;
    ofPtr<TXModParamFloat> layerC_offsetProcess2MultOutputY;
    
    ofParameter<int>       layerC_generatorProcessType;  // unaryOpFuncs
    ofParameter<int>       layerC_genInputXYProcess;     // binaryOpFuncs
    ofPtr<TXModParamFloat> layerC_genInputXMult;
    ofPtr<TXModParamInt>   layerC_genInputXPower;
    ofPtr<TXModParamFloat> layerC_genInputYMult;
    ofPtr<TXModParamInt>   layerC_genInputYPower;
    ofPtr<TXModParamFloat> layerC_genInputMult;
    ofPtr<TXModParamFloat> layerC_genInputOffset;
    
    ofParameter<bool>      layerC_postProcess1Active;
    ofParameter<int>       layerC_postProcess1Type;       // unaryOpFuncs & binaryOpFuncs
    ofPtr<TXModParamFloat> layerC_postProcess1YVal;
    ofParameter<bool>      layerC_postProcess2Active;
    ofParameter<int>       layerC_postProcess2Type;
    ofPtr<TXModParamFloat> layerC_postProcess2YVal;
    ofParameter<bool>      layerC_postProcess3Active;
    ofParameter<int>       layerC_postProcess3Type;
    ofPtr<TXModParamFloat> layerC_postProcess3YVal;
    
    ofParameter<bool>      layerD_usePolarCoords;
    ofPtr<TXModParamFloat> layerD_rotate;
    ofPtr<TXModParamFloat> layerD_inputXMin;
    ofPtr<TXModParamFloat> layerD_inputXMax;
    ofPtr<TXModParamFloat> layerD_inputYMin;
    ofPtr<TXModParamFloat> layerD_inputYMax;
    ofParameter<bool>      layerD_offsetProcs12InSeries;
    
    ofParameter<bool>      layerD_offsetProcess1Active;
    ofParameter<int>       layerD_offsetProcess1Type;   // unaryOpFuncs
    ofPtr<TXModParamFloat> layerD_offsetProcess1MultInputX;
    ofPtr<TXModParamFloat> layerD_offsetProcess1AddInputX;
    ofPtr<TXModParamFloat> layerD_offsetProcess1MultOutputX;
    ofPtr<TXModParamFloat> layerD_offsetProcess1MultInputY;
    ofPtr<TXModParamFloat> layerD_offsetProcess1AddInputY;
    ofPtr<TXModParamFloat> layerD_offsetProcess1MultOutputY;
    
    ofParameter<bool>      layerD_offsetProcess2Active;
    ofParameter<int>       layerD_offsetProcess2Type;   // unaryOpFuncs
    ofPtr<TXModParamFloat> layerD_offsetProcess2MultInputX;
    ofPtr<TXModParamFloat> layerD_offsetProcess2AddInputX;
    ofPtr<TXModParamFloat> layerD_offsetProcess2MultOutputX;
    ofPtr<TXModParamFloat> layerD_offsetProcess2MultInputY;
    ofPtr<TXModParamFloat> layerD_offsetProcess2AddInputY;
    ofPtr<TXModParamFloat> layerD_offsetProcess2MultOutputY;
    
    ofParameter<int>       layerD_generatorProcessType;  // unaryOpFuncs
    ofParameter<int>       layerD_genInputXYProcess;     // binaryOpFuncs
    ofPtr<TXModParamFloat> layerD_genInputXMult;
    ofPtr<TXModParamInt>   layerD_genInputXPower;
    ofPtr<TXModParamFloat> layerD_genInputYMult;
    ofPtr<TXModParamInt>   layerD_genInputYPower;
    ofPtr<TXModParamFloat> layerD_genInputMult;
    ofPtr<TXModParamFloat> layerD_genInputOffset;
    
    ofParameter<bool>      layerD_postProcess1Active;
    ofParameter<int>       layerD_postProcess1Type;       // unaryOpFuncs & binaryOpFuncs
    ofPtr<TXModParamFloat> layerD_postProcess1YVal;
    ofParameter<bool>      layerD_postProcess2Active;
    ofParameter<int>       layerD_postProcess2Type;
    ofPtr<TXModParamFloat> layerD_postProcess2YVal;
    ofParameter<bool>      layerD_postProcess3Active;
    ofParameter<int>       layerD_postProcess3Type;
    ofPtr<TXModParamFloat> layerD_postProcess3YVal;
    
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
    ofPtr<TXModParamBool>  clearColorHSBAsRGB;
    
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
    ofImage colorMixImage;
    ofImage curvesImage;
    ofImage curvesHSLImage;
    ofMesh drawMesh;
	ofShader drawShader;
	ofShader renderShader;
    bool oldRenderNow;
    bool oldClearNow;
    bool shaderCodeHasChanged;
    bool colorMixImageHasChanged;
    bool curvesImageHasChanged;
    bool curvesHSLImageHasChanged;
    bool layerAUsed;
    bool layerBUsed;
    bool layerCUsed;
    bool layerDUsed;
    
 };


/*  Coloring methods
 [
 "Use color1/2/3 with lookupCurve4 to blend",
 "Use color1/2/3 with linear blend",
 "Use color1/2 with lookupCurve4 to blend",
 "Use color1/2 with linear blend",
 "Use color2/3 with lookupCurve4 to blend",
 "Use color2/3 with linear blend",
 "Use Black/Grey/White with lookupCurve4 to blend",
 "Use Black/Grey/White with linear blend",
 "Use White/Black/White with lookupCurve4 to blend",
 "Use White/Black/White with linear blend",
 "Use Black/White/Black with lookupCurve4 to blend",
 "Use Black/White/Black with linear blend",
 "Use Blue/Black/Red with lookupCurve4 to blend",
 "Use Blue/Black/Red with linear blend",
 "Use Color Curves as HSBA",
 "Use Color Curves as RGBA",
 ]

 
 //===================
 // WaveTerrain Uniforms - other variables commented out
 
 // Global:
 // ofParameter<int>       terrainStructure;  // using 1/2/3/4 layers
 
 // ofParameter<int>       layerABJoinProcess;  // binaryOpFuncs
 // ofParameter<int>       layerBCJoinProcess;
 // ofParameter<int>       layerCDJoinProcess;
 
 ofParameter<int>       outputRangeProcess;    //  options: fold/ wrap/ clip
 uniform float outputRangeMin;  // default -1
 uniform float outputRangeMax;  // default 1
 uniform int outputRangeProcess;
 
 // Curves
 // TXParameterFloat256    lookupCurve1A;   // curve index 0
 // TXParameterFloat256    lookupCurve1B;
 uniform float lookupCurve1Morph;
 uniform float lookupCurve1Phase;
 // TXParameterFloat256    lookupCurve2A;   // curve index 1
 // TXParameterFloat256    lookupCurve2B;
 uniform float lookupCurve2Morph;
 uniform float lookupCurve2Phase;
 // TXParameterFloat256    lookupCurve3A;   // curve index 2
 // TXParameterFloat256    lookupCurve3B;
 uniform float lookupCurve3Morph;
 uniform float lookupCurve3Phase;
 // TXParameterFloat256    lookupCurve4A;   // curve index 3
 // TXParameterFloat256    lookupCurve4B;
 uniform float lookupCurve4Morph;
 uniform float lookupCurve4Phase;
 
 // ofParameter<bool>      colorCurvesHSBAsRGB;   // default false
 // TXParameterFloat256    colorHueCurveA;   // HSL curve index 0
 // TXParameterFloat256    colorHueCurveB;
 uniform float colorHueCurveMorph;
 // TXParameterFloat256    colorSaturationCurveA;   // HSL curve index 1
 // TXParameterFloat256    colorSaturationCurveB;
 uniform float colorSaturationCurveMorph;
 // TXParameterFloat256    colorBrightnessCurveA;   // HSL curve index 2
 // TXParameterFloat256    colorBrightnessCurveB;
 uniform float colorBrightnessCurveMorph;
 // TXParameterFloat256    colorAlphaCurveA;   // HSL curve index 3
 // TXParameterFloat256    colorAlphaCurveB;
uniform float colorAlphaCurveMorph;
 
 // Layers:
 // ofParameter<bool>      layerA_inputXInvert;
 // ofParameter<bool>      layerA_inputYInvert;
uniform float layerA_inputXMin;
uniform float layerA_inputXMax;
uniform float layerA_inputYMin;
uniform float layerA_inputYMax;
 // ofParameter<bool>      layerA_offsetProcs12InSeries;
 
 // ofParameter<bool>      layerA_offsetProcess1Active;
 // ofParameter<int>       layerA_offsetProcess1Type;   // unaryOpFuncs
 uniform float layerA_offsetProcess1MultInputX;
 uniform float layerA_offsetProcess1AddInputX;
 uniform float layerA_offsetProcess1MultOutputX;
 uniform float layerA_offsetProcess1MultInputY;
 uniform float layerA_offsetProcess1AddInputY;
 uniform float layerA_offsetProcess1MultOutputY;
 
 // ofParameter<bool>     layerA_offsetProcess2Active;
 // ofParameter<int>       layerA_offsetProcess2Type;   // unaryOpFuncs
 uniform float layerA_offsetProcess2MultInputX;
 uniform float layerA_offsetProcess2AddInputX;
 uniform float layerA_offsetProcess2MultOutputX;
 uniform float layerA_offsetProcess2MultInputY;
 uniform float layerA_offsetProcess2AddInputY;
 uniform float layerA_offsetProcess2MultOutputY;
 
 // ofParameter<int>       layerA_generatorProcessType;  // unaryOpFuncs
 // ofParameter<int>       layerA_genInputXYProcess;     // binaryOpFuncs
 uniform float layerA_genInputXMult;
 uniform int   layerA_genInputXPower;
 uniform float layerA_genInputYMult;
 uniform int   layerA_genInputYPower;
 uniform float layerA_genInputMult;
 uniform float layerA_genInputOffset;
 
 // ofParameter<bool>      layerA_postProcess1Active;
 // ofParameter<int>       layerA_postProcess1Type;       // unaryOpFuncs & binaryOpFuncs
 uniform float layerA_postProcess1YVal;
 // ofParameter<bool>      layerA_postProcess2Active;
 // ofParameter<int>       layerA_postProcess2Type;
 uniform float layerA_postProcess2YVal;
 // ofParameter<bool>      layerA_postProcess3Active;
 // ofParameter<int>       layerA_postProcess3Type;
 uniform float layerA_postProcess3YVal;
 
 
 
 //===================
 // for Generator function
 genInput = (genInputXYProcess(genInputXMult * pow(inputX, genInputXPower), genInputYMult * pow(inputY, genInputYPower))
	* genInputMult) + genInputOffset;

 //===================


 //===================
 outputRangeProcessNames = [
 "fold(x, minVal, maxVal);"
 "wrap(x, minVal, maxVal);"
 "clip(x, minVal, maxVal);"
 ];
 //===================
 structureProcessNames = [
 "1L (A)"
 "1L (B)"
 "1L (C)"
 "1L (D)"
 "2L (A:B)"
 "3L ((A:B) : C)"
 "3L (A : (B:C))"
 "4L (((A:B) : C) : D)"
 "4L ((A:B) : (C:D))"
 "4L ((A : (B:C)) : D)"
 "4L (A : (B : (C:D)))"
 ];
 //===================
 // outputRangeProcesses - size: 3
 string outputRangeProcesses[] = {
 "fold(x, minVal, maxVal);"
 "wrap(x, minVal, maxVal);"
 "clip(x, minVal, maxVal);"
 }
 //===================
 // structureProcesses - size: 11
 string structureProcesses[] = {
 "buildLayer(x,y, 0);"
 "buildLayer(x,y, 1);"
 "buildLayer(x,y, 2);"
 "buildLayer(x,y, 3);"
 "  // 4 STRINGIFY(
 layA = buildLayer(x,y, 0);
 layB = buildLayer(x,y, 1);
 chain = runBinaryOp(layerABJoinProcess, layA, layB);
	"
 "  // 5 STRINGIFY(
 layA = buildLayer(x,y, 0);
 layB = buildLayer(x,y, 1);
 layC = buildLayer(x,y, 2);
 chain = runBinaryOp(layerABJoinProcess, layA, layB);
 chain = runBinaryOp(layerBCJoinProcess, chain, layC);
	"
 "  // 6 STRINGIFY(
 layA = buildLayer(x,y, 0);
 layB = buildLayer(x,y, 1);
 layC = buildLayer(x,y, 2);
 chain = runBinaryOp(layerBCJoinProcess, layB, layC);
 chain = runBinaryOp(layerABJoinProcess, layA, chain);
	"
 "  // 7 STRINGIFY(
 layA = buildLayer(x,y, 0);
 layB = buildLayer(x,y, 1);
 layC = buildLayer(x,y, 2);
 layD = buildLayer(x,y, 3);
 chain = runBinaryOp(layerABJoinProcess, layA, layB);
 chain = runBinaryOp(layerBCJoinProcess, chain, layC);
 chain = runBinaryOp(layerCDJoinProcess, chain, layD);
	"
 "  // 8 STRINGIFY(
 layA = buildLayer(x,y, 0);
 layB = buildLayer(x,y, 1);
 layC = buildLayer(x,y, 2);
 layD = buildLayer(x,y, 3);
 chainAB = runBinaryOp(layerABJoinProcess, layA, layB);
 chainCD = runBinaryOp(layerCDJoinProcess, layC, layD);
 chain = runBinaryOp(layerBCJoinProcess, chainAB, chainCD);
	"
 "  // 9 STRINGIFY(
 layA = buildLayer(x,y, 0);
 layB = buildLayer(x,y, 1);
 layC = buildLayer(x,y, 2);
 layD = buildLayer(x,y, 3);
 chain = runBinaryOp(layerBCJoinProcess, layB, layC);
 chain = runBinaryOp(layerABJoinProcess, layA, chain);
 chain = runBinaryOp(layerCDJoinProcess, chain, layD);
	"
 "  // 10 STRINGIFY(
 layA = buildLayer(x,y, 0);
 layB = buildLayer(x,y, 1);
 layC = buildLayer(x,y, 2);
 layD = buildLayer(x,y, 3);
 chain = runBinaryOp(layerCDJoinProcess, layC, layD);
 chain = runBinaryOp(layerBCJoinProcess, layB, chain);
 chain = runBinaryOp(layerABJoinProcess, layA, chain);
	"
 }
 //===================

 //===================
 unaryOpProcessNames = [
 "x"
 "-x"
 "abs(x)"
 "sign(x) [1 or 0 or -1]"
 "(1 / x)"
 "sin(2*pi * x)"
 "cos(2*pi * x)"
 "tan(2*pi * x)"
 "asin(x) * 2/pi"
 "acos(x) * 2/pi"
 "atan(x) * 2/pi"
 "noise1(x) [smooth noise between -1 and 1]"
 "abs(noise1(x)) [smooth noise between -1 and 1]"
 "fract(x)"
 "ceil(x)"
 "floor(x)"
 "squared(x)"
 "cubed(x)"
 "sqrt(abs(x))"
 "1 / sqrt(abs(x))"
 "exp(abs(x))"
 "exp2(x) - 2 to the power x"
 "log(x)"
 "log2(x)"
 "step(0.5, x) [0 if x < 0.5, otherwise 1]"
 "step(0, x) [0 if x < 0, otherwise 1]"
 "clamp(x, 0, 1) [clamp x from 0 to 1]"
 "clamp(x, -1, 1) [clamp x to +/-1]"
 "fold(x, 0, 1) [fold x from 0 to 1]"
 "fold(x, -1, 1) [bilateral fold x to +/-1]"
 "wrap(x, 0, 1) [wrap x from 0 to 1]"
 "wrap(x, -1, 1) [bilateral wrap x to +/-1]"
 "lookup curve 1 unipolar clamp(x, 0, 1)"
 "lookup curve 1 bipolar clamp(x, -1, 1)"
 "lookup curve 1 unipolar fold(x, 0, 1)"
 "lookup curve 1 bipolar fold(x, -1, 1)"
 "lookup curve 1 unipolar wrap(x, 0, 1)"
 "lookup curve 1 bipolar wrap(x, -1, 1)"
 "lookup curve 2 unipolar clamp(x, 0, 1)"
 "lookup curve 2 bipolar clamp(x, -1, 1)"
 "lookup curve 2 unipolar fold(x, 0, 1)"
 "lookup curve 2 bipolar fold(x, -1, 1)"
 "lookup curve 2 unipolar wrap(x, 0, 1)"
 "lookup curve 2 bipolar wrap(x, -1, 1)"
 "lookup curve 3 unipolar clamp(x, 0, 1)"
 "lookup curve 3 bipolar clamp(x, -1, 1)"
 "lookup curve 3 unipolar fold(x, 0, 1)"
 "lookup curve 3 bipolar fold(x, -1, 1)"
 "lookup curve 3 unipolar wrap(x, 0, 1)"
 "lookup curve 3 bipolar wrap(x, -1, 1)"
 "lookup curve 4 unipolar clamp(x, 0, 1)"
 "lookup curve 4 bipolar clamp(x, -1, 1)"
 "lookup curve 4 unipolar fold(x, 0, 1)"
 "lookup curve 4 bipolar fold(x, -1, 1)"
 "lookup curve 4 unipolar wrap(x, 0, 1)"
 "lookup curve 4 bipolar wrap(x, -1, 1)"
 ];
 //===================
 binaryOpProcessNames = [
 "x + y"
 "x - y"
 "y - x"
 "x * y"
 "x / y"
 "y / x"
 "x % y"
 "y % x"
 "min(x, y)"
 "max(x, y)"
 "pow(abs(x), y)"
 "pow(abs(y), x)"
 "int(x == y) [0 or 1]"
 "int(x != y) [0 or 1]"
 "int(x > y) [0 or 1]"
 "int(x < y) [0 or 1]"
 "int(x >= y) [0 or 1]"
 "int(x <= y) [0 or 1]"
 "step(x, y) [0 if y<x, otherwise 1]"
 "step(y, x) [0 if x<y, otherwise 1]"
 "smoothstep(-x, x, y) [0 if y <= -x, smoothed for y between -x and x, otherwise 1]"
 "smoothstep(-y, y, x) [0 if x <= y-, smoothed for x between -y and y, otherwise 1]"
 "distance(x, y) [distance between x and y]"
 "pnoise2(x,y) [smooth noise]"
 "pnoise2(y, x) [smooth noise]"
 "atan(x/y)"
 "atan(y/x)"
 "clamp(x, 0, y) [clamp x from 0 to y]"
 "clamp(y, 0, x) [clamp y from 0 to x]"
 "clamp2(x, -y, y) [bilateral clamp x to +/-y]"
 "clamp2(y, -x, x) [bilateral clamp y to +/-x]"
 "fold(x, y) [fold x from 0 to y]"
 "fold(y, x) [fold y from 0 to x]"
 "fold2(x, y) [bilateral fold x to +/-y]"
 "fold2(y, x) [bilateral fold y to +/-x]"
 "wrap(x, y) [wrap x from 0 to y]"
 "wrap(y, x) [wrap y from 0 to x]"
 "wrap2(x, y) [bilateral wrap x to +/-y]"
 "wrap2(y, x) [bilateral wrap y to +/-x]"
 "round(x, y) [round x to multiple of y]"
 "round(y, x) [round y to multiple of x]"
 "roundUp(x, y) [round up x to multiple of y]"
 "roundUp(y, x) [round up y to multiple of x]"
 "trunc(x, y) [truncate x to multiple of y]"
 "trunc(y, x) [truncate y to multiple of x]"
 "thresh(x, y)"
 "thresh(y, x)"
 "x [y ignored]"
 "y [x ignored]"
 ];


*/

