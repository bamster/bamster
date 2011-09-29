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
	// only static const INTs maybe in-class constants
	// see Bjarne Stroustrup's C++ Style and Technique FAQ
	// http://www2.research.att.com/~bs/bs_faq2.html#in-class
        float jumpPower;
        enum  { xvel = 2 };
        enum {cadenz = 40};
            
        enum {size = 3};
	
        int waitingAnimationState;
        int saltoAnimationState;
	bool isRunning;

        bool facingLeft;
        GLuint bamsterRun[7];
        GLuint bamsterWait[4];
        GLuint bamsterJump[8];
	unsigned int addonType;
    public:
        bool isJumping;
        double timeLastFiring;
        double timeLastMoving;
        unsigned int framesJumping;


        bamster (double x, double y) : fallingObject(x,y),    framesJumping ( 0), facingLeft (true), timeLastFiring (0.0), jumpPower (5.0)
        {
            Image* image = loadBMP("animations/bamster_wait_r0.bmp");
            bamsterWait[0] = loadTexture(image);
            image = loadBMP("animations/bamster_wait_r1.bmp");
            bamsterWait[1] = loadTexture(image);
            image = loadBMP("animations/bamster_wait_r2.bmp");
            bamsterWait[2] = loadTexture(image);
            image = loadBMP("animations/bamster_wait_r3.bmp");
            bamsterWait[3] = loadTexture(image);
            image = loadBMP("animations/bamster_run_r0.bmp");

            bamsterRun[0] = loadTexture(image);
            image = loadBMP("animations/bamster_run_r0.bmp");
            bamsterRun[1] = loadTexture(image);
            image = loadBMP("animations/bamster_run_r1.bmp");
            bamsterRun[2] = loadTexture(image);
            image = loadBMP("animations/bamster_run_r2.bmp");
            bamsterRun[3] = loadTexture(image);
            image = loadBMP("animations/bamster_run_r3.bmp");
            bamsterRun[4] = loadTexture(image);
            image = loadBMP("animations/bamster_run_r4.bmp");
            bamsterRun[5] = loadTexture(image);
            image = loadBMP("animations/bamster_run_r5.bmp");
            bamsterRun[6] = loadTexture(image);
            image = loadBMP("animations/bamster_run_r6.bmp");

            delete image;
            hitpoints=1;
            gravity=1.0;
	    waitingAnimationState=0;
	    
        }
        
        void updateBoundingBox(); 
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
                    hitpoints--;
            else
                fallingObject::collision(with,fromWhere);

            }
	    if (with->getObjectInfo() == _addon_)
	    {
		    switch (((addon*)with)->addonType){
		    case 1:
			jumpPower = 6.0;
			break;
		    }
	    }
        }



        virtual bool timerCallback(double dt);


};






#endif
