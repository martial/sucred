//
//  AnimationPickerGui.cpp
//  Sucre
//
//  Created by Martial on 23/10/2013.
//
//

#include "AnimationPickerGui.h"
#include "Globals.h"
#include "testApp.h"
#include "ofxModifierKeys.h"

void AnimationPickerGui::populate () {
    
        
    setDrawBack(true);
    
    
    
    //addSpacer();
    
    
    //addTextArea("ANIMS", "ANIMS", OFX_UI_FONT_LARGE);
    //addSpacer();
    
     
     
    
    setScrollableDirections(false, true);
    
    setScrollAreaToScreenHeight();
    
    //autoSizeToFitWidgets();
    getRect()->setHeight(ofGetHeight());

    //setDrawWidgetPadding(true);
    
    autoSizeToFitWidgets();

    show();
    
    
    
    /*
    vector<ofxUIWidget*> spacers = getWidgetsOfType(OFX_UI_WIDGET_SPACER);
    
    for(int i = 0; i < spacers.size(); i++)
    {
        ofxUISpacer *s = (ofxUISpacer *) spacers[i];
        s->toggleVisible();
    }
     
     */

    
    
    ofAddListener(ofEvents().windowResized, this, &AnimationPickerGui::onWindowResize);
    ofAddListener(newGUIEvent,this,&AnimationPickerGui::onGuiEvent);
}

void AnimationPickerGui::setAnims(vector<AnimationDataObject*> anims) {
    
  
	toggles.clear();
   
        removeWidgets();
       // addSpacer();
   
    
	

    
    
     
    ofxUIToggle * nullToggle = addToggle("NONE", false);
    nullToggle->extraID = -999;
    toggles.push_back(nullToggle);
    
    for (int i=0; i<anims.size(); i++) {
       
        ofxUIToggle * tgl = addToggle(ofToUpper(anims[i]->name), false);
        tgl->extraID = anims[i]->id;
        toggles.push_back(tgl);
        
    }
    
    setScrollAreaToScreenHeight();
    autoSizeToFitWidgets();
    
}

void AnimationPickerGui::selectToggle(int index) {
    
    for (int i=0;  i<toggles.size(); i++) {
        if(toggles[i]->extraID == index)
            toggles[i]->ofxUIButton::setValue(true);
        else
            toggles[i]->ofxUIButton::setValue(false);
        
    }
    
}

void AnimationPickerGui::selectToggleByIndex(int index) {
    
    for (int i=0;  i<toggles.size(); i++) {
        if(i == index)
            toggles[i]->ofxUIButton::setValue(true);
        else
            toggles[i]->ofxUIButton::setValue(false);
        
    }
}

void AnimationPickerGui::onWindowResize(ofResizeEventArgs &e) {
    
    
    
    setScrollAreaToScreenHeight();
    
    autoSizeToFitWidgets();
    //getRect()->setHeight(ofGetHeight());
    
    
}


void AnimationPickerGui::hide() {
    bEnabled = false;
    tween.setParameters(1,easingquint,ofxTween::easeOut, getSRect()->x, -getRect()->getWidth(),300, 0);
}

void AnimationPickerGui::show () {
    bEnabled = true;
    
 
    
    tween.setParameters(1,easingquint,ofxTween::easeOut, getSRect()->x, 212,300, 0);
    
}



void AnimationPickerGui::draw() {
    
  
    
    float xPos = ( tween.isRunning()) ? tween.update() : ( bEnabled ) ? 212 : ofGetWidth();
    //getRect()->x = xPos;
    rect->x = xPos;
    getSRect()->x = xPos;
    ofxUICanvas::draw();
    
    
}

void AnimationPickerGui::onGuiEvent(ofxUIEventArgs & e) {
    
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
    ofxUIToggle * tgl = e.getToggle();
    
    for (int i=0;  i<toggles.size(); i++) {
        if(toggles[i]->getName() != name)
            toggles[i]->ofxUIButton::setValue(false);
    }
    
    
    Animator * mainAnimator = Globals::get()->animatorManager->getAnimator(0);
    Animator * previewAnimator = Globals::get()->animatorManager->getAnimator(1);
    Animator * overlayAnimator = Globals::get()->animatorManager->getAnimator(2);
    int mode = Globals::get()->app->mode;
    
    
    // if we're in live mode - check CAPS and set (a) to preview or (b) main

    // if we're in editor set to both
    
    
    
    if(mode == MODE_EDITOR )
        Globals::get()->animData->saveCurrentFrame(mainAnimator->currentFrame);
    
    
    

    
    if(mode == MODE_EDITOR ) {
        
        Globals::get()->animData->saveCurrentFrame(mainAnimator->currentFrame);
        Globals::get()->sceneManager->resetEditorFrames();
        Globals::get()->animData->setAnimationByID(tgl->extraID);
        

        mainAnimator->setAnimation(Globals::get()->animData->currentAnimation);
        previewAnimator->setAnimation(Globals::get()->animData->currentAnimation);
        
        Globals::get()->gui->editorInspectorGui->setCategories(Globals::get()->animData->currentAnimation->categories);
        
    } else {
        
        //Globals::get()->animData->setAnimationByID(tgl->extraID);
        
        AnimationDataObject * anim = Globals::get()->animData->getAnimationByID(tgl->extraID);
        
        // we need to know wich scene
        int sceneIndex = Globals::get()->sceneManager->getSelected();
        
        if(sceneIndex == 3)
            previewAnimator->setAnimation(anim);
        
        if(sceneIndex== 4)
            overlayAnimator->setAnimation(anim);
        
    }
    
    
}

void AnimationPickerGui::renameToggle(int index, string name) {
    

    for (int i=0; i<toggles.size();i ++) {
        
        if(toggles[i]->extraID == index) {
            toggles[i]->getLabel()->setLabel(name);
            toggles[i]->setName(name);
            //toggles[i]->set
        }
        
    }
    
    autoSizeToFitWidgets();
    
    
}

int AnimationPickerGui::getSelected() {
    for (int i=0; i<toggles.size(); i++) {
        if(toggles[i]->getValue())
            return i;
    }
    
    return -1;
}

void AnimationPickerGui::nextAnim() {
    
    // check selected ?
    int selected = getSelected();
    
    selected++;
    if(selected >= toggles.size() )
        selected = 0;
    
    this->selectToggleByIndex(selected);
    
    Animator * previewAnimator = Globals::get()->animatorManager->getAnimator(1);
    Animator * overlayAnimator = Globals::get()->animatorManager->getAnimator(2);
    AnimationDataObject * anim = Globals::get()->animData->getAnimationByID(toggles[selected]->extraID);
    
    // we need to know wich scene
    int sceneIndex = Globals::get()->sceneManager->getSelected();
    
    if(sceneIndex == 3)
        previewAnimator->setAnimation(anim);
    
    if(sceneIndex== 4)
        overlayAnimator->setAnimation(anim);

    
    
}
void AnimationPickerGui::prevAnim() {
    
    // check selected ?
    int selected = getSelected();
    
    selected--;
    if(selected < 0 )
        selected = toggles.size() - 1 ;
    
    //ofLog(OF_LOG_NOTICE, "selected %d", selected);
    
    this->selectToggleByIndex(selected);
    
    Animator * previewAnimator = Globals::get()->animatorManager->getAnimator(1);
    Animator * overlayAnimator = Globals::get()->animatorManager->getAnimator(2);
    AnimationDataObject * anim = Globals::get()->animData->getAnimationByID(toggles[selected]->extraID);
    
    // we need to know wich scene
    int sceneIndex = Globals::get()->sceneManager->getSelected();
    
    if(sceneIndex == 3)
        previewAnimator->setAnimation(anim);
    
    if(sceneIndex== 4)
        overlayAnimator->setAnimation(anim);

    
}




