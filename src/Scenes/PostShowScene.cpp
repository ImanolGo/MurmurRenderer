/*
 *  PostShowScene.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 21/10/15.
 *
 */


#include "PostShowScene.h"
#include "AppManager.h"

void PostShowScene::setup() {
    ofLogNotice("PostShowScene::setup");
    
    this->setupImages();
}

void PostShowScene::setupImages() {
   
    string imageName = "postshow";
    m_image.setResource(imageName);
    m_image.setCentred(true);

}

void PostShowScene::update() {
    
}

void PostShowScene::draw() {
    ofBackground(0,0,0);
    this->drawImages();
}

void PostShowScene::drawImages() {
    ofRectangle rect = this->getDrawingArea();
    m_image.setHeight(rect.getHeight());
    m_image.setPosition(rect.getCenter());
    m_image.draw();
}

void PostShowScene::willFadeIn() {
     ofLogNotice("PostShowScene::willFadeIn");
}

void PostShowScene::willDraw() {
    ofLogNotice("PostShowScene::willDraw");
}

void PostShowScene::willFadeOut() {
    ofLogNotice("PostShowScene::willFadeOut");
}

void PostShowScene::willExit() {
    ofLogNotice("PostShowScene::willExit");
}

ofRectangle PostShowScene::getDrawingArea()
{
    auto rect = AppManager::getInstance().getBeautifulMindManager().getRectangleSpace();
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    
    rect.x *= windowsSettings.width;
    rect.width *= windowsSettings.width;
    rect.y *= windowsSettings.height;
    rect.height *= windowsSettings.height;
    
    return rect;
}