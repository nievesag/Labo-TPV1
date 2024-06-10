#ifndef BOMB_H
#define BOMB_H

#include "SceneObject.h"
#include "Weapon.h"
#include "../checkML.h"

class SDLApplication;
class PlayState;

class Bomb : public SceneObject, public Weapon
{
private:
	Vector2D<double> vel;
	bool alive;
	int hits;	// contador de golpes
	char c;

public:
	// ---- constructora ----
	Bomb(char type, Point2D<double> position, int width, int height, int vidas, Texture* texture, PlayState* game)
		: SceneObject(position, width, height, vidas, texture, game), Weapon(type)
	{
		// inicializa alive a true al construirse
		alive = true;

		hits = 0;

		vel.setY(-1);

		c = type;
	};

	// ---- render ----
	void render() const override;

	// ---- update ----
	void update() override;

	// ---- hit ----
	// colisiones
	bool hit(SDL_Rect* rect, Weapon* frenemy) override;

	// devuelve si esta fuera del marco de juego 
	bool isOut() const;

	// devuelve si esta vivo el laser
	bool IsAlive() const { return alive; }

protected:
	// mueve la bomba segun el vector velocidad
	void move();

	// actualiza el rect
	void updateRect() override;
};

#endif