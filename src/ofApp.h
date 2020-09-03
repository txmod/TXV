#pragma once


/*  ///////////////////////////
 
 NOTE OF HACKS IN OPENFRAMEWORKS & OFXADDONS
 
 - ofxSVG - extra method added: ofxSVG::clear():
 - in ofxSvg.h:
 void clear();  // added  by paul
 - in ofxSvg.cpp:
 // added  by paul:
 void ofxSVG::clear(){
     paths.clear();
 }
 
  - ofxVideoRecorder - made small changes to:
 bool ofxVideoRecorder::setup(string fname, int w, int h, float fps, int sampleRate, int channels)
 - because ffmpeg reported errors
 
 - ofxMathMesh - changes to ofxParametricSurface.cpp (search for paul):
 // HACK NOTE: ofxParametricSurface::setup() in addon ofxMathMesh
 // clear statments added by paul before call to loadDomainPoints() so that setup can be called multiple times
 uDomainPoints.clear();
 vDomainPoints.clear();
 // END OF HACK
 
 - changes to ofxOrnament - files Ornament.h/cpp  (search for paul):
 - Note: there are various changes in order to add zoomX/Y, shiftX/Y & rotate

 ///////////////// OLDER OUT OF DATE CHANGES - IGNORE THESE: ////
 
 //// NOTE - THE FOLLOWING IS OLD -
 - made changes to: ofGraphics.cpp, method:
 void ofRectRounded(float x, float y, float z, float w, float h, float topLeftRadius, float topRightRadius, float bottomRightRadius, float bottomLeftRadius) {
 // next line added by paul
 shape.setCircleResolution(currentStyle.circleResolution);
 //// END OF OLD
 
 
 //// NOTE - THE FOLLOWING IS OLD -
 - changed ofxAssimpModelLoader3.0/ofxAssimpUtils.h,  method aiMeshToOfMesh(...)
 removing the last line which doesn't compile since ofMesh doesn't have .setName:
 //ofm.setName(string(aim->mName.data));
 //// END OF OLD
 
// NOTE - THE FOLLOWING IS OLD - ofxBullet NOT USED NOW
 - change to incorrect method in ofxBulletSoftBody:
 void ofxBulletSoftBody::setDynamicFriction(float v) {
 v = ofClamp(v, 0, 1);
 // amended by PAUL
 //_softBody->m_cfg.kVC = v;
 _softBody->m_cfg.kDF = v;
 }
 
 // NOTE - THE FOLLOWING IS OLD - ofxLeapMotion NOT USED NOW AS NOT WORKING IN OF 0.9.8
 - changes for leap motion - from https://github.com/ofTheo/ofxLeapMotion
 "On OS X, you must have this in the Run Script Build Phase of your Xcode project. where the first path ../../../addons/ofxLeapMotion/ is the path to the ofxLeapMotion addon:"
 cp -f ../../../addons/ofxLeapMotion/libs/lib/osx/libLeap.dylib "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/libLeap.dylib"; install_name_tool -change ./libLeap.dylib @executable_path/libLeap.dylib "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/$PRODUCT_NAME";
 "If you don't have this you'll see an error in the console: dyld: Library not loaded: @loader_path/libLeap.dylib"
 
 ///////////////////////////
 */

#include "ofMain.h"

#include "TXMain.h"
#include "TXSystem.h"

//#include "ofxGui.h"
//#include "ofxOscParameterSync.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    // properties
    
    TXSystem system;
    
    // NOT CURRENTLY USED:
    //    ofParameterGroup parameters;
    //    ofxPanel gui;
    //    ofxOscParameterSync sync;
    
protected:
    ofWindowMode mode;
};


