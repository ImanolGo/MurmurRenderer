/*
 *  AudioManager.h
 *  Murmur
 *
 *  Created by Imanol Gomez on 30/07/15.
 *
 */


#pragma once

#include "ofMain.h"
#include "Manager.h"

#include "ofxProcessFFT.h"

//========================== class AudioManager ==============================
//============================================================================
/** \class AudioManager AudioManager.h
 *	\brief Class managing the audio input
 *	\details It reads from the input microphone and calculates the energy.
 */


class AudioManager: public Manager
{
    
public:
    
    //! Constructor
    AudioManager();
    
    //! Destructor
    ~AudioManager();
    
    //! Setup the Audio Manager
    void setup();
    
    //! Update the Audio Manager
    void update();
    
    //! Draw the Audio Manager
    void draw();
    
    float getAudioMax();
    
    void onChangeVolumeRange(float& value);
    
    void onChangeAudioOn(bool& value);
    
    void setAudioMax(float audioMax);
    
private:
    
    void setupFFT();
    
    
private:
    
    int         m_volumeRange;
    ProcessFFT  m_fft;
    bool        m_audioOn;
    float       m_audioMax;
    
};


