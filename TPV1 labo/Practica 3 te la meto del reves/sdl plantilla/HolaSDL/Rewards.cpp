#include "Rewards.h"
#include "SDLApplication.h"

void Rewards::emit() const
{
	// llama a todas las funciones registradas
	for (const SDLEventCallback& rewardCallback : callbacks)
		rewardCallback();
}

void Rewards::render() const
{

}

void Rewards::update()
{
	// mueve al laser
	move();

	// actualiza el rect (colisiones)
	updateRect();

	if (isOut()) {

	}

	// le pregunta si hay alguien a quien pegar un hostion
	if (playState->mayGrantReward(destRect) && !isOut()) {
		emit();
	}
}

bool Rewards::isOut()
{
	return (this->position.getY() >= winHeight);
}

void Rewards::move()
{
	// mueve la reward
	position.setY(position.getY() - (vel.getY() * REWARD_SPEED));
}

void Rewards::updateRect()
{
	// posicion               
	destRect.x = position.getX();
	destRect.y = position.getY();
}

void Rewards::connectReward(SDLEventCallback rewardCallback)
{
	callbacks.push_back(rewardCallback);
}