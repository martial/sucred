//
//  AutomaticMode.cpp
//  Sucre
//
//  Created by Martial on 27/11/2013.
//
//

#include "AutomaticMode.h"
#include "Globals.h"

void AutomaticMode::setup() {
    
    millisTimer     = 10000;
    bChangeColors   = true;
    
    timer.setup(millisTimer, true);
    timer.stopTimer();
    
    ofAddListener(timer.TIMER_REACHED, this, &AutomaticMode::onTimerhandler);
    
    //timer.startTimer();
    
    
    
}

void AutomaticMode::update() {
    
}

void AutomaticMode::onTimerhandler(ofEventArgs & e ) {
    
    // get Random animation
    
    // get selected categories
    
    vector<string> categories = Globals::get()->gui->inspectorGui->getCategories();
    
    AnimationDataObject * anim = Globals::get()->animData->getRandomAnimation(categories);
    Globals::get()->animatorManager->getAnimator(1)->setAnimation(anim);
    Globals::get()->gui->animPickerGui->selectToggle(anim->id);
    
    if(bChangeColors) {
        
        
        ColorDataObject * colorScheme = Globals::get()->animData->getRandomColor();
        Globals::get()->colorManager->setColorScheme(3, colorScheme);
        
        // update gui if first scene is selected only
        int sceneSelected = Globals::get()->sceneManager->getSelected();
        if(sceneSelected == 3)
            Globals::get()->gui->colorPickerGui->selectToggle(colorScheme->id);

        
    }
    
    
}

void AutomaticMode::setEnabled(bool bEnabled) {
    
    this->bEnabled = bEnabled;
    if(bEnabled)
        timer.startTimer();
    else
        timer.stopTimer();
    
    
}


void AutomaticMode::setTimer(int millis) {
    
    this->millisTimer = millis;
    timer.setTimer(this->millisTimer);
    
}


