//
//  EffectsManager.cpp
//  Sucre
//
//  Created by Martial on 05/11/2013.
//
//

#include "EffectsManager.h"
#include "EffectSoundReactive.h"

EffectsManager::EffectsManager () {
    
    currentEffect = 1;
    strobSpeed = 0.0;
    
}

void EffectsManager::setup(vector<ofPtr<LightObject> > lights) {
    
    this->lights = lights;
    
    strobEffect = new EffectStrob();
    effects.push_back(strobEffect);
    
    EffectSoundReactive * sound = new EffectSoundReactive();
    effects.push_back(sound);
    
    for (int i=0; i<lights.size(); i++) {
        ofAddListener(lights[i]->readyToEffect, this, &EffectsManager::process);
    }
    
    
}

void EffectsManager::update() {
    
    strobEffect->strobSpeed = strobSpeed;
}

void EffectsManager::enableEffect(int index)  {
    
    if(!ofContains(effectsEnabled, index))
        effectsEnabled.push_back(index);
    
}

void EffectsManager::disableEffect(int index) {
    
    int posInVector = ofFind(effectsEnabled, index);
    effectsEnabled.erase(effectsEnabled.begin()+ posInVector);
    
}

void EffectsManager::disableAll() {
    effectsEnabled.clear();
}

void EffectsManager::process(SceneObjectEvent &e) {
    
    if(currentEffect < 0 )
        return;
    
    for (int i=0; i<effectsEnabled.size(); i++)
        effects[effectsEnabled[i]]->process(dynamic_cast<LightObject*>(e.object));
    
    //effects[currentEffect]->process(dynamic_cast<LightObject*>(e.object));
    
    
}