#pragma once
#include "../checkML.h"
#include <SDL.h>

#include "../Vector2D.h"
#include "../texture.h"
#include "SceneObject.h"
#include "GameObject.h"
#include "Weapon.h"

class Mothership;
class SDLApplication;
class PlayState;

class Kamikaze : public SceneObject, public Weapon
{
private:
	Vector2D<double> vel;
	int dir;
	double cooldown;
	Mothership* mothership;	  // puntero a mothership
	Point2D<double> cannonPos;

public:
	Kamikaze(char type, Point2D<double> position, int vidas, int width, int height, Texture* texture, PlayState* game);

	// ---- render ----
	// renderiza
	void render() const override;

	// ---- update ----
	// actualiza
	void update() override;

	// ---- save ----
	// guarda objeto
	void save(std::ostream& out) const override;

	// ---- hit ----
	// colisiones
	bool hit(SDL_Rect* rect, Weapon* frenemy) override;

	void updateRect() override;

	// devuelve si esta fuera del marco de juego 
	bool isOut() const;

protected:
	void move();
};