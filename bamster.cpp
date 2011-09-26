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
                timeLastMoving = object::gameTime;
                xpos-= xvel * dt;
					 facingLeft = true;
				}
            if (pressedKeys.rightKey == true) {
                timeLastMoving = object::gameTime;
                xpos+= xvel * dt;
					facingLeft = false;
				}

				if ((pressedKeys.downKey == true) || (pressedKeys.spaceKey == true)) {  // firing
					
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



            if ((pressedKeys.upKey == true) && yvel == 0) {  // start jumping
                timeLastMoving = object::gameTime;
                    yvel += jumpPower;
				}
            if (yvel > 0)
            {
                if (pressedKeys.upKey == false)
						yvel = 0;
            }

				//updateBoundingBox();			
				return fallingObject::timerCallback(dt);
        }

        void bamster::plot()
        {
            Image* image = loadBMP("animations/bamster_wait_r0.bmp");
            GLuint bamster_wait_r0 = loadTexture(image);
            delete image;


            // render with qudas
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, bamster_wait_r0);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glDisable(GL_NORMALIZE);
            glColor3f(1, 1, 1);
            glNormal3f(0, 1, 0);
            glBegin(GL_QUADS);
            //glColor3f(0.0f, 1.0f,0.0f);
            if (facingLeft) {
                glTexCoord2f(1,0);
                glVertex2f(xpos -size, ypos - size);
                glTexCoord2f(0,0);
                glVertex2f(xpos + size, ypos - size); 
                glTexCoord2f(0,1);
                glVertex2f(xpos + size, ypos + size); 
                glTexCoord2f(1,1);
                glVertex2f(xpos - size, ypos + size);
            }
            else {
                glTexCoord2f(0,0);
                glVertex2f(xpos -size, ypos - size);
                glTexCoord2f(1,0);
                glVertex2f(xpos + size, ypos - size); 
                glTexCoord2f(1,1);
                glVertex2f(xpos + size, ypos + size); 
                glTexCoord2f(0,1);
                glVertex2f(xpos - size, ypos + size);
            }
            glEnd();
        }
        





