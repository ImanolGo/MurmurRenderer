/*
 *  SceneManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 25/06/15.
 *
 */

#include "ofMain.h"


#include "SceneManager.h"
#include "BlankScene.h"
#include "SmokyHandsScene.h"


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

    this->createSceneManagers();
    this->createScenes();

    ofLogNotice() <<"SceneManager::initialized";

}

void SceneManager::createSceneManagers()
{
    m_sceneManagers[WindowIndex(FRONT)] = ofPtr<ofxSceneManager> (new ofxSceneManager());
    m_sceneManagers[WindowIndex(FRONT)]->setTransitionDissolve();
    
    m_sceneManagers[WindowIndex(TOP)] = ofPtr<ofxSceneManager> (new ofxSceneManager());
    m_sceneManagers[WindowIndex(TOP)]->setTransitionDissolve();
}


void SceneManager::createScenes()
{
    this->createFrontScenes();
    this->createTopScenes();
}

void SceneManager::createFrontScenes()
{
    int i = 0;
    ofPtr<ofxScene> scene;
    
    //Create Blank Scene
    scene = ofPtr<ofxScene> (new BlankScene());
    this->createScene("BlankScene", SceneIndex(i), scene, WindowIndex(FRONT));
    i++;
    
    //Create Smoky Hands Scene
    scene = ofPtr<ofxScene> (new SmokyHandsScene());
    this->createScene("SmokyHandsScene", SceneIndex(i), scene, WindowIndex(FRONT));
    i++;
    
}

void SceneManager::createScene(string name, SceneIndex i, ofPtr<ofxScene> ofx_scene, WindowIndex w)
{
    ofPtr<Scene> scene = ofPtr<Scene> (new Scene());
    
    scene->index = i;
    scene->name = name;
    scene->window_index = w;
    scene->scene = ofx_scene;
    m_scenes.push_back(scene);
    
    ofLogNotice() <<"SceneManager::createScene -> name =  " << name << ", scene index = " << i << ", window index = " << w ;
    
    this->addSceneToSceneManager(scene, w);
}


bool SceneManager::addSceneToSceneManager(ofPtr<Scene> scene, WindowIndex w)
{
    if(m_sceneManagers.find(w)!= m_sceneManagers.end()){
        m_sceneManagers[w]->addScene(scene->scene);
        ofLogNotice() <<"SceneManager::addSceneToSceneManager -> Added  "<< scene->name << " to Scene Manager " << w;
        return true;
    }
    
    
    ofLogNotice() <<"SceneManager::addSceneToSceneManager -> No Scene Manager attached to window " << w;
    return false;
}
  


void SceneManager::createTopScenes()
{
    
    int i = 0;
    ofPtr<ofxScene> scene;
    
    //Create Blank Scene
    scene = ofPtr<ofxScene> (new BlankScene());
    this->createScene("BlankScene", SceneIndex(i), scene, WindowIndex(TOP));
    i++;
}


bool SceneManager::run(WindowIndex w)
{
    if(m_sceneManagers.find(w)!= m_sceneManagers.end()){
        m_sceneManagers[w]->run();
        ofLogNotice() <<"SceneManager::runSceneManager -> Running Scene Manager attached to window " << w;
        return true;
    }
    
    ofLogNotice() <<"SceneManager::runSceneManager -> No Scene Manager attached to window " << w;
    return false;
}

void SceneManager::update()
{
     for(auto sceneManager : m_sceneManagers) {
         sceneManager.second->update();
     }
}

void SceneManager::draw(WindowIndex w)
{
    if(m_sceneManagers.find(w)!= m_sceneManagers.end()){
        m_sceneManagers[w]->draw();
        return;
    }
    
    ofLogVerbose() <<"SceneManager::draw -> No Scene Manager attached to window " << w;
}


bool SceneManager::changeScene(string sceneName)
{
    bool sceneFound = false;
    
    for(auto scene : m_scenes) {
        
        if(scene->name == sceneName && m_sceneManagers.find(scene->window_index)!= m_sceneManagers.end()){
            sceneFound = true;
            m_sceneManagers[scene->window_index]->changeScene((int) scene->index);
        }
    }
    
    
    if(sceneFound){
        ofLogNotice() <<"SceneManager::changeScene -> Changed to scene  " << sceneName;
        return true;
    }
    else{
        ofLogNotice() <<"SceneManager::changeScene -> No scene found with name  " << sceneName;
        return false;
    }
   
}



