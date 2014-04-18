//
//  ofxUIFont.h
//  Sucre
//
//  Created by Martial on 02/01/2014.
//
//

#ifndef __Sucre__ofxUIFont__
#define __Sucre__ofxUIFont__

#include <iostream>

#include "ofMain.h"

class ofxUIFont : public ofTrueTypeFont {
    
public:
    
    void drawString(string s, float x, float y);
    
    
private:
    
    
    string cachedString;
    
    vector<string> strings;
    vector<ofFbo*> fbos;
    
    
};





#endif /* defined(__Sucre__ofxUIFont__) */
