//
//  GridObject.h
//  Sucre
//
//  Created by Martial on 16/10/13.
//
//

#ifndef __Sucre__GridObject__
#define __Sucre__GridObject__

#include "ofMain.h"
#include "SceneObject.h"

class GridObject : public SceneObject {
    
public :
    
    GridObject();
    void setup();
    void update();
    void draw();
    
    
};

#endif /* defined(__Sucre__GridObject__) */
