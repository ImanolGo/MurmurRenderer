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
    
    WindowSettingsVector windowSettingsVector = AppManager::getInstance().getWindowSettingsManager().getWindowsSettings();
    
    m_windows = &m_glfw->windows;
    
    int i = 0;
    for(auto windowSettings : windowSettingsVector) {
        ofLogNotice() << "AppManager::setupMultipleWidows -> creating window: " << i;
        
        m_glfw->undecorate(windowSettings.fullscreen);
       // m_glfw->hideBorder();
        if (i>0) {
            m_glfw->createWindow(windowSettings.width, windowSettings.height);
        }
        m_glfw->setWindow(m_windows->at(i));    // set window pointer
        
        m_glfw->initializeWindow();       // initialize events (mouse, keyboard, etc) on window (optional)
        
        //m_glfw->setWindowShape(windowSettings.width, windowSettings.height);
        
        if (i>0) {
            m_glfw->setWindowShape(windowSettings.width, windowSettings.height);
        }
        
        m_glfw->setWindowPosition(windowSettings.x, windowSettings.y);
        //m_glfw->undecorate(windowSettings.fullscreen);
        //ofSetWindowPosition(windowSettings.x, windowSettings.y);    // business as usual...
        //ofSetWindowShape(windowSettings.width, windowSettings.height);
        ofSetWindowTitle(windowSettings.title);
       
        //ofSetFullscreen(windowSettings.fullscreen);        // order important with fullscreen
        //ofLogNotice() << "AppManager::setupGlfwWidows -> width = " << ofGetWidth() << ", height = " << ofGetHeight();
        
        if(windowSettings.showCursor){
            m_glfw->showCursor();
        }
        else{
            m_glfw->hideCursor();
        }
        
        m_sceneManager.run(WindowIndex(i));
        
        i++;
    }
    
    // vector of windows, count set in main
    m_windows = &m_glfw->windows;
    m_glfw->setWindow(m_windows->at(0));
    
    auto windowSettings = AppManager::getInstance().getSettingsManager().getWindowsSettings(0);
    m_glfw->setWindowShape(windowSettings.width, windowSettings.height);
   
    if(windowSettings.showCursor){
         m_glfw->showCursor();
    }
    else{
         m_glfw->hideCursor();
    }
    
}


void AppManager::setupManagers()
{
    ofLogNotice() << "AppManager::setupManagers";
    
    m_windowSettingsManager.setup();
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
    m_birdsManager.setup();
    m_midiManager.setup();
    m_previewManager.setup();
    m_maskManager.setup();
}

void AppManager::update()
{
    m_audioManager.update();
    m_oscManager.update();
    m_udpManager.update();
    m_visualEffectsManager.update();
    m_contourManager.update();
    m_birdsManager.update();
    m_sceneManager.update();
    m_handsManager.update();
}


void AppManager::draw()
{
    int wIndex = m_glfw->getWindowIndex();
    
    switch (wIndex) { // switch on window index
        case 0:
            ofBackground(0,0,0); // change background color on each window
            
            if (m_debugMode) {
                m_viewManager.draw();
                m_sceneManager.draw(WindowIndex(wIndex));
                m_previewManager.draw();
                m_guiManager.draw();
                m_audioManager.draw();
            }
           
            break;
        case 1:
            m_previewManager.begin(wIndex);
                ofBackground(0,0,0); // change background color on each window
                ofClear(0, 0, 0);
                m_maskManager.begin(wIndex);
           
                    //ofRect(0, 0, image.getWidth(), image.getHeight());
                    m_sceneManager.draw(WindowIndex(wIndex));
                    m_layoutManager.draw();
                m_maskManager.end(wIndex);
            
            m_previewManager.end(wIndex);
            m_previewManager.draw(wIndex);
            break;
        case 2:
            m_previewManager.begin(wIndex);
                ofBackground(0,0,0); // change background color on each window
                m_maskManager.begin(wIndex);
                    m_sceneManager.draw(WindowIndex(wIndex));
                m_maskManager.end(wIndex);
            m_previewManager.end(wIndex);
            m_previewManager.draw(wIndex);
            break;
    }
}

void AppManager::toggleDebugMode()
{
    m_debugMode = !m_debugMode;
    setDebugMode(m_debugMode);
    //m_viewManager.showDebugMode(m_debugMode);
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
    
   // m_guiManager.showGui(m_debugMode);

}

void AppManager::setFullScreen(bool& value)
{
}



