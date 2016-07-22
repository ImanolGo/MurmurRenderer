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

const float ProjectorCalibrationScene::LINE_THICKNESS = 5.0;


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
    m_thickLineShader.setGeometryInputType(GL_LINES);
    m_thickLineShader.setGeometryOutputType(GL_TRIANGLE_STRIP);
    m_thickLineShader.setGeometryOutputCount(4);
    
    
    if(ofIsGLProgrammableRenderer()){
        m_thickLineShader.load("shaders/shadersGL3/ThickLineShaderVert.glsl", "shaders/shadersGL3/ThickLineShaderFrag.glsl", "shaders/shadersGL3/ThickLineShaderGeom.glsl");
    }
    else{
        m_thickLineShader.load("shaders/shadersGL2/ThickLineShaderVert.glsl", "shaders/shadersGL2/ThickLineShaderFrag.glsl", "shaders/shadersGL2/ThickLineShaderGeom.glsl");
    }
    
    printf("Maximum number of output vertices support is: %i\n", m_thickLineShader.getGeometryMaxOutputCount());
    
}

void ProjectorCalibrationScene::update()
{
    /// Intentionally left empty
}


void ProjectorCalibrationScene::drawTestPattern()
{
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    float ratio = windowsSettings.width / windowsSettings.height;
    float tileSize = windowsSettings.width/16;
    float rectSize = 3;
    
    ofPushStyle();
    ofSetCircleResolution(100);
            m_thickLineShader.begin();
            m_thickLineShader.setUniform1f("thickness", LINE_THICKNESS);
                ofSetColor(ofColor::white);
                ofSetLineWidth(LINE_THICKNESS);
                ofLine(windowsSettings.width*0.5, 0, windowsSettings.width*0.5, windowsSettings.height);
                ofLine(0, windowsSettings.height*0.5, windowsSettings.width, windowsSettings.height*0.5);
    
                ofLine(LINE_THICKNESS*0.5, 0, LINE_THICKNESS*0.5, windowsSettings.height);
                ofLine(0, LINE_THICKNESS*0.5, windowsSettings.width, LINE_THICKNESS*0.5);
                ofLine(windowsSettings.width - LINE_THICKNESS*0.5, 0, windowsSettings.width - LINE_THICKNESS*0.5, windowsSettings.height);
                ofLine(0,  windowsSettings.height - LINE_THICKNESS*0.5, windowsSettings.width,  windowsSettings.height - LINE_THICKNESS*0.5);
    
            m_thickLineShader.end();
    
            ofSetColor(ofColor::white);
            ofSetLineWidth(1.0);
            for(int i = 0; i <= 16; i++)
            {
                ofLine(i*tileSize, 0, i*tileSize, windowsSettings.height);
                ofLine(0, i*tileSize, windowsSettings.width, i*tileSize);
                
                for(int j = 0; j <= 16; j++){
                    
                    float x = i*tileSize + tileSize*0.5 - rectSize*0.5;
                    float y = j*tileSize + tileSize*0.5 - rectSize*0.5;
                    
                    ofRect(x, y, rectSize, rectSize);
                }
                
            }
    
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