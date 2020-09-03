// modified by paul for TX

//
//  ofxExtrudedLetter.cpp
//  emptyExample
//
//  Created by Jeffrey Crouse on 11/12/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "TXExtrudedLetter.h"


// ------------------------------
void TXExtrudedLetter::draw()
{
    front.draw();
    back.draw();
    side.draw();
}


// ------------------------------
void TXExtrudedLetter::setup(ofTTFCharacter letter, float depth, int depthResolution)
{
    //
    depth = fmax(depth, 1.0);
    depthResolution = max(depthResolution, 1);
    lines = letter.getOutline();
    front = letter.getTessellation();
    back = front;
    
    ofVec3f* v = back.getVerticesPointer();
    for(int j=0; j< back.getNumVertices(); j++)
    {
        v[j].z -= depth;
    }
    
    for(int j=0; j<lines.size(); j++)
    {
        float depthDelta = depth / depthResolution;
        
        for(int level=0; level<depthResolution; level++)
        {
            
            float depth1 = level * depthDelta;
            float depth2 = depth1 + depthDelta;
            
            vector<ofPoint> points = lines[j].getVertices();
            int k;
            for(k=0; k<points.size()-1; k++)
            {
                ofPoint p1 = points[k+0];
                ofPoint p2 = points[k+1];
                
                side.addVertex(ofPoint(p1.x, p1.y, p1.z-depth1));
                side.addVertex(ofPoint(p2.x, p2.y, p2.z-depth1));
                side.addVertex(ofPoint(p1.x, p1.y, p1.z-depth2));
                
                side.addVertex(ofPoint(p1.x, p1.y, p1.z-depth2));
                side.addVertex(ofPoint(p2.x, p2.y, p2.z-depth2));
                side.addVertex(ofPoint(p2.x, p2.y, p2.z-depth1));
            }
            
            ofPoint p1 = points[k];
            ofPoint p2 = points[0];
            
            side.addVertex(ofPoint(p1.x, p1.y, p1.z-depth1));
            side.addVertex(ofPoint(p2.x, p2.y, p2.z-depth1));
            side.addVertex(ofPoint(p1.x, p1.y, p1.z-depth2));
            
            side.addVertex(ofPoint(p1.x, p1.y, p1.z-depth2));
            side.addVertex(ofPoint(p2.x, p2.y, p2.z-depth2));
            side.addVertex(ofPoint(p2.x, p2.y, p2.z-depth1));
        }
    }
}