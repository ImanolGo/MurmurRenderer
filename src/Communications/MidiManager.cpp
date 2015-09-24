/*
 *  MidiManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 17/06/15.
 *
 */


#include "MidiManager.h"
#include "AppManager.h"


MidiManager::MidiManager(): Manager()
{
    //Intentionally left empty
}

MidiManager::~MidiManager()
{
   ofLogNotice() << "MidiManager::destructor";
}


//--------------------------------------------------------------

void MidiManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    ofLogNotice() <<"MidiManager::initialized" ;
    
    this->setupMidiPorts();
    
}

void MidiManager::setupMidiPorts()
{
   	// print input ports to console
    ofLogNotice() <<"MidiManager::setupMidiPorts-> Ports: ";
    m_midiIn.listPorts(); // via instance
    //ofxMidiIn::listPorts(); // via static as well
    
    // open port by number (you may need to change this)
    m_midiIn.openPort(0);
    //midiIn.openPort("IAC Pure Data In");	// by name
    //midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port
    
    // don't ignore sysex, timing, & active sense messages,
    // these are ignored by default
    m_midiIn.ignoreTypes(false, false, false);
    
    // add ofApp as a listener
    m_midiIn.addListener(this);
    
    // print received messages to the console
    m_midiIn.setVerbose(true);
}


//--------------------------------------------------------------
void MidiManager::newMidiMessage(ofxMidiMessage& msg) {
    
    // make a copy of the latest message
    m_midiMessage = msg;
    this->logMidiMessage();
}

//--------------------------------------------------------------
void MidiManager::logMidiMessage() {
    
    ofLogNotice() <<"MidiManager::logMidiMessage-> Received: " << ofxMidiMessage::getStatusString(m_midiMessage.status);
    ofLogNotice() <<"MidiManager::logMidiMessage-> Channel: " << m_midiMessage.channel;
    ofLogNotice() <<"MidiManager::logMidiMessage-> Pitch: " << m_midiMessage.pitch;
    ofLogNotice() <<"MidiManager::logMidiMessage-> Velocity: " << m_midiMessage.velocity;
    ofLogNotice() <<"MidiManager::logMidiMessage-> Control: " << m_midiMessage.control;
    ofLogNotice() <<"MidiManager::logMidiMessage-> Value: " << m_midiMessage.value;
}







