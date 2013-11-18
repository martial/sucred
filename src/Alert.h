//
//  Alert.h
//  Sucre
//
//  Created by Martial on 15/11/2013.
//
//

#ifndef __Sucre__Alert__
#define __Sucre__Alert__

#include "ofMain.h"
#include "ofxTimer.h"
#include "ofxTween.h"

class Alert {
    
    public :
    
    
    Alert(string txt, int delay, ofTrueTypeFont * font, bool autoHide) {
        
        this->font      = font;
        this->txt       = txt;
        this->delay     = delay;
        this->autoHide  =  autoHide;
        
        spacing     = 20;
        
        bAlive      = true;
        
        rect.width  = getWidth();
        rect.height = getHeight();
        

        
    }
    
    float getWidth () {
        
        return font->stringWidth(this->txt);
        
    }
    
    float getHeight () {
        
        return font->stringHeight(this->txt);
        
    }
    
    void onTimerReached(ofEventArgs & e) {
        hide();
    }
    
    void onShowReached(int & e) {
        
        ofRemoveListener(tween.end_E, this, &Alert::onShowReached);
        
        timer.setup(delay, false);
        ofAddListener(timer.TIMER_REACHED, this, &Alert::onAnimationTimerReached);
    }
    
    void onHideReached(int & e) {
        bAlive = false;
        ofRemoveListener(tween.end_E, this, &Alert::onHideReached);

    }
    
    void onAnimationTimerReached(ofEventArgs & e) {
        hide();
    }
    
    void show() {
        
        if(autoHide) {
            tween.setParameters(back,ofxTween::easeOut, - ofGetHeight() * .5 -rect.height, rect.y, 400, 0);
            tween.start();
            ofAddListener(tween.end_E, this, &Alert::onShowReached);
        }
        
    }
    
    void hide () {
        
        tween.setParameters(quint,ofxTween::easeIn, rect.y, - ofGetHeight() * .5 -rect.height, 300, 0);
        tween.start();
        ofAddListener(tween.end_E, this, &Alert::onHideReached);
        
    }
    
       void draw() {
        
        ofPushMatrix();
        ofTranslate(ofGetWidth() * .5 - rect.width * .5, ofGetHeight() * .5 + tween.update());
        
        ofFill();
        ofSetColor(0);
        ofRect(-spacing, -spacing,rect.width + spacing*2, rect.height + spacing*2);
        
        ofSetColor(255);
        font->drawString(this->txt, 0.0, rect.height);
        
        ofPopMatrix();
        
        
    }
    
    void setPosition(ofPoint pos) {
        rect.x = pos.x;
        rect.y = pos.y;
    }
    
    bool isAlive() {
        return bAlive;
    }
    
private:
    
    string  txt;
    int     delay;
    int spacing;
    ofxTimer timer;
    ofxTween tween;
    ofxEasingQuint quint;
    ofxEasingBack back;
    //ofxEasing
    ofRectangle rect;
    ofTrueTypeFont * font;
    
    bool bAlive, autoHide;
    
    
};

#endif /* defined(__Sucre__Alert__) */
