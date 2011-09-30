
#include "game.h"


game * activGame;



void game::handleCollisions()
{
	//object-object

	list<object*>::iterator it, jt, next;

	unsigned int counteri, counterj;
	char fromWhere;


	for (it = otherObjects.begin() ; it != otherObjects.end(); it++)
	{
		jt = it;
		for (jt++; jt != otherObjects.end(); jt++)
		{
			if ((fromWhere = ((* it)->collidesWith (**jt))))
			{
				(*it)-> collision(*jt, fromWhere);
				(*jt)-> collision(*it, otherSide(fromWhere));


			}
		}

	}

}




