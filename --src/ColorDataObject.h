//
//  ColorDataObject.h
//  Sucre
//
//  Created by Martial on 15/11/2013.
//
//

#ifndef __Sucre__ColorDataObject__
#define __Sucre__ColorDataObject__


#include "ofMain.h"
#include "AnimationDataObject.h"
#include "ofxXmlSettings.h"

class ColorData {
public:
    int id;
    ofColor color;
    bool bPermanent;
    
};

class ColorDataObject  : public  ofxXmlSettings {
    
public:
    
    
    ColorDataObject();
    int     id;
    string  name;
    string path;
    
    
    void create();
    void parse(ofxXmlSettings * node);
    
    void rename(string name);
    
    void addColor(int id, ofColor color, bool bPermanent);
    
    void save();
    
    vector<ColorData> colors;
    
    

    
    
};

#endif /* defined(__Sucre__AnimationDataObject__) */



