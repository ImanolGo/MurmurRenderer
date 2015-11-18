/*
 *  BeautifulMindScene.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 02/07/15.
 *
 */


#include "AppManager.h"
#include "BeautifulMindScene.h"

const int BeautifulMindScene::NUMBER_SCENES = 4;
const float BeautifulMindScene::FADE_TIME = 2.0f;
const int BeautifulMindScene::NUMBER_SCENES_IN_SCENE_02 = 4;
const int BeautifulMindScene::NUMBER_SCENES_IN_SCENE_04 = 3;


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
    this->setupShaders();
    
    ofLogNotice("BeautifulMindScene::setup");
    
}

void BeautifulMindScene::setupFbos()
{
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    m_fboMask.allocate(windowsSettings.width, windowsSettings.height,GL_RGB);
    m_fboMask.begin(); ofClear(0, 0, 0); m_images["frame_mask"]->draw(); m_fboMask.end();
    
    
    m_fboVideo.allocate(windowsSettings.width, windowsSettings.height,GL_RGB);
    m_fboVideo.begin(); ofClear(0, 0, 0); m_fboVideo.end();
}

void BeautifulMindScene::setupImages()
{
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    
    string resourceName = "frame_mask";
    ofPoint position = ofPoint(0,0,0);
    
    ofPtr<ImageVisual> image = ofPtr<ImageVisual>(new ImageVisual(position,resourceName));
    image->setHeight(windowsSettings.height); image->setWidth(windowsSettings.width);
    m_images[resourceName] = image;
    
    resourceName = "calibration_image";
    image = ofPtr<ImageVisual>(new ImageVisual(position,resourceName));
    image->setHeight(windowsSettings.height); image->setWidth(windowsSettings.width);
    m_images[resourceName] = image;
    
}


void BeautifulMindScene::setupShaders()
{
    if(ofIsGLProgrammableRenderer()){
        m_maskShader.load("shaders/shadersGL3/BlackMask");
    }
    else{
        m_maskShader.load("shaders/shadersGL2/BlackMask");
    }
    
}

void BeautifulMindScene::setupVideo()
{
    string videoFileName = "videos/BeautifulMind.mp4";
    m_video.setResource(videoFileName);
    m_video.setWidth(m_fboMask.getWidth()); m_video.setHeight(m_fboMask.getHeight());
    m_video.setLoopState(OF_LOOP_NORMAL);
}



void BeautifulMindScene::update()
{
    this->updateVideo();
}

void BeautifulMindScene::updateVideo()
{
    m_video.update();
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
    m_fboVideo.begin();
        ofClear(0, 0, 0);
        m_maskShader.begin();
        m_maskShader.setUniformTexture("imageMask", m_fboMask.getTextureReference(), 1);
    
            this->drawVideo();
            //m_fboMask.draw(0,0);
        m_maskShader.end();
    m_fboVideo.end();
    
    m_fboVideo.draw(getDrawingArea());
    //m_fboVideo.draw(0,0);
    //m_fboMask.draw(0,0);
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
    
    m_video.draw();
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
    
    /*
    for (auto image: m_images) {
        image.second->setAlpha(0);
    }
    
     this->setScene(0);
    */
    
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