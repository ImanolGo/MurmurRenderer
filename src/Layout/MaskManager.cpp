/*
 *  MaskManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 18/11/15.
 *
 */

#include "ofMain.h"

#include "AppManager.h"
#include "MaskManager.h"



MaskManager::MaskManager(): Manager()
{
	//Intentionally left empty
}


MaskManager::~MaskManager()
{
    ofLogNotice() <<"MaskManager::Destructor";
}


void MaskManager::setup()
{
	if(m_initialized)
		return;

	Manager::setup();
    
    this->setupMasks();
    
    ofLogNotice() <<"MaskManager::initialized";

}

void MaskManager::setupMasks()
{
    
    
    WindowSettingsVector windowSettingsVector = AppManager::getInstance().getSettingsManager().getWindowsSettings();
    
    for(auto windowSettings : windowSettingsVector)
    {
        ofPtr<ofxMaskAddon> mask =  ofPtr<ofxMaskAddon>(new ofxMaskAddon());
        mask->setup(windowSettings.width, windowSettings.height, ofxMaskAddon::LUMINANCE);
    
        ofLogNotice() <<"MaskManager::setupMasks -> width =  " << windowSettings.width << ", height =  " << windowSettings.height;
        m_masks.push_back(mask);
    }
    

    this->setMaskWindowFront();
    this->setMaskWindowTop();
}

void MaskManager::setMaskWindowFront()
{
    int windowIndex = 1;
    
    if(windowIndex<0 ||  windowIndex > (m_masks.size()-1)){
        return;
    }
    
    ofLogNotice() <<"MaskManager::setup Front Mask ";
    
    ImageVisual gradientMask = ImageVisual(ofPoint(0,0), "frame_mask" );
    gradientMask.setWidth(m_masks[windowIndex]->getWidth()); gradientMask.setHeight(m_masks[windowIndex]->getHeight());
    
    
    m_masks[windowIndex]->beginMask();
        ofClear(0, 0, 0);
        gradientMask.draw();
    m_masks[windowIndex]->endMask();

}

void MaskManager::setMaskWindowTop()
{
    int windowIndex = 2;
    
    if(windowIndex<0 ||  windowIndex > (m_masks.size()-1)){
        return;
    }
    
    ofLogNotice() <<"MaskManager::setup Top Mask ";
    
    ImageVisual gradientMask = ImageVisual(ofPoint(m_masks[windowIndex]->getWidth()*0.5,m_masks[windowIndex]->getHeight()*0.5), "floor_mask", true );
    gradientMask.setHeight(m_masks[windowIndex]->getHeight(), true);

  
    m_masks[windowIndex]->beginMask();
        ofClear(0, 0, 0);
        gradientMask.draw();
    m_masks[windowIndex]->endMask();

    
}

void MaskManager::begin(int windowIndex)
{
    if(windowIndex<0 ||  windowIndex > (m_masks.size()-1)){
        return;
    }
    
    m_masks[windowIndex]->begin(true);
}

void MaskManager::end(int windowIndex)
{
    if(windowIndex<0 ||  windowIndex > (m_masks.size()-1)){
        return;
    }
    
    m_masks[windowIndex]->end();
    
    m_masks[windowIndex]->draw();
}




