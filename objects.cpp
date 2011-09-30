
#include "objects.h"
#include "game.h"

//plain function implementation



game * object::activGame;


				void addon::collision (object *with, char fromWhere) {
						if (fromWhere == fromDown)
						{
								yvel = 0;
								ypos = (b.ymax - b.ymin)/2.0  + with->b.ymax;
						}
						if (with->getObjectInfo() == _player_)
								gotCollected = true;
				}
				bool addon::timerCallback (double dt)
				{
						ypos += yvel* dt;
						yvel -= gravity*dt;
						updateBoundingBox();
					return !gotCollected;
				}

				void addon::updateBoundingBox ()
				{
						b.xmin = xpos - size / 2;
						b.xmax = xpos + size / 2;
						b.ymin = ypos - size / 2;
						b.ymax = ypos + size / 2;
				}			



				void addon::plot() {
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



block::~block() {
	object::activGame->score++;
}; 
char otherSide (char side)
{
	if (side == fromLeft)
		return fromRight;
	if (side == fromRight)
		return fromLeft;
	if (side == fromUp)
		return fromDown;
	
	return fromUp;
}
addon::addon (double x, double y, double l, int t) : fallingObject (x,y), size ( l), addonType (t),gotCollected (false)  {  
			updateBoundingBox();
			hitpoints=3;

			Image* image = loadBMP("animations/jumpingShoes.bmp");
			animation = loadTexture(image);
			delete image;

		};

//object-class implementation
void object::stopMeFalling(double height)
{
	//yy	 ypos = ypos - b.ymin  + height;
	ypos = (b.ymax - b.ymin)/2.0  + height;
}
object::object (double x, double y) : xpos (x), ypos(y) {}

objectInfo object::getObjectInfo() { 
	return _undefined_;  
}

void object::updateBoundingBox() { 
	cout << "updateBoundingBox of object called" << endl; 
}

GLuint object::loadTexture(Image *image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGB,
			image->width, image->height,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			image->pixels
	);
	return textureId;
}


char object::collidesWith (object &o)  // return 0 for no, 1 for horizontal, 2 for vertical collision
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

object::~object() {};
void object::plot() { cout << "plot of object called" << endl; }
bool object::timerCallback (double dt) {return true;}
void object::collision (object *with, char fromWhere) { }

//fallingObject implementations
fallingObject::fallingObject (double x, double y) : object (x,y), gravity(0.1) {}

void fallingObject::stopMeFalling (double height)
{
	cout << "autsch" << endl;
	yvel = 0;
	object::stopMeFalling (height);
}

void fallingObject::collision (object *with, char fromWhere)
{
	if (fromWhere == fromDown)
	{
		yvel = 0;
		ypos = (b.ymax - b.ymin)/2.0  + with->b.ymax;
	}

}	

objectInfo fallingObject::getObjectInfo() { return _undefined_;}

bool fallingObject::timerCallback(double dt)
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

//vwall-implementation
//
void vwall::plot() {
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f,0.0f);
	glVertex2f(xpos, ypos - length / 2);
	glVertex2f(xpos, ypos + length / 2); 
	glEnd();	
}
void vwall::updateBoundingBox ()
{
	b.xmin = b.xmax = xpos;
	b.ymin = ypos - length / 2;
	b.ymax = ypos + length / 2;
}			
vwall::vwall (double x, double y, double l) : object (x,y), length ( l) { updateBoundingBox(); };

//hwall-implementation
//
void hwall::plot() {
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f,0.0f);
	glVertex2f(xpos - length / 2, ypos);
	glVertex2f(xpos + length / 2, ypos); 
	glEnd();	
}
void hwall::updateBoundingBox ()
{
	b.ymin = b.ymax = ypos;
	b.xmin = xpos - length / 2;
	b.xmax = xpos + length / 2;
}			
hwall::hwall (double x, double y, double l) : object (x,y), length ( l) { updateBoundingBox(); };

//Implementation of block-methods
block::block (double x, double y, double l, unsigned int color_idx) : fallingObject (x,y), size ( l)  {  
	updateBoundingBox(); 
	red = colors[color_idx][0];
	green = colors[color_idx][1];	
	blue = colors[color_idx][2];	
	hitpoints=3; 
};




void block::plot() {
	glColor3f(red,green,blue);
	glBegin(GL_QUADS);
	glVertex2f(xpos - size / 2, ypos- size / 2);
	glVertex2f(xpos + size / 2, ypos- size / 2);
	glVertex2f(xpos + size / 2, ypos+ size / 2);
	glVertex2f(xpos - size / 2, ypos+ size / 2);
	glEnd();	
}

void block::updateBoundingBox () {
	b.xmin = xpos - size / 2;
	b.xmax = xpos + size / 2;
	b.ymin = ypos - size / 2;
	b.ymax = ypos + size / 2;
}			

void block::collision (object *with, char fromWhere) {
	if (with->getObjectInfo() == _bullet_) {
//		_		if (fromWhere== fromLeft || fromWhere == fromRight)
//				{
		hitpoints = hitpoints -1;
//				}
	}
	fallingObject::collision(with,fromWhere);
}


bool block::timerCallback(double dt)
{
	return fallingObject::timerCallback(dt);

}

//bullet-class implementation
bullet::bullet (double s, double x, double y) : speed(s), object(x,y), hitSomething(false) {}

void bullet::plot ()
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

objectInfo bullet::getObjectInfo() { 
	return _bullet_;  
}

void bullet::updateBoundingBox ()
{
	b.xmin = xpos - 1.2;
	b.xmax = xpos + 1.2;
	b.ymin = ypos - 0.3;
	b.ymax = ypos - 0.3;
}
void bullet::collision (object *with, char fromWhere) {
	if (with->getObjectInfo() != _player_ && with->getObjectInfo() != _bullet_)
		hitSomething = true;  	
	}

bool bullet::timerCallback (double dt)
{
	xpos += dt * speed;
	updateBoundingBox();
	return !hitSomething;
}	
