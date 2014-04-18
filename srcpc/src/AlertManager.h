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
#include "AppAlert.h"

class AlertManager {
    
public:
    
    void setup();
    void update();
    void draw();
    
    void removeSimpleAlert(AppAlert * alert);
    
    AppAlert * addSimpleAlert(string text, bool autoHide = true, int delay = 2000);
    
private:
    
    vector<AppAlert* > alerts;
    
    ofTrueTypeFont font;
    
};

#endif /* defined(__Sucre__AlertManager__) */
