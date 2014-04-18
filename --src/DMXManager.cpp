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
    
    this->lights = lights;
    //dmx.listDevices();
    
    
    
    
    for ( int i=0 ; i<lights->size(); i++ ) {
        
        ofPtr<LightObject>  light = lights->at(i);
        ofAddListener(light->readyToDmx, this, &DMXManager::onDmxUpdate);
    }
    
    hasInit = false;
    hasShutdown = false;
    
}

void DMXManager::onDmxUpdate(SceneObjectEvent & e) {
    
    if(hasShutdown)
        return;
    
    LightObject * light = dynamic_cast<LightObject*>(e.object);
    
    ofColor c = light->finalColor;
    
    int r           = (int)ofClamp(c.r, 0, 255);
    int g           = (int)ofClamp(c.g, 0, 255);
    int b           = (int)ofClamp(c.b, 0, 255);
    int w           = (int)ofClamp(light->white, 0, 255);
    
    if (r == 0 && b == 0 && g == 0) {
        w = 0;
    }
    
    int dimmer      = (int)ofClamp(c.a, 0, 255);
    //dimmer = 255;
    
    int dmxAddress = light->data->dmxAddress;
    
    //return;
    
    
    if(dmxAddress >= 1 && dmxAddress <= 512) {
                
        dmx.setLevel(dmxAddress,      r);
        dmx.setLevel(dmxAddress+1,    g);
        dmx.setLevel(dmxAddress+2,    b);
        dmx.setLevel(dmxAddress+3,    w);
        dmx.setLevel(dmxAddress+4,    0);
        dmx.setLevel(dmxAddress+6,    255);
        
        
      //  ofLog(OF_LOG_NOTICE, "--- %d", dmxAddress);
       // ofLog(OF_LOG_NOTICE, "adress r g b w %d %d %d %d",r, g, b, w);
        
        // strob
        
        if(light->strobDmx) {
            //ofLog(OF_LOG_NOTICE, "strob dmx");
            dmx.setLevel(dmxAddress+5,    255);
        } else {
            dmx.setLevel(dmxAddress+5,    0);
        }
        // override alpha
        dmx.setLevel(dmxAddress+6,    dimmer);
        
    }

    
    
    
}

void DMXManager::disconnect() {
    
    for ( int i=0 ; i<lights->size(); i++ ) {
        
        ofPtr<LightObject>  light = lights->at(i);
        ofRemoveListener(light->readyToDmx, this, &DMXManager::onDmxUpdate);
    }

    
    //dmx.disconnect();
    hasShutdown = true;
    
}

void DMXManager::update() {
    
    // update lights
    
    dmx.update();
    
    if(dmx.isConnected()) {
        
        
        if(!hasInit) {
            reset(lights);
            hasInit = true;
        }
        
        /*
        ofLog(OF_LOG_NOTICE, "update");
        
        dmx.setLevel(57,      255);
        dmx.setLevel(57+1,    0);
        dmx.setLevel(57+2,    0);
        dmx.setLevel(57+3,    0);
        dmx.setLevel(57+4,    0);
        dmx.setLevel(57+6,    255);
         
         */
        
        
        
        return;
    }
        
}

void DMXManager::reset(vector<ofPtr<LightObject> > * lights) {
    
    for ( int i=0 ; i<lights->size(); i++ ) {
        
        ofPtr<LightObject>  light = lights->at(i);
        
        ofColor c = light->finalColor;
        
        int dmxAddress = light->data->dmxAddress;
        
        //ofLog(OF_LOG_NOTICE, "RESET %d", dmxAddress);
        
        if(dmxAddress >= 1 && dmxAddress <= 512) {
            
            dmx.setLevel(dmxAddress,      0);
            dmx.setLevel(dmxAddress+1,    0);
            dmx.setLevel(dmxAddress+2,    0);
            dmx.setLevel(dmxAddress+3,    0);
            dmx.setLevel(dmxAddress+4,    0);
            dmx.setLevel(dmxAddress+5,    0);
            dmx.setLevel(dmxAddress+6,    0);
            
           // ofLog(OF_LOG_NOTICE, "go %d", dmxAddress);

          
            
        }

        
    }
    
}

void DMXManager::send(int channel, int value) {
    
    dmx.setLevel(channel, value);
    
}