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
    this->setupBirdsGui();
    this->setupContourGui();
    this->setupHandsGui();
    this->setupFloorGui();
    this->setupLayoutGui();
    this->setupBeautifulMindGui();
    this->setupAudioGui();
    this->setupTopGui();
    
    m_gui.loadFromFile(GUI_SETTINGS_FILE_NAME);
    
    m_gui.minimizeAll();
 
}

void GuiManager::setupBirdsGui()
{
    auto birdsManager = &AppManager::getInstance().getBirdsManager();
    
    m_parametersBirds.setName("Birds");
    
    m_birdsPosition.set("Position", ofVec3f(0,0,0) , ofVec3f(-1.0,-1.0,-1.0) , ofVec3f(1.0,1.0,1.0));
    m_birdsPosition.addListener(birdsManager, &BirdsManager::onChangePosition);
    m_parametersBirds.add(m_birdsPosition);

    m_birdsSize.set("Size", 1.0, 0.0, 5.0);
    m_birdsSize.addListener(birdsManager, &BirdsManager::onChangeSize);
    m_parametersBirds.add(m_birdsSize);
    
    m_birdsSwarmSize.set("SwarmSize", 4.0, 0.0, 30.0);
    m_birdsSwarmSize.addListener(this, &GuiManager::onSetBirdsSwarmSize);
    m_parametersBirds.add(m_birdsSwarmSize);
    
    m_birdsSwarmSizeVector.set("SwarmSize",  ofVec3f(4,4,4) , ofVec3f(0.0,0.0,0.0) , ofVec3f(30,30,30));
    m_birdsSwarmSizeVector.addListener(birdsManager, &BirdsManager::onChangeSwarmSize);
    m_parametersBirds.add(m_birdsSwarmSizeVector);
    
    m_birdsNumber.set("BirdsNumber", 250, 0, 1000);
    m_birdsNumber.addListener(birdsManager, &BirdsManager::onChangeSwarmNumber);
    m_parametersBirds.add(m_birdsNumber);
    
    m_birdsSpeed.set("Speed", 10, 0, 20);
    m_birdsSpeed.addListener(birdsManager, &BirdsManager::onChangeSpeed);
    m_parametersBirds.add(m_birdsSpeed);
    
    m_birdsRandomness.set("Randomness", 0, 0, 50);
    m_birdsRandomness.addListener(birdsManager, &BirdsManager::onChangeSwarmRandomness);
    m_parametersBirds.add(m_birdsRandomness);

    m_gui.add(m_parametersBirds);
    
}

void GuiManager::setupScenesGui()
{
    
    auto sceneManager = &AppManager::getInstance().getSceneManager();
    
    m_parametersScenes.setName("Scenes");
    
    m_sceneOpacity.set("Opacity", 0.0, 0.0, 1.0);
    m_sceneOpacity.addListener(this, &GuiManager::onSetSceneOpacity);
    m_parametersScenes.add(m_sceneOpacity);
    
    m_sceneOpacityFront.set("OpacityFront", 0.0, 0.0, 1.0);
    m_sceneOpacityFront.addListener(sceneManager, &SceneManager::onFrontOpacityChange);
    m_parametersScenes.add(m_sceneOpacityFront);
    
    m_sceneOpacityTop.set("OpacityTop", 0.0, 0.0, 1.0);
    m_sceneOpacityTop.addListener(sceneManager, &SceneManager::onTopOpacityChange);
    m_parametersScenes.add(m_sceneOpacityTop);

    
    m_sceneTransitionTime.set("TransitionTime", 2.0, 0.0, 10);
    m_sceneTransitionTime.addListener(sceneManager, &SceneManager::onTransitionTimeChange);
    m_parametersScenes.add(m_sceneTransitionTime);
    
    m_sceneBlank.set("BlankScene", false);
    m_sceneBlank.addListener(this, &GuiManager::onSetBlankScene);
    m_parametersScenes.add(m_sceneBlank);
    
    m_sceneKathak.set("KathakScene", false);
    m_sceneKathak.addListener(this, &GuiManager::onSetKathakScene);
    m_parametersScenes.add(m_sceneKathak);

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
    
    m_birdsOpeningScene.set("BirdsOpeningScene", false);
    m_birdsOpeningScene.addListener(this, &GuiManager::onSetBirdsOpeningScene);
    m_parametersScenes.add(m_birdsOpeningScene);
    
    m_birdsAndPaperScene.set("BirdsAndPaperScene", false);
    m_birdsAndPaperScene.addListener(this, &GuiManager::onSetBirdsAndPaperScene);
    m_parametersScenes.add(m_birdsAndPaperScene);
    
    m_postShowScene.set("PostShowScene", false);
    m_postShowScene.addListener(this, &GuiManager::onSetPostShowScene);
    m_parametersScenes.add(m_postShowScene);

    
    m_gui.add(m_parametersScenes);
    
}

void GuiManager::setupAudioGui()
{
    auto audioManager = &AppManager::getInstance().getAudioManager();
    m_parametersAudio.setName("Audio");
    
    m_audioOn.set("AudioOn", false);
    m_audioOn.addListener(audioManager, &AudioManager::onChangeAudioOn);
    m_parametersAudio.add(m_audioOn);
    
    m_audioVolume.set("Volume", 0.5, 0.0, 1.0);
    m_audioVolume.addListener(audioManager, &AudioManager::onChangeVolume);
    m_parametersAudio.add(m_audioVolume);
    
    m_gui.add(m_parametersAudio);
}

void GuiManager::setupTopGui()
{
    auto oscManager = &AppManager::getInstance().getOscManager();
    m_parametersTop.setName("FloorTracking");
    
    
    m_paperThrowerSpeed.set("PaperThrowerSpeed", 0, 0, 100);
    m_paperThrowerSpeed.addListener(oscManager, &OscManager::onChangePaperThrowerSpeed);
    m_parametersTop.add(m_paperThrowerSpeed);
    
    m_gui.add(m_parametersTop);
    
    ofxButton * paperThrowerFire = new ofxButton();
    paperThrowerFire->setup("PaperThrowerFire");
    paperThrowerFire->addListener(oscManager, &OscManager::onFirePaperThrower);
    m_gui.add(paperThrowerFire);
    
    ofxButton * resetBackground = new ofxButton();
    resetBackground->setup("ResetBackground");
    resetBackground->addListener(oscManager, &OscManager::onResetTopBackground);
    m_gui.add(resetBackground);
    
   
}

void GuiManager::setupContourGui()
{
    
    auto contourManager = &AppManager::getInstance().getContourManager();
    m_parametersContour.setName("Contour");
    
    m_contourThickness.set("Thickness", 1.0, 0.0, 4.0);
    m_contourThickness.addListener(contourManager, &ContourManager::setContourThickness);
    m_parametersContour.add(m_contourThickness);
    
    
    m_contourOffset.set("Offset", ofVec2f(0.0,0.0) , ofVec2f(-0.7,-0.7) , ofVec2f(0.7,0.7));
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
    
    m_handsOn.set("On", false);
    m_handsOn.addListener(handsManager, &HandsManager::setHandsOn);
    m_parametersHands.add(m_handsOn);
    
    m_handsOffset.set("Offset", ofVec2f(0.0,0.0) , ofVec2f(-0.5,-0.5) , ofVec2f(0.5,0.5) );
    m_handsOffset.addListener(handsManager, &HandsManager::setOffset);
    m_parametersHands.add(m_handsOffset);
    
    m_handsScale.set("Scale", ofVec2f(1.0,1.0) , ofVec2f(-1.0,-1.0) , ofVec2f(1.0,1.0) );
    m_handsScale.addListener(handsManager, &HandsManager::setScale);
    m_parametersHands.add(m_handsScale);
    
    m_handsSize.set("Size", 1.0, 0.0, 5.0);
    m_handsSize.addListener(handsManager, &HandsManager::setSize);
    m_parametersHands.add(m_handsSize);

    m_handsFadeTime.set("FadeTime", 2.0, 0.0, 15.0);
    m_handsFadeTime.addListener(handsManager, &HandsManager::setFadeTime);
    m_parametersHands.add(m_handsFadeTime);
    
    m_gui.add(m_parametersHands);
    
}

void GuiManager::setupFloorGui()
{
    
    auto floorManager = &AppManager::getInstance().getFloorManager();
    m_parametersFloor.setName("Floor");
    
    m_floorOffset.set("Offset", ofVec2f(0.0,0.0) , ofVec2f(-0.5,-0.5) , ofVec2f(0.5,0.5) );
    m_floorOffset.addListener(floorManager, &FloorManager::setOffset);
    m_parametersFloor.add(m_floorOffset);
    
    m_floorScale.set("Scale", ofVec2f(1.0,1.0) , ofVec2f(-2.0,-2.0) , ofVec2f(2.0,2.0) );
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
    
    m_beautifulMindFloorOn.set("FloorOn", false);
    m_beautifulMindFloorOn.addListener(beautifulMindManager, &BeautifulMindManager::setFloorOn);
    m_parametersBeautifulMind.add(m_beautifulMindFloorOn);
    
    m_beautifulMindFloorSpeed.set("Speed", 1.0, 0.0, 5.0);
    m_beautifulMindFloorSpeed.addListener(beautifulMindManager, &BeautifulMindManager::setFloorSpeed);
    m_parametersBeautifulMind.add(m_beautifulMindFloorSpeed);
    
    m_beautifulMindCalibrationOn.set("CalibrationOn", false);
    m_beautifulMindCalibrationOn.addListener(beautifulMindManager, &BeautifulMindManager::setCalibrationOn);
    m_parametersBeautifulMind.add(m_beautifulMindCalibrationOn);


    m_gui.add(m_parametersBeautifulMind);
}

void GuiManager::setupLayoutGui()
{
    auto appManager = &AppManager::getInstance();
    auto layoutManager = &AppManager::getInstance().getLayoutManager();
    
    m_parametersLayout.setName("Layout");

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
        m_sceneKathak = false;
        m_birdsAndPaperScene = false;
        m_birdsOpeningScene = false;
        m_postShowScene = false;
        
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
        m_sceneKathak = false;
        m_birdsAndPaperScene = false;
        m_birdsOpeningScene = false;
        m_postShowScene = false;

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
        m_sceneKathak = false;
        m_birdsAndPaperScene = false;
        m_birdsOpeningScene = false;
        m_postShowScene = false;

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
        m_sceneKathak = false;
        m_birdsAndPaperScene = false;
        m_birdsOpeningScene = false;
        m_postShowScene = false;

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
        m_sceneKathak = false;
        m_birdsAndPaperScene = false;
        m_birdsOpeningScene = false;
        m_postShowScene = false;

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
        m_sceneKathak = false;
        m_birdsAndPaperScene = false;
        m_birdsOpeningScene = false;
        m_postShowScene = false;

        AppManager::getInstance().getSceneManager().changeScene(m_sceneFluidFloor.getName());
    }
}

void GuiManager::onSetKathakScene(bool& value)
{
    if(value == true){
        m_sceneBlank = false;
        m_sceneSmokyHands = false;
        m_sceneBattleOfSelf = false;
        m_sceneHandsWriting = false;
        m_sceneBeautifulMind = false;
        m_sceneFluidFloor = false;
        m_birdsAndPaperScene = false;
        m_birdsOpeningScene = false;
        m_postShowScene = false;

        AppManager::getInstance().getSceneManager().changeScene(m_sceneKathak.getName());
    }
}

void GuiManager::onSetBirdsOpeningScene(bool& value)
{
    if(value == true){
        m_sceneBlank = false;
        m_sceneSmokyHands = false;
        m_sceneBattleOfSelf = false;
        m_sceneHandsWriting = false;
        m_sceneBeautifulMind = false;
        m_sceneFluidFloor = false;
        m_sceneKathak = false;
        m_birdsAndPaperScene = false;
        m_postShowScene = false;
        
        AppManager::getInstance().getSceneManager().changeScene(m_birdsOpeningScene.getName());
    }
}

void GuiManager::onSetBirdsAndPaperScene(bool& value)
{
    if(value == true){
        m_sceneBlank = false;
        m_sceneSmokyHands = false;
        m_sceneBattleOfSelf = false;
        m_sceneHandsWriting = false;
        m_sceneBeautifulMind = false;
        m_sceneFluidFloor = false;
        m_sceneKathak = false;
        m_birdsOpeningScene = false;
        m_postShowScene = false;
        
        AppManager::getInstance().getSceneManager().changeScene(m_birdsAndPaperScene.getName());
    }
}

void GuiManager::onSetPostShowScene(bool& value)
{
    if(value == true){
        m_sceneBlank = false;
        m_sceneSmokyHands = false;
        m_sceneBattleOfSelf = false;
        m_sceneHandsWriting = false;
        m_sceneBeautifulMind = false;
        m_sceneFluidFloor = false;
        m_sceneKathak = false;
        m_birdsOpeningScene = false;
        m_birdsAndPaperScene = false;
        
        AppManager::getInstance().getSceneManager().changeScene(m_postShowScene.getName());
    }
}



 void GuiManager::onSetBirdsSwarmSize(float& value)
{
    m_birdsSwarmSize = value;
    ofVec3f size(value,value,value);
    m_birdsSwarmSizeVector.set(size);
    
}


void GuiManager::setScene(const string &sceneName)
{
    if(!m_parametersScenes.contains(sceneName)){
        return;
    }
    
    ofParameter<bool>& scene = (ofParameter<bool>&) m_parametersScenes.get(sceneName);
    scene.set(true);
}

void GuiManager::onSetSceneOpacity(float& value)
{
    m_sceneOpacityFront = value;
    m_sceneOpacityTop = value;
}


