//
//  DMXManager.cpp
//  Sucre
//
//  Created by Martial on 05/11/2013.
//
//

#include "DMXManager.h"

void DMXManager::setup(vector<ofPtr<LightObject> > * lights) {
    
    dmx.connect(0, 512);
    //dmx.listDevices();
    
    for ( int i=0 ; i<lights->size(); i++ ) {
        
        ofPtr<LightObject>  light = lights->at(i);
        ofAddListener(light->readyToDmx, this, &DMXManager::onDmxUpdate);
    }
    
}

void DMXManager::onDmxUpdate(SceneObjectEvent & e) {
    
    LightObject * light = dynamic_cast<LightObject*>(e.object);
    
    ofColor c = light->finalColor;
    
    int r           = (int)ofClamp(c.r, 0, 255);
    int g           = (int)ofClamp(c.g, 0, 255);
    int b           = (int)ofClamp(c.b, 0, 255);
    int w           = (int)ofClamp(light->white, 0, 255);
    
    int dimmer      = (int)ofClamp(c.a, 0, 255);
    
    int dmxAddress = light->data->dmxAddress;
    
    if(dmxAddress >= 1 && dmxAddress <= 512) {
                
        dmx.setLevel(dmxAddress,      r);
        dmx.setLevel(dmxAddress+1,    g);
        dmx.setLevel(dmxAddress+2,    b);
        dmx.setLevel(dmxAddress+3,    w);
        dmx.setLevel(dmxAddress+4,    0);
        dmx.setLevel(dmxAddress+6,    255);
        
        // strob
        
        if(light->strobDmx)
            dmx.setLevel(dmxAddress+5,    255);
        
        // override alpha
        dmx.setLevel(dmxAddress+6,    dimmer);
        
    }

    
    
    
}

void DMXManager::update() {
    
    // update lights
    
    dmx.update();
    
    if(dmx.isConnected()) {
    }
        
}

void DMXManager::reset(vector<ofPtr<LightObject> > * lights) {
    
    for ( int i=0 ; i<lights->size(); i++ ) {
        
        ofPtr<LightObject>  light = lights->at(i);
        
        ofColor c = light->finalColor;
        
        int r           = 0;
        int g           = 0;
        int b           = 0;
        int w           = 0;
        
        int dimmer      = 0;
        
        int dmxAddress = light->data->dmxAddress;
        
        if(dmxAddress >= 1 && dmxAddress <= 512) {
            
            dmx.setLevel(dmxAddress,      r);
            dmx.setLevel(dmxAddress+1,    g);
            dmx.setLevel(dmxAddress+2,    b);
            dmx.setLevel(dmxAddress+3,    w);
            dmx.setLevel(dmxAddress+4,    0);
            dmx.setLevel(dmxAddress+6,    255);
            
            // strob
            
  
            dmx.setLevel(dmxAddress+5,    0);
            
            // override alpha
            dmx.setLevel(dmxAddress+6,    dimmer);
            
        }

        
    }
    
}