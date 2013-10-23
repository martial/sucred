//
//  EditorGui.cpp
//  Sucre
//
//  Created by Martial on 17/10/13.
//
//

#include "ConfigGui.h"
#include "Globals.h"

void ConfigGui::init () {
    
    live->setValue      (false);
    editor->setValue    (false);
    config->setValue    (true);
    
}

void ConfigGui::populate () {
    
    
    setDrawBack(true);
    setAutoDraw(false);
    
    
    addSpacer();
    image.loadImage("GUI/logo.png");
    addImage("", &image, 80, 80);
    
    
    addSpacer();
    addFPS();
    addSpacer();
    
    live            = addToggle("LIVE", false, OFX_UI_FONT_MEDIUM);
    editor          = addToggle("EDITOR", false, OFX_UI_FONT_MEDIUM);
    config          = addToggle("CONFIG", true, OFX_UI_FONT_MEDIUM);
    config->enabled = false;
    addSpacer();
    
    
    
    addSlider("SCALE", 0.0, 1.0, &editorSceneScale);
    addToggle("SHOW IDS", false);
    
    autoSizeToFitWidgets();
    
    
}

void ConfigGui::hide() {
    tween.setParameters(1,easingquint,ofxTween::easeOut, rect->x,-rect->width,300, 0);
}

void ConfigGui::show () {
    tween.setParameters(1,easingquint,ofxTween::easeOut, rect->x, 0,300, 0);
    
}

void ConfigGui::update() {
    this->setPosition(tween.update(), 0.0);
    ofxUICanvas::update();
    
    
    
}

void ConfigGui::draw() {
    
    ofxUICanvas::draw();
    
}