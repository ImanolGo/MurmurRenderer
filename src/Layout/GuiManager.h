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
    
    void setSceneTransparency(float value) {m_sceneTransparency = value;}
    
    void setSceneTransitionTime(float value) {m_sceneTransitionTime = value;}
    
    void setScene(const string& sceneName);
    
    void onSetBlankScene(bool& value);
    
    void onSetSmokyHandsScene(bool& value);
    
    void onSetBattleOfSelfScene(bool& value);
    
    void onSetHandsWritingScene(bool& value);
    
    void onSetBeautifulMindScene(bool& value);
    
    void onSetFluidFloorScene(bool& value);
    
    void onSetKathakScene(bool& value);
    
    void onSetBirdsScene(bool& value);
    
    void setAudioVolume(float& value){m_audioVolume = value;}
    
    void setAudioOn(bool& value){m_audioOn = value;}
    
    void setContourThickness(float value) {m_contourThickness = value;}
    
    void setContourOffset(ofVec2f value) {m_contourOffset = value;}
    
    void setContourScale(ofVec2f value) {m_contourScale = value;}
    
    void setHandsOn(bool value) {m_handsOn = value;}
    
    void setHandsFadeTime(float value) {m_handsFadeTime = value;}
    
    void setHandsSize(float value) {m_handsSize = value;}
    
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
    
    void setFullScreen(bool value) {m_fullscreen = value;}
    
    void setBirdsPosition(const ofVec3f& pos) {m_birdsPosition = pos;}
    
    void setBirdsSize(float value) {m_birdsSize = value;}
    
    void setBirdsSwarmSize(float value) {m_birdsSwarmSize = value;}
    
    
private:
    
    void setupScenesGui();
    
    void setupAudioGui();
    
    void setupContourGui();
    
    void setupHandsGui();
    
    void setupFloorGui();
    
    void setupBeautifulMindGui();
    
    void setupLayoutGui();
    
    void setupBirdsGui();
    
    
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
    ofParameterGroup        m_parametersAudio;
    ofParameterGroup        m_parametersBirds;
   
    bool                    m_showGui;  //It defines the whether the gui should be shown or not
    
    ofParameter<float>      m_guiFPS;

    ofParameter<float>      m_sceneTransparency;
    ofParameter<float>      m_sceneTransitionTime;
    ofParameter<bool>       m_sceneSmokyHands;
    ofParameter<bool>       m_sceneBlank;
    ofParameter<bool>       m_sceneBattleOfSelf;
    ofParameter<bool>       m_sceneHandsWriting;
    ofParameter<bool>       m_sceneFluidFloor;
    ofParameter<bool>       m_sceneBeautifulMind;
    ofParameter<bool>       m_sceneKathak;
    ofParameter<bool>       m_birdsScene;
    
    ofParameter<int>        m_cropLeft, m_cropRight, m_cropTop, m_cropBottom;
    ofParameter<bool>       m_fullscreen;
    
    ofParameter<float>      m_contourThickness;
    ofParameter<ofVec2f>    m_contourOffset;
    ofParameter<ofVec2f>    m_contourScale;
    
    ofParameter<float>      m_audioVolume;
    ofParameter<bool>       m_audioOn;
    
    ofParameter<ofVec2f>    m_handsOffset;
    ofParameter<ofVec2f>    m_handsScale;
    ofParameter<bool>       m_handsOn;
    ofParameter<float>      m_handsFadeTime;
    ofParameter<float>      m_handsSize;
    
    ofParameter<ofVec2f>    m_floorOffset;
    ofParameter<ofVec2f>    m_floorScale;
    
    ofParameter<ofVec2f>    m_beautifulMindOffset;
    ofParameter<ofVec2f>    m_beautifulMindScale;
    
    ofParameter<ofVec3f>    m_birdsPosition;
    ofParameter<float>      m_birdsSize;
    ofParameter<float>      m_birdsSwarmSize;
    ofParameter<int>        m_birdsNumber;

    
    
    
};

//==========================================================================


