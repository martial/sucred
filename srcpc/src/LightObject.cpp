//
//  LightObject.cpp
//  Sucre
//
//  Created by Martial on 16/10/13.
//
//

#include "LightObject.h"

LightObject::LightObject() {
    
    InteractiveSceneObject::InteractiveSceneObject();
    bSelected   = false;
    bDebug      = false;
    strobDmx    = false;
    bStatic     = false;
    
}



void LightObject::setup() {
    
    
}

void LightObject::update() {
    
    
    
}



void LightObject::setRadius(float radius) {
    
    this->radius = radius*2;
    boundingBox.set(-radius , -radius, radius*2, radius*2);
}

void LightObject::draw(float *iMatrix, bool debug ) {
    
    SceneObject::draw(iMatrix, debug);
    
    if(!bStatic) {
    
        float t, b ,  c,  d;
    
        t = decay;
        d = 1.0;
        b = 0.0;
        c = 1.0;
    
        float dec =  c*(t/=d)*t*t*t*t + b;
    
    
        if(alpha >= 0 )
            alpha -= dec;
    
        if(alpha<0)
            alpha = 0.0;
    
        if(hasOverrideColor() && bPermanentOverride)
            alpha = 1;
    
          
    
        if(bSelected) {

            alpha = 1.0;
            ofFill();
        
        }
    
        if(hasOverrideColor() || bPermanentOverride) {
            color = overrideColor;
        }
    

    
        colorTarget = color;
    
        easeColor(&finalColor, &colorTarget);
    

        finalColor.a *= alpha;

    
   
        }
    // apply effects
    SceneObjectEvent e (this) ;
    ofNotifyEvent(readyToEffect, e);
    
    // apply global alpha
    finalColor.a *= overrideAlpha;
    
    ofNotifyEvent(readyToDmx, e);
    dmxColor = finalColor;
    dmxWhite = white;

    
    
    // send DMX
    if(finalColor != dmxColor || finalColor.a != dmxColor.a || dmxWhite != white ){
        
        
        //ofLog(OF_LOG_NOTICE, "send dmx");
        
    } else {
        
       
        
    }

    
    
    
    ofFill();
    //ofRectMode(OF_RECTMODE_CENTER);
    
    ofSetColor(0);
	ofRect(-radius/2,-radius/2,radius, radius);
    //ofCircle(0,0, radius);
    
    ofSetColor(finalColor);
    //ofCircle(0,0, radius);
	ofRect(-radius/2,-radius/2,radius, radius);
    
    
    
    if(bHightlighted ) {
        
        ofNoFill();
        ofSetColor(120);
       // ofCircle(0,0, radius + 4);
		ofRect(-(radius+4)/2,-(radius+4)/2,radius+4, radius+4);
        
    }
    
    ofFill();

    
}

void LightObject::easeColor(ofColor * color, ofColor * colorTarget) {
    
    blur = .93;
    
    
    color->r = blur * color->r + (1.0 - blur) * colorTarget->r;
    color->g = blur * color->g + (1.0 - blur) * colorTarget->g;
    color->b = blur * color->b + (1.0 - blur) * colorTarget->b;
    color->a = 255.0;
    
    
}