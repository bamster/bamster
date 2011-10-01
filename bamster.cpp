#include "bamster.h"
#include "game.h"

double schneeSchieber::fireLeft(double xpos, double ypos)
{
	if (object::activGame->gameTime - timeLastFiring > kadenz)
	{

		timeLastFiring = object::activGame->gameTime;
		object::activGame->spawnObject(new bullet (-3.0,xpos, ypos - 1.0));
		object::activGame->spawnObject(new bullet (-3.0,xpos, ypos));
		object::activGame->spawnObject(new bullet (-3.0,xpos, ypos + 1.0));
		return 0.1;
	}
	return 0.0;
}


double schneeSchieber::fireRight(double xpos, double ypos)
{
	if (object::activGame->gameTime - timeLastFiring > kadenz)
	{
		timeLastFiring = object::activGame->gameTime;
		object::activGame->spawnObject(new bullet (3.0,xpos, ypos - 1.0));
		object::activGame->spawnObject(new bullet (3.0,xpos, ypos));
		object::activGame->spawnObject(new bullet (3.0,xpos, ypos + 1.0));
		return -0.1;
	}
	return 0.0;
}


double tripelLaser::fireLeft(double xpos, double ypos)
{
	if (object::activGame->gameTime - timeLastFiring > kadenz)
	{

		timeLastFiring = object::activGame->gameTime;
		object::activGame->spawnObject(new bullet (-3.0,xpos, ypos - 1.0));
		object::activGame->spawnObject(new bullet (-3.0,xpos, ypos));
		object::activGame->spawnObject(new bullet (-3.0,xpos, ypos + 1.0));
		return 0.1;
	}
	return 0.0;
}


double tripelLaser::fireRight(double xpos, double ypos)
{
	if (object::activGame->gameTime - timeLastFiring > kadenz)
	{
		timeLastFiring = object::activGame->gameTime;
		object::activGame->spawnObject(new bullet (3.0,xpos, ypos - 1.0));
		object::activGame->spawnObject(new bullet (3.0,xpos, ypos));
		object::activGame->spawnObject(new bullet (3.0,xpos, ypos + 1.0));
		return -0.1;
	}
	return 0.0;
}



double laser::fireLeft(double xpos, double ypos)
{
	if (object::activGame->gameTime - timeLastFiring > kadenz)
	{

		timeLastFiring = object::activGame->gameTime;
		object::activGame->spawnObject(new bullet (-3.0,xpos, ypos));
		return 0.1;
	}
	return 0.0;
}


double laser::fireRight(double xpos, double ypos)
{
	if (object::activGame->gameTime - timeLastFiring > kadenz)
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
				xpos += weapons[activeWeapon]->fireLeft(xpos, ypos);	
			else
				xpos += weapons[activeWeapon]->fireRight(xpos, ypos);

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




bamster::bamster (double x, double y) : fallingObject(x,y),    facingLeft (true), timeLastFiring (0.0), timeLastMoving (0.0), jumpPower (5.0), xvel (2.0)
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




