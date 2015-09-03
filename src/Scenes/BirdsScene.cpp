/*
 *  BirdsScene.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 05/08/15.
 *
 */

#include "AppManager.h"

#include "BirdsScene.h"

void BirdsScene::setup() {
    ofLogNotice("BirdsScene::setup");
    this->setupSyphonVisual();
}


void BirdsScene::setupSyphonVisual() {
    
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    
    m_syphonVisual.setWidth(windowsSettings.width); m_syphonVisual.setHeight(windowsSettings.height);
    
    //m_syphonVisual.setup("","Simple Server");
    m_syphonVisual.setup("Main Camera","Unity");
    //m_syphonVisual.setup("Main Camera","birds");
    
}


void BirdsScene::update() {
    
    //AppManager::getInstance().getBirdsManager().update();
}

void BirdsScene::draw() {
    ofBackground(0,0,0);
    //AppManager::getInstance().getBirdsManager().draw();
    m_syphonVisual.draw();
}

void BirdsScene::willFadeIn() {
     ofLogNotice("BirdsScene::willFadeIn");
}

void BirdsScene::willDraw() {
    ofLogNotice("BirdsScene::willDraw");
}

void BirdsScene::willFadeOut() {
    ofLogNotice("BirdsScene::willFadeOut");
}

void BirdsScene::willExit() {
    ofLogNotice("BirdsScene::willExit");
}