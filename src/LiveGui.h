//
//  LiveGui.h
//  Sucre
//
//  Created by Martial on 17/10/13.
//
//

#ifndef __Sucre__LiveGui__
#define __Sucre__LiveGui__

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxUIWidget.h"

class LiveGui : public ofxUICanvas {
    
public:
    
    LiveGui(float x, float y, float w, float h) : ofxUICanvas()
    {
        ofxUICanvas::ofxUICanvas(x,y,w,h);
    }
    
    
    void init();
    void populate ();
    
    ofImage image;
    
    ofxUIToggle *       live, * editor, * config;
    
    ofxUISlider     *    overrideSlider;
    ofxUISpectrum * leftSpectrum;
    ofxUISpectrum * rightSpectrum;

    
};

#endif /* defined(__Sucre__LiveGui__) */
