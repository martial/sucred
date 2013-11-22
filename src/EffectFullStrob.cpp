//
//  EffectFullStrob.cpp
//  Sucre
//
//  Created by Martial on 20/11/2013.
//
//

#include "EffectFullStrob.h"

void EffectFullStrob::run() {
    
    /*
    vector<ofPtr<LightObject> > lights = AbstractEffect::getLightObjects();
    
    
    for (int i=0; i < lights.size(); i++) {
    
        
        if(ofGetFrameNum() % (int)strobSpeed > (int)(strobSpeed / 2) ) {
            
            lights[i]->finalColor.a = 0;
            lights[i]->strobDmx     = false;
        
        } else {
            lights[i]->finalColor.a = 255;
        }
        
    }
     
     */
    

    
}


void EffectFullStrob::process(LightObject * light) {
    
    if(ofGetFrameNum() % (int)strobSpeed > (int)(strobSpeed / 2) ) {
        
        light->finalColor.a = 0;
        //light->strobDmx     = strobDmx;
        
    } else {
        light->finalColor.a = 255;
    }

    
}

