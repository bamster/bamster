#include "bamster.h"

#include <list>




class game 
{

    private:
        player * thePlayer;
		  list<player *> otherObjects;
		  
    public:
        game () {
            thePlayer = new bamster();
        }
	
		  void spawnObject(player *p)
		  {
			  otherObjects.push_back (p);
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
				
				list<player *>::iterator it;
				for (it = otherObjects.begin(); it != otherObjects.end(); it ++)
					(*it)->plot();

        }

        void timerCallback()
        {
				list<player *>::iterator it;
            thePlayer-> timerCallback(0.5);
				for (it = otherObjects.begin(); it != otherObjects.end(); it ++)
					(*it)->timerCallback(0.5);

        }

};



