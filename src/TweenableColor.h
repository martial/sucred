//
//  TweenableColor.h
//  Sucre
//
//  Created by Martial on 18/11/2013.
//
//

#ifndef __Sucre__TweenableColor__
#define __Sucre__TweenableColor__

#include "ofMain.h"
#include "ofxTween.h"

class TweenableColor : public ofColor {


    
public:
    
    TweenableColor() {
        ofColor::set(255);
    }
    void set(float v) {
        ofColor::set(v);
    }
    
    void set(float _r, float _g, float _b, float _a, float time = 200) {
        
        ofColor dumm;
        dumm.set(_r, _g, _b, _a);
        
        if(dumm != target) {
            
            
        target.set(_r, _g, _b, _a);
        
        twR.setParameters(quint, ofxTween::easeOut, this->r, _r, time, 0.0);
        twR.start();
        
        twG.setParameters(quint, ofxTween::easeOut, this->g, _g, time, 0.0);
        twG.start();
        
        twB.setParameters(quint, ofxTween::easeOut, this->b, _b, time, 0.0);
        twB.start();
        
        twA.setParameters(quint, ofxTween::easeOut, this->a, _a, time, 0.0);
        twA.start();
            
        }
        
        
        
    }
    
    void update() {
        
        r = twR.update();
        g = twG.update();
        b = twB.update();
        a = twA.update();
        
       
        
        
    }
    
    ofxTween twR, twG, twB, twA;
    ofxEasingQuint quint;
    ofColor target;
    
};

#endif /* defined(__Sucre__TweenableColor__) */
