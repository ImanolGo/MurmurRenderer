/*
 *  HandsWritingScene.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 02/07/15.
 *
 */


#include "AppManager.h"
#include "ContourManager.h"

#include "HandsWritingScene.h"


HandsWritingScene::HandsWritingScene():m_initialized(false)
{
    
}

HandsWritingScene::~HandsWritingScene()
{
    //Intentionally left empty
}

void HandsWritingScene::setup()
{
    if (m_initialized) {
        return;
    }
    
    m_initialized = true;
    
    ofLogNotice("HandsWritingScene::setup");
    
}


void HandsWritingScene::update()
{
    ///
}


void HandsWritingScene::draw() {
    ofBackground(0,50,0);
    this->drawVisuals();
}


void HandsWritingScene::drawVisuals()
{
    AppManager::getInstance().getHandsManager().draw();
}

void HandsWritingScene::willFadeIn() {
    ofLogNotice("HandsWritingScene::willFadeIn");
}

void HandsWritingScene::willDraw() {
    ofLogNotice("HandsWritingScene::willDraw");
}

void HandsWritingScene::willFadeOut() {
    ofLogNotice("HandsWritingScene::willFadeOut");
}

void HandsWritingScene::willExit() {
    ofLogNotice("HandsWritingScene::willExit");
}