/*
 *  MaskManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 18/11/15.
 *
 */

#pragma once

#include "Manager.h"
#include "RectangleVisual.h"
#include "TextVisual.h"

//========================== class MaskManager ==============================
//============================================================================
/** \class MaskManager MaskManager.h
 *	\brief Class managing the preview of the application
 *	\details It reads the render visuals in the other windows and previews them in the main window
 */

class MaskManager: public Manager
{
public:

    //! Constructor
    MaskManager();

    //! Destructor
    ~MaskManager();

    //! Set-up the layout
    void setup();
    
    //! Begin fbo for a specific window
    void begin(int windowIndex);
    
    //! End fbo for a specific window
    void end(int windowIndex);
    

private:

    //! Set-up the shaders
    void setupShaders();
    
    //! Set-up the fbos
    void setupFbos();
    
    void setMaskWindowFront();
    
    void setMaskWindowTop();
    

private:
    
    typedef  vector<ofPtr<ofFbo> >                  FboVector;        ///< defines a vector of FBOs
    
    FboVector          m_fbos;
    
    ofShader        m_maskShader;
    
};

//==========================================================================


