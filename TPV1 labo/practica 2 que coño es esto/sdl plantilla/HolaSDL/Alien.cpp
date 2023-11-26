#include "Alien.h"

void Alien::render() const
{
	//SDL_Rect destRect;

	// tamaño
	//destRect.w = texture->getFrameWidth();
	//destRect.h = texture->getFrameHeight();

	// posicion
	
	Point2D<double> newPos(position.getX(), position.getY());

	SDL_Rect newDestRect;

	newDestRect.w = texture->getFrameWidth();
	newDestRect.h = texture->getFrameHeight();

	newDestRect.x = newPos.getX();
	newDestRect.y = newPos.getY();

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! esto da error rarete sadly
	//SetDestRect(newDestRect);

	// lo mete en el render
	texture->renderFrame(newDestRect, type, alienFrame);
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! cambiar newDestRect a detsRect
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
