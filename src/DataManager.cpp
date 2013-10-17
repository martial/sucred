//
//  DataManager.cpp
//  Sucre
//
//  Created by Martial on 17/10/13.
//
//

#include "DataManager.h"

void DataManager::loadConfig() {
    
    if ( config.loadFile("config.xml") ) {
        
    } else {
        config.saveFile("config.xml");
        config.loadFile("config.xml");
    }
    
   
    
    
}

void DataManager::updateLight(ofPtr<LightObject> light) {

    config.pushTag("root");
    config.pushTag("lights");
    
    int nNodes = config.getNumTags("light");;
    
    // find tag
    bool bFound = false;
    for (int i=0; i<nNodes; i++) {
        
        int id = config.getAttribute("light", "id", 0, i);
        
        if (id == light->id) {
            config.setAttribute("light", "id", light->id, i);
            bFound = true;
        }
        
    }
    
    if (!bFound) {
        config.addTag("light");
    }
    
    config.popTag();
    config.popTag();

    

}