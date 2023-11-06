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

// avanzar de acuerdo a su velocidad y comprobar si ha acertado objetivo
void Laser::update(bool pum)
{
	game->checkColision();
	// si se puede mover se mueve
	if (!cannotMove()) {

		move();
	}
	else {

		// acaba con el laser
		killLaser();
	}
}


void Laser::move()
{
	// TODO

}

bool Laser::cannotMove()
{
	// TODO

	return false;
}

void Laser::killLaser()
{
	// TODO
}

// accede a la posicion del laser
void Laser::getPosition()
{

}