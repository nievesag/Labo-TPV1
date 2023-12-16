#ifndef REWARDS_H
#define REWARDS_H

#include "SceneObject.h"
#include "checkML.h"

using namespace std;
using uint = unsigned int;

// recompensa de inmunidad (clase extensible)
class Rewards : public SceneObject
{
	// atributos privados
private:
	// inmunidad 'i' si es la reward de inmunidad
	// (aqui solo hay una reward pero asi es extnsible si hubiese mas)
	char rewardType;

	SDL_Rect* rect;

	Vector2D<double> vel;

	// metodos publicos
public: 
	// ---- constructora ----
	Rewards(char type, Point2D<double> position, int width, int height, int vidas, Texture* texture, PlayState* game)
		: rewardType(type), SceneObject(position, width, height, vidas, texture, game)
	{ };

	// ---- render ----
	void render() const override;

	// ---- update ----
	void update() override;

	// ---- hit ----
	// colision con la nave
	bool obtain(SDL_Rect* rect, char frenemy);

	// devuelve si esta fuera del marco de juego 
	bool isOut();

	// mueve la reward segun el vector velocidad
	void move();

	// actualiza el rect
	void updateRect() override;
};

#endif