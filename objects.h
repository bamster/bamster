#ifndef objects_h
#define objects_h objects_h

#include <X11/Xlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

#include "imageloader.h"

using namespace std;

struct boundingBox
{
		double xmin;
		double xmax;
		double ymin;
		double ymax;
};


//const double gravity = 1.0;

const char fromLeft = 1;
const char fromRight = 2;
const char fromUp = 3;
const char fromDown = 4;

const static double colors[5][3] = {
	{1.,0.,0.},
	{0.,1.,0.},
	{0.,0.,1.},
	{1.,0.,1.},
	{0.,1.,1.}
} ;

char otherSide (char side);

enum enum_objectInfo { _player_, _block_, _bullet_, _addon_, _undefined_};


typedef enum_objectInfo objectInfo;


class game;

class object {
		protected:
		public:
				static game * activGame;
				static double gameTime;
				double xpos, ypos;
				boundingBox b;
		virtual void stopMeFalling(double height);
				int hitpoints;
		object (double x, double y); 
		virtual objectInfo getObjectInfo();
		virtual void updateBoundingBox();
		GLuint loadTexture(Image *image);
		char collidesWith (object &o);
		virtual void plot();
		virtual bool timerCallback(double dt);
		virtual void collision(object *with, char fromWhere);
};

class fallingObject : public object
{
		private:
	public:
				float yvel;
				double gravity;
				unsigned int hitpoints;
		fallingObject (double x, double y);
		virtual void stopMeFalling (double height);
		virtual void collision (object *with, char fromWhere);
		virtual objectInfo getObjectInfo();
		virtual bool timerCallback(double dt);
};



class vwall : public object
{
		private:
				double length;
		public:
		virtual void plot();
		void updateBoundingBox ();
		vwall (double x, double y, double l);
};

class hwall : public object
{
		private:
				double length;
		public:
		virtual void plot();
		void updateBoundingBox ();
		hwall (double x, double y, double l);
};

class block: public fallingObject
{
		private:
				double size;
		double red;
		double green; 
		double blue;
		public:
		virtual void plot();
		void updateBoundingBox ();
		block (double x, double y, double l, unsigned int color);
				virtual ~block();
		virtual void collision (object *with, char fromWhere);
		virtual bool timerCallback(double dt);
};


class bullet : public object
{
		private:
				double speed;
				bool hitSomething;
		public:
		bullet (double s, double x, double y);
		void plot ();
		virtual objectInfo getObjectInfo();
		void updateBoundingBox ();
		virtual void collision (object *with, char fromWhere);
		bool timerCallback (double dt);
};

class addon : public fallingObject
{
		private:
				double size;
				bool gotCollected;
				GLuint animation;
		public:
			
			unsigned int addonType;
		addon (double x, double y, double l, int t) : fallingObject (x,y), size ( l), addonType (t),gotCollected (false)  {  
				updateBoundingBox();
				hitpoints=3;
		
            Image* image = loadBMP("animations/jumpingShoes.bmp");
            animation = loadTexture(image);
			delete image;
		
		};
				virtual void plot() {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, animation);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glDisable(GL_NORMALIZE);
            glColor3f(1, 1, 1);
            glNormal3f(0, 1, 0);
            glBegin(GL_QUADS);
            //glColor3f(0.0f, 1.0f,0.0f);
		glTexCoord2f(1,0);
		glVertex2f(xpos -size, ypos - size);
		glTexCoord2f(0,0);
		glVertex2f(xpos + size, ypos - size); 
		glTexCoord2f(0,1);
		glVertex2f(xpos + size, ypos + size); 
		glTexCoord2f(1,1);
		glVertex2f(xpos - size, ypos + size);
            glEnd();
            glEnable(GL_NORMALIZE);
            glDisable(GL_TEXTURE_2D);
				}
				void updateBoundingBox ()
				{
						b.xmin = xpos - size / 2;
						b.xmax = xpos + size / 2;
						b.ymin = ypos - size / 2;
						b.ymax = ypos + size / 2;
				}			
				virtual objectInfo getObjectInfo() { return _addon_;  }
				virtual void collision (object *with, char fromWhere) {
						if (fromWhere == fromDown)
						{
								yvel = 0;
								ypos = (b.ymax - b.ymin)/2.0  + with->b.ymax;
						}
						if (with->getObjectInfo() == _player_)
								gotCollected = true;
				}
				bool timerCallback (double dt)
				{
						ypos += yvel* dt;
						yvel -= gravity*dt;
						updateBoundingBox();
					return !gotCollected;
				}
};

#endif
