/*
 *  HandsManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 01/07/15.
 *
 */


#include "HandsManager.h"


HandsManager::HandsManager()
{
    //Intentionaly left empty
}


HandsManager::~HandsManager()
{
    ofLogNotice() <<"HandsManager::Destructor" ;
}


void HandsManager::setup()
{
    Manager::setup();
    
    ofLogNotice() <<"HandsManager::initialized" ;
    
}


void HandsManager::draw()
{
    ofPushStyle();
    ofSetColor(ofColor::white);
        for (auto hand: m_hands){
            hand.x = (hand.x - 0.5)*ofGetWidth();
            hand.y = (hand.x - 0.5)*ofGetHeight();
            ofCircle(hand, 20);
        }
    ofPopStyle();
}


void HandsManager::readHands(char const* data)
{
    //Formatting the message: 'X' <len(c8)> [<xpos(f32),ypos(f32)>] 'x'
    
    char const* p = data;
    
    char headerByte;
    p = extract(p, headerByte); // p contains next position to read
    
    if(headerByte == 'X') //Beginning of message
    {
        m_hands.clear();
        
        int8_t numberOfHands;
        p = extract(p, numberOfHands); // p contains next position to read
        
        for(int8_t i = 0; i < numberOfHands; i++) //Extract all the hands
        {
            Float32 x, y;
            p = extract(p, x); // p contains next position to read
            //x = htonl(x);
            p = extract(p, y); // p contains next position to read
            //y = htonl(y);
            m_hands.push_back(ofPoint(x,y));
        }
        
        char tailByte;
        p = extract(p, tailByte); // p contains next position to read
        
        if(headerByte == 'x') //Message correctly formatted
        {
            ofLogNotice() <<"HandsManager::readHands << Hands correctly parsed";
            return;
        }
        
    }
    
}


/**
 * General routing to extract aligned integral types
 * from the UDP packet.
 *
 * @param data Pointer into the UDP packet data
 * @param type Integral type to extract
 *
 * @return data pointer advanced to next position after extracted integral.
 */
template<typename Type>
char const* HandsManager::extract(char const* data, Type& type)
{
    // This union will ensure the integral data type is correctly aligned
    union tx_t
    {
        unsigned char cdata[sizeof(Type)];
        Type tdata;
    } tx;
    
    for(size_t i(0); i < sizeof(Type); ++i)
        tx.cdata[i] = data[i];
    
    type = tx.tdata;
    
    return data + sizeof(Type);
}

/**
 * If strings are null terminated in the buffer then this could be used to extract them.
 *
 * @param data Pointer into the UDP packet data
 * @param s std::string type to extract
 *
 * @return data pointer advanced to next position after extracted std::string.
 */
char const* HandsManager::extract(char const* data, std::string& s)
{
    s.assign((char const*)data, std::strlen((char const*)data));
    return data + s.size();
}
