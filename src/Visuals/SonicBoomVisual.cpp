/*
 *  SonicBoomVisual.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 31/07/15.
 *
 */

#include "FluidVisual.h"
#include "SonicBoomVisual.h"



SonicBoomParticle::SonicBoomParticle(const ofPoint& pos): BasicVisual(pos,0,0), m_lifeTime(10), m_live(true), m_time(0)
{
    //Intentionaly left empty
}


SonicBoomParticle::~SonicBoomParticle()
{
    //Intentionaly left empty
}


void SonicBoomParticle::setup()
{
    m_time = 0;
    m_lifeTime = 10;
    m_color = ofColor::white;
}


void SonicBoomParticle::update()
{
    double dt = ofGetLastFrameTime();
    
    m_time += ofGetLastFrameTime();
    
    m_width = ofMap(m_time, 0, m_lifeTime, 0, 200);
    m_color.a = ofMap(m_time, 0, m_lifeTime, 255, 0);
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
    for(ParticlesVector::iterator it = m_particle.begin(); it != m_particle.end();)
    {
        if(!(*it)->isAlive()){
            it = m_particle.erase(it);
        }
        else{
            ++it;
        }
    }
}

void SonicBoomVisual::draw()
{
    for (auto particle: m_particle) {
        particle->draw();
    }
}

void SonicBoomVisual::addParticle(const ofPoint &pos)
{
    auto particle = ofPtr<SonicBoomParticle> (new SonicBoomParticle(pos));
    m_particle.push_back(particle);
}

void SonicBoomVisual::clear()
{
    m_particle.clear();
}