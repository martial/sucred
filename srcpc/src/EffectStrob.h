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
    
    EffectStrob() {
        strobDmx = false;
    }
    void    run();
    void    process(LightObject * light);
    
    int     strobSpeed;
    bool    strobDmx;
};



#endif /* defined(__Sucre__EffectStrob__) */
