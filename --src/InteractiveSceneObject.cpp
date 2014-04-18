//
//  InteractiveSceneObject.cpp
//  Sucre
//
//  Created by Martial on 16/10/13.
//
//

#include "InteractiveSceneObject.h"
#include "Globals.h"


InteractiveSceneObject::InteractiveSceneObject () {
    
    SceneObject();
    bSelected       = false;
    bHightlighted   = false;

}

void InteractiveSceneObject::enableMouse() {
    
    ofAddListener(ofEvents().mousePressed, this, &InteractiveSceneObject::onMousePressed);
    
    
}

void InteractiveSceneObject::disableMouse() {
    
    ofRemoveListener(ofEvents().mousePressed, this, &InteractiveSceneObject::onMousePressed);
    
}


void InteractiveSceneObject::onMousePressed(ofMouseEventArgs & e) {
    
    
    
    if(hitTest(e.x, e.y) &&  Globals::instance()->gui->getEmptyUIZone().inside(e.x, e.y)) {
        
        SceneObjectEvent e (this) ;
        ofNotifyEvent(mousePressed, e);
        
    }
    
}