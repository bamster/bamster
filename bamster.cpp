#include "bamster.h"


void bamster::timerCallback(double dt)
        {

            if (pressedKeys.leftKey == true)
                xpos-= xvel * dt;
            if (pressedKeys.rightKey == true)
                xpos+= xvel * dt;

            if ((pressedKeys.upKey == true) && !isJumping)    // start jumping
                isJumping = true;

            if (isJumping)
            {
                if (pressedKeys.upKey == false)
                {
                    if ((jumpPower - framesJumping) * dt > 0)
							  framesJumping = jumpPower;

                }        
                framesJumping++;
                ypos = ypos + (jumpPower - framesJumping) * dt;
            }

				// collision with boundaries
            if (ypos < 5)
            {
                isJumping = false;
                framesJumping = 0;
                ypos = 5;    
            }
            if (xpos < 0)
                xpos = 0;
            if (xpos > 100)
                xpos = 100;


        }

        void bamster::plot()
        {

            glClear ( GL_COLOR_BUFFER_BIT ); //clear pixel buffer
            // render with points
            glBegin(GL_LINES);
            glColor3f(0.0f, 1.0f,0.0f);
				double size = 4.0;
            glVertex2f(xpos -size, ypos - size);
            glVertex2f(xpos + size, ypos - size); 
            glVertex2f(xpos + size, ypos - size); 
            glVertex2f(xpos + size, ypos + size); 
            glVertex2f(xpos + size, ypos + size); 
            glVertex2f(xpos - size, ypos + size);
            glVertex2f(xpos - size, ypos + size);
            glVertex2f(xpos - size, ypos - size);
            glEnd();





    //        glBegin(GL_POINTS);
            // render with points
//            glColor3f(0.0f, 1.0f,0.0f);
  //          glVertex2f(xpos,ypos); //display a point
      //      glEnd();
        } 
