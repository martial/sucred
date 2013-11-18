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
    
    
    selected = NULL;
    
    setDrawBack(true);
    setAutoDraw(false);
    
    addSpacer();
    addTextArea("INSPECTOR", "INSPECTOR", OFX_UI_FONT_LARGE);
    addSpacer();
    
    
    idTextArea  = addTextArea("id", "ID");
    addSpacer();
    
    /*
    dmxText     = addTextArea("DMXADR", "DMX ADDRESS");
    dmxInput    = addTextInput("DMX", "");
     
     */
    
    rSlider = new ofxUIRotarySlider(24*2.0, 0.0, 255, &r, "R");
    gSlider = new ofxUIRotarySlider(24*2.0, 0.0, 255, &g, "G");
    bSlider = new ofxUIRotarySlider(24*2.0, 0.0, 255, &b, "B");
    
    addWidgetDown(rSlider);
    addWidgetRight(gSlider);
    addWidgetRight(bSlider);
    
    hsbPicker = addHsbPicker("HSB");
    
    
    permanentToggle = addToggle("PERMANENT", false);
    
    addSpacer();
    
    
    addLabelButton("RESET COLORS", false, true);
    addSpacer();
    addLabelButton("NEW COLOR SCHEME", false, true);
    addLabelButton("SAVE COLOR SCHEME", false, true);
    addLabelButton("DELETE COLOR SCHEME", false, true);
    colorInput = addTextInput("COLOR NAME", "");

    
    ofAddListener(newGUIEvent,this,&InspectorGui::onGuiEvent);
}

void InspectorGui::draw() {
    
    
    
    rSlider->setColorFill(ofxUIColor(r,g,b));
    gSlider->setColorFill(ofxUIColor(r,g,b));
    bSlider->setColorFill(ofxUIColor(r,g,b));
    
    rSlider->setColorFillHighlight(ofxUIColor(r,g,b));
    gSlider->setColorFillHighlight(ofxUIColor(r,g,b));
    bSlider->setColorFillHighlight(ofxUIColor(r,g,b));
    
    // position right
    rect->height = ofGetHeight();
    float xPos = ( tween.isRunning()) ? tween.update() : ( bEnabled ) ? ofGetWidth() - rect->width : ofGetWidth();

    setPosition(xPos, 0);
    ofxUICanvas::draw();
    
    
}

void InspectorGui::setId(float id) {
    
    show();
    idTextArea->setVisible(true);
    idTextArea->setTextString("ID : " + ofToString(id));
    
}
void InspectorGui::setDmxAddress(float dmx) {
    
    /*
    show();
    dmxText->setVisible(true);
    dmxInput->setVisible(true);
    dmxInput->setTextString(ofToString(dmx));
     */
    
    
}

void InspectorGui::setMulti(vector<SceneObject* > lights) {
    
    
    selected = NULL;
    
    
    if(lights.size() == 0 )
        hide();
    else
        show();
    
    if(lights.size() == 1 ) {
        selected = lights[0];
        setId(selected->id);
        setDmxAddress(selected->data->dmxAddress);
        return;
        
    }
        
    
    idTextArea->setVisible(true);
    /*
    dmxInput->setVisible(false);
    dmxText->setVisible(false);
     */
    
    string str ="Ids";
    for (int i=0; i<lights.size(); i++) {
        str += " " + ofToString(lights[i]->id);
    }
     idTextArea->setTextString(ofToString(lights.size()) + " SELECTED");
    
    
    this->lights = lights;
    
}

void InspectorGui::onGuiEvent(ofxUIEventArgs & e) {
    
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
    
    if( name == "DMX" )  {
        
        if(!selected)
            return;
        // update light id
        int id  = ofToInt(idTextArea->getTextString());
        int dmx = ofToInt(dmxInput->getTextString());

        selected->data->dmxAddress = dmx;
        
        
        Globals::instance()->sceneManager->getScene(0)->updateData();
    }
    
    if (name == "HSB") {
        
        ofColor c = hsbPicker->getColor();
        
        r = c.r;
        g = c.g;
        b = c.b;
        
        for (int i =0; i<lights.size(); i++) {
            lights[i]->overrideColor.set(r, g, b);
            lights[i]->bPermanentOverride = permanentToggle->getValue();

        }
        
    }
    
    if (name == "RESET COLORS") {
        
        for (int i =0; i<lights.size(); i++) {
            lights[i]->overrideColor.set(0,0,0);
            lights[i]->bPermanentOverride = false;
            
            
            
        }
        
      
        
    }
    
    if ( name == "NEW COLOR SCHEME") {
        
        Globals::instance()->animData->addColorScheme();
        
        
    }
    
    if ( name == "SAVE COLOR SCHEME") {
        
        Globals::instance()->animData->saveColorScheme("coucou", Globals::instance()->sceneManager->getScene(0)->getLightObjects());
        
        
    }
    
    if ( name == "COLOR NAME") {
        
        Globals::instance()->animData->currentColorScheme->name = colorInput->getTextString();
        Globals::instance()->gui->colorPickerGui->renameToggle(Globals::instance()->animData->currentColorScheme->id, colorInput->getTextString());
        
        
    }
    
    if (name == "DELETE COLOR SCHEME") {
        if(!Globals::instance()->animData->currentColorScheme)
            return;
        Globals::instance()->animData->deleteColorSchemeByID(Globals::instance()->animData->currentColorScheme->id);
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

