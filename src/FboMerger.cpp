//
//  FboMerger.cpp
//  Sucre
//
//  Created by Martial on 22/11/2013.
//
//

#include "FboMerger.h"


void FboMerger::setup() {
    
    
    
}


ofFbo * FboMerger::process(ofFbo * input, ofFbo * overlay) {
    
    
    input->draw(0,0);
    overlay->draw(0,0);
    
}