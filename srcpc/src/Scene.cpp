//
//  Scene.cpp
//  Sucre
//
//  Created by Martial on 16/10/13.
//
//

#include "Scene.h"
#include "ofxSosoRenderer.h"
#include "Globals.h"
#include "testApp.h"
#include "ofxModifierKeys.h"

Scene::Scene () {
    
    scale           = 1.0;
    bActive         = true;
    bInteractive    = false;
    bDrawBack       = false;
    bDebugObjects   = false;
    bStatic         = false;
    bSelected       = false;
	bStrobDmx		= false;
    
    rows            = 6;
    cols            = 7;
    
    colorSchemeId   = 0;

    
}

void Scene::setup(bool useFbo) {
    
    this->bUseFbo    = useFbo;

    
    container = new SceneObject();
    
    setDefaultMatrix();
    setBasicLightGrid();
    
    if(bInteractive)
        ofAddListener(Globals::instance()->gui->selector.selectorLock, this, &Scene::onGuiSelectorEvent);
    
    
    
    if(bUseFbo) {
        ofFbo::Settings s;

        s.width     = 300;
        s.height    = 300;
        
        //s.textureTarget = GL_TEXTURE_2D;
        s.internalformat =GL_RGBA;
        //s.useStencil= true;
        //s.useDepth = true;
        //s.depthStencilInternalFormat = GL_DEPTH_COMPONENT24;
      //  s.numSamples = 4;
        //s.numColorbuffers = 8;
        //s.minFilter = GL_NEAREST_MIPMAP_LINEAR;
        //s.maxFilter = GL_NEAREST_MIPMAP_LINEAR;
        
        
        //s.depthStencilAsTexture = true;
        //s.wrapModeVertical = GL_MIRRORED_REPEAT;
    
        // and assigning this values to the fbo like this:
        fbo.allocate(s);
        ofAddListener(ofEvents().windowResized, this, &Scene::onResizeEvent);
    }
    
    
    // fbo for output
    ofFbo::Settings sOutput;
    
    sOutput.width           = 8;
    sOutput.height          = 8;
    
    sOutput.internalformat  = GL_RGBA;
    outputFbo.allocate(sOutput);
    
    
}

void Scene::onResizeEvent(ofResizeEventArgs &e) {
    //fbo.allocate(-bBox.getWidth(), -bBox.getHeight());

    fbo.allocate(ofGetWidth(), ofGetHeight());
}

void Scene::update() {
    
    if(bUseFbo) {
        container->setPos(0.0, 0.0, 0.0);
    }
    
    container->xyzRot.y = tween.update();
    container->setScale(scale,scale,scale);
    
    
    
}

void Scene::draw() {
    
   
    
    
    ofEnableAlphaBlending();
    
    //fbo.begin(true);
    
    if(bUseFbo) {
        
        fbo.begin(false);
        ofClear(255, 255, 255, 0);
    }

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    
    
    
    glLoadIdentity();
    
    
    glPushMatrix();
    
    
    ofEnableAlphaBlending();
    
    
   
    
    
    
    
    if(bSelected) {
        ofFill();
        ofSetColor(0);
        
    } else {
        ofFill();
        ofSetColor(25);
    }
    
    
    ofRect(bBox);
    
    ofSetColor(255, 255, 255);
    container->draw(defaultMatrix);
    
    
    
    glPopMatrix();
    
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    
    if(bUseFbo) {
        fbo.end();
    }
   
    

    
}

void Scene::drawOutput() {
    
    outputFbo.begin();
    ofClear(0, 0, 0, 0);
     //glBegin(GL_POINTS);
    int id = 0;
    for (int i=0; i<rows; i++ ) {
        
        for (int j=0; j<cols; j++ ) {
            
            ofPtr<LightObject> light  = lightObjects[id];
            

            ofSetColor(light->finalColor);
			ofRect(i,j,1,1);
            //glBegin(GL_POINTS);
            //glVertex2f(i, j);
           // glEnd();
            id ++;

        }
        
    }
   //  glEnd();
    outputFbo.end();
    ofSetColor(255, 255,255,255);
    //outputFbo.draw(0.0, 0.0);

    
}

void Scene::animate() {
    
    tween.setParameters(1,easingquint,ofxTween::easeInOut, container->xyzRot.y, container->xyzRot.y + 360, 900, 0);
    
}

/* ------------------------ Setup */

void Scene::setBasicLightGrid() {
    
    
    float x, y;
    float radius    = 10.0;
    float spacing   = 60.0;
    
    
    x = - ( (rows / 2) * spacing ) + spacing / 2;
    y = - ( (cols / 2) * spacing ) + spacing / 2;;
    
    
    bBox.set(-x+spacing, -y+spacing, x*2 - spacing*2, y*2 - spacing*2);
    
    int id = 0;
    for (int i=0; i<rows; i++ ) {
        
        for (int j=0; j<cols; j++ ) {
        
        ofPtr<LightObject> light = ofPtr<LightObject> (new LightObject());
            
        light->id = id ++;
        
        light->bStatic = bStatic;
        light->setRadius(radius);
        if(bInteractive) light->enableMouse();
        light->setPos(x + (i * spacing), y + (j*spacing), 0.0);
            
        
            if(bDebugObjects) {
            light->bDebug = true;
            }
            
        container->addChild(light);
            
        lightObjects.push_back(light);
        
            
        }
        
    }
    
}

ofRectangle Scene::getRect() {
    
	ofRectangle rect;
	return rect;
    
}

void Scene::addObject(SceneObject *obj) {
    
    objects.push_back(obj);
    
}

void Scene::setSelecteds(vector<int> selecteds) {
    
    deselectLightObjects(NULL);
    
    for ( int i=0; i<selecteds.size(); i++) {
        
        int id = selecteds[i];
        
        for (int i=0; i<container->childs.size(); i++) {
            ofPtr<LightObject> t =  dynamic_pointer_cast<LightObject>(container->childs[i]);
            if(t && t->id == id) {
                t->bSelected = true;
                
            }
        }
        
    }
    
}

/* ---------------------- modes  */

void Scene::setMode(int mode) {
    
    animate();
    this->mode = mode;
    
    deHighlightLightObjects(NULL);
    deselectLightObjects(NULL);
    
    if(!bInteractive) {
        return;
    }
    
    if (mode == MODE_LIVE ) {
        
        enableLightEvents(true);
        
    }
    
    if (mode == MODE_EDITOR ) {
        
        enableLightEvents(true);
        
    }
    
    if (mode == MODE_CONFIG ) {
        
        enableLightEvents(true);
        
    }
    
   
        
    
}


/* ---------------------- Events  */

void Scene::enableLightEvents (bool bEnabled) {
    
    //deselectLightObjects(NULL);
    
    for (int i=0; i<container->childs.size(); i++) {
        ofPtr<LightObject> t =  dynamic_pointer_cast<LightObject>(container->childs[i]);
        if(t) {
            if (bEnabled)
                ofAddListener(t->mousePressed, this, &Scene::onObjectClickEvent);
            else
                ofRemoveListener(t->mousePressed, this, &Scene::onObjectClickEvent);

        }
    }
    
}

void Scene::deselectLightObjects (SceneObject *  exception) {
    

    
    for (int i=0; i<container->childs.size(); i++) {
        ofPtr<LightObject> t =  dynamic_pointer_cast<LightObject>(container->childs[i]);
        if(t && t.get() != exception) {
            t->bSelected = false;
            
             SceneObject * obj = dynamic_cast<SceneObject*>(t.get());
            
            if (ofContains(selecteds, obj)) {
                int index = ofFind(selecteds, obj);
                selecteds.erase(selecteds.begin() + index);
                
            }

        }
    }
    
}

void Scene::deHighlightLightObjects (SceneObject *  exception ) {
    
    for (int i=0; i<container->childs.size(); i++) {
        ofPtr<LightObject> t =  dynamic_pointer_cast<LightObject>(container->childs[i]);
        if(t && t.get() != exception) {
            t->bHightlighted = false;
            
            
        }
    }

    
    
}

void Scene::setStrobDmx(bool bStrobDmx) {

	 for (int i=0; i<container->childs.size(); i++) {
        ofPtr<LightObject> t =  dynamic_pointer_cast<LightObject>(container->childs[i]);
		t->strobDmx = bStrobDmx;
    }

}


void Scene::onObjectClickEvent(SceneObjectEvent & e) {
  
    
    InteractiveSceneObject * obj = dynamic_cast<InteractiveSceneObject*>(e.object);
    
    
    
    
    if ( mode == MODE_EDITOR) {
         obj->bSelected = !obj->bSelected;
    
        if(obj->bSelected) {
        
            if (!ofContains(selecteds, e.object))
                selecteds.push_back(e.object);
        
        } else {
        
            if (ofContains(selecteds, e.object)) {
                int index = ofFind(selecteds, e.object);
                selecteds.erase(selecteds.begin() + index);
            
            }
        
        }
         
    }
    
    if ( mode == MODE_CONFIG || mode == MODE_LIVE) {
        
        if( mode == MODE_CONFIG)
            deHighlightLightObjects(obj);
        
        obj->bHightlighted = !obj->bHightlighted;
       
        vector<SceneObject* > highlighteds = getHighLighteds();
        Globals::instance()->gui->inspectorGui->setMulti(highlighteds);
         
        
    }
    
    if(mode == MODE_EDITOR)
        Globals::get()->animData->saveCurrentFrame(Globals::get()->animatorManager->getAnimator(0)->currentFrame);
   
	
	
		

}

void Scene::onGuiSelectorEvent(SelectorEvent & e) {
    
    
    /*
    if(!ofGetModifierPressed(OF_KEY_SHIFT)) {
        //selecteds.clear();
        //deselectLightObjects(NULL);
        
    }
     
     */


	int count = 0;
    for (int i=0; i<container->childs.size(); i++) {
        
        ofPtr<LightObject> t =  dynamic_pointer_cast<LightObject>(container->childs[i]);
        if(t)  {
            
            if ( mode == MODE_EDITOR) {
            
                if (e.selection.inside (t->screenCoords)) t->bSelected = !ofGetModifierPressed(OF_KEY_SHIFT);
                if (t->bSelected && !ofContains(selecteds, container->childs[i].get())) selecteds.push_back(t.get());
            
            
                if (!t->bSelected && ofContains(selecteds, container->childs[i].get())) {
                
                // delete
                    int index = ofFind(selecteds, container->childs[i].get());
                    selecteds.erase(selecteds.begin() + index);
                
                }
                
            }
            
            if ( mode == MODE_LIVE ) {
				//t->bHightlighted = false;
					if (e.selection.inside (t->screenCoords)) {
						t->bHightlighted = !ofGetModifierPressed(OF_KEY_SHIFT);
							count ++;
					}
				
            }
            
            
        }

    }

	if(count == 0) {

		for (int i=0; i<container->childs.size(); i++) {
        
        ofPtr<LightObject> t =  dynamic_pointer_cast<LightObject>(container->childs[i]);
			if(t)  {
				t->bHightlighted = false;
			}

			}
		
	
	}
    
    if ( mode == MODE_CONFIG || mode == MODE_LIVE) {

        Globals::get()->gui->inspectorGui->setMulti(getHighLighteds());
        
    }
    
    // save animation
    if(mode == MODE_EDITOR)
        Globals::get()->animData->saveCurrentFrame(Globals::get()->animatorManager->getAnimator(0)->currentFrame);
    
    
}

vector<ofPtr<LightObject> > Scene::getLightObjects() {
    
    
      
    return lightObjects;
    
}

vector<SceneObject* > Scene::getSelecteds() {
    
    vector<SceneObject* > result;
    for (int i=0; i<container->childs.size(); i++) {
        
        ofPtr<LightObject> t =  dynamic_pointer_cast<LightObject>(container->childs[i]);
        if(t && t->bSelected) {
            result.push_back(t.get());
        }
        
    }
    
    return result;

    
}

vector<SceneObject* > Scene::getHighLighteds() {
    
    vector<SceneObject* > result;
    for (int i=0; i<container->childs.size(); i++) {
        
        ofPtr<LightObject> t =  dynamic_pointer_cast<LightObject>(container->childs[i]);
        if(t && t->bHightlighted) {
            result.push_back(t.get());
        }
        
    }
    
    return result;
    
    
}



/* ---------------------- Utils **/


void Scene::setDefaultMatrix() {
    
    defaultMatrix = (float *)malloc(sizeof(float) * 16);
    defaultMatrix[0] = 1.0;
    defaultMatrix[1] = 0;
    defaultMatrix[2] = 0;
    defaultMatrix[3] = 0;
    
    defaultMatrix[4] = 0;
    defaultMatrix[5] = 1.0;
    defaultMatrix[6] = 0;
    defaultMatrix[7] = 0;
    
    defaultMatrix[8] = 0;
    defaultMatrix[9] = 0;
    defaultMatrix[10] = 1.0;
    defaultMatrix[11] = 0;
    
    defaultMatrix[12] = 0;
    defaultMatrix[13] = 0;
    defaultMatrix[14] = 0;
    defaultMatrix[15] = 1.0;

    
}


void Scene::updateData() {
    
    Globals::instance()->data->updateLights(getLightObjects());
    
    
}

void Scene::setStatic(bool bStatic) {
    
    this->bStatic = bStatic;
    for (int i=0; i<lightObjects.size(); i++ ) {
               lightObjects[i]->bStatic = bStatic;

    }
}


