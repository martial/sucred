//
//  Alert.cpp
//  Sucre
//
//  Created by Martial on 15/11/2013.
//
//

#include "AppAlert.h"

  AppAlert::AppAlert(string txt, int delay, ofTrueTypeFont * font, bool autoHide) {
        
        this->font      = font;
        this->txt       = txt;
        this->delay     = delay;
        this->autoHide  =  autoHide;
        
        spacing     = 20;
        
        bAlive      = true;
        
        rect.width  = getWidth();
        rect.height = getHeight();
        

        
    }
    
    float AppAlert::getWidth () {
        
        return font->stringWidth(this->txt);
        
    }
    
    float AppAlert::getHeight () {
        
        return font->stringHeight(this->txt);
        
    }
    
    void AppAlert::onTimerReached(ofEventArgs & e) {
        hide();
    }
    
    void AppAlert::onShowReached(int & e) {
        
        ofRemoveListener(tween.end_E, this, &AppAlert::onShowReached);
        
        timer.setup(delay, false);
        ofAddListener(timer.TIMER_REACHED, this, &AppAlert::onAnimationTimerReached);
    }
    
    void AppAlert::onHideReached(int & e) {
        bAlive = false;
        ofRemoveListener(tween.end_E, this, &AppAlert::onHideReached);

    }
    
    void AppAlert::onAnimationTimerReached(ofEventArgs & e) {
        hide();
    }
    
    void AppAlert::show() {
        
        if(autoHide) {
            tween.setParameters(back,ofxTween::easeOut, - ofGetHeight() * .5 -rect.height, rect.y, 400, 0);
            tween.start();
            ofAddListener(tween.end_E, this, &AppAlert::onShowReached);
        }
        
    }
    
    void AppAlert::hide () {
        
        tween.setParameters(quint,ofxTween::easeIn, rect.y, - ofGetHeight() * .5 -rect.height, 300, 0);
        tween.start();
        ofAddListener(tween.end_E, this, &AppAlert::onHideReached);
        
    }
    
       void AppAlert::draw() {
        
        ofPushMatrix();
        ofTranslate(ofGetWidth() * .5 - rect.width * .5, ofGetHeight() * .5 + tween.update());
        
        ofFill();
        ofSetColor(0);
        ofRect(-spacing, -spacing,rect.width + spacing*2, rect.height + spacing*2);
        
        ofSetColor(255);
        font->drawString(this->txt, 0.0, rect.height);
        
        ofPopMatrix();
        
        
    }
    
    void AppAlert::setPosition(ofPoint pos) {
        rect.x = pos.x;
        rect.y = pos.y;
    }
    
    bool AppAlert:: isAlive() {
        return bAlive;
    }