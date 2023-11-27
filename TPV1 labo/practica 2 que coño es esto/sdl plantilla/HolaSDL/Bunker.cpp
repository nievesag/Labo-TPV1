#include "Bunker.h"

// para que el bestie bestiee
// #include "Game.h"

void Bunker::render() const
{
	// lo mete en el render
	texture->renderFrame(destRect, 0, hits);
}

void Bunker::update()
{
	// update

	// creo que sobra ????
	updateRect();
}

bool Bunker::hit(SDL_Rect* rect, char frenemy)
{
	return false;
}

void Bunker::updateRect()
{
	// posicion
	destRect.x = position.getX();
	destRect.y = position.getY();
}
