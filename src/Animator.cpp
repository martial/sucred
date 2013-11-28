//
//  Animator.cpp
//  Sucre
//
//  Created by Martial on 23/10/2013.
//
//

#include "Animator.h"
#include "Globals.h"

Animator::Animator () {
    
    anim            = NULL;
    
}

void Animator::setup(){
    
    bIsPlaying      = false;
    bReverse        = false;
    bLoopPalyndrome = true;
    speedPct        = 1.0;
    direction       = 1;
    
    currentFrame    = 0;
    
    maxDelay        = 500.0f;
    
    
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
            
            
            
            nextFrame();
            
            ofNotifyEvent(tickEvent, currentFrame);
            
        }
        
        
    }
    
    
}

void Animator::setAnimation(AnimationDataObject * anim) {
    
    this->anim      = NULL;
    this->anim      = anim;
    
    if(this->anim)
        this->speedPct  = anim->speed;
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

void Animator::nextFrame() {
    
    if(!anim)
        return;
    
    if(!bLoopPalyndrome)
        direction = 1;
    
    
    if(bLoopPalyndrome && currentFrame >= anim->frames.size() -1 )
        direction = -1;
    
    if(bLoopPalyndrome && currentFrame <= 0 )
        direction = 1;
        
    
    currentFrame += direction;
    
    if (!bLoopPalyndrome && currentFrame >= anim->frames.size()) {
        currentFrame = 0 ;
    }
    
    if(!bLoopPalyndrome && currentFrame < 0 ) {
        currentFrame = anim->frames.size() -1;
    }

    
}

void Animator::pushFrame() {
    if(!anim)
        return;
    
    currentFrame += 1;
    if (currentFrame >= anim->frames.size()) {
        currentFrame = 0 ;
    }
    
   
    
    // populate
    
}


void Animator::popFrame() {
    if(!anim)
        return;
    
    currentFrame--;
    if(currentFrame < 0 )
        currentFrame = anim->frames.size() -1;
    
}
 


void Animator::onResetHandler(int & frame) {
    currentFrame = 0;
    pause();
    
}
void Animator::onUpdateHandler(int & frame) {
    
    
    currentFrame = frame;
}


