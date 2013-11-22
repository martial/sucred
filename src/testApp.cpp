#include "testApp.h"
#include "ofxSosoRenderer.h"
#include "Globals.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetLogLevel(OF_LOG_NOTICE);
    ofSetFrameRate(60);
    ofSetCircleResolution(92);
    
    
    /* Globals */
    
    Globals::instance()->app                = this;
    Globals::instance()->eq                 = &eq;
    Globals::instance()->sceneManager       = &sceneManager;
    Globals::instance()->gui                = &gui;
    Globals::instance()->data               = &dataManager;
    Globals::instance()->animData           = &animDataManager;
    Globals::instance()->animatorManager    = &animatorManager;
    //Globals::instance()->mainAnimator       = &mainAnimator;
    //Globals::instance()->previewAnimator    = &previewAnimator;
    Globals::instance()->colorManager       = &colorManager;
    Globals::instance()->effectsManager     = &effectsManager;
    Globals::instance()->alertManager       = &alertManager;
    
    
    
    /* EQ */
    ofSoundStreamSetup(0,2,this, 44100, 512, 4);
    eq.setup();
    eq.setRange(16);
    eq.smooth = .999;
    
    
    /* main animator */
    
    animatorManager.setup();
    animatorManager.addAnimator(); // main
    animatorManager.addAnimator(); // preview edit
    animatorManager.addAnimator(); // preview live
    animatorManager.addAnimator(); // overlay live
    
    /* gui */
    gui.setup();
    
    alertManager.setup();

    sceneManager.setup();
    
    colorManager.setLightObjects(sceneManager.getScene(0)->getLightObjects());
    
    //gui.editorInspectorGui->addFbo("preview", &Globals::instance()->sceneManager->getScene(3)->fbo);
    
    
    /* Data */
    dataManager.setup();
    animDataManager.setup();
    
    
    dataManager.assignData(sceneManager.getScene(0)->getLightObjects());
    
    effectsManager.setup(sceneManager.getScene(0)->getLightObjects());
    
   

    Animator * mainAnimator     = animatorManager.getAnimator(0);
    Animator * previewAnimator  = animatorManager.getAnimator(1);
    Animator * overlayAnimator  = animatorManager.getAnimator(2);
    previewAnimator->play();
    overlayAnimator->play();
    
    // events for gui, and frames
    ofAddListener(mainAnimator->tickEvent, &sceneManager, &SceneManager::updateEditorFrames);
    ofAddListener(mainAnimator->tickEvent, gui.editorInspectorGui, &EditorInspectorGui::onFrameEvent);

    
    ofAddListener(previewAnimator->tickEvent, &sceneManager, &SceneManager::updatePreviewFrames);
    ofAddListener(overlayAnimator->tickEvent, &sceneManager, &SceneManager::updateOverlayFrames);

    
    ofAddListener(animDataManager.resetEvent, mainAnimator, &Animator::onResetHandler );
    ofAddListener(animDataManager.updateEvent, mainAnimator, &Animator::onUpdateHandler );
    
    
    //defaultRenderer = ofPtr<ofBaseRenderer>(new ofGLRenderer(false));
    sosoRenderer =ofPtr<ofBaseRenderer>(new ofxSosoRenderer(false));
    
    

    
    
    dmxManager.setup(&sceneManager.getScene(0)->lightObjects);
    
    
    gui.loadSettings();
    
    
    setMode (MODE_EDITOR);
    alertManager.addSimpleAlert("HELLO LE SUCRE !", 1000);
	
    
}

//--------------------------------------------------------------
void testApp::setMode(int mode){
    
    this->mode = mode;
    gui.setMode(mode);
    sceneManager.setMode(mode);
    sceneManager.getScene(0)->setMode(mode);
    
    
    if(mode == MODE_LIVE) {
        animatorManager.getAnimator(0)->play();
        
    }
    else {
        
        animatorManager.getAnimator(0)->stop();
        
    }
    
    if (mode == MODE_EDITOR) {
        //animDataManager.saveCurrentAnimation();
        effectsManager.disableAll();
    }
    
    // reset colors
    colorManager.resetColors();
    colorManager.setGlobalColor(ofColor(255,255,255), 255);
    

}

//--------------------------------------------------------------

void testApp::onFrameEvent(int & e) {
    
}


//--------------------------------------------------------------
void testApp::update(){
    
    alertManager.update();
    
    animatorManager.update();
    
    
    sceneManager.update();
    
    effectsManager.update();
    
    dmxManager.update();
    
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
    
    // test to draw preview
    
    ofPushMatrix();
    ofTranslate((int)(ofGetWidth()/3), (int)(ofGetHeight()/3 + ( ofGetHeight() / 3 / 4 ) - ofGetHeight() * .5));
    ofRectangle rect = sceneManager.getScene(0)->bBox;
    ofSetColor(255,255,255,255);
    sceneManager.getScene(3)->fbo.draw(-(int)(ofGetWidth() / 3 / 4), 0.0, (int)(ofGetWidth() / 3), (int)(ofGetHeight() / 3) );
    sceneManager.getScene(4)->fbo.draw((int)(ofGetWidth() / 3 / 4), 0.0, (int)(ofGetWidth() / 3), (int)(ofGetHeight() / 3) );
    ofPopMatrix();
    
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight() / 2);
    
    sceneManager.getScene(0)->drawOutput();
    
    
    ofPopMatrix();
   
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
    gui.save();
    // reset
    
    dmxManager.reset(&sceneManager.getScene(0)->lightObjects);
}


