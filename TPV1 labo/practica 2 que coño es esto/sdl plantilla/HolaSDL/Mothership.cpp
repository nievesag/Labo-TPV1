#include "Mothership.h"

#include "Game.h"

void Mothership::update()
{
	// framerate de los aliens
	if (alienTimer < ALIEN_RR) {
		alienTimer++;
	}
	else {
		alienTimer = 0;
	}

	// direccion de los aliens
	
	
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
	return alienTimer == ALIEN_RR;
}

void Mothership::cannotMove()
{
	//cout << "state 1: " << currentState << endl;

	// RIGHT
	if (currentState == RIGHT) { currentState = dRIGHT; }
	// DOWN RIGHT
	else if (currentState == dRIGHT) { currentState = LEFT; }
	// LEFT
	else if (currentState == LEFT) { currentState = dLEFT; }
	// DOWN LEFT
	else { currentState = RIGHT; }

	//cout << "state 2: " << currentState << endl;
}
