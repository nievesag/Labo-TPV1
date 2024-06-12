#pragma once
#include "../GameObjects/SceneObject.h"

class ScrollImage : public SceneObject
{
	Vector2D<double> vel;

	bool finish;

public:
	// ---- constructora ----
	ScrollImage(Point2D<double> position, int width, int height, Texture* texture, GameState* game);

	// ---- render ----
	void render() const override;

	// ---- update ----
	void update() override;

	// devuelve si esta fuera del marco de juego 
	bool isOut() const;

	bool getFinish() const
	{
		return finish;
	}

protected:
	// mueve el laser segun el vector velocidad
	void move();

	// actualiza el rect
	void updateRect() override;
};