#include "ShooterAlien.h"
#include "Game.h"

void ShooterAlien::shoot()
{
	if (CDcounter >= cooldown)
	{
		// crea un laser nuevo
		game->fireLaser(this->getPosition(), 'r');
	}
}

void ShooterAlien::manageCooldown()
{
	// gestion de cooldown
	if (CDcounter >= cooldown) {
		// elige un nuevo cooldown 
		cooldown = game->getRandomRange(minCD, maxCD);

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
}

void ShooterAlien::update()
{
	if (mothership->shouldMove()) {

		// se mueve
		move();

		//
		manageCooldown();

		// anima
		animate();

		// actualiza el rect (para colisiones)
		updateRect();
	}
}

void ShooterAlien::save(ostream& out) const
{
	// guarda el indicador de numero
	out << "2 ";

	//  guarda la posicion
	SceneObject::save(out);

	// guarda el subtipo y el cooldown del disparo
	out << type << " " << cooldown << endl;

}
