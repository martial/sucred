//
//  Globals.h
//  NS2013
//
//  Created by Martial on 26/03/13.
//
//

#pragma once
#include "ofxEQ.h"
#include "Scene.h"

class Globals
{
public:
    
    Globals					();
    static Globals*			instance();
    
    
    ofxEQ       *               eq;
    Scene       *               scene;
       
    int                         DMX1_PORT, DMX2_PORT, USB1_PORT, USB2_PORT;
    
	    
private:
    static Globals*			inst;
};
