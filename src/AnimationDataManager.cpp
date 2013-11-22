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
    currentColorScheme  = NULL;
    //currentFrame        = 0;
    
}

void AnimationDataManager::setup() {
    
    // check in the animations folder
    
    ofAddListener(httpUtils.newResponseEvent,this,&AnimationDataManager::newResponse);
    httpUtils.start();
    
    ofAddListener(httpUtilsColors.newResponseEvent,this,&AnimationDataManager::newResponseColors);
    httpUtilsColors.start();
    
    
    
    
    ofHttpResponse request = ofLoadURL("http://localhost:8888/sucre/upload?tmp="+ofToString(ofRandom(999)));
    
    string result = request.data;
    
    ofxXmlSettings xml;
    xml.loadFromBuffer(result);
    xml.saveFile("anims.xml");
    

    
    // get through all anims
    
    xml.pushTag("root");
    
    
    // ------------------------------------------------------------ animations
    
    xml.pushTag("animations");
    
    int numOfAnims = xml.getNumTags("anim");
    
    
    for(int i = 0; i < numOfAnims; i++){
        
        xml.pushTag("anim", i);
        
        AnimationDataObject * data = new AnimationDataObject();
        data->parse(&xml);
        
        animations.push_back(data);
        
        xml.popTag();
        
	}
    
    xml.popTag();
    
    // ------------------------------------------------------------ colors
    
    xml.pushTag("colors");
    
    int numOfColors = xml.getNumTags("color");
    
   // ofLog(OF_LOG_NOTICE, "num of color schemes %d", numOfColors);
    
    for(int i = 0; i < numOfColors; i++){
        
        
        
        xml.pushTag("color", i);
        
            ColorDataObject * colorData = new ColorDataObject();
            colorData->parse(&xml);
            colors.push_back(colorData);
        
            xml.popTag();
            
        
        
	}
    
    
    
    if(animations.size() > 0 ) {
        setAnimation(0);
    } else {
        addAnimation();
    }
    
    Globals::instance()->gui->animPickerGui->setAnims(animations);
    Globals::instance()->gui->colorPickerGui->setColors(colors);
}


/*
---------------------------------------------------------------------------------------------------- animations
*/


void AnimationDataManager::setAnimation(string name) {
    
    for (int i =0; i<animations.size(); i++) {
        
        if(animations[i]->name == name)
            setAnimation(i);
    }
    
}

void AnimationDataManager::setAnimationByID(int id) {
    
    
    for (int i =0; i<animations.size(); i++) {
        
        if(animations[i]->id == id)
            setAnimation(i);
        
    }

    
}

AnimationDataObject * AnimationDataManager::getAnimationByID(int id) {
    
    for (int i =0; i<animations.size(); i++) {
        
        if(animations[i]->id == id)
            return animations[i];
        
    }
    
    return NULL;
}

void AnimationDataManager::setAnimation(int index) {
    
    // first save current
  
    currentAnimation = animations[index];
    
    // update animator
    int foo = 0;
    ofNotifyEvent(resetEvent, foo);
    
    
    
     // update GUI
    Globals::get()->animatorManager->getAnimator(0)->setAnimation(currentAnimation);
    Globals::get()->animatorManager->getAnimator(1)->setAnimation(currentAnimation);
    Globals::get()->animatorManager->getAnimator(2)->setAnimation(currentAnimation);
    
    
    Globals::get()->gui->editorInspectorGui->setUrl(currentAnimation->name);
    Globals::get()->gui->editorInspectorGui->setFrame(1, currentAnimation->getNumFrames());
    Globals::get()->gui->animPickerGui->selectToggle(currentAnimation->id);
    Globals::get()->sceneManager->updateEditorFrames();
    
    // set speed
    
    
    
    
    
}

void AnimationDataManager::addAnimation() {
    
    
    
    // check if there's already unsaved color scheme
    
        for(int i=0; i<animations.size();i++) {
            if(animations[i]->id == 0) {
                Globals::instance()->alertManager->addSimpleAlert("'" +animations[i]->name + "' IS NOT SAVED");
                return;
            }
        }
    
        AnimationDataObject * data = new AnimationDataObject();
    
        data->name = "NEW ANIM";
        data->create();
        animations.push_back(data);
        
    
        // reset animator
        
        int foo = 0;
        ofNotifyEvent(resetEvent, foo);
        
        Globals::instance()->gui->editorInspectorGui->setUrl(data->name);
        Globals::instance()->gui->animPickerGui->setAnims(animations);
        Globals::instance()->gui->animPickerGui->selectToggle(currentAnimation->id);

    
        setAnimation((animations.size()-1));
    
    
}

void AnimationDataManager::deleteAnimation(string name) {
    
    /*
    if(name == "") {
        deleteAnimation(currentAnimation->name);
        return;
    }
    
    for (int i =0; i<animations.size(); i++) {
        
        if(animations[i]->name == name)
            deleteAnimation();
        
    }
     
     */
}

void AnimationDataManager::deleteAnimationByID(int id) {
    
    for (int i =0; i<animations.size(); i++) {
        
        if(animations[i]->id == id)
            deleteAnimation(i);
        
    }
    
}

void AnimationDataManager::deleteFrame(int index) {
    
    int frame = index;
    
    if(currentAnimation->frames.size() <= 1 )
        return;
   
    currentAnimation->deleteFrame(frame);
    
    // update animator
    int e = ( currentAnimation->frames.size() == 0 ) ? 0 : frame - 1;;
    if(e < 0 ) e = 0;
    
    ofNotifyEvent(updateEvent, e);
    Globals::instance()->sceneManager->updateEditorFrames();
   
    
}

void AnimationDataManager::deleteAnimation(int index) {
    
    AnimationDataObject * anim = animations[index];
    
    ofHttpResponse request = ofLoadURL("http://localhost:8888/sucre/sucre/deleteAnim/"+ ofToString(anim->id));
    
    animations.erase (animations.begin()+index);
    
    // update animator
    
    
    if(animations.size() == 0 ) {
        
        addAnimation();
        setAnimation(0);
    } else {
        int ind = (index == 0 ) ? 0 : index - 1;
        setAnimation(ind);
    }
    
    
    delete anim;
    anim = NULL;
    
    int e = index;
    ofNotifyEvent(resetEvent,e);
    
    Globals::instance()->gui->animPickerGui->setAnims(animations);
    Globals::instance()->gui->animPickerGui->selectToggle(currentAnimation->id);

}



void AnimationDataManager::addFrame(int index, bool copyCurrent) {
    
    if(!currentAnimation)
        return;
    
    saveCurrentFrame(index);
    currentAnimation->addFrame(index, copyCurrent);
    
    //TODO
    //event to updated animator
    int e = index + 1;
    
    ofNotifyEvent(updateEvent, e);
    
    
    
}



vector<int> AnimationDataManager::getFrame(int index) {
    
    if(!currentAnimation || currentAnimation->frames.size() == 0)
        return;
        
    return getFrame(currentAnimation, index);
    
}

vector<int> AnimationDataManager::getPrevFrame(int index) {
    
    if(!currentAnimation)
        return;
    
    return getPrevFrame(currentAnimation, index);
    
    
}

vector<int> AnimationDataManager::getNextFrame(int index) {
    
    if(!currentAnimation)
        return;
    
    return getNextFrame(currentAnimation, index);
    
    
}


vector<int> AnimationDataManager::getFrame(AnimationDataObject * anim, int index) {
    
    if(!anim || anim->frames.size() == 0)
        return;
    
    int i = ofClamp(index, 0, (anim->frames.size() -1 ));
    
    return anim->frames[i];
    
}
vector<int> AnimationDataManager::getPrevFrame(AnimationDataObject * anim,int index) {
    
    if(!anim)
        return;
    
    int frame = index - 1;
    if(frame < 0 )
        frame = anim->frames.size() -1;
    
    return anim->frames[frame];
    

    
}
vector<int> AnimationDataManager::getNextFrame(AnimationDataObject * anim,int index) {
    
    if(!anim)
        return;
    
    int frame = index + 1;
    if(frame >= anim->frames.size() )
        frame = 0;
    
    return anim->frames[frame];
    
}



void AnimationDataManager::saveCurrentFrame(int index) {
    
    if(!currentAnimation)
        return;
    
    
    vector<SceneObject*> selected = Globals::instance()->sceneManager->getScene(0)->getSelecteds();
    vector<int> result;
    for (int i=0; i<selected.size(); i++) {
        result.push_back(selected[i]->id);
        
    }
    
    currentAnimation->setData(index, result);
    
}

void AnimationDataManager::saveCurrentAnimation () {
    
    
    if(!currentAnimation)
        return;
    
    
    currentAnimation->save();
    
    if(currentAnimation->frames.size() == 1 && currentAnimation->frames[0].size() == 0 )
        return;
    
    ofxHttpForm form;
	form.action = "http://localhost:8888/sucre/";
	form.method = OFX_HTTP_POST;
	form.addFile("file","tmp.xml");
	httpUtils.addForm(form);
    saveAlert = Globals::instance()->alertManager->addSimpleAlert("SAVING...", false);
    
    
    
}

void AnimationDataManager::newResponse(ofxHttpResponse & response){
    
    
    string responseStr = ofToString(response.status) + ": " + (string)response.responseBody;
    
    ofLog(OF_LOG_NOTICE, responseStr);
    
    if(response.status != 200) {
        Globals::instance()->alertManager->addSimpleAlert("ERROR ! CHECK YOUR INTERNET");
    }
    
    if((string)response.responseBody == "error" ) {
        Globals::instance()->alertManager->addSimpleAlert("ERROR");
    } else {
        
         currentAnimation->id = ofToInt((string)response.responseBody);
         Globals::instance()->gui->animPickerGui->setAnims(animations);
        Globals::instance()->gui->animPickerGui->selectToggle(currentAnimation->id);
        
        if(saveAlert)
            saveAlert->hide();
        
         //Globals::instance()->alertManager->addSimpleAlert("ANIMATION SAVED !", 1000);
        
    }
    
}

/*
 ---------------------------------------------------------------------------------------------------- Colors
 */

void AnimationDataManager::addColorScheme() {
    
    // check if there's already unsaved color scheme
    
    for(int i=0; i<colors.size();i++) {
        if(colors[i]->id == -1) {
            Globals::instance()->alertManager->addSimpleAlert("'" +colors[i]->name + "' IS NOT SAVED");
            return;
        }
    }
    
    
    
    ColorDataObject * colorDataObject = new ColorDataObject();
    colorDataObject->name   = "new";
    colorDataObject->id     = -1;
    colors.push_back(colorDataObject);
    
    Globals::instance()->gui->colorPickerGui->setColors(colors);
    setColorSchemeByID(-1);
    Globals::instance()->gui->colorPickerGui->selectToggle(currentColorScheme->id);


    
}

void AnimationDataManager::saveColorScheme(ColorDataObject * colorDataObject, string name,vector<ofPtr<LightObject> > highlighteds) {
    
    colorDataObject->name   = name;
    //colorDataObject->id     = 0 ;
    
    colorDataObject->colors.clear();
    for (int i = 0; i<highlighteds.size(); i++ ) {
        colorDataObject->addColor(highlighteds[i]->id, highlighteds[i]->overrideColor, highlighteds[i]->bPermanentOverride);
    }
    
    colorDataObject->save();
    
    currentColorScheme = colorDataObject;
    
    ofxHttpForm form;
	form.action = "http://localhost:8888/sucre/sucre/uploadcolor";
	form.method = OFX_HTTP_POST;
	form.addFile("file","tmpcolor.xml");
	httpUtilsColors.addForm(form);
    saveAlert = Globals::instance()->alertManager->addSimpleAlert("SAVING...", false);
    
    
    
}

void AnimationDataManager::saveColorScheme(string name, vector<ofPtr<LightObject> > highlighteds) {
    
    ColorDataObject * colorDataObject;
    if(!currentColorScheme) {
        
        addColorScheme();
        

    }
    else
        saveColorScheme(currentColorScheme, currentColorScheme->name, highlighteds);
    
    
    Globals::instance()->gui->colorPickerGui->selectToggle(currentColorScheme->id);
    
}

void AnimationDataManager::deleteColorSchemeByID(int id) {
    
    for (int i=0; i<colors.size(); i++) {
        
        if(colors[i]->id == id)
            deleteColorScheme(i);
        
    }
    
}

void AnimationDataManager::deleteColorScheme(int index) {
    
    ColorDataObject * color = colors[index];
    
    ofHttpResponse request = ofLoadURL("http://localhost:8888/sucre/sucre/deletecolor/"+ ofToString(color->id));
    
    colors.erase (colors.begin()+index);
    
    // update animator
    
    
    if(colors.size() == 0 ) {
        
        addColorScheme();
    } else {
        int ind = (index == 0 ) ? 0 : index - 1;
        
        setColorScheme(ind);
    }
    
    
    delete color;
    color = NULL;
    
    Globals::instance()->gui->colorPickerGui->setColors(colors);
    Globals::instance()->gui->colorPickerGui->selectToggle(currentColorScheme->id);
}

void AnimationDataManager::setColorScheme(int index) {
    
    currentColorScheme = colors[index];
    Globals::instance()->gui->inspectorGui->colorInput->setTextString(currentColorScheme->name);

}

void AnimationDataManager::setColorSchemeByID(int id) {
    
    
    for (int i=0; i<colors.size(); i++) {
        
        if(colors[i]->id == id) {
            setColorScheme(i);
        }
        
    }
    
    Globals::instance()->gui->inspectorGui->colorInput->setTextString(currentColorScheme->name);
    
}


void AnimationDataManager::newResponseColors(ofxHttpResponse & response){
    
    
    string responseStr = ofToString(response.status) + ": " + (string)response.responseBody;
    
    if(response.status != 200) {
        Globals::instance()->alertManager->addSimpleAlert("ERROR ! CHECK YOUR INTERNET");
    }
    
    if((string)response.responseBody == "error" ) {
        Globals::instance()->alertManager->addSimpleAlert("ERROR");
    } else {
        
        currentColorScheme->id = ofToInt((string)response.responseBody);
        Globals::instance()->gui->colorPickerGui->setColors(colors);
        Globals::instance()->gui->colorPickerGui->selectToggle(currentColorScheme->id);
    
        
        if(saveAlert)
            saveAlert->hide();
        
        //Globals::instance()->alertManager->addSimpleAlert("ANIMATION SAVED !", 1000);
        
    }
    
}

