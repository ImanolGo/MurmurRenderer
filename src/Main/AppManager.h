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
#include "FloorManager.h"
#include "BeautifulMindManager.h"
#include "AudioManager.h"
#include "BirdsManager.h"
#include "MidiManager.h"
#include "PreviewManager.h"
#include "MaskManager.h"
#include "ProjectorsManager.h"

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

    //! Returns the layout manager
    LayoutManager& getLayoutManager() { return m_layoutManager; }
    
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
    
    //! Returns the Floor Manager
    FloorManager&  getFloorManager() { return m_floorManager; }
    
    //! Returns the Beautiful Mind Manager
    BeautifulMindManager&  getBeautifulMindManager() { return m_beautifulMindManager; }
    
    //! Returns the Audio Manager
    AudioManager&  getAudioManager() { return m_audioManager; }
    
    //! Returns the Birds Manager
    BirdsManager&  getBirdsManager() { return m_birdsManager; }
    
    //! Returns the Midi Manager
    MidiManager&  getMidiManager() { return m_midiManager; }
    
    //! Returns the Preview Manager
    PreviewManager&  getPreviewManager() { return m_previewManager; }
    
    //! Returns the Mask Manager
    MaskManager&  getMaskManager() { return m_maskManager; }
    
    //! Returns the projectors Manager
    ProjectorsManager&  getProjectorsManager() { return m_projectorsManager; }
    
    //==========================================================================
    
    void toggleDebugMode();
    
    void setDebugMode(bool showDebug);
    
    bool getDebugMode() const {return m_debugMode;}
    
    void setFullScreen(bool& value);
    

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
    
    //! Set-up windows
    void setupMultipleWidows();

    //! update all the managers
    void updateManagers();
    
    void checkMasks();


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
    FloorManager                    m_floorManager;             ///< Manages the floor tracking position coming from the top camera
    HandsManager                    m_handsManager;             ///< Manages the hand information coming from the laser ranger
    UdpManager                      m_udpManager;               ///< Manages the UDP messages
    BeautifulMindManager            m_beautifulMindManager;     ///< Manages the Beautiful Mind Scene
    AudioManager                    m_audioManager;             ///< Manages the audio input
    BirdsManager                    m_birdsManager;             ///< Manages the birds
    MidiManager                     m_midiManager;              ///< Manages the midi input messages
    PreviewManager                  m_previewManager;           ///< Manages the preview
    MaskManager                     m_maskManager;              ///< Manages the masking
    ProjectorsManager               m_projectorsManager;        ///< Manages the projectors
    
    bool                            m_areMasksResized;
    

    bool                            m_debugMode;
};

//==========================================================================


