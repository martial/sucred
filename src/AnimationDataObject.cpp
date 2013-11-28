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

void AnimationDataObject::create() {
    
  
    // first frame
    id = 0;
    frames.push_back(vector<int>());
                     
}

void AnimationDataObject::rename(string name) {
    
    this->name = name;
    
}

void AnimationDataObject::parse() {
    
    pushTag("root");
    
    name = getValue("name", "undefined");
    speed = getValue("speed", 0.5);
    
    pushTag("frames");
    
    int numOfFrames = getNumTags("frame");
    //ofLog(OF_LOG_NOTICE, "Num of frames : %d", numOfFrames);
    
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
        addFrame(-1);
    
    // 
    
}

void AnimationDataObject::parse(ofxXmlSettings * node) {
    
    // we should be here on the right node
    
    this->id                = node->getValue("id", 0);
    this->name              = node->getValue("name", "undefined");
    this->speed             = node->getValue("speed", 0.5);
    this->categoriesParsed  = node->getValue("categories", "");
    
    this->categories = ofSplitString(categoriesParsed, ",");
    
    //ofLog(OF_LOG_NOTICE, categoriesParsed);
    
    //ofLog(OF_LOG_NOTICE, "ADD ID %d", id);
    
    node->pushTag("frames");
    int numOfFrames = node->getNumTags("frame");
    
     for (int i=0; i<numOfFrames; i++) {
         
         node->pushTag("frame", i);
         int numOfIds = node->getNumTags("id");
         
         vector<int> ids;
         
         for(int j=0; j<numOfIds; j++) {
             
             int id = node->getValue("id", -1, j);
             ids.push_back(id);
         }
         
         frames.push_back(ids);
         node->popTag();
         
         
     }
    
    
    node->popTag();
    
    if(frames.size()==0)
        addFrame(-1);
    
    
}

void AnimationDataObject::save () {
    
    // delete all
    clear();
    
    // find the right frame
    addTag("root");
    pushTag("root");
    
    addTag("id");
    setValue("id", id);
    
    // always save name
    addTag("name");
    setValue("name", name);
    
    // always save name
    addTag("speed");
    setValue("speed", speed);
    
    addTag("categories");
    setValue("categories", categoriesParsed);
    
    addTag("frames");
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
    
    
    
    
    saveFile("tmp.xml");

    
        
    
}

void AnimationDataObject::addFrame(int index, bool copyCurrent) {
    
    // you can't copy current
        
    if(!copyCurrent) {
    frames.insert(frames.begin() + index +1, vector<int>());
    }
    else {
        vector<int> data = frames[index];
        frames.insert(frames.begin() + index + 1, data);
    }
   
}

void AnimationDataObject::deleteFrame(int index) {
    
      if ( index >= frames.size())
          return;
    
    
     frames.erase(frames.begin()+index);
     if(frames.size()==0)
         addFrame(0);
    
     
    
}

void AnimationDataObject::setCategories(vector<string> categories) {
    
    this->categories = categories;
    categoriesParsed = "";
    for (int i=0; i<categories.size(); i++ ) {
        categoriesParsed += categories[i];
        if(i<categories.size()-1)
            categoriesParsed += ",";
    }
    
    //ofLog(OF_LOG_NOTICE, categoriesParsed);
    
}

void AnimationDataObject::setData(int frame, vector<int> ids) {
    
    //ofLog(OF_LOG_NOTICE, " frame[%d], with %d elements", frame, ids.size());
    frames[frame] = ids;
    
    save();
    
    
    
}