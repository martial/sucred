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
    //addSpacer();
    //addImage("", &image, 80, 80);
    
    
    addSpacer();
    addFPS();
    addSpacer();
    
    live            = addToggle("LIVE", true, OFX_UI_FONT_SMALL);
    live->enabled   = false;
    
    editor          = addToggle("EDITOR", false, OFX_UI_FONT_SMALL);
    config          = addToggle("CONFIG", false, OFX_UI_FONT_SMALL);
    
    
    
    addSpacer();
    addTextArea("SND", "SOUND", OFX_UI_FONT_LARGE);
    
    leftSpectrum        = addSpectrum("SPECTRUML", Globals::instance()->eq->leftPreview, 512);
    rightSpectrum       = addSpectrum("SPECTRUMR", Globals::instance()->eq->rightPreview, 512);
    
    
    leftSpectrum->setSteps          (&Globals::instance()->eq->range);
    leftSpectrum->setFilterRange    (&Globals::instance()->eq->filterRange);
    rightSpectrum->setSteps         (&Globals::instance()->eq->range);
    rightSpectrum->setFilterRange   (&Globals::instance()->eq->filterRange);
    
    addSlider("RANGE", 1, 16, 8);
    overrideSlider = addSlider("OVERRIDE", -1, 16, 8);
    
    addSlider("DECAY", 0, 1, 1);

    //addSlider("DECAY", 0, 100, 0);
    
    addSpacer();
    addTextArea("PLAYER", "PLAYER", OFX_UI_FONT_LARGE);
    addSpacer();
    addButton("SET ANIM", false);
    playBtn = addToggle("PLAY", &Globals::get()->animatorManager->getAnimator(0)->bIsPlaying, OFX_UI_FONT_SMALL);
    //stopBtn = addToggle("STOP", true);
    speedSlider = addSlider("SPEED", 1.0, 0.0, &Globals::get()->animatorManager->getAnimator(0)->speedPct);
    addToggle("LOOP PALYNDROME",  &Globals::get()->animatorManager->getAnimator(0)->bLoopPalyndrome, OFX_UI_FONT_SMALL);
    
    addSpacer();
    addTextArea("EFFECTS", "EFFECTS", OFX_UI_FONT_LARGE);
    addSpacer();
    
    
    addToggle("SOUND + ALPHA", false);
    addToggle("STROB", false);
    addToggle("STROB / DMX", &Globals::instance()->effectsManager->strobEffect->strobDmx, OFX_UI_FONT_SMALL);
    addToggle("FULL STROB", false);
    addSlider("STROB SPEED", 4, 100, &Globals::instance()->effectsManager->strobSpeed);
    addSpacer();
    
    r = 255.0;
    g = 255.0;
    b = 255.0;
    w = 255.0,
    
    rSlider = new ofxUIRotarySlider(24*2.0, 0.0, 255, &r, "R");
    gSlider = new ofxUIRotarySlider(24*2.0, 0.0, 255, &g, "G");
    bSlider = new ofxUIRotarySlider(24*2.0, 0.0, 255, &b, "B");
    wslider = new ofxUIRotarySlider(24*2.0, 0.0, 255, &w, "W");
    
    addWidgetDown(rSlider);
    addWidgetRight(gSlider);
    addWidgetRight(bSlider);
    addWidgetDown(wslider);
    
    addSlider("ALPHA", 0, 1, 1);
    hsbPicker = addHsbPicker("HSB");
    
    //addSlider("SCALE", 0.0, 1.0, &editorSceneScale);
    
    autoSizeToFitWidgets();
    
    ofAddListener(newGUIEvent,this,&LiveGui::onGuiEvent);

    
    
}

void LiveGui::hide() {
    tween.setParameters(1,easingquint,ofxTween::easeOut, rect->x,-rect->width,300, 0);
}

void LiveGui::show () {
    tween.setParameters(1,easingquint,ofxTween::easeOut, rect->x, 0,300, 0);
    live->setValue      (true);
    editor->setValue    (false);
    config->setValue    (false);


}

void LiveGui::update() {
    
    
    this->setPosition(tween.update(), 0.0);
    this->getRect()->setHeight(ofGetHeight());
    ofxUICanvas::update();
    
    rSlider->setColorFill(ofxUIColor(r,g,b));
    gSlider->setColorFill(ofxUIColor(r,g,b));
    bSlider->setColorFill(ofxUIColor(r,g,b));
    
    rSlider->setColorFillHighlight(ofxUIColor(r,g,b));
    gSlider->setColorFillHighlight(ofxUIColor(r,g,b));
    bSlider->setColorFillHighlight(ofxUIColor(r,g,b));
    
    Globals::instance()->colorManager->setGlobalColor(ofColor(r,g,b), w);
    

}

void LiveGui::draw() {
    
    ofxUICanvas::draw();
    
}

void LiveGui::onGuiEvent(ofxUIEventArgs & e) {
    
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
    Scene * mainScene       = Globals::get()->sceneManager->getScene(0);
    Scene * prevScene       = Globals::get()->sceneManager->getScene(1);
    Scene * nextScene       = Globals::get()->sceneManager->getScene(2);
    
    Animator * mainAnimator = Globals::get()->animatorManager->getAnimator(0);
    Animator * previewAnimator = Globals::get()->animatorManager->getAnimator(1);

    if( name =="PLAY") {
        
        if(playBtn->getValue())
            mainAnimator->play();
        else
            mainAnimator->stop();
    }
    
    if( name =="STOP") {
        
        mainAnimator->stop();
        
    }
    
    if(name == "SPEED") {
        
        mainAnimator->speedPct = speedSlider->getValue();
        previewAnimator->speedPct = speedSlider->getValue();
        
    }
    
    if (name == "SOUND + ALPHA") {
        
        if(e.getToggle()->getValue()) {
            Globals::get()->effectsManager->enableEffect(1);
        }
        else {
            Globals::get()->effectsManager->disableEffect(1);
        }
    }
    
    if (name == "STROB") {
        
        if(e.getToggle()->getValue()) {
            Globals::get()->effectsManager->enableEffect(0);
        }
        else {
            Globals::get()->effectsManager->disableEffect(0);
        }
    }
    
    if (name == "STROB DMX") {
        
        if(e.getToggle()->getValue()) {
            Globals::get()->effectsManager->enableEffect(0);
        }
        else {
            Globals::get()->effectsManager->disableEffect(0);
        }
    }
    
    if (name == "FULL STROB") {
        
        if(e.getToggle()->getValue()) {
            Globals::get()->effectsManager->enableEffect(2);
        }
        else {
            Globals::get()->effectsManager->disableEffect(2);
        }
    }
    
    if(name == "DECAY") {
        
        Globals::get()->colorManager->setGlobalDecay(e.getSlider()->getValue());
        
    }
    
    if (name == "HSB") {
        
        ofColor c = hsbPicker->getColor();
        
        r = c.r;
        g = c.g;
        b = c.b;
        
        
    }
    
    if (name == "ALPHA") {
        
        Globals::get()->colorManager->setGlobalAlpha(e.getSlider()->getValue());
        
    }
    
    if(name == "LOOP PALYNDROME") {
        
        mainAnimator->bLoopPalyndrome = e.getButton()->getValue();
    }
    
    if (name == "SET ANIM") {
        
        // do the stuff
        
    }
    
}