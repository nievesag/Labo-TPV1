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

	// direccion de los aliens
}

void Mothership::save(ostream& out) const
{
	// guarda el indicador de numero, la altura de los aliens, el estado actual y el cooldown
	out << "3 " << level << " " << currentState << " " << alienTimer << endl;

}

Vector2D<int> Mothership::getDirection()
{
	Vector2D<int> dir{0,0};

	// RIGHT
	if (currentState == RIGHT) { dir.setX(1); dir.setY(0); }
	// DOWN RIGHT
	else if (currentState== dRIGHT) { dir.setX(1); dir.setY(1); }
	// LEFT
	else if (currentState == LEFT) { dir.setX(-1); dir.setY(0); }
	// DOWN LEFT
	else if (currentState == dLEFT) { dir.setX(-1); dir.setY(1); }

	return dir;
}


bool Mothership::shouldMove()
{
	return alienTimer == ALIEN_FR;
}

void Mothership::cannotMove()
{
	// RIGHT
	if (currentState == RIGHT) { currentState = dRIGHT; }
	// DOWN RIGHT
	else if (currentState == dRIGHT) { currentState = LEFT; }
	// LEFT
	else if (currentState == LEFT) { currentState = dLEFT; }
	// DOWN LEFT
	else { currentState = RIGHT; }
}
