#include "ShooterAlien.h"

//
#include "Game.h"


void ShooterAlien::shoot()
{
	if (CDcounter >= cooldown)
	{
		// crea un laser nuevo
		game->fireLaser(this->getPosition(), 'r');
	}
}

void ShooterAlien::attack()
{
	// gestion de cooldown
	if (CDcounter >= cooldown) {
		// elige un nuevo cooldown 
		cooldown = game->getRandomRange(minCD, maxCD) * 30;

		// reinicia el contador
		CDcounter = 0;
	}
	else
		CDcounter++;

	shoot();

}

void ShooterAlien::setCD()
{
	// elige un nuevo cooldown 
	cooldown = game->getRandomRange(minCD, maxCD);

	CDcounter = 0;

	cout << cooldown << endl;
}

void ShooterAlien::update()
{
	if (mothership->shouldMove()) {

		// se mueve
		move();

		//
		attack();

		// anima
		animate();

		// actualiza el rect (para colisiones)
		updateRect();
	}

	

}
