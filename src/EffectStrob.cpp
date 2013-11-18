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
    
    
    if(ofGetFrameNum() % (int)strobSpeed > (int)(strobSpeed / 2) ) {

        light->finalColor.a = 0;
        
    } else {
        
        //light->finalColor.a = 255;
        
    }
    
    
}


