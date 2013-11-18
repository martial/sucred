//
//  SceneObject.cpp
//  Sucre
//
//  Created by Martial on 16/10/13.
//
//

#include "SceneObject.h"

SceneObject::SceneObject () {
    
    
    //transformation matrix
	matrix = (float*)malloc(sizeof(float)*16);
	loadIdentity(matrix);
	//matrixTmp = (float*)malloc(sizeof(float)*16);
	localMatrix = (float*)malloc(sizeof(float)*16);
	loadIdentity(localMatrix);
    
    setPos(0.0f, 0.0f, 0.0f);
    xyzRot.set(0., 0., 0.);
    xyz.set(0.,0.,0.);
    scale.set(1.0,1.0, 1.0);
    boundingBox.set(0,0,0,0);
    
    color.set(255);
    overrideColor.set(0,0,0);
    finalColor.set(255);
    
    overrideAlpha   = 1.0;
    alpha           = 1.0;
    decay           = 1.0;
    
    blur            = 0.9;
    
    
    alwaysMatrixDirty = false;
    localMatrixDirty  = true;
    
    id = 0;
    
    bDrawback = false;
    
    bPermanentOverride = false;
    
}

SceneObject::~SceneObject() {
    
}


void SceneObject::setup () {
    
    
}

void SceneObject::update (float *iMatrix) {
    
    /*
    float *mat = updateMatrix(iMatrix);
    
    for ( int i=0; i<childs.size(); i++)
        childs[i]->update(mat);
    */
    
    
}

void SceneObject::draw (float *iMatrix, bool debug) {
    
    
   
    ofLoadMatrix(matrix);
    
    if(bDrawback) {
        float w = 370;
        float h = 430;
        ofNoFill();
        ofSetColor(10);
        ofRect(-w / 2, -h / 2, w,h);
        ofFill();
    }
    
    
    //glLoadMatrixf(matrix);
        
    if(debug) {
        ofSetColor(255,0,0);
        ofRect(0.0,0.0, 100, 100);
    }
        
    float *mat = updateMatrix(iMatrix);

    for ( int i=0; i<childs.size(); i++) {
        childs[i]->draw(mat, false);
        
    }
    
    screenCoords = getWindowCoords();
    
}

void SceneObject::drawBoundingBox () {
    
    ofSetColor(255);
    ofNoFill();
    ofRect(boundingBox);
    ofFill();
}

void SceneObject::addChild(ofPtr<SceneObject> object) {
    
    childs.push_back(object);
    object->parents.push_back(ofPtr<SceneObject>(this));
}

void SceneObject::setScale(float x, float y, float z) {
    
    scale.set(x, y, z);
}

void SceneObject::setPos(float x, float y, float z)
{
    xyz.set(x, y, z);
    
    localMatrix[12] = xyz[0];
    localMatrix[13] = xyz[1];
    localMatrix[14] = xyz[2];
    matrixDirty = true;
}



void SceneObject::loadIdentity(float *dest)
{
    dest[0] = 1;
    dest[1] = 0;
    dest[2] = 0;
    dest[3] = 0;
    
    dest[4] = 0;
    dest[5] = 1;
    dest[6] = 0;
    dest[7] = 0;
    
    dest[8] = 0;
    dest[9] = 0;
    dest[10] = 1;
    dest[11] = 0;
    
    dest[12] = 0;
    dest[13] = 0;
    dest[14] = 0;
    dest[15] = 1;
}

void SceneObject::updateLocalMatrix()
{
    static float cX, sX, cY, sY, cZ, sZ;        //for xyz rotation
    
    //calculate cos + sin for rotations ONCE
    cX = (float)cos(xyzRot[0] * DEG_TO_RAD);
    sX = (float)sin(xyzRot[0] * DEG_TO_RAD);
    cY = (float)cos(xyzRot[1] * DEG_TO_RAD);
    sY = (float)sin(xyzRot[1] * DEG_TO_RAD);
    cZ = (float)cos(xyzRot[2] * DEG_TO_RAD);
    sZ = (float)sin(xyzRot[2] * DEG_TO_RAD);
    
    //build composite matrix for XYZ rotation:
    //order of transformations:  scale, rotateX, rotateY, rotateZ, translate
    localMatrix[0] = scale.x * (cY*cZ);
    localMatrix[4] = scale.y * (-cY*sZ);
    localMatrix[8] = scale.z * (sY);
    
    localMatrix[1] = scale.x * (sX*sY*cZ + cX*sZ);
    localMatrix[5] = scale.y * (-sX*sY*sZ + cX*cZ);
    localMatrix[9] = scale.z * (-sX*cY);
    
    localMatrix[2] = scale.x * (-cX*sY*cZ + sX*sZ);
    localMatrix[6] = scale.y * (cX*sY*sZ + sX*cZ);
    localMatrix[10] = scale.z * (cX*cY);
    
    
    localMatrixDirty = false;
}

void SceneObject::updateMatrices(float *iParentMatrix)
{
    static float *mat = NULL;
    
    if (iParentMatrix != NULL) {
        mat = iParentMatrix;
    }
    else {
        // create root matrix
        if (mat == NULL) {
            mat = (float *)malloc(sizeof(float) * 16);
            loadIdentity(mat);
        }
    }
    
    float *matrix2 = updateMatrix(mat);
    
    for (unsigned int i = 0; i < childs.size(); i++) {
        childs[i]->updateMatrices(matrix2);
    }
}


float* SceneObject::updateMatrix(float *iParentMatrix)
{
    // if the object has multiple parents, the hierarchy tree matrix needs to be set to dirty, using mMatrixDirty.
    if (parents.size() > 1) matrixDirty = true;
    
    localMatrixDirty = true;
    if (matrixDirty  ||  localMatrixDirty  || alwaysMatrixDirty) {
        if (localMatrixDirty) {
            updateLocalMatrix();
        }
        
        //matrix multiplication
        Mul(localMatrix, iParentMatrix, matrix);
        
        
        // set matrix dirty flags of all children
        for (unsigned int i = 0; i < childs.size(); i++)
            childs[i]->matrixDirty = true;
        
        //reset matrix dirty flag
        matrixDirty = false;
    }
    
    return matrix;
}

void SceneObject::Mul(float *source1, float *source2, float *_dest)
{
    float dest[16];
    
    dest[0] = source1[0]*source2[0] + source1[1]*source2[4] + source1[2]*source2[8] + source1[3]*source1[12];
    dest[1] = source1[0]*source2[1] + source1[1]*source2[5] + source1[2]*source2[9] + source1[3]*source2[13];
    dest[2] = source1[0]*source2[2] + source1[1]*source2[6] + source1[2]*source2[10] + source1[3]*source2[14];
    dest[3] = source1[0]*source2[3] + source1[1]*source2[7] + source1[2]*source2[11] + source1[3]*source2[15];
    
    dest[4] = source1[4]*source2[0] + source1[5]*source2[4] + source1[6]*source2[8] + source1[7]*source2[12];
    dest[5] = source1[4]*source2[1] + source1[5]*source2[5] + source1[6]*source2[9] + source1[7]*source2[13];
    dest[6] = source1[4]*source2[2] + source1[5]*source2[6] + source1[6]*source2[10] + source1[7]*source2[14];
    dest[7] = source1[4]*source2[3] + source1[5]*source2[7] + source1[6]*source2[11] + source1[7]*source2[15];
    
    dest[8] = source1[8]*source2[0] + source1[9]*source2[4] + source1[10]*source2[8] + source1[11]*source2[12];
    dest[9] = source1[8]*source2[1] + source1[9]*source2[5] + source1[10]*source2[9] + source1[11]*source2[13];
    dest[10] = source1[8]*source2[2] + source1[9]*source2[6] + source1[10]*source2[10] + source1[11]*source2[14];
    dest[11] = source1[8]*source2[3] + source1[9]*source2[7] + source1[10]*source2[11] + source1[11]*source2[15];
    
    dest[12] = source1[12]*source2[0] + source1[13]*source2[4] + source1[14]*source2[8] + source1[15]*source2[12];
    dest[13] = source1[12]*source2[1] + source1[13]*source2[5] + source1[14]*source2[9] + source1[15]*source2[13];
    dest[14] = source1[12]*source2[2] + source1[13]*source2[6] + source1[14]*source2[10] + source1[15]*source2[14];
    dest[15] = source1[12]*source2[3] + source1[13]*source2[7] + source1[14]*source2[11] + source1[15]*source2[15];
    
    for (int i = 0; i < 16; i++)
        _dest[i] = dest[i];
}

float* SceneObject::getMatrix()
{
    return (float *)matrix;
}

float* SceneObject::getLocalMatrix()
{
    return (float *)localMatrix;
    
}


ofVec3f SceneObject::getWindowCoords()
{
    double                mM[16];
    double                wx, wy, wz;
    GLint                 v[4];
    double                pM[16];
    
    // this gets set once up top
    glGetIntegerv(GL_VIEWPORT, v);
    // this gets set once up top
    glGetDoublev(GL_PROJECTION_MATRIX, pM);
    
    // grab the most recent version of the MODELVIEW matrix
    glGetDoublev(GL_MODELVIEW_MATRIX, mM);
    float *curMat = getMatrix();
    for (int i=0; i < 16; i++) mM[i] = (double)curMat[i];
    
    gluProject(0, 0, 0, mM, pM, v, &wx, &wy, &wz);
    
    // flip
    
    wy = ofGetHeight() - wy;
    
    return ofVec3f(wx, wy, wz);
}


bool SceneObject::hitTest(float x, float y) {
    
    
    ofRectangle box;
    box.set(screenCoords.x + boundingBox.x, screenCoords.y + boundingBox.y, boundingBox.width, boundingBox.height);
    
    return box.inside(x,y);
}

bool SceneObject::hasOverrideColor() {
    
    return (overrideColor.r > 0 || overrideColor.g > 0 || overrideColor.b > 0);
    
}



