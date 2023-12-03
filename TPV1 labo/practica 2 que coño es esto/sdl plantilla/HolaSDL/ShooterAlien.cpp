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
	cooldown = game->getRandomRange(minCD , maxCD);

	CDcounter = 0;
}

void ShooterAlien::update()
{
	if (mothership->shouldMove()) {

		// se mueve
		position.setX(position.getX() + (mothership->getDirection() * alienSpeed));
		//
		manageCooldown();
		// anima
		animate();
		// actualiza el rect (para colisiones)
		updateRect();
	}

	// si se pasa de corto o de largo cambia la direccion y lo baja una posicion
	if ((position.getX() <= 0) || (position.getX() >= (game->getWinWidth() - texture->getFrameWidth()))) {

		mothership->cannotMove();

	}

	// baja cuando level sube (sube cada vez que le llama cannotMove)
	position.setY(initialY + ALIEN_SPEED * mothership->getLevel());

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

void ShooterAlien::setInitialCooldown()
{
	if (cooldown == -1) {
		// rango del cooldown aleatorio
		minCD = game->getRandomRange(2, 7);
		maxCD = game->getRandomRange(8, 15);

		setCD();
	}

	CDcounter = 0;
}
