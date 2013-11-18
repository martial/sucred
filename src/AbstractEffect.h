//
//  AbstractEffect.h
//  Sucre
//
//  Created by Martial on 05/11/2013.
//
//

#ifndef __Sucre__AbstractEffect__
#define __Sucre__AbstractEffect__

#include "ofMain.h"
#include "LightObject.h"

class AbstractEffect {
    
public:
    
    void setLightObjects(vector<LightObject* > lights);
    void run();
    
    virtual void process(LightObject * light){};
    
};

#endif /* defined(__Sucre__AbstractEffect__) */
