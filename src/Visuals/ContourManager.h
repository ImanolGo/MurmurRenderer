/*
 *  ContourManager.h
 *  Murmur
 *
 *  Created by Imanol Gomez on 26/05/15.
 *
 */


#pragma once

#include "ofMain.h"
#include "Manager.h"

//========================== class ContourManager ==============================
//============================================================================
/** \class ContourManager ContourManager.h
 *	\brief Class managing the contours from the cameras
 *	\details It reads the contours and puts them into a texture
 */


class ContourManager: public Manager
 {
    
public:
    
    //! Constructor
    ContourManager();
    
    //! Destructor
    ~ContourManager();
    
    //! Setup the Contour Manager
    void setup();
    
    //! Update the Contour Manager
    void update();
    
    //! Draw the Contour Manager
    void draw();
     
    void resetContours();
     
    void setContour(vector<float> contourPoints);
    
    void setOffsetX(float & dx);
    void setOffsetY(float & dy);
    void setScaleX(float & sx);
    void setScaleY(float & sy);
    
    
private:
     
    typedef vector< ofPtr<ofPolyline> > ContourVector;
    
    ofVec2f             m_contourOffset;
    ofVec2f             m_contourScale;
     
    ContourVector       m_contours;
     
    
};



