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
#include "ofxTween.h"

class LiveGui : public ofxUICanvas {
    
public:
    
    LiveGui(float x, float y, float w, float h) : ofxUICanvas()
    {
        ofxUICanvas::ofxUICanvas(x,y,w,h);
    }
    
    
    void init();
    void populate ();
    void update();
    void draw();
    
    ofImage image;
    
    ofxUIToggle *       live, * editor, * config;
    
    ofxUISlider     *    overrideSlider;
    ofxUISpectrum * leftSpectrum;
    ofxUISpectrum * rightSpectrum;
    
    ofxUIToggle  * playBtn, *stopBtn, *strobBtn, *strobDmxBtn, *fullStrobBtn, *audioReacBtn;
    ofxUISlider * speedSlider, *speedOverlaySlider, *decaySlider, *decayOverlaySlider, *strobSlider;

    ofxUIRotarySlider *rSlider, *gSlider, *bSlider, *wslider;
    ofxUIHsbPicker * hsbPicker;
    

    void show();
    void hide();
    
    ofxTween        tween;
    ofxEasingQuint 	easingquint;
    
    void onGuiEvent(ofxUIEventArgs & e);
    
    float r,g,b,w;
    
    void setRed(float value);
    void setGreen(float value);
    void setBlue(float value);
    void setWhite(float value);
    
    
    
};

#endif /* defined(__Sucre__LiveGui__) */
