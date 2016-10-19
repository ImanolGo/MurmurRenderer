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
    m_initSize = 0 + ofNoise( ofGetElapsedTimef()/4)*20;
    //m_lifeTime = 1 + ofNoise( ofGetElapsedTimef()/2)*2;
    m_lifeTime = 1 + ofRandom(2);
    
    m_size = 450 + ofNoise( ofGetElapsedTimef()/2)*350 ;
    m_color = ofColor::white;
    
    m_image.setResource("sonic_ring");
    m_image.setCentred(true);
}


void SonicBoomParticle::update()
{
    double dt = ofGetLastFrameTime();
    
    m_time += ofGetLastFrameTime();
    
    m_width = ofMap(m_time, 0, m_lifeTime, m_initSize, m_size);
    float brightness = ofMap(m_time, 0, m_lifeTime, 200, 0, true);
    m_color.setBrightness(brightness);
    //m_color.a = brightness;
    
    //m_color.a = 50;
    
    m_image.setColor(m_color);
    m_image.setWidth(m_width,true);
    m_image.setPosition(m_position);
    if(m_time>=m_lifeTime){
        m_live = false;
    }
    
}

void SonicBoomParticle::draw()
{
    //ofPushStyle();
    //ofEnableAlphaBlending();
    //ofSetColor(m_color);
    //ofCircle(m_position, m_width);
    m_image.draw();
    //ofDisableAlphaBlending();
    //ofPopStyle();
}



SonicBoomVisual::SonicBoomVisual(): m_elapsedTime(10000), m_newParticleTime(0.2), m_frequency(0.6), m_amplitude(1.0), m_speed(0.5)
{
    
}


SonicBoomVisual::~SonicBoomVisual()
{
    //Intentionaly left empty
}


void SonicBoomVisual::setup(int width, int height)
{
    
    this->setupFbos(width, height);
    this->setupShaders();
}



void SonicBoomVisual::setupFbos(int width, int height)
{
    m_fbo.allocate(width, height);
    m_fbo.begin(); ofClear(0); m_fbo.end();
}

void SonicBoomVisual::setupShaders()
{
    
    if(ofIsGLProgrammableRenderer()){
        m_shader.load("shaders/shadersGL3/LiquifyShader");
    }
    else{
        m_shader.load("shaders/shadersGL2/LiquifyShader");
        
    }
    
    m_frequency = 0.6;
    m_amplitude = 1.0;
    m_speed = 0.5;
}

void SonicBoomVisual::update()
{
    this->updateParticles();
}


void SonicBoomVisual::updateParticles()
{
    auto hands = AppManager::getInstance().getHandsManager().getHands();
    
    for (auto hand : hands) {
        ofPoint pos = hand;
        pos.x *= m_fbo.getWidth();
        pos.y *= m_fbo.getHeight();
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


void SonicBoomVisual::draw()
{
    this->drawParticles();
    //this->drawWaterRipples();
}


void SonicBoomVisual::drawParticles()
{
    
    //ofPushStyle();
    
    m_fbo.begin();
    
    //ofEnableAlphaBlending();
    ofClear(0,0,0);
    //ofRect(0,0,m_fbo.getWidth(),m_fbo.getHeight());
    //ofSetColor(255,255,255);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    for (auto particle: m_particles) {
        particle->draw();
    }
    
    //ofDisableAlphaBlending();
    // ofDisableBlendMode();
    m_fbo.end();
    
    // ofPopStyle();
    
    //Drawing to screen through the shader
    m_shader.begin();		//Enable the shader
    
    m_shader.setUniform1f("time", ofGetElapsedTimef());
   // m_shader.setUniformTexture("tex", m_fbo.getTextureReference(), 0);
    m_shader.setUniform1f("frequency", m_frequency);
    m_shader.setUniform1f("amplitude", m_amplitude);
    m_shader.setUniform1f("speed", m_speed);
    

   // float time = ofGetElapsedTimef();
    //m_shader.setUniform1f( "time", time );	//Passing float parameter "time" to shader
    //m_shader.setUniform1f( "amplitude", 0.21 );	//Passing float parameter "amplitude" to shader
    
    //Draw fbo image
    ofSetColor( 255, 255, 255 );
    m_fbo.draw( 0, 0 );
    
    m_shader.end();		//Disable the shader
    
}


void SonicBoomVisual::addParticle(const ofPoint &pos)
{
    m_elapsedTime += ofGetLastFrameTime();
    
    if (m_elapsedTime >= m_newParticleTime) {
        m_elapsedTime = 0.0;
        auto particle = ofPtr<SonicBoomParticle> (new SonicBoomParticle(pos));
        m_particles.push_back(particle);
    }
   
}

void SonicBoomVisual::clear()
{
    m_particles.clear();
}