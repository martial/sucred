//
//  Scene.cpp
//  Sucre
//
//  Created by Martial on 16/10/13.
//
//

#include "Scene.h"
#include "ofxSosoRenderer.h"

Scene::Scene () {
    
    scale = 1.0;
    
    
}

void Scene::setup() {
    
    
    container = new SceneObject();
    

    

    setBasicLightGrid();
    
    //addObject(container);
    
    
    if(!defaultMatrix){
        defaultMatrix = (float *)malloc(sizeof(float) * 16);
        defaultMatrix[0] = 1.0;
        defaultMatrix[1] = 0;
        defaultMatrix[2] = 0;
        defaultMatrix[3] = 0;
        
        defaultMatrix[4] = 0;
        defaultMatrix[5] = 1.0;
        defaultMatrix[6] = 0;
        defaultMatrix[7] = 0;
        
        defaultMatrix[8] = 0;
        defaultMatrix[9] = 0;
        defaultMatrix[10] = 1.0;
        defaultMatrix[11] = 0;
        
        defaultMatrix[12] = 0;
        defaultMatrix[13] = 0;
        defaultMatrix[14] = 0;
        defaultMatrix[15] = 1.0;
    }
    
}

void Scene::update() {
    

    container->setScale(scale,scale,scale);
    
    
}

void Scene::draw() {
    
    
    ofEnableAlphaBlending();
    glEnable(GL_BLEND);
    ofColor backgroundColor;
    backgroundColor.r = 90;

    glClearColor(backgroundColor[0]/255.0f, backgroundColor[1]/255.0f, backgroundColor[2]/255.0f, backgroundColor[3]/255.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    

    glPushMatrix();
    container->draw(defaultMatrix);
    glPopMatrix();
    
    
    //ofLog(OF_LOG_NOTICE, "screenpos : %f %f %f", screenPos.x, screenPos.y, screenPos.z);
    
    //glPopMatrix();
    
}
/* ------------------------ */

void Scene::setBasicLightGrid() {
    
    float x, y;
    float radius    = 20.0;
    float spacing   = 100.0;
    
    float rows      = 8;
    float cols      = 8;
    
    x = - ( (rows / 2) * spacing ) + spacing / 2;
    y = - ( (cols / 2) * spacing ) + spacing / 2;;
    
    for (int i=0; i<rows; i++ ) {
        
        for (int j=0; j<cols; j++ ) {
        
        ofPtr<LightObject> light = ofPtr<LightObject> (new LightObject());
        light->id = i + j * cols;
        container->addChild(light);
        light->setRadius(radius);
        light->enableMouse();
        light->setPos(x + (i * spacing), y + (j*spacing), 0.0);
            
        }
        
    }
    
}

void Scene::addObject(SceneObject *obj) {
    
    objects.push_back(obj);
    
}