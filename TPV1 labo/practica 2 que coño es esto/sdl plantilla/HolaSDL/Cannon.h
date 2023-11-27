#ifndef CANNON_H
#define CANNON_H

#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"
#include "GameObject.h"

// PLACEHOLDERRRRR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include "Game.h"

using namespace std;
using uint = unsigned int;

class Cannon : public SceneObject
{
	// atributos privados
private:

	// input
	bool keyA = false, keyD = false, keyE = false, keySpace = false;

	// metodos publicos 
public:
	// ---- constructora ----
	Cannon(SDL_Rect destRect, Point2D<double> position, int width, int height, int vidas, Texture* texture, Game* game)
		: SceneObject(destRect, position, width, height, vidas, texture, game)  { };

	// aqui si van los overrides porque aqui se especifican las cositas
	//
	void render() const override;

	//
	void update() override;

	//
	void save(ostream&) const override;

	// getter de vidas restantes
	int getLives() {
		return vidas;
	}

	// manejo de eventos del player
	void handleEvent(SDL_Event event);

	// ---- hit ----
	// colisiones
	bool hit(SDL_Rect* rect, char frenemy) override;

	//
	void updateRect() override;

private:
	// movimiento de la nave
	void movement();

	// disparos de la nave
	void shoot();
};

#endif