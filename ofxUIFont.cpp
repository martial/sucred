//
//  ofxUIFont.cpp
//  Sucre
//
//  Created by Martial on 02/01/2014.
//
//

#include "ofxUIFont.h"


void ofxUIFont::drawString(string s, float x, float y) {
    
    ofRectangle rect = this->getStringBoundingBox(s, x, y);
    
    // if we have this string in cache
    
    if(s.empty())
        return;
    
    ofFbo * fbo;
    
    if (!ofContains(strings, s) || strings.empty() ) {

        fbo = new ofFbo();
        
        fbo->allocate(rect.width, rect.height);
        fbo->begin();
        ofClear(0,0,0, 255);
        ofEnableAlphaBlending();
        ofTrueTypeFont::drawString(s, 0   , rect.height );
        ofSetColor(255, 255, 255);
        fbo->end();
        
        cachedString = s;
        
        strings.push_back(s);
        fbos.push_back(fbo);
        
        //ofLog(OF_LOG_NOTICE, "allocate " + s);
        
    } else {
        
        int index = ofFind(strings, s);
        fbo = fbos[index];
    //ofLog(OF_LOG_NOTICE, s);
    }

    //ofLog(OF_LOG_NOTICE, s);


    if (fbo ) {
    ofEnableAlphaBlending();
    fbo->draw(rect.x, rect.y);
        
    }
    
}



