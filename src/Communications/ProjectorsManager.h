/*
 *  ProjectorsManager.h
 *  Murmur
 *
 *  Created by Imanol Gomez on 15/10/16.
 *
 */


#pragma once

#include "ofMain.h"
#include "SettingsManager.h"
#include "ofxPanasonicControl.h"
#include "Manager.h"


//========================== class ProjectorsManager =======================================
//==============================================================================
/** \class ProjectorsManager ProjectorsManager.h
 *	\brief class for managing the networked panasonic projectors
 *	\details it controls and can turn on/off the projectors or the shutter
 */


class ProjectorsManager: public Manager
{
    
public:
    
    //! Constructor
    ProjectorsManager();

    //! Destructor
    virtual ~ProjectorsManager();

    //! setups the manager
    void setup();
    
    void setupProjectors();

    void shutterProjector1(bool& value);
    
    void shutterProjector2(bool& value);
    
    void shutterProjector(int num, bool value);
    
    void urlResponse(ofHttpResponse & response);
    
 private:
    
    typedef vector< ofPtr< ofxPanasonicControl> >  ProkectorsVector;
    ProkectorsVector   m_projectors;
    
};

