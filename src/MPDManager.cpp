//
//  MPDManager.cpp
//  Sucre
//
//  Created by Martial on 06/12/2013.
//
//

#include "MPDManager.h"
#include "Globals.h"

void MPDManager::setup(string address) {
    
    
	// print input ports to console
	midiIn.listPorts(); // via instance
	//ofxMidiIn::listPorts(); // via static as well
	
	// open port by number (you may need to change this)
	midiIn.openPort(address);
	//midiIn.openPort("IAC Pure Data In");	// by name
	//midiIn.openVirtualPort("ofxMidiIn Input");	// open a virtual port
	
	// don't ignore sysex, timing, & active sense messages,
	// these are ignored by default
	midiIn.ignoreTypes(true, false, false);
	
	// add testApp as a listener
	midiIn.addListener(this);
	
	// print received messages to the console
	midiIn.setVerbose(true);
    
    strobVelocity = 255;

}

//--------------------------------------------------------------
void MPDManager::newMidiMessage(ofxMidiMessage& msg) {
    
	// make a copy of the latest message
	midiMessage = msg;
    
    
    
    float normalized = ofNormalize((float)msg.value, 0, 127);
    float normalizedInv = 1.0 - normalized;
    
    
    float val;
    int value ;
    
    float eightByteValue =  normalized * 255.0;

    
    //ofLog(OF_LOG_NOTICE, "control %d, pitch %d value %d velocity %d", msg.control, msg.pitch, msg.value, msg.velocity);
    
    
    switch (msg.control) {
            
        // GUI
        case 20:
            
            Globals::get()->colorManager->setGlobalAlpha(3, normalized);
            
            Globals::get()->gui->liveGui->alphaSlider->setValue(normalized);
            
            break;
            
        case 21:
            
            Globals::get()->colorManager->setGlobalAlpha(4, normalized);
            Globals::get()->gui->liveGui->alphaOverSlider->setValue(normalized);
            break;
            
            
        case 22:
            Globals::get()->animatorManager->getAnimator(1)->setSpeed(normalized);
            Globals::get()->gui->liveGui->speedSlider->setValue(normalized);
            break;
            
            // GUI
        case 23:
            Globals::get()->colorManager->setGlobalDecay(3, normalizedInv);
            Globals::get()->gui->liveGui->decaySlider->setValue(normalizedInv);

            //ofLog(OF_LOG_NOTICE, "%f", normalizedInv);
            // Globals::get()->colorManager->setGlobalDecay(3, normalized);
            break;
            
            
        case 24:
            Globals::get()->animatorManager->getAnimator(2)->setSpeed(normalized);
            Globals::get()->gui->liveGui->speedOverlaySlider->setValue(normalized);
            break;
            
       
            
        // GUI
        case 25:
            Globals::get()->gui->liveGui->decayOverlaySlider->setValue(normalizedInv);
            Globals::get()->colorManager->setGlobalDecay(4, normalizedInv);

            break;
            
        case 26:
        {
            
            value = (int)ofMap(msg.value, 0, 127, 215, 255);
            strobVelocity = value;
            //ofLog(OF_LOG_NOTICE, "%d", value);
            Globals::get()->dmxManager->send(365, value);
            Globals::get()->dmxManager->send(369, value);
        }
           
        case 27:{
            
            //ofLog(OF_LOG_NOTICE, "normalized %f", normalized);
            //Globals::get()->gui->liveGui->strobSlider->setValue(normalized);
            
            float value = 4 + normalizedInv * 96.0;
            
            Globals::get()->effectsManager->strobSpeed = value;
            Globals::get()->gui->liveGui->strobSlider->setValue(value);
            
            //  ofLog(OF_LOG_NOTICE, "normalized %f", Globals::get()->gui->liveGui->strobSlider->getValue());
            break;
        }
            
            
       
            
         // Loop 1
        case 30:
            Globals::get()->animatorManager->getAnimator(1)->bLoopPalyndrome = !Globals::get()->animatorManager->getAnimator(1)->bLoopPalyndrome;
            
            Globals::get()->gui->liveGui->palydromBtn->setValue(!Globals::get()->gui->liveGui->palydromBtn->getValue());

            
            //Globals::get()->gui->liveGui->pa
            break;
            
        // Loop 2
        case 32:
            Globals::get()->animatorManager->getAnimator(2)->bLoopPalyndrome = !Globals::get()->animatorManager->getAnimator(2)->bLoopPalyndrome;
            break;
            
            
            // sens
        case 31:
            Globals::get()->animatorManager->getAnimator(1)->toggleDirection();
            break;
            
            
            // sens
        case 41:
            Globals::get()->animatorManager->getAnimator(1)->toggleDirection();
            break;
        
        case 16:
            Globals::get()->gui->liveGui->setRed(eightByteValue);
            
            break;

            
        case 17:
            Globals::get()->gui->liveGui->setGreen(eightByteValue);
            break;

        case 18:
            Globals::get()->gui->liveGui->setBlue(eightByteValue);
            break;

        case 19:
            Globals::get()->gui->liveGui->setWhite(eightByteValue);
            break;

        
        // switch anim prev next
        case 96:
            Globals::get()->gui->animPickerGui->nextAnim();
            break;
            
        case 97:
             Globals::get()->gui->animPickerGui->prevAnim();
            break;
            
            
       
            
       

            
    }
    
    
    
    switch (msg.pitch) {
            
        case 48:
        {
            Globals::get()->gui->liveGui->fullStrobBtn->setValue(!Globals::get()->gui->liveGui->fullStrobBtn->getValue());
            bool bFullStrob = Globals::get()->gui->liveGui->fullStrobBtn->getValue();
            
            if(bFullStrob) {
                Globals::get()->effectsManager->enableEffect(2);

            }
            else {
                Globals::get()->effectsManager->disableEffect(2);

            }

            break;
        }
            
        case 49:
            {
            Globals::get()->gui->liveGui->strobBtn->setValue(!Globals::get()->gui->liveGui->strobBtn->getValue());
            bool bStrob = Globals::get()->gui->liveGui->strobBtn->getValue();
            
            if(bStrob) {
                Globals::get()->effectsManager->enableEffect(0);
                
            }
            else {
                Globals::get()->effectsManager->disableEffect(0);
                
            }
            
            break;
            }
            
        case 50:
        {
            Globals::get()->gui->liveGui->audioReacBtn->setValue(!Globals::get()->gui->liveGui->audioReacBtn->getValue());
            bool bAudioReac = Globals::get()->gui->liveGui->audioReacBtn->getValue();
            
            if(bAudioReac) {
                Globals::get()->effectsManager->enableEffect(0);
                
            }
            else {
                Globals::get()->effectsManager->disableEffect(0);
                
            }
            
            break;
        }
            
        case 36:
            
            
            
            
            
            value = (int)ofMap(msg.value, 0, 127, 0, 255);
            Globals::get()->dmxManager->send(365,strobVelocity);
            Globals::get()->dmxManager->send(365+1,value);
            
            if(value == 0 ) {
                Globals::get()->dmxManager->send(365,0);
                
            }

            break;

            
        case 37:
            
            value = (int)ofMap(msg.value, 0, 127, 0, 255);
            Globals::get()->dmxManager->send(369,strobVelocity);

            Globals::get()->dmxManager->send(369+1, value);
            
            if(value == 0 ) {
                Globals::get()->dmxManager->send(369,0);

            }
            
            break;
            
            
        case 38:
       
            Globals::get()->sceneManager->setSelected(3);
            break;
            
            
        case 39:
            Globals::get()->sceneManager->setSelected(4);

            break;

            

    }
    

}