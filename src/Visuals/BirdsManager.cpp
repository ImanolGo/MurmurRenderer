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
    return;
    
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

    
    GLfloat color[] = { 1.0, 0.2, 0.2 };
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
    
}



void BirdsManager::update()
{
    ofPoint p;
    p.x = ofMap(ofGetMouseX(), 0, ofGetWidth(), -500, 500);
    p.y = ofMap(ofGetMouseY(), 0, ofGetHeight(), 500, -500);
    p.z = ofRandom(-100, 100);
    for (int i = 0; i < m_boids.size(); i++)
    {
        
        m_boids[i].seek(p);
        m_boids[i].flock(m_boids);
        m_boids[i].update();
        //boids[i].wrap(300, 300, 300);
    }
}

void BirdsManager::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    m_camera.begin();
    
    for (int i = 0; i < m_boids.size(); i++)
    {
        glPushMatrix();
        glTranslatef(m_boids[i].position.x, m_boids[i].position.y, m_boids[i].position.z);
        
        GLfloat color[] = { 0.8, 0.2, 0.2, 1.0 };
        
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
        ofFill();
        ofSetColor(255);
        ofDrawBox(2);

        glPopMatrix();
    }
    
    m_camera.end();
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




