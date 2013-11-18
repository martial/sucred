//
//  AnimationPickerGui.h
//  Sucre
//
//  Created by Martial on 23/10/2013.
//
//

#ifndef __Sucre__AnimationPickerGui__
#define __Sucre__AnimationPickerGui__

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxTween.h"
#include "AnimationDataObject.h"

class AnimationPickerGui : public ofxUIScrollableCanvas {
    
public:
    
    AnimationPickerGui(float x, float y, float w, float h) : ofxUIScrollableCanvas()
    {
        ofxUIScrollableCanvas::ofxUIScrollableCanvas(x,y,w,h);
    }
    
    
    void setAnims(vector<AnimationDataObject*> anims);
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
