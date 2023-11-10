#include "Laser.h"
#include "Game.h"

void Laser::render()
{
	// si es amigo/enemigo pintar de un color u otro
	if (frenemy)
		SDL_SetRenderDrawColor(game->getRenderer(), 255, 0, 114, 255);
	else 
		SDL_SetRenderDrawColor(game->getRenderer(), 255, 242, 0, 255);

	// posicion para el coso 
	SDL_Rect destRect;

	// tamaño
	destRect.w = 2;
	destRect.h = 10;

	// posicion
	destRect.x = (position.getX()+offset);
	destRect.y = position.getY();

	// dibuja el rectangulo
	SDL_RenderFillRect(game->getRenderer(), &destRect);
}

// avanzar de acuerdo a su velocidad y comprobar si ha acertado objetivo
void Laser::update(bool pum)
{
	move();

	game->checkColision();

	/*
	game->checkColision();

	// si se puede mover se mueve
	if (!cannotMove()) {
		move();
	}
	else {
		// acaba con el laser
		killLaser();
	}
	*/
	
}

void Laser::move()
{
	// mueve al laser
	//position.setY(position.getY() + (vel.getY() * speed));
	//vel.getX() *= speed;

	position = position + vel;

	//std::cout << position.getX() << " " << position.getY() << endl;
}

bool Laser::cannotMove()
{
	// TODO

	return false;
}

void Laser::killLaser()
{
	// TODO
}

// accede a la posicion del laser
void Laser::getPosition()
{

}