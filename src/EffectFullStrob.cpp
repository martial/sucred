//
//  EffectFullStrob.cpp
//  Sucre
//
//  Created by Martial on 20/11/2013.
//
//

#include "EffectFullStrob.h"
#include "Globals.h"

void EffectFullStrob::run() {
    
    //ofLog(OF_LOG_NOTICE, "GOGOGO");
    
    
    
    vector<ofPtr<LightObject> > lights = AbstractEffect::getLightObjects();
    vector<ofPtr<LightObject> > previewLights = Globals::get()->sceneManager->getScene(3)->getLightObjects();

    
    
    for (int i=0; i < lights.size(); i++) {
    
        lights[i]->finalColor = previewLights[i]->hasOverrideColor() ? previewLights[i]->overrideColor : previewLights[i]->color;
        
        if(ofGetFrameNum() % (int)strobSpeed > (int)(strobSpeed / 2) ) {
            
            
            lights[i]->finalColor.a = 255;
            
        
        } else {
            lights[i]->finalColor.a = 0;
        }
        
    }
     
    
    

    
}


void EffectFullStrob::process(LightObject * light) {
    
    /*
    if(ofGetFrameNum() % (int)strobSpeed > (int)(strobSpeed / 2) ) {
        
        light->finalColor.a = 0;
        
    } else {
        light->finalColor.a = 255;
    }
     
     */

    
}

