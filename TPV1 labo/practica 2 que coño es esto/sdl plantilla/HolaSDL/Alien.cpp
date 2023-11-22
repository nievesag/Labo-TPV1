#include "Alien.h"

void Alien::render(SDL_Rect destRect) const
{
	// tamaño
	destRect.w = texture->getFrameWidth();
	destRect.h = texture->getFrameHeight();

	// posicion
	destRect.x = position.getX();
	destRect.y = position.getY();

	// lo mete en el render
	texture->renderFrame(destRect, type, alienFrame);
}

void Alien::update()
{
	cout << "coñete";
}

void Alien::save(ostream&) const
{
	cout << "coñardo";
}
