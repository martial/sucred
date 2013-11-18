//
//  EditorInspectorGUi.cpp
//  Sucre
//
//  Created by Martial on 21/10/13.
//
//

#include "EditorInspectorGui.h"
#include "Globals.h"
#include "ofxModifierKeys.h"

void EditorInspectorGui::populate () {
    
    setDrawBack(true);
    setAutoDraw(false);
    
    //addSpacer();
    addTextArea("INSPECTOR", "INSPECTOR", OFX_UI_FONT_LARGE);
    addSpacer();
    
    urlText     = addTextInput("URL", "...", OFX_UI_FONT_SMALL);
    frameText   = addTextArea("FRAME", "FRAME : 1/1");
    
    addSpacer();
    addLabelButton("ADD FRAME", false, true);
    addLabelButton("DELETE FRAME", false, true);
    addLabelButton("PREV FRAME", false, true);
    addLabelButton("NEXT FRAME", false, true);
    
    addSpacer();
    addTextArea("PLAYER", "PLAYER", OFX_UI_FONT_LARGE);
    addSpacer();
    playBtn = addToggle("PLAY", &Globals::instance()->mainAnimator->bIsPlaying);
    //stopBtn = addToggle("STOP", true);
    //addSpacer();
    speedSlider = addSlider("SPEED", 1.0, 0.0, 0.0);
    addSpacer();
    addLabelButton("HIDE/SHOW LIST", false, true);
    
    
    
    
    ofAddListener(newGUIEvent,this,&EditorInspectorGui::onGuiEvent);
    
    ofAddListener(ofEvents().keyPressed, this, &EditorInspectorGui::keyPressed);
}

void EditorInspectorGui::setUrl(string url) {
    
    urlText->setTextString(url);
}

void EditorInspectorGui::setFrame(int frame, int total) {
    
    frameText->setTextString("FRAME : " + ofToString(frame) + "/" + ofToString(total));
    
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
    
    Scene * mainScene       = Globals::instance()->sceneManager->getScene(0);
    Scene * prevScene       = Globals::instance()->sceneManager->getScene(1);
    Scene * nextScene       = Globals::instance()->sceneManager->getScene(2);
    Animator * mainAnimator = Globals::instance()->mainAnimator;
    
    if( name =="ADD FRAME") {
        
        addFrame();
        
    }
    
    if( name =="DELETE FRAME") {
        
        Globals::instance()->animData->deleteFrame(mainAnimator->currentFrame);
        setFrame(mainAnimator->currentFrame + 1, Globals::instance()->animData->currentAnimation->getNumFrames());
        //mainScene->setSelecteds(Globals::instance()->animData->getFrame(mainAnimator->currentFrame));
        
    }
    
    
    if( name =="PREV FRAME") {
        
        prevFrame();
        
        
    }
    
    if( name =="NEXT FRAME") {
        
        nextFrame();
        
    }
    
    if( name =="PLAY") {
        
        if(playBtn->getValue())
            Globals::instance()->mainAnimator->play();
        else
            Globals::instance()->mainAnimator->stop();

        //playBtn->setValue(true);
        //stopBtn->setValue(false);
        //setFrame(Globals::instance()->animData->currentFrame + 1, Globals::instance()->animData->currentAnimation->getNumFrames());
        
    }
    
    if( name =="STOP") {
        
        Globals::instance()->mainAnimator->stop();
        //playBtn->setValue(false);
       // stopBtn->setValue(true);
        //setFrame(Globals::instance()->animData->currentFrame + 1, Globals::instance()->animData->currentAnimation->getNumFrames());
        
    }
    
    if (name == "HIDE/SHOW LIST") {
        
        AnimationPickerGui * list = Globals::instance()->gui->animPickerGui;
        
        if(list->bEnabled)
            Globals::instance()->gui->animPickerGui->hide();
        else
            Globals::instance()->gui->animPickerGui->show();

    }
    
    if (name == "URL") {
        
        
        Globals::instance()->animData->currentAnimation->rename(urlText->getTextString());
        Globals::instance()->gui->animPickerGui->renameToggle(Globals::instance()->animData->currentAnimation->id, urlText->getTextString());
    }
    
    if(name == "SPEED") {
        
        Globals::instance()->mainAnimator->speedPct = speedSlider->getValue();
        Globals::instance()->previewAnimator->speedPct = speedSlider->getValue();
        
    }
    
    
}

void EditorInspectorGui::onFrameEvent(int &e ) {
    
    Animator * mainAnimator = Globals::instance()->mainAnimator;

    setFrame(mainAnimator->currentFrame + 1, Globals::instance()->animData->currentAnimation->getNumFrames());


}

void EditorInspectorGui::keyPressed(ofKeyEventArgs & key) {
    
    
    if(urlText->isClicked())
        return;
    
    if(key.key == OF_KEY_RIGHT) {
        nextFrame();
        
    }
    
    if(key.key == OF_KEY_LEFT) {
        prevFrame();
    }
    
    if(key.key == ' ') {
        
        
        playBtn->toggleValue();
        
        if(playBtn->getValue())
            Globals::instance()->mainAnimator->play();
        else
            Globals::instance()->mainAnimator->stop();
        
    }

    
    
    if(key.key == 'a' || key.key == 'A' ) {
        addFrame();
    }
    
    
}



void EditorInspectorGui::addFrame () {
    
    
    Scene * mainScene       = Globals::instance()->sceneManager->getScene(0);
    Scene * prevScene       = Globals::instance()->sceneManager->getScene(1);
    Scene * nextScene       = Globals::instance()->sceneManager->getScene(2);
    Animator * mainAnimator = Globals::instance()->mainAnimator;
    
    Globals::instance()->animData->addFrame(mainAnimator->currentFrame, ofGetModifierPressed(OF_KEY_SHIFT));
    setFrame(mainAnimator->currentFrame + 1, Globals::instance()->animData->currentAnimation->getNumFrames());
    Globals::instance()->sceneManager->updateEditorFrames();

    
}

void EditorInspectorGui::prevFrame() {
    
    Animator * mainAnimator = Globals::instance()->mainAnimator;

    mainAnimator->popFrame();
    setFrame(mainAnimator->currentFrame + 1, Globals::instance()->animData->currentAnimation->getNumFrames());
    Globals::instance()->sceneManager->updateEditorFrames();

    
}

void EditorInspectorGui::nextFrame() {
    
    Animator * mainAnimator = Globals::instance()->mainAnimator;

    mainAnimator->pushFrame();
    setFrame(mainAnimator->currentFrame + 1, Globals::instance()->animData->currentAnimation->getNumFrames());
    Globals::instance()->sceneManager->updateEditorFrames();
}