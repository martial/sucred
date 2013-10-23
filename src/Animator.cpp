//
//  Animator.cpp
//  Sucre
//
//  Created by Martial on 23/10/2013.
//
//

#include "Animator.h"
#include "Globals.h"

void Animator::setup(Scene * scene){
    
    bIsPlaying  = false;
    bReverse    = false;
    speedPct    = 1.0;
    
    maxDelay    = 500.0f;
    
    anim        = NULL;
    
    this->scene = scene;
    
    int foo = 0;
    ofNotifyEvent(tickEvent, foo);
    
}

void Animator::update(){
    
    if(bIsPlaying ) {
        
        
        
        float currentMillis     = ofGetElapsedTimeMillis();
        float diff              = currentMillis - savedMillis;
        
        if(diff > maxDelay * speedPct) {
            // fireevent
            savedMillis   = ofGetElapsedTimeMillis();
            
            int foo = 0;
            ofNotifyEvent(tickEvent, foo);
            
        }
        
        
    }
    
    
}

void Animator::setAnimation(AnimationDataObject *anim) {
    this->anim = anim;
}


void Animator::play(){
    
    savedMillis     = ofGetElapsedTimeMillis();
    bIsPlaying      = true;
    
    
}

void Animator::stop(){
    
    bIsPlaying = false;
    
}

void Animator::pause(){
    
    
}




void Animator::setSpeed(float pct){
    
    this->speedPct = pct;
    
}

float Animator::getSpeed(){
    
    return speedPct;
    
}


void Animator::setReverse(bool bReverse){
    
    this->bReverse = bReverse;
    
}

bool Animator::getReverse(){
    
    return bReverse;
}


bool Animator::isPlaying(){
    
    return bIsPlaying;
}
