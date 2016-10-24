/*
 *  AudioManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 30/07/15.
 *
 */


#include "AudioManager.h"
#include "AppManager.h"


AudioManager::AudioManager(): m_volume(0.5)
{
    //Intentionaly left empty
}


AudioManager::~AudioManager()
{
    ofLogNotice() <<"AudioManager::Destructor" ;
}


void AudioManager::setup()
{
    Manager::setup();
    
    ofLogNotice() <<"AudioManager::initialized" ;
    
    this->setupText();
    this->setupFFT();
}


void AudioManager::setupFFT()
{
    m_fft.setup();
    m_fft.setMirrorData(false);
    m_fft.setPeakDecay(0.915);
    m_fft.setMaxDecay(0.995);
    m_fft.setThreshold(1.0);
    m_fft.setVolume(m_volume);
}

void AudioManager::setupText()
{
    auto windowSettings = AppManager::getInstance().getSettingsManager().getWindowsSettings(0);
    
    ofVec3f position;
    
    float width =  (windowSettings.width - 4*LayoutManager::MARGIN - GuiManager::GUI_WIDTH)*0.5 - LayoutManager::MARGIN;
    int fontSize = 12;
    float height = fontSize*3;
    ofPtr<RectangleVisual> rect = AppManager::getInstance().getPreviewManager().getTopRectangle();
    float y_offset = rect->getPosition().y + rect->getHeight();
    //ofColor color = AppManager::getInstance().getSettingsManager().getColor("GUI1");
    
    string text = "AUDIO";
    float width_offset = (windowSettings.width - 4*LayoutManager::MARGIN - GuiManager::GUI_WIDTH)*0.5;
    
    position.x = GuiManager::GUI_WIDTH + 2.5*LayoutManager::MARGIN + LayoutManager::MARGIN  + width_offset;
    position.y = LayoutManager::MARGIN + y_offset;
    
    ofPtr<TextVisual> textVisual = ofPtr<TextVisual>(new TextVisual(position, width, height));
    textVisual->setText(text, "fonts/open-sans/OpenSans-Semibold.ttf", fontSize);
    textVisual->setColor(ofColor::white);
    
    AppManager::getInstance().getViewManager().addOverlay(textVisual);
    
    position.x -= LayoutManager::MARGIN*0.5;
    position.y -= LayoutManager::MARGIN*0.5;
    height = textVisual->getHeight() + LayoutManager::MARGIN;
    width = textVisual->getWidth() + LayoutManager::MARGIN;
    ofPtr<RectangleVisual> rectangleVisual = ofPtr<RectangleVisual>(new RectangleVisual(position, width, height));
    ofColor color(60,60,60);
    
    rectangleVisual->setColor(color);
    
    AppManager::getInstance().getViewManager().addOverlay(rectangleVisual,2);
    
    rect = AppManager::getInstance().getPreviewManager().getTopRectangle();
    m_circlePosition.x = rect->getPosition().x + rect->getWidth()*0.5;
    m_circlePosition.y = rectangleVisual->getPosition().y + rectangleVisual->getHeight() + (windowSettings.height - rectangleVisual->getPosition().y - rectangleVisual->getHeight())*0.3;
    
}

void AudioManager::update()
{
    if (!m_audioOn) {
        return;
    }
    
    m_fft.update();
    m_audioMax = ofMap(m_fft.getAveragePeak(), 0.0, 0.8, 0.0, 1.0, true);
    
    //ofLogNotice() <<"AudioManager::update: " << m_fft.getUnScaledLoudestValue();
    //ofLogNotice() <<"AudioManager::update2: " << m_fft.getLoudBand();
}

void AudioManager::draw()
{
    //m_fft.draw(340,600);
    this->drawCircle();
}

void AudioManager::drawCircle()
{
    int mainWindowIndex = 0;
    WindowSettings windowSettings = AppManager::getInstance().getSettingsManager().getWindowsSettings(mainWindowIndex);
    
    float radius = ofMap(m_fft.getAveragePeak(), 0.0, 1.0, windowSettings.height*0.05, windowSettings.height*0.15, true);
    
    //ofColor color = AppManager::getInstance().getSettingsManager().getColor("GUI1");
    
    ofPushStyle();
    ofSetCircleResolution(100);
    ofSetColor(ofColor::white);
        ofCircle(m_circlePosition, radius);
    ofPopStyle();
    
  
}


void AudioManager::onChangeVolume(float& value)
{
    m_volume = value;
    m_fft.setVolume(m_volume);
}

void AudioManager::setAudioMax(float audioMax)
{
    if(m_audioOn){
        return;
    }
    
    m_audioMax = audioMax;
}

void AudioManager::onChangeAudioOn(bool& value)
{
    m_audioOn = value;
    
}


float AudioManager::getAudioMax()
{
    return m_audioMax;
}



void AudioManager::onSendAudioVolume(float& value)
{
    ofxOscMessage m;
    m.setAddress("/MurmurContourTracking/AudioVolume");
    m.addFloatArg(value);
    AppManager::getInstance().getOscManager().sendMessageToContourTracking(m);
}
