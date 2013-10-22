//
//  EditorInspectorGUi.cpp
//  Sucre
//
//  Created by Martial on 21/10/13.
//
//

#include "EditorInspectorGui.h"
#include "Globals.h"

void EditorInspectorGui::populate () {
    
    setDrawBack(true);
    setAutoDraw(false);
    
    addSpacer();
    addTextArea("INSPECTOR", "INSPECTOR", OFX_UI_FONT_LARGE);
    addSpacer();
    
    urlText     = addTextArea("URL", "...", OFX_UI_FONT_SMALL);
    frameText   = addTextArea("FRAME", "FRAME : 1/1");
    
    addButton("+ ADD FRAME", false);
    
    addSpacer();

    
    ofAddListener(newGUIEvent,this,&EditorInspectorGui::onGuiEvent);
}

void EditorInspectorGui::setUrl(string url) {
    
    urlText->setTextString(url);
}

void EditorInspectorGui::setFrame(int frame, int total) {
    
    frameText->setTextString(ofToString(frame) + "/" + ofToString(total));
    
}

void EditorInspectorGui::hide() {
    bEnabled = false;
    tween.setParameters(1,easingquint,ofxTween::easeOut, rect->x, ofGetWidth(),300, 0);
}

void EditorInspectorGui::show () {
    bEnabled = true;
    tween.setParameters(1,easingquint,ofxTween::easeOut, rect->x, ofGetWidth() - rect->width,300, 0);
    
}



void EditorInspectorGui::draw() {
    
    // position right
    rect->height = ofGetHeight();
    
    float xPos = ( tween.isRunning()) ? tween.update() : ( bEnabled ) ? ofGetWidth() - rect->width : ofGetWidth();
    
    setPosition(xPos, 0);
    ofxUICanvas::draw();
    
    
}

void EditorInspectorGui::onGuiEvent(ofxUIEventArgs & e) {
    
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
    if( name =="+ ADD FRAME") {
        
        Globals::instance()->animData->addFrame();
        setFrame(Globals::instance()->animData->currentFrame + 1, Globals::instance()->animData->currentAnimation->getNumFrames());
        
    }
    
    
}