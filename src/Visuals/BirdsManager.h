/*
 *  BirdsManager.h
 *  Murmur
 *
 *  Created by Imanol Gomez on 05/08/15.
 *
 */


#pragma once

#include "ofMain.h"
#include "Manager.h"

#include "SyphonVisual.h"

//========================== class BirdsManager ==============================
//============================================================================
/** \class BirdsManager BirdsManager.h
 *	\brief Class managing the bird swarm created in unity
 *	\details It communicates the values to Unity through OSC and it gets the render window using Syphon
 */


class BirdsManager: public Manager
{
    
public:
    
    //! Constructor
    BirdsManager();
    
    //! Destructor
    ~BirdsManager();
    
    //! Setup the Birds Manager
    void setup();
    
    //! Update the Birds Manager
    void update();
    
    //! Draw the Birds Manager
    void draw();
    
    void onChangePosition(ofVec3f& target);
    
    void onChangeSize(float& value);
    
    void onChangeSpeed(float& value);
    
    void onChangeSwarmSize(float& value);
    
    void onChangeSwarmNumber(int& value);
    
private:
    
    void setupSyphon();
    
    void setupShader();
    
    
private:
    
    
    int        m_birdsSwarmNumber;
    ofVec3f    m_target;
    float      m_birdsSize;
    float      m_birdsSpeed;
    float      m_birdsSwarmSize;
    
    SyphonVisual    m_syphonVisual;
    ofShader        m_shader;
};


