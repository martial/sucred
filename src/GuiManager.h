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
#include "ConfigGui.h"
#include "EditorGui.h"
#include "Selector.h"
#include "EditorInspectorGui.h"
#include "AnimationPickerGui.h"
#include "ColorPickerGui.h"

class GuiManager {
    
public:
    
    void setup ();
    void update();
    void draw();
    void loadSettings();
    void onGuiEvent(ofxUIEventArgs & e);
    
    void setMode(int mode);
    
    void animate();
    
    /* */
    void showInspector();
    void hideInspector();
    
    void save();
    
    ofRectangle     getEmptyUIZone();
    
    LiveGui         *       liveGui;
    InspectorGui    *       inspectorGui;
    ConfigGui       *       configGui;
    EditorGui       *       editorGui;
    EditorInspectorGui *    editorInspectorGui;
    AnimationPickerGui *    animPickerGui;
    ColorPickerGui  *       colorPickerGui;
    
    Selector selector;
    
private :
    


    
    
    
   
    
};

#endif /* defined(__Sucre__GuiManager__) */
