//
//  EffectFullStrob.h
//  Sucre
//
//  Created by Martial on 20/11/2013.
//
//

#ifndef __Sucre__EffectFullStrob__
#define __Sucre__EffectFullStrob__

#include "ofMain.h"
#include "AbstractEffect.h"

class EffectFullStrob : public AbstractEffect {
    
public:
    
    EffectFullStrob() {
    }
    void    run();
    void    process(LightObject * light);
    
    int     strobSpeed;
    
};



#endif /* defined(__Sucre__EffectFullStrob__) */
