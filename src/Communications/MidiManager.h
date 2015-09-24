/*
 *  MidiManager.h
 *  Murmur
 *
 *  Created by Imanol Gomez on 24/09/15.
 *
 */


#pragma once

#include "ofxMidi.h"
#include "Manager.h"

//========================== class MidiManager =======================================
//==============================================================================
/** \class MidiManager MidiManager.h
 *	\brief class for managing midi unputs
 *	\details It wraps the ofxMidi addon
 */


class MidiManager: public Manager, public ofxMidiListener
{

public:
    //! Constructor
    MidiManager();

    //! Destructor
    virtual ~MidiManager();

    //! setup
    void setup();

    void newMidiMessage(ofxMidiMessage& eventArgs);

private:

    //! setups the midi ports
    void setupMidiPorts();

    void logMidiMessage();


private:


    ofxMidiIn           m_midiIn;    ///< Hanles Midi input
    ofxMidiMessage      m_midiMessage;  ///< Hanles Midi messages

};

