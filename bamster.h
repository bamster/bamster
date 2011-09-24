// vim: set ts=4 sw=4 expandtab sts=4:
#ifndef BAMSTER_H_INCLUDED
#define BAMSTER_H_INCLUDED

#include "keyLogger.h"

#include <iostream>

#include <GL/glut.h>
#include "objects.h"

using namespace std;




class bamster : public fallingObject {
    private:
        // Velocity in y-direction when bamster starts jumping
        float jumpPower;
        // Position of the bamster
//        float xpos, ypos;
        // Velocity of the bamster
        float xvel;//, yvel;

        bool facingLeft;
    public:
        bool isJumping;
        unsigned int framesJumping;


        bamster (double x, double y) : fallingObject(x,y),  jumpPower (12.0), xvel (1), framesJumping ( 0), facingLeft (true) 
        {
        }
        
        void updateBoundingBox(); 

        virtual void plot ();

        virtual void timerCallback(double dt);

};






#endif
