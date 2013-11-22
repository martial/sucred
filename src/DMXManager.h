//
//  DMXManager.h
//  Sucre
//
//  Created by Martial on 05/11/2013.
//
//

#ifndef __Sucre__DMXManager__
#define __Sucre__DMXManager__

#include "ofMain.h"
#include "ofxDmx.h"
#include "LightObject.h"

class DMXManager {
    
public :
    
    void setup(vector<ofPtr<LightObject> > * lights);
    void update();
    void onDmxUpdate(SceneObjectEvent & e);
    
    void reset(vector<ofPtr<LightObject> > * lights);
    
    
    ofxDmx dmx;
    
};

#endif /* defined(__Sucre__DMXManager__) */
