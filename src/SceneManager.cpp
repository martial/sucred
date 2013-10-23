//
//  SceneManager.cpp
//  Sucre
//
//  Created by Martial on 23/10/2013.
//
//


#include "SceneManager.h"
#include "testApp.h"
#include "Globals.h"

void SceneManager::setup() {
    
    Scene * mainScene = new Scene();
    mainScene->bInteractive = true;
    mainScene->setup(false);
    
    Scene * prevScene = new Scene();
    prevScene->setup(true);
    prevScene->container->setPos(-300, 0, 0);
    prevScene->scale = .8f;
    prevScene->enableLightEvents(false);
    
    Scene * nextScene = new Scene();
    nextScene->setup(true);
    nextScene->container->setPos(300, 0, 0);
    nextScene->scale = .8f;
    nextScene->enableLightEvents(false);

    
    scenes.push_back(mainScene);
    scenes.push_back(prevScene);
    scenes.push_back(nextScene);
    
    
    
    
}

void SceneManager::setMode(int mode) {
    
    
    
    if(mode == MODE_EDITOR) {
        getScene(1)->bActive = true;
        getScene(2)->bActive = true;
               
        
    }
    
    if(mode == MODE_LIVE) {
        getScene(1)->bActive = false;
        getScene(2)->bActive = false;
        
    }
    
    if(mode == MODE_CONFIG) {
        getScene(1)->bActive = false;
        getScene(2)->bActive = false;
        
    }
    
    
}


void SceneManager::update() {
    
    for (int i=0; i<scenes.size(); i++) {
        
        if(scenes[i]->bActive)
            scenes[i]->update();
        
    }
    
}

void SceneManager::draw() {
    
    for (int i=0; i<scenes.size(); i++) {
        
        if(scenes[i]->bActive)
            scenes[i]->draw();
        
    }
    
    


}

void SceneManager::drawFbos() {
    
    
    
    
    
    for (int i=0; i<scenes.size(); i++) {
        
        if(scenes[i]->bActive && scenes[i]->isFbo()) {
            
            glPushMatrix();
            glScalef(1, 1, 1);
            ofSetColor(255, 255, 255, 20);
            scenes[i]->fbo.draw(0, 0);
            glPopMatrix();
            
        }
        
    }
    
}

Scene * SceneManager::getScene(int index) {
    
    return scenes[index];
}

void SceneManager::updateEditorFrames() {
    
    // enable or disable prev / nex
    
    AnimationDataManager * animData = Globals::instance()->animData;
    
    //ofLog(OF_LOG_NOTICE, "CURRENT FRAME YOLO %d", animData->currentFrame);
    
    getScene(1)->bActive = (animData->currentFrame != 0 );
    getScene(2)->bActive = (animData->currentFrame != ( animData->currentAnimation->getNumFrames() -1 ) );
    
    getScene(0)->setSelecteds(animData->getCurrentFrame());
    getScene(1)->setSelecteds(animData->getPrevFrame());
    getScene(2)->setSelecteds(animData->getNextFrame());
    
    
    
}

