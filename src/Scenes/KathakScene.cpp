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
    
    this->setupFbos();
    this->setupShaders();
    this->setupWaterRipples();
    
    ofLogNotice("KathakScene::setup");
    
}

void KathakScene::setupFbos()
{
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    m_fboMask.allocate(windowsSettings.width, windowsSettings.height);
    
    ImageVisual gradientMask = ImageVisual(ofPoint(windowsSettings.width*0.5, windowsSettings.height*0.5), "floor_mask", true );
    gradientMask.setHeight(windowsSettings.height, true);
    if(windowsSettings.height>windowsSettings.width){
        gradientMask.setHeight(windowsSettings.width,true);
    }
    
    m_fboMask.begin();
        ofClear(0);
        gradientMask.draw();
    m_fboMask.end();
    
    m_drawArea = ofRectangle(0, 0, windowsSettings.width, windowsSettings.height);
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

void KathakScene::setupWaterRipples()
{
    ofSetCircleResolution(100);
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    
    ofImage waterBackground;
    waterBackground.allocate(windowsSettings.width, windowsSettings.height, OF_IMAGE_GRAYSCALE);
    
    
    ofFbo waterBackgroundFbo;
    waterBackgroundFbo.allocate(windowsSettings.width, windowsSettings.height);
    waterBackgroundFbo.begin(); ofBackground(0, 0, 255); waterBackgroundFbo.end();
    
    m_water.loadBackground(waterBackgroundFbo);
    m_water.setDensity(0.97);
    
}

void KathakScene::update()
{
    this->updateWaterRipples();
}


void KathakScene::draw() {
    ofBackground(0,0,0);
    
    //m_maskShader.begin();
    //m_maskShader.setUniformTexture("imageMask", m_fboMask.getTextureReference(), 1);

        this->drawWaterRipples();
    //m_maskShader.end();
    

}

void KathakScene::updateWaterRipples()
{
    auto volume = AppManager::getInstance().getAudioManager().getAudioMax();
    auto position = AppManager::getInstance().getFloorManager().getPosition();
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    auto minSize = AppManager::getInstance().getFloorManager().getKathakMinSize();
    auto maxSize = AppManager::getInstance().getFloorManager().getKathakMaxSize();
    auto lineWidth = AppManager::getInstance().getFloorManager().getKathakLineWidth();
    
    //auto radius = ofMap(volume, 0.0, 1.0, minSize, maxSize);
    auto radius = ofMap(volume, 0.0, 1.0, minSize, windowsSettings.height*0.3);
    
    position.x *= windowsSettings.width;
    position.y *= windowsSettings.height;
    
    //ofLogNotice() << "KathakScene::updateWaterDrops: " << volume;
    
    m_water.begin();
        ofNoFill();
        ofSetLineWidth(lineWidth);
        ofColor color = ofColor::lightSeaGreen;
        color.setSaturation( 50 + ofNoise( ofGetFrameNum() ) * 255 );
        ofSetColor(color);
        //ofSetColor(ofNoise( ofGetFrameNum() ) * 255 * 5, 255);
        //ofSetColor(ofColor::blue);
    
       // float radius = ofMap(volume, 0.0, 1.0, 70, windowsSettings.height/2.5);
        ofCircle(position, radius);
        //ofCircle(ofGetMouseX(), ofGetMouseY(), radius);
    m_water.end();
    
    m_water.update();

}


void KathakScene::drawWaterRipples()
{
    m_water[1].draw(0,0);
    //m_water.draw(0,0);
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