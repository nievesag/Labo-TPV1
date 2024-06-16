#ifndef INFOBAR_H
#define INFOBAR_H

#include "../checkML.h"

#include <iostream>
#include <SDL.h>
#include "GameObject.h"
#include "../texture.h"
#include "../Font.h"

const std::string fontRoot = "..\\fonts\\font.ttf";

// para mostrar en pantalla las vidas restantes del jugador y su score
class Infobar : public GameObject
{
private:
	Point2D<double> position = Point2D<double>(0, 0);
	Texture* cannonTexture = nullptr; // textura del cannon
	int spacing; // espacios entre vidas

	SDL_Renderer* renderer; // referencia de render de game

	Font* font = new Font(fontRoot, 24); // fuente a usar para el score
	SDL_Color color = { 255, 255, 255 , 255 }; // color de la fuente para score

	int currentLifes; // vidas de cannon
	int currentScore = 0; // score de cannon

public:
	//constructoras
	Infobar() = default;
	Infobar(const Point2D<double>& position, Texture* cannonTexture, int spacing, GameState* gameState, SDL_Renderer* renderer);

	// destructora
	~Infobar();

	// ---- setters ----
	// settea el score
	void setScore(int value) { currentScore = value; }

	// setter las vidas
	void setLifes(int value) { currentLifes = value; }

	// ---- bloques de renderizado ----
	void renderLifes() const;
	void renderScore() const;

	// ---- generales ----
	void render() const override;
	void update() override {};
	void save(std::ostream& os) const override {}
};

#endif