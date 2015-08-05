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

#include "ofxBoids.h"

//========================== class BirdsManager ==============================
//============================================================================
/** \class BirdsManager BirdsManager.h
 *	\brief Class managing the birds
 *	\details It calculates the birds position, size and speed
 */


class BirdsManager: public Manager
{
    
public:
    
    //! Constructor
    BirdsManager();
    
    //! Destructor
    ~BirdsManager();
    
    //! Setup the Audio Manager
    void setup();
    
    //! Update the Audio Manager
    void update();
    
    //! Draw the Audio Manager
    void draw();
    
    void onChangePosition(ofVec3f& target){m_target = target;}
    
    void onChangeSize(float& value){m_birdsSize = value;}
    
    void onChangeSwarmSize(float& value){m_birdsSwarmSize = value;}
    
    
private:
    
    int                         m_boidsNumber;
    vector<SteeredVehicle>      m_boids;
    
    ofVec3f                 m_target;
    float                   m_birdsSize;
    float                   m_birdsSwarmSize;
    
};

