/*
 *  SceneManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 25/06/15.
 *
 */

#include "ofMain.h"


#include "SceneManager.h"


SceneManager::SceneManager(): Manager()
{
	//Intentionally left empty
}


SceneManager::~SceneManager()
{
    ofLogNotice() <<"SceneManager::Destructor";
}


void SceneManager::setup()
{
	if(m_initialized)
		return;

	Manager::setup();

    this->createScenes();

    ofLogNotice() <<"SceneManager::initialized";

}


void SceneManager::createScenes()
{
    ///To implement in case we have scenes
}

void SceneManager::update()
{
    
}

void SceneManager::draw()
{
    
}
