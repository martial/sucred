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
    
    void setLightObjects(vector<ofPtr<LightObject> > lights);
    
    virtual void run();
    virtual void process(LightObject * light){};
    
    
    
    
    
    
protected:
    
    virtual vector<ofPtr<LightObject> > getLightObjects() {
        return lights;
    }
    
private:
    
    vector<ofPtr<LightObject> > lights;
    
    
};

#endif /* defined(__Sucre__AbstractEffect__) */
