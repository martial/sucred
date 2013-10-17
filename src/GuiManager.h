//
//  GuiManager.h
//  Sucre
//
//  Created by Martial on 16/10/13.
//
//

#ifndef __Sucre__GuiManager__
#define __Sucre__GuiManager__

#include "ofMain.h"
#include "ofxUI.h"

class GuiManager {
    
public:
    
    void setup ();
    void update();
    void onGuiEvent(ofxUIEventArgs & e);
    
private :
    
    
    ofImage image;
    ofxUICanvas * canvas;
    
    ofxUISlider     *    overrideSlider;
    
    ofxUISpectrum * leftSpectrum;
    ofxUISpectrum * rightSpectrum;
    
};

#endif /* defined(__Sucre__GuiManager__) */
