#ifndef BOMB_H
#define BOMB_H

#include "SceneObject.h"
#include "checkML.h"

using namespace std;
using uint = unsigned int;

class Bomb : public SceneObject
{
private:

	Vector2D<double> vel;
	bool alive;

public:
	// ---- constructora ----
	Bomb(Point2D<double> position, int width, int height, int vidas, Texture* texture, PlayState* game)
		: SceneObject(position, width, height, vidas, texture, game)
	{
		// inicializa alive a true al construirse
		alive = true;
	};

	// ---- render ----
	void render() const override;

	// ---- update ----
	void update() override;

	// ---- hit ----
	// colisiones
	bool hit(SDL_Rect* rect, char frenemy) override;

	// devuelve si esta fuera del marco de juego 
	bool isOut();

	// devuelve si esta vivo el laser
	bool IsAlive() { return alive; }

protected:
	// mueve la bomba segun el vector velocidad
	void move();

	// actualiza el rect
	void updateRect() override;
};

#endif