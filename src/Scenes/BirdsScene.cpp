/*
 *  BirdsScene.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 05/08/15.
 *
 */

#include "AppManager.h"

#include "BirdsScene.h"

void BirdsScene::setup() {
    ofLogNotice("BirdsScene::setup");
}


void BirdsScene::update() {
    
    //AppManager::getInstance().getBirdsManager().update();
}

void BirdsScene::draw() {
    ofBackground(0,0,0);
    AppManager::getInstance().getBirdsManager().draw();
}

void BirdsScene::willFadeIn() {
     ofLogNotice("BirdsScene::willFadeIn");
}

void BirdsScene::willDraw() {
    ofLogNotice("BirdsScene::willDraw");
}

void BirdsScene::willFadeOut() {
    ofLogNotice("BirdsScene::willFadeOut");
}

void BirdsScene::willExit() {
    ofLogNotice("BirdsScene::willExit");
}