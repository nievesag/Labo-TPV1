#include "Alien.h"

void Alien::render() const
{
	SDL_Rect destRect;

	// tamanio
	destRect.w = texture->getFrameWidth();
	destRect.h = texture->getFrameHeight();

	// posicion
	destRect.x = position.getX();
	destRect.y = position.getY();

	// lo mete en el render
	texture->renderFrame(destRect, type, alienFrame);
}

bool Alien::update()
{
	// si esta muerto devuelve false
	if (vidas <= 0) return false;

	// se mueve
	move();

	// anima
	animate();

	// si esta vivo devuelve true
	return true;
}

void Alien::save(ostream&) const
{
	cout << "coñardo";
}

void Alien::lowerAlien()
{
	// si no se acaba (PLACEHOLDER!!!!!!!!!!!!!!!!!!!!!)
	if (true) {
		// lo baja 
		position.setY(position.getY() + mothership->getLevel());
	}
	else {
		// acaba el juego
		game->EndGame();
	}
}

bool Alien::hit(SDL_Rect* rect, char frenemy)
{
	return false;
}

void Alien::move()
{
	// mueve al alien
	position.setX(position.getX() + (mothership->getDirection().getX() * alienSpeed));

	// si se pasa de corto o de largo cambia la direccion y lo baja una posicion
	if (position.getX() < 0 || position.getX() > game->getWinWidth() - texture->getFrameWidth()) {
		mothership->cannotMove();
	}
}

void Alien::animate()
{
	// se anima ig
}
