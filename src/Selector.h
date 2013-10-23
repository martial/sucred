//
//  Selector.h
//  Sucre
//
//  Created by Martial on 17/10/13.
//
//

#ifndef __Sucre__Selector__
#define __Sucre__Selector__

#include "ofMain.h"

class SelectorEvent : public ofEventArgs {
    
public:
    SelectorEvent (ofRectangle selection ) {
        this->selection = selection;
    }
    ofRectangle selection;
    
};

/* --------------- */

class Selector {
    
public:
    
    Selector() {
        bDraw = false;
    }
    
    void draw() {
        
        ofSetColor(255);
        
      
        ofNoFill();
        ofRect(selection);
        ofFill();
        
        
        
    }
    
    
    void enable() {
        
        ofAddListener(ofEvents().mousePressed, this, &Selector::onMousePressed);
        ofAddListener(ofEvents().mouseReleased, this, &Selector::onMouseReleased);
        ofAddListener(ofEvents().mouseDragged, this, &Selector::onMouseDrag);
        
    }
    
    
    void disable() {
        
        ofRemoveListener(ofEvents().mousePressed, this, &Selector::onMousePressed);
        ofRemoveListener(ofEvents().mouseReleased, this, &Selector::onMouseReleased);
        ofRemoveListener(ofEvents().mouseDragged, this, &Selector::onMouseDrag);
        
    }
    
    
    void onMousePressed(ofMouseEventArgs & e) {
        clickedPoint.set(ofGetMouseX(), ofGetMouseY());
    }
    
    void onMouseReleased(ofMouseEventArgs & e) {
        
        if( selection.getArea() > 100 ) {
            SelectorEvent e(selection);
            ofNotifyEvent(selectorLock, e);
        }
        selection.set(0.0, 0.0, 0.0, 0.0);
    }
    
    void onMouseDrag(ofMouseEventArgs & e) {
        selection.set(clickedPoint.x, clickedPoint.y, e.x - clickedPoint.x, e.y - clickedPoint.y);
        
    }
    
    ofEvent<SelectorEvent> selectorLock;
    
    
private:
    
    
    bool        bDraw;
    ofVec2f     clickedPoint;
    ofRectangle selection;
    
};



#endif /* defined(__Sucre__Selector__) */
