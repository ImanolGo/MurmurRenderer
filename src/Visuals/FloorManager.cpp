/*
 *  FloorManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 02/07/15.
 *
 */


#include "FluidVisual.h"
#include "FloorManager.h"


const int FloorManager::FLOOR_POS_CIRCLE_RADIUS = 20;

FloorManager::FloorManager()
{
    //Intentionaly left empty
}


FloorManager::~FloorManager()
{
    ofLogNotice() <<"FloorManager::Destructor" ;
}


void FloorManager::setup()
{
    Manager::setup();
    
    ofLogNotice() <<"FloorManager::initialized" ;
}


void FloorManager::draw()
{
    ofPushMatrix();
    ofPushStyle();
    
    ofSetColor(ofColor::white);
    
    ofNoFill();
    
        auto transformedPosition = m_floorPosition;
        transformedPosition.x *= ofGetWidth();
        transformedPosition.y *= ofGetHeight();
    
        ofCircle(transformedPosition, FLOOR_POS_CIRCLE_RADIUS);
        ofCircle(transformedPosition, FLOOR_POS_CIRCLE_RADIUS/10);
        //ofLogNotice() <<"FloorManager::draw << x:  " << transformedPosition << ", y: " << transformedPosition.y;

    ofPopStyle();
    ofPopMatrix();
}


void FloorManager::setPosition(const ofVec2f& position)
{
    m_floorPosition =  position - 0.5;
    m_floorPosition *= m_floorScale;
    m_floorPosition =m_floorPosition + 0.5 + m_floorOffset;
}


void FloorManager::setOffset(ofVec2f & offset)
{
    m_floorOffset = offset;
}

void FloorManager::setScale(ofVec2f & scale)
{
    m_floorScale = scale;
}

