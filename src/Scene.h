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


class Scene {
    
public :
    
    Scene();
    void setup();
    void update();
    void draw();
    
    void setBasicLightGrid();
    
    /* events  */
    void enableLightEvents (bool bEnabled);
    void onObjectClickEvent (SceneObjectEvent & e);
    void onGuiSelectorEvent(SelectorEvent & e);
    
    /* ----- */
    void deselectLightObjects (SceneObject * exception = NULL);
    
    float scale;
    void setMode(int mode);
    
    
    
private:
    
    
    void setDefaultMatrix();
    void addObject(SceneObject * obj);
    
    
    vector<SceneObject*>    objects;
    
    float *defaultMatrix;
    
    /* objects */

    SceneObject * container;
    SceneObject * test;
    
    /* utils  */
    
    

    
};

#endif /* defined(__Sucre__Scene__) */
