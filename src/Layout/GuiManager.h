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
 *	\brief Class managing the application�s grapical user interface (GUI)
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
    
    void setSceneOpacity(float value) {m_sceneOpacity = value;}
    
    void onSetSceneOpacity(float& value);
    
    void setSceneOpacityTop(float value) {m_sceneOpacityTop = value;}
    
    void setSceneOpacityFront(float value) {m_sceneOpacityFront = value;}
    
    void setSceneTransitionTime(float value) {m_sceneTransitionTime = value;}
    
    void setScene(const string& sceneName);
    
    void onSetBlankScene(bool& value);
    
    void onSetSmokyHandsScene(bool& value);
    
    void onSetBattleOfSelfScene(bool& value);
    
    void onSetHandsWritingScene(bool& value);
    
    void onSetBeautifulMindScene(bool& value);
    
    void onSetFluidFloorScene(bool& value);
    
    void onSetKathakScene(bool& value);
    
    void onSetBirdsAndPaperScene(bool& value);
    
    void onSetBirdsOpeningScene(bool& value);
    
    void onSetPostShowScene(bool& value);
    
    void onSetSonicBoomScene(bool& value);
    
    void onSetProjectCalibrationScene(bool& value);
    
    void setAudioVolume(float& value){m_audioVolume = value;}
    
    void setAudioOn(bool& value){m_audioOn = value;}
    
    void setContourThickness(float value) {m_contourThickness = value;}
    
    void setContourOffset(ofVec2f value) {m_contourOffset = value;}
    
    void setContourOffsetX(float value) {m_contourOffset = ofVec2f(value, m_contourOffset->y);}
    
    void setContourOffsetY(float value)  {m_contourOffset = ofVec2f(m_contourOffset->x, value);}
    
    void setContourScale(ofVec2f value) {m_contourScale = value;}
    
    void setContourScaleX(float value) {m_contourScale = ofVec2f(value, m_contourScale->y);}
    
    void setContourScaleY(float value)  {m_contourScale = ofVec2f(m_contourScale->x, value);}
    
    void setHandsOn(bool value) {m_handsOn = value;}
    
    void setHandsFadeTime(float value) {m_handsFadeTime = value;}
    
    void setHandsSize(float value) {m_handsSize = value;}
    
    void setHandsOffset(ofVec2f value) {m_handsOffset = value;}
    
    void setHandsOffsetX(float value) {m_handsOffset = ofVec2f(value, m_handsOffset->y);}
    
    void setHandsOffsetY(float value)  {m_handsOffset = ofVec2f(m_handsOffset->x, value);}
    
    void setHandsScale(ofVec2f value) {m_handsScale = value;}
    
    void setHandsScaleX(float value) {m_handsScale = ofVec2f(value, m_handsScale->y);}
    
    void setHandsScaleY(float value)  {m_handsScale = ofVec2f(m_handsScale->x, value);}
    
    void setFloorOffset(ofVec2f value) {m_floorOffset = value;}
    
    void setFloorOffsetX(float value) {m_floorOffset = ofVec2f(value, m_floorOffset->y);}
    
    void setFloorOffsetY(float value)  {m_floorOffset = ofVec2f(m_floorOffset->x, value);}
    
    void setFloorScale(ofVec2f value) {m_floorScale = value;}
    
    void setFloorScaleX(float value) {m_floorScale = ofVec2f(value, m_floorScale->y);}
    
    void setFloorScaleY(float value)  {m_floorScale = ofVec2f(m_floorScale->x, value);}
    
    void setBeautifulMindOffset(ofVec2f value) {m_beautifulMindOffset = value;}
    
    void setBeautifulMindScale(ofVec2f value) {m_beautifulMindScale = value;}
    
    void setBeautifulMindFloorSpeed(float value) {m_beautifulMindFloorSpeed = value;}
    
    void setBeautifulMindFloorOn(bool value) {m_beautifulMindFloorOn = value;}
    
    void setBeautifulMindCalibrationOn(bool value) {m_beautifulMindCalibrationOn = value;}
    
    void setCropLeft(unsigned int value) {m_cropLeft = value;}
    
    void setCropRight(unsigned int value) {m_cropRight = value;}
    
    void setCropTop(unsigned int value) {m_cropTop = value;}
    
    void setCropBottom(unsigned int value) {m_cropBottom = value;}
    
    void setFullScreen(bool value) {m_fullscreen = value;}
    
    void setBirdsPosition(const ofVec3f& pos) {m_birdsPosition = pos;}
    
    void setBirdsSize(const ofVec3f& size) {m_birdsSwarmSizeVector = size;}
    
    void setBirdsSize(float value) {m_birdsSize = value;}
    
    void setBirdsSpeed(float value) {m_birdsSpeed = value;}
    
    void setBirdsNumber(float value) {m_birdsNumber = value;}
    
    void setBirdsRandomness(float value) {m_birdsRandomness = value;}
    
    void setPaperThrowerSpeed(float value) {m_paperThrowerSpeed = value;}
    
    void onSetBirdsSwarmSize(float& value);
    
    
private:
    
    void setupScenesGui();
    
    void setupAudioGui();
    
    void setupContourGui();
    
    void setupTopGui();
    
    void setupHandsGui();
    
    void setupFloorGui();
    
    void setupBeautifulMindGui();
    
    void setupLayoutGui();
    
    void setupBirdsGui();
    
    void setupProjectorsGui();
    
    
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
    ofParameterGroup        m_parametersTop;
    ofParameterGroup        m_parametersProjector;
   
    bool                    m_showGui;  //It defines the whether the gui should be shown or not
    
    ofParameter<float>      m_guiFPS;

    ofParameter<float>      m_sceneOpacity;
    ofParameter<float>      m_sceneOpacityFront;
    ofParameter<float>      m_sceneOpacityTop;
    ofParameter<float>      m_sceneTransitionTime;
    ofParameter<bool>       m_sceneSmokyHands;
    ofParameter<bool>       m_sceneBlank;
    ofParameter<bool>       m_sceneBattleOfSelf;
    ofParameter<bool>       m_sceneHandsWriting;
    ofParameter<bool>       m_sceneFluidFloor;
    ofParameter<bool>       m_sceneBeautifulMind;
    ofParameter<bool>       m_sceneKathak;
    ofParameter<bool>       m_birdsOpeningScene;
    ofParameter<bool>       m_birdsAndPaperScene;
    ofParameter<bool>       m_postShowScene;
    ofParameter<bool>       m_sonicBoomScene;
    ofParameter<bool>       m_projectorCalibrationScene;
    
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
    ofParameter<float>      m_floorMinSize;
    ofParameter<float>      m_floorMaxSize;
    ofParameter<float>      m_floorLineWidth;
    
    ofParameter<ofVec2f>    m_beautifulMindOffset;
    ofParameter<ofVec2f>    m_beautifulMindScale;
    ofParameter<float>      m_beautifulMindFloorSpeed;
    ofParameter<bool>       m_beautifulMindFloorOn;
    ofParameter<bool>       m_beautifulMindCalibrationOn;
    
    ofParameter<ofVec3f>    m_birdsPosition;
    ofParameter<ofVec3f>    m_birdsSwarmSizeVector;
    ofParameter<float>      m_birdsSize;
    ofParameter<float>      m_birdsSwarmSize;
    ofParameter<int>        m_birdsNumber;
    ofParameter<float>      m_birdsSpeed;
    ofParameter<float>      m_birdsRandomness;
    
    
    ofParameter<bool>       m_projector1Shutter;
    ofParameter<bool>       m_projector2Shutter;
    
    ofParameter<int>        m_paperThrowerSpeed;
    
    
};

//==========================================================================


