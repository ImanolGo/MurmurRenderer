/*
 *  ProjectorsManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 15/10/16.
 *
 */


#include "ProjectorsManager.h"
#include "AppManager.h"



ProjectorsManager::ProjectorsManager(): Manager()
{
    //Intentionally left empty
}

ProjectorsManager::~ProjectorsManager()
{
   ofLogNotice() << "ProjectorsManager::destructor";
}


//--------------------------------------------------------------

void ProjectorsManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    this->setupProjectors();
    
    
    ofLogNotice() <<"ProjectorsManager::initialized" ;
}


void ProjectorsManager::urlResponse(ofHttpResponse & response) {
    if (response.status==200 && response.request.name == "async_req") {
        ofLogNotice() <<"ProjectorsManager::shutterProjector -> url status: " << response.status << ", error " << response.error;
    } else {
        ofLogNotice() <<"ProjectorsManager::shutterProjector -> url status: " << response.status << ", error " << response.error;
        ofRemoveAllURLRequests();
    }
}


void ProjectorsManager::setupProjectors()
{
    
  auto projectorsIps =  AppManager::getInstance().getSettingsManager().getProjectorsIps();

    for(auto projectorIp: projectorsIps)
    {
        ofPtr <ofxPanasonicControl> projector = ofPtr <ofxPanasonicControl> (new ofxPanasonicControl());
        projector->setup(projectorIp,Panasonic_MODE,"admin1","panasonic");
        m_projectors.push_back(projector);
    }
}


void ProjectorsManager::shutterProjector1(bool& value)
{
    //this->shutterProjector(0, value);
}

void ProjectorsManager::shutterProjector2(bool& value)
{
    //this->shutterProjector(1, value);
}

void ProjectorsManager::shutterProjector(int num, bool value)
{
    if(m_projectors.size() < num){
        return;
    }
    
    if(value){
        ofLogNotice() <<"ProjectorsManager::shutterProjector -> projector " << num << ", shutter closed";
        m_projectors[num]->sendCommand("00OSH:1\r"); //shutter closed
    }
    else{
        ofLogNotice() <<"ProjectorsManager::shutterProjector -> projector " << num << ", shutter closed";
        m_projectors[num]->sendCommand("00OSH:0\r"); //shutter open
    }
}








