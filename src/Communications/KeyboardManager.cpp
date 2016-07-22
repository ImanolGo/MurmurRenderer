/*
 *  KeyboardManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 17/06/15.
 *
 */


#include "KeyboardManager.h"
#include "AppManager.h"


KeyboardManager::KeyboardManager(): Manager()
{
    //Intentionally left empty
}

KeyboardManager::~KeyboardManager()
{
   ofUnregisterKeyEvents(this);
   ofLogNotice() << "KeyboardManager::destructor";
}


//--------------------------------------------------------------

void KeyboardManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    ofLogNotice() <<"KeyboardManager::initialized" ;
    this->addListeners();
}

void KeyboardManager::addListeners()
{
    ofRegisterKeyEvents(this); // this will enable the InteractiveVisual class to listen to the key events.
}

void KeyboardManager::keyPressed(ofKeyEventArgs &e)
{
    int key = e.key;
    
    ofLogNotice() <<"KeyboardManager::keyPressed-> " + ofToString(key);
    
    if(key == 'g' || key == 'G') {
        AppManager::getInstance().getGuiManager().toggleGui();
    }
    
    if(key == 'r' || key == 'R') {
        AppManager::getInstance().getOscManager().OscManager::onResetTopBackground();
    }
    
    if(key == 'p' || key == 'P') {
        AppManager::getInstance().getOscManager().OscManager::onFirePaperThrower();
    }
    
    if(key == OF_KEY_UP) {
        ofPoint pos = AppManager::getInstance().getLayoutManager().getCircleOffset();
        pos.y -= 2;
        AppManager::getInstance().getLayoutManager().setCircleOffset(pos);
    }
    
    
    if(key == OF_KEY_DOWN) {
        ofPoint pos = AppManager::getInstance().getLayoutManager().getCircleOffset();
        pos.y += 2;
        AppManager::getInstance().getLayoutManager().setCircleOffset(pos);
    }

    if(key == OF_KEY_RIGHT) {
        ofPoint pos = AppManager::getInstance().getLayoutManager().getCircleOffset();
        pos.x += 2;
        AppManager::getInstance().getLayoutManager().setCircleOffset(pos);
    }

    
    if(key == OF_KEY_LEFT) {
        ofPoint pos = AppManager::getInstance().getLayoutManager().getCircleOffset();
        pos.x -= 2;
        AppManager::getInstance().getLayoutManager().setCircleOffset(pos);
    }


    
    else if(key == ' ') {
        AppManager::getInstance().toggleDebugMode();
    }

}

void KeyboardManager::keyReleased(ofKeyEventArgs &e)
{
     //Intentionally left empty
}










