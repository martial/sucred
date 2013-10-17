//
//  InteractiveSceneObject.cpp
//  Sucre
//
//  Created by Martial on 16/10/13.
//
//

#include "InteractiveSceneObject.h"

InteractiveSceneObject::InteractiveSceneObject () {
    
    SceneObject();
    bSelected = false;

}

void InteractiveSceneObject::enableMouse() {
    
    ofAddListener(ofEvents().mousePressed, this, &InteractiveSceneObject::onMousePressed);
    
    
}

void InteractiveSceneObject::disableMouse() {
    
    ofRemoveListener(ofEvents().mousePressed, this, &InteractiveSceneObject::onMousePressed);
    
}


void InteractiveSceneObject::onMousePressed(ofMouseEventArgs & e) {
    
    
    ofLog(OF_LOG_NOTICE, "WHATT");
    
    if(hitTest(ofGetMouseX(), ofGetMouseY()) ) {
        bSelected = false;
    }
    
}