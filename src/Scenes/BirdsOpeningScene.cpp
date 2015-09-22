/*
 *  BirdsOpeningScene.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 22/09/15.
 *
 */

#include "AppManager.h"

#include "BirdsOpeningScene.h"

void BirdsOpeningScene::setup() {
    ofLogNotice("BirdsOpeningScene::setup");
    
    this->setInitialParameters();
}


void BirdsOpeningScene::update() {
    
    //AppManager::getInstance().getBirdsManager().update();
}

void BirdsOpeningScene::draw() {
    ofBackground(0,0,0);
    AppManager::getInstance().getBirdsManager().draw();
}

void BirdsOpeningScene::willFadeIn() {
    ofLogNotice("BirdsOpeningScene::willFadeIn");
    
    this->setInitialParameters();
    AppManager::getInstance().getGuiManager().update();
}


void BirdsOpeningScene::setInitialParameters() {
    
    AppManager::getInstance().getGuiManager().setBirdsSize(1.7);
    AppManager::getInstance().getGuiManager().setBirdsNumber(0);
    
    ofVec3f position(0,-0.7,0);
    AppManager::getInstance().getGuiManager().setBirdsPosition(position);
    
    m_swarmSize = 1.0;
    AppManager::getInstance().getGuiManager().onSetBirdsSwarmSize(m_swarmSize);
    
    AppManager::getInstance().getGuiManager().setBirdsSpeed(7.0);
    
}

void BirdsOpeningScene::willDraw() {
    ofLogNotice("BirdsOpeningScene::willDraw");
    
    this->startBirds();
}

void BirdsOpeningScene::startBirds()
{
    AppManager::getInstance().getGuiManager().setBirdsSize(1.2);
    AppManager::getInstance().getGuiManager().setBirdsNumber(100);
    
    ofVec3f position(0,0.3,0);
    AppManager::getInstance().getGuiManager().setBirdsPosition(position);
    
    m_swarmSize = 1.0;
    AppManager::getInstance().getGuiManager().onSetBirdsSwarmSize(m_swarmSize);
    

}

void BirdsOpeningScene::willFadeOut() {
    ofLogNotice("BirdsOpeningScene::willFadeOut");
}

void BirdsOpeningScene::willExit() {
    ofLogNotice("BirdsOpeningScene::willExit");
    this->setInitialParameters();
}