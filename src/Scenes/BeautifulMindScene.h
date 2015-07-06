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
    static const int NUMBER_SCENES_IN_SCENE_02;
    static const int NUMBER_SCENES_IN_SCENE_04;
    static const float FADE_TIME;
    
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
    
    //! Setup all the scenes
    void   setupScenes();
    
    //! Setup Scene 1
    void   setupScene1();
    
    //! Update Scene 1
    void   updateScene1();
    
    //! Setup Scene 2
    void   setupScene2();
    
    //! Update Scene 2
    void   updateScene2();
    
    //! Setup Scene 3
    void   setupScene3();
    
    //! Update Scene 3
    void   updateScene3();
    
    //! Setup Scene 4
    void   setupScene4();
    
    //! Update Scene 4
    void   updateScene4();
    
    //! Draw the complete scene
    void   drawScene();
    
    //! Calculate the drawing area
    ofRectangle  getDrawingArea();
    
    void setScene(int scene);
    
    void startCurrentScene();
    
    void nextScene();
    
    void fadeOutVisuals();
    
    void resetTimeValues();
    
    void nextSecondaryScene();
    
    void resetSecondaryScene();
    
private:
    
     typedef   map < string, ofPtr< ImageVisual > >  ImageMap;
    
     bool          m_initialized;
     ImageMap      m_images;
     int           m_sceneNumber;
     float         m_elapsedTime;
     float         m_duration;
     float         m_elapsedTimeSecondary;
     int           m_sceneNumberSecondary;
     float         m_durationSecondary;
     ofFbo         m_fbo;

};

