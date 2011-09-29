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


char otherSide (char side);

enum enum_objectInfo { _player_, _block_, _bullet_, _addon_, _undefined_};


typedef enum_objectInfo objectInfo;

class object {
		protected:
		public:
				static double gameTime;



				double xpos, ypos;
				boundingBox b;
				virtual void stopMeFalling(double height)
				{
						//yy	 ypos = ypos - b.ymin  + height;
						ypos = (b.ymax - b.ymin)/2.0  + height;
				}
				int hitpoints;
				object (double x, double y) : xpos (x), ypos(y) {}

				virtual objectInfo getObjectInfo() { return _undefined_;  }
				virtual ~object () {}


				virtual void updateBoundingBox() { cout << "updateBoundingBox of object called" << endl; }

				GLuint loadTexture(Image *image) {
						GLuint textureId;
						glGenTextures(1, &textureId);
						glBindTexture(GL_TEXTURE_2D, textureId);
						glTexImage2D(GL_TEXTURE_2D,
										0,
										GL_RGB,
										image->width, image->height,
										0,
										GL_RGB,
										GL_UNSIGNED_BYTE,
										image->pixels);
						return textureId;
				}


				char collidesWith (object &o)  // return 0 for no, 1 for horizontal, 2 for vertical collision
				{



						double distLeft = b.xmin - o.b.xmax;
						double distRight = o.b.xmin - b.xmax;
						double distUp = o.b.ymin - b.ymax;
						double distDown = b.ymin - o.b.ymax;

						bool collision = (distLeft < 0) && (distRight < 0) && ( distUp  < 0) && ( distDown < 0);
						if (collision)
						{
								if ((distLeft > distRight) && (distLeft > distUp) && (distLeft > distDown))
										return fromLeft;

								else if ((distRight > distLeft) && (distRight > distUp) && (distRight > distDown))
										return fromRight;

								else if ((distUp > distRight) && (distUp > distLeft) && (distUp > distDown))
										return fromUp;

								else
										return fromDown;
						}
						return 0;
				}
				//		  virtual void collision() = 0;
				virtual void plot() { cout << "plot of object called" << endl; }
				virtual bool timerCallback (double dt) {return true;}
				virtual void collision (object *with, char fromWhere) { }
};

class fallingObject : public object
{
		private:
		public:
				float yvel;
				double gravity;
				unsigned int hitpoints;
				fallingObject (double x, double y) : object (x,y), gravity(0.1) {}	
				//virtual ~fallingObject() {
				//}
	
				virtual void stopMeFalling (double height)
				{
						cout << "autsch" << endl;
						yvel = 0;
						object::stopMeFalling (height);
				}

				virtual void collision (object *with, char fromWhere)
				{
						if (fromWhere == fromDown)
						{
								yvel = 0;
								ypos = (b.ymax - b.ymin)/2.0  + with->b.ymax;
						}

				}	

				virtual objectInfo getObjectInfo() { return _undefined_;}

				virtual bool timerCallback(double dt)
				{
						ypos += yvel* dt;
						yvel -= gravity*dt;
						updateBoundingBox();
						if (hitpoints == 0)
								return 0;
						else 
								return 1;
						return true;
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



class block: public fallingObject
{
		private:
				double size;
		public:
				virtual void plot() {
						glColor3f(rand()%100*0.01, rand()%100*0.01, rand()%100*0.01);
						glBegin(GL_QUADS);
						glVertex2f(xpos - size / 2, ypos- size / 2);
						glVertex2f(xpos + size / 2, ypos- size / 2);
						glVertex2f(xpos + size / 2, ypos+ size / 2);
						glVertex2f(xpos - size / 2, ypos+ size / 2);
						glEnd();	
				}
				void updateBoundingBox ()
				{
						b.xmin = xpos - size / 2;
						b.xmax = xpos + size / 2;
						b.ymin = ypos - size / 2;
						b.ymax = ypos + size / 2;
				}			
				block (double x, double y, double l) : fallingObject (x,y), size ( l)  {  updateBoundingBox();  hitpoints=3; };
				virtual ~block();
				virtual void collision (object *with, char fromWhere) {
						if (with->getObjectInfo() == _bullet_)
						{
								//		_		if (fromWhere== fromLeft || fromWhere == fromRight)
								//				{
								hitpoints = hitpoints -1;
								//				}
						}
						fallingObject::collision(with,fromWhere);
				}


				virtual bool timerCallback(double dt)
				{
						return fallingObject::timerCallback(dt);

				}

};


class bullet : public object
{
		private:
				double speed;
				bool hitSomething;
		public:
				bullet (double s, double x, double y) : speed(s), object(x,y), hitSomething(false) {}
				void plot ()
				{	
						double size = 0.3;
						glNormal3f(0, 1, 0);
						glBegin(GL_QUADS);
						glColor3f(1, 1, 1);
						glTexCoord2f(1,0);
						glVertex2f(xpos -size*4, ypos - size);
						glTexCoord2f(0,0);
						glVertex2f(xpos + size*4, ypos - size); 
						glTexCoord2f(0,1);
						glVertex2f(xpos + size*4, ypos + size); 
						glTexCoord2f(1,1);
						glVertex2f(xpos - size*4, ypos + size);
						glEnd();
				}

				virtual objectInfo getObjectInfo() { return _bullet_;  }
				void updateBoundingBox ()
				{
						b.xmin = xpos - 1.2;
						b.xmax = xpos + 1.2;
						b.ymin = ypos - 0.3;
						b.ymax = ypos - 0.3;
				}
				virtual void collision (object *with, char fromWhere) {
						if (with->getObjectInfo() != _player_ && with->getObjectInfo() != _bullet_)
								hitSomething = true;  	
				}

				bool timerCallback (double dt)
				{
						xpos += dt * speed;
						updateBoundingBox();
						return !hitSomething;
				}	


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
