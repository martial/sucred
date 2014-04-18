//
//  AlertManager.h
//  Sucre
//
//  Created by Martial on 15/11/2013.
//
//

#ifndef __Sucre__AlertManager__
#define __Sucre__AlertManager__

#include "ofMain.h"
#include "Alert.h"

class AlertManager {
    
public:
    
    void setup();
    void update();
    void draw();
    
    void removeSimpleAlert(Alert * alert);
    
    Alert * addSimpleAlert(string text, bool autoHide = true, int delay = 2000);
    
private:
    
    vector<Alert* > alerts;
    
    ofTrueTypeFont font;
    
};

#endif /* defined(__Sucre__AlertManager__) */
