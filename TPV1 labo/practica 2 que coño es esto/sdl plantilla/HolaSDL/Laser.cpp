#include "Laser.h"

void Laser::render() const
{
	/*
	// si es amigo/enemigo pintar de un color u otro
	if (laserType == rojo)
		SDL_SetRenderDrawColor(game->getRenderer(), 255, 0, 114, 255);	// cannon
	else
		SDL_SetRenderDrawColor(game->getRenderer(), 255, 242, 0, 255);	// aliens

	// tamaño
	destRect.w = 2;
	destRect.h = 10;

	// posicion
	destRect.x = (position.getX() + offset);
	destRect.y = position.getY();

	// dibuja el rectangulo
	SDL_RenderFillRect(game->getRenderer(), &destRect);
	*/
	
}

bool Laser::update()
{
	return false;
}

bool Laser::hit(SDL_Rect* rect, char frenemy)
{

	return false;
}

void Laser::move()
{
	// mueve al laser
	position = position + vel;
}
