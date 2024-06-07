#include "../checkML.h"
#include "Laser.h"
#include "../SDLApplication.h"

Laser::Laser(char type, Point2D<double> position, int width, int height, int vidas, Texture* texture, PlayState* game)
	: laserType(type), SceneObject(position, width, height, vidas, texture, game) 
{
	// inicializa alive a true al construirse
	alive = true;

	if (laserType == 'a') vel.setY(1);
	else vel.setY(-1);
}

void Laser::render() const
{
	// si es amigo/enemigo pintar de un color u otro
	if (laserType == 'a')
		SDL_SetRenderDrawColor(playState->getAppRenderer(), 255, 0, 114, 255);	// cannon
	else
		SDL_SetRenderDrawColor(playState->getAppRenderer(), 255, 242, 0, 255);	// aliens

	// dibuja el rectangulo
	SDL_RenderFillRect(playState->getAppRenderer(), &destRect);
}

void Laser::update()
{
	// mueve al laser
	move();

	// actualiza el rect (colisiones)
	updateRect();

	// le pregunta si hay alguien a quien pegar un hostion
	if (playState->damage(destRect, laserType) || isOut()) {

		// le dice al game que ha muerto
		playState->hasDied(sceneanc);
	}
}

void Laser::save(ostream& out) const
{
	// guarda el indicador de numero
	out << "6 ";

	// guarda la posicion
	SceneObject::save(out);

	// guarda el color 
	out << laserType << endl;
}

bool Laser::hit(SDL_Rect* rect, char frenemy)
{
	if (SDL_HasIntersection(rect, &destRect) && (frenemy != laserType)) {

		// le dice al game que ha muerto
		playState->hasDied(sceneanc);

		return true;
	}
	return false;
}

bool Laser::isOut() const
{
	return ((this->position.getY() >= winHeight && 'r')
		|| (this->position.getY() <= 0 && 'a'));
}

void Laser::move()
{
	// mueve al laser
	position.setY(position.getY() - (vel.getY()*LASER_SPEED));
}

void Laser::updateRect()
{
	// posicion               
	destRect.x = position.getX();
	destRect.y = position.getY();
}