#include "Alien.h"

void Alien::render() const
{
	SDL_Rect destRect;

	// tama�o
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
	cout << "co�ete";
}

void Alien::save(ostream&) const
{
	cout << "co�ardo";
}
