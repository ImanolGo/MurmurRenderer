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
    m_shader.load("shaders/shadersGL4/BattleOfSelfVert.glsl", "shaders/shadersGL4/BattleOfSelfFrag.glsl", "shaders/shadersGL4/BattleOfSelfGeom.glsl");
    
    ofLogNotice() << "BattleOfSelfScene::setupShaders -> " << m_shader.getGeometryMaxOutputCount();
    
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