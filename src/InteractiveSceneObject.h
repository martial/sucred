//
//  InteractiveSceneObject.h
//  Sucre
//
//  Created by Martial on 16/10/13.
//
//

#ifndef __Sucre__InteractiveSceneObject__
#define __Sucre__InteractiveSceneObject__

#include "ofMain.h"
#include "SceneObject.h"

class InteractiveSceneObject : public SceneObject {
    
public:
    
    InteractiveSceneObject();
    void enableMouse();
    void disableMouse();
    

    
    
    bool bRollOver;
    bool bSelected;
    
private:
    
    void onMousePressed(ofMouseEventArgs & e);
    
};

#endif /* defined(__Sucre__InteractiveSceneObject__) */
