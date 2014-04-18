//
//  LightObject.h
//  Sucre
//
//  Created by Martial on 16/10/13.
//
//

#ifndef __Sucre__LightObject__
#define __Sucre__LightObject__

#include "ofMain.h"
#include "InteractiveSceneObject.h"
#include "LightDataObject.h"

class LightObject : public InteractiveSceneObject {
    
public :
    
    LightObject();
    void setup();
    void update();
    void draw(float *iMatrix, bool debug = false);
    
    void setRadius(float radius);
    
    void easeColor(ofColor * color, ofColor * colorTarget);
    
    ofEvent<SceneObjectEvent> readyToEffect;
    ofEvent<SceneObjectEvent> readyToDmx;
    
    ofColor dmxColor;
    float   dmxWhite;
    
    bool   strobDmx;
    
    //float masterDimmerPct;
    
    bool bDebug;
    
    bool bStatic;
    
private:
    
    float radius;
    
};

#endif /* defined(__Sucre__LightObject__) */
