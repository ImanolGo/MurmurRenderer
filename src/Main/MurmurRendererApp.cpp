/*
 *  MurmurRendererApp.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 19/06/15.
 *
 */

#include "AppManager.h"

#include "MurmurRendererApp.h"

//--------------------------------------------------------------
void MurmurRendererApp::setup(){
    AppManager::getInstance().setup();
}

//--------------------------------------------------------------
void MurmurRendererApp::update(){
    AppManager::getInstance().update();
}

//--------------------------------------------------------------
void MurmurRendererApp::draw(){
    AppManager::getInstance().draw();
}

void MurmurRendererApp::exit()
{
    ofLogNotice() <<"MurmurRenderer::Exit";

}


