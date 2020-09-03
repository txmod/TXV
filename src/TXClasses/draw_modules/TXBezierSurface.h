
// this code is modified from ofxBezierSurface - see changes marked paul

#pragma once

// #include "ofVboMesh.h"// replaced with plane by paul
#include "ofMain.h"

class TXBezierSurface {
public:
    TXBezierSurface() {};
    void setup(int w, int h, int dim, int res);
    void update();
    void draw();
    void drawWireframe();
    void drawControls();
    void reset();
    vector<ofVec3f> getVertices();
    void setVertices(vector<ofVec3f> & verts);
    vector<ofVec3f> getControlPnts();
    void setControlPnts(vector<ofVec3f>);
    void setControlPntDim(int dim);
    int getControlPntDim();
    void mousePressed(ofMouseEventArgs& mouseArgs);
    void mouseDragged(ofMouseEventArgs &mouseArgs);
    void mouseReleased(ofMouseEventArgs& mouseArgs);
    void keyPressed(ofKeyEventArgs& keyArgs);
    void keyReleased(ofKeyEventArgs& keyArgs);
    void addListeners();
    
    float ctrlPntSize;
    ofPlanePrimitive plane; // public plane added by paul
    
private:
    int width;
    int height;
    int cx;
    int cy;
    int rx;
    int ry;
    vector< vector<ofVec3f> > inp;
    vector< vector<ofVec3f> > outp;
    void createSurface();
    vector< vector<ofVec3f> > calculateSurface(vector< vector<ofVec3f> > ip, vector< vector<ofVec3f> > op, int cpx, int cpy, int rpx, int rpy);
    void calcMeshNormals();
    double bezierBlend(int k, double mu, int n);
    ofPoint findPoint(ofMouseEventArgs mouseArgs);
    
    //ofVboMesh mesh; // replaced with plane by paul
    
    vector<ofPoint> selectedPnts;
    bool updateSurface;
    ofPoint lastMouse;
    bool up;
    bool down;
    bool left;
    bool right;
    bool found;
};