/*
 *  GuiManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 17/06/15.
 *
 */

#include "ofMain.h"

#include "AppManager.h"
#include "LayoutManager.h"

#include "GuiManager.h"

const string GuiManager::GUI_SETTINGS_FILE_NAME = "xmls/GuiSettings.xml";
const string GuiManager::GUI_SETTINGS_NAME = "MurmurRenderer";
const int GuiManager::GUI_WIDTH = 250;


GuiManager::GuiManager(): Manager(), m_showGui(true)
{
    //Intentionally left empty
}


GuiManager::~GuiManager()
{
    this->saveGuiValues();
    ofLogNotice() <<"GuiManager::Destructor";
}


void GuiManager::setup()
{
    if(m_initialized)
        return;
    
    ofLogNotice() <<"GuiManager::initialized";
    
    Manager::setup();
    
    m_gui.setDefaultWidth(GUI_WIDTH);
    m_gui.setup(GUI_SETTINGS_NAME, GUI_SETTINGS_FILE_NAME);
    m_gui.setPosition(LayoutManager::MARGIN, LayoutManager::MARGIN);
    m_gui.add(m_guiFPS.set("FPS", 0, 0, 60));
    
    this->setupScenesGui();
    this->setupContourGui();
    this->setupHandsGui();
    this->setupFloorGui();
    
    m_gui.loadFromFile(GUI_SETTINGS_FILE_NAME);
 
   
}

void GuiManager::setupScenesGui()
{
    
    SceneManager* sceneManager = &AppManager::getInstance().getSceneManager();
    
    m_parametersScenes.setName("Scenes");
    
    m_sceneTransitionTime.set("TransitionTime", 2.0, 0.0, 10);
    m_sceneTransitionTime.addListener(sceneManager, &SceneManager::onTransitionTimeChange);
    m_parametersScenes.add(m_sceneTransitionTime);
    
    m_sceneBlank.set("BlankScene", false);
    m_sceneBlank.addListener(this, &GuiManager::onSetBlankScene);
    m_parametersScenes.add(m_sceneBlank);
    
    m_sceneSmokyHands.set("SmokyHandsScene", false);
    m_sceneSmokyHands.addListener(this, &GuiManager::onSetSmokyHandsScene);
    m_parametersScenes.add(m_sceneSmokyHands);
    
    m_sceneBattleOfSelf.set("BattleOfSelfScene", false);
    m_sceneBattleOfSelf.addListener(this, &GuiManager::onSetBattleOfSelfScene);
    m_parametersScenes.add(m_sceneBattleOfSelf);
    
    m_sceneHandsWriting.set("HandsWritingScene", false);
    m_sceneHandsWriting.addListener(this, &GuiManager::onSetHandsWritingScene);
    m_parametersScenes.add(m_sceneHandsWriting);
    
    m_sceneFloorFluid.set("FloorFluidScene", false);
    m_sceneFloorFluid.addListener(this, &GuiManager::onSetFloorFluidScene);
    m_parametersScenes.add(m_sceneFloorFluid);
    
    m_sceneBeautifulMind.set("BeautifulMindScene", false);
    m_sceneBeautifulMind.addListener(this, &GuiManager::onSetBeautifulMindScene);
    m_parametersScenes.add(m_sceneBeautifulMind);
    
    m_gui.add(m_parametersScenes);
    
}

void GuiManager::setupContourGui()
{
    
    ContourManager* contourManager = &AppManager::getInstance().getContourManager();
    m_parametersContour.setName("Contour");
    
    m_contourThickness.set("Thickness", 1.0, 0.0, 10.0);
    m_contourThickness.addListener(contourManager, &ContourManager::setContourThickness);
    m_parametersContour.add(m_contourThickness);
    
    
    m_contourOffset.set("Offset", ofVec2f(0.0,0.0) , ofVec2f(-10.0,-10.0) , ofVec2f(10.0,10.0) );
    m_contourOffset.addListener(contourManager, &ContourManager::setOffset);
    m_parametersContour.add(m_contourOffset);
    
    m_contourScale.set("Scale", ofVec2f(1.0,1.0) , ofVec2f(-10.0,-10.0) , ofVec2f(10.0,10.0) );
    m_contourScale.addListener(contourManager, &ContourManager::setOffset);
    m_parametersContour.add(m_contourScale);
    
    m_gui.add(m_parametersContour);
    
}

void GuiManager::setupHandsGui()
{
    
    HandsManager* handsManager = &AppManager::getInstance().getHandsManager();
    m_parametersHands.setName("Hands");
    
    m_handsOffset.set("Offset", ofVec2f(0.0,0.0) , ofVec2f(-1.0,-1.0) , ofVec2f(1.0,1.0) );
    m_handsOffset.addListener(handsManager, &HandsManager::setOffset);
    m_parametersHands.add(m_handsOffset);
    
    m_handsScale.set("Scale", ofVec2f(1.0,1.0) , ofVec2f(-1.0,-1.0) , ofVec2f(1.0,1.0) );
    m_handsScale.addListener(handsManager, &HandsManager::setScale);
    m_parametersHands.add(m_handsScale);
    
    m_gui.add(m_parametersHands);
    
}

void GuiManager::setupFloorGui()
{
    
    FloorManager* floorManager = &AppManager::getInstance().getFloorManager();
    m_parametersFloor.setName("Floor");
    
    m_floorOffset.set("Offset", ofVec2f(0.0,0.0) , ofVec2f(-1.0,-1.0) , ofVec2f(1.0,1.0) );
    m_floorOffset.addListener(floorManager, &FloorManager::setOffset);
    m_parametersFloor.add(m_floorOffset);
    
    m_floorScale.set("Scale", ofVec2f(1.0,1.0) , ofVec2f(-1.0,-1.0) , ofVec2f(1.0,1.0) );
    m_floorScale.addListener(floorManager, &FloorManager::setScale);
    m_parametersFloor.add(m_floorScale);
    
    m_gui.add(m_parametersFloor);
    
}

void GuiManager::draw()
{
    if(!m_showGui)
        return;
    
    //ofLogNotice() <<"GuiManager::drawGUI";
    m_guiFPS = ofGetFrameRate();
    m_gui.draw();
    
}


void GuiManager::saveGuiValues()
{
    m_gui.saveToFile(GUI_SETTINGS_FILE_NAME);
}

void GuiManager::loadGuiValues()
{
    m_gui.loadFromFile(GUI_SETTINGS_FILE_NAME);
}

void GuiManager::toggleGui()
{
    ofLogNotice() <<"GuiManager::toggleGui -> show GUI "<< m_showGui;
    m_showGui = !m_showGui;
}


void GuiManager::onSetBlankScene(bool& value)
{
    if(value == true){
        m_sceneSmokyHands = false;
        m_sceneBattleOfSelf = false;
        m_sceneHandsWriting = false;
        m_sceneBeautifulMind = false;
        m_sceneFloorFluid = false;
        AppManager::getInstance().getSceneManager().changeScene(m_sceneBlank.getName());
    }
}

void GuiManager::onSetSmokyHandsScene(bool& value)
{
    if(value == true){
        m_sceneBlank = false;
        m_sceneBattleOfSelf = false;
        m_sceneHandsWriting = false;
        m_sceneBeautifulMind = false;
        m_sceneFloorFluid = false;
        AppManager::getInstance().getSceneManager().changeScene(m_sceneSmokyHands.getName());
    }
}

void GuiManager::onSetBattleOfSelfScene(bool& value)
{
    if(value == true){
        m_sceneBlank = false;
        m_sceneSmokyHands = false;
        m_sceneHandsWriting = false;
        m_sceneBeautifulMind = false;
        m_sceneFloorFluid = false;
        AppManager::getInstance().getSceneManager().changeScene(m_sceneBattleOfSelf.getName());
    }
}

void GuiManager::onSetHandsWritingScene(bool& value)
{
    if(value == true){
        m_sceneBlank = false;
        m_sceneSmokyHands = false;
        m_sceneBattleOfSelf = false;
        m_sceneBeautifulMind = false;
        m_sceneFloorFluid = false;
        AppManager::getInstance().getSceneManager().changeScene(m_sceneHandsWriting.getName());
    }
}

void GuiManager::onSetBeautifulMindScene(bool& value)
{
    if(value == true){
        m_sceneBlank = false;
        m_sceneSmokyHands = false;
        m_sceneBattleOfSelf = false;
        m_sceneHandsWriting = false;
        m_sceneFloorFluid = false;
        AppManager::getInstance().getSceneManager().changeScene(m_sceneBeautifulMind.getName());
    }
}

void GuiManager::onSetFloorFluidScene(bool& value)
{
    if(value == true){
        m_sceneBlank = false;
        m_sceneSmokyHands = false;
        m_sceneBattleOfSelf = false;
        m_sceneHandsWriting = false;
        m_sceneBeautifulMind = false;
        AppManager::getInstance().getSceneManager().changeScene(m_sceneFloorFluid.getName());
    }
}




