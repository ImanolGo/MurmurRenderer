/*
 *  SmokyHandsScene.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 25/06/15.
 *
 */


#include "AppManager.h"
#include "ContourManager.h"

#include "SmokyHandsScene.h"

void SmokyHandsScene::setup() {
    
    m_smokeFluid.setup();
}

void SmokyHandsScene::update() {
    
    const ofFbo& source = AppManager::getInstance().getContourManager().getSource();
    m_smokeFluid.setSource(source);
    m_smokeFluid.update();
}

void SmokyHandsScene::draw() {
    ofBackground(0,0,0);
    //AppManager::getInstance().getContourManager().draw();
    
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    
    //AppManager::getInstance().getContourManager().draw();
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    m_smokeFluid.draw();
    ofPopStyle();
    
}

void SmokyHandsScene::willFadeIn() {

}

void SmokyHandsScene::willDraw() {

}

void SmokyHandsScene::willFadeOut() {

}

void SmokyHandsScene::willExit() {
    
}