#include "ScreenSaverObject.h"
#include "../SDLApplication.h"
#include "../checkML.h"

ScreenSaverObject::ScreenSaverObject(Point2D<double> position, int width, int height, Texture* texture, GameState* game)
	: SceneObject(position, width, height, texture, game)
{
	spawn.setX(winWidth);
	spawn.setY(300);
}

void ScreenSaverObject::render() const
{
	texture->renderFrame(destRect, 0, 0);
}

void ScreenSaverObject::update()
{
	// mueve la imagen
	move();

	// actualiza el rect
	updateRect();

	if(isOut())
	{
		position.setX(spawn.getX());
	}
}

bool ScreenSaverObject::isOut() const
{
	return (this->position.getX() + texture->getFrameWidth() <= 0);
}

void ScreenSaverObject::move()
{
	// mueve al ufo
	position.setX(position.getX() - vel);
}

void ScreenSaverObject::updateRect()
{
	// posicion               
	destRect.x = position.getX();
	destRect.y = position.getY();
}