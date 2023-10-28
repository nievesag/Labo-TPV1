#include "Cannon.h"

void Cannon::render()
{
	// posicion para el coso 
	SDL_Rect destRect;

	// tama�o
	destRect.w = texture->getFrameWidth()*10;
	destRect.h = texture->getFrameHeight()*10;

	// posicion
	destRect.x = position.getX();
	destRect.y = position.getY();


	texture->render(destRect);
}
