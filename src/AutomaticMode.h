//
//  AutomaticMode.h
//  Sucre
//
//  Created by Martial on 27/11/2013.
//
//

#ifndef __Sucre__AutomaticMode__
#define __Sucre__AutomaticMode__

#include "ofMain.h"
#include "ofxTimer.h"
class AutomaticMode {
    
public:
    
    void setup();
    void update();
    
    
    void setTimer(int millis);
    void setEnabled(bool bEnabled);
    
    void onTimerhandler(ofEventArgs & e);
    
    bool bChangeColors;
    
    
private:
    
    float millisTimer;
    bool bEnabled;
    
    ofxTimer timer;

    
};

#endif /* defined(__Sucre__AutomaticMode__) */
