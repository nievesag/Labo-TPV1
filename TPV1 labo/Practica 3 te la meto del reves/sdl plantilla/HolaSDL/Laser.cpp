#include "checkML.h"
#include "Laser.h"
#include "SDLApplication.h"

void Laser::render() const
{
	// si es amigo/enemigo pintar de un color u otro
	if (laserType == 'r')
		SDL_SetRenderDrawColor(application->getRenderer(), 255, 0, 114, 255);	// cannon
	else
		SDL_SetRenderDrawColor(application->getRenderer(), 255, 242, 0, 255);	// aliens

	// dibuja el rectangulo
	SDL_RenderFillRect(application->getRenderer(), &destRect);
}

void Laser::update()
{
	// mueve al laser
	move();

	// actualiza el rect (colisiones)
	updateRect();

	// le pregunta si hay alguien a quien pegar un hostion
	if (application->damage(this) || isOut()) {

		// le dice al game que ha muerto
		game->hasDied(anc);
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
	// si colisiona con un laser amigo true
	return (SDL_HasIntersection(rect, &destRect) && frenemy != laserType);
}

bool Laser::isOut()
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