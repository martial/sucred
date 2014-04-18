//
//  Scene.h
//  Sucre
//
//  Created by Martial on 16/10/13.
//
//

#ifndef __Sucre__Scene__
#define __Sucre__Scene__

#include "ofMain.h"
#include "SceneObject.h"
#include "GridObject.h"
#include "LightObject.h"
#include "SceneObjectEvent.h"
#include "Selector.h"
#include "ofxTween.h"


class Scene {
    
public :
    
    Scene();
    void setup(bool useFbo = false);
    void update();
    void draw();
    
    void drawOutput();
    
    void setBasicLightGrid();
    
    void setSelecteds(vector<int> selecteds);
    
    /* events  */
    void enableLightEvents (bool bEnabled);
    void onObjectClickEvent (SceneObjectEvent & e);
    void onGuiSelectorEvent(SelectorEvent & e);
    
    /* ----- */
    void deselectLightObjects (SceneObject *  exception );
    void deHighlightLightObjects (SceneObject *  exception );

    
    float   scale;
    void    setMode(int mode);
    void    animate();
    
    vector<SceneObject* > getSelecteds();
    vector<SceneObject* > getHighLighteds() ;
    
    vector<ofPtr<LightObject> > getLightObjects();
    vector<SceneObject* > selecteds;
    
    
    void updateData();
    
    void setStatic(bool bStatic);
    
    SceneObject * container;
    
    bool bActive;
    bool bInteractive;
    
    ofFbo fbo, outputFbo;
    
    void onResizeEvent(ofResizeEventArgs & e);
    
    bool isFbo() {return bUseFbo;};
    
    bool bDrawBack;
    
    vector<ofPtr<LightObject> >   lightObjects;
    
    bool bDebugObjects;
    
    ofRectangle getRect();
    ofRectangle bBox;
    
    bool bStatic;
    
    bool bSelected;
    
    ofRectangle clickableZone;
    
    int colorSchemeId;
    
    float alpha;

    
private:
    
    
    void setDefaultMatrix();
    void addObject(SceneObject * obj);
    
    vector<SceneObject*>        objects;
    
    float *defaultMatrix;
    
    /* objects */

    
    SceneObject * test;
    
    /* utils  */
    
    
    ofxTween        tween, tweenScale;
    ofxEasingQuint 	easingquint;
    
    int mode;
    bool bUseFbo;
    
    float rows, cols;
    
    

    
};

#endif /* defined(__Sucre__Scene__) */
