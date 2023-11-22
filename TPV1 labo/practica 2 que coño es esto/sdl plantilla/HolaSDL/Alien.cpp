#include "Alien.h"

void Alien::render() const
{
	SDL_Rect destRect;

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
