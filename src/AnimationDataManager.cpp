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
    
    currentAnimation    = NULL;
    currentFrame        = 0;
    
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
        setAnimation(0);
    }
    
    Globals::instance()->gui->animPickerGui->setAnims(animations);

}

void AnimationDataManager::setAnimation(string name) {
    
    for (int i =0; i<animations.size(); i++) {
        
        if(animations[i]->name == name)
            setAnimation(i);
        
    }
    
}

void AnimationDataManager::setAnimation(int index) {
    
    currentAnimation = animations[index];
    currentFrame = 0;
    
     // update GUI
    
    Globals::instance()->gui->editorInspectorGui->setUrl(currentAnimation->name);
    Globals::instance()->gui->editorInspectorGui->setFrame(1, currentAnimation->getNumFrames());
    Globals::instance()->sceneManager->updateEditorFrames();
    
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
        Globals::instance()->gui->editorInspectorGui->setFrame(currentFrame+1, currentAnimation->getNumFrames());
        
        // update list
        
        
        
    }
    
    Globals::instance()->gui->animPickerGui->setAnims(animations);
    
}

void AnimationDataManager::addFrame(bool copyCurrent) {
    
    if(!currentAnimation)
        return;
    
    saveCurrentAnimation();
    currentAnimation->addFrame(currentFrame, copyCurrent);
    currentFrame++;
    Globals::instance()->sceneManager->updateEditorFrames();
    
}

void AnimationDataManager::pushFrame() {
    currentFrame++;
    if (currentFrame >= currentAnimation->frames.size()) {
        currentFrame = 0 ;
    }
    
    // populate
    
}

void AnimationDataManager::popFrame() {
    currentFrame--;
    if(currentFrame < 0 )
        currentFrame = currentAnimation->frames.size() -1;
}

vector<int> AnimationDataManager::getCurrentFrame() {
    
    if(!currentAnimation || currentAnimation->frames.size() == 0)
        return;
    
    return currentAnimation->frames[currentFrame];
    
    
}

vector<int> AnimationDataManager::getPrevFrame() {
    
    if(!currentAnimation)
        return;
    
    int frame = currentFrame - 1;
    if(frame < 0 )
        frame = currentAnimation->frames.size() -1;
    
    return currentAnimation->frames[frame];
    
    
}

vector<int> AnimationDataManager::getNextFrame() {
    
    if(!currentAnimation)
        return;
    
    int frame = currentFrame + 1;
    if(frame >= currentAnimation->frames.size() )
        frame = 0;
    
    return currentAnimation->frames[frame];
    
    
}



void AnimationDataManager::saveCurrentAnimation() {
    
    if(!currentAnimation)
        return;
    
    
    vector<SceneObject*> selected = Globals::instance()->sceneManager->getScene(0)->selecteds;
    vector<int> result;
    for (int i=0; i<selected.size(); i++) {
        result.push_back(selected[i]->id);
        
    }
    
    currentAnimation->setData(currentFrame, result);
    
    
}