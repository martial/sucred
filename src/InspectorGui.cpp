//
//  InspectorGui.cpp
//  Sucre
//
//  Created by Martial on 17/10/13.
//
//

#include "InspectorGui.h"
#include "Globals.h"

void InspectorGui::populate () {
    
    setDrawBack(true);
    setAutoDraw(false);
    
    addSpacer();
    addTextArea("INSPECTOR", "INSPECTOR", OFX_UI_FONT_LARGE);
    addSpacer();
    
    
    idTextArea  = addTextArea("id", "ID");
    addSpacer();
    dmxText     = addTextArea("DMXADR", "DMX ADDRESS");
    dmxInput    = addTextInput("DMX", "");
    
    ofAddListener(newGUIEvent,this,&InspectorGui::onGuiEvent);
}

void InspectorGui::draw() {
    
    // position right
    rect->height = ofGetHeight();
    float xPos = ( tween.isRunning()) ? tween.update() : ( bEnabled ) ? ofGetWidth() - rect->width : ofGetWidth();

    setPosition(xPos, 0);
    ofxUICanvas::draw();
    
    
}

void InspectorGui::setId(float id) {
    
    idTextArea->setVisible(true);
    idTextArea->setTextString("ID : " + ofToString(id));
    
}
void InspectorGui::setDmxAddress(float dmx) {
    
    dmxText->setVisible(true);
    dmxInput->setVisible(true);
    dmxInput->setTextString(ofToString(dmx));
    
}

void InspectorGui::setMulti(vector<SceneObject* > lights) {
    
    if(lights.size() == 1 ) {
        setId(lights[0]->id);
        setDmxAddress(lights[0]->data->dmxAddress);
        return;
    }
        
    
    idTextArea->setVisible(true);
    dmxInput->setVisible(false);
    dmxText->setVisible(false);
    
    string str ="Ids";
    for (int i=0; i<lights.size(); i++) {
        str += " " + ofToString(lights[i]->id);
    }
     idTextArea->setTextString(ofToString(lights.size()) + " SELECTED");
    
    
}

void InspectorGui::onGuiEvent(ofxUIEventArgs & e) {
    
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
    
    if( name == "DMX" )  {
        // update light id
        int id  = ofToInt(idTextArea->getTextString());
        int dmx = ofToInt(dmxInput->getTextString());
        
       

        Globals::instance()->scene->selecteds[0]->data->dmxAddress = dmx;
        Globals::instance()->scene->updateData();
    }
        
    
}


void InspectorGui::hide() {
    bEnabled = false;
    tween.setParameters(1,easingquint,ofxTween::easeOut, rect->x,ofGetWidth(),300, 0);
}

void InspectorGui::show () {
    bEnabled = true;
    tween.setParameters(1,easingquint,ofxTween::easeOut,rect->x, ofGetWidth() - rect->width,300, 0);
    
}

