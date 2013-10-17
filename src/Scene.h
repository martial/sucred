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

class Scene {
    
public :
    
    Scene();
    void setup();
    void update();
    void draw();
    
    void setBasicLightGrid();

    
    float scale;
    
    float                        *defaultMatrix;
    
private:
    
    void addObject(SceneObject * obj);
    
    
    vector<SceneObject*>    objects;
    
    /* objects */
    SceneObject * container;
    SceneObject * test;
    
    /* props  */
    
    
    
};

#endif /* defined(__Sucre__Scene__) */
