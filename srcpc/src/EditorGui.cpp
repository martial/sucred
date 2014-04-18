//
//  EditorGui.cpp
//  Sucre
//
//  Created by Martial on 21/10/13.
//
//

#include "EditorGui.h"

#include "Globals.h"

void EditorGui::init () {
    
    live->setValue      (false);
    editor->setValue    (true);
    config->setValue    (false);
    
}

void EditorGui::populate () {
    
    
    setDrawBack(true);
    //setAutoDraw(false);
    
    
    //addSpacer();
    image.loadImage("GUI/logo.png");
    addImage("", &image, 80, 80);
    
    
   // addSpacer();
  //  addFPS();
    addSpacer();
    
    live            = addToggle("LIVE", false, OFX_UI_FONT_SMALL);
    editor          = addToggle("EDITOR", true, OFX_UI_FONT_SMALL);
    editor->enabled = false;
    config          = addToggle("CONFIG", false, OFX_UI_FONT_SMALL);
    
    addSpacer();
    
    addSlider("SCALE", 0.1, 1.4, &editorSceneScale);
    
    addSpacer();
    addButton("NEW", false);
    addButton("SAVE", false);
    addButton("DELETE", false);
    
    autoSizeToFitWidgets();
    ofAddListener(newGUIEvent,this,&EditorGui::onGuiEvent);

}

void EditorGui::hide() {
    tween.setParameters(1,easingquint,ofxTween::easeOut, rect->x,-rect->width,300, 0);
}

void EditorGui::show () {
    tween.setParameters(1,easingquint,ofxTween::easeOut, rect->x, 0,300, 0);
    live->setValue      (false);
    editor->setValue    (true);
    config->setValue    (false);
    
}

void EditorGui::update() {
    this->setPosition(tween.update(), 0.0);
    ofxUICanvas::update();
    
}

void EditorGui::draw() {
    
    getRect()->setHeight(ofGetHeight());
    ofxUICanvas::draw();
    
}

void EditorGui::onGuiEvent(ofxUIEventArgs & e) {
    
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
    Animator * mainAnimator = Globals::get()->animatorManager->getAnimator(0);
    Animator * previewAnimator = Globals::get()->animatorManager->getAnimator(1);

    
    if(name == "NEW") {
        
        
        Globals::instance()->animData->addAnimation();
        mainAnimator->setAnimation(Globals::instance()->animData->currentAnimation);
        previewAnimator->setAnimation(Globals::instance()->animData->currentAnimation);
        previewAnimator->play();
        Globals::instance()->sceneManager->updateEditorFrames();
        
    }
    
    if (name == "SAVE") {
        Globals::get()->animData->saveCurrentAnimation();
    }
    
    if (name == "DELETE") {
        
        Globals::instance()->animData->deleteAnimationByID(Globals::instance()->animData->currentAnimation->id);
        
    }
    
    if (name == "SCALE") {
        Globals::instance()->sceneManager->setGlobalScale(editorSceneScale);
        
    }
    
    
}