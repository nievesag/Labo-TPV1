#include "checkML.h"
#include "ShooterAlien.h"
#include "SDLApplication.h"
#include "PlayState.h"
#include "Alien.h"

ShooterAlien::ShooterAlien(double cooldown, Mothership* mothership, int alienFrame, int type, Point2D<double> position,
	int width, int height, int vidas, Texture* texture, PlayState* game) 
	: cooldown(cooldown), Alien(mothership, alienFrame, type, position, width, height, vidas, texture, game)
{}


void ShooterAlien::shoot()
{
	if (CDcounter >= cooldown)
	{
		

		
	}
}

void ShooterAlien::manageCooldown()
{
	// gestion de cooldown
	if (CDcounter >= cooldown) {
		// elige un nuevo cooldown 
		cooldown = playState->getRandomRange(minCD * SHOOT_FRAMES, maxCD* SHOOT_FRAMES);

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
	cooldown = playState->getRandomRange(minCD * SHOOT_FRAMES , SHOOT_FRAMES);

	CDcounter = 0;
}

void ShooterAlien::update()
{
	if (CDcounter <= 0)
		CDcounter = playState->getRandomRange(minCD * SHOOT_FRAMES, maxCD * SHOOT_FRAMES); 
	else
		CDcounter--;

	// !! dentro de la comprobacion anterior todos los aliens disparaban en la primera iteracion
	// iniciando los aliens ya con un valor del random se solucionaria??
	if (CDcounter <= 0) { 
		int prob = playState->getRandomRange(playState->getMinProbBomb(), playState->getMaxProbBomb());
		//cout << prob << endl;

		if (prob == 1) {

			playState->fireBomb(this->getPosition());
		}
		else {
			// crea un laser nuevo
			playState->fireLaser(this->getPosition(), 'r');
		}
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