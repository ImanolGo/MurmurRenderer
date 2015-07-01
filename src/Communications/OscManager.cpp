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


OscManager::OscManager(): Manager(), m_numberOfContours(0)
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
    
    this->setupOscReceiver();
    this->setupOscSender();
    this->setupText();
    
    ofLogNotice() <<"OscManager::initialized" ;
}

void OscManager::setupOscReceiver()
{
    int portReceive = AppManager::getInstance().getSettingsManager().getOscPortReceive();
    ofLogNotice() <<"OscManager::setupOscReceiver -> listening for osc messages on port  " << portReceive;
    m_oscReceiver.setup(portReceive);
   
    
}

void OscManager::setupOscSender()
{
    int portSend = AppManager::getInstance().getSettingsManager().getOscPortSend();
    string host = AppManager::getInstance().getSettingsManager().getIpAddress();
    
    ofLogNotice() <<"OscManager::setupOscSender -> open osc connection " << host << ":" << portSend;
    
    m_oscSender.setup(host, portSend);
    
   
}

void OscManager::setupText()
{
    ofVec3f position;
   
    position.x = GuiManager::GUI_WIDTH + 2*LayoutManager::MARGIN;
    position.y = LayoutManager::MARGIN;
    
    int width = 700;
    int fontSize = 12;
    int height = fontSize*3;
    
    int portSend = AppManager::getInstance().getSettingsManager().getOscPortSend();
    string host = AppManager::getInstance().getSettingsManager().getIpAddress();
    string text = ">> OSC sending -> Host: " + host + ", Port: " + ofToString(portSend);
    
    m_sendingInformation =  ofPtr<TextVisual> (new TextVisual(position, width, height));
    m_sendingInformation->setText(text, "fonts/open-sans/OpenSans-Semibold.ttf", fontSize);
    m_sendingInformation->setColor(ofColor::white);
    m_sendingInformation->setLineHeight(2.5);
    
    AppManager::getInstance().getViewManager().addOverlay(m_sendingInformation);
    
    
    int porReceive = AppManager::getInstance().getSettingsManager().getOscPortReceive();
    text = ">> OSC receiving -> Port: " + ofToString(porReceive);
    
    position.y += (height + 3*fontSize);
    m_receivingInformation =  ofPtr<TextVisual> (new TextVisual(position, width, height));
    m_receivingInformation->setText(text, "fonts/open-sans/OpenSans-Semibold.ttf", fontSize);
    m_receivingInformation->setColor(ofColor::white);
    m_receivingInformation->setLineHeight(2.5);
    
    AppManager::getInstance().getViewManager().addOverlay(m_receivingInformation);
}


void OscManager::update()
{
    // check for waiting messages
    while(m_oscReceiver.hasWaitingMessages())
    {
        // get the next message
        ofxOscMessage m;
        m_oscReceiver.getNextMessage(&m);
        
        m_latestOscMessage = m;
       
        if(m.getAddress() == "/MurmurRenderer/Scene"){
            string sceneName = m.getArgAsString(0);
            AppManager::getInstance().getSceneManager().changeScene(sceneName);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/SceneTransitionTime"){
            float value = m.getArgAsFloat(0);
            AppManager::getInstance().getGuiManager().setSceneTransitionTime(value);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/NumContours"){
            m_numberOfContours = m.getArgAsInt32(0);
            AppManager::getInstance().getContourManager().resetContours();
            this->updateReceiveText();
        }
        
        
        for (int i = 0; i<m_numberOfContours; i++) {
            string contourAddr = "/MurmurRenderer/Contour/" + ofToString(i);
            
            if(m.getAddress() == contourAddr){
                
                vector<float> contourPoints;
                for (int n = 0; n < m.getNumArgs(); n++) {
                    contourPoints.push_back(m.getArgAsFloat(n));
                }
                
                AppManager::getInstance().getContourManager().setContour(contourPoints);
               
            }
        }

        
    }
}


void OscManager::updateSendText()
{
    int portSend = AppManager::getInstance().getSettingsManager().getOscPortSend();
    string host = AppManager::getInstance().getSettingsManager().getIpAddress();
    string text = ">> OSC sending -> Host: " + host + ", Port: " + ofToString(portSend);
    
    text += ("\n   " + this->getMessageAsString(m_latestOscMessage));
    m_sendingInformation->setText(text);
}

void OscManager::updateReceiveText()
{
    int porReceive = AppManager::getInstance().getSettingsManager().getOscPortReceive();
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







