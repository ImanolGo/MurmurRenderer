/*
 *  AudioManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 30/07/15.
 *
 */


#include "FluidVisual.h"
#include "AudioManager.h"


AudioManager::AudioManager(): m_volumeRange(100)
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
    m_fft.setup();
    m_fft.setNumFFTBins(8);
    m_fft.setVolumeRange(m_volumeRange);
    //m_fft.setNormalize(true);
   
}


void AudioManager::update()
{
    if (!m_audioOn) {
        return;
    }
    
    m_fft.update();
    m_audioMax = ofMap(m_fft.getUnScaledLoudestValue(), 0.0, m_volumeRange, 0.0, 1.0, true);
    
    //ofLogNotice() <<"AudioManager::update: " << m_fft.getUnScaledLoudestValue();
    //ofLogNotice() <<"AudioManager::update2: " << m_fft.getLoudBand();
}

void AudioManager::draw()
{
    m_fft.drawBars();
}

void AudioManager::onChangeVolumeRange(float& value)
{
    m_volumeRange = ofMap(value, 0, 1, 2000, 1);
    m_fft.setVolumeRange(m_volumeRange);

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

