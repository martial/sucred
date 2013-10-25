//
//  AnimationDataObject.cpp
//  Sucre
//
//  Created by Martial on 21/10/13.
//
//

#include "AnimationDataObject.h"

AnimationDataObject::AnimationDataObject() {
    name = "undefined";
}

void AnimationDataObject::create(string path) {
    
    this->path = path;
    
    addTag("root");
    pushTag("root");
    addTag("name");
    setValue("name", name);
    addTag("frames");
    popTag();
    
    saveFile(path);
    
    // first frame
    
    frames.push_back(vector<int>());
                     
}

void AnimationDataObject::parse() {
    
    pushTag("root");
    
    name = getValue("name", "undefined");
    
    pushTag("frames");
    
    int numOfFrames = getNumTags("frame");
    ofLog(OF_LOG_NOTICE, "Num of frames : %d", numOfFrames);
    
    for (int i=0; i<numOfFrames; i++) {
        
        pushTag("frame", i);
        
        
        vector<int> ids;
        int numOfIds = getNumTags("id");
        
        
        for(int j=0; j<numOfIds; j++) {
                int id = getValue("id", -1, j);
                ids.push_back(id);
        }
        
        //frames[i] = ids;
        frames.push_back(ids);
        
        popTag();
        
    }
    
    popTag();
    
    popTag();
    
    if(frames.size()==0)
        addFrame(0);
    
    // 
    
}

void AnimationDataObject::save () {
    
        
    
}

void AnimationDataObject::addFrame(int index, bool copyCurrent) {
    
    // you can't copy current
        
    if(!copyCurrent)
        frames.insert(frames.begin() + index, vector<int>());
        else
    frames.insert(frames.begin() + index, frames[index]);
   
}

void AnimationDataObject::setData(int frame, vector<int> ids) {
    

    
    
    frames[frame] = ids;
    
    
   
    
    // find the right frame
    pushTag("root");
    
    // always save name
    setValue("name", name);
    
    
    pushTag("frames");
    
    // delete all
    clear();
    
    for (int j=0; j<frames.size(); j++) {
        
        addTag("frame");
        pushTag("frame", j);
    
        for (int i=0; i<frames[j].size(); i++) {
        
            setValue("id",  frames[j][i], i);
        
        }
        popTag();
        
    }
    
    
    popTag();
    popTag();
    

    
    
    saveFile(path);
    
    
}