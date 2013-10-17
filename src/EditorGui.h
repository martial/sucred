//
//  EditorGui.h
//  Sucre
//
//  Created by Martial on 17/10/13.
//
//

#ifndef __Sucre__EditorGui__
#define __Sucre__EditorGui__

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxUIWidget.h"
#include "ofxTween.h"

class EditorGui : public ofxUICanvas {
    
public:
    
    EditorGui(float x, float y, float w, float h) : ofxUICanvas()
    {
        ofxUICanvas::ofxUICanvas(x,y,w,h);
    }
    
    
    void init();
    void populate ();
    void draw();
    void update();
    
    ofImage image;
    
    ofxUIToggle *       live, * editor, * config;

    void show();
    void hide();
    
    ofxTween        tween;
    ofxEasingQuint 	easingquint;
    
};

#endif /* defined(__Sucre__EditorGui__) */
