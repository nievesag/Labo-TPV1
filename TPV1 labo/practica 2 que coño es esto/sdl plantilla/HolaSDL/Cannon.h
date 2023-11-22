#ifndef CANNON_H
#define CANNON_H

#include "texture.h"
#include "SceneObject.h"
#include "GameObject.h"

using namespace std;
using uint = unsigned int;

class Cannon : public SceneObject
{
	// atributos privados
private:

	// metodos publicos 
public:

	// ---- constructora ----
	Cannon( Point2D<double> position, int width, int height, int vidas, Texture* texture, Game* game)
		: SceneObject(position, width, height, vidas, texture, game) { }


	// getter de vidas restantes
	int getLives() {
		return vidas;
	}

	// manejo de eventos del player
	void handleEvent(SDL_Event event);

};

#endif