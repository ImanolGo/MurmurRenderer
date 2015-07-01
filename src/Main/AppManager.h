/*
 *  AppManager.h
 *  Murmur
 *
 *  Created by Imanol Gomez on 17/06/15.
 *
 */

#pragma once

#include "ofMain.h"

#include "Manager.h"
#include "ofxMultiGLFWWindow.h"

#include "SettingsManager.h"
#include "LayoutManager.h"
#include "GuiManager.h"
#include "ResourceManager.h"
#include "VisualEffectsManager.h"
#include "ViewManager.h"
#include "KeyboardManager.h"
#include "OscManager.h"
#include "SceneManager.h"
#include "ContourManager.h"
#include "HandsManager.h"
#include "UdpManager.h"

//========================== class AppManager ==============================
//============================================================================
/** \class AppManager AppManager.h
 *	\brief Class managing the whole application
 *	\details it set-ups, updates and renders all the different managers used for the application
 */

class AppManager: public Manager
{
public:

    //! Destructor
    ~AppManager();

    //! Returns the singleton instance.
    static AppManager& getInstance();

    //! Compares two transition objects
    void setup();

    //! updates the logic
    void update();

    //! calls the view manager to draw
    void draw();

    //==========================================================================

    //! Returns the settings manager
    SettingsManager& getSettingsManager() { return m_settingsManager; }
    
    //! Returns the GUI manager
    GuiManager&  getGuiManager() { return m_guiManager; }
    
    //! Returns the resource manager
    ResourceManager&  getResourceManager() { return m_resourceManager; }
    
    //! Returns the view manager
    ViewManager&  getViewManager() { return m_viewManager; }
    
    //! Returns the visual effects manager
    VisualEffectsManager&  getVisualEffectsManager() { return m_visualEffectsManager; }
    
    //! Returns the  keyboard manager
    KeyboardManager&  getKeyboardManager() { return m_keyboardManager; }
    
    //! Returns the  OSC manager
    OscManager&  getOscManager() { return m_oscManager; }
    
    //! Returns the  Scene Manager
    SceneManager&  getSceneManager() { return m_sceneManager; }
    
    //! Returns the  Contour Manager
    ContourManager&  getContourManager() { return m_contourManager; }
    
    //! Returns the  Hands Manager
    HandsManager&  getHandsManager() { return m_handsManager; }
    
    //! Returns the  Udp Manager
    UdpManager&  getUdpManager() { return m_udpManager; }

    
    //==========================================================================
    
    void toggleDebugMode();
    
    void setDebugMode(bool showDebug);
    

private:

     //! Constructor
     AppManager();

	//! Stop the compiler generating methods of copy the object
	 AppManager(AppManager const& copy);              // Don't Implement

    //! Prevent operator= being generated.
     AppManager& operator=(AppManager const& copy);     // Don't implement

    //==========================================================================

    //! Set-up all the managers
    void setupManagers();

    //! Set-up OpenFrameworks
    void setupOF();
    
    //! Set-up GLFW windows
    void setupGlfwWidows();

    //! update all the managers
    void updateManagers();


private:
    
    ofxMultiGLFWWindow*             m_glfw;                     ///< Pointer to the multi-GLFW window
    vector<GLFWwindow*>*            m_windows;                  ///< Pointer the vector holding all the GLFW windows

    SettingsManager                 m_settingsManager;          ///< Manages the application's settings
    LayoutManager                   m_layoutManager;            ///< Manages the layoutx
    GuiManager                      m_guiManager;               ///< Manages the graphical user interface
    ResourceManager                 m_resourceManager;          ///< Manages the resources
    ViewManager                     m_viewManager;              ///< Manages the visuals
    VisualEffectsManager            m_visualEffectsManager;     ///< Manages the visual effects
    OscManager                      m_oscManager;               ///< Manages the OSC messages
    KeyboardManager                 m_keyboardManager;          ///< Manages the keboard input
    SceneManager                    m_sceneManager;             ///< Manages all the scenes
    ContourManager                  m_contourManager;           ///< Manages the contour coming from the camera
    HandsManager                    m_handsManager;             ///< Manages the hand information coming from the laser ranger
    UdpManager                      m_udpManager;               ///< Manages the UDP messages

    bool                            m_debugMode;
};

//==========================================================================


