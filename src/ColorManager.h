//
//  ColorManager.h
//  Sucre
//
//  Created by Martial on 31/10/2013.
//
//

#ifndef __Sucre__ColorManager__
#define __Sucre__ColorManager__

#include "ofMain.h"
#include "LightObject.h"
#include "ColorDataObject.h"
class ColorManager {
    
    
public:
    
    void setup();
    void setLightObjects(vector<ofPtr<LightObject> >  lightObjects);
    
    void update();
    
    void setGlobalColor(ofColor c, float white);
    void setGlobalColor(float r,float g, float b);
    
    void setGlobalDecay(float pct);
    void setGlobalAlpha(float pct);
    
    void setColorScheme(ColorDataObject * colorData);
    
    void resetColors();
    
    
    
private:
    
    vector<ofPtr<LightObject> >  lightObjects;
    
    
    
    
};

#endif /* defined(__Sucre__ColorManager__) */
