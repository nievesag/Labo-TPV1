#include "checkML.h"
#include "ShooterAlien.h"
#include "SDLApplication.h"

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
		cooldown = game->getRandomRange(minCD * SHOOT_FRAMES, maxCD* SHOOT_FRAMES);

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
	cooldown = game->getRandomRange(minCD * SHOOT_FRAMES , SHOOT_FRAMES);

	CDcounter = 0;
}

void ShooterAlien::update()
{
	if (CDcounter <= 0)
		CDcounter = game->getRandomRange(minCD * SHOOT_FRAMES, maxCD * SHOOT_FRAMES); 
	else
		CDcounter--;

	// !! dentro de la comprobacion anterior todos los aliens disparaban en la primera iteracion
	// iniciando los aliens ya con un valor del random se solucionaria??
	if (CDcounter <= 0) { 

		game->fireLaser(this->getPosition(), 'r');
	}

	Alien::update();
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

