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

class FboMerger {
    
public:
    
    void setup();
    ofFbo * process(ofFbo * input, ofFbo * overlay);
    
    ofFbo output;
    
};

#endif /* defined(__Sucre__FboMerger__) */
