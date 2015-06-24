/*
 *  OscManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 17/06/15.
 *
 */


#include "OscManager.h"
#include "SettingsManager.h"
#include "AppManager.h"


OscManager::OscManager(): Manager()
{
    //Intentionally left empty
}

OscManager::~OscManager()
{
   ofLogNotice() << "OscManager::destructor";
}


//--------------------------------------------------------------

void OscManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    ofLogNotice() <<"OscManager::initialized" ;
    this->setupOscReceiver();
    this->setupOscSender();
    this->setupText();
}

void OscManager::setupOscReceiver()
{
    int portReceive = AppManager::getInstance().getSettingsManager().getPortReceive();
    
    m_oscReceiver.setup(portReceive);
   
    ofLogNotice() <<"OscManager::setupOscReceiver -> listening for osc messages on port  " << portReceive;
}

void OscManager::setupOscSender()
{
    int portSend = AppManager::getInstance().getSettingsManager().getPortSend();
    string host = AppManager::getInstance().getSettingsManager().getIpAddress();
    
    m_oscSender.setup(host, portSend);
    
    ofLogNotice() <<"OscManager::setupOscSender -> open osc connection " << host << ":" << portSend;
}

void OscManager::setupText()
{
    
}


void OscManager::update()
{
    // check for waiting messages
    while(m_oscReceiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        m_oscReceiver.getNextMessage(&m);
        
        m_latestOscMessage = m;
        
       }
}


void OscManager::updateSendText()
{
    int portSend = AppManager::getInstance().getSettingsManager().getPortSend();
    string host = AppManager::getInstance().getSettingsManager().getIpAddress();
    string text = ">> OSC sending -> Host: " + host + ", Port: " + ofToString(portSend);
    
    text += ("\n   " + this->getMessageAsString(m_latestOscMessage));
    m_sendingInformation->setText(text);
}

void OscManager::updateReceiveText()
{
    int porReceive = AppManager::getInstance().getSettingsManager().getPortReceive();
    string text = ">> OSC receiving -> Port: " + ofToString(porReceive);
    
    text += ("\n   " + this->getMessageAsString(m_latestOscMessage));
    m_receivingInformation->setText(text);
}


string OscManager::getMessageAsString(const ofxOscMessage& m) const
{
    string msg_string;
    msg_string = m.getAddress();
    for(int i = 0; i < m.getNumArgs(); i++){
        // get the argument type
        msg_string += " ";
        // display the argument - make sure we get the right type
        if(m.getArgType(i) == OFXOSC_TYPE_INT32){
            msg_string += ofToString(m.getArgAsInt32(i));
        }
        else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
            msg_string += ofToString(m.getArgAsFloat(i));
        }
        else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
            msg_string += m.getArgAsString(i);
        }
        else{
            msg_string += "unknown";
        }
    }
    
    return msg_string;
}







