/*
 *  AudioManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 30/07/15.
 *
 */


#include "FluidVisual.h"
#include "AudioManager.h"


AudioManager::AudioManager(): m_volume(0.5)
{
    //Intentionaly left empty
}


AudioManager::~AudioManager()
{
    ofLogNotice() <<"AudioManager::Destructor" ;
}


void AudioManager::setup()
{
    Manager::setup();
    
    ofLogNotice() <<"AudioManager::initialized" ;
    
    this->setupFFT();
}


void AudioManager::setupFFT()
{
    m_fft.setMirrorData(false);
    m_fft.setup();
    m_fft.setPeakDecay(0.915);
    m_fft.setMaxDecay(0.995);
    m_fft.setThreshold(1.0);
    m_fft.setVolume(m_volume);
}


void AudioManager::update()
{
    if (!m_audioOn) {
        return;
    }
    
    m_fft.update();
    m_audioMax = ofMap(m_fft.getAveragePeak(), 0.0, 0.1, 0.0, 1.0, true);
    
    //ofLogNotice() <<"AudioManager::update: " << m_fft.getUnScaledLoudestValue();
    //ofLogNotice() <<"AudioManager::update2: " << m_fft.getLoudBand();
}

void AudioManager::draw()
{
    if (!m_audioOn) {
        return;
    }

    m_fft.draw(340,600);
}

void AudioManager::onChangeVolumeRange(float& value)
{
    m_volume = value;
    m_fft.setVolume(m_volume);
}

void AudioManager::setAudioMax(float audioMax)
{
    if(m_audioOn){
        return;
    }
    
    m_audioMax = audioMax;
}

void AudioManager::onChangeAudioOn(bool& value)
{
    m_audioOn = value;
    
}


float AudioManager::getAudioMax()
{
    return m_audioMax;
}

