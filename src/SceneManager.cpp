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
    previewScene->bSelected = true;
    
    
    Scene * overlayScene = new Scene();

    overlayScene->setup(true);
    //previewScene->scale = 2.0f;
    overlayScene->enableLightEvents(false);
    
    
    scenes.push_back(mainScene);
    scenes.push_back(prevScene);
    scenes.push_back(nextScene);
    scenes.push_back(previewScene);
    scenes.push_back(overlayScene);
    
    ofAddListener(ofEvents().mousePressed, this, &SceneManager::onMousePressed);
    
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
            
            if( (i == 1 || i == 2 ) ) {
                
            glPushMatrix();
            glScalef(1, 1, 1);
            ofSetColor(255, 255, 255, 30);
                
            float x = (i == 1) ? (- 440 * scenes[i]->scale) : 440  * scenes[i]->scale;
                
            scenes[i]->fbo.draw(x, 0);
            glPopMatrix();
            }
            
            if(i == 0 ) {
                glPushMatrix();
                glScalef(1, 1, 1);
                ofSetColor(255, 255, 255, 255);
                scenes[i]->fbo.draw(0, 0);
                glPopMatrix();
                
            }
            
        }
        
    }
    
}

void SceneManager::drawFbo(int index) {
    
    
}

void SceneManager::drawPreviews() {
    
    ofPushMatrix();
    ofTranslate((int)(ofGetWidth()/3), (int)(ofGetHeight()/3 + ( ofGetHeight() / 3 / 4 ) - ofGetHeight() * .5));
    ofRectangle rect = getScene(0)->bBox;
    ofSetColor(255,255,255,255);
    
    getScene(3)->clickableZone.set(-(int)(ofGetWidth() / 3 / 4), 0.0, (int)(ofGetWidth() / 3), (int)(ofGetHeight() / 3) );
    getScene(3)->fbo.draw(getScene(3)->clickableZone.x, getScene(3)->clickableZone.y, getScene(3)->clickableZone.width, getScene(3)->clickableZone.height);
    
    
    getScene(4)->clickableZone.set((int)(ofGetWidth() / 3 / 4), 0.0, (int)(ofGetWidth() / 3), (int)(ofGetHeight() / 3) );
    getScene(4)->fbo.draw(getScene(4)->clickableZone.x, getScene(4)->clickableZone.y, getScene(4)->clickableZone.width, getScene(4)->clickableZone.height);
    
    getScene(3)->clickableZone.x += (ofGetWidth()/3);
    getScene(3)->clickableZone.y += (int)(ofGetHeight()/3 + ( ofGetHeight() / 3 / 4 ) - ofGetHeight() * .5);
    
    getScene(4)->clickableZone.x += (ofGetWidth()/3);
    getScene(4)->clickableZone.y += (int)(ofGetHeight()/3 + ( ofGetHeight() / 3 / 4 ) - ofGetHeight() * .5);
    
    ofPopMatrix();
    
    getScene(3)->clickableZone.width /= 2;
    getScene(3)->clickableZone.x +=  getScene(3)->clickableZone.width/2;
    
    getScene(4)->clickableZone.width /= 2;
    getScene(4)->clickableZone.x +=  getScene(4)->clickableZone.width/2;
    
    
    //ofSetColor(255,0,0);
    //ofRect(getScene(4)->clickableZone);

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

void SceneManager::onMousePressed(ofMouseEventArgs & e) {
    
    
    if(Globals::get()->gui->isRollOver() || Globals::instance()->app->mode != MODE_LIVE)
        return;
    // here we need to be able to select the fbos
    
    int selected = 0;
    for (int i=0; i<scenes.size(); i++) {
        
        if(scenes[i]->clickableZone.inside(e.x, e.y)) {
            
            scenes[i]->bSelected = true;
            selected = i;
            
        } else {
            scenes[i]->bSelected = false;
        }
        
    }
    
    // always select first preview if none
    
    if(getSelected() == 0 ) {
        scenes[3]->bSelected = true;
        selected = 3;
    }
    
    
    ofNotifyEvent(sceneChanged, selected );
    
    
}

int SceneManager::getSelected () {
    
    
    // here we need to be able to select the fbos
    for (int i=0; i<scenes.size(); i++) {
        
        if(scenes[i]->bSelected) return i;
    }

    return 0;
    
}

void SceneManager::setSelected(int index) {
    
    // here we need to be able to select the fbos
    for (int i=0; i<scenes.size(); i++) {
        
        scenes[i]->bSelected = false;
    }
    
    scenes[index]->bSelected = true;
    
    ofNotifyEvent(sceneChanged, index );

    
    
}


