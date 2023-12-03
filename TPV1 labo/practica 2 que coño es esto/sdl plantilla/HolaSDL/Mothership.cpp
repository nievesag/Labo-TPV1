#include "Mothership.h"

#include "Game.h"

void Mothership::update()
{
	// framerate de los aliens
	if (alienTimer < ALIEN_FR) {
		alienTimer++;
	}
	else {
		alienTimer = 0;
	}


	if (shouldMove() && switchDir)
	{
		dir = -dir;
		switchDir = false;
	}
}

void Mothership::save(ostream& out) const
{
	// guarda el indicador de numero, la altura de los aliens, el estado actual y el cooldown
	out << "3 " << level << " " << dir << " " << alienTimer << endl;

}

int Mothership::getDirection()
{
	

	return dir;
}


bool Mothership::shouldMove()
{
	return alienTimer == ALIEN_FR;
}

void Mothership::cannotMove()
{
	if (!switchDir) {
		switchDir = true;

		level++;
	}
	

}

void Mothership::alienLanded(const Alien* alien)
{
	// si llegan a 3/4 de la altura acaba
	if (alien->getPosition().getY() > winHeight * 3 / 4) {

		// acaba el juego
		haveLanded();
	}
}


void Mothership::haveLanded()
{
	// acaba el juego
	game->EndGame();
}
