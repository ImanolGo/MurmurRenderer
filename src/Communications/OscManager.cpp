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
    auto windowSettings = AppManager::getInstance().getSettingsManager().getWindowsSettings(0);
    
    ofVec3f position;
  
    int width =  (windowSettings.width - 4*LayoutManager::MARGIN - GuiManager::GUI_WIDTH)*0.5 - LayoutManager::MARGIN;
    int fontSize = 12;
    int height = fontSize*3;
    
    
    string text = "COMMUNICATIONS";
    position.x = GuiManager::GUI_WIDTH + 2.5*LayoutManager::MARGIN;
    position.y = LayoutManager::MARGIN + windowSettings.height*0.5;
    
    ofPtr<TextVisual> textVisual = ofPtr<TextVisual>(new TextVisual(position, width, height));
    textVisual->setText(text, "fonts/open-sans/OpenSans-Semibold.ttf", fontSize);
    textVisual->setColor(ofColor::white);
    
    AppManager::getInstance().getViewManager().addOverlay(textVisual);
    
    position.x -= LayoutManager::MARGIN*0.5;
    position.y -= LayoutManager::MARGIN*0.5;
    height = textVisual->getHeight() + LayoutManager::MARGIN;
    width = textVisual->getWidth() + LayoutManager::MARGIN;
    ofPtr<RectangleVisual> rectangleVisual = ofPtr<RectangleVisual>(new RectangleVisual(position, width, height));
    ofColor color(60,60,60);
    rectangleVisual->setColor(color);
    
    AppManager::getInstance().getViewManager().addOverlay(rectangleVisual,2);
    
    
    int portSend = AppManager::getInstance().getSettingsManager().getOscPortSend();
    string host = AppManager::getInstance().getSettingsManager().getIpAddress();
    text = ">> OSC sending -> Host: " + host + ", Port: " + ofToString(portSend);
    
    
    width =  (windowSettings.width - 4*LayoutManager::MARGIN - GuiManager::GUI_WIDTH)*0.5 - LayoutManager::MARGIN;
    height = fontSize*3;
    
    position.x = GuiManager::GUI_WIDTH + 2.5*LayoutManager::MARGIN ;
    position.y = LayoutManager::MARGIN + rectangleVisual->getPosition().y + rectangleVisual->getHeight();
    
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
    
    
    
    width += LayoutManager::MARGIN;
    height = 5.5*LayoutManager::MARGIN;
    
    position.x -= LayoutManager::MARGIN*0.5;
    position.y =  0.5*LayoutManager::MARGIN + rectangleVisual->getPosition().y + rectangleVisual->getHeight();
    
    rectangleVisual = ofPtr<RectangleVisual>(new RectangleVisual(position, width, height));
    rectangleVisual->setColor(color);
    
    AppManager::getInstance().getViewManager().addOverlay(rectangleVisual,2);
    
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
        
        else if(m.getAddress() == "/MurmurRenderer/HandsSize"){
            float value = m.getArgAsFloat(0);
            AppManager::getInstance().getGuiManager().setHandsSize(value);
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
        
        else if(m.getAddress() == "/MurmurRenderer/FloorOffset/x"){
            float value = m.getArgAsFloat(0);
            AppManager::getInstance().getGuiManager().setFloorOffsetX(value);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/FloorOffset/y"){
            float value = m.getArgAsFloat(0);
            AppManager::getInstance().getGuiManager().setFloorOffsetY(value);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/FloorScale/x"){
            float value = m.getArgAsFloat(0);
            AppManager::getInstance().getGuiManager().setFloorScaleX(value);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/FloorScale/y"){
            float value = m.getArgAsFloat(0);
            AppManager::getInstance().getGuiManager().setFloorScaleY(value);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/HandsOffset/x"){
            float value = m.getArgAsFloat(0);
            AppManager::getInstance().getGuiManager().setHandsOffsetX(value);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/HandsOffset/y"){
            float value = m.getArgAsFloat(0);
            AppManager::getInstance().getGuiManager().setHandsOffsetY(value);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/HandsScale/x"){
            float value = m.getArgAsFloat(0);
            AppManager::getInstance().getGuiManager().setHandsScaleX(value);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/HandsScale/y"){
            float value = m.getArgAsFloat(0);
            AppManager::getInstance().getGuiManager().setHandsScaleY(value);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/ContourOffset/x"){
            float value = m.getArgAsFloat(0);
            AppManager::getInstance().getGuiManager().setContourOffsetX(value);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/ContourOffset/y"){
            float value = m.getArgAsFloat(0);
            AppManager::getInstance().getGuiManager().setContourOffsetY(value);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/ContourScale/x"){
            float value = m.getArgAsFloat(0);
            AppManager::getInstance().getGuiManager().setContourScaleX(value);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/ContourScale/y"){
            float value = m.getArgAsFloat(0);
            AppManager::getInstance().getGuiManager().setContourScaleY(value);
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
            AppManager::getInstance().getGuiManager().onSetBirdsSwarmSize(value);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/BirdsNumber"){
            float value = m.getArgAsFloat(0);
            AppManager::getInstance().getGuiManager().setBirdsNumber(value);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/BirdsSpeed"){
            float value = m.getArgAsFloat(0);
            AppManager::getInstance().getGuiManager().setBirdsSpeed(value);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/BirdsRandomness"){
            float value = m.getArgAsFloat(0);
            AppManager::getInstance().getGuiManager().setBirdsRandomness(value);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/BeautifulMindFloorSpeed"){
            float value = m.getArgAsFloat(0);
            AppManager::getInstance().getGuiManager().setBeautifulMindFloorSpeed(value);
            this->updateReceiveText();
        }
        
        else if(m.getAddress() == "/MurmurRenderer/BeautifulMindFloorOn"){
            int value = m.getArgAsInt32(0);
            bool floorOn = value != 0;
            AppManager::getInstance().getGuiManager().setBeautifulMindFloorOn(floorOn);
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
    string text = ">> OSC sending -> Host: " + host + ", Port: " + ofToString(portSend) + "\n";
    
    text += this->getMessageAsString(m_latestOscMessage);
    m_sendingInformation->setText(text);
}

void OscManager::updateReceiveText()
{
    int porReceive = AppManager::getInstance().getSettingsManager().getOscPortReceive();
    string text = ">> OSC receiving -> Port: " + ofToString(porReceive) + "\n";
    
    text +=  this->getMessageAsString(m_latestOscMessage);
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







