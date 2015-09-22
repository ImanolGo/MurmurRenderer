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
    //m_syphonVisual.setup("Main Camera","Unity");
    m_syphonVisual.setup("Main Camera","birds");
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
    //m_shader.begin();
      //  m_syphonVisual.draw();
    //m_shader.end();
    
    m_syphonVisual.draw();
}


void BirdsManager::onChangePosition(ofVec3f& target)
{
    float scale = 50;
    m_target = target;
    
    ofxOscMessage m;
    m.setAddress("/MurmurBirds/position/x");
    m.addFloatArg(m_target.x*scale);
    AppManager::getInstance().getOscManager().sendMessageToUnity(m);
    
    scale = 30;
    m.clear();
    m.setAddress("/MurmurBirds/position/y");
    m.addFloatArg(m_target.y*scale);
    AppManager::getInstance().getOscManager().sendMessageToUnity(m);
    
    scale = 30;
    m.clear();
    m.setAddress("/MurmurBirds/position/z");
    m.addFloatArg(m_target.z*scale);
    AppManager::getInstance().getOscManager().sendMessageToUnity(m);
}

void BirdsManager::onChangeSize(float& value)
{
    m_birdsSize = value;
    
    ofxOscMessage m;
    m.setAddress("/MurmurBirds/birdSize");
    m.addFloatArg(m_birdsSize);
    AppManager::getInstance().getOscManager().sendMessageToUnity(m);

}

void BirdsManager::onChangeSpeed(float& value)
{
    m_birdsSpeed = value;
    
    ofxOscMessage m;
    m.setAddress("/MurmurBirds/speed");
    m.addFloatArg(m_birdsSpeed);
    AppManager::getInstance().getOscManager().sendMessageToUnity(m);
    
}

/*void BirdsManager::onChangeSwarmSize(float& value)
{
    m_birdsSwarmSize = value;
    
    ofxOscMessage m;
    m.setAddress("/MurmurBirds/swarmSize");
    m.addFloatArg(m_birdsSwarmSize);
    AppManager::getInstance().getOscManager().sendMessageToUnity(m);
}*/

void BirdsManager::onChangeSwarmSize(ofVec3f& size)
 {
     
     ofxOscMessage m;
     m.setAddress("/MurmurBirds/swarmSize/width");
     m.addFloatArg(size.x);
     AppManager::getInstance().getOscManager().sendMessageToUnity(m);
     
     m.clear();
     m.setAddress("/MurmurBirds/swarmSize/height");
     m.addFloatArg(size.y);
     AppManager::getInstance().getOscManager().sendMessageToUnity(m);
     
     m.clear();
     m.setAddress("/MurmurBirds/swarmSize/depth");
     m.addFloatArg(size.z);
     AppManager::getInstance().getOscManager().sendMessageToUnity(m);
}

void BirdsManager::onChangeSwarmNumber(int& value)
{
    m_birdsSwarmNumber = value;
    
    ofxOscMessage m;
    m.setAddress("/MurmurBirds/swarmNumber");
    m.addFloatArg(m_birdsSwarmNumber);
    AppManager::getInstance().getOscManager().sendMessageToUnity(m);
}





