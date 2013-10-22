//
//  AnimationDataObject.cpp
//  Sucre
//
//  Created by Martial on 21/10/13.
//
//

#include "AnimationDataObject.h"

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
    
    for (int i=0; i<numOfFrames; i++) {
        
        pushTag("frame", i);
        
        frames.push_back(vector<int>());
        vector<int> ids;
        int numOfIds = getNumTags("id");
        
        for(int j=0; j<numOfIds; j++) {
                int id = getValue("frame", -1, j);
                ids.push_back(id);
        }
        
        frames[i] = ids;
        
        popTag();
        
    }
    
    popTag();
    
    popTag();
    
}

void AnimationDataObject::save () {
    
    
    
    
    
}

void AnimationDataObject::addFrame(bool copyCurrent) {
    
    frames.push_back(vector<int>());
    
}

void AnimationDataObject::setData(int frame, vector<int> ids) {
    
    
    frames[frame].clear();
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
    
        for (int i=0; i<ids.size(); i++) {
        
            setValue("id", ids[i], i);
        
        }
        popTag();
        
    }
    
    
    popTag();
    popTag();
    
    
    
    
    saveFile(path);
    
    
}