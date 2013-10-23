#pragma once

#include "ofMain.h"
#include "GuiManager.h"
#include "ofxEQ.h"
#include "Scene.h"
#include "ofxSosoRenderer.h"
#include "DataManager.h"
#include "AnimationDataManager.h"
#include "Animator.h"
#include "SceneManager.h"

#define MODE_LIVE 0
#define MODE_EDITOR 1
#define MODE_CONFIG 2

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void setMode(int mode);
        void onFrameEvent(int & e);
    
        void audioReceived (float * input, int bufferSize, int nChannels);
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    
    
    
    
        ofPtr<ofBaseRenderer>    defaultRenderer;
        ofPtr<ofBaseRenderer>    sosoRenderer;
        GuiManager              gui;
        ofxEQ                   eq;
    
        SceneManager            sceneManager;
    
    /*
        Scene                   scene;
    
        Scene                   prevScene, nextScene;
     */
    
        DataManager             dataManager;
        AnimationDataManager    animDataManager;
    
        Animator                mainAnimator;
    
        int                     mode;
    
};
