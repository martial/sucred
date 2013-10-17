//
//  SceneObject.h
//  Sucre
//
//  Created by Martial on 16/10/13.
//
//

#ifndef __Sucre__SceneObject__
#define __Sucre__SceneObject__

#include "ofMain.h"

class SceneObject {
    
public:
    
    SceneObject();
    virtual void setup();
    virtual void update(float *iMatrix);
    virtual void draw(float *iMatrix, bool debug = false);
    virtual void drawBoundingBox();
    
    virtual void setPos(float x, float y, float z);
    virtual void setScale(float x, float y, float z);
    
    virtual void addChild(ofPtr<SceneObject> object);
    
    
    float   * getMatrix();
    float   * getLocalMatrix();
    
    virtual ofVec3f getWindowCoords();
    
    int id;
    
    vector <ofPtr<SceneObject> >    childs;
    vector <ofPtr<SceneObject> >  parents;
    
    ofVec3f screenCoords;
    
    
protected:
    
    
    float       *localMatrix;
    float       *matrix;
    ofVec3f     xyzRot,xyz,scale;
    
    
    
    ofRectangle boundingBox;
    
    /* matrices operations */
    
    
    void    loadIdentity(float *dest);
    void    updateLocalMatrix();
    void    updateMatrices(float *iParentMatrix);
    float*  updateMatrix(float *iParentMatrix);
    void    Mul(float *source1, float *source2, float *_dest);
    
    bool    localMatrixDirty,alwaysMatrixDirty,matrixDirty;
    
    
    bool hitTest(float x, float y);

    
};

#endif /* defined(__Sucre__SceneObject__) */
