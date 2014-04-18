//
//  AnimatorManager.cpp
//  Sucre
//
//  Created by Martial on 21/11/2013.
//
//

#include "AnimatorManager.h"

void AnimatorManager::setup() {
    
}

void AnimatorManager::update() {
    
    for(int i=0; i<animators.size(); i++ ) {
        animators[i]->update();
    }
    
}

Animator *  AnimatorManager::addAnimator() {
    
    Animator * animator = new Animator();
    animator->setup();
    animators.push_back(animator);
    
    return  animator;
    
}

Animator *  AnimatorManager::getAnimator(int index) {
    
    if( index >= animators.size() )
       return NULL;
    
    Animator * animator = animators[index];
    return  animator;
    
}

void AnimatorManager::setAnimation(AnimationDataObject * anim, int animatorIndex) {
    
    if(animatorIndex >= animators.size() )
       return;
       
    animators[animatorIndex]->setAnimation(anim);
    
}