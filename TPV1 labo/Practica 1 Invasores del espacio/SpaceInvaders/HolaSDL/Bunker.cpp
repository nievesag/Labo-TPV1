#include "checkML.h"
#include "Bunker.h"

void Bunker::render()
{
	// tamaño
	destRect.w = texture->getFrameWidth();
	destRect.h = texture->getFrameHeight();

	// posicion
	destRect.x = position.getX();
	destRect.y = position.getY();

	// lo mete en el render
	texture->renderFrame(destRect, 0, hits);
}

bool Bunker::update()
{
	// si esta muerto devuelve false
	if (hits == lifes) return false;

	// si esta vivo devuelve true
	return true;
}

// contador de daño
void Bunker::hit()
{
	hits++;
}

