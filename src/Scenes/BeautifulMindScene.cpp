/*
 *  BeautifulMindScene.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 02/07/15.
 *
 */


#include "AppManager.h"
#include "BeautifulMindScene.h"



BeautifulMindScene::BeautifulMindScene(): m_initialized(false)
{
    //! Intentionally left empty
}


BeautifulMindScene::~BeautifulMindScene()
{
    //! Intentionally left empty
}


void BeautifulMindScene::setup() {
    
    if(m_initialized){
        return;
    }
    
    m_initialized = true;
    
    this->setupImages();
    this->setupFbos();
    this->setupVideo();
    this->setupShader();

    ofLogNotice("BeautifulMindScene::setup");
    
}

void BeautifulMindScene::setupFbos()
{
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    m_fboVideo.allocate(windowsSettings.width, windowsSettings.height,GL_RGB);
    m_fboVideo.begin(); ofClear(0, 0, 0);  ; m_fboVideo.end();
    
}

void BeautifulMindScene::setupImages()
{
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    
    string resourceName = "frame_mask";
    ofPoint position = ofPoint(0,0,0);
    
    ofPtr<ImageVisual> image = ofPtr<ImageVisual>(new ImageVisual(position,resourceName));
     image->setWidth(windowsSettings.width); image->setHeight(windowsSettings.height);
    m_images[resourceName] = image;
    
    resourceName = "calibration_image";
    image = ofPtr<ImageVisual>(new ImageVisual(position,resourceName));
    image->setHeight(windowsSettings.height); image->setWidth(windowsSettings.width);
    m_images[resourceName] = image;
    
}


void BeautifulMindScene::setupShader()
{
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    
    m_mask.setup(windowsSettings.width, windowsSettings.height, ofxMaskAddon::LUMINANCE);
    this->setupMask();
}


void BeautifulMindScene::setupMask()
{
    // creating masker texture
    m_mask.beginMask();
        ofClear(0, 0, 0);
        m_images["frame_mask"]->draw();
    // draw masker here in gray scale
    m_mask.endMask();
}

void BeautifulMindScene::setupVideo()
{
    string videoFileName = "videos/BeautifulMind.mov";
    m_video.setResource(videoFileName);
    m_video.setWidth(m_fboVideo.getWidth()); m_video.setHeight(m_fboVideo.getHeight());
    m_video.setLoopState(OF_LOOP_NORMAL);
}



void BeautifulMindScene::update()
{
    this->updateVideo();
    this->updateMask();
}

void BeautifulMindScene::updateVideo()
{
    m_video.update();
    
    auto area = getDrawingArea();
    m_video.setHeight(area.height); m_video.setWidth(area.width);
    ofVec2f pos(area.x,area.y);
    m_video.setPosition(pos);
    
    m_fboVideo.begin();
        ofClear(0, 0, 0);
        m_video.draw();
    m_fboVideo.end();

}


void BeautifulMindScene::updateMask()
{
    string resourceName = "frame_mask";
    
    auto area = getDrawingArea();
    m_images[resourceName]->setHeight(area.height); m_images[resourceName]->setWidth(area.width);
    ofVec2f pos(area.x,area.y);
    
    m_images[resourceName]->setPosition(pos);
    
    this->setupMask();
}



void BeautifulMindScene::draw() {
   
    ofBackground(0,0,0);
    
    bool calibration = AppManager::getInstance().getBeautifulMindManager().isCalibrationOn();
    
    if(calibration){
        this->drawCalibration();
    }
    else{
        this->drawScene();
    }
    
   
}

void BeautifulMindScene::drawScene()
{
    // creating maskee texture
    m_mask.begin();
    // draw maskee here
        this->drawVideo();
    m_mask.end();
    
    // draw result
    m_mask.draw();
    
    //m_video.draw();
    
    //this->drawVideo();
}

void BeautifulMindScene::drawCalibration()
{
    string resourceName = "calibration_image";
    
    auto area = getDrawingArea();
    m_images[resourceName]->setHeight(area.height); m_images[resourceName]->setWidth(area.width);
    ofVec2f pos(area.x,area.y);
    
    m_images[resourceName]->setPosition(pos);
    
    m_images[resourceName]->draw();

}

void BeautifulMindScene::drawVideo() {
    
    m_fboVideo.draw(0,0);
}

ofRectangle BeautifulMindScene::getDrawingArea()
{
    auto rect = AppManager::getInstance().getBeautifulMindManager().getRectangleSpace();
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    
    rect.x *= windowsSettings.width;
    rect.width *= windowsSettings.width;
    rect.y *= windowsSettings.height;
    rect.height *= windowsSettings.height;
    
    return rect;
}

void BeautifulMindScene::willFadeIn() {
     ofLogNotice("BeautifulMindScene::willFadeIn");
    
     m_video.stop();
     m_video.setFrame(0);
     m_video.play();
    
}

void BeautifulMindScene::willDraw() {
    ofLogNotice("BeautifulMindScene::willDraw");
}

void BeautifulMindScene::willFadeOut() {
    ofLogNotice("BeautifulMindScene::willFadeOut");
}

void BeautifulMindScene::willExit() {
    ofLogNotice("BeautifulMindScene::willExit");
    
    m_video.stop();
}