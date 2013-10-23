//
//  SceneManager.h
//  Sucre
//
//  Created by Martial on 23/10/2013.
//
//

#ifndef __Sucre__SceneManager__
#define __Sucre__SceneManager__

#include "ofMain.h"
#include "Scene.h"

class SceneManager {
    
public:
    
    void setup();
    void update();
    void draw();
    void drawFbos();
    
    void updateEditorFrames();
    
    Scene * getScene(int index);
    
    void setMode(int mode);
    
private:
    
    vector<Scene* > scenes;
    
};

#endif /* defined(__Sucre__SceneManager__) */
