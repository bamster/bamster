#ifndef objects_h
#define objects_h objects_h



class player {
    public:
        virtual void plot() = 0;
        virtual void timerCallback(double dt) = 0;
};

class game ;

extern game * activGame;

void spawnObject (player *p);



class bullet : public player
{
	private:
		double speed;
		double xpos;
		double ypos;
	public:
	bullet (double s, double x, double y) : speed(s), xpos(x), ypos(y) {}
	void plot ()
	{	
            // render with points
            glBegin(GL_LINES);
            glColor3f(0.0f, 1.0f,0.0f);
				double size = 2.0;
            glVertex2f(xpos -size, ypos - size);
            glVertex2f(xpos + size, ypos - size); 
            glVertex2f(xpos + size, ypos - size); 
            glVertex2f(xpos + size, ypos + size); 
            glVertex2f(xpos + size, ypos + size); 
            glVertex2f(xpos - size, ypos + size);
            glVertex2f(xpos - size, ypos + size);
            glVertex2f(xpos - size, ypos - size);
            glEnd();
	}
	void timerCallback (double dt)
	{
		xpos += dt * speed;
	}	


};



#endif
