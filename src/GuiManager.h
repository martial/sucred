//
//  GuiManager.h
//  Sucre
//
//  Created by Martial on 16/10/13.
//
//

#ifndef __Sucre__GuiManager__
#define __Sucre__GuiManager__

#include "ofMain.h"
#include "LiveGui.h"
#include "InspectorGui.h"
#include "EditorGui.h"
#include "Selector.h"


class GuiManager {
    
public:
    
    void setup ();
    void update();
    void draw();
    void onGuiEvent(ofxUIEventArgs & e);
    
    void setMode(int mode);
    
    void animate();
    
    /* */
    void showInspector();
    void hideInspector();
    
    ofRectangle     getEmptyUIZone();
    
    LiveGui         * liveGui;
    InspectorGui    * inspectorGui;
    EditorGui       * editorGui;
    
    Selector selector;
    
private :
    


    
    
    
   
    
};

#endif /* defined(__Sucre__GuiManager__) */
