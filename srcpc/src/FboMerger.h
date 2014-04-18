//
//  FboMerger.h
//  Sucre
//
//  Created by Martial on 22/11/2013.
//
//

#ifndef __Sucre__FboMerger__
#define __Sucre__FboMerger__

#include "ofMain.h"
#include "Scene.h"
#include "Scene.h"

class FboMerger {
    
public:
    
    void setup();
    void process(ofFbo * input, ofFbo * overlay);
    void apply(Scene * scene);
    
    ofFbo fbo;
    ofPixels pixels;

};

#endif /* defined(__Sucre__FboMerger__) */
