/*
 *  SonicBoomVisual.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 31/07/15.
 *
 */

#include "FluidVisual.h"
#include "SonicBoomVisual.h"



SonicBoomParticle::SonicBoomParticle(const ofPoint& pos): BasicVisual(pos,0,0), m_lifeTime(5), m_live(true), m_time(0)
{
    this->setup();
}


SonicBoomParticle::~SonicBoomParticle()
{
    //Intentionaly left empty
}


void SonicBoomParticle::setup()
{
    m_time = 0;
    m_lifeTime = 1 + ofNoise( ofGetElapsedTimef()/2)*7 ;
    m_size = 50 + ofNoise( ofGetElapsedTimef()/2)*550 ;
    m_color = ofColor::white;
}


void SonicBoomParticle::update()
{
    double dt = ofGetLastFrameTime();
    
    m_time += ofGetLastFrameTime();
    
    m_width = ofMap(m_time, 0, m_lifeTime, 4, m_size);
    m_color.a = ofMap(m_time, 0, m_lifeTime, 255, 0, true);
    
    if(m_time>=m_lifeTime){
        m_live = false;
    }
}

void SonicBoomParticle::draw()
{
    ofPushStyle();
    ofEnableAlphaBlending();
        ofSetColor(m_color);
        ofCircle(m_position, m_width);
    ofDisableAlphaBlending();
    ofPopStyle();
}



SonicBoomVisual::SonicBoomVisual()
{
    //Intentionaly left empty
}


SonicBoomVisual::~SonicBoomVisual()
{
    //Intentionaly left empty
}


void SonicBoomVisual::update()
{
    for(ParticlesVector::iterator it = m_particles.begin(); it != m_particles.end();)
    {
        (*it)->update();
        
        if(!(*it)->isAlive()){
            it = m_particles.erase(it);
        }
        else{
            ++it;
        }
    }
}

void SonicBoomVisual::draw()
{
    
    for (auto particle: m_particles) {
        particle->draw();
    }
}

void SonicBoomVisual::addParticle(const ofPoint &pos)
{
    auto particle = ofPtr<SonicBoomParticle> (new SonicBoomParticle(pos));
    m_particles.push_back(particle);
}

void SonicBoomVisual::clear()
{
    m_particles.clear();
}