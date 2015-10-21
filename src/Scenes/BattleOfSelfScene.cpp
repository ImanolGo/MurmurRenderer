/*
 *  BattleOfSelfScene.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 30/06/15.
 *
 */


#include "AppManager.h"
#include "ContourManager.h"

#include "BattleOfSelfScene.h"


BattleOfSelfScene::BattleOfSelfScene():m_initialized(false)
{
    
}

BattleOfSelfScene::~BattleOfSelfScene()
{
    //Intentionally left empty
}

void BattleOfSelfScene::setup()
{
    if (m_initialized) {
        return;
    }
    
    this->setupFbos();
    this->setupPostProcessing();
    
    m_sonicBoomVisual.setup();
    
    m_fluid.setup("xmls/BattleOfSelfFluid.xml");
    m_initialized = true;
    
    ofLogNotice("BattleOfSelfScene::setup");
    
}

void BattleOfSelfScene::setupFbos()
{
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    
    m_drawArea = ofRectangle(0, 0, windowsSettings.width, windowsSettings.height);
    
    m_fbo.allocate(windowsSettings.width, windowsSettings.height);
    m_fbo.begin(); ofClear(0); m_fbo.end();
    
}



void BattleOfSelfScene::setupShaders()
{
    //m_shader.setGeometryInputType(GL_LINES);
    //m_shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
    //m_shader.setGeometryOutputCount(24);
    
    
    if(ofIsGLProgrammableRenderer()){
        m_shader.load("shaders/shadersGL3/LiquifyShader");
    }
    else{
        m_shader.load("shaders/shadersGL2/LiquifyShader");
        
    }
    
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    m_blur.setup(windowsSettings.width, windowsSettings.height, 2, .2, 4);
    //m_blur.setScale(5);
    
    //ofLogNotice() << "BattleOfSelfScene::setupShaders -> Geometry Max Output Count: " << m_shader.getGeometryMaxOutputCount();
    
}

void BattleOfSelfScene::setupPostProcessing()
{
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    
    // Setup post-processing chain
    m_postProcessing.init(windowsSettings.width, windowsSettings.height);
    m_postProcessing.createPass<FxaaPass>()->setEnabled(true);
    //m_postProcessing.createPass<BloomPass>()->setEnabled(true);
    
    //ofPtr<ZoomBlurPass> zoomBlurPass =  m_postProcessing.createPass<ZoomBlurPass>();
    //zoomBlurPass->setDensity(0.5);
    //zoomBlurPass->setEnabled(true);
    
    ofPtr<NoiseWarpPass> noisePass =  m_postProcessing.createPass<NoiseWarpPass>();
    noisePass->setAmplitude(0.007);
    noisePass->setSpeed(0.5);
    noisePass->setFrequency(10);
    noisePass->setEnabled(true);
    
    
    //m_postProcessing.createPass<ZoomBlurPass>()->setEnabled(true);
    //m_postProcessing.createPass<NoiseWarpPass>()->setEnabled(true);
}

void BattleOfSelfScene::update()
{
    this->updateFluid();
    this->updateSonicBoom();
}


void BattleOfSelfScene::updateFluid()
{
    auto source = AppManager::getInstance().getContourManager().getSource();
    m_fluid.setSource(source);
    m_fluid.update();
}


void BattleOfSelfScene::updateContour()
{
    ofEnableAlphaBlending();
    m_fbo.begin();
    ofPushStyle();
    ofSetColor(0,0,0, 20);
    ofRect(0,0,m_fbo.getWidth(),m_fbo.getHeight());
    ofSetColor(255,255,255);
    AppManager::getInstance().getContourManager().draw();
    ofPopStyle();
    m_fbo.end();
    ofDisableAlphaBlending();
}

void BattleOfSelfScene::updateSonicBoom()
{
    m_sonicBoomVisual.update();
}

void BattleOfSelfScene::draw() {
    
    //ofLogNotice("BattleOfSelfScene::draw");

    ofPushStyle();
        ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    
        this->drawSonicBoom();
    
        ofEnableBlendMode(OF_BLENDMODE_ADD);
    
        this->drawFluid();
        //m_fluid.draw(m_drawArea);
        //m_fluid.drawGui();
    
    ofPopStyle();
    
}


void BattleOfSelfScene::drawContour()
{
    // copy enable part of gl state
    //glPushAttrib(GL_ENABLE_BIT);
    
    /*m_postProcessing.begin();
     
     ofPushMatrix();
     //ofSetColor(255,255,255);
     ofScale(1, -1);
     ofTranslate(0, -ofGetHeight());
     m_fbo.draw(0,0);
     // AppManager::getInstance().getContourManager().draw();
     ofPopMatrix();
     
     // end scene and draw
     m_postProcessing.end();*/
    
    
    // set gl state back to original
    //glPopAttrib();
    
    //m_filter->begin();
    //AppManager::getInstance().getContourManager().draw();
    //m_filter->end();
    m_blur.begin();
    m_shader.begin();
    float time = ofGetElapsedTimef();
    m_shader.setUniform1f( "time", time );	//Passing float parameter "time" to shader
    m_shader.setUniform1f( "amplitude", .4f );	//Passing float parameter "time" to shader
    m_fbo.draw(0,0);
    
    m_shader.end();
    m_blur.end();
    
    m_blur.draw();
}

void BattleOfSelfScene::drawSonicBoom()
{
    ofEnableAlphaBlending();
    m_postProcessing.begin();
    ofPushStyle();
    ofPushMatrix();
    //ofEnableBlendMode(OF_BLENDMODE_DISABLED);
        ofScale(1, -1);
        ofTranslate(0, -m_fbo.getHeight());
        //m_fbo.draw(0,0);
    //ofEnableBlendMode(OF_BLENDMODE_ADD);
        m_sonicBoomVisual.draw();
    
    ofPopMatrix();
    m_postProcessing.end();
    ofPopStyle();
    ofDisableAlphaBlending();
}

void BattleOfSelfScene::drawFluid()
{
    ofPushStyle();
    //ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    ofEnableAlphaBlending();
    
    m_fbo.begin();
    
    ofSetColor(0,0,0, 40);
    ofRect(0,0,m_fbo.getWidth(),m_fbo.getHeight());
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetColor(120,120,255);
    m_fluid.draw(m_drawArea);
    
    m_fbo.end();
    ofDisableAlphaBlending();
    ofPopStyle();
    
    m_fbo.draw(0,0);
    
    //m_fluid.drawGui();
    
}


void BattleOfSelfScene::willFadeIn() {
    ofLogNotice("BattleOfSelfScene::willFadeIn");
    
    m_sonicBoomVisual.clear();
    m_fluid.reset();
    AppManager::getInstance().getGuiManager().setHandsOn(false);
    
    AppManager::getInstance().getGuiManager().setContourThickness(0.25);
}

void BattleOfSelfScene::willDraw() {
    ofLogNotice("BattleOfSelfScene::willDraw");
}

void BattleOfSelfScene::willFadeOut() {
    ofLogNotice("BattleOfSelfScene::willFadeOut");
}

void BattleOfSelfScene::willExit() {
    ofLogNotice("BattleOfSelfScene::willExit");
    
    m_sonicBoomVisual.clear();
    m_fluid.reset();
}