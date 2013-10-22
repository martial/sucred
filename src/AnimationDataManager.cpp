//
//  AnimationDataManager.cpp
//  Sucre
//
//  Created by Martial on 21/10/13.
//
//

#include "AnimationDataManager.h"
#include "Globals.h"

AnimationDataManager::AnimationDataManager () {
    
    currentAnimation = NULL;
    
}

void AnimationDataManager::setup() {
    
    // check in the animations folder
    
    ofDirectory dir;
    dir.listDir("anims/");

    
    for(int i = 0; i < (int)dir.size(); i++){
		string url = dir.getPath(i);
        
        AnimationDataObject * data = new AnimationDataObject();
        data->loadFile(url);
        data->parse();
        animations.push_back(data);
        
	}
    
    if(animations.size() > 0 ) {
        currentAnimation = animations[0];
    
    }
}

void AnimationDataManager::setAnimation(int index) {
    
     currentAnimation = animations[index];
    
     // update GUI
    
    Globals::instance()->gui->editorInspectorGui->setUrl(currentAnimation->name);
     Globals::instance()->gui->editorInspectorGui->setFrame(0, currentAnimation->getNumFrames());
    
}

void AnimationDataManager::addAnimation() {
    
    ofFileDialogResult result = ofSystemSaveDialog("anim.xml", "Save as");
    
    string path = result.getPath();
    if ( path != "" ) {
        
        AnimationDataObject * data = new AnimationDataObject();
        data->name = result.getName();
        data->create(path);
        animations.push_back(data);
        
        currentAnimation    = data;
        currentFrame        = 0;
        
        Globals::instance()->gui->editorInspectorGui->setUrl(data->name);
        
    }
    
}

void AnimationDataManager::addFrame(bool copyCurrent) {
    
    if(!currentAnimation)
        return;
    
    saveCurrentAnimation();
    currentAnimation->addFrame(copyCurrent);
    currentFrame++;
    
    
}

void AnimationDataManager::pushFrame() {
    
}

void AnimationDataManager::popFrame() {
    
}

void AnimationDataManager::saveCurrentAnimation() {
    
    if(!currentAnimation)
        return;
    
    vector<SceneObject*> selected = Globals::instance()->scene->selecteds;
    vector<int> result;
    for (int i=0; i<selected.size(); i++) {
        result.push_back(selected[i]->id);
        
    }
    
    currentAnimation->setData(currentFrame, result);
    
    
}