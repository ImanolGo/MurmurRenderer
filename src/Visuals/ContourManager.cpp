/*
 *  ContourManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 26/05/15.
 *
 */


#include "FluidVisual.h"
#include "ContourManager.h"


ContourManager::ContourManager(): m_isFrameNew(false), m_contourThickness(1.0)
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
    
    this->setupShader();
    this->setupFbo();
}


void ContourManager::setupShader()
{
    m_thickLineShader.load("shaders/shadersGL3/ThickLineShaderVert.glsl", "shaders/shadersGL3/ThickLineShaderFrag.glsl", "shaders/shadersGL3/ThickLineShaderGeom.glsl");
    
    m_contourThickness = 0.3;
    ofLogNotice() <<"ContourManager::setupShader";
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
        //ofEnableBlendMode(OF_BLENDMODE_DISABLED);
        m_contourFbo.begin();
        m_thickLineShader.begin();
        m_thickLineShader.setUniform1f("thickness", m_contourThickness);
            ofClear(0);
            for (auto contour: m_contours){
                ofSetLineWidth(10);
                contour->draw();
        }
        m_thickLineShader.end();
        m_contourFbo.end();
        ofPopStyle();
        
        m_isFrameNew = false;
    }
   
}

void ContourManager::draw()
{
    m_contourFbo.draw(0,0, ofGetWidth(), ofGetHeight());
}

void ContourManager::resetContours()
{
    m_contours.clear();
}

void ContourManager::setContour(vector<float> contourPoints)
{
    //ofLogNotice() <<"ContourManager::setContour-> NEW FRAME!!!!!!!!";
    
    ofPtr<ofPath> contour = ofPtr<ofPath> (new ofPath());
    
    for (int i = 0; i < contourPoints.size(); i = i + 2) {
        float x = contourPoints[i]*FluidVisual::FLUID_WIDTH;
        float y = contourPoints[i+1]*FluidVisual::FLUID_HEIGHT;
        
        contour->lineTo(x,y);
    }
   
    //contour->setMode(ofPath::POLYLINES);
    contour->setStrokeColor(ofColor::white);
    contour->setFillColor(ofColor::white);
    contour->setFilled(false);
    contour->setStrokeWidth(0.1);
    //contour->setPolyWindingMode((ofPolyWindingMode) 2);
    contour->close(); // close the shape
    m_contours.push_back(contour);
    
    m_isFrameNew = true;
    
}


const ofFbo& ContourManager::getSource() const
{
    return m_contourFbo;
}

void ContourManager::setOffset(ofVec2f & offset)
{
    m_contourOffset = offset;
}

void ContourManager::setScale(ofVec2f & scale)
{
    m_contourScale = scale;
}

void ContourManager::setContourThickness(float & value)
{
    m_contourThickness = ofClamp(value, 0.0, 10.0);
}
