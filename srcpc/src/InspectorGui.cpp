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
    setFontSize(OFX_UI_FONT_MEDIUM, 6);

    setDrawBack(true);
   //setAutoDraw(false);
    
    addSpacer();
    addTextArea("INSPECTOR", "INSPECTOR", OFX_UI_FONT_LARGE);
    addSpacer();
    
    
    idTextArea  = addTextArea("id", "ID");
    //addSpacer();
    
    
    dmxText     = addTextArea("DMXADR", "DMX ADDRESS");
    dmxInput    = addTextInput("DMX", "");
     
    
    
    rSlider = new ofxUIRotarySlider(24*2.0, 0.0, 255, &r, "R");
    gSlider = new ofxUIRotarySlider(24*2.0, 0.0, 255, &g, "G");
    bSlider = new ofxUIRotarySlider(24*2.0, 0.0, 255, &b, "B");
    
    addWidgetDown(rSlider);
    addWidgetRight(gSlider);
    addWidgetRight(bSlider);
    
    hsbPicker = addHsbPicker("HSB");
    
    
    permanentToggle = addToggle("PERMANENT", false);
    
    addSpacer();
    
    addLabelButton("RESET OVERLAY", false, true);
    addLabelButton("RESET COLORS", false, true);
    addSpacer();
    addLabelButton("NEW COLOR SCHEME", false, true);
    addLabelButton("SAVE COLOR SCHEME", false, true);
    addLabelButton("DELETE COLOR SCHEME", false, true);
    colorInput = addTextInput("COLOR NAME", "");
    addSpacer();
    
    
    autoModeToggle = addToggle("AUTO", false);
    addToggle("COLOR AUTO", false);
    addSlider("AUTO TIME", 1, 100, 40);
    
    
    vector<string> test;
    test.push_back("0");
    test.push_back("1");
    test.push_back("2");
    test.push_back("3");
    test.push_back("4");
    test.push_back("5");
    
    categoriesList =  addDropDownList("CATEGORIES", test);
    categoriesList->setAllowMultiple(true);
    

    
    ofAddListener(newGUIEvent,this,&InspectorGui::onGuiEvent);
    bEnabled = true;
    
    
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
    float xPos =  ofGetWidth() - rect->width;

    setPosition(xPos, 0);
    ofxUICanvas::draw();
    
    //ofLog(OF_LOG_NOTICE , "draw inspector %d", ofGetFrameNum());
    
    
}

void InspectorGui::setId(float id) {
    
    /*
    show();
    idTextArea->setVisible(true);
    idTextArea->setTextString("ID : " + ofToString(id));
     
     */
    
}
void InspectorGui::setDmxAddress(float dmx) {
    
    
    show();
    dmxText->setVisible(true);
    dmxInput->setVisible(true);
    dmxInput->setTextString(ofToString(dmx));
    
    
    
}

void InspectorGui::setMulti(vector<SceneObject* > lights) {
    
    
    selected = NULL;
    
    show();
    
    
    /*
    if(lights.size() == 0 )
        hide();
    else
        show();
     */
    
    if(lights.size() == 1 ) {
        selected = lights[0];
        //setId(selected->id);
        setDmxAddress(selected->data->dmxAddress);
        return;
        
    }
        
    
    //idTextArea->setVisible(true);
    
    dmxInput->setVisible(false);
    dmxText->setVisible(false);
     
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
        
        vector<ofPtr<LightObject> > l = Globals::get()->sceneManager->getScene(3)->getLightObjects();
        
        for (int i =0; i<lights.size(); i++) {
            l[lights[i]->id]->overrideColor.set(r, g, b);
            l[lights[i]->id]->bPermanentOverride = permanentToggle->getValue();

        }
        
    }

	
    if (name == "RESET COLORS") {
        
        vector<ofPtr<LightObject> > l = Globals::get()->sceneManager->getScene(3)->getLightObjects();
        
        for (int i =0; i<l.size(); i++) {
            l[i]->overrideColor.set(0.0,0.0,0.0, 0.0);
            l[i]->bPermanentOverride = false;
            //ofLog(OF_LOG_NOTICE, "bye color");
            
        }
        
        
        Globals::get()->colorManager->setGlobalColor(3, ofColor(Globals::get()->gui->liveGui->r, Globals::get()->gui->liveGui->g, Globals::get()->gui->liveGui->b), Globals::get()->gui->liveGui->w);
        
      
        
    }
    
    if ( name == "NEW COLOR SCHEME") {
        
        Globals::instance()->animData->addColorScheme();
        
        
    }
    
    if ( name == "SAVE COLOR SCHEME") {
        
        Globals::instance()->animData->saveColorScheme("coucou", Globals::instance()->sceneManager->getScene(3)->getLightObjects());
        
        
    }
    
    if ( name == "COLOR NAME") {
        
        if(!Globals::instance()->animData->currentColorScheme)
            return;
        
        Globals::instance()->animData->currentColorScheme->name = ofToUpper(colorInput->getTextString());
        Globals::instance()->gui->colorPickerGui->renameToggle(Globals::instance()->animData->currentColorScheme->id, ofToUpper(colorInput->getTextString()));
        
        
    }
    
    if (name == "DELETE COLOR SCHEME") {
        if(!Globals::instance()->animData->currentColorScheme)
            return;
        Globals::instance()->animData->deleteColorSchemeByID(Globals::instance()->animData->currentColorScheme->id);
    }
    
    if(name =="AUTO") {
        
        Globals::get()->app->autoMode.setEnabled(e.getToggle()->getValue());
        
    }
    
    if ( name =="COLOR AUTO") {
        
        Globals::get()->app->autoMode.bChangeColors = e.getToggle()->getValue();
    }
    
    if( name == "AUTO TIME") {
        
        Globals::get()->app->autoMode.setTimer(e.getSlider()->getScaledValue() * 1000);
        
    }

    
    
}


void InspectorGui::hide() {
   // bEnabled = false;
    //tween.setParameters(1,easingquint,ofxTween::easeOut, rect->x,ofGetWidth(),300, 0);
}

void InspectorGui::show () {
    bEnabled = true;
    tween.setParameters(1,easingquint,ofxTween::easeOut,rect->x, ofGetWidth() - rect->width,300, 0);
    
}

vector<string> InspectorGui::getCategories() {
    
    vector<ofxUIWidget*> selecteds = categoriesList->getSelected();
    vector<string> result;
    for (int i=0; i<selecteds.size(); i++)
        result.push_back(selecteds[i]->getName());
    
    return result;
}

