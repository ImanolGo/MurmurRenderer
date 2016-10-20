/*
 *  FloorManager.h
 *  Murmur
 *
 *  Created by Imanol Gomez on 02/07/15.
 *
 */


#pragma once

#include "ofMain.h"
#include "Manager.h"

//========================== class FloorManager ==============================
//============================================================================
/** \class FloorManager FloorManager.h
 *	\brief Class managing the position of the dancer
 *	\details It reads the position from top camera and calibrates it
 */


class FloorManager: public Manager
 {
    
     static const int FLOOR_POS_CIRCLE_RADIUS;
     
public:
    
    //! Constructor
    FloorManager();
    
    //! Destructor
    ~FloorManager();
    
    //! Setup the Contour Manager
    void setup();
    
    //! Draw the Contour Manager
    void draw();
    
    //! Draw the Contour Manager
    void draw(const ofRectangle& area);
     
    const ofVec2f& getPosition() const {return m_floorPosition;}
     
    void setPosition(const ofVec2f& position);
    
    void setOffset(ofVec2f & offset);
    
    void setScale(ofVec2f & scale);
     
    void onMaskOn(bool& value);
     
    void onStretchMask(bool& value);
     
    void onSetKathakRadius(float& value) {m_kathakRadius = value;}
     
    void onSetKathakWidth(float& value) {m_floorWidth = value;}
     
    float getKathakRadius() const {return m_kathakRadius;}
     
    float getKathakWidth() const {return m_floorWidth;}
    
     
private:
     
    typedef vector< ofPtr<ofPath> > ContourVector;
    

    ofVec2f             m_floorPosition;
    ofVec2f             m_floorOffset;
    ofVec2f             m_floorScale;
    float               m_kathakRadius;
    float               m_floorWidth;
     
};



