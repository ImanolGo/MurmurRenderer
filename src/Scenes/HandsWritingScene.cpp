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
    
    m_fluid.setup("xmls/HandsWritingFluid.xml");
    
    ofLogNotice("HandsWritingScene::setup");
    
}


void HandsWritingScene::update()
{
    this->updateFluid();
}


void HandsWritingScene::draw() {
    ofBackground(0,0,0);
    //AppManager::getInstance().getHandsManager().draw();
    this->drawFluid();
}

void HandsWritingScene::updateFluid()
{
    const vector< ofVec2f >& hands = AppManager::getInstance().getHandsManager().getHands();
    
    const ofFbo& source = AppManager::getInstance().getHandsManager().getSource();
    m_fluid.setSource(source);
    
    for (auto hand : hands) {
        m_fluid.addForce(hand);
    }
    
    m_fluid.update();
}

void HandsWritingScene::drawFluid()
{
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    
    AppManager::getInstance().getHandsManager().draw();
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    m_fluid.draw();
    ofPopStyle();
    
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