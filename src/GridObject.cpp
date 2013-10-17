//
//  GridObject.cpp
//  Sucre
//
//  Created by Martial on 16/10/13.
//
//

#include "GridObject.h"

GridObject::GridObject() {
    
    SceneObject();
    
}



void GridObject::setup() {
    
    
}

void GridObject::update() {
    

    
}

void GridObject::draw() {
    
    //SceneObject::draw();
    
    ofDrawGrid(250, 5, false, false, false, true);
    
}