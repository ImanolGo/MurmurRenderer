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
    m_fft.setNumFFTBins(16);
    m_fft.setVolumeRange(m_volumeRange);
    //m_fft.setNormalize(true);
   
}


void AudioManager::update()
{
    m_fft.update();
}

void AudioManager::draw()
{
    m_fft.drawBars();
}

