/*
 *  BattleOfSelfScene.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 30/06/15.
 *
 */


#include "AppManager.h"
#include "ContourManager.h"

#include "BattleOfSelfScene.h"


BattleOfSelfScene::BattleOfSelfScene():m_initialized(false)
{
    
}

BattleOfSelfScene::~BattleOfSelfScene()
{
    //Intentionally left empty
}

void BattleOfSelfScene::setup()
{
    if (m_initialized) {
        return;
    }
    
    this->setupFbos();
    this->setupPostProcessing();
    
    //this->setupShaders();
    
    m_sonicBoomVisual.setup();
    
    m_fluid.setup("xmls/BattleOfSelfFluid.xml");
    m_initialized = true;
    
    ofLogNotice("BattleOfSelfScene::setup");
    
}

void BattleOfSelfScene::setupFbos()
{
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    
    m_drawArea = ofRectangle(0, 0, windowsSettings.width, windowsSettings.height);
    
    m_fbo.allocate(windowsSettings.width, windowsSettings.height);
    m_fbo.begin(); ofClear(0); m_fbo.end();
    
}



void BattleOfSelfScene::setupShaders()
{
    
    if(ofIsGLProgrammableRenderer()){
        m_shader.load("shaders/shadersGL3/LiquifyShader");
    }
    else{
        m_shader.load("shaders/shadersGL2/LiquifyShader");
        
    }
}

void BattleOfSelfScene::setupPostProcessing()
{
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    
    // Setup post-processing chain
    m_postProcessing.init(windowsSettings.width, windowsSettings.height);
    m_postProcessing.createPass<FxaaPass>()->setEnabled(true);
    //m_postProcessing.createPass<BloomPass>()->setEnabled(true);
    
    //ofPtr<ZoomBlurPass> zoomBlurPass =  m_postProcessing.createPass<ZoomBlurPass>();
    //zoomBlurPass->setDensity(0.5);
    //zoomBlurPass->setEnabled(true);
    
    ofPtr<NoiseWarpPass> noisePass =  m_postProcessing.createPass<NoiseWarpPass>();
    noisePass->setAmplitude(0.01);
    noisePass->setSpeed(0.3);
    noisePass->setFrequency(5);
    noisePass->setEnabled(true);
    
    
    //m_postProcessing.createPass<ZoomBlurPass>()->setEnabled(true);
    //m_postProcessing.createPass<NoiseWarpPass>()->setEnabled(true);
}

void BattleOfSelfScene::update()
{
    this->updateFluid();
    this->updateSonicBoom();
}


void BattleOfSelfScene::updateFluid()
{
    auto source = AppManager::getInstance().getContourManager().getSource();
    
    //source = m_sonicBoomVisual.getFbo();
    m_fluid.setSource(source);
    m_fluid.update();
}


void BattleOfSelfScene::updateSonicBoom()
{
    m_sonicBoomVisual.update();
}

void BattleOfSelfScene::draw() {
    
    //ofLogNotice("BattleOfSelfScene::draw");

    ofClear(0, 0, 0);
    ofPushStyle();
        ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    
        this->drawSonicBoom();
    
        ofEnableBlendMode(OF_BLENDMODE_ADD);

        this->drawFluid();
    
    ofPopStyle();
    
}


void BattleOfSelfScene::drawSonicBoom()
{
    if (m_sonicBoomVisual.empty()) {
        return;
    }
    
    m_postProcessing.begin();
    //ofPushStyle();
    ofPushMatrix();
        ofScale(1, -1);
        ofTranslate(0, -m_fbo.getHeight());
        m_sonicBoomVisual.draw();
    
    ofPopMatrix();
    m_postProcessing.end();
    //ofPopStyle();
    //ofDisableAlphaBlending();
}

void BattleOfSelfScene::drawFluid()
{
    
    ofSetColor(160,160,255);
    m_fluid.draw(m_drawArea);
    return;
    
    ofPushStyle();
    //ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    ofEnableAlphaBlending();
    
    m_fbo.begin();
    
    //ofClear(0, 0, 0);
    
    ofSetColor(0,0,0);
    ofRect(0,0,m_fbo.getWidth(),m_fbo.getHeight());
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetColor(120,120,255);
    m_fluid.draw(m_drawArea);
    
    m_fbo.end();
    ofDisableAlphaBlending();
    ofPopStyle();
    
    m_fbo.draw(0,0);
    
    //m_fluid.drawGui();
    
}


void BattleOfSelfScene::willFadeIn() {
    ofLogNotice("BattleOfSelfScene::willFadeIn");
    
    m_sonicBoomVisual.clear();
    m_fluid.reset();
    AppManager::getInstance().getGuiManager().setHandsOn(false);
    
    AppManager::getInstance().getGuiManager().setContourThickness(0.25);
}

void BattleOfSelfScene::willDraw() {
    ofLogNotice("BattleOfSelfScene::willDraw");
}

void BattleOfSelfScene::willFadeOut() {
    ofLogNotice("BattleOfSelfScene::willFadeOut");
}

void BattleOfSelfScene::willExit() {
    ofLogNotice("BattleOfSelfScene::willExit");
    
    m_sonicBoomVisual.clear();
    m_fluid.reset();
}