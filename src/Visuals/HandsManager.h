/*
 *  HandsManager.h
 *  Murmur
 *
 *  Created by Imanol Gomez on 01/07/15.
 *
 */


#pragma once

#include "ofMain.h"
#include "Manager.h"

//========================== class HandsManager ==============================
//============================================================================
/** \class HandsManager HandsManager.h
 *	\brief Class managing the hands information
 *	\details It reads the hands given from the UDP messages and puts them into a texture
 */


class HandsManager: public Manager
 {

public:
    
    //! Constructor
    HandsManager();
    
    //! Destructor
    ~HandsManager();
    
    //! Setup the Hands Manager
    void setup();
    
    //! Draw the Hands Manager
    void draw();
     
    //! parses the hands information coming from the laser ranger
    void readHands(char const* udpMessage);
     
    const vector< ofPoint >& getHands() const {return m_hands;}
    
     
private:
     
     //! General routing to extract aligned integral types from the UDP packet.
     template<typename Type>
     char const* extract(char const* data, Type& type);
     
     //! If strings are null terminated in the buffer then this could be used to extract them.
     char const* extract(char const* data, std::string& s);

    
private:
     
    
    typedef vector< ofPoint > PointVector;
     
    PointVector   m_hands; ///< Vector holding the hands information
     
};



