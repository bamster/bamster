// vim: set ts=4 sw=4 expandtab sts=4:
#ifndef BAMSTER_H_INCLUDED
#define BAMSTER_H_INCLUDED

#include "keyLogger.h"

#include <iostream>

using namespace std;

class player {
    public:
        virtual void plot() = 0;
        virtual void timerCallback() = 0;
};




class bamster : public player {
    private:
        // Position of the bamster
        float bamsterPos[2];
        // Velocity of the bamster
        float bamsterVel[2];
        float jumpPower;
    public:
        bool isJumping;
        unsigned int framesSinceIStartedJumping;


        bamster ()
        {
            jumpPower = 3.0;
            bamsterPos [0] = 10;
            bamsterPos [1] = 10;
            bamsterVel [0] = 1;
            bamsterVel [1] = 1;
            framesSinceIStartedJumping = 0;

        }


        virtual void plot()
        {
            glBegin(GL_POINTS);
            // render with points
            glColor3f(0.0f, 1.0f,0.0f);
            glVertex2f(bamsterPos[0],bamsterPos[1]); //display a point
            glEnd();




        } 

        virtual void timerCallback()
        {

            if (pressedKeys.leftKey == true)
            { 
                bamsterPos[0]-= bamsterVel[0];
            }
            if (pressedKeys.rightKey == true)
                bamsterPos[0]+= bamsterVel[0];

            if ((pressedKeys.upKey == true) && !isJumping)
            {   cout << "moving up " << endl;
                isJumping = true;
            }
            if (isJumping)
            {
                framesSinceIStartedJumping++;
                bamsterPos[1] = bamsterPos[1] + (jumpPower - framesSinceIStartedJumping/3);
            }
            if (bamsterPos[1] < 5)
            {
                isJumping = false;
                framesSinceIStartedJumping = 0;
                bamsterPos[1] = 5;    
            }
            if (bamsterPos[0] < 0)
                bamsterPos[0] = 0;
            if (bamsterPos[0] > 100)
                bamsterPos[0] = 100;


        }

};



class game {

    private:
        player * thePlayer;

    public:
        game () {
            thePlayer = new bamster();
        }

        void plot()
        {

            glClear ( GL_COLOR_BUFFER_BIT ); //clear pixel buffer
            // render with points
            glBegin(GL_LINES);
            glColor3f(0.0f, 1.0f,0.0f);
            glVertex2f(0, 0);
            glVertex2f(100, 0); 
            glVertex2f(100, 0); 
            glVertex2f(100, 100); 
            glVertex2f(100, 100); 
            glVertex2f(0, 100);
            glVertex2f(0, 100);
            glVertex2f(0, 0);
            glEnd();


            thePlayer -> plot();
        }

        void timerCallback()
        {
            thePlayer-> timerCallback();

        }

};


#endif
