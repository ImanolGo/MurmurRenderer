/*
 *  BirdsSwarmVisual.h
 *  Murmur
 *
 *  Created by Imanol Gomez on 22/09/15.
 *
 */


#pragma once

#include "ofMain.h"
#include "BasicVisual.h"


//======================== class BirdsSwarmVisual ============================
//============================================================================
/** \class BirdsSwarmVisual BirdsSwarmVisual.h
 *	\brief Class managing the sonic boom particles
 *	\details It creates and destroyes the sonic boom visuals
 */


class BirdsSwarmVisual: public BasicVisual
 {
    
public:
    
    //! Constructor
    BirdsSwarmVisual();
    
    //! Destructor
    ~BirdsSwarmVisual();
     
     
public:
     
    float   m_speed;               ///< Speed of the birds
    float   m_size;                ///< Size of the swarm
    int     m_number;              ///< Number of the birds
    float   m_birdSize;            ///< Size of the swarm
    float   m_randomness;          ///< Size of the swarm

};





