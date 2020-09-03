/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 */

/*
 ====== TEMPLATE FOR RENDERED FX USING 2 TEXTURES
 */


#pragma once

#include "ofMain.h"
#include "TXShaderFXBase.h"

class TXShaderFX2TexBase  :  public TXShaderFXBase
{
public:
	// constructor
	TXShaderFX2TexBase();
    
    // destructor
    ~TXShaderFX2TexBase();
    
    //------ overide virtual methods in FX modules as needed:
    virtual void addExtraImageParameters();
	virtual void addExtraParameters();
    virtual void addExtraListeners();
	virtual void loadRenderShader();
    virtual void extraSetupAction(); // NB if overriding, sub-modules should call this method as well
    virtual bool setExtraUniforms(int sourceImageWidth, int sourceImageHeight, int sourceImage2Width, int sourceImage2Height);
	//------------------------------------------
    
    virtual void renderTexture(bool clearFirstArg);
    bool loadSourceImage2();
    bool getSourceImage2HasLoaded();

    virtual void imageAssetSlotChanged(string slotNameArg);
    
    ofParameter<bool> useExternalSourceImage2;
    ofPtr<TXModParamInt> sourceImage2ScaleMode;
    
protected:
    ofMesh renderMesh;
    ofImage sourceImage2;
    bool sourceImage2HasChanged = false;
    bool sourceImage2HasLoaded = false;
    float tex2Left, tex2Right, tex2Top, tex2Bottom;
    float tex1Left, tex1Right, tex1Top, tex1Bottom;

public:
    // Extra methods & parameters in subclasses:
    //    EXAMPLE CODE:
    //    void  showEdgeColorChanged(ofAbstractParameter & parameterArg );
    
    //    ofPtr<TXModParamInt> copies;
    //    ofPtr<TXModParamFloat> freqX;
    //    ofPtr<TXModParamFloat> freqY;
    //    ofPtr<TXModParamFloat> ampX;
    //    ofPtr<TXModParamFloat> ampY;    
};
