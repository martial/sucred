//
//  GuiManager.cpp
//  Sucre
//
//  Created by Martial on 16/10/13.
//
//

#include "GuiManager.h"
#include "Globals.h"
#include "testApp.h"

void GuiManager::setup () {
    
    liveGui = new LiveGui(0,0, 220,ofGetHeight());
    liveGui->populate();
    
    ofAddListener(liveGui->newGUIEvent,this,&GuiManager::onGuiEvent);
    
    inspectorGui = new InspectorGui(0,0, 220,ofGetHeight());
    inspectorGui->populate();
    ofAddListener(inspectorGui->newGUIEvent,this,&GuiManager::onGuiEvent);
    
   

    
    configGui = new ConfigGui(0,0, 220,ofGetHeight());
    configGui->populate();
    ofAddListener(configGui->newGUIEvent,this,&GuiManager::onGuiEvent);
    
    
    animPickerGui = new AnimationPickerGui(0,0, 220,ofGetHeight());
    animPickerGui->populate();
    
    colorPickerGui = new ColorPickerGui(0,0, 220,ofGetHeight());
    colorPickerGui->populate();
    
    //animPickerGui->hide();
    //ofAddListener(editorGui->newGUIEvent,this,&GuiManager::onGuiEvent);
    
    editorInspectorGui = new EditorInspectorGui(0,0, 220,ofGetHeight());
    editorInspectorGui->populate();
    ofAddListener(editorInspectorGui->newGUIEvent,this,&GuiManager::onGuiEvent);
    
    editorGui = new EditorGui(0,0, 220,ofGetHeight());
    editorGui->populate();
    ofAddListener(editorGui->newGUIEvent,this,&GuiManager::onGuiEvent);

    
    selector.enable();
    
}

void GuiManager::loadSettings() {
    liveGui->loadSettings("GUI/live.xml");
}

void GuiManager::setMode (int mode) {
    
    if ( mode == MODE_EDITOR ) {
        //liveGui->disable();
        
        liveGui->hide();
        configGui->hide();
        editorGui->show();
        
        editorInspectorGui->show();
        inspectorGui->hide();
        
        inspectorGui->enable();
        
        selector.enable();
    }
    
    if ( mode == MODE_LIVE ) {
        
        liveGui->enable();
        
        liveGui->show();
        configGui->hide();
        editorGui->hide();
        //editorGui->disable();
        inspectorGui->enable();
        
        editorInspectorGui->hide();
        inspectorGui->show();
        
        //selector.disable();
    }
    
    if ( mode == MODE_CONFIG ) {
        
        //liveGui->disable();
        editorGui->hide();
        liveGui->hide();
        configGui->show();
        inspectorGui->enable();
        
        editorInspectorGui->hide();
        inspectorGui->show();

        
        selector.enable();
    }

    
    liveGui->init();
    configGui->init();
    
}

void GuiManager::update() {
    
    
    
}

void GuiManager::draw() {
    selector.draw();
}

ofRectangle GuiManager::getEmptyUIZone () {
    
    ofRectangle r;
    r.set(220, 0, ofGetWidth() - 220*2, ofGetHeight());
    return r;
}

void GuiManager::onGuiEvent(ofxUIEventArgs &e) {
    
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
    if( name == "LIVE" )
        Globals::instance()->app->setMode(MODE_LIVE);
    
    if( name == "EDITOR" )
        Globals::instance()->app->setMode(MODE_EDITOR);
    
    
    if( name == "CONFIG" )
        Globals::instance()->app->setMode(MODE_CONFIG);
    
    
    
	if(name == "RANGE") {
        ofxUISlider * slider = (ofxUISlider *) e.widget;
        Globals::instance()->eq->setRange((int)slider->getScaledValue());
        if(Globals::instance()->eq->filterRange > slider->getScaledValue() ) {
            Globals::instance()->eq->setFilterRange(slider->getScaledValue() - 1);
        }
        
        liveGui->overrideSlider->setMax(slider->getScaledValue());
    }
    
    if(name == "OVERRIDE") {
        ofxUISlider * slider = (ofxUISlider *) e.widget;
        Globals::instance()->eq->setFilterRange((int)slider->getScaledValue());
    }

    
}

bool GuiManager::isRollOver() {
    
    float x = ofGetMouseX();
    float y = ofGetMouseY();
    
    if (liveGui->isHit(x, y) ||
        inspectorGui->isHit(x, y) ||
        animPickerGui->isHit(x, y) ||
        colorPickerGui->isHit(x, y) ||
        editorGui->isHit(x, y)
        ) return true;
    
    return false;
    
}

void GuiManager::save() {
    
    liveGui->saveSettings("GUI/live.xml");
    //inspectorGui->saveSettings("gui/inspector.xml");
    
    
    
}



