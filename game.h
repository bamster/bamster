#include "bamster.h"

#include <list>




class game 
{

    private:
        object * thePlayer;
		  list<object *> otherObjects;
		  
    public:
        game () {
            otherObjects.push_back(new bamster( 20, 50));
				otherObjects.push_back(new hwall (50,0,100));
				otherObjects.push_back(new hwall (50,100,100));

				otherObjects.push_back(new hwall (0,50,100));
				otherObjects.push_back(new hwall (100,50,100));
        }
	
		  void spawnObject(object *p)
		  {
			  otherObjects.push_back (p);
		  }

			void handleCollisions();

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


//            thePlayer -> plot();
				
				list<object *>::iterator it;
				for (it = otherObjects.begin(); it != otherObjects.end(); it ++)
					(*it)->plot();

        }

        void timerCallback()
        {
				list<object *>::iterator it;
  //          thePlayer-> timerCallback(0.5);
				for (it = otherObjects.begin(); it != otherObjects.end(); it ++)
					(*it)->timerCallback(0.5);
	
				handleCollisions();


        }

};



