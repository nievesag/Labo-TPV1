#include "ScrollImage.h"
#include "SDLApplication.h"

ScrollImage::ScrollImage(Point2D<double> position, int width, int height, Texture* texture, GameState* game):
	SceneObject(position, width, height, texture, game)
{
	vel.setY(-1);
	vel.setX(0);
}

void ScrollImage::render() const
{

}

void ScrollImage::update()
{
	// mueve la imagen
	move();

	// actualiza el rect
	updateRect();

	// si se ha salido
	if (isOut()) 
	{
		// le dice al game que ha muerto
		playState->hasDied(sceneanc);

		// cambia de estado
	}
}

bool ScrollImage::isOut() const
{
	return (position.getY() + texture->getFrameHeight() >= winHeight);
}

void ScrollImage::move()
{
	// mueve al laser
	position.setY(position.getY() - (vel.getY() * LASER_SPEED));
}

void ScrollImage::updateRect()
{
	// posicion               
	destRect.x = position.getX();
	destRect.y = position.getY();
}