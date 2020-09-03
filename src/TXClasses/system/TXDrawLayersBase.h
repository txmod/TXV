/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"

#include "TXDrawBase.h"

//#include "TXMain.h"

enum TXDRAWLAYERSRULE {TXDRAWLAYERSRULE_ALLEXCEPT20,
    TXDRAWLAYERSRULE_LAYER1,
    TXDRAWLAYERSRULE_LAYER2,
    TXDRAWLAYERSRULE_LAYER3,
    TXDRAWLAYERSRULE_LAYER4,
    TXDRAWLAYERSRULE_LAYER5,
    TXDRAWLAYERSRULE_LAYER6,
    TXDRAWLAYERSRULE_LAYER7,
    TXDRAWLAYERSRULE_LAYER8,
    TXDRAWLAYERSRULE_LAYER9,
    TXDRAWLAYERSRULE_LAYER10,
    TXDRAWLAYERSRULE_LAYER11,
    TXDRAWLAYERSRULE_LAYER12,
    TXDRAWLAYERSRULE_LAYER13,
    TXDRAWLAYERSRULE_LAYER14,
    TXDRAWLAYERSRULE_LAYER15,
    TXDRAWLAYERSRULE_LAYER16,
    TXDRAWLAYERSRULE_LAYER17,
    TXDRAWLAYERSRULE_LAYER18,
    TXDRAWLAYERSRULE_LAYER19,
    TXDRAWLAYERSRULE_LAYER20,
    TXDRAWLAYERSRULE_LAYERS_1_TO_5,
    TXDRAWLAYERSRULE_LAYERS_6_TO_10,
    TXDRAWLAYERSRULE_LAYERS_11_TO_15,
    TXDRAWLAYERSRULE_LAYERS_16_TO_20,
    TXDRAWLAYERSRULE_LAYERS_1_TO_10,
    TXDRAWLAYERSRULE_LAYERS_11_TO_20,
    TXDRAWLAYERSRULE_TOTAL,
};

class TXDrawLayersBase :  public TXDrawBase
{
public:
    
	// constructor
	TXDrawLayersBase ();

	virtual void draw(TXDRAWLAYERSRULE layersRuleArg = TXDRAWLAYERSRULE_ALLEXCEPT20);
    virtual void addDrawModule(int moduleIDArg, int layerNoArg);
    virtual void removeDrawModule(int moduleIDArg, int layerNoArg);

    // for testing
    void printAllLayers();
};

