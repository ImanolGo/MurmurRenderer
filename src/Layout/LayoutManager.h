/*
 *  LayoutManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 17/06/15.
 *
 */

#pragma once

#include "Manager.h"
#include "TextVisual.h"
#include "SvgVisual.h"
#include "ImageVisual.h"

//========================== class LayoutManager ==============================
//============================================================================
/** \class LayoutManager LayoutManager.h
 *	\brief Class managing the layout of the application
 *	\details It creates an places al the text and elements regarding the layout
 */

class LayoutManager: public Manager
{
public:

    //! Constructor
    LayoutManager();

    //! Destructor
    ~LayoutManager();

    //! Set-up the layout
    void setup();
    
    //! Draw Layer
    void draw();
    
    
    
     int getCropLeft() const {return m_cropLeft;}
    
     int getCropRight() const {return m_cropRight;}
    
     int getCropTop() const {return m_cropTop;}
    
     int getCropBottom() const {return m_cropBottom;}
    
    
    void onCropLeft( int & pixels) {m_cropLeft = pixels;}
    
    void onCropRight( int & pixels) {m_cropRight = pixels;}
    
    void onCropTop( int & pixels) {m_cropTop = pixels;}
    
    void onCropBottom( int & pixels){m_cropBottom = pixels;}
    

private:


    //! Create the text visuals
    void createTextVisuals();

    //! Create the svg visuals
    void createSvgVisuals();

    //! Create the image visuals
    void createImageVisuals();

    //! Create the background Image
    void createBackground();

    //! Add all visuals as overlays
    void addVisuals();

public:
    
    static const int MARGIN;
    static const int PADDING;


private:


    typedef  map<string, ofPtr<TextVisual> >      TextMap;            ///< defines a map of Text attached to an identifier
    typedef  map<string, ofPtr<SvgVisual>  >      SvgMap;             ///< defines a map of SvgVisual Map attached to an identifier
    typedef  map<string, ofPtr<ImageVisual>  >    ImageMap;           ///< defines a map of ImageVisual Map attached to an identifier
  
    TextMap             m_textVisuals;             ///< map storing the text visuals attached to a name
    SvgMap              m_svgVisuals;              ///< map storing the svg visuals attached to a name
    ImageMap            m_imageVisuals;            ///< map storing the image visuals attached to a name
    
    int                 m_cropLeft, m_cropRight, m_cropTop, m_cropBottom;
};

//==========================================================================


