//
//  Scene.cpp
//  Sucre
//
//  Created by Martial on 16/10/13.
//
//

#include "Scene.h"
#include "ofxSosoRenderer.h"
#include "Globals.h"
#include "testApp.h"
#include "ofxModifierKeys.h"

Scene::Scene () {
    
    scale = 1.0;
    
    
}

void Scene::setup() {
    
    
    container = new SceneObject();
    
    setDefaultMatrix();
    setBasicLightGrid();
    
    ofAddListener(Globals::instance()->gui->selector.selectorLock, this, &Scene::onGuiSelectorEvent);
    
    // assignData
    

    Globals::instance()->data->assignData(getLightObjects());
    //Globals::instance()->data->updateLights(getLightObjects());

    
    //addObject(container);
    
    
}

void Scene::update() {
    
    container->xyzRot.y = tween.update();
    container->setScale(scale,scale,scale);
    
}

void Scene::draw() {
    
    
    ofEnableAlphaBlending();
    glEnable(GL_BLEND);
    
    float bgBrightness = 0.1;

    glClearColor(bgBrightness,bgBrightness,bgBrightness,bgBrightness);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    

    glPushMatrix();
    container->draw(defaultMatrix);
    glPopMatrix();
    

    
}

void Scene::animate() {
    
    tween.setParameters(1,easingquint,ofxTween::easeInOut, container->xyzRot.y, container->xyzRot.y + 360, 900, 0);
    
}

/* ------------------------ Setup */

void Scene::setBasicLightGrid() {
    
    float x, y;
    float radius    = 10.0;
    float spacing   = 40.0;
    
    float rows      = 8;
    float cols      = 8;
    
    x = - ( (rows / 2) * spacing ) + spacing / 2;
    y = - ( (cols / 2) * spacing ) + spacing / 2;;
    
    for (int i=0; i<rows; i++ ) {
        
        for (int j=0; j<cols; j++ ) {
        
        ofPtr<LightObject> light = ofPtr<LightObject> (new LightObject());
            
        light->id = j * cols + i;
        
        light->setRadius(radius);
        light->enableMouse();
        light->setPos(x + (i * spacing), y + (j*spacing), 0.0);
            
        container->addChild(light);
        
            
        }
        
    }
    
}

void Scene::addObject(SceneObject *obj) {
    
    objects.push_back(obj);
    
}

/* ---------------------- modes  */

void Scene::setMode(int mode) {
    
    animate();
    
    if (mode == MODE_LIVE ) {
        
        enableLightEvents(false);
        
    }
    
    if (mode == MODE_EDITOR ) {
        
        enableLightEvents(true);
        
    }
    
    if (mode == MODE_CONFIG ) {
        
        enableLightEvents(true);
        
    }
        
    
}


/* ---------------------- Events  */

void Scene::enableLightEvents (bool bEnabled) {
    
    deselectLightObjects(NULL);
    
    for (int i=0; i<container->childs.size(); i++) {
        ofPtr<LightObject> t =  dynamic_pointer_cast<LightObject>(container->childs[i]);
        if(t) {
            if (bEnabled)
                ofAddListener(t->mousePressed, this, &Scene::onObjectClickEvent);
            else
                ofRemoveListener(t->mousePressed, this, &Scene::onObjectClickEvent);

        }
    }
    
}

void Scene::deselectLightObjects (SceneObject *  exception) {
    
    for (int i=0; i<container->childs.size(); i++) {
        ofPtr<LightObject> t =  dynamic_pointer_cast<LightObject>(container->childs[i]);
        if(t && t.get() != exception) t->bSelected = false;
    }
    
}

void Scene::onObjectClickEvent(SceneObjectEvent & e) {
    
    if(!ofGetModifierPressed(OF_KEY_SHIFT)) {
        
        //for(vector<SceneObject*>::const_iterator it = selecteds.begin(); it != selecteds.end(); it++)
            //delete *it;
        
        selecteds.clear();
        
        deselectLightObjects (e.object);
        
    }
    
    
    if (!ofContains(selecteds, e.object))
        selecteds.push_back(e.object);
    
    if(selecteds.size() > 1) {
        Globals::instance()->gui->inspectorGui->setMulti(selecteds);
    } else {
        Globals::instance()->gui->inspectorGui->setId(e.object->id);
        Globals::instance()->gui->inspectorGui->setDmxAddress(e.object->data->dmxAddress);
    }
    
    
    Globals::instance()->animData->saveCurrentAnimation();
   
    
    
}

void Scene::onGuiSelectorEvent(SelectorEvent & e) {
    
    if(!ofGetModifierPressed(OF_KEY_SHIFT)) {
        selecteds.clear();
        deselectLightObjects(NULL);
        
    }
    
    for (int i=0; i<container->childs.size(); i++) {
        
        ofPtr<LightObject> t =  dynamic_pointer_cast<LightObject>(container->childs[i]);
        if(t)  {
            if (e.selection.inside (t->screenCoords)) t->bSelected = true;
            if (t->bSelected && !ofContains(selecteds, container->childs[i].get())) selecteds.push_back(t.get());
        }

    }
    
    if(selecteds.size() > 0)
        Globals::instance()->gui->inspectorGui->setMulti(selecteds);
    
    
}

vector<ofPtr<LightObject> > Scene::getLightObjects() {
    
    
    vector<ofPtr<LightObject> > result;
    for (int i=0; i<container->childs.size(); i++) {
        
        ofPtr<LightObject> t =  dynamic_pointer_cast<LightObject>(container->childs[i]);
        if(t) {
            result.push_back(t);
        }
        
    }
    
    return result;
    
}


/* ---------------------- Utils **/


void Scene::setDefaultMatrix() {
    
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


void Scene::updateData() {
    
    Globals::instance()->data->updateLights(getLightObjects());
    
}


