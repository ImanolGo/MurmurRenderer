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
 *	\brief Class managing the applicationęs grapical user interface (GUI)
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
    
    void onSetBlankScene(bool& value);
    
    void onSetSmokyHandsScene(bool& value);
    
    void onSetBattleOfSelfScene(bool& value);
    
    void onSetHandsWritingScene(bool& value);
    
    void onSetBeautifulMindScene(bool& value);
    
    void onSetFluidFloorScene(bool& value);
    
    void setContourThickness(float value) {m_contourThickness = value;}
    
    void setContourOffset(ofVec2f value) {m_contourOffset = value;}
    
    void setContourScale(ofVec2f value) {m_contourScale = value;}
    
    void setHandsOffset(ofVec2f value) {m_handsOffset = value;}
    
    void setHandsScale(ofVec2f value) {m_handsScale = value;}
    
    void setFloorOffset(ofVec2f value) {m_floorOffset = value;}
    
    void setFloorScale(ofVec2f value) {m_floorScale = value;}
    
    void setBeautifulMindOffset(ofVec2f value) {m_beautifulMindOffset = value;}
    
    void setBeautifulMindScale(ofVec2f value) {m_beautifulMindScale = value;}
    
    void setCropLeft(unsigned int value) {m_cropLeft = value;}
    
    void setCropRight(unsigned int value) {m_cropRight = value;}
    
    void setCropTop(unsigned int value) {m_cropTop = value;}
    
    void setCropBottom(unsigned int value) {m_cropBottom = value;}
    
    
private:
    
    void setupScenesGui();
    
    void setupContourGui();
    
    void setupHandsGui();
    
    void setupFloorGui();
    
    void setupBeautifulMindGui();
    
    void setupLayoutGui();
    
    
public:
    
    static const int GUI_WIDTH;
    
private:
    
    ofxPanel                m_gui;
    ofParameterGroup        m_parametersContour;
    ofParameterGroup        m_parametersScenes;
    ofParameterGroup        m_parametersHands;
    ofParameterGroup        m_parametersFloor;
    ofParameterGroup        m_parametersBeautifulMind;
    ofParameterGroup        m_parametersLayout;
   
    bool                    m_showGui;  //It defines the whether the gui should be shown or not
    
    ofParameter<float>      m_guiFPS;

    ofParameter<float>      m_sceneTransitionTime;
    ofParameter<bool>       m_sceneSmokyHands;
    ofParameter<bool>       m_sceneBlank;
    ofParameter<bool>       m_sceneBattleOfSelf;
    ofParameter<bool>       m_sceneHandsWriting;
    ofParameter<bool>       m_sceneFluidFloor;
    ofParameter<bool>       m_sceneBeautifulMind;
    
    ofParameter<int>     m_cropLeft, m_cropRight, m_cropTop, m_cropBottom;
    
    ofParameter<float>      m_contourThickness;
    ofParameter<ofVec2f>    m_contourOffset;
    ofParameter<ofVec2f>    m_contourScale;
    
    ofParameter<ofVec2f>    m_handsOffset;
    ofParameter<ofVec2f>    m_handsScale;
    
    ofParameter<ofVec2f>    m_floorOffset;
    ofParameter<ofVec2f>    m_floorScale;
    
    ofParameter<ofVec2f>    m_beautifulMindOffset;
    ofParameter<ofVec2f>    m_beautifulMindScale;
    
};

//==========================================================================


