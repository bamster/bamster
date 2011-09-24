#include "game.h"


game * activGame;




void game::handleCollisions()
{
	//object-object

	list<object*>::iterator it, jt;

	unsigned int counteri, counterj;

	for (it = otherObjects.begin() ; it != otherObjects.end(); it++)
	{
		for (jt = otherObjects.begin() ; jt != it; jt++)
		{
			if (((* it)->collidesWith (**jt)) == 1)
			{
				(*jt)->hitpoints -= (*it)->hitpoints;
				(*it)->hitpoints -= (*jt)->hitpoints;
			}
			if ((( *it)->collidesWith (**jt)) == 2)
			{
				if ( (*it)->ypos  > (*jt)->ypos )	
					(*it)->stopMeFalling( (*jt)->b.ymax   );
				else
					(*jt)->stopMeFalling( (*it)->b.ymax  );


			}
		}

	}

}

void spawnObject (object *p)
{ 
	activGame->spawnObject(p);
}

