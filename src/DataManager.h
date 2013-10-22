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
    
    void setup();
    void assignData(vector<ofPtr<LightObject> > lights);
    void updateLights(vector<ofPtr<LightObject> > lights);
    int getTagForId(int id);
    void popAll();
    
    ofxXmlSettings config;
    
    
    
    
};

#endif /* defined(__Sucre__DataManager__) */
