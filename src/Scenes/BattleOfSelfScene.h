/*
 *  BattleOfSelfScene.h
 *  Murmur
 *
 *  Created by Imanol Gomez on 30/06/15.
 *
 */

#pragma once


#include "FluidVisual.h"
#include "ofxScene.h"
#include "ofxPostProcessing.h"

class BattleOfSelfScene : public ofxScene {

public:
    
    //Contructor
    BattleOfSelfScene();
    
    //Destructor
    ~BattleOfSelfScene();

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
    
    void setupShaders();
    
    void setupPostProcessing();
    
    void drawFluid();
    
    void updateFluid();
    
    void drawVisuals();
    
private:
    
    bool            m_initialized;
    
    ofShader                m_shader;
    FluidVisual             m_fluid;
    
     ofxPostProcessing      m_postProcessing;

};

