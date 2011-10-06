#ifndef BAMSTER_H_INCLUDED
#define BAMSTER_H_INCLUDED

#include "keyLogger.h"

#include <iostream>
#include <vector>
#include <GL/glut.h>
#include "objects.h"
#include "SDL/SDL.h"


using namespace std;

extern SDL_Surface *screen;
class weapon
{
	protected:
		double timeLastFiring;
	public:
		weapon () : timeLastFiring (0) {}
		virtual double fireLeft (double xpos, double ypos, double hamsterSpeed) = 0;
		virtual double fireRight (double xpos, double ypos, double hamsterSpeed) = 0;


};


class laser : public weapon
{
	double kadenz;
	public:
	virtual double fireLeft (double xpos, double ypos, double hamsterSpeed);
	virtual double fireRight (double xpos, double ypos, double hamsterSpeed);

	laser () : kadenz (50) {}


};

class tripelLaser : public weapon
{
	double kadenz;
	public:
	virtual double fireLeft (double xpos, double ypos, double hamsterSpeed);
	virtual double fireRight (double xpos, double ypos, double hamsterSpeed);

	tripelLaser () : kadenz (90) {}
};


class schneeSchieber : public weapon
{
	double kadenz;
	public:
	virtual double fireLeft (double xpos, double ypos, double hamsterSpeed);
	virtual double fireRight (double xpos, double ypos, double hamsterSpeed);

	schneeSchieber () : kadenz (110) {}
};


class bamster : public fallingObject {
	private:
		// Velocity in y-direction when bamster starts jumping
		// only static const INTs maybe in-class constants
		// see Bjarne Stroustrup's C++ Style and Technique FAQ
		// http://www2.research.att.com/~bs/bs_faq2.html#in-class


		vector <weapon *> weapons;
		unsigned int activeWeapon;

		double xvel;
		enum {cadenz = 40};
		double size;

		objectInfo collisionObject;
		int waitingAnimationState;
		int saltoAnimationState;
		bool isRunning;

		GLuint bamsterRun[7];
		GLuint bamsterWait[4];
		GLuint bamsterJump[8];
		unsigned int addonType;
	public:
		bool facingLeft;
		double timeLastFiring;
		double timeLastMoving;
		float jumpPower;

		bamster (double x, double y);


		void updateBoundingBox(); 
		virtual void plot ();
		virtual objectInfo getObjectInfo() { return _player_;} 


		virtual void collision (object *with, char fromWhere);
	



		virtual bool timerCallback(double dt);


};






#endif
