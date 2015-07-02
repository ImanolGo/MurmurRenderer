/*
 *  FluidFloorScene.h
 *  Murmur
 *
 *  Created by Imanol Gomez on 02/07/15.
 *
 */

#pragma once

#include "FluidVisual.h"
#include "ofxScene.h"

class FluidFloorScene : public ofxScene {

public:
    
    //Contructor
    FluidFloorScene();
    
    //Destructor
    ~FluidFloorScene();

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
    
    void drawFluid();
    
    void updateFluid();
    
private:
    
    FluidVisual     m_fluid;
    bool            m_initialized;

};

