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
    
    //! Setup scene 1
    void   setupScene1();
    
private:
    
     typedef   map < string, ofPtr< ImageVisual > >  ImageMap;
    
     bool          m_initialized;
     ImageMap      m_images;

};

