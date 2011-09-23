// vim: set ts=4 sw=4 expandtab sts=4:
#ifndef BAMSTER_H_INCLUDED
#define BAMSTER_H_INCLUDED

#include "keyLogger.h"

#include <iostream>

#include <GL/glut.h>
using namespace std;

class player {
    public:
        virtual void plot() = 0;
        virtual void timerCallback(double dt) = 0;
};




class bamster : public player {
    private:
        // Velocity in y-direction when bamster starts jumping
        float jumpPower;
        // Position of the bamster
        float xpos, ypos;
        // Velocity of the bamster
        float xvel, yvel;
    public:
        bool isJumping;
        unsigned int framesJumping;


        bamster () : jumpPower (12.0), xpos (10), ypos (10), xvel (1), yvel (1), framesJumping ( 0) 
        {
        }

        virtual void plot ();

        virtual void timerCallback(double dt);

};






#endif
