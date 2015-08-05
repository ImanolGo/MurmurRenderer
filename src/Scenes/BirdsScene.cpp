/*
 *  BirdsScene.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 05/08/15.
 *
 */


#include "BirdsScene.h"

void BirdsScene::setup() {
    ofLogNotice("BirdsScene::setup");
}

void BirdsScene::update() {
    
}

void BirdsScene::draw() {
    ofBackground(0,0,0);
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