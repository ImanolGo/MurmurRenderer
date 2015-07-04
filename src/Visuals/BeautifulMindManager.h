/*
 *  BeautifulMindManager.h
 *  Murmur
 *
 *  Created by Imanol Gomez on 04/07/15.
 *
 */


#pragma once

#include "ofMain.h"
#include "Manager.h"

//========================== class BeautifulMindManager ==============================
//============================================================================
/** \class BeautifulMindManager BeautifulMindManager.h
 *	\brief Class managing the beautiful mind scene parameters
 *	\details It reads the parameters sets the FBO of the Beautiful Mind Scene
 */


class BeautifulMindManager: public Manager
 {

public:
    
    //! Constructor
    BeautifulMindManager();
    
    //! Destructor
    ~BeautifulMindManager();
    
    //! Setup the Hands Manager
    void setup();
    
    //! Draw the Hands Manager
    void draw();
     
    void setOffset(ofVec2f & offset);
     
    void setScale(ofVec2f & scale);
    
     
private:
     
     void setupRectangleSpace();
     
    
private:
     
    ofVec2f             m_handsOffset;
    ofVec2f             m_handsScale;
    ofRectangle         m_rectangleSpace;
     
};



