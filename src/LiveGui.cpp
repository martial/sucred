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
    playBtn = addToggle("PLAY", &Globals::instance()->mainAnimator->bIsPlaying);
    //stopBtn = addToggle("STOP", true);
    speedSlider = addSlider("SPEED", 1.0, 0.0, 0.0);
    addToggle("LOOP PALYNDROME",  &Globals::instance()->mainAnimator->bLoopPalyndrome);
    
    addSpacer();
    addTextArea("EFFECTS", "EFFECTS", OFX_UI_FONT_LARGE);
    addSpacer();
    
    
    addToggle("SOUND + ALPHA", false);
    addToggle("STROB", false);
    addSlider("STROB SPEED", 4, 100, &Globals::instance()->effectsManager->strobSpeed);
    addSpacer();
    
    r = 255.0;
    g = 255.0;
    b = 255.0;
    
    rSlider = new ofxUIRotarySlider(24*2.0, 0.0, 255, &r, "R");
    gSlider = new ofxUIRotarySlider(24*2.0, 0.0, 255, &g, "G");
    bSlider = new ofxUIRotarySlider(24*2.0, 0.0, 255, &b, "B");
    
    addWidgetDown(rSlider);
    addWidgetRight(gSlider);
    addWidgetRight(bSlider);
    
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

}

void LiveGui::update() {
    
    
    this->setPosition(tween.update(), 0.0);
    ofxUICanvas::update();
    
    rSlider->setColorFill(ofxUIColor(r,g,b));
    gSlider->setColorFill(ofxUIColor(r,g,b));
    bSlider->setColorFill(ofxUIColor(r,g,b));
    
    rSlider->setColorFillHighlight(ofxUIColor(r,g,b));
    gSlider->setColorFillHighlight(ofxUIColor(r,g,b));
    bSlider->setColorFillHighlight(ofxUIColor(r,g,b));
    
    Globals::instance()->colorManager->setGlobalColor(ofColor(r,g,b));
    

}

void LiveGui::draw() {
    
    ofxUICanvas::draw();
    
}

void LiveGui::onGuiEvent(ofxUIEventArgs & e) {
    
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
    Scene * mainScene       = Globals::instance()->sceneManager->getScene(0);
    Scene * prevScene       = Globals::instance()->sceneManager->getScene(1);
    Scene * nextScene       = Globals::instance()->sceneManager->getScene(2);
    Animator * mainAnimator = Globals::instance()->mainAnimator;
    

    if( name =="PLAY") {
        
        if(playBtn->getValue())
        Globals::instance()->mainAnimator->play();
        else
            Globals::instance()->mainAnimator->stop();
        //playBtn->setValue(true);
        //stopBtn->setValue(false);
        //setFrame(Globals::instance()->animData->currentFrame + 1, Globals::instance()->animData->currentAnimation->getNumFrames());
        
    }
    
    if( name =="STOP") {
        
        Globals::instance()->mainAnimator->stop();
        //playBtn->setValue(false);
        //stopBtn->setValue(true);
        //setFrame(Globals::instance()->animData->currentFrame + 1, Globals::instance()->animData->currentAnimation->getNumFrames());
        
    }
    

    
    if(name == "SPEED") {
        
        Globals::instance()->mainAnimator->speedPct = speedSlider->getValue();
        Globals::instance()->previewAnimator->speedPct = speedSlider->getValue();
        
        
    }
    
    if (name == "SOUND + ALPHA") {
        
        if(e.getToggle()->getValue()) {
            Globals::instance()->effectsManager->enableEffect(1);
        }
        else {
        Globals::instance()->effectsManager->disableEffect(1);
        }
    }
    
    if (name == "STROB") {
        
        if(e.getToggle()->getValue()) {
            Globals::instance()->effectsManager->enableEffect(0);
        }
        else {
            Globals::instance()->effectsManager->disableEffect(0);
        }
    }
    

    
    
    if(name == "DECAY") {
        
        Globals::instance()->colorManager->setGlobalDecay(e.getSlider()->getValue());
        
    }
    
    if (name == "HSB") {
        
        ofColor c = hsbPicker->getColor();
        
        r = c.r;
        g = c.g;
        b = c.b;
        
        
        
        
    }
    
    if (name == "ALPHA") {
        
        Globals::instance()->colorManager->setGlobalAlpha(e.getSlider()->getValue());

        
        
        
        
    }
    
    
}