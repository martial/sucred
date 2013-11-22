//
//  AnimationDataObject.h
//  Sucre
//
//  Created by Martial on 21/10/13.
//
//

#ifndef __Sucre__AnimationDataObject__
#define __Sucre__AnimationDataObject__

#include "ofMain.h"
#include "AnimationDataObject.h"
#include "ofxXmlSettings.h"

class AnimationDataObject  : public  ofxXmlSettings {
    
public:
    
    
    AnimationDataObject();
    int     id;
    string  name;
    string path;
    float speed;
    
    
    void create();
    void parse();
    void parse(ofxXmlSettings * node);
    
    void rename(string name);
    
    void save();
    
    void addFrame(int index, bool copyCurrent = false);
    void deleteFrame(int index = -1);
    void setData(int frame, vector<int> ids);
    
    int getNumFrames() {return frames.size();}
    
    vector<vector<int> > frames;
    
    
};

#endif /* defined(__Sucre__AnimationDataObject__) */
