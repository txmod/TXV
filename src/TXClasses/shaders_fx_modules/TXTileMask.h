/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

#pragma once

#include "ofMain.h"
#include "TXShaderFXBase.h"


class TXTileMask  :  public TXShaderFXBase
{
public:
	// constructor
	TXTileMask();
    
    // destructor
    ~TXTileMask();
    
    // overide  methods
    bool setExtraUniforms(int sourceImageWidth, int sourceImageHeight);
	void addExtraParameters();
	void addExtraListeners();
	void loadRenderShader();
    void imageAssetSlotChanged(string slotNameArg);
    void extraUpdateAction();
    void renderTexture(bool clearFirstArg);

public:
    // Extra parameters:
    
    void loadMaskImage();
//    int getTextureWidth(); // overide base class
//    int getTextureHeight(); // overide base class
//    ofTexture *  getTexture(); // overide base class
//    ofPixelsRef getPixels(); // overide base class
    
    ofParameter<bool> useExternalMaskImage;
    ofPtr<TXModParamInt> maskType;
    ofParameter<bool> invertMask;
    ofPtr<TXModParamFloat> feathering;
    
    ofParameter<bool> useSamplePosForRenderPos;
    ofParameter<bool> useSampleSizeForRenderSize;
    ofParameter<bool> constrainToEdges;
    ofPtr<TXModParamFloat> alpha;
    ofPtr<TXModParamFloat> samplePosX;
    ofPtr<TXModParamFloat> samplePosY;
    ofPtr<TXModParamFloat> sampleWidth;
    ofPtr<TXModParamFloat> sampleHeight;
    ofPtr<TXModParamFloat> numTiles;
    ofPtr<TXModParamBool> mirrorTileX;
    ofPtr<TXModParamBool> mirrorTileY;
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
    
    ofImage maskImage;
    
private:
    bool maskImageHasChanged;
    ofMesh drawMesh;
    ofShader renderWithMaskShader;
    ofShader renderWithMaskTexShader;
    ofShader * holdShader;
    
};

