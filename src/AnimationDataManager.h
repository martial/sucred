//
//  AnimationDataManager.h
//  Sucre
//
//  Created by Martial on 21/10/13.
//
//

#ifndef __Sucre__AnimationDataManager__
#define __Sucre__AnimationDataManager__

#include "ofMain.h"
#include "AnimationDataObject.h"
#include "ofxHttpUtils.h"
#include "Alert.h"
#include "ColorDataObject.h"
#include "LightObject.h"


class AnimationDataManager {
    
public:
    
    AnimationDataManager();
    void setup();
    
    void deleteAnimation(string name = "");
    void deleteAnimation(int index);
    void deleteAnimationByID(int id);
    void setAnimation(string name);
    void setAnimation(int index);
    void setAnimationByID(int id);
    
    AnimationDataObject             * getRandomAnimation();
    AnimationDataObject             * getRandomAnimation(vector<string> categories);
    
    AnimationDataObject * getAnimationByID(int id);
    
    void addAnimation();
    void addFrame(int index, bool copyCurrent = false);
    void deleteFrame(int index );
    void saveCurrentFrame(int index);
    
    void saveCurrentAnimation();
        
    vector<int> getFrame(int index);
    vector<int> getPrevFrame(int index);
    vector<int> getNextFrame(int index);
    
    vector<int> getFrame(AnimationDataObject * anim, int index);
    vector<int> getPrevFrame(AnimationDataObject * anim,int index);
    vector<int> getNextFrame(AnimationDataObject * anim,int index);
    
    AnimationDataObject             * currentAnimation;
    //int                             currentFrame;
    vector<AnimationDataObject* >   animations;
    vector<ColorDataObject* >       colors;
    
    ofEvent<int>                    resetEvent;
    ofEvent<int>                    updateEvent;
    
    ofxHttpUtils                    httpUtils;
    ofxHttpUtils                    httpUtilsColors;
    
    Alert   *                       saveAlert;
    
    void newResponse(ofxHttpResponse & response);
    
    
    /*
     * colors
     */
    
    void setColorScheme(int index);
    void setColorSchemeByID(int id);
    void addColorScheme();
    void saveColorScheme(ColorDataObject * colorDataObject, string name, vector<ofPtr<LightObject> > highlighteds);
    void saveColorScheme(string name, vector<ofPtr<LightObject> > highlighteds);
    void deleteColorScheme(int index);
    void deleteColorSchemeByID(int id);
    
    
    ColorDataObject             * getRandomColor();

    void newResponseColors(ofxHttpResponse & response);
    ColorDataObject             * currentColorScheme;

    
};

#endif /* defined(__Sucre__AnimationDataManager__) */
