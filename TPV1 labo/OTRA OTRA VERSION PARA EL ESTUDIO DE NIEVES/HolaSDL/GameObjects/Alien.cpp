#include "../checkML.h"
#include "Alien.h"
#include "../SDLApplication.h"

Alien::Alien(Mothership* mothership, int alienFrame, int type, Point2D<double> position,
	int width, int height, int vidas, Texture* texture, PlayState* game)
	: mothership(mothership), alienFrame(alienFrame), type(type), 
	SceneObject(position, width, height, vidas, texture, game)
{
	// settea la velocidad
	setAlienSpeed();

	// settea el spawn
	initialY = position.getY();

	// settea la puntuacion que dan los aliens
	if (type == 0) alienScore = score3;
	else if (type == 1) alienScore = score2;
	else if (type == 2) alienScore = score1;
	else alienScore = 0;
}

void Alien::render() const
{
	// lo renderiza
	texture->renderFrame(destRect, type, alienFrame);
}

void Alien::update()
{
	// pregunta si han llegado al suelo
	mothership->alienLanded(this);

	// pregunta si se debe mover
	if (mothership->shouldMove()) {

		// mueve al alien
		position.setX(position.getX() + (mothership->getDirection() * alienSpeed));

		// anima
		animate();

		// actualiza el rect
		updateRect();
	}

	// si se pasa de corto o de largo cambia la direccion y lo baja una posicion
	if ((position.getX() <= 0) || (position.getX() >= (application->getWinWidth() - texture->getFrameWidth()))) 
	{

		mothership->cannotMove();
	}

	// baja cuando level sube (sube cada vez que le llama cannotMove)
	position.setY(initialY + ALIEN_SPEED * mothership->getLevel());
}

bool Alien::hit(SDL_Rect* rect, Weapon* frenemy)
{
	// colisiones, si interseccionan con un laser del cannon (char a)
	if (SDL_HasIntersection(rect, &destRect) && frenemy->getChar() == 'a') {

		// informa al game que ha muerto
		playState->hasDied(sceneanc);

		// informa a mothership que ha muerto
		mothership->alienDied();

		// aumenta puntuacion del jugador
		playState->getApplication()->increaseScore(GetAlienPoints());

		return true;
	}
	else return false;
}

void Alien::animate()
{
	// se anima
	alienFrame = (alienFrame + 1) % texture->getNumColumns();
}

void Alien::updateRect()
{
	// posicion
	destRect.x = position.getX();
	destRect.y = position.getY();
}

void Alien::setAlienSpeed()
{
	alienSpeed = ALIEN_SPEED;
}

void Alien::save(ostream& out) const
{
	// guarda el indicador de numero
	out << "1 ";

	//  guarda la posicion
	SceneObject::save(out);

	// guarda el subtipo
	out << type << endl;
}