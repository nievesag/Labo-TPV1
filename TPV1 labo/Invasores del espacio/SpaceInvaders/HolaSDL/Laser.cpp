#include "Laser.h"
#include "Game.h"

void Laser::render()
{
	// si es amigo/enemigo pintar de un color u otro
	if (frenemy)
		SDL_SetRenderDrawColor(game->getRenderer(), 255, 0, 114, 255);
	else 
		SDL_SetRenderDrawColor(game->getRenderer(), 255, 242, 0, 255);

	// tamaño
	destRect.w = 2;
	destRect.h = 10;

	// posicion
	destRect.x = (position.getX()+offset);
	destRect.y = position.getY();

	// dibuja el rectangulo
	SDL_RenderFillRect(game->getRenderer(), &destRect);
}

bool Laser::update(bool pum)
{
	// si esta muerto devuelve false
	if (!alive) { 

		return false; 
	}

	// avanzar de acuerdo a su velocidad
	move();

	// comprueba las colisiones del propio laser
	return game->checkColision(this);
}

void Laser::move()
{
	// mueve al laser
	//position.setY(position.getY() + (vel.getY() * speed));
	//vel.getX() *= speed;

	position = position + vel;
}

void Laser::hit()
{
	alive = false;

	//cout << "DOLOR Y SUFRIMIENTO" << endl;
}