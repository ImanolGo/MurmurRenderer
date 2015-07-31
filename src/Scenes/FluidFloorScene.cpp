/*
 *  FluidFloorScene.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 02/07/15.
 *
 */


#include "AppManager.h"
#include "ContourManager.h"
#include "SettingsManager.h"

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
    
    this->setupFbos();
    this->setupShaders();
    
    ofLogNotice("FluidFloorScene::setup");
    
}

void FluidFloorScene::setupFbos()
{
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    m_fboMask.allocate(windowsSettings.width, windowsSettings.height);
    
    ImageVisual gradientMask = ImageVisual(ofPoint(windowsSettings.width*0.5, windowsSettings.height*0.5), "floor_mask", true );
    
    m_fboMask.begin();
        ofClear(0);
        gradientMask.draw();
    m_fboMask.end();
}

void FluidFloorScene::setupShaders()
{
    if(ofIsGLProgrammableRenderer()){
        m_maskShader.load("shaders/shadersGL3/BlackMask");
    }
    else{
        m_maskShader.load("shaders/shadersGL2/BlackMask");
    }
    
    
}

void FluidFloorScene::update()
{
    this->updateFluid();
}


void FluidFloorScene::draw() {
    ofBackground(0,0,0);
    
    m_maskShader.begin();
    m_maskShader.setUniformTexture("imageMask", m_fboMask.getTextureReference(), 1);
        AppManager::getInstance().getHandsManager().draw();
        this->drawFluid();
    m_maskShader.end();
    
    
    if(AppManager::getInstance().getDebugMode()){
        m_fluid.drawGui();
    }

}

void FluidFloorScene::updateFluid()
{
    auto floorPosition = AppManager::getInstance().getFloorManager().getPosition();
    
    m_fluid.addForce(floorPosition);
    m_fluid.update();
}



void FluidFloorScene::drawFluid()
{
    ofPushMatrix();
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    
        AppManager::getInstance().getFloorManager().draw();
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
        m_fluid.draw();
    
    ofPopStyle();
    ofPopMatrix();
    
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