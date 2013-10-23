#include "testApp.h"
#include "ofxSosoRenderer.h"
#include "Globals.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetLogLevel(OF_LOG_NOTICE);
    ofSetFrameRate(60);
    
    
    /* Globals */
    
    Globals::instance()->app            = this;
    Globals::instance()->eq             = &eq;
    Globals::instance()->sceneManager   = &sceneManager;
    Globals::instance()->gui            = &gui;
    Globals::instance()->data           = &dataManager;
    Globals::instance()->animData       = &animDataManager;
    Globals::instance()->mainAnimator   = &mainAnimator;

    /* gui */
    gui.setup();

    sceneManager.setup();
    
    
    /* Data */
    dataManager.setup();
    animDataManager.setup();
    
    
    /* EQ */
    ofSoundStreamSetup(0,2,this, 44100, 512, 4);
    eq.setup();
    eq.setRange(16);
    eq.smooth = .999;
    
    
    
    
    
    
    /* main animator */
    mainAnimator.setup(sceneManager.getScene(0));
    ofAddListener(mainAnimator.tickEvent, this, &testApp::onFrameEvent);
    ofAddListener(mainAnimator.tickEvent, gui.editorInspectorGui, &EditorInspectorGui::onFrameEvent);
    
    //defaultRenderer = ofPtr<ofBaseRenderer>(new ofGLRenderer(false));
    sosoRenderer =ofPtr<ofBaseRenderer>(new ofxSosoRenderer(false));
    
    
    ofSetCircleResolution(92);
    
    setMode (MODE_EDITOR);
}

//--------------------------------------------------------------
void testApp::setMode(int mode){
    
    this->mode = mode;
    gui.setMode(mode);
    sceneManager.setMode(mode);
    sceneManager.getScene(0)->setMode(mode);
}

//--------------------------------------------------------------

void testApp::onFrameEvent(int & e) {
    
    // what is going on frame event
    
    
    if (mode == MODE_EDITOR) {
        animDataManager.pushFrame();
        sceneManager.updateEditorFrames();
    }
    
}


//--------------------------------------------------------------
void testApp::update(){
    
    mainAnimator.update();
    sceneManager.update();

    
    
}

//--------------------------------------------------------------
void testApp::draw(){

    
    ofPushMatrix();
    
    ofSetCurrentRenderer(sosoRenderer);
    
    float bgBrightness = 0.1;
    
    glClearColor(bgBrightness,bgBrightness,bgBrightness,bgBrightness);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    ofSetColor(255,255,255,255);
    
    sceneManager.draw();
    ofPopMatrix();

    
    ofGetCurrentRenderer()->setupScreenPerspective();
    
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    sceneManager.drawFbos();
   
    gui.draw();


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
