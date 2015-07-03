/*
 *  BeautifulMindScene.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 02/07/15.
 *
 */


#include "AppManager.h"
#include "BeautifulMindScene.h"

const int BeautifulMindScene::NUMBER_SCENES = 4;


BeautifulMindScene::BeautifulMindScene(): m_initialized(false)
{
    //! Intentionally left empty
}


BeautifulMindScene::~BeautifulMindScene()
{
    //! Intentionally left empty
}


void BeautifulMindScene::setup() {
    
    if(m_initialized){
        return;
    }
    
    m_initialized = true;
    
    this->setupScene1();
    
    ofLogNotice("BeautifulMindScene::setup");
    
}


void BeautifulMindScene::setupScene1()
{
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    
    string resourceName = "scene_01_BLURRED_FRONT";
    ofPoint position = ofPoint(0,0,0);
    
    auto image = ofPtr<ImageVisual>(new ImageVisual(position,resourceName));
    image->setHeight(windowsSettings.height); image->setWidth(windowsSettings.width);
    m_images[resourceName] = image;
    
    resourceName = "scene_01_BLURRED_MIDDLE";
    
    image = ofPtr<ImageVisual>(new ImageVisual(position,resourceName));
    image->setHeight(windowsSettings.height); image->setWidth(windowsSettings.width);
    m_images[resourceName] = image;
    
    
    resourceName = "scene_01_BLURRED_REAR";
    image = ofPtr<ImageVisual>(new ImageVisual(position,resourceName));
    image->setHeight(windowsSettings.height); image->setWidth(windowsSettings.width);
    m_images[resourceName] = image;
    
}

void BeautifulMindScene::update() {
    
}

void BeautifulMindScene::draw() {
    ofBackground(0,0,0);
    
    
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
        for (auto image: m_images) {
            image.second->draw();
        }
    
    ofPopStyle();
}

void BeautifulMindScene::willFadeIn() {
     ofLogNotice("BeautifulMindScene::willFadeIn");
}

void BeautifulMindScene::willDraw() {
    ofLogNotice("BeautifulMindScene::willDraw");
}

void BeautifulMindScene::willFadeOut() {
    ofLogNotice("BeautifulMindScene::willFadeOut");
}

void BeautifulMindScene::willExit() {
    ofLogNotice("BeautifulMindScene::willExit");
}