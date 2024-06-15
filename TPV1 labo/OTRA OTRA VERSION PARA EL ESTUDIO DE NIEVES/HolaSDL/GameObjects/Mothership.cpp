#include "../checkML.h"
#include "Mothership.h"
#include "../SDLApplication.h"
#include "../GameStates/PlayState.h"

Mothership::Mothership(int level, PlayState* playState, int alienTimer, int n) : level(level), alienTimer(alienTimer), playState_(playState)
{
	dir = 1;
	switchDir = false;
	alienCount = 0;

	setPosCD();
	setTimeCD();
}

void Mothership::update()
{
	// framerate de los aliens
	if (alienTimer < ALIEN_FR) 
	{
		alienTimer++;
	}

	else 
	{
		alienTimer = 0;
	}
	
	if (shouldMove() && switchDir)
	{
		dir = -dir;
		switchDir = false;
	}

	generateKamikaze();
}

int Mothership::getDirection() const
{
	return dir;
}

bool Mothership::shouldMove() const
{
	return alienTimer == ALIEN_FR;
}

void Mothership::cannotMove()
{
	if (!switchDir) 
	{
		switchDir = true;

		level++;
	}
}

void Mothership::alienLanded(const Alien* alien)
{
	// si llegan a 3/4 de la altura acaba
	if (alien->getPosition().getY() >= winHeight * 3 / 4) 
	{
		// acaba el juego
		haveLanded();
	}
}

void Mothership::haveLanded()
{
	// acaba el juego
	playState_->EndGame();
}

void Mothership::setTimeCD()
{
	// elige un nuevo cooldown      
	rndCooldown = playState_->getRandomRange(50, 500);

	CDcounter = 0;
}

void Mothership::setPosCD()
{
	rndPos = playState_->getRandomRange(0, winWidth);

	kPos.setY(0);
	kPos.setX(rndPos);
}

void Mothership::generateKamikaze()
{
	// gestion de cooldown
	if (CDcounter >= rndCooldown) 
	{
		// crea kamikaze
		playState_->createKamikaze(kPos);

		// resetea la pos
		setPosCD();

		// settea un nuevo cooldown
		setTimeCD();
	}
	else
		CDcounter++;
}

void Mothership::save(ostream& out) const
{
	// guarda el indicador de numero, la altura de los aliens, el estado actual y el cooldown
	out << "3 " << level << " " << dir << " " << alienTimer << endl;
}