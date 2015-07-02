/*
 *  UdpManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 01/07/15.
 *
 */


#include "UdpManager.h"
#include "SettingsManager.h"
#include "HandsManager.h"
#include "AppManager.h"


const int UdpManager::UDP_MESSAGE_LENGHT = 100;

UdpManager::UdpManager(): Manager()
{
    //Intentionally left empty
}

UdpManager::~UdpManager()
{
   ofLogNotice() << "UdpManager::destructor";
}


//--------------------------------------------------------------

void UdpManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    this->setupUdpReceiver();
    this->setupText();
    
    ofLogNotice() <<"UdpManager::initialized" ;
}

void UdpManager::setupUdpReceiver()
{
    int portReceive = AppManager::getInstance().getSettingsManager().getUdpPortReceive();
    ofLogNotice() <<"UdpManager::setupUdpReceiver -> listening for udp messages on port  " << portReceive;
    
    m_udpConnection.Create(); //create the socket
    m_udpConnection.Bind(portReceive); //and bind to port
    m_udpConnection.SetNonBlocking(true);
}

void UdpManager::setupText()
{
    
    int width = 700;
    int fontSize = 12;
    int height = fontSize*3;
    
    ofVec3f position;
    
    //position.x = GuiManager::GUI_WIDTH + 2*LayoutManager::MARGIN;
    position.y = LayoutManager::MARGIN + 9*fontSize;
    position.x = 2*LayoutManager::MARGIN + GuiManager::GUI_WIDTH ;
    
    int porReceive = AppManager::getInstance().getSettingsManager().getUdpPortReceive();
    string text = ">> UDP receiving -> Port: " + ofToString(porReceive);
    
    m_receivingInformation =  ofPtr<TextVisual> (new TextVisual(position, width, height));
    m_receivingInformation->setText(text, "fonts/open-sans/OpenSans-Semibold.ttf", fontSize);
    m_receivingInformation->setColor(ofColor::white);
    m_receivingInformation->setLineHeight(2.5);
    
    AppManager::getInstance().getViewManager().addOverlay(m_receivingInformation);
}


void UdpManager::update()
{
    char udpMessage[UDP_MESSAGE_LENGHT];
    string message;
    string tempMessage;
    bool getNext = true;
    
    string text = ">>UdpManager::update -> " ;
    
    while (getNext) {
        m_udpConnection.Receive(udpMessage,UDP_MESSAGE_LENGHT);
        tempMessage=udpMessage;
        
        if (tempMessage==""){
            getNext = false;
        }
        else{
            message = tempMessage;
        }
    
    }
   
    //ofLogNotice() <<">>UdpManager::update -> message: " << message;
    
    AppManager::getInstance().getHandsManager().readHands(message.c_str());
    
    m_udpConnection.Receive(udpMessage,UDP_MESSAGE_LENGHT);
   
    //ofLogNotice() << message;
    //this->updateReceiveText(message);
}


void UdpManager::updateReceiveText(const string& message)
{
    int porReceive = AppManager::getInstance().getSettingsManager().getUdpPortReceive();
    string text = ">> UDP receiving -> Port: " + ofToString(porReceive);
    text += "\n   " + message;
    m_receivingInformation->setText(text);
}









