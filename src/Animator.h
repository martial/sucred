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
    
    
    Animator();
    void    setup();
    void    update();
    
    void    play();
    void    stop();
    void    pause();
    
    void    nextFrame();
    void    pushFrame();
    void    popFrame();
    
    
    
    void    setSpeed(float pct);
    float   getSpeed();
    
    void    setReverse(bool bReverse);
    bool    getReverse();
    
    bool    isPlaying();
    
    ofEvent<int>    tickEvent;
    
    float   speedPct;
    
    void setAnimation(AnimationDataObject * anim);

    int currentFrame;
    
    void onResetHandler(int & frame);
    void onUpdateHandler(int & frame);
    
    bool    bIsPlaying, bLoopPalyndrome;
    int     direction;
    
    AnimationDataObject * anim;


    
private:
    
    
    
    bool    bReverse;
    
    
    float   maxDelay;
    float   savedMillis;
    
    
};

#endif /* defined(__Sucre__Animator__) */
