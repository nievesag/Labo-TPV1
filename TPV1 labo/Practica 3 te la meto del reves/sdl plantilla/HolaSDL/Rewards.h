#ifndef REWARDS_H
#define REWARDS_H

#include "SceneObject.h"
#include "checkML.h"
#include "cannon.h"

using namespace std;
using uint = unsigned int;

// utiliza callbacks funcionales de tipo <void(void)>
//using SDLEventCallback = function<void(void)>;

// recompensa de inmunidad (clase extensible)
class Rewards : public SceneObject
{
	// atributos privados
private:

	SDL_Rect* rect;
	Texture* rewardTexture;

	Vector2D<double> vel;

	SDLEventCallback rewardCallback;

	// CALLBACKS: funcion ejecutable «A» que se usa como argumento de función «B». 
	// -> al llamar a «B» la funcion ejecuta «A»
	// lista de funciones a llamar cuando sucede un evento
	list<SDLEventCallback> callbacks;

	// metodos publicos
public: 
	// ---- constructora ----
	Rewards(Point2D<double> position, int width, int height, Texture* rewardTexture, PlayState* game, SDLEventCallback rewardCallback);

	// ---- render ----
	void render() const override;

	// ---- update ----
	void update() override;

	// devuelve si esta fuera del marco de juego 
	bool isOut();

	// mueve la reward segun el vector velocidad
	void move();

	// actualiza el rect
	void updateRect() override;
};

#endif