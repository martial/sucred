//
//  LiveGui.cpp
//  Sucre
//
//  Created by Martial on 17/10/13.
//
//

#include "LiveGui.h"
#include "Globals.h"

void LiveGui::init () {
    
    live->setValue      (true);
    editor->setValue    (false);
    config->setValue    (false);
    
}

void LiveGui::populate () {
    
    
    setDrawBack(true);
    setAutoDraw(false);
    
    
    
    
    image.loadImage("GUI/logo.png");
    addSpacer();
    addImage("", &image, 80, 80);
    
    
    addSpacer();
    addFPS();
    addSpacer();
    
    live            = addToggle("LIVE", true, OFX_UI_FONT_MEDIUM);
    live->enabled   = false;
    
    editor          = addToggle("EDITOR", false, OFX_UI_FONT_MEDIUM);
    config          = addToggle("CONFIG", false, OFX_UI_FONT_MEDIUM);
    
    
    
    addSpacer();
    addTextArea("SND", "SOUND", OFX_UI_FONT_LARGE);
    
    leftSpectrum     = addSpectrum("SPECTRUML", Globals::instance()->eq->leftPreview, 512);
    rightSpectrum   = addSpectrum("SPECTRUMR", Globals::instance()->eq->rightPreview, 512);
    
    
    leftSpectrum->setSteps          (&Globals::instance()->eq->range);
    leftSpectrum->setFilterRange    (&Globals::instance()->eq->filterRange);
    rightSpectrum->setSteps         (&Globals::instance()->eq->range);
    rightSpectrum->setFilterRange   (&Globals::instance()->eq->filterRange);
    
    addSlider("RANGE", 1, 16, 8);
    overrideSlider = addSlider("OVERRIDE", -1, 16, 8);
    
    addSlider("SCALE", 0.0, 1.0, &Globals::instance()->scene->scale);
    
    autoSizeToFitWidgets();
     
    
}

void LiveGui::hide() {
    tween.setParameters(1,easingquint,ofxTween::easeOut, rect->x,-rect->width,300, 0);
}

void LiveGui::show () {
    tween.setParameters(1,easingquint,ofxTween::easeOut, rect->x, 0,300, 0);

}

void LiveGui::update() {
    this->setPosition(tween.update(), 0.0);
    ofxUICanvas::update();
    
    

}

void LiveGui::draw() {
    
    ofxUICanvas::draw();
    
}