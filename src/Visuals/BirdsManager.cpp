/*
 *  BirdsManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 05/08/15.
 *
 */


#include "FluidVisual.h"
#include "BirdsManager.h"


BirdsManager::BirdsManager()
{
    //Intentionaly left empty
}


BirdsManager::~BirdsManager()
{
    ofLogNotice() <<"BirdsManager::Destructor" ;
}


void BirdsManager::setup()
{

    Manager::setup();
    
    ofLogNotice() <<"BirdsManager::initialized" ;
    

    
    m_boidsNumber = 1000;
    
    for (int i = 0; i < m_boidsNumber; i++)
    {
        SteeredVehicle boid(ofRandom(100)-50, ofRandom(100)-50, ofRandom(100)-50);
        boid.maxForce = 2.5f;
        boid.inSightDist = 600.0f;
        m_boids.push_back(boid);
    }
    
    m_camera.setDistance(500);

    
    // rather than always drawing things on top of each other
    //ofEnableDepthTest();
    
    // ofBox uses texture coordinates from 0-1, so you can load whatever
    // sized images you want and still use them to texture your box
    // but we have to explicitly normalize our tex coords here
    //ofEnableNormalizedTexCoords();

    
    ofSetSmoothLighting(true);
    pointLight.setDiffuseColor( ofFloatColor(.95, .95, .95) );
    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    
    pointLight2.setDiffuseColor( ofFloatColor( 238.f/255.f, 57.f/255.f, 135.f/255.f ));
    pointLight2.setSpecularColor(ofFloatColor(.8f, .8f, .9f));
    
    pointLight3.setDiffuseColor( ofFloatColor(19.f/255.f,94.f/255.f,77.f/255.f) );
    pointLight3.setSpecularColor( ofFloatColor(18.f/255.f,150.f/255.f,135.f/255.f) );
    
    // shininess is a value between 0 - 128, 128 being the most shiny //
    material.setShininess( 120 );
    // the light highlight of the material //
    material.setSpecularColor(ofColor(255, 255, 255, 255));
    
    ofSetSphereResolution(12);

    
}



void BirdsManager::update()
{
    ofPoint p;
    //p.x = ofMap(ofGetMouseX(), 0, ofGetWidth(), -500, 500);
    //p.y = ofMap(ofGetMouseY(), 0, ofGetHeight(), 500, -500);
    //p.z = ofRandom(-100, 100);
    
    p.x = m_target.x * ofGetWidth();
    p.y = m_target.y * ofGetHeight();
    p.z = m_target.z * ofGetWidth();
    
    for (int i = 0; i < m_boids.size(); i++)
    {
        
        p.z = ofGetHeight()*0.5*ofSignedNoise(ofGetElapsedTimef() + i*1000);
        
        m_boids[i].seek(p);
        m_boids[i].flock(m_boids);
        m_boids[i].update();
        //boids[i].wrap(300, 300, 300);
    }
}

void BirdsManager::draw()
{
    ofEnableDepthTest();
    
    ofEnableLighting();
    pointLight.enable();
    pointLight2.enable();
    pointLight3.enable();
    
    material.begin();

    
    m_camera.begin();
    
    for (int i = 0; i < m_boids.size(); i++)
    {
        glPushMatrix();
        //glTranslatef(m_boids[i].position.x, m_boids[i].position.y, m_boids[i].position.z);
        
        ofDrawSphere(m_boids[i].position.x, m_boids[i].position.y, m_boids[i].position.z, m_birdsSize);

        glPopMatrix();
    }
    
    m_camera.end();
    
    material.end();
    ofDisableLighting();
    
    ofDisableDepthTest();
}



void  BirdsManager::onChangeMaxForce(float& value)
{
    for (int i = 0; i < m_boids.size(); i++){
        m_boids[i].maxForce = value;
    }
}

void  BirdsManager::onChangeWanderDistance(float& value)
{
    for (int i = 0; i < m_boids.size(); i++){
        m_boids[i].wanderDistance = value;
    }
}

void  BirdsManager::onChangeWanderRadius(float& value)
{
    for (int i = 0; i < m_boids.size(); i++){
        m_boids[i].wanderRadius = value;
    }
}

void  BirdsManager::onChangeWanderRange(float& value)
{
    for (int i = 0; i < m_boids.size(); i++){
        m_boids[i].wanderRange = value;
    }
}

void  BirdsManager::onChangeInSightDist(float& value)
{
    for (int i = 0; i < m_boids.size(); i++){
        m_boids[i].inSightDist = value;
    }
}


void  BirdsManager::onChangeTooCloseDist(float& value)
{
    for (int i = 0; i < m_boids.size(); i++){
        m_boids[i].tooCloseDist = value;
    }
}




