/*
 *  PreviewManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 29/09/15.
 *
 */

#include "ofMain.h"

#include "AppManager.h"
#include "PreviewManager.h"



PreviewManager::PreviewManager(): Manager()
{
	//Intentionally left empty
}


PreviewManager::~PreviewManager()
{
    ofLogNotice() <<"PreviewManager::Destructor";
}


void PreviewManager::setup()
{
	if(m_initialized)
		return;

	Manager::setup();
    
    this->setupFbos();

    ofLogNotice() <<"PreviewManager::initialized";

}

void PreviewManager::setupFbos()
{
    WindowSettingsVector windowSettingsVector = AppManager::getInstance().getSettingsManager().getWindowsSettings();
    
    for(auto windowSettings : windowSettingsVector)
    {
        ofPtr<ofFbo> fbo =  ofPtr<ofFbo>(new ofFbo());
        fbo->allocate(windowSettings.width, windowSettings.height, GL_RGBA);
        m_fbos.push_back(fbo);
    }

    
}

void PreviewManager::draw()
{
   
}

void PreviewManager::draw(int windowIndex)
{
    if(windowIndex<0 ||  windowIndex > (m_fbos.size()-1)){
        return;
    }
    
    m_fbos[windowIndex]->draw(0,0);
}


void PreviewManager::begin(int windowIndex)
{
    if(windowIndex<0 ||  windowIndex > (m_fbos.size()-1)){
        return;
    }
    
    m_fbos[windowIndex]->begin();
}

void PreviewManager::end(int windowIndex)
{
    if(windowIndex<0 ||  windowIndex > (m_fbos.size()-1)){
        return;
    }
    
    m_fbos[windowIndex]->end();

}




