//
//  InspectorGui.cpp
//  Sucre
//
//  Created by Martial on 17/10/13.
//
//

#include "InspectorGui.h"

void InspectorGui::populate () {
    
    setDrawBack(true);
    setAutoDraw(false);
    
    addSpacer();
    addTextArea("INSPECTOR", "INSPECTOR", OFX_UI_FONT_LARGE);
    addSpacer();
    
    
    idTextArea = addTextArea("id", "ID");
    addSpacer();
    addTextArea("DMX", "DMX ADDRESS");
    dmxInput = addTextInput("DMX", "YOLO");
    
    
}

void InspectorGui::draw() {
    
    // position right
    setPosition(ofGetWidth() - rect->width, 0);
    ofxUICanvas::draw();
    
    
}

void InspectorGui::setId(float id) {
    
    idTextArea->setTextString("ID : " + ofToString(id));
    
}
void InspectorGui::setDmxAddress(float dmx) {
    
    dmxInput->setTextString(ofToString(dmx));
    
}