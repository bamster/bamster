#include "bamster.h"




class bullet : player
{
	


};



class game 
{

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
            thePlayer-> timerCallback(0.5);

        }

};


