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

		InspectorGui(float x, float y, float w, float h, ofxUICanvas *sharedResources) {
		 ofxUICanvas::ofxUICanvas(x,y,w,h,sharedResources);
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
    
    ofxUIRotarySlider *rSlider, *gSlider, *bSlider;
    ofxUIHsbPicker * hsbPicker;
    
    ofxUIToggle   *  permanentToggle;
    ofxUITextInput  * colorInput;

    ofxUIToggle * autoModeToggle;
    
    ofxUIDropDownList  * categoriesList;
    
    vector<string> getCategories();

    
    float r,g,b;
    
    bool bEnabled;
    
    vector<SceneObject* > lights;
    
    SceneObject * selected;
    
};

#endif /* defined(__Sucre__InspectorGui__) */
