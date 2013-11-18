//
//  EffectSoundReactive.h
//  Sucre
//
//  Created by Martial on 06/11/2013.
//
//

#ifndef __Sucre__EffectSoundReactive__
#define __Sucre__EffectSoundReactive__

#include "ofMain.h"
#include "AbstractEffect.h"
#include "Globals.h"

class EffectSoundReactive : public AbstractEffect {
    
public:
    
    void process(LightObject * light) {
        
        // TODO change this
        
        // split in left right
        // left < num / 2
        
        /*
        if(light->overrideColor.r > 0 ||light->overrideColor.g > 0 || light->overrideColor.b > 0  )
            return;
         */
        
        
        int numOfLights = Globals::instance()->sceneManager->getScene(0)->getLightObjects().size();
        int eqIndex;
        float value;
        
        if(light->id < numOfLights / 2 ) {
            
            eqIndex = (int)ofMap(light->id, 0, (numOfLights/2)-1, 0, 511);
            value = Globals::instance()->eq->left[eqIndex];
            
        } else {
            
            eqIndex = 511 - (int)ofMap(light->id, (numOfLights / 2)-1, numOfLights, 0, 511);
            
            
            value = Globals::instance()->eq->right[eqIndex];
            
        }
        
        
        
        
        light->finalColor *= value;
        
        
        
        
        
        
    }
    
};

#endif /* defined(__Sucre__EffectSoundReactive__) */
