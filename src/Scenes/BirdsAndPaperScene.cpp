/*
 *  BirdsAndPaperScene.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 22/09/15.
 *
 */

#include "AppManager.h"

#include "BirdsAndPaperScene.h"

void BirdsAndPaperScene::setup() {
    ofLogNotice("BirdsAndPaperScene::setup");
    this->setInitialParameters();
}


void BirdsAndPaperScene::update() {
    
    //AppManager::getInstance().getBirdsManager().update();
    
}

void BirdsAndPaperScene::draw() {
    ofBackground(0,0,0);
    AppManager::getInstance().getBirdsManager().draw();
}

void BirdsAndPaperScene::willFadeIn() {
    ofLogNotice("BirdsAndPaperScene::willFadeIn");
    
    this->setInitialParameters();
    AppManager::getInstance().getGuiManager().update();
}


void BirdsAndPaperScene::setInitialParameters()
{
    AppManager::getInstance().getBirdsManager().stopEffects();
    
    m_visual.setScale(ofVec3f(1.0,1.0,1.0));
    m_visual.setPosition(ofVec3f(0,-0.7,0));
    
    AppManager::getInstance().getGuiManager().setBirdsSize(1.2);
    AppManager::getInstance().getGuiManager().setBirdsNumber(500);
    
    AppManager::getInstance().getGuiManager().setBirdsPosition(m_visual.getPosition());
    AppManager::getInstance().getGuiManager().setBirdsSize(m_visual.getScale().x);
    
    AppManager::getInstance().getGuiManager().setBirdsSpeed(15.0);
}

void BirdsAndPaperScene::willDraw()
{
    ofLogNotice("BirdsAndPaperScene::willDraw");
    this->startBirds();
}

void BirdsAndPaperScene::startBirds()
{
    m_visual.setScale(ofVec3f(20,20,20));
    m_visual.setPosition(ofVec3f(0,0,0));
    
    
    AppManager::getInstance().getBirdsManager().addMoveEffect(m_visual.getPosition(), 10);
    AppManager::getInstance().getBirdsManager().addScaleEffect(m_visual.getScale(), 50, 30);
    
    //AppManager::getInstance().getGuiManager().setBirdsPosition(m_visual.getPosition());
    //AppManager::getInstance().getGuiManager().setBirdsSize(m_visual.getScale());

    AppManager::getInstance().getGuiManager().setBirdsNumber(500);
    AppManager::getInstance().getGuiManager().setBirdsRandomness(10);
}

void BirdsAndPaperScene::willFadeOut() {
    ofLogNotice("BirdsAndPaperScene::willFadeOut");
}

void BirdsAndPaperScene::willExit() {
    ofLogNotice("BirdsAndPaperScene::willExit");
    this->setInitialParameters();
}