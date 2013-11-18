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

void AnimationPickerGui::populate () {
    
        
    setDrawBack(true);
    setAutoDraw(false);
    
    
    
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
    
    
    if(toggles.size() > 0) {
        removeWidgets();
       // addSpacer();
   
    }
    
    toggles.clear();
     
    
    
    for (int i=0; i<anims.size(); i++) {
       
        ofxUIToggle * tgl = addToggle(anims[i]->name, false);
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
    
 
    
    tween.setParameters(1,easingquint,ofxTween::easeOut, getSRect()->x, 211,300, 0);
    
}



void AnimationPickerGui::draw() {
    
  
    
    float xPos = ( tween.isRunning()) ? tween.update() : ( bEnabled ) ? 211 : ofGetWidth();
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
    
    Globals::instance()->animData->saveCurrentFrame(Globals::instance()->mainAnimator->currentFrame);
    Globals::instance()->sceneManager->resetEditorFrames();
    Globals::instance()->animData->setAnimationByID(tgl->extraID);
    Globals::instance()->app->mainAnimator.setAnimation(Globals::instance()->animData->currentAnimation);
    Globals::instance()->app->previewAnimator.setAnimation(Globals::instance()->animData->currentAnimation);
    
    
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


