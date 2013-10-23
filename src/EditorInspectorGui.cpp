//
//  EditorInspectorGUi.cpp
//  Sucre
//
//  Created by Martial on 21/10/13.
//
//

#include "EditorInspectorGui.h"
#include "Globals.h"

void EditorInspectorGui::populate () {
    
    setDrawBack(true);
    setAutoDraw(false);
    
    addSpacer();
    addTextArea("INSPECTOR", "INSPECTOR", OFX_UI_FONT_LARGE);
    addSpacer();
    
    urlText     = addTextArea("URL", "...", OFX_UI_FONT_SMALL);
    frameText   = addTextArea("FRAME", "FRAME : 1/1");
    
    addButton("+ ADD FRAME", false);
    
    addSpacer();
    addButton("PREV FRAME", false);
    addButton("NEXT FRAME", false);
    
    addSpacer();
    
    addButton("PLAY", false);
    addButton("STOP", false);


    
    ofAddListener(newGUIEvent,this,&EditorInspectorGui::onGuiEvent);
}

void EditorInspectorGui::setUrl(string url) {
    
    urlText->setTextString(url);
}

void EditorInspectorGui::setFrame(int frame, int total) {
    
    frameText->setTextString(ofToString(frame) + "/" + ofToString(total));
    
}

void EditorInspectorGui::hide() {
    bEnabled = false;
    tween.setParameters(1,easingquint,ofxTween::easeOut, rect->x, ofGetWidth(),300, 0);
}

void EditorInspectorGui::show () {
    bEnabled = true;
    tween.setParameters(1,easingquint,ofxTween::easeOut, rect->x, ofGetWidth() - rect->width,300, 0);
    
}



void EditorInspectorGui::draw() {
    
    // position right
    rect->height = ofGetHeight();
    
    float xPos = ( tween.isRunning()) ? tween.update() : ( bEnabled ) ? ofGetWidth() - rect->width : ofGetWidth();
    
    setPosition(xPos, 0);
    ofxUICanvas::draw();
    
    
}

void EditorInspectorGui::onGuiEvent(ofxUIEventArgs & e) {
    
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
    Scene * mainScene = Globals::instance()->sceneManager->getScene(0);
    Scene * prevScene = Globals::instance()->sceneManager->getScene(1);
    Scene * nextScene = Globals::instance()->sceneManager->getScene(2);
    
    if( name =="+ ADD FRAME") {
        
        Globals::instance()->animData->addFrame();
        setFrame(Globals::instance()->animData->currentFrame + 1, Globals::instance()->animData->currentAnimation->getNumFrames());
        mainScene->setSelecteds(Globals::instance()->animData->getCurrentFrame());
        
    }
    
    if( name =="PREV FRAME") {
        
        Globals::instance()->animData->popFrame();
        Globals::instance()->sceneManager->updateEditorFrames();
        
        
        setFrame(Globals::instance()->animData->currentFrame + 1, Globals::instance()->animData->currentAnimation->getNumFrames());
        
        //setFrame(Globals::instance()->animData->currentFrame + 1, Globals::instance()->animData->currentAnimation->getNumFrames());
        
    }
    
    if( name =="NEXT FRAME") {
        
        Globals::instance()->animData->pushFrame();
        Globals::instance()->sceneManager->updateEditorFrames();
        setFrame(Globals::instance()->animData->currentFrame + 1, Globals::instance()->animData->currentAnimation->getNumFrames());
        
        //setFrame(Globals::instance()->animData->currentFrame + 1, Globals::instance()->animData->currentAnimation->getNumFrames());
        
    }
    
    if( name =="PLAY") {
        
        Globals::instance()->mainAnimator->play();
        
        //setFrame(Globals::instance()->animData->currentFrame + 1, Globals::instance()->animData->currentAnimation->getNumFrames());
        
    }
    
    if( name =="STOP") {
        
        Globals::instance()->mainAnimator->stop();
        
        //setFrame(Globals::instance()->animData->currentFrame + 1, Globals::instance()->animData->currentAnimation->getNumFrames());
        
    }
    
    
}

void EditorInspectorGui::onFrameEvent(int &e ) {
    
    setFrame(Globals::instance()->animData->currentFrame + 1, Globals::instance()->animData->currentAnimation->getNumFrames());

}