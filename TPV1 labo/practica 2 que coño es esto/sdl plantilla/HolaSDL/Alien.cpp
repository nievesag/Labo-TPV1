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

bool Alien::update()
{
	//cout << "coñete";

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

void Alien::move()
{
	// mueve al alien
	position.setX(position.getX() + (mothership->getDirection().getX() * alienSpeed));
	//position.setY(position.getY() + (mothership->getDirection().getY()) * mothership->getLevel());

	

	// si se pasa de corto o de largo cambia la direccion y lo baja una posicion
	if (position.getX() < 0 || position.getX() > game->getWinWidth() - texture->getFrameWidth()) {
		mothership->cannotMove();
	}

}

void Alien::animate()
{
	// se anima ig

}
