//
//  ColorManager.cpp
//  Sucre
//
//  Created by Martial on 31/10/2013.
//
//

#include "ColorManager.h"
#include "Globals.h"

void ColorManager::setup() {
    
    
}


void ColorManager::setLightObjects(vector<ofPtr<LightObject> >  lightObjects) {
    
    this->lightObjects = lightObjects;
    setGlobalColor(ofColor(255), 255);
}


void ColorManager::update() {
    
    
}


void ColorManager::setGlobalColor(ofColor c, float white){
    
    for ( int i=0; i<lightObjects.size(); i++ ) {
        
        ofPtr<LightObject> obj = lightObjects[i];
        obj->color = c;
        obj->white = white;
    }
    
}

void ColorManager::setGlobalColor(int sceneIndex, ofColor c, float white) {
    
    vector<ofPtr<LightObject> >  lights = Globals::get()->sceneManager->getScene(sceneIndex)->getLightObjects();
    
    for ( int i=0; i<lights.size(); i++ ) {
        
        ofPtr<LightObject> obj = lights[i];
        obj->color = c;
        obj->white = white;
    }
    
}



void ColorManager::setGlobalDecay(float pct) {
    
    for ( int i=0; i<lightObjects.size(); i++ ) {
        
        ofPtr<LightObject> obj = lightObjects[i];
        obj->decay = pct;
        
    }

    
}

void ColorManager::setGlobalDecay(int sceneIndex,float pct) {
    
    vector<ofPtr<LightObject> >  lights = Globals::get()->sceneManager->getScene(sceneIndex)->getLightObjects();
    
    for ( int i=0; i<lights.size(); i++ ) {
        
        ofPtr<LightObject> obj = lights[i];
        obj->decay = pct;
    }
    
}

void ColorManager::setGlobalAlpha(float pct) {
    
    for ( int i=0; i<lightObjects.size(); i++ ) {
        
        ofPtr<LightObject> obj = lightObjects[i];
        obj->overrideAlpha = pct;
       // obj->color.set(255);
        
    }
    
}

void ColorManager::setGlobalAlpha(int sceneIndex, float pct) {
    
    vector<ofPtr<LightObject> >  lights = Globals::get()->sceneManager->getScene(sceneIndex)->getLightObjects();

    for ( int i=0; i<lights.size(); i++ ) {
        
        ofPtr<LightObject> obj = lights[i];
        obj->overrideAlpha = pct;
        // obj->color.set(255);
        
    }
    
}


void ColorManager::setColorScheme(ColorDataObject * colorData) {

    
    resetColors();
    
    for (int i=0; i < colorData->colors.size(); i++) {
        
        
        for ( int j=0; j<lightObjects.size(); j++ ) {
            
            ofPtr<LightObject> obj = lightObjects[j];
            
            if(colorData->colors[i].id == obj->id) {
                
                obj->overrideColor.r = colorData->colors[i].color.r;
                obj->overrideColor.g = colorData->colors[i].color.g;
                obj->overrideColor.b = colorData->colors[i].color.b;
                


                
            }
            
        }
        
    }

}

void ColorManager::setColorScheme(int sceneIndex, ColorDataObject * colorData) {
    
    
    //resetColors();
    
    vector<ofPtr<LightObject> >  lights = Globals::get()->sceneManager->getScene(sceneIndex)->getLightObjects();

    
    for (int i=0; i < colorData->colors.size(); i++) {
        
        
        for ( int j=0; j<lights.size(); j++ ) {
            
            ofPtr<LightObject> obj = lights[j];
            //obj->overrideColor.set(0, 0, 0);
            //obj->color.set(255,255,255);
            
            if(colorData->colors[i].id == obj->id) {
                
                obj->overrideColor.r = colorData->colors[i].color.r;
                obj->overrideColor.g = colorData->colors[i].color.g;
                obj->overrideColor.b = colorData->colors[i].color.b;
                
                
                
                
            }
            
        }
        
    }
    
}

void ColorManager::resetColors() {
    
    for ( int i=0; i<lightObjects.size(); i++ ) {
        
        ofPtr<LightObject> obj = lightObjects[i];
        obj->overrideColor.set(0, 0, 0);
        obj->color.set(255,255,255);
        
    }
    
}