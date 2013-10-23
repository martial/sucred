//
//  Animator.h
//  Sucre
//
//  Created by Martial on 23/10/2013.
//
//

#ifndef __Sucre__Animator__
#define __Sucre__Animator__

#include "ofMain.h"
#include "Scene.h"
#include "AnimationDataObject.h"

class Animator {
    
    
public:
    
    
    
    void    setup(Scene * scene);
    void    update();
    
    void    play();
    void    stop();
    void    pause();
    
    
    
    void    setSpeed(float pct);
    float   getSpeed();
    
    void    setReverse(bool bReverse);
    bool    getReverse();
    
    bool    isPlaying();
    
    ofEvent<int>    tickEvent;
    
    float   speedPct;
    
    void setAnimation(AnimationDataObject * anim);

    
    
private:
    
    
    
    bool    bReverse;
    bool    bIsPlaying;
    
    
    float   maxDelay;
    float   savedMillis;
    
    Scene * scene;
    AnimationDataObject * anim;
    
};

#endif /* defined(__Sucre__Animator__) */
