//
//  DMXManager.cpp
//  Sucre
//
//  Created by Martial on 05/11/2013.
//
//

#include "DMXManager.h"

void DMXManager::setup() {
    
    dmx.connect(0, 512);
    //dmx.listDevices();
    
}

void DMXManager::update(vector<ofPtr<LightObject> > * lights) {
    
    // update lights
    
    dmx.update();
    
    if(dmx.isConnected()) {
    
    for ( int i=0 ; i<lights->size(); i++ ) {
        
        // get dmx address
        
        ofPtr<LightObject>  light = lights->at(i);
        ofColor c = light->finalColor;
        
        int r = (int)ofClamp(c.r, 0, 255);
        int g = (int)ofClamp(c.g, 0, 255);
        int b = (int)ofClamp(c.b, 0, 255);
        
        
        int dmxAddress = light->data->dmxAddress;
        
        
        
        if(dmxAddress >= 1 && dmxAddress <= 512) {
        
           // ofLog(OF_LOG_NOTICE, "Dmx address %d", dmxAddress);
            
        dmx.setLevel(dmxAddress,      r);
        dmx.setLevel(dmxAddress+1,    g);
        dmx.setLevel(dmxAddress+2,    b);
        dmx.setLevel(dmxAddress+4,    0);
        dmx.setLevel(dmxAddress+6,    255);
            
        }
        
        
    }
        
    }
    
    
}