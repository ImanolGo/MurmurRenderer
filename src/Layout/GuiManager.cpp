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
    ofxGuiSetFont( "fonts/open-sans/OpenSans-Semibold.ttf", 9 );
    
    this->setupScenesGui();
    this->setupContourGui();
    this->setupHandsGui();
    this->setupFloorGui();
    this->setupLayoutGui();
    this->setupBeautifulMindGui();
    
    m_gui.loadFromFile(GUI_SETTINGS_FILE_NAME);
 
   
}

void GuiManager::setupScenesGui()
{
    
    auto sceneManager = &AppManager::getInstance().getSceneManager();
    
    m_parametersScenes.setName("Scenes");
    
    m_sceneTransparency.set("Transparency", 0.0, 0.0, 1.0);
    m_sceneTransparency.addListener(sceneManager, &SceneManager::onTransparencyChange);
    m_parametersScenes.add(m_sceneTransparency);
    
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
    
    m_sceneFluidFloor.set("FluidFloorScene", false);
    m_sceneFluidFloor.addListener(this, &GuiManager::onSetFluidFloorScene);
    m_parametersScenes.add(m_sceneFluidFloor);
    
    m_sceneBeautifulMind.set("BeautifulMindScene", false);
    m_sceneBeautifulMind.addListener(this, &GuiManager::onSetBeautifulMindScene);
    m_parametersScenes.add(m_sceneBeautifulMind);
    
    m_gui.add(m_parametersScenes);
    
}

void GuiManager::setupContourGui()
{
    
    auto contourManager = &AppManager::getInstance().getContourManager();
    m_parametersContour.setName("Contour");
    
    m_contourThickness.set("Thickness", 1.0, 0.0, 10.0);
    m_contourThickness.addListener(contourManager, &ContourManager::setContourThickness);
    m_parametersContour.add(m_contourThickness);
    
    
    m_contourOffset.set("Offset", ofVec2f(0.0,0.0) , ofVec2f(-2.0,-2.0) , ofVec2f(2.0,2.0));
    m_contourOffset.addListener(contourManager, &ContourManager::setOffset);
    m_parametersContour.add(m_contourOffset);
    
    m_contourScale.set("Scale", ofVec2f(1.0,1.0) , ofVec2f(-2.0,-2.0) , ofVec2f(2.0,2.0) );
    m_contourScale.addListener(contourManager, &ContourManager::setScale);
    m_parametersContour.add(m_contourScale);
    
    m_gui.add(m_parametersContour);
    
}

void GuiManager::setupHandsGui()
{
    
    auto handsManager = &AppManager::getInstance().getHandsManager();
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
    
    auto floorManager = &AppManager::getInstance().getFloorManager();
    m_parametersFloor.setName("Floor");
    
    m_floorOffset.set("Offset", ofVec2f(0.0,0.0) , ofVec2f(-1.0,-1.0) , ofVec2f(1.0,1.0) );
    m_floorOffset.addListener(floorManager, &FloorManager::setOffset);
    m_parametersFloor.add(m_floorOffset);
    
    m_floorScale.set("Scale", ofVec2f(1.0,1.0) , ofVec2f(-1.0,-1.0) , ofVec2f(1.0,1.0) );
    m_floorScale.addListener(floorManager, &FloorManager::setScale);
    m_parametersFloor.add(m_floorScale);
    
    m_gui.add(m_parametersFloor);
    
}

void GuiManager::setupBeautifulMindGui()
{
    
    auto beautifulMindManager = &AppManager::getInstance().getBeautifulMindManager();
    m_parametersBeautifulMind.setName("BeautifulMind");
    
    m_beautifulMindOffset.set("Offset", ofVec2f(0.0,0.0) , ofVec2f(-1.0,-1.0) , ofVec2f(1.0,1.0) );
    m_beautifulMindOffset.addListener(beautifulMindManager, &BeautifulMindManager::setOffset);
    m_parametersBeautifulMind.add(m_beautifulMindOffset);
    
    m_beautifulMindScale.set("Scale", ofVec2f(1.0,1.0) , ofVec2f(0.0,0.0) , ofVec2f(1.0,1.0) );
    m_beautifulMindScale.addListener(beautifulMindManager, &BeautifulMindManager::setScale);
    m_parametersBeautifulMind.add(m_beautifulMindScale);
    m_gui.add(m_parametersBeautifulMind);
    
}

void GuiManager::setupLayoutGui()
{
    auto layoutManager = &AppManager::getInstance().getLayoutManager();
    m_parametersLayout.setName("Crop");
    
    m_cropLeft.set("CropLeft", 0.0, 0.0, 500.0);
    m_cropLeft.addListener(layoutManager, &LayoutManager::onCropLeft);
    m_parametersLayout.add(m_cropLeft);
    
    m_cropRight.set("CropRight", 0.0, 0.0, 500.0);
    m_cropRight.addListener(layoutManager, &LayoutManager::onCropRight);
    m_parametersLayout.add(m_cropRight);
    
    m_cropTop.set("CropTop", 0.0, 0.0, 500.0);
    m_cropTop.addListener(layoutManager, &LayoutManager::onCropTop);
    m_parametersLayout.add(m_cropTop);
    
    m_cropBottom.set("CropBottom", 0.0, 0.0, 500.0);
    m_cropBottom.addListener(layoutManager, &LayoutManager::onCropBottom);
    m_parametersLayout.add(m_cropBottom);
    
     m_gui.add(m_parametersLayout);
    
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
        m_sceneFluidFloor = false;
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
        m_sceneFluidFloor = false;
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
        m_sceneFluidFloor = false;
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
        m_sceneFluidFloor = false;
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
        m_sceneFluidFloor = false;
        AppManager::getInstance().getSceneManager().changeScene(m_sceneBeautifulMind.getName());
    }
}

void GuiManager::onSetFluidFloorScene(bool& value)
{
    if(value == true){
        m_sceneBlank = false;
        m_sceneSmokyHands = false;
        m_sceneBattleOfSelf = false;
        m_sceneHandsWriting = false;
        m_sceneBeautifulMind = false;
        AppManager::getInstance().getSceneManager().changeScene(m_sceneFluidFloor.getName());
    }
}




