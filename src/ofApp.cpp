#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // setup ofLog()
    // ofLog::setAutoSpace(true);
    ofLog::setAutoSpace(false);

#if defined(_DEBUG)
    //ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetLogLevel(OF_LOG_NOTICE);
    //    ofSetLogLevel(OF_LOG_WARNING);
    ofLogVerbose() << "ofLogVerbose() - test print line";
    ofLogNotice() << "ofLogNotice() - test print line";
    ofLogWarning() << "ofLogWarning() - test print line";
#else
    ofSetLogLevel(OF_LOG_ERROR);
#endif  
    
    // of init
    ofSetCircleResolution(400);
    ofSetVerticalSync(true);
    
    ofSetEscapeQuitsApp(true);

    //ofSetTextureWrap(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
    // choices: GL_MIRRORED_REPEAT GL_CLAMP_TO_EDGE GL_REPEAT
    
    //ofSetFrameRate(60);
    
    system.setup();
    
    //    parameters.setName("TX_Modular_System");
    //    parameters.add(system.parameters);
    //    gui.setup(parameters);
    //    sync.setup((ofParameterGroup&)gui.getParameter(), localPort, host, remotePort);
}

//--------------------------------------------------------------
void ofApp::update(){
    //    sync.update();
    system.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    system.draw();
    //    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // report to system
    system.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
 
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    // report to system
    system.mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    // report to system
    system.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // report to system
    system.mousePressed(x, y, button); 
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    // report to system
    system.mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    // report to system
    system.windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

