#include "Alien.h"

void Alien::render()
{
	// posicion para el coso 
	SDL_Rect destRect;

	// tama�o
	destRect.w = texture->getFrameWidth();
	destRect.h = texture->getFrameHeight();

	// posicion
	destRect.x = position.getX();
	destRect.y = position.getY();

	// lo mete en el render
	texture->renderFrame(destRect, type-1, 0);
}
