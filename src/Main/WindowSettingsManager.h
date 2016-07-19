/*
 *  WindowSettingsManager.h
 *
 *  Created by Imanol Gomez on 27/02/16.
 *
 */

#pragma once

#include "ofMain.h"



//========================== class WindowSettingsManager ==============================
//============================================================================
/** \class WindowSettingsManager WindowSettingsManager.h
 *	\brief Class managing the window settings
 *	\details it setups and provides access the window settings
 */


class WindowSettingsManager
{
      static const int MAX_NUM_WINDOWS; ///Defines the maximum number of windows available
    
public:
    
    typedef     vector<WindowSettings>    WindowSettingsVector;   ///< Vector of WindowSettingsPtr
    

    //! Constructor
    WindowSettingsManager();
    
    //! Destructor
    ~WindowSettingsManager();

    //! Setup
    void setup();
    
    const WindowSettingsVector&  getWindowsSettings(){return m_windows;}

private:
    
    //! Read all the window settings
    void readSettings();


private:

    
    WindowSettingsVector           m_windows;                 ///< Vector holding all the window settings

};

//==========================================================================
