#ifndef CANNON_H
#define CANNON_H

#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"
#include "GameObject.h"

class Game;

using namespace std;
using uint = unsigned int;

class Cannon : public SceneObject
{
	// atributos privados
private:

	// input
	bool keyA = false, keyD = false, keyE = false, keySpace = false;

	// cooldown del disparo
	int cooldown;

	// contador del cooldown
	int currentCD;

	// metodos publicos 
public:
	// ---- constructora ----
	Cannon(int cooldown, Point2D<double> position, int width, int height, int vidas, Texture* texture, Game* game)
		: cooldown(cooldown), SceneObject(position, width, height, vidas, texture, game) {
		currentCD = 0; 
	};

	// ---- aqui si van los overrides porque aqui se especifican las cosas ----

	void render() const override;

	void update() override;

	void save(ostream& out) const override;

	// getter de vidas restantes
	int getLives() {
		return vidas;
	}

	// manejo de eventos del player
	void handleEvent(SDL_Event event);

	// ---- hit ----
	// colisiones
	bool hit(SDL_Rect* rect, char frenemy) override;

	// actualiza el rect
	void updateRect() override;

	// maneja el cooldown
	void manageCooldown();

private:
	// movimiento de la nave
	void movement();

	// disparos de la nave
	void shoot();
};

#endif