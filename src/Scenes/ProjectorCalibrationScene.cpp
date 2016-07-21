/*
 *  ProjectorCalibrationScene.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 20/07/16.
 *
 */


#include "AppManager.h"
#include "ContourManager.h"
#include "SettingsManager.h"

#include "ProjectorCalibrationScene.h"


ProjectorCalibrationScene::ProjectorCalibrationScene():m_initialized(false)
{
    
}

ProjectorCalibrationScene::~ProjectorCalibrationScene()
{
    //Intentionally left empty
}

void ProjectorCalibrationScene::setup()
{
    if (m_initialized) {
        return;
    }
    
    m_initialized = true;
    
    this->setupFbos();
    this->setupShaders();
    
    ofLogNotice("ProjectorCalibrationScene::setup");
    
}

void ProjectorCalibrationScene::setupFbos()
{
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    m_fboTestPattern.allocate(windowsSettings.width, windowsSettings.height);
    
    m_fboTestPattern.begin();
        ofClear(0);
        this->drawTestPattern();
    m_fboTestPattern.end();
    
}


void ProjectorCalibrationScene::setupShaders()
{
    if(ofIsGLProgrammableRenderer()){
        m_thickLineShader.load("shaders/shadersGL3/ThickLineShaderFrag");
    }
    else{
        m_thickLineShader.load("shaders/shadersGL2/ThickLineShaderFrag");
    }
    
}

void ProjectorCalibrationScene::update()
{
    /// Intentionally left empty
}


void ProjectorCalibrationScene::drawTestPattern()
{
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    
    ofPushStyle();
        ofSetColor(ofColor::yellow);
            ofLine(windowsSettings.width*0.5, 0, windowsSettings.width*0.5, windowsSettings.height);
            ofLine(0, windowsSettings.height*0.5, windowsSettings.width, windowsSettings.height*0.5);
    ofPopStyle();
}

void ProjectorCalibrationScene::draw() {
    ofBackground(0,0,0);
    m_fboTestPattern.draw(0, 0);
}



void ProjectorCalibrationScene::willFadeIn() {
    AppManager::getInstance().getLayoutManager().setIsMasked(false);
    ofLogNotice("ProjectorCalibrationScene::willFadeIn");
}

void ProjectorCalibrationScene::willDraw() {
    ofLogNotice("ProjectorCalibrationScene::willDraw");
}

void ProjectorCalibrationScene::willFadeOut() {
    AppManager::getInstance().getLayoutManager().setIsMasked(true);
    ofLogNotice("ProjectorCalibrationScene::willFadeOut");
}

void ProjectorCalibrationScene::willExit() {
    ofLogNotice("ProjectorCalibrationScene::willExit");
    
}