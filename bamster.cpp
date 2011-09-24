#include "bamster.h"


void bamster::updateBoundingBox()

{
	b.xmin = xpos - 4.0;
	b.xmax = xpos + 4.0;
	b.ymin = ypos - 4.0;
	b.ymax = ypos + 4.0;

}

void bamster::timerCallback(double dt)
        {
			

            if (pressedKeys.leftKey == true) {
                xpos-= xvel * dt;
					 facingLeft = true;
				}
            if (pressedKeys.rightKey == true) {
               xpos+= xvel * dt;
					facingLeft = false;
				}

				if (pressedKeys.downKey == true) {  // firing
					if (facingLeft)
					{
						spawnObject(new bullet (-10.0,xpos, ypos));		
	
						xpos += 0.1;
					}
					else
					{
						spawnObject(new bullet (10.0,xpos, ypos));		
						xpos -= 0.1;
					}


				}



            if ((pressedKeys.upKey == true) && !isJumping)    // start jumping
				{ 
				 	yvel += jumpPower;	
					isJumping = true;

				}
            if (yvel > 0)
            {
                if (pressedKeys.upKey == false)
						yvel = 0;
            }

				// collision with boundaries
//            if (ypos < 5)
  //          {
    //            isJumping = false;
      //          framesJumping = 0;
        //        ypos = 5;    
          //  }
            if (xpos < 0)
                xpos = 0;
            if (xpos > 100)
                xpos = 100;
				fallingObject::timerCallback(dt); 
				updateBoundingBox();			

        }

        void bamster::plot()
        {

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
