//
//  LightObject.cpp
//  Sucre
//
//  Created by Martial on 16/10/13.
//
//

#include "LightObject.h"

LightObject::LightObject() {
    
    InteractiveSceneObject();
    
    
}



void LightObject::setup() {
    
    
}

void LightObject::update() {
    
    
}



void LightObject::setRadius(float radius) {
    
    this->radius = radius;
    boundingBox.set(-radius / 2, radius/2, radius, radius);
}

void LightObject::draw(float *iMatrix, bool debug ) {
    
    

     
     SceneObject::draw(iMatrix, debug);
    
    if(bSelected)
        ofSetColor(0,255,0);
    else
        ofSetColor(255, 0, 0);
    
    
     ofCircle(-radius / 2, radius/2, radius);
    
}