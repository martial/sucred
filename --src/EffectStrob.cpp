//
//  EffectStrob.cpp
//  Sucre
//
//  Created by Martial on 05/11/2013.
//
//

#include "EffectStrob.h"


void EffectStrob::run() {
    
    
    
}


void EffectStrob::process(LightObject * light) {
   
    //AbstractEffect::process(light);
    
    light->strobDmx     = strobDmx;
    
    
    
    if(strobDmx) {
        ofLog(OF_LOG_NOTICE, "What the ..");
        return;
    }
    
    
    
    if(ofGetFrameNum() % (int)strobSpeed > (int)(strobSpeed / 2) ) {

        light->finalColor.a = 0;
        light->strobDmx     = strobDmx;
        
        
    } else {
        
        //ofLog(OF_LOG_NOTICE, "strobbbz");
        //light->finalColor.a = 255;
    }
    
    
}


