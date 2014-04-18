//
//  ColorPickerGui.cpp
//  Sucre
//
//  Created by Martial on 15/11/2013.
//
//

#include "ColorPickerGui.h"
#include "Globals.h"
#include "testApp.h"

void ColorPickerGui::populate () {
    
    
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
    
    
    
    ofAddListener(ofEvents().windowResized, this, &ColorPickerGui::onWindowResize);
    ofAddListener(newGUIEvent,this,&ColorPickerGui::onGuiEvent);
}

void ColorPickerGui::setColors(vector<ColorDataObject*> colors) {
    
    
    if(toggles.size() > 0) {
        removeWidgets();
        // addSpacer();
        
    }
    
    toggles.clear();
    
    
    
    for (int i=0; i<colors.size(); i++) {
        
        ofxUIToggle * tgl = addToggle(ofToUpper(colors[i]->name), false);
        tgl->extraID = colors[i]->id;
        
        toggles.push_back(tgl);
        
    }
    
    setScrollAreaToScreenHeight();
    autoSizeToFitWidgets();
    
}

void ColorPickerGui::selectToggle(int index) {
    
    for (int i=0;  i<toggles.size(); i++) {
        if(toggles[i]->extraID == index)
            toggles[i]->ofxUIButton::setValue(true);
        else
            toggles[i]->ofxUIButton::setValue(false);
        
    }
    
}

void ColorPickerGui::onWindowResize(ofResizeEventArgs &e) {
    
    
    
    setScrollAreaToScreenHeight();
    
    autoSizeToFitWidgets();
    //getRect()->setHeight(ofGetHeight());
    
    
}


void ColorPickerGui::hide() {
    bEnabled = false;
    tween.setParameters(1,easingquint,ofxTween::easeOut, getSRect()->x, ofGetWidth(),300, 0);
}

void ColorPickerGui::show () {
    bEnabled = true;
    
   
    float xRect = 0.0;
    if ( Globals::instance()->app->mode == MODE_LIVE) {
        xRect = Globals::instance()->gui->inspectorGui->getRect()->x;
    }
    
    if ( Globals::instance()->app->mode == MODE_EDITOR) {
        xRect = Globals::instance()->gui->editorInspectorGui->getRect()->x;
    }
    tween.setParameters(1,easingquint,ofxTween::easeOut, getSRect()->x, xRect - getRect()->getWidth() - 1,300, 0);
    
}



void ColorPickerGui::draw() {
    
    float xRect = 0.0;
    if ( Globals::instance()->app->mode == MODE_LIVE) {
        xRect = Globals::instance()->gui->inspectorGui->getRect()->x;
    }
    
    if ( Globals::instance()->app->mode == MODE_EDITOR) {
        xRect = Globals::instance()->gui->editorInspectorGui->getRect()->x;
    }
    
    float xPos = ( tween.isRunning()) ? tween.update() : ( bEnabled ) ? xRect - getRect()->getWidth() - 1 : ofGetWidth();
    //getRect()->x = xPos;
    rect->x = xPos;
    getSRect()->x = xPos;
    ofxUICanvas::draw();
    
    
}

void ColorPickerGui::onGuiEvent(ofxUIEventArgs & e) {
    
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    int extraID = e.getToggle()->extraID;
    
    ofxUIToggle * tgl = e.getToggle();
    
    for (int i=0;  i<toggles.size(); i++) {
        if(toggles[i]->extraID != extraID)
            toggles[i]->ofxUIButton::setValue(false);
    }
    
    AnimationDataObject * anim = Globals::get()->animData->getAnimationByID(tgl->extraID);
    
    // we need to know wich scene
    int sceneIndex = Globals::get()->sceneManager->getSelected();
    
    
    Globals::get()->animData->setColorSchemeByID(tgl->extraID);
    Globals::get()->colorManager->setColorScheme(sceneIndex, Globals::get()->animData->currentColorScheme);
    
}

void ColorPickerGui::renameToggle(int index, string name) {
    

    for (int i=0; i<toggles.size();i ++) {
        
        
        if(toggles[i]->extraID == index) {
            toggles[i]->getLabel()->setLabel(name);
            toggles[i]->setName(name);
            //toggles[i]->set
        }
        
    }
    
    autoSizeToFitWidgets();
    
    
}


