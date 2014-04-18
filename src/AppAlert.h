//
//  Alert.h
//  Sucre
//
//  Created by Martial on 15/11/2013.
//
//

#ifndef __Sucre__cocoo
#define __Sucre__cocoo

#include "ofMain.h"
#include "ofxTimer.h"
#include "ofxTween.h"

class AppAlert {
    
    public :
    
    
    AppAlert(string txt, int delay, ofTrueTypeFont * font, bool autoHide);
    
    float getWidth ();
    float getHeight ();
    void onTimerReached(ofEventArgs & e);
    void onShowReached(int & e);
    void onHideReached(int & e);
    void onAnimationTimerReached(ofEventArgs & e);
    void show();
    
    void hide ();
    
    void draw();
    
    void setPosition(ofPoint pos);
    
    bool isAlive();
    
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
