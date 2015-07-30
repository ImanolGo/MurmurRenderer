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
    
    this->setupShaders();
    this->setupPostProcessing();
    
    m_fluid.setup("xmls/BattleOfSelfFluid.xml");
    m_initialized = true;
    
    ofLogNotice("BattleOfSelfScene::setup");
    
}

void BattleOfSelfScene::setupShaders()
{
    m_shader.setGeometryInputType(GL_LINES);
    m_shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
    m_shader.setGeometryOutputCount(24);
    m_shader.load("shaders/shadersGL3/BattleOfSelfVert.glsl", "shaders/shadersGL3/BattleOfSelfFrag.glsl", "shaders/shadersGL3/BattleOfSelfGeom.glsl");
    
    
    ofLogNotice() << "BattleOfSelfScene::setupShaders -> Geometry Max Output Count: " << m_shader.getGeometryMaxOutputCount();
    
}

void BattleOfSelfScene::setupPostProcessing()
{
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    
    // Setup post-processing chain
    m_postProcessing.init(windowsSettings.width, windowsSettings.height);
    m_postProcessing.createPass<FxaaPass>()->setEnabled(true);
    m_postProcessing.createPass<BloomPass>()->setEnabled(true);
}

void BattleOfSelfScene::update()
{
    this->updateFluid();
}


void BattleOfSelfScene::updateFluid()
{
    auto source = AppManager::getInstance().getContourManager().getSource();
    m_fluid.setSource(source);
    m_fluid.update();
}


void BattleOfSelfScene::draw() {
    ofBackground(0,0,0);
    this->drawVisuals();
}


void BattleOfSelfScene::drawVisuals()
{
    // copy enable part of gl state
    glPushAttrib(GL_ENABLE_BIT);
    
    // setup gl state
    //glEnable(GL_DEPTH_TEST);
   // glEnable(GL_CULL_FACE);
    
    // begin scene to post process
    m_postProcessing.begin();
    
        AppManager::getInstance().getContourManager().draw();
    
    // end scene and draw
    m_postProcessing.end();
    
    // set gl state back to original
    glPopAttrib();
    
    //m_filter->begin();
        //AppManager::getInstance().getContourManager().draw();
    //m_filter->end();
    //m_shader.begin();
    //m_shader.setUniform1f("nshift", 0);
    //m_shader.setUniform1f("thick", 0.03);
    //ofLine(0, 0, 200, 200);
    
    //m_shader.end();
}

void BattleOfSelfScene::drawFluid()
{
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    
    AppManager::getInstance().getContourManager().draw();
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    m_fluid.draw();
    //m_fluid.drawGui();
    ofPopStyle();
    
}


void BattleOfSelfScene::willFadeIn() {
    ofLogNotice("BattleOfSelfScene::willFadeIn");
}

void BattleOfSelfScene::willDraw() {
    ofLogNotice("BattleOfSelfScene::willDraw");
}

void BattleOfSelfScene::willFadeOut() {
    ofLogNotice("BattleOfSelfScene::willFadeOut");
}

void BattleOfSelfScene::willExit() {
    ofLogNotice("BattleOfSelfScene::willExit");
}