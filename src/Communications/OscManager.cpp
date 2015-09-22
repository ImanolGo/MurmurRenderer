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
    
    portSend = AppManager::getInstance().getSettingsManager().getOscPortUnity();
    host = "127.0.0.1";
    
    ofLogNotice() <<"OscManager::setupOscSenderUnity -> open osc connection " << host << ":" << portSend;
    
    m_oscSenderUnity.setup(host, portSend);
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
            //AppManager::getInstance().getSceneManager().changeScene(sceneName);
            AppManager::getInstance().getGuiManager().setScene(sceneName);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/SceneTransparency"){
            float value = m.getArgAsFloat(0);
            AppManager::getInstance().getGuiManager().setSceneTransparency(value);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/AudioVolume"){
            float value = m.getArgAsFloat(0);
            AppManager::getInstance().getGuiManager().setAudioVolume(value);
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
        
        else if(m.getAddress() == "/MurmurRenderer/ContourThickness"){
            float value = m.getArgAsFloat(0);
            AppManager::getInstance().getGuiManager().setContourThickness(value);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/ContourOffset"){
            ofVec2f pos;
            pos.x = m.getArgAsFloat(0);
            pos.y = m.getArgAsFloat(1);
            AppManager::getInstance().getGuiManager().setContourOffset(pos);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/ContourScale"){
            ofVec2f scale;
            scale.x = m.getArgAsFloat(0);
            scale.y = m.getArgAsFloat(1);
            AppManager::getInstance().getGuiManager().setContourScale(scale);
            this->updateReceiveText();
        }
        
        
        else if(m.getAddress() == "/MurmurRenderer/HandsOn"){
            int value = m.getArgAsInt32(0);
            bool handsOn = value != 0;
            AppManager::getInstance().getGuiManager().setHandsOn(handsOn);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/HandsFadeTime"){
            float value = m.getArgAsFloat(0);
            AppManager::getInstance().getGuiManager().setHandsFadeTime(value);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/HandsOffset"){
            ofVec2f pos;
            pos.x = m.getArgAsFloat(0);
            pos.y = m.getArgAsFloat(1);
            AppManager::getInstance().getGuiManager().setHandsOffset(pos);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/HandsScale"){
            ofVec2f scale;
            scale.x = m.getArgAsFloat(0);
            scale.y = m.getArgAsFloat(1);
            AppManager::getInstance().getGuiManager().setHandsScale(scale);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/FloorTrackingPos"){
            ofVec2f pos;
            pos.x = m.getArgAsFloat(0);
            pos.y = m.getArgAsFloat(1);
            AppManager::getInstance().getFloorManager().setPosition(pos);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/FloorOffset"){
            ofVec2f offset;
            offset.x = m.getArgAsFloat(0);
            offset.y = m.getArgAsFloat(1);
            AppManager::getInstance().getGuiManager().setFloorOffset(offset);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/FloorScale"){
            ofVec2f scale;
            scale.x = m.getArgAsFloat(0);
            scale.y = m.getArgAsFloat(1);
            AppManager::getInstance().getGuiManager().setFloorScale(scale);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/BeautifulMindOffset"){
            ofVec2f offset;
            offset.x = m.getArgAsFloat(0);
            offset.y = m.getArgAsFloat(1);
            AppManager::getInstance().getGuiManager().setBeautifulMindOffset(offset);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/BeautifulMindScale"){
            ofVec2f scale;
            scale.x = m.getArgAsFloat(0);
            scale.y = m.getArgAsFloat(1);
            AppManager::getInstance().getGuiManager().setBeautifulMindScale(scale);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/CropLeft"){
            int value  =  m.getArgAsInt32(0);
            AppManager::getInstance().getGuiManager().setCropLeft(value);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/CropRight"){
            int value  =  m.getArgAsInt32(0);
            AppManager::getInstance().getGuiManager().setCropRight(value);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/CropTop"){
            int value  =  m.getArgAsInt32(0);
            AppManager::getInstance().getGuiManager().setCropTop(value);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/CropBottom"){
            int value  =  m.getArgAsInt32(0);
            AppManager::getInstance().getGuiManager().setCropBottom(value);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/AudioMax"){
            float value  =  m.getArgAsFloat(0);
            AppManager::getInstance().getAudioManager().setAudioMax(value);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/BirdsPosition"){
            ofVec3f pos;
            pos.x = m.getArgAsFloat(0);
            pos.y = m.getArgAsFloat(1);
            pos.z = m.getArgAsFloat(2);
            AppManager::getInstance().getGuiManager().setBirdsPosition(pos);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/BirdsSize"){
            float value = m.getArgAsFloat(0);
            AppManager::getInstance().getGuiManager().setBirdsSize(value);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/BirdsSwarmSize"){
            float value = m.getArgAsFloat(0);
            AppManager::getInstance().getGuiManager().setBirdsSwarmSize(value);
            this->updateReceiveText();
        }

        else{
            
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
}

void OscManager::sendMessageToUnity(ofxOscMessage& message)
{
    m_oscSenderUnity.sendMessage(message);
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







