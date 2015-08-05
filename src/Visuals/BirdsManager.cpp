/*
 *  BirdsManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 05/08/15.
 *
 */


#include "FluidVisual.h"
#include "BirdsManager.h"


BirdsManager::BirdsManager()
{
    //Intentionaly left empty
}


BirdsManager::~BirdsManager()
{
    ofLogNotice() <<"BirdsManager::Destructor" ;
}


void BirdsManager::setup()
{
    Manager::setup();
    
    ofLogNotice() <<"BirdsManager::initialized" ;
    
}



void BirdsManager::update()
{
}

void BirdsManager::draw()
{
    
}



