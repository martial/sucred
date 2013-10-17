//
//  LightObject.cpp
//  Sucre
//
//  Created by Martial on 16/10/13.
//
//

#include "LightObject.h"

LightObject::LightObject() {
    
    InteractiveSceneObject::InteractiveSceneObject();
    bSelected = false;
    
}



void LightObject::setup() {
    
    
}

void LightObject::update() {
    
    
}



void LightObject::setRadius(float radius) {
    
    this->radius = radius;
    boundingBox.set(-radius , -radius, radius*2, radius*2);
}

void LightObject::draw(float *iMatrix, bool debug ) {
    
    

     
     SceneObject::draw(iMatrix, debug);
    
    if(bSelected) {
        ofSetColor(255);
        drawBoundingBox();
    }
    else
        ofSetColor(255);
    
    
     ofCircle(0,0, radius);
    
}