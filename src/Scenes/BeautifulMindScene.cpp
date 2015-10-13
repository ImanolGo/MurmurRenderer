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


BeautifulMindScene::BeautifulMindScene(): m_initialized(false), m_sceneNumber(0), m_elapsedTime(0.0f), m_elapsedTimeSecondary(0.0f), m_sceneNumberSecondary(0)
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
    
    this->setupFbo();
    this->setupVideo();
    //this->setupScenes();
    
    ofLogNotice("BeautifulMindScene::setup");
    
}

void BeautifulMindScene::setupFbo()
{
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    m_fbo.allocate(windowsSettings.width, windowsSettings.height);
}

void BeautifulMindScene::setupVideo()
{
    string videoFileName = "videos/BeautifulMind.mov";
    m_video.setResource(videoFileName);
    m_video.setWidth(m_fbo.getWidth()); m_video.setHeight(m_fbo.getHeight());
    m_video.setLoopState(OF_LOOP_NORMAL);
}

void BeautifulMindScene::setupScenes()
{
    this->setupScene1();
    this->setupScene2();
    this->setupScene3();
    this->setupScene4();
}

void BeautifulMindScene::setupScene1()
{
    
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    
    string resourceName = "scene_01_BLURRED_FRONT";
    ofPoint position = ofPoint(0,0,0);
    
    ofPtr<ImageVisual> image = ofPtr<ImageVisual>(new ImageVisual(position,resourceName));
    image->setHeight(windowsSettings.height); image->setWidth(windowsSettings.width);
    m_images[resourceName] = image;
    
    resourceName = "scene_01_BLURRED_MIDDLE";
    image = ofPtr<ImageVisual>(new ImageVisual(position,resourceName));
    image->setHeight(windowsSettings.height); image->setWidth(windowsSettings.width);
    m_images[resourceName] = image;
    
    
    resourceName = "scene_01_BLURRED_REAR";
    image = ofPtr<ImageVisual>(new ImageVisual(position,resourceName));
    image->setHeight(windowsSettings.height); image->setWidth(windowsSettings.width);
    m_images[resourceName] = image;
    
}

void BeautifulMindScene::setupScene2()
{
    
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    
    string resourceName = "scene_02_CANVAS_BG";
    ofPoint position = ofPoint(0,0,0);
    
    ofPtr<ImageVisual> image = ofPtr<ImageVisual>(new ImageVisual(position,resourceName));
    image->setHeight(windowsSettings.height); image->setWidth(windowsSettings.width);
    m_images[resourceName] = image;
    
    resourceName = "scene_02_img1_FRONT";
    image = ofPtr<ImageVisual>(new ImageVisual(position,resourceName));
    image->setHeight(windowsSettings.height); image->setWidth(windowsSettings.width);
    m_images[resourceName] = image;
    
    resourceName = "scene_02_img2_FRONT";
    image = ofPtr<ImageVisual>(new ImageVisual(position,resourceName));
    image->setHeight(windowsSettings.height); image->setWidth(windowsSettings.width);
    m_images[resourceName] = image;
    
    resourceName = "scene_02_img3_FRONT";
    image = ofPtr<ImageVisual>(new ImageVisual(position,resourceName));
    image->setHeight(windowsSettings.height); image->setWidth(windowsSettings.width);
    m_images[resourceName] = image;
    
    resourceName = "scene_02_img4_FRONT";
    image = ofPtr<ImageVisual>(new ImageVisual(position,resourceName));
    image->setHeight(windowsSettings.height); image->setWidth(windowsSettings.width);
    m_images[resourceName] = image;

}

void BeautifulMindScene::setupScene3()
{
    
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    
    string resourceName = "scene_03_REAR";
    ofPoint position = ofPoint(0,0,0);
    
    ofPtr<ImageVisual> image = ofPtr<ImageVisual>(new ImageVisual(position,resourceName));
    image->setHeight(windowsSettings.height); image->setWidth(windowsSettings.width);
    m_images[resourceName] = image;
    
    resourceName = "scene_03_FRONT";
    image = ofPtr<ImageVisual>(new ImageVisual(position,resourceName));
    image->setHeight(windowsSettings.height); image->setWidth(windowsSettings.width);
    m_images[resourceName] = image;
    
    resourceName = "scene_03_MIDDLE";
    image = ofPtr<ImageVisual>(new ImageVisual(position,resourceName));
    image->setHeight(windowsSettings.height); image->setWidth(windowsSettings.width);
    m_images[resourceName] = image;
    
}

void BeautifulMindScene::setupScene4()
{
    
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    
    string resourceName = "scene_04_FRONT";
    ofPoint position = ofPoint(0,0,0);
    
    ofPtr<ImageVisual> image = ofPtr<ImageVisual>(new ImageVisual(position,resourceName));
    image->setHeight(windowsSettings.height); image->setWidth(windowsSettings.width);
    m_images[resourceName] = image;
    
    resourceName = "scene_04_MIDDLE";
    image = ofPtr<ImageVisual>(new ImageVisual(position,resourceName));
    image->setHeight(windowsSettings.height); image->setWidth(windowsSettings.width);
    m_images[resourceName] = image;
    
    resourceName = "scene_04_REAR";
    image = ofPtr<ImageVisual>(new ImageVisual(position,resourceName));
    image->setHeight(windowsSettings.height); image->setWidth(windowsSettings.width);
    m_images[resourceName] = image;
    
    resourceName = "scene_04_MIDDLE_SAIL_1";
    image = ofPtr<ImageVisual>(new ImageVisual(position,resourceName));
    image->setHeight(windowsSettings.height); image->setWidth(windowsSettings.width);
    m_images[resourceName] = image;
    
    resourceName = "scene_04_MIDDLE_SAIL_2";
    image = ofPtr<ImageVisual>(new ImageVisual(position,resourceName));
    image->setHeight(windowsSettings.height); image->setWidth(windowsSettings.width);
    m_images[resourceName] = image;
    
    resourceName = "scene_04_MIDDLE_SAIL_3";
    image = ofPtr<ImageVisual>(new ImageVisual(position,resourceName));
    image->setHeight(windowsSettings.height); image->setWidth(windowsSettings.width);
    m_images[resourceName] = image;

}


void BeautifulMindScene::nextScene()
{
    m_sceneNumber = (m_sceneNumber+1)%NUMBER_SCENES;
    this->setScene(m_sceneNumber);
}

void BeautifulMindScene::setScene(int sceneNumber)
{
    if ( sceneNumber < 0 || sceneNumber >= NUMBER_SCENES) {
        return;
    }
    
    m_sceneNumber = sceneNumber;
    
    this->resetTimeValues();
    this->fadeOutVisuals();
    this->startCurrentScene();
    
}


void BeautifulMindScene::resetSecondaryScene()
{
    
    switch (m_sceneNumber)
    {
        case 1:
            m_sceneNumberSecondary = NUMBER_SCENES_IN_SCENE_02 - 1;
            m_elapsedTimeSecondary = 0;
            m_durationSecondary = m_duration/4.0;
            break;
        
        case 3:
            m_sceneNumberSecondary = NUMBER_SCENES_IN_SCENE_04 - 1;
            m_elapsedTimeSecondary = 0;
            m_durationSecondary = 2;
            break;
            
        default:
            break;
    }
}


void BeautifulMindScene::fadeOutVisuals()
{
    for (auto image: m_images) {
        AppManager::getInstance().getVisualEffectsManager().createFadeEffect(image.second, 0.0, 0.0, FADE_TIME);
    }
    
}

void BeautifulMindScene::resetTimeValues()
{
    m_elapsedTime = 0.0f;
    m_duration = AppManager::getInstance().getBeautifulMindManager().getTiming(m_sceneNumber);
    
    this->resetSecondaryScene();
}

void BeautifulMindScene::startCurrentScene()
{
    string resourceName = "scene_0" + ofToString(m_sceneNumber+1);
    ofLogNotice() << "BeautifulMindScene::startCurrentScene: " << resourceName;
    for (auto image: m_images) {
        if (ofIsStringInString(image.first, resourceName)) {
            AppManager::getInstance().getVisualEffectsManager().removeAllVisualEffects(image.second);
            AppManager::getInstance().getVisualEffectsManager().createFadeEffect(image.second, 255, 0.0, FADE_TIME);
        }
        
    }
    
    int secondarySceneId = 1;
    if(m_sceneNumber==secondarySceneId){
        this->nextSecondaryScene();
    }
    
}


void BeautifulMindScene::updateScene1()
{
    
    float xPos = ofMap(sin(ofGetElapsedTimef()*0.3), -1, 1, -40, 0);
    float yPos = ofMap(sin(ofGetElapsedTimef()*0.2), -1, 1, -29, 0);
    string resourceName = "scene_01_BLURRED_FRONT";
    auto position = m_images[resourceName]->getPosition();
    position.x = xPos; position.y = yPos;
    m_images[resourceName]->setPosition(position);
    
    
    xPos = ofMap(sin(ofGetElapsedTimef()*0.31 + 0.5), -1, 1, 40, 0);
    yPos = ofMap(sin(ofGetElapsedTimef()*0.21+ 0.5), -1, 1, 29, 0);
    resourceName = "scene_01_BLURRED_MIDDLE";
    position = m_images[resourceName]->getPosition();
    position.x = xPos; position.y = yPos;
    m_images[resourceName]->setPosition(position);
    
}

void BeautifulMindScene::updateScene2()
{
    m_elapsedTimeSecondary += ofGetLastFrameTime();
    if(m_elapsedTimeSecondary >= m_durationSecondary){
        this->nextSecondaryScene();
    }

    
    float xPos = ofMap(sin(ofGetElapsedTimef()*0.3), -1, 1, -40, 0);
    float yPos = ofMap(sin(ofGetElapsedTimef()*0.2), -1, 1, -29, 0);
    string resourceName = "scene_02_img1_FRONT";
    auto position = m_images[resourceName]->getPosition();
    position.x = xPos; position.y = yPos;
    m_images[resourceName]->setPosition(position);
    
    resourceName = "scene_02_img2_FRONT";
    m_images[resourceName]->setPosition(position);
    
    resourceName = "scene_02_img3_FRONT";
    m_images[resourceName]->setPosition(position);
    
    resourceName = "scene_02_img4_FRONT";
    m_images[resourceName]->setPosition(position);
    
}

void BeautifulMindScene::nextSecondaryScene()
{
    
    m_elapsedTimeSecondary = 0.0f;
    
    
    switch (m_sceneNumber)
    {
        case 1:
        {
            m_sceneNumberSecondary = (m_sceneNumberSecondary + 1)%NUMBER_SCENES_IN_SCENE_02;
            string resourceName = "scene_02_img";
            for (auto image: m_images) {
                if (ofIsStringInString(image.first, resourceName)) {
                    AppManager::getInstance().getVisualEffectsManager().removeAllVisualEffects(image.second);
                    AppManager::getInstance().getVisualEffectsManager().createFadeEffect(image.second, 0, 0.0, FADE_TIME);
                }
                
            }
            
            resourceName = "scene_02_img" + ofToString(m_sceneNumberSecondary+1);
            // ofLogNotice() << "BeautifulMindScene::nextSecondaryScene: " << resourceName;
            for (auto image: m_images) {
                if (ofIsStringInString(image.first, resourceName)) {
                    AppManager::getInstance().getVisualEffectsManager().removeAllVisualEffects(image.second);
                    AppManager::getInstance().getVisualEffectsManager().createFadeEffect(image.second, 255, 0.0, FADE_TIME);
                }
                
            }
            
            break;

        }
            
        case 3:
        {
           
            m_sceneNumberSecondary = (m_sceneNumberSecondary + 1)%NUMBER_SCENES_IN_SCENE_04;
            string resourceName = "scene_04_MIDDLE_SAIL_";
            for (auto image: m_images) {
                if (ofIsStringInString(image.first, resourceName)) {
                    AppManager::getInstance().getVisualEffectsManager().removeAllVisualEffects(image.second);
                    AppManager::getInstance().getVisualEffectsManager().createFadeEffect(image.second, 0, 0.0, m_durationSecondary);
                }
                
            }
            
            resourceName = "scene_04_MIDDLE_SAIL_" + ofToString(m_sceneNumberSecondary+1);
            //ofLogNotice() << "BeautifulMindScene::nextSecondaryScene: " << resourceName;
            for (auto image: m_images) {
                if (ofIsStringInString(image.first, resourceName)) {
                    AppManager::getInstance().getVisualEffectsManager().removeAllVisualEffects(image.second);
                    AppManager::getInstance().getVisualEffectsManager().createFadeEffect(image.second, 255, 0.0, m_durationSecondary);
                }
                
            }

            break;
        }
            
            
        default:
            break;
    }
    
}

void BeautifulMindScene::updateScene3()
{
    
    float xPos = ofMap(sin(ofGetElapsedTimef()*0.3), -1, 1, -40, 0);
    float yPos = ofMap(sin(ofGetElapsedTimef()*0.2), -1, 1, -29, 0);
    string resourceName = "scene_03_FRONT";
    auto position = m_images[resourceName]->getPosition();
    position.x = xPos; position.y = yPos;
    m_images[resourceName]->setPosition(position);
    
    
    xPos = ofMap(sin(ofGetElapsedTimef()*0.31 + 0.5), -1, 1, 40, 0);
    yPos = ofMap(sin(ofGetElapsedTimef()*0.21+ 0.5), -1, 1, 29, 0);
    resourceName = "scene_03_MIDDLE";
    position = m_images[resourceName]->getPosition();
    position.x = xPos; position.y = yPos;
    m_images[resourceName]->setPosition(position);
    
}

void BeautifulMindScene::updateScene4()
{
    m_elapsedTimeSecondary += ofGetLastFrameTime();
    if(m_elapsedTimeSecondary >= m_durationSecondary){
        this->nextSecondaryScene();
    }
    
    float xPos = ofMap(sin(ofGetElapsedTimef()*0.4), -1, 1, -40, 0);
    float yPos = ofMap(sin(ofGetElapsedTimef()*0.3), -1, 1, -29, 0);
    string resourceName = "scene_04_MIDDLE";
    auto position = m_images[resourceName]->getPosition();
    position.x = xPos; position.y = yPos;
    m_images[resourceName]->setPosition(position);
    
    resourceName = "scene_04_MIDDLE_SAIL_1";
    m_images[resourceName]->setPosition(position);
    
    resourceName = "scene_04_MIDDLE_SAIL_2";
    m_images[resourceName]->setPosition(position);
    
    resourceName = "scene_04_MIDDLE_SAIL_3";
    m_images[resourceName]->setPosition(position);
    

    yPos = ofMap(sin(ofGetElapsedTimef()*0.27+ 0.5), -1, 1, 29, 0);
    resourceName = "scene_04_REAR";
    position = m_images[resourceName]->getPosition();
    position.y = yPos;
    m_images[resourceName]->setPosition(position);
    
}

void BeautifulMindScene::update() {
    
    
    this->updateVideo();
    
    
    /*
    m_elapsedTime += ofGetLastFrameTime();
    if(m_elapsedTime >= m_duration){
        this->nextScene();
    }
    
    switch (m_sceneNumber) {
        case 0:
            this->updateScene1();
            break;
        case 1:
            this->updateScene2();
            break;
        case 2:
            this->updateScene3();
            break;
        case 3:
            this->updateScene4();
            break;
            
        default:
            break;
    }*/
    
    m_fbo.begin();
        this->drawScene();
    m_fbo.end();
}

void BeautifulMindScene::updateVideo()
{
    m_video.update();
}


void BeautifulMindScene::draw() {
   
    ofBackground(0,0,0);
    m_fbo.draw(getDrawingArea());
}

void BeautifulMindScene::drawScene() {
    
    /*
    ofBackground(0,0,0);
  
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    for (auto image: m_images) {
        image.second->draw();
    }
     
    m_video.draw();
     
    ofPopStyle();
    */
    
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
    
    //rect.x = AppManager::getInstance().getLayoutManager().getCropLeft();
    //rect.y = AppManager::getInstance().getLayoutManager().getCropTop();
    //rect.width = ofGetWidth() - AppManager::getInstance().getLayoutManager().getCropLeft() - AppManager::getInstance().getLayoutManager().getCropRight();
    //rect.height = ofGetHeight() - AppManager::getInstance().getLayoutManager().getCropTop() - AppManager::getInstance().getLayoutManager().getCropBottom();
    
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