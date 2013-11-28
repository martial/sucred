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
    
    void drawFbo(int index);
    void drawFbos();
    
    void drawPreviews();
    
    void setGlobalScale(float scale);
    
    void resetEditorFrames();
    void updateEditorFrames();
    void updateEditorFrames(int & );
    void updatePreviewFrames(int & e);
    void updateOverlayFrames(int & e );
    
    Scene * getScene(int index);
    
    void setMode(int mode);
    
    int getSelected();
    void onMousePressed(ofMouseEventArgs & e);
    
private:
    
    vector<Scene* > scenes;
    
};

#endif /* defined(__Sucre__SceneManager__) */
