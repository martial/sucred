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
    playBtn = addToggle("PLAY", &Globals::get()->animatorManager->getAnimator(0)->bIsPlaying);
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
    
    Animator * mainAnimator = Globals::get()->animatorManager->getAnimator(0);
    Animator * previewAnimator = Globals::get()->animatorManager->getAnimator(1);
    
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
            mainAnimator->play();
        else
            mainAnimator->stop();

    }
    
    if( name =="STOP") {
        
        mainAnimator->stop();
        
    }
    
    if (name == "HIDE/SHOW LIST") {
        
        AnimationPickerGui * list = Globals::instance()->gui->animPickerGui;
        
        if(list->bEnabled)
            Globals::get()->gui->animPickerGui->hide();
        else
            Globals::get()->gui->animPickerGui->show();

    }
    
    if (name == "URL") {
        
        
        Globals::get()->animData->currentAnimation->rename(urlText->getTextString());
        Globals::get()->gui->animPickerGui->renameToggle(Globals::instance()->animData->currentAnimation->id, urlText->getTextString());
    }
    
    if(name == "SPEED") {
        
       mainAnimator->speedPct = speedSlider->getValue();
       previewAnimator->speedPct = speedSlider->getValue();
        
        Globals::get()->animData->currentAnimation->speed = speedSlider->getValue();
        
    }
    
    
}

void EditorInspectorGui::onFrameEvent(int &e ) {
    
    Animator * mainAnimator = Globals::get()->animatorManager->getAnimator(0);
    setFrame(mainAnimator->currentFrame + 1, Globals::get()->animData->currentAnimation->getNumFrames());


}

void EditorInspectorGui::keyPressed(ofKeyEventArgs & key) {
    
    
    if(urlText->isClicked() || Globals::instance()->app->mode != MODE_EDITOR)
        return;
    
    if(key.key == OF_KEY_RIGHT) {
        nextFrame();
        
    }
    
    if(key.key == OF_KEY_LEFT) {
        prevFrame();
    }
    
    if(key.key == ' ') {
        
        
        playBtn->toggleValue();
        
        Animator * mainAnimator = Globals::get()->animatorManager->getAnimator(0);

        
        if(playBtn->getValue())
            mainAnimator->play();
        else
            mainAnimator->stop();
        
    }

    
    
    if(key.key == 'a' || key.key == 'A' ) {
        addFrame();
    }
    
    
}



void EditorInspectorGui::addFrame () {
    
    
    Scene * mainScene       = Globals::get()->sceneManager->getScene(0);
    Scene * prevScene       = Globals::get()->sceneManager->getScene(1);
    Scene * nextScene       = Globals::get()->sceneManager->getScene(2);
    Animator * mainAnimator = Globals::get()->animatorManager->getAnimator(0);
    
    Globals::get()->animData->addFrame(mainAnimator->currentFrame, ofGetModifierPressed(OF_KEY_SHIFT));
    setFrame(mainAnimator->currentFrame + 1, Globals::instance()->animData->currentAnimation->getNumFrames());
    Globals::instance()->sceneManager->updateEditorFrames();

    
}

void EditorInspectorGui::prevFrame() {
    
    Animator * mainAnimator = Globals::get()->animatorManager->getAnimator(0);

    mainAnimator->popFrame();
    setFrame(mainAnimator->currentFrame + 1, Globals::instance()->animData->currentAnimation->getNumFrames());
    Globals::instance()->sceneManager->updateEditorFrames();

    
}

void EditorInspectorGui::nextFrame() {
    
    Animator * mainAnimator = Globals::get()->animatorManager->getAnimator(0);

    mainAnimator->pushFrame();
    setFrame(mainAnimator->currentFrame + 1, Globals::instance()->animData->currentAnimation->getNumFrames());
    Globals::instance()->sceneManager->updateEditorFrames();
}