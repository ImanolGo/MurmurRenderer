/*
 *  BeautifulMindManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 04/07/15.
 *
 */

#include "AppManager.h"
#include "BeautifulMindManager.h"

BeautifulMindManager::BeautifulMindManager(): m_handsOffset(ofVec2f(0,0)), m_handsScale(ofVec2f(1,1))
{
    //Intentionaly left empty
}


BeautifulMindManager::~BeautifulMindManager()
{
    ofLogNotice() <<"BeautifulMindManager::Destructor" ;
}


void BeautifulMindManager::setup()
{
    Manager::setup();
    
    ofLogNotice() <<"BeautifulMindManager::initialized" ;
    
    this->setupRectangleSpace();
    this->setupTiming();
    
}


void BeautifulMindManager::setupTiming()
{
    m_timings = AppManager::getInstance().getSettingsManager().getTimings();
}


float BeautifulMindManager::getTiming(int id) const
{
    if(m_timings.find(id) != m_timings.end() ){
        return m_timings.at(id);
    }
    
    return 0.0f;
}

void BeautifulMindManager::draw()
{
    ofPushMatrix();
    ofPushStyle();
   
    ofSetColor(ofColor::white);
    
        ofNoFill();
        ofRect(m_rectangleSpace.position.x*ofGetWidth(), m_rectangleSpace.position.y*ofGetHeight(), m_rectangleSpace.width*ofGetWidth(), m_rectangleSpace.height*ofGetHeight() );
    
    ofPopStyle();
    ofPopMatrix();
}


void BeautifulMindManager::setupRectangleSpace()
{
    m_rectangleSpace = ofRectangle(0.0,0.0,1.0,1.0);
}



void BeautifulMindManager::setOffset(ofVec2f & offset)
{
    m_handsOffset = offset;
    m_rectangleSpace.setFromCenter(m_handsOffset.x+0.5, m_handsOffset.y+0.5, m_handsScale.x, m_handsScale.y);
}

void BeautifulMindManager::setScale(ofVec2f & scale)
{
    m_handsScale = scale;
    m_rectangleSpace.setFromCenter(m_handsOffset.x+0.5, m_handsOffset.y+0.5, m_handsScale.x, m_handsScale.y);
}
