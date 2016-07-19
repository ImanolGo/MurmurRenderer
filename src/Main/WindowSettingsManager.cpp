/*
 *  WindowSettingsManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 27/02/15.
 *
 */

#include "ofMain.h"

#include "AppManager.h"
#include "WindowSettingsManager.h"

const int WindowSettingsManager::MAX_NUM_WINDOWS = 3; ///Defines the maximum number of windows available


WindowSettingsManager::WindowSettingsManager()
{
    //Intentionally left empty
}


WindowSettingsManager::~WindowSettingsManager()
{
    ofLogNotice() <<"WindowSettingsManager::Destructor";
}


void WindowSettingsManager::setup()
{
    ofLogNotice() << "WindowSettingsManager::initialized";
    this->readSettings();
}

void WindowSettingsManager::readSettings()
{
    // Get screen widths and heights from Quartz Services
    // See https://developer.apple.com/library/mac/documentation/GraphicsImaging/Reference/Quartz_Services_Ref/index.html
    
    CGDisplayCount displayCount;
    CGDirectDisplayID displays[32];
    
    // Grab the active displays
    CGGetActiveDisplayList(32, displays, &displayCount);
    int numDisplays= displayCount;
    
    for(int displayID = 0; displayID<numDisplays; displayID++)
    {
        //WindowSettingsPtr settings = WindowSettingsPtr (new ofGLFWWindowSettings());
        WindowSettings settings;
        
        settings.height = CGDisplayPixelsHigh ( displays[displayID] );
        settings.width = CGDisplayPixelsWide ( displays[displayID] );
        CGRect displayBounds= CGDisplayBounds (displays[displayID]);
        settings.x = displayBounds.origin.x;
        settings.y = displayBounds.origin.y;
        
        if(displayID==0){
            settings.showCursor = true;
        }
        
        if(displayID>0){
            settings.fullscreen = true;
        }

        settings.title = "MurmurRenderer : " + ofToString(displayID);
        m_windows.push_back(settings);
        
    }
    
    for(int displayID = numDisplays; displayID<MAX_NUM_WINDOWS; displayID++)
    {
        m_windows.push_back(m_windows.front());
    }
    
    
    ofLogNotice() << "WindowSettingsManager::readSettings -> Displays detected: " <<  numDisplays;
    
    int i = 0;
    for (auto windowSettings: m_windows)
    {
        ofLogNotice() << "WindowSettingsManager::readSettings -> Window " <<  i << ": x = " << windowSettings.x
        << ", y = " << windowSettings.y << ", width = " << windowSettings.width << ", height = " << windowSettings.height;
        i++;
    }
    
}

