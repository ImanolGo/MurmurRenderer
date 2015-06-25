/*
 *  SceneManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 25/06/15.
 *
 */

#pragma once

#include "Manager.h"
#include "ofxSceneManager.h"

//========================== class SceneManager ==============================
//============================================================================
/** \class SceneManager SceneManager.h
 *	\brief Class managing the scenes of the application
 *	\details It creates and manages all the scenes 
 */

class SceneManager: public Manager
{
public:

    //! Constructor
    SceneManager();

    //! Destructor
    ~SceneManager();

    //! Set-up the scenes
    void setup();
    
    //! Update the scenes
    void update();
    
    //! Draw the scenes
    void draw();

private:


    //! Create the scenes
    void createScenes();

private:


    ofxSceneManager     m_sceneManagerFront;
    ofxSceneManager     m_sceneManagerTop;

};

//==========================================================================


