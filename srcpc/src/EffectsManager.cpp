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
    strobSpeed = 4.0;
    
    // init in constructor 
    strobEffect = new EffectStrob();
    
    
}

void EffectsManager::setup(vector<ofPtr<LightObject> > lights) {
    
    this->lights = lights;
    
    //strobEffect = new EffectStrob();
    effects.push_back(strobEffect);
    
    EffectSoundReactive * sound = new EffectSoundReactive();
    effects.push_back(sound);
    
    fullStrobEffect = new EffectFullStrob();
    fullStrobEffect->setLightObjects(lights);

    effects.push_back(fullStrobEffect);
    
    for (int i=0; i<lights.size(); i++) {
        //ofAddListener(lights[i]->readyToEffect, this, &EffectsManager::process);
    }
    
    
}

void EffectsManager::update() {
    
    strobEffect->strobSpeed     = strobSpeed;
    fullStrobEffect->strobSpeed = strobSpeed;
    
   
}

void EffectsManager::run () {
    for(int i=0; i<effectsEnabled.size(); i++) {
        effects[effectsEnabled[i]]->run();
    }
}

void EffectsManager::enableEffect(int index)  {
    
    if(!ofContains(effectsEnabled, index))
        effectsEnabled.push_back(index);
    
}

void EffectsManager::disableEffect(int index) {
    
    
    int posInVector = ofFind(effectsEnabled, index);
    
    if(posInVector >= effectsEnabled.size() )
        return;
    
    effectsEnabled.erase(effectsEnabled.begin()+ posInVector);
    
}

void EffectsManager::disableAll() {
    effectsEnabled.clear();
}

void EffectsManager::applyFilters() {
    
    if(currentEffect < 0 )
        return;
    
    
    
    for (int i=0; i<effectsEnabled.size(); i++) {
        
        for (int j=0; j<lights.size();j++) {
            //lights[j].get()->finalColor.set(255, 0, 0);
            effects[effectsEnabled[i]]->process(lights[j].get());
        }
        
    }
    
    
}

void EffectsManager::process(SceneObjectEvent &e) {
    
    if(currentEffect < 0 )
        return;
    
    for (int i=0; i<effectsEnabled.size(); i++)
        effects[effectsEnabled[i]]->process(dynamic_cast<LightObject*>(e.object));
    
    //effects[currentEffect]->process(dynamic_cast<LightObject*>(e.object));
    
    
}