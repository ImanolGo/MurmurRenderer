/*
 *  BeautifulMindScene.h
 *  Murmur
 *
 *  Created by Imanol Gomez on 02/07/15.
 *
 */

#pragma once

#include "ImageVisual.h"
#include "ofxScene.h"



class BeautifulMindScene : public ofxScene {

    static const int NUMBER_SCENES;
    
public:

    //! Constructor
    BeautifulMindScene();
    
    //! Destructor
    ~BeautifulMindScene();

    //! Set up the scene
    void setup();

    //! Update the scene
    void update();

    //! Draw the scene
    void draw();
    
    //! Called when fading in
    void willFadeIn();

    //! Called when to start drawing
    void willDraw();

    //! Called fading out
    void willFadeOut();

    //! Called when exit
    void willExit();
    
private:
    
    //! Setup Fbo
    void   setupFbo();
    
    //! Setup Scene 1
    void   setupScene1();
    
    //! Update Scene 1
    void   updateScene1();
    
    //! Draw the complete scene
    void   drawScene();
    
    //! Calculate the drawing area
    ofRectangle  getDrawingArea();
    
private:
    
     typedef   map < string, ofPtr< ImageVisual > >  ImageMap;
    
     bool          m_initialized;
     ImageMap      m_images;
     unsigned int  m_sceneNumber;
    
     ofFbo         m_fbo;

};

