#include "Rewards.h"
#include "SDLApplication.h"

Rewards::Rewards(Point2D<double> position, int width, int height, Texture* rewardTexture, PlayState* game, SDLEventCallback rewardCallback)
	:  SceneObject(position, width, height, 1, rewardTexture, game), rewardCallback(rewardCallback)
{
	destRect.w = texture->getFrameWidth();
	destRect.h = texture->getFrameHeight();

	vel.setY(-1);
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

		// llama al callback de la reward
		rewardCallback();

		// elimina reward después de colisionar
		playState->hasDied(sceneanc);
	}
	else if (isOut()) {
		// elimina reward si se sale del marco de juego
		playState->hasDied(sceneanc);
	}
}

bool Rewards::isOut() const
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