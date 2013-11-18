//
//  ColorPickerGui.h
//  Sucre
//
//  Created by Martial on 15/11/2013.
//
//



#ifndef __Sucre__ColorPickerGui__
#define __Sucre__ColorPickerGui__

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxTween.h"
#include "AnimationDataObject.h"
#include "ColorDataObject.h"

class ColorPickerGui : public ofxUIScrollableCanvas {
    
public:
    
    ColorPickerGui(float x, float y, float w, float h) : ofxUIScrollableCanvas()
    {
        ofxUIScrollableCanvas::ofxUIScrollableCanvas(x,y,w,h);
    }
    
    
    void setColors(vector<ColorDataObject*> colors);
    void populate();
    
    void renameToggle(int index, string name);
    void selectToggle(int index);
    
    void draw();
    
    void show();
    void hide();
    
    
    
    void onGuiEvent(ofxUIEventArgs & e);
    void onWindowResize(ofResizeEventArgs & e);
    
    vector<ofxUIToggle*> toggles;
    
    ofxTween        tween;
    ofxEasingQuint 	easingquint;
    
    bool bEnabled;
    
    
};

#endif /* defined(__Sucre__AnimationPickerGui__) */


