//
//  AnimatorManager.h
//  Sucre
//
//  Created by Martial on 21/11/2013.
//
//

#ifndef __Sucre__AnimatorManager__
#define __Sucre__AnimatorManager__

#include "ofMain.h"
#include "Animator.h"
#include "AnimationDataObject.h"

class AnimatorManager {
    
public:
    
    void setup();
    void update();
    
    
    void setAnimation(AnimationDataObject * anim, int animatorIndex);
    
    Animator * addAnimator();
    Animator * getAnimator(int index);
    
private:
    
    vector<Animator*> animators;
    
    
    
};

#endif /* defined(__Sucre__AnimatorManager__) */
