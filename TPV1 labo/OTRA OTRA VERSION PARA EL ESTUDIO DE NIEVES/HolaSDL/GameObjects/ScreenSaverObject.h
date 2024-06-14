#pragma once
#include "../GameObjects/SceneObject.h"

class ScreenSaverObject : public SceneObject
{
	int vel = 1;
	Point2D<double> spawn;

public:
	// ---- constructora ----
	ScreenSaverObject(Point2D<double> position, int width, int height, Texture* texture, GameState* game);

	// ---- render ----
	void render() const override;

	// ---- update ----
	void update() override;

	// devuelve si esta fuera del marco de juego 
	bool isOut() const;

protected:
	// mueve el laser segun el vector velocidad
	void move();

	// actualiza el rect
	void updateRect() override;
};