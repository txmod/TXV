// modified by paul for TX

//
//  ofxExtrudedText.h
//  emptyExample
//
//  Created by Jeffrey Crouse on 11/12/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofMain.h"
#include "TXExtrudedLetter.h"

class TXExtrudedText {
public:
    
    TXExtrudedText();
    void init(string _fontfile, int _size, int _depth,  int _depthResolution, string _text, float _simplifyAmt=0.3, float _letterSpacing = 1.0, float _spaceSize = 1.0);
    void draw();
    void adjustFont(float _size, float _simplifyAmt, float _letterSpacing, float _spaceSize);
    void adjustDepth(int _depth,  int _depthResolution);
    void setText(string _text);
    void updateMeshes();

    float getHeight()    {   return bbox.height;     }
    float getWidth()     {   return bbox.width;      }
    float getDepth()     {   return depth;           }
    bool  getFontLoaded(){   return fontLoaded;      }
    
    vector<TXExtrudedLetter> letters;
    
    
protected:
    
    
    string textString;
    string fontfile;
    int fontSize;
    float simplifyAmt;
    int depth;
    int depthResolution;
    float letterSpacing;
    float spaceSize;
    ofTrueTypeFont font;
    ofRectangle bbox;
    bool fontLoaded;
    bool meshesNeedRebuilding;
};