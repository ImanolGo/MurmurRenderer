/*
 *  FluidVisual.h
 *  Murmur
 *
 *  Created by Imanol Gomez on 29/05/15.
 *
 */


#pragma once

#include "ofxFlowTools.h"
#include "ofxGui.h"

#define USE_FASTER_INTERNAL_FORMATS			// about 15% faster but gives errors from ofGLUtils
using namespace flowTools;

//========================== class FluidManager ==============================
//============================================================================
/** \class FluidVisual FluidVisual.h
 *	\brief Class managing the fluid visuals
 *	\details It creates and manages all the parameters and fluid-like visualizations 
 */


class FluidVisual
{
    
public:
    
    //! Constructor
    FluidVisual();
    
    //! Destructor
    ~FluidVisual();
    
    //! Setup the Halo Visuals
    void setup();
    
    //! Update the Halo Visuals
    void update();
    
    //! Draw the Halo Visuals
    void draw();
    
    //! Set the source texture use to create the fluid
    void setSource(const ofFbo& source);
    
    //Gui
    void resetDrawForces(bool& _value) { if (_value) {for (int i=0; i<m_numDrawForces; i++) m_flexDrawForces[i].reset();}}
    void setDisplayScalarScale(float& _value) { m_displayScalar.setScale(_value); }
    void setVelocityFieldArrowScale(float& _value) { m_velocityField.setVectorSize(_value); }
    void setTemperatureFieldBarScale(float& _value) { m_temperatureField.setVectorSize(_value); }
    void setVisualisationLineSmooth(bool& _value) { m_velocityField.setLineSmooth(_value); }
     
public:
    
    static const int FLUID_WIDTH;
    static const int FLUID_HEIGHT;
    
private:
    
    
    void drawVisuals();
    
    void setupFluid();
    
    void updateFluid();
    
    void drawFluid();
    
public:
    
    ftOpticalFlow		m_opticalFlow;
    ftVelocityMask		m_velocityMask;
    ftFluidSimulation	m_fluid;
    
    ftDisplayScalar		m_displayScalar;
    ftVelocityField		m_velocityField;
    ftTemperatureField	m_temperatureField;
    
    int					m_numDrawForces;
    ftDrawForce*		m_flexDrawForces;
    
    ofFbo               m_source;
    
    
};



