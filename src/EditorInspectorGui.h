//
//  EditorInspectorGUi.h
//  Sucre
//
//  Created by Martial on 21/10/13.
//
//

#ifndef __Sucre__EditorInspectorGUi__
#define __Sucre__EditorInspectorGUi__

#include "ofMain.h"
#include "ofxUI.h"
#include "SceneObject.h"
#include "ofxTween.h"

class EditorInspectorGui : public ofxUICanvas {
public:
    EditorInspectorGui(float x, float y, float w, float h) : ofxUICanvas()
    {
        ofxUICanvas::ofxUICanvas(x,y,w,h);
    }
    
    
    void populate();

    void setUrl(string url);
    void setFrame(int frame, int total);
    
    void draw();
    
    void onGuiEvent(ofxUIEventArgs & e);
    void onFrameEvent( int & e);
    
    
    void show();
    void hide();
    
    ofxUITextInput * urlText;
    ofxUITextArea  *frameText;
    ofxUIToggle  * playBtn, *stopBtn;
    ofxUISlider * speedSlider;
    
    ofxTween        tween;
    ofxEasingQuint 	easingquint;
    
    void keyPressed(ofKeyEventArgs & key);

    bool bEnabled;
    
    
    // functions
    
    void addFrame();
    void prevFrame();
    void nextFrame();
};

#endif /* defined(__Sucre__EditorInspectorGUi__) */
