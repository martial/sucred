//
//  Globals.h
//  NS2013
//
//  Created by Martial on 26/03/13.
//
//

#pragma once
#include "ofxEQ.h"
#include "SceneManager.h"
#include "GuiManager.h"
#include "testApp.h"
#include "DataManager.h"
#include "AnimationDataManager.h"
#include "Animator.h"

class Globals
{
public:
    
    Globals					();
    static Globals*			instance();
    
    
    ofxEQ       *               eq;
    SceneManager       *        sceneManager;
    GuiManager  *               gui;
    testApp     *               app;
    DataManager *               data;
    AnimationDataManager *      animData;
    Animator    *               mainAnimator;
    
    int                         DMX1_PORT, DMX2_PORT, USB1_PORT, USB2_PORT;
    
	    
private:
    static Globals*			inst;
};
