/*
 *  KathakScene.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 30/07/15.
 *
 */


#include "AppManager.h"
#include "ContourManager.h"
#include "SettingsManager.h"
#include "ofxWater.h"

#include "KathakScene.h"


KathakScene::KathakScene():m_initialized(false)
{
    
}

KathakScene::~KathakScene()
{
    //Intentionally left empty
}

void KathakScene::setup()
{
    if (m_initialized) {
        return;
    }
    
    m_initialized = true;
    
    m_fluid.setup("xmls/FluidFloor.xml");
    
    this->setupFbos();
    this->setupShaders();
    this->setupWaterDrops();
    
    ofLogNotice("KathakScene::setup");
    
}

void KathakScene::setupFbos()
{
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    m_fboMask.allocate(windowsSettings.width, windowsSettings.height);
    
    ImageVisual gradientMask = ImageVisual(ofPoint(windowsSettings.width*0.5, windowsSettings.height*0.5), "floor_mask", true );
    
    m_fboMask.begin();
        ofClear(0);
        gradientMask.draw();
    m_fboMask.end();
}

void KathakScene::setupShaders()
{
    if(ofIsGLProgrammableRenderer()){
        m_maskShader.load("shaders/shadersGL3/BlackMask");
    }
    else{
        m_maskShader.load("shaders/shadersGL2/BlackMask");
    }
    
}

void KathakScene::setupWaterDrops()
{
    ofSetCircleResolution(100);
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    
    ofImage waterBackground;
    waterBackground.allocate(windowsSettings.width, windowsSettings.height, OF_IMAGE_GRAYSCALE);
    m_water.loadBackground(waterBackground);
    m_water.setDensity(0.95);
    
}

void KathakScene::update()
{
    this->updateFluid();
    this->updateWaterDrops();
}


void KathakScene::draw() {
    ofBackground(0,0,0);
    
    m_maskShader.begin();
    m_maskShader.setUniformTexture("imageMask", m_fboMask.getTextureReference(), 1);
        AppManager::getInstance().getHandsManager().draw();
        this->drawFluid();
        this->drawWaterDrops();
    m_maskShader.end();
    
    m_fluid.drawGui();

}

void KathakScene::updateFluid()
{
    auto floorPosition = AppManager::getInstance().getFloorManager().getPosition();
    
    m_fluid.addForce(floorPosition);
    m_fluid.update();
}

void KathakScene::updateWaterDrops()
{
    float volume = AppManager::getInstance().getAudioManager().getMaxSound();
    auto position = AppManager::getInstance().getFloorManager().getPosition();
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    
    //ofLogNotice() << "KathakScene::updateWaterDrops: " << volume;
    
    m_water.begin();
        ofNoFill();
        ofSetLineWidth(10);
        ofSetColor(ofNoise( ofGetFrameNum() ) * 255 * 5, 255);
        float radius = ofMap(volume, 0.0, 1.0, 30, windowsSettings.height/3);
        //ofCircle(position, radius);
        ofCircle(ofGetMouseX(), ofGetMouseY(), radius);
    m_water.end();
    
    m_water.update();

}




void KathakScene::drawFluid()
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

void KathakScene::drawWaterDrops()
{
    ofPushStyle();
        ofSetColor(ofColor::blue);
        m_water[1].draw(0,0);
    ofPopStyle();
}


void KathakScene::willFadeIn() {
    ofLogNotice("KathakScene::willFadeIn");
}

void KathakScene::willDraw() {
    ofLogNotice("KathakScene::willDraw");
}

void KathakScene::willFadeOut() {
    ofLogNotice("KathakScene::willFadeOut");
}

void KathakScene::willExit() {
    ofLogNotice("KathakScene::willExit");
}