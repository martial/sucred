//
//  DataManager.cpp
//  Sucre
//
//  Created by Martial on 17/10/13.
//
//

#include "DataManager.h"

void DataManager::setup() {
    
    if ( config.loadFile("config.xml") ) {
        
    } else {
        config.saveFile("config.xml");
        config.loadFile("config.xml");
    }
    
   
    
    
}

void DataManager::assignData(vector<ofPtr<LightObject> > lights) {
    
    config.pushTag("root", 0);
    config.pushTag("lights", 0);
    
    for(int i = 0; i < lights.size(); i++){
        
        int nodeIndex = getTagForId(lights[i]->id);
        
        LightDataObject * dataObject    = new LightDataObject();
        dataObject->id                  =   config.getValue("light:id", -1, nodeIndex);
        dataObject->dmxAddress          =   config.getValue("light:dmx", -1, nodeIndex);
        lights[i]->data                 = dataObject;
        
        
    }

    popAll();
    
}

void DataManager::updateLights(vector<ofPtr<LightObject> > lights) {
    
    config.pushTag("root", 0);
    config.pushTag("lights", 0);
    
    
    
    for(int i = 0; i < lights.size(); i++){
        
        int nodeIndex = getTagForId(lights[i]->id);
        
        if(nodeIndex== - 1) {
        
            config.addTag("light");
            config.pushTag("light",i);
            config.setValue("id", lights[i]->id);
            config.setValue("dmx", "0");
            config.popTag();
            
        } else {
            
            config.pushTag("light",nodeIndex);
            config.setValue("id", lights[i]->id);
            config.setValue("dmx", lights[i]->data->dmxAddress);
            config.popTag();
            
        }
    }
    
    

    popAll();

    config.saveFile();
    

}

int DataManager::getTagForId(int id) {
    
    
    int nNodes = config.getNumTags("light");;
    
    
    // find tag
    bool bFound = false;
    for (int i=0; i<nNodes; i++) {
        
        //config.pushTag("light",i);
        int lightId = config.getValue("light:id", -1, i);
        

        
        if (id == lightId) {
           // config.popTag();
            return i;
        }
        
        //config.popTag();
    }
    
    
    return -1;
    
}

void DataManager::popAll() {
    
    while (config.getPushLevel() > 0  ) {
        config.popTag();
    }
    
    
}

