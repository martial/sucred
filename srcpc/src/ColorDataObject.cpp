//
//  ColorDataObject.cpp
//  Sucre
//
//  Created by Martial on 15/11/2013.
//
//

#include "ColorDataObject.h"


ColorDataObject::ColorDataObject() {
    name = "undefined";
}

void ColorDataObject::create() {
    
    
    // first frame
    id = 0;
    
}

void ColorDataObject::rename(string name) {
    
    this->name = name;
    
}



void ColorDataObject::parse(ofxXmlSettings * node) {
    
    // we should be here on the right node
    
    
    this->id    = node->getValue("id", 0);
    this->name  = node->getValue("name", "undefined");
    
    //ofLog(OF_LOG_NOTICE, "parse %d", this->id);
    
    
    node->pushTag("colors");
    int numOfColors = node->getNumTags("color");
    
    for (int i=0; i<numOfColors; i++) {
        
        node->pushTag("color", i);
        
        ColorData colorData;
        colorData.color.set( (int)node->getValue("r", 0, 0), (int)node->getValue("g", 0, 0), (int)node->getValue("b", 0, 0));
        colorData.id    =       node->getValue("id", 0, 0);
        colorData.bPermanent =  node->getValue("permanent", false, 0);
        
        colors.push_back(colorData);

        node->popTag();
            
        

        
        
    }
    
    node->popTag();
    
    
    
}

void ColorDataObject::addColor(int id, ofColor color, bool bPermanent) {
    
   
    
    
    ColorData colorData;
    colorData.id            = id;
    colorData.color         = color;
    colorData.bPermanent    = bPermanent;
    
    colors.push_back(colorData);
    
}

void ColorDataObject::save () {
    
    // delete all
    clear();
    
    // find the right frame
    addTag("root");
    pushTag("root");
    
    addTag("id");
    setValue("id", id);
    
    // always save name
    addTag("name");
    setValue("name", name);
    
    addTag("colors");
    pushTag("colors");
    
       // delete all
    clear();
    
    for (int j=0; j<colors.size(); j++) {
        
        addTag("color");
        pushTag("color", j);
        
        
        setValue("id", colors[j].id);
        setValue("r", colors[j].color.r);
        setValue("g", colors[j].color.g);
        setValue("b", colors[j].color.b);
        setValue("permanent", colors[j].bPermanent);
        
        popTag();
        
    }
    
    
    popTag();
    popTag();
    
    
    
    
    saveFile("tmpcolor.xml");
    
    
    
    
}
