/*
 *  PreviewManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 29/09/15.
 *
 */

#pragma once

#include "Manager.h"
#include "TextVisual.h"
#include "SvgVisual.h"
#include "ImageVisual.h"

//========================== class PreviewManager ==============================
//============================================================================
/** \class PreviewManager PreviewManager.h
 *	\brief Class managing the preview of the application
 *	\details It reads the render visuals in the other windows and previews them in the main window
 */

class PreviewManager: public Manager
{
public:

    //! Constructor
    PreviewManager();

    //! Destructor
    ~PreviewManager();

    //! Set-up the layout
    void setup();
    
    //! Draw Layer
    void draw();
    
    //! Draw a specific fbo
    void draw(int windowIndex);
    
    //! Begin fbo for a specific window
    void begin(int windowIndex);
    
    //! End fbo for a specific window
    void end(int windowIndex);
    

private:

    //! Set-up the fbos
    void setupFbos();

private:
    
    typedef  vector<ofPtr<ofFbo> >      FboVector;            ///< defines a vector of FBOs
    
    FboVector                           m_fbos;


};

//==========================================================================


