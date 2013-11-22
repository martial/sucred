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
    mainScene->bDebugObjects = true;

    mainScene->bInteractive = true;
    mainScene->bDrawBack    = true;
    mainScene->setup(false);
    
    Scene * prevScene = new Scene();
    prevScene->setup(true);
    prevScene->container->setPos(-360, -0, 0);
    //prevScene->scale = .8f;
    prevScene->enableLightEvents(false);
    
    
    
    Scene * nextScene = new Scene();
    nextScene->setup(true);
    nextScene->container->setPos (360, 0, 0);
    //nextScene->scale = .8f;
    nextScene->enableLightEvents(false);
    
    Scene * previewScene = new Scene();
    previewScene->setup(true);
    //previewScene->scale = 2.0f;
    previewScene->enableLightEvents(false);
    
    
    Scene * overlayScene = new Scene();
    overlayScene->setup(true);
    //previewScene->scale = 2.0f;
    overlayScene->enableLightEvents(false);
    
    
    
    scenes.push_back(mainScene);
    scenes.push_back(prevScene);
    scenes.push_back(nextScene);
    scenes.push_back(previewScene);
    scenes.push_back(overlayScene);
    
    
}

void SceneManager::setMode(int mode) {
    
    
    
    if(mode == MODE_EDITOR) {
        //getScene(1)->bActive = true;
        //getScene(2)->bActive = true;
               
        
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

void SceneManager::setGlobalScale(float scale ) {
    
    for (int i=0; i<scenes.size(); i++) {
     
        scenes[i]->scale = scale;
        //scenes[i]->container
        
    }
    
    
}

void SceneManager::drawFbos() {
    
    
    
    ofEnableAlphaBlending();
    
    for (int i=0; i<scenes.size(); i++) {
        
        if(scenes[i]->bActive && scenes[i]->isFbo()) {
            
            // exception for prev next if animator is playing
            
            if( ( i == 1 || i == 2 ) && Globals::get()->animatorManager->getAnimator(0)->isPlaying()) {
                break;
            }
            
            if( ( i == 1 || i == 2 ) ) {
                
            glPushMatrix();
            glScalef(1, 1, 1);
            ofSetColor(255, 255, 255, 30);
                
            float x = (i == 1) ? (- 440 * scenes[i]->scale) : 440  * scenes[i]->scale;
                
            scenes[i]->fbo.draw(x, 0);
            glPopMatrix();
            }
            
        }
        
    }
    
}

Scene * SceneManager::getScene(int index) {
    
    return scenes[index];
}

void SceneManager::resetEditorFrames() {
    
    getScene(0)->deselectLightObjects(NULL);
    getScene(1)->deselectLightObjects(NULL);
    getScene(2)->deselectLightObjects(NULL);
    
    
    
}

void SceneManager::updateEditorFrames() {
    // dunno how to not do this :/
    int foo = 0;
    updateEditorFrames(foo);
}

void SceneManager::updateEditorFrames(int & e) {
    
    // enable or disable prev / nex
    
    AnimationDataManager * animData = Globals::get()->animData;
    
    // current frame on animation
    
    Animator * animator         = Globals::get()->animatorManager->getAnimator(0);
    
    getScene(1)->bActive = (animator->currentFrame != 0 );
    getScene(2)->bActive = (animator->currentFrame != ( animData->currentAnimation->getNumFrames() -1 ) );
    
    getScene(0)->setSelecteds(animData->getFrame(animator->currentFrame));
    getScene(1)->setSelecteds(animData->getPrevFrame(animator->currentFrame));
    getScene(2)->setSelecteds(animData->getNextFrame(animator->currentFrame));
    
    
    

    
    
}

void SceneManager::updatePreviewFrames(int & e ) {
    
    AnimationDataManager * animData = Globals::get()->animData;

    Animator * previewAnimator  = Globals::get()->animatorManager->getAnimator(1);
    getScene(3)->setSelecteds(animData->getNextFrame(previewAnimator->anim, previewAnimator->currentFrame));
    

    
}

void SceneManager::updateOverlayFrames(int & e ) {
    
    AnimationDataManager * animData = Globals::get()->animData;
    
    
    Animator * overlayAnimator  = Globals::get()->animatorManager->getAnimator(2);
    getScene(4)->setSelecteds(animData->getNextFrame(overlayAnimator->anim, overlayAnimator->currentFrame));
    
    
}


