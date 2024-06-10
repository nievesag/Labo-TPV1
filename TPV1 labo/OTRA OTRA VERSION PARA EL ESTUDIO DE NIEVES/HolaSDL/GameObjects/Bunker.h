#ifndef BUNKER_H
#define BUNKER_H

#include "../Vector2D.h"
#include "../texture.h"
#include "SceneObject.h"
#include "GameObject.h"

class PlayState;

class Bunker : public SceneObject
{
private:
	int hits;	// contador de golpes

	// metodos publicos
public:
	// atributos privados
	// ---- constructora ----
	Bunker(int hits, Point2D<double> position, int width, int height, int vidas, Texture* texture, PlayState* game)
		: hits(hits), SceneObject(position, width, height, vidas, texture, game) { };

	// ---- render ----
	// renderiza
	void render() const override;

	// ---- update ----
	// actualiza
	void update() override;

	// ---- hit ----
	// colisiones
	bool hit(SDL_Rect* rect, Weapon* frenemy) override;

	void updateRect() override;

	// ---- save ----
	// guarda objeto
	void save(std::ostream& out) const override;
};

#endif