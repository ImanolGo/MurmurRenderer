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
    
	Manager::setup();
    
    this->setupOF();
	this->setupManagers();
    this->setupMultipleWidows();
    m_guiManager.setup();
    
    setDebugMode(m_debugMode);
    
    ofLogNotice() << "AppManager::initialized";
}

void AppManager::setupOF()
{
    ofLogNotice() << "AppManager::setupOF";
    
    ofSetVerticalSync(true);
    ofSetEscapeQuitsApp(false);
}
void AppManager::setupMultipleWidows()
{
    
    m_glfw = (ofxMultiGLFWWindow*)ofGetWindowPtr();
    
    WindowSettingsVector windowSettingsVector = AppManager::getInstance().getSettingsManager().getWindowsSettings();
    
    m_windows = &m_glfw->windows;
    
    int i = 0;
    for(auto windowSettings : windowSettingsVector) {
        ofLogNotice() << "AppManager::setupMultipleWidows -> creating window: " << i;
        
        m_glfw->undecorate(windowSettings.fullscreen);
        if (i>0) {
            m_glfw->createWindow(windowSettings.width, windowSettings.height);
        }
        m_glfw->setWindow(m_windows->at(i));    // set window pointer
        m_glfw->initializeWindow();       // initialize events (mouse, keyboard, etc) on window (optional)
        m_glfw->setWindowPosition(windowSettings.x, windowSettings.y);
        //m_glfw->setWindowShape(windowSettings.width, windowSettings.height);
        //m_glfw->undecorate(windowSettings.fullscreen);
        //ofSetWindowPosition(windowSettings.x, windowSettings.y);    // business as usual...
        //ofSetWindowShape(windowSettings.width, windowSettings.height);
        ofSetWindowTitle(windowSettings.title);
       
        //ofSetFullscreen(windowSettings.fullscreen);        // order important with fullscreen
        //ofLogNotice() << "AppManager::setupGlfwWidows -> width = " << ofGetWidth() << ", height = " << ofGetHeight();
        
        if(windowSettings.showCursor){
            ofShowCursor();
        }
        else{
            ofHideCursor();
        }
        
        m_sceneManager.run(WindowIndex(i));
        
        i++;
    }
    
    // vector of windows, count set in main
    m_windows = &m_glfw->windows;
    m_glfw->setWindow(m_windows->at(0));
}


void AppManager::setupManagers()
{
    ofLogNotice() << "AppManager::setupManagers";
    
    m_viewManager.setup();
    m_visualEffectsManager.setup();
    m_settingsManager.setup();
    m_resourceManager.setup();
    m_layoutManager.setup();
    m_contourManager.setup();
    m_handsManager.setup();
    m_floorManager.setup();
    m_beautifulMindManager.setup();
    m_oscManager.setup();
    m_udpManager.setup();
    m_sceneManager.setup();
    m_audioManager.setup();
    m_keyboardManager.setup();
}

void AppManager::update()
{
    m_audioManager.update();
    m_oscManager.update();
    m_udpManager.update();
    m_visualEffectsManager.update();
    m_contourManager.update();
    m_sceneManager.update();
    m_handsManager.update();
}


void AppManager::draw()
{
    int wIndex = m_glfw->getWindowIndex();
    
    //glfwWindowHint(GLFW_DECORATED, false);
    //m_glfw->undecorate(true);
    
    switch (wIndex) { // switch on window index
        case 0:
            ofBackground(0,0,0); // change background color on each window
            m_viewManager.draw();
            m_sceneManager.draw(WindowIndex(wIndex));
            m_audioManager.draw();
            m_guiManager.draw();
            break;
        case 1:
            ofBackground(0,0,0); // change background color on each window
            m_sceneManager.draw(WindowIndex(wIndex));
            m_layoutManager.draw();
            break;
        case 2:
            ofBackground(0,0,0); // change background color on each window
            m_sceneManager.draw(WindowIndex(wIndex));
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

void AppManager::setFullScreen(bool& value)
{
}



