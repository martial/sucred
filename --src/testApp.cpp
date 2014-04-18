#include "testApp.h"
#include "ofxSosoRenderer.h"
#include "Globals.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetLogLevel(OF_LOG_NOTICE);
    ofSetFrameRate(120);
    //ofSetCircleResolution(92);
    
    
    /* Globals */
    
    Globals::get()->app                = this;
    Globals::get()->eq                 = &eq;
    Globals::get()->sceneManager       = &sceneManager;
    Globals::get()->gui                = &gui;
    Globals::get()->data               = &dataManager;
    Globals::get()->animData           = &animDataManager;
    Globals::get()->animatorManager    = &animatorManager;
    Globals::get()->colorManager       = &colorManager;
    Globals::get()->effectsManager     = &effectsManager;
    Globals::get()->alertManager       = &alertManager;
    Globals::get()->dmxManager         = &dmxManager;
    
    
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
    
    autoMode.setup();
    autoMode.setEnabled(false);
    
    /* gui */
    gui.setup();
    
    alertManager.setup();

    sceneManager.setup();
    
    colorManager.setLightObjects(sceneManager.getScene(3)->getLightObjects());
    
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
    overlayAnimator->setAnimation(NULL);
    
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
    
    mpdManager.setup();
    
    //scene evebt
    
    ofAddListener(sceneManager.sceneChanged, this, &testApp::onSceneChanged);
    
    
    setMode (MODE_EDITOR);
    //alertManager.addSimpleAlert("HELLO LE SUCRE !", 1000);
	
    
}

//--------------------------------------------------------------
void testApp::setMode(int mode){
    
    this->mode = mode;
    gui.setMode(mode);
    sceneManager.setMode(mode);
    sceneManager.getScene(0)->setMode(mode);
    
    
    if(mode == MODE_LIVE) {
        animatorManager.getAnimator(0)->play();
        sceneManager.getScene(0)->setStatic(true);
    }
    else {
        
        autoMode.setEnabled(false);
        gui.inspectorGui->autoModeToggle->setValue(false);
        
        animatorManager.getAnimator(0)->stop();
        
        
    }
    
    if (mode == MODE_EDITOR) {
        //animDataManager.saveCurrentAnimation();
        effectsManager.disableAll();
        sceneManager.getScene(0)->setStatic(false);
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
    
    autoMode.update();
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
    
    
    if(mode == MODE_LIVE) {

        sceneManager.getScene(3)->drawOutput();
        sceneManager.getScene(4)->drawOutput();
    
        fboMerger.process(&sceneManager.getScene(3)->outputFbo, &sceneManager.getScene(4)->outputFbo);
        fboMerger.apply(sceneManager.getScene(0));
        effectsManager.applyFilters();
        effectsManager.run();
    
    }
    
    // process fbos's
    sceneManager.draw();
    
    ofPopMatrix();
    
    ofGetCurrentRenderer()->setupScreenPerspective();
    ofSetupGraphicDefaults();
    
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
    
    sceneManager.drawFbos();
    
    if(mode == MODE_LIVE)
        sceneManager.drawPreviews();
    // test to draw preview
       
    
  
   
    gui.draw();
    
    alertManager.draw();
    


    
}


//--------------------------------------------------------------
void testApp::audioReceived (float * input, int bufferSize, int nChannels){
	
	eq.audioReceived(input, bufferSize);
    
}

void testApp::onSceneChanged(int & sceneIndex) {
    
    // update Anim GUI
    // get current animation and update
    AnimationDataObject * anim;
    ofColor color;
    int colorSchemeID;
    
    if ( sceneIndex == 3) {
        anim = animatorManager.getAnimator(1)->anim;
        color = sceneManager.getScene(3)->getLightObjects()[0]->color;
        colorSchemeID = sceneManager.getScene(3)->colorSchemeId;
    }
    
    if ( sceneIndex == 4) {
        anim = animatorManager.getAnimator(2)->anim;
        color = sceneManager.getScene(4)->getLightObjects()[0]->color;
        colorSchemeID = sceneManager.getScene(4)->colorSchemeId;
    }
    
    if(!anim)
        gui.animPickerGui->selectToggle( -999);
    else
        gui.animPickerGui->selectToggle(anim->id);
    
    // update colors too
    
    gui.liveGui->r = color.r;
    gui.liveGui->g = color.g;
    gui.liveGui->b = color.b;
    
    // update color scheme
    // at some point we'll need to store it somewhere
    // maybe in scene directly ? 
    
    gui.colorPickerGui->selectToggle(colorSchemeID);
    
    
    
}



//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    
    if(key == 'p') {
        
        dmxManager.reset(dmxManager.lights);
        dmxManager.reset(dmxManager.lights);

        dmxManager.reset(dmxManager.lights);

        dmxManager.reset(dmxManager.lights);

        dmxManager.reset(dmxManager.lights);

        dmxManager.hasShutdown = true;
        dmxManager.disconnect();
    }

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
    
    dmxManager.reset(dmxManager.lights);
    dmxManager.reset(dmxManager.lights);
    
    dmxManager.reset(dmxManager.lights);
    
    dmxManager.reset(dmxManager.lights);
    
    dmxManager.reset(dmxManager.lights);
    
    dmxManager.hasShutdown = true;
    dmxManager.disconnect();
    
    ofLog(OF_LOG_NOTICE, "adios");
}


