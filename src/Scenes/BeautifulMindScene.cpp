/*
 *  BeautifulMindScene.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 02/07/15.
 *
 */


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
    
    ofLogNotice("BeautifulMindScene::setup");
    
}

void BeautifulMindScene::update() {
    
}

void BeautifulMindScene::draw() {
    ofBackground(40,0,0);
}

void BeautifulMindScene::willFadeIn() {
     ofLogNotice("BeautifulMindScene::willFadeIn");
}

void BeautifulMindScene::willDraw() {
    ofLogNotice("BeautifulMindScene::willDraw");
}

void BeautifulMindScene::willFadeOut() {
    ofLogNotice("BeautifulMindScene::willFadeOut");
}

void BeautifulMindScene::willExit() {
    ofLogNotice("BeautifulMindScene::willExit");
}