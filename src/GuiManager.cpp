//
//  GuiManager.cpp
//  Sucre
//
//  Created by Martial on 16/10/13.
//
//

#include "GuiManager.h"
#include "Globals.h"

void GuiManager::setup () {
    
    canvas = new ofxUICanvas(0,0, 220,ofGetHeight());
    
    canvas->setDrawBack(true);
    canvas->setAutoDraw(false);
    
    
    image.loadImage("GUI/logo.png");
    canvas->addImage("", &image, 80, 80);
    
    canvas->addSpacer();
    canvas->addFPS();
    canvas->addTextArea("EDITOR", "EDITOR MODE", OFX_UI_FONT_LARGE);
    canvas->addSpacer();
    canvas->addTextArea("SND", "SOUND", OFX_UI_FONT_LARGE);
    
    leftSpectrum     = canvas->addSpectrum("SPECTRUML", Globals::instance()->eq->leftPreview, 512);
    ofxUISpectrum *  rightSpectrum   = canvas->addSpectrum("SPECTRUMR", Globals::instance()->eq->rightPreview, 512);
    
    
    leftSpectrum->setSteps          (&Globals::instance()->eq->range);
    leftSpectrum->setFilterRange    (&Globals::instance()->eq->filterRange);
    rightSpectrum->setSteps         (&Globals::instance()->eq->range);
    rightSpectrum->setFilterRange   (&Globals::instance()->eq->filterRange);
    
    canvas->addSlider("RANGE", 1, 16, 8);
    overrideSlider = canvas->addSlider("OVERRIDE", -1, 16, 8);
    
    canvas->addSlider("SCALE", 0.0, 1.0, &Globals::instance()->scene->scale);
    
    canvas->autoSizeToFitWidgets();
    ofAddListener(canvas->newGUIEvent,this,&GuiManager::onGuiEvent);
    
    
}

void GuiManager::update() {
    
    
}

void GuiManager::onGuiEvent(ofxUIEventArgs &e) {
    
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
	if(name == "RANGE") {
        ofxUISlider * slider = (ofxUISlider *) e.widget;
        Globals::instance()->eq->setRange((int)slider->getScaledValue());
        if(Globals::instance()->eq->filterRange > slider->getScaledValue() ) {
            Globals::instance()->eq->setFilterRange(slider->getScaledValue() - 1);
        }
        
        overrideSlider->setMax(slider->getScaledValue());
    }
    
    if(name == "OVERRIDE") {
        ofxUISlider * slider = (ofxUISlider *) e.widget;
        Globals::instance()->eq->setFilterRange((int)slider->getScaledValue());
    }

    
}