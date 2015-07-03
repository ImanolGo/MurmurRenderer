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


BeautifulMindScene::BeautifulMindScene(): m_initialized(false), m_sceneNumber(0)
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
    
    ofPtr<ImageVisual> image = ofPtr<ImageVisual>(new ImageVisual(position,resourceName));
    
    ofLogNotice()<< "BeautifulMindScene::setupScene1 --> " << windowsSettings.height;
    
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

void BeautifulMindScene::updateScene1()
{
    
    float xPos = ofMap(sin(ofGetElapsedTimef()*0.3), -1, 1, -40, 0);
    float yPos = ofMap(sin(ofGetElapsedTimef()*0.2), -1, 1, -25, 0);
    string resourceName = "scene_01_BLURRED_FRONT";
    auto position = m_images[resourceName]->getPosition();
    position.x = xPos; position.y = yPos;
    m_images[resourceName]->setPosition(position);
    
    
    xPos = ofMap(sin(ofGetElapsedTimef()*0.31 + 500), -1, 1, 40, 0);
    yPos = ofMap(sin(ofGetElapsedTimef()*0.21+ 500), -1, 1, 25, 0);
    resourceName = "scene_01_BLURRED_MIDDLE";
    position = m_images[resourceName]->getPosition();
    position.x = xPos; position.y = yPos;
    m_images[resourceName]->setPosition(position);
    
}

void BeautifulMindScene::update() {
    
    switch (m_sceneNumber) {
        case 0:
            this->updateScene1();
            break;
            
        default:
            break;
    }
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