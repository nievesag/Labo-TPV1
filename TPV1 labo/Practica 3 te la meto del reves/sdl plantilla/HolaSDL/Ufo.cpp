#include "checkML.h"
#include "Ufo.h"
#include "SDLApplication.h"

void Ufo::render() const
{
	// lo mete en el render
	texture->renderFrame(destRect, 0, frame);
}

void Ufo::update()
{
	updateRect();

	switch (state)
	{
		case visible:
			// se mueve
			move();

			// si se sale 
			if (isOut()) {
				// desaparece
				disappear();
			}
			// si le pegan
			if (vidas <= 0) {
				// muere
				die();
			}
			break;

		case oculto:
			// gestiona el cooldown de aparicion
			// cd management
			manageCooldown();
			break;

		case destruido:
			// simplemente la animacion y luego muere
			anima();
			break;
	}
}

void Ufo::updateRect()
{
	// posicion               
	destRect.x = position.getX();
	destRect.y = position.getY();
}

void Ufo::anima()
{
	// si ha llegado al tope de frames vuelve a estar oculto
	if (frame >= texture->getNumColumns()) {

		// cambia el estado
		state = oculto;
	}

	// si el contador de animacion (tiempo entre frame y frame) es menor que 0
	if (animTimer <= 0) {

		// aumenta el frame
		frame++;

		// reinicia el contador
		animTimer = ANIMATION_DURATION;
	}
	else animTimer--;
}

bool Ufo::hit(SDL_Rect* rect, char frenemy)
{
	if (SDL_HasIntersection(rect, &destRect) && frenemy) {

		vidas--;

		if (vidas <= 0) {

			// lo 'mata' 
			die();

			// da los puntos
			playState->increaseScore(UfoScore);
		}
		return true;
	}
	// si no
	return false;
}

void Ufo::appear()
{
	state = visible;

	if (!isOut()) { }
	else state = oculto;
}

void Ufo::disappear()
{
	state = oculto;
}

void Ufo::die()
{
	state = destruido;

	// gestion de dropeo de reward
	rewardProb = playState->getRandomRange(playState->getMinProbReward(), playState->getMaxProbReward());
	if (rewardProb == 1) {

	}
}

void Ufo::manageCooldown()
{
	// gestion de cooldown
	if (CDcounter >= cooldown) {

		// cambia el estado
		appear();

		// reinicia la posicion
		position.setX(spawn.getX());

		// settea un nuevo cooldown
		setCD();
	}
	else
		CDcounter++;
}

void Ufo::setCD()
{
	// elige un nuevo cooldown      
	cooldown = playState->getRandomRange(1 * SHOOT_FRAMES, 5 * SHOOT_FRAMES);

	CDcounter = 0;
}


bool Ufo::isOut()
{
	return (this->position.getX() + texture->getFrameWidth() <= 0);
}

void Ufo::move()
{
	// mueve al laser
	position.setX(position.getX() - vel);
}

void Ufo::save(ostream& out) const
{
	// guarda el indicador de numero, la altura, el estado y el cooldown (y los golpes)
	out << "5 "
		<< spawn.getY() << " "
		<< state << " "
		<< cooldown << " "
		<< vidas << endl;
}