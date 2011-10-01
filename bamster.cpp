#include "bamster.h"
#include "game.h"

		void bamster::collision (object *with, char fromWhere)
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

double schneeSchieber::fireLeft(double xpos, double ypos,double hamsterspeed)
{
	if (object::activGame->gameTime - timeLastFiring > kadenz / hamsterspeed)
	{

		timeLastFiring = object::activGame->gameTime;
		object::activGame->spawnObject(new bullet (-3.0,xpos, ypos - 2.0));
		object::activGame->spawnObject(new bullet (-3.0,xpos, ypos - 1.0));
		object::activGame->spawnObject(new bullet (-3.0,xpos, ypos));
		object::activGame->spawnObject(new bullet (-3.0,xpos, ypos));
		object::activGame->spawnObject(new bullet (-3.0,xpos, ypos + 1.0));
		object::activGame->spawnObject(new bullet (-3.0,xpos, ypos + 2.0));
		return 0.1;
	}
	return 0.0;
}


double schneeSchieber::fireRight(double xpos, double ypos, double hamsterspeed)
{
	if (object::activGame->gameTime - timeLastFiring > kadenz / hamsterspeed)
	{
		timeLastFiring = object::activGame->gameTime;
		object::activGame->spawnObject(new bullet (3.0,xpos, ypos - 1.0));
		object::activGame->spawnObject(new bullet (3.0,xpos, ypos));
		object::activGame->spawnObject(new bullet (3.0,xpos, ypos + 1.0));
		return -0.1;
	}
	return 0.0;
}


double tripelLaser::fireLeft(double xpos, double ypos, double hamsterspeed)
{
	if (object::activGame->gameTime - timeLastFiring > kadenz / hamsterspeed)
	{

		timeLastFiring = object::activGame->gameTime;
		object::activGame->spawnObject(new bullet (-3.0,xpos, ypos - 1.0));
		object::activGame->spawnObject(new bullet (-3.0,xpos, ypos));
		object::activGame->spawnObject(new bullet (-3.0,xpos, ypos + 1.0));
		return 0.1;
	}
	return 0.0;
}


double tripelLaser::fireRight(double xpos, double ypos, double hamsterspeed)
{
	if (object::activGame->gameTime - timeLastFiring > kadenz/ hamsterspeed)
	{
		timeLastFiring = object::activGame->gameTime;
		object::activGame->spawnObject(new bullet (3.0,xpos, ypos - 1.0));
		object::activGame->spawnObject(new bullet (3.0,xpos, ypos));
		object::activGame->spawnObject(new bullet (3.0,xpos, ypos + 1.0));
		return -0.1;
	}
	return 0.0;
}



double laser::fireLeft(double xpos, double ypos, double hamsterspeed)
{
	if (object::activGame->gameTime - timeLastFiring > kadenz/ hamsterspeed)
	{

		timeLastFiring = object::activGame->gameTime;
		object::activGame->spawnObject(new bullet (-3.0,xpos, ypos));
		return 0.1;
	}
	return 0.0;
}


double laser::fireRight(double xpos, double ypos, double hamsterspeed)
{
	if (object::activGame->gameTime - timeLastFiring > kadenz/ hamsterspeed)
	{
		timeLastFiring = object::activGame->gameTime;
		object::activGame->spawnObject(new bullet (3.0,xpos, ypos));
		return -0.1;
	}
	return 0.0;
}

void bamster::updateBoundingBox()

{
	b.xmin = xpos - size;
	b.xmax = xpos + size;
	b.ymin = ypos - size;
	b.ymax = ypos + size;

}




bool bamster::timerCallback(double dt)
{
	isRunning = false;
	if (pressedKeys.leftKey == true) {
		timeLastMoving = object::activGame->gameTime;
		xpos-= xvel * dt;
		facingLeft = true;
		isRunning = true;
	}

	if (pressedKeys.rightKey == true) {
		timeLastMoving = object::activGame->gameTime;
		xpos+= xvel * dt;
		facingLeft = false;
		isRunning = true;
	}

	if (pressedKeys.downKey == true)
	{
		activeWeapon++;
		if (activeWeapon == weapons.size())
			activeWeapon = 0;


	}	


	if (pressedKeys.spaceKey == true) {  // firing

		if ((object::activGame->gameTime - timeLastFiring) > cadenz)
		{


			if (facingLeft)
				xpos += weapons[activeWeapon]->fireLeft(xpos, ypos, size / 2.0);	
			else
				xpos += weapons[activeWeapon]->fireRight(xpos, ypos, size / 2.0);

		}	

	}



	if ((pressedKeys.upKey == true) && yvel == 0) {  // start jumping
		timeLastMoving = object::activGame->gameTime;
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




bamster::bamster (double x, double y) : fallingObject(x,y),    facingLeft (true), timeLastFiring (0.0), timeLastMoving (0.0), jumpPower (5.0), xvel (2.0), size (1.5)
{
	Image* image = loadBMP("animations/bamster_wait_r0.bmp");
	bamsterWait[0] = loadTexture(image);
	image = loadBMP("animations/bamster_wait_r1.bmp");
	bamsterWait[1] = loadTexture(image);
	image = loadBMP("animations/bamster_wait_r2.bmp");
	bamsterWait[2] = loadTexture(image);
	image = loadBMP("animations/bamster_wait_r3.bmp");
	bamsterWait[3] = loadTexture(image);
	image = loadBMP("animations/bamster_run_r0.bmp");

	bamsterRun[0] = loadTexture(image);
	image = loadBMP("animations/bamster_run_r0.bmp");
	bamsterRun[1] = loadTexture(image);
	image = loadBMP("animations/bamster_run_r1.bmp");
	bamsterRun[2] = loadTexture(image);
	image = loadBMP("animations/bamster_run_r2.bmp");
	bamsterRun[3] = loadTexture(image);
	image = loadBMP("animations/bamster_run_r3.bmp");
	bamsterRun[4] = loadTexture(image);
	image = loadBMP("animations/bamster_run_r4.bmp");
	bamsterRun[5] = loadTexture(image);
	image = loadBMP("animations/bamster_run_r5.bmp");
	bamsterRun[6] = loadTexture(image);
	image = loadBMP("animations/bamster_run_r6.bmp");

	delete image;
	hitpoints=1;
	gravity=1.0;
	waitingAnimationState=0;

}


void bamster::plot()
{

	// render with qudas
	glEnable(GL_TEXTURE_2D);
	if ( isRunning == true )
		glBindTexture(GL_TEXTURE_2D, bamsterRun[waitingAnimationState%7]);
	else
		glBindTexture(GL_TEXTURE_2D, bamsterWait[waitingAnimationState%4]);
	waitingAnimationState++;
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
	glEnable(GL_NORMALIZE);
	glDisable(GL_TEXTURE_2D);
}




