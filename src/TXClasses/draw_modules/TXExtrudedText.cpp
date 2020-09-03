// modified by paul for TX

//
//  ofxExtrudedText.cpp
//  emptyExample
//
//  Created by Jeffrey Crouse on 11/12/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "TXExtrudedText.h"


// ------------------------------
TXExtrudedText::TXExtrudedText()
{
    depth = 50;
}

// ------------------------------
void TXExtrudedText::init(string _fontfile, int _size, int _depth, int _depthResolution, string _text, float _simplifyAmt, float _letterSpacing, float _spaceSize)
{
    fontfile = _fontfile;
    fontSize =_size;
    simplifyAmt = _simplifyAmt;
    letterSpacing = _letterSpacing;
    spaceSize = _spaceSize;
    fontLoaded = font.load(_fontfile, fontSize, true, true, true, simplifyAmt);
    font.setLetterSpacing(_letterSpacing);
    font.setSpaceSize(_spaceSize);
    depth = _depth;
    depthResolution = _depthResolution;
    textString = _text;
    meshesNeedRebuilding = true;
    updateMeshes();
}

// ------------------------------
void TXExtrudedText::draw()
{
    for(int i=0; i<letters.size(); i++)
    {
        letters[i].draw();
    }
}

// ------------------------------
void TXExtrudedText::adjustFont(float _size, float _simplifyAmt, float _letterSpacing, float _spaceSize)
{
    bool fontHasChanged = false;
    if ((fontSize !=_size) || (simplifyAmt != _simplifyAmt)) {
        fontHasChanged = true;
        fontSize =_size;
        simplifyAmt = _simplifyAmt;
        fontLoaded = font.load(fontfile, fontSize, true, true, true, simplifyAmt);
        fontSize =_size;
        simplifyAmt = _simplifyAmt;
    };
    if (fontHasChanged || (letterSpacing != _letterSpacing) || (spaceSize != _spaceSize)) {
        font.setLetterSpacing(_letterSpacing);
        font.setSpaceSize(_spaceSize);
        meshesNeedRebuilding = true;
        letterSpacing = _letterSpacing;
        spaceSize = _spaceSize;
    };
}

// ------------------------------
void TXExtrudedText::adjustDepth(int _depth,  int _depthResolution)
{
    depth = _depth;
    depthResolution = _depthResolution;
    meshesNeedRebuilding = true;
}

// ------------------------------
void TXExtrudedText::setText(string _text)
{
    textString = _text;
    meshesNeedRebuilding = true;
}

// ------------------------------
void TXExtrudedText::updateMeshes()
{
    if (meshesNeedRebuilding) {
        letters.clear();
        bbox = font.getStringBoundingBox(textString, 0, 0);
        
        vector<ofTTFCharacter> letterPaths = font.getStringAsPoints(textString);
        for(int i=0; i<letterPaths.size(); i++)
        {
            TXExtrudedLetter letter;
            letter.setup(letterPaths[i], depth, depthResolution);
            
            letters.push_back(letter);
        }
        meshesNeedRebuilding = false;
    }
}

