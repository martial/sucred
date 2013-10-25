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

class AnimationDataManager {
    
public:
    
    AnimationDataManager();
    void setup();
    
    void setAnimation(string name);
    void setAnimation(int index);
    
    void addAnimation();
    void addFrame(bool copyCurrent = false);
    void saveCurrentAnimation();
    
    void pushFrame();
    void popFrame();
    
    vector<int> getCurrentFrame();
    vector<int> getPrevFrame();
    vector<int> getNextFrame();
    
    AnimationDataObject             * currentAnimation;
    int                             currentFrame;
    vector<AnimationDataObject* >   animations;
    
};

#endif /* defined(__Sucre__AnimationDataManager__) */
