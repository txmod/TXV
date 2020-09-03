/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 *
 *  NOTE: TXSimpleLFO2 is not a TX Module. It's just to be used inside other modules,
 *        such as TXParticles.
 *
 *        It doesn't have modulatable parameters
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"
#include "TXSimpleLFO.h"
#include "TXLFO2D.h"


class TXSimpleLFO2D
{
	//  Output range is 0 to +1
    
public:

    // NOTE - change totalLFOTypes when adding new types:
    enum {totalLFOTypes = 18, maxNoLevels = 20};

	// constructor
	TXSimpleLFO2D (string paramNamePrefix = "", int lfoTypeArg = TXLFO2DTYPE_CIRCLES, int randomSmoothTypeArg = TXLFOSMOOTHTYPE_SINE_INOUT, int noLevelsArg = 1, float bpmArg = 120.0, float cycleTimeBeatsArg = 16.0, float cycleTimeDivisorArg = 1.0, float phaseOffsetArg = 0.0, bool reverseXArg = false, bool reverseYArg = false, bool swapXAndYArg = false, bool circularDirectionOutArg = true, bool useMasterBpmArg = true, float scaleXArg = 1.0, float scaleYArg = 1.0, bool frozenArg = false, float customCurveXMorphArg = 0.0, float customCurveYMorphArg = 0.0);
	
    // destructor
    ~TXSimpleLFO2D ();
    
	// methods
	void setup (string paramNamePrefix = "", int lfoTypeArg = TXLFO2DTYPE_CIRCLES, int randomSmoothTypeArg = TXLFOSMOOTHTYPE_LINEAR_INOUT, int noLevelsArg = 1, float bpmArg = 120.0, float cycleTimeBeatsArg = 16.0, float cycleTimeDivisorArg = 1.0, float phaseOffsetArg = 0.0, bool reverseXArg = false, bool reverseYArg = false, bool swapXAndYArg = false, bool circularDirectionOutArg = true, bool useMasterBpmArg = true, float scaleXArg = 1.0, float scaleYArg = 1.0, bool frozenArg = false, float customCurveXMorphArg = 0.0, float customCurveYMorphArg = 0.0);
    void lfoTypeChangedInt(int & dummyParameterArg );
    void bpmChangedInt(int & dummyParameterArg );
    void bpmChangedBool(bool & dummyParameterArg );
    void bpmChangedFloat(float & dummyParameterArg );
    void cycleTimeBeatsChangedFloat(float & dummyParameterArg );
    void cycleTimeDivisorChangedFloat(float & dummyParameterArg );
    void customCurveXChanged(ofAbstractParameter & dummyParameterArg );
    void customCurveX2Changed(ofAbstractParameter & dummyParameterArg );
    void customCurveYChanged(ofAbstractParameter & dummyParameterArg );
    void customCurveY2Changed(ofAbstractParameter & dummyParameterArg );
    void resetTime();
    void update();
    void setMasterBpm(float masterBpmArg);
    void advanceBy(float timeDeltaArg, float masterBpmArg);
    void setTime(float timeArg, float masterBpmArg);

    void getAllValues(TXLFO2DValues & dataArg);
    void setAllValues(TXLFO2DValues & dataArg);


public:
	// properties
    ofParameter<int> lfoType;
    ofParameter<int> randomSmoothType;
    ofParameter<float> bpm;
    ofParameter<float> cycleTimeBeats;
    ofParameter<float> cycleTimeDivisor;
    ofParameter<float> phaseOffset;
    ofParameter<bool> useMasterBpm;
    ofParameter<bool> frozen;
    ofParameter<int> noLevels;
    ofParameter<bool> circularDirectionOut;
    ofParameter<bool> reverseX;
    ofParameter<bool> reverseY;
    ofParameter<bool> swapXAndY;
    ofParameter<float> scaleX;
    ofParameter<float> scaleY;
    
    TXParameterFloat256 customCurveX;
    TXParameterFloat256   customCurveX2;
    ofParameter<float> customCurveXMorph;
    TXParameterFloat256 customCurveY;
    TXParameterFloat256   customCurveY2;
    ofParameter<float> customCurveYMorph;

    float positionX;
    float positionY;
    float masterBpm;
    	
protected:
    void updateLfoType();
    void updateBpm();
    void updateCycleTimeBeats();
    void updateCycleTimeDivisor();
    void updateCurveX();
    void updateCurveX2();
    void updateCurveY();
    void updateCurveY2();

    void recalcPosXY();

    float currentTime;
    bool  quantiseLfoAmp;
    bool  quantiseLfoX;
    bool  quantiseLfoY;

	// lfos
    TXSimpleLFO lfoAmp;
    TXSimpleLFO lfoX;
    TXSimpleLFO lfoY;
    bool useLfoAmp;
    bool customCurveXHasChanged;
    bool customCurveX2HasChanged;
    bool customCurveYHasChanged;
    bool customCurveY2HasChanged;
    bool  requestResetClock;
};

