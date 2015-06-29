/*
 *  ContourManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 26/05/15.
 *
 */


#include "FluidVisual.h"
#include "ContourManager.h"


ContourManager::ContourManager(): m_isFrameNew(false)
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
    
    this->setupFbo();
}


void ContourManager::setupFbo()
{
    m_contourFbo.allocate(FluidVisual::FLUID_WIDTH, FluidVisual::FLUID_HEIGHT);
    //m_contourFbo.allocate(1920, 1080);
    m_contourFbo.begin(); ofClear(0); m_contourFbo.end();
    
    ofLogNotice() <<"ContourManager::setupFbo-> Set up FBO with width = " << m_contourFbo.getTextureReference().getWidth() << ", height = " << m_contourFbo.getTextureReference().getHeight();
    
}


void ContourManager::update()
{

    if(m_isFrameNew)
    {
        ofPushStyle();
        ofEnableBlendMode(OF_BLENDMODE_DISABLED);
        m_contourFbo.begin();
            ofClear(0);
            for (auto contour: m_contours){
                ofSetLineWidth(20);
                contour->draw();
           
        }
        m_contourFbo.end();
        ofPopStyle();
        
        m_isFrameNew = false;
    }
   
}

void ContourManager::draw()
{
    m_contourFbo.draw(0,0);
}

void ContourManager::resetContours()
{
    m_contours.clear();
}

void ContourManager::setContour(vector<float> contourPoints)
{
    //ofLogNotice() <<"ContourManager::setContour-> NEW FRAME!!!!!!!!";
    
    ofPtr<ofPolyline> contour = ofPtr<ofPolyline> (new ofPolyline());
    
    for (int i = 0; i < contourPoints.size(); i = i + 2) {
        float x = contourPoints[i]*FluidVisual::FLUID_WIDTH;
        float y = contourPoints[i+1]*FluidVisual::FLUID_HEIGHT;
        
        contour->addVertex(x,y);
    }
    
    contour->close(); // close the shape
    m_contours.push_back(contour);
    
    m_isFrameNew = true;
    
}


const ofFbo& ContourManager::getSource() const
{
    return m_contourFbo;
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
