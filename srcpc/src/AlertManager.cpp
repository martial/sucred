//
//  AlertManager.cpp
//  Sucre
//
//  Created by Martial on 15/11/2013.
//
//

#include "AlertManager.h"

void AlertManager::setup() {
    
    font.loadFont("fonts/205-MaaxBold.otf", 16);
    
}

void AlertManager::update() {
    
    for (int i=alerts.size()-1; i>=0; i-- ) {
        
        if (!alerts[i]->isAlive()) {
            
            delete alerts[i];
            alerts.erase(alerts.begin()+i);
            
            
        }
    }
    
    
}

void AlertManager::draw() {
    
    if(alerts.size() > 0 ) {
        
        ofEnableAlphaBlending();
        ofSetColor(0, 0, 0, 140);
        ofRect(0.0, 0.0, ofGetWidth(), ofGetHeight());
        
    }
    
    for (int i=0; i<alerts.size(); i++ ) {
        alerts[i]->draw();
    }
    
}


AppAlert * AlertManager::addSimpleAlert(string text, bool autoHide, int delay) {
    
    AppAlert * alert = new AppAlert(text, delay, &font, autoHide);
    alerts.push_back(alert);
    alert->show();
    
    return alert;
    
}

void AlertManager::removeSimpleAlert(AppAlert * alert) {
    
    for (int i=0; i<alerts.size(); i++ ) {
        if(alerts[i]== alert) {
            alert->hide();
        }
    }
    
}
