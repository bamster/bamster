#ifndef BAMSTER_H_INCLUDED
#define BAMSTER_H_INCLUDED

#include "keyLogger.h"

#include <iostream>
#include <vector>
#include <GL/glut.h>
#include "objects.h"

using namespace std;


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


		virtual void collision (object *with, char fromWhere)
		{
			collisionObject = with->getObjectInfo();	
			if ((collisionObject != _bullet_ )&&(collisionObject != _addon_))
			{

				if (fromWhere == fromLeft)
					xpos = (b.xmax - b.xmin) / 2.0 + with-> b.xmax;
				if (fromWhere == fromRight)
					xpos =with-> b.xmin  -  (b.xmax - b.xmin) / 2.0;
				if (fromWhere == fromUp){
					if (with->yvel < -2.0)
						if (size > 1.5)
							size--;
						else if (hitpoints != 0)
						hitpoints--;
				}
				else
					fallingObject::collision(with,fromWhere);

			}
			if (with->getObjectInfo() == _addon_)
			{
				switch (((addon*)with)->addonType){
					case 0:
						weapons.push_back(new laser ());
						activeWeapon = weapons.size() -1 ;
						break;
					case 1:
						weapons.push_back(new tripelLaser ());
						activeWeapon = weapons.size() -1 ;
						break;
					case 2:
						jumpPower = 6.0;
						break;
					case 3:
						jumpPower = 6.5;
						xvel = 2.2;
						break;
					case 4:
						jumpPower = 7.0;
						xvel = 2.7;
						break;
					case 5:
						jumpPower = 7.0;
						xvel = 3.0;
						break;
					case 6:
						jumpPower = 6.0;
						xvel = 3.2;
						break;
					case 7:
						jumpPower = 9.0;
						xvel = 3.5;
						break;



					case 10:
						weapons.push_back ( new schneeSchieber ());
						activeWeapon = weapons.size() -1 ;
						break;
					case 99:
						size += 0.1;
						break;
				}
			}
		}



		virtual bool timerCallback(double dt);


};






#endif
