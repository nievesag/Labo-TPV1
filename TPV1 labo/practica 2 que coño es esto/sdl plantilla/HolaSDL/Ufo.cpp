#include "Ufo.h"
#include "Game.h"

void Ufo::render() const
{
	// lo mete en el render
	texture->renderFrame(destRect, 0, 0);
}

void Ufo::update()
{

	//cout << state << endl;
	updateRect();
	
	switch (state)
	{
	case visible:

		// se mueve con zoomies
		move();

		// si se sale 
		if (isOut()) {

			//cout << "holi   -------------------------------------------------" << endl;

			// desaparece
			disappear();
		}

		// si le pegan una hostia
		if (hits >= vidas) {

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

// --------------------------------------------------------------------------------------


void Ufo::updateRect()
{
	// posicion               
	destRect.x = position.getX();
	destRect.y = position.getY();
}

void Ufo::anima()
{

	// yes
	if (animTimer <= 0)
	{
		state = oculto;
		//position = iniPos;
		animTimer = ANIMATION_DURATION;
	}
	else animTimer--;


}


bool Ufo::hit(SDL_Rect* rect, char frenemy)
{
	if (SDL_HasIntersection(rect, &destRect) && frenemy) {

		hits++;

		if (hits >= vidas) game->hasDied(it);
		state = destruido;
		game->increaseScore(UfoScore);

		return true;
	}
	// si no
	return false;
}

void Ufo::appear()
{

	state = visible;

	if (!isOut())
	{
		
	}
	else state = oculto;
}

void Ufo::disappear()
{
	// no tiene mas miesterio xd
	state = oculto;
}

void Ufo::die()
{
	// muereeee
	state = destruido;
}

void Ufo::manageCooldown()
{

	//cout << "AAAAAAAAAAA EL CD: " << cooldown << endl;

	//cout << CDcounter << endl;

	// gestion de cooldown
	if (CDcounter >= cooldown) {

		// cambia el estado
		appear();

		// reinicia la posicion
		//

		// settea un nuevo cooldown
		setCD();
	}
	else
		CDcounter++;

}

void Ufo::setCD()
{
	// elige un nuevo cooldown         10 20
	cooldown = game->getRandomRange(1 * SHOOT_FRAMES, 5 * SHOOT_FRAMES);

	CDcounter = 0;
}

void Ufo::setInitialCD()
{
	if (cooldown == -1) {
		// rango del cooldown aleatorio
		minCD = game->getRandomRange(2, 7);
		maxCD = game->getRandomRange(8, 15);

		setCD();
	}

	CDcounter = 0;
}

bool Ufo::isOut()
{
	return (this->position.getX() <= 0);
}

void Ufo::move()
{
	//cout << "HOLIWIS" << endl;


	cout << position.getX() << " " << position.getY() << endl;

	// mueve al laser
	position.setX(position.getX() - (vel.getX() * 0.09));
}

void Ufo::save(ostream& out) const
{
	// guarda el indicador de numero, la altura, el estado y el cooldown (y los golpes)
	out << "5 "
		<< spawn.getY() << " "
		<< state << " "
		<< cooldown << " "
		<< hits << endl;

}