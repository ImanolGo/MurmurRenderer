/*
 *  FluidVisual.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 05/05/15.
 *
 */


#include "ofMain.h"

#include "AppManager.h"

#include "FluidVisual.h"


const int FluidVisual::FLUID_WIDTH = 1280;
const int FluidVisual::FLUID_HEIGHT = 720;

FluidVisual::FluidVisual()
{
    //Intentionaly left empty
}


FluidVisual::~FluidVisual()
{
    //Intentionaly left empty
}


void FluidVisual::setup()
{
    this->setupFluid();
    //ofLogNotice()<< "FluidVisual::SETUP!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
}


void FluidVisual::setupFluid()
{
    
    // process all but the density on 16th resolution
    int flowWidth = FLUID_WIDTH/4;
    int flowHeight = FLUID_HEIGHT/4;
    
    // Flow & Mask
    m_opticalFlow.setup(flowWidth, flowHeight);
    m_velocityMask.setup(FLUID_WIDTH, FLUID_HEIGHT);
    
    // m_fluid
    #ifdef USE_FASTER_INTERNAL_FORMATS
        m_fluid.setup(flowWidth, flowHeight, FLUID_WIDTH, FLUID_HEIGHT, true);
    #else
        m_fluid.setup(flowWidth, flowHeight, FLUID_WIDTH, FLUID_HEIGHT, false);
    #endif
    
    
    // Visualisation
    m_displayScalar.allocate(flowWidth, flowHeight);
    m_velocityField.allocate(flowWidth / 4, flowHeight / 4);
    m_temperatureField.allocate(flowWidth / 4, flowHeight / 4);
    
    // Draw Forces
    m_numDrawForces = 3;
    m_flexDrawForces = new ftDrawForce[m_numDrawForces];
    m_flexDrawForces[0].setup(FLUID_WIDTH, FLUID_HEIGHT, FT_DENSITY, false);
    m_flexDrawForces[0].setName("draw full res");
    m_flexDrawForces[1].setup(flowWidth, flowHeight, FT_VELOCITY, false);
    m_flexDrawForces[1].setName("draw flow res 1");
    m_flexDrawForces[2].setup(flowWidth, flowHeight, FT_TEMPERATURE, false);
    m_flexDrawForces[2].setName("draw flow res 2");
    
    
    m_opticalFlow.setStrength(100);
    m_opticalFlow.setOffset(3);
    m_opticalFlow.setLambda(0.01);
    m_opticalFlow.setThreshold(0.0255);
    m_opticalFlow.setTimeBlurActive(true);
    m_opticalFlow.setTimeBlurDecay(0.1201);
    m_opticalFlow.setTimeBlurRadius(2);
    
    m_velocityMask.strength = 10;
    
    
    
    m_fluid.setSpeed(48);
    m_fluid.setCellSize(1.25);
    m_fluid.setNumJacobiIterations(40);
    m_fluid.setViscosity(0.88);
    m_fluid.setVorticity(0.061);
    m_fluid.setDissipation(0.0018);
    m_fluid.setDissipationVelocityOffset(0);
    m_fluid.setDissipationDensityOffset(0);
    m_fluid.setDissipationTemperatureOffset(0);
    m_fluid.setSmokeSigma(0);
    m_fluid.setSmokeWeight(0.0681);
    m_fluid.setAmbientTemperature(0) ;
    m_fluid.setGravity(ofPoint(0,100));
    m_fluid.setClampForce(0.073) ;
    m_fluid.setMaxVelocity(4.4) ;
    m_fluid.setMaxDensity(0.96);
    m_fluid.setMaxTemperature(2.334);
    m_fluid.setDensityFromVorticity(0) ;
    m_fluid.setDensityFromPressure(0.153) ;
}


void FluidVisual::update()
{
    this->updateFluid();
}

void FluidVisual::updateFluid()
{
    double dt = ofGetLastFrameTime();
    
    m_fluid.addVelocity(m_opticalFlow.getOpticalFlowDecay());
    m_fluid.addDensity(m_velocityMask.getColorMask());
    m_fluid.addTemperature(m_velocityMask.getLuminanceMask());
    
    for (int i=0; i<m_numDrawForces; i++) {
        m_flexDrawForces[i].update();
        if (m_flexDrawForces[i].didChange()) {
            // if a force is constant multiply by deltaTime
            float strength = m_flexDrawForces[i].getStrength();
            if (!m_flexDrawForces[i].getIsTemporary())
                strength *=dt;
            switch (m_flexDrawForces[i].getType()) {
                case FT_DENSITY:
                    m_fluid.addDensity(m_flexDrawForces[i].getTextureReference(), strength);
                    break;
                case FT_VELOCITY:
                    m_fluid.addVelocity(m_flexDrawForces[i].getTextureReference(), strength);
                    break;
                case FT_TEMPERATURE:
                    m_fluid.addTemperature(m_flexDrawForces[i].getTextureReference(), strength);
                    break;
                case FT_PRESSURE:
                    m_fluid.addPressure(m_flexDrawForces[i].getTextureReference(), strength);
                    break;
                case FT_OBSTACLE:
                    m_fluid.addTempObstacle(m_flexDrawForces[i].getTextureReference());
                default:
                    break;
            }
        }
    }
    
    m_fluid.update();
}

void FluidVisual::draw()
{
    ofClear(0);
    
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    
    m_source.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
     m_fluid.draw(0, 0, ofGetWidth(), ofGetHeight());
    ofPopStyle();

    
   
    //ofLogNotice() << "FluidVisual::draw()-> " << ofGetWidth();
}

void FluidVisual::setSource(const ofFbo& source)
{
    double dt = ofGetLastFrameTime();
    
    m_source =  source;
    
    m_opticalFlow.setSource(m_source.getTextureReference());
    m_opticalFlow.update(dt);
    
    m_velocityMask.setDensity(m_source.getTextureReference());
    m_velocityMask.setVelocity(m_opticalFlow.getOpticalFlow());
    m_velocityMask.update();
}



