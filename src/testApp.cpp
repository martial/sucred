#include "testApp.h"
#include "ofxSosoRenderer.h"
#include "Globals.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetLogLevel(OF_LOG_NOTICE);
    ofSetFrameRate(60);
    
    
    /* Globals */
    
    Globals::instance()->app                = this;
    Globals::instance()->eq                 = &eq;
    Globals::instance()->sceneManager       = &sceneManager;
    Globals::instance()->gui                = &gui;
    Globals::instance()->data               = &dataManager;
    Globals::instance()->animData           = &animDataManager;
    Globals::instance()->mainAnimator       = &mainAnimator;
    Globals::instance()->previewAnimator    = &previewAnimator;
    Globals::instance()->colorManager       = &colorManager;
    Globals::instance()->effectsManager     = &effectsManager;
    Globals::instance()->alertManager       = &alertManager;
    
    dmxManager.setup();
    
    /* EQ */
    ofSoundStreamSetup(0,2,this, 44100, 512, 4);
    eq.setup();
    eq.setRange(16);
    eq.smooth = .999;
    
    
    
    /* gui */
    gui.setup();
    
    alertManager.setup();

    sceneManager.setup();
    
    colorManager.setLightObjects(sceneManager.getScene(0)->getLightObjects());
    
    gui.editorInspectorGui->addFbo("preview", &Globals::instance()->sceneManager->getScene(3)->fbo);
    
    
    /* Data */
    dataManager.setup();
    animDataManager.setup();
    
    
    dataManager.assignData(sceneManager.getScene(0)->getLightObjects());
    
    effectsManager.setup(sceneManager.getScene(0)->getLightObjects());
    
   
    
    /* main animator */
    mainAnimator.setup(sceneManager.getScene(0));
    previewAnimator.setup(sceneManager.getScene(3));
    previewAnimator.play();
    
    ofAddListener(mainAnimator.tickEvent, this, &testApp::onFrameEvent);
    
    ofAddListener(previewAnimator.tickEvent, &sceneManager, &SceneManager::updatePreviewFrames);
    
    ofAddListener(mainAnimator.tickEvent, gui.editorInspectorGui, &EditorInspectorGui::onFrameEvent);
    
    ofAddListener(animDataManager.resetEvent, &mainAnimator, &Animator::onResetHandler );
    ofAddListener(animDataManager.updateEvent, &mainAnimator, &Animator::onUpdateHandler );
    
    //defaultRenderer = ofPtr<ofBaseRenderer>(new ofGLRenderer(false));
    sosoRenderer =ofPtr<ofBaseRenderer>(new ofxSosoRenderer(false));
    
    ofSetCircleResolution(92);
    
    setMode (MODE_EDITOR);
    
    /*
     
     test httputils
     
    
    
    ofAddListener(httpUtils.newResponseEvent,this,&testApp::newResponse);

    httpUtils.start();
    
    
    ofxHttpForm form;
	form.action = "http://localhost:8888/sucre/";
	form.method = OFX_HTTP_POST;
	form.addFile("file","anims/fuck.xml");
	httpUtils.addForm(form);
     
     */
    
    alertManager.addSimpleAlert("HELLO LE SUCRE !", 1000);
	
    
}

//--------------------------------------------------------------
void testApp::setMode(int mode){
    
    this->mode = mode;
    gui.setMode(mode);
    sceneManager.setMode(mode);
    sceneManager.getScene(0)->setMode(mode);
    
    
    if(mode == MODE_LIVE) {
        mainAnimator.play();
    }
    else {
        
        mainAnimator.stop();
        
    }
    
    if (mode == MODE_EDITOR) {
        animDataManager.saveCurrentAnimation();
    }
    
    // reset colors
    colorManager.resetColors();
    colorManager.setGlobalColor(ofColor(255,255,255));
    

}

//--------------------------------------------------------------

void testApp::onFrameEvent(int & e) {
    
    // what is going on frame event
    
    
    if (mode == MODE_EDITOR || mode == MODE_LIVE) {
        //animDataManager.pushFrame();
        sceneManager.updateEditorFrames();
    }
    
}


//--------------------------------------------------------------
void testApp::update(){
    
    alertManager.update();
    
    mainAnimator.update();
    previewAnimator.update();
    sceneManager.update();
    
    effectsManager.update();
    
    dmxManager.update(&sceneManager.getScene(0)->lightObjects);
    
    //ofLog(OF_LOG_NOTICE, "current id %d" , animDataManager.currentAnimation->id);
    //ofLog(OF_LOG_NOTICE, animDataManager.currentAnimation->name);
    
}

//--------------------------------------------------------------
void testApp::draw(){

    
    ofPushMatrix();
    
    ofSetCurrentRenderer(sosoRenderer);
    
    ofBackground(34);
    
    ofSetColor(255,255,255,255);
    
    sceneManager.draw();
    ofPopMatrix();

    
    ofGetCurrentRenderer()->setupScreenPerspective();
    ofSetupGraphicDefaults();
    
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    sceneManager.drawFbos();
   
    gui.draw();
    
    alertManager.draw();
    
    

    
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

void testApp::exit(){
    
    //animDataManager.saveCurrentAnimation();
}


