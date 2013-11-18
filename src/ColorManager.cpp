//
//  ColorManager.cpp
//  Sucre
//
//  Created by Martial on 31/10/2013.
//
//

#include "ColorManager.h"

void ColorManager::setup() {
    
    
}


void ColorManager::setLightObjects(vector<ofPtr<LightObject> >  lightObjects) {
    
    this->lightObjects = lightObjects;
    setGlobalColor(ofColor(255));
}


void ColorManager::update() {
    
    
}


void ColorManager::setGlobalColor(ofColor c){
    
    for ( int i=0; i<lightObjects.size(); i++ ) {
        
        ofPtr<LightObject> obj = lightObjects[i];
        obj->color = c;
        
    }
    
}

void ColorManager::setGlobalColor(float r,float g, float b) {
    
    
}

void ColorManager::setGlobalDecay(float pct) {
    
    for ( int i=0; i<lightObjects.size(); i++ ) {
        
        ofPtr<LightObject> obj = lightObjects[i];
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

void ColorManager::resetColors() {
    
    for ( int i=0; i<lightObjects.size(); i++ ) {
        
        ofPtr<LightObject> obj = lightObjects[i];
        obj->overrideColor.set(0, 0, 0);
        obj->color.set(255,255,255);
        
    }
    
}