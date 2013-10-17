//
//  EditorGui.cpp
//  Sucre
//
//  Created by Martial on 17/10/13.
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
    setAutoDraw(false);
    
    
    addSpacer();
    image.loadImage("GUI/logo.png");
    addImage("", &image, 80, 80);
    
    
    addSpacer();
    addFPS();
    addSpacer();
    
    live            = addToggle("LIVE", false, OFX_UI_FONT_MEDIUM);
    editor          = addToggle("EDITOR", true, OFX_UI_FONT_MEDIUM);
    editor->enabled = false;
    config          = addToggle("CONFIG", false, OFX_UI_FONT_MEDIUM);
    
    addSpacer();
    
    
    
    addSlider("SCALE", 0.0, 1.0, &Globals::instance()->scene->scale);
    addToggle("SHOW IDS", false);
    
    autoSizeToFitWidgets();
    
    
}

void EditorGui::hide() {
    tween.setParameters(1,easingquint,ofxTween::easeOut, rect->x,-rect->width,300, 0);
}

void EditorGui::show () {
    tween.setParameters(1,easingquint,ofxTween::easeOut, rect->x, 0,300, 0);
    
}

void EditorGui::update() {
    this->setPosition(tween.update(), 0.0);
    ofxUICanvas::update();
    
    
    
}

void EditorGui::draw() {
    
    ofxUICanvas::draw();
    
}