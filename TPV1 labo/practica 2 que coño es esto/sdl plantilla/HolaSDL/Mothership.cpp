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

}

void Mothership::save(ostream& out) const
{
	// guarda el indicador de numero, la altura de los aliens, el estado actual y el cooldown
	out << "3 " << level << " " << dir << " " << alienTimer << endl;

}

Vector2D<int> Mothership::getDirection()
{
	Vector2D<int> direc{0,0};

	if (dir == 1) {

		direc.setX(1);
	}
	else if (dir -1) {
		direc.setX(-1);
	}

	return direc;
}


bool Mothership::shouldMove()
{
	return alienTimer == ALIEN_FR;
}

void Mothership::cannotMove()
{
	/*
	// RIGHT
	if (currentState == RIGHT) { currentState = dRIGHT; }
	// DOWN RIGHT
	else if (currentState == dRIGHT) { currentState = LEFT; }
	// LEFT
	else if (currentState == LEFT) { currentState = dLEFT; }
	// DOWN LEFT
	else { currentState = RIGHT; }
	*/

	// cambia de direccion
	dir *= -1;

	level++;

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
