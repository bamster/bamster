#ifndef objects_h
#define objects_h objects_h

#include <X11/Xlib.h>
#include <GL/glut.h>

#include <iostream>

using namespace std;

struct boundingBox
{
	double xmin;
	double xmax;
	double ymin;
	double ymax;
};


const double gravity = 0.5;



class object {
	protected:
	public:

		double xpos, ypos;
		boundingBox b;
		virtual void stopMeFalling(double height)
		{
		//yy	 ypos = ypos - b.ymin  + height;
		 ypos = (b.ymax - b.ymin)/2.0  + height;
		}
		int hitpoints;
		object (double x, double y) : xpos (x), ypos(y) {}

		virtual void updateBoundingBox() { cout << "updateBoundingBox of object called" << endl; }


		char collidesWith (object &o)  // return 0 for no, 1 for horizontal, 2 for vertical collision
		{
			  
			int ret 
				= 2 *( 
						((o.b.ymin < b.ymax) && (o.b.ymax > b.ymax)) ||
						((o.b.ymax > b.ymin) && (o.b.ymin < b.ymin)) ) +
					(
						((o.b.xmin < b.xmax) && (o.b.xmax > b.xmax)) ||
						((o.b.xmax > b.xmin) && (o.b.xmin < b.xmin))  );
							
			cout << ret << endl;
			return ret;
		}
		//		  virtual void collision() = 0;
		virtual void plot() { cout << "plot of object called" << endl; }
		virtual void timerCallback (double dt) {}
};

class fallingObject : public object
{
	private:
public:
		float yvel;
		fallingObject (double x, double y) : object (x,y) {}	

		virtual void stopMeFalling (double height)
		{
			cout << "autsch" << endl;
			yvel = 0;
			object::stopMeFalling (height);
		}

		virtual void timerCallback(double dt)
		{
			ypos += yvel* dt;
			yvel -= gravity*dt;
		}

};

class game ;

extern game * activGame;

void spawnObject (object *p);



class vwall : public object
{
	private:
		double length;
	public:
		virtual void plot() {
			glBegin(GL_LINES);
			glColor3f(0.0f, 1.0f,0.0f);
			glVertex2f(xpos, ypos - length / 2);
			glVertex2f(xpos, ypos + length / 2); 
			glEnd();	
		}
		void updateBoundingBox ()
		{
			b.xmin = b.xmax = xpos;
			b.ymin = ypos - length / 2;
			b.ymax = ypos + length / 2;
		}			
		vwall (double x, double y, double l) : object (x,y), length ( l) { updateBoundingBox(); };
};

class hwall : public object
{
	private:
		double xpos;
		double ypos;
		double length;
	public:
		virtual void plot() {
			glBegin(GL_LINES);
			glColor3f(0.0f, 1.0f,0.0f);
			glVertex2f(xpos - length / 2, ypos);
			glVertex2f(xpos + length / 2, ypos);
			glEnd();	
		}
		void updateBoundingBox ()
		{
			b.ymin = b.ymax = ypos;
			b.xmin = xpos - length / 2;
			b.xmax = xpos + length / 2;
		}			
		hwall (double x, double y, double l) : object (x,y), length ( l) {  updateBoundingBox();   };
};


class bullet : public object
{
	private:
		double speed;
	public:
		bullet (double s, double x, double y) : speed(s), object(x,y) {}
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

		void updateBoundingBox ()
		{
			b.xmin = xpos - 2.0;
			b.xmax = xpos + 2.0;
			b.ymin = ypos - 2.0;
			b.ymax = ypos - 2.0;
		}

		void timerCallback (double dt)
		{
			xpos += dt * speed;
		}	


};



#endif
