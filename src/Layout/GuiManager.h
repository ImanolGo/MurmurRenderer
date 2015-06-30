/*
 *  GuiManager.h
 *  Murmur
 *
 *  Created by Imanol Gomez on 17/06/15.
 *
 */

#pragma once

#include "Manager.h"
#include "ofxGui.h"
//========================== class GuiManager ==============================
//============================================================================
/** \class GuiManager GuiManager.h
 *	\brief Class managing the application«s grapical user interface (GUI)
 *	\details It creates the gui and the callback functions that will be affected
 *    by the gui
 */

class GuiManager: public Manager
{
    
    static const string GUI_SETTINGS_FILE_NAME;
    static const string GUI_SETTINGS_NAME;
    
public:
    
    //! Constructor
    GuiManager();
    
    //! Destructor
    ~GuiManager();
    
    //! Set-up the gui
    void setup();
    
    //! Draw the gui
    void draw();
    
    void saveGuiValues();
    
    void loadGuiValues();
    
    void toggleGui();
    
    void showGui(bool show){m_showGui=show;}
    
    int getWidth()  {return m_gui.getWidth();}
    
    int getHeight()  {return m_gui.getHeight();}
    
    void setSceneTransitionTime(float value) {m_sceneTransitionTime = value;}
    
    
    //! Changes the blank scene from the GUI
    void onSetBlankScene(bool& value);
    
    //! Changes the smoky hands scene from the GUI
    void onSetSmokyHandsScene(bool& value);
    
    //! Changes the battle of self scene from the GUI
    void onSetBattleOfSelfScene(bool& value);
    
    
private:
    
    void setupScenesGui();
    
    void setupContourGui();
    
    
public:
    
    static const int GUI_WIDTH;
    
private:
    
    ofxPanel                m_gui;
    ofParameterGroup        m_parametersContour;
    ofParameterGroup        m_parametersScenes;
   
    bool                    m_showGui;  //It defines the whether the gui should be shown or not
    
    ofParameter<float>      m_guiFPS;

    ofParameter<float>      m_sceneTransitionTime;
    ofParameter<bool>       m_sceneSmokyHands;
    ofParameter<bool>       m_sceneBlank;
    ofParameter<bool>       m_sceneBattleOfSelf;
    
    ofParameter<float>      m_contourThickness;
    ofParameter<ofVec2f>    m_contourOffset;
    ofParameter<ofVec2f>    m_contourScale;
    
};

//==========================================================================


