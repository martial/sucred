//
//  InspectorGui.h
//  Sucre
//
//  Created by Martial on 17/10/13.
//
//

#ifndef __Sucre__InspectorGui__
#define __Sucre__InspectorGui__

#include "ofMain.h"
#include "ofxUI.h"
#include "SceneObject.h"
#include "ofxTween.h"

class InspectorGui : public ofxUICanvas {
public:
    InspectorGui(float x, float y, float w, float h) : ofxUICanvas()
    {
        ofxUICanvas::ofxUICanvas(x,y,w,h);
    }
    
    
    void populate();
    void setId(float id);
    void setDmxAddress(float dmx);
    
    
    void setMulti(vector<SceneObject* > lights);
    void draw();
    
    void show();
    void hide();
    
    void onGuiEvent(ofxUIEventArgs & e);
    
    ofxUITextArea   * idTextArea;
    ofxUITextArea   * dmxText;

    ofxUITextInput  * dmxInput;
    
    ofxTween        tween;
    ofxEasingQuint 	easingquint;
    
    bool bEnabled;
    
    
};

#endif /* defined(__Sucre__InspectorGui__) */
