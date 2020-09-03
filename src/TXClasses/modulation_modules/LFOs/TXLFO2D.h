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

enum TXLFO2DTYPE {
    TXLFO2DTYPE_NOPATTERN,
    TXLFO2DTYPE_CIRCLES,
    TXLFO2DTYPE_SPIRALS,
    TXLFO2DTYPE_SPIRALSINE,
    TXLFO2DTYPE_SPIRALTRI,
    TXLFO2DTYPE_LINES,
    TXLFO2DTYPE_DIAGONALLINES,
    TXLFO2DTYPE_GRID,
    TXLFO2DTYPE_SINEWAVE,
    TXLFO2DTYPE_ZIGZAG,
    TXLFO2DTYPE_RANDOM,
    TXLFO2DTYPE_RANDOMQUANTISED,
    TXLFO2DTYPE_RANDOMSMOOTHED,
    TXLFO2DTYPE_DOUBLERANDOM,
    TXLFO2DTYPE_DOUBLERANDOMQUANTISED,
    TXLFO2DTYPE_DOUBLERANDOMSMOOTHED,
    TXLFO2DTYPE_CUSTOMCURVE,
    TXLFO2DTYPE_CUSTOMCURVE_MIRRORED,
};

struct TXLFO2DValues
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
    bool swapXAndY;
    float scaleX;
    float scaleY;
    TXParameterFloat256 customCurveX;
    TXParameterFloat256 customCurveX2;
    float customCurveXMorph;
    TXParameterFloat256 customCurveY;
    TXParameterFloat256 customCurveY2;
    float customCurveYMorph;
};

class TXLFO2D : public TXModuleBase
{
	//  Output range is 0 to +1
    
public:

    // NOTE - change totalLFOTypes when adding new types:
    const static int totalLFOTypes = 18;
    const static int maxNoLevels = 20;

	// constructor
	TXLFO2D (string paramNamePrefix = "", int lfoTypeArg = TXLFO2DTYPE_CIRCLES, int randomSmoothTypeArg = TXLFOSMOOTHTYPE_SINE_INOUT, int noLevelsArg = 1, float bpmArg = 120.0, float cycleTimeBeatsArg = 16.0, float cycleTimeDivisorArg = 1.0, float phaseOffsetArg = 0.0, bool reverseXArg = false, bool reverseYArg = false, bool swapXAndYArg = false, bool circularDirectionOutArg = true, bool useMasterBpmArg = true, float scaleXArg = 1.0, float scaleYArg = 1.0, bool frozenArg = false, float customCurveXMorphArg = 0.0, float customCurveYMorphArg = 0.0);
	
    // destructor
    ~TXLFO2D ();
    
	// methods
	void setup (string paramNamePrefix = "", int lfoTypeArg = TXLFO2DTYPE_CIRCLES, int randomSmoothTypeArg = TXLFOSMOOTHTYPE_LINEAR_INOUT, int noLevelsArg = 1, float bpmArg = 120.0, float cycleTimeBeatsArg = 16.0, float cycleTimeDivisorArg = 1.0, float phaseOffsetArg = 0.0, bool reverseXArg = false, bool reverseYArg = false, bool swapXAndYArg = false, bool circularDirectionOutArg = true, bool useMasterBpmArg = true, float scaleXArg = 1.0, float scaleYArg = 1.0, bool frozenArg = false, float customCurveXMorphArg = 0.0, float customCurveYMorphArg = 0.0);
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
    void setBpmFixed(float bpmArg);
    void setNoLevelsFixed(int noLevelsArg);
    void setCycleTimeBeatsFixed(float cycleTimeBeatsArg);
    void setCycleTimeDivisorFixed(float cycleTimeDivisorArg);
    // void setTime(float timeArg = 0);
    void resetTime();
    void update();
    void setMasterBpm(float masterBpmArg);
	void advanceBy(float timeDeltaArg);

    void getAllOutputValues(TXLFO2DValues & dataArg);
    void setAllFixedValues(TXLFO2DValues & dataArg);


public:
    // parameters
    
    ofPtr<TXModParamInt> lfoType;
    ofPtr<TXModParamInt> randomSmoothType;
    ofPtr<TXModParamInt> noLevels;
    ofPtr<TXModParamFloat> bpm;
    ofPtr<TXModParamBool> useMasterBpm;
    ofPtr<TXModParamFloat> cycleTimeBeats;
    ofPtr<TXModParamFloat> cycleTimeDivisor;
    ofPtr<TXModParamFloat> phaseOffset;
    ofPtr<TXModParamBool> circularDirectionOut;
    ofPtr<TXModParamBool> frozen;
    ofPtr<TXModParamBool> resetClock;
    ofPtr<TXModParamBool> reverseX;
    ofPtr<TXModParamBool> reverseY;
    ofPtr<TXModParamBool> swapXAndY;
    ofPtr<TXModParamFloat> scaleX;
    ofPtr<TXModParamFloat> scaleY;
    
    TXParameterFloat256 customCurveX;
    TXParameterFloat256   customCurveX2;
    ofPtr<TXModParamFloat> customCurveXMorph;
    TXParameterFloat256 customCurveY;
    TXParameterFloat256   customCurveY2;
    ofPtr<TXModParamFloat> customCurveYMorph;

    ofPtr<TXModSource> positionX;
    ofPtr<TXModSource> positionY;
	
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

    void recalcPosXY();

    float currentTime;
    bool  quantiseLfoAmp;
    bool  quantiseLfoX;
    bool  quantiseLfoY;
    bool  requestResetClock;

	// lfos
    TXSimpleLFO lfoAmp;
    TXSimpleLFO lfoX;
    TXSimpleLFO lfoY;
    bool useLfoAmp;
    bool customCurveXHasChanged;
    bool customCurveX2HasChanged;
    bool customCurveYHasChanged;
    bool customCurveY2HasChanged;
};

