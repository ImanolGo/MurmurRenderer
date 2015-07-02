/*
 *  FluidFloorScene.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 02/07/15.
 *
 */


#include "AppManager.h"
#include "ContourManager.h"

#include "FluidFloorScene.h"


FluidFloorScene::FluidFloorScene():m_initialized(false)
{
    
}

FluidFloorScene::~FluidFloorScene()
{
    //Intentionally left empty
}

void FluidFloorScene::setup()
{
    if (m_initialized) {
        return;
    }
    
    m_initialized = true;
    
    m_fluid.setup("xmls/FluidFloor.xml");
    
    ofLogNotice("FluidFloorScene::setup");
    
}


void FluidFloorScene::update()
{
    this->updateFluid();
}


void FluidFloorScene::draw() {
    ofBackground(0,0,0);
    //AppManager::getInstance().getHandsManager().draw();
    this->drawFluid();
}

void FluidFloorScene::updateFluid()
{
    auto floorPosition = AppManager::getInstance().getFloorManager().getPosition();
    
    m_fluid.addForce(floorPosition);
    m_fluid.update();
}

void FluidFloorScene::drawFluid()
{
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    
    AppManager::getInstance().getFloorManager().draw();
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    m_fluid.draw();
    ofPopStyle();
    
}


void FluidFloorScene::willFadeIn() {
    ofLogNotice("FluidFloorScene::willFadeIn");
}

void FluidFloorScene::willDraw() {
    ofLogNotice("FluidFloorScene::willDraw");
}

void FluidFloorScene::willFadeOut() {
    ofLogNotice("FluidFloorScene::willFadeOut");
}

void FluidFloorScene::willExit() {
    ofLogNotice("FluidFloorScene::willExit");
}