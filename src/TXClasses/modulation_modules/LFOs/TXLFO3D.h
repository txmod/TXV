/*
 *  Created by paul on 09/09/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"
#include "TXModuleBase.h"
#include "TXSimpleLFO.h"

enum TXLFO3DTYPE {TXLFO3DTYPE_NOPATTERN,
    TXLFO3DTYPE_CIRCLES,
    TXLFO3DTYPE_SPIRALS,
    TXLFO3DTYPE_SPIRALSINE,
    TXLFO3DTYPE_SPIRALTRI,
    TXLFO3DTYPE_LINES,
    TXLFO3DTYPE_DIAGONALLINES,
    TXLFO3DTYPE_GRID,
    TXLFO3DTYPE_SINEWAVE,
    TXLFO3DTYPE_ZIGZAG,
    TXLFO3DTYPE_RANDOM,
    TXLFO3DTYPE_RANDOMQUANTISED,
    TXLFO3DTYPE_RANDOMSMOOTHED,
    TXLFO3DTYPE_DOUBLERANDOM,
    TXLFO3DTYPE_DOUBLERANDOMQUANTISED,
    TXLFO3DTYPE_DOUBLERANDOMSMOOTHED,
    TXLFO3DTYPE_TREFOILKNOT,
    TXLFO3DTYPE_CUSTOMCURVE,
    TXLFO3DTYPE_CUSTOMCURVE_MIRRORED,
};

class TXLFO3DValues
{
public:
    int lfoType;
    int randomSmoothType;
    int noLevels;
    float bpm;
    bool useMasterBpm;
    bool frozen ;
    float cycleTimeBeats;
    float cycleTimeDivisor;
    float phaseOffset;
    bool circularDirectionOut;
    bool reverseX;
    bool reverseY;
    bool reverseZ;
    bool swapXAndY;
    float scaleX;
    float scaleY;
    float scaleZ;
    TXParameterFloat256 customCurveX;
    TXParameterFloat256   customCurveX2;
    float customCurveXMorph;
    TXParameterFloat256 customCurveY;
    TXParameterFloat256   customCurveY2;
    float customCurveYMorph;
    TXParameterFloat256 customCurveZ;
    TXParameterFloat256   customCurveZ2;
    float customCurveZMorph;
};

class TXLFO3D : public TXModuleBase
{
	//  Output range is 0 to +1
    
public:

    // NOTE - change totalLFOTypes when adding new types:
    const static int totalLFOTypes = 19;
    const static int maxNoLevels = 20;

	// constructor
	TXLFO3D (string paramNamePrefix = "", int lfoTypeArg = TXLFO3DTYPE_CIRCLES, int randomSmoothTypeArg = TXLFOSMOOTHTYPE_SINE_INOUT, int noLevelsArg = 1, float bpmArg = 120.0, float cycleTimeBeatsArg = 16.0, float cycleTimeDivisorArg = 1.0, float phaseOffsetArg = 0.0, bool reverseXArg = false, bool reverseYArg = false, bool reverseZArg = false, bool swapXAndYArg = false, bool circularDirectionOutArg = true, bool useMasterBpmArg = true, float scaleXArg = 1.0, float scaleYArg = 1.0, float scaleZArg = 1.0, bool frozenArg = false, float customCurveXMorphArg = 0.0, float customCurveYMorphArg = 0.0, float customCurveZMorphArg = 0.0);
	
    // destructor
    ~TXLFO3D ();
    
	// methods
	void setup (string paramNamePrefix = "", int lfoTypeArg = TXLFO3DTYPE_CIRCLES, int randomSmoothTypeArg = TXLFOSMOOTHTYPE_LINEAR_INOUT, int noLevelsArg = 1, float bpmArg = 120.0, float cycleTimeBeatsArg = 16.0, float cycleTimeDivisorArg = 1.0, float phaseOffsetArg = 0.0, bool reverseXArg = false, bool reverseYArg = false, bool reverseZArg = false, bool swapXAndYArg = false, bool circularDirectionOutArg = true, bool useMasterBpmArg = true, float scaleXArg = 1.0, float scaleYArg = 1.0, float scaleZArg = 1.0, bool frozenArg = false, float customCurveXMorphArg = 0.0, float customCurveYMorphArg = 0.0, float customCurveZMorphArg = 0.0);
    void lfoTypeChanged(ofAbstractParameter & dummyParameterArg );
    void bpmChanged(ofAbstractParameter & dummyParameterArg );
    void resetClockChanged(ofAbstractParameter & dummyParameterArg );
    void cycleTimeBeatsChanged(ofAbstractParameter & dummyParameterArg );
    void cycleTimeDivisorChanged(ofAbstractParameter & dummyParameterArg );
    void phaseOffsetChanged(ofAbstractParameter & dummyParameterArg );
    void customCurveXChanged(ofAbstractParameter & dummyParameterArg );
    void customCurveX2Changed(ofAbstractParameter & dummyParameterArg );
    void customCurveYChanged(ofAbstractParameter & dummyParameterArg );
    void customCurveY2Changed(ofAbstractParameter & dummyParameterArg );
    void customCurveZChanged(ofAbstractParameter & dummyParameterArg );
    void customCurveZ2Changed(ofAbstractParameter & dummyParameterArg );
  
    void setBpmFixed(float bpmArg);
    void setNoLevelsFixed(float noLevelsArg);
    void setCycleTimeBeatsFixed(float cycleTimeBeatsArg);
    void setCycleTimeDivisorFixed(float cycleTimeDivisorArg);
    // void setTime(float timeArg = 0);
    void resetTime();
    void update();
    void setMasterBpm(float masterBpmArg);
	void advanceBy(float timeDeltaArg);

    void getAllOutputValues(TXLFO3DValues & dataArg);
    void setAllFixedValues(TXLFO3DValues & dataArg);

	// properties

    ofPtr<TXModParamInt> lfoType;
    ofPtr<TXModParamInt> randomSmoothType;
    ofPtr<TXModParamBool> frozen;
    ofPtr<TXModParamBool> resetClock;
    ofPtr<TXModParamInt> noLevels;
    ofPtr<TXModParamFloat> bpm;
    ofPtr<TXModParamBool> useMasterBpm;
    ofPtr<TXModParamFloat> cycleTimeBeats;
    ofPtr<TXModParamFloat> cycleTimeDivisor;
    ofPtr<TXModParamFloat> phaseOffset;
    ofPtr<TXModParamBool> circularDirectionOut;
    ofPtr<TXModParamBool> reverseX;
    ofPtr<TXModParamBool> reverseY;
    ofPtr<TXModParamBool> reverseZ;
    ofPtr<TXModParamBool> swapXAndY;
    ofPtr<TXModParamFloat> scaleX;
    ofPtr<TXModParamFloat> scaleY;
    ofPtr<TXModParamFloat> scaleZ;
    
    TXParameterFloat256 customCurveX;
    TXParameterFloat256   customCurveX2;
    ofPtr<TXModParamFloat> customCurveXMorph;
    TXParameterFloat256 customCurveY;
    TXParameterFloat256   customCurveY2;
    ofPtr<TXModParamFloat> customCurveYMorph;
    TXParameterFloat256 customCurveZ;
    TXParameterFloat256 customCurveZ2;
    ofPtr<TXModParamFloat> customCurveZMorph;

    ofPtr<TXModSource> positionX;
    ofPtr<TXModSource> positionY;
    ofPtr<TXModSource> positionZ;

	// lfos
    TXSimpleLFO lfoAmp;
    TXSimpleLFO lfoX;
    TXSimpleLFO lfoY;
    TXSimpleLFO lfoZ;
	
protected:
    void updateLfoType();
    void updateBpm();
    void updateCycleTimeBeats();
    void updateCycleTimeDivisor();
    void updatePhaseOffset();
    void updateCurveX();
    void updateCurveX2();
    void updateCurveY();
    void updateCurveY2();
    void updateCurveZ();
    void updateCurveZ2();
    void recalcPosXYZ();

    float currentTime;
    bool  quantiseLfoAmp;
    bool  quantiseLfoX;
    bool  quantiseLfoY;
    bool  quantiseLfoZ;
    bool  requestResetClock;

    bool useLfoAmp;
    bool customCurveXHasChanged;
    bool customCurveX2HasChanged;
    bool customCurveYHasChanged;
    bool customCurveY2HasChanged;
    bool customCurveZHasChanged;
    bool customCurveZ2HasChanged;
};

