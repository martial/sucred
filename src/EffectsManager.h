//
//  EffectsManager.h
//  Sucre
//
//  Created by Martial on 05/11/2013.
//
//

#ifndef __Sucre__EffectsManager__
#define __Sucre__EffectsManager__

#include "ofMain.h"
#include "AbstractEffect.h"
#include "LightObject.h"
#include "EffectStrob.h"
#include "EffectFullStrob.h"

class EffectsManager {
    
    
public:
    
    EffectsManager();
    void setup(vector<ofPtr<LightObject> > lights);
    void update();
    void run();
    void process(SceneObjectEvent & e);
    
    void applyFilters();
    
    void enableEffect(int index);
    void disableEffect(int index);
    void disableAll();
    
    EffectStrob     * strobEffect;
    EffectFullStrob * fullStrobEffect;
    
    void setStrobDmx(bool b);
    
    vector<AbstractEffect *>    effects;
    vector<ofPtr<LightObject> > lights;
    
    int currentEffect;
    
    vector<int> effectsEnabled;
    
    float strobSpeed;
    
    
};


#endif /* defined(__Sucre__EffectsManager__) */
