#include "Bomb.h"

void Bomb::render() const
{
	// lo mete en el render
	texture->render(destRect);
}

void Bomb::update()
{
	// movimiento igual que el laser enemigo

}

bool Bomb::hit(SDL_Rect* rect, char frenemy)
{
	// colisiones iguales que el laser practicamente
	return false;
}

bool Bomb::isOut()
{

	// igual que el laser
	return false;
}

void Bomb::move()
{

	// movimiento como el laseeeer
}

void Bomb::updateRect()
{

	// un clasico
}
