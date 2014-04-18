//
//  SceneObjectEvent.h
//  Sucre
//
//  Created by Martial on 17/10/13.
//
//

#ifndef __Sucre__SceneObjectEvent__
#define __Sucre__SceneObjectEvent__

#include "ofMain.h"
#include "SceneObject.h"

class SceneObjectEvent : public ofEventArgs {
    
public:
    
    SceneObjectEvent(SceneObject * obj) {
        object = obj;
    }
    
    ~SceneObjectEvent () {
        //delete object;
    }
    int button;
    SceneObject *   object;
    
    
    
    
};

#endif /* defined(__Sucre__SceneObjectEvent__) */
