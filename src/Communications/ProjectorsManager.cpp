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
    
     m_projectorsIps = AppManager::getInstance().getSettingsManager().getProjectorsIps();
    
//    auto projectorsIps =  AppManager::getInstance().getSettingsManager().getProjectorsIps();
//
//    for(auto projectorIp: projectorsIps)
//    {
//        ofPtr <ofxPanasonicControl> projector = ofPtr <ofxPanasonicControl> (new ofxPanasonicControl());
//        projector->setup();
//        m_projectors.push_back(projector);
//    }
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
    if(m_projectorsIps.size() < num){
        return;
    }
    
    
    string command_url = "http://user1:panasonic@" + m_projectorsIps[num];
    
    if(value){
        command_url +=   "/cgi-bin/proj_ctl.cgi?key=shutter_on&lang=e&osd=off";
    }
    else{
        command_url +=   "/cgi-bin/proj_ctl.cgi?key=shutter_off&lang=e&osd=off";
    }
    
    ofLogNotice() <<"ProjectorsManager::shutterProjector -> projector " << num << ", shutter " << value;
    ofLogNotice() <<"ProjectorsManager::shutterProjector -> url send: " << command_url;
    
    ofLoadURLAsync(command_url, "async_req");
    
}








