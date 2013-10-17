#pragma once

#include "ofMain.h"
#include "GuiManager.h"
#include "ofxEQ.h"
#include "Globals.h"
#include "Scene.h"
#include "ofxSosoRenderer.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
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
        Scene                   scene;
    
};
