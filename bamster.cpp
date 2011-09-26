#include "bamster.h"


void bamster::updateBoundingBox()

{
	b.xmin = xpos - size;
	b.xmax = xpos + size;
	b.ymin = ypos - size;
	b.ymax = ypos + size;

}

bool bamster::timerCallback(double dt)
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
					
					if ((object::gameTime - timeLastFiring) > cadenz)
					{

					
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
						timeLastFiring = object::gameTime;

					}	

				}



            if ((pressedKeys.upKey == true) && yvel == 0)    // start jumping
				{ 
				 	yvel += jumpPower;	

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
//            if (xpos < 0)
  //              xpos = 0;
    //        if (xpos > 100)
      //          xpos = 100;
				fallingObject::timerCallback(dt); 
				updateBoundingBox();			
				return true;
        }

        void bamster::plot()
        {

            // render with points
            glBegin(GL_LINES);
            glColor3f(0.0f, 1.0f,0.0f);
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
