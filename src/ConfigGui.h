//
//  EditorGui.h
//  Sucre
//
//  Created by Martial on 17/10/13.
//
//

#ifndef __Sucre__ConfigGui__
#define __Sucre__ConfigGui__

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxUIWidget.h"
#include "ofxTween.h"

class ConfigGui : public ofxUICanvas {
    
public:
    
    ConfigGui(float x, float y, float w, float h) : ofxUICanvas()
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
    
    float editorSceneScale;
    
};

#endif /* defined(__Sucre__EditorGui__) */
