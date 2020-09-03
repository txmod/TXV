// modified by paul for TX

//
//  ofxExtrudedLetter.h
//  emptyExample
//
//  Created by Jeffrey Crouse on 11/12/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#include "ofMain.h"

class TXExtrudedLetter {
public:
    ofMesh front;
    ofMesh back;
    ofMesh side;
    vector<ofPolyline> lines;
    
    void setup(ofTTFCharacter letter, float depth, int depthResolution = 1);
    void draw();
    
};

