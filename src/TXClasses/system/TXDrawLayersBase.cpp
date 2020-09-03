/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXDrawLayersBase.h"
#include "TXSystem.h"

// constructor
TXDrawLayersBase::TXDrawLayersBase ()
{
    canDrawLayers = true;
}

// properties

void TXDrawLayersBase::draw(TXDRAWLAYERSRULE layersRuleArg) {
    
    // call draw on all modules in layers
    multimap<int, int>::iterator iterModID;
    for (iterModID=drawLayerModules.begin(); iterModID!=drawLayerModules.end(); ++iterModID)
    {
        bool validDraw = true;  // default true
        
        // Error Catch: don't draw if layer is pointing to self!
        if (iterModID->second == moduleID) {
            validDraw = false;
        } else {
            int holdLayer = iterModID->first;
            // check layersRule
            if (layersRuleArg == TXDRAWLAYERSRULE_ALLEXCEPT20 ) {
                if (holdLayer == 20) {
                    validDraw = false;
                };
            } else if (layersRuleArg == TXDRAWLAYERSRULE_LAYERS_1_TO_5 ) {
                if (holdLayer > 5) {
                    validDraw = false;
                };
            } else if (layersRuleArg == TXDRAWLAYERSRULE_LAYERS_6_TO_10 ) {
                if ((holdLayer < 6) || (holdLayer > 10)) {
                    validDraw = false;
                };
            } else if (layersRuleArg == TXDRAWLAYERSRULE_LAYERS_11_TO_15 ) {
                if ((holdLayer < 11) || (holdLayer > 15)) {
                    validDraw = false;
                };
            } else if (layersRuleArg == TXDRAWLAYERSRULE_LAYERS_16_TO_20 ) {
                if (holdLayer < 16) {
                    validDraw = false;
                };
            } else if (layersRuleArg == TXDRAWLAYERSRULE_LAYERS_1_TO_10 ) {
                if (holdLayer > 10) {
                    validDraw = false;
                };
            } else if (layersRuleArg == TXDRAWLAYERSRULE_LAYERS_11_TO_20 ) {
                if (holdLayer < 11) {
                    validDraw = false;
                };
            } else {
                // for TXDRAWLAYERSRULE_LAYER1 to TXDRAWLAYERSRULE_LAYER20
                if (holdLayer != layersRuleArg) {
                    validDraw = false;
                };
            };
        };
        // draw if valid
        if (validDraw) {
            map<int, ofPtr <TXModuleBase> >::iterator iterDrawMod = parentSystem->allModules.find(iterModID->second);
            if (iterDrawMod != parentSystem->allModules.end()) {
                //ofPushMatrix();
                iterDrawMod->second->draw();
                //ofPopMatrix();
            };
        };
    }
}

void TXDrawLayersBase::addDrawModule(int moduleIDArg, int layerNoArg) {
    drawLayerModules.insert(std::make_pair(layerNoArg, moduleIDArg));
}

void TXDrawLayersBase::removeDrawModule(int moduleIDArg, int layerNoArg) {
    bool found = false;
    for (multimap<int, int>::iterator iter = drawLayerModules.begin(); iter != drawLayerModules.end();)
    {
        if (!found && (iter->first == layerNoArg) && (iter->second == moduleIDArg)) {
            multimap<int, int>::iterator save_iter = iter;
            ++save_iter;
            drawLayerModules.erase(iter);
            iter = save_iter;
            found = true; // only erase 1 instance
        } else {
            ++iter;
        }
    }
}

// for testing

void TXDrawLayersBase::printAllLayers() {
    ofLogNotice() << "TXDrawLayersBase::printAllLayers() module:   " << getName() << "-------------- ";

    for (multimap<int, int>::iterator iter = drawLayerModules.begin(); iter != drawLayerModules.end();)
    {
        ofLogNotice() << "      - moduleIDArg, layerNoArg:  " << iter->second << ", " << iter->first;
        ++iter;
    }
    
}

