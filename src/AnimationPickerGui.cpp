//
//  AnimationPickerGui.cpp
//  Sucre
//
//  Created by Martial on 23/10/2013.
//
//

#include "AnimationPickerGui.h"
#include "Globals.h"

void AnimationPickerGui::populate () {
    
        
    setDrawBack(true);
    setAutoDraw(false);
    
    
    
    addSpacer();
    
    
    addTextArea("ANIMS", "ANIMS", OFX_UI_FONT_LARGE);
    addSpacer();
    
     
     
    
    setScrollableDirections(false, true);
    
    setScrollAreaToScreenHeight();
    
    //autoSizeToFitWidgets();
    getRect()->setHeight(ofGetHeight());

    //setDrawWidgetPadding(true);
    
    autoSizeToFitWidgets();

    show();
    
    
    /*
    vector<ofxUIWidget*> spacers = getWidgetsOfType(OFX_UI_WIDGET_SPACER);
    
    for(int i = 0; i < spacers.size(); i++)
    {
        ofxUISpacer *s = (ofxUISpacer *) spacers[i];
        s->toggleVisible();
    }
     
     */

    
    
    ofAddListener(ofEvents().windowResized, this, &AnimationPickerGui::onWindowResize);
    ofAddListener(newGUIEvent,this,&AnimationPickerGui::onGuiEvent);
}

void AnimationPickerGui::setAnims(vector<AnimationDataObject*> anims) {
    
    
    
   for (int i=0; i<toggles.size(); i++) {
       removeWidget(toggles[i]);
   }
    
    toggles.clear();
     
    
    
    for (int i=0; i<anims.size(); i++) {
        toggles.push_back(addToggle(anims[i]->name, false));
        
    }
    
    autoSizeToFitWidgets();
    
}

void AnimationPickerGui::onWindowResize(ofResizeEventArgs &e) {
    
    
    
    setScrollAreaToScreenHeight();
    
    autoSizeToFitWidgets();
    //getRect()->setHeight(ofGetHeight());
    
    
}


void AnimationPickerGui::hide() {
    bEnabled = false;
    tween.setParameters(1,easingquint,ofxTween::easeOut, rect->x, ofGetWidth(),300, 0);
}

void AnimationPickerGui::show () {
    bEnabled = true;
    tween.setParameters(1,easingquint,ofxTween::easeOut, rect->x, ofGetWidth() - (rect->width * 2),300, 0);
    
}



void AnimationPickerGui::draw() {
    
    //setScrollAreaToScreenHeight();

    // position right
    //rect->height = ofGetHeight();
    
    float xPos = ( tween.isRunning()) ? tween.update() : ( bEnabled ) ? ofGetWidth() - ( rect->width * 2 ) : ofGetWidth();
    //getRect()->x = xPos;
    rect->x = xPos;
    getSRect()->x = xPos;
    ofxUICanvas::draw();
    
    
}

void AnimationPickerGui::onGuiEvent(ofxUIEventArgs & e) {
    
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
    for (int i=0;  i<toggles.size(); i++) {
        if(toggles[i]->getName() != name)
            toggles[i]->ofxUIButton::setValue(false);
    }
    
    Globals::instance()->animData->setAnimation(name);

    
    
}


