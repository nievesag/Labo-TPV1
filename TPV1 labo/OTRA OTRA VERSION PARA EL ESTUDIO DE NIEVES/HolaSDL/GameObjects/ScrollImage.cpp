#include "ScrollImage.h"
#include "../SDLApplication.h"

ScrollImage::ScrollImage(Point2D<double> position, int width, int height, Texture* texture, GameState* game):
	SceneObject(position, width, height, texture, game)
{
	vel.setY(-1);
	vel.setX(0);
	finish = false;
}

void ScrollImage::render() const
{
	texture->renderRect(destRect);
}

void ScrollImage::update()
{
	if(!finish)
	{
		// mueve la imagen
		move();

		// actualiza el rect
		updateRect();
	}
	
	// si se ha salido
	if (isOut()) 
	{
		// cambia de estado
		finish = true;
	}
}

bool ScrollImage::isOut() const
{
	return (position.getY() + texture->getFrameHeight() <= 0);
}

void ScrollImage::move()
{
	// mueve imagen
	position.setY(position.getY() + (vel.getY() * LASER_SPEED));
}

void ScrollImage::updateRect()
{
	// posicion               
	destRect.x = position.getX();
	destRect.y = position.getY();
}