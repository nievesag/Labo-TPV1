#ifndef REWARDS_H
#define REWARDS_H

#include "SceneObject.h"
#include "checkML.h"
#include "cannon.h"

using namespace std;
using uint = unsigned int;

// utiliza callbacks funcionales de tipo <void(void)>
using SDLEventCallback = function<void(void)>;

// recompensa de inmunidad (clase extensible)
class Rewards : public SceneObject
{
	// atributos privados
private:
	SDL_Rect* rect;

	Cannon* cannon;

	Vector2D<double> vel;

	SDLEventCallback callback;

	// CALLBACKS: funcion ejecutable «A» que se usa como argumento de función «B». 
	// -> al llamar a «B» la funcion ejecuta «A»
	// lista de funciones a llamar cuando sucede un evento
	list<SDLEventCallback> callbacks;

	// METODOS PRIVADOS
	void emit() const;

	// metodos publicos
public: 
	// ---- constructora ----
	Rewards(SDLEventCallback callback, char type, Point2D<double> position, int width, int height, int vidas, Texture* texture, PlayState* game)
		: callback(callback), SceneObject(position, width, height, vidas, texture, game)
	{ };

	// ---- render ----
	void render() const override;

	// ---- update ----
	void update() override;

	// ---- hit ----
	// colision con la nave
	//bool obtain(SDL_Rect* rect, char frenemy);

	// devuelve si esta fuera del marco de juego 
	bool isOut();

	// mueve la reward segun el vector velocidad
	void move();

	// actualiza el rect
	void updateRect() override;

	// PARA CALLBACKS
	void connectReward(SDLEventCallback rewardCallback);
};

#endif