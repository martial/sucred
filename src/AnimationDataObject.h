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
    
    
    void create(string path);
    void parse();
    
    void save();
    
    void addFrame(bool copyCurrent = false);
    void setData(int frame, vector<int> ids);
    
    int getNumFrames() {return frames.size();}
    
    vector<vector<int> > frames;
    
    
};

#endif /* defined(__Sucre__AnimationDataObject__) */
