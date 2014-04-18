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


void FboMerger::process(ofFbo * input, ofFbo * overlay) {
    
    // fbo for output
    
    
    //sOutput.width           = input->getWidth();
   // sOutput.height          = input->getHeight();
    
   

	if(!fbo.isAllocated()) {
		ofFbo::Settings sOutput;
		sOutput.internalformat  = GL_RGBA;
		sOutput.width           = input->getWidth();
		sOutput.height          = input->getHeight();
		fbo.allocate(sOutput);
	}
    
    ofSetColor(255,255,255,255);
    ofEnableAlphaBlending();
    
    fbo.begin();
    ofClear(0,0,0, 255);
    
    ofEnableAlphaBlending();
    
    input->draw(0,0);
    
    ofEnableBlendMode(OF_BLENDMODE_SCREEN);

    overlay->draw(0,0);
    

    fbo.end();
    
    ofDisableBlendMode();
    ofEnableAlphaBlending();
    ofSetColor(255,255,255,255);

   // fbo.draw(0.0, 0.0);
    

}

void FboMerger::apply(Scene * scene) {
    
    
    // get pixels
	
	if(!pixels.isAllocated())
    pixels.allocate(fbo.getWidth(), fbo.getHeight(), OF_PIXELS_RGBA);

    fbo.readToPixels(pixels);
    
    
   // ofLog(OF_LOG_NOTICE, "coucou %f %f", fbo.getWidth(), fbo.getHeight());    // set colors
    
    int w = (int)fbo.getWidth();
    int h = (int)fbo.getHeight();
    
    vector<ofPtr<LightObject> >  lights = scene->getLightObjects();
    
    int id=0;
    for( int i=0; i<6; i++) {
        
        for ( int j=0; j<7; j++) {
            
            if(id < lights.size())
            lights[id]->finalColor.set(pixels.getColor(i, j));
            id++;
            
        }
        
    }
    
    
    
}

