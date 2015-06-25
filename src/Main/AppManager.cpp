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
    
    this->setupOF();
	this->setupManagers();
    this->setupGlfwWidows();
    
    setDebugMode(m_debugMode);
}

void AppManager::setupOF()
{
    ofLogNotice() << "AppManager::setupOF";
    
    ofSetVerticalSync(true);
    ofSetEscapeQuitsApp(false);
}
void AppManager::setupGlfwWidows()
{
    ofLogNotice() << "AppManager::setupGlfwWidows";
    
    //ofVbo::disableVAOs();
    
    m_glfw = (ofxMultiGLFWWindow*)ofGetWindowPtr();
    
    // vector of windows, count set in main
    m_windows = &m_glfw->windows;
    
    WindowSettingsVector windowSettingsVector = AppManager::getInstance().getSettingsManager().getWindowsSettings();
    
    int i = 0;
    for(auto windowSettings : windowSettingsVector) {
        ofLogNotice() << "AppManager::setupGlfwWidows -> creating window: " << i;
        
        if(i>1){
            m_glfw->createWindow();
        }
      
        m_glfw->setWindow(m_windows->at(i));    // set window pointer
        m_glfw->initializeWindow();       // initialize events (mouse, keyboard, etc) on window (optional)
        ofSetWindowPosition(windowSettings.x, windowSettings.y);    // business as usual...
        ofSetWindowShape(windowSettings.width, windowSettings.height);
        ofSetWindowTitle(windowSettings.title);
        ofSetFullscreen(windowSettings.fullscreen);        // order important with fullscreen
        
        if(windowSettings.showCursor){
            ofShowCursor();
        }
        else{
            ofHideCursor();
        }

        i++;
    }
    
    
    m_glfw->setWindow(m_windows->at(0));
    
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



