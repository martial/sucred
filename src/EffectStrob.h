//
//  EffectStrob.h
//  Sucre
//
//  Created by Martial on 05/11/2013.
//
//

#ifndef __Sucre__EffectStrob__
#define __Sucre__EffectStrob__

#include "ofMain.h"
#include "AbstractEffect.h"

class EffectStrob : public AbstractEffect {

public:
    
    void run();
    void process(LightObject * light);
    
    int strobSpeed;
};



#endif /* defined(__Sucre__EffectStrob__) */
