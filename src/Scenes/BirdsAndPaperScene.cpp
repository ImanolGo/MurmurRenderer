/*
 *  BirdsAndPaperScene.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 22/09/15.
 *
 */

#include "AppManager.h"

#include "BirdsAndPaperScene.h"

void BirdsAndPaperScene::setup() {
    ofLogNotice("BirdsAndPaperScene::setup");
}


void BirdsAndPaperScene::update() {
    
    //AppManager::getInstance().getBirdsManager().update();
}

void BirdsAndPaperScene::draw() {
    ofBackground(0,0,0);
    AppManager::getInstance().getBirdsManager().draw();
}

void BirdsAndPaperScene::willFadeIn() {
     ofLogNotice("BirdsAndPaperScene::willFadeIn");
}

void BirdsAndPaperScene::willDraw() {
    ofLogNotice("BirdsAndPaperScene::willDraw");
}

void BirdsAndPaperScene::willFadeOut() {
    ofLogNotice("BirdsAndPaperScene::willFadeOut");
}

void BirdsAndPaperScene::willExit() {
    ofLogNotice("BirdsAndPaperScene::willExit");
}