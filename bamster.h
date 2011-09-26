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
        static const float jumpPower = 5.0;
        static const float xvel = 2.0;
        static const float cadenz = 10.0;
            
        static const float size = 3.0;

        int waitingAnimationState;
        int saltoAnimationState;

        // Position of the bamster
//        float xpos, ypos;
        // Velocity of the bamster

        bool facingLeft;
        GLuint bamsterRun[7];
        GLuint bamsterWait[4];
        GLuint bamsterJump[8];
    public:
        bool isJumping;
        double timeLastFiring;
        double timeLastMoving;
        unsigned int framesJumping;


        bamster (double x, double y) : fallingObject(x,y),    framesJumping ( 0), facingLeft (true), timeLastFiring (0.0)
        {
            Image* image = loadBMP("animations/bamster_wait_r0.bmp");
            bamsterWait[0] = loadTexture(image);
            image = loadBMP("animations/bamster_wait_r1.bmp");
            bamsterWait[1] = loadTexture(image);
            image = loadBMP("animations/bamster_wait_r2.bmp");
            bamsterWait[2] = loadTexture(image);
            image = loadBMP("animations/bamster_wait_r3.bmp");
            bamsterWait[3] = loadTexture(image);
            delete image;
            hitpoints=1;
            gravity=1.0;
        }
        
        void updateBoundingBox(); 
        void loadAnimations();
        virtual void plot ();
		virtual objectInfo getObjectInfo() { return _player_;} 
            

		virtual void collision (object *with, char fromWhere)
        {

            if (with->getObjectInfo() != _bullet_)
            {

            if (fromWhere == fromLeft)
                xpos = (b.xmax - b.xmin) / 2.0 + with-> b.xmax;
            if (fromWhere == fromRight)
                xpos =with-> b.xmin  -  (b.xmax - b.xmin) / 2.0;
            if (fromWhere == fromUp)
                //if (((fallingObject *)with)->yvel<0)
                    hitpoints--;
            else
                fallingObject::collision(with,fromWhere);

            }
        }



        virtual bool timerCallback(double dt);


};






#endif
