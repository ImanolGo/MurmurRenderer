/*
 *  KathakScene.h
 *  Murmur
 *
 *  Created by Imanol Gomez on 30/07/15.
 *
 */

#pragma once

#include "FluidVisual.h"
#include "ofxScene.h"
#include "ofxWater.h"
#include "ImageVisual.h"

class KathakScene : public ofxScene {

public:
    
    //Contructor
    KathakScene();
    
    //Destructor
    ~KathakScene();

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
    
    void setupWaterDrops();
    
    void setupFbos();
    
    void setupShaders();
    
    void drawFluid();
    
    void drawWaterDrops();
    
    void updateFluid();
    
    void updateWaterDrops();
    
private:
    
    FluidVisual     m_fluid;
    bool            m_initialized;
    ofShader        m_maskShader;
    ofFbo           m_fboMask;

    ofxWater        m_water;
    
    ofRectangle     m_drawArea;

};

