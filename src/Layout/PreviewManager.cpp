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
        fbo->begin(); ofClear(0); fbo->end();
        m_fbos.push_back(fbo);
    }

    
}

void PreviewManager::draw()
{
    this->drawPreviewWindowFront();
    this->drawPreviewWindowTop();
}

void PreviewManager::drawPreviewWindowFront()
{
    int indexWindow = 1;
    
    if(indexWindow<0 ||  indexWindow > (m_fbos.size()-1)){
        return;
    }

    
    int fontSize = 12;
    int height = fontSize*3;
    
    float w = GuiManager::GUI_WIDTH*3;
    float h = w* m_fbos[indexWindow]->getHeight() / m_fbos[indexWindow]->getWidth();

    
    ofVec3f position;
    
    position.y = LayoutManager::MARGIN + 16*fontSize;
    position.x = 2*LayoutManager::MARGIN + GuiManager::GUI_WIDTH ;
    
    
    m_fbos[indexWindow]->draw(position.x, position.y, w, h);
}

void PreviewManager::drawPreviewWindowTop()
{
    int indexWindow = 2;
    
    if(indexWindow<0 ||  indexWindow > (m_fbos.size()-1)){
        return;
    }
    
    
    int fontSize = 12;
    int height = fontSize*3;
    
    float w = GuiManager::GUI_WIDTH*3;
    float h = w * m_fbos[indexWindow]->getHeight() / m_fbos[indexWindow]->getWidth();
    
    
    ofVec3f position;
    
    position.y = 2*LayoutManager::MARGIN + 16*fontSize + h;
    position.x = 2*LayoutManager::MARGIN + GuiManager::GUI_WIDTH ;
    
    
    m_fbos[indexWindow]->draw(position.x, position.y, w, h);
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




