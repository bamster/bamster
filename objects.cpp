
#include "objects.h"
#include "game.h"

block::~block() {
    game::score++;
}; 
double object::gameTime = 0;
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

