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
    
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    m_drawArea = ofRectangle(windowsSettings.x, windowsSettings.y, windowsSettings.width, windowsSettings.height);
    
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
    auto hands = AppManager::getInstance().getHandsManager().getHands();
    
    //ofLogNotice() <<"HandsManager::readHands << size -> " << hands.size();
    
    for (auto hand : hands) {
        m_fluid.addForce(hand);
         //ofLogNotice() <<"HandsManager::readHands << y -> " << hand.y;
         //ofLogNotice() <<"HandsManager::readHands << x -> " << hand.x;
    }
    
    m_fluid.update();
}

void HandsWritingScene::drawFluid()
{
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    
    //AppManager::getInstance().getHandsManager().draw(m_drawArea);
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    m_fluid.draw(m_drawArea);
    
    if(AppManager::getInstance().getDebugMode()){
        m_fluid.drawGui();
    }
    
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