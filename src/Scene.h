//
//  Scene.h
//  Sucre
//
//  Created by Martial on 16/10/13.
//
//

#ifndef __Sucre__Scene__
#define __Sucre__Scene__

#include "ofMain.h"
#include "SceneObject.h"
#include "GridObject.h"
#include "LightObject.h"
#include "SceneObjectEvent.h"
#include "Selector.h"
#include "ofxTween.h"


class Scene {
    
public :
    
    Scene();
    void setup(bool useFbo = false);
    void update();
    void draw();
    
    void setBasicLightGrid();
    
    void setSelecteds(vector<int> selecteds);
    
    /* events  */
    void enableLightEvents (bool bEnabled);
    void onObjectClickEvent (SceneObjectEvent & e);
    void onGuiSelectorEvent(SelectorEvent & e);
    
    /* ----- */
    void deselectLightObjects (SceneObject *  exception );
    
    float   scale;
    void    setMode(int mode);
    void    animate();
    
    vector<ofPtr<LightObject> > getLightObjects();
    vector<SceneObject* > selecteds;
    
    void updateData();
    
    SceneObject * container;
    
    bool bActive;
    bool bInteractive;
    
    ofFbo fbo;
    
    void onResizeEvent(ofResizeEventArgs & e);
    
    bool isFbo() {return bUseFbo;};

    
private:
    
    
    void setDefaultMatrix();
    void addObject(SceneObject * obj);
    
    
    vector<SceneObject*>        objects;
    
    float *defaultMatrix;
    
    /* objects */

    
    SceneObject * test;
    
    /* utils  */
    
    
    ofxTween        tween;
    ofxEasingQuint 	easingquint;
    
    int mode;
    bool bUseFbo;
    
    
    

    
};

#endif /* defined(__Sucre__Scene__) */
