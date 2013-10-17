#include "testApp.h"
#include "ofxSosoRenderer.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetLogLevel(OF_LOG_NOTICE);
    ofSetFrameRate(60);
    
    
    /* Globals */
    
    Globals::instance()->eq = &eq;
    Globals::instance()->scene = &scene;
    
    /* EQ */
    ofSoundStreamSetup(0,2,this, 44100, 512, 4);
    eq.setup();
    eq.setRange(16);
    eq.smooth = .999;
    
    scene.setup();
    
    
    /* gui */
    gui.setup();
    
    //defaultRenderer = ofPtr<ofBaseRenderer>(new ofGLRenderer(false));
    sosoRenderer =ofPtr<ofBaseRenderer>(new ofxSosoRenderer(false));

}

//--------------------------------------------------------------
void testApp::update(){
    
    scene.update();
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
     //ofLoadIdentityMatrix();
    
    

    
    
    
    ofPushMatrix();
    
    ofSetCurrentRenderer(sosoRenderer);
    scene.draw();
    ofPopMatrix();
    
    
    //ofSetCurrentRenderer(defaultRenderer, true);
    ofGetCurrentRenderer()->setupScreenPerspective();


    //ofB
    
    //eq.debugDraw();
    

}


//--------------------------------------------------------------
void testApp::audioReceived (float * input, int bufferSize, int nChannels){
	
	eq.audioReceived(input, bufferSize);
    
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
