//
//  DataManager.h
//  Sucre
//
//  Created by Martial on 17/10/13.
//
//

#ifndef __Sucre__DataManager__
#define __Sucre__DataManager__

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "LightObject.h"

class DataManager {
    
public:
    
    void loadConfig();
    
    
    void updateLight(ofPtr<LightObject> light);
    
    
    
    ofxXmlSettings config;
    
    
    
    
};

#endif /* defined(__Sucre__DataManager__) */
