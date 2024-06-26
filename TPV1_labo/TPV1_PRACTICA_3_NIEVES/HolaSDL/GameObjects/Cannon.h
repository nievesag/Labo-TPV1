#ifndef CANNON_H
#define CANNON_H

#include "../Vector2D.h"
#include "../texture.h"
#include "SceneObject.h"
#include "GameObject.h"
#include "../EventHandler.h"
#include "Button.h"
#include "../GameStates/PlayState.h"
class SDLApplication;

using namespace std;
using uint = unsigned int;

class Cannon : public EventHandler, public SceneObject
{
	// atributos privados
private:

	// input
	bool keyA = false, keyD = false, keyE = false, keySpace = false;

	// cooldown del disparo
	int cooldown;

	// contador del cooldown
	int currentCD;

	// si el cannon tiene la reward de invencibilidad o no
	bool invencibleReward = false; 

	int rewardTimer = 0;
	int maxRewardTimer = 2000;

	int cannonOffsetX = 15, cannonOffsetY = 25;

	int maxLives = 3;

	// metodos publicos 
public:
	// ---- constructora ----
	Cannon(int cooldown, Point2D<double> position, int width, int height, int vidas, Texture* texture, PlayState* game);

	// ---- aqui si van los overrides porque aqui se especifican las cosas ----

	void render() const override;

	void update() override;

	void save(ostream& out) const override;

	Point2D<double> getPos() const
	{
		return position;
	}

	// getter de vidas restantes
	int getLives() {
		return vidas;
	}

	// setter de vidas
	void setLives(int newVidas) {
		vidas = newVidas;
	}

	// manejo de eventos del player
	void handleEvent(const SDL_Event& event) override;

	// ---- hit ----
	// colisiones
	bool hit(SDL_Rect* rect, Weapon* frenemy) override;

	// actualiza el rect
	void updateRect() override;

	// maneja el cooldown
	void manageRewardDuration();

	void setInvencibleReward();

private:
	// movimiento de la nave
	void movement();

	// disparos de la nave
	void shoot();
};
#endif