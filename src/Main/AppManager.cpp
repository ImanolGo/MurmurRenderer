/*
 *  AppManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 17/06/15.
 *
 */

#include "ofMain.h"


#include "AppManager.h"

AppManager& AppManager::getInstance()
{
	// The only instance
	// Guaranteed to be lazy initialized
	// Guaranteed that it will be destroyed correctly
	static AppManager    m_instance;
    return m_instance;

}

AppManager::AppManager(): Manager(), m_debugMode(true)
{
    //Intentioanlly left empty
}


AppManager::~AppManager()
{
    ofLogNotice() <<"AppManager::Destructor";
}


void AppManager::setup()
{
	if(m_initialized)
		return;

    ofLogNotice() << "AppManager::initialized";

	Manager::setup();
    
    this->setupGlfwWidows();
	this->setupManagers();
    
    setDebugMode(m_debugMode);
}

void AppManager::setupGlfwWidows()
{
    ofLogNotice() << "AppManager::setupGlfwWidows";
    
    ofSetVerticalSync(true);
    
    //ofVbo::disableVAOs();
    
    m_glfw = (ofxMultiGLFWWindow*)ofGetWindowPtr();
    
    // vector of windows, count set in main
    m_windows = &m_glfw->windows;
    
    // configure first window
    m_glfw->setWindow(m_windows->at(0));    // set window pointer
    m_glfw->initializeWindow();       // initialize events (mouse, keyboard, etc) on window (optional)
    ofSetWindowPosition(0, 100);    // business as usual...
    ofSetWindowShape(600, 800);
    ofSetWindowTitle("Murmur Renderer GUI");
    ofShowCursor();
    //ofSetFullscreen(true);        // order important with fullscreen
    
    
    // configure second window
    m_glfw->setWindow(m_windows->at(1));
    m_glfw->initializeWindow();
    ofSetWindowPosition(500, 100);
    ofSetWindowShape(500, 800);
    ofSetWindowTitle("Murmur Renderer Front Projection");
    ofHideCursor();
    //ofSetFullscreen(true);        // order important with fullscreen
    
    
    // create third window dynamically
    m_glfw->createWindow();
    m_glfw->setWindow(m_windows->at(2));
    m_glfw->initializeWindow();
    ofSetWindowPosition(500+500, 100);
    ofSetWindowShape(500, 800);
    ofSetWindowTitle("Murmur Renderer Top Projection");
    ofHideCursor();
    //ofSetFullscreen(true);        // order important with fullscreen
    
    m_glfw->setWindow(m_windows->at(0));
    ofShowCursor();
    
}


void AppManager::setupManagers()
{
    ofLogNotice() << "AppManager::setupManagers";
    
    m_viewManager.setup();
    m_visualEffectsManager.setup();
    m_settingsManager.setup();
    m_layoutManager.setup();
    m_oscManager.setup();
    m_keyboardManager.setup();
    m_guiManager.setup();
}

void AppManager::update()
{
    m_visualEffectsManager.update();
    m_oscManager.update();
}


void AppManager::draw()
{
    // draw is called once on each window every frame
    
    // the window index will increment
    int wIndex = m_glfw->getWindowIndex();
    
    switch (wIndex) { // switch on window index
        case 0:
            ofBackground(0,0,0); // change background color on each window
            m_guiManager.draw();
            //m_viewManager.draw();
            break;
        case 1:
            ofBackground(0,255,0); // change background color on each window
            break;
        case 2:
            ofBackground(0,0,255); // change background color on each window
            
            break;
    }

}

void AppManager::toggleDebugMode()
{
    m_debugMode = !m_debugMode;
    setDebugMode(m_debugMode);
}


void AppManager::setDebugMode(bool showDebug)
{
    m_debugMode = showDebug;
    
    ofLogNotice()<<"AppManager::setDebugMode-> " << m_debugMode;
    
    if(m_debugMode){
        //ofSetLogLevel(OF_LOG_VERBOSE);
    }
    else{
        ofSetLogLevel(OF_LOG_NOTICE);
    }
    
    m_guiManager.showGui(m_debugMode);

}



