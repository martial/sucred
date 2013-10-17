//
//  EditorGui.cpp
//  Sucre
//
//  Created by Martial on 17/10/13.
//
//

#include "EditorGui.h"
#include "Globals.h"

void EditorGui::init () {
    
    live->setValue      (false);
    editor->setValue    (true);
    config->setValue    (false);
    
}

void EditorGui::populate () {
    
    
    setDrawBack(true);
    setAutoDraw(false);
    
    
    image.loadImage("GUI/logo.png");
    addImage("", &image, 80, 80);
    
    
    addSpacer();
    addFPS();
    addSpacer();
    
    live            = addToggle("LIVE", false);
    editor          = addToggle("EDITOR", true);
    editor->enabled = false;
    config          = addToggle("CONFIG", false);
    
    addSpacer();
    
    addSlider("SCALE", 0.0, 1.0, &Globals::instance()->scene->scale);
    
    autoSizeToFitWidgets();
    
    
}