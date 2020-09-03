#pragma once

#include "ofxMathMesh.h"
#include "TXParaShapes.h"


// =============== EXAMPLE ofx3dFunction CLASS
//
//class Parabala:public ofx3dFunction {
//public:
//    Parabala():ofx3dFunction(){
//    }
//    
//    float valueForPoint(float x,float z){
//        return curve * pow(x, 2) + curve * z * z;
//    }
//    
//    ofFloatColor colorForPoint(float x, float z,float y){
//        float maxY = valueForPoint(getXMax(), getZMax());
//        ofFloatColor color;
//        float hueValue = ofMap(y, 0, maxY, 0, ofFloatColor::limit());
//        color.setHsb(hueValue, 1.0, 1.0);
//        return color;
//    }
//    
//public:
//    float curve = 1;
//};
// ============================================


// TX Base class ====================

class TXParametricSurfaceBase :public ofxParametricSurface{
    
public:
    TXParametricSurfaceBase(): ofxParametricSurface(){
    // e.g. add overrides
//    minU = -2;
//    maxU = 2;
//    minV = 0;
//    maxV = 2 * PI;
//    scale = 3;
    }
    virtual void setup(float resUArg=24, float resVArg=24) {
        resolutionU = resUArg;
        resolutionV = resVArg;
        float stepU = (maxU - minU) / resolutionU;
        float stepV = (maxV - minV) / resolutionV;
        ofxParametricSurface::setup(minU, maxU, minV, maxV, stepU, stepV);
    }
    virtual ofPoint valueForPoint(float u,float v){
        float x, y, z;
        //  e.g. Ellipsoid Surface
        x = (cos(u) * sin(v));
        y = (sin(u) * sin(v));
        z = (cos(v));
        return scaledPoint(x, y, z);
    }
    virtual ofVec2f texCoordForPoint(float u,float v,ofPoint value){
        float s = textureWidth * (u - minU)/(maxU - minU);
        float t = textureHeight * (v - minV)/(maxV - minV);
        return ofVec2f(s,t);
    }
    ofPoint scaledPoint(float &x,float &y, float &z){
        return ofPoint(x * scale * width, y * scale * height, z * scale * depth);
    }
    void setXVals(float * xarrayArg){
        x1 = xarrayArg[0];
        x2 = xarrayArg[1];
        x3 = xarrayArg[2];
    }
    void setYVals(float * yarrayArg){
        y1 = yarrayArg[0];
        y2 = yarrayArg[1];
        y3 = yarrayArg[2];
    }
    void setZVals(float * zarrayArg){
        z1 = zarrayArg[0];
        z2 = zarrayArg[1];
        z3 = zarrayArg[2];
    }
//    void rescale() {
//        resizeMesh = getMesh();
//        int totalVertices = resizeMesh.getNumVertices();
//        ofVec3f holdVertex, newVertex;
//        float minX = 100000, maxX = -100000, minY = 100000, maxY = -100000, minZ = 100000, maxZ = -100000;
//        float halfWidth = width * 0.5;
//        float halfHeight = height * 0.5;
//        float halfDepth = depth * 0.5;
//        //
//        for(int i = 0; i < totalVertices; i++ ) {
//            holdVertex = resizeMesh.getVertex( i );
//            // change relevent vertices
//            minX = min(minX, holdVertex.x);
//            minY = min(minY, holdVertex.y);
//            minZ = min(minZ, holdVertex.z);
//            maxX = max(maxX, holdVertex.x);
//            maxY = max(maxY, holdVertex.y);
//            maxZ = max(maxZ, holdVertex.z);
//        }
//        for(int i = 0; i < totalVertices; i++ ) {
//            holdVertex = resizeMesh.getVertex( i );
//            newVertex.x = map(holdVertex.x, minX, maxX, -halfWidth, halfWidth);
//            newVertex.y = map(holdVertex.y, minY, maxY, -halfHeight, halfHeight);
//            newVertex.z = map(holdVertex.z, minZ, maxZ, -halfDepth, halfDepth);
//            getMesh().setVertex(i, holdVertex);
//        }
//    }
    
    float map(float value, float inputMin, float inputMax, float outputMin, float outputMax) {
        float outVal;
        if (inputMin == inputMax) {
            outVal = outputMin;
        } else {
            outVal = ofMap(value, inputMin, inputMax, outputMin, outputMax);
        };
        return outVal;
    }
    
        
public:
    float resolutionU = 24;
    float resolutionV = 24;
    float textureWidth = 1;
    float textureHeight = 1;
    float minU = 0;
    float maxU = 2 * PI;
    float minV = 0;
    float maxV = 2 * PI;
    float scale = 1;
    float width = 1;
    float height = 1;
    float depth = 1;
    float x1 = 1;
    float x2 = 1;
    float x3 = 1;
    float y1 = 1;
    float y2 = 1;
    float y3 = 1;
    float z1 = 1;
    float z2 = 1;
    float z3 = 1;
    
private:
//    ofVboMesh resizeMesh;
};

// TX CLASSES ====================================

/*
 // ===============   TEMPLATE ====================
 
 // TXParaShape_xyx xyx;
 class TXParaShape_xyx :public TXParametricSurfaceBase{
 public:
 TXParaShape_xyx():TXParametricSurfaceBase(){
 minU = -2;
 maxU = 2;
 minV = -2;
 maxV = 2;
 scale = 1;
 }
 ofPoint valueForPoint(float u,float v){
 float x, y, z;
 // xyx
 x = (cos(u) * sin(v));
 y = (sin(u) * sin(v));
 z = (cos(v));
 return scaledPoint(x, y, z);
 }
 };
  */

//  x/y/z scalars ====
//
//  x1*  x2*  x3*
//  y1*  y2*  y3*
//  z1*  z2*  z3*

// TXParaShape_Diamond Diamond;
class TXParaShape_Diamond :public TXParametricSurfaceBase{
public:
    TXParaShape_Diamond():TXParametricSurfaceBase(){
        minU = -HALF_PI;
        maxU = HALF_PI;
        minV = 0;
        maxV = 2 * PI;
        scale = 1.23;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Diamond
        x = cos(u)*cos(v) / ((abs(cos(4*u/4))+abs(sin(4*u/4)))*(abs(cos(4*v/4))+abs(sin(4*v/4))));
        y = cos(u)*sin(v) / ((abs(cos(4*u/4))+abs(sin(4*u/4)))*(abs(cos(4*v/4))+abs(sin(4*v/4))));
        z = sin(u) / (abs(cos(4*u/4))+abs(sin(4*u/4)));
        return scaledPoint(x, y, z);
    }
};

class TXParaShape_Torus :public TXParametricSurfaceBase{
public:
    TXParaShape_Torus():TXParametricSurfaceBase(){
        scale = 0.5;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Torus Surface - x1, x2, x3, y1, y2, z1, z2, z3
        // x = (1 + cos(v)) * cos(u);
        // y = sin(v);
        // z = (1 + cos(v)) * sin(u);
        x = (1 + cos(x1*v)) * cos((x2-1)*2*PI + x3*u);
        y = sin((y2-1)*2*PI + y1*v);
        z = (1 + cos(z1*v)) * sin((z2-1)*2*PI + z3*u);
        return scaledPoint(x, y, z);
    }
};

class TXParaShape_Ellipsoid :public TXParametricSurfaceBase{
public:
    TXParaShape_Ellipsoid():TXParametricSurfaceBase(){
        minU = -2;
        maxU = 2;
        minV = 0;
        maxV = 2 * PI;
        scale = 1.2;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Ellipsoid Surface - x1, x2, x3, y1, y2, y3, z1, z2
        // x = (cos(u) * sin(v));
        // y = (sin(u) * sin(v));
        // z = (cos(v));
        x = (cos(x1*u) * sin((x2-1)*2*PI + x3*v));
        y = (sin(y1*u) * sin((y2-1)*2*PI + y3*v));
        z = (cos((z2-1)*2*PI + z1*v));
        return scaledPoint(x, y, z);
    }
};

class TXParaShape_Paraboloid :public TXParametricSurfaceBase{
public:
    TXParaShape_Paraboloid():TXParametricSurfaceBase(){
        minU = -2;
        maxU = 2;
        minV = -2;
        maxV = 2;
        scale = 0.25;
}
    
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Paraboloid Surface - x1, x2, y1, y2
        // x =  2 * u * cos(v);
        // y =  2 * u * sin(v);
        // z =  u * u;
        x =  2 * u * cos((x2-1)*2*PI +x1*v);
        y =  2 * u * sin((y2-1)*2*PI +y1*v);
        z =  u * u;
        return scaledPoint(x, y, z);
    }
};


class TXParaShape_HyperbolicParaboloid :public TXParametricSurfaceBase{
public:
    TXParaShape_HyperbolicParaboloid():TXParametricSurfaceBase(){
        minU = -2;
        maxU = 2;
        minV = -2;
        maxV = 2;
        scale = 0.135;
    }
    
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // HyperbolicParaboloid Surface
        x = 4 * u;
        y = 4 * v;
        z = u * v;
        return scaledPoint(x, y, z);
    }
};


class TXParaShape_Hyperboloid1 :public TXParametricSurfaceBase{
public:
    TXParaShape_Hyperboloid1():TXParametricSurfaceBase(){
        minU = -2;
        maxU = 2;
        minV = 0;
        maxV = 2 * PI;
        scale = .25;
}
    
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Hyperboloid1 - x1, x2, x3, y1, y2, y3, z1, z2
        // x = cosh(u) * cos(v);
        // y = cosh(u) * sin(v);
        // z = sinh(u);
        x = cosh(x1*u) * cos((x2-1)*2*PI + x3*v);
        y = cosh(y1*u) * sin((y2-1)*2*PI + y3*v);
        z = sinh((z2-1)*2*PI + z1*u);
        return scaledPoint(x, y, z);
    }
};


class TXParaShape_Hyperboloid2 :public TXParametricSurfaceBase{
public:
    TXParaShape_Hyperboloid2():TXParametricSurfaceBase(){
        minU = -2;
        maxU = 2;
        minV = -2;
        maxV = 2;
        scale = 0.308;
    }
    
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Hyperboloid2 - x1, x2, x3, y1, y2, y3, z1, z2
        // x = sinh(u) * cos(v);
        // y = sinh(u) * sin(v) ;
        // z = cosh(u);
        x = sinh(x1*u) * cos((x2-1)*2*PI + x3*v);
        y = sinh(y1*u) * sin((y2-1)*2*PI + y3*v) ;
        z = cosh((z2-1)*2*PI + z1*u);
        return scaledPoint(x, y, z);
    }
};

class TXParaShape_RightConoid :public TXParametricSurfaceBase{
public:
    TXParaShape_RightConoid():TXParametricSurfaceBase(){
        scale = 0.135;
    }
    
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // RightConoid - x1, x2, y1, y2, z1, z2
        //A RightConoid is a surface generated by a 1-parameter family of horizontal straight lines that all meet a vertical straight line.
        //x = v * cos(u);
        //y = v * sin(u);
        //z = 8 * sin(u);
        x = v * cos((x2-1)*2*PI + x1*u);
        y = v * sin((y2-1)*2*PI + y1*u);
        z = 8 * sin((z2-1)*2*PI +z1*u);
        return scaledPoint(x, y, z);
    }
};


class TXParaShape_Helicoid :public TXParametricSurfaceBase{
public:
    TXParaShape_Helicoid():TXParametricSurfaceBase(){
        scale = 0.2;
    }
    
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Helicoid - x1, x2, y1, y2, z1
        float modVal;
        // float aa = 1;
        // modVal = aa - int(aa); //  0 ≤ aa ≤ 1.
        // x = v * cos( u );
        // y = v * sin( u );
        // z = (2 * modVal * sin(u)) + ((1.0-modVal) * u);
        modVal = z1 - int(z1); //  0 ≤ aa ≤ 1.
        x = v * cos((x2-1)*2*PI + x1*u);
        y = v * sin((y2-1)*2*PI + y1*u);
        z = (2 * modVal * sin(z2*u)) + ((1.0-modVal) * u);
        return scaledPoint(x, y, z);
    }
};

class TXParaShape_Periwinkle :public TXParametricSurfaceBase{
public:
    TXParaShape_Periwinkle():TXParametricSurfaceBase(){
        scale = 0.464;
    }
    
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Periwinkle - x1, x2, x3, y1, y2, y3, z1, z2
        float R=1;    // radius of tube
        float N=4.6;  // number of turns
        float H=2;    // height
        float P=2;    // power
        float holdVal = u/(2 * PI) * R;
        x = holdVal * cos(N * x1*u) * (1 + cos((x2-1)*2*PI + x3*v));
        y = holdVal * sin(N * y1*u) * (1 + cos((y2-1)*2*PI + y3*v));
        z = holdVal * sin((z2-1)*2*PI + z1*v) + H * powf(u/(2 * PI), P);
        return scaledPoint(x, y, z);
    }
};

class TXParaShape_Topshell :public TXParametricSurfaceBase{
public:
    TXParaShape_Topshell():TXParametricSurfaceBase(){
        scale = 0.45;
    }
    
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Topshell
        float R=1;    // radius of tube
        float N=7.6;  // number of turns
        float H=2.5;  // height
        float P=1.3;  // power
        float holdVal = u/(2*PI)*R;
        x = holdVal * cos(N * u) * (1 + cos(v));
        y = holdVal * sin(N * u) * (1 + cos(v));
        z = holdVal * sin(v) + H * powf(u/(2 * PI), P);
        return scaledPoint(x, y, z);
    }
};

class TXParaShape_ConeShell :public TXParametricSurfaceBase{
public:
    TXParaShape_ConeShell():TXParametricSurfaceBase(){
        scale = 0.48;
    }
    
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // ConeShell
        float R=1;    // radius of tube
        float N=4.6;  // number of turns
        float H=0.5;  // height
        float P=2;    // power
        float holdVal = u/(2*PI)*R;
        x = holdVal*cos(N * u) * (1 + cos(v));
        y = holdVal * sin(N * u) * (1 + cos(v));
        z = holdVal * sin(v) * 1.25 + H * powf(u/(2 * PI), P) + holdVal * cos(v) * 1.25;
        return scaledPoint(x, y, z);
    }
};

class TXParaShape_Periwinkle2 :public TXParametricSurfaceBase{
public:
    TXParaShape_Periwinkle2():TXParametricSurfaceBase(){
        scale = 0.435;
    }
    
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Periwinkle
        float R=1;    // radius of tube
        float N=4.6;  // number of turns
        float H=2.5;  // height
        float F=80;   // wave frequency
        float A=0.2;  // wave amplitude
        float P=1.9;  // power
        float holdVal = u/(2 * PI) * R;
        x = holdVal * cos(N * u) * (1 + cos(v) + cos(F * u) * A);
        y = holdVal * sin(N * u) * (1 + cos(v) + cos(F * u) * A);
        z = holdVal * sin(v) + H * powf(u/(2 * PI), P);
        return scaledPoint(x, y, z);
    }
};

class TXParaShape_ToothedTopshell :public TXParametricSurfaceBase{
public:
    TXParaShape_ToothedTopshell():TXParametricSurfaceBase(){
        scale = 0.47;
    }
    
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // TXParaShape_ToothedTopshell - x1, x2, x3, y1, y2, y3, z1, z2, z3
        float R=1;    // radius of tube
        float N=7.6;  // number of turns
        float H=2.5;  // height
        float P=1.3;  // power
        float T=0.8;  // Triangleness of cross section
        float A=-0.3;  // Angle of tilt of cross section (radians)
        float holdVal = u/(2 * PI) * R;
        x = holdVal * cos(N * x3*u) * (1 + cos(v + x1*A) + sin(2 * v + x1*A) * x2*T/4);
        y = holdVal * sin(N * y3*u) * (1 + cos(v + y1*A) + sin(2 * v + y1*A) * y2*T/4);
        z = holdVal * (sin(v + z1*A) + cos(2 * v + (z2-1)*2*PI + z1*A) * z3*T/4) + H * powf(u/(2 * PI), P);
        return scaledPoint(x, y, z);
    }
};

class TXParaShape_TurretShell :public TXParametricSurfaceBase{
public:
    TXParaShape_TurretShell():TXParametricSurfaceBase(){
        scale = 0.209;
    }
    
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // TurretShell
        float R=1;    // radius of tube
        float N=9.6;  // number of turns
        float H=5.0;  // height
        float P=1.5;  // power
        float P1=1.1; // another power
        float T=0.8;  // Triangleness of cross section
        float A=0.1;  // Angle of tilt of cross section (radians)
        float S=1.5;  // Stretch
        
        float holdVal = powf(u/(2 * PI) * R, P1);
        x = holdVal * cos(N * u) * (1 + cos(v + A) + sin(2 * v + A) * T/4);
        y = holdVal * sin(N * u) * (1 + cos(v + A) + sin(2 * v + A) * T/4);
        z = S * holdVal * (sin(v + A) + cos(2 * v + A) * T/4) + S * H * powf(u/(2 * PI), P);
        return scaledPoint(x, y, z);
    }
};

class TXParaShape_ShellX :public TXParametricSurfaceBase{
public:
    TXParaShape_ShellX():TXParametricSurfaceBase(){
        scale = 0.194;
    }
    
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // ShellX
        float R=1;    // radius of tube
        float N=7.6;  // number of turns
        float H=2.5;  // height
        float P=1.3;  // power
        float T=0.8;  // Triangleness of cross section
        float A=-0.3; // Angle of tilt of cross section (radians)
        float S=3.0;  // Stretch
        
        float holdVal = u/(2 * PI) * R;
        x = holdVal * cos(N * u) * (1 + cos(v + A) + sin(2 * v + A) * T/4);
        y = holdVal * sin(N * u) * (1 + cos(v + A) + sin(2 * v + A) * T/4);
        z = S * holdVal * (sin(v + A) + cos(2 * v + A) * T/4) + S * H * powf(u/(2 * PI), P);
        return scaledPoint(x, y, z);
    }
};

class TXParaShape_SpindleShell :public TXParametricSurfaceBase{
public:
    TXParaShape_SpindleShell():TXParametricSurfaceBase(){
        scale = 0.212;
    }
    
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // SpindleShell
        float R=1;    // radius of tube
        float N=5.6;  // number of turns
        float H=4.5;  // height
        float P=1.4;  // power
        float L=4;    // Controls spike length
        float K=9;    // Controls spike sharpness
        
        float holdVal = pow((u/(2 * PI)*R), 0.9);
        
        x = holdVal * cos(N * u) * (1 + cos(v));
        y = holdVal * sin(N * u) * (1 + cos(v));
        z = holdVal * (sin(v) + L * pow(sin(v/2), K)) + H * powf(u/(2 * PI), P);
        return scaledPoint(x, y, z);
    }
};

class TXParaShape_Topshell2 :public TXParametricSurfaceBase{
public:
    TXParaShape_Topshell2():TXParametricSurfaceBase(){
        scale = 0.47;
    }
    
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Topshell2
        float R=1;    // radius of tube
        float N=7.6;  // number of turns
        float H=2.5;  // height
        float P=1.3;  // power
        float T=0.8;  // Triangleness of cross section
        float A=-0.3;  // Angle of tilt of cross section (radians)
        
        float holdVal = u/(2 * PI) * R;
        x = holdVal * cos(N * u) * (1 + cos(v + A) + sin(2 * v + A) * T/4);
        y = holdVal * sin(N * u) * (1 + cos(v + A) + sin(2 * v + A) * T/4);
        z = holdVal * (sin(v + A) + cos(2 * v + A) * T/4) + H * powf(u/(2 * PI), P);
        return scaledPoint(x, y, z);
    }
};

class TXParaShape_CrossCap :public TXParametricSurfaceBase{
public:
    TXParaShape_CrossCap():TXParametricSurfaceBase(){
        minU = -HALF_PI;
        maxU = HALF_PI;
        minV = -HALF_PI;
        maxV = HALF_PI;
        scale = 0.5;
}
    
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // CrossCap - x1, x2, x3, y1, y2, y3, z1, z2, z3
        x = 2 * (sin(x1*u)*sin((x2-1)*2*PI + 2*x3*v)/2);
        y = 2 * (sin(2*y1*u)*pow(cos((y2-1)*2*PI + y3*v), 2));
        z = 2 * (cos(2*z1*u)*pow(cos((z2-1)*2*PI + z3*v), 2));
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Klien klein;
class TXParaShape_Klien :public TXParametricSurfaceBase{
public:
    TXParaShape_Klien():TXParametricSurfaceBase(){
            minU = 0;
            maxU = PI;
            minV = 0;
            maxV = 2 * PI;
            scale = .12;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Klien - x1, x2, x3, y1, y2, y3, z1, z2
        x = (1-cos(x1*u)/2)*cos(x1*u)*cos(x3*v) + 6*cos(x2*u)*(1 + sin(x2*u));
        y = (1-cos(y1*u)/2)*sin(y1*u)*cos(y3*v) + 16*sin(y2*u);
        z = (1-cos(z1*u)/2)*sin(z2*v);
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Klein2 Klein2;
class TXParaShape_Klein2 :public TXParametricSurfaceBase{
public:
    TXParaShape_Klein2():TXParametricSurfaceBase(){
        minU = 0;
        maxU = 2 * PI;
        minV = 0;
        maxV = 2 * PI;
        scale = .38;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Klein2
        x = (2 + cos(x2*v/2)*sin(x1*u)-sin(v/2)*sin(2*x3*u))*cos(x2*v);
        y = (2 + cos(y2*v/2)*sin(y1*u)-sin(y2*v/2)*sin(2*y3*u))*sin(y2*v);
        z = sin(z2*v/2)*sin(z1*u) + cos(z2*v/2)*sin(2*z3*u);
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Cosinus cosinus;
class TXParaShape_Cosinus :public TXParametricSurfaceBase{
public:
    TXParaShape_Cosinus():TXParametricSurfaceBase(){
            minU = -1;
            maxU = 1;
            minV = -1;
            maxV = 1;
            scale = 1;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Cosinus - z1, z2
        x = u;
        y = v;
        z = -sin(PI*((z1*u*u) + (z2*v*v)))/3;
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Moebius moebius;
class TXParaShape_Moebius :public TXParametricSurfaceBase{
public:
    TXParaShape_Moebius():TXParametricSurfaceBase(){
            minU = -0.4;
            maxU = 0.4;
            minV = 0;
            maxV = 2 * PI;
        scale = 0.86;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Moebius
        x = cos(v) + u*cos(v/2)*cos(v);
        y = sin(v) + u*cos(v/2)*sin(v);
        z = u*sin(v/2);
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Reiman Reiman;
class TXParaShape_Reiman :public TXParametricSurfaceBase{
public:
    TXParaShape_Reiman():TXParametricSurfaceBase(){
            minU = -6;
            maxU = 6;
            minV = -25;
            maxV = 25;
            scale = 0.0028;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Reiman
        x = u*v;
        y = (v*v)-(u*u);
        z = 30*u;
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Henneberg Henneberg;
class TXParaShape_Henneberg :public TXParametricSurfaceBase{
public:
    TXParaShape_Henneberg():TXParametricSurfaceBase(){
            minU = -1;
            maxU = 1;
            minV = -HALF_PI;
            maxV = HALF_PI;
            scale = 0.258;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Henneberg - x1, x2, y1, y2, z1, z2
        x = 2*sinh(x1*u)*cos(x2*v)-(2/3)*sinh(3*x1*u)*cos(3*x2*v);
        y = 2*sinh(y1*u)*sin(y2*v) + (2/3)*sinh(3*y1*u)*sin(3*y2*v);
        z = 2*cosh(2*z1*u)*cos(2*z2*v);
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Enneper Enneper;
class TXParaShape_Enneper :public TXParametricSurfaceBase{
public:
    TXParaShape_Enneper():TXParametricSurfaceBase(){
            minU = -2;
            maxU = 2;
            minV = -2;
            maxV = 2;
            scale = 0.148;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Enneper - x1, x2, y1, y2, z1, z2
        x = x1*u-pow(x1*u,x2*3)/x2*3 + x1*u*(v*v);
        y = y1*v-pow(y1*v,y2*3)/y2*3 + y1*v*(u*u);
        z = (z1*u*u)-(z2*v*v);
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Enneper2 Enneper2;
class TXParaShape_Enneper2 :public TXParametricSurfaceBase{
public:
    TXParaShape_Enneper2():TXParametricSurfaceBase(){
        minU = 0;
        maxU = 1.2;
        minV = -PI;
        maxV = PI;
        scale = 0.58;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Enneper2 - x1, x2, y1, y2, z1
        x = u*cos(x1*v)-pow(u,3)/3*cos(3*x2*v);
        y = -u*sin(y1*v)-pow(u,3)/3*sin(3*y2*v);
        z = (u*u)*cos(z1*2*v);
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Helix Helix;
class TXParaShape_Helix :public TXParametricSurfaceBase{
public:
    TXParaShape_Helix():TXParametricSurfaceBase(){
            minU = 0;
            maxU = 4 * PI;
            minV = 0;
            maxV = 2 * PI;
            scale = 0.672;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Helix
        x = (1-0.1*cos(v))*cos(u);
        y = (1-0.1*cos(v))*sin(u);
        z = 0.2*(sin(v) + u/1.7-10);
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Hexaedron Hexaedron;
class TXParaShape_Hexaedron :public TXParametricSurfaceBase{
public:
    TXParaShape_Hexaedron():TXParametricSurfaceBase(){
            minU = -1.3;
            maxU = 1.3;
            minV = 0;
            maxV = 2 * PI;
            scale = 1;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Hexaedron - x1, x2, y1, y2, z1, z2
        x = pow(cos(x3*v),x3*3)*pow(cos(x1*u),x2*3);
        y = pow(sin(y3*v),y3*3)*pow(cos(y1*u),y2*3);
        z = pow(sin(z1*u),z2*3);  
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Catalan Catalan;
class TXParaShape_Catalan :public TXParametricSurfaceBase{
public:
    TXParaShape_Catalan():TXParametricSurfaceBase(){
            minU = -PI;
            maxU = 3 * PI;
            minV = -2;
            maxV = 2;
            scale = 0.28;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Catalan - x1, x2, y1, y2, z1, z2
        x = u-(sin(x1*u)*cosh(x2*v));
        y = 1-(cos(y1*u)*cosh(y2*v));
        z = 4*sin(z1*0.5*u)*sinh(0.5*z2*v);
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_ Toupie Toupie;
class TXParaShape_Toupie :public TXParametricSurfaceBase{
public:
    TXParaShape_Toupie():TXParametricSurfaceBase(){
            minU = -1;
            maxU = 1;
            minV = 0;
            maxV = 2 * PI;
            scale = 1.2;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Toupie - x1, x2, y1, y2
        x = pow(abs(u)-1, 2)*cos((x1-1)*2*PI + x2*v);
        y = pow(abs(u)-1, 2)*sin((y1-1)*2*PI + y2*v);
        z = u;
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Toupie2 Toupie2;
class TXParaShape_Toupie2 :public TXParametricSurfaceBase{
public:
    TXParaShape_Toupie2():TXParametricSurfaceBase(){
            minU = 0;
            maxU = 1;
            minV = 0;
            maxV = 2 * PI;
            scale = 1.2;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Toupie2 - x1, x2, y1, y2
        x = pow(abs(u)-1, 2)*cos((x1-1)*2*PI + x2*v);
        y = pow(abs(u)-1, 2)*sin((y1-1)*2*PI + y2*v);
        z = u;
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Trumpet Trumpet;
class TXParaShape_Trumpet :public TXParametricSurfaceBase{
public:
    TXParaShape_Trumpet():TXParametricSurfaceBase(){
            minU = 0;
            maxU = 2 * PI;
            minV = 0.03;
            maxV = 2;
            scale = 0.412;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Trumpet - x1, x2, y1, y2, z1, z2
        x = cos(x1*u)*sin(x2*v);
        y = sin(y1*u)*sin(y2*v);
        z = (cos(z1*v) + log(tan(0.5*z2*v)));
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Catenoid Catenoid;
class TXParaShape_Catenoid :public TXParametricSurfaceBase{
public:
    TXParaShape_Catenoid():TXParametricSurfaceBase(){
            minU = -PI;
            maxU = PI;
            minV = -PI;
            maxV = PI;
            scale = 0.315;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Catenoid
        x = 2*cosh(x1*v*0.5)*cos(x2*u);
        y = 2*cosh(y1*v*0.5)*sin(y2*u);
        z = v;
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Shoe Shoe;
class TXParaShape_Shoe :public TXParametricSurfaceBase{
public:
    TXParaShape_Shoe():TXParametricSurfaceBase(){
            minU = -2;
            maxU = 2;
            minV = -2;
            maxV = 2;
            scale = 1;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Shoe
        x = u;
        y = v;
        z = 1/3*pow(u,3)-1/2*(v*v);
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Crescent Crescent;
class TXParaShape_Crescent :public TXParametricSurfaceBase{
public:
    TXParaShape_Crescent():TXParametricSurfaceBase(){
            minU = 0;
            maxU = 1;
            minV = 0;
            maxV = 0.5;
            scale = 0.444;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Crescent - x1, x2, x3, y1, y2, y3, z1, z2
        x = (2 + sin(2*PI*x1*u)*sin(2*PI*x2*v))*sin(3*PI*x3*v);
        y = (2 + sin(2*PI*y1*u)*sin(2*PI*y2*v))*cos(3*PI*y3*v);
        z = cos(2*PI*z1*u)*sin(2*PI*z2*v) + 4*v-2;
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Crescent2 Crescent2;
class TXParaShape_Crescent2 :public TXParametricSurfaceBase{
public:
    TXParaShape_Crescent2():TXParametricSurfaceBase(){
            minU = 0;
            maxU = 1;
            minV = 0;
            maxV = 1;
            scale = 0.417;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Crescent2 - x1, x2, x3, y1, y2, y3, z1, z2
        x = (2 + sin(2*PI*x1*u)*sin(2*PI*x2*v))*sin(3*PI*x3*v);
        y = (2 + sin(2*PI*y1*u)*sin(2*PI*y2*v))*cos(3*PI*y3*v);
        z = cos(2*PI*z1*u)*sin(2*PI*z2*v) + 4*v-2;
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_HyperbolicHelicoid HyperbolicHelicoid;
class TXParaShape_HyperbolicHelicoid :public TXParametricSurfaceBase{
public:
    TXParaShape_HyperbolicHelicoid():TXParametricSurfaceBase(){
            minU = -PI;
            maxU = PI;
            minV = -PI;
            maxV = PI;
            scale = 1.23;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // HyperbolicHelicoid - x1, x2, x3, y1, y2, y3, z1, z2, z3
        x = (sinh(x1*v)*cos(3*x2*u))/(1 + cosh(x3*u)*cosh(x1*v));
        y = (sinh(y1*v)*sin(3*y2*u))/(1 + cosh(y3*u)*cosh(y1*v));
        z = (cosh(z1*v)*sinh(z2*u))/(1 + cosh(z3*u)*cosh(z1*v));
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Horn Horn;
class TXParaShape_Horn :public TXParametricSurfaceBase{
public:
    TXParaShape_Horn():TXParametricSurfaceBase(){
            minU = 0;
            maxU = 1;
            minV = 0;
            maxV = 2 * PI;
            scale = 0.35;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Horn
        x = (2 + u*cos(x1*v))*sin(2*PI*x2*u);
        y = (2 + u*cos(y1*v))*cos(2*PI*y2*u) + 2*u;
        z = u*sin(z1*v);
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Fresnel Fresnel;
class TXParaShape_Fresnel :public TXParametricSurfaceBase{
public:
    TXParaShape_Fresnel():TXParametricSurfaceBase(){
            minU = 0;
            maxU = 2 * PI;
            minV = -HALF_PI;
            maxV = HALF_PI;
            scale = 0.538;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Fresnel
        x = cos(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((pow(cos(u),4) + pow(sin(u),4))*pow(cos(v),4) + pow(sin(v),4)))*cos((acos(-(-0.941/6. + 0.374*((pow(cos(u),4) + pow(sin(u),4))*pow(cos(v),4) + pow(sin(v),4))-1.309/6.*((pow(cos(u),6) + pow(sin(u),6))*pow(cos(v),6) + pow(sin(v),6))-1.221*pow(cos(u),2)*pow(cos(v),4)*pow(sin(u),2)*pow(sin(v),2))/pow(sqrt(0.965/3.-0.935/3.*((pow(cos(u),4) + pow(sin(u),4))*pow(cos(v),4) + pow(sin(v),4))),3)) + PI)/3.) + 0.8);
        y = sin(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((pow(cos(u),4) + pow(sin(u),4))*pow(cos(v),4) + pow(sin(v),4)))*cos((acos(-(-0.941/6. + 0.374*((pow(cos(u),4) + pow(sin(u),4))*pow(cos(v),4) + pow(sin(v),4))-1.309/6.*((pow(cos(u),6) + pow(sin(u),6))*pow(cos(v),6) + pow(sin(v),6))-1.221*pow(cos(u),2)*pow(cos(v),4)*pow(sin(u),2)*pow(sin(v),2))/pow(sqrt(0.965/3.-0.935/3.*((pow(cos(u),4) + pow(sin(u),4))*pow(cos(v),4) + pow(sin(v),4))),3)) + PI)/3.) + 0.8);
        z = sin(v)/(-2.*sqrt(0.965/3.-0.935/3.*((pow(cos(u),4) + pow(sin(u),4))*pow(cos(v),4) + pow(sin(v),4)))*cos((acos(-(-0.941/6. + 0.374*((pow(cos(u),4) + pow(sin(u),4))*pow(cos(v),4) + pow(sin(v),4))-1.309/6.*((pow(cos(u),6) + pow(sin(u),6))*pow(cos(v),6) + pow(sin(v),6))-1.221*pow(cos(u),2)*pow(cos(v),4)*pow(sin(u),2)*pow(sin(v),2))/pow(sqrt(0.965/3.-0.935/3.*((pow(cos(u),4) + pow(sin(u),4))*pow(cos(v),4) + pow(sin(v),4))),3)) + PI)/3.) + 0.8);
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Steiner Steiner;
class TXParaShape_Steiner :public TXParametricSurfaceBase{
public:
    TXParaShape_Steiner():TXParametricSurfaceBase(){
            minU = -HALF_PI;
            maxU = HALF_PI;
            minV = -HALF_PI;
            maxV = HALF_PI;
            scale = 1;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Steiner - x1, x2, x3, y1, y2, y3, z1, z2, z3
        x = (sin(2*x1*u)*cos(x2*v)*cos((x3-1)*2*PI + x2*v));
        y = (sin(y1*u)*sin((y3-1)*2*PI + 2*y2*v));
        z = (cos(z1*u)*sin((z3-1)*2*PI + 2*z2*v));
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_MaedersOwl MaedersOwl;
class TXParaShape_MaedersOwl :public TXParametricSurfaceBase{
public:
    TXParaShape_MaedersOwl():TXParametricSurfaceBase(){
            minU = 0;
            maxU = 4 * PI;
            minV = 0;
            maxV = 1;
            scale = 0.82;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // MaedersOwl - x1, x2, x3, y1, y2, y3, z1, z2
        x = v*cos(x1*u)-0.5*(v*v)*cos((x2-1)*2*PI + 2*x3*u);
        y = -v*sin(y1*u)-0.5*(v*v)*sin((y2-1)*2*PI + 2*y3*u);
        z = 4*pow(v,1.5f)*cos((z1-1)*2*PI + 1.5*z2*u)/3;
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_TrippleFin TrippleFin;
class TXParaShape_TrippleFin :public TXParametricSurfaceBase{
public:
    TXParaShape_TrippleFin():TXParametricSurfaceBase(){
            minU = 0;
            maxU = PI;
            minV = 0;
            maxV = PI;
            scale = 0.756;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // TrippleFin
        x = 0.6*(cos(u)*cos(2*v) + sqrt(2)*sin(u)*cos(v))*cos(u)/(sqrt(2)-sin(2*u)*sin(3*v));
        y = 0.6*(cos(u)*sin(2*v)-sqrt(2)*sin(u)*sin(v))*cos(u)/(sqrt(2)-sin(2*u)*sin(3*v));
        z = sqrt(2)*cos(u)*cos(u)/(sqrt(2)-sin(2*u)*sin(3*v));
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_EightSurface EightSurface;
class TXParaShape_EightSurface :public TXParametricSurfaceBase{
public:
    TXParaShape_EightSurface():TXParametricSurfaceBase(){
        minU = 0;
        maxU = 2 * PI;
        minV = -HALF_PI;
        maxV = HALF_PI;
        scale = 0.96;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // EightSurface - x1, x2, x3, y1, y2, y3, z1, z2
        x = cos(x1*u)*sin((x2-1)*2*PI + 2*x3*u);
        y = sin(y1*u)*sin((y2-1)*2*PI + 2*y3*u);
        z = sin((z1-1)*2*PI + z2*v);
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_EightSurface2 EightSurface2;
class TXParaShape_EightSurface2 :public TXParametricSurfaceBase{
public:
    TXParaShape_EightSurface2():TXParametricSurfaceBase(){
        minU = 0;
        maxU = 2 * PI;
        minV = 0;
        maxV = HALF_PI;
        scale = 1.12;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // EightSurface2 - x1, x2, x3, y1, y2, y3, z1, z2
        x = cos(x1*u)*sin((x2-1)*2*PI + 2*x3*u);
        y = sin(y1*u)*sin((y2-1)*2*PI + 2*y3*u);
        z = sin((z1-1)*2*PI + z2*v);
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Roman Roman;
class TXParaShape_Roman :public TXParametricSurfaceBase{
public:
    TXParaShape_Roman():TXParametricSurfaceBase(){
        minU = 0;
        maxU = PI;
        minV = -HALF_PI;
        maxV = HALF_PI;
        scale = 0.96;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Roman - x1, x2, x3, y1, y2, y3, z1, z2, z3
        x = sin(2*x1*u)*pow(sin((x2-1)*2*PI + x3*v),2);
        y = sin(y1*u)*cos((y2-1)*2*PI + 2*y3*v);
        z = cos(z1*u)*sin((z2-1)*2*PI + 2*z3*v);
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Dini Dini;
class TXParaShape_Dini :public TXParametricSurfaceBase{
public:
    TXParaShape_Dini():TXParametricSurfaceBase(){
            minU = 0;
            maxU = 12.4;
            minV = 0.1;
            maxV = 2;
            scale = 0.5;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Dini - x1, x2, x3, y1, y2, y3, z1, z2, z3
        x = cos(x1*u)*sin((x2-1)*2*PI + x3*v);
        y = sin(y1*u)*sin((y2-1)*2*PI + y3*v);
        z = (cos(z1*v) + log(tan(z2*PI + 0.5*z3*v))) + 0.2*u;
        return scaledPoint(x, y, z);
    }
};


// TXParaShape_Apple Apple;
class TXParaShape_Apple :public TXParametricSurfaceBase{
public:
    TXParaShape_Apple():TXParametricSurfaceBase(){
            minU = 0;
            maxU = 2 * PI;
            minV = -PI;
            maxV = PI;
            scale = 0.08;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Apple
        x = cos(u)*(4 + 3.8*cos(v));
        y = sin(u)*(4 + 3.8*cos(v));
        z = (cos(v) + sin(v)-1)*(1 + sin(v))*log(1-PI*v/10) + 7.5*sin(v);
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Drop Drop;
class TXParaShape_Drop :public TXParametricSurfaceBase{
public:
    TXParaShape_Drop():TXParametricSurfaceBase(){
            minU = 0;
            maxU = 2;
            minV = 0;
            maxV = 2 * PI;
            scale = 0.5;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Drop - x1, x2, y1, y2, z1, z2, z3
        x = u*cos((x1-1)*2*PI + x2*v);
        y = u*sin((y1-1)*2*PI + y2*v);
        z = exp(-u*u)*(sin(2*PI*z1*u)-u*cos((z2-1)*2*PI + 3*z3*v));
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Kidney Kidney;
class TXParaShape_Kidney :public TXParametricSurfaceBase{
public:
    TXParaShape_Kidney():TXParametricSurfaceBase(){
            minU = 0;
            maxU = 2 * PI;
            minV = -HALF_PI;
            maxV = HALF_PI;
            scale = 0.35;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Kidney - x1, x2, x3, y1, y2, y3, z1, z2, z3
        x = cos((x1-1)*2*PI + x2*u)*(3*cos(x3*v)-cos(3*x3*v));
        y = sin((y1-1)*2*PI + y2*u)*(3*cos(y3*v)-cos(3*y3*v));
        z = 3*sin((z1-1)*2*PI + z2*v)-sin(3*z3*v);
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_LimpetTorus LimpetTorus;
class TXParaShape_LimpetTorus :public TXParametricSurfaceBase{
public:
    TXParaShape_LimpetTorus():TXParametricSurfaceBase(){
            minU = -PI;
            maxU = PI;
            minV = -PI;
            maxV = PI;
            scale = 0.45;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // LimpetTorus - x1, x2, x3, y1, y2, y3, z1, z2
        x = cos((x1-1)*2*PI + x2*u)/(sqrt(2) + sin(x3*v));
        y = sin((y1-1)*2*PI + y2*u)/(sqrt(2) + sin(y3*v));
        z = 1/(sqrt(2) + cos((z1-1)*2*PI + z2*v));
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Lemniscape Lemniscape;
class TXParaShape_Lemniscape :public TXParametricSurfaceBase{
public:
    TXParaShape_Lemniscape():TXParametricSurfaceBase(){
            minU = 0;
            maxU = PI;
            minV = 0;
            maxV = PI;
            scale = 1.2;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        float modU = (z1-1)*2*PI + z2*u;
        float modV = z3*v;
        // Lemniscape - x1, x2, x3, y1, y2, y3, z1, z2, z3
        x = cos((x1-1)*2*PI + x2*v)*sqrt(abs(sin(2*u)))*cos(x3*u);
        y = cos((y1-1)*2*PI + y2*v)*sqrt(abs(sin(2*u)))*sin(y3*u);
        z = pow(cos(modV)*sqrt(abs(sin(2*modU)))*cos(modU),2) - pow(cos(modV)*sqrt(abs(sin(2*modU)))*sin(modU), 2) + 2*(cos(modV)*sqrt(abs(sin(2*modU)))*cos(modU))*(cos(modV)*sqrt(abs(sin(2*modU)))*sin(modU))*pow(tan(modV),2);
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Folium Folium;
class TXParaShape_Folium :public TXParametricSurfaceBase{
public:
    TXParaShape_Folium():TXParametricSurfaceBase(){
            minU = -PI;
            maxU = PI;
            minV = -PI;
            maxV = PI;
            scale = 1.2;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Folium - x1, x2, x3, y1, y2, y3, z1, z2, z3
        x = cos((x1-1)*2*PI + x2*u)*(2*x3*v/PI-tanh(x3*v));
        y = cos((y1-1)*2*PI + y2*u + 2*PI/3)/cosh(y3*v);
        z = cos((z1-1)*2*PI + z2*u-2*PI/3)/cosh(z3*v);
        return scaledPoint(x, y, z);
    }
};

/*  NB HEART REMOVED - NOT WORKING
 
// TXParaShape_Heart Heart;
class TXParaShape_Heart :public TXParametricSurfaceBase{
public:
    TXParaShape_Heart():TXParametricSurfaceBase(){
        minU = -PI;
        maxU = PI;
        minV = -1;
        maxV = 1;
        scale = 1;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Heart
        //x = cos(u)* pow(4*sqrt(1-(v*v))*sin(abs(u)),abs(u));
        //y = sin(u)* pow(4*sqrt(1-(v*v))*sin(abs(u)),abs(u));
        x = cos(u)* 4*sqrt(1-(v*v))*pow(sin(abs(u)),abs(u));
        y = sin(u)* 4*sqrt(1-(v*v))*pow(sin(abs(u)),abs(u));
        z = v;
        return scaledPoint(x, y, z);
    }
};
 */

// TXParaShape_PinchedSphere PinchedSphere;
class TXParaShape_PinchedSphere :public TXParametricSurfaceBase{
public:
    TXParaShape_PinchedSphere():TXParametricSurfaceBase(){
        minU = -HALF_PI;
        maxU = HALF_PI;
        minV = 0;
        maxV = 2 * PI;
        scale = 1.2;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // PinchedSphere - x1, x2, x3, y1, y2, y3, z1, z2, z3
        x = cos((x1-1)*2*PI + x2*u)*cos(x3*v);
        y = cos((y1-1)*2*PI + y2*u)*sin(y3*v);
        z = sin((z1-1)*2*PI + z2*u)*sin(z3*v)*cos(z3*v);
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_PinchedPillow PinchedPillow;
class TXParaShape_PinchedPillow :public TXParametricSurfaceBase{
public:
    TXParaShape_PinchedPillow():TXParametricSurfaceBase(){
        minU = -HALF_PI;
        maxU = HALF_PI;
        minV = 0;
        maxV = 2 * PI;
        scale = 1.2;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // PinchedPillow - x1, x2, x3, y1, y2, y3, z1, z2, z3
        x = cos((x1-1)*2*PI + x2*u)*cos(x3*v)*sin(x2*u);
        y = cos((y1-1)*2*PI + y2*u)*sin(y3*v)*cos(y2*u);
        z = sin((z1-1)*2*PI + z2*u)*sin(z3*v)*sin(z2*u);
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_TwistedSphere TwistedSphere;
class TXParaShape_TwistedSphere :public TXParametricSurfaceBase{
public:
    TXParaShape_TwistedSphere():TXParametricSurfaceBase(){
        minU = -HALF_PI;
        maxU = HALF_PI;
        minV = 0;
        maxV = 2 * PI;
        scale = 0.35;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // TwistedSphere - x1, x2, x3, y1, y2, y3, z1, z2
        x = cos(x1*u)*cos((x2-1)*2*PI + x3*v) + sin((sin(x1*u) + 1)*2*PI);
        y = cos(y1*u)*sin((y2-1)*2*PI + y3*v) + cos((sin(y1*u) + 1)*2*PI);
        z = 4*sin((z1-1)*2*PI + z2*u);
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_TwistedTorus TwistedTorus;
class TXParaShape_TwistedTorus :public TXParametricSurfaceBase{
public:
    TXParaShape_TwistedTorus():TXParametricSurfaceBase(){
        minU = 0;
        maxU = 2 * PI;
        minV = 0;
        maxV = 2 * PI;
        scale = .8;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        float holdYU = (y1-1)*2*PI + y2*u;
        float holdYV = y3*v;
        float holdZU = (z1-1)*2*PI + z2*u;
        float holdZV = z3*v;
        // TwistedTorus - x1, x2, x3, y1, y2, y3, z1, z2, z3
        x = (1 + 0.5*cos((x1-1)*2*PI + x2*u))*cos(x3*v);
        y = 0.632456*((1 + 0.5*cos(holdYU))*sin(holdYV)*cos(((1 + 0.5*cos(holdYU))*cos(holdYV)-1.5)*2*PI*0.9/3)-0.5*sin(holdYU)*sin(((1 + 0.5*cos(holdYU))*cos(holdYV)-1.5)*2*PI*0.9/3));
        z = 0.632456*((1 + 0.5*cos(holdZU))*sin(holdZV)*sin(((1 + 0.5*cos(holdZU))*cos(holdZV)-1.5)*2*PI*0.9/3) + 0.5*sin(holdZU)*cos(((1 + 0.5*cos(holdZU))*cos(holdZV)-1.5)*2*PI*0.9/3));
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Hurricane Hurricane;
class TXParaShape_Hurricane :public TXParametricSurfaceBase{
public:
    TXParaShape_Hurricane():TXParametricSurfaceBase(){
        minU = -PI;
        maxU = PI;
        minV = -PI;
        maxV = PI;
        scale = 0.1;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Hurricane
        x = 1*(2*cosh(v/2)*cos(u)*cos((2.1*(2*cosh(v/2)*sin(u)*sin((2*cosh(v/2)*cos(u)-5.01836)*2*PI*0/10.0367) + 2*(v)*cos((2*cosh(v/2)*cos(u)-5.01836)*2*PI*0/10.0367))-13.1947)*2*PI*1.5/26.3894)-2.1*(2*cosh(v/2)*sin(u)*cos((2*cosh(v/2)*cos(u)-5.01836)*2*PI*0/10.0367)-2*(v)*sin((2*cosh(v/2)*cos(u)-5.01836)*2*PI*0/10.0367))*sin((2.1*(2*cosh(v/2)*sin(u)*sin((2*cosh(v/2)*cos(u)-5.01836)*2*PI*0/10.0367) + 2*(v)*cos((2*cosh(v/2)*cos(u)-5.01836)*2*PI*0/10.0367))-13.1947)*2*PI*1.5/26.3894));
        y = 1*(2*cosh(v/2)*cos(u)*sin((2.1*(2*cosh(v/2)*sin(u)*sin((2*cosh(v/2)*cos(u)-5.01836)*2*PI*0/10.0367) + 2*(v)*cos((2*cosh(v/2)*cos(u)-5.01836)*2*PI*0/10.0367))-13.1947)*2*PI*1.5/26.3894) + 2.1*(2*cosh(v/2)*sin(u)*cos((2*cosh(v/2)*cos(u)-5.01836)*2*PI*0/10.0367)-2*(v)*sin((2*cosh(v/2)*cos(u)-5.01836)*2*PI*0/10.0367))*cos((2.1*(2*cosh(v/2)*sin(u)*sin((2*cosh(v/2)*cos(u)-5.01836)*2*PI*0/10.0367) + 2*(v)*cos((2*cosh(v/2)*cos(u)-5.01836)*2*PI*0/10.0367))-13.1947)*2*PI*1.5/26.3894));
        z = 2.1*(2*cosh(v/2)*sin(u)*sin((2*cosh(v/2)*cos(u)-5.01836)*2*PI*0/10.0367) + 2*(v)*cos((2*cosh(v/2)*cos(u)-5.01836)*2*PI*0/10.0367));
        return scaledPoint(x, y, z);
    }
};

 
// TXParaShape_Star5 Star5;
class TXParaShape_Star5 :public TXParametricSurfaceBase{
public:
    TXParaShape_Star5():TXParametricSurfaceBase(){
        minU = -HALF_PI;
        maxU = HALF_PI;
        minV = 0;
        maxV = 2 * PI;
        scale = 1.24;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Star5
        x = cos(u)*cos(v)*pow((pow(abs(cos(1*u/4)), 0.5f)+pow(abs(sin(1*u/4)), 0.5f)), (-1/0.3f))*pow((pow(abs(cos(5*v/4)), 1.7f)+pow(abs(sin(5*v/4)), 1.7f)), (-1/0.1f));
        y = cos(u)*sin(v)*pow((pow(abs(cos(1*u/4)), 0.5f)+pow(abs(sin(1*u/4)), 0.5f)), (-1/0.3f))*pow((pow(abs(cos(5*v/4)), 1.7f)+pow(abs(sin(5*v/4)), 1.7f)), (-1/0.1f));
        z = sin(u)*pow((pow(abs(cos(1*u/4)), 0.5f) +pow(abs(sin(1*u/4)), 0.5f)), (-1/0.3f));
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Seed Seed;
class TXParaShape_Seed :public TXParametricSurfaceBase{
public:
    TXParaShape_Seed():TXParametricSurfaceBase(){
        minU = -HALF_PI;
        maxU = HALF_PI;
        minV = 0;
        maxV = 2 * PI;
        scale = 0.5;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Seed
        x = cos(u)*cos(v)*pow((pow(abs(cos(3*u/4)), 1)+pow(abs(sin(3*u/4)), 1)), (-1))*pow((pow(abs(cos(6*v/4)), 1)+pow(abs(sin(6*v/4)), 30)), (-1));
        y = cos(u)*sin(v)*pow((pow(abs(cos(3*u/4)), 1)+pow(abs(sin(3*u/4)), 1)), (-1))*pow((pow(abs(cos(6*v/4)), 1)+pow(abs(sin(6*v/4)), 30)), (-1));
        z = sin(u)*pow((pow(abs(cos(3*u/4)), 1) +pow(abs(sin(3*u/4)), 1)), (-1));
        return scaledPoint(x, y, z);
    }
};

/* MORE - IF REQUIRED, NEED TO CONVERT: ^ -> pow(xx, yy)

// TXParaShape_Breather Breather;
class TXParaShape_Breather :public TXParametricSurfaceBase{
public:
    TXParaShape_Breather():TXParametricSurfaceBase(){
        minU = -13.2;
        maxU = 13.2;
        minV = -37.4;
        maxV = 37.4;
        scale = 1;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Breather
        x = (2*sqrt(0.84)*cosh(0.4*u)*(-(sqrt(0.84)*cos(v)*cos(sqrt(0.84)*v))-sin(v)*sin(sqrt(0.84)*v)))/(0.4*((sqrt(0.84)*cosh(0.4*u))^2+(0.4*sin(sqrt(0.84)*v))^2));
        y = (2*sqrt(0.84)*cosh(0.4*u)*(-(sqrt(0.84)*sin(v)*cos(sqrt(0.84)*v))+cos(v)*sin(sqrt(0.84)*v)))/(0.4*((sqrt(0.84)*cosh(0.4*u))^2+(0.4*sin(sqrt(0.84)*v))^2));
        z = -u+(2*0.84*cosh(0.4*u)*sinh(0.4*u))/(0.4*((sqrt(0.84)*cosh(0.4*u))^2+(0.4*sin(sqrt(0.84)*v))^2))
        ;
        return scaledPoint(x, y, z);
    }
};


// TXParaShape_RoundedCube RoundedCube;
class TXParaShape_RoundedCube :public TXParametricSurfaceBase{
public:
    TXParaShape_RoundedCube():TXParametricSurfaceBase(){
        minU = -HALF_PI;
        maxU = HALF_PI;
        minV = 0;
        maxV = 2 * PI;
        scale = 1;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // RoundedCube
        x = pow(cos(u)*cos(v)*pow(abs(cos(4*u/4))^100 + abs(sin(4*u/4)),100),-1/100)*pow(pow(abs(cos(4*v/4)),100) + pow(abs(sin(4*v/4)),100),-1/100);
        y = pow(cos(u)*sin(v)*pow(abs(cos(4*u/4))^100 + abs(sin(4*u/4)),100),-1/100)*pow(pow(abs(cos(4*v/4)),100) + pow(abs(sin(4*v/4)),100),-1/100);
        z = sin(u)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100);
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_ RoundedPrism RoundedPrism;
class TXParaShape_RoundedPrism :public TXParametricSurfaceBase{
public:
    TXParaShape_RoundedPrism():TXParametricSurfaceBase(){
        minU = -HALF_PI;
        maxU = HALF_PI;
        minV = 0;
        maxV = 2 * PI;
        scale = 1;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // RoundedPrism
        x = cos(u)*cos(v)*pow((pow(abs(cos(3*v/4)),500) + pow(abs(sin(3*v/4)),500)),-1/260)*pow(pow(abs(cos(4*u/4)),200) + pow(abs(sin(4*u/4)),200)),-1/200);
        y = cos(u)*sin(v)*pow((pow(abs(cos(3*v/4)),500) + pow(abs(sin(3*v/4)),500)),-1/260)*pow(pow(abs(cos(4*u/4)),200) + pow(abs(sin(4*u/4)),200)),-1/200);
        z = sin(u)*(abs(cos(4*u/4))^200 + abs(sin(4*u/4))^200)^(-1/200);
        return scaledPoint(x, y, z);
    }
};

// TXParaShape_Hexagon Hexagon;
class TXParaShape_Hexagon :public TXParametricSurfaceBase{
public:
    TXParaShape_Hexagon():TXParametricSurfaceBase(){
        minU = -HALF_PI;
        maxU = HALF_PI;
        minV = 0;
        maxV = 2 * PI;
        scale = 1;
    }
    ofPoint valueForPoint(float u,float v){
        float x, y, z;
        // Hexagon
        x = cos(u)*cos(v)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)*(abs(cos(6*v/4))^400 + abs(sin(6*v/4))^400)^(-1/1000);
        y = cos(u)*sin(v)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)*(abs(cos(6*v/4))^400 + abs(sin(6*v/4))^400)^(-1/1000);
        z = sin(u)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300);
        return scaledPoint(x, y, z);
    }
};

*/


