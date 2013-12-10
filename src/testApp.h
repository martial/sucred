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
#include "ColorManager.h"
#include "EffectsManager.h"
#include "DMXManager.h"
#include "ofxHttpUtils.h"
#include "AlertManager.h"
#include "AnimatorManager.h"
#include "FboMerger.h"
#include "AutomaticMode.h"
#include "MPDManager.h"

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
    
        void exit();
    
    
        ofxHttpUtils httpUtils;
        //--------------------------------------------------------------
        void newResponse(ofxHttpResponse & response){
        string responseStr = ofToString(response.status) + ": " + (string)response.responseBody;
            ofLog(OF_LOG_NOTICE, responseStr);
        }
    
    
        void onSceneChanged(int & sceneIndex);

    
    
    
    
        ofPtr<ofBaseRenderer>    defaultRenderer;
        ofPtr<ofBaseRenderer>    sosoRenderer;
        GuiManager              gui;
        ofxEQ                   eq;
    
        SceneManager            sceneManager;
        ColorManager            colorManager;
        AlertManager            alertManager;
    
    /*
        Scene                   scene;
    
        Scene                   prevScene, nextScene;
     */
    
        DataManager             dataManager;
        AnimationDataManager    animDataManager;
    
        //Animator                mainAnimator, previewAnimator;
    
        EffectsManager          effectsManager;
    
        DMXManager              dmxManager;
    
        AnimatorManager         animatorManager;
    
        AutomaticMode           autoMode;
    
        FboMerger               fboMerger;
    
        int                     mode;
    
        MPDManager mpdManager;
    
};
