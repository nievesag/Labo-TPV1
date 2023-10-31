#include "Laser.h"

void Laser::render()
{
	// posicion para el coso 
	SDL_Rect destRect;

	// tamaño
	destRect.w = 2;
	destRect.h = 10;

	// posicion
	destRect.x = position.getX();
	destRect.y = position.getY();

	SDL_RenderFillRect(game->getRenderer(), &destRect);
}

void Laser::update()
{
	// si se puede mover se mueve
	if (!cannotMove()) {

		// mueve el laser
		move();
	}
	else {

		// acaba con el laser
		killLaser();
	}
}

void Laser::move()
{
	// TO DO

}

bool Laser::cannotMove()
{
	// TO DO

	return false;
}

void Laser::killLaser()
{
	// TO DO
}
