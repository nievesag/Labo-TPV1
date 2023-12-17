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
	// lo mete en el render
	texture->render(destRect);
}

void Rewards::update()
{
	// mueve la reward
	move();

	// actualiza el rect (colisiones)
	updateRect();

	// le pregunta si hay alguien a quien dar reward
	if (playState->mayGrantReward(destRect)) {
		emit();
	}
	else if (isOut()) {
		playState->hasDied(sceneanc);
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