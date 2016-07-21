/*
 *  ProjectorCalibrationSceneFloor.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 20/07/16.
 *
 */


#include "AppManager.h"
#include "ContourManager.h"
#include "SettingsManager.h"

#include "ProjectorCalibrationSceneFloor.h"


ProjectorCalibrationSceneFloor::ProjectorCalibrationSceneFloor():m_initialized(false)
{
    
}

ProjectorCalibrationSceneFloor::~ProjectorCalibrationSceneFloor()
{
    //Intentionally left empty
}

void ProjectorCalibrationSceneFloor::setup()
{
    if (m_initialized) {
        return;
    }
    
    m_initialized = true;
    
    this->setupFbos();
    this->setupShaders();
    
    ofLogNotice("ProjectorCalibrationSceneFloor::setup");
    
}

void ProjectorCalibrationSceneFloor::setupFbos()
{
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    m_fboTestPattern.allocate(windowsSettings.width, windowsSettings.height);
    
    m_fboTestPattern.begin();
        ofClear(0);
        this->drawTestPattern();
    m_fboTestPattern.end();
}

void ProjectorCalibrationSceneFloor::setupShaders()
{
    if(ofIsGLProgrammableRenderer()){
        m_thickLineShader.load("shaders/shadersGL3/ThickLineShaderFrag");
    }
    else{
        m_thickLineShader.load("shaders/shadersGL2/ThickLineShaderFrag");
    }
    
}

void ProjectorCalibrationSceneFloor::update()
{
    //Intenionally left empty
}


void ProjectorCalibrationSceneFloor::draw() {
    ofBackground(0,0,0);
    m_fboTestPattern.draw(0, 0);
}


void ProjectorCalibrationSceneFloor::drawTestPattern()
{
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    
    ofPushStyle();
        ofSetColor(ofColor::yellow);
            ofLine(windowsSettings.width*0.5, 0, windowsSettings.width*0.5, windowsSettings.height);
            ofLine(0, windowsSettings.height*0.5, windowsSettings.width, windowsSettings.height*0.5);
    ofPopStyle();
}

void ProjectorCalibrationSceneFloor::willFadeIn() {
    ofLogNotice("ProjectorCalibrationSceneFloor::willFadeIn");
}

void ProjectorCalibrationSceneFloor::willDraw() {
    ofLogNotice("ProjectorCalibrationSceneFloor::willDraw");
}

void ProjectorCalibrationSceneFloor::willFadeOut() {
    ofLogNotice("ProjectorCalibrationSceneFloor::willFadeOut");
}

void ProjectorCalibrationSceneFloor::willExit() {
    ofLogNotice("ProjectorCalibrationSceneFloor::willExit");
}