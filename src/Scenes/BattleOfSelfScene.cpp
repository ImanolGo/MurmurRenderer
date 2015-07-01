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
    
    m_initialized = true;
    
    ofLogNotice("BattleOfSelfScene::setup");
    
}

void BattleOfSelfScene::setupShaders()
{
    m_shader.setGeometryInputType(GL_LINES);
    m_shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
    m_shader.setGeometryOutputCount(4);
    m_shader.load("shaders/shadersGL3/BattleOfSelfVert.glsl", "shaders/shadersGL3/BattleOfSelfFrag.glsl", "shaders/shadersGL3/BattleOfSelfGeom.glsl");
    
    ofLogNotice() << "BattleOfSelfScene::setupShaders -> Geometry Max Output Count: " << m_shader.getGeometryMaxOutputCount();
    
}

void BattleOfSelfScene::update()
{
    ///
}


void BattleOfSelfScene::draw() {
    ofBackground(0,50,0);
    this->drawVisuals();
}


void BattleOfSelfScene::drawVisuals()
{
    m_shader.begin();
    //m_shader.setUniform1f("nshift", 0);
    //m_shader.setUniform1f("thick", 0.03);
    ofLine(0, 0, 200, 200);
    AppManager::getInstance().getContourManager().draw();
    m_shader.end();
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