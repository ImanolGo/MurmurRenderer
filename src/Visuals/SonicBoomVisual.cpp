/*
 *  SonicBoomVisual.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 31/07/15.
 *
 */

#include "SonicBoomVisual.h"

#include "AppManager.h"



SonicBoomParticle::SonicBoomParticle(const ofPoint& pos): BasicVisual(pos,0,0), m_lifeTime(5), m_live(true), m_time(0), m_initSize(0.0)
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
    m_initSize = 10 + ofNoise( ofGetElapsedTimef()/4)*10;
    m_lifeTime = 1 + ofNoise( ofGetElapsedTimef()/2)*7 ;
    m_size = 50 + ofNoise( ofGetElapsedTimef()/2)*550 ;
    m_color = ofColor::white;
}


void SonicBoomParticle::update()
{
    double dt = ofGetLastFrameTime();
    
    m_time += ofGetLastFrameTime();
    
    m_width = ofMap(m_time, 0, m_lifeTime, m_initSize, m_size);
    float brightness = ofMap(m_time, 0, m_lifeTime, 255, 0, true);
    m_color.setBrightness(brightness);
   // m_color.a = ofMap(m_time, 0, m_lifeTime, 255, 0, true);
    
    //m_color.a = 50;
    
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

void SonicBoomVisual::setup()
{
    this->setupWaterRipples();
}


void SonicBoomVisual::setupWaterRipples()
{
    //ofSetCircleResolution(100);
    m_windowsSettings = AppManager::getInstance().getSettingsManager().getWindowsSettings(1);
    
    ofImage waterBackground;
    waterBackground.allocate(m_windowsSettings.width, m_windowsSettings.height, OF_IMAGE_GRAYSCALE);
    m_water.loadBackground(waterBackground);
    m_water.setDensity(0.9);
    
}

void SonicBoomVisual::update()
{
    this->updateParticles();
    this->updateWaterRipples();
    
}


void SonicBoomVisual::updateParticles()
{
    auto hands = AppManager::getInstance().getHandsManager().getHands();
    
    for (auto hand : hands) {
        ofPoint pos = hand;
        pos.x *= m_windowsSettings.width;
        pos.y *= m_windowsSettings.height;
        this->addParticle(pos);
    }

    
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

void SonicBoomVisual::updateWaterRipples()
{
    auto hands = AppManager::getInstance().getHandsManager().getHands();
    
    //ofEnableAlphaBlending();
    m_water.begin();
    
    /*ofPushStyle();
    ofFill();
    ofSetLineWidth(16);
    ofColor color = ofColor::white;
    color.a =  ofMap(ofNoise( ofGetFrameNum() ) , 0.0, 1.0, 0, 255);
    ofSetColor(color);
    //ofSetColor(ofNoise( ofGetFrameNum() ) * 255 * 5, 255);
    //ofSetColor(ofColor::blue);
    float radius = ofMap(ofNoise( ofGetFrameNum() ) , 0.0, 1.0, 20, 60);
    for (auto hand : hands) {
        ofPoint pos = hand;
        pos.x *= m_windowsSettings.width;
        pos.y *= m_windowsSettings.height;
        ofCircle(pos, radius);
    }
    ofPopStyle();*/
    
    this->drawParticles();
    
    //ofCircle(ofGetMouseX(), ofGetMouseY(), radius);
    m_water.end();
    
    m_water.update();
    
    //ofDisableAlphaBlending();
    
}


void SonicBoomVisual::draw()
{
    this->drawWaterRipples();
    //this->drawParticles();
}

void SonicBoomVisual::drawWaterRipples()
{
    m_water[1].draw(0,0);
}

void SonicBoomVisual::drawParticles()
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