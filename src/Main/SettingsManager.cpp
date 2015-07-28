/*
 *  SettingsManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 17/06/15.
 *
 */


#include "ofMain.h"

#include "SettingsManager.h"


const string SettingsManager::APPLICATION_SETTINGS_FILE_NAME = "xmls/ApplicationSettings.xml";
const string SettingsManager::LOCALHOST = "127.0.0.1";


SettingsManager::SettingsManager(): Manager(), m_portUdpReceive(0), m_portOscReceive(0), m_portOscSend(0), m_ipAddress(LOCALHOST)
{
    //Intentionally left empty
}


SettingsManager::~SettingsManager()
{
    ofLogNotice() <<"SettingsManager::Destructor" ;
}


void SettingsManager::setup()
{
	if(m_initialized)
		return;

	Manager::setup();

    if(this->loadSettingsFile()){
        this->loadAllSettings();
    }
    
    ofLogNotice() <<"SettingsManager::initialized" ;
}

void SettingsManager::loadAllSettings()
{
    this->setWindowProperties();
    this->setNetworkProperties();
    this->loadTextureSettings();
    this->loadSvgSettings();
    this->loadColors();
    this->loadTimings();
}

bool SettingsManager::loadSettingsFile()
{

	if(!m_xmlSettings.load(APPLICATION_SETTINGS_FILE_NAME)){
        ofLogNotice() <<"SettingsManager::loadSettingsFile-> unable to load file: " << APPLICATION_SETTINGS_FILE_NAME ;
        return false;
    }

    ofLogNotice() <<"SettingsManager::loadSettingsFile->  successfully loaded " << APPLICATION_SETTINGS_FILE_NAME ;
    return true;
}


void SettingsManager::setWindowProperties()
{
    m_xmlSettings.setTo("//");

    string windowPath = "//of_settings";
    if(m_xmlSettings.exists(windowPath)) {
        
        windowPath += "/window[0]";
        m_xmlSettings.setTo(windowPath);
        typedef   std::map<string, string>   AttributesMap;
        
        do {
            
            AttributesMap attributes = m_xmlSettings.getAttributes();
            WindowSettings windowSettings;
            
            windowSettings.title = attributes["title"];
            windowSettings.width = ofToInt(attributes["width"]);
            windowSettings.height = ofToInt(attributes["height"]);
            windowSettings.x = ofToInt(attributes["x"]);
            windowSettings.y = ofToInt(attributes["y"]);
            windowSettings.fullscreen = ofToBool(attributes["fullscreen"]);
            windowSettings.showCursor = ofToBool(attributes["showCursor"]);
            
            ofLogNotice() <<"SettingsManager::setWindowProperties->  title = "<< windowSettings.title <<", width = " << windowSettings.width <<", height = "
            <<windowSettings.height <<", x = "<< windowSettings.x << ", y = " <<windowSettings.y << ", fullscreen = " << windowSettings.fullscreen
            << ", showCursor = " << windowSettings.showCursor;
            
            m_windowsSettings.push_back(windowSettings);
        }
        while(m_xmlSettings.setToSibling()); // go to the next texture
        
        
        ofLogNotice() <<"SettingsManager::setWindowProperties->  successfully loaded the window settings" ;
        return;
    }

    ofLogNotice() <<"SettingsManager::setWindowProperties->  path not found: " << windowPath ;
}

void SettingsManager::setNetworkProperties()
{
    m_xmlSettings.setTo("//");

    string networkPath = "//of_settings/network";
    if(m_xmlSettings.exists(networkPath)) {
        m_xmlSettings.setTo(networkPath);
        typedef   std::map<string, string>   AttributesMap;
        AttributesMap attributes = m_xmlSettings.getAttributes();

        m_portUdpReceive = ofToInt(attributes["portUdpReceive"]);
        m_portOscReceive = ofToInt(attributes["portOscReceive"]);
        m_portOscSend  =   ofToInt(attributes["portOscSend"]);
        m_ipAddress  =  ofToString(attributes["ipAddress"]);

        ofLogNotice() <<"SettingsManager::setNetworkProperties->  receive UDP port = " << m_portUdpReceive << ". receive OSC port = "<< m_portOscReceive<<", send OSC port = " << m_portOscSend<<", host = "
        <<m_ipAddress ; 

        ofLogNotice() <<"SettingsManager::setNetworkProperties->  successfully loaded the network settings" ;
        return;
    }

    ofLogNotice() <<"SettingsManager::setNetworkProperties->  path not found: " << networkPath ;
}

void SettingsManager::loadColors()
{
    
    m_xmlSettings.setTo("//");
    
    string colorsSettingsPath = "//colors";
    if(m_xmlSettings.exists(colorsSettingsPath)) {
        
        typedef   std::map<string, string>   AttributesMap;
        AttributesMap attributes;
        
        colorsSettingsPath = "//colors/color[0]";
        m_xmlSettings.setTo(colorsSettingsPath);
        do {
            
            attributes = m_xmlSettings.getAttributes();
            
            int r = ofToInt(attributes["r"]);
            int g = ofToInt(attributes["g"]);
            int b = ofToInt(attributes["b"]);
            int a = ofToInt(attributes["a"]);
            
            ofColor color = ofColor(r,g,b,a);
            m_colors[attributes["name"]] = color;
            
            
            ofLogNotice() <<"SettingsManager::loadColors->  color = " << attributes["name"] <<", r = " << r
            <<", g = "<< g << ", b = " << b << ", a = " << a ;
        }
        while(m_xmlSettings.setToSibling()); // go to the next node
        
        
        ofLogNotice() <<"SettingsManager::loadColors->  successfully loaded the applications colors" ;
        return;
    }
    
    ofLogNotice() <<"SettingsManager::loadColors->  path not found: " << colorsSettingsPath ;
}

void SettingsManager::loadTextureSettings()
{
    m_xmlSettings.setTo("//");

    string resourcesPath = "//textures";
    if(m_xmlSettings.exists(resourcesPath)) {

        typedef   std::map<string, string>   AttributesMap;
        AttributesMap attributes;

        resourcesPath = "//textures/texture[0]";
        m_xmlSettings.setTo(resourcesPath);
        do {

            attributes = m_xmlSettings.getAttributes();
            m_texturesPath[attributes["name"]] = attributes["path"];

            ofLogNotice() <<"SettingsManager::loadTextureSettings->  texture = " << attributes["name"]
            <<", path = "<< attributes["path"] ;
        }
        while(m_xmlSettings.setToSibling()); // go to the next texture


        ofLogNotice() <<"SettingsManager::loadTextureSettings->  successfully loaded the resource settings" ;
        return;
    }

    ofLogNotice() <<"SettingsManager::loadTextureSettings->  path not found: " << resourcesPath ;
}

ofColor SettingsManager::getColor(const string& colorName)
{
    ofColor color;
    if(m_colors.find(colorName)!= m_colors.end()){
        color = m_colors[colorName];
    }
    
    return color;
}


void SettingsManager::loadSvgSettings()
{
    m_xmlSettings.setTo("//");

    string svgPath = "//svgs";
    if(m_xmlSettings.exists(svgPath)) {

        typedef   std::map<string, string>   AttributesMap;
        AttributesMap attributes;

        svgPath = "//svgs/svg[0]";
        m_xmlSettings.setTo(svgPath);
        do {

            attributes = m_xmlSettings.getAttributes();
            m_svgResourcesPath[attributes["name"]] = attributes["path"];

            ofLogNotice() <<"SettingsManager::loadSvgSettings->  svg = " << attributes["name"]
            <<", path = "<< attributes["path"] ;
        }
        while(m_xmlSettings.setToSibling()); // go to the next svg


        ofLogNotice() <<"SettingsManager::loadSvgSettings->  successfully loaded the resource settings" ;
        return;
    }

    ofLogNotice() <<"SettingsManager::loadSvgSettings->  path not found: " << svgPath ;
}

const WindowSettings& SettingsManager::getWindowsSettings  (int windowIndex) const
{
    if(0 <= windowIndex < m_windowsSettings.size()){
        return m_windowsSettings.at(windowIndex);
    }
    
    return m_defaultWindow;
}

void SettingsManager::loadTimings()
{
    m_xmlSettings.setTo("//");
    
    string path = "//timings";
    if(m_xmlSettings.exists(path)) {
        
        typedef   std::map<string, string>   AttributesMap;
        AttributesMap attributes;
        
        path = "//timings/timing[0]";
        m_xmlSettings.setTo(path);
        do {
            
            attributes = m_xmlSettings.getAttributes();
            
            int id = ofToInt(attributes["id"]);
            float duration = ofToFloat(attributes["duration"]);
            
            m_timings[id] = duration;
            
            ofLogNotice() <<"SettingsManager::loadTimings->  id = " << id <<", duration = "<< duration << "s";
        }
        while(m_xmlSettings.setToSibling()); // go to the next svg
        
        
        ofLogNotice() <<"SettingsManager::loadTimings->  successfully loaded the timing settings" ;
        return;
    }
    
    ofLogNotice() <<"SettingsManager::loadTimings->  path not found: " << path ;
}










