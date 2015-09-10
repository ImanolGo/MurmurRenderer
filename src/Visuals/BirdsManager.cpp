/*
 *  BirdsManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 05/08/15.
 *
 */


#include "AppManager.h"
#include "BirdsManager.h"


BirdsManager::BirdsManager()
{
    //Intentionaly left empty
}


BirdsManager::~BirdsManager()
{
    ofLogNotice() <<"BirdsManager::Destructor" ;
}


void BirdsManager::setup()
{

    Manager::setup();
    
    ofLogNotice() <<"BirdsManager::initialized" ;
    
    this->setupSyphon();
    this->setupShader();
}


void BirdsManager::setupSyphon()
{
    int windowIndex = 1;
    auto windowsSettings = AppManager::getInstance().getSettingsManager().getWindowsSettings(windowIndex);
    
    m_syphonVisual.setWidth(windowsSettings.width); m_syphonVisual.setHeight(windowsSettings.height);
    
    //m_syphonVisual.setup("","Simple Server");
    m_syphonVisual.setup("Main Camera","Unity");
    //m_syphonVisual.setup("Main Camera","birds");
}

void BirdsManager::setupShader()
{
    if(ofIsGLProgrammableRenderer()){
        m_shader.load("shaders/shadersGL3/InverterShader");
    }
    else{
        m_shader.load("shaders/shadersGL2/InverterShader");
    }
    
    ofLogNotice() <<"ContourManager::setupShader";
}



void BirdsManager::update()
{

}

void BirdsManager::draw()
{
    m_shader.begin();
        m_syphonVisual.draw();
    m_shader.end();
}






