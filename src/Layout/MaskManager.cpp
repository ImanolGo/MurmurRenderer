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
    
    this->setupFbos();
    this->setupShaders();
    
    ofLogNotice() <<"MaskManager::initialized";

}

void MaskManager::setupFbos()
{
    WindowSettingsVector windowSettingsVector = AppManager::getInstance().getSettingsManager().getWindowsSettings();
    
    for(auto windowSettings : windowSettingsVector)
    {
        ofPtr<ofFbo> fbo =  ofPtr<ofFbo>(new ofFbo());
        fbo->allocate(windowSettings.width, windowSettings.height, GL_RGB);
        ofLogNotice() <<"MaskManager::setupFbos -> width =  " << windowSettings.width << ", height =  " << windowSettings.height;

        fbo->begin(); ofClear(0); fbo->end();
        m_fbos.push_back(fbo);
    }

}

void MaskManager::setMaskWindowFront()
{
    int indexWindow = 1;
    
    if(indexWindow<0 ||  indexWindow > (m_fbos.size()-1)){
        return;
    }
    
    ImageVisual gradientMask = ImageVisual(ofPoint(0,0), "floor_mask", true );
    gradientMask.setWidth(m_fbos[indexWindow]->getWidth()); gradientMask.setHeight(m_fbos[indexWindow]->getHeight());
    
    
    m_fbos[indexWindow]->begin();
        gradientMask.draw();
    m_fbos[indexWindow]->end();

}

void MaskManager::setMaskWindowTop()
{
    int indexWindow = 2;
    
    if(indexWindow<0 ||  indexWindow > (m_fbos.size()-1)){
        return;
    }
    
    ImageVisual gradientMask = ImageVisual(ofPoint(m_fbos[indexWindow]->getWidth()*0.5,m_fbos[indexWindow]->getHeight()*0.5), "floor_mask", true );
    gradientMask.setHeight(m_fbos[indexWindow]->getHeight(), true);

  
    m_fbos[indexWindow]->begin();
        gradientMask.draw();
    m_fbos[indexWindow]->end();
    
}

void MaskManager::setupShaders()
{
    if(ofIsGLProgrammableRenderer()){
        m_maskShader.load("shaders/shadersGL3/BlackMask");
    }
    else{
        m_maskShader.load("shaders/shadersGL2/BlackMask");
    }
}


void MaskManager::begin(int windowIndex)
{
    if(windowIndex<0 ||  windowIndex > (m_fbos.size()-1)){
        return;
    }
    
    m_maskShader.begin();
    m_maskShader.setUniformTexture("imageMask", m_fbos[windowIndex]->getTextureReference(), 1);
}

void MaskManager::end(int windowIndex)
{
  
    m_maskShader.end();
}




