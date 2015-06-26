/*
 *  ContourManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 26/05/15.
 *
 */


#include "ContourManager.h"


ContourManager::ContourManager()
{
    //Intentionaly left empty
}


ContourManager::~ContourManager()
{
    ofLogNotice() <<"ContourManager::Destructor" ;
}


void ContourManager::setup()
{
    Manager::setup();
    
    ofLogNotice() <<"ContourManager::initialized" ;
}

void ContourManager::update()
{
    
}

void ContourManager::draw()
{
    
}

void ContourManager::resetContours()
{
    m_contours.clear();
}

void ContourManager::setContour(vector<float> contourPoints)
{
    int i = 0;
    ofPtr<ofPolyline> contour = ofPtr<ofPolyline> (new ofPolyline());
    //ofLogNotice() <<"ContourManager::contourPoint size = " << contourPoints.size();
    
    while (i<contourPoints.size()-1)
    {
        float x = contourPoints[i++];
        float y = contourPoints[i++];
        
        contour->addVertex(x,y);
    }
    
    contour->close(); // close the shape
    m_contours.push_back(contour);
    
}

void ContourManager::setOffsetX(float & dx)
{
    m_contourOffset.x = dx;
}

void ContourManager::setOffsetY(float & dy)
{
    m_contourOffset.y = dy;
}

void ContourManager::setScaleX(float & sx)
{
    m_contourScale.x = sx;
}

void ContourManager::setScaleY(float & sy)
{
    m_contourScale.y = sy;
}
