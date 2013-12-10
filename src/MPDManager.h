//
//  MPDManager.h
//  Sucre
//
//  Created by Martial on 06/12/2013.
//
//

#ifndef __Sucre__MPDManager__
#define __Sucre__MPDManager__

#include "ofMain.h"
#include "ofxMidi.h"

class MPDManager : public ofxMidiListener {
    
public:
    
    void setup();
    void update();
    void newMidiMessage(ofxMidiMessage& eventArgs);

    
private:
    
    ofxMidiIn midiIn;
	ofxMidiMessage midiMessage;
    
    
    int strobVelocity;
    
   };

#endif /* defined(__Sucre__MPDManager__) */
